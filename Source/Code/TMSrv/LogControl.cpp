#include "LogControl.h"

using namespace std;

LogControl::LogControl()
{
	m_sDir = std::string();
	m_pStream = std::make_unique<std::ofstream>();
}

LogControl::~LogControl()
{
	if (!m_sDir.empty())
		m_sDir.clear();

	if (m_pStream.get()->is_open()) {
		m_pStream.get()->close();
		m_pStream.release();
	}
}

void LogControl::Initialize(std::string LogName)
{
	if (this == nullptr) {
		printf("Error in Initialize: this was nullptr");
		return;
	}

	//If filename is empty we can't continue
	if (LogName.empty())
		return;

	//Clear old string
	m_sDir.clear();

	//Set the new directory name as LogName variable
	m_sDir = std::string(LogName);

	//Update the stream to a new one
	if (m_pStream.get()->is_open()) {
		m_pStream.get()->close();
		m_pStream.get()->clear();
		m_pStream.reset();
	}

	m_pStream.get()->open(m_sDir.c_str(), std::ios_base::app);

	return;
}

void LogControl::Reset(std::string LogName)
{
	Initialize(LogName);
	return;
}

void LogControl::WriteLog(std::string Message, std::string MacAddress, std::string IP, std::string Account)
{
	if (this == nullptr) {
		printf("Error in WriteLog::std: this was nullptr");
		return;
	}

	if (m_pStream.get()->is_open())
	{
		struct tm when;
		time_t now;
		time(&now);
		when = *localtime(&now);

		char tmp_msg[1024] = { 0, };

		sprintf_s(tmp_msg, "(%02d/%02d/%04d|%02d:%02d:%02d) [%s|%s|%s] : %s\n",
			when.tm_mday, when.tm_mon + 1, when.tm_year + 1900, when.tm_hour, when.tm_min, when.tm_sec,
			Account.c_str(), MacAddress.c_str(), IP.c_str(), Message.c_str());

		*(m_pStream.get()) << std::string(tmp_msg);
	}
}
