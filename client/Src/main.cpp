#include "main.h"

RakClientInterface *pRakClient = NULL;
int iAreWeConnected = 0, iConnectionRequested = 0, iSpawned = 0, iGameInited = 0, iSpawnsAvailable = 0;
int iReconnectTime = 2 * 1000, iNotificationDisplayedBeforeSpawn = 0;

PLAYERID g_myPlayerID;
char g_szNickName[32];

struct stPlayerInfo playerInfo[MAX_PLAYERS];
struct stVehiclePool vehiclePool[MAX_VEHICLES];

DWORD dwAutoRunTick = GetTickCount();

extern int iMoney, iDrunkLevel, iLocalPlayerSkin;
extern BOOL bIsSpectating;

// 客户端日志文件句柄
FILE *flLog = NULL;

// TextDraw日志文件句柄
FILE *flTextDrawsLog = nullptr;

int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	srand((unsigned int)GetTickCount());

	// 打开客户端日志文件
	flLog = fopen("RakSAMPClient.log", "a");
	if(!flLog)
	{
		MessageBox(NULL, TEXT("客户端日志文件打开失败"), TEXT("错误"),MB_ICONERROR | MB_OK);
		exit(1);
	}

	// 打开TextDraw日志文件
	flTextDrawsLog = fopen( "TextDraws.log", "a" );
	if(!flTextDrawsLog)
	{
		MessageBox(NULL, TEXT("TextDraw日志文件打开失败"), TEXT("错误"),MB_ICONERROR | MB_OK);
		exit(1);
	}
	

	//创建日志流管理对象
	LogManager Log(L"Client.log");
	Settings Set(L"RakSAMPClient.xml");

	//加载设置
	if(!LoadSettings())
	{
		Log.write("加载配置文件失败");
		
		::MessageBox(NULL, TEXT("配置文件加载失败"), TEXT("错误"),MB_ICONERROR | MB_OK);

		//getchar();
		exit(1);
	}

	std::unique_ptr<std::thread> p_wndThread;
	if(Set.IsConsole())
	{
		// 控制台模式
		SetUpConsole();
	}
	else
	{
		// 窗口模式
		SetUpWindow(hInstance, p_wndThread);
		//::Sleep(500); // 等待一段时间初始化窗口
	}

	// RCON 模式
	if(Set.GetRunMode() == run_mode::RCON)
	{
		if(RCONReceiveLoop())
		{
			
			if(flLog != NULL)
			{
				fclose(flLog);
				flLog = NULL;
			}

			return 0;
		}
	}	

	// set up networking
	pRakClient = RakNetworkFactory::GetRakClientInterface();
	if(pRakClient == NULL)
		return 0;

	pRakClient->SetMTUSize(576);

	resetPools(1, 0);
	RegisterRPCs(pRakClient);

	SYSTEMTIME time;
	GetLocalTime(&time);

	char szInfo[400];
	char szLastInfo[400];
	
	int iLastMoney = iMoney;	// 钱
	int iLastDrunkLevel = iDrunkLevel; // 醉酒指数

	int iLastStatsUpdate = GetTickCount();
	
	//主循环体
	while(true)
	{
		UpdateNetwork(pRakClient);

		if(settings.bSpam)
			sampSpam();

		if (settings.bFakeKill)
			sampFakeKill();

		if (settings.bLag)
			sampLag();

		if (settings.bJoinFlood)
			sampJoinFlood();

		if (settings.bChatFlood)
			sampChatFlood();

		if (settings.bClassFlood)
			sampClassFlood();

		processPulsator();
		processBulletFlood();

		if (!iConnectionRequested)
		{
			if(!iGettingNewName)
				sampConnect(settings.server.szAddr, settings.server.iPort, settings.server.szNickname, settings.server.szPassword, pRakClient);
			else
				sampConnect(settings.server.szAddr, settings.server.iPort, g_szNickName, settings.server.szPassword, pRakClient);

			iConnectionRequested = 1;
		}

		
		if (iAreWeConnected && iGameInited)
		{
			//已经连接到服务器且数据已经初始化


			static DWORD dwLastInfoUpdate = GetTickCount();
			if(dwLastInfoUpdate && dwLastInfoUpdate < (GetTickCount() - 1000))
			{
				char szHealthText[16], szArmourText[16];

				if(settings.fPlayerHealth > 200.0f)
					sprintf_s(szHealthText, sizeof(szHealthText), "N/A");
				else
					sprintf_s(szHealthText, sizeof(szHealthText), "%.2f", settings.fPlayerHealth);

				if(settings.fPlayerArmour > 200.0f)
					sprintf_s(szArmourText, sizeof(szArmourText), "N/A");
				else
					sprintf_s(szArmourText, sizeof(szArmourText), "%.2f", settings.fPlayerArmour);

				sprintf_s(szInfo, 400, "Hostname: %s     Players: %d     Ping: %d     Authors: %s\nHealth: %s     Armour: %s     Skin: %d     X: %.4f     Y: %.4f     Z: %.4f     Rotation: %.4f",
				g_szHostName, getPlayerCount(), playerInfo[g_myPlayerID].dwPing, AUTHOR, szHealthText, szArmourText, iLocalPlayerSkin, settings.fNormalModePos[0], settings.fNormalModePos[1], settings.fNormalModePos[2], settings.fNormalModeRot);
				
				if(strcmp(szInfo, szLastInfo) != 0)
				{
					SetWindowText(texthwnd, szInfo);
					sprintf_s(szLastInfo, szInfo);
				}
			}

			if (settings.iUpdateStats)
			{
				if((GetTickCount() - iLastStatsUpdate >= 1000) || iMoney != iLastMoney || iDrunkLevel != iLastDrunkLevel)
				{
					RakNet::BitStream bsSend;

					bsSend.Write((BYTE)ID_STATS_UPDATE);

					iDrunkLevel -= (rand() % settings.iMaxFPS + settings.iMinFPS);

					if(iDrunkLevel < 0)
						iDrunkLevel = 0;

					bsSend.Write(iMoney);
					bsSend.Write(iDrunkLevel);

					pRakClient->Send(&bsSend, HIGH_PRIORITY, RELIABLE, 0);

					iLastMoney = iMoney;
					iLastDrunkLevel = iDrunkLevel;

					iLastStatsUpdate = GetTickCount();
				}
			}

			if(Set.GetRunMode() == run_mode::bare)
				goto bare;

			if(!iSpawned)
			{
				// 还没有出生

				if(settings.iManualSpawn != 0)
				{
					if(!iNotificationDisplayedBeforeSpawn)
					{
						sampRequestClass(settings.iClassID);
						
						//Log.write("Please write !spawn into the console when you're ready to spawn.");

						iNotificationDisplayedBeforeSpawn = 1;
					}
				}
				else
				{
					sampRequestClass(settings.iClassID);
					sampSpawn();

					iSpawned = 1;
					iNotificationDisplayedBeforeSpawn = 1;
				}
			}
			else
			{
				// 已经出生
				
				if(Set.GetRunMode() == run_mode::normal)
				{
					// 常规模式
					if(!bIsSpectating)
					{
						if(settings.AutoGotoCP && settings.CurrentCheckpoint.bActive)
						{
							settings.fNormalModePos[0] = settings.CurrentCheckpoint.fPosition[0];
							settings.fNormalModePos[1] = settings.CurrentCheckpoint.fPosition[1];
							settings.fNormalModePos[2] = settings.CurrentCheckpoint.fPosition[2];
						}

						onFootUpdateAtNormalPos();
					}
					else
						spectatorUpdate();
				}

				// Run autorun commands
				if(settings.iAutorun)
				{
					if(dwAutoRunTick && dwAutoRunTick < (GetTickCount() - 2000))
					{
						static int autorun;
						if(!autorun)
						{
							Log.write("Loading autorun...");
							for(int i = 0; i < MAX_AUTORUN_CMDS; i++)
								if(settings.autoRunCMDs[i].iExists)
									RunCommand(settings.autoRunCMDs[i].szCMD, 1);

							autorun = 1;
						}
					}
				}

				if(Set.GetRunMode() == run_mode::follow)
				{
					// 步行跟随模式

					// 跟随配置文件中的设置的玩家
					// 根据配置文件中的玩家名来获取玩家的id
					PLAYERID copyingID = getPlayerIDFromPlayerName(settings.szFollowingPlayerName);


					if(copyingID != (PLAYERID)-1)
						onFootUpdateFollow(copyingID);
				}

				
				if(Set.GetRunMode() == run_mode::follow_vehicle)
				{
					// 驾驶跟随模式

					// 跟随配置文件中的设置的玩家
					// 根据配置文件中的玩家名来获取玩家的id
					PLAYERID copyingID = getPlayerIDFromPlayerName(settings.szFollowingPlayerName);

					if(copyingID != (PLAYERID)-1)
						inCarUpdateFollow(copyingID, (VEHICLEID)settings.iFollowingWithVehicleID);
				}
			}
		}
bare:;
		Sleep(30);
	}

	// 关闭客户端日志文件句柄
	if(flLog != NULL)
	{
		fclose(flLog);
		flLog = NULL;
	}
	
	// 关闭TextDraw日志文件句柄
	if(flTextDrawsLog != NULL)
	{
		fclose(flTextDrawsLog);
		flTextDrawsLog = NULL;
	}

	return 0;
}

void Log(char *fmt, ...)
{

	SYSTEMTIME time;
	GetLocalTime(&time);

	fprintf(flLog, "[%02d:%02d:%02d.%03d] ", time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);

	char buffer[512];
	memset(buffer, 0, 512);

	va_list args;
	va_start(args, fmt);
	vsprintf_s(buffer, 512, fmt, args);
	va_end(args);

	fprintf(flLog, buffer);

	LPTSTR tbuf = new TCHAR[512];
	wsprintf(tbuf, buffer);

	int lbCount = SendMessage(loghwnd, LB_GETCOUNT, 0, 0);
	WPARAM idx = SendMessage(loghwnd, LB_ADDSTRING, 0, (LPARAM)tbuf);

	SendMessage(loghwnd, LB_SETCURSEL, lbCount - 1, 0);
	SendMessage(loghwnd, LB_SETTOPINDEX, idx, 0);

	fprintf(flLog, "\n");

	fclose(flLog);
}

void SaveTextDrawData ( WORD wTextID, TEXT_DRAW_TRANSMIT *pData, CHAR* cText )
{
	fprintf( flTextDrawsLog, "TextDraw ID: %d, Text: %s\n", wTextID, cText );
	fprintf( flTextDrawsLog, "Flags: box(%i), left(%i), right(%i), center(%i), proportional(%i), padding(%i)\n", pData->byteBox, pData->byteLeft, pData->byteRight, pData->byteCenter, pData->byteProportional, pData->bytePadding );
	fprintf( flTextDrawsLog, "LetterWidth: %.3f, LetterHeight: %.3f, LetterColor: %X, LineWidth: %.3f, LineHeight: %.3f\n", pData->fLetterWidth, pData->fLetterHeight, pData->dwLetterColor, pData->fLineWidth, pData->fLineHeight );
	fprintf( flTextDrawsLog, "BoxColor: %X, Shadow: %i, Outline: %i, BackgroundColor: %X, Style: %i, Selectable: %i\n", pData->dwBoxColor, pData->byteShadow, pData->byteOutline, pData->dwBackgroundColor, pData->byteStyle, pData->byteSelectable );
	fprintf( flTextDrawsLog, "X: %.3f, Y: %.3f, ModelID: %d, RotX: %.3f, RotY: %.3f, RotZ: %.3f, Zoom: %.3f, Colors: %d, %d", pData->fX, pData->fY, pData->wModelID, pData->fRotX, pData->fRotY, pData->fRotZ, pData->fZoom, pData->wColor1, pData->wColor2 );

	fprintf( flTextDrawsLog, "\n\n" );

	fflush( flTextDrawsLog );
}

void gen_random(char *s, const int len)
{
	static const char alphanum[] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";

	for (int i = 0; i < len; ++i)
		s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];

	s[len] = 0;
}
