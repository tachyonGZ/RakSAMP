#include "LogManager.h"

//���캯��
LogManager::LogManager(const std::wstring file_name)
{
	this->m_LogStrm.open(file_name, std::ios::out);

	// ����־�ļ�ʧ��
	if(!this->m_LogStrm.is_open())
	{
		MessageBox(NULL, TEXT("��־�ļ���ʧ��"), TEXT("������һ�������Ĵ���"),MB_ICONERROR | MB_OK);
	}
}

//��������
LogManager::~LogManager()
{
	this->m_LogStrm.close();
}

//����־�д�ӡһ����Ϣ
void LogManager::write(const std::string &fmt)
{
	char s_time[32];	// �洢��ǰʱ����ַ���
	SYSTEMTIME time;	//ϵͳʱ��

	//��ȡ��ǰϵͳʱ��
	GetLocalTime(&time);

	// ��ʽ����ǰʱ���ַ���
	sprintf_s(s_time,sizeof(s_time),"[%02d:%02d:%02d.%03d]",time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);

	// ��ʽ����һ�д�ӡ����־�ļ���
	this->m_LogStrm << s_time << fmt << std::endl;
}