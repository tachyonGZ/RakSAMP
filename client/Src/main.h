#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <memory>
#include <thread>
#include "../../common/common.h"
#include "../../tinyxml/tinyxml.h"

// window stuff
#include <commctrl.h>
#include "resource.h"

// raknet stuff
#include "PacketEnumerations.h"
#include "RakNetworkFactory.h"
#include "RakClientInterface.h"
#include "NetworkTypes.h"
#include "BitStream.h"
#include "StringCompressor.h"

enum eRunModes
{
	RUNMODE_RCON,
	RUNMODE_BARE,
	RUNMODE_STILL,
	RUNMODE_NORMAL,
	RUNMODE_FOLLOWPLAYER,
	RUNMODE_FOLLOWPLAYERSVEHICLE,
	RUNMODE_PLAYROUTES,
};

#pragma warning(disable:4996)

#include "samp_netencr.h"
#include "samp_auth.h"
#include "SAMPRPC.h"
#include "SAMP_VER.h"

#include "netgame.h"
#include "netrpc.h"
#include "localplayer.h"
#include "misc_funcs.h"
#include "CVector.h"
#include "math_stuff.h"
#include "rcon.h"
#include "query.h"
#include "LogManager.h"
#include "Settings.h"

#include "console.h"
#include "window.h"
#include "cmds.h"
#include "xmlsets.h"

struct stVehiclePool
{
	int iDoesExist;
	float fPos[3];
	int iModelID;
};

extern int iAreWeConnected, iConnectionRequested, iSpawned, iGameInited, iSpawnsAvailable;
extern int iReconnectTime;
extern PLAYERID g_myPlayerID;
extern char g_szNickName[32];

extern struct stPlayerInfo playerInfo[MAX_PLAYERS];
extern struct stVehiclePool vehiclePool[MAX_VEHICLES];

extern PLAYERID imitateID;

void handleQueries(char *s, int len);
void Log ( char *fmt, ... );
void SaveTextDrawData ( WORD wTextID, TEXT_DRAW_TRANSMIT *pData, CHAR* cText );
void gen_random(char *s, const int len);
extern RakClientInterface *pRakClient;