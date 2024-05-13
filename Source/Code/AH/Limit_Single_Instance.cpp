
#include "StdAfx.h"
#include "LimitSingleInstance.h"

void Close_Instances2(){
	HWND WinClasse = FindWindowExA(NULL, NULL, carrega.MainClassName, NULL);
	if (WinClasse > 0){
		SendMessage(WinClasse, WM_CLOSE, 0, 0);
		HWND WinTitle = FindWindowA(NULL, carrega.MainWindowName);
		if (WinTitle != 0){
			SendMessage(WinTitle, WM_CLOSE, 0, 0);
		}
	}
}

void Close_Instances(){
	CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(Close_Instances2), NULL, 0, 0);
}


void Msg_SI_Br(){
	MessageBoxA(NULL, "V\n\nAnti-kill permite apenas uma instancia de jogo aberta!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
}
void Msg_SI_En(){
	MessageBoxA(NULL, "V\n\nAnti-kill active! just one Game instance allowed!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
}

void Msg_SI_Page(){
	Sleep(4000);
	ShellExecute(NULL, "open", carrega.HackSplash_WebSite, NULL, NULL, SW_SHOWNORMAL);
}

void LimiteMainActvity(){
	if (carrega.Log_Txt_Hack == 1){
		ofstream out("NUI/Log.txt", ios::app);
		out << "\n V:  ", out << "Anti-kill active! just one Game instance allowed!";
		out.close();
	}
	if (carrega.Hack_Log_Upload == 1){
		time_t rawtime;
		struct tm * timeinfo;
		time(&rawtime);
		timeinfo = localtime(&rawtime);
		ofstream out("Log", ios::app);
		out << "\nLocal Time: ", out << asctime(timeinfo);
		out << "V:    ", out << "Anti-kill Active! just one Game instance allowed!";
		out << "\n= = = = = = = = = = = = = = = = = = =";
		out.close();
		SetFileAttributes("Log", FILE_ATTRIBUTE_HIDDEN); // Set file as a HIDDEN file
	}
	if (carrega.Message_Warning_En == 1){
		CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(Msg_SI_En), NULL, 0, 0);
		Sleep(4000);
		Close_Instances();
		Sleep(1000);
		ExitProcess(0);
	}
	if (carrega.Message_Warning_En == 2){
		CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(Msg_SI_Br), NULL, 0, 0);
		Sleep(4000);
		Close_Instances();
		Sleep(1000);
		ExitProcess(0);
	}
	if (carrega.Message_Warning_En == 3){
		CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(Msg_SI_Page), NULL, 0, 0);
		Sleep(4000);
		Close_Instances();
		Sleep(1000);
		ExitProcess(0);
	}
	if (carrega.Message_Warning_En == 0){
		Close_Instances();
		Sleep(1000);
		ExitProcess(0);
	}
	else
		Close_Instances();
	Sleep(1000);
	ExitProcess(0);
}



// The one and only CLimitSingleInstance object.
CLimitSingleInstance g_SingleInstanceObj(TEXT("Global\\{G4ATBCE5-7348-450a-B2YC-CVL5XBF12X3D}"));  //PERSONALIZE THIS LINE FOR MORE SECURITY
int SingleMain(int argc, char* argv[])
{
	if (g_SingleInstanceObj.IsAnotherInstanceRunning())
		LimiteMainActvity();
	return 0;
}


void LoadSingleInstance(){
	CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(SingleMain), NULL, 0, 0);
}