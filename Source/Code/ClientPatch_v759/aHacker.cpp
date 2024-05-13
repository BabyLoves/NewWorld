#include "main.h" 
#include "VirtualizerSDK.h"
 
bool ReadConfig(const char* FileName)
{
	FILE* pFile = NULL;


	pFile = fopen(FileName, "r");


	if (pFile != NULL)
	{
		return true;
	}

	return false;
}

unsigned static long dwRecvCall; // Addr do início da func Recv
unsigned static long dwSendCall; // Addr do início da func Send
unsigned static char bAddr_r[6], bAddr_s[6]; // Bytes iniciais das funções send/recv

void BackupWinsockData() {
	
	LoadLibrary("ws2_32.dll"); // Hook na dll da winsock2
	dwRecvCall = (unsigned long)GetProcAddress(GetModuleHandle("ws2_32.dll"), "recv"); // Seta o valor de dwRecvCall com o addrbase da func Recv
	dwSendCall = (unsigned long)GetProcAddress(GetModuleHandle("ws2_32.dll"), "send"); // Seta o valor de dwSendCall com o addrbase da func Send
	ReadProcessMemory(GetCurrentProcess(), (LPVOID)dwRecvCall, bAddr_r, 6, 0); // Move os bytes iniciais originais da func recv para o buffer
	ReadProcessMemory(GetCurrentProcess(), (LPVOID)dwSendCall, bAddr_s, 6, 0); // Move os bytes iniciais originais da func send para o buffer
	
}
void CloseGame() {
	DWORD exitCode;
	GetExitCodeProcess(GetCurrentProcess(), &exitCode);
	ExitProcess(exitCode);
}
void WINAPI AntiHack() {
	while (true) {
		if (memcmp((LPVOID)dwRecvCall, bAddr_r, 6) != 0) CloseGame(); // Verifica se os bytes iniciais da func Recv estão diferentes do original
		if (memcmp((LPVOID)dwSendCall, bAddr_s, 6) != 0) CloseGame(); // Verifica se os bytes iniciais da func Send estão diferentes do original
		Sleep(1000); // Delay para não dar lag
	}
}
unsigned long __stdcall AntiWPEPro(void* pVoid)
{
	
	bool bHooked = false;
	unsigned char szBuffer[8];

	// First 6 bytes of of Send/Recv
	unsigned char bOriginal[] = "\x55"         // PUSH EBP
		"\x8B\xEC\x83"   // MOV EBP, ESP
		"\xEC\x10";   // SUB ESP, 10

	int i;

	unsigned long dwRecvCall = (unsigned long)GetProcAddress(GetModuleHandle("WS2_32.dll"), "recv");
	unsigned long dwSendCall = (unsigned long)GetProcAddress(GetModuleHandle("WS2_32.dll"), "send");

	while (true)
	{
		ReadProcessMemory(GetCurrentProcess(), (void*)dwRecvCall, szBuffer, 6, 0);

		for (i = 0; i < 6; i++)
		{
			// If we find one part missing, write the original bytes back and break the loop
			if (bOriginal[i] != szBuffer[i])
			{
				WriteProcessMemory(GetCurrentProcess(), (void*)dwRecvCall, bOriginal, 6, 0);
				break;
			}
		}

		ReadProcessMemory(GetCurrentProcess(), (void*)dwSendCall, szBuffer, 6, 0);

		for (i = 0; i < 6; i++)
		{
			// Send + Recvs first 6 bytes are the same, we can use the same buffer
			if (bOriginal[i] != szBuffer[i])
			{
				WriteProcessMemory(GetCurrentProcess(), (void*)dwSendCall, bOriginal, 6, 0);
				break;
			}
		}

		Sleep(500);
	}

	return 0;
	
};


void I_loop()
{
	VIRTUALIZER_TIGER_WHITE_START
	// [NAME.extension] Are NON case-sensitive.
	if (GetModuleHandle("speedhack.dll") ||
		(GetModuleHandle("speed-hack.dll")) ||
		(GetModuleHandle("speed-hack.dll")) ||
		(GetModuleHandle("speed_hack.dll")) ||
		(GetModuleHandle("hack_speed.dll")) ||
		(GetModuleHandle("hack-speed.dll")) ||
		(GetModuleHandle("hackspeed.dll")) ||
		(GetModuleHandle("hack.dll")) ||
		(GetModuleHandle("wpepro.dll")) ||
		(GetModuleHandle("Cr4ck3r.dll")) ||
		(GetModuleHandle("wpeprospy.dll")) ||
		(GetModuleHandle("engine.dll")) ||
		(GetModuleHandle("CheatEngine.dll")) ||
		(GetModuleHandle("c.e.dll")) ||
		(GetModuleHandle("cheat.dll")) ||
		(GetModuleHandle("mukilin.dll")) ||
		(GetModuleHandle("Whook.dll")) ||
		(GetModuleHandle("whook762.dll")) ||
		(GetModuleHandle("hook.dll")) ||
		(GetModuleHandle("wHook.dll")) ||
		(GetModuleHandle("Hook756.dll")) ||
		(GetModuleHandle("WHOOK.dll")) ||
		(GetModuleHandle("whook759.dll")) ||
		(GetModuleHandle("whook.dll"))
		)
	{
		Injetado();
	}
	else
		Sleep(100);
	VIRTUALIZER_TIGER_WHITE_END
}

void Msg_I_Br()
{
	
	MessageBoxA(NULL, "AntiHacker\n\nA integridade do processo foi corrompida!", Config.MsgBox_Title, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
	
}

void Injetado()
{

	if (Config.EnableLogFile == 1)
	{
		using namespace std;
	//	ofstream out("WYD.log", ios::app);
		//out << "\n AntiHacker:  ", out << "File integrity violated!";
	}
	if (Config.SendClientMsg == 2)
	{
		CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(Msg_I_Br), NULL, 0, 0);
		Sleep(5000);
		ExitProcess(0);
	}
	if (Config.SendClientMsg == 0)
	{
		ExitProcess(0);
	}
	else
		ExitProcess(0);
}

void I_Scan()
{
again:
	I_loop();
	Sleep(58000);
	goto again;
}

void Dll_Inject()
{
	CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(I_Scan), NULL, 0, 0);
}

void Msg_W_Br()
{
	VIRTUALIZER_TIGER_WHITE_START
	MessageBoxA(NULL, "AntiHacker\n\nConteúdo suspeito detectado!", Config.MsgBox_Title, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
	VIRTUALIZER_TIGER_WHITE_END
}


bool TitleWindow(LPCSTR WindowTitle)
{
	HWND WinTitle = FindWindowA(NULL, WindowTitle);
	if (WinTitle > 0)
	{

		if (Config.EnableLogFile == 1)
		{
			using namespace std;
		}
		if (Config.SendClientMsg == 2)
		{
			CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(Msg_W_Br), NULL, 0, 0);
			Sleep(5000);
			ExitProcess(0);
		}
		if (Config.SendClientMsg == 0)
		{
			ExitProcess(0);
		}
		else
			ExitProcess(0);
		return false;
	}
	return true;
}


//ANTI HACKER PARA NOMES DE PROGRAMAS PINHEIRO
void TitleCheckWindow()
{
	VIRTUALIZER_TIGER_WHITE_START
		TitleWindow("Cheat Engine 5.0");
	TitleWindow("Cheat Engine 5.1");
	TitleWindow("Cheat Engine 5.1.1");
	TitleWindow("Cheat Engine 5.2");
	TitleWindow("Cheat Engine 5.3");
	TitleWindow("Cheat Engine 5.4");
	TitleWindow("Cheat Engine 5.5");
	TitleWindow("Cheat Engine 5.6");
	TitleWindow("Cheat Engine 5.6.1");
	TitleWindow("Cheat Engine 6.0");
	TitleWindow("Cheat Engine 6.1");
	TitleWindow("Cheat Engine 6.2");
	TitleWindow("Cheat Engine 6.3");
	TitleWindow("Cheat Engine 6.4");
	TitleWindow("Cheat Engine 6.5");
	TitleWindow("Cheat Engine 6.6");
	TitleWindow("Cheat Engine 6.7");
	TitleWindow("Cheat Engine 6.8");
	TitleWindow("Cheat Engine 6.9");
	TitleWindow("Cheat Engine 7.0");
	TitleWindow("Cheat Engine 7.1");
	TitleWindow("Cheat Engine 7.2");
	TitleWindow("Cheat Engine 7.3");
	TitleWindow("Cheat Engine 7.4");
	TitleWindow("Cheat Engine");
	TitleWindow("WPE PRO");
	TitleWindow("WPePro 0.9a");
	TitleWindow("WPePro 1.3");
	TitleWindow("DLL Injector v1.1 www.dllinjector.com");
	TitleWindow("Extreme Injector v3.7.3 by master131");
	TitleWindow("new 1 - Notepad++");
	VIRTUALIZER_TIGER_WHITE_END
}

void W_Scan()
{
again:
	TitleCheckWindow();
	Sleep(1000);
	goto again;
}

void YProtectionMain()
{
	CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(W_Scan), NULL, 0, 0);
}
void Closeproc(LPCSTR wName)
{
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	if (Process32First(snapshot, &entry) == TRUE)
	{
		while (Process32Next(snapshot, &entry) == TRUE)
		{
			if (_stricmp(entry.szExeFile, wName) == 0) //wName = nome da aba
			{
				HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, entry.th32ProcessID);
				ExitProcess(0);
				CloseHandle(hProcess);
			}
		}
	}
	CloseHandle(snapshot);
}

void disablemwyd_exe() // contar somente 2 WYD's.exe se não fechar
{
	
	LPCSTR wexe = "TheNewWorld.exe";
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (Process32First(snapshot, &entry) == TRUE)
	{
		DWORD pid, pid2; int verifpid = 0;
		/* necessário contar a quantia de wyd.exe's*/
		while (Process32Next(snapshot, &entry) == TRUE)
		{
			if (_stricmp(entry.szExeFile, wexe) == 0) //wName = nome da aba
			{
				HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, entry.th32ProcessID);
				if (verifpid == 0) { /* talve não funcione por conta do loop*/
					pid = entry.th32ProcessID;
					verifpid = 1;
				}
				else if (verifpid == 1) {
					pid2 = entry.th32ProcessID;
					verifpid = 2;
				}
				else {
					DWORD newpid = entry.th32ProcessID;
					if (newpid != pid) {
						MessageBox(NULL, "Sorry, just only 2 clients for pc.", "[ERRO] #PROIBIDO MULTIWYD", MB_OK);
						ExitProcess(0);
					}
					// verificar pela janela 'X WYD'
				}
				//MessageBox(NULL, LPCSTR(pid), "[ERRO] #PROIBIDO MULTIWYD", MB_OK);
				//ExitProcess(0);
				CloseHandle(hProcess);
			}
		}
	}
	CloseHandle(snapshot);
	
}

void Closeclass(LPCSTR hackclass) {
	DWORD pid;
	HWND hWnd = FindWindowA(hackclass, 0); // parametro 1 = classe , parametro = nome da janela
	GetWindowThreadProcessId(hWnd, &pid);
	if (hWnd) {
		ExitProcess(0);
		WriteProcessMemory(hWnd, LPVOID(0x0), LPCVOID(0x0), 0, 0);
	}
}

void Listaproc() {
	VIRTUALIZER_TIGER_WHITE_START
	Closeproc("PCHunter32.exe");
	Closeproc("PCHunter64.exe");
	Closeproc("ProcessHacker.exe"); // n funciona?
	Closeproc("OLLYDBG.EXE");
	VIRTUALIZER_TIGER_WHITE_END
}

// ADC NOME DO PROGRAMA PARA CLIENTE DO WYD FECHAR .exe PINHEIRO
void ClassList() {
	VIRTUALIZER_TIGER_WHITE_START
		Closeclass("ProcessHacker");
	    Closeclass("Cheat Engine");
	//Closeclass("notepad++.exe");
	VIRTUALIZER_TIGER_WHITE_END
}


