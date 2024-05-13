#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <Windows.h>


#define MAX_MISSION 25

// Precisa atualizar para versão 7.62
static int32_t __cdecl CalcAddress(int32_t addr)
{
	return (int32_t)GetModuleHandleA(0) + addr;
}

#define addr_client_chat_1 CalcAddress(0x005B8113 - 0x400000)
#define addr_client_chat_2 CalcAddress(0x00406AC8 - 0x400000)
#define addr_client_chat_3 CalcAddress(0x00408569 - 0x400000)

// 00401508  |. 8B0D B00A6F00  MOV ECX,DWORD PTR DS:[6F0AB0]
#define base_addr1 0x6F0AB0

class Func
{
private:
	Func() = delete;
	virtual ~Func() = delete;
	Func(const Func&) = delete;
	Func& operator=(const Func&) = delete;
public:
	static void ShowExpMessage(int color, char* s);
	static char* strFmt(const char* str, ...);

	static int32_t HKD_GetItemAbility_Esferas(STRUCT_ITEM* item, INT32 effectId);
	static INT32 HKD_GreenTime_NewArea(INT32 posX, INT32 posY);
	static void HKD_ItemPrice_FormatDecimal_03(char* pointer, int gold);
	static void HKD_ItemPrice_FormatDecimal_02(char* pointer, int gold);
	static void HKD_ItemPrice_FormatDecimal_AutoTrade(char* gold, int value);
	static void NKD_SetCliver();
	static void NKD_ProcessClientMessage_03BBh();
	static void __stdcall AddIndex(int32_t index, int32_t* value);
	static void __stdcall CorrectBone(int32_t index, int32_t* bone);
	static void __stdcall LoadFile(int32_t index, char* textureName, char* meshName);
	static int32_t __stdcall UseShortcutFeed(uint16_t mountId, uint16_t feedId);
	static int32_t __stdcall AddItemDescription(STRUCT_ITEM* item, char* line1, char* line2, char* line3, char* line4, char* line5, char* line6, char* line7, char* line8, char* line9, char* line10, DWORD* line1Color, DWORD* line2Color, DWORD* line3Color, DWORD* line4Color, DWORD* line5Color, DWORD* line6Color, DWORD* line7Color, DWORD* line8Color, DWORD* line9Color, DWORD* line10Color);

	static bool SetVolatileMessageBoxText(int32_t itemID, char* text);

	static bool __stdcall AddAmountItem(int32_t itemID);

	static void CheckNewDll();
	static void RecordBufferData();

	static int checkCord(INT32 posX, INT32 posY, int cX, int cY, int cX2, int cY2);
	static char* stringFormat(const char* str, ...);
	static int GetClientID();

	static char* nString(int gold);
	static char* nString(long long gold);

	static void wydLog(char* mensagem);

	static bool __stdcall SetItemPriceString(STRUCT_ITEM* item, char* str);

	static char* __stdcall ReadMessage(char* pMsg, int32_t pSize);

	static void __stdcall NewMount(int32_t index, int32_t* value);
	static int32_t teste(STRUCT_ITEM* item, char* str);
	static int32_t FirstLineValidade(STRUCT_ITEM* item, char* pointer);

	static int SendChat(char* command);
	static void loadMission();

	static void Shown(int color, const char* str, ...);

	static void __stdcall HKD_Create_Scene_World(int arg1, int arg2, int arg3, int arg4);
	static void __stdcall HKD_CallBack_Handle_Click(int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8, int arg9, int arg10);
	static void __stdcall HKD_CallBack_Mouse(int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8, int arg9, int arg10);
	static void __stdcall HKD_CallBack_Inf_Mouse(int arg1, int arg2, int arg3, int arg4, int arg5);
	static void __stdcall HKD_CallBack_Event_Click(int handle, int gui, int clickstatus);
	static bool __stdcall HKD_CallBack_Event_Esc();
	static void __stdcall HKD_CallBack_Label(char* arg1);
	static void __stdcall HKD_Create_Scene_Login_After();
	static void __stdcall HKD_Create_Scene_Login(int arg1, int arg2, int arg3, int arg4);

	static bool __stdcall HKD_ItemTempo(int index);

	static void __stdcall HKD_OpenInventory(UINT32 Open);
	static int HKD_SendChat(char* command);
	static void __stdcall HKD_CheckJanelas(UINT32 addr1);

	static void __stdcall HKD_Att_Label_EXP();
	static INT32 HKD_KeyPress_NewButton(BYTE button);
	static void loadPainelGuild();
	static void loadMissao();

	static void FormataValidadeFada(char* msg, STRUCT_ITEM* item);
	static void FormataValidadeTraje(char* msg, STRUCT_ITEM* item);
	static void FormataValidadeEsferas(char* msg, STRUCT_ITEM* item);
	static bool NewItensDay(INT32 Item);
};

//static int32_t(*BASE_GetItemAmount)(STRUCT_ITEM* item) = (int32_t(*)(STRUCT_ITEM*)) 0x5386C1; //(GM CLIENT 0x539d71, GAMEPATCH 5386C1)
/* This client sender an protocol to server */
//static void(*SendPacket)(char*, int) = (void(__cdecl*)(char*, int)) 0x054DA23;

#define GetItemName(itemId) reinterpret_cast<char*>((itemId * 0x8C) + 0xD87150)
#define GetItemPrice(itemId) *reinterpret_cast<uint32_t*>((itemId * 0x8C) + 0xD871D0)
#define GetItemList(itemId) reinterpret_cast<STRUCT_ITEMLIST*>((itemId * 0x8C) + 0xD87150)

#define callCdecl(dwAddress, Retn, ...) (*(Retn (__cdecl*)(__VA_ARGS__)) dwAddress)
#define callThiscall(dwAddress, Retn, ...) (*(Retn (__thiscall*)(__VA_ARGS__)) dwAddress)
#define callThiscallMethod(dwClass, dwIndex, Retn, ...) (*(Retn (__thiscall*)(__VA_ARGS__)) (*(PDWORD)((*(PDWORD)dwClass) + (dwIndex * 4))))



__forceinline void SetInvSlot(int slot, int itemID, int ef1, int efv1, int ef2, int efv2, int ef3, int efv3)
{
	int pointer = (0x85C + (slot * 8));
	int usedPointer;
	__asm
	{
		MOV ECX, DWORD PTR DS : [0x277C024]
		ADD ECX, pointer
		MOV usedPointer, ECX
	}

	*(short*)usedPointer = itemID;
	*(short*)(usedPointer + 0x01) = ef1;
	*(short*)(usedPointer + 0x02) = efv1;
	*(short*)(usedPointer + 0x03) = ef2;
	*(short*)(usedPointer + 0x04) = efv2;
	*(short*)(usedPointer + 0x05) = ef3;
	*(short*)(usedPointer + 0x06) = efv3;
}


__forceinline int GetPlayerID()
{
	__asm
	{
		MOV ECX, DWORD PTR DS : [base_addr1]
		ADD ECX, 0x26EFC
		MOV EAX, DWORD PTR DS : [ECX]
	}
}


#endif // !FUNCTIONS_H
