#include "main.h"
#include "../CommonNewInfo.h"
auto& WYD = HookMgr::instance();

bool HookNaked::Start()
{
	try
	{
		DWORD dwOldProtectFlag_text;
		VirtualProtect((int*)0x0401000, 0x5F0FFF - 0x0401000, 0x40, &dwOldProtectFlag_text);

		WYD.SetHook(eHookType::JGE, 0x004252D6, WYD.GetPtr(&HookNaked::NKD_ClientReceiver), 0);
		WYD.SetHook(eHookType::JMP, 0x00425887, WYD.GetPtr(&HookNaked::NKD_ClientSended), 0);

		strcpy((char*)0x622CDA, "  WyD Project");

		HookMgr::instance().SetValue(0x0054A062 + 6, 640);  HookMgr::instance().SetValue(0x0054A06C + 6, 480); HookMgr::instance().SetValue(0x0054A076 + 6, 32);
		HookMgr::instance().SetValue(0x0054A080 + 6, 800); HookMgr::instance().SetValue(0x0054A08A + 6, 600); HookMgr::instance().SetValue(0x0054A094 + 6, 32);
		HookMgr::instance().SetValue(0x0054A09E + 6, 1280); HookMgr::instance().SetValue(0x0054A0A8 + 6, 720); HookMgr::instance().SetValue(0x0054A0B2 + 6, 32);
		HookMgr::instance().SetValue(0x0054A0BC + 6, 1600); HookMgr::instance().SetValue(0x0054A0C6 + 6, 900); HookMgr::instance().SetValue(0x0054A0D0 + 6, 32);
		HookMgr::instance().SetValue(0x0054A0DA + 6, 1920); HookMgr::instance().SetValue(0x0054A0E4 + 6, 1080); HookMgr::instance().SetValue(0x0054A0EE + 6, 32);


		JMP_NEAR(0x004205D0, HookNaked::NKD_AddAmountItem, 4);

		strcpy((char*)0x613EC4, "Monstro"); /* Classe do personagem 'C' */
		strcpy((char*)0x613EB4, "[%s]"); /* Nick do personagem 'C' */

		WYD.SetHook(eHookType::JMP, 0x0046052E, WYD.GetPtr(&HookNaked::NKD_NPCClick), 2);

		WYD.SetHook(eHookType::JMP, 0x0004182C4, WYD.GetPtr(&NKD_SGrid_OnMouseMove_SkinName));/* Trajes de Montarias */
		WYD.SetHook(eHookType::JA, 0x00519635, WYD.GetPtr(&NKD_ProcessViewMount_Skins));/* Trajes de Montarias */

		/* SkillData - CheckSum*/
		//WYD.SetValue<BYTE>(0x0053AC6A, 0xEB);

		/* ItemList - CheckSum */
		WYD.SetValue<BYTE>(0x0053ACE2, 0xEB);
		WYD.SetValue<BYTE>(0x0053AE7E, 0xEB);

		//Servidor Local porta 4286
		WYD.SetValue(0x4B380B, 8281);// Altera a Porta do Game
		WYD.SetValue(0x486426, 8281);// Altera a Porta do Game
		
		//Tempo dos buffs
		strcpy((char*)0x61460C, "%dD");

		// Teste para SkillDelay
		for (int i = 0; i < 104; i++)
			*(int*)(0x11DA838 + (i * 96) + 48) = *(int*)(0x11DA838 + (i * 96) + 48) / 4;

		//BM USAR TRAJE TRANSFORMADO, TESTAR
		WYD.SetHook(eHookType::JMP, 0x456ADE, 0x456B59);
		WYD.SetHook(eHookType::JMP, 0x45A600, 0x45A67B);

		//Brilho em Trajes
		WYD.SetHook(eHookType::JMP, 0x519E36, WYD.GetPtr(&NKD_NewEffectTraje));

		/* ExtraItem - CheckSum*/
		WYD.SetValue<BYTE>(0x0053ADA6, 0xEB);

		/* Chat Colorido */
		SpeakChatColor = TNColor::Speak;

		//Novas Composições
		WYD.SetHook(eHookType::JMP, 0x498ACD, WYD.GetPtr(&HookNaked::NKD_NewNPCComp));

		WYD.SetValue(0x043b2f5 + 1, WYD.GetPtr("http://wydtnw.com.br/img_guilds/"));/*Altera endereço das img das guildas*/
		WYD.SetValue(0x043b111 + 1, WYD.GetPtr("http://wydtnw.com.br/img_guilds/"));/*Altera endereço das img das guildas*/

		/* Hook On - Client Speak Message */
		WYD.SetHook(eHookType::JMP, 0x004A0164, WYD.GetPtr(&HookNaked::NKD_SpeakChatColor), 0);

		/* Hook On - Item Description */
		WYD.SetHook(eHookType::JMP, 0x0041C468, WYD.GetPtr(&HookNaked::NKD_FixItemDescription), 4);//Item Description

		/* Hook On - Correção Green Time Qualquer Mapa */
		JMP_NEAR(0x047DACA, HookNaked::NKD_GreenTime_NewArea, 1);

		/*  Hook Casas Decimal*/
		JMP_NEAR(0x041D1B4, HookNaked::NKD_ItemPrice_FormatDecimal_03, 1);
		//JMP_NEAR(0x041CFD8, HookNaked::NKD_ItemPrice_FormatDecimal_02, 1);
		JMP_NEAR(0x0421356, HookNaked::NKD_ItemPrice_FormatDecimal);

		/* Troca de cor do TAB */
		JMP_NEAR(0x04E21DB, HookNaked::NKD_ChangeTabColor);

		/* Pula checksum dos arquivos trn (mapas) */
		WYD.SetHook(eHookType::JMP, 0x51E621, 0x51E6B4, 1);
		WYD.SetHook(eHookType::JMP, 0x52FB84, 0x52FC3A, 1);

		/* New Itens Day - Time */
		WYD.SetHook(eHookType::JMP, 0x0041A51E, WYD.GetPtr(&HookNaked::NKD_NewItensDays_1));
		WYD.SetHook(eHookType::JMP, 0x0041A535, WYD.GetPtr(&HookNaked::NKD_NewItensDays_2));
		//WYD.SetHook(eHookType::JMP, 0x41A14D, WYD.GetPtr(&Client::NKD_ValidadeFadas), 0);
		//WYD.SetHook(eHookType::JMP, 0x41A14D, WYD.GetPtr(&HookNaked::NKD_ValidadeFadas), 0);
		WYD.SetHook(eHookType::JMP, 0x41A87D, WYD.GetPtr(&HookNaked::NKD_ValidadeTrajes), 0);
		WYD.SetHook(eHookType::JMP, 0x41A56E, WYD.GetPtr(&HookNaked::NKD_ValidadeEsferas), 0);

		/* Item Price String */
		WYD.SetHook(eHookType::JMP, 0x41CFCD, WYD.GetPtr(&HookNaked::NKD_ItemPriceString), 1);

		/* Fix Pacote 0x3BB */
		JMP_NEAR(0x0048B04F, HookNaked::NKD_ProcessClientMessage_03BBh, 1);   //28/11

		// ReadMessage
		//JGE_NEAR(0x4252D6, NKD_ReadMessage); 

		// ITEM BOX
		JMP_NEAR(0x422007, NKD_AddVolatileMessageItem, 2); //421F1A
		JMP_NEAR(0x41FB30, NKD_AddVolatileMessageBox, 5);

		WYD.SetHook(eHookType::JMP, 0x4205FC, WYD.GetPtr(&HookNaked::NKD_AddAmountItem), 4);

		WYD.SetHook(eHookType::JMP, 0x4676C5, WYD.GetPtr(&HookNaked::NKD_SendChat));

		//Trajes
		WYD.SetValue<DWORD>(0x4DCA09 + 1, 4250);

		WYD.SetHook(eHookType::JMP, 0x519D60, WYD.GetPtr(&HookNaked::NKD_FixIndex));
		WYD.SetHook(eHookType::JMP, 0x4DE210, WYD.GetPtr(&HookNaked::NKD_CorrectBones), 1);
		WYD.SetHook(eHookType::JMP, 0x4CFDAF, WYD.GetPtr(&HookNaked::NKD_LoadFiles), 4);

		/* Modificações nos atributos da esferas.*/
		JMP_NEAR(0x005385AC, HookNaked::NKD_GetItemAbility_Esfera, 3);

		/* Adicionar novos pots hp/mp no macro */
		//JMP_NEAR(0x0045169A, HookNaked::NKD_Macro_NewPotions_HP);
		//JMP_NEAR(0x00451BA0, HookNaked::NKD_Macro_NewPotions_MP);

		/* Fix Macro Mage */
		JE_NEAR(0x04974C7, HookNaked::NKD_FixMageMacro);
		JE_NEAR(0x04974D7, HookNaked::NKD_FixMageMacro);


		/* KeyPress_NewButton */
		JMP_NEAR(0x045488D, HookNaked::NKD_KeyPress_NewButton, 1);

		//MainLoop /*by SeiTbN*/
		//JMP_NEAR(0x0040CF4E, GameInterface::NKD_MainLoop);
		//JMP_NEAR(0x00477b95, NKD_UpdateResources, 1);

		/*by SeiTbN*/
		JMP_NEAR(0x04B55D2, HookNaked::NKD_Cam, 1);

		//desativa legenda de buffs
		//WYD.SetValue<BYTE>(0x00477299, 0xEB);

		/* Pula limit dos news buff */
		*(char*)(0x005495A8) = 100;
		*(char*)(0x0047B0AB) = 100;
		*(char*)(0x0044B476) = 100;
		*(char*)(0x00476CF1) = 100;

		WYD.SetHook(eHookType::JMP, 0x0423447, WYD.GetPtr(&NKD_SetDefaultLocation), 2); // Hook dano azul
		WYD.SetHook(eHookType::JMP, 0x0494AAF, WYD.GetPtr(&NKD_GetAttackType), 3);      // Hook dano azul
		WYD.SetHook(eHookType::JMP, 0x04921DB, WYD.GetPtr(&NKD_GetAttackType2), 4);     // Hook dano azul
		WYD.SetHook(eHookType::JMP, 0x04232E5, WYD.GetPtr(&NKD_ChangeTextureFont), 2);  // Hook dano azul

		WYD.SetHook(eHookType::JMP, 0x048471E, WYD.GetPtr(&NKD_GetCreateMob_ChangeHPText), 5);//HP DO MOB EM NUMERO NA BARRA
		WYD.SetHook(eHookType::JMP, 0x04E216E, WYD.GetPtr(&NKD_SetHPNumberOnMonsterHP), 3);//HP DO MOB EM NUMERO NA BARRA

		// falta atualizar os addrees
		//WYD.SetHook(eHookType::JMP, 0x00401706, WYD.GetPtr(&HookNaked::NKD_ScrollMouseController), 5);

#pragma region Ajuste efeito refinação
//Altera o tamanho do efftest de 35.0 para 70.0
//0040D3FC | . 68 00000C42              PUSH 420C0000; / Arg5 = 420C0000
		WYD.SetValue<uint32_t>(0x040D3FD, 0x428C0000);
		//0040D401 | . 68 00000C42              PUSH 420C0000; | Arg4 = 420C0000
		WYD.SetValue<uint32_t>(0x040D402, 0x428C0000);
		//00434BD3  |. 68 00000C42              PUSH 420C0000                            ; |Arg4 = 420C0000
		WYD.SetValue<uint32_t>(0x0434BD4, 0x428C0000);
		////00434BD8 | . 68 00000C42              PUSH 420C0000; | Arg3 = 420C0000
		WYD.SetValue<uint32_t>(0x0434BD9, 0x428C0000);
		//00434E18  |. 68 00000C42              PUSH 420C0000                            ; |Arg4 = 420C0000
		WYD.SetValue<uint32_t>(0x0434E19, 0x428C0000);
		//00434E1D | . 68 00000C42              PUSH 420C0000; | Arg3 = 420C0000
		WYD.SetValue<uint32_t>(0x0434E1E, 0x428C0000);
		//00434CC4  |> C745 C8 00809D43         MOV DWORD PTR SS:[EBP-38],439D8000
		WYD.SetValue<uint32_t>(0x0434CC7, 0x441D8000);
		//00434CD0  |> C745 C8 0000AF43         MOV DWORD PTR SS:[EBP-38],43AF0000
		WYD.SetValue<uint32_t>(0x0434CD3, 0x442F0000);
		//00434CDC  |> C745 C8 0080C043         MOV DWORD PTR SS:[EBP-38],43C08000
		WYD.SetValue<uint32_t>(0x0434CDF, 0x44408000);
		//00434CE8  |> C745 C8 0000D243         MOV DWORD PTR SS:[EBP-38],43D20000
		WYD.SetValue<uint32_t>(0x0434CEB, 0x44520000);
		//00434CFB  |. C745 B8 00000C42         MOV DWORD PTR SS:[EBP-48],420C0000
		WYD.SetValue<uint32_t>(0x0434CFE, 0x428C0000);
		//00434D07  |> C745 C8 00000C42         MOV DWORD PTR SS:[EBP-38],420C0000
		WYD.SetValue<uint32_t>(0x0434D0A, 0x428C0000);
		//00434D0E  |. C745 B8 00000C42         MOV DWORD PTR SS:[EBP-48],420C0000
		WYD.SetValue<uint32_t>(0x0434D11, 0x428C0000);
		//00434D1A  |> C745 C8 00008C42         MOV DWORD PTR SS:[EBP-38],428C0000
		WYD.SetValue<uint32_t>(0x0434D1D, 0x430C0000);
		//00434D21  |. C745 B8 00000C42         MOV DWORD PTR SS:[EBP-48],420C0000
		WYD.SetValue<uint32_t>(0x0434D24, 0x428C0000);
		//00434D2A  |> C745 C8 0000D242         MOV DWORD PTR SS:[EBP-38],42D20000
		WYD.SetValue<uint32_t>(0x0434D2D, 0x43520000);
		//00434D31  |. C745 B8 00000C42         MOV DWORD PTR SS:[EBP-48],420C0000
		WYD.SetValue<uint32_t>(0x0434D34, 0x428C0000);
		//00434D3A  |> C745 C8 00000C43         MOV DWORD PTR SS:[EBP-38],430C0000
		WYD.SetValue<uint32_t>(0x0434D3D, 0x438C0000);
		//00434D41  |. C745 B8 00000C42         MOV DWORD PTR SS:[EBP-48],420C0000
		WYD.SetValue<uint32_t>(0x0434D44, 0x428C0000);
		//00434D4A  |> C745 C8 00002F43         MOV DWORD PTR SS:[EBP-38],432F0000
		WYD.SetValue<uint32_t>(0x0434D4D, 0x43AF0000);
		//00434D51  |. C745 B8 00000C42         MOV DWORD PTR SS:[EBP-48],420C0000
		WYD.SetValue<uint32_t>(0x0434D54, 0x428C0000);
		//00434D5A  |> C745 C8 00005243         MOV DWORD PTR SS:[EBP-38],43520000
		WYD.SetValue<uint32_t>(0x0434D5D, 0x43D20000);
		//00434D61  |. C745 B8 00000C42         MOV DWORD PTR SS:[EBP-48],420C0000
		WYD.SetValue<uint32_t>(0x0434D64, 0x428C0000);
		//00434D6A  |> C745 C8 00007543         MOV DWORD PTR SS:[EBP-38],43750000
		WYD.SetValue<uint32_t>(0x0434D6D, 0x43F50000);
		//00434D71  |. C745 B8 00000C42         MOV DWORD PTR SS:[EBP-48],420C0000
		WYD.SetValue<uint32_t>(0x0434D74, 0x428C0000);
		//00434D7A  |> C745 C8 00008C43         MOV DWORD PTR SS:[EBP-38],438C0000
		WYD.SetValue<uint32_t>(0x0434D7D, 0x440C0000);
		//00434D81  |. C745 B8 00000C42         MOV DWORD PTR SS:[EBP-48],420C0000
		WYD.SetValue<uint32_t>(0x0434D84, 0x428C0000);
		//00434D8A  |> C745 C8 00809D43         MOV DWORD PTR SS:[EBP-38],439D8000
		WYD.SetValue<uint32_t>(0x0434D8D, 0x441D8000);
		//00434D91  |. C745 B8 00000C42         MOV DWORD PTR SS:[EBP-48],420C0000
		WYD.SetValue<uint32_t>(0x0434D94, 0x428C0000);

		WYD.SetHook(eHookType::JMP, 0x47D73F, WYD.GetPtr(&HookNaked::NKD_FixSkillBar)); //Hook Correção Skill Bar Time
		WYD.fillWithNop(0x47D8F7, 6); //Hook Correção Skill Bar Time
		WYD.SetHook(eHookType::JMP, 0x47D71A, 0x47D73F);  //Hook Correção Skill Bar Time

		WYD.SetHook(eHookType::JMP, 0x44FE91, WYD.GetPtr(&HookNaked::NKD_CallBack_Event_Esc), 3);

#pragma endregion

		VirtualProtect((int*)0x0401000, 0x5F0FFF - 0x0401000, dwOldProtectFlag_text, &dwOldProtectFlag_text);

		return TRUE;
	}
	catch (...)
	{
		return FALSE;
	}
} 

__declspec(naked) void HookNaked::NKD_NewNPCComp()
{
	static int CALL_Nativo = 0x57E819;
	static int CALL_Nativo2 = 0x497DF2;

	static int JMP_SaidaNativo = 0x498B3B;
	static int JMP_SaidaIndex = 0x498B39;
	static int JMP_SaidaIndex3 = 0x498B39;
	static int JMP_SaidaIndex2 = 0x498B17;

	__asm
	{
		CMP EDX, 0x43
		JNZ lblVerificarNovoIndex

		PUSH 0x0D
		PUSH 0x19
		PUSH 0x43
		MOV ECX, DWORD PTR SS : [EBP - 0x4]
		ADD ECX, 0x27D6C
		CALL CALL_Nativo
		MOV EAX, DWORD PTR SS : [EBP - 0x4]
		MOV ECX, DWORD PTR DS : [EAX + 0x6A4C4]
		XOR EDX, EDX
		CMP DWORD PTR DS : [ECX + 0x28] , 0
		SETE DL
		PUSH EDX
		MOV ECX, DWORD PTR SS : [EBP - 0x4]
		CALL CALL_Nativo2
		MOV EAX, 1
		JMP JMP_SaidaNativo

		lblVerificarNovoIndex :
		CMP EDX, 0x3a // FACE
			JNZ lblSaidaGeral
			MOV DWORD PTR DS : [0x636650] , 1
			PUSH 0x15 //Definir X/128 onde o NPC vai está (Essa janela só sera aberta nessas posições)
			PUSH 0x15 //Definir Y/128 onde o NPC vai está (Essa janela só sera aberta nessas posições)
			PUSH 0x3a //(FACE do NPC NOVO)
			MOV ECX, DWORD PTR SS : [EBP - 0x4]
			ADD ECX, 0x27D6C
			CALL CALL_Nativo
			MOV ECX, DWORD PTR SS : [EBP - 0x4]
			MOV EDX, DWORD PTR DS : [ECX + 0x6A4C4]
			JMP JMP_SaidaIndex2

			lblSaidaGeral :
		JMP JMP_SaidaIndex3

	}
}

void HookNaked::SetStringOnHP(int pointer, char* strz)
{
	__asm
	{
		PUSH 0x1
		MOV EAX, DWORD PTR SS : [strz]
		PUSH EAX

		MOV EDX, pointer
		MOV ECX, DWORD PTR DS : [EDX + 0x610]
		MOV EAX, pointer
		MOV EDX, DWORD PTR DS : [EAX + 0x610]
		MOV EAX, DWORD PTR DS : [EDX]
		CALL DWORD PTR DS : [EAX + 0x80]
	}
}

void HookNaked::FormatIntegerToStringWithDots(char* string, int value)
{
	char st[32];
	char result[32];
	memset(result, 0, sizeof result);

	_itoa(value, st, 10);

	int len = strlen(st);
	int sum = ((len - 1) / 3);



	for (int i = (len - 1), count = 0, index = (len - 1) + sum; i >= 0; i--, count++)
	{
		if (!(count % 3) && count != 0)
		{
			result[index] = '.';
			index--;
		}

		result[index] = st[i];

		count++;
		index--;
	}

	sprintf(string, "%s", result);
}

void HookNaked::ToPrettySize(int value, char* str)
{
	if (value < 100000)
	{
		FormatIntegerToStringWithDots(str, value);
		return;
	}

	int thousand = 1000;
	int million = 1000000;
	int billion = 1000000000;

	int asThousand = static_cast<int>(round((double)value / thousand));
	int asMillion = static_cast<int>(round((double)value / million));
	int asBillion = static_cast<int>(round((double)value / billion));

	if (asBillion > 1)
		sprintf(str, "%dKKK", asBillion);
	else if (asMillion > 1)
		sprintf(str, "%dKK", asMillion);
	else if (asThousand > 1)
		sprintf(str, "%dK", asThousand);
}

bool __stdcall HookNaked::HKD_SetHPNumberOnMosterHP(int pointer)
{
	int* connId = reinterpret_cast<int*>(pointer + 0x20);

	if (*connId < 1000)
		return false;

	char* name = reinterpret_cast<char*>(pointer + 0xF0);
	int* curHp = reinterpret_cast<int*>(pointer + 0x1CC);
	int* maxHp = reinterpret_cast<int*>(pointer + 0x1D0);

	char str[256];
	

	if (*maxHp != 0) //MOB com item de HP
	{
		if (curHp != 0 && maxHp != 0)
		{
			sprintf(str, "%s - [%d de %d]", name, *curHp, *maxHp);
		}
		else
			sprintf(str, "%s", name);
	}
	else // MOB sem item de HP
	{
		STRUCT_SCORE* status = reinterpret_cast<STRUCT_SCORE*>(pointer + 0x3F8);

		if (status->Hp != 0 && status->MaxHp != 0)
		{
			sprintf(str, "%s - [%d de %d]", name, status->Hp, status->MaxHp);
		}
		else
			sprintf(str, "%s", name);
	}

	//// MOB com item de HP
	//if (*maxHp != 0)
	//{
	//	if (curHp != 0 && maxHp != 0)
	//	{
	//		char curHpStr[30];
	//		ToPrettySize(*curHp, curHpStr);

	//		char maxHpStr[30];
	//		ToPrettySize(*maxHp, maxHpStr);

	//		sprintf(str, "%s - [%s de %s]", name, curHpStr, maxHpStr);
	//	}
	//	else
	//		sprintf(str, "%s - [?/?]", name);
	//}
	//else // MOB sem item de HP
	//{
	//	STRUCT_SCORE* status = reinterpret_cast<STRUCT_SCORE*>(pointer + 0x3F8);

	//	if (status->Hp != 0 && status->MaxHp != 0)
	//	{
	//		char curHpStr[30];
	//		ToPrettySize(status->Hp, curHpStr);

	//		char maxHpStr[30];
	//		ToPrettySize(status->Hp, maxHpStr);

	//		sprintf(str, "%s - [%s de %s]", name, curHpStr, maxHpStr);
	//	}
	//	else
	//		sprintf(str, "%s - [?/?]", name);
	//}

	SetStringOnHP(pointer, str);

	return true;
}

__declspec(naked) void HookNaked::NKD_SetHPNumberOnMonsterHP()
{
	__asm
	{
		MOV EAX, DWORD PTR SS : [EBP - 0x1B4]
		PUSH EAX

		CALL HKD_SetHPNumberOnMosterHP

		CMP AL, FALSE
		JE lbl_ContinueNormalExecution
		PUSH 0x04E219D
		RETN

		lbl_ContinueNormalExecution :
		PUSH 0x1
			MOV ECX, DWORD PTR SS : [EBP - 0x1B4]

			MOV EAX, 0x04E2176
			JMP EAX
	}
}

__declspec(naked) void HookNaked::NKD_GetCreateMob_ChangeHPText()
{
	__asm
	{
		MOV EAX, DWORD PTR SS : [EBP - 0x10]
		PUSH EAX

		CALL HKD_SetHPNumberOnMosterHP

		MOV EDX, DWORD PTR SS : [EBP - 0x10]
		CMP DWORD PTR DS : [EDX + 0x218] , 0x38

		PUSH 0x0484728
		RETN
	}
}

__declspec(naked) void HookNaked::NKD_SetDefaultLocation()
{
	__asm
	{
		MOV DWORD PTR SS : [EBP - 0x18] , 0x0
		MOV EAX, DWORD PTR SS : [EBP - 0x2C]
		MOV DWORD PTR DS : [EAX + 0x30] , 0xB
		PUSH 0x042344E
		RETN
	}
}

int HookNaked::HKD_GetSkillType(int skillId)
{
	if (skillId >= 0 && skillId <= 96)
		return 7;

	return 3;
}

__declspec(naked) void HookNaked::NKD_GetAttackType()
{
	__asm
	{
		MOV ECX, DWORD PTR SS : [EBP - 0x10]
		MOVSX EDX, WORD PTR DS : [ECX + 0x38]
		PUSH EDX
		CALL HookNaked::HKD_GetSkillType
		ADD ESP, 0x4
		PUSH EAX
		MOV ECX, DWORD PTR SS : [EBP - 0x9DC]
		PUSH 0x0494AB7
		RETN
	}
}

__declspec(naked) void HookNaked::NKD_GetAttackType2()
{
	__asm
	{
		MOV ECX, DWORD PTR SS : [EBP - 0x10]
		MOVSX EDX, WORD PTR DS : [ECX + 0x38]
		PUSH EDX
		CALL HookNaked::HKD_GetSkillType
		ADD ESP, 0x4
		PUSH EAX
		PUSH 0x0
		PUSH 0x5DC
		PUSH 0x04921E4
		RETN

	}
}

__declspec(naked) void HookNaked::NKD_ChangeTextureFont()
{
	__asm
	{
		MOV EAX, DWORD PTR SS : [EBP - 0x2C]
		CMP DWORD PTR DS : [EAX + 0xAC] , 0x7
		JE ChangeTexture
		MOV EAX, DWORD PTR SS : [EBP - 0x2C]
		CMP DWORD PTR DS : [EAX + 0xAC] , 0x1
		PUSH 0x04232EC
		RETN

		ChangeTexture :
		MOV ECX, DWORD PTR SS : [EBP - 0x2C]
			MOV DWORD PTR DS : [ECX + 0xB0] , 143
			PUSH 0x04233AF
			RETN
	}
}

__declspec(naked) void HookNaked::NKD_FixSkillBar()
{
	__asm
	{
		MOVSX ECX, BYTE PTR SS : [EBP - 034Ch]
		MOV EDX, DWORD PTR SS : [EBP - 07B8h]
		MOV EAX, DWORD PTR SS : [EBP + 08h]
		SUB EAX, DWORD PTR DS : [EDX + ECX * 04h + 08BEA0h]
		MOV DWORD PTR SS : [EBP - 0350h] , EAX

		MOVSX ECX, BYTE PTR SS : [EBP - 034Ch]
		TEST ECX, ECX

		PUSH 0047D76Fh
		RETN
	}
}

__declspec(naked) void HookNaked::NKD_ScrollMouseController()
{/*by seitbnao*/
	 // falta atualizar os addrees
	__asm
	{ 
		MOV EAX, DWORD PTR SS : [EBP - 0x8]
		CMP DWORD PTR DS : [EDX + 0x44] , 0x1019B
		PUSH 0x00401715

		PUSH DWORD PTR SS : [EBP + 0x14]//PosY
		PUSH DWORD PTR SS : [EBP + 0x10]//PosX
		PUSH DWORD PTR SS : [EBP + 0xC]//MouseStatus
		PUSH DWORD PTR SS : [EBP + 0x8]//Scontrol
		CALL GameInterface::ControlMouseController
		ADD ESP, 0x10
		RETN
	 
	}
} 
__declspec(naked) void HookNaked::NKD_UpdateResources()
{/*by seitbnao*/
	__asm
	{
		PUSH DWORD PTR SS : [EBP - 0x18C]
		CALL HookFunction
		ADD ESP, 0x4

		MOV EAX, DWORD PTR SS : [EBP - 0xC]
		ADD EAX, 1
		PUSH 0x00477B9B
		RETN
	}
}
__declspec(naked) void  HookNaked::NKD_Cam()
{ 
	if (!CameraLivre)
	{
		_asm
		{
			MOV EAX, DWORD PTR SS : [EBP - 0x8]// 
			MOV ECX, DWORD PTR SS : [EBP - 0x8]
			MOV DWORD PTR DS : [ECX + 0xC0] , 0x41a00000 // 0x14 
			FLD DWORD PTR DS : [EAX + 0x34] 
			FCOMP DWORD PTR DS : [ECX + 0xC0]
			FSTSW AX
			TEST AH, 0x41
			JNZ label_saida

			PUSH 0x004B55E8 

			 
			RETN

			label_saida :
			PUSH 0x004B5603 


				RETN
		}

		CameraLivre = 1;
	}
	else
	{
		_asm
		{
			MOV EAX, DWORD PTR SS : [EBP - 0x8]
			MOV ECX, DWORD PTR SS : [EBP - 0x8]
			MOV DWORD PTR DS : [ECX + 0xC0] , 0x41800000 // 0x20
			FLD DWORD PTR DS : [EAX + 0x34]
			FCOMP DWORD PTR DS : [ECX + 0xC0]
			FSTSW AX
			TEST AH, 0x41
			JNZ label_saida_2

			PUSH 0x004B55E8
			RETN

			label_saida_2 :
			PUSH 0x004B5603
				RETN
		}

		CameraLivre = 0;
	}

}


__declspec(naked) void HookNaked::NKD_KeyPress_NewButton()
{
	__asm
	{
		CMP EAX, 01h
		JE lbl_end

		XOR EAX, EAX
		MOV AL, BYTE PTR SS : [EBP + 08h]
		PUSH EAX

		CALL HKD_KeyPress_NewButton

		TEST EAX, EAX
		JE lbl_xor

		MOV EAX, 01h
		JMP lbl_end

		lbl_xor :
		XOR EAX, EAX

			lbl_end :
		MOV ESP, EBP
			POP EBP

			RETN 08h
	}//emblema
}

__declspec(naked) void HookNaked::NKD_SendChat()
{
	__asm
	{
		MOV EAX, DWORD PTR SS : [EBP - 0x98]
		MOV EDX, DWORD PTR DS : [EAX]
		MOV ECX, DWORD PTR SS : [EBP - 0x98]
		CALL DWORD PTR DS : [EDX + 0x88]

		PUSH EAX
		CALL HKD_SendChat
		ADD ESP, 0x08

		TEST EAX, EAX
		JNZ chk_other_cmd

		MOV EAX, 0x01
		MOV ECX, 0x473794
		JMP ECX

		chk_other_cmd :

		MOV ECX, 0x467740
			JMP ECX
	}
}

//__declspec(naked) void HookNaked::NKD_Macro_NewPotions_MP()
//{
//	__asm
//	{
//		CMP DWORD PTR SS : [EBP - 018h] , 00h
//		JE lbl_continueLoop
//
//		PUSH 02h
//
//		MOV ECX, DWORD PTR SS : [EBP - 018h]
//		MOV EDX, DWORD PTR DS : [ECX + 0670h]
//
//		PUSH EDX
//
//		CALL HKD_Macro_NewPotions
//		ADD ESP, 08h
//
//		TEST EAX, EAX
//		JE lbl_continueLoop
//
//		MOV EAX, 00451688h
//		JMP EAX
//
//		lbl_continueLoop :
//		MOV EAX, 00451588h
//			JMP EAX
//	}
//}
//
//__declspec(naked) void HookNaked::NKD_Macro_NewPotions_HP()
//{
//	__asm
//	{
//		CMP DWORD PTR SS : [EBP - 018h] , 00h
//		JE lbl_continueLoop
//
//		PUSH 01h
//
//		MOV ECX, DWORD PTR SS : [EBP - 018h]
//		MOV EDX, DWORD PTR DS : [ECX + 0670h]
//
//		PUSH EDX
//
//		CALL HKD_Macro_NewPotions
//		ADD ESP, 08h
//
//		TEST EAX, EAX
//		JE lbl_continueLoop
//
//		MOV EAX, 00451688h
//		JMP EAX
//
//		lbl_continueLoop :
//		MOV EAX, 00451588h
//			JMP EAX
//	}
//}

__declspec(naked) void HookNaked::NKD_GetItemAbility_Esfera()
{
	static const DWORD dwContinue[2] = { 0x005385B4, 0x005388BF };
	__asm
	{
		MOV EAX, DWORD PTR SS : [EBP + 0Ch]
		AND EAX, 0FFh

		PUSH EAX

		PUSH DWORD PTR SS : [EBP + 08h]

		CALL HKD_GetItemAbility_Esferas
		ADD ESP, 08h

		TEST EAX, EAX
		JE lbl_continue

		JMP dwContinue + 04h

		lbl_continue :
		MOV EAX, DWORD PTR SS : [EBP + 0Ch]
			AND EAX, 0FFh

			JMP dwContinue
	}
}

__declspec(naked) void HookNaked::NKD_ValidadeEsferas()
{
	__asm {

		MOV EDX, DWORD PTR SS : [EBP - 0x8]
		MOV EAX, DWORD PTR DS : [EDX + 0x670]
		PUSH EAX
		LEA ECX, DWORD PTR SS : [EBP - 0xAC]
		PUSH ECX
		CALL FormataValidadeEsferas
		ADD ESP, 0xC
		PUSH 0x41A7BC
		RETN
	}


}

__declspec(naked) void HookNaked::NKD_ValidadeTrajes()
{
	__asm {
		MOV EDX, DWORD PTR SS : [EBP - 0x8]
		MOV EAX, DWORD PTR DS : [EDX + 0x670]
		PUSH EAX
		LEA ECX, DWORD PTR SS : [EBP - 0xAC]
		PUSH ECX
		CALL FormataValidadeTraje
		ADD ESP, 0xC
		PUSH 0x41AACB
		RETN
	}
}

__declspec(naked) void HookNaked::NKD_ValidadeFadas()
{
	__asm {
		// 3 argumentoss  msg ta certa?
		LEA ECX, DWORD PTR SS : [EBP - 0xA18]
		PUSH ECX
		LEA ECX, DWORD PTR SS : [EBP - 0xAC] // msg ta certo?
		PUSH ECX
		CALL FormataValidadeFada // to falando oq agr? ouvi
		ADD ESP, 0xC
		PUSH 0x41A176
		RETN

	}
}

__declspec(naked) void HookNaked::NKD_ProcessClientMessage_03BBh()
{
	__asm
	{
		MOV ECX, DWORD PTR SS : [EBP - 04h]
		XOR EDX, EDX

		MOV DX, WORD PTR DS : [ECX + 0Eh]

		MOV DWORD PTR SS : [EBP - 08Ch] , EDX

		MOV EAX, DWORD PTR SS : [EBP - 04h]
		XOR ECX, ECX

		MOV CX, WORD PTR DS : [EAX + 0Ch]

		MOV DWORD PTR SS : [EBP - 088h] , ECX

		MOV EAX, 0048B076h
		JMP EAX
	}
}

__declspec(naked) void HookNaked::NKD_ItemPriceString()
{
	__asm
	{
		LEA EAX, DWORD PTR SS : [EBP - 0x11D4] // MSG
		PUSH EAX
		MOV EAX, DWORD PTR SS : [EBP - 0x8]
		MOV ECX, DWORD PTR DS : [EAX + 0x670]
		PUSH ECX
		CALL SetItemPriceString
		TEST AL, AL
		JE lblContinueExec
		PUSH 0x41D05B
		RETN

		lblContinueExec :
		FLD DWORD PTR SS : [EBP - 0x11E4]
			PUSH 0x41CFD3
			RETN
	}
}

__declspec(naked) void HookNaked::NKD_FixMageMacro()
{
	__asm
	{
		MOV ECX, DWORD PTR SS : [EBP - 0x11C]
		// Diferente do Macro Continuo, então pula
		CMP DWORD PTR DS : [ECX + 0x8A3A0] , 0x0
		JNZ lbl_JMP
		PUSH 0x004970F9
		RETN

		lbl_JMP :
		PUSH 0x004972E5
			RETN
	}
}


__declspec(naked) void HookNaked::NKD_NewItensDays_1()
{
	__asm
	{
		CMP EAX, 0x0F8C
		JL LoopOriginal
		PUSH 0x41A529
		RETN
		LoopOriginal :
		PUSH EAX
			CALL NewItensDay
			TEST AL, AL
			JE VoltaOriginal
			PUSH 0x41A56E
			RETN

			VoltaOriginal :
		PUSH 0x41A825
			RETN
	}
}

__declspec(naked) void HookNaked::NKD_NewItensDays_2()
{
	__asm
	{
		CMP EAX, 0x0F9F
		JG LoopOriginal
		PUSH 0x41A540
		RETN

		LoopOriginal :
		PUSH EAX
			CALL NewItensDay
			TEST AL, AL
			JE VoltaOriginal
			PUSH 0x41A56E
			RETN
			VoltaOriginal :
		PUSH 0x41A825
			RETN
	}
}

__declspec(naked) void HookNaked::NKD_ChangeTabColor()
{
	__asm
	{
		MOV EDX, DWORD PTR SS : [EBP - 0x1B4]
		ADD EDX, 0x100
		PUSH EDX

		CALL HKD_ChangeTabColor

		ADD ESP, 04h

		PUSH EAX

		MOV EDX, 0x04E21E0

		JMP EDX
	}
}

__declspec(naked) void HookNaked::NKD_ItemPrice_FormatDecimal_03()
{
	__asm
	{
		MOV EDX, DWORD PTR SS : [EBP - 011F4h]
		PUSH EDX

		LEA EAX, DWORD PTR SS : [EBP - 01278h]
		PUSH EAX

		CALL HKD_ItemPrice_FormatDecimal_03
		ADD ESP, 08h

		MOV EAX, 0x041D1CF
		JMP EAX
	}

}

__declspec(naked) void HookNaked::NKD_ItemPrice_FormatDecimal_02()
{
	{
		static int retn = 0;
		__asm
		{
			LEA EAX, DWORD PTR SS : [EBP - 1278]
			PUSH EAX

			MOV EDX, DWORD PTR SS : [EBP - 01154h]
			ADD EDX, EAX
			PUSH EDX

			LEA EAX, DWORD PTR SS : [EBP - 011D4h]
			PUSH EAX

			CALL HKD_ItemPrice_FormatDecimal_02
			ADD ESP, 08h


			MOV EAX, 0x041CFF5
			JMP EAX
		}
	}
}

__declspec(naked) void HookNaked::NKD_ItemPrice_FormatDecimal()
{
	__asm
	{
		MOV EAX, DWORD PTR SS : [EBP - 08Ch]
		MOV ECX, DWORD PTR DS : [EAX + 058Ch]
		PUSH ECX

		MOV EAX, DWORD PTR SS : [EBP + 08h]
		PUSH EAX

		CALL HKD_ItemPrice_FormatDecimal_AutoTrade
		ADD ESP, 08h

		MOV EAX, 0x04213DA
		JMP EAX
	}
}

__declspec(naked) void HookNaked::NKD_CallBack_Event_Esc()
{
	// 756 -> 0040B980  /$ 55             PUSH EBP
	// 762 -> 0040C2C0  /$ 55             PUSH EBP
	static int call_1 = 0x40C2C0;

	// 756 -> 00454A72  |> 8B4D D0        MOV ECX,DWORD PTR SS:[EBP-30]
	// 762 -> 0044FEB5  |> 8B4D D0        MOV ECX,DWORD PTR SS:[EBP-30]
	static int addr_jmp_jnz = 0x44FEB5;

	// 756 -> 00454CAE  |> 8BE5           MOV ESP,EBP
	// 762 -> 004500F1  |> 8BE5           MOV ESP,EBP
	static int addr_jmp_saida = 0x4500F1;

	_asm
	{
		/*Guarda o Valor em ECX*/
		MOV ECX, EAX

		CALL HookNaked::HKD_CallBack_Event_Esc

		TEST AL, AL
		JNZ lbl_saida //retorna true ele jumpa, se retornar false ele n jumpa


		/*retorna o Valor pra EAX*/
		MOV EAX, ECX


		MOV ECX, DWORD PTR SS : [EBP - 0x38]
		CALL call_1
		CMP EAX, 1
		JNZ lbl_proximo
		PUSH 0x0
		PUSH 0x100E9
		MOV EAX, DWORD PTR SS : [EBP - 0x40]
		MOV EDX, DWORD PTR DS : [EAX]
		MOV ECX, DWORD PTR SS : [EBP - 0x40]
		CALL DWORD PTR DS : [EDX + 0x58]
		JMP addr_jmp_saida


		lbl_proximo :
		JMP addr_jmp_jnz

			lbl_saida :
		/*retorna o Valor pra EAX*/
		MOV EAX, ECX

			JMP addr_jmp_saida

	}
}

__declspec(naked) void HookNaked::NKD_GreenTime_NewArea()
{
	__asm
	{
		MOV EDX, DWORD PTR SS : [EBP - 07B8h]
		MOV EAX, DWORD PTR DS : [EDX + 040h]

		PUSH DWORD PTR DS : [EAX + 020A24h]

		MOV EDX, DWORD PTR SS : [EBP - 07B8h]
		MOV EAX, DWORD PTR DS : [EDX + 040h]

		PUSH DWORD PTR DS : [EAX + 020A20h]

		CALL HKD_GreenTime_NewArea
		ADD ESP, 08h

		TEST EAX, EAX
		JE lbl_retn

		MOV EAX, 0047DD1Ah
		JMP EAX

		lbl_retn :
		MOV EAX, 0047DAF2h
			JMP EAX
	}
}

__declspec(naked) void HookNaked::NKD_FixItemDescription()
{
	static COLORREF line1Color = 0, line2Color = 0, line3Color = 0, line4Color = 0,
		line5Color = 0, line6Color = 0, line7Color = 0, line8Color = 0, line9Color = 0, line10Color = 0;
	static int32_t lineCounter = 0, index = 0;
	static char line2[128] = { 0 }, line3[128] = { 0 }, line4[128]{ 0, },
		line5[128] = { 0 }, line6[128] = { 0 }, line7[128]{ 0, },
		line8[128] = { 0 }, line9[128] = { 0 }, line10[128]{ 0, };

	__asm
	{
		LEA EAX, line10Color
		PUSH EAX
		LEA EAX, line9Color
		PUSH EAX
		LEA EAX, line8Color
		PUSH EAX
		LEA EAX, line7Color
		PUSH EAX
		LEA EAX, line6Color
		PUSH EAX
		LEA EAX, line5Color
		PUSH EAX
		LEA EAX, line4Color
		PUSH EAX
		LEA EAX, line3Color
		PUSH EAX
		LEA EAX, line2Color
		PUSH EAX
		LEA EAX, line1Color
		PUSH EAX
		LEA ECX, line10
		PUSH ECX
		LEA ECX, line9
		PUSH ECX
		LEA ECX, line8
		PUSH ECX
		LEA ECX, line7
		PUSH ECX
		LEA ECX, line6
		PUSH ECX
		LEA ECX, line5
		PUSH ECX
		LEA ECX, line4
		PUSH ECX
		LEA ECX, line3
		PUSH ECX
		LEA ECX, line2
		PUSH ECX
		LEA EDX, DWORD PTR SS : [EBP - 0xA8]
		PUSH EDX
		MOV ECX, DWORD PTR SS : [EBP - 0x8]
		MOV EDX, DWORD PTR DS : [ECX + 0x670]
		PUSH EDX
		CALL AddItemDescription
		TEST EAX, EAX
		JE lblContinueExec

		MOV lineCounter, EAX // 2
		MOV index, 0
		JMP LoopStart

		LoopEnd :
		MOV EAX, index
			ADD EAX, 1
			MOV index, EAX
			LoopStart :
		MOV EAX, index
			CMP EAX, lineCounter
			JGE lblContinueExec


			PUSH 0
			CMP index, 0
			JG lblLine2
			LEA ECX, DWORD PTR SS : [EBP - 0xA8]
			PUSH ECX
			JMP lblContinuePush
			lblLine2 :
		CMP index, 1
			JG  lblLine3
			LEA ECX, line2
			PUSH ECX
			JMP lblContinuePush
			lblLine3 :
		CMP index, 2
			JG  lblLine4
			LEA ECX, line3
			PUSH ECX
			JMP lblContinuePush
			lblLine4 :
		CMP index, 3
			JG  lblLine5
			LEA ECX, line4
			PUSH ECX
			JMP lblContinuePush
			lblLine5 :
		CMP index, 4
			JG  lblLine6
			LEA ECX, line5
			PUSH ECX
			JMP lblContinuePush
			lblLine6 :
		CMP index, 5
			JG  lblLine7
			LEA ECX, line6
			PUSH ECX
			JMP lblContinuePush
			lblLine7 :
		CMP index, 6
			JG  lblLine8
			LEA ECX, line7
			PUSH ECX
			JMP lblContinuePush
			lblLine8 :
		CMP index, 7
			JG  lblLine9
			LEA ECX, line8
			PUSH ECX
			JMP lblContinuePush
			lblLine9 :
		CMP index, 8
			JG  lblLine10
			LEA ECX, line9
			PUSH ECX
			JMP lblContinuePush
			lblLine10 :
		CMP index, 9
			JG  lblEmptyLine
			LEA ECX, line10
			PUSH ECX
			JMP lblContinuePush
			lblEmptyLine :
		PUSH 0
			JMP lblContinuePush
			lblContinuePush :
		MOV EDX, DWORD PTR SS : [EBP - 0x28]
			MOV EAX, DWORD PTR SS : [EBP - 0x10]
			MOV ECX, DWORD PTR DS : [EAX + EDX * 4 + 0x27A10]
			MOV EDX, DWORD PTR SS : [EBP - 0x28]
			MOV EAX, DWORD PTR SS : [EBP - 0x10]
			MOV EDX, DWORD PTR DS : [EAX + EDX * 4 + 0x27A10]
			MOV EAX, DWORD PTR DS : [EDX]
			CALL DWORD PTR DS : [EAX + 0x80]


			CMP index, 0
			JG lblColorLine2
			PUSH line1Color
			JMP lblContinueFuncCall

			lblColorLine2 :
		CMP index, 1
			JG lblColorLine3
			PUSH line2Color
			JMP lblContinueFuncCall

			lblColorLine3 :
		CMP index, 2
			JG lblColorLine4
			PUSH line3Color
			JMP lblContinueFuncCall

			lblColorLine4 :
		CMP index, 3
			JG lblColorLine5
			PUSH line4Color
			JMP lblContinueFuncCall

			lblColorLine5 :
		CMP index, 4
			JG lblColorLine6
			PUSH line5Color
			JMP lblContinueFuncCall

			lblColorLine6 :
		CMP index, 5
			JG lblColorLine7
			PUSH line6Color
			JMP lblContinueFuncCall

			lblColorLine7 :
		CMP index, 6
			JG lblColorLine8
			PUSH line7Color
			JMP lblContinueFuncCall

			lblColorLine8 :
		CMP index, 7
			JG lblColorLine9
			PUSH line8Color
			JMP lblContinueFuncCall

			lblColorLine9 :
		CMP index, 8
			JG lblColorLine10
			PUSH line9Color
			JMP lblContinueFuncCall

			lblColorLine10 :
		CMP index, 9
			JG lblNoColor
			PUSH line10Color
			JMP lblContinueFuncCall

			lblNoColor :
		PUSH 0
			JMP lblContinueFuncCall

			lblContinueFuncCall :
		MOV EDX, DWORD PTR SS : [EBP - 0x28]
			MOV EAX, DWORD PTR SS : [EBP - 0x10]
			MOV ECX, DWORD PTR DS : [EAX + EDX * 4 + 0x27A10]
			MOV EDX, DWORD PTR SS : [EBP - 0x28]
			MOV EAX, DWORD PTR SS : [EBP - 0x10]
			MOV EDX, DWORD PTR DS : [EAX + EDX * 4 + 0x27A10]
			MOV EAX, DWORD PTR DS : [EDX]
			CALL DWORD PTR DS : [EAX + 0x84]

			MOV ECX, DWORD PTR SS : [EBP - 0x28]
			ADD ECX, 0x1
			MOV DWORD PTR SS : [EBP - 0x28] , ECX

			JMP LoopEnd

			lblContinueExec :
		MOV EDX, DWORD PTR SS : [EBP - 0x8]
			MOV EAX, DWORD PTR DS : [EDX + 0x670]

			PUSH 0x0041C471
			RETN
	}
}

//__declspec(naked) void HookNaked::NKD_ItemDescription()
//{
//	static COLORREF line1Color = 0, line2Color = 0, line3Color = 0, line4Color = 0, line5Color = 0, line6Color = 0, line7Color = 0, line8Color = 0, line9Color = 0, line10Color = 0;
//
//	static int lineCounter = 0, index = 0;
//
//	static char line2[128] = { 0 }, line3[128] = { 0 }, line4[128]{ 0, }, line5[128] = { 0 }, line6[128] = { 0 }, line7[128]{ 0, }, line8[128] = { 0 }, line9[128] = { 0 }, line10[128]{ 0, };
//
//	__asm
//	{
//		LEA EAX, line10Color
//		PUSH EAX
//		LEA EAX, line9Color
//		PUSH EAX
//		LEA EAX, line8Color
//		PUSH EAX
//		LEA EAX, line7Color
//		PUSH EAX
//		LEA EAX, line6Color
//		PUSH EAX
//		LEA EAX, line5Color
//		PUSH EAX
//		LEA EAX, line4Color
//		PUSH EAX
//		LEA EAX, line3Color
//		PUSH EAX
//		LEA EAX, line2Color
//		PUSH EAX
//		LEA EAX, line1Color
//		PUSH EAX
//		LEA ECX, line10
//		PUSH ECX
//		LEA ECX, line9
//		PUSH ECX
//		LEA ECX, line8
//		PUSH ECX
//		LEA ECX, line7
//		PUSH ECX
//		LEA ECX, line6
//		PUSH ECX
//		LEA ECX, line5
//		PUSH ECX
//		LEA ECX, line4
//		PUSH ECX
//		LEA ECX, line3
//		PUSH ECX
//		LEA ECX, line2
//		PUSH ECX
//		LEA EDX, DWORD PTR SS : [EBP - 0xAC]
//		PUSH EDX
//		MOV ECX, DWORD PTR SS : [EBP - 0x8]
//		MOV EDX, DWORD PTR DS : [ECX + 0x670]
//		PUSH EDX
//		CALL CreateObjectText
//		TEST EAX, EAX
//		JE lblContinueExec
//
//		MOV lineCounter, EAX // 2
//		MOV index, 0
//		JMP LoopStart
//
//		LoopEnd :
//		MOV EAX, index
//			ADD EAX, 1
//			MOV index, EAX
//			LoopStart :
//		MOV EAX, index
//			CMP EAX, lineCounter
//			JGE lblContinueExec
//
//
//			PUSH 0
//			CMP index, 0
//			JG lblLine2
//			LEA ECX, DWORD PTR SS : [EBP - 0xAC]
//			PUSH ECX
//			JMP lblContinuePush
//			lblLine2 :
//		CMP index, 1
//			JG  lblLine3
//			LEA ECX, line2
//			PUSH ECX
//			JMP lblContinuePush
//			lblLine3 :
//		CMP index, 2
//			JG  lblLine4
//			LEA ECX, line3
//			PUSH ECX
//			JMP lblContinuePush
//			lblLine4 :
//		CMP index, 3
//			JG  lblLine5
//			LEA ECX, line4
//			PUSH ECX
//			JMP lblContinuePush
//			lblLine5 :
//		CMP index, 4
//			JG  lblLine6
//			LEA ECX, line5
//			PUSH ECX
//			JMP lblContinuePush
//			lblLine6 :
//		CMP index, 5
//			JG  lblLine7
//			LEA ECX, line6
//			PUSH ECX
//			JMP lblContinuePush
//			lblLine7 :
//		CMP index, 6
//			JG  lblLine8
//			LEA ECX, line7
//			PUSH ECX
//			JMP lblContinuePush
//			lblLine8 :
//		CMP index, 7
//			JG  lblLine9
//			LEA ECX, line8
//			PUSH ECX
//			JMP lblContinuePush
//			lblLine9 :
//		CMP index, 8
//			JG  lblLine10
//			LEA ECX, line9
//			PUSH ECX
//			JMP lblContinuePush
//			lblLine10 :
//		CMP index, 9
//			JG  lblEmptyLine
//			LEA ECX, line10
//			PUSH ECX
//			JMP lblContinuePush
//			lblEmptyLine :
//		PUSH 0
//			JMP lblContinuePush
//			lblContinuePush :
//		MOV EDX, DWORD PTR SS : [EBP - 0x28]
//			MOV EAX, DWORD PTR SS : [EBP - 0x10]
//			MOV ECX, DWORD PTR DS : [EAX + EDX * 4 + 0x27A10]
//			MOV EDX, DWORD PTR SS : [EBP - 0x28]
//			MOV EAX, DWORD PTR SS : [EBP - 0x10]
//			MOV EDX, DWORD PTR DS : [EAX + EDX * 4 + 0x27A10]
//			MOV EAX, DWORD PTR DS : [EDX]
//			CALL DWORD PTR DS : [EAX + 0x80]
//
//
//			CMP index, 0
//			JG lblColorLine2
//			PUSH line1Color
//			JMP lblContinueFuncCall
//
//			lblColorLine2 :
//		CMP index, 1
//			JG lblColorLine3
//			PUSH line2Color
//			JMP lblContinueFuncCall
//
//			lblColorLine3 :
//		CMP index, 2
//			JG lblColorLine4
//			PUSH line3Color
//			JMP lblContinueFuncCall
//
//			lblColorLine4 :
//		CMP index, 3
//			JG lblColorLine5
//			PUSH line4Color
//			JMP lblContinueFuncCall
//
//			lblColorLine5 :
//		CMP index, 4
//			JG lblColorLine6
//			PUSH line5Color
//			JMP lblContinueFuncCall
//
//			lblColorLine6 :
//		CMP index, 5
//			JG lblColorLine7
//			PUSH line6Color
//			JMP lblContinueFuncCall
//
//			lblColorLine7 :
//		CMP index, 6
//			JG lblColorLine8
//			PUSH line7Color
//			JMP lblContinueFuncCall
//
//			lblColorLine8 :
//		CMP index, 7
//			JG lblColorLine9
//			PUSH line8Color
//			JMP lblContinueFuncCall
//
//			lblColorLine9 :
//		CMP index, 8
//			JG lblColorLine10
//			PUSH line9Color
//			JMP lblContinueFuncCall
//
//			lblColorLine10 :
//		CMP index, 9
//			JG lblNoColor
//			PUSH line10Color
//			JMP lblContinueFuncCall
//
//			lblNoColor :
//		PUSH 0
//			JMP lblContinueFuncCall
//
//			lblContinueFuncCall :
//		MOV EDX, DWORD PTR SS : [EBP - 0x28]
//			MOV EAX, DWORD PTR SS : [EBP - 0x10]
//			MOV ECX, DWORD PTR DS : [EAX + EDX * 4 + 0x27A10]
//			MOV EDX, DWORD PTR SS : [EBP - 0x28]
//			MOV EAX, DWORD PTR SS : [EBP - 0x10]
//			MOV EDX, DWORD PTR DS : [EAX + EDX * 4 + 0x27A10]
//			MOV EAX, DWORD PTR DS : [EDX]
//			CALL DWORD PTR DS : [EAX + 0x84]
//
//			MOV ECX, DWORD PTR SS : [EBP - 0x28]
//			ADD ECX, 0x1
//			MOV DWORD PTR SS : [EBP - 0x28] , ECX
//
//			JMP LoopEnd
//
//			lblContinueExec :
//		MOV EDX, DWORD PTR SS : [EBP - 0x8]
//			MOV EAX, DWORD PTR DS : [EDX + 0x670]
//
//			PUSH 0x41C471 //0x041C484// | . 8B45 F8        MOV EAX, DWORD PTR SS : [EBP - 8]
//
//			RETN
//	}
//}

__declspec(naked) void HookNaked::NKD_SpeakChatColor()
{
	static const UINT32 dwContinue = 0x004A016E;

	__asm
	{
		MOV EAX, SpeakChatColor
		MOV DWORD PTR SS : [EBP - 0x87C] , EAX
		JMP dwContinue
	}
}

bool NewEffectTraje(INT32 Item)
{
	if (Item == 4171 || Item == 4172 || Item == 4176 || Item == 4177 || Item == 4182 || Item == 4183) //ID do traje que vai brilhar.
		return false;

	if (Item >= 4205 && Item <= 4207) //ID do traje que vai brilhar.
		return false;

	if (Item >= 4209 && Item <= 4213) //ID do traje que vai brilhar.
		return false;

	if (Item >= 4215 && Item <= 4229) //ID do traje que vai brilhar.
		return false;

	if (Item >= 4231 && Item <= 4235) //ID do traje que vai brilhar.
		return false;

	if (Item >= 4238 && Item <= 4240) //ID do traje que vai brilhar.
		return false;

	if (Item == 4242) //ID do traje que vai brilhar.
		return false;

	if (Item >= 4244 && Item <= 4248) //ID do traje que vai brilhar.
		return false;

}

__declspec(naked) void HookNaked::NKD_SGrid_OnMouseMove_SkinName()
{
	static const DWORD dwContinue = 0x004182CD;
	__asm
	{
		MOV EAX, DWORD PTR SS : [EBP - 08h]
		MOV ECX, DWORD PTR DS : [EAX + 0670h]

		PUSH ECX

		LEA EAX, DWORD PTR SS : [EBP - 0550h]
		PUSH EAX

		CALL SGrid_OnMouseMove_SkinName
		ADD ESP, 08h

		TEST AL, AL
		JE lbl_retn

		MOV EAX, 00418340h
		JMP EAX

		lbl_retn :
		MOV EAX, DWORD PTR SS : [EBP - 08h]
			MOV ECX, DWORD PTR DS : [EAX + 0670h]

			JMP dwContinue
	}
}

__declspec(naked) void HookNaked::NKD_ProcessViewMount_Skins()
{
	__asm
	{
		MOV EDX, DWORD PTR SS : [EBP - 04h]
		PUSH EDX

		PUSH DWORD PTR SS : [EBP - 08h]

		CALL ProcessViewMount_Skins
		ADD ESP, 08h

		MOV EAX, 005198A1h
		JMP EAX
	}
}

__declspec(naked) void HookNaked::NKD_NewEffectTraje()
{
	__asm
	{
		MOV ECX, DWORD PTR SS : [EBP - 0x18]
		MOVSX   EDX, WORD PTR[ECX + 0A60h]
		PUSH EDX
		CALL NewEffectTraje
		PUSH 0x519E46
		RETN

	}
}

__declspec(naked) void HookNaked::NKD_noSancFace() // Se não adicionar a face da Montaria ela fica brilhosa para os outros.
{
	_asm//onde c pois
	{
		CMP DWORD PTR SS : [EBP - 0x20] , 387
		JE correto
		CMP DWORD PTR SS : [EBP - 0x20] , 347
		JE correto
		CMP DWORD PTR SS : [EBP - 0x20] , 348
		JE correto
		CMP DWORD PTR SS : [EBP - 0x20] , 349
		JE correto
		CMP DWORD PTR SS : [EBP - 0x20] , 350
		JE correto
		PUSH 0x50C533
		RETN



	correto:
		PUSH 0x50C53C
			RETN

	}
}

__declspec(naked) void HookNaked::NKD_noSancID() // se não add o ID aqui a montaria fica brilhosa pros outros 
{
	_asm
	{
		CMP DWORD PTR SS : [EBP - 0x8] , 3990
		JE correto
		CMP DWORD PTR SS : [EBP - 0x8] , 3994
		JE correto
		CMP DWORD PTR SS : [EBP - 0x8] , 3999
		JE correto
		CMP DWORD PTR SS : [EBP - 0x8] , 3993
		JE correto
		CMP DWORD PTR SS : [EBP - 0x64] , 3996 //CMP DWORD PTR SS : [EBP - 0x8], 3996
		JE correto
		PUSH 0x50C779
		RETN

		correto :
		MOV ECX, DWORD PTR SS : [EBP - 0x28]
			MOV BYTE PTR DS : [ECX + 0x148] , 0
			MOV ECX, DWORD PTR SS : [EBP - 0x28]
			MOV BYTE PTR DS : [ECX + 0x147] , 0
			MOV EDX, DWORD PTR SS : [EBP - 0x28]
			MOV BYTE PTR DS : [EDX + 0x146] , 0
			PUSH 0x50C779
			RETN

	}
}

__declspec(naked) void HookNaked::NKD_AddVolatileMessageItem()
{
	__asm
	{
		CMP DWORD PTR SS : [EBP + 0xC] , 0x15E2 // 0xFD1
		JNZ lblNext
		JMP lblSuccess
		lblNext :
		PUSH DWORD PTR SS : [EBP + 0xC]
			CALL AddVolatileMessageItem
			TEST EAX, EAX
			JE lblContinueExec
			lblSuccess :
		MOV EAX, 1
			lblContinueExec :
			PUSH 0x422017
			RETN 4
	}
}

__declspec(naked) void HookNaked::NKD_AddVolatileMessageBox()
{
	static char msg[128] = { 0 };

	__asm
	{
		CMP DWORD PTR SS : [EBP - 0x1AC] , 0xD3
		JNZ lblNext
		PUSH 0x41FB3C
		RETN 4

		lblNext :
		LEA ECX, msg
		PUSH ECX
		MOV EAX, DWORD PTR SS : [EBP - 0x1B0]
		PUSH EAX
		CALL SetVolatileMessageBoxText
		TEST AL, AL
		JE lblContinueExec

		MOV EAX, DWORD PTR DS : [0x6F0AB0]
		MOV DWORD PTR SS : [EBP - 0x388] , EAX
		PUSH    0 // 0
		PUSH	0x373 // 0x373
		LEA EAX, msg
		PUSH EAX
		MOV     ECX, DWORD PTR SS : [EBP - 0x388]
		MOV     ECX, DWORD PTR DS : [ECX + 0xCC]
		MOV     EDX, DWORD PTR SS : [EBP - 0x388]
		MOV     EAX, DWORD PTR DS : [EDX + 0xCC]
		MOV     EDX, DWORD PTR DS : [EAX]
		CALL    DWORD PTR DS : [EDX + 0x8C]
		MOV     EAX, DWORD PTR SS : [EBP + 0x8]
		SHL     EAX, 0x10
		OR      EAX, DWORD PTR SS : [EBP + 0xC]
		MOV     ECX, DWORD PTR SS : [EBP - 0x388]
		MOV     EDX, DWORD PTR DS : [ECX + 0xCC]
		MOV     DWORD PTR DS : [EDX + 0x1E8] , EAX
		PUSH    1
		MOV     EAX, DWORD PTR SS : [EBP - 0x388]
		MOV     ECX, DWORD PTR DS : [EAX + 0xCC]
		MOV     EDX, DWORD PTR SS : [EBP - 0x388]
		MOV     EAX, DWORD PTR DS : [EDX + 0xCC]
		MOV     EDX, DWORD PTR DS : [EAX]
		CALL    DWORD PTR DS : [EDX + 0x60]
		PUSH 0x41FCFC
		RETN 4

		lblContinueExec :
		PUSH 0x41FBB2
		RETN 4
	}
}

__declspec(naked) void HookNaked::NKD_AddAmountItem()
{
	__asm
	{
		MOV EAX, DWORD PTR SS : [EBP - 0x60]

			CALL isSplittable
			TEST AL, AL
			JE lblIsSplittable

			MOV ECX, DWORD PTR SS : [EBP - 0x60]
			MOV EDX, DWORD PTR DS : [ECX + 0x670]

			PUSH 0x004205D9
			RETN

		lblIsSplittable :
		MOV BYTE PTR SS : [EBP - 0x5C], 1
			PUSH 0x420626
			RETN
	}

}

__declspec (naked) void HookNaked::NKD_CorrectBones()
{
	__asm
	{
		MOV EDX, DWORD PTR SS : [EBP - 0x350]
		LEA EDX, DWORD PTR DS : [EDX + 0x5C]
		PUSH EDX
		MOV EAX, DWORD PTR SS : [EBP - 0x14]
		PUSH EAX
		CALL HKD_CorrectBone
		MOV EDX, DWORD PTR SS : [EBP - 0x350]
		PUSH 0x004DE216
		RETN 4
	}
}

__declspec(naked) void HookNaked::NKD_LoadFiles()
{

	__asm
	{
		CMP DWORD PTR SS : [EBP + 0x8] , 0x21
		JNZ lblContinue
		PUSH 0x4CFDB9
		RETN 4


		lblContinue :
		MOV EAX, DWORD PTR SS : [EBP + 0x10]
		PUSH EAX // Mesh (MSH)
		MOV ECX, DWORD PTR SS : [EBP + 0xC]
		PUSH ECX // Texture (WYT)
		MOV EDX, DWORD PTR SS : [EBP + 0x8]
		PUSH EDX // Id
		CALL HKD_LoadFile
		PUSH 0x4CFEB6
		RETN 4
	}
}

__declspec(naked) void HookNaked::NKD_FixIndex()
{
	__asm
	{
		CMP EAX, 0x1037
		JNZ lblContinue
		PUSH 0x519E05
		RETN 4

		lblContinue:

		//Costume
		LEA ECX, DWORD PTR SS : [EBP - 0x4]
			PUSH ECX

			//st Body
			MOV EDX, DWORD PTR SS : [EBP - 0x18]
			PUSH EDX

			CALL HKD_FixIndex
			PUSH 0x519E36
			RETN 4
	}
}

INT32 g_pAffectId[] = { -1, 1, 41, 16, 165, 119, 105, 19, 161, 44, 51, 43, 84, 11, 3, 45, 71, 5, 46, 76, 40, 77, 37, 54, 13, 53, 89,
75, 95, 102, 163, 85, 47, 96, 164, 125, 92, 81, 87, 162, 96, 26, 121, 129, 99, 114, 130, 147, 140, 165, 103, 103, 104, 169, 170,
31, 122, 123, 124, 171 };
// ultimo id: 59
char g_pAffectName[128][24];

void AffectIconLimit()
{
	WYD.SetValue(0x044B0ED + 2, (UINT32)g_pAffectName, 4); // OK
	WYD.SetValue(0x047719C + 2, (UINT32)g_pAffectName, 4); // OK
	WYD.SetValue(0x0478038 + 2, (UINT32)g_pAffectName, 4); // ok
	WYD.SetValue(0x05495B1 + 2, (UINT32)g_pAffectName, 4); // OK

	WYD.SetValue(0x044B4C3 + 3, (UINT32)g_pAffectId, 4); // OK
	WYD.SetValue(0x04776F5 + 3, (UINT32)g_pAffectId, 4); // OK
	WYD.SetValue(0x0477D0D + 3, (UINT32)g_pAffectId, 4); // OK
	WYD.SetValue(0x047B0EF + 3, (UINT32)g_pAffectId, 4); // ok
	WYD.SetValue(0x04968EE + 3, (UINT32)g_pAffectId, 4); // ok
	WYD.SetValue(0x049692B + 3, (UINT32)g_pAffectId, 4); // ok
}
//void BASE_EffectMagic(bool IsEnable = false)
//{
	/* Enable the Effect Buffs */
	//WYD.SetValue<DWORD>(0x0054A331 + 6, IsEnable ? FALSE : TRUE);
	//WYD.SetValue<DWORD>(0x0054A331 + 6, IsEnable ? FALSE : TRUE);
	//WYD.SetValue<DWORD>(0x00467651 + 6, IsEnable ? FALSE : TRUE);

	/* Disable D3D9 - Buffer */
	//WYD.SetValue<DWORD>(0x0277C1C0, IsEnable ? TRUE : FALSE);
	//WYD.SetValue<DWORD>(0x0277C1C4, IsEnable ? TRUE : FALSE);

	// Força os graficos
	//*(DWORD*)(0x427213 + 6) = 0;
//}
