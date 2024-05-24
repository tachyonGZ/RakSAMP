#include "settings.h"

// ���캯��
Settings::Settings(const wchar_t *file_name)
{
	using namespace pugi;

	// xml�����ļ�����
	xml_document doc;
	
	// ��������ĵ�ʧ��
	if(doc.load_file(file_name, parse_default, encoding_utf8).status != status_ok)
	{
		MessageBox(NULL,TEXT("XML�����ļ�����ʧ��"),TEXT("����"),MB_OK | MB_ICONERROR);
		exit(1);
	}

	// ��ȡRakSAMPClient�ڵ�
	xml_node node_root = doc.child("Client");

	// ��ȡconsole����
	this->m_Console = node_root.attribute("console").as_int();
	
	// ��ȡnpc����
	this->m_NPC = node_root.attribute("npc").as_int();

	// ��ȡrunmode����
	this->m_RunMode = node_root.attribute("runmode").as_int();

	// ��ȡautorun����
	this->m_AutoRun = node_root.attribute("autorun").as_int();

	// ��ȡfind����
	this->m_Find = node_root.attribute("find").as_int();

	//��ȡselect_classid����
	this->m_ClassId = node_root.attribute("classid").as_int();

	//��ȡminfps����
	this->m_MinFPS = node_root.attribute("minfps").as_int();

	//��ȡmaxfps����
	this->m_MaxFPS = node_root.attribute("maxfps").as_int();

	//��ȡversion����
	this->m_Version = node_root.attribute("version").as_string();
}

// �Ƿ��Կ���̨��������
bool Settings::IsConsole()
{
	return m_Console;
}

// �Ƿ���NPC������ӵ�������
/*
bool Settings::IsNPC()
{
	return m_NPC;
}
*/

// ��ȡ�ͻ�������ģʽ
int Settings::GetRunMode()
{
	return this->m_RunMode;
}