
#include "StdAfx.h"

void Msg_L_Br(){
	MessageBoxA(NULL, "IX\n\nO arquivo [Launcher.exe] foi alterado ou corrompido!\n", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
}
void Msg_L_En(){
	MessageBoxA(NULL, "IX\n\n[Launcher.exe] Corrupted or missing file!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
}

void Msg_P_Br(){
	MessageBoxA(NULL, "IX\n\nO arquivo [GamePatch.dll] foi alterado ou corrompido!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
}

void Msg_P_En(){
	MessageBoxA(NULL, "IX\n\n[Player.bmp] Corrupted or missing file!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
}

void Msg_PD_Br(){
	MessageBoxA(NULL, "IX\n\nO arquivo [Launcher.dll] foi alterado ou corrompido!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
}

void Msg_PD_En(){
	MessageBoxA(NULL, "IX\n\n[Launcher.dll] Corrupted or missing file!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
}

void Msg_Pro_BMD_Br(){
	MessageBoxA(NULL, "IX\n\nO arquivo [Protect.bmp] foi alterado ou corrompido!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
}

void Msg_Pro_BMD_En(){
	MessageBoxA(NULL, "IX\n\n[Protect.bmd] Corrupted or missing file!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
}

void Msg_Logo_Br(){
	MessageBoxA(NULL, "IX\n\nO arquivo [serverlist.bin] foi alterado ou corrompido!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
}
void Msg_Logo_En(){
	MessageBoxA(NULL, "IX\n\n[123] Corrupted or missing file!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
}

void Msg_T1_Br(){
	MessageBoxA(NULL, "IX\n\nO arquivo [123] foi alterado ou corrompido!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
}
void Msg_T1_En(){
	MessageBoxA(NULL, "IX\n\n[123] Corrupted or missing file!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
}

void Msg_T2_Br(){
	MessageBoxA(NULL, "IX\n\nO arquivo [123] foi alterado ou corrompido!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
}
void Msg_T2_En(){
	MessageBoxA(NULL, "IX\n\n[123] Corrupted or missing file!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
}

void Msg_T3_Br(){
	MessageBoxA(NULL, "IX\n\nO arquivo [123] foi alterado ou corrompido!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
}
void Msg_T3_En(){
	MessageBoxA(NULL, "IX\n\n[123] Corrupted or missing file!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
}

void Msg_T4_Br(){
	MessageBoxA(NULL, "IX\n\nO arquivo [123] foi alterado ou corrompido!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
}
void Msg_T4_En(){
	MessageBoxA(NULL, "IX\n\n[123] Corrupted or missing file!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
}

void Msg_T5_Br(){
	MessageBoxA(NULL, "IX\n\nO arquivo [123] foi alterado ou corrompido!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
}
void Msg_T5_En(){
	MessageBoxA(NULL, "IX\n\n[123] Corrupted or missing file!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
}

void Msg_T6_Br(){
	MessageBoxA(NULL, "IX\n\nO arquivo [123] foi alterado ou corrompido!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
}
void Msg_T6_En(){
	MessageBoxA(NULL, "IX\n\n[123] Corrupted or missing file!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
}

void Msg_T7_Br(){
	MessageBoxA(NULL, "IX\n\nO arquivo [132] foi alterado ou corrompido!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
}
void Msg_T7_En(){
	MessageBoxA(NULL, "IX\n\n[123] Corrupted or missing file!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
}

////////////////////////////////////////////////

CheckSum Check;

void CheckSum::Arquivos()
{
	Check.Initialize();

	if (carrega.CRC_Launcher == 1)
	{
		long Arquivo1 = Check.FileCRC(carrega.Nome_do_Launcher);

		if (Arquivo1 != carrega.CRC_LauncherEXE)
		{
			if (carrega.Log_Txt_Hack == 1)
			{
				ofstream out("NUI/Log.txt", ios::app);
				out << "\n IX:", out << carrega.Nome_do_Launcher;
				out.close();
			}

			if (carrega.Message_Warning_En == 1 || carrega.Message_Warning_En == 3)
			{
				CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(Msg_L_En), NULL, 0, 0);
				Sleep(5000);
				ExitProcess(0);
			}
			if (carrega.Message_Warning_En == 2)
			{
				CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(Msg_L_Br), NULL, 0, 0);
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

	////////////////////////////////////////////////
	if (carrega.CRC_Player == 1)
	{
		long Player = Check.FileCRC("Data/Player/player.bmd");

		if (Player != carrega.CRC_PlayerBMD)
		{
			if (carrega.Log_Txt_Hack == 1)
			{
				ofstream out("NUI/Log.txt", ios::app);
				out << "\n IX:", out << "Data/Player/player.bmd";
				out.close();
			}

			if (carrega.CRC_Player == 1)
			{
				long Player = Check.FileCRC("GamePatch.dll");

				if (Player != carrega.CRC_PlayerBMD)
				{
					if (carrega.Log_Txt_Hack == 1){
						ofstream out("NUI/Log.txt", ios::app);
						out << "\n IX:", out << "GamePatch.dll";
						out.close();
					}

					if (carrega.Message_Warning_En == 1 || carrega.Message_Warning_En == 3)
					{
						CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(Msg_P_En), NULL, 0, 0);
						Sleep(5000);
						ExitProcess(0);
					}
					if (carrega.Message_Warning_En == 2)
					{
						CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(Msg_P_Br), NULL, 0, 0);
						//Sleep(5000);
						//ExitProcess(0);
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

	////////////////////////////////////////////////
	if (carrega.CRC_ProtectBMP == 1)
	{
		long Image = Check.FileCRC("NUI/Protect.bmp");

		if (Image != carrega.CRC_Protect)
		{
			if (carrega.Log_Txt_Hack == 1)
			{
				ofstream out("NUI/Log.txt", ios::app);
				out << "\n IX:", out << "NUI/Protect.bmp";
				out.close();
			}
			if (carrega.Message_Warning_En == 1 || carrega.Message_Warning_En == 3)
			{
				CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(Msg_Pro_BMD_En), NULL, 0, 0);
				Sleep(5000);
				ExitProcess(0);
			}
			if (carrega.Message_Warning_En == 2)
			{
				CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(Msg_Pro_BMD_Br), NULL, 0, 0);
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

	////////////////////////////////////////////////		
	if (carrega.CRC_WebZenLogoOZJ == 1)
	{
		long Image2 = Check.FileCRC("serverlist.bin");

		if (Image2 != carrega.CRC_WebLogo)
		{
			if (carrega.Log_Txt_Hack == 1)
			{
				ofstream out("NUI/Log.txt", ios::app);
				out << "\n IX:", out << "serverlist";
				out.close();
			}
			if (carrega.Message_Warning_En == 1 || carrega.Message_Warning_En == 3)
			{
				CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(Msg_Logo_En), NULL, 0, 0);
				Sleep(5000);
				ExitProcess(0);
			}
			if (carrega.Message_Warning_En == 2)
			{
				CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(Msg_Logo_Br), NULL, 0, 0);
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

	////////////////////////////////////////////////
	if (carrega.CRC_7_Terrains == 1)
	{
		long ter1 = Check.FileCRC("");
		long ter2 = Check.FileCRC("");
		long ter3 = Check.FileCRC("");
		long ter4 = Check.FileCRC("");
		long ter5 = Check.FileCRC("");
		long ter6 = Check.FileCRC("");
		long ter7 = Check.FileCRC("");

		////////////////////////////////////////////////
		if (ter1 != carrega.CRC_Terrain1)
		{
			if (carrega.Log_Txt_Hack == 1)
			{
				using namespace std;
				ofstream out("NUI/Log.txt", ios::app);
				out << "\n IX:", out << "";
				out.close();
			}
			if (carrega.Message_Warning_En == 1 || carrega.Message_Warning_En == 3)
			{
				CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(Msg_T1_En), NULL, 0, 0);
				Sleep(5000);
				ExitProcess(0);
			}
			if (carrega.Message_Warning_En == 2)
			{
				CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(Msg_T1_Br), NULL, 0, 0);
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


		////////////////////////////////////////////////
		if (ter2 != carrega.CRC_Terrain2)
		{
			if (carrega.Log_Txt_Hack == 1)
			{
				ofstream out("NUI/Log.txt", ios::app);
				out << "\n IX:", out << "";
				out.close();
			}
			if (carrega.Message_Warning_En == 1 || carrega.Message_Warning_En == 3)
			{
				CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(Msg_T2_En), NULL, 0, 0);
				Sleep(5000);
				ExitProcess(0);
			}
			if (carrega.Message_Warning_En == 2)
			{
				CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(Msg_T2_Br), NULL, 0, 0);
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

		////////////////////////////////////////////////
		if (ter3 != carrega.CRC_Terrain3)
		{
			if (carrega.Log_Txt_Hack == 1)
			{
				ofstream out("NUI/Log.txt", ios::app);
				out << "\n IX:", out << "";
				out.close();
			}
			if (carrega.Message_Warning_En == 1 || carrega.Message_Warning_En == 3)
			{
				CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(Msg_T3_En), NULL, 0, 0);
				Sleep(5000);
				ExitProcess(0);
			}
			if (carrega.Message_Warning_En == 2)
			{
				CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(Msg_T3_Br), NULL, 0, 0);
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

		////////////////////////////////////////////////
		if (ter4 != carrega.CRC_Terrain4)
		{
			if (carrega.Log_Txt_Hack == 1)
			{
				ofstream out("NUI/Log.txt", ios::app);
				out << "\n IX:", out << "";
				out.close();
			}
			if (carrega.Message_Warning_En == 1 || carrega.Message_Warning_En == 3)
			{
				CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(Msg_T4_En), NULL, 0, 0);
				Sleep(5000);
				ExitProcess(0);
			}
			if (carrega.Message_Warning_En == 2)
			{
				CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(Msg_T4_Br), NULL, 0, 0);
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

		////////////////////////////////////////////////
		if (ter5 != carrega.CRC_Terrain5)
		{
			if (carrega.Log_Txt_Hack == 1)
			{
				ofstream out("NUI/Log.txt", ios::app);
				out << "\n IX:", out << "";
				out.close();
			}
			if (carrega.Message_Warning_En == 1 || carrega.Message_Warning_En == 3)
			{
				CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(Msg_T5_En), NULL, 0, 0);
				Sleep(5000);
				ExitProcess(0);
			}
			if (carrega.Message_Warning_En == 2)
			{
				CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(Msg_T5_Br), NULL, 0, 0);
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

		////////////////////////////////////////////////
		if (ter6 != carrega.CRC_Terrain6)
		{
			if (carrega.Log_Txt_Hack == 1)
			{
				ofstream out("NUI/Log.txt", ios::app);
				out << "\n CRC-Scan:", out << "";
				out.close();
			}
			if (carrega.Message_Warning_En == 1 || carrega.Message_Warning_En == 3)
			{
				CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(Msg_T6_En), NULL, 0, 0);
				Sleep(5000);
				ExitProcess(0);
			}
			if (carrega.Message_Warning_En == 2)
			{
				CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(Msg_T6_Br), NULL, 0, 0);
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

		////////////////////////////////////////////////
		if (ter7 != carrega.CRC_Terrain7)
		{
			if (carrega.Log_Txt_Hack == 1)
			{
				ofstream out("NUI/Log.txt", ios::app);
				out << "\n CRC-Scan:", out << "";
				out.close();
			}
			if (carrega.Message_Warning_En == 1 || carrega.Message_Warning_En == 3)
			{
				CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(Msg_T7_En), NULL, 0, 0);
				Sleep(5000);
				ExitProcess(0);
			}
			if (carrega.Message_Warning_En == 2)
			{
				CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(Msg_T7_Br), NULL, 0, 0);
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

void MainThread(void * lpParam)
{
	while (true)
	{
		Check.Arquivos();
		Sleep(60000);
	}
	_endthread();
}