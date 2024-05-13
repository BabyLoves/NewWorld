
#include "StdAfx.h"

HANDLE m_DllModule;
extern  "C"  __declspec(dllexport) void __cdecl DigDon_V1()  // Função API (init) da dll
{
	/*ON: 1 | OFF: 0*/

	//string title = _T("Mxmain");  
	//SetConsoleTitle(title.c_str());

	carrega.TESTE = 0;     //On/Off = Test cpp
	//SPLASH screen
	carrega.Splash_Screen = 1;     // On/Off = Load splash image (/GameGuard/Protect.bmd)
	carrega.Nome_das_Janelas = "SparTanus";   //Splash message Server name

	carrega.Message_Warning_En = 2;    // Hack detect splash message:  0 = silent, 1 = Engish, 2 = Portuguese 3 = Open php webpage with splash image and make a Log.txt file with Date / ip
	//carrega.HackSplash_WebSite          = "http://127.0.0.1/HackSplash/Splash.php";

	carrega.Log_Txt_Hack = 1;     // On/Off = Creates a hack log ("GameGuard/Log.txt")


	carrega.Hack_Log_Upload = 0;     // On/Off = Creates a Hide hacklog file and upload it to server (inside Hardware Ban folder, are named with computer user name), that uses FTP, when file are uploaded, computer file are deleted.
	carrega.Log_File_Size_To_upload = 10; // 10000 = more or less 100 hack detections, only will upload if file are bigger than that.

	//[ATENTION!] Watch video tutorial! 
	carrega.LA_Detecta_byPipe = 0;     //[ READ-ME ] >> On/Off Start [carrega.Nome_do_Main] defense! This need a lot of configuration on both side, Main and Launchcer 
	carrega.LA_Detecta_ByFileSize = 0;     // Protect Launcher/Main from kill using file conference
	carrega.Launcher_Mem_Protection = 0;     // On/Off This is an active memory protection from Launcher, if launcher are not running and if ther signature are not ok, main closes.
	carrega.Memory_Buffer_L = 0;     // On/Off Message box with address buffer for configuration! Need to configure values on: Detecta_Virtual_Memory.cpp

	//[ATENTION!] >> OPEN ROUTER PORTS: 80 (defalt HTTP) and 21 (defalt FTP)
	carrega.Server_Ban = 0;     // On/Off [ATENTION !] Need configure your Muserver database, watch video tutorials
	carrega.DBan_occours = 60000; // 60000 Occours every 1 minute

	carrega.Hardware_Ban = 0;     // Get Mac Addrees, PC Name and User name game id (from laucher) and create a file to FTP upload, read banlist every 5 minutes
	carrega.DHard_occours = 0;   // 600000, Occours every 10 minutes
	carrega.IP_Server_and_Hard = "192.168.0.106";   //This IP Need be like: "192.168.1.1" or "adress.sytes.net" without [www, http:// or [port], This IP are used by: FTP Up/Down and server Ban post autenticatition
	carrega.FTP_User = "digdon"; //FTP Server User
	carrega.FTP_Pass = "12368";  //FTP Server Password	

	//File names protection
	carrega.Verifica_Nome = 0;     // On/Off = Search [mxmain.exe], [Launcher.exe] file name inside folder. Are NON case-sensitive
	carrega.DVerifica_occours = 953;   //Occours every X miliseconds. [ ATENTION! If antikill by Scans active this value canot be more than 1000 ]
	carrega.Nome_do_Main = "GYD.exe";          // Main name        
	carrega.Nome_do_Launcher = "serverlist.bin";        //Launhcer name
	carrega.Nome_da_Dll = "AntiHackerWYD.dll";           // Anti-hack dll name
	carrega.MainWindowName = "Great Your Destiny";              //Utiliitários Handler.exe >> WindowName = for one single instance 
	carrega.MainClassName = "Great Your Destiny";  //Utiliitários Handler.exe >> Classname  = for one single instance

	carrega.Launcher_Ativo = 0;     // On/Off = check if Launcher are always on   
	carrega.DLauncher_Occours = 939;   //Occours every X miliseconds. [ ATENTION! If antikill by Scans active this value canot be more than 1000 ]
	carrega.Launcher_Window = "Great Your Destiny"; //Launcher window name = Use utilities/Handler 1.5 >> Windowtext

	carrega.Detecta_Hide_Toolz = 0;     // On/Off = Generic Hide toolz / Cheat engine detector - Use at your own risk! 
	carrega.DHide_occours = 976;   //Occours every X miliseconds. [ ATENTION! If antikill by Scans active this value canot be more than 1000 ]

	carrega.Detecta_Dump = 1;     // On/Off = Detect application entrypoint and first 16 HexDump
	carrega.Token_Privileges = 0;     // [alwais ON] - Add adminstrator privileges to open handle on WINDOWS OS, if disabled, dump detector can't detect hacks on WINDOWS XP OS.
	carrega.DDump_occours = 947;   //Occours every X miliseconds. [ ATENTION! If antikill by Scans active this value canot be more than 1000 ]

	carrega.Detecta_Window = 1;     // On/Off = Close GAME when detect Hack WindowName
	carrega.Close_Window = 1;     // On/Off Close HACK window, if CLOSE HACK window fail, close GAME. Use to close "especific" apps. This can crash your system.
	carrega.DWindow_occours = 736;   //Occours every X miliseconds. [ ATENTION! If antikill by Scans active this value canot be more than 1000 ]

	carrega.Detecta_ClassName = 1;     // On/Off = Close GAME when detect Hack ClassName
	carrega.Close_ClassName = 1;     // On/Off = Close HACK ClassName, if CLOSE HACK ClassName fail, close GAME. Use to close "especific" apps. This can crash your system. This detector are good to detect "generic" speed hack created using VB. Exemple: ["WindowsForms10.Window.8.app.0xxxxxx]
	carrega.DClassName_occours = 968;   //Occours every X miliseconds. [ ATENTION! If antikill by Scans active this value canot be more than 1000 ]

	//[ ATENTION ! ] use: carrega.Detecta_Inject_API at your own risk!] 
	carrega.Delete_GetModuleHandle = 0;     //[ READ-ME ] >> On/Off = [Don't work for MUOnline, use at your own risk!] Thread count need be stable! Protect from code (dll) injection, silently! This feature delete GetModuleHandle after be loading.
	carrega.Detecta_Inject_API = 0;     //[ READ-ME ] >> On/Off = [Don't work for MUOnline, use at your own risk!] Thread count need be stable! Protect API from code (dll) injection, silently! this detector don't uses any splash!
	carrega.DAPIInject_occours = 966;


	carrega.Detecta_Inject = 1;     // On/Off = Detect dll inject (by dll {name.extension}) 
	carrega.DInject_occours = 936;   //Occours every X miliseconds. [ ATENTION! If antikill by Scans active this value canot be more than 1000 ]

	carrega.Detecta_PID = 0;     // On/Off = Detect application by {name.extension}
	carrega.DPID_occours = 976;   //Occours every X miliseconds. [ ATENTION! If antikill by Scans active this value canot be more than 1000 ]

	carrega.Detecta_Speed_Tickcount = 0;     // On/Off = Speed hack and System freeze (suspend) detector
	carrega.DSpeed_occours = 500;   //[ ATENTION! ] Don't change this value!

	carrega.Detecta_Speed_Performance = 0;     // On/Off = Speed hack detector
	carrega.DAnti_Speed_P_occours = 969;   //Occours every X miliseconds. [ ATENTION! If antikill by Scans active this value canot be more than 1000 ]

	carrega.Detecta_Heuristica_Win = 1;     // On/Off = Detect bad Words, are case sensitive and scan WebBrowsers
	carrega.DHeuristica_Win_occours = 596;   //Occours every X miliseconds. [ ATENTION! If antikill by Scans active this value canot be more than 1000 ]

	carrega.Detecta_Heuristica_Class = 1;     // On/Off = Detect bad Words, are case sensitive and scan WebBrowsers
	carrega.DHeuristica_Class_occours = 766;   //Occours every X miliseconds. [ ATENTION! If antikill by Scans active this value canot be more than 1000 ]

	carrega.Detecta_Heuristica = 1;     // On/Off = Detect bad Words, are case sensitive and scan WebBrowsers
	carrega.DHeuristica_occours = 556;   //Occours every X miliseconds. [ ATENTION! If antikill by Scans active this value canot be more than 1000 ]

	carrega.Detecta_Heuristica_NC = 0;     // On/Off = Detect bad Words, are NON case sensitive and DONT scan webbrowsers
	carrega.DHeuristica_NC_occours = 565;   //Occours every X miliseconds. [ ATENTION! If antikill by Scans active this value canot be more than 1000 ]

	//[ ATENTION ! ] sometimes AKS-Scan may have [ExitProcess] caused by Internet delay on >> (Server Ban / Hardware Ban) 
	carrega.Anti_Kill_Scans = 0;     // On/Off = Detect kill Scans, this are fully based on time occours, so, don't change any detectors time_occours if it are ON!
	carrega.DAnti_Kill_occours = 2000;  //[ATENTION! This value need be 2x more than detectors. 

	//[ ATENTION ! ] use: carrega.Detecta_Kill_by_Thread at your own risk!] 
	carrega.Detecta_Kill_by_Thread = 0;     //[ READ-ME ] >> On/Off = This detector detect KILL and INJECT.  [ ATENTION! Don't work for MU Online, don't work with Ban Server, Hardware Ban or Hack Log Upload active] Use at your own risk! 
	carrega.DAnti_Kill_T_occours = 937;   //Occours every X miliseconds. [ ATENTION! If antikill by Scans active this value canot be more than 1000 ] 

	carrega.Virtual_Memory_Protect = 0;     // On/Off = protect code from auteration on virtual memory (need be configured) on [Virtual_Memory.cpp]
	carrega.Memory_Buffer_P = 0;     // On/Off Message box with address buffer for configuration! Need to configure values on: Detecta_Virtual_Memory.cpp
	carrega.Virtual_Mem_occours = 965;   //Occours every X miliseconds. [ ATENTION! If antikill by Scans active this value canot be more than 1000 ]

	//NEED CONFIGURE [ Serial_Versao.cpp ]
	carrega.Carrega_serial_versao = 0;     // On/Off = Menset Ip/Serial/Version, without codex.dll mxmain dont make any autentication funciton.
	carrega.Serial = "Dig_Don";	// (16) Your server serial = Watch video tutoral 
	carrega.Versao = "DigV1";				// (5)  Your server version
	carrega.IP = "Ip";	    //      Your server Ip

	carrega.Rebuild_Main_Data = 0; // On/Off = Need configure Rebuild_Main_Data.cpp or system crash! = Watch Video Tutorial

	//NEED CONFIGURE!  To Configure CRC files use [utilities/Igorware hasher.exe] = CRC
	carrega.Ativa_CRC_Geral = 1;          // [alwais ON] = CRC files check 

	carrega.CRC_Launcher = 0;          // On/Off = CRC Do Launcher
	carrega.CRC_LauncherEXE = 0xfb5c4d77; // Launcher

	carrega.CRC_ProtectBMP = 1;          // On/Off = CRC da Protect.bmd 
	carrega.CRC_Protect = 0xCD112B69; // Protect.BMP v4 = f04c9046

	carrega.CRC_Player = 1;          // On/Off = CRC Player.bmd 
	carrega.CRC_PlayerBMD = 0x5E1C626E; // Player.BMD CA90466C

	carrega.CRC_WebZenLogoOZJ = 1;          // On/Off = Splash image 
	carrega.CRC_WebLogo = 0x79117659; // WebZenlogo.OZJ ServeList.bin
	//carrega.CRC_WebLogo = 0xf822b9b0; // WebZenlogo.OZJ 

	carrega.CRC_7_Terrains = 0;          // On/Off = 7 first Terrain ("Data/WorldX/EncTerrainX.att") 
	carrega.CRC_Terrain1 = 0x5339965e;			// Terrain 1
	carrega.CRC_Terrain2 = 0xc3e83648;			// Terrain 2 
	carrega.CRC_Terrain3 = 0x0847c665;			// Terrain 3 
	carrega.CRC_Terrain4 = 0x7cc0297c;			// Terrain 4 
	carrega.CRC_Terrain5 = 0x76487ad9;			// Terrain 5 
	carrega.CRC_Terrain6 = 0xb3b0cf70;			// Terrain 6 
	carrega.CRC_Terrain7 = 0x98fb5fca;           // Terrain 7 

	//Carregar Glow.dll (Mu Online)
	carrega.GlowDLL = 0; // On/Off = Load Glow.dll inside gameguard folder. (Glow.dll not included). only works in v97

	//Carregar Minimizer / autoclick .dll
	carrega.MinimizerDLL = 0; // On/Off = Start some dll by name (in Gameguard folder), use it for start some Minimizer, autoclick...
	carrega.Nome_da_DLL = "GameGuard/Minimizer.dll"; //Some dll = Adress/name.extension  

}
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{

	switch (ul_reason_for_call){
	case DLL_PROCESS_ATTACH: m_DllModule = hModule;
		DigDon_V1(); //API funciton

		if (carrega.TESTE == 1)
		{
			TESTES();
		}

		if (carrega.LA_Detecta_byPipe || carrega.LA_Detecta_ByFileSize == 1)
		{
			LoadSingleInstance();
			HWND WinTitle = FindWindowA(NULL, carrega.Launcher_Window);
			if (WinTitle == 0){
				if (carrega.Launcher_Ativo == 1){
					if (carrega.Message_Warning_En == 1 || carrega.Message_Warning_En == 3){
						MessageBoxA(NULL, "XXVII\n\nLauncher not found!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
						ExitProcess(0);
					}
				}
				if (carrega.Message_Warning_En == 2){
					if (carrega.Launcher_Ativo == 1){
						MessageBoxA(NULL, "XXVII\n\nO Launcher deve permanecer ativo!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
						ExitProcess(0);
					}
				}
			}
		}
		if (carrega.LA_Detecta_ByFileSize == 1)
		{
			ExeByFileSize();
		}

		if (carrega.LA_Detecta_byPipe == 1)
		{
			ServerThread();
			ClienteThread();
		}

		if (carrega.Splash_Screen == 1)
		{
			SplashShow();
		}

		if (carrega.Rebuild_Main_Data == 1)
		{
			RebuildData();
		}

		if (carrega.Hack_Log_Upload == 1)
		{
			Hack_Log_Up();
		}

		if (carrega.Close_ClassName == 1)
		{
			Close_Class();
		}

		if (carrega.Close_Window == 1)
		{
			Close_Window();
		}

		if (carrega.Delete_GetModuleHandle == 1)
		{
			DeleteAPI();
		}

		if (carrega.Detecta_Inject_API == 1)
		{
			API_Inject();
		}

		if (carrega.Hardware_Ban == 1)
		{
			Mac_Load();
		}

		if (carrega.Verifica_Nome == 1)
		{
			Nomes();
		}

		if (carrega.MinimizerDLL == 1)
		{
			LoadLibraryA(carrega.Nome_da_DLL);
		}

		if (carrega.Ativa_CRC_Geral == 1)
		{
			_beginthread(MainThread, 0, NULL);
		}

		if (carrega.GlowDLL == 1)
		{
			LoadLibraryA("Glow.dll");
		}

		if (carrega.Detecta_Speed_Performance == 1)
		{
			SPerformance();
		}

		if (carrega.Detecta_Heuristica_NC == 1)
		{
			Heuristica2();
		}

		if (carrega.Detecta_Speed_Tickcount == 1)
		{
			DetectSpeed();
		}

		if (carrega.Detecta_PID == 1)
		{
			DetectID();
		}

		if (carrega.Launcher_Mem_Protection == 1)
		{
			Mem_Launcher_Protection();
		}

		if (carrega.Detecta_Dump == 1)
		{
			ProtectionMain();
		}

		if (carrega.Detecta_Window == 1)
		{
			DwProtection();
		}

		if (carrega.Detecta_Heuristica == 1)
		{
			HProtection();
		}

		if (carrega.Detecta_Heuristica_Win == 1)
		{
			HeuristicW();
		}

		if (carrega.Detecta_Heuristica_Class == 1)
		{
			Heuristicclass();
		}

		if (carrega.Detecta_ClassName == 1)
		{
			CNProtection();
		}

		if (carrega.Launcher_Ativo == 1)
		{
			LA_On_byName();
		}

		if (carrega.Detecta_Inject == 1)
		{
			Dll_Inject();
		}

		if (carrega.Server_Ban == 1 && carrega.Anti_Kill_Scans == 0)
		{
			HTTP_Connect(); //Direto pro ban server, cria uma nova thread.
		}

		if (carrega.Carrega_serial_versao == 1)
		{
			Serial_e_Etc();
		}

		if (carrega.Virtual_Memory_Protect == 1)
		{
			Virtual_Attack();
		}

		if (carrega.Detecta_Hide_Toolz == 1)
		{
			Hide_T();
		}

		if (carrega.Anti_Kill_Scans == 1)
		{
			Anti_kill1();
			Anti_kill2();
		}

		if (carrega.Detecta_Kill_by_Thread == 1)
		{
			AntiKill_T();
			if (carrega.Server_Ban == 1 || carrega.Hardware_Ban == 1){
				MessageBoxA(NULL, "WARNING! Anti-Kill by thread incompatibility detected!\n\n\nThis detector don't work for WYD or any Main without STATIC thread count!\n\n\nThis detector don't work with: [Ban server or Hardware Ban] for the same reason.\n\nYou can disable this message on START.cpp adding lines intersection: '//' on both lines.", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
			}
		}

		if (carrega.Token_Privileges == 1)
		{

			//Add adminstrator privileges to open handle (Dump detector) on WINDOWS XP
			HANDLE hToken = NULL;
			TOKEN_PRIVILEGES tokenPriv;
			LUID luidDebug;
			if (OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &hToken) != FALSE)
			{
				if (LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &luidDebug) != FALSE)
				{
					tokenPriv.PrivilegeCount = 1;
					tokenPriv.Privileges[0].Luid = luidDebug;
					tokenPriv.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
					if (AdjustTokenPrivileges(hToken, FALSE, &tokenPriv, 0, NULL, NULL) != FALSE)
					{
						//cout << "SUCCESSFULLY CHANGED TOKEN PRIVILEGES" << endl;
						Sleep(1);
					}
					else
					{
						Sleep(1);
						//cout << "FAILED TO CHANGE TOKEN PRIVILEGES, CODE: " << GetLastError() << endl;
					}
				}
			}
			CloseHandle(hToken);
		}
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}







