#ifndef __SETTINGS_H__
#define __SETTINGS_H__

#include <iostream>
#include <string>
#include <windows.h>
#include "../../pugixml/pugixml.hpp"

namespace run_mode
{
	enum eRunModes
	{
		RCON,			// RCON模式
		bare,			// 监听模式
		still,			// 稻草人模式
		normal,			// 常规模式
		follow,			// 步行跟随模式
		follow_vehicle,	// 载具跟随模式
		plauroutes,		//
	};
};

class Settings
{
public:

	// 构造函数
	Settings(const wchar_t *file_name);

	// 是否为控制台模式
	bool IsConsole();

	// 获取客户端运行模式
	int GetRunMode();

private:

	bool m_Console;	// 以控制台模式运行
	bool m_NPC;		// 以NPC身份连接服务器
	int m_RunMode;	// 运行模式
	int m_AutoRun;	//
	int m_Find;		//
	int m_ClassId;	// 玩家类选择器id
	int m_MinFPS;	// 最小FPS值
	int m_MaxFPS;	// 最大FPS值
	std::string m_Version;	// 客户端版本
};

#endif