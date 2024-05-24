#ifndef __LOG_MANAGER_H__
#define __LOG_MANAGER_H__

#include <fstream>
#include <sstream>
#include <cstdio>
#include <windows.h>

class LogManager
{
public:

	//构造函数
	LogManager(const std::wstring file_name);

	//析构函数
	~LogManager();

	//写一条日志
	void write(const std::string &fmt);

	
private:
	std::ofstream m_LogStrm;	// 日志流

};

#endif