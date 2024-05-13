#pragma once

#include <string>
#include <vector>
#include <memory>

class IPControl
{
private:
	//List with all IPs registered
	std::vector<std::string> m_pList;

public:
	bool isInitialized;

	//Start the class to clear all unecessary infos
	void Initialize();

	//Add a new IP to the list
	void Add(unsigned int IP);

	//Remove element from vector array
	void Remove(unsigned int IP);

	//Clear the IP List
	void Clear();

	//Check if is in the list
	bool Contains(unsigned int IP);

};

extern std::unique_ptr<IPControl> g_pIPControl;
extern std::unique_ptr<IPControl> g_pEventoControl;