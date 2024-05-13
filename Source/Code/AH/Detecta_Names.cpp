
#include "StdAfx.h"

CARREGAR carrega;

void Msg_Nomes_En(){
	MessageBoxA(NULL, "Warning! \n\nInvalid file name detected!", "File Name - Scanner", MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
}

void Msg_nomes_Br(){
	MessageBoxA(NULL, "Alteração detectada! \n\nAtenção! Não modifique o nome dos arquivos do server!", "File Name - Scaner", MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
}

void Msg_nomes_Page(){
	Sleep(4000);
	ShellExecute(NULL, "open", carrega.HackSplash_WebSite, NULL, NULL, SW_SHOWNORMAL);
}

void Nome_Scanner(){
	char * Nome = carrega.Nome_do_Main;
	WIN32_FILE_ATTRIBUTE_DATA wfad;
	if (GetFileAttributesEx(Nome, GetFileExInfoStandard, &wfad) == 0){

		if (carrega.Log_Txt_Hack == 1){
			ofstream out("NUI/Log.txt", ios::app);
			out << "\n XX: O arquivo não existe dentro da pasta:", out << Nome;
			out.close();
		}
		if (carrega.Hack_Log_Upload == 1){
			time_t rawtime;
			struct tm * timeinfo;
			time(&rawtime);
			timeinfo = localtime(&rawtime);
			ofstream out("Log", ios::app);
			out << "\nLocal Time: ", out << asctime(timeinfo);
			out << "XX: O arquivo não existe dentro da pasta: ", out << Nome;
			out << "\n= = = = = = = = = = = = = = = = = = =";
			out.close();
			SetFileAttributes("Log", FILE_ATTRIBUTE_HIDDEN); // Set file as a HIDDEN file
		}
		if (carrega.Message_Warning_En == 1){
			CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(Msg_Nomes_En), NULL, 0, 0);
			Sleep(5000);
			ExitProcess(0);
		}
		if (carrega.Message_Warning_En == 2){
			CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(Msg_nomes_Br), NULL, 0, 0);
			Sleep(5000);
			ExitProcess(0);
		}
		if (carrega.Message_Warning_En == 3){
			CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(Msg_nomes_Page), NULL, 0, 0);
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

//File folder detector
void Nome_Scanner2(){
	char * Nome2 = carrega.Nome_do_Launcher;
	WIN32_FILE_ATTRIBUTE_DATA wfad;
	if (GetFileAttributesEx(Nome2, GetFileExInfoStandard, &wfad) == 0){

		if (carrega.Log_Txt_Hack == 1){
			using namespace std;
			ofstream out("NUI/Log.txt", ios::app);
			out << "\n XX: O arquivo não existe dentro da pasta:  ", out << Nome2;
			out.close();
		}
		if (carrega.Hack_Log_Upload == 1){
			time_t rawtime;
			struct tm * timeinfo;
			time(&rawtime);
			timeinfo = localtime(&rawtime);
			ofstream out("Log", ios::app);
			out << "\nLocal Time: ", out << asctime(timeinfo);
			out << "XX: O arquivo não existe dentro da pasta: ", out << Nome2;
			out << "\n= = = = = = = = = = = = = = = = = = =";
			out.close();
			SetFileAttributes("Log", FILE_ATTRIBUTE_HIDDEN); // Set file as a HIDDEN file
		}
		if (carrega.Message_Warning_En == 1){
			CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(Msg_Nomes_En), NULL, 0, 0);
			Sleep(5000);
			ExitProcess(0);
		}
		if (carrega.Message_Warning_En == 2){
			CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(Msg_nomes_Br), NULL, 0, 0);
			Sleep(5000);
			ExitProcess(0);
		}
		if (carrega.Message_Warning_En == 3){
			CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(Msg_nomes_Page), NULL, 0, 0);
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

//Handle splash Main///////////////////
void Detect_HandlesM(){
	if (carrega.Log_Txt_Hack == 1){
		ofstream out("NUI/Log.txt", ios::app);
		out << "\n XX: Este não é meu nome! Meu nome é: ", out << carrega.Nome_do_Main;
		out.close();
	}
	if (carrega.Hack_Log_Upload == 1){
		time_t rawtime;
		struct tm * timeinfo;
		time(&rawtime);
		timeinfo = localtime(&rawtime);
		ofstream out("Log", ios::app);
		out << "\nLocal Time: ", out << asctime(timeinfo);
		out << "XX: Este não é meu nome! Meu nome é: ", out << carrega.Nome_do_Main;
		out << "\n= = = = = = = = = = = = = = = = = = =";
		out.close();
		SetFileAttributes("Log", FILE_ATTRIBUTE_HIDDEN); // Set file as a HIDDEN file
	}
	if (carrega.Message_Warning_En == 1){
		CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(Msg_Nomes_En), NULL, 0, 0);
		Sleep(5000);
		ExitProcess(0);
	}
	if (carrega.Message_Warning_En == 2){
		CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(Msg_nomes_Br), NULL, 0, 0);
		Sleep(5000);
		ExitProcess(0);
	}
	if (carrega.Message_Warning_En == 3){
		CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(Msg_nomes_Page), NULL, 0, 0);
		Sleep(5000);
		ExitProcess(0);
	}
	if (carrega.Message_Warning_En == 0){
		ExitProcess(0);
	}
	else
		ExitProcess(0);
}

//Handle splash Dll///////////////////
void Detect_HandlesD(){
	if (carrega.Log_Txt_Hack == 1){
		ofstream out("NUI/Log.txt", ios::app);
		out << "\n XX: Este não é meu nome! Meu nome é: ", out << carrega.Nome_da_Dll;
		out.close();
	}
	if (carrega.Hack_Log_Upload == 1){
		time_t rawtime;
		struct tm * timeinfo;
		time(&rawtime);
		timeinfo = localtime(&rawtime);
		ofstream out("Log", ios::app);
		out << "\nLocal Time: ", out << asctime(timeinfo);
		out << "XX: Este não é meu nome! Meu nome é: ", out << carrega.Nome_da_Dll;
		out << "\n= = = = = = = = = = = = = = = = = = =";
		out.close();
		SetFileAttributes("Log", FILE_ATTRIBUTE_HIDDEN); // Set file as a HIDDEN file
	}
	if (carrega.Message_Warning_En == 1){
		CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(Msg_Nomes_En), NULL, 0, 0);
		Sleep(5000);
		ExitProcess(0);
	}
	if (carrega.Message_Warning_En == 2){
		CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(Msg_nomes_Br), NULL, 0, 0);
		Sleep(5000);
		ExitProcess(0);
	}
	if (carrega.Message_Warning_En == 3){
		CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(Msg_nomes_Page), NULL, 0, 0);
		Sleep(5000);
		ExitProcess(0);
	}
	if (carrega.Message_Warning_En == 0){
		ExitProcess(0);
	}
	else
		ExitProcess(0);
}

//File name detector by handle ///////////////////////////////////
int NamesH(const char *filename)
{
	FILE *arquivo;
	if (arquivo = fopen(filename, "r"))
	{
		cout << arquivo << endl;
		fclose(arquivo);
		return 1;
	}
	return 0;
}


void Name_by_Handle(){
	if (!GetModuleHandle(carrega.Nome_do_Main)){
		Detect_HandlesM();
	}
	else
	{
		Sleep(10);
	}

	if (!GetModuleHandle(carrega.Nome_da_Dll)){
		Detect_HandlesD();
	}
	else
	{
		Sleep(10);
	}
}





void Nome_Scan(){
	if (carrega.Anti_Kill_Scans == 1)
	{
	again:
		Dname(); //Antikill
		Nome_Scanner();
		Nome_Scanner2();
		Name_by_Handle();
		Sleep(carrega.DVerifica_occours);
		goto again;
	}
	else
	{
	again2:
		Nome_Scanner();
		Nome_Scanner2();
		Name_by_Handle();
		Sleep(carrega.DVerifica_occours * 50); // x 50 times
		goto again2;
	}
}

void Nomes(){
	CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(Nome_Scan), NULL, 0, 0);
}

