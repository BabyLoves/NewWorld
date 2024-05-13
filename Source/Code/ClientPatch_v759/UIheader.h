#include <Windows.h>

#include <iostream>
#include <io.h>
#include <fcntl.h>
#include "hook.h"
#include "GlobalPoint.h"
#include <tchar.h>
#include <stdio.h>
#include "..\Basedef.h"
#include <mshtmhst.h>
#include <d3d9.h>
#include <tlhelp32.h>
#include "singleton.h"
#include "../ItemEffect.h"
#include <Rpc.h>
#pragma comment(lib, "Rpcrt4.lib")
using namespace std;
//viu ? sim mt bom
#define callCdecl(dwAddress, Retn, ...) (*(Retn (__cdecl*)(__VA_ARGS__)) dwAddress)
#define callThiscall(dwAddress, Retn, ...) (*(Retn (__thiscall*)(__VA_ARGS__)) dwAddress)
#define callstdcall(dwAddress, Retn, ...) (*(Retn (__stdcall*)(__VA_ARGS__)) dwAddress)
#define callThiscallMethod(dwClass, dwIndex, Retn, ...) (*(Retn (__thiscall*)(__VA_ARGS__)) (*(PDWORD)((*(PDWORD)dwClass) + (dwIndex * 4))))
#define callThiscallMethod_2(dwClass, dwIndex, Retn, ...) (*(Retn (__thiscall*)(__VA_ARGS__)) (*(PDWORD)((*(PDWORD)dwClass) + (dwIndex * 1))))
#define callstdcallMethod(dwClass, dwIndex, Retn, ...) (*(Retn (__stdcall*)(__VA_ARGS__)) (*(PDWORD)((*(PDWORD)dwClass) + dwIndex)))


#include "UIControl.h"
#include "UITextControl.h"
#include "GameInterface.h"
#include "UIProgressControl.h"
#include "UIListBox.h"
#include "UITextBox.h"
#include "UIClick.h"
#include "UIItem.h"
#include "UISlot.h"
//todo componente novo add abaixo da UIControl.H


/* This client sender an protocol to server */
static void(*SendPacket)(char*, int) = (void(__cdecl*)(char*, int)) 0x054DA23;


__forceinline STRUCT_MOB GetChar()
{
	__asm
	{
		MOV EAX, DWORD PTR DS : [0x277C024]
		ADD EAX, 0x750
	}
}
__forceinline int GetClientID()
{
	__asm
	{
		MOV ECX, DWORD PTR DS : [0x277C024]
		ADD ECX, 0xDFC
		XOR EAX, EAX
		MOV AX, WORD PTR DS : [ECX]
	}
}
__forceinline short GetInvSlot(int slot)
{
	int pointer = (0x7C8 + (slot * 8));
	__asm
	{
		MOV ECX, DWORD PTR DS : [0x277C024]
		ADD ECX, pointer
		MOV EAX, DWORD PTR DS : [ECX]
	}
}



enum LogType
{
	System,
	Quests,
	Debugs,
	Events,
	Combines,
	Itens,
	Command,
	Attack,
	Banned,
};

struct STRUCT_USER
{
	int CounterHist;

};



struct WYDClient
{
	bool m_DisabledExpMsg;
};


enum Banned
{
	Tempo3horas,
	Tempo3dias,
	Tempo7dias,
	Tempo15dias,
	Tempo30dias,
	Permanente,
	Analise,
	Mac,
};
enum { _Max_Recycle_Bin_ = 10 };




extern WYDClient Client;
static TNColor SpeakColor;
extern int SpeakChatColor;
extern 		STRUCT_CAPSULE file;
//extern STRUCT_QUESTDIARIA QuestDay;
//extern STRUCT_CLIENTPAC g_pSendClientPac;
extern int CameraLivre;


