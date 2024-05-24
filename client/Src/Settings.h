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
		RCON,			// RCONģʽ
		bare,			// ����ģʽ
		still,			// ������ģʽ
		normal,			// ����ģʽ
		follow,			// ���и���ģʽ
		follow_vehicle,	// �ؾ߸���ģʽ
		plauroutes,		//
	};
};

class Settings
{
public:

	// ���캯��
	Settings(const wchar_t *file_name);

	// �Ƿ�Ϊ����̨ģʽ
	bool IsConsole();

	// ��ȡ�ͻ�������ģʽ
	int GetRunMode();

private:

	bool m_Console;	// �Կ���̨ģʽ����
	bool m_NPC;		// ��NPC������ӷ�����
	int m_RunMode;	// ����ģʽ
	int m_AutoRun;	//
	int m_Find;		//
	int m_ClassId;	// �����ѡ����id
	int m_MinFPS;	// ��СFPSֵ
	int m_MaxFPS;	// ���FPSֵ
	std::string m_Version;	// �ͻ��˰汾
};

#endif