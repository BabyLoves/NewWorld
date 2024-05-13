
#include "StdAfx.h"

void Msg_PK_Br(){
	MessageBoxA(NULL, "IV\n\nO Launcher não respondeu!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
}
void Msg_PK_En(){
	MessageBoxA(NULL, "IV\n\nLauncher response not found!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
}
void Msg_PK_Page(){
	Sleep(4000);
	ShellExecute(NULL, "open", carrega.HackSplash_WebSite, NULL, NULL, SW_SHOWNORMAL);
}


void PipeKill(){
	if (carrega.Log_Txt_Hack == 1){
		ofstream out("NUI/Log.txt", ios::app);
		out << "\n IV:  ", out << carrega.Launcher_Window << " response not found!";
		out.close();
	}
	if (carrega.Hack_Log_Upload == 1){
		time_t rawtime;
		struct tm * timeinfo;
		time(&rawtime);
		timeinfo = localtime(&rawtime);
		ofstream out("Log", ios::app);
		out << "\nLocal Time: ", out << asctime(timeinfo);
		out << "IV:    ", out << carrega.Launcher_Window << " response not found!";
		out << "\n= = = = = = = = = = = = = = = = = = =";
		out.close();
		SetFileAttributes("Log", FILE_ATTRIBUTE_HIDDEN); // Set file as a HIDDEN file
	}

	if (carrega.Message_Warning_En == 1){
		CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(Msg_PK_En), NULL, 0, 0);
		Sleep(5000);
		ExitProcess(0);
	}
	if (carrega.Message_Warning_En == 2){
		CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(Msg_PK_Br), NULL, 0, 0);
		Sleep(5000);
		ExitProcess(0);
	}
	if (carrega.Message_Warning_En == 3){
		CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(Msg_PK_Page), NULL, 0, 0);
		Sleep(5000);
		ExitProcess(0);
	}
	if (carrega.Message_Warning_En == 0){
		ExitProcess(0);
	}
	else
		ExitProcess(0);
}


//SERVER//////////////////////
void Server1()
{
	while (true)
	{
		//pipe 1 my_pipe
		HANDLE pipe = CreateNamedPipe("\\\\.\\pipe\\my_pipe", PIPE_ACCESS_INBOUND | PIPE_ACCESS_OUTBOUND, PIPE_WAIT, 1, 1024, 1024, 120 * 1000, NULL); //PERSONALIZE NAME PIPE FOR MORE SECURITY
		if (pipe == INVALID_HANDLE_VALUE)
		{
			//cout << "pipe == INVALID_HANDLE_VALUE" << endl;
			PipeKill();
		}
		char data[4];
		DWORD numRead;
		ConnectNamedPipe(pipe, NULL);
		ReadFile(pipe, data, 1024, &numRead, NULL);
		if (numRead > 0)
			cout << data << endl; //DONT TOUCH THIS SHIT!
		CloseHandle(pipe);
	}
}


//CLIENTE//////////////////////////////////////
void Cliente2()
{
	//pipe 2 My_PipeX
	HANDLE pipe = CreateFile("\\\\.\\pipe\\my_pipeX", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL); //PERSONALIZE NAME PIPE FOR MORE SECURITY
	if (pipe == INVALID_HANDLE_VALUE)
	{
		//cout <<"Pipe not found!"<<endl;
		PipeKill();
	}
	string message = "Hi";
	//cout << message.length();
	DWORD numWritten;
	WriteFile(pipe, message.c_str(), message.length(), &numWritten, NULL);
}


void Cliente1(){
	Dpipe(); //Antikill
	Sleep(500);
	Dpipe(); //Antikill
again:
	Sleep(500);
	Dpipe(); //Antikill	
	Cliente2();
	goto again;
}

void ClienteThread(){
	CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(Cliente1), NULL, 0, 0);
}

void ServerThread(){
	CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(Server1), NULL, 0, 0);
}