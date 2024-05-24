#include "LogManager.h"

//构造函数
LogManager::LogManager(const std::wstring file_name)
{
	this->m_LogStrm.open(file_name, std::ios::out);

	// 打开日志文件失败
	if(!this->m_LogStrm.is_open())
	{
		MessageBox(NULL, TEXT("日志文件打开失败"), TEXT("发生了一个致命的错误"),MB_ICONERROR | MB_OK);
	}
}

//析构函数
LogManager::~LogManager()
{
	this->m_LogStrm.close();
}

//在日志中打印一条信息
void LogManager::write(const std::string &fmt)
{
	char s_time[32];	// 存储当前时间的字符串
	SYSTEMTIME time;	//系统时间

	//获取当前系统时间
	GetLocalTime(&time);

	// 格式化当前时间字符串
	sprintf_s(s_time,sizeof(s_time),"[%02d:%02d:%02d.%03d]",time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);

	// 格式化成一行打印到日志文件中
	this->m_LogStrm << s_time << fmt << std::endl;
}