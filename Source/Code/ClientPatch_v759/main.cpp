#include "main.h"
//bagu ta bem loco
//STRUCT_QUESTDIARIA QuestDay;
STRUCT_CLIENTPAC g_pSendClientPac; 
int __stdcall DllMain(HINSTANCE hInstDLL, DWORD catchReason, LPVOID lpResrv)
{
	__try
	{//coloca o console
		switch (catchReason)
		{
		case DLL_PROCESS_ATTACH:
		{
			DWORD dwOldProtectFlag_text;
			VirtualProtect((int*)0x0401000, 0x5F0FFF - 0x0401000, 0x40, &dwOldProtectFlag_text);
			// se remover o comentario de CreateConsole irá ativar o console para auxliar a debug.
			// // CMD CONSOLE DO CLIENT
			//CreateConsole("Debug"); // COMENTAR AQUI TIRAR JANELA QUE ABRE COM CLIENTE
			Dll_Inject();
			TitleCheckWindow();
			YProtectionMain(); 

			HookNaked::Start();

			/* Tira os check-sum para manipulação de ponteiros */
			/* Remove - Client Is Bad Ptr */
			JMP_NEAR(0x005D33FD, (INT32*)0x005D3418);

			/* Remove - Client Is Write Ptr */
			JMP_NEAR(0x005D3419, (INT32*)0x005D3434);

			/* Remove - Client Is Bad Code Ptr */
			JMP_NEAR(0x005D3435, (INT32*)0x005D344C);


			JMP_NEAR(0x0046B55F, HookNaked::NKD_ControlEventClick, 4);
			JMP_NEAR(0x004B242E, HookNaked::NKD_HandleScene, 2);

			//BASE_EffectMagic(true);
			AffectIconLimit();

			VirtualProtect((int*)0x0401000, 0x5F0FFF - 0x0401000, dwOldProtectFlag_text, &dwOldProtectFlag_text);
			break;
		}

		case DLL_PROCESS_DETACH:
		{
			FreeLibrary(hInstDLL);
			break;
		}

		}
	}
	__except (GetExceptionCode())
	{

	}

	return TRUE;
}