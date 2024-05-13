#include "IPControl.h"

std::unique_ptr<IPControl> g_pIPControl;
std::unique_ptr<IPControl> g_pEventoControl;

//g_pIPControl.get()->Initialize();
void IPControl::Initialize()
{
	if (isInitialized)
		return;

	m_pList = std::vector<std::string>{};

	m_pList.clear();

	isInitialized = true;
}

//g_pIPControl.get()->Clear();
void IPControl::Clear()
{
	if (m_pList.size() != 0)
		m_pList.clear();
}

//g_pIPControl.get()->Add(pUser[conn].IP);
void IPControl::Add(unsigned int IP)
{
	if (!isInitialized)
		Initialize();

	char tmp[32] = { 0, };
	sprintf_s(tmp, "%d.%d.%d.%d",
		IP & 0xFF,
		(IP >> 8) & 0xFF,
		(IP >> 16) & 0xFF,
		(IP >> 24) & 0xFF);

	m_pList.push_back(std::string(tmp));
}

void IPControl::Remove(unsigned int IP)
{
	if (!isInitialized)
		Initialize();

	char tmp[32] = { 0, };
	sprintf_s(tmp, "%d.%d.%d.%d",
		IP & 0xFF,
		(IP >> 8) & 0xFF,
		(IP >> 16) & 0xFF,
		(IP >> 24) & 0xFF);

	std::string currentIp = std::string(tmp);

	int i = 0;

	for (auto el : m_pList)
	{
		if (el == currentIp)
		{
			m_pList.erase(m_pList.begin() + i);
			break;
		}

		i++;
	}

	return;
}

//g_pIPControl.get()->Contains(pUser[conn].IP);
bool IPControl::Contains(unsigned int IP)
{
	if (!isInitialized)
		Initialize();

	if (m_pList.size() == 0)
		return false;

	char tmp[32] = { 0, };
	sprintf_s(tmp, "%d.%d.%d.%d",
		IP & 0xFF,
		(IP >> 8) & 0xFF,
		(IP >> 16) & 0xFF,
		(IP >> 24) & 0xFF);

	std::string currentIp = std::string(tmp);

	for (auto i : m_pList)
	{
		if (i == currentIp)
			return true;
	}

	return false;
}