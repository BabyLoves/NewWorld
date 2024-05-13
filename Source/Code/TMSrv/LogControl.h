#pragma once

#include <memory>
#include <string>
#include <fstream>
#include <stdexcept>

class LogControl
{
public:
	//Directory for current log
	std::string m_sDir;

	//File stream pointer
	std::unique_ptr <std::ofstream> m_pStream;

public:
	//Constructor - Clear all pointers to start with the Log system
	LogControl();

	//Destructor - Leave all info when class terminates
	~LogControl();

	//Initialize the log system
	void Initialize(std::string LogName);

	//Write to the log using std::string
	void WriteLog(std::string Message, std::string MacAddress, std::string IP, std::string Account);

	//Reset the log to a new file
	void Reset(std::string LogName);
	

};

template<typename ... Args>
std::string string_format(const std::string& format, Args ... args)
{
	int size = snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
	if (size <= 0) { throw std::runtime_error("Error during formatting."); }
	std::unique_ptr<char[]> buf(new char[size]);
	snprintf(buf.get(), size, format.c_str(), args ...);
	return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
}