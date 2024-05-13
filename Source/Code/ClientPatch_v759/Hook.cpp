/*
*   Copyright (C) {2015}  {Victor Klafke, Charles TheHouse}
*
*   This program is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program.  If not, see [http://www.gnu.org/licenses/].
*
*   Contact at: victor.klafke@ecomp.ufsm.br
*/

#include "Main.h"
#include "../CommonNewInfo.h"

//__declspec(naked) void NKD_FixMageMacro()
//{
//	__asm
//	{
//		MOV ECX, DWORD PTR SS : [EBP - 0x11C]
//		// Diferente do Macro Continuo, então pula
//		CMP DWORD PTR DS : [ECX + 0x8A3A0], 0x0
//		JNZ lbl_JMP
//		PUSH 0x04970F9
//		RETN
//
//		lbl_JMP :
//		PUSH 0x04972E5
//			RETN
//	}
//}

//__declspec(naked) void NKD_Amount()
//{/*0040CD91  |. 8B4D E0        MOV ECX,DWORD PTR SS:[EBP-20]            ; |
// 0040CD94  |. 8B91 94000000  MOV EDX,DWORD PTR DS:[ECX+94]            ; |
// 0040CD9A  |. 52             PUSH EDX                                 ; |Arg2
// NEste call fica a cor da descrição
// */
//	__asm
//	{
//		MOV ECX, DWORD PTR SS : [EBP + 0Ch]
//			MOVSX EAX, WORD PTR DS : [ECX]
//
//		CMP EAX, 4011	// ADICIONE mais aqui
//		CMP EAX, 420
//		CMP EAX, 419
//		CMP EAX, 413
//		CMP EAX, 412
//		JNZ lbl_continueNormal
//
//		
//	}
//
//	static STRUCT_ITEM *item;
//	static int* retn;
//	__asm
//	{
//		LEA EAX, DWORD PTR SS : [EBP - 018h]
//		MOV retn, EAX
//		CMP EAX, 4011
//		MOV ECX, DWORD PTR SS : [EBP + 0Ch]
//		MOV DWORD PTR DS : [item], ECX
//	}
//
//	*retn = *(BYTE*)&item->stEffect[0].cEffect;
//
//	__asm
//	{
//		MOV EDX, 0x40D7F8
//		JMP EDX
//		
//		lbl_continueNormal :
//		MOV ECX, DWORD PTR SS : [EBP + 0Ch]
//			PUSH ECX
//
//			MOV EAX, 0x539810
//			CALL EAX
//			
//			MOV EDX, 0x40D7F2
//			JMP EDX
//	}
//}

__declspec(naked) void NKD_AddVolatileMessageItem()
{
	__asm
	{
		CMP DWORD PTR SS : [EBP + 0xC], 0x15E2 // 0xFD1
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

__declspec(naked) void NKD_AddVolatileMessageBox()
{
	static char msg[128] = { 0 };

	__asm
	{
		CMP DWORD PTR SS : [EBP - 0x1AC], 0xD3
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
				MOV DWORD PTR SS : [EBP - 0x388], EAX
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
				MOV     DWORD PTR DS : [EDX + 0x1E8], EAX
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


//void HKD_ItemPrice_FormatDecimal_AutoTrade(char *gold, int value)
//{
//	if (value <= 1000)
//	{
//		sprintf(gold, "Item em modo demonstração");
//
//		return;
//	}
//
//	char st[32];
//	char result[32];
//	memset(result, 0, sizeof result);
//
//	itoa(value, st, 10);
//
//	int len = strlen(st);
//	int sum = ((len - 1) / 3);
//
//	for (int i = (len - 1), count = 0, index = (len - 1) + sum; i >= 0; i--, count++)
//	{
//		if (!(count % 3) && count != 0)
//		{
//			result[index] = ',';
//			index--;
//		}
//
//		result[index] = st[i];
//
//		count++;
//		index--;
//	}
//
//	sprintf(gold, "%s Gold", result);
//}
//
//void HKD_ItemPrice_FormatDecimal_02(char *pointer, int gold)
//{
//	char st[32];
//	char result[32];
//	memset(result, 0, sizeof result);
//
//	itoa(gold, st, 10);
//
//	int len = strlen(st);
//	int sum = ((len - 1) / 3);
//
//	for (int i = (len - 1), count = 0, index = (len - 1) + sum; i >= 0; i--, count++)
//	{
//		if (!(count % 3) && count != 0)
//		{
//			result[index] = ',';
//			index--;
//		}
//
//		result[index] = st[i];
//
//		count++;
//		index--;
//	}
//	sprintf(pointer, "Preço: %s", result);
//}
//
//void HKD_ItemPrice_FormatDecimal_03(char *pointer, int gold)
//{
//	char st[32];
//	char result[32];
//	memset(result, 0, sizeof result);
//
//	itoa(gold, st, 10);
//
//	int len = strlen(st);
//	int sum = ((len - 1) / 3);
//
//	for (int i = (len - 1), count = 0, index = (len - 1) + sum; i >= 0; i--, count++)
//	{
//		if (!(count % 3) && count != 0)
//		{
//			result[index] = ',';
//			index--;
//		}
//
//		result[index] = st[i];
//
//		count++;
//		index--;
//	}
//
//	sprintf(pointer, "Preço de venda: %s", result);
//}
//
//
//
//
//__declspec(naked) void NKD_ItemPrice_FormatDecimal_03()
//{
//	__asm
//	{
//		MOV EDX, DWORD PTR SS : [EBP - 011D0h]
//			PUSH EDX
//
//			LEA EAX, DWORD PTR SS : [EBP - 01254h]
//			PUSH EAX
//
//			CALL HKD_ItemPrice_FormatDecimal_03
//			ADD ESP, 08h
//
//			MOV EAX, 0x041CE5B
//			JMP EAX
//	}
//
//}
//
//__declspec(naked) void NKD_ItemPrice_FormatDecimal_02()
//{
//	static int retn = 0;
//	__asm
//	{
//		MOV EDX, DWORD PTR SS : [EBP - 01130h]
//			ADD EDX, EAX
//			PUSH EDX
//
//			LEA EAX, DWORD PTR SS : [EBP - 011B0h]
//			PUSH EAX
//
//			CALL HKD_ItemPrice_FormatDecimal_02
//			ADD ESP, 08h
//
//			MOV EAX, 0x041CC9A
//			JMP EAX
//	}
//}
//
//__declspec(naked) void NKD_ItemPrice_FormatDecimal()
//{
//	__asm
//	{
//		MOV EAX, DWORD PTR SS : [EBP - 08Ch]
//			MOV ECX, DWORD PTR DS : [EAX + 058Ch]
//			PUSH ECX
//
//			MOV EAX, DWORD PTR SS : [EBP + 08h]
//			PUSH EAX
//
//			CALL HKD_ItemPrice_FormatDecimal_AutoTrade
//			ADD ESP, 08h
//
//			MOV EAX, 0420FCFh
//			JMP EAX
//	}
//}


//__declspec(naked) void NKD_SendChat()
//{
//	__asm
//	{
//		MOV EAX, DWORD PTR SS : [EBP - 0x98]
//		MOV EDX, DWORD PTR DS : [EAX]
//		MOV ECX, DWORD PTR SS : [EBP - 0x98]
//		CALL DWORD PTR DS : [EDX + 0x88]
//
//		PUSH EAX
//		CALL SendChat
//		ADD ESP, 0x08
//
//		TEST EAX, EAX
//		JNZ chk_other_cmd
//
//		MOV EAX, 0x01
//		MOV ECX, 0x473794
//		JMP ECX
//
//		chk_other_cmd :
//
//		MOV ECX, 0x467740
//			JMP ECX
//	}
//}
//
//__declspec(naked) void NKD_ReadMessage()
//{
//	__asm
//	{
//		MOV EAX, DWORD PTR SS : [EBP - 0x8]
//		PUSH EAX
//		MOV ECX, DWORD PTR SS : [EBP - 0x18]
//		PUSH ECX
//		CALL ReadMessage
//		MOV DWORD PTR SS : [EBP - 0x18], EAX
//		PUSH 0x4253CC
//		RETN
//	}
//}
//__declspec(naked) void NKD_GreenTime_NewArea()
//{
//	__asm
//	{
//
//		MOV EDX, DWORD PTR SS : [EBP - 07B8h]
//			MOV EAX, DWORD PTR DS : [EDX + 040h]
//
//			PUSH DWORD PTR DS : [EAX + 020A24h]
//
//			MOV EDX, DWORD PTR SS : [EBP - 07B8h]
//			MOV EAX, DWORD PTR DS : [EDX + 040h]
//
//			PUSH DWORD PTR DS : [EAX + 020A20h]
//
//			CALL HKD_GreenTime_NewArea
//			ADD ESP, 08h
//
//			TEST EAX, EAX
//			JE lbl_retn
//
//			MOV EAX, 0047DD1Ah
//
//			JMP EAX
//
//		lbl_retn :
//		MOV EAX, 0047DAF2h
//
//			JMP EAX
//	}
//}
//
//INT32 HKD_GreenTime_NewArea(INT32 posX, INT32 posY)
//{
//	/*if (posX == 2 && posY == 4)
//	return 1;
//
//	if (posX == 1 && posY == 31)
//	return 1;
//
//	if (posX == 20 && posY == 13)
//	return 1;
//
//	if (posX == 13 && posY == 16)
//	return 1;*/
//
//	return 1;
//}

__declspec(naked) void NKD_AddAmountItem()
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

	lblIsSplittable:
		MOV BYTE PTR SS : [EBP - 0x5C], 1
		PUSH 0x420626
		RETN
	}
	
}


void LoadHooks()
{
	JMP_NEAR(0x004205D0, NKD_AddAmountItem, 4);

	//// Efeito de Buffs 6.13
	//*(DWORD*)(0x0054A331 + 6) = 0;
	//*(DWORD*)(0x0054A351 + 6) = 0;
	//*(DWORD*)(0x00467651 + 6) = 0;

	// Força os graficos
	//*(DWORD*)(0x427213 + 6) = 0;

	// Altera o salto das verificações de checksum para JMP afim de não verificar o checksum.
	*(BYTE*)0x53AC6A = 0xEB;
	*(BYTE*)0x53AD52 = 0xEB;
	*(BYTE*)0x53AE7E = 0xEB;

	//JE_NEAR(0x04974C7, NKD_FixMageMacro);
	//JE_NEAR(0x04974D7, NKD_FixMageMacro);

	//// ReadMessage
	//JGE_NEAR(0x4252D6, NKD_ReadMessage);

	//// SendChat
	//JMP_NEAR(0x4676C5, NKD_SendChat);

	// ITEM BOX
	JMP_NEAR(0x422007, NKD_AddVolatileMessageItem, 2); //421F1A
	JMP_NEAR(0x41FB30, NKD_AddVolatileMessageBox, 5);
	
	
	/*JMP_NEAR(0x041CC7D, NKD_ItemPrice_FormatDecimal_02, 1);
	JMP_NEAR(0x041CE40, NKD_ItemPrice_FormatDecimal_03, 1);
	JMP_NEAR(0x0420F4B, NKD_ItemPrice_FormatDecimal);*/
	
	/*JMP_NEAR(0x0047DACA, NKD_GreenTime_NewArea, 1);*/
	//hooks.setHook(eHookType::JMP, 0x0047DACA, hooks.getAddress(&NKD_GreenTime_NewArea), 1);
	
	*(int*)(0x4E21DC) = 0xFFFFA500;//Coloque a cor aqui
	
	// Teste para SkillDelay
	for (int i = 0; i < 104; i++)
		*(int*)(0x11DA838 + (i * 96) + 48) = *(int*)(0x11DA838 + (i * 96) + 48) / 4;

	strcpy((char*)0x0622CDC, "Liberty Destiny");
}
