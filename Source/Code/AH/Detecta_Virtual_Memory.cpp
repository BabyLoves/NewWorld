
#include "stdafx.h"
//VM-Scan splash////////////////////////////////////////////////////////////
void Msg_VM_Br(){
	MessageBoxA(NULL, "XXIV\n\nConteúdo suspeito detectado!12", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
}
void Msg_VM_En(){
	MessageBoxA(NULL, "XXIV\n\nAn illegal choice haas been detected!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
}

void Msg_VM_Page(){
	Sleep(4000);
	ShellExecute(NULL, "open", carrega.HackSplash_WebSite, NULL, NULL, SW_SHOWNORMAL);
}

void Attack_Value(){
	if (carrega.Log_Txt_Hack == 1){
		ofstream out("NUI/Log.txt", ios::app);
		out << "\n XXIV:  ", out << "Virtual memory Value changed!";
		out.close();
	}
	if (carrega.Message_Warning_En == 1){
		CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(Msg_VM_En), NULL, 0, 0);
		Sleep(5000);
		ExitProcess(0);
	}
	if (carrega.Message_Warning_En == 2){
		CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(Msg_VM_Br), NULL, 0, 0);
		Sleep(5000);
		ExitProcess(0);
	}
	if (carrega.Message_Warning_En == 3){
		CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(Msg_VM_Page), NULL, 0, 0);
		Sleep(5000);
		ExitProcess(0);
	}
	if (carrega.Message_Warning_En == 0){
		ExitProcess(0);
	}
	else
		ExitProcess(0);
}

//VML-Scan splash////////////////////////////////////////////////////////////
void Msg_VML_Br(){
	MessageBoxA(NULL, "XXIV\n\nConteúdo suspeito detectado!13", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
}
void Msg_VML_En(){
	MessageBoxA(NULL, "XXIV\n\nAn illegal choice haas been detected!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
}

void Msg_VML_Page(){
	Sleep(4000);
	ShellExecute(NULL, "open", carrega.HackSplash_WebSite, NULL, NULL, SW_SHOWNORMAL);
}

void Attack_Value2(){
	if (carrega.Log_Txt_Hack == 1){
		ofstream out("NUI/Log.txt", ios::app);
		out << "\n XXIV:  ", out << "Virtual memory value changed!";
		out.close();
	}
	if (carrega.Message_Warning_En == 1){
		CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(Msg_VML_En), NULL, 0, 0);
		Sleep(5000);
		ExitProcess(0);
	}
	if (carrega.Message_Warning_En == 2){
		CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(Msg_VML_Br), NULL, 0, 0);
		Sleep(5000);
		ExitProcess(0);
	}
	if (carrega.Message_Warning_En == 3){
		CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(Msg_VML_Page), NULL, 0, 0);
		Sleep(5000);
		ExitProcess(0);
	}
	if (carrega.Message_Warning_En == 0){
		ExitProcess(0);
	}
	else
		ExitProcess(0);
}

void Msg_VML3_Br(){
	MessageBoxA(NULL, "XXIV\n\nLauncher não encontrado!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
}
void Msg_VML3_En(){
	MessageBoxA(NULL, "XXIV\n\nLauncher not found!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
}

void Msg_VML3_Page(){
	Sleep(4000);
	ShellExecute(NULL, "open", carrega.HackSplash_WebSite, NULL, NULL, SW_SHOWNORMAL);
}

void Attack_Value3(){
	if (carrega.Log_Txt_Hack == 1){
		ofstream out("NUI/Log.txt", ios::app);
		out << "\n XXIV:  ", out << "Launcher not found!";
		out.close();
	}
	if (carrega.Message_Warning_En == 1){
		CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(Msg_VML3_En), NULL, 0, 0);
		Sleep(5000);
		ExitProcess(0);
	}
	if (carrega.Message_Warning_En == 2){
		CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(Msg_VML3_Br), NULL, 0, 0);
		Sleep(5000);
		ExitProcess(0);
	}
	if (carrega.Message_Warning_En == 3){
		CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(Msg_VML3_Page), NULL, 0, 0);
		Sleep(5000);
		ExitProcess(0);
	}
	if (carrega.Message_Warning_En == 0){
		ExitProcess(0);
	}
	else
		ExitProcess(0);
}

////////////////////////////////////////////////////////////////////////////////////////////////
// Virtual Memory protection - VM-Scan 

//How to:
// Use HxD.exe to get address that you want to protect
// For example, run mxmain(fake).exe, open mxmain(fake).exe with HxD (virtual memory), search for string Gasmask, or important value that need be protected on virtual memory.  
// Select G, press CTRL+E (or right click) Select bloc.  That is your addrees. 0x449081
// Turn On carrega.Memory_Buffer_L on START.cpp to get address buffer, add buffer on detector, turn off carrega.Memory_Buffer_L. 
// Change values on memory with HxD to test. (unsigned short) protect 5 hex from start point adrees
////////////////////////////////////////////////////////////////////////////////////////////////


// CHECK LAUNCHER VIRTUAL MEMORY //////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
HANDLE GetProcessHandle(const char *procName);
void Memory_by_window()
{
	HWND handle = FindWindow(0, TEXT(carrega.Launcher_Window));
	if (handle == 0)
	{
		Attack_Value3();  // If not find Window, closes!
		//cout << "VM-Scan failed to find window: "<<carrega.Launcher_Window<<endl;
	}
	else
	{
		DWORD ID;
		GetWindowThreadProcessId(handle, &ID);
		HANDLE hProcess = OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, ID);
		if (!hProcess)
		{
			Attack_Value3();  // If not find Window, closes!
		}
		else
		{
			int buffer;
			char cbuffer[12];
			if (ReadProcessMemory(hProcess, (void *)0x449080, &buffer, 4, NULL)){ //ADRESS HERE!		
				if (carrega.Memory_Buffer_L == 1){
					sprintf(cbuffer, "%d", buffer);
					MessageBoxA(NULL, (LPCSTR)cbuffer, "Memory_Buffer_L", MB_ICONWARNING);
					CloseHandle(hProcess);
					ExitProcess(0);
				}
				else
				{
					//cout<<"Main buffer: "<<buffer<<endl;       
					if (buffer != 1191182336){  //BUFFER HERE!
						Attack_Value2();
						CloseHandle(hProcess);
					}
				}
			}
		}
	}
}



void Launcher_Pro_Start(){
	DVirtualMLauncher(); // Antikill
	if (carrega.Anti_Kill_Scans == 1)
	{
	again:
		DVirtualMLauncher(); //Antikill
		Memory_by_window();
		Sleep(carrega.Virtual_Mem_occours);
		goto again;
	}
	else
	{
	again2:
		Memory_by_window();
		Sleep(carrega.Virtual_Mem_occours);
		goto again2;
	}
}

void Mem_Launcher_Protection(){
	CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(Launcher_Pro_Start), NULL, 0, 0);
}




////////////////////////////////////////////////////////////////////////////////////////////////
// Virtual Memory protection - VM-Scan 

//How to:
// Use HxD.exe to get address that you want to protect
// For example, run mxmain(fake).exe, open mxmain(fake).exe with HxD (virtual memory), search for string Gasmask, or important value that need be protected on virtual memory.  
// Select G, press CTRL+E (or right click) Select bloc.  That is your addrees. 0x449081
// Turn On carrega.Memory_Buffer_L on START.cpp to get address buffer, add buffer on detector, turn off carrega.Memory_Buffer_L. 
// Change values on memory with HxD to test. (unsigned short) protect 5 hex from start point adrees
////////////////////////////////////////////////////////////////////////////////////////////////

// PROTECT MAIN VIRTUAL MEMORY ///////////////////////////////////////
bool Virt()
{
	// GET BUFFER MESSAGE
	if (carrega.Memory_Buffer_P == 1){
		char cbuffer[10];

		//WARNING!  Add an address that not exist on Mxmain.exe will crash Mxmain.exe

		sprintf(cbuffer, "%d", (*(unsigned short*)0x449081));  //Put ADDRESS here, this is for [carrega.Memory_Buffer_P]                    
		MessageBoxA(NULL, (LPCSTR)cbuffer, "Memory_Buffer_P___", MB_ICONWARNING);
		ExitProcess(0);
	}

	//WARNING!  Add an address that not exist on Mxmain.exe will crash Mxmain.exe

	//DETECTOR - Protect 5 hex from address start point
	//((*(unsigned short*)0xADDRESS != BUFFER)
	if ((*(unsigned short*)0x449081 != 29537) ||
		// (*(unsigned short*)0x449081 != 29537) || 
		// (*(unsigned short*)0x449081 != 29537) || 
		//	(*(unsigned short*)0x449081 != 29537) || 
		//	(*(unsigned short*)0x449081 != 29537) || 
		(*(unsigned short*)0x449081 != 29537)){

		Attack_Value();  //ExitProcess(0);
		return true;
	}
	else
	{
		return false;
	}
}


void VirtA(){
	if (carrega.Anti_Kill_Scans == 1)
	{
	again:
		DVirtualM(); //Antikill
		Virt();
		Sleep(carrega.Virtual_Mem_occours);
		goto again;
	}
	else
	{
	again2:
		Virt();
		Sleep(carrega.Virtual_Mem_occours);
		goto again2;
	}
}

void Virtual_Attack(){
	CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(VirtA), NULL, 0, 0);
}