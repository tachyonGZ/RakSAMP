#include "settings.h"

// 构造函数
Settings::Settings(const wchar_t *file_name)
{
	using namespace pugi;

	// xml配置文件对象
	xml_document doc;
	
	// 如果加载文档失败
	if(doc.load_file(file_name, parse_default, encoding_utf8).status != status_ok)
	{
		MessageBox(NULL,TEXT("XML配置文件加载失败"),TEXT("错误"),MB_OK | MB_ICONERROR);
		exit(1);
	}

	// 读取RakSAMPClient节点
	xml_node node_root = doc.child("Client");

	// 获取console参数
	this->m_Console = node_root.attribute("console").as_int();
	
	// 获取npc参数
	this->m_NPC = node_root.attribute("npc").as_int();

	// 获取runmode参数
	this->m_RunMode = node_root.attribute("runmode").as_int();

	// 获取autorun参数
	this->m_AutoRun = node_root.attribute("autorun").as_int();

	// 获取find参数
	this->m_Find = node_root.attribute("find").as_int();

	//获取select_classid参数
	this->m_ClassId = node_root.attribute("classid").as_int();

	//获取minfps参数
	this->m_MinFPS = node_root.attribute("minfps").as_int();

	//获取maxfps参数
	this->m_MaxFPS = node_root.attribute("maxfps").as_int();

	//获取version参数
	this->m_Version = node_root.attribute("version").as_string();
}

// 是否以控制台窗口运行
bool Settings::IsConsole()
{
	return m_Console;
}

// 是否以NPC身份连接到服务器
/*
bool Settings::IsNPC()
{
	return m_NPC;
}
*/

// 获取客户端运行模式
int Settings::GetRunMode()
{
	return this->m_RunMode;
}