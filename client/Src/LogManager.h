#ifndef __LOG_MANAGER_H__
#define __LOG_MANAGER_H__

#include <fstream>
#include <sstream>
#include <cstdio>
#include <windows.h>

class LogManager
{
public:

	//���캯��
	LogManager(const std::wstring file_name);

	//��������
	~LogManager();

	//дһ����־
	void write(const std::string &fmt);

	
private:
	std::ofstream m_LogStrm;	// ��־��

};

#endif