#ifndef _SENDFUNC_ // Last updated 27/01/2013
#define _SENDFUNC_

#include <time.h>
#include <Windows.h>

#define GetItemList(itemId) reinterpret_cast<STRUCT_ITEMLIST*>((itemId * 0x8C) + 0xFB9608)
#define GetItemName(itemId) reinterpret_cast<char*>((itemId * 0x8C) +  0xFB9608)
#define GetItemPrice(itemId) *reinterpret_cast<uint32_t*>((itemId * 0x8C) + 0xFB9688)

enum class SkinId
{
    Arvak_Vermelho = 11,
    Arvak_Azul = 12,
    Arvak_Flamejante = 13,
    Arvak_Roxo = 14,
    Arvak_Metalico = 15,
    Deer = 16,
    Deer_Azul = 17,
    Asvid_Vermelho = 18,
    Asvid_Azul = 19,
    Asvid_Metalico = 20,
    Bode_Branco = 21,
    Big_Horns = 22,
    Small_Horns = 23,
    White_Hair = 24,
    Raposa_Amarela = 25,
    Raposa_Roxo = 26,
    Quimera_Flamejante = 27,
    Quimera_de_Madeira = 28,
    Quimera_Roxa = 29,
    Quimera_Verde = 30,
    Goat_Azul = 31,
    Goat_Vermelho = 32,
    Tigre_Negro = 33,
    Tigre_de_Gelo = 34,
    Tigre_Metalico = 35,
    Bola_de_Futebol = 36,
    Surkur = 37,
    Coelho_Macabro = 38,
    Pacman = 39,
    Dragão_Negro = 40,
    Dragão_Flamejante = 41,
    Dragão_de_Madeira = 42,
    Dragão_Metalico = 43,
    DV_Vermelho = 44,
    DV_Azul = 45,
    DV_Flamejante = 46,
    DV_Metalico = 47,
    Fire_Dragon = 48,
    Diamond_Dragon = 49,
    Metal_Dragon = 50,
    Fire_Elemental_Dragon = 51,
    Ice_Elemental_Dragon = 52,
    Metal_Elemental_Dragon = 53,
    Grifo_Negro = 54,
    Grifo_Verde = 55,
    Gargula_Vermelho = 56,
    Gargula_Bege = 57,
    Gargula_Flamejante = 58,
    Gargula_Negro = 59,
    Hipogrifo_Clestial = 60,
};

enum class SkinInitialId : uint32_t
{
    dr01 = 20,
    sp01 = 28,
    hs01 = 31,	
    tg01 = 38,
	dr02 = 39,
    bd02 = 40,
    kk01 = 49,	
	ct01 = 51,
	mo02 = 59,	
};

#pragma pack(push, 1)
struct InternalMob
{
	char Unknown_1[294];
	short MountBackMeshId;
	short MountBackSubMeshId;
	short MountFrontMeshId;
	short MountFrontSubMeshId;
	short MountSaddleMeshId;
	short MountSaddleSubMeshId;
	char Unknown_306[20];
	char MountBackSanc;
	char MountFrontSanc;
	char MountSaddleSanc;
	char Unknown_329[13];
	char MountBackSanc2;
	char MountFrontSanc2;
	char MountSaddleSanc2;
	char Unknown_2[2287];
	int MountInitialId;
	float fMountSize;
};
#pragma pack(pop)

void ProcessViewMount_Skins(SkinId skinId, InternalMob* mob);
bool SGrid_OnMouseMove_SkinName(char* pItemName, const STRUCT_ITEM* pItem);
void AffectIconLimit();
//void BASE_EffectMagic(bool IsEnable);
void AffectIconLimit();
INT32 HKD_GreenTime_NewArea(INT32 posX, INT32 posY);
void HKD_ItemPrice_FormatDecimal_AutoTrade(char* gold, int value);
void HKD_ItemPrice_FormatDecimal_02(char* pointer, int gold);
void HKD_ItemPrice_FormatDecimal_03(char* pointer, int gold);
void HandlerController(char* pBuffer, int a_iSize, int a_iType);
char* ClientReceiver(char* pBuffer, int a_iSize);
//char* ClientSended(char* pBuffer, int a_iSize);
void ClientSended(MSG_STANDARD* pBuffer, int a_iSize); 
char* ReadMessage(char* pMsg, int pSize);
int SendPack(const int conn, char* const pMsg, const int len);
void SendMsgExp(TNColor Color, char* msg, ...);
void CreateMessagePanel(char* msg, int color);
bool NewItensDay(INT32 Item);
bool SetItemPriceString(STRUCT_ITEM* item, char* str);
void FormataValidadeFada(char* msg, STRUCT_ITEM* item);
void FormataValidadeTraje(char* msg, STRUCT_ITEM* item);
void FormataValidadeEsferas(char* msg, STRUCT_ITEM* item);
INT32 FirstLineValidadeBag(int index, char* pointer, char string, char* v9, char* v13);
INT32 HKD_GetItemAbility_Esferas(STRUCT_ITEM* item, INT32 effectId);
//INT32 HKD_Macro_NewPotions(STRUCT_ITEM* item, INT32 type);
int AddItemDescription(STRUCT_ITEM* item, char* line1, char* line2, char* line3, char* line4, char* line5, char* line6, char* line7, char* line8, char* line9, char* line10, int* line1Color, int* line2Color, int* line3Color, int* line4Color, int* line5Color, int* line6Color, int* line7Color, int* line8Color, int* line9Color, int* line10Color);
int HKD_ChangeTabColor(char* msg);
int HKD_SendChat(char* command);
void HKD_FixIndex(DWORD* sTraje, int32_t* Costume);
void HKD_CorrectBone(int32_t index, int32_t* bone);
void HKD_LoadFile(int32_t index, char* textureName, char* meshName);

INT32 HKD_KeyPress_NewButton(BYTE button);
void NewMount(int32_t index, int32_t* value);
bool SetVolatileMessageBoxText(int itemID, char* text);
int AddVolatileMessageItem(int itemID);

void SendTextServer(const char* Text);
void OpenStore(int Warp);
void OpenDroplist(const char* mobname, int region);
void SendFiltro(int Index);
void Sendteleport(int X, int Y);
void SendReqDonateShop(int Shop, int Page, int ItemPos, int Qnt);
void RequestDropList(int Page);
void SendJephi(int Item, int Qnt);
void SendItemLevel(int Item, int Qnt);
void ExecItemLevel();
void ReqAlias(int Type);
void AttTraje(int Type);
void SendPix(int qnt, const char* chave);
#pragma endregion

#endif
