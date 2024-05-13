
#include "StdAfx.h"

void Msg_K_Br(){
	MessageBoxA(NULL, "II\n\nA integridade do processo foi corrompida!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
}
void Msg_K_En(){
	MessageBoxA(NULL, "II\n\nFile Integrity violated!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
}
void Msg_K_Page(){
	Sleep(4000);
	ShellExecute(NULL, "open", carrega.HackSplash_WebSite, NULL, NULL, SW_SHOWNORMAL);
}

void DC(){
	if (carrega.Log_Txt_Hack == 1){
		ofstream out("NUI/Log.txt", ios::app);
		out << "\n II:  ", out << "Thread attack!";
		out.close();
	}
	if (carrega.Message_Warning_En == 1){
		CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(Msg_K_En), NULL, 0, 0);
		Sleep(5000);
		ExitProcess(0);
	}
	if (carrega.Message_Warning_En == 2){
		CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(Msg_K_Br), NULL, 0, 0);
		Sleep(5000);
		ExitProcess(0);
	}
	if (carrega.Message_Warning_En == 3){
		CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(Msg_K_Page), NULL, 0, 0);
		Sleep(5000);
		ExitProcess(0);
	}
	if (carrega.Message_Warning_En == 0){
		ExitProcess(0);
	}
	else
		ExitProcess(0);
}

////////////////////////////////////////////

PROCESSENTRY32 *GetProcessInfo(char *szExeFile)
{
	PROCESSENTRY32  *pe32 = new PROCESSENTRY32[sizeof(PROCESSENTRY32)];
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (hSnapshot == INVALID_HANDLE_VALUE)
		return NULL;

	if (!Process32First(hSnapshot, pe32))
	{
		CloseHandle(hSnapshot);
		return NULL;
	}

	while (Process32Next(hSnapshot, pe32))
	{
		if (strcmp(szExeFile, pe32->szExeFile) == 0)
		{
			CloseHandle(hSnapshot);
			return pe32;
		}
	}
	return NULL;
}

void T_Kill()
{
	DKill_t(); //Antikill
	Sleep(carrega.DAnti_Kill_T_occours);
	DKill_t(); //Antikill
	Sleep(carrega.DAnti_Kill_T_occours);
	DKill_t(); //Antikill
	Sleep(carrega.DAnti_Kill_T_occours);

	PROCESSENTRY32 *spe32 = GetProcessInfo(carrega.Nome_do_Main);
again:
	Sleep(carrega.DAnti_Kill_T_occours);
	PROCESSENTRY32 *pe32 = GetProcessInfo(carrega.Nome_do_Main);
	//cout << "AntiKill Threads = firstvalue: "<<spe32->cntThreads <<"  secondvalue: "<<pe32->cntThreads <<endl;
	if (spe32->cntThreads != pe32->cntThreads){
		DC();
		//cout << "DC !" <<endl;	 
	}
	else
	{
		DKill_t(); //Antikill
		delete[] pe32;
		pe32 = NULL;
		goto again;
	}
}


void T_Kills(){
	if (carrega.Anti_Kill_Scans == 1)
	{
		DKill_t(); //Antikill
		T_Kill();
	}
	else
	{
		T_Kill();
	}
}

void AntiKill_T(){
	CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(T_Kills), NULL, 0, 0);
}
