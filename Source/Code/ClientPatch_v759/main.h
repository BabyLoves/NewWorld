#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>

#include <iostream>
#include <io.h>
#include <fcntl.h>
#include "hook.h"
#include "hooknaked.h"
#include "Anti_RE.h"
#include "GlobalPoint.h"
#include "sendfunc.h"
#include "CClientInfo.h"
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

  
#include <locale.h>

inline void CreateConsole(char* Titulo)
{
    //Fixed bug printf vs 15 - 17
    //By seitbnao
    char Temp[256];
    AllocConsole();
    sprintf(Temp, "%s", Titulo);
#ifdef _DEBUG
    sprintf(Temp, "[DEBUG] - %s", Titulo);
#endif // _DEBUG

#ifdef __RELEASE
    sprintf(Temp, "[RELEASE] - %s", Titulo);
#endif // __RELEASE

    SetConsoleTitleA(Temp);
    typedef struct
    {
        char* _ptr;
        int _cnt;
        char* _base;
        int _flag;
        int _file;
        int _charbuf;
        int _bufsiz;
        char* _tmpfname;
    } FILE_COMPLETE;
    *(FILE_COMPLETE*)stdout = *(FILE_COMPLETE*)_fdopen(_open_osfhandle((long)GetStdHandle(STD_OUTPUT_HANDLE), _O_TEXT), "w");
    *(FILE_COMPLETE*)stderr = *(FILE_COMPLETE*)_fdopen(_open_osfhandle((long)GetStdHandle(STD_ERROR_HANDLE), _O_TEXT), "w");
    *(FILE_COMPLETE*)stdin = *(FILE_COMPLETE*)_fdopen(_open_osfhandle((long)GetStdHandle(STD_INPUT_HANDLE), _O_TEXT), "r");
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
    setvbuf(stdin, NULL, _IONBF, 0);
    setlocale(LC_ALL, "Portuguese");
}

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




extern WYDClient Client;
static TNColor SpeakColor;
extern int SpeakChatColor;
extern 		STRUCT_CAPSULE file;
//extern STRUCT_QUESTDIARIA QuestDay;
extern STRUCT_CLIENTPAC g_pSendClientPac;
extern int CameraLivre;


