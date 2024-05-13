
#include "stdafx.h"

void Msg_Sf_Br(){
	MessageBoxA(NULL, "XXII\n\nConteúdo suspeito detectado!10", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
}

void Msg_Sf_En(){
	MessageBoxA(NULL, "XXII\n\nAn illegal choice haas been detected!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
}

void Msg_Sf_Page(){
	Sleep(4000);
	ShellExecute(NULL, "open", carrega.HackSplash_WebSite, NULL, NULL, SW_SHOWNORMAL);
}


void Speed_perf(){
	//cout << *(unsigned long*)QueryPerformanceCounter <<endl;
	if (*(unsigned long*)QueryPerformanceCounter != 2337669003){
		if (carrega.Log_Txt_Hack == 1){
			ofstream out("NUI/Log.txt", ios::app);
			out << "\n XXII: ", out << "Speed Hack Detectado!";
			out.close();
		}
		if (carrega.Hack_Log_Upload == 1){
			time_t rawtime;
			struct tm * timeinfo;
			time(&rawtime);
			timeinfo = localtime(&rawtime);
			ofstream out("Log", ios::app);
			out << "\nLocal Time: ", out << asctime(timeinfo);
			out << "XXII:    ", out << "Speed Hack Detectado!";
			out << "\n= = = = = = = = = = = = = = = = = = =";
			out.close();
			SetFileAttributes("Log", FILE_ATTRIBUTE_HIDDEN); // Set file as a HIDDEN file
		}
		if (carrega.Message_Warning_En == 1){
			CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(Msg_Sf_En), NULL, 0, 0);
			Sleep(5000);
			ExitProcess(0);
		}
		if (carrega.Message_Warning_En == 2){
			CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(Msg_Sf_Br), NULL, 0, 0);
			Sleep(5000);
			ExitProcess(0);
		}
		if (carrega.Message_Warning_En == 3){
			CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(Msg_Sf_Page), NULL, 0, 0);
			Sleep(5000);
			ExitProcess(0);
		}
		if (carrega.Message_Warning_En == 0){
			ExitProcess(0);
		}
		else
			ExitProcess(0);
	}
}


void performance(){
	if (carrega.Anti_Kill_Scans == 1)
	{
	again:
		DSPerf(); //Antikill
		Speed_perf();
		Sleep(carrega.DAnti_Speed_P_occours);
		goto again;
	}
	else
	{
	again2:
		Speed_perf();
		Sleep(carrega.DAnti_Speed_P_occours);
		goto again2;
	}
}

void SPerformance(){
	CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(performance), NULL, 0, 0);
}