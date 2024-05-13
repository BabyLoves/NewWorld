
#include "stdafx.h"

void Msg_H_Br(){
	MessageBoxA(NULL, "XIV\n\nConteúdo suspeito detectado!3", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
}

void Msg_H_En(){
	MessageBoxA(NULL, "XIV\n\nAn illegal choice haas been detected!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
}

void Msg_H_Page(){
	Sleep(4000);
	ShellExecute(NULL, "open", carrega.HackSplash_WebSite, NULL, NULL, SW_SHOWNORMAL);
}

void TxtCheckWindow()
{
	POINT p;
	HWND DebugerFound = 0;

	for (int qy = 0; qy < 100; qy++)
	{
		for (int qx = 0; qx < 100; qx++)
		{
			p.x = qx * 20;
			p.y = qy * 20;
			DebugerFound = WindowFromPoint(p);
			char t[255];
			GetWindowTextA(DebugerFound, t, 225);
			DHeuri();  //Antikill

			////////////////////////////////////////////////////////////////////////////////////////////////
			//Heuristic scan - H-Scan (Bad words) 
			//Are Case-sensitive - scan Web Brosers
			//strstr(t,"xxxx")    || 
			////////////////////////////////////////////////////////////////////////////////////////////////

			if (strstr(t, "BYPASS") ||
				strstr(t, "ByPass") ||
				strstr(t, "byPass") ||
				strstr(t, "Bypass") ||
				strstr(t, "DUPAR") ||
				strstr(t, "Dupar") ||
				strstr(t, "dupar") ||
				strstr(t, "DUPER") ||
				strstr(t, "Duper") ||
				strstr(t, "duper") ||
				strstr(t, "ENGINE") ||
				strstr(t, "Engine") ||
				strstr(t, "engine") ||
				strstr(t, "FREEZE") ||
				strstr(t, "Freeze") ||
				strstr(t, "freeze") ||
				strstr(t, "SPEED") ||
				strstr(t, "Speed") ||
				strstr(t, "Speed") ||
				strstr(t, "HACK") ||
				strstr(t, "Hack") ||
				strstr(t, "hack") ||
				strstr(t, "HACKER") ||
				strstr(t, "Hacker") ||
				strstr(t, "hacker") ||
				strstr(t, "HIDE") ||
				strstr(t, "Hide") ||
				strstr(t, "hide") ||
				strstr(t, "TOOLZ") ||
				strstr(t, "Toolz") ||
				strstr(t, "toolz") ||
				strstr(t, "INJECT") ||
				strstr(t, "Inject") ||
				strstr(t, "inject") ||
				strstr(t, "INJECTOR") ||
				strstr(t, "Injector") ||
				strstr(t, "injector") ||
				strstr(t, "KILL") ||
				strstr(t, "Kill") ||
				strstr(t, "kill") ||
				strstr(t, "OLLY") ||
				strstr(t, "Olly") ||
				strstr(t, "olly") ||
				strstr(t, "PACKAGER") ||
				strstr(t, "Packager") ||
				strstr(t, "Packager") ||
				strstr(t, "PACOTES") ||
				strstr(t, "Pacotes") ||
				strstr(t, "Pacotes") ||
				strstr(t, "SUSPEND") ||
				strstr(t, "Suspend") ||
				strstr(t, "suspend") ||
				strstr(t, "WILDPROXY") ||
				strstr(t, "Wildproxy") ||
				strstr(t, "wildproxy") ||
				strstr(t, "WPE PRO") ||
				strstr(t, "Wpe Pro") ||
				strstr(t, "wpe pro") ||
				strstr(t, "XELERATOR") ||
				strstr(t, "Xelerator") ||
				strstr(t, "xelerator") ||
				strstr(t, "XTRAP") ||
				strstr(t, "XTrap") ||
				strstr(t, "xtrap") ||
				strstr(t, "XSPEED") ||
				strstr(t, "XSpeed") ||
				strstr(t, "xSpeed") ||
				strstr(t, "xspeed") ||
				strstr(t, "FUNNYZHYPER") ||
				strstr(t, "FunnyZhyper") ||
				strstr(t, "funnyzhyper") ||
				strstr(t, "AUTOKILL") ||
				strstr(t, "Autokill") ||
				strstr(t, "autokill") ||
				strstr(t, "AGILITY") ||
				strstr(t, "Agility") ||
				strstr(t, "agility") ||
				strstr(t, "PACKET") ||
				strstr(t, "Packet") ||
				strstr(t, "packet") ||
				strstr(t, "AUTOIT") ||
				strstr(t, "AutoIt") ||
				strstr(t, "autoit") ||
				strstr(t, "AUTOKEYBOARD") ||
				strstr(t, "AutoKeyboard") ||
				strstr(t, "autokeyboard") ||
				strstr(t, "DEFALTBOX") ||
				strstr(t, "DefaltBox") ||
				strstr(t, "defaltbox") ||
				strstr(t, "HXD") ||
				strstr(t, "HxD") ||
				strstr(t, "hxd") ||
				strstr(t, "BVKHEX") ||
				strstr(t, "Bvkhex") ||
				strstr(t, "bvkhex") ||
				strstr(t, "bvkhex") ||
				strstr(t, "bvkhex") ||
				strstr(t, ".dll") ||
				strstr(t, "Injetor") ||
				strstr(t, "DLL") ||
				strstr(t, "AutoClicker") ||
				strstr(t, "Autoclicker") ||
				strstr(t, "autoclicker"))
			{
				unsigned char * hack = (unsigned char*)GetProcAddress(GetModuleHandleA("kernel32.dll"), "OpenProcess");

				if (*(hack + 6) == 0xEA)
				{
					Sleep(1);
				}
				if (carrega.Log_Txt_Hack == 1)
				{
					ofstream out("NUI/Log.txt", ios::app);
					out << "\n XIV:  ", out << (t);
					out.close();
				}
				if (carrega.Hack_Log_Upload == 1)
				{
					time_t rawtime;
					struct tm * timeinfo;
					time(&rawtime);
					timeinfo = localtime(&rawtime);
					ofstream out("Log", ios::app);
					out << "\nLocal Time: ", out << asctime(timeinfo);
					out << "XIV:     ", out << (t);
					out << "\n= = = = = = = = = = = = = = = = = = =";
					out.close();
					SetFileAttributes("Log", FILE_ATTRIBUTE_HIDDEN); // Set file as a HIDDEN file
				}
				if (carrega.Message_Warning_En == 1)
				{
					CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(Msg_H_En), NULL, 0, 0);
					Sleep(5000);
					ExitProcess(0);
				}
				if (carrega.Message_Warning_En == 2)
				{
					CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(Msg_H_Br), NULL, 0, 0);
					Sleep(500);
					ExitProcess(0);
				}
				if (carrega.Message_Warning_En == 3)
				{
					CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(Msg_H_Page), NULL, 0, 0);
					Sleep(5000);
					ExitProcess(0);
				}
				if (carrega.Message_Warning_En == 0)
				{
					ExitProcess(0);
				}
				else
					ExitProcess(0);
			}
		}
	}
}


void H_Scan()
{
	if (carrega.Anti_Kill_Scans == 1)
	{
	again:
		TxtCheckWindow();
		Sleep(carrega.DHeuristica_occours);
		goto again;
	}
	else
	{
	again2:
		TxtCheckWindow();
		Sleep(carrega.DHeuristica_occours);
		goto again2;
	}
}

void HProtection()
{
	CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(H_Scan), NULL, 0, 0);
}