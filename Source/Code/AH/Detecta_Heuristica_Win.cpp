
#include "StdAfx.h"


void Msg_WIN_Br(){
	MessageBoxA(NULL, "XVII\n\nConteúdo suspeito detectado!6", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
}
void Msg_WIN_En(){
	MessageBoxA(NULL, "XVII\n\nAn illegal choice haas been detected!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
}

void Msg_WIN_Page(){
	Sleep(4000);
	ShellExecute(NULL, "open", carrega.HackSplash_WebSite, NULL, NULL, SW_SHOWNORMAL);
}

BOOL CALLBACK heurprocess(HWND hwnd, LPARAM lParam){
	static TCHAR x[40];
	GetWindowText(hwnd, x, 40);

	////////////////////////////////////////////////////////////////////////////////////////////////
	//Heuristic Window name scan - HW-scan 
	//Are Case-sensitive - Find it just looking window name or using [Handler 1.5 by Oliver Bock] 
	//_tcsstr(x,"xxx") Just one word, without empty space
	////////////////////////////////////////////////////////////////////////////////////////////////

	if (
		_tcsstr(x, "BYPASS") ||
		_tcsstr(x, "ByPass") ||
		_tcsstr(x, "byPass") ||
		_tcsstr(x, "Bypass") ||
		_tcsstr(x, "DUPAR") ||
		_tcsstr(x, "Dupar") ||
		_tcsstr(x, "dupar") ||
		_tcsstr(x, "DUPER") ||
		_tcsstr(x, "Duper") ||
		_tcsstr(x, "duper") ||
		_tcsstr(x, "FREEZE") ||
		_tcsstr(x, "Freeze") ||
		_tcsstr(x, "freeze") ||
		_tcsstr(x, "SPEED") ||
		_tcsstr(x, "Speed") ||
		_tcsstr(x, "Speed") ||
		_tcsstr(x, "HACK") ||
		_tcsstr(x, "Hack") ||
		_tcsstr(x, "hack") ||
		_tcsstr(x, "HACKER") ||
		_tcsstr(x, "Hacker") ||
		_tcsstr(x, "hacker") ||
		_tcsstr(x, "INJECT") ||
		_tcsstr(x, "Inject") ||
		_tcsstr(x, "inject") ||
		_tcsstr(x, "INJECTOR") ||
		_tcsstr(x, "Injector") ||
		_tcsstr(x, "injector") ||
		_tcsstr(x, "KILL") ||
		_tcsstr(x, "Kill") ||
		_tcsstr(x, "kill") ||
		_tcsstr(x, "OLLY") ||
		_tcsstr(x, "Olly") ||
		_tcsstr(x, "olly") ||
		_tcsstr(x, "PACKAGER") ||
		_tcsstr(x, "Packager") ||
		_tcsstr(x, "Packager") ||

		_tcsstr(x, "WPE") ||
		_tcsstr(x, "Wpe") ||
		_tcsstr(x, "wpe") ||
		_tcsstr(x, "XTRAP") ||
		_tcsstr(x, "XTrap") ||
		_tcsstr(x, "xtrap") ||
		_tcsstr(x, "XSPEED") ||
		_tcsstr(x, "XSpeed") ||
		_tcsstr(x, "xSpeed") ||
		_tcsstr(x, "xspeed") ||
		_tcsstr(x, "Injetor") ||
		_tcsstr(x, "DLL") ||
		_tcsstr(x, ".dll") ||

		_tcsstr(x, "AUTOKILL") ||
		_tcsstr(x, "Autokill") ||
		_tcsstr(x, "autokill") ||
		_tcsstr(x, "AGILITY") ||
		_tcsstr(x, "Agility") ||
		_tcsstr(x, "agility") ||
		_tcsstr(x, "PACKET") ||
		_tcsstr(x, "Packet") ||
		_tcsstr(x, "packet") ||
		_tcsstr(x, "AUTOIT") ||
		_tcsstr(x, "AutoIt") ||
		_tcsstr(x, "autoit") ||
		_tcsstr(x, "AUTOKEYBOARD") ||
		_tcsstr(x, "AutoKeyboard") ||
		_tcsstr(x, "autokeyboard") ||
		_tcsstr(x, "SANDBOX") ||
		_tcsstr(x, "Sandbox") ||
		_tcsstr(x, "sandbox") ||
		_tcsstr(x, "SANDBOXED") ||
		_tcsstr(x, "Sandboxed") ||
		_tcsstr(x, "sandboxed") ||
		_tcsstr(x, "DEFALTBOX") ||
		_tcsstr(x, "DefaltBox") ||
		_tcsstr(x, "defaltbox") ||
		_tcsstr(x, "HXD") ||
		_tcsstr(x, "HxD") ||
		_tcsstr(x, "hxd") ||
		_tcsstr(x, "AutoClicker") ||
		_tcsstr(x, "Autoclicker") ||
		_tcsstr(x, "autoclicker") ||
		_tcsstr(x, "WHOOK") ||
		_tcsstr(x, "Whook") ||
		_tcsstr(x, "WhooK") ||
		_tcsstr(x, "DEBUG") ||
		_tcsstr(x, "DEBUG") ||
		_tcsstr(x, "Debug") ||
		_tcsstr(x, "debug")){

	}
	/*
if (carrega.Log_Txt_Hack == 1){
ofstream out("NUI/Log.txt", ios::app);
out << "\n XVII:   ", out <<   x;    // printf ("Found Hack = %s " , windowName);
out.close();
}
if (carrega.Hack_Log_Upload == 1){
time_t rawtime;
struct tm * timeinfo;
time (&rawtime);
timeinfo = localtime (&rawtime);
ofstream out("Log", ios::app);
out <<"\nLocal Time: ", out << asctime(timeinfo);
out <<"XVII:    ", out << x;
out << "\n= = = = = = = = = = = = = = = = = = =";
out.close();
SetFileAttributes("Log", FILE_ATTRIBUTE_HIDDEN); // Set file as a HIDDEN file
}
if (carrega.Message_Warning_En == 1){
CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Msg_WIN_En),NULL,0,0);
Sleep(5000);
ExitProcess(0);
}
if (carrega.Message_Warning_En == 2){
CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Msg_WIN_Br),NULL,0,0);
Sleep(500);
ExitProcess(0);
}
if (carrega.Message_Warning_En == 3){
CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Msg_WIN_Page),NULL,0,0);
Sleep(5000);
ExitProcess(0);
}
if (carrega.Message_Warning_En == 0){
ExitProcess(0);
}
else
ExitProcess(0);
return FALSE;
}*/
	//cout <<"true";
	return TRUE;
}


void heuristica(){
	EnumWindows(heurprocess, NULL);
}

void heuristico(){
	if (carrega.Anti_Kill_Scans == 1)
	{
	again:
		DHeuriWin(); //Antikill
		heuristica();
		Sleep(carrega.DHeuristica_Win_occours);
		goto again;
	}
	else
	{
	again2:
		heuristica();
		Sleep(carrega.DHeuristica_Win_occours);
		goto again2;
	}
}

void HeuristicW(){
	CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(heuristico), NULL, 0, 0);
}