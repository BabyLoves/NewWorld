
#include <Windows.h>
#include <stdio.h>
#include <fcntl.h>
#include <time.h>
#include <math.h>
#include <io.h>
#include <errno.h>
#include <fstream>

#include "..\Basedef.h"
#include "..\CPSock.h"
#include "..\ItemEffect.h"
#include "Language.h"

#include "CItem.h"
#include "Server.h"
#include "GetFunc.h"
#include "SendFunc.h"
#include "ProcessClientMessage.h"
#include "ProcessDBMessage.h"
#include "CReadFiles.h"
#include "CWarTower.h"
#include "CColiseu.h"
#include "CCubo.h"
#include "IPControl.h"
#include <vector> 
#include "wMySQL.h"
#include "Functions.h"

#pragma region Defines


int FREEEXP = 35;
int PARTY_DIF = 400;

int FreyjaGoldAposta = 0;

int ServerDown = -1000;

int g_EmptyMob = MAX_USER;

int ServerIndex = -1;
int Sapphire = 8;
int ServerGroup = -1;
int GuildCounter = 1;

int ApostaPista = 0;
STRUCT_USER   wUser[MAX_USER];

AccountBanned BannedUser[MAX_USER];

//recaptcha
int random_words;

char Keywords[30][7] = {
	"AVIÃO", "TREM", "AVIÃO", "CARRO", "MOTO",
	"MOTO", "AVIÃO", "CARRO", "BIKE", "BIKE",
	"AVIÃO", "BIKE", "NAVIO", "BIKE", "NAVIO",
	"MOTO", "AVIÃO", "NAVIO", "CARRO", "MOTO",
	"NAVIO", "NAVIO", "TREM", "BIKE", "BIKE",
	"CARRO", "BIKE", "NAVIO", "AVIÃO", "TREM"
};

char Keywords1[30][7] = {
	"MOTO", "NAVIO", "BIKE", "TREM", "CARRO",
	"TREM", "MOTO", "MOTO", "AVIÃO", "AVIÃO",
	"CARRO", "BIKE", "AVIÃO", "AVIÃO", "CARRO",
	"AVIÃO", "NAVIO", "TREM", "CARRO", "NAVIO",
	"AVIÃO", "BIKE", "NAVIO", "CARRO", "TREM",
	"BIKE", "TREM", "NAVIO", "BIKE", "MOTO"
};

char Keywords2[30][7] = {
	"BIKE", "TREM", "BIKE", "BIKE", "TREM",
	"CARRO", "MOTO", "CARRO", "NAVIO", "MOTO",
	"NAVIO", "BIKE", "BIKE", "AVIÃO", "TREM",
	"MOTO", "CARRO", "AVIÃO", "TREM", "BIKE",
	"CARRO", "TREM", "BIKE", "CARRO", "AVIÃO",
	"MOTO", "MOTO", "AVIÃO", "AVIÃO", "NAVIO",
};

// Donate Store

int cStoreItens[3][3][15][3] = {};

extern int ExpBaseN[12] = {};
extern int ExpBaseM[12] = {};
extern int ExpCele[24] = {};
int ArchDiv;
int CeleDiv;

//////////////////////////////
///// STATUS DOS BOSS//
bool g_BSombraNegra = FALSE;
bool g_BVerid = FALSE;
bool g_SombraP = FALSE;
bool g_LanNBoss = FALSE;
bool g_RainhaG = FALSE;
int g_LanNBossCount = 0;

bool g_QBoss1 = FALSE;
bool g_QBoss2 = FALSE;
bool g_QBoss3 = FALSE;
bool g_QBoss4 = FALSE;
bool g_QBoss5 = FALSE;

bool PistaPlaying;

bool g_BFDarkShadow = FALSE;

STRUCT_QUEST QuestDiaria[36];

////////
bool TarantulaKilled = FALSE;
bool MsgArea = FALSE;
bool MsgArea2 = FALSE;
int BigCubo = 1; 

char ACCOUNT_DIRECTORY[MESSAGECHAT_LENGTH];

///MARKET

int pOriRest = 0;
int pLacRest = 0;
int pOriPounder = 0;
int pLacPounder = 0;
int pSabio = 0;
int pDiamante = 0;
int pEsmeralda = 0;
int pCoral = 0;
int pGarnet = 0;
int pBarraDn = 0;
int pBarraMg = 0;
int pBarraAc = 0;
int pBarraCr = 0;
int pClasseD = 0;
int pClasseE = 0;
int pLuz = 0;
int pUnk = 0;
int pUnk2 = 0;
int pUnk3 = 0;
int pUnk4 = 0;

char RankName[50][16];
int RankLevel[50];
char RankClasse[50][4];
char RankClass[50][4];

//DROPLIST

int dListItem[170][64];
char dListMobName[170][16];

///////////////////////////////

int ValidGuild = MAX_GUILDZONE; 
int WaterScrollPosition[3][10][2] =
{
	{//N
		{ 1121, 3554 },//LV1
		{ 1085, 3554 },//2
		{ 1049, 3554 },//3
		{ 1049, 3518 },//4
		{ 1049, 3482 },//5
		{ 1085, 3482 },//6
		{ 1121, 3482 },//7
		{ 1121, 3518 },//8
		{ 1085, 3518 },
		{ 1085, 3518 }
	},
	{//M
		{ 1250, 3682 },//LV1
		{ 1214, 3682 },//2
		{ 1178, 3682 },//3
		{ 1178, 3646 },//4
		{ 1178, 3610 },//5
		{ 1214, 3610 },//6
		{ 1250, 3610 },//7
		{ 1250, 3646 },//8
		{ 1214, 3646 },
		{ 1214, 3646 }
	},
	{//A
		{ 1379, 3554 },//LV1
		{ 1340, 3554 },//2
		{ 1305, 3554 },//3
		{ 1305, 3518 },//4
		{ 1305, 3482 },//5
		{ 1341, 3482 },//6
		{ 1377, 3482 },//7
		{ 1377, 3518 },//8
		{ 1343, 3518 },
		{ 1343, 3518 }
	}
};
int PesaNPosStandard[13][2] =
{
	{ 1304, 335 },
	{ 1304, 335 },
	{ 1304, 335 },
	{ 1304, 335 },
	{ 1304, 335 },
	{ 1304, 335 },
	{ 1304, 335 },
	{ 1304, 335 },
	{ 1304, 335 },
	{ 1304, 335 },
	{ 1304, 335 },
	{ 1304, 335 },
	{ 1304, 335 }
};

int PesaMPosStandard[13][2] =
{
	{ 1083, 308 },
	{ 1083, 308 },
	{ 1083, 308 },
	{ 1083, 308 },
	{ 1083, 308 },
	{ 1083, 308 },
	{ 1083, 308 },
	{ 1083, 308 },
	{ 1083, 308 },
	{ 1083, 308 },
	{ 1083, 308 },
	{ 1083, 308 },
	{ 1083, 308 }
};

int PesaAPosStandard[13][2] =
{
	{ 1204, 152 },
	{ 1217, 155 },
	{ 1195, 175 },
	{ 1182, 174 },
	{ 1171, 190 },
	{ 1189, 196 },
	{ 1209, 182 },
	{ 1226, 190 },
	{ 1230, 174 },
	{ 1247, 184 },
	{ 1224, 190 },
	{ 1211, 165 },
	{ 1209, 174 }
};

int CartaPos[4][2] =
{
	{ 786, 3688 },
	{ 843, 3688 },
	{ 843, 3632 },
	{ 786, 3640 }
};

int CTarantulaPos[4][2] =
{	// Tarantula Liberadora
	{ 1754, 3674 },
	{ 1728, 3646 },
	{ 1703, 3635 },
	{ 1752, 3618 }
};

int TarantulaPos[2][2][2] =
{
	{//Tarantula Normal = 1
		{ 1752, 3645 }, // = 2 , 3
		{ 1700, 3646 }
	},
	{//Tarantula Normal
		{ 1683, 3632 },
		{ 1724, 3673 }
	}
};

int PistaPos[7][3][2] =
{
	{//Sala 1 Lich
		{ 3350, 1622 }, //Grupo 1
		{ 3431, 1634 }, //Grupo 2
		{ 0, 0 }  //Grupo 3
	},
	{//Sala 2 Torre
		{ 3362, 1574 }, //Grupo 1
		{ 3385, 1555 }, //Grupo 2
		{ 3414, 1575 }  //Grupo 3
	},
	{//Sala 3 Amon
		{ 3410, 1453 }, //Grupo 1
		{ 3419, 1426 }, //Grupo 2
		{ 3358, 1436 }  //Grupo 3
	},
	{//Sala 4 Sulrang
		{ 3376, 1096 }, //Grupo 1
		{ 3400, 1089 }, //Grupo 2
		{ 3392, 1073 }  //Grupo 3
	},
	{//Sala 5 Labirinto
		{ 3342, 1394 }, //Grupo 1
		{ 3444, 1394 }, //Grupo 2
		{ 3442, 1293 }  //Grupo 3
	},
	{//Sala 6 Balrog
		{ 3421, 1217 }, //Grupo 1
		{ 3426, 1211 }, //Grupo 2
		{ 3424, 1226 }  //Grupo 3
	},
	{//Sala 7 Coelho
		{ 3404, 1517 }, //Grupo 1
		{ 3392, 1479 }, //Grupo 2
		{ 3383, 1501 }  //Grupo 3
	}
};

int PistaBalrogPos[5][2] =
{
	{3421, 1217}, //Sala1
	{3428, 1180}, //Sala2
	{3357, 1186}, //Sala3
	{3393, 1255}, //Sala4
	{3385, 1204} //Sala Boss
};

int PistaBalrogPortalPos[5][5][2] =
{
	//Sala1
	{
		{3428, 1196},
		{0, 0},
		{0, 0},
		{0, 0}
	},

	//Sala2
	{
		{3380, 1176},
		{3380, 1164},
		{0, 0},
		{0, 0}
	},

	//Sala3
	{
		{3360, 1224},
		{3352, 1224},
		{3340, 1224},
		{0, 0}
	},

	//Sala4
	{
		{3400, 1236},
		{3392, 1236},
		{3384, 1236},
		{3376, 1236}
	},

	//Sala5
	{
		{0, 0},
		{0, 0},
		{0, 0},
		{0, 0}
	}
};

int CartaTime = 0;
int CartaSala = 0;

short weapon[32][9];

CPSock BillServerSocket;
char   BillServerAddress[32] = { 0, };
int	   BillServerPort = 0;

HWND  hWndMain;
HMENU hMainMenu;
HFONT hFont = NULL;


std::unique_ptr<std::ofstream> fLogFile;
std::string fLogFile_Dir;

std::unique_ptr<LogControl> g_pChatLog; //

std::unique_ptr<LogControl> g_phackLog;

std::unique_ptr<LogControl> g_pMobdropLog;

std::unique_ptr<LogControl> g_pCompositorLog;

std::unique_ptr<LogControl> g_pItemLog;

std::unique_ptr<LogControl> g_pSystemLog;

std::unique_ptr<LogControl> g_pItradeLog;

FILE *fLogFile1 = NULL;

//FILE *fChatLogFile = NULL;
//FILE *fItemLogFile = NULL;
//FILE* fICompositorLogsFile = NULL;
//FILE* fIMobDropLogLogsFile = NULL;
//FILE* trade_itemLogsFile = NULL;

FILE *fReadDir = NULL;

CPSock DBServerSocket;

unsigned int pAdminIP[MAX_ADMIN] = { 1, };

CNPCGenerator mNPCGen;
CNPCSummon mSummon;

CUser pUser[MAX_USER];
CMob pMob[MAX_MOB];
STRUCT_BLOCKMAC pMac[MAX_MAC];
 
STRUCT_TREASURE g_pTreasure[8];

STRUCT_ITEM LevelItem[4][4][400];

char temp[4096];
char logQuery[256];

CItem pItem[MAX_ITEM];

unsigned int CurrentTime = 0;
unsigned int LastSendTime = 0;


QuizInfo SendQuiz[1000];
char QuizLineCounter;
MSG_Quiz QuizList[50];

MSG_BigQuiz CuboList[50];
char CuboQuizLine;

int BillCounter = 0;

int	g_Week = 0;
int	g_Hour = 0;

int LastLogDay = 0;
int LastChatLogDay = 0;
int LasthackLogDay = 0;
int LastItemLogDay = 0;
int LastSystemLogDay = 0;
int LastCompositorLogsDay = 0;
int trade_itemLogsFileDay = 0;
int fIMobDropLogFileDay = 0;

int GTorrePoints[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
int GTorreGuildID[10];

int GShopItens[30][2];
int GuildPoints[100][2];

int EvItemId[5][4];
int EvItemQt[5][4];

int EvItemId2[5][4];
int EvItemQt2[5][4];

int ConfigReady = 0;

///////////////////////////////////////
//Config for Event
//////////////////////////////////////
int evNotice = 1;
int evStartIndex = 0;
int evEndIndex = 0;
int evCurrentIndex = 0;
int evRate = 0;
int evItem = 0;
int evIndex = 0;
int evOn = 0;
int evDelete = 0;
////////////////////////////////////
// New Server Stats
////////////////////////////////////

int EventStatus;
int DOUBLEMODE;
int AUTODOUBLE;
int GlobalExp;
int GTorreHour;
int GTorreStatus;
int RvRHour;
int RvRStatus;
int RvRBonus;
int BatalhaRealStatus;
int BatalhaRealHour;
int PistaStatus;
int EvolutionStatus;
int PesaStatus;
int PergaStatus;

////////////////////////////////////

int NewbieEventServer = 0;
int CastleServer = 0;

int DUNGEONEVENT = 1;
int DEADPOINT = 1;
int StatSapphire = 30;
 

MSG_BattleReal p_BatalhaReal;


int BRItem = 518;
int BRHour = 17;

int BILLING = 3;
int CHARSELBILL = 0;
int POTIONCOUNT = 10;
int PARTYBONUS = 100;
int GUILDBOARD = 0;

int UserCount = 1;
int SaveCount = 1;
int ItemCount = 100;

int ForceWeather = -1;

int WeekMode = 4;
int ForceWeekMode = -1;
int GuildDay = 0;
int GuildHour = 20;

int NumGuildBattle = 26;
int PotionReady = 0;

int PotionDelay = 100;

int RvRState = 0;
int AltarSta = 0;
//int RvRHour = 0;
//int RvRBonus = 0;

int GTorreState = 0;
//int GTorreHour = 21;
int GTorreGuild = 0;

int NewbieHour = 20;

int ColoStateN = 0;
int ColoHourN = 4; //HORARIO COLISEU N

int ColoStateM = 0;
int ColoHourM = 2;  //horario coliseu M
int WTowerState = 0;
int ColoStateA = 0;
int ColoHourA = 3;  //horario coliseu A

//int BatalhaRealHour = 22; 
int NumServerInGroup = 0;

int LiveTower[3];

int pChallangerMoney[6];

unsigned short g_pGuildWar[65536];
unsigned short g_pGuildAlly[65536];
STRUCT_GUILDINFO GuildInfo[65536];

unsigned short pMobGrid[MAX_GRIDY][MAX_GRIDX];
unsigned short pItemGrid[MAX_GRIDY][MAX_GRIDX];
char pHeightGrid[MAX_GRIDY][MAX_GRIDX];

unsigned char LocalIP[4] = { 0, };

char FailAccount[16][16];

CPSock ListenSocket;

char DBServerAddress[32] = { 0, };
int DBServerPort = 0;

int isDropItem = 0;
int isHardCore = 0;
int maxNightmare = 3;
int maxPortaoInfernal = 3;
int CurrentWeather = 0;
int TESTSERVER = 0;
int LOCALSERVER = 0;

int TransperCharacter = 0;

unsigned int SecCounter = 0;
unsigned int MinCounter = 0;

int GuildImpostoID[MAX_GUILDZONE];

int BrTime = 0;
int BrState = 0;
int BrMod = 0;
int BrGrid = 0;
int CastleState = 0;
int ColoLevelN = 0;
int ColoLevelM = 0;
int ColoLevelA = 0;
int KefraLive = 1;
int EspelhoLive = 0;
int RandBoss = 0;
int Lich_1 = 0;
int Lich_2 = 0;
int Lich_3 = 0;
int Lich_4 = 0;
char KefraKiller[32] = "LOCALSERVER";

int g_dLevel = 0;
int g_dLevel1 = 0;
int g_dLevel2 = 0;

int Kingdom1Clear = 0;
int Kingdom2Clear = 0;

int GuildNameInitialized = 0;

///////////////////////////////////////
//Config for Duel: 1:1 5:5 10:10 All:All
//////////////////////////////////////
char nRanking1[32] = { "unnamed" };
char nRanking2[32] = { "unnamed" };
char nTitle1[32] = { "unnamed" };
char nTitle2[32] = { "unnamed" };

int RankingProgress = 0;
int Ranking1 = 0;
int Ranking2 = 0;
int lTitle1 = 0;
int lTitle2 = 0;
int RankingTime = 0;

int Ranking1X = 147;
int Ranking1Y = 4044;
int Ranking2X = 189;
int Ranking2Y = 4044;

int cRanking1X = 2564;
int cRanking1Y = 1688;
int cRanking2X = 2579;
int cRanking2Y = 1714;

int kRanking1X = 142;
int kRanking1Y = 4007;
int kRanking2X = 195;
int kRanking2Y = 4082;

int TaxChanged[MAX_GUILDZONE] = { 0, 0, 0, 0, 0 };

HDC hDC;

//////////////////////////////////////

int WaterClear1[3][10] = { 0, 0, 0, 0, 0, };
int PartyPesa[3] = { 0, 0, 0 };
int PartyPortao[3] = { 0, 0, 0 };

int RvRBluePoint = 0;
int RvRRedPoint = 0;

STRUCT_PISTA Pista[7] = { 0, 0, 0, 0, 0, };

STRUCT_PVP Desafio[1] = { 0 };

STRUCT_QUESTS g_quests;

STRUCT_MERC pMobMerc[MAX_MOB_MERC];

int PistaRune[7][10] =
{
	// Lich
	{
		5110, 5112, 5115, 5113, 5111, 0, 0, 0, 0, 0
	},

	// Torre
	{
		5114, 5113, 5117, 5111, 5115, 5112, 0, 0, 0, 0
	},

	// Amon
	{
		5118, 5121, 5122, 5116, 5130, 5119, 0, 0, 0, 0
	},

	// Sulrang
	{
		5122, 5126, 5121, 5116, 5119, 0, 0, 0, 0, 0
	},

	// Labirinto
	{
		5125, 5126, 5124, 5127, 0, 0, 0, 0, 0, 0
	},

	// Balrog
	{
		5120, 5131, 5118, 5119, 5123, 5132, 5121, 0, 0, 0
	},

	//Coelho
	{
		5130, 5131, 5119, 5133, 5120, 5123, 5132, 5129, 5128, 0
	}
};

std::vector<TMP_BLOCKIP> g_pBlockIP;
//////////////////////////////////////
extern STRUCT_GUILDZONE g_pGuildZone[MAX_GUILDZONE];

#pragma endregion

void LimiteBsWepom(int conn)
{
	if (conn <= 0 || conn >= MAX_USER)
		return;

	if (pUser[conn].Mode != USER_PLAY)
		return;

	if (pUser[conn].cSock.Sock == 0)
		return;

	int i = 0;
	int iss = 0;

	int MaxMG = 28;
	int MaxDM = 63;
	int MaxAc = 30;
	int MaxDMSet = 30;
	int MaxMGSet = 12;	

	for (int i = 0; i < 64; i++) {
		int Pos = BASE_GetItemAbility(&pMob[conn].MOB.Carry[i], EF_POS);

		if (Pos == 2 || Pos == 4 || Pos == 8 || Pos == 16 || Pos == 32) {			
			for (int z = 0; z < 3; z++) {
				if (pMob[conn].MOB.Carry[i].stEffect[z].cEffect == EF_MAGIC && pMob[conn].MOB.Carry[i].stEffect[z].cValue > MaxMGSet) {
					pMob[conn].MOB.Carry[i].stEffect[z].cValue = MaxMGSet;
					SendItem(conn, ITEM_PLACE_CARRY, i, &pMob[conn].MOB.Carry[i]);
				}
				if (pMob[conn].MOB.Carry[i].stEffect[z].cEffect == EF_MAGICADD) {
					int max = pMob[conn].MOB.Carry[i].stEffect[z].cValue;
					pMob[conn].MOB.Carry[i].stEffect[z].cEffect = 0;
					pMob[conn].MOB.Carry[i].stEffect[z].cValue = 0;

					for (int y = 0; y < 3; y++) {
						if (pMob[conn].MOB.Carry[i].stEffect[y].cEffect == EF_MAGIC) {
							pMob[conn].MOB.Carry[i].stEffect[y].cValue += max;
						}
					}
					SendItem(conn, ITEM_PLACE_CARRY, i, &pMob[conn].MOB.Carry[i]);
				}
				if (pMob[conn].MOB.Carry[i].stEffect[z].cEffect == EF_DAMAGE && pMob[conn].MOB.Carry[i].stEffect[z].cValue > MaxDMSet) {
					pMob[conn].MOB.Carry[i].stEffect[z].cValue = MaxDMSet;
					SendItem(conn, ITEM_PLACE_CARRY, i, &pMob[conn].MOB.Carry[i]);
				}
				if (pMob[conn].MOB.Carry[i].stEffect[z].cEffect == EF_DAMAGE2 && Pos != 32) {
					int max = pMob[conn].MOB.Carry[i].stEffect[z].cValue;
					pMob[conn].MOB.Carry[i].stEffect[z].cEffect = 0;
					pMob[conn].MOB.Carry[i].stEffect[z].cValue = 0;

					for (int y = 0; y < 3; y++) {
						if (pMob[conn].MOB.Carry[i].stEffect[y].cEffect == EF_DAMAGE) {
							pMob[conn].MOB.Carry[i].stEffect[y].cValue += max;
						}
					}
					SendItem(conn, ITEM_PLACE_CARRY, i, &pMob[conn].MOB.Carry[i]);
				}
			}
		}
		if (Pos == 64 || Pos == 192) {
			for (int z = 0; z < 3; z++) {
				if (pMob[conn].MOB.Carry[i].stEffect[z].cEffect == EF_MAGIC && pMob[conn].MOB.Carry[i].stEffect[z].cValue > MaxMG) {
					pMob[conn].MOB.Carry[i].stEffect[z].cValue = MaxMG;
					SendItem(conn, ITEM_PLACE_CARRY, i, &pMob[conn].MOB.Carry[i]);
				}
				if (pMob[conn].MOB.Carry[i].stEffect[z].cEffect == EF_MAGICADD) {
					int max = pMob[conn].MOB.Carry[i].stEffect[z].cValue;
					pMob[conn].MOB.Carry[i].stEffect[z].cEffect = 0;
					pMob[conn].MOB.Carry[i].stEffect[z].cValue = 0;

					for (int y = 0; y < 3; y++) {
						if (pMob[conn].MOB.Carry[i].stEffect[y].cEffect == EF_MAGIC) {
							pMob[conn].MOB.Carry[i].stEffect[y].cValue += max;
						}
					}
					SendItem(conn, ITEM_PLACE_CARRY, i, &pMob[conn].MOB.Carry[i]);
				}	
				if (pMob[conn].MOB.Carry[i].stEffect[z].cEffect == EF_DAMAGE && pMob[conn].MOB.Carry[i].stEffect[z].cValue > MaxDM) {
					pMob[conn].MOB.Carry[i].stEffect[z].cValue = MaxDM;
					SendItem(conn, ITEM_PLACE_CARRY, i, &pMob[conn].MOB.Carry[i]);
				}
				if (pMob[conn].MOB.Carry[i].stEffect[z].cEffect == EF_DAMAGE2) {
					int max = pMob[conn].MOB.Carry[i].stEffect[z].cValue;
					pMob[conn].MOB.Carry[i].stEffect[z].cEffect = 0;
					pMob[conn].MOB.Carry[i].stEffect[z].cValue = 0;

					for (int y = 0; y < 3; y++) {
						if (pMob[conn].MOB.Carry[i].stEffect[y].cEffect == EF_DAMAGE) {
							pMob[conn].MOB.Carry[i].stEffect[y].cValue += max;
						}
					}
					SendItem(conn, ITEM_PLACE_CARRY, i, &pMob[conn].MOB.Carry[i]);
				}
			}
		}
	}
	for (int i = 0; i < 16; i++) {
		int Pos = BASE_GetItemAbility(&pMob[conn].MOB.Equip[i], EF_POS);

		if (Pos == 2 || Pos == 4 || Pos == 8 || Pos == 16 || Pos == 32) {
			for (int z = 0; z < 3; z++) {
				if (pMob[conn].MOB.Equip[i].stEffect[z].cEffect == EF_MAGIC && pMob[conn].MOB.Equip[i].stEffect[z].cValue > MaxMGSet) {
					pMob[conn].MOB.Equip[i].stEffect[z].cValue = MaxMGSet;
					SendItem(conn, ITEM_PLACE_EQUIP, i, &pMob[conn].MOB.Equip[i]);
				}
				if (pMob[conn].MOB.Equip[i].stEffect[z].cEffect == EF_MAGICADD) {
					int max = pMob[conn].MOB.Equip[i].stEffect[z].cValue;
					pMob[conn].MOB.Equip[i].stEffect[z].cEffect = 0;
					pMob[conn].MOB.Equip[i].stEffect[z].cValue = 0;

					for (int y = 0; y < 3; y++) {
						if (pMob[conn].MOB.Equip[i].stEffect[y].cEffect == EF_MAGIC) {
							pMob[conn].MOB.Equip[i].stEffect[y].cValue += max;
						}
					}
					SendItem(conn, ITEM_PLACE_EQUIP, i, &pMob[conn].MOB.Equip[i]);
				}
				if (pMob[conn].MOB.Equip[i].stEffect[z].cEffect == EF_DAMAGE && pMob[conn].MOB.Equip[i].stEffect[z].cValue > MaxDMSet) {
					pMob[conn].MOB.Equip[i].stEffect[z].cValue = MaxDMSet;
					SendItem(conn, ITEM_PLACE_EQUIP, i, &pMob[conn].MOB.Equip[i]);
				}
				if (pMob[conn].MOB.Equip[i].stEffect[z].cEffect == EF_DAMAGE2 && Pos != 32) {
					int max = pMob[conn].MOB.Equip[i].stEffect[z].cValue;
					pMob[conn].MOB.Equip[i].stEffect[z].cEffect = 0;
					pMob[conn].MOB.Equip[i].stEffect[z].cValue = 0;

					for (int y = 0; y < 3; y++) {
						if (pMob[conn].MOB.Equip[i].stEffect[y].cEffect == EF_DAMAGE) {
							pMob[conn].MOB.Equip[i].stEffect[y].cValue += max;
						}
					}
					SendItem(conn, ITEM_PLACE_EQUIP, i, &pMob[conn].MOB.Equip[i]);
				}
			}
		}
		if (Pos == 64 || Pos == 192) {
			for (int z = 0; z < 3; z++) {
				if (pMob[conn].MOB.Equip[i].stEffect[z].cEffect == EF_MAGIC && pMob[conn].MOB.Equip[i].stEffect[z].cValue > MaxMG) {
					pMob[conn].MOB.Equip[i].stEffect[z].cValue = MaxMG;
					SendItem(conn, ITEM_PLACE_EQUIP, i, &pMob[conn].MOB.Equip[i]);
				}
				if (pMob[conn].MOB.Equip[i].stEffect[z].cEffect == EF_MAGICADD) {
					int max = pMob[conn].MOB.Equip[i].stEffect[z].cValue;
					pMob[conn].MOB.Equip[i].stEffect[z].cEffect = 0;
					pMob[conn].MOB.Equip[i].stEffect[z].cValue = 0;

					for (int y = 0; y < 3; y++) {
						if (pMob[conn].MOB.Equip[i].stEffect[y].cEffect == EF_MAGIC) {
							pMob[conn].MOB.Equip[i].stEffect[y].cValue += max;
						}
					}
					SendItem(conn, ITEM_PLACE_EQUIP, i, &pMob[conn].MOB.Equip[i]);
				}
				if (pMob[conn].MOB.Equip[i].stEffect[z].cEffect == EF_DAMAGE && pMob[conn].MOB.Equip[i].stEffect[z].cValue > MaxDM) {
					pMob[conn].MOB.Equip[i].stEffect[z].cValue = MaxDM;
					SendItem(conn, ITEM_PLACE_EQUIP, i, &pMob[conn].MOB.Equip[i]);
				}
				if (pMob[conn].MOB.Equip[i].stEffect[z].cEffect == EF_DAMAGE2) {
					int max = pMob[conn].MOB.Equip[i].stEffect[z].cValue;
					pMob[conn].MOB.Equip[i].stEffect[z].cEffect = 0;
					pMob[conn].MOB.Equip[i].stEffect[z].cValue = 0;

					for (int y = 0; y < 3; y++) {
						if (pMob[conn].MOB.Equip[i].stEffect[y].cEffect == EF_DAMAGE) {
							pMob[conn].MOB.Equip[i].stEffect[y].cValue += max;
						}
					}
					SendItem(conn, ITEM_PLACE_EQUIP, i, &pMob[conn].MOB.Equip[i]);
				}
			}
		}
	}
}
void ClearCrown(int conn)
{
	if (pUser[conn].Mode != USER_PLAY)
		return;

	int GLevel = pMob[conn].MOB.GuildLevel;
	int Guild = pMob[conn].MOB.Guild;

	int IsCrownGuild = FALSE;

	int i = 0;

	for (i = 0; i < MAX_SERVER; i++)
	{
		int CrownGuild = ChargedGuildList[i][4];

		if ((Guild != 0) && (CrownGuild != 0) && (CrownGuild == Guild && GLevel == 9))
		{
			IsCrownGuild = TRUE;

			break;
		}
	}

	if (IsCrownGuild == 1)
	{
		int HaveCrow = 0;
		int HaveDrag = 0;

		for (i = 0; i < MAX_EQUIP; i++)
		{
			if (pMob[conn].MOB.Equip[i].sIndex == 747)
				HaveCrow = 1;

			if (pMob[conn].MOB.Equip[i].sIndex != 3993 && pMob[conn].MOB.Equip[i].sIndex != 3994) // 747 = Crown on itemlist
				continue;

			HaveDrag = 1;

			if (pMob[conn].MOB.Equip[i].sIndex == 3993 && pMob[conn].MOB.Clan == 7)
			{
				sprintf_s(temp, "etc,crown guild:%d level:%d charge:%d name:%s", Guild, GLevel, ChargedGuildList[ServerIndex][4], pMob[conn].MOB.MobName);
				SystemLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, temp);

				pMob[conn].MOB.Equip[i].sIndex = 3994;

				SendItem(conn, ITEM_PLACE_EQUIP, i, &pMob[conn].MOB.Equip[i]);
			}
			else if (pMob[conn].MOB.Equip[i].sIndex == 3994 && pMob[conn].MOB.Clan == 8)
			{
				sprintf_s(temp, "etc,crown guild:%d level:%d charge:%d name:%s", Guild, GLevel, ChargedGuildList[ServerIndex][4], pMob[conn].MOB.MobName);
				SystemLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, temp);

				pMob[conn].MOB.Equip[i].sIndex = 3993;

				SendItem(conn, ITEM_PLACE_EQUIP, i, &pMob[conn].MOB.Equip[i]);
			}
		}

		for (i = 0; i < MAX_CARRY; i++)
		{
			if (pMob[conn].MOB.Carry[i].sIndex == 747)
				HaveCrow = 1;

			if (pMob[conn].MOB.Carry[i].sIndex != 3993 && pMob[conn].MOB.Carry[i].sIndex != 3994) // 747 = Crown on itemlist
				continue;

			HaveDrag = 1;

			if (pMob[conn].MOB.Carry[i].sIndex == 3993 && pMob[conn].MOB.Clan == 7)
			{
				sprintf_s(temp, "etc,crown guild:%d level:%d charge:%d name:%s", Guild, GLevel, ChargedGuildList[ServerIndex][4], pMob[conn].MOB.MobName);
				SystemLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, temp);

				pMob[conn].MOB.Carry[i].sIndex = 3994;

				SendItem(conn, ITEM_PLACE_CARRY, i, &pMob[conn].MOB.Carry[i]);
			}

			if (pMob[conn].MOB.Carry[i].sIndex == 3994 && pMob[conn].MOB.Clan == 8)
			{
				sprintf_s(temp, "etc,crown guild:%d level:%d charge:%d name:%s", Guild, GLevel, ChargedGuildList[ServerIndex][4], pMob[conn].MOB.MobName);
				SystemLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, temp);

				pMob[conn].MOB.Carry[i].sIndex = 3993;

				SendItem(conn, ITEM_PLACE_CARRY, i, &pMob[conn].MOB.Carry[i]);
			}
		}

		for (i = 0; i < MAX_CARGO; i++)
		{
			if (pUser[conn].Cargo[i].sIndex == 747)
				HaveCrow = 1;

			if (pUser[conn].Cargo[i].sIndex != 3993 && pUser[conn].Cargo[i].sIndex != 3994) // 747 = Crown on itemlist
				continue;

			HaveDrag = 1;

			if (pUser[conn].Cargo[i].sIndex == 3993 && pMob[conn].MOB.Clan == 7)
			{
				sprintf_s(temp, "etc,crown guild:%d level:%d charge:%d name:%s", Guild, GLevel, ChargedGuildList[ServerIndex][4], pMob[conn].MOB.MobName);
				SystemLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, temp);

				pUser[conn].Cargo[i].sIndex = 3994;

				SendItem(conn, ITEM_PLACE_CARGO, i, &pUser[conn].Cargo[i]);
			}
			else if (pUser[conn].Cargo[i].sIndex == 3994 && pMob[conn].MOB.Clan == 8)
			{
				sprintf_s(temp, "etc,crown guild:%d level:%d charge:%d name:%s", Guild, GLevel, ChargedGuildList[ServerIndex][4], pMob[conn].MOB.MobName);
				SystemLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, temp);

				pUser[conn].Cargo[i].sIndex = 3993;

				SendItem(conn, ITEM_PLACE_CARGO, i, &pUser[conn].Cargo[i]);
			}
		}

		if (HaveCrow == 0)
		{
			STRUCT_ITEM Item;
			memset(&Item, 0, sizeof(STRUCT_ITEM));

			Item.sIndex = 747;
			Item.stEffect[0].cEffect = 43;
			Item.stEffect[0].cValue = 9;

			PutItem(conn, &Item);
		}

		if (HaveDrag == 0)
		{
			STRUCT_ITEM Item;
			memset(&Item, 0, sizeof(STRUCT_ITEM));

			if (pMob[conn].MOB.Clan == 8)
				Item.sIndex = 3993;

			else if (pMob[conn].MOB.Clan == 7)
				Item.sIndex = 3994;


			PutItem(conn, &Item);
		}

		return;
	}

	for (i = 0; i < MAX_EQUIP; i++)
	{
		if (pMob[conn].MOB.Equip[i].sIndex != 747 && pMob[conn].MOB.Equip[i].sIndex != 3993 && pMob[conn].MOB.Equip[i].sIndex != 3994) // 747 = Crown on itemlist
			continue;

		sprintf_s(temp, "etc,crown guild:%d level:%d charge:%d name:%s", Guild, GLevel, ChargedGuildList[ServerIndex][4], pMob[conn].MOB.MobName);
		SystemLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, temp);

		memset(&pMob[conn].MOB.Equip[i], 0, sizeof(STRUCT_ITEM));

		SendItem(conn, ITEM_PLACE_EQUIP, i, &pMob[conn].MOB.Equip[i]);
	}

	for (i = 0; i < MAX_CARRY; i++)
	{
		if (pMob[conn].MOB.Carry[i].sIndex != 747 && pMob[conn].MOB.Carry[i].sIndex != 3993 && pMob[conn].MOB.Carry[i].sIndex != 3994) // 747 = Crown on itemlist
			continue;

		sprintf_s(temp, "etc,crown guild:%d level:%d charge:%d name:%s", Guild, GLevel, ChargedGuildList[ServerIndex][4], pMob[conn].MOB.MobName);
		SystemLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, temp);

		memset(&pMob[conn].MOB.Carry[i], 0, sizeof(STRUCT_ITEM));

		SendItem(conn, ITEM_PLACE_CARRY, i, &pMob[conn].MOB.Carry[i]);
	}

	for (i = 0; i < MAX_CARGO; i++)
	{
		if (pUser[conn].Cargo[i].sIndex != 747 && pUser[conn].Cargo[i].sIndex != 3993 && pUser[conn].Cargo[i].sIndex != 3994) // 747 = Crown on itemlist
			continue;

		sprintf_s(temp, "etc,crown guild:%d level:%d charge:%d name:%s", Guild, GLevel, ChargedGuildList[ServerIndex][4], pMob[conn].MOB.MobName);
		SystemLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, temp);

		memset(&pUser[conn].Cargo[i], 0, sizeof(STRUCT_ITEM));

		SendItem(conn, ITEM_PLACE_CARGO, i, &pUser[conn].Cargo[i]);
	}
}

BOOL AddCrackError(int conn, int val, int Type)
{
	if (Type != 3 && Type != 8 && Type != 15)
	{
		//sprintf(temp, "cra point: %d  type: %d", val, Type);
		//Log(temp, pUser[conn].AccountName, pUser[conn].IP);
	}

	pUser[conn].NumError = pUser[conn].NumError + val;

	if (pUser[conn].NumError >= 2000000000)
	{
		 
		SendMsgExp(conn, g_pMessageStringTable[_NN_Bad_Network_Packets], TNColor::Default, false);
		CharLogOut(conn);

		//sprintf(temp, "cra char logout type: %d", Type);
		//Log(temp, pUser[conn].AccountName, pUser[conn].IP);

		return TRUE;
	}

	return FALSE;
}

BOOL PutItemArea(STRUCT_ITEM *item, int x1, int y1, int x2, int y2)
{
	for (int i = 0; i < MAX_USER; i++)
	{
		if (i <= 0 || i >= MAX_USER)
			return FALSE;

		if (pUser[i].Mode != USER_PLAY)
			return FALSE;

		int pos = 0;

		if (pMob[i].TargetX >= x1 && pMob[i].TargetX <= x2 && pMob[i].TargetY >= y1 && pMob[i].TargetY <= y2)
		{
			for (pos = 0; pos < pMob[i].MaxCarry && pos < MAX_CARRY; pos++)
			{
				if (pMob[i].MOB.Carry[pos].sIndex == 0)
					break;
			}

			if (pos >= 0 && pos < pMob[i].MaxCarry && pos < MAX_CARRY)
			{
				memcpy(&pMob[i].MOB.Carry[pos], item, sizeof(STRUCT_ITEM));

				SendItem(i, ITEM_PLACE_CARRY, pos, &pMob[i].MOB.Carry[pos]);
			}
			else
			{ 
				SendMsgExp(i, g_pMessageStringTable[_NN_You_Have_No_Space_To_Trade], TNColor::Red, false);
				return FALSE;
			}
		}
	}
	return TRUE;
}

BOOL PutItem(int conn, STRUCT_ITEM *item)
{
	if (conn <= 0 || conn >= MAX_USER)
		return FALSE;

	if (pUser[conn].Mode != USER_PLAY)
		return FALSE;

	int pos = 0;

	for (pos = 0; pos < pMob[conn].MaxCarry && pos < MAX_CARRY; pos++)
	{
		if (pMob[conn].MOB.Carry[pos].sIndex == 0)
			break;
	}

	if (pos >= 0 && pos < pMob[conn].MaxCarry && pos < MAX_CARRY)
	{
		memcpy(&pMob[conn].MOB.Carry[pos], item, sizeof(STRUCT_ITEM));

		SendItem(conn, ITEM_PLACE_CARRY, pos, &pMob[conn].MOB.Carry[pos]);
	}
	else
	{ 
		SendMsgExp(conn, g_pMessageStringTable[_NN_You_Have_No_Space_To_Trade], TNColor::Red, false);
		return FALSE;
	}
	return TRUE;
}

void GuildZoneReport(void)
{
	MSG_GuildZoneReport sm;
	memset(&sm, 0, sizeof(MSG_GuildZoneReport));

	sm.Type = _MSG_GuildZoneReport;
	sm.Size = sizeof(sm);
	sm.ID = ServerIndex;

	for (int i = 0; i < MAX_GUILDZONE; i++)
	{
		sm.Guild[i] = g_pGuildZone[i].ChargeGuild;
	}

	DBServerSocket.SendOneMessage((char*)&sm, sizeof(sm));
}

HFONT__ *GetAFont()
{
	return 0;
}

void ReadConfig(void) // TODO : EVERYTHING
{
	FILE *fp = NULL;
	fp = fopen("gameconfig.txt", "rt");

	if (fp == NULL)
	{
		MessageBox(hWndMain, "no gameconfig.txt, server will generate default setting.", "Error", MB_OK | MB_SYSTEMMODAL);

		ConfigReady = 1;

		DrawConfig(TRUE);

		return;
	}

	char tmp[512];
	char parm[16][32];
	int  value[26];

	fgets(tmp, 511, fp);

	if (strcmp(tmp, "Drop Item Event Settings:\n"))
	{
		MessageBox(hWndMain, "not game-server generated gameconfig.txt - Line1", "Error", MB_OK | MB_SYSTEMMODAL);

		fclose(fp);

		return;
	}

	for (int i = 0; i < 16; i++)
	{
		value[i] = -1;

		memset(parm[i], 0, 32);
	}

	fgets(tmp, 511, fp);

	sscanf(tmp, "%s %d %s %d %s %d %s %d %s %d %s %d %d %d %d", parm[0], &value[0], parm[1], &value[1], parm[2], &value[2], parm[3], &value[3], parm[4], &value[4], parm[5], &value[5], &value[6], &value[7], &value[8]);

	if (strcmp(parm[0], "evindex") || strcmp(parm[1], "evdelete") || strcmp(parm[2], "evon") || strcmp(parm[3], "evitem") || strcmp(parm[4], "evrate") || strcmp(parm[5], "evstart"))
	{
		MessageBox(hWndMain, "not game-server generated gameconfig.txt - Line2", "Error", MB_OK | MB_SYSTEMMODAL);

		fclose(fp);

		return;
	}

	if (value[0] == -1 || value[1] == -1 || value[2] == -1 || value[3] == -1 || value[4] == -1 || value[5] == -1 || value[6] == -1 || value[7] == -1)
	{
		MessageBox(hWndMain, "not game-server generated gameconfig.txt - Line2", "Error", MB_OK | MB_SYSTEMMODAL);

		fclose(fp);

		return;
	}

	evIndex = value[0];
	evDelete = value[1];
	evOn = value[2];
	evItem = value[3];
	evRate = value[4];
	evStartIndex = value[5];
	evCurrentIndex = value[6];
	evEndIndex = value[7];
	evNotice = value[8];

	fgets(tmp, 511, fp);

	if (strcmp(tmp, "Etc Event Settings:\n"))
	{
		MessageBox(hWndMain, "not game server generated gameconfig.txt - Line3", "Error", MB_OK | MB_SYSTEMMODAL);

		fclose(fp);

		return;
	}

	for (int i = 0; i < 16; i++)
	{
		value[i] = -1;

		memset(parm[i], 0, 32);
	}

	fgets(tmp, 511, fp);

	sscanf(tmp, "%s %d %s %d %s %d %s %d %s %d", parm[0], &value[0], parm[1], &value[1], parm[2], &value[2], parm[3], &value[3], parm[4], &value[4]);

	if (strcmp(parm[0], "double") || strcmp(parm[1], "deadpoint") || strcmp(parm[2], "dungeonevent") || strcmp(parm[3], "statsapphire"))
	{
		MessageBox(hWndMain, "not game-server generated gameconfig.txt - Line4", "Error", MB_OK | MB_SYSTEMMODAL);

		fclose(fp);

		return;
	}

	if (value[0] == -1 || value[1] == -1 || value[2] == -1 || value[3] == -1)
	{
		MessageBox(hWndMain, "not game-server generated gameconfig.txt - Line4", "Error", MB_OK | MB_SYSTEMMODAL);

		fclose(fp);

		return;
	}

	DOUBLEMODE = value[0];
	DUNGEONEVENT = value[1];
	DEADPOINT = value[2];
	StatSapphire = value[3];
	BRItem = value[4];

	fgets(tmp, 511, fp);

	if (strcmp(tmp, "Billing Settings:\n"))
	{
		MessageBox(hWndMain, "not game server generated gameconfig.txt - Line5", "Error", MB_OK | MB_SYSTEMMODAL);

		fclose(fp);

		return;
	}

	for (int i = 0; i < 16; i++)
	{
		value[i] = -1;

		memset(parm[i], 0, 32);
	}

	fgets(tmp, 511, fp);

	sscanf(tmp, "%s %d %s %d %s %d %s %d %s %d %s %d", parm[0], &value[0], parm[1], &value[1], parm[2], &value[2], parm[3], &value[3], parm[4], &value[4], parm[5], &value[5]);

	if (strcmp(parm[0], "billmode") || strcmp(parm[1], "freeexp"))
	{
		MessageBox(hWndMain, "not game-server generated gameconfig.txt - Line6", "Error", MB_OK | MB_SYSTEMMODAL);

		fclose(fp);

		return;
	}

	if (value[0] == -1 || value[1] == -1)
	{
		MessageBox(hWndMain, "not game-server generated gameconfig.txt - Line6", "Error", MB_OK | MB_SYSTEMMODAL);

		fclose(fp);

		return;
	}

	BILLING = value[0];
	FREEEXP = value[1];
	CHARSELBILL = value[2];
	POTIONCOUNT = value[3];
	PARTYBONUS = value[4];
	GUILDBOARD = value[5];

	if (PARTYBONUS < 50 || PARTYBONUS > 200)
		PARTYBONUS = 100;

	fgets(tmp, 511, fp);

	if (strcmp(tmp, "Item Drop Bonus Settings:\n"))
	{
		MessageBox(hWndMain, "not game server generated gameconfig.txt - Line7", "Error", MB_OK | MB_SYSTEMMODAL);

		return;
	}

	fgets(tmp, 511, fp);

	sscanf(tmp, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", &value[0], &value[1], &value[2], &value[3], &value[4], &value[5], &value[6], &value[7], &value[8], &value[9], &value[10], &value[11], &value[12], &value[13], &value[14], &value[15]);

	for (int k = 0; k < 16; k++)
	{
		if (value[k] < 0 || value[k] > 9999)
		{
			MessageBox(hWndMain, "not game-server generated gameconfig.txt - Line8", "Error", MB_OK | MB_SYSTEMMODAL);

			fclose(fp);

			return;
		}

		g_pDropBonus[k] = value[k];
		value[k] = -1;
	}

	fgets(tmp, 511, fp);

	sscanf(tmp, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", &value[0], &value[1], &value[2], &value[3], &value[4], &value[5], &value[6], &value[7], &value[8], &value[9], &value[10], &value[11], &value[12], &value[13], &value[14], &value[15]);

	for (int k = 0; k < 16; k++)
	{
		if (value[k] < 0 || value[k] > 9999)
		{
			MessageBox(hWndMain, "not game-server generated gameconfig.txt - Line9", "Error", MB_OK | MB_SYSTEMMODAL);

			fclose(fp);

			return;

		}

		g_pDropBonus[k + 16] = value[k];

		value[k] = -1;
	}

	fgets(tmp, 511, fp);

	sscanf(tmp, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", &value[0], &value[1], &value[2], &value[3], &value[4], &value[5], &value[6], &value[7], &value[8], &value[9], &value[10], &value[11], &value[12], &value[13], &value[14], &value[15]);

	for (int k = 0; k < 16; k++)
	{
		if (value[k] < 0 || value[k] > 9999)
		{
			MessageBox(hWndMain, "not game-server generated gameconfig.txt - Line10", "Error", MB_OK | MB_SYSTEMMODAL);

			fclose(fp);

			return;
		}

		g_pDropBonus[k + 32] = value[k];

		value[k] = -1;
	}

	fgets(tmp, 511, fp);

	sscanf(tmp, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", &value[0], &value[1], &value[2], &value[3], &value[4], &value[5], &value[6], &value[7], &value[8], &value[9], &value[10], &value[11], &value[12], &value[13], &value[14], &value[15]);

	for (int k = 0; k < 16; k++)
	{
		if (value[k] < 0 || value[k] > 9999)
		{
			MessageBox(hWndMain, "not game-server generated gameconfig.txt - Line11", "Error", MB_OK | MB_SYSTEMMODAL);

			fclose(fp);

			return;
		}

		g_pDropBonus[k + 48] = value[k];

		value[k] = -1;
	}

	fgets(tmp, 511, fp);

	if (strcmp(tmp, "Treasure Settings:\n"))
	{
		MessageBox(hWndMain, "not game server generated gameconfig.txt - Line12", "Error", MB_OK | MB_SYSTEMMODAL);

		fclose(fp);

		return;
	}

	for (int k = 0; k < 8; k++)
	{
		STRUCT_TREASURE *t = &g_pTreasure[k];

		memset(t, 0, sizeof(*t));

		for (int i = 0; i < 26; i++)
			value[i] = -1;

		fgets(tmp, 511, fp);

		sscanf(tmp, "%d  %d %d %d %d %d  %d %d %d %d %d  %d %d %d %d %d  %d %d %d %d %d  %d %d %d %d %d",
			&value[0], &value[1], &value[2], &value[3], &value[4], &value[5], &value[6], &value[7], &value[8], &value[9],
			&value[10], &value[11], &value[12], &value[13], &value[14], &value[15], &value[16], &value[17], &value[18], &value[19],
			&value[20], &value[21], &value[22], &value[23], &value[24], &value[25]);

		t->Source = value[0];

		for (int i = 0; i < 5; i++)
		{
			STRUCT_ITEM *it = &t->Target[i];

			it->sIndex = value[1 + i * 5];
			it->stEffect[0].cEffect = value[2 + i * 5];
			it->stEffect[0].cValue = value[3 + i * 5];
			it->stEffect[1].cEffect = value[4 + i * 5];
			it->stEffect[1].cValue = value[5 + i * 5];

		}

		fgets(tmp, 511, fp);

		sscanf(tmp, "%d %d %d %d %d", &value[0], &value[1], &value[2], &value[3], &value[4]);

		for (int i = 0; i < 5; i++)
			t->Rate[i] = value[i];
	}

	fgets(tmp, 511, fp);

	if (strcmp(tmp, "Etc Settings:\n"))
	{
		MessageBox(hWndMain, "not game server generated gameconfig.txt - Line13", "Error", MB_OK | MB_SYSTEMMODAL);

		fclose(fp);

		return;
	}

	for (int i = 0; i < 16; i++)
	{
		value[i] = -1;

		memset(parm[i], 0, 32);
	}

	fgets(tmp, 511, fp);

	sscanf(tmp, "%s %3d %s %3d %s %3d %s %3d %s %3d %s %3d %s %3d %s %3d %s %3d", parm[0], &value[0], parm[1], &value[1], parm[2], &value[2], parm[3], &value[3], parm[4], &value[4], parm[5], &value[5], parm[6], &value[6], parm[7], &value[7], parm[8], &value[8]);

	if (strcmp(parm[0], "partydif") || strcmp(parm[1], "kefrastatus") || strcmp(parm[2], "GTorreHour") || strcmp(parm[3], "RVRHour") || strcmp(parm[4], "DropItem") || strcmp(parm[5], "BRHour") || strcmp(parm[6], "maxNightmare") || strcmp(parm[7], "PotionDelay") || strcmp(parm[8], "HardCore"))
	{
		MessageBox(hWndMain, "not game-server generated gameconfig.txt - Line13", "Error", MB_OK | MB_SYSTEMMODAL);

		fclose(fp);

		return;
	}

	if (value[0] == -1 || value[1] == -1 || value[2] == -1 || value[3] == -1 || value[4] == -1 || value[5] == -1 || value[6] == -1 || value[7] == -1 || value[8] == -1)
	{
		MessageBox(hWndMain, "not game-server generated gameconfig.txt - Line13", "Error", MB_OK | MB_SYSTEMMODAL);

		fclose(fp);

		return;
	}

	PARTY_DIF = value[0];
	KefraLive = value[1];
	GTorreHour = value[2];
	RvRHour = value[3];
	isDropItem = value[4];
	BRHour = value[5];
	maxNightmare = value[6];
	PotionDelay = value[7];
	isHardCore = value[8];

	fclose(fp);
}

void BASE_ReadQuestDiaria()
{
	FILE* fp = fopen("QuestDiaria.txt", "rb");

	if (fp == NULL)
	{
		MessageBoxA(NULL, "N�o foi poss�vel carregar o arquivo 'QuestDiaria.txt'", "TMSRV", MB_OK);

		return;
	}

	int count = 0;

	while (fscanf(fp, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",
		&QuestDiaria[count].IndexQuest,
		&QuestDiaria[count].Nivel,
		&QuestDiaria[count].IdMob1, &QuestDiaria[count].QtdMob1,
		&QuestDiaria[count].IdMob2, &QuestDiaria[count].QtdMob2,
		&QuestDiaria[count].IdMob3, &QuestDiaria[count].QtdMob3,
		&QuestDiaria[count].ExpReward,
		&QuestDiaria[count].GoldReward,
		&QuestDiaria[count].Item->sIndex,
		&QuestDiaria[count].Item->stEffect[0].cEffect,
		&QuestDiaria[count].Item->stEffect[0].cValue,
		&QuestDiaria[count].Item->stEffect[1].cEffect,
		&QuestDiaria[count].Item->stEffect[1].cValue,
		&QuestDiaria[count].Item->stEffect[2].cEffect,
		&QuestDiaria[count].Item->stEffect[2].cValue) != EOF && count < 7)
		count++;

	fclose(fp);
}

void DrawConfig(int wb)
{
	if (ConfigReady == 0)
		return;

	int x = 0;
	int y = 0;
	HFONT h = 0;

	int color = 255;
	int backcolor = 0;

	char String[4096];
	int len = 0;

	hDC = GetDC(hWndMain);

	if (hDC == NULL)
		return;

	if (hFont == 0)
		return;

	if (SelectObject(hDC, hFont) != 0)
		h = (HFONT)SelectObject(hDC, hFont);

	FILE *fp = NULL;

	if (wb)
		fp = fopen("gameconfig.txt", "w+");

	SetTextColor(hDC, color);

	sprintf_s(String, "Drop Item Event Settings:");
	len = strlen(String);

	TextOutA(hDC, x, y, String, len);

	y += 16;

	if (wb)
		fprintf(fp, "%s\n", String);

	SetTextColor(hDC, backcolor);

	sprintf_s(String, "   evindex %d   evdelete %d   evon %d   evitem %d   evrate %d   evstart %d %d %d %d",
		evIndex, evDelete, evOn, evItem, evRate, evStartIndex, evCurrentIndex, evEndIndex, evNotice);

	len = strlen(String);

	TextOutA(hDC, x, y, String, len);

	y += 16;

	if (wb)
		fprintf(fp, "%s\n", String);

	SetTextColor(hDC, color);

	sprintf_s(String, "Etc Event Settings:");

	len = strlen(String);
	TextOutA(hDC, x, y, String, len);

	y += 16;

	if (wb)
		fprintf(fp, "%s\n", String);

	SetTextColor(hDC, backcolor);
	sprintf_s(String, "   double %d   deadpoint %d   dungeonevent %d   statsapphire %d    battleroyal %d",
		DOUBLEMODE, DEADPOINT, DUNGEONEVENT, StatSapphire, BRItem);

	len = strlen(String);

	TextOutA(hDC, x, y, String, len);

	y += 16;

	if (wb)
		fprintf(fp, "%s\n", String);

	SetTextColor(hDC, color);

	sprintf_s(String, "Billing Settings:");

	len = strlen(String);
	TextOutA(hDC, x, y, String, len);

	y += 16;

	if (wb)
		fprintf(fp, "%s\n", String);

	SetTextColor(hDC, backcolor);

	sprintf_s(String, "   billmode %d   freeexp %d   charselbill %d    potioncount %d   partybonus %d   guildboard %d",
		BILLING, FREEEXP, CHARSELBILL, POTIONCOUNT, PARTYBONUS, GUILDBOARD);

	len = strlen(String);
	TextOutA(hDC, x, y, String, len);

	y += 16;

	if (wb)
		fprintf(fp, "%s\n", String);

	SetTextColor(hDC, color);

	sprintf_s(String, "Item Drop Bonus Settings:");

	len = strlen(String);
	TextOutA(hDC, x, y, String, len);

	y += 16;

	if (wb)
		fprintf(fp, "%s\n", String);

	SetTextColor(hDC, backcolor);

	for (int i = 0; i < 4; i++)
	{
		int pos = 16 * i;
		sprintf(String, "   %3d %3d %3d %3d %3d %3d %3d %3d   %3d %3d %3d %3d %3d %3d %3d %3d",
			g_pDropBonus[0 + pos], g_pDropBonus[1 + pos], g_pDropBonus[2 + pos], g_pDropBonus[3 + pos],
			g_pDropBonus[4 + pos], g_pDropBonus[5 + pos], g_pDropBonus[6 + pos], g_pDropBonus[7 + pos],
			g_pDropBonus[8 + pos], g_pDropBonus[9 + pos], g_pDropBonus[10 + pos], g_pDropBonus[11 + pos],
			g_pDropBonus[12 + pos], g_pDropBonus[13 + pos], g_pDropBonus[14 + pos], g_pDropBonus[15 + pos]);

		len = strlen(String);
		TextOutA(hDC, x, y, String, len);

		y += 16;

		if (wb)
			fprintf(fp, "%s\n", String);
	}

	SetTextColor(hDC, color);

	sprintf_s(String, "Treasure Settings:");
	len = strlen(String);

	TextOutA(hDC, x, y, String, len);
	y += 16;

	if (wb)
		fprintf(fp, "%s\n", String);

	SetTextColor(hDC, backcolor);

	for (int j = 0; j < 8; j++)
	{
		STRUCT_TREASURE *tr = &g_pTreasure[j];

		sprintf_s(String, "%-4d ", g_pTreasure[j].Source);

		for (int k = 0; k < 5; ++k)
		{
			STRUCT_ITEM *item = &tr->Target[k];

			sprintf_s(String, "%s  %-4d %2d %2d %2d %2d   ",
				String, item->sIndex, item->stEffect[0].cEffect, item->stEffect[0].cValue, item->stEffect[1].cEffect, item->stEffect[1].cValue);
		}
		len = strlen(String);

		TextOutA(hDC, x, y, String, len);
		y += 16;

		if (wb)
			fprintf(fp, "%s\n", String);

		sprintf_s(String, "       %-5d                %-5d                %-5d                %-5d                %-5d",
			tr->Rate[0], tr->Rate[1], tr->Rate[2], tr->Rate[3], tr->Rate[4]);

		len = strlen(String);
		TextOutA(hDC, x, y, String, len);
		y += 16;
		if (wb)
			fprintf(fp, "%s\n", String);
	}

	SetTextColor(hDC, color);

	sprintf_s(String, "Etc Settings:");

	len = strlen(String);
	TextOutA(hDC, x, y, String, len);

	y += 16;

	if (wb)
		fprintf(fp, "%s\n", String);

	SetTextColor(hDC, backcolor);
	sprintf_s(String, "   partydif %d   kefrastatus %d   GTorreHour %d    RVRHour %d    DropItem %d   BRHour %d   maxNightmare %d   PotionDelay %d   HardCore %d",
		PARTY_DIF, KefraLive, GTorreHour, RvRHour, isDropItem, BRHour, maxNightmare, PotionDelay, isHardCore);

	len = strlen(String);

	TextOutA(hDC, x, y, String, len);

	y += 16;

	if (wb)
		fprintf(fp, "%s\n", String);

	if (hFont && h)
		h = (HFONT)SelectObject(hDC, h);

	ReleaseDC(hWndMain, hDC);

	if (wb)
		fclose(fp);
}

void AddFailAccount(char *Account)
{
	for (int i = 0; i < 16; i++)
	{
		if (FailAccount[i][0] == 0)
		{
			strncpy(FailAccount[i], Account, sizeof(FailAccount[i]));

			return;
		}
	}
}

int  CheckFailAccount(char *Account)
{
	int Num = 0;

	for (int i = 0; i < 16; i++)
	{
		if (FailAccount[i][0] != 0)
		{
			if (strcmp(FailAccount[i], Account) == 0)
				Num++;
		}
	}

	return Num;
}

int  IsFree(STRUCT_SELCHAR *sel)
{
	if (FREEEXP <= 0)
		return 1;

	for (int i = 0; i < MOB_PER_ACCOUNT; i++)
	{
		if (sel->Name[i][0] != 0 && sel->Score[i].Level >= FREEEXP && sel->Score[i].Level < 999)
			return 1;
	}

	return 0;
}

int  SendBilling(int a1, char *a2, int a3, int a4)
{
	return TRUE;
}

int  SendBilling2(_AUTH_GAME *m, int hostlong)
{
	*(u_long*)&m->Unk = htonl(hostlong);

	sprintf_s(m->Unk, "%d", ServerIndex + 10 * ServerGroup);

	BillServerSocket.SendBillMessage((char*)m);

	return 0;
}

void SetItemBonus(STRUCT_ITEM *Dest, int Level, int a3, int DropBonus)
{
	int addDropBonus = DropBonus / 8;

	if (DropBonus / 8 < 0)
		addDropBonus = 0;

	if (addDropBonus > 2)
		addDropBonus = 2;

	int add1 = -1;
	int add2 = -1;

	if (Dest->stEffect[0].cEffect >= EF_GRADE0 && Dest->stEffect[0].cEffect <= EF_GRADE5)
	{
		add1 = Dest->stEffect[0].cEffect - EF_GRADE0;
		add2 = Dest->stEffect[0].cValue;

		Dest->stEffect[0].cEffect = 0;
		Dest->stEffect[0].cValue = 0;
	}

	g_dLevel1 = 0;
	g_dLevel2 = 0;

	if (!a3 && Level >= 210)
		Level -= 47;

	int ItemId = Dest->sIndex;
	int nUnique = g_pItemList[ItemId].nUnique;
	int nReqLv = g_pItemList[ItemId].ReqLvl;
	int nPos = g_pItemList[ItemId].nPos;

	int lvdif = (Level - nReqLv + 1) / 25;

	if (add1 != -1)
		lvdif = add1;

	g_dLevel = lvdif;

	int pForc = 0;

	if (lvdif >= 4)
		pForc = 1;

	if (lvdif < 0)
		lvdif = 0;

	if (lvdif > 3)
		lvdif = 3;

	if (a3 && lvdif >= 3)
		lvdif = 2;

	if (nPos & 0xFE && !LOBYTE(Dest->stEffect[0].sValue) && nPos != 128)
	{

		int v38 = 59;
		int v37 = 0;
		int v36 = 0;
		int v35 = rand() % 101;
		int v34 = 100;

		if (a3)
		{
			v34 = v35 % 3;
		}
		else
		{
			if (lvdif)
			{
				if (lvdif == 1)
				{
					v34 = v35 % (6 - addDropBonus);
				}
				else
				{
					if (lvdif == 2)
					{
						v34 = v35 % (6 - addDropBonus);
					}
					else
					{
						if (lvdif >= 3)
							v34 = v35 % 4;
					}
				}
			}
			else
			{
				v34 = v35 % (8 - addDropBonus);
			}
		}
		switch (nPos)
		{
		case 2:
			if (v34)
			{
				if (v34 == 1)
				{
					v38 = 60;
					v36 = 2;
				}
			}
			else
			{
				v38 = 26;
				v36 = 3;
			}
			break;
		case 4:
			v38 = 71;
			v36 = 10;
			v37 = 1;
			break;
		case 8:
			v38 = 71;
			v36 = 10;
			v37 = 1;
			break;
		case 16:
			v38 = 72;
			v36 = 5;
			break;
		case 32:
			v38 = 73;
			v36 = 6;
			v37 = -1;
			break;
		case 64:
		case 192:
			if (nUnique != 44 && nUnique != 47)
			{
				if (v34)
				{
					if (v34 == 1)
					{
						v38 = 2;
						v36 = 9;
						v37 = -1;
					}
					else
					{
						if (v34 == 2)
						{
							v38 = 74;
							v36 = 3;
						}
					}
				}
				else
				{
					v38 = 26;
					v36 = 3;
					v37 = 1;
				}
			}
			else
			{
				if (v34)
				{
					if (v34 == 1)
					{
						v38 = 74;
						v36 = 3;
						v37 = 1;
					}
				}
				else
				{
					v38 = 60;
					v36 = 4;
					v37 = -1;
				}
			}
			break;
		}
		int v33 = rand() % 100;
		if (a3)
			v33 = 2 * v33 / 3;
		int v32 = 100;
		if (a3)
		{
			v32 = v33 % 4;
		}
		else
		{
			if (lvdif)
			{
				if (lvdif == 1)
				{
					v32 = v33 % 6;
				}
				else
				{
					if (lvdif == 2)
					{
						v32 = v33 % 6;
					}
					else
					{
						if (lvdif >= 3)
							v32 = v33 % 4;
					}
				}
			}
			else
			{
				v32 = v33 % 8;
			}
		}
		int v31 = 59;
		int v30 = 0;
		int v29 = 0;
		switch (nPos)
		{
		case 2:
			if (v32)
			{
				if (v32 == 1)
				{
					v31 = 3;
					v30 = 5;
					v29 = -1;
				}
			}
			else
			{
				v31 = 4;
				v30 = 10;
			}
			break;
		case 4:
			if (v32)
			{
				if (v32 == 1)
				{
					v31 = 2;
					v30 = 6;
					v29 = -1;
				}
				else
				{
					if (v32 == 2)
					{
						v31 = 3;
						v30 = 5;
						v29 = -1;
					}
				}
			}
			else
			{
				v31 = 60;
				v30 = 2;
				v29 = -1;
			}
			break;
		case 8:
			if (v32)
			{
				if (v32 == 1)
				{
					v31 = 2;
					v30 = 6;
					v29 = -1;
				}
				else
				{
					if (v32 == 2)
					{
						v31 = 3;
						v30 = 5;
						v29 = -1;
					}
				}
			}
			else
			{
				v31 = 60;
				v30 = 2;
				v29 = -1;
			}
			break;
		case 16:
			if (v32)
			{
				switch (v32)
				{
				case 1:
					v31 = 2;
					v30 = 6;
					v29 = -1;
					break;
				case 2:
					v31 = 74;
					v30 = 3;
					break;
				case 3:
					v31 = 54;
					v30 = 3;
					break;
				}
			}
			else
			{
				v31 = 60;
				v30 = 2;
				v29 = -1;
			}
			break;
		case 32:
			if (v32)
			{
				if (v32 == 1)
				{
					v31 = 74;
					v30 = 3;
				}
			}
			else
			{
				v31 = 60;
				v30 = 2;
				v29 = -1;
			}
			break;
		case 64:
		case 128:
		case 192:
			if (nUnique != 44 && nUnique != 47)
			{
				if (v32)
				{
					if (v32 == 1)
					{
						v31 = 2;
						v30 = 9;
						v29 = -1;
					}
					else
					{
						if (v32 == 2)
						{
							v31 = 74;
							v30 = 3;
							v29 = 1;
						}
					}
				}
				else
				{
					v31 = 26;
					v30 = 3;
					v29 = 1;
				}
			}
			else
			{
				if (v32)
				{
					if (v32 == 1)
					{
						v31 = 74;
						v30 = 3;
						v29 = 1;
					}
				}
				else
				{
					v31 = 60;
					v30 = 4;
					v29 = -1;
				}
			}
			break;
		}
		int v28 = 0;
		v35 = rand() % 100;
		if (lvdif)
		{
			switch (lvdif)
			{
			case 1:
				if (v35 >= 1)
				{
					if (v35 >= 5)
					{
						if (v35 >= 24)
						{
							if (v35 >= 65)
								v28 = 1;
							else
								v28 = 2;
						}
						else
						{
							v28 = 3;
						}
					}
					else
					{
						v28 = 4;
					}
				}
				else
				{
					v28 = 5;
				}
				break;
			case 2:
				if (v35 >= 2)
				{
					if (v35 >= 16)
					{
						if (v35 >= 60)
							v28 = 2;
						else
							v28 = 3;
					}
					else
					{
						v28 = 4;
					}
				}
				else
				{
					v28 = 5;
				}
				break;
			case 3:
				if (v35 >= 2)
				{
					if (v35 >= 9)
					{
						if (v35 >= 45)
						{
							if (v35 >= 75)
								v28 = 2;
							else
								v28 = 3;
						}
						else
						{
							v28 = 4;
						}
					}
					else
					{
						v28 = 5;
					}
				}
				else
				{
					v28 = 6;
				}
				break;
			default:
				if (lvdif >= 4)
				{
					if (v35 >= 2)
					{
						if (v35 >= 10)
						{
							if (v35 >= 30)
							{
								if (v35 >= 75)
									v28 = 3;
								else
									v28 = 4;
							}
							else
							{
								v28 = 5;
							}
						}
						else
						{
							v28 = 6;
						}
					}
					else
					{
						v28 = 7;
					}
				}
				break;
			}
		}
		else
		{
			if (v35 >= 2)
			{
				if (v35 >= 6)
				{
					if (v35 >= 24)
						v28 = v35 < 55;
					else
						v28 = 2;
				}
				else
				{
					v28 = 3;
				}
			}
			else
			{
				v28 = 4;
			}
		}
		if (pForc && v28 < 4)
			v28 = 4;
		v28 += v37;
		if (a3 && !v28)
			v28 = 1;
		if (LOBYTE(Dest->stEffect[1].sValue) || v28 <= 0)
		{
			if (LOBYTE(Dest->stEffect[1].sValue) || v28 > 0 || nPos != 32)
			{
				if (!LOBYTE(Dest->stEffect[1].sValue))
				{
					Dest->stEffect[1].cEffect = 59;
					int v4 = rand() & 0x8000007F;
					if (v4 < 0)
						v4 = ((unsigned __int8)(v4 - 1) | 0x80) + 1;
					Dest->stEffect[1].cValue = v4;
				}
			}
			else
			{
				Dest->stEffect[1].cEffect = v38;
				Dest->stEffect[1].cValue = 0;
			}
		}
		else
		{
			Dest->stEffect[1].cEffect = v38;
			Dest->stEffect[1].cValue = v36 * v28;
		}
		g_dLevel1 = v28;
		int v27 = 0;
		v33 = rand() % 100;
		if (lvdif)
		{
			switch (lvdif)
			{
			case 1:
				if (v33 >= 1)
				{
					if (v33 >= 5)
					{
						if (v33 >= 24)
						{
							if (v33 >= 65)
								v27 = 1;
							else
								v27 = 2;
						}
						else
						{
							v27 = 3;
						}
					}
					else
					{
						v27 = 4;
					}
				}
				else
				{
					v27 = 5;
				}
				break;
			case 2:
				if (v33 >= 2)
				{
					if (v33 >= 16)
					{
						if (v33 >= 60)
							v27 = 2;
						else
							v27 = 3;
					}
					else
					{
						v27 = 4;
					}
				}
				else
				{
					v27 = 5;
				}
				break;
			case 3:
				if (v33 >= 2)
				{
					if (v33 >= 9)
					{
						if (v33 >= 45)
						{
							if (v33 >= 75)
								v27 = 2;
							else
								v27 = 3;
						}
						else
						{
							v27 = 4;
						}
					}
					else
					{
						v27 = 5;
					}
				}
				else
				{
					v27 = 6;
				}
				break;
			default:
				if (lvdif >= 4)
				{
					if (v33 >= 2)
					{
						if (v33 >= 10)
						{
							if (v33 >= 30)
							{
								if (v33 >= 75)
									v27 = 3;
								else
									v27 = 4;
							}
							else
							{
								v27 = 5;
							}
						}
						else
						{
							v27 = 6;
						}
					}
					else
					{
						v27 = 7;
					}
				}
				break;
			}
		}
		else
		{
			if (v35 >= 2)
			{
				if (v33 >= 6)
				{
					if (v33 >= 24)
						v27 = v33 < 55;
					else
						v27 = 2;
				}
				else
				{
					v27 = 3;
				}
			}
			else
			{
				v28 = 4;
			}
		}
		if (pForc && v27 < 3)
			v27 = 3;
		if (a3 && v27 >= 5)
			v27 = 4;
		v27 += v29;
		if (addDropBonus && !v27)
			v27 = addDropBonus;
		if (a3 && !v27)
			v27 = 1;
		if (v27 <= 0 || LOBYTE(Dest->stEffect[2].sValue))
		{
			if (!LOBYTE(Dest->stEffect[2].sValue))
			{
				Dest->stEffect[2].cEffect = 59;
				int v5 = rand() & 0x8000007F;
				if (v5 < 0)
					v5 = ((unsigned __int8)(v5 - 1) | 0x80) + 1;
				Dest->stEffect[2].cValue = v5;
			}
		}
		else
		{
			Dest->stEffect[2].cEffect = v31;
			Dest->stEffect[2].cValue = v30 * v27;
		}
		g_dLevel2 = v27;

		if (!LOBYTE(Dest->stEffect[0].sValue))
		{
			int v26 = rand() % 100;
			if (a3)
				v26 /= 2;
			int v25 = 1;
			int v24 = 12;
			int v23 = 45;
			int v22 = 70;
			if (lvdif >= 3)
			{
				v25 = 6;
				v24 = 35;
				v23 = 85;
				v22 = 100;
			}
			if (lvdif == 2)
			{
				v25 = 6;
				v24 = 35;
				v23 = 85;
				v22 = 100;
			}
			if (lvdif == 1)
			{
				v25 = 6;
				v24 = 22;
				v23 = 75;
				v22 = 90;
			}
			if (!lvdif)
			{
				v25 = 6;
				v24 = 22;
				v23 = 75;
				v22 = 90;
			}
			if (v26 >= v25)
			{
				if (v26 >= v24)
				{
					if (v26 >= v23)
					{
						if (v26 >= v22)
						{
							Dest->stEffect[0].cEffect = 59;
							int v6 = rand() & 0x8000007F;
							if (v6 < 0)
								v6 = ((unsigned __int8)(v6 - 1) | 0x80) + 1;
							Dest->stEffect[0].cValue = v6;
						}
						else
						{
							int v20 = rand() % 10;
							int v19 = g_pBonusType[v20];
							int v18 = lvdif;
							int v17 = g_pBonusValue[v20][lvdif][0];
							int v16 = g_pBonusValue[v20][lvdif][1];
							int v15 = v16 + 1 - v17;
							int v14 = rand() % v15 + v17;
							Dest->stEffect[0].cEffect = v19;
							Dest->stEffect[0].cValue = v14;
						}
					}
					else
					{
						Dest->stEffect[0].cEffect = 43;
						Dest->stEffect[0].cValue = 0;
					}
				}
				else
				{
					Dest->stEffect[0].cEffect = 43;
					Dest->stEffect[0].cValue = 1;
				}
			}
			else
			{
				Dest->stEffect[0].cEffect = 43;
				Dest->stEffect[0].cValue = 2;
				if (add2 > 2)
				{
					int v21 = rand() % 100;
					switch (add2)
					{
					case 3:
						if (v21 < 30)
							Dest->stEffect[0].cValue = 3;
						break;
					case 4:
						if (v21 >= 10)
						{
							if (v21 < 40)
								Dest->stEffect[0].cValue = 3;
						}
						else
						{
							Dest->stEffect[0].cValue = 4;
						}
						break;
					case 5:
						if (v21 >= 10)
						{
							if (v21 >= 30)
							{
								if (v21 < 60)
									Dest->stEffect[0].cValue = 3;
							}
							else
							{
								Dest->stEffect[0].cValue = 4;
							}
						}
						else
						{
							Dest->stEffect[0].cValue = 5;
						}
						break;
					case 6:
						if (v21 >= 10)
						{
							if (v21 >= 20)
							{
								if (v21 >= 40)
								{
									if (v21 < 60)
										Dest->stEffect[0].cValue = 3;
								}
								else
								{
									Dest->stEffect[0].cValue = 4;
								}
							}
							else
							{
								Dest->stEffect[0].cValue = 5;
							}
						}
						else
						{
							Dest->stEffect[0].cValue = 6;
						}
						break;
					case 7:
						if (v21 >= 4)
						{
							if (v21 >= 10)
							{
								if (v21 >= 20)
								{
									if (v21 >= 35)
									{
										if (v21 < 60)
											Dest->stEffect[0].cValue = 3;
									}
									else
									{
										Dest->stEffect[0].cValue = 4;
									}
								}
								else
								{
									Dest->stEffect[0].cValue = 5;
								}
							}
							else
							{
								Dest->stEffect[0].cValue = 6;
							}
						}
						else
						{
							Dest->stEffect[0].cValue = 7;
						}
						break;
					}
				}
			}
		}
	}

	for (int i = 0; i < 12; ++i)
	{
		int v12 = g_pItemList[ItemId].ReqLvl;
		switch (g_pItemList[ItemId].stEffect[i].sEffect)
		{
		case 0x2B:
			Dest->stEffect[0].cEffect = 43;
			Dest->stEffect[0].cValue = (unsigned char)g_pItemList[ItemId].stEffect[i].sValue;
			break;
		case 0x3D:
			Dest->stEffect[0].cEffect = 61;
			Dest->stEffect[0].cValue = LOBYTE(g_pItemList[ItemId].stEffect[i].sValue);
			break;
		case 0x4E:
			Dest->stEffect[0].cEffect = 78;
			int v11 = rand() % 4 + g_pItemList[ItemId].stEffect[i].sValue;
			if (v11 > 9)
				v11 = 9;
			Dest->stEffect[0].cValue = v11;
			break;
		}
	}
	if (Dest->sIndex == 412 || Dest->sIndex == 413 || Dest->sIndex == 419 || Dest->sIndex == 420 || Dest->sIndex == 753)
	{
		if (!Dest->stEffect[0].cEffect)
		{
			Dest->stEffect[0].cEffect = 59;
			Dest->stEffect[0].cValue = rand();
		}
		if (!Dest->stEffect[1].cEffect)
		{
			Dest->stEffect[1].cEffect = 59;
			Dest->stEffect[01].cValue = rand();
		}
		if (!Dest->stEffect[2].cEffect)
		{
			Dest->stEffect[2].cEffect = 59;
			Dest->stEffect[2].cValue = rand();
		}
	}
	if (Dest->sIndex >= 447 && Dest->sIndex <= 450
		|| Dest->sIndex >= 692 && Dest->sIndex <= 695)
	{
		if (!Dest->stEffect[0].cEffect)
		{
			Dest->stEffect[0].cEffect = 59;
			Dest->stEffect[0].cValue = rand();
		}
		if (!Dest->stEffect[1].cEffect)
		{
			Dest->stEffect[1].cEffect = 59;
			Dest->stEffect[01].cValue = rand();
		}
		if (!Dest->stEffect[2].cEffect)
		{
			Dest->stEffect[2].cEffect = 59;
			Dest->stEffect[2].cValue = rand() % 256;
		}
	}
}

void SetItemBonus2(STRUCT_ITEM *Dest)
{
	int nPos = g_pItemList[Dest->sIndex].nPos;

	if (nPos == 2)//Elmo
	{
		int _rand = rand() % 25;

		if (Dest->stEffect[0].cEffect == EF_SANC)
		{
			int sanc = BASE_GetItemSanc(Dest);

			if (sanc < 6)
			{
				sanc += rand() % 2;

				if (sanc >= 6)
					sanc = 6;

				BASE_SetItemSanc(Dest, sanc, 0);
			}
		}
		else
		{
			Dest->stEffect[0].cEffect = EF_SANC;
			Dest->stEffect[0].cValue = rand() % 2;
		}
		Dest->stEffect[1].cEffect = g_pBonusValue3[_rand][0];
		Dest->stEffect[1].cValue = g_pBonusValue3[_rand][1];

		Dest->stEffect[2].cEffect = g_pBonusValue3[_rand][2];
		Dest->stEffect[2].cValue = g_pBonusValue3[_rand][3];
	}
	//Peito cal�a
	if (nPos == 4 || nPos == 8)
	{
		int _rand = rand() % 48;

		if (Dest->stEffect[0].cEffect == EF_SANC)
		{
			int sanc = BASE_GetItemSanc(Dest);

			if (sanc < 6)
			{
				sanc += rand() % 2;

				if (sanc >= 6)
					sanc = 6;

				BASE_SetItemSanc(Dest, sanc, 0);
			}
		}
		else
		{
			Dest->stEffect[0].cEffect = EF_SANC;
			Dest->stEffect[0].cValue = rand() % 2;
		}

		Dest->stEffect[1].cEffect = g_pBonusValue2[_rand][0];
		Dest->stEffect[1].cValue = g_pBonusValue2[_rand][1];

		Dest->stEffect[2].cEffect = g_pBonusValue2[_rand][2];
		Dest->stEffect[2].cValue = g_pBonusValue2[_rand][3];
	}

	//Luva
	if (nPos == 16)
	{
		int _rand = rand() % 30;

		if (Dest->stEffect[0].cEffect == EF_SANC)
		{
			int sanc = BASE_GetItemSanc(Dest);

			if (sanc < 6)
			{
				sanc += rand() % 2;

				if (sanc >= 6)
					sanc = 6;

				BASE_SetItemSanc(Dest, sanc, 0);
			}
		}
		else
		{
			Dest->stEffect[0].cEffect = EF_SANC;
			Dest->stEffect[0].cValue = rand() % 2;
		}

		Dest->stEffect[1].cEffect = g_pBonusValue4[_rand][0];
		Dest->stEffect[1].cValue = g_pBonusValue4[_rand][1];

		Dest->stEffect[2].cEffect = g_pBonusValue4[_rand][2];
		Dest->stEffect[2].cValue = g_pBonusValue4[_rand][3];
	}

	//Bota
	if (nPos == 32)
	{
		int _rand = rand() % 30;

		if (Dest->stEffect[0].cEffect == EF_SANC)
		{
			int sanc = BASE_GetItemSanc(Dest);

			if (sanc < 6)
			{
				sanc += rand() % 2;

				if (sanc >= 6)
					sanc = 6;

				BASE_SetItemSanc(Dest, sanc, 0);
			}
		}
		else
		{
			Dest->stEffect[0].cEffect = EF_SANC;
			Dest->stEffect[0].cValue = rand() % 2;
		}

		Dest->stEffect[1].cEffect = g_pBonusValue5[_rand][0];
		Dest->stEffect[1].cValue = g_pBonusValue5[_rand][1];

		Dest->stEffect[2].cEffect = g_pBonusValue5[_rand][2];
		Dest->stEffect[2].cValue = g_pBonusValue5[_rand][3];
	}
}

/*void SetItemBonus2(STRUCT_ITEM *Dest)
{
	int chance = rand()%100;

	int nPos = g_pItemList[Dest->sIndex].nPos;

	if (nPos == 2)//Elmo
	{
		int _rand = rand() % 25;

		if (Dest->stEffect[0].cEffect == EF_SANC)
		{
			int sanc = BASE_GetItemSanc(Dest);

			if (sanc < 6)
			{
				sanc += rand() % 2;

				if (sanc >= 6)
					sanc = 6;

				BASE_SetItemSanc(Dest, sanc, 0);
			}
		}
		else
		{
			Dest->stEffect[0].cEffect = EF_SANC;
			Dest->stEffect[0].cValue = rand() % 2;
		}
		Dest->stEffect[1].cEffect = g_pBonusValue3[_rand][0];
		Dest->stEffect[1].cValue = g_pBonusValue3[_rand][1];

		Dest->stEffect[2].cEffect = g_pBonusValue3[_rand][2];
		Dest->stEffect[2].cValue = g_pBonusValue3[_rand][3];
	}


	//Peito cal�a
	if(nPos == 4 || nPos == 8)
	{
		if(Dest->stEffect[0].cEffect == EF_SANC)
		{
			int sanc = BASE_GetItemSanc(Dest);

			if (sanc < 6)
			{
				sanc += rand() % 2;

				if (sanc >= 6)
					sanc = 6;

				BASE_SetItemSanc(Dest, sanc, 0);
			}
		}
		else
		{
			Dest->stEffect[0].cEffect = EF_SANC;
			Dest->stEffect[0].cValue = rand()%2;
		}

		if(chance < 5)
		{
			Dest->stEffect[1].cEffect = 3;
			Dest->stEffect[1].cValue = 15;
			Dest->stEffect[2].cEffect = 71;
			Dest->stEffect[2].cValue = 60;
		}
		else if(chance >= 5 && chance < 10)
		{
			Dest->stEffect[1].cEffect = 71;
			Dest->stEffect[1].cValue = 60;
			Dest->stEffect[2].cEffect = 60;
			Dest->stEffect[2].cValue = 10;
		}
		else if(chance >= 10 && chance < 15)
		{
			Dest->stEffect[1].cEffect = 2;
			Dest->stEffect[1].cValue = 24;
			Dest->stEffect[2].cEffect = 3;
			Dest->stEffect[2].cValue = 25;
		}
		else if(chance >= 15 && chance < 18)//dificil
		{
			Dest->stEffect[1].cEffect = 3;
			Dest->stEffect[1].cValue = 30;
			Dest->stEffect[2].cEffect = 60;
			Dest->stEffect[2].cValue = 10;
		}
		else if(chance >= 18 && chance < 23)
		{
			Dest->stEffect[1].cEffect = 2;
			Dest->stEffect[1].cValue = 24;
			Dest->stEffect[2].cEffect = 60;
			Dest->stEffect[2].cValue = 6;
		}
		else if(chance >= 23 && chance < 28)
		{
			Dest->stEffect[1].cEffect = 2;
			Dest->stEffect[1].cValue = 18;
			Dest->stEffect[2].cEffect = 60;
			Dest->stEffect[2].cValue = 6;
		}
		else if(chance >= 28 && chance < 33)
		{
			Dest->stEffect[1].cEffect = 2;
			Dest->stEffect[1].cValue = 24;
			Dest->stEffect[2].cEffect = 3;
			Dest->stEffect[2].cValue = 30;
		}
		else if(chance >= 33 && chance < 38)
		{
			Dest->stEffect[1].cEffect = 3;
			Dest->stEffect[1].cValue = 40;
			Dest->stEffect[2].cEffect = 0;
			Dest->stEffect[2].cValue = 0;
		}
		else if(chance >= 38 && chance < 41)//dificil
		{
			Dest->stEffect[1].cEffect = 3;
			Dest->stEffect[1].cValue = 30;
			Dest->stEffect[2].cEffect = 71;
			Dest->stEffect[2].cValue = 70;
		}
		else if(chance >= 41 && chance < 44)//dificil
		{
			Dest->stEffect[1].cEffect = 2;
			Dest->stEffect[1].cValue = 30;
			Dest->stEffect[2].cEffect = 3;
			Dest->stEffect[2].cValue = 30;
		}
		else if(chance >= 44 && chance < 49)
		{
			Dest->stEffect[1].cEffect = 71;
			Dest->stEffect[1].cValue = 60;
			Dest->stEffect[2].cEffect = 60;
			Dest->stEffect[2].cValue = 8;
		}
		else if(chance >= 49 && chance < 54)
		{
			Dest->stEffect[1].cEffect = 3;
			Dest->stEffect[1].cValue = 25;
			Dest->stEffect[2].cEffect = 60;
			Dest->stEffect[2].cValue = 8;
		}
		else if(chance >= 54 && chance < 59)
		{
			Dest->stEffect[1].cEffect = 3;
			Dest->stEffect[1].cValue = 25;
			Dest->stEffect[2].cEffect = 60;
			Dest->stEffect[2].cValue = 6;
		}
		else if(chance >= 59 && chance < 62)//dificl
		{
			Dest->stEffect[1].cEffect = 2;
			Dest->stEffect[1].cValue = 30;
			Dest->stEffect[2].cEffect = 71;
			Dest->stEffect[2].cValue = 70;
		}
		else if(chance >= 62 && chance < 67)
		{
			Dest->stEffect[1].cEffect = 3;
			Dest->stEffect[1].cValue = 25;
			Dest->stEffect[2].cEffect = 60;
			Dest->stEffect[2].cValue = 6;
		}
		else if(chance >= 67 && chance < 71)
		{
			Dest->stEffect[1].cEffect = 71;
			Dest->stEffect[1].cValue = 60;
			Dest->stEffect[2].cEffect = 60;
			Dest->stEffect[2].cValue = 6;
		}
		else if(chance >= 71 && chance < 76)
		{
			Dest->stEffect[1].cEffect = 3;
			Dest->stEffect[1].cValue = 50;
			Dest->stEffect[2].cEffect = 0;
			Dest->stEffect[2].cValue = 0;
		}
		else if(chance >= 76 && chance < 81)
		{
			Dest->stEffect[1].cEffect = 2;
			Dest->stEffect[1].cValue = 18;
			Dest->stEffect[2].cEffect = 71;
			Dest->stEffect[2].cValue = 70;
		}
		else if(chance >= 81 && chance < 86)
		{
			Dest->stEffect[1].cEffect = 3;
			Dest->stEffect[1].cValue = 20;
			Dest->stEffect[2].cEffect = 71;
			Dest->stEffect[2].cValue = 60;
		}
		else if(chance >= 86 && chance < 91)
		{
			Dest->stEffect[1].cEffect = 71;
			Dest->stEffect[1].cValue = 60;
			Dest->stEffect[2].cEffect = 60;
			Dest->stEffect[2].cValue = 10;
		}
		else if(chance >= 91 && chance < 96)
		{
			Dest->stEffect[1].cEffect = 3;
			Dest->stEffect[1].cValue = 30;
			Dest->stEffect[2].cEffect = 60;
			Dest->stEffect[2].cValue = 8;
		}
		else if(chance > 96)//dificil
		{
			Dest->stEffect[1].cEffect = 71;
			Dest->stEffect[1].cValue = 70;
			Dest->stEffect[2].cEffect = 60;
			Dest->stEffect[2].cValue = 10;
		}
	}

	//Luva
	if (nPos == 16)
	{
		int _rand = rand() % 30;

		if (Dest->stEffect[0].cEffect == EF_SANC)
		{
			int sanc = BASE_GetItemSanc(Dest);

			if (sanc < 6)
			{
				sanc += rand() % 2;

				if (sanc >= 6)
					sanc = 6;

				BASE_SetItemSanc(Dest, sanc, 0);
			}
		}
		else
		{
			Dest->stEffect[0].cEffect = EF_SANC;
			Dest->stEffect[0].cValue = rand() % 2;
		}

		Dest->stEffect[1].cEffect = g_pBonusValue4[_rand][0];
		Dest->stEffect[1].cValue = g_pBonusValue4[_rand][1];

		Dest->stEffect[2].cEffect = g_pBonusValue4[_rand][2];
		Dest->stEffect[2].cValue = g_pBonusValue4[_rand][3];
	}
	//Bota
	if(nPos == 32)
	{
		if (Dest->stEffect[0].cEffect == EF_SANC)
		{
			int sanc = BASE_GetItemSanc(Dest);

			if (sanc < 6)
			{
				sanc += rand() % 2;

				if (sanc >= 6)
					sanc = 6;

				BASE_SetItemSanc(Dest, sanc, 0);
			}
		}
		else
		{
			Dest->stEffect[0].cEffect = EF_SANC;
			Dest->stEffect[0].cValue = rand()%2;
		}
		if (chance < 2)
		{
			Dest->stEffect[1].cEffect = 2;
			Dest->stEffect[1].cValue = 6;
			Dest->stEffect[2].cEffect = 60;
			Dest->stEffect[2].cValue = 8;
		}
		else if(chance >= 2 && chance < 10)
		{
			Dest->stEffect[1].cEffect = 2;
			Dest->stEffect[1].cValue = 0;
			Dest->stEffect[2].cEffect = 60;
			Dest->stEffect[2].cValue = 8;
		}
		else if(chance >= 10 && chance < 15)
		{
			Dest->stEffect[1].cEffect = 2;
			Dest->stEffect[1].cValue = 0;
			Dest->stEffect[2].cEffect = 74;
			Dest->stEffect[2].cValue = 15;
		}
		else if(chance >= 15 && chance < 18)//dificil
		{
			Dest->stEffect[1].cEffect = 2;
			Dest->stEffect[1].cValue = 0;
			Dest->stEffect[2].cEffect = 0;
			Dest->stEffect[2].cValue = 0;
		}
		else if(chance >= 18 && chance < 23)
		{
			Dest->stEffect[1].cEffect = 2;
			Dest->stEffect[1].cValue = 0;
			Dest->stEffect[2].cEffect = 74;
			Dest->stEffect[2].cValue = 12;
		}
		else if(chance >= 23 && chance < 24)
		{
			Dest->stEffect[1].cEffect = 2;
			Dest->stEffect[1].cValue = 6;
			Dest->stEffect[2].cEffect = 0;
			Dest->stEffect[2].cValue = 0;
		}
		else if(chance >= 24 && chance < 33)
		{
			Dest->stEffect[1].cEffect = 2;
			Dest->stEffect[1].cValue = 0;
			Dest->stEffect[2].cEffect = 74;
			Dest->stEffect[2].cValue = 12;
		}
		else if(chance >= 33 && chance < 38)
		{
			Dest->stEffect[1].cEffect = 2;
			Dest->stEffect[1].cValue = 0;
			Dest->stEffect[2].cEffect = 60;
			Dest->stEffect[2].cValue = 6;
		}
		else if(chance >= 38 && chance < 39)//dificil
		{
			Dest->stEffect[1].cEffect = 2;
			Dest->stEffect[1].cValue = 6;
			Dest->stEffect[2].cEffect = 60;
			Dest->stEffect[2].cValue = 10;
		}
		else if(chance >= 39 && chance < 40)//dificil
		{
			Dest->stEffect[1].cEffect = 2;
			Dest->stEffect[1].cValue = 6;
			Dest->stEffect[2].cEffect = 74;
			Dest->stEffect[2].cValue = 18;
		}
		else if(chance >= 41 && chance < 44)
		{
			Dest->stEffect[1].cEffect = 2;
			Dest->stEffect[1].cValue = 6;
			Dest->stEffect[2].cEffect = 74;
			Dest->stEffect[2].cValue = 12;
		}
		else if(chance >= 44 && chance < 49)
		{
			Dest->stEffect[1].cEffect = 2;
			Dest->stEffect[1].cValue = 0;
			Dest->stEffect[2].cEffect = 60;
			Dest->stEffect[2].cValue = 10;
		}
		else if(chance >= 49 && chance < 55)
		{
			Dest->stEffect[1].cEffect = 74;
			Dest->stEffect[1].cValue = 18;
			Dest->stEffect[2].cEffect = 0;
			Dest->stEffect[2].cValue = 0;
		}
		else if(chance >= 55 && chance < 56)//dificl
		{
			Dest->stEffect[1].cEffect = 2;
			Dest->stEffect[1].cValue = 6;
			Dest->stEffect[2].cEffect = 74;
			Dest->stEffect[2].cValue = 18;
		}
		else if(chance >= 56 && chance < 67)
		{
			Dest->stEffect[1].cEffect = 74;
			Dest->stEffect[1].cValue = 15;
			Dest->stEffect[2].cEffect = 0;
			Dest->stEffect[2].cValue = 0;
		}
		else if(chance >= 67 && chance < 71)
		{
			Dest->stEffect[1].cEffect = 60;
			Dest->stEffect[1].cValue = 10;
			Dest->stEffect[2].cEffect = 0;
			Dest->stEffect[2].cValue = 0;
		}
		else if(chance >= 71 && chance < 76)
		{
			Dest->stEffect[1].cEffect = 2;
			Dest->stEffect[1].cValue = 6;
			Dest->stEffect[2].cEffect = 60;
			Dest->stEffect[2].cValue = 6;
		}
		else if(chance >= 76 && chance < 81)
		{
			Dest->stEffect[1].cEffect = 2;
			Dest->stEffect[1].cValue = 0;
			Dest->stEffect[2].cEffect = 60;
			Dest->stEffect[2].cValue = 6;
		}
		else if(chance >= 81 && chance < 86)
		{
			Dest->stEffect[1].cEffect = 2;
			Dest->stEffect[1].cValue = 0;
			Dest->stEffect[2].cEffect = 74;
			Dest->stEffect[2].cValue = 12;
		}
		else if(chance >= 86 && chance < 91)
		{
			Dest->stEffect[1].cEffect = 2;
			Dest->stEffect[1].cValue = 0;
			Dest->stEffect[2].cEffect = 60;
			Dest->stEffect[2].cValue = 6;
		}
		else if(chance >= 91 && chance < 96)
		{
			Dest->stEffect[1].cEffect = 74;
			Dest->stEffect[1].cValue = 18;
			Dest->stEffect[2].cEffect = 0;
			Dest->stEffect[2].cValue = 0;
		}
		else if(chance > 96)
		{
			Dest->stEffect[1].cEffect = 74;
			Dest->stEffect[1].cValue = 12;
			Dest->stEffect[2].cEffect = 0;
			Dest->stEffect[2].cValue = 0;
		}
	}
}*/

int Challange(int conn, int mob, int coin)
{
	if (mob < MAX_USER || mob >= MAX_MOB)
		return 0;

	int ZoneChall = pMob[mob].MOB.BaseScore.Level;
	int Guild = pMob[conn].MOB.Guild;

	if (ZoneChall < 0 || ZoneChall >= ValidGuild)
		return 0;

	if (ZoneChall == 4)
		return 0;


	if (pMob[conn].MOB.GuildLevel != 9)
	{
		SendSay(mob, g_pMessageStringTable[_NN_Only_Guild_Master_can]);

		return 0;
	}

	if (g_pGuildZone[ZoneChall].ChargeGuild == Guild)
	{
		SendSay(mob, g_pMessageStringTable[_NN_Champions_Cant_Challange]);

		return 0;
	}
	if (pMob[conn].extra.Citizen != (ServerIndex + 1))
	{
		SendSay(mob, g_pMessageStringTable[_DN_ANOTHER_TOWNSPEOPLE]);
		return 0;
	}

	int Group = ServerGroup;
	int Server = Guild / MAX_GUILD;
	int usGuild = Guild & MAX_GUILD - 1;

	int GuildName = 1;

	if (Group >= 0 && Group < MAX_SERVERGROUP && Server >= 0 && Server < 16 && usGuild >= 0 && usGuild < MAX_GUILD && g_pGuildName[Group][Server][usGuild][0] == 0)
		GuildName = 0;


	if (GuildName == 0)
	{
		SendSay(mob, g_pMessageStringTable[_NN_Only_Named_Guild]);

		return 0;
	}

	if (GuildInfo[Guild].Fame < 100)
	{
		sprintf_s(temp, g_pMessageStringTable[_DN_Need_1000000_For_Challange], 100);
		SendSay(mob, temp);

		return 0;
	}

	MSG_GuildInfo sm;
	memset(&sm, 0, sizeof(MSG_GuildInfo));

	sm.Type = _MSG_GuildInfo;
	sm.Size = sizeof(MSG_GuildInfo);
	sm.ID = conn;

	sm.Guild = Guild;

	coin = GuildInfo[Guild].Fame;

	GuildInfo[Guild].Fame -= 100;

	sm.GuildInfo = GuildInfo[Guild];

	auto& pc = cSQL::instance();
	sprintf(xQuery, "UPDATE `guilds` SET fame = '%d' WHERE `guild` = '%d'", GuildInfo[usGuild].Fame - 100, usGuild);
	pc.wQuery(xQuery);

	DBServerSocket.SendOneMessage((char*)&sm, sizeof(MSG_GuildInfo));
	 
	SendMsgExp(conn, g_pMessageStringTable[_NN_Challanged], TNColor::Default, false);

	//sprintf(temp, "etc,challange guild:%d fame:%d zone:%d", Guild, coin, ZoneChall);
	//Log(temp, pMob[conn].MOB.MobName, 0);

	if (pChallangerMoney[ZoneChall] < coin)
	{
		g_pGuildZone[ZoneChall].ChallangeGuild = Guild;
		pChallangerMoney[ZoneChall] = coin;

		CReadFiles::WriteChallanger();
		CReadFiles::WriteGuild();
	}

	return 1;
}
 
//int GenerateEvocation(int conn, int SummonID, STRUCT_ITEM* sItem, int Num)
//{
//	int Leader = pMob[conn].Leader;
//
//	if (Leader <= 0)
//		Leader = conn;
//
//	int MobEmpty = GetEmptyNPCMob();
//
//	if (MobEmpty == 0)
//	{
//		SendClientMessage(conn, g_pMessageStringTable[_NN_Cant_Create_More_Summons]);
//
//		return 0;
//	}
//
//	if (SummonID < 0 || SummonID >= MAX_SUMMONLIST)
//		return 0;
//
//	int sFace = mSummon.Mob[SummonID].Equip[0].sIndex;
//	int Unk = 0;
//	int SummonNum = 0;
//
//	int IsSummonOther = 0;
//
//	for (int i = 0; i < MAX_PARTY; i++)
//	{
//		int partyconn = pMob[Leader].Evocations[i];
//
//		if (partyconn == 0)
//			continue;
//
//		if (partyconn <= 0 || partyconn >= MAX_MOB)
//			continue;
//
//		for (int k = 0; k < MAX_SUMMONLIST; k++)
//		{
//			if (pMob[partyconn].MOB.Equip[0].sIndex == mSummon.Mob[k].Equip[0].sIndex && mSummon.Mob[k].Equip[0].sIndex != sFace)
//			{
//				return 0;
//			}
//		}
//
//		if (pMob[partyconn].MOB.Equip[0].sIndex != sFace || SummonID >= MAX_SUMMONLIST)
//			continue;
//
//		int posX = pMob[conn].TargetX;
//		int posY = pMob[conn].TargetY;
//		SummonNum++;
//		if (GetEmptyMobGrid(partyconn, &posX, &posY) != 0 && GetInView(conn, partyconn) == FALSE)
//		{
//			MSG_Action sm;
//			memset(&sm, 0, sizeof(MSG_Action));
//
//			GetAction(partyconn, posX, posY, &sm);
//
//			sm.Effect = 8;
//			sm.Speed = 6;
//
//			GridMulticast(partyconn, posX, posY, (MSG_STANDARD*)&sm);
//
//			if (SummonNum >= Num)
//				return 0;
//			else
//				continue;
//		}
//		else if (SummonNum >= Num)
//			return 0;
//	}
//	for (int i = SummonNum; i < Num; i++)
//	{
//		MobEmpty = GetEmptyNPCMob();
//
//		if (MobEmpty == 0)
//		{
//			SendClientMessage(conn, g_pMessageStringTable[_NN_Cant_Create_More_Summons]);
//
//			return 0;
//		}
//		int j = 0;
//
//		for (j = 0; j < MAX_PARTY; j++)
//		{
//			if (pMob[Leader].Evocations[j])
//				continue;
//
//			else
//				break;
//		}
//
//		if (j >= MAX_PARTY)
//		{
//			SendClientMessage(conn, g_pMessageStringTable[_NN_Party_Full_Cant_Summon]);
//			return 0;
//		}
//
//		memset(pMob[MobEmpty].Evocations, 0, sizeof(pMob[MobEmpty].Evocations));
//		memcpy(&pMob[MobEmpty], &mSummon.Mob[SummonID], sizeof(mSummon.Mob[SummonID]));
//
//		pMob[MobEmpty].MOB.BaseScore.Level = pMob[conn].MOB.BaseScore.Level <= MAX_LEVEL ? pMob[conn].MOB.BaseScore.Level : MAX_LEVEL;
//
//		strcat(pMob[MobEmpty].MOB.MobName, "^");
//
//		for (int k = 0; k < NAME_LENGTH; k++)
//		{
//			if (pMob[MobEmpty].MOB.MobName[k] == '_')
//				pMob[MobEmpty].MOB.MobName[k] = ' ';
//		}
//
//		memset(pMob[MobEmpty].Affect, 0, sizeof(pMob[MobEmpty].Affect));
//
//		int Con = pMob[conn].MOB.CurrentScore.Con;
//		int Evocacao = pMob[conn].MOB.CurrentScore.Special[2];
//
//		int sBase = Con * pSummonBonus[SummonID].Unk / 100;
//		int sMax = Evocacao * pSummonBonus[SummonID].Unk2 / 100;
//
//		pMob[MobEmpty].MOB.BaseScore.Damage += sMax + sBase;
//
//		sBase = Con * pSummonBonus[SummonID].Unk3 / 100;
//		sMax = Evocacao * pSummonBonus[SummonID].Unk4 / 100;
//
//		pMob[MobEmpty].MOB.BaseScore.Ac += sMax + sBase;
//
//		sBase = Con * pSummonBonus[SummonID].Unk5 / 100;
//		sMax = Evocacao * pSummonBonus[SummonID].Unk6 / 100;
//
//		pMob[MobEmpty].MOB.BaseScore.MaxHp += sMax + sBase;
//
//		pMob[MobEmpty].MOB.CurrentScore.MaxHp = pMob[MobEmpty].MOB.BaseScore.MaxHp;
//
//		pMob[MobEmpty].GenerateIndex = -1;
//
//		pMob[MobEmpty].Formation = 5;
//
//		pMob[MobEmpty].RouteType = 5;
//		pMob[MobEmpty].Mode = MOB_PEACE;
//
//		//	*(int*)&pMob[MobEmpty].Unk6[64] = 0;
//		//	*(int*)&pMob[MobEmpty].Unk6[60] = 0;
//
//		pMob[MobEmpty].SegmentProgress = 0;
//		pMob[MobEmpty].SegmentDirection = 0;
//
//		memset(&pMob[MobEmpty].SegmentX, 0, sizeof(pMob[MobEmpty].SegmentX));
//		memset(&pMob[MobEmpty].SegmentY, 0, sizeof(pMob[MobEmpty].SegmentY));
//
//		//	memset(pMob[MobEmpty].Unk6, 0, 20);
//		//	memset(&pMob[MobEmpty].Unk6[20], 0, 20);
//
//		pMob[MobEmpty].Leader = Leader;
//		pMob[MobEmpty].LastTime = CurrentTime;
//
//		if (sItem != 0)
//		{
//			int mountsanc = BASE_GetItemAbility(sItem, EF_MOUNTSANC);
//
//			if (mountsanc >= 100)
//				mountsanc = 100;
//
//			int face = pMob[MobEmpty].MOB.Equip[0].sIndex;
//			int con = 0;
//
//			if (face >= 315 && face < 345)
//			{
//				int mcon = /*0x4C7974[face]*/0; // Voltar e identificar essa var
//				int mUnk = mcon / 2 - 1000;
//				int mUnk2 = mcon - mUnk;
//
//				con = mountsanc * (mcon - mUnk) / 100 + mcon / 2 - 1000;
//			}
//
//			pMob[MobEmpty].MOB.BaseScore.Con = con;
//			pMob[MobEmpty].MOB.CurrentScore.Con = con;
//
//			pMob[MobEmpty].MOB.BaseScore.Damage += 6 * BASE_GetItemAbility(sItem, EF_MOUNTSANC);
//			pMob[MobEmpty].MOB.CurrentScore.Damage = pMob[MobEmpty].MOB.BaseScore.Damage;
//		}
//
//		if (pMob[conn].GuildDisable == 0)
//		{
//			pMob[MobEmpty].MOB.Guild = pMob[MobEmpty].MOB.Guild;
//			pMob[MobEmpty].MOB.GuildLevel = 0;
//		}
//
//		GetGuild(MobEmpty);
//
//
//		pMob[MobEmpty].MOB.CurrentScore.Hp = pMob[MobEmpty].MOB.CurrentScore.MaxHp;
//
//		if (pMob[conn].MOB.Equip[15].sIndex == 543 || pMob[conn].MOB.Equip[15].sIndex == 545)
//		{
//			memset(&pMob[MobEmpty].MOB.Equip[15], 0, sizeof(STRUCT_ITEM));
//			pMob[MobEmpty].MOB.Equip[15].sIndex = 734;
//		}
//
//		if (pMob[conn].MOB.Equip[15].sIndex == 544 || pMob[conn].MOB.Equip[15].sIndex == 546)
//		{
//			memset(&pMob[MobEmpty].MOB.Equip[15], 0, sizeof(STRUCT_ITEM));
//			pMob[MobEmpty].MOB.Equip[15].sIndex = 735;
//		}
//
//		if (pMob[conn].MOB.Equip[15].sIndex == 548 || pMob[conn].MOB.Equip[15].sIndex == 549)
//		{
//			memset(&pMob[MobEmpty].MOB.Equip[15], 0, sizeof(STRUCT_ITEM));
//			pMob[MobEmpty].MOB.Equip[15].sIndex = 550;
//		}
//
//		pMob[MobEmpty].MOB.Clan = 4;
//
//		pMob[MobEmpty].GetCurrentScore(MAX_USER);
//
//		memset(pMob[MobEmpty].EnemyList, 0, sizeof(pMob[MobEmpty].EnemyList));
//
//		int posX = pMob[conn].TargetX;
//		int posY = pMob[conn].TargetY;
//
//		int tmob = GetEmptyMobGrid(MobEmpty, &posX, &posY);
//
//		if (tmob == 0)
//		{
//			pMob[MobEmpty].Mode = MOB_EMPTY;
//
//			return 0;
//		}
//
//		pMob[MobEmpty].TargetX = posX;
//		pMob[MobEmpty].LastX = posX;
//		pMob[MobEmpty].TargetY = posY;
//		pMob[MobEmpty].LastY = posY;
//
//		if (sItem == 0)
//		{
//			pMob[MobEmpty].Affect[0].Type = 24;
//			pMob[MobEmpty].Affect[0].Value = 0;
//			pMob[MobEmpty].Affect[0].Level = 0;
//			pMob[MobEmpty].Affect[0].Time = 20;
//
//			if (SummonID >= 28 && SummonID <= 37)
//				pMob[MobEmpty].Affect[0].Time = 2000000000;
//		}
//
//		if (sItem != 0)
//		{
//			if (sItem->stEffect[0].sValue > pMob[MobEmpty].MOB.CurrentScore.MaxHp)
//				sItem->stEffect[0].sValue = pMob[MobEmpty].MOB.CurrentScore.MaxHp;
//
//			pMob[MobEmpty].MOB.BaseScore.Hp = sItem->stEffect[0].sValue;
//			pMob[MobEmpty].MOB.CurrentScore.Hp = pMob[MobEmpty].MOB.BaseScore.Hp;
//		}
//		MSG_CreateMob sm;
//		memset(&sm, 0, sizeof(MSG_CreateMob));
//
//		GetCreateMob(MobEmpty, &sm);
//
//		sm.CreateType |= 3u;
//		pMobGrid[posY][posX] = MobEmpty;
//
//		GridMulticast(posX, posY, (MSG_STANDARD*)&sm, 0);
//
//		pMob[Leader].Evocations[j] = MobEmpty;
//		pMob[MobEmpty].Leader = Leader;
//
//		/*if (SummonNum == 0)
//			SendAddParty(Leader, Leader, 0);
//
//		SendAddParty(MobEmpty, Leader, 0);
//
//		if (SummonNum == 0)
//			SendAddParty(MobEmpty, MobEmpty, j + 1);
//
//		SendAddParty(Leader, MobEmpty, j + 1);*/
//
//		if (SummonNum == 0)
//			SendAddPartyEvocation(Leader);
//		if (SummonNum == 0)
//			 SendAddPartyEvocation(MobEmpty);
//		for (int l = 0; l < MAX_PARTY; l++)
//		{
//			if (pMob[Leader].Evocations[l] == 0)
//				continue;
//
//			if (pMob[Leader].Evocations[l] != MobEmpty)
//				SendAddPartyEvocation(pMob[Leader].Evocations[l]), SendAddPartyEvocation(MobEmpty);
//
//		}
//
//		pMob[MobEmpty].Summoner = conn;
//	}
//	return 1;
//}

int GenerateSummon(int conn, int SummonID, STRUCT_ITEM* sItem, int Num)
{
	int Leader = pMob[conn].Leader;

	if (Leader <= 0)
		Leader = conn;

	int MobEmpty = GetEmptyNPCMob();

	if (MobEmpty == 0)
	{
		SendClientMessage(conn, g_pMessageStringTable[_NN_Cant_Create_More_Summons]);

		return 0;
	}

	if (SummonID < 0 || SummonID >= MAX_SUMMONLIST)
		return 0;

	int sFace = mSummon.Mob[SummonID].Equip[0].sIndex;
	int Unk = 0;
	int SummonNum = 0;

	int IsSummonOther = 0;

	for (int i = 0; i < MAX_PARTY; i++)
	{
		int partyconn = pMob[Leader].PartyList[i];

		if (partyconn == 0)
			continue;

		if (partyconn <= 0 || partyconn >= MAX_MOB)
			continue;

		for (int k = 0; k < MAX_SUMMONLIST; k++)
		{
			if (pMob[partyconn].MOB.Equip[0].sIndex == mSummon.Mob[k].Equip[0].sIndex && mSummon.Mob[k].Equip[0].sIndex != sFace)
			{
				return 0;
			}
		}

		if (pMob[partyconn].MOB.Equip[0].sIndex != sFace || SummonID >= MAX_SUMMONLIST)
			continue;

		int posX = pMob[conn].TargetX;
		int posY = pMob[conn].TargetY;

		SummonNum++;


		if (GetEmptyMobGrid(partyconn, &posX, &posY) != 0 && GetInView(conn, partyconn) == FALSE)
		{
			MSG_Action sm;
			memset(&sm, 0, sizeof(MSG_Action));

			GetAction(partyconn, posX, posY, &sm);

			sm.Effect = 8;
			sm.Speed = 6;

			GridMulticast(partyconn, posX, posY, (MSG_STANDARD*)&sm);

			if (SummonNum >= Num)
				return 0;
			else
				continue;
		}
		else if (SummonNum >= Num)
			return 0;
	}
	for (int i = SummonNum; i < Num; i++)
	{
		MobEmpty = GetEmptyNPCMob();

		if (MobEmpty == 0)
		{
			SendClientMessage(conn, g_pMessageStringTable[_NN_Cant_Create_More_Summons]);

			return 0;
		}
		int j = 0;

		for (j = 0; j < MAX_PARTY; j++)
		{
			if (pMob[Leader].PartyList[j])
				continue;

			else
				break;
		}

		if (j >= MAX_PARTY)
		{
			SendClientMessage(conn, g_pMessageStringTable[_NN_Party_Full_Cant_Summon]);

			return 0;
		}

		memset(pMob[MobEmpty].PartyList, 0, sizeof(pMob[MobEmpty].PartyList));
		memcpy(&pMob[MobEmpty], &mSummon.Mob[SummonID], sizeof(mSummon.Mob[SummonID]));

		pMob[MobEmpty].MOB.BaseScore.Level = pMob[conn].MOB.BaseScore.Level <= MAX_LEVEL ? pMob[conn].MOB.BaseScore.Level : MAX_LEVEL;

		strcat(pMob[MobEmpty].MOB.MobName, "^");

		for (int k = 0; k < NAME_LENGTH; k++)
		{
			if (pMob[MobEmpty].MOB.MobName[k] == '_')
				pMob[MobEmpty].MOB.MobName[k] = ' ';
		}

		memset(pMob[MobEmpty].Affect, 0, sizeof(pMob[MobEmpty].Affect));

		int Int = pMob[conn].MOB.CurrentScore.Int;
		int Con = pMob[conn].MOB.CurrentScore.Con;
		int Evocacao = pMob[conn].MOB.CurrentScore.Special[2];

		int sBase = (Con + Int) * pSummonBonus[SummonID].Unk / 60;
		int sMax = Evocacao * pSummonBonus[SummonID].Unk2 / 60;

		pMob[MobEmpty].MOB.BaseScore.Damage += sMax + sBase;

		sBase = (Con + Int) * pSummonBonus[SummonID].Unk3 / 100;
		sMax = Evocacao * pSummonBonus[SummonID].Unk4 / 100;

		pMob[MobEmpty].MOB.BaseScore.Ac += sMax + sBase;

		sBase = (Con + Int) * pSummonBonus[SummonID].Unk5 / 70;
		sMax = Evocacao * pSummonBonus[SummonID].Unk6 / 70;

		pMob[MobEmpty].MOB.BaseScore.MaxHp += sMax + sBase;

		pMob[MobEmpty].MOB.CurrentScore.MaxHp = pMob[MobEmpty].MOB.BaseScore.MaxHp;

		pMob[MobEmpty].GenerateIndex = -1;

		pMob[MobEmpty].Formation = 5;

		pMob[MobEmpty].RouteType = 5;
		pMob[MobEmpty].Mode = MOB_PEACE;

		//	*(int*)&pMob[MobEmpty].Unk6[64] = 0;
		//	*(int*)&pMob[MobEmpty].Unk6[60] = 0;

		pMob[MobEmpty].SegmentProgress = 0;
		pMob[MobEmpty].SegmentDirection = 0;

		memset(&pMob[MobEmpty].SegmentX, 0, sizeof(pMob[MobEmpty].SegmentX));
		memset(&pMob[MobEmpty].SegmentY, 0, sizeof(pMob[MobEmpty].SegmentY));

		//	memset(pMob[MobEmpty].Unk6, 0, 20);
		//	memset(&pMob[MobEmpty].Unk6[20], 0, 20);

		pMob[MobEmpty].Leader = Leader;
		pMob[MobEmpty].LastTime = CurrentTime;

		if (sItem != 0)
		{
			int mountsanc = BASE_GetItemAbility(sItem, EF_MOUNTSANC);

			if (mountsanc >= 100)
				mountsanc = 100;

			int face = pMob[MobEmpty].MOB.Equip[0].sIndex;
			int con = 0;

			if (face >= 315 && face < 345)
			{
				int mcon = /*0x4C7974[face]*/0; // Voltar e identificar essa var
				int mUnk = mcon / 2 - 1000;
				int mUnk2 = mcon - mUnk;

				con = mountsanc * (mcon - mUnk) / 100 + mcon / 2 - 1000;
			}

			pMob[MobEmpty].MOB.BaseScore.Con = con;
			pMob[MobEmpty].MOB.CurrentScore.Con = con;

			pMob[MobEmpty].MOB.BaseScore.Damage += 6 * BASE_GetItemAbility(sItem, EF_MOUNTSANC);
			pMob[MobEmpty].MOB.CurrentScore.Damage = pMob[MobEmpty].MOB.BaseScore.Damage;
		}

		if (pMob[conn].GuildDisable == 0)
		{
			pMob[MobEmpty].MOB.Guild = pMob[MobEmpty].MOB.Guild;
			pMob[MobEmpty].MOB.GuildLevel = 0;
		}

		GetGuild(MobEmpty);


		pMob[MobEmpty].MOB.CurrentScore.Hp = pMob[MobEmpty].MOB.CurrentScore.MaxHp;

		if (pMob[conn].MOB.Equip[15].sIndex == 543 || pMob[conn].MOB.Equip[15].sIndex == 545)
		{
			memset(&pMob[MobEmpty].MOB.Equip[15], 0, sizeof(STRUCT_ITEM));
			pMob[MobEmpty].MOB.Equip[15].sIndex = 734;
		}

		if (pMob[conn].MOB.Equip[15].sIndex == 544 || pMob[conn].MOB.Equip[15].sIndex == 546)
		{
			memset(&pMob[MobEmpty].MOB.Equip[15], 0, sizeof(STRUCT_ITEM));
			pMob[MobEmpty].MOB.Equip[15].sIndex = 735;
		}

		if (pMob[conn].MOB.Equip[15].sIndex == 548 || pMob[conn].MOB.Equip[15].sIndex == 549)
		{
			memset(&pMob[MobEmpty].MOB.Equip[15], 0, sizeof(STRUCT_ITEM));
			pMob[MobEmpty].MOB.Equip[15].sIndex = 550;
		}

		pMob[MobEmpty].MOB.Clan = 4;

		pMob[MobEmpty].GetCurrentScore(MAX_USER);

		memset(pMob[MobEmpty].EnemyList, 0, sizeof(pMob[MobEmpty].EnemyList));

		int posX = pMob[conn].TargetX;
		int posY = pMob[conn].TargetY;

		int tmob = GetEmptyMobGrid(MobEmpty, &posX, &posY);

		if (tmob == 0)
		{
			pMob[MobEmpty].Mode = MOB_EMPTY;

			return 0;
		}

		pMob[MobEmpty].TargetX = posX;
		pMob[MobEmpty].LastX = posX;
		pMob[MobEmpty].TargetY = posY;
		pMob[MobEmpty].LastY = posY;

		if (sItem == 0)
		{
			pMob[MobEmpty].Affect[0].Type = 24;
			pMob[MobEmpty].Affect[0].Value = 0;
			pMob[MobEmpty].Affect[0].Level = 0;
			pMob[MobEmpty].Affect[0].Time = 20;

			if (SummonID >= 28 && SummonID <= 37)
				pMob[MobEmpty].Affect[0].Time = 2000000000;
		}

		if (sItem != 0)
		{
			if (sItem->stEffect[0].sValue > pMob[MobEmpty].MOB.CurrentScore.MaxHp)
				sItem->stEffect[0].sValue = pMob[MobEmpty].MOB.CurrentScore.MaxHp;

			pMob[MobEmpty].MOB.BaseScore.Hp = sItem->stEffect[0].sValue;
			pMob[MobEmpty].MOB.CurrentScore.Hp = pMob[MobEmpty].MOB.BaseScore.Hp;
		}
		MSG_CreateMob sm;
		memset(&sm, 0, sizeof(MSG_CreateMob));

		GetCreateMob(MobEmpty, &sm);

		sm.CreateType |= 3u;
		pMobGrid[posY][posX] = MobEmpty;

		GridMulticast(posX, posY, (MSG_STANDARD*)&sm, 0);

		pMob[Leader].PartyList[j] = MobEmpty;
		pMob[MobEmpty].Leader = Leader;

		if (SummonNum == 0)
			SendAddParty(Leader, Leader, 0);

		SendAddParty(MobEmpty, Leader, 0);

		if (SummonNum == 0)
			SendAddParty(MobEmpty, MobEmpty, j + 1);

		SendAddParty(Leader, MobEmpty, j + 1);

		for (int l = 0; l < MAX_PARTY; l++) //09/03
		{
			if (pMob[Leader].PartyList[l] == 0)
				continue;

			if (pMob[Leader].PartyList[l] != MobEmpty)
				SendAddParty(pMob[Leader].PartyList[l], MobEmpty, l + 1);

			SendAddParty(MobEmpty, pMob[Leader].PartyList[l], l + 1);
		}

		pMob[MobEmpty].Summoner = conn;
		pMob[MobEmpty].IsSummon = 1; // Crias/Outros

		if (SummonID >= 0 && SummonID <= 7)
			pMob[MobEmpty].IsSummon = 2; // Evoca��es
	}
	return 1;
}

int CreateMob(char* MobName, int PosX, int PosY, char* folder, int Type)
{
	int tmob = GetEmptyNPCMob();

	if (tmob == 0)
	{
		sprintf_s(temp, "err,no emptymob create %s", MobName);
		SystemLog("-system", "-", 0, temp);

		return -1;
	}

	strncpy(pMob[tmob].MOB.MobName, MobName, NAME_LENGTH);

	memset(&pMob[tmob].PartyList, 0, sizeof(pMob[tmob].PartyList));

	int read = ReadMob(&pMob[tmob].MOB, folder);

	if (read == 0)
		return 0;

	pMob[tmob].MOB.MobName[NAME_LENGTH - 1] = 0;
	pMob[tmob].MOB.BaseScore.Merchant = 0;


	for (int i = 0; i < NAME_LENGTH; i++)
	{
		if (pMob[tmob].MOB.MobName[i] == 95)
			pMob[tmob].MOB.MobName[i] = 32;

		if (pMob[tmob].MOB.MobName[i] == '@')
			pMob[tmob].MOB.MobName[i] = 0;
	}
	memset(pMob[tmob].Affect, 0, sizeof(pMob[tmob].Affect));


	for (int i = 0; i < MAX_SEGMENT; i++)
	{
		if (pMob[tmob].MOB.Equip[0].sIndex != 220 && pMob[tmob].MOB.Equip[0].sIndex != 219 && pMob[tmob].MOB.Equip[0].sIndex != 358)
		{
			pMob[tmob].SegmentListX[i] = PosX + rand() % 5 - 2;
			pMob[tmob].SegmentListY[i] = PosY + rand() % 5 - 2;
		}

		else
		{
			pMob[tmob].SegmentListX[i] = PosX;
			pMob[tmob].SegmentListY[i] = PosY;
		}
	}


	if (pMob[tmob].MOB.Equip[0].sIndex == 220 || pMob[tmob].MOB.Equip[0].sIndex == 219)
	{
		if (pMob[tmob].MOB.Equip[0].sIndex == 219)
		{
			pMob[tmob].MOB.Guild = g_pGuildZone[4].ChargeGuild;
			pMob[tmob].MOB.GuildLevel = 0;
		}
	}

	pMob[tmob].GenerateIndex = -1;

	pMob[tmob].Formation = 0;

	pMob[tmob].RouteType = Type;
	pMob[tmob].Mode = MOB_PEACE;

	pMob[tmob].SegmentDirection = 0;

	pMob[tmob].Leader = 0;
	pMob[tmob].WaitSec = Type == 0 ? 10 : 40;
	pMob[tmob].LastTime = CurrentTime;

	pMob[tmob].GetCurrentScore(MAX_USER);
	pMob[tmob].MOB.CurrentScore.Hp = pMob[tmob].MOB.CurrentScore.MaxHp;

	if (NewbieEventServer && pMob[tmob].MOB.CurrentScore.Level < 120)
		pMob[tmob].MOB.CurrentScore.Hp = 3 * pMob[tmob].MOB.CurrentScore.Hp / 4;

	pMob[tmob].SegmentProgress = Type == 0 ? 0 : 4;

	memset(pMob[tmob].EnemyList, 0, sizeof(pMob[tmob].EnemyList));

	int px = pMob[tmob].SegmentListX[0];
	int py = pMob[tmob].SegmentListY[0];

	int mobslot = GetEmptyMobGrid(tmob, &px, &py);

	if (mobslot == 0)
	{
		sprintf_s(temp, "err,No empty mobgrid:%s x:%d y:%d", MobName, px, py);
		SystemLog("-system", "-", 0, temp);

		pMob[tmob].Mode = 0;
		pMob[tmob].MOB.MobName[0] = 0;
		pMob[tmob].GenerateIndex = -1;

		return -2;
	}

	pMob[tmob].SegmentX = px;
	pMob[tmob].TargetX = px;
	pMob[tmob].LastX = px;
	pMob[tmob].SegmentY = py;
	pMob[tmob].TargetY = py;
	pMob[tmob].LastY = py;

	int skillnum = pMob[tmob].MOB.BaseScore.MaxMp;

	if (skillnum)
	{
		SetAffect(tmob, skillnum, 30000, 200);
		SetTick(tmob, skillnum, 30000, 200);
	}

	MSG_CreateMob sm;
	memset(&sm, 0, sizeof(MSG_CreateMob));

	GetCreateMob(tmob, &sm);

	sm.CreateType |= 2;

	pMobGrid[py][px] = tmob;

	GridMulticast(px, py, (MSG_STANDARD*)&sm, 0);

	return TRUE;
}

void GenerateMob(int index, int PosX, int PosY)
{
	int GenerateMin = mNPCGen.pList[index].MinuteGenerate;

	int nindex = index;

	for (int i = 0; i < MAX_MOB_MERC; i++)
	{
		if (index != pMobMerc[i].GenerateIndex || index == 0)
			continue;

		memcpy(mNPCGen.pList[index].Leader.Carry, pMobMerc[i].Carry, sizeof(mNPCGen.pList[index].Leader.Carry));
		break;
	}

	if (GenerateMin >= 500)
	{
		int segx = mNPCGen.pList[index].SegmentListX[0];
		int segy = mNPCGen.pList[index].SegmentListY[0];

		int res = segx - segy;

		if ((segx - segy) <= 0)
		{
			Log("err,end index < start index", "-system", 0);
			printf("Index Error. Index %d, PosX %d, PosY %d", index, PosX, PosY);  //monitor console
			return;
		}

		int reloc = rand() % segx + segy;
		if (reloc < 0 || reloc >= mNPCGen.NumList)
			Log("err,wrong index relocation", "-system", 0);

		index = reloc;
	}

	int Formation = mNPCGen.pList[nindex].Formation;
	int MinGroup = mNPCGen.pList[nindex].MinGroup;

	int qmob = mNPCGen.pList[nindex].MaxGroup - mNPCGen.pList[nindex].MinGroup + 1;

	if (qmob <= 0)
	{
		sprintf_s(temp, "err,zero divide : %d", index);
		SystemLog("-system", "-", 0, temp);
		qmob = 1;
	}

	MinGroup += rand() % qmob;

	if (mNPCGen.pList[nindex].CurrentNumMob >= mNPCGen.pList[nindex].MaxNumMob)
		return;

	if (mNPCGen.pList[nindex].CurrentNumMob + MinGroup > mNPCGen.pList[nindex].MaxNumMob)
		MinGroup = mNPCGen.pList[nindex].MaxNumMob - mNPCGen.pList[nindex].CurrentNumMob;

	int tmob = GetEmptyNPCMob();

	if (tmob == 0)
	{
		//sprintf_s(temp, "err,no emptymob leader: %d", index);
		//SystemLog("-system", "-", 0, temp);

		return;
	}

	if (mNPCGen.pList[index].Leader.Equip[0].sIndex != 219 && mNPCGen.pList[index].SegmentListX[0] >= 2440 && mNPCGen.pList[index].SegmentListX[0] <= 2545 && mNPCGen.pList[index].SegmentListY[0] >= 1845 && mNPCGen.pList[index].SegmentListY[0] <= 1921)
	{
		mNPCGen.pList[index].MinuteGenerate = -1;
		return;
	}

	int tmob2 = tmob;

	memset(&pMob[tmob].PartyList, 0, sizeof(pMob[tmob].PartyList));
	memcpy(&pMob[tmob].MOB, &mNPCGen.pList[nindex].Leader, sizeof(STRUCT_MOB));

	pMob[tmob].MOB.MobName[NAME_LENGTH - 1] = 0;
	pMob[tmob].MOB.BaseScore.Merchant = 0;

	strncpy(pMob[tmob].MOB.MobName, mNPCGen.pList[nindex].Leader.MobName, NAME_LENGTH);

	if (strcmp(pMob[tmob].MOB.MobName, mNPCGen.pList[nindex].Leader.MobName) != 0)
		memcpy(pMob[tmob].MOB.MobName, mNPCGen.pList[nindex].Leader.MobName, NAME_LENGTH);

	for (int i = 0; i < NAME_LENGTH; i++)
	{
		if (pMob[tmob].MOB.MobName[i] == 95)
			pMob[tmob].MOB.MobName[i] = 32;

		if (pMob[tmob].MOB.MobName[i] == 64)
			pMob[tmob].MOB.MobName[i] = 32;
	}
	memset(pMob[tmob].Affect, 0, sizeof(pMob[tmob].Affect));

	for (int i = 0; i < MAX_SEGMENT; i++)
	{
		if (mNPCGen.pList[index].SegmentListX[i])
		{
			if (mNPCGen.pList[index].SegmentRange[i])
			{
				pMob[tmob].SegmentListX[i] = mNPCGen.pList[index].SegmentListX[i]
					- mNPCGen.pList[index].SegmentRange[i] + (rand() % (mNPCGen.pList[index].SegmentRange[i] + 1));

				pMob[tmob].SegmentListY[i] = mNPCGen.pList[index].SegmentListY[i]
					- mNPCGen.pList[index].SegmentRange[i] + (rand() % (mNPCGen.pList[index].SegmentRange[i] + 1));
			}
			else
			{
				pMob[tmob].SegmentListX[i] = mNPCGen.pList[index].SegmentListX[i];
				pMob[tmob].SegmentListY[i] = mNPCGen.pList[index].SegmentListY[i];
			}
			pMob[tmob].SegmentWait[i] = mNPCGen.pList[index].SegmentWait[i];
		}
		else
		{
			pMob[tmob].SegmentListX[i] = 0;
			pMob[tmob].SegmentListY[i] = 0;
		}
	}

	if (PosX && PosY)
	{
		for (int i = 0; i < MAX_SEGMENT; i++)
		{
			pMob[tmob].SegmentListX[i] = PosX;
			pMob[tmob].SegmentListY[i] = PosY;
		}
	}

	if (pMob[tmob].MOB.Equip[0].sIndex == 220 || pMob[tmob].MOB.Equip[0].sIndex == 219)
	{
		int br = BrState;
		if (BrState > 0 && br < MAX_USER)
		{
			if (pUser[br].Mode == USER_PLAY && RvRState == 0 && GTorreState == 0)
			{
				*(int*)&pMob[tmob].MOB.Equip[15] = *(int*)&pMob[br].MOB.Equip[15];
				*(int*)(&pMob[tmob].MOB.Equip[15] + 4) = *(int*)(&pMob[br].MOB.Equip[15] + 4);

				if (pMob[tmob].MOB.Equip[0].sIndex == 219)
				{
					pMob[tmob].MOB.Guild = pMob[br].MOB.Guild;

					GetGuild(tmob);

					if (pMob[br].MOB.GuildLevel == 9)
						pMob[tmob].MOB.GuildLevel = 0;
				}
			}
		}
	}

	CWarTower::GGenerateMob(index, PosX, PosY, tmob);
 

	pMob[tmob].GenerateIndex = index;
	pMob[tmob].IsSummon = 0;

	pMob[tmob].Formation = mNPCGen.pList[nindex].Formation;

	pMob[tmob].RouteType = mNPCGen.pList[nindex].RouteType;
	pMob[tmob].Mode = MOB_PEACE;

	pMob[tmob].SegmentDirection = 0;

	pMob[tmob].Leader = 0;
	pMob[tmob].WaitSec = pMob[tmob].SegmentWait[0];
	pMob[tmob].LastTime = CurrentTime;

	pMob[tmob].GetCurrentScore(MAX_USER);
	pMob[tmob].MOB.CurrentScore.Hp = pMob[tmob].MOB.CurrentScore.MaxHp;

	if (NewbieEventServer && pMob[tmob].MOB.CurrentScore.Level < 120)
		pMob[tmob].MOB.CurrentScore.Hp = 3 * pMob[tmob].MOB.CurrentScore.Hp / 4;

	pMob[tmob].SegmentProgress = 0;

	memset(pMob[tmob].EnemyList, 0, sizeof(pMob[tmob].EnemyList));

	if (pMob[tmob].MOB.Clan == 1 && rand() % 10 == 1)
		pMob[tmob].MOB.Clan = 2;

	int mobslot = GetEmptyMobGrid(tmob, &pMob[tmob].SegmentListX[0], &pMob[tmob].SegmentListY[0]);

	if (mobslot == 0)
	{
		sprintf_s(temp, "err,No empty mobgrid(1): %d %d %d", index, pMob[tmob].SegmentListX[0], pMob[tmob].SegmentListY[0]);
		SystemLog("-system", "-", 0, temp);

		pMob[tmob].Mode = 0;
		pMob[tmob].MOB.MobName[0] = 0;
		pMob[tmob].GenerateIndex = -1;

		return;
	}

	//Imposto
	if (pMob[tmob].MOB.Merchant == 6 && tmob >= MAX_USER)
	{
		int level = pMob[tmob].MOB.CurrentScore.Level;

		GuildImpostoID[level] = tmob;
		pMob[tmob].MOB.Guild = g_pGuildZone[level].ChargeGuild;
	}


	pMob[tmob].SegmentX = pMob[tmob].SegmentListX[0];
	pMob[tmob].TargetX = pMob[tmob].SegmentListX[0];
	pMob[tmob].LastX = pMob[tmob].SegmentListX[0];
	pMob[tmob].SegmentY = pMob[tmob].SegmentListY[0];
	pMob[tmob].TargetY = pMob[tmob].SegmentListY[0];
	pMob[tmob].LastY = pMob[tmob].SegmentListY[0];

	if (mNPCGen.pList[nindex].CurrentNumMob < 0)
		mNPCGen.pList[nindex].CurrentNumMob = 0;

	mNPCGen.pList[nindex].CurrentNumMob++;

	int skillnum = mNPCGen.pList[nindex].Leader.BaseScore.MaxMp;

	if (skillnum)
	{
		SetAffect(tmob, skillnum, 30000, 200);
		SetTick(tmob, skillnum, 30000, 200);
	}

	MSG_CreateMob sm;
	memset(&sm, 0, sizeof(MSG_CreateMob));
	GetCreateMob(tmob, &sm);

	sm.CreateType |= 2;

	pMobGrid[pMob[tmob].SegmentListY[0]][pMob[tmob].SegmentListX[0]] = tmob;

	GridMulticast(pMob[tmob].SegmentListX[0], pMob[tmob].SegmentListY[0], (MSG_STANDARD*)&sm, 0);

	for (int i = 0; i < MinGroup && i < MAX_PARTY; i++)
	{
		int tempmob = GetEmptyNPCMob();

		if (tempmob == 0)
		{
			pMob[tmob2].PartyList[i] = 0;

			sprintf_s(temp, "err,no empty mob: %d", index);

			SystemLog("-system", "-", 0, temp);
			continue;
		}

		memset(&pMob[tempmob].PartyList, 0, sizeof(pMob[tempmob].PartyList));

		pMob[tmob2].PartyList[i] = tempmob;

		memcpy(&pMob[tempmob], &mNPCGen.pList[nindex].Follower, sizeof(STRUCT_MOB));

		pMob[tempmob].MOB.BaseScore.Merchant = 0;

		strncpy(pMob[tempmob].MOB.MobName, mNPCGen.pList[nindex].Follower.MobName, NAME_LENGTH);

		for (int j = 0; j < NAME_LENGTH; ++j)
		{
			if (pMob[tempmob].MOB.MobName[j] == 95)
				pMob[tempmob].MOB.MobName[j] = 32;

			if (pMob[tempmob].MOB.MobName[j] == '@')
				pMob[tempmob].MOB.MobName[j] = 0;
		}
		memset(pMob[tempmob].Affect, 0, sizeof(pMob[tempmob].Affect));

		for (int j = 0; j < MAX_SEGMENT; j++)
		{
			if (mNPCGen.pList[index].SegmentRange[j])
			{
				pMob[tempmob].SegmentListX[j] = g_pFormation[i][j][Formation] + pMob[tmob].SegmentListX[j];

				pMob[tempmob].SegmentListY[j] = g_pFormation[i][j][Formation] + pMob[tmob].SegmentListY[j];


				pMob[tempmob].SegmentWait[j] = mNPCGen.pList[index].SegmentWait[j];
			}
			else
			{
				pMob[tempmob].SegmentListX[j] = mNPCGen.pList[index].SegmentListX[j];
				pMob[tempmob].SegmentListY[j] = mNPCGen.pList[index].SegmentListY[j];
			}
		}
		if (PosX && PosY)
		{
			for (int k = 0; k < MAX_SEGMENT; k++)
			{
				pMob[tempmob].SegmentListX[k] = PosX + rand() % 5 - 2;
				pMob[tempmob].SegmentListY[k] = PosY + rand() % 5 - 2;
			}
		}

		pMob[tempmob].GenerateIndex = index;

		pMob[tempmob].Formation = mNPCGen.pList[nindex].Formation;

		pMob[tempmob].RouteType = mNPCGen.pList[nindex].RouteType;
		pMob[tempmob].Mode = MOB_PEACE;

		pMob[tempmob].SegmentProgress = 0;

		pMob[tempmob].Leader = tmob2;
		pMob[tempmob].LastTime = CurrentTime;

		pMob[tempmob].GetCurrentScore(MAX_USER);
		pMob[tempmob].MOB.CurrentScore.Hp = pMob[tempmob].MOB.CurrentScore.MaxHp;

		if (NewbieEventServer && pMob[tempmob].MOB.CurrentScore.Level < 120)
			pMob[tempmob].MOB.CurrentScore.Hp = 3 * pMob[tempmob].MOB.CurrentScore.Hp / 4;

		pMob[tempmob].WaitSec = pMob[tempmob].SegmentWait[0];
		pMob[tempmob].SegmentDirection = 0;

		memset(pMob[tempmob].EnemyList, 0, sizeof(pMob[tempmob].EnemyList));

		if (pMob[tempmob].MOB.Clan == 1 && rand() % 10 == 1)
			pMob[tempmob].MOB.Clan = 2;

		int mslot = GetEmptyMobGrid(tempmob, &pMob[tempmob].SegmentListX[0], &pMob[tempmob].SegmentListY[0]);

		if (mslot == 0)
		{
			sprintf_s(temp, "err,No empty mobgrid: %d %d %d", index, pMob[tempmob].SegmentListX[0], pMob[tempmob].SegmentListY[0]);
			SystemLog("-system", "-", 0, temp);

			pMob[tempmob].Mode = 0;
			pMob[tempmob].MOB.MobName[0] = 0;
			pMob[tempmob].GenerateIndex = -1;
			pMob[tmob2].PartyList[i] = 0;

			return;
		}


		pMob[tempmob].SegmentX = pMob[tempmob].SegmentListX[0];
		pMob[tempmob].TargetX = pMob[tempmob].SegmentListX[0];
		pMob[tempmob].LastX = pMob[tempmob].SegmentListX[0];
		pMob[tempmob].SegmentY = pMob[tempmob].SegmentListY[0];
		pMob[tempmob].TargetY = pMob[tempmob].SegmentListY[0];
		pMob[tempmob].LastY = pMob[tempmob].SegmentListY[0];

		skillnum = mNPCGen.pList[nindex].Leader.BaseScore.MaxMp;

		if (skillnum)
		{
			SetAffect(tempmob, skillnum, 30000, 200);
			SetTick(tempmob, skillnum, 30000, 200);
		}

		MSG_CreateMob sm2;
		memset(&sm2, 0, sizeof(MSG_CreateMob));
		GetCreateMob(tempmob, &sm2);

		sm2.CreateType |= 2;

		pMobGrid[pMob[tempmob].SegmentListY[0]][pMob[tempmob].SegmentListX[0]] = tempmob;

		GridMulticast(pMob[tempmob].SegmentListX[0], pMob[tempmob].SegmentListY[0], (MSG_STANDARD*)&sm2, 0);

		if (mNPCGen.pList[nindex].CurrentNumMob < 0)
			mNPCGen.pList[nindex].CurrentNumMob = 0;

		mNPCGen.pList[nindex].CurrentNumMob++;
	}
}

 


void RebuildGenerator()
{
	for (int i = 0; i < mNPCGen.NumList; i++)
		mNPCGen.NumOld[i] = 0;

	for (int i = MAX_USER; i < MAX_MOB; i++)
	{
		if (pMob[i].Mode == 0)
			continue;

		int GenerateIndex = pMob[i].GenerateIndex;

		if (GenerateIndex >= 0 && GenerateIndex < mNPCGen.NumList)
			mNPCGen.NumOld[GenerateIndex]++;
	}

	for (int i = MAX_USER; i < mNPCGen.NumList; i++)
	{
		if (mNPCGen.pList[i].CurrentNumMob == mNPCGen.NumOld[i])
			continue;

		//sprintf(temp, "Idx:%d Name:%s Old:%d New:%d", i, mNPCGen.pList[i].Leader.MobName, mNPCGen.pList[i].CurrentNumMob, mNPCGen.NumOld[i]);

		//Log(temp, "-system", 0);

		mNPCGen.pList[i].CurrentNumMob = mNPCGen.NumOld[i];
	}
}

bool FileExist(const char* Name)
{
	if (FILE* file = fopen(Name, "r"))
	{
		fclose(file);
		return true;
	}
	return false;
}
BOOL InitApplication(HANDLE hInstance)
{
	WNDCLASS  wc;

	wc.style = CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS;

	wc.lpfnWndProc = (WNDPROC)MainWndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = (HICON)LoadIcon((HINSTANCE)hInstance, "MAINICON");
	wc.hInstance = (HINSTANCE)hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "MainClass";

	if (!RegisterClass(&wc))
		return RegisterClass(&wc);

	return TRUE;
}

BOOL InitInstance(HANDLE hInstance, int nCmdShow)
{
	hMainMenu = CreateMenu();
	hWndMain = CreateWindow("MainClass", "WYD v7.59",
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,  
		CW_USEDEFAULT, CW_USEDEFAULT, 900, 600,  
		NULL, hMainMenu, (HINSTANCE)hInstance, NULL);

	if (!hWndMain)
		return (FALSE);

	ShowWindow(hWndMain, nCmdShow);
	UpdateWindow(hWndMain);

	return TRUE;
}

FILE*  WriteHeader(char *fileName)
{
	FILE *fp = NULL;

	fp = fopen(fileName, "wt");

	fprintf(fp, "<script>\n");
	fprintf(fp, "function f_show(idx) \n");
	fprintf(fp, "{\n");
	fprintf(fp, "opener.document.frmRegist.item_code.value=idx;\n");
	fprintf(fp, "self.close();\n");
	fprintf(fp, "}\n");
	fprintf(fp, "</script>\n");
	fprintf(fp, "<style><!--\n");
	fprintf(fp, "A:link {color:#111111;font-size:9pt;text-decoration:none}\n");
	fprintf(fp, "A:visited {color:#333333;font-size:9pt;text-decoration:none}\n");
	fprintf(fp, "A:active {color:red;font-size:9pt}\n");
	fprintf(fp, "A:hover {text-color:red;text-decoration:underline}\n");
	fprintf(fp, "BODY,TD,TH {font-size: 9pt}\n");
	fprintf(fp, "--></style>\n");

	return fp;
}

inline void FixIOHandles()
{
	int outParam = _open_osfhandle((long)GetStdHandle(STD_OUTPUT_HANDLE), _O_TEXT);
	FILE *stdout_stream = _fdopen(outParam, "w");
	*stdout = *stdout_stream;
	int inParam = _open_osfhandle((long)GetStdHandle(STD_INPUT_HANDLE), _O_TEXT);
	FILE *stdin_stream = _fdopen(inParam, "r");
	*stdin = *stdin_stream;
}

inline void CreateConsole()
{
	AllocConsole();
	FixIOHandles();
}

void  WriteArmor(FILE *fp)
{
}

BOOL WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;

	g_pBlockIP.clear();
	UNREFERENCED_PARAMETER(lpCmdLine);

	if (!hPrevInstance)
		if (!InitApplication(hInstance))
			return FALSE;

	if (!InitInstance(hInstance, nCmdShow))
		return FALSE;

	hFont = CreateFont(12, 0, 0, 0, FW_LIGHT, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEVICE_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Fixedsys"); // |FF_DECORATIVE

	BASE_InitModuleDir();
	BASE_InitializeHitRate();

	/*StartLog();
	StartChatLog();*/

	memset(&g_pTreasure, 0, sizeof(g_pTreasure));

	ReadDirectory();
	BASE_ReadQuestDiaria();
	ReadConfig();
	ReadLevelItemConfig();
	// Leitura de txt ao iniciar
	//ReadMarket();
	//ReadGuildPoints();
	//ReadEvent();
	//ReadEvent2();
	//ReadGItens();

	ConfigReady = 1;

	DrawConfig(0);

	memset(g_pGuildWar, 0, sizeof(g_pGuildWar));
	memset(g_pGuildAlly, 0, sizeof(g_pGuildAlly));
	memset(GuildInfo, 0, sizeof(GuildInfo));
	memset(pMac, 0, sizeof(pMac));
	memset(pMobMerc, 0, sizeof(pMobMerc));

	int ret = ListenSocket.WSAInitialize();

	if (!ret)
	{
		//Log("erro,n�o foi possivel iniciar a seguinte fun��o : WSAInitialize", "-system", 0);

		return FALSE;
	}

	Reboot();
	ReadQuiz();

	StartSystemLog();
	StartChatLog();
	StartItemLog();
	CompositorLog(); // 23/02
	trade_item(); // 23/02
	MobDropLogs();

	SetCastleDoor(1);

	char name[255];

	FILE* fp = fopen("localip.txt", "rt");

	if (fp)
	{
		fscanf(fp, "%s", name);

		fclose(fp);
	}
	else
		MessageBox(hWndMain, "N�o foi possivel encontrar o arquivo LocalIP.txt", "Erro ao iniciar", NULL);

	int r1 = 0, r2 = 0, r3 = 0, r4 = 0;

	sscanf(name, "%d.%d.%d.%d", &r1, &r2, &r3, &r4);

	LocalIP[0] = r1;
	LocalIP[1] = r2;
	LocalIP[2] = r3;
	LocalIP[3] = r4;
	DBServerAddress[0] = 0;

	for (int i = 0; i < MAX_SERVERGROUP; i++)
	{
		for (int j = 1; j < MAX_SERVERNUMBER; j++)
		{
			if (!strcmp(g_pServerList[i][j], name))
			{
				strncpy(DBServerAddress, g_pServerList[i][0], sizeof(DBServerAddress));

				ServerGroup = i;
				ServerIndex = j - 1;

				break;
			}
		}

		if (DBServerAddress[0] == 0)
			continue;
	}

	if (DBServerAddress[0] == 0)
	{
		MessageBox(hWndMain, "N�o foi possivel pegar o ServerGroup. LocalIP.txt / ServerList.txt", "Erro ao iniciar", MB_OK | MB_SYSTEMMODAL);

		return TRUE;
	}

	DBServerPort = 7514;

	int *pip = (int*)LocalIP;

	ret = DBServerSocket.ConnectServer(DBServerAddress, 7514, *pip, WSA_READDB);

	if (ret == NULL)
	{
		Log("erro, N�o foi possivel se conectar a DBServer", "-system", 0);
		MessageBox(hWndMain, "N�o foi possivel se conectar a DBServer", "Erro ao iniciar", NULL);

		return FALSE;
	}

	for (int i = 1; i < MAX_SERVERNUMBER; i++)
	{
		if (g_pServerList[ServerGroup][i][0] != 0)
			NumServerInGroup++;
	}

	if (NumServerInGroup <= 0)
		NumServerInGroup = 1;

	if (NumServerInGroup > 10)
		NumServerInGroup = 10;

	//IP ERRADO
	//if (!strcmp(DBServerAddress, "")) 
		//TESTSERVER = 1;

	//IP ERRADO
	//if (!strcmp(DBServerAddress, ""))  
		//LOCALSERVER = 1;

	fp = fopen("biserver.txt", "rt");

	if (fp)
	{
		fscanf(fp, "%s %d", BillServerAddress, &BillServerPort);

		fclose(fp);
	}

	if (BILLING > 0)
	{
		int *pip2 = (int*)LocalIP;

		ret = BillServerSocket.ConnectBillServer(BillServerAddress, BillServerPort, *pip2, WSA_READBILL);

		if (ret == NULL)
		{
			Log("erro, N�o foi possivel se conectar na BIServer", "-system", 0);
			BILLING = 0;
		}
		else
		{
			_AUTH_GAME sm;

			memset(&sm, 0, sizeof(sm));

			SendBilling2(&sm, 4); // MSG_BillLogin ?
		}
	}

	SetColoseumDoor(1);
	SetColoseumDoor2(3);

	memset(FailAccount, 0, sizeof(FailAccount));

	CurrentTime = timeGetTime();

	CReadFiles::CReadFiles();
	// CEncampment::ReadCamp();
	CCastleZakum::ReadCastleQuest();
	//CCubo::Initialize();

	SetTimer(hWndMain, TIMER_SEC, 500, NULL);
	SetTimer(hWndMain, TIMER_MIN, 12000, NULL);

	ListenSocket.StartListen(hWndMain, *pip, GAME_PORT, WSA_ACCEPT);

	GuildZoneReport();

	if (KefraLive == 0)
	{
		for (int k = KEFRA_MOB_INITIAL; k < KEFRA_MOB_END; k++)
			GenerateMob(k, 0, 0);

		GenerateMob(KEFRA_BOSS, 0, 0);
	}

	UpdateShopDonate1();
	UpdateShopDonate2();
	UpdateShopDonate3();
	LoadEvent();
	BalanceioPvP();
	ReadServerConfigs();
	ReadExpTableN();
	ReadExpTableM();

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return	msg.wParam;
}

void WriteWeapon(FILE *fp)
{
	fprintf(fp, "<body leftmargin=0 topmargin=0 marginwidth=0 marginheight=0><table>\n");

	for (int i = 0; i < 32; i++)
	{
		fprintf(fp, "<tr  height=10>");

		for (int j = 0; j < 9; j++)
		{
			char dest[256];

			int item = weapon[i][j];

			if (j == 0)
				strncpy(dest, "#F6EED9", sizeof(dest));
			if (j == 1)
				strncpy(dest, "#DFDFDF", sizeof(dest));
			if (j == 2)
				strncpy(dest, "#D9EAF6", sizeof(dest));
			if (j == 3)
				strncpy(dest, "#DFE9D0", sizeof(dest));
			if (j == 4)
				strncpy(dest, "#F6D9E0", sizeof(dest));
			if (j == 5)
				strncpy(dest, "#F6EED9", sizeof(dest));
			if (j == 6)
				strncpy(dest, "#DFDFDF", sizeof(dest));
			if (j == 7)
				strncpy(dest, "#D9EAF6", sizeof(dest));
			if (j == 8)
				strncpy(dest, "#DFE9D0", sizeof(dest));

			int reqlv = g_pItemList[item].ReqLvl;
			int reqstatus = g_pItemList[item].ReqCon + g_pItemList[item].ReqDex + g_pItemList[item].ReqInt + g_pItemList[item].ReqStr;

			if (reqlv || reqstatus <= 75)
			{
				if (reqlv || reqstatus <= 20)
					strncpy(temp, "#000000", sizeof(temp));
				else
					strncpy(temp, "#00BF00", sizeof(temp));
			}
			else
				strncpy(temp, "#FF00FF", sizeof(temp));

			fprintf(fp, "<td width=140 height=16 bgcolor='%s'><a href=\"javascript:f_show(%d); title='%d'><font color='%s'>%16.16s</font></a></td>",
				&dest, item, item, &temp, &g_pItemList[item].Name);
		}
		fprintf(fp, "</tr>\n");
	}
	fprintf(fp, "</table></body>\n");
}

void BuildList()
{

}

LONG APIENTRY MainWndProc(HWND hWnd, UINT message, UINT wParam, LONG lParam)
{
	switch (message)
	{

	case WM_TIMER:
	{
		if (wParam == TIMER_SEC)
			ProcessSecTimer();
		else if (wParam == TIMER_MIN)
			ProcessMinTimer();
	} break;

	case WSA_READBILL:
	{
		if (WSAGETSELECTEVENT(lParam) != FD_READ)
		{
			Log("err Billing Connection lost.", "-system", 0);

			BillServerSocket.CloseSocket();
			BillCounter = 360;

			Log("err,billing disconnected.", "-system", 0);

			return TRUE;
		}

		int ret = BillServerSocket.Receive();

		if (ret != TRUE)
		{
			Log("err bill receive fail", "-system", 0);

			BillServerSocket.CloseSocket();
			BillCounter = 360;

			return TRUE;
		}

		if (ret == FALSE)
		{
			ret = WSAGetLastError();

			sprintf_s(temp, "err,socket %d %d-%d-%d", ret, BillServerSocket.nRecvPosition, BillServerSocket.nProcPosition, BillServerSocket.nSendPosition);

			ret = BillServerSocket.Receive();

			if (ret != TRUE)
			{
				//Log("err,bill receive retry_recv fail", "-system", 0);

				BillServerSocket.CloseSocket();
				BillCounter = 360;

				break;
			}
		}
		else if (ret == -1)
		{
			//sprintf_s(temp, "clo,bill receive %d-%d-%d", BillServerSocket.nRecvPosition, BillServerSocket.nProcPosition, BillServerSocket.nSendPosition);
			//Log(temp, "-system", 0);

			ret = recv(BillServerSocket.Sock, BillServerSocket.pRecvBuffer, RECV_BUFFER_SIZE, NULL);

			BillServerSocket.CloseSocket();
			BillCounter = 360;

			break;
		}

		int Error = 0;
		int ErrorCode = 0;

		while (1)
		{
			char *Msg = BillServerSocket.ReadBillMessage(&Error, &ErrorCode);

			if (Msg == NULL)
				break;

			if (Error == 1 || Error == 2)
			{
				//sprintf_s(temp, "err readbill (%d),%d", Error, ErrorCode);
				//Log(temp, "-system", 0);

				break;
			}

			ProcessBILLMessage(Msg);

		};

	}  break;

	case WSA_READDB:
	{
		int t = WSAGETSELECTEVENT(lParam);
		if (WSAGETSELECTEVENT(lParam) != FD_READ)
		{
			Log("err wsareaddb fail", "-system", 0);

			DBServerSocket.CloseSocket();

			int ret = 0;

			for (int i = 0; i < 2; i++)
			{
				int *pip = (int*)LocalIP;

				ret = DBServerSocket.ConnectServer(DBServerAddress, DBServerPort, *pip, WSA_READDB);

				if (ret != NULL)
					break;

				Sleep(200);
			}

			if (ret == 0)
			{
				Log("reconnect DB fail.", "-system", 0);

				PostQuitMessage(NULL);

				return TRUE;

			}

			Sleep(200);
			PostQuitMessage(NULL);
			return TRUE;
		}

		if (DBServerSocket.Receive() == FALSE)
		{
			Log("err wsareaddb fail", "-system", 0);

			DBServerSocket.CloseSocket();

			int ret = 0;

			for (int i = 0; i < 2; i++)
			{
				int *pip = (int*)LocalIP;

				ret = DBServerSocket.ConnectServer(DBServerAddress, DBServerPort, *pip, WSA_READDB);

				if (ret != NULL)
					break;

				Sleep(200);
			}

			if (ret == 0)
			{
				Log("reconnect DB fail.", "-system", 0);

				PostQuitMessage(NULL);

				return TRUE;

			}
			PostQuitMessage(NULL);
			return TRUE;

		}

		int Error = 0;
		int ErrorCode = 0;

		while (1)
		{
			char *Msg = DBServerSocket.ReadMessage(&Error, &ErrorCode);

			if (Msg == NULL)
				break;


#ifdef  _PACKET_DEBUG
			MSG_STANDARD *debug = (MSG_STANDARD*)Msg;

			if (BASE_CheckPacket(debug))
			{
				//sprintf(temp, "**PACKET_DEBUG** Type:%d Size:%d", debug->Type, debug->Size);
				//Log(temp, "-system", 0);

				break;
			}
#endif

			if (Error == 1 || Error == 2)
			{
				//sprintf(temp, "err readdb (%d),%d", Error, ErrorCode);
				//Log(temp, "-system", 0);
				break;
			}

			ProcessDBMessage(Msg);
		};

	} break;

	case  WSA_READ:
	{
		int User = GetUserFromSocket(wParam);
		if (User == 0)
		{
			closesocket(wParam);

			break;
		}

		if (WSAGETSELECTEVENT(lParam) != FD_READ)
		{
			//sprintf(temp, "clo,fd %d-%d", pUser[User].Mode, pMob[User].Mode);
			//Log(temp, pUser[User].AccountName, pUser[User].IP);

			CloseUser(User);
			break;
		}

		int ret = pUser[User].cSock.Receive();

		if (ret == FALSE)
		{
			ret = WSAGetLastError();

			//sprintf(temp, "err,socket %d %d-%d-%d %d-%d", ret, pUser[User].cSock.nRecvPosition, pUser[User].cSock.nProcPosition, pUser[User].cSock.nSendPosition, pUser[User].Mode, pMob[User].Mode);

			ret = pUser[User].cSock.Receive();

			if (ret == FALSE)
			{
				//Log("err,retry_recv fail", pUser[User].AccountName, pUser[User].IP);

				CloseUser(User);

				break;
			}
		}
		else if (ret == -1)
		{
			//sprintf(temp, "clo,receive %d-%d-%d %d-%d", pUser[User].cSock.nRecvPosition, pUser[User].cSock.nProcPosition, pUser[User].cSock.nSendPosition, pUser[User].Mode, pMob[User].Mode);

			//Log("clo,receive %d-%d-%d", pUser[User].AccountName, pUser[User].IP);

			ret = recv(pUser[User].cSock.Sock, pUser[User].cSock.pRecvBuffer, RECV_BUFFER_SIZE, NULL);

			CloseUser(User);

			break;
		}

		int Error = 0;
		int ErrorCode = 0;

		while (1)
		{
			char *Msg = pUser[User].cSock.ReadMessage(&Error, &ErrorCode);

			if (Msg == NULL)
				break;

#ifdef  _PACKET_DEBUG
			MSG_STANDARD *debug = (MSG_STANDARD*)Msg;

			if (Msg != NULL && BASE_CheckPacket(debug))
			{
				//sprintf(temp, "**PACKET_DEBUG** Type:%d Size:%d", debug->Type, debug->Size);
				//Log(temp, "-system", 0);
			}
#endif

			if (Error == 1 || Error == 2)
			{
				pUser[User].AccountName[ACCOUNTNAME_LENGTH - 1] = 0;
				pUser[User].AccountName[ACCOUNTNAME_LENGTH - 2] = 0;

				sprintf_s(temp, "err,read (%d),%d", Error, ErrorCode);
				SystemLog(pUser[User].AccountName, pUser[User].MacAddress, pUser[User].IP, temp);

				break;
			}

			ProcessClientMessage(User, Msg, FALSE);
		};

	} break;

	case WSA_ACCEPT:
	{
		if (WSAGETSELECTERROR(lParam) == 0)
		{

			int User = GetEmptyUser();

			if (User == 0)
			{
				Log("err,accept fail - no empty", "-system", 0);

				break;
			}

			int ret = pUser[User].AcceptUser(ListenSocket.Sock);

#pragma region Bloqueio de excesso de tentativas por IP
			int DEFAULT_BLOCKIP = 5; // consideramos 3 segundos aqui, agora � pra ser 2 minutos
			TMP_BLOCKIP bIp = TMP_BLOCKIP(pUser[User].IP, DEFAULT_BLOCKIP);

			// verificamos se o usu�rio j� est� na lista, se ele estiver, a conex�o ser� anulada e nada ser� processado pela dbsrv ou tmsrv.
			for (auto& i : g_pBlockIP)
			{
				if (i.IPAddress == bIp.IPAddress)
				{
					CloseUser(User);
					return TRUE;
				}
			}


			// adiciona o IP do usu�rio na lista para evitar com que requisite mais de uma conex�o em um curto periodo de tempo
			g_pBlockIP.push_back(bIp);
#pragma endregion


			if (User >= MAX_USER - ADMIN_RESERV)
			{

				SendClientMessage(User, g_pMessageStringTable[_NN_Reconnect]);
				pUser[User].cSock.SendMessageA();

				CloseUser(User);

				return TRUE;
			}

			if (ServerDown != -1000)
			{
				SendClientMessage(User, g_pMessageStringTable[_NN_ServerReboot_Cant_Connect]);

				CloseUser(User);

				return TRUE;
			}

		}
		else
			Log("err,- accept - wsagetselecterror", "-system", 0);

	} break;

	case WM_PAINT:
		PAINTSTRUCT ps;
		BeginPaint(hWnd, &ps);
		DrawConfig(0);

		EndPaint(hWnd, &ps);
		break;

	case WM_CREATE:
	{ 
		HMENU hMenu, hSubMenu;
		// HICON hIcon, hIconSm;

		CreateConsole("");   //console

		hMenu = CreateMenu();

		hSubMenu = CreatePopupMenu();
		AppendMenu(hSubMenu, MF_STRING, IDC_EXIT, "&Exit");
		AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&File");

		hSubMenu = CreatePopupMenu();
		AppendMenu(hSubMenu, MF_STRING, IDC_MOBRELOAD, "&ReloadMob");
		AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&Mob");

		hSubMenu = CreatePopupMenu();
		AppendMenu(hSubMenu, MF_STRING, IDC_REBOOT, "&Reboot");
		AppendMenu(hSubMenu, MF_STRING, IDC_SAVEALL, "&SaveAll");
		AppendMenu(hSubMenu, MF_STRING, IDC_READGUILD, "&ReadGuild");
		AppendMenu(hSubMenu, MF_STRING, IDC_READGUILDNAME, "&ReadGuildName");
		AppendMenu(hSubMenu, MF_STRING, IDC_READGAMECONFIG, "&ReadGameConfig");
		AppendMenu(hSubMenu, MF_STRING, IDC_READSKILLDATA, "&ReadSkillData");
		AppendMenu(hSubMenu, MF_STRING, IDC_READITEMLIST, "&ReadItemList");
		AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&Sistema");

		SetMenu(hWnd, hMenu);
	} break;

	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDC_EXIT:
			PostMessage(hWnd, WM_CLOSE, 0, 0);
			break;

		case IDC_MOBRELOAD:
			mNPCGen.ReadNPCGenerator();
			break;

		case IDC_REBOOT:
			ServerDown = 1;
			break;

		case IDC_SAVEALL:
			SaveAll();
			break;

		case IDC_READGUILD:
			CReadFiles::ReadGuild();
			break;

		case IDC_READGUILDNAME:
			BASE_InitializeGuildName();
			break;

		case IDC_READGAMECONFIG:
		{
			ReadConfig();
			DrawConfig(0);
		} break;
		case IDC_READSKILLDATA:
		{
			BASE_InitializeSkill();
		} break;
		case IDC_READITEMLIST:
		{
			BASE_InitializeItemList();
		} break;
		  
		}
	} break;
	case WM_CLOSE:
	{
		if (MessageBox(hWndMain, "Voc� realmente deseja desligar o server?", "Aviso!!!", MB_ICONQUESTION | MB_YESNO) == IDNO)
			break;

		if (BILLING != 0)
		{
			_AUTH_GAME sm;
			memset(&sm, 0, sizeof(sm));
			SendBilling2(&sm, 4);

			BILLING = 0;
		}

		CReadFiles::WriteGuild();
		if (fLogFile)
		{
			fLogFile.reset(); //Reset or release?
		}

		if (hFont)
		{
			DeleteObject(hFont);
			hFont = NULL;
		}

		DefWindowProc(hWnd, message, wParam, lParam);

	} break;

	case WM_DESTROY:
		WSACleanup();
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

int  GetUserInArea(int x1, int y1, int x2, int y2, char *MobName)
{
	int userCount = 0;

	for (int i = 0; i < MAX_USER; i++)
	{
		if (pUser[i].Mode != USER_PLAY)
			continue;

		if (pMob[i].Mode == 0)
			continue;

		if (pMob[i].TargetX >= x1 && pMob[i].TargetX <= x2 && pMob[i].TargetY >= y1 && pMob[i].TargetY <= y2)
		{
			strncpy(MobName, pMob[i].MOB.MobName, NAME_LENGTH);
			userCount++;
		}
	}
	return userCount;
}

void MountProcess(int conn, STRUCT_ITEM *Mount)
{
	STRUCT_ITEM *MItem = &pMob[conn].MOB.Equip[14];

	int IsEqual = 1;

	if (Mount != NULL)
		IsEqual = memcmp(Mount, MItem, sizeof(STRUCT_ITEM));

	if (IsEqual != 0)
		return;

	int leaderid = pMob[conn].Leader;

	if (leaderid == 0)
		leaderid = conn;

	for (int i = 0; i < MAX_PARTY; i++)
	{
		int partyconn = pMob[leaderid].PartyList[i];

		if (partyconn <= 0 || partyconn > MAX_MOB)
			continue;

		int face = pMob[partyconn].MOB.Equip[0].sIndex;

		if (pMob[partyconn].Summoner == conn)
		{
			if (face >= 315 && face < 345)
				DeleteMob(partyconn, 3);
		}
	}

	int MBabyId = MItem->sIndex - 2320;


	if (MBabyId >= 10 && MBabyId < 40)
	{
		int MHp = BASE_GetItemAbility(MItem, EF_MOUNTHP);

		if (MHp > 0)
			GenerateSummon(conn, MBabyId, MItem, 1);
	}
}

int GetItemSancNew(STRUCT_ITEM* item)
{
	int value = 0;
	if (item->stEffect[0].cEffect == 43)
		value = item->stEffect[0].cValue;
	else if (item->stEffect[1].cEffect == 43)
		value = item->stEffect[1].cValue;
	else if (item->stEffect[2].cEffect == 43)
		value = item->stEffect[2].cValue;
	else
	{
		for (int i = 0; i < 3; i++)
		{
			if (item->stEffect[i].cEffect >= 116 && item->stEffect[i].cEffect <= 125)
			{
				value = item->stEffect[i].cValue;

				break;
			}
		}
	}

	if (value >= 230)
	{
		value = 10 + ((value - 230) / 4);
		if (value > 15)
			value = 15;
	}
	else
		value %= 10;

	return value;
}

void LinkMountHp(int mobConn)
{
	if (mobConn < MAX_USER || mobConn >= MAX_MOB)
		return;

	if (pMob[mobConn].MOB.Clan != 4)
		return;

	int face = pMob[mobConn].MOB.Equip[0].sIndex;

	if (face < 315 || face >= 345)
		return;

	int Summoner = pMob[mobConn].Summoner;

	if (Summoner <= 0 || Summoner >= MAX_USER)
		return;

	if (pMob[Summoner].Mode == USER_EMPTY)
		return;

	if (pUser[Summoner].Mode != USER_PLAY)
		return;

	int mountId = pMob[Summoner].MOB.Equip[14].sIndex - 2330;
	int mountFace = face - 315;

	if ((face - 315) != mountId)
		return;

	int mountHpItem = pMob[Summoner].MOB.Equip[14].stEffect[0].sValue;
	int mountHp = pMob[mobConn].MOB.CurrentScore.Hp;

	if (mountHpItem == mountHp)
		return;

	pMob[Summoner].MOB.Equip[14].stEffect[0].sValue = mountHp;
	SendItem(Summoner, ITEM_PLACE_EQUIP, 14, &pMob[Summoner].MOB.Equip[14]);
}

void ProcessAdultMount(int conn, int HpLost)
{
	STRUCT_ITEM* MItem = &pMob[conn].MOB.Equip[14];

	if (MItem->sIndex < 2360 || MItem->sIndex >= 2390)
		return;

	int midx = MItem->sIndex - 2360;
	int MMaxHp = mSummon.Mob[midx + 10].CurrentScore.MaxHp;
	int MFeed = 0;
	bool Buff = false;

	//revigorante
	for (int i = 0; i < MAX_AFFECT; i++)
	{
		if (pMob[conn].Affect[i].Type == 51)
			Buff = true;
	}

	if (Buff == true) {
		MFeed = 100;
	}
	else
		MFeed = MItem->stEffect[2].cEffect;

	if (MFeed <= 0 && MItem->stEffect[0].sValue > 0)
	{
		MItem->stEffect[0].sValue = 0;
		MFeed = 0;
	}

	int MHp = MItem->stEffect[0].sValue;
	int MHp2 = MItem->stEffect[0].sValue - HpLost;

	if (MHp2 >= MMaxHp)
		MHp2 = MMaxHp;

	int NMHp = MHp2;

	if (Buff == false)
		MItem->stEffect[0].sValue = NMHp;

	if (MHp2 <= 0)
		MItem->stEffect[2].cEffect = 0;

	if ((MHp <= 0 && MHp2 > 0) || (MHp2 <= 0 && MHp > 0))
		SendEquip(conn, 0);

	if (MHp != MHp2 && conn < MAX_USER)
		SendItem(conn, ITEM_PLACE_EQUIP, 14, &pMob[conn].MOB.Equip[14]);
}

void ProcessBILLMessage(char *pMsg)
{
}

void CheckIdle(int conn)
{
	int ser = SecCounter;
	int lst = pUser[conn].LastReceiveTime;

	if (lst > ser)
		pUser[conn].LastReceiveTime = SecCounter;

	if (lst < ser - 1440)
		pUser[conn].LastReceiveTime = SecCounter;

	if (lst < ser - 720)
	{	
		//sprintf(temp, "sys,disconnect last:%d server:%d mode:%d conn:%d", pUser[conn].LastReceiveTime, SecCounter, pUser[conn].Mode, conn);
		//Log(temp, pUser[conn].AccountName, 0);

		CloseUser(conn);
	}
}

void FinishCastleWar()
{
	SetCastleDoor(1);

	ClearAreaGuild(1036, 1672, 1144, 1764, g_pGuildZone[4].ChargeGuild);

	CastleState = 0;

	for (int i = 0; i < MAX_USER; i++)
	{
		if (pUser[i].Mode != USER_PLAY)
			continue;

		SendClientSignal(i, _MSG_SendCastleState, CastleState);
	}

	for (int i = 0; i < MAX_USER; i++)
	{
		if (pUser[i].Mode != USER_PLAY)
			continue;

		SendClientSignalParm(i, ESCENE_FIELD, _MSG_SendCastleState, CastleState);
	}

	for (int i = MAX_USER; i < MAX_MOB; i++)
	{
		if (pMob[i].Mode == MOB_EMPTY)
			continue;

		if (pMob[i].MOB.Equip[0].sIndex != 219)
			continue;

		DeleteMob(i, 2);
	}

	ClearArea(1036, 1672, 1144, 1764);
}

void RegenMob(int conn)
{
	if (conn > 0 && conn < MAX_USER)
	{
		int Guild = pMob[conn].MOB.Guild;
		if (CastleState <= 1 || pMob[conn].TargetX != 1046 || pMob[conn].TargetY != 1690 || Guild <= 0 || pMob[conn].MOB.GuildLevel != 9 || Guild == g_pGuildZone[4].ChargeGuild)
			pUser[conn].CastleStatus = 0;

		else
		{
			int Citys = 0;

			for (int i = 0; i < ValidGuild; i++)
			{
				if (g_pGuildZone[i].ChargeGuild == pMob[conn].MOB.Guild && i != 4)
					Citys++;
			}

			if (Citys != 0)
			{
				if (pUser[conn].CastleStatus == 0)
				{
					SendNotice(strFmt(g_pMessageStringTable[_SN_S_is_charging_castle], pMob[conn].MOB.MobName));
				}
				MSG_STANDARDPARM sm;
				memset(&sm, 0, sizeof(MSG_STANDARDPARM));

				sm.Type = _MSG_SendCastleState2;
				sm.Size = sizeof(MSG_STANDARDPARM);
				sm.ID = conn;
				sm.Parm = 1;

				GridMulticast(pMob[conn].TargetX, pMob[conn].TargetY, (MSG_STANDARD*)&sm, 0);

				pUser[conn].CastleStatus++;

				if (pUser[conn].CastleStatus > 22)
				{
					SendNotice(strFmt(g_pMessageStringTable[_SN_S_charge_castle], pMob[conn].MOB.MobName));

					g_pGuildZone[4].ChargeGuild = Guild;
					g_pGuildZone[4].Clan = pMob[conn].MOB.Clan;

					FinishCastleWar();

					for (int i = 0; i < MAX_USER; i++)
						ClearCrown(i);
				}
			}
		}

		pUser[conn].Unk_2736++;

		if (!(pUser[conn].Unk_2736 % 450))
		{
			int PKP = GetPKPoint(conn);
			if (PKP < 75)
			{
				PKP++;
				SetPKPoint(conn, PKP);
				SendMsgExp(conn, strFmt(g_pMessageStringTable[_DD_PKPointPlus], PKP - 75, 1), TNColor::Default, false);
			}

			STRUCT_ITEM *Mount = &pMob[conn].MOB.Equip[14];
			if (pMob[conn].MOB.Equip[14].sIndex >= 2300 && Mount->sIndex < 2330)
			{
				int Incubacao = BASE_GetBonusItemAbility(Mount, EF_INCUDELAY);
				if (Incubacao > 0)
				{
					Incubacao--;
					Mount->stEffect[2].cValue = Incubacao;
					SendItem(conn, ITEM_PLACE_EQUIP, 14, &pMob[conn].MOB.Equip[14]);
					 SendMsgExp(conn, g_pMessageStringTable[_NN_Incu_Proceed], TNColor::Default, false);
				}
			}
			if (Mount->sIndex >= 2330 && Mount->sIndex < 2390 && Mount->stEffect[0].sValue > 0)
			{
				int Feed = Mount->stEffect[2].cEffect;
				int MountDiv = Mount->sIndex - 2330 % 30;

				if (MountDiv > 15)
					Feed -= 4;
				else
					Feed -= 2;

				if (Feed > 1)
					Mount->stEffect[2].cEffect = Feed;

				else
				{
					Mount->stEffect[0].sValue = 0;
					Mount->stEffect[2].cEffect = 4;

				 
					SendMsgExp(conn, g_pMessageStringTable[_NN_Mount_died], TNColor::Default, false);
					memcpy(&pMob[conn].MOB.Equip[14], Mount, sizeof(STRUCT_ITEM));

					Mount->stEffect[2].cEffect = 0;

					if (Mount->sIndex >= 2360 && Mount->sIndex < 2390)
						ProcessAdultMount(conn, 0);

					if (Mount->sIndex >= 2360)
						pMob[conn].GetCurrentScore(conn);

					else
						MountProcess(conn, Mount);
				}
				SendItem(conn, ITEM_PLACE_EQUIP, 14, &pMob[conn].MOB.Equip[14]);
			}
		}
		int Guilty = GetGuilty(conn);

		if (Guilty > 0)
		{
			Guilty--;
			SetGuilty(conn, Guilty);

			if (!Guilty)
			{
				MSG_CreateMob CreateMob;
				GetCreateMob(conn, &CreateMob);
				GridMulticast(pMob[conn].TargetX, pMob[conn].TargetY, (MSG_STANDARD*)&CreateMob, 0);

				for (int j = MAX_USER; j < MAX_MOB; j++)
				{
					if (pMob[j].Mode == 5 && pMob[j].MOB.Clan == 4)
					{
						if (pMob[j].CurrentTarget == conn)
						{
							pMob[j].CurrentTarget = 0;
							pMob[j].Mode = 4;
						}
						for (int k = 0; k < MAX_ENEMY; k++)
						{
							if (pMob[j].EnemyList[k] == conn)
							{
								pMob[j].EnemyList[k] = 0;
								pMob[j].Mode = MOB_PEACE;
							}
						}
					}
				}
			}
		}
	}
}

int  ProcessAffect(int idx)
{
	int FadaIndex = FadaIndex = pMob[idx].MOB.Equip[13].sIndex;
	int currentTarget = pMob[idx].CurrentTarget;

	if (idx >= MAX_USER || FadaIndex != 753 && FadaIndex != 769 && FadaIndex != 1726 || currentTarget == 0)
		goto LABEL_59;

	if (currentTarget == idx)
		pMob[idx].CurrentTarget = 0;

#pragma region Fada / Chama Resistente - Attack
	else
	{
		if (currentTarget > 0 && currentTarget < MAX_MOB)
		{
			if (pMob[currentTarget].Mode)
			{
				unsigned char map_att = GetAttribute(pMob[idx].TargetX, pMob[idx].TargetY);

				if (map_att & 0x40 || currentTarget >= MAX_USER && pMob[currentTarget].MOB.Clan != 4)
				{
					if (pUser[idx].PKMode || currentTarget >= MAX_USER)
					{
						int leader = pMob[idx].Leader;
						if (!leader)
							leader = idx;

						int targetleader = pMob[currentTarget].Leader;
						if (!targetleader)
							targetleader = currentTarget;

						int guild = pMob[idx].MOB.Guild;
						if (pMob[idx].GuildDisable)
							guild = 0;

						int mobguild = pMob[currentTarget].MOB.Guild;
						if (pMob[currentTarget].GuildDisable)
							mobguild = 0;

						if (!guild && !mobguild)
							guild = -1;

						if (leader != targetleader && guild != mobguild)
						{
							if (currentTarget < MAX_USER)
							{
								unsigned char map_att2 = GetAttribute(pMob[currentTarget].TargetX, pMob[currentTarget].TargetY);

								if (!(map_att & 0x40))
								{
									pMob[idx].CurrentTarget = 0;
									goto LABEL_59;
								}
								if (pMob[currentTarget].MOB.Rsv & 0x10)
								{
									pMob[idx].CurrentTarget = 0;
									goto LABEL_59;
								}
								if (pMob[currentTarget].MOB.BaseScore.Level >= MAX_LEVEL && pMob[currentTarget].MOB.Merchant & 1)
								{
									pMob[idx].CurrentTarget = 0;
									goto LABEL_59;
								}
							}
							int sameclan = 0;
							int clan = pMob[idx].MOB.Clan;
							int mobclan = pMob[currentTarget].MOB.Clan;

							if (clan == 7 && mobclan == 7 || clan == 8 && mobclan == 8)
								sameclan = 1;

							if ((sameclan != 1 || pUser[idx].PKMode) && (sameclan != 1 || currentTarget < MAX_USER))
							{
								if (pMob[currentTarget].TargetX >= pMob[idx].TargetX - HALFGRIDX
									&& pMob[currentTarget].TargetX <= pMob[idx].TargetX + HALFGRIDX
									&& (pMob[currentTarget].TargetY >= pMob[idx].TargetY - HALFGRIDY || pMob[currentTarget].TargetY <= pMob[idx].TargetY + HALFGRIDY))
								{
									MSG_Attack sm;

									memset(&sm, 0, sizeof(MSG_AttackOne));

									sm.Type = _MSG_AttackOne;
									sm.ID = idx;
									sm.Size = sizeof(MSG_AttackOne);

									//check
									sm.ClientTick = 0xE0A1ACA;
									sm.Motion = 254;

									sm.TargetX = pMob[idx].TargetX;
									sm.TargetY = pMob[idx].TargetY;

									//check
									sm.CurrentMp = -2;
									//check
									sm.AttackerID = idx;

									//check
									sm.SkillIndex = 32;

									if (FadaIndex == 769)
										sm.SkillIndex = 34;
									if (FadaIndex == 1726)
										sm.SkillIndex = 36;

									sm.Dam[0].TargetID = currentTarget;
									sm.Dam[0].Damage = -1;

									ProcessClientMessage(idx, (char*)&sm, TRUE);
								}
								else
									pMob[idx].CurrentTarget = 0;
							}
							goto LABEL_59;
						}
						pMob[idx].CurrentTarget = 0;
					}
					else
						pMob[idx].CurrentTarget = 0;
				}
				else
					pMob[idx].CurrentTarget = 0;
			}
			else
				pMob[idx].CurrentTarget = 0;
		}
		else
			pMob[idx].CurrentTarget = 0;
	}
#pragma endregion
	LABEL_59:

			int regen = 0;
			int upScore = 0;
			int FaceChange = 0;
			int Damage = 0;

			for (int i = 0; i < MAX_AFFECT; i++)
			{
				int Type = pMob[idx].Affect[i].Type;

				if (Type <= 0)
					continue;

				int MaxHp = pMob[idx].MOB.CurrentScore.MaxHp;
				int Hp = pMob[idx].MOB.CurrentScore.Hp;
				int AffectValue = pMob[idx].Affect[i].Value;
				int AffectLevel = pMob[idx].Affect[i].Level;
				int Level = pMob[idx].MOB.CurrentScore.Level;

				if (pMob[idx].extra.ClassMaster != MORTAL && pMob[idx].extra.ClassMaster != ARCH)
					Level += MAX_LEVEL;

#pragma region Regen de HP Aura da Vida
				if (Type == 17)
				{
					Hp += AffectLevel / 2 + AffectValue;

					if (Hp < 1)
						Hp = 1;

					if (Hp > MaxHp)
						Hp = MaxHp;

					if (pMob[idx].MOB.CurrentScore.Hp != Hp)
						upScore = 1;

					Damage = Hp - pMob[idx].MOB.CurrentScore.Hp;

					pMob[idx].MOB.CurrentScore.Hp = Hp;
					regen = 1;
					goto LessAffect;
				}
#pragma endregion
#pragma region Veneno / Sangrar - Drenagem de HP
				if (Type == 20 || Type == 47) //??? Possivelmente Veneno's
				{
					if (idx > 0 && idx < MAX_USER) {
						AffectValue = 100;

						if (idx >= MAX_USER)
							AffectValue -= pMob[idx].MOB.LearnedSkill / MAX_USER;

						AffectValue /= 10;

						int HpLose = (int)((100 - AffectValue) / 100.0);
						int Perda = 1000;

						if (idx >= MAX_USER)
							Perda = 10 * (100 - pMob[idx].MOB.LearnedSkill / MAX_USER);

						int Perdamax = Hp - Perda;

						Hp = (int)((double)Hp * HpLose);

						if (Hp < (signed int)Perdamax)
							Hp = Perdamax;

						if (Hp < 1)
							Hp = 1;

						if (Hp > MaxHp)
							Hp = MaxHp;

						if (pMob[idx].MOB.CurrentScore.Hp != Hp)
							upScore = 1;

						Damage = Hp - pMob[idx].MOB.CurrentScore.Hp;
						pMob[idx].MOB.CurrentScore.Hp = Hp;

						if (idx > 0 && idx < MAX_USER)
							pUser[idx].ReqHp += Damage;

						regen = 1;

						if (idx > MAX_USER && pMob[idx].MOB.Clan == 4)
							LinkMountHp(idx);

						goto LessAffect;
					}
				}
#pragma endregion
#pragma region RegenHP Type21
				/*		if (Type == 21)//Regen de HT
						{
							Hp += AffectValue * MaxHp / 100;

							if (Hp < 1)
								Hp = 1;

							if (Hp > MaxHp)
								Hp = MaxHp;

							if (pMob[idx].MOB.CurrentScore.Hp != Hp)
								upScore = 1;

							Damage = Hp - pMob[idx].MOB.CurrentScore.Hp;

							pMob[idx].MOB.CurrentScore.Hp = Hp;
							regen = 1;

							goto LessAffect;
						}*/
#pragma endregion
#pragma region Trov�o
				if (Type == 22)
				{
					int alvo1 = 0;
					int alvo2 = 0;
					int alvo3 = 0;
					int alvo4 = 0;
					int alvo6 = 0;
					int alvo7 = 0;

					unsigned char map_att = GetAttribute(pMob[idx].TargetX, pMob[idx].TargetY);

					int Clan = pMob[idx].MOB.Clan;

					if (map_att & 1)
						goto LessAffect;

					int yv = pMob[idx].TargetY - 1;
					int xv = pMob[idx].TargetX - 1;
					int leader = pMob[idx].Leader;

					if (leader <= 0)
						leader = idx;

					for (int yy = yv; yy <= (yv + 1); yy++)
					{
						for (int xx = xv; xx <= (xv + 1); xx++)
						{
							if (xx < 0 || xx >= MAX_GRIDX || yy < 0 || yy >= MAX_GRIDY || pMobGrid[yy][xx] <= 0 || pMobGrid[yy][xx] >= MAX_MOB || !pMob[pMobGrid[yy][xx]].Mode || pMob[pMobGrid[yy][xx]].MOB.CurrentScore.Hp <= 0 || leader == pMob[pMobGrid[yy][xx]].Leader)
								continue;

							int tmob = pMobGrid[yy][xx];

							int tclan = pMob[tmob].MOB.Clan;
							int SameClan = 0;

							if (Clan == 7 && tclan == 7 || Clan == 8 && tclan == 8)
								SameClan = 1;

							if (pMob[tmob].MOB.Merchant & 1)
								continue;

							unsigned char map_attack = GetAttribute(xx, yy);

							if (map_attack & 1)
								continue;

							if (idx >= MAX_USER)
								break;

							if ((pUser[idx].PKMode || tmob >= MAX_USER && tclan != 4 && SameClan != 1) && (map_att & 0x40 || tmob >= 100 && tclan != 4 && SameClan != 1) && !(pMob[tmob].MOB.Rsv & 0x10))
							{
								if (SameClan == 1 && tmob >= MAX_USER || tclan == 6 || tmob == idx)
									continue;

								int idxleader = pMob[idx].Leader;

								if (!idxleader)
									idxleader = idx;

								int mobleader = pMob[tmob].Leader;
								if (!mobleader)
									mobleader = tmob;

								int Guild = pMob[idx].MOB.Guild;

								if (pMob[idx].GuildDisable)
									Guild = 0;

								int MobGuild = pMob[tmob].MOB.Guild;

								if (pMob[tmob].GuildDisable)
									MobGuild = 0;

								int Ally = g_pGuildAlly[Guild];

								if (!Ally)
									Ally = -2;

								if (!Guild && !MobGuild)
									Guild = -1;

								if (idxleader == mobleader || Guild == MobGuild || Ally == MobGuild)
									continue;

								if (!alvo1)
								{
									alvo1 = tmob;
									continue;
								}

								if (alvo1 == tmob)
									continue;

								if (!alvo2)
								{
									alvo2 = tmob;
									continue;
								}
								if (alvo2 == tmob)
									continue;

								if (!alvo3)
								{
									alvo3 = tmob;
									continue;
								}
								if (alvo3 == tmob)
									continue;

								if (!alvo4)
								{
									alvo4 = tmob;
									continue;
								}
								if (alvo4 == tmob)
									continue;

								if (!alvo6)
								{
									alvo6 = tmob;
									continue;
								}

								if (alvo6 == tmob || alvo7)
									continue;

								alvo7 = tmob;
							}
						}
					}

					yv = pMob[idx].TargetY - 4;
					xv = pMob[idx].TargetX - 4;


					for (int yy = yv; yy <= (yv + 4); yy++)
					{
						for (int xx = xv; xx <= (xv + 4); xx++)
						{
							if (xx < 0 || xx >= MAX_GRIDX || yy < 0 || yy >= MAX_GRIDY || pMobGrid[yy][xx] <= 0 || pMobGrid[yy][xx] >= MAX_MOB || !pMob[pMobGrid[yy][xx]].Mode || pMob[pMobGrid[yy][xx]].MOB.CurrentScore.Hp <= 0 || leader == pMob[pMobGrid[yy][xx]].Leader)
								continue;

							int tmob = pMobGrid[yy][xx];

							int tclan = pMob[tmob].MOB.Clan;
							int SameClan = 0;

							if (Clan == 7 && tclan == 7 || Clan == 8 && tclan == 8)
								SameClan = 1;

							if (pMob[tmob].MOB.Merchant & 1)
								continue;

							unsigned char map_attack = GetAttribute(xx, yy);

							if (map_attack & 1)
								continue;

							if (idx >= MAX_USER)
								break;

							if ((pUser[idx].PKMode || tmob >= MAX_USER && tclan != 4 && SameClan != 1) && (map_att & 0x40 || tmob >= MAX_USER && tclan != 4 && SameClan != 1) && !(pMob[tmob].MOB.Rsv & 0x10))
							{
								if (SameClan == 1 && tmob >= MAX_USER || tclan == 6 || tmob == idx)
									continue;

								int idxleader = pMob[idx].Leader;

								if (!idxleader)
									idxleader = idx;

								int mobleader = pMob[tmob].Leader;
								if (!mobleader)
									mobleader = tmob;

								int Guild = pMob[idx].MOB.Guild;

								if (pMob[idx].GuildDisable)
									Guild = 0;

								int MobGuild = pMob[tmob].MOB.Guild;

								if (pMob[tmob].GuildDisable)
									MobGuild = 0;

								int Ally = g_pGuildAlly[Guild];

								if (!Ally)
									Ally = -2;

								if (!Guild && !MobGuild)
									Guild = -1;

								if (idxleader == mobleader || Guild == MobGuild || Ally == MobGuild)
									continue;

								if (!alvo1)
								{
									alvo1 = tmob;
									continue;
								}

								if (alvo1 == tmob)
									continue;

								if (!alvo2)
								{
									alvo2 = tmob;
									continue;
								}
								if (alvo2 == tmob)
									continue;

								if (!alvo3)
								{
									alvo3 = tmob;
									continue;
								}
								if (alvo3 == tmob)
									continue;

								if (!alvo4)
								{
									alvo4 = tmob;
									continue;
								}
								if (alvo4 == tmob)
									continue;

								if (!alvo6)
								{
									alvo6 = tmob;
									continue;
								}

								if (alvo6 == tmob || alvo7)
									continue;

								alvo7 = tmob;
							}
						}
					}

					if (alvo1)
					{
						MSG_Attack sm;

						memset(&sm, 0, sizeof(MSG_Attack));

						sm.Type = _MSG_Attack;
						sm.ID = idx;
						sm.Size = sizeof(MSG_Attack);

						sm.ClientTick = 0xE0A1ACA;
						sm.Motion = 254;

						sm.TargetX = pMob[idx].TargetX;
						sm.TargetY = pMob[idx].TargetY;

						sm.CurrentMp = -2;

						if (pMob[idx].MOB.Equip[0].sIndex == 219)
							sm.CurrentMp = -4;

						sm.AttackerID = idx;
						sm.SkillIndex = 33;

						int calc = 500 + rand() % 100 + (pMob[idx].extra.ClassMaster == MORTAL || pMob[idx].extra.ClassMaster == MORTAL ? Level : Level + MAX_CLEVEL) + AffectLevel;

						sm.Dam[0].TargetID = alvo1;
						sm.Dam[0].Damage = -1;

						if (calc > 300)
						{
							sm.Dam[1].TargetID = alvo2;
							sm.Dam[1].Damage = -1;
						}

						if (calc > 350)
						{
							sm.Dam[2].TargetID = alvo3;
							sm.Dam[2].Damage = -1;
						}

						if (calc > 400)
						{
							sm.Dam[3].TargetID = alvo4;
							sm.Dam[3].Damage = -1;
						}

						if (calc > 450)
						{
							sm.Dam[4].TargetID = alvo6;
							sm.Dam[4].Damage = -1;
						}

						if (calc > 500)
						{
							sm.Dam[5].TargetID = alvo7;
							sm.Dam[5].Damage = -1;
						}


						if (idx < MAX_USER)
							ProcessClientMessage(idx, (char*)&sm, TRUE);
					}
				}
#pragma endregion
#pragma region Aura Bestial
				if (Type == 23)
				{
					int alvo1 = 0;
					int alvo2 = 0;
					int alvo3 = 0;
					int alvo4 = 0;
					int alvo6 = 0;
					int alvo7 = 0;

					unsigned char map_att = GetAttribute(pMob[idx].TargetX, pMob[idx].TargetY);

					int Clan = pMob[idx].MOB.Clan;

					if (map_att & 1)
						goto LessAffect;

					int yv = pMob[idx].TargetY - 1;
					int xv = pMob[idx].TargetX - 1;
					int leader = pMob[idx].Leader;

					if (leader <= 0)
						leader = idx;

					for (int yy = yv; yy <= (yv + 1); yy++)
					{
						for (int xx = xv; xx <= (xv + 1); xx++)
						{
							if (xx < 0 || xx >= MAX_GRIDX || yy < 0 || yy >= MAX_GRIDY || pMobGrid[yy][xx] <= 0 || pMobGrid[yy][xx] >= MAX_MOB || !pMob[pMobGrid[yy][xx]].Mode || pMob[pMobGrid[yy][xx]].MOB.CurrentScore.Hp <= 0 || leader == pMob[pMobGrid[yy][xx]].Leader)
								continue;

							int tmob = pMobGrid[yy][xx];

							int tclan = pMob[tmob].MOB.Clan;
							int SameClan = 0;

							if (Clan == 7 && tclan == 7 || Clan == 8 && tclan == 8)
								SameClan = 1;

							if (pMob[tmob].MOB.Merchant & 1)
								continue;

							unsigned char map_attack = GetAttribute(xx, yy);

							if (map_attack & 1)
								continue;

							if (idx >= MAX_USER)
								break;

							if ((pUser[idx].PKMode || tmob >= MAX_USER && tclan != 4 && SameClan != 1) && (map_att & 0x40 || tmob >= 100 && tclan != 4 && SameClan != 1) && !(pMob[tmob].MOB.Rsv & 0x10))
							{
								if (SameClan == 1 && tmob >= MAX_USER || tclan == 6 || tmob == idx)
									continue;

								int idxleader = pMob[idx].Leader;

								if (!idxleader)
									idxleader = idx;

								int mobleader = pMob[tmob].Leader;
								if (!mobleader)
									mobleader = tmob;

								int Guild = pMob[idx].MOB.Guild;

								if (pMob[idx].GuildDisable)
									Guild = 0;

								int MobGuild = pMob[tmob].MOB.Guild;

								if (pMob[tmob].GuildDisable)
									MobGuild = 0;

								int Ally = g_pGuildAlly[Guild];

								if (!Ally)
									Ally = -2;

								if (!Guild && !MobGuild)
									Guild = -1;

								if (idxleader == mobleader || Guild == MobGuild || Ally == MobGuild)
									continue;

								if (!alvo1)
								{
									alvo1 = tmob;
									continue;
								}

								if (alvo1 == tmob)
									continue;

								if (!alvo2)
								{
									alvo2 = tmob;
									continue;
								}
								if (alvo2 == tmob)
									continue;

								if (!alvo3)
								{
									alvo3 = tmob;
									continue;
								}
								if (alvo3 == tmob)
									continue;

								if (!alvo4)
								{
									alvo4 = tmob;
									continue;
								}
								if (alvo4 == tmob)
									continue;

								if (!alvo6)
								{
									alvo6 = tmob;
									continue;
								}

								if (alvo6 == tmob || alvo7)
									continue;

								alvo7 = tmob;
							}
						}
					}

					yv = pMob[idx].TargetY - 4;
					xv = pMob[idx].TargetX - 4;


					for (int yy = yv; yy <= (yv + 4); yy++)
					{
						for (int xx = xv; xx <= (xv + 4); xx++)
						{
							if (xx < 0 || xx >= MAX_GRIDX || yy < 0 || yy >= MAX_GRIDY || pMobGrid[yy][xx] <= 0 || pMobGrid[yy][xx] >= MAX_MOB || !pMob[pMobGrid[yy][xx]].Mode || pMob[pMobGrid[yy][xx]].MOB.CurrentScore.Hp <= 0 || leader == pMob[pMobGrid[yy][xx]].Leader)
								continue;

							int tmob = pMobGrid[yy][xx];

							int tclan = pMob[tmob].MOB.Clan;
							int SameClan = 0;

							if (Clan == 7 && tclan == 7 || Clan == 8 && tclan == 8)
								SameClan = 1;

							if (pMob[tmob].MOB.Merchant & 1)
								continue;

							unsigned char map_attack = GetAttribute(xx, yy);

							if (map_attack & 1)
								continue;

							if (idx >= MAX_USER)
								break;

							if ((pUser[idx].PKMode || tmob >= MAX_USER && tclan != 4 && SameClan != 1) && (map_att & 0x40 || tmob >= MAX_USER && tclan != 4 && SameClan != 1) && !(pMob[tmob].MOB.Rsv & 0x10))
							{
								if (SameClan == 1 && tmob >= MAX_USER || tclan == 6 || tmob == idx)
									continue;

								int idxleader = pMob[idx].Leader;

								if (!idxleader)
									idxleader = idx;

								int mobleader = pMob[tmob].Leader;
								if (!mobleader)
									mobleader = tmob;

								int Guild = pMob[idx].MOB.Guild;

								if (pMob[idx].GuildDisable)
									Guild = 0;

								int MobGuild = pMob[tmob].MOB.Guild;

								if (pMob[tmob].GuildDisable)
									MobGuild = 0;

								int Ally = g_pGuildAlly[Guild];

								if (!Ally)
									Ally = -2;

								if (!Guild && !MobGuild)
									Guild = -1;

								if (idxleader == mobleader || Guild == MobGuild || Ally == MobGuild)
									continue;

								if (!alvo1)
								{
									alvo1 = tmob;
									continue;
								}

								if (alvo1 == tmob)
									continue;

								if (!alvo2)
								{
									alvo2 = tmob;
									continue;
								}
								if (alvo2 == tmob)
									continue;

								if (!alvo3)
								{
									alvo3 = tmob;
									continue;
								}
								if (alvo3 == tmob)
									continue;

								if (!alvo4)
								{
									alvo4 = tmob;
									continue;
								}
								if (alvo4 == tmob)
									continue;

								if (!alvo6)
								{
									alvo6 = tmob;
									continue;
								}

								if (alvo6 == tmob || alvo7)
									continue;

								alvo7 = tmob;
							}
						}
					}

					if (alvo1)
					{
						MSG_Attack sm;

						memset(&sm, 0, sizeof(MSG_Attack));

						sm.Type = _MSG_Attack;
						sm.ID = idx;
						sm.Size = sizeof(MSG_Attack);

						sm.ClientTick = 0xE0A1ACA;
						sm.Motion = 254;

						sm.TargetX = pMob[idx].TargetX;
						sm.TargetY = pMob[idx].TargetY;

						sm.CurrentMp = -2;

						if (pMob[idx].MOB.Equip[0].sIndex == 219)
							sm.CurrentMp = -4;

						sm.AttackerID = idx;
						sm.SkillIndex = 52;

						int calc = 5000 + rand() % 100 + (pMob[idx].extra.ClassMaster == MORTAL || pMob[idx].extra.ClassMaster == MORTAL ? Level : Level + MAX_CLEVEL) + AffectLevel;

						sm.Dam[0].TargetID = alvo1;
						sm.Dam[0].Damage = -1;

						if (calc > 300)
						{
							sm.Dam[1].TargetID = alvo2;
							sm.Dam[1].Damage = -1;
						}

						if (calc > 350)
						{
							sm.Dam[2].TargetID = alvo3;
							sm.Dam[2].Damage = -1;
						}

						if (calc > 400)
						{
							sm.Dam[3].TargetID = alvo4;
							sm.Dam[3].Damage = -1;
						}

						if (calc > 450)
						{
							sm.Dam[4].TargetID = alvo6;
							sm.Dam[4].Damage = -1;
						}

						if (calc > 500)
						{
							sm.Dam[5].TargetID = alvo7;
							sm.Dam[5].Damage = -1;
						}


						if (idx < MAX_USER)
							ProcessClientMessage(idx, (char*)&sm, TRUE);
					}
				}
#pragma endregion
#pragma region Aura Bestial
				if (Type == 23)
				{
					int alvo1 = 0;
					int alvo2 = 0;
					int alvo3 = 0;
					int alvo4 = 0;
					int alvo6 = 0;
					int alvo7 = 0;

					unsigned char map_att = GetAttribute(pMob[idx].TargetX, pMob[idx].TargetY);

					int Clan = pMob[idx].MOB.Clan;

					if (map_att & 1)
						goto LessAffect;

					int yv = pMob[idx].TargetY - 1;
					int xv = pMob[idx].TargetX - 1;
					int leader = pMob[idx].Leader;

					if (leader <= 0)
						leader = idx;

					for (int yy = yv; yy <= (yv + 1); yy++)
					{
						for (int xx = xv; xx <= (xv + 1); xx++)
						{
							if (xx < 0 || xx >= MAX_GRIDX || yy < 0 || yy >= MAX_GRIDY || pMobGrid[yy][xx] <= 0 || pMobGrid[yy][xx] >= MAX_MOB || !pMob[pMobGrid[yy][xx]].Mode || pMob[pMobGrid[yy][xx]].MOB.CurrentScore.Hp <= 0 || leader == pMob[pMobGrid[yy][xx]].Leader)
								continue;

							int tmob = pMobGrid[yy][xx];

							int tclan = pMob[tmob].MOB.Clan;
							int SameClan = 0;

							if (Clan == 7 && tclan == 7 || Clan == 8 && tclan == 8)
								SameClan = 1;

							if (pMob[tmob].MOB.Merchant & 1)
								continue;

							unsigned char map_attack = GetAttribute(xx, yy);

							if (map_attack & 1)
								continue;

							if (idx >= MAX_USER)
								break;

							if ((pUser[idx].PKMode || tmob >= MAX_USER && tclan != 4 && SameClan != 1) && (map_att & 0x40 || tmob >= 100 && tclan != 4 && SameClan != 1) && !(pMob[tmob].MOB.Rsv & 0x10))
							{
								if (SameClan == 1 && tmob >= MAX_USER || tclan == 6 || tmob == idx)
									continue;

								int idxleader = pMob[idx].Leader;

								if (!idxleader)
									idxleader = idx;

								int mobleader = pMob[tmob].Leader;
								if (!mobleader)
									mobleader = tmob;

								int Guild = pMob[idx].MOB.Guild;

								if (pMob[idx].GuildDisable)
									Guild = 0;

								int MobGuild = pMob[tmob].MOB.Guild;

								if (pMob[tmob].GuildDisable)
									MobGuild = 0;

								int Ally = g_pGuildAlly[Guild];

								if (!Ally)
									Ally = -2;

								if (!Guild && !MobGuild)
									Guild = -1;

								if (idxleader == mobleader || Guild == MobGuild || Ally == MobGuild)
									continue;

								if (!alvo1)
								{
									alvo1 = tmob;
									continue;
								}

								if (alvo1 == tmob)
									continue;

								if (!alvo2)
								{
									alvo2 = tmob;
									continue;
								}
								if (alvo2 == tmob)
									continue;

								if (!alvo3)
								{
									alvo3 = tmob;
									continue;
								}
								if (alvo3 == tmob)
									continue;

								if (!alvo4)
								{
									alvo4 = tmob;
									continue;
								}
								if (alvo4 == tmob)
									continue;

								if (!alvo6)
								{
									alvo6 = tmob;
									continue;
								}

								if (alvo6 == tmob || alvo7)
									continue;

								alvo7 = tmob;
							}
						}
					}

					yv = pMob[idx].TargetY - 4;
					xv = pMob[idx].TargetX - 4;


					for (int yy = yv; yy <= (yv + 4); yy++)
					{
						for (int xx = xv; xx <= (xv + 4); xx++)
						{
							if (xx < 0 || xx >= MAX_GRIDX || yy < 0 || yy >= MAX_GRIDY || pMobGrid[yy][xx] <= 0 || pMobGrid[yy][xx] >= MAX_MOB || !pMob[pMobGrid[yy][xx]].Mode || pMob[pMobGrid[yy][xx]].MOB.CurrentScore.Hp <= 0 || leader == pMob[pMobGrid[yy][xx]].Leader)
								continue;

							int tmob = pMobGrid[yy][xx];

							int tclan = pMob[tmob].MOB.Clan;
							int SameClan = 0;

							if (Clan == 7 && tclan == 7 || Clan == 8 && tclan == 8)
								SameClan = 1;

							if (pMob[tmob].MOB.Merchant & 1)
								continue;

							unsigned char map_attack = GetAttribute(xx, yy);

							if (map_attack & 1)
								continue;

							if (idx >= MAX_USER)
								break;

							if ((pUser[idx].PKMode || tmob >= MAX_USER && tclan != 4 && SameClan != 1) && (map_att & 0x40 || tmob >= MAX_USER && tclan != 4 && SameClan != 1) && !(pMob[tmob].MOB.Rsv & 0x10))
							{
								if (SameClan == 1 && tmob >= MAX_USER || tclan == 6 || tmob == idx)
									continue;

								int idxleader = pMob[idx].Leader;

								if (!idxleader)
									idxleader = idx;

								int mobleader = pMob[tmob].Leader;
								if (!mobleader)
									mobleader = tmob;

								int Guild = pMob[idx].MOB.Guild;

								if (pMob[idx].GuildDisable)
									Guild = 0;

								int MobGuild = pMob[tmob].MOB.Guild;

								if (pMob[tmob].GuildDisable)
									MobGuild = 0;

								int Ally = g_pGuildAlly[Guild];

								if (!Ally)
									Ally = -2;

								if (!Guild && !MobGuild)
									Guild = -1;

								if (idxleader == mobleader || Guild == MobGuild || Ally == MobGuild)
									continue;

								if (!alvo1)
								{
									alvo1 = tmob;
									continue;
								}

								if (alvo1 == tmob)
									continue;

								if (!alvo2)
								{
									alvo2 = tmob;
									continue;
								}
								if (alvo2 == tmob)
									continue;

								if (!alvo3)
								{
									alvo3 = tmob;
									continue;
								}
								if (alvo3 == tmob)
									continue;

								if (!alvo4)
								{
									alvo4 = tmob;
									continue;
								}
								if (alvo4 == tmob)
									continue;

								if (!alvo6)
								{
									alvo6 = tmob;
									continue;
								}

								if (alvo6 == tmob || alvo7)
									continue;

								alvo7 = tmob;
							}
						}
					}

					if (alvo1)
					{
						MSG_Attack sm;

						memset(&sm, 0, sizeof(MSG_Attack));

						sm.Type = _MSG_Attack;
						sm.ID = idx;
						sm.Size = sizeof(MSG_Attack);

						sm.ClientTick = 0xE0A1ACA;
						sm.Motion = 254;

						sm.TargetX = pMob[idx].TargetX;
						sm.TargetY = pMob[idx].TargetY;

						sm.CurrentMp = -2;

						if (pMob[idx].MOB.Equip[0].sIndex == 219)
							sm.CurrentMp = -4;

						sm.AttackerID = idx;
						sm.SkillIndex = 52;

						int calc = 5000 + rand() % 100 + (pMob[idx].extra.ClassMaster == MORTAL || pMob[idx].extra.ClassMaster == MORTAL ? Level : Level + MAX_CLEVEL) + AffectLevel;

						sm.Dam[0].TargetID = alvo1;
						sm.Dam[0].Damage = -1;

						if (calc > 300)
						{
							sm.Dam[1].TargetID = alvo2;
							sm.Dam[1].Damage = -1;
						}

						if (calc > 350)
						{
							sm.Dam[2].TargetID = alvo3;
							sm.Dam[2].Damage = -1;
						}

						if (calc > 400)
						{
							sm.Dam[3].TargetID = alvo4;
							sm.Dam[3].Damage = -1;
						}

						if (calc > 450)
						{
							sm.Dam[4].TargetID = alvo6;
							sm.Dam[4].Damage = -1;
						}

						if (calc > 500)
						{
							sm.Dam[5].TargetID = alvo7;
							sm.Dam[5].Damage = -1;
						}


						if (idx < MAX_USER)
							ProcessClientMessage(idx, (char*)&sm, TRUE);
					}
				}
#pragma endregion
#pragma region Chama Resistente
				if (Type == 46)
				{
					int alvo1 = 0;

					unsigned char map_att = GetAttribute(pMob[idx].TargetX, pMob[idx].TargetY);

					int Clan = pMob[idx].MOB.Clan;

					if (map_att & 1)
						goto LessAffect;

					int yv = pMob[idx].TargetY - 1;
					int xv = pMob[idx].TargetX - 1;
					int leader = pMob[idx].Leader;

					if (leader <= 0)
						leader = idx;

					for (int yy = yv; yy <= (yv + 1); yy++)
					{
						for (int xx = xv; xx <= (xv + 1); xx++)
						{
							if (xx < 0 || xx >= MAX_GRIDX || yy < 0 || yy >= MAX_GRIDY || pMobGrid[yy][xx] <= 0 || pMobGrid[yy][xx] >= MAX_MOB || !pMob[pMobGrid[yy][xx]].Mode || pMob[pMobGrid[yy][xx]].MOB.CurrentScore.Hp <= 0 || leader == pMob[pMobGrid[yy][xx]].Leader)
								continue;

							int tmob = pMobGrid[yy][xx];

							int tclan = pMob[tmob].MOB.Clan;
							int SameClan = 0;

							if (Clan == 7 && tclan == 7 || Clan == 8 && tclan == 8)
								SameClan = 1;

							if (pMob[tmob].MOB.Merchant & 1)
								continue;

							unsigned char map_attack = GetAttribute(xx, yy);

							if (map_attack & 1)
								continue;

							if (idx >= MAX_USER)
								break;

							if ((pUser[idx].PKMode || tmob >= MAX_USER && tclan != 4 && SameClan != 1) && (map_att & 0x40 || tmob >= 100 && tclan != 4 && SameClan != 1) && !(pMob[tmob].MOB.Rsv & 0x10))
							{
								if (SameClan == 1 && tmob >= MAX_USER || tclan == 6 || tmob == idx)
									continue;

								int idxleader = pMob[idx].Leader;

								if (!idxleader)
									idxleader = idx;

								int mobleader = pMob[tmob].Leader;
								if (!mobleader)
									mobleader = tmob;

								int Guild = pMob[idx].MOB.Guild;

								if (pMob[idx].GuildDisable)
									Guild = 0;

								int MobGuild = pMob[tmob].MOB.Guild;

								if (pMob[tmob].GuildDisable)
									MobGuild = 0;

								int Ally = g_pGuildAlly[Guild];

								if (!Ally)
									Ally = -2;

								if (!Guild && !MobGuild)
									Guild = -1;

								if (idxleader == mobleader || Guild == MobGuild || Ally == MobGuild)
									continue;

								if (!alvo1)
								{
									alvo1 = tmob;
									continue;
								}

								if (alvo1 == tmob)
									continue;
							}
						}
					}

					yv = pMob[idx].TargetY - 4;
					xv = pMob[idx].TargetX - 4;


					for (int yy = yv; yy <= (yv + 4); yy++)
					{
						for (int xx = xv; xx <= (xv + 4); xx++)
						{
							if (xx < 0 || xx >= MAX_GRIDX || yy < 0 || yy >= MAX_GRIDY || pMobGrid[yy][xx] <= 0 || pMobGrid[yy][xx] >= MAX_MOB || !pMob[pMobGrid[yy][xx]].Mode || pMob[pMobGrid[yy][xx]].MOB.CurrentScore.Hp <= 0 || leader == pMob[pMobGrid[yy][xx]].Leader)
								continue;

							int tmob = pMobGrid[yy][xx];

							int tclan = pMob[tmob].MOB.Clan;
							int SameClan = 0;

							if (Clan == 7 && tclan == 7 || Clan == 8 && tclan == 8)
								SameClan = 1;

							if (pMob[tmob].MOB.Merchant & 1)
								continue;

							unsigned char map_attack = GetAttribute(xx, yy);

							if (map_attack & 1)
								continue;

							if (idx >= MAX_USER)
								break;

							if ((pUser[idx].PKMode || tmob >= MAX_USER && tclan != 4 && SameClan != 1) && (map_att & 0x40 || tmob >= MAX_USER && tclan != 4 && SameClan != 1) && !(pMob[tmob].MOB.Rsv & 0x10))
							{
								if (SameClan == 1 && tmob >= MAX_USER || tclan == 6 || tmob == idx)
									continue;

								int idxleader = pMob[idx].Leader;

								if (!idxleader)
									idxleader = idx;

								int mobleader = pMob[tmob].Leader;
								if (!mobleader)
									mobleader = tmob;

								int Guild = pMob[idx].MOB.Guild;

								if (pMob[idx].GuildDisable)
									Guild = 0;

								int MobGuild = pMob[tmob].MOB.Guild;

								if (pMob[tmob].GuildDisable)
									MobGuild = 0;

								int Ally = g_pGuildAlly[Guild];

								if (!Ally)
									Ally = -2;

								if (!Guild && !MobGuild)
									Guild = -1;

								if (idxleader == mobleader || Guild == MobGuild || Ally == MobGuild)
									continue;

								if (!alvo1)
								{
									alvo1 = tmob;
									continue;
								}

								if (alvo1 == tmob)
									continue;
							}
						}
					}

					if (alvo1)
					{
						MSG_Attack sm;

						memset(&sm, 0, sizeof(MSG_AttackOne));

						sm.Type = _MSG_AttackOne;
						sm.ID = idx;
						sm.Size = sizeof(MSG_AttackOne);

						sm.ClientTick = 0xE0A1ACA;
						sm.Motion = 254;

						sm.TargetX = pMob[idx].TargetX;
						sm.TargetY = pMob[idx].TargetY;

						sm.CurrentMp = -2;

						sm.AttackerID = idx;
						sm.SkillIndex = 48;

						//int calc = 500 + rand() % 100 + (pMob[idx].extra.ClassMaster == MORTAL || pMob[idx].extra.ClassMaster == MORTAL ? Level : Level + MAX_CLEVEL) + AffectLevel;

						sm.Dam[0].TargetID = alvo1;
						sm.Dam[0].Damage = -1;

						if (idx < MAX_USER)
							ProcessClientMessage(idx, (char*)&sm, TRUE);
					}
				}
#pragma endregion
#pragma region Affects less time
				LessAffect :
						   if (pMob[idx].Affect[i].Time < 32400000)
							   pMob[idx].Affect[i].Time--;


						   if (pMob[idx].Affect[i].Time <= 0)
						   {
							   if (pMob[idx].Affect[i].Type == 16 || pMob[idx].Affect[i].Type == 33)
								   FaceChange = 1;

							   pMob[idx].Affect[i].Type = 0;
							   pMob[idx].Affect[i].Time = 0;
							   pMob[idx].Affect[i].Value = 0;
							   pMob[idx].Affect[i].Level = 0;
							   upScore = 1;
						   }
#pragma endregion
			}

			if (regen)
			{
				if (idx > 0 && idx < MAX_USER)
				{
					SetReqHp(idx);
					SetReqMp(idx);
				}
				MSG_SetHpDam dam;

				dam.Type = _MSG_SetHpDam;
				dam.Size = sizeof(MSG_SetHpDam);
				dam.ID = idx;

				dam.Hp = pMob[idx].MOB.CurrentScore.Hp;
				dam.Dam = Damage;

				GridMulticast(pMob[idx].TargetX, pMob[idx].TargetY, (MSG_STANDARD*)&dam, 0);
			}
			if (upScore)
			{
				pMob[idx].GetCurrentScore(idx);
				SendScore(idx);

				if (FaceChange)
					SendEquip(idx, 0);

				return TRUE;
			}
			else
				return 0;

			return 0;
}

void SendDamage(int x1, int y1, int x2, int y2)
{
	for (int i = 0; i < MAX_USER; i++)
	{
		if (pUser[i].Mode != USER_PLAY)
			continue;

		if (pMob[i].MOB.CurrentScore.Hp <= 0)
			continue;

		if (pMob[i].TargetX < x1 || pMob[i].TargetX > x2 || pMob[i].TargetY < y1 || pMob[i].TargetY > y2)
			continue;

		int UNK = 1048576000;

		int dam_base = 2000;

		int hp = pMob[i].MOB.CurrentScore.Hp;

		if (hp < dam_base)
			dam_base = hp - 1;

		int dam = hp - dam_base;


		if (hp < dam_base)
			dam = hp;

		if (hp < 1)
			dam = 1;

		int req_hp = dam - pMob[i].MOB.CurrentScore.Hp;

		pMob[i].MOB.CurrentScore.Hp = dam;

		pUser[i].ReqHp = dam;

		SetReqHp(i);
		SetReqMp(i);

		MSG_SetHpDam sm;
		memset(&sm, 0, sizeof(MSG_SetHpDam));

		sm.Type = _MSG_SetHpDam;
		sm.Size = sizeof(MSG_SetHpDam);
		sm.ID = i;

		sm.Hp = dam;
		sm.Dam = req_hp;

		GridMulticast(pMob[i].TargetX, pMob[i].TargetY, (MSG_STANDARD*)&sm, 0);
	}
}

void SendDamageKingdom(int x1, int y1, int x2, int y2, int Clan)
{
	for (int i = 0; i < MAX_USER; i++)
	{
		if (pUser[i].Mode != USER_PLAY)
			continue;

		if (pMob[i].MOB.CurrentScore.Hp <= 0)
			continue;

		if (pMob[i].TargetX < x1 || pMob[i].TargetX > x2 || pMob[i].TargetY < y1 || pMob[i].TargetY > y2)
			continue;

		if (pMob[i].MOB.Clan == Clan)
			continue;

		int UNK = 1048576000;

		int dam_base = pMob[i].MOB.CurrentScore.MaxHp / 10;

		int hp = pMob[i].MOB.CurrentScore.Hp;

		if (hp < dam_base)
			dam_base = hp - 1;

		int dam = hp - dam_base;


		if (hp < dam_base)
			dam = hp;

		if (hp < 1)
			dam = 1;

		int req_hp = dam - pMob[i].MOB.CurrentScore.Hp;

		pMob[i].MOB.CurrentScore.Hp = dam;

		pUser[i].ReqHp = dam;

		SetReqHp(i);
		SetReqMp(i);

		MSG_SetHpDam sm;
		memset(&sm, 0, sizeof(MSG_SetHpDam));

		sm.Type = _MSG_SetHpDam;
		sm.Size = sizeof(MSG_SetHpDam);
		sm.ID = i;

		sm.Hp = dam;
		sm.Dam = req_hp;

		GridMulticast(pMob[i].TargetX, pMob[i].TargetY, (MSG_STANDARD*)&sm, 0);
	}
}

void SendDamageLeader(int x1, int y1, int x2, int y2)
{
	int HaveUser = 0;

	for (int x = x1; x < x2; x++)
	{
		for (int y = y1; y < y2; y++)
		{
			if (x < 0 || x >= MAX_GRIDX || y < 0 || y >= MAX_GRIDY)
				continue;

			if (pMobGrid[y][x] == 0)
				continue;

			if (pMobGrid[y][x] >= MAX_USER)
				continue;

			int tmob = pMobGrid[y][x];

			if (tmob == Pista[4].Party[0].LeaderID)
			{
				HaveUser++;
				continue;
			}

			if (tmob == Pista[4].Party[1].LeaderID)
			{
				HaveUser++;
				continue;
			}
			if (tmob == Pista[4].Party[1].LeaderID)
			{
				HaveUser++;
				continue;
			}
		}
	}

	if (HaveUser)
		return;

	for (int i = 0; i < MAX_USER; i++)
	{
		if (pUser[i].Mode != USER_PLAY)
			continue;

		if (pMob[i].MOB.CurrentScore.Hp <= 0)
			continue;

		if (pMob[i].TargetX < x1 || pMob[i].TargetX > x2 || pMob[i].TargetY < y1 || pMob[i].TargetY > y2)
			continue;

		int UNK = 1048576000;

		int dam_base = 2000;

		int hp = pMob[i].MOB.CurrentScore.Hp;

		if (hp < dam_base)
			dam_base = hp - 1;

		int dam = hp - dam_base;


		if (hp < dam_base)
			dam = hp;

		if (hp < 1)
			dam = 1;

		int req_hp = dam - pMob[i].MOB.CurrentScore.Hp;

		pMob[i].MOB.CurrentScore.Hp = dam;

		pUser[i].ReqHp = dam;

		SetReqHp(i);
		SetReqMp(i);

		MSG_SetHpDam sm;
		memset(&sm, 0, sizeof(MSG_SetHpDam));

		sm.Type = _MSG_SetHpDam;
		sm.Size = sizeof(MSG_SetHpDam);
		sm.ID = i;

		sm.Hp = dam;
		sm.Dam = req_hp;

		GridMulticast(pMob[i].TargetX, pMob[i].TargetY, (MSG_STANDARD*)&sm, 0);
	}
}

void SummonGuild2(int Guild, int tx, int ty, int maxsummon, int village)
{
	if (Guild <= 0)
		return;

	int summons = 0;

	for (int i = 0; i < MAX_USER; i++)
	{
		if (pUser[i].Mode != USER_PLAY || pMob[i].Mode == USER_EMPTY)
			continue;

		if (pMob[i].MOB.Guild != Guild)
			continue;

		if (pUser[i].OnlyTrade)
			continue;

		if (village < 1 || village > 3 || BASE_GetVillage(pMob[i].TargetX, pMob[i].TargetY) == village)
		{
			DoTeleport(i, tx, ty);

			summons++;

			if (summons == 30)
			{
				tx++;
				ty++;
			}

			if (summons == 45)
			{
				tx = tx - 2;
				ty = ty - 2;
			}

			if (summons >= maxsummon)
				break;
		}
	}
}

void SendItemagrupar(const int client, int itemID)
{

	int x = 0;
	int invfree = 0;
	int i = 0;
	int j = 0;

	//Verificar espa�o no invent�rio
	for (x = 0; x < pMob[client].MaxCarry; x++)
	{
		if (pMob[client].MOB.Carry[x].sIndex == 0)
			invfree++;
	}

	if (invfree < 1)
	{
		for (j = 0; j < pMob[client].MaxCarry; j++)
		{
			if (pMob[client].MOB.Carry[j].sIndex != itemID)
				continue;

			break;
		}

		if (j != pMob[client].MaxCarry)
		{

			for (i = 0; i < pMob[client].MaxCarry; i++)
			{
				if (pMob[client].MOB.Carry[i].sIndex == itemID && pMob[client].MOB.Carry[i].stEffect[0].cValue < 120)
				{
					int amount = BASE_GetItemAmount(&pMob[client].MOB.Carry[i]);

					if (amount < 120)
						BASE_SetItemAmount(&pMob[client].MOB.Carry[i], amount + 1);

					SendItem(client, ITEM_PLACE_CARRY, i, &pMob[client].MOB.Carry[i]);

					return;
				}



			}

		}
		SendClientMessage(client, "Seu invent�rio est� cheio");

		return;
	}

	for (j = 0; j < pMob[client].MaxCarry; j++)
	{
		if (pMob[client].MOB.Carry[j].sIndex != itemID)
			continue;

		break;
	}


	if (j != pMob[client].MaxCarry)
	{

		for (i = 0; i < pMob[client].MaxCarry; i++)
		{
			if (pMob[client].MOB.Carry[i].sIndex == itemID && pMob[client].MOB.Carry[i].stEffect[0].cValue < 120)
			{
				int amount = BASE_GetItemAmount(&pMob[client].MOB.Carry[i]);

				if (amount < 120)
					BASE_SetItemAmount(&pMob[client].MOB.Carry[i], amount + 1);

				SendItem(client, ITEM_PLACE_CARRY, i, &pMob[client].MOB.Carry[i]);

				return;
			}



		}

	}
	sendeitempremio(client, itemID, 1);
	return;
}

void sendeitempremio(const int client, int itemID, int valor)
{

	STRUCT_ITEM Item;
	memset(&Item, 0, sizeof(STRUCT_ITEM));

	int x = 0;
	int invfree = 0;

	//Verificar espa�o no invent�rio
	for (x = 0; x < pMob[client].MaxCarry; x++)
	{
		if (pMob[client].MOB.Carry[x].sIndex == 0)
			invfree++;
	}

	if (invfree < 1)
	{
		SendClientMessage(client, "Seu invent�rio est� cheio");
		pUser[client].TimeLojinha = 0;
		return;
	}


	Item.sIndex = itemID;
	Item.stEffect[0].cEffect = 61;
	Item.stEffect[0].cValue = valor;

	//entegrar item
	PutItem(client, &Item);
	//sprintf(temp, "!Chegou um item [%s]", g_pItemList[Item.sIndex].Name);
	//SendClientMessage(client, temp);
	SendScore(client);
	//SaveUser(conn, 0);
	//pUser[client].TimeLoja = 0;

	return;
}


void SummonGuild(int Guild, int tx, int ty, int maxsummon, int village)
{
	if (Guild <= 0)
		return;

	int summons = 0;

	for (int i = 0; i < MAX_USER; i++)
	{
		if (pUser[i].Mode != USER_PLAY || pMob[i].Mode == USER_EMPTY)
			continue;

		if (pMob[i].MOB.Guild != Guild)
			continue;

		if (pUser[i].OnlyTrade)
			continue;

		if (village && village != 1 && village != 3 || BASE_GetVillage(pMob[i].TargetX, pMob[i].TargetY) == village)
		{
			if (village != 2 || pMob[i].extra.ClassMaster == MORTAL)
			{
				DoTeleport(i, tx, ty);

				summons++;

				if (summons == 30)
				{
					tx++;
					ty++;
				}

				if (summons == 45)
				{
					tx = tx - 2;
					ty = ty - 2;
				}

				if (summons >= maxsummon)
					break;
			}
			else
		 
			SendMsgExp(i, g_pMessageStringTable[_NN_3rd_village_limit], TNColor::Default, false);
		}
	}
}

void ClearAreaQuest(int conn, int x1, int y1, int x2, int y2)
{
	for (int i = 0; i < MAX_USER; i++)
	{

		if (pUser[conn].Mode != USER_PLAY)
			continue;

		if (pMob[conn].Mode == USER_EMPTY)
			continue;

		if (pMob[conn].TargetX < x1 || pMob[conn].TargetX > x2 || pMob[conn].TargetY < y1 || pMob[conn].TargetY > y2)
			continue;

		if (pMob[conn].MOB.CurrentScore.Hp <= 0)
		{
			pMob[conn].MOB.CurrentScore.Hp = 2;
			SendScore(conn);
		}

		pMob[conn].QuestFlag = 0;
		pMob[conn].extra.CheckTimeKersef = 0;
		pMob[conn].CheckQuest = 0;
		//pMob[conn].MOB.CheckQuestisDead = FALSE;
		DoRecall(conn);
	}
}
void ClearAreaQuestold(int x1, int y1, int x2, int y2)
{
	for (int i = 0; i < MAX_USER; i++)
	{
		if (pUser[i].Mode != USER_PLAY)
			continue;

		if (pMob[i].Mode == USER_EMPTY)
			continue;

		if (pMob[i].TargetX < x1 || pMob[i].TargetX > x2 || pMob[i].TargetY < y1 || pMob[i].TargetY > y2)
			continue;

		if (pMob[i].MOB.CurrentScore.Hp <= 0)
		{
			pMob[i].MOB.CurrentScore.Hp = 2;
			SendScore(i);
		}

		pMob[i].QuestFlag = 0;
		DoRecall(i);
	}
}

void ClearMobArea(int x1, int y1, int x2, int y2)
{
	for (int i = MAX_USER; i < MAX_MOB; i++)
	{
		if (pMob[i].Mode == USER_EMPTY)
			continue;

		if (pMob[i].TargetX < x1 || pMob[i].TargetX > x2 || pMob[i].TargetY < y1 || pMob[i].TargetY > y2)
			continue;

		DeleteMob(i, 1);
	}
}

void ClearArea(int x1, int y1, int x2, int y2)
{
	for (int i = 0; i < MAX_USER; i++)
	{
		if (pUser[i].Mode != USER_PLAY)
			continue;

		if (pMob[i].Mode == USER_EMPTY)
			continue;

		if (pMob[i].TargetX < x1 || pMob[i].TargetX > x2 || pMob[i].TargetY < y1 || pMob[i].TargetY > y2)
			continue;

		if (pMob[i].MOB.CurrentScore.Hp <= 0)
		{
			pMob[i].MOB.CurrentScore.Hp = 2;
			SendScore(i);
		}
		pUser[i].CaptchaDelay = GetTickCount64();

		pMob[i].QuestFlag = 0;
		pMob[i].LanNFlag = 0;
		pMob[i].LanMFlag = 0;
		pMob[i].LanAFlag = 0;
		DoRecall(i);
	}
}

void ClearAreaNoVip(int x1, int y1, int x2, int y2)
{
	for (int i = 0; i < MAX_USER; i++)
	{
		if (pUser[i].Mode != USER_PLAY)
			continue;

		if (pMob[i].Mode == USER_EMPTY)
			continue;

		if (pMob[i].TargetX < x1 || pMob[i].TargetX > x2 || pMob[i].TargetY < y1 || pMob[i].TargetY > y2)
			continue;

		if (pMob[i].MOB.CurrentScore.Hp <= 0)
		{
			pMob[i].MOB.CurrentScore.Hp = 2;
			SendScore(i);
		}

		if (pUser[i].Keys[1] == 1)
			continue;

		DoRecall(i);
	}
}

void ClearAreaVip(int x1, int y1, int x2, int y2)
{
	for (int i = 0; i < MAX_USER; i++)
	{
		if (pUser[i].Keys[1] == 0)
			continue;

		if (pUser[i].Mode != USER_PLAY)
			continue;

		if (pMob[i].Mode == USER_EMPTY)
			continue;

		if (pMob[i].TargetX < x1 || pMob[i].TargetX > x2 || pMob[i].TargetY < y1 || pMob[i].TargetY > y2)
			continue;

		if (pMob[i].MOB.CurrentScore.Hp <= 0)
		{
			pMob[i].MOB.CurrentScore.Hp = 2;
			SendScore(i);
		}
		DoRecall(i);
	}
}

void ClearAreaLevel(int x1, int y1, int x2, int y2, int minLv, int maxLv)
{
	for (int i = 0; i < MAX_USER; i++)
	{
		if (pUser[i].Mode != USER_PLAY)
			continue;

		if (pMob[i].Mode == USER_EMPTY)
			continue;

		if (pMob[i].TargetX < x1 || pMob[i].TargetX > x2 || pMob[i].TargetY < y1 || pMob[i].TargetY > y2)
			continue;

		if (pMob[i].MOB.CurrentScore.Level < minLv)
			continue;

		if (pMob[i].MOB.CurrentScore.Level > maxLv)
			continue;

		if (pMob[i].MOB.CurrentScore.Hp <= 0)
		{
			pMob[i].MOB.CurrentScore.Hp = 2;
			SendScore(i);
		}

		DoRecall(i);
	}
}

void ClearAreaGuild(int x1, int y1, int x2, int y2, int Guild)
{
	for (int i = 0; i < MAX_USER; i++)
	{
		if (pUser[i].Mode != USER_PLAY)
			continue;

		if (pMob[i].Mode == USER_EMPTY)
			continue;

		if (pMob[i].TargetX < x1 || pMob[i].TargetX > x2 || pMob[i].TargetY < y1 || pMob[i].TargetY > y2)
			continue;

		if (pMob[i].MOB.Guild == Guild)
			continue;

		if (pMob[i].MOB.CurrentScore.Hp <= 0)
		{
			pMob[i].MOB.CurrentScore.Hp = 2;
			SendScore(i);
		}

		DoRecall(i);
	}
}

void ClearAreaTeleport(int x1, int y1, int x2, int y2, int tx, int ty)
{
	for (int i = 0; i < MAX_USER; i++)
	{
		if (pUser[i].Mode != USER_PLAY)
			continue;

		if (pMob[i].Mode == USER_EMPTY)
			continue;

		if (pMob[i].TargetX < x1 || pMob[i].TargetX > x2 || pMob[i].TargetY < y1 || pMob[i].TargetY > y2)
			continue;

		if (pMob[i].MOB.CurrentScore.Hp <= 0)
		{
			pMob[i].MOB.CurrentScore.Hp = 1;

			SendScore(i);
		}
		/*
		if(rand()%1 == 0)
			tx -= rand()%3;
		else
			tx += rand()%3;

		if(rand()%1 == 0)
			ty -= rand()%3;
		else
			ty += rand()%3;
*/
		DoTeleport(i, tx, ty);
	}
}

void ClearGuildPKZone()
{
	int x1 = 128;
	int y1 = 128;

	int x2 = 256;
	int y2 = 256;

	for (int i = 0; i < MAX_USER; i++)
	{
		if (pUser[i].Mode != USER_PLAY)
			continue;

		if (pMob[i].Mode == 0)
			continue;

		if (pMob[i].TargetX >= x1 && pMob[i].TargetX <= x2 && pMob[i].TargetY >= y1 && pMob[i].TargetY <= y2)
			DoRecall(i);
	}
}

void SetBigCuboDoor(int state)
{
	int gate = 0;

	int height = 0;

	for (int i = 0; i < 10; i++)
	{
		gate = i + 49;

		if (pItem[i + 49].ITEM.sIndex <= 0 || pItem[gate].ITEM.sIndex >= MAX_ITEMLIST)
			continue;

		if (pItem[gate].State == state)
			continue;

		UpdateItem(gate, state, &height);

		if (state == 1)
		{
			MSG_UpdateItem sm;
			memset(&sm, 0, sizeof(MSG_UpdateItem));

			sm.ID = ESCENE_FIELD;
			sm.Type = _MSG_UpdateItem;

			sm.ItemID = gate + 10000;

			sm.Size = sizeof(MSG_UpdateItem);

			//		sm.Height = height;
			sm.State = pItem[gate].State;

			GridMulticast(pItem[gate].PosX, pItem[gate].PosY, (MSG_STANDARD*)&sm, 0);
		}
		else
		{
			MSG_CreateItem sm;
			memset(&sm, 0, sizeof(MSG_CreateItem));

			GetCreateItem(gate, &sm);

			GridMulticast(pItem[gate].PosX, pItem[gate].PosY, (MSG_STANDARD*)&sm, 0);
		}

		pItem[gate].Delay = 0;
	}
}

void SetColoseumDoor(int state)
{
	int gate = 0;

	int height = 0;

	for (int i = 0; i < 2; i++)
	{
		gate = i + 13;

		if (pItem[i + 13].ITEM.sIndex <= 0 || pItem[gate].ITEM.sIndex >= MAX_ITEMLIST)
			continue;

		if (pItem[gate].State == state)
			continue;

		UpdateItem(gate, state, &height);

		if (state == STATE_OPEN)
		{
			MSG_UpdateItem sm;
			memset(&sm, 0, sizeof(MSG_UpdateItem));

			sm.ID = ESCENE_FIELD;
			sm.Type = _MSG_UpdateItem;

			sm.ItemID = gate + 10000;

			sm.Size = sizeof(MSG_UpdateItem);

			//		sm.Height = height;
			sm.State = pItem[gate].State;

			GridMulticast(pItem[gate].PosX, pItem[gate].PosY, (MSG_STANDARD*)&sm, 0);
		}
		else
		{
			MSG_CreateItem sm;
			memset(&sm, 0, sizeof(MSG_CreateItem));

			GetCreateItem(gate, &sm);

			GridMulticast(pItem[gate].PosX, pItem[gate].PosY, (MSG_STANDARD*)&sm, 0);
		}
		pItem[gate].Delay = 0;
	}
}

void SetColoseumDoor2(int state)
{
	int gate = 0;

	int height = 0;

	for (int i = 0; i < 5; i++)
	{
		gate = i + 15;

		if (pItem[i + 15].ITEM.sIndex <= 0 || pItem[gate].ITEM.sIndex >= MAX_ITEMLIST)
			continue;

		if (pItem[gate].State == state)
			continue;

		UpdateItem(gate, state, &height);

		if (state == STATE_OPEN)
		{
			MSG_UpdateItem sm;
			memset(&sm, 0, sizeof(MSG_UpdateItem));

			sm.ID = ESCENE_FIELD;
			sm.Type = _MSG_UpdateItem;

			sm.ItemID = gate + 10000;

			sm.Size = sizeof(MSG_UpdateItem);

			//		sm.Height = height;
			sm.State = pItem[gate].State;

			GridMulticast(pItem[gate].PosX, pItem[gate].PosY, (MSG_STANDARD*)&sm, 0);
		}
		else
		{
			MSG_CreateItem sm;
			memset(&sm, 0, sizeof(MSG_CreateItem));

			GetCreateItem(gate, &sm);

			GridMulticast(pItem[gate].PosX, pItem[gate].PosY, (MSG_STANDARD*)&sm, 0);
		}
		pItem[gate].Delay = 0;
	}
}

void GenerateColoseum(int InitID)
{
	int MaxSpawn = 4 + rand() % 4;

	for (int i = 0; i < MaxSpawn; i++)
		GenerateMob(InitID, 0, 0);
}

void DeleteColoseum()
{
	for (int i = MAX_USER; i < MAX_MOB; i++)
	{
		if (!pMob[i].Mode)
			continue;

		if (pMob[i].MOB.CurrentScore.Hp <= 0)
			continue;

		if (!pMob[i].GenerateIndex || pMob[i].GenerateIndex == 1 || pMob[i].GenerateIndex == 2)
			DeleteMob(i, 2);

		if (pMob[i].GenerateIndex == 5 || pMob[i].GenerateIndex == 6 || pMob[i].GenerateIndex == 7)
			DeleteMob(i, 2);
	}
}

void SetArenaDoor(int state)
{
	for (int i = 0; i < ValidGuild; i++)
	{
		if (i == 4)
			continue;

		for (int j = 0; j < 3; j++)
		{
			int gate = 3 * i + j + 1;
			int height = 0;

			if (pItem[gate].ITEM.sIndex <= 0 || pItem[gate].ITEM.sIndex >= MAX_ITEMLIST)
				continue;

			if (pItem[gate].State == state)
				continue;

			UpdateItem(gate, state, &height);

			if (state == STATE_OPEN)
			{
				MSG_UpdateItem sm;
				memset(&sm, 0, sizeof(MSG_UpdateItem));

				sm.ID = ESCENE_FIELD;
				sm.Type = _MSG_UpdateItem;

				sm.ItemID = gate + 10000;

				sm.Size = sizeof(MSG_UpdateItem);

				//sm.Height = height;
				sm.State = pItem[gate].State;

				GridMulticast(pItem[gate].PosX, pItem[gate].PosY, (MSG_STANDARD*)&sm, 0);
			}
			else
			{
				MSG_CreateItem sm;
				memset(&sm, 0, sizeof(MSG_CreateItem));

				GetCreateItem(gate, &sm);

				GridMulticast(pItem[gate].PosX, pItem[gate].PosY, (MSG_STANDARD*)&sm, 0);
			}
			pItem[gate].Delay = 0;
		}
	}
}

void SetCastleDoor(int state)
{
	for (int i = 0; i < 4; i++)
	{
		int DoorId = i + 36;

		if (pItem[DoorId].ITEM.sIndex <= 0 || pItem[DoorId].ITEM.sIndex >= MAX_ITEMLIST)
			continue;

		if (pItem[DoorId].State == state)
			continue;

		int height = 0;

		UpdateItem(DoorId, state, &height);

		if (state == STATE_OPEN)
		{
			MSG_UpdateItem sm;
			memset(&sm, 0, sizeof(MSG_UpdateItem));

			sm.ID = ESCENE_FIELD;
			sm.Type = _MSG_UpdateItem;
			sm.ItemID = DoorId + 10000;
			sm.Size = sizeof(MSG_UpdateItem);
			//		sm.Height = height;
			sm.State = pItem[DoorId].State;

			GridMulticast(pItem[DoorId].PosX, pItem[DoorId].PosY, (MSG_STANDARD*)&sm, 0);
		}
		else
		{
			int keyid = BASE_GetItemAbility(&pItem[DoorId].ITEM, EF_KEYID);

			if (keyid == 15)
				CreateMob("GATE", pItem[DoorId].PosX, pItem[DoorId].PosY, "npc", 0);

			MSG_CreateItem sm;
			memset(&sm, 0, sizeof(MSG_CreateItem));

			GetCreateItem(DoorId, &sm);

			GridMulticast(pItem[DoorId].PosX, pItem[DoorId].PosY, (MSG_STANDARD*)&sm, 0);
		}
		pItem[DoorId].Delay = 0;
	}
}


//Decidir Armia
void DecideWinner0()
{
	int i = 0;

	int ChargeSurvivor = 0;
	int ChallangeSurvivor = 0;

	int ChargeGuild = g_pGuildZone[i].ChargeGuild;
	int ChallangeGuild = g_pGuildZone[i].ChallangeGuild;

	if (ChallangeGuild == 0)
		return;

	char GuildChargeName[256];
	char GuildChallangeName[256];

	BASE_GetGuildName(ServerGroup, g_pGuildZone[i].ChargeGuild, GuildChargeName);
	BASE_GetGuildName(ServerGroup, ChallangeGuild, GuildChallangeName);

	for (int j = g_pGuildZone[i].WarAreaY1; j <= g_pGuildZone[i].WarAreaY2; j++)
	{
		for (int k = g_pGuildZone[i].WarAreaX1; k <= g_pGuildZone[i].WarAreaX2; k++)
		{
			if (j < 0 || j >= MAX_GRIDY || k < 0 || k >= MAX_GRIDX)
				continue;

			int tmob = pMobGrid[j][k];

			if (tmob <= 0 || tmob >= MAX_USER)
				continue;

			if (pUser[tmob].Mode != USER_PLAY)
				continue;

			if (pMob[tmob].Mode == MOB_EMPTY)
				continue;

			if (pMob[tmob].MOB.CurrentScore.Hp <= 0)
				continue;

			int Guild = pMob[tmob].MOB.Guild;
			int Level = pMob[tmob].extra.ClassMaster != MORTAL && pMob[tmob].extra.ClassMaster != MORTAL ? pMob[tmob].MOB.CurrentScore.Level + MAX_LEVEL : pMob[tmob].MOB.CurrentScore.Level;

			if (Guild == 0)
				continue;

			if (Guild == ChargeGuild || Guild == ChallangeGuild)
			{
				sprintf_s(temp, "sys,guild war survive %s(%d-%d)", pMob[tmob].MOB.MobName, Guild, Level);
				SystemLog("-system", "-", 0, temp);

				if (Guild == ChargeGuild)
					ChargeSurvivor += Level;

				else if (Guild == ChallangeGuild)
					ChallangeSurvivor += Level;

				else;
				//Log("err, more than 3 guild, at same guild zone", "-system", 0);
			}
		}
	}

	sprintf_s(temp, "sys,guild war %d result %d(%d) %d(%d)", i, ChargeGuild, ChargeSurvivor, ChallangeGuild, ChallangeSurvivor);
	SystemLog("-system", "-", 0, temp);

	if (ChargeSurvivor < ChallangeSurvivor)
	{
		SendGuildNotice(ChargeGuild, strFmt(g_pMessageStringTable[_SSNN_GuildWarResult], GuildChallangeName, GuildChargeName, ChallangeSurvivor, ChargeSurvivor));
		SendGuildNotice(ChallangeGuild, strFmt(g_pMessageStringTable[_SSNN_GuildWarResult], GuildChallangeName, GuildChargeName, ChallangeSurvivor, ChargeSurvivor));

		g_pGuildZone[i].ChargeGuild = ChallangeGuild;
		g_pGuildZone[i].Victory = 0;
	}
	else
	{
		SendGuildNotice(ChargeGuild, strFmt(g_pMessageStringTable[_SSNN_GuildWarResult], GuildChargeName, GuildChallangeName, ChargeSurvivor, ChallangeSurvivor));
		SendGuildNotice(ChallangeGuild, strFmt(g_pMessageStringTable[_SSNN_GuildWarResult], GuildChargeName, GuildChallangeName, ChargeSurvivor, ChallangeSurvivor));

		if (g_pGuildZone[i].Victory < 4)
			g_pGuildZone[i].Victory++;
	}

	g_pGuildZone[i].ChallangeGuild = 0;

	// Verifica��o para setar Noatum
	if (g_pGuildZone[1].ChargeGuild == g_pGuildZone[0].ChargeGuild && g_pGuildZone[2].ChargeGuild == g_pGuildZone[0].ChargeGuild && g_pGuildZone[3].ChargeGuild == g_pGuildZone[0].ChargeGuild)
		g_pGuildZone[4].ChargeGuild = g_pGuildZone[0].ChargeGuild;
}

//Decidir Azran
void DecideWinner1()
{
	int i = 1;

	int ChargeSurvivor = 0;
	int ChallangeSurvivor = 0;

	int ChargeGuild = g_pGuildZone[i].ChargeGuild;
	int ChallangeGuild = g_pGuildZone[i].ChallangeGuild;

	if (ChallangeGuild == 0)
		return;

	char GuildChargeName[256];
	char GuildChallangeName[256];

	BASE_GetGuildName(ServerGroup, g_pGuildZone[i].ChargeGuild, GuildChargeName);
	BASE_GetGuildName(ServerGroup, ChallangeGuild, GuildChallangeName);

	for (int j = g_pGuildZone[i].WarAreaY1; j <= g_pGuildZone[i].WarAreaY2; j++)
	{
		for (int k = g_pGuildZone[i].WarAreaX1; k <= g_pGuildZone[i].WarAreaX2; k++)
		{
			if (j < 0 || j >= MAX_GRIDY || k < 0 || k >= MAX_GRIDX)
				continue;

			int tmob = pMobGrid[j][k];

			if (tmob <= 0 || tmob >= MAX_USER)
				continue;

			if (pUser[tmob].Mode != USER_PLAY)
				continue;

			if (pMob[tmob].Mode == MOB_EMPTY)
				continue;

			if (pMob[tmob].MOB.CurrentScore.Hp <= 0)
				continue;

			int Guild = pMob[tmob].MOB.Guild;
			int Level = pMob[tmob].extra.ClassMaster != MORTAL && pMob[tmob].extra.ClassMaster != MORTAL ? pMob[tmob].MOB.CurrentScore.Level + MAX_LEVEL : pMob[tmob].MOB.CurrentScore.Level;

			if (Guild == 0)
				continue;

			if (Guild == ChargeGuild || Guild == ChallangeGuild)
			{
				sprintf_s(temp, "sys,guild war survive %s(%d-%d)", pMob[tmob].MOB.MobName, Guild, Level);
				SystemLog("-system", "-", 0, temp);

				if (Guild == ChargeGuild)
					ChargeSurvivor += Level;

				else if (Guild == ChallangeGuild)
					ChallangeSurvivor += Level;

				else;
				//Log("err, more than 3 guild, at same guild zone", "-system", 0);
			}
		}
	}

	sprintf_s(temp, "sys,guild war %d result %d(%d) %d(%d)", i, ChargeGuild, ChargeSurvivor, ChallangeGuild, ChallangeSurvivor);
	SystemLog("-system", "-", 0, temp);

	if (ChargeSurvivor < ChallangeSurvivor)
	{
		SendGuildNotice(ChargeGuild, strFmt(g_pMessageStringTable[_SSNN_GuildWarResult], GuildChallangeName, GuildChargeName, ChallangeSurvivor, ChargeSurvivor));
		SendGuildNotice(ChallangeGuild, strFmt(g_pMessageStringTable[_SSNN_GuildWarResult], GuildChallangeName, GuildChargeName, ChallangeSurvivor, ChargeSurvivor));

		g_pGuildZone[i].ChargeGuild = ChallangeGuild;
		g_pGuildZone[i].Victory = 0;
	}
	else
	{
		SendGuildNotice(ChargeGuild, strFmt(g_pMessageStringTable[_SSNN_GuildWarResult], GuildChargeName, GuildChallangeName, ChargeSurvivor, ChallangeSurvivor));
		SendGuildNotice(ChallangeGuild, strFmt(g_pMessageStringTable[_SSNN_GuildWarResult], GuildChargeName, GuildChallangeName, ChargeSurvivor, ChallangeSurvivor));

		if (g_pGuildZone[i].Victory < 4)
			g_pGuildZone[i].Victory++;
	}

	g_pGuildZone[i].ChallangeGuild = 0;

}

//Decidir Erion
void DecideWinner2()
{
	int i = 2;

	int ChargeSurvivor = 0;
	int ChallangeSurvivor = 0;

	int ChargeGuild = g_pGuildZone[i].ChargeGuild;
	int ChallangeGuild = g_pGuildZone[i].ChallangeGuild;

	if (ChallangeGuild == 0)
		return;

	char GuildChargeName[256];
	char GuildChallangeName[256];

	BASE_GetGuildName(ServerGroup, g_pGuildZone[i].ChargeGuild, GuildChargeName);
	BASE_GetGuildName(ServerGroup, ChallangeGuild, GuildChallangeName);

	for (int j = g_pGuildZone[i].WarAreaY1; j <= g_pGuildZone[i].WarAreaY2; j++)
	{
		for (int k = g_pGuildZone[i].WarAreaX1; k <= g_pGuildZone[i].WarAreaX2; k++)
		{
			if (j < 0 || j >= MAX_GRIDY || k < 0 || k >= MAX_GRIDX)
				continue;

			int tmob = pMobGrid[j][k];

			if (tmob <= 0 || tmob >= MAX_USER)
				continue;

			if (pUser[tmob].Mode != USER_PLAY)
				continue;

			if (pMob[tmob].Mode == MOB_EMPTY)
				continue;

			if (pMob[tmob].MOB.CurrentScore.Hp <= 0)
				continue;

			int Guild = pMob[tmob].MOB.Guild;
			int Level = pMob[tmob].extra.ClassMaster != MORTAL && pMob[tmob].extra.ClassMaster != MORTAL ? pMob[tmob].MOB.CurrentScore.Level + MAX_LEVEL : pMob[tmob].MOB.CurrentScore.Level;

			if (Guild == 0)
				continue;

			if (Guild == ChargeGuild || Guild == ChallangeGuild)
			{
				sprintf_s(temp, "sys,guild war survive %s(%d-%d)", pMob[tmob].MOB.MobName, Guild, Level);
				SystemLog("-system", "-", 0, temp);

				if (Guild == ChargeGuild)
					ChargeSurvivor += Level;

				else if (Guild == ChallangeGuild)
					ChallangeSurvivor += Level;

				else;
				//Log("err, more than 3 guild, at same guild zone", "-system", 0);
			}
		}
	}

	sprintf_s(temp, "sys,guild war %d result %d(%d) %d(%d)", i, ChargeGuild, ChargeSurvivor, ChallangeGuild, ChallangeSurvivor);
	SystemLog("-system", "-", 0, temp);

	if (ChargeSurvivor < ChallangeSurvivor)
	{
		SendGuildNotice(ChargeGuild, strFmt(g_pMessageStringTable[_SSNN_GuildWarResult], GuildChallangeName, GuildChargeName, ChallangeSurvivor, ChargeSurvivor));
		SendGuildNotice(ChallangeGuild, strFmt(g_pMessageStringTable[_SSNN_GuildWarResult], GuildChallangeName, GuildChargeName, ChallangeSurvivor, ChargeSurvivor));

		g_pGuildZone[i].ChargeGuild = ChallangeGuild;
		g_pGuildZone[i].Victory = 0;
	}
	else
	{
		SendGuildNotice(ChargeGuild, strFmt(g_pMessageStringTable[_SSNN_GuildWarResult], GuildChargeName, GuildChallangeName, ChargeSurvivor, ChallangeSurvivor));
		SendGuildNotice(ChallangeGuild, strFmt(g_pMessageStringTable[_SSNN_GuildWarResult], GuildChargeName, GuildChallangeName, ChargeSurvivor, ChallangeSurvivor));

		if (g_pGuildZone[i].Victory < 4)
			g_pGuildZone[i].Victory++;
	}

	g_pGuildZone[i].ChallangeGuild = 0;
}

//Decidir Nippleheim
void DecideWinner3()
{
	int i = 3;

	int ChargeSurvivor = 0;
	int ChallangeSurvivor = 0;

	int ChargeGuild = g_pGuildZone[i].ChargeGuild;
	int ChallangeGuild = g_pGuildZone[i].ChallangeGuild;

	if (ChallangeGuild == 0)
		return;

	char GuildChargeName[256];
	char GuildChallangeName[256];

	BASE_GetGuildName(ServerGroup, g_pGuildZone[i].ChargeGuild, GuildChargeName);
	BASE_GetGuildName(ServerGroup, ChallangeGuild, GuildChallangeName);

	for (int j = g_pGuildZone[i].WarAreaY1; j <= g_pGuildZone[i].WarAreaY2; j++)
	{
		for (int k = g_pGuildZone[i].WarAreaX1; k <= g_pGuildZone[i].WarAreaX2; k++)
		{
			if (j < 0 || j >= MAX_GRIDY || k < 0 || k >= MAX_GRIDX)
				continue;

			int tmob = pMobGrid[j][k];

			if (tmob <= 0 || tmob >= MAX_USER)
				continue;

			if (pUser[tmob].Mode != USER_PLAY)
				continue;

			if (pMob[tmob].Mode == MOB_EMPTY)
				continue;

			if (pMob[tmob].MOB.CurrentScore.Hp <= 0)
				continue;

			int Guild = pMob[tmob].MOB.Guild;
			int Level = pMob[tmob].extra.ClassMaster != MORTAL && pMob[tmob].extra.ClassMaster != MORTAL ? pMob[tmob].MOB.CurrentScore.Level + MAX_LEVEL : pMob[tmob].MOB.CurrentScore.Level;

			if (Guild == 0)
				continue;

			if (Guild == ChargeGuild || Guild == ChallangeGuild)
			{
				sprintf_s(temp, "sys,guild war survive %s(%d-%d)", pMob[tmob].MOB.MobName, Guild, Level);
				SystemLog("-system", "-", 0, temp);

				if (Guild == ChargeGuild)
					ChargeSurvivor += Level;

				else if (Guild == ChallangeGuild)
					ChallangeSurvivor += Level;

				else;
				//Log("err, more than 3 guild, at same guild zone", "-system", 0);
			}
		}
	}

	sprintf_s(temp, "sys,guild war %d result %d(%d) %d(%d)", i, ChargeGuild, ChargeSurvivor, ChallangeGuild, ChallangeSurvivor);
	SystemLog("-system", "-", 0, temp);

	if (ChargeSurvivor < ChallangeSurvivor)
	{
		SendGuildNotice(ChargeGuild, strFmt(g_pMessageStringTable[_SSNN_GuildWarResult], GuildChallangeName, GuildChargeName, ChallangeSurvivor, ChargeSurvivor));
		SendGuildNotice(ChallangeGuild, strFmt(g_pMessageStringTable[_SSNN_GuildWarResult], GuildChallangeName, GuildChargeName, ChallangeSurvivor, ChargeSurvivor));

		g_pGuildZone[i].ChargeGuild = ChallangeGuild;
		g_pGuildZone[i].Victory = 0;
	}
	else
	{
		SendGuildNotice(ChargeGuild, strFmt(g_pMessageStringTable[_SSNN_GuildWarResult], GuildChargeName, GuildChallangeName, ChargeSurvivor, ChallangeSurvivor));
		SendGuildNotice(ChallangeGuild, strFmt(g_pMessageStringTable[_SSNN_GuildWarResult], GuildChargeName, GuildChallangeName, ChargeSurvivor, ChallangeSurvivor));

		if (g_pGuildZone[i].Victory < 4)
			g_pGuildZone[i].Victory++;
	}

	g_pGuildZone[i].ChallangeGuild = 0;
}

void GuildProcess()
{
	time_t rawtime;
	tm *timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	if (timeinfo->tm_hour == 3 && GuildNameInitialized == 0)
	{
		BASE_InitializeGuildName();

		//Log("sys,GuildName initialized", "-system", 0);

		GuildNameInitialized = 1;
	}

	if (timeinfo->tm_hour > 3 && GuildNameInitialized == 1)
		GuildNameInitialized = 0;

#pragma region Guerra de Noatum
	if (CastleServer == 1 && (timeinfo->tm_hour == 14))
	{
		if (CastleState || timeinfo->tm_min >= 5)
		{
			if (CastleState != 1 || timeinfo->tm_min <= 5 || timeinfo->tm_min >= 10)
			{
				if (CastleState != 2 || timeinfo->tm_min <= 50)
				{
					if (CastleState == 3 && timeinfo->tm_min > 55)
					{
						SendNotice(strFmt(g_pMessageStringTable[_DN_Castle_closed], timeinfo->tm_hour - 17));
						FinishCastleWar();
					}
				}
				else
				{
					SendNotice(strFmt(g_pMessageStringTable[_DN_Castle_will_be_closed], timeinfo->tm_hour - 17));
					CastleState = 3;
				}
			}
			else
			{
				ClearAreaGuild(1036, 1672, 1144, 1764, g_pGuildZone[4].ChargeGuild);

				ClearAreaTeleport(1129, 1705, 1129, 1709, 1057, 1742);
				ClearAreaTeleport(1116, 1705, 1116, 1709, 1057, 1742);
				ClearAreaTeleport(1094, 1688, 1094, 1692, 1057, 1742);
				ClearAreaTeleport(1087, 1609, 1087, 1713, 1057, 1742);
				ClearAreaTeleport(1050, 1690, 1050, 1690, 1057, 1742);
				ClearAreaTeleport(1046, 1690, 1047, 1691, 1057, 1742);
				ClearAreaTeleport(1124, 1708, 1124, 1708, 1057, 1742);

				SetCastleDoor(3);

				for (int i = 0; i < 3; ++i)
				{
					GenerateMob(i + TORRE_NOATUM1, 0, 0);
					LiveTower[i] = 1;
				}

				SendNotice(strFmt(g_pMessageStringTable[_DN_Castle_opened], timeinfo->tm_hour - 17));
				CastleState = 2;
			}
		}
		else
		{
			SendNotice(strFmt(g_pMessageStringTable[_DN_Castle_will_be_open], timeinfo->tm_hour - 17));
			CastleState = 1;

			for (int j = 0; j < MAX_USER; j++)
			{
				if (pUser[j].Mode == USER_PLAY)
					SendClientSignalParm(j, ESCENE_FIELD, 940, CastleState);
			}
		}
	}

#pragma region Guerra de Cidades
	int day = GuildDay - 1;

	if (day < 0)
		day += 7;

	int fweek = timeinfo->tm_wday;

	if (ForceWeekMode != -1)
		fweek = -1;

	//Libera as Apostas
	if (WeekMode == 4 && timeinfo->tm_wday == 6) {
		SendNotice(g_pMessageStringTable[_NN_Guild_Battle_Notice5]);
		WeekMode = 5;
	}
	//Define os desafiantes
	if (WeekMode == 5 && timeinfo->tm_wday == 0)
	{
		SendNotice(g_pMessageStringTable[_NN_Guild_Battle_Notice6]);
		WeekMode = 0;

		for (int i = 0; i < MAX_GUILDZONE; i++)
		{
			if (i == 4)
				continue;

			if (g_pGuildZone[i].ChallangeGuild == 0 && g_pGuildZone[i].Victory < 4)
				g_pGuildZone[i].Victory++;
		}
	}
	//Diz para come�arem a esperar nas cidades (20h)
	if (WeekMode == 0 && timeinfo->tm_wday == 0 && timeinfo->tm_hour == GuildHour)
	{
		SendNotice(g_pMessageStringTable[_NN_Guild_Battle_Notice1]);
		WeekMode = 1;
	}
	//A guerra de Erion ir� come�ar em 3 minutos e Teleporta os Players (20:02)
	if (WeekMode == 1 && timeinfo->tm_wday == 0 && timeinfo->tm_hour == GuildHour && timeinfo->tm_min == 2)
	{
		SendNotice("A Guerra de Erion ir� come�ar em 3 minutos");
		ClearGuildPKZone();
		WeekMode = 2;
		SetArenaDoor(STATE_LOCKED);

		//0-armia,1-arzan,2-erion,3-nipplehein,4-noatum
		int n = 2;

		if (g_pGuildZone[n].ChallangeGuild)
		{
			if (g_pGuildZone[n].ChargeGuild)
				SummonGuild(g_pGuildZone[n].ChargeGuild, g_pGuildZone[n].ChargeWarSpawnX, g_pGuildZone[n].ChargeWarSpawnY, NumGuildBattle, n);
		}
		if (g_pGuildZone[n].ChallangeGuild)
			SummonGuild(g_pGuildZone[n].ChallangeGuild, g_pGuildZone[n].ChallangeWarSpawnX, g_pGuildZone[n].ChallangeWarSpawnY, NumGuildBattle, n);
	}
	//Guerra de Erion Iniciada (20:05)
	if (WeekMode == 2 && timeinfo->tm_wday == 0 && timeinfo->tm_hour == GuildHour && timeinfo->tm_min == 5)
	{
		SendNotice(g_pMessageStringTable[_NN_Guild_Battle_Notice3]);
		WeekMode = 3;
		SetArenaDoor(STATE_OPEN);
	}
	//Guerra de Erion Encerrada (20:15)
	if (WeekMode == 3 && timeinfo->tm_wday == 0 && timeinfo->tm_hour == GuildHour && timeinfo->tm_min == 15)
	{
		SendNotice("Guerra de Erion Finalizada!");
		//0-armia,1-arzan,2-erion,3-nipplehein,4-noatum
		DecideWinner2();
		ClearChallanger2();
		ClearGuildPKZone();

		CReadFiles::WriteChallanger();
		SetArenaDoor(STATE_LOCKED);
		WeekMode = 1;

		GuildZoneReport();
	}
	//A guerra de Nipplehein ir� come�ar em 3 minutos e Teleporta os Players (20:17)
	if (WeekMode == 1 && timeinfo->tm_wday == 0 && timeinfo->tm_hour == GuildHour && timeinfo->tm_min == 17)
	{
		SendNotice("A Guerra de Nipplehein ir� come�ar em 3 minutos");
		ClearGuildPKZone();
		WeekMode = 2;
		SetArenaDoor(STATE_LOCKED);

		//0-armia,1-arzan,2-erion,3-nipplehein,4-noatum
		int n = 3;

		if (g_pGuildZone[n].ChallangeGuild)
		{
			if (g_pGuildZone[n].ChargeGuild)
				SummonGuild(g_pGuildZone[n].ChargeGuild, g_pGuildZone[n].ChargeWarSpawnX, g_pGuildZone[n].ChargeWarSpawnY, NumGuildBattle, n);
		}
		if (g_pGuildZone[n].ChallangeGuild)
			SummonGuild(g_pGuildZone[n].ChallangeGuild, g_pGuildZone[n].ChallangeWarSpawnX, g_pGuildZone[n].ChallangeWarSpawnY, NumGuildBattle, n);
	}
	//Guerra de Nipplehein Iniciada (20:20)
	if (WeekMode == 2 && timeinfo->tm_wday == 0 && timeinfo->tm_hour == GuildHour && timeinfo->tm_min == 20)
	{
		SendNotice(g_pMessageStringTable[_NN_Guild_Battle_Notice3]);
		WeekMode = 3;
		SetArenaDoor(STATE_OPEN);
	}
	//Guerra de Nipplehein Encerrada (20:30)
	if (WeekMode == 3 && timeinfo->tm_wday == 0 && timeinfo->tm_hour == GuildHour && timeinfo->tm_min == 30)
	{
		SendNotice("Guerra de Nipplehein Finalizada!");
		//0-armia,1-arzan,2-erion,3-nipplehein,4-noatum
		DecideWinner3();
		ClearChallanger3();
		ClearGuildPKZone();

		CReadFiles::WriteChallanger();
		SetArenaDoor(STATE_LOCKED);
		WeekMode = 1;

		GuildZoneReport();
	}
	//A guerra de Azran ir� come�ar em 3 minutos e Teleporta os Players (20:32)
	if (WeekMode == 1 && timeinfo->tm_wday == 0 && timeinfo->tm_hour == GuildHour && timeinfo->tm_min == 32)
	{
		SendNotice("A Guerra de Azran ir� come�ar em 3 minutos");
		ClearGuildPKZone();
		WeekMode = 2;
		SetArenaDoor(STATE_LOCKED);

		//0-armia,1-arzan,2-erion,3-nipplehein,4-noatum
		int n = 1;

		if (g_pGuildZone[n].ChallangeGuild)
		{
			if (g_pGuildZone[n].ChargeGuild)
				SummonGuild(g_pGuildZone[n].ChargeGuild, g_pGuildZone[n].ChargeWarSpawnX, g_pGuildZone[n].ChargeWarSpawnY, NumGuildBattle, n);
		}
		if (g_pGuildZone[n].ChallangeGuild)
			SummonGuild(g_pGuildZone[n].ChallangeGuild, g_pGuildZone[n].ChallangeWarSpawnX, g_pGuildZone[n].ChallangeWarSpawnY, NumGuildBattle, n);
	}
	//Guerra de Azran Iniciada (20:35)
	if (WeekMode == 2 && timeinfo->tm_wday == 0 && timeinfo->tm_hour == GuildHour && timeinfo->tm_min == 35)
	{
		SendNotice(g_pMessageStringTable[_NN_Guild_Battle_Notice3]);
		WeekMode = 3;
		SetArenaDoor(STATE_OPEN);
	}
	//Guerra de Azran Encerrada (20:45)
	if (WeekMode == 3 && timeinfo->tm_wday == 0 && timeinfo->tm_hour == GuildHour && timeinfo->tm_min == 45)
	{
		SendNotice("Guerra de Azran Finalizada!");
		//0-armia,1-arzan,2-erion,3-nipplehein,4-noatum
		DecideWinner1();
		ClearChallanger1();
		ClearGuildPKZone();

		CReadFiles::WriteChallanger();
		SetArenaDoor(STATE_LOCKED);
		WeekMode = 1;

		GuildZoneReport();
	}
	//A guerra de Armia ir� come�ar em 3 minutos e Teleporta os Players (20:47)
	if (WeekMode == 1 && timeinfo->tm_wday == 0 && timeinfo->tm_hour == GuildHour && timeinfo->tm_min == 47)
	{
		SendNotice("A Guerra de Armia ir� come�ar em 3 minutos");
		ClearGuildPKZone();
		WeekMode = 2;
		SetArenaDoor(STATE_LOCKED);

		//0-armia,1-arzan,2-erion,3-nipplehein,4-noatum
		int n = 0;

		if (g_pGuildZone[n].ChallangeGuild)
		{
			if (g_pGuildZone[n].ChargeGuild)
				SummonGuild(g_pGuildZone[n].ChargeGuild, g_pGuildZone[n].ChargeWarSpawnX, g_pGuildZone[n].ChargeWarSpawnY, NumGuildBattle, n);
		}
		if (g_pGuildZone[n].ChallangeGuild)
			SummonGuild(g_pGuildZone[n].ChallangeGuild, g_pGuildZone[n].ChallangeWarSpawnX, g_pGuildZone[n].ChallangeWarSpawnY, NumGuildBattle, n);
	}
	//Guerra de Armia Iniciada (20:50)
	if (WeekMode == 2 && timeinfo->tm_wday == 0 && timeinfo->tm_hour == GuildHour && timeinfo->tm_min == 50)
	{
		SendNotice(g_pMessageStringTable[_NN_Guild_Battle_Notice3]);
		WeekMode = 3;
		SetArenaDoor(STATE_OPEN);
	}
	//Guerra de Armia Encerrada (20:59)
	if (WeekMode == 3 && timeinfo->tm_wday == 0 && timeinfo->tm_hour == GuildHour && timeinfo->tm_min == 59)
	{
		SendNotice("Guerra de Armia Finalizada!");
		//0-armia,1-arzan,2-erion,3-nipplehein,4-noatum
		DecideWinner0();
		ClearChallanger0();
		ClearGuildPKZone();

		CReadFiles::WriteChallanger();
		SetArenaDoor(STATE_LOCKED);
		WeekMode = 4;

		GuildZoneReport();
	}

#pragma endregion
//#pragma region Guerra de Cidades
//	int day = GuildDay - 1;
//
//	if (day < 0)
//		day += 7;
//
//	int fweek = timeinfo->tm_wday;
//
//	if (ForceWeekMode != -1)
//		fweek = -1;
//
//	if (WeekMode || ((fweek != GuildDay) || timeinfo->tm_hour < GuildHour) && ForceWeekMode != 1)
//	{
//		if (WeekMode != 1 || (fweek != GuildDay || (timeinfo->tm_hour < GuildHour) || timeinfo->tm_min <= 2) && ForceWeekMode != 2)
//		{
//			if (WeekMode != 2 || ((fweek != GuildDay) || timeinfo->tm_hour < GuildHour || timeinfo->tm_min <= 5) && ForceWeekMode != 3)
//			{
//				if (WeekMode != 3
//					|| (fweek != GuildDay || (timeinfo->tm_hour < GuildHour) || timeinfo->tm_min <= 20) && ForceWeekMode != 4)
//				{
//					if (WeekMode != 4 || fweek != day && ForceWeekMode != 5)
//					{
//						if (WeekMode == 5 && (fweek == GuildDay || !ForceWeekMode))
//						{
//							SendNotice(g_pMessageStringTable[_NN_Guild_Battle_Notice6]);
//							WeekMode = 0;
//
//							for (int i = 0; i < MAX_GUILDZONE; i++)
//							{
//								if (i == 4)
//									continue;
//
//								if (g_pGuildZone[i].ChallangeGuild == 0 && g_pGuildZone[i].Victory < 4)
//									g_pGuildZone[i].Victory++;
//							}
//
//						}
//					}
//					else
//					{
//						SendNotice(g_pMessageStringTable[_NN_Guild_Battle_Notice5]);
//						WeekMode = 5;
//					}
//				}
//				else
//				{
//					SendNotice(g_pMessageStringTable[_NN_Guild_Battle_Notice4]);
//					DecideWinner();
//					ClearGuildPKZone();
//					ClearChallanger();
//					CReadFiles::WriteChallanger();
//					SetArenaDoor(STATE_LOCKED);
//					WeekMode = 4;
//
//					GuildZoneReport();
//				}
//			}
//			else
//			{
//				SendNotice(g_pMessageStringTable[_NN_Guild_Battle_Notice3]);
//				WeekMode = 3;
//				SetArenaDoor(STATE_OPEN);
//			}
//		}
//		else
//		{
//			SendNotice(g_pMessageStringTable[_NN_Guild_Battle_Notice2]);
//			ClearGuildPKZone();
//			WeekMode = 2;
//			SetArenaDoor(STATE_LOCKED);
//
//			for (int n = 0; n < ValidGuild; n++)
//			{
//				if (n != 4)
//				{
//					if (g_pGuildZone[n].ChallangeGuild)
//					{
//						if (g_pGuildZone[n].ChargeGuild)
//							SummonGuild(g_pGuildZone[n].ChargeGuild, g_pGuildZone[n].ChargeWarSpawnX, g_pGuildZone[n].ChargeWarSpawnY, NumGuildBattle, n);
//					}
//				}
//			}
//
//			for (int n = 0; n < ValidGuild; n++)
//			{
//				if (n != 4)
//				{
//					if (g_pGuildZone[n].ChallangeGuild)
//						SummonGuild(g_pGuildZone[n].ChallangeGuild, g_pGuildZone[n].ChallangeWarSpawnX, g_pGuildZone[n].ChallangeWarSpawnY, NumGuildBattle, n);
//				}
//			}
//		}
//	}
//	else
//	{
//		SendNotice(g_pMessageStringTable[_NN_Guild_Battle_Notice1]);
//		WeekMode = 1;
//	}
//#pragma endregion
#pragma region Guerra de Reino RVR_ON
	//if (NewbieEventServer == 1 && timeinfo->tm_wday != 0 && timeinfo->tm_wday != 6 && timeinfo->tm_hour == RvRHour)
	if (timeinfo->tm_wday != 0 && timeinfo->tm_wday != 6 && timeinfo->tm_hour == RvRHour)
	{
		if (RvRState == 0 && timeinfo->tm_min < 5)
		{
			SendNotice(strFmt(g_pMessageStringTable[_DD_KINGDOMWAR_BEGIN], 5, ServerIndex + 1));
			RvRState = 1;
		}
		if (RvRState == 1 && timeinfo->tm_min >= 5)
		{
			GenerateMob(RVRTORRE_1, 0, 0);
			GenerateMob(RVRTORRE_2, 0, 0);

			SendNotice(g_pMessageStringTable[_DD_KINGDOMWAR_START]);
			RvRState = 2;
			RvRRedPoint = 0;
			RvRBluePoint = 0;
		}

		if (RvRState == 2 && timeinfo->tm_min >= 29)
			RvRState = 3;

		if (RvRState == 3 && timeinfo->tm_min == 34)
		{
			for (int conn = 1; conn < MAX_USER; conn++)
			{
				if (pMob[conn].MOB.Clan)
				{
					if (RvRRedPoint > RvRBluePoint)
					{
						SendNotice(strFmt(g_pMessageStringTable[_SN_KINGDOMWAR_DROP_], g_pMessageStringTable[_NN_KINGDOM_RED]));
						RvRBonus = 8;
					}
					else if (RvRBluePoint > RvRRedPoint)
					{
						SendNotice(strFmt(g_pMessageStringTable[_SN_KINGDOMWAR_DROP_], g_pMessageStringTable[_NN_KINGDOM_BLUE]));
						RvRBonus = 7;
					}
					else if (RvRBluePoint == RvRRedPoint)
					{
						SendNotice("Guerra de Reinos terminou em empate [Sem B�nus RVR]. ");
						RvRBonus = 0;
					}
				}
			}
			for (int i = MAX_USER; i < MAX_MOB; i++)
			{
				if (pMob[i].GenerateIndex == RVRTORRE_1 || pMob[i].GenerateIndex == RVRTORRE_2)
					DeleteMob(i, 1);
			}

			ClearArea(1020, 1916, 1286, 2178);
			RvRState = 0;
			RvRRedPoint = 0;
			RvRBluePoint = 0;
		}
	}
#pragma endregion
	/*CCOLISEU::ColoProcessN(timeinfo);
	CCOLISEU::ColoProcessM(timeinfo);
	CCOLISEU::ColoProcessA(timeinfo);*/
	CWarTower::GuildProcess(timeinfo); 
}
 
int GetUserInAreaMac(int notUsage, int x1, int y1, int x2, int y2)
{
	int userCount = 0;

	for (int conn = 1; conn < MAX_USER; conn++)
	{
		if (pUser[conn].Mode != USER_PLAY)
			continue;

		if (pMob[conn].Mode == 0)
			continue;

		for (int i = 1; i < MAX_USER; i++)
		{
			if (pUser[i].Mode != USER_PLAY)
				continue;

			if (i == conn) continue;

			if (pMob[i].Mode == 0)
				continue;

			if (pMob[conn].TargetX >= x1 && pMob[conn].TargetX <= x2 && pMob[conn].TargetY >= y1 && pMob[conn].TargetY <= y2)
			{
				if (pMob[i].TargetX >= x1 && pMob[i].TargetX <= x2 && pMob[i].TargetY >= y1 && pMob[i].TargetY <= y2)
				{
					if (!strcmp(pUser[conn].MacAddress, pUser[i].MacAddress))
					{
						DoRecall(i);

						SendClientMessage(i, "Somente 1 conta por computador.");
						userCount++;
						continue;
					}
				}
			}
		}
	}
	return userCount;
}

void StartLog()
{
	if (fLogFile1 != NULL)
		fclose(fLogFile1);

	struct tm when;
	time_t now;
	time(&now);
	when = *localtime(&now);

	sprintf_s(temp, ".\\Logs\\server_log\\TM_%02d_%02d_%04d_%02d_%02d_%02d.txt", when.tm_mday, when.tm_mon + 1, when.tm_year + 1900, when.tm_hour, when.tm_min, when.tm_sec);

	fLogFile1 = fopen(temp, "wt");

	LastLogDay = when.tm_mday;
}

void CrackLog(int conn, char *str)
{
	char AccountName[16];

	if (conn <= 0 || conn >= MAX_USER)
	{
		if (conn < 0 || conn >= MAX_MOB)
			sprintf_s(temp, "index:%d", conn);

		else
			sprintf_s(temp, "mob:%d name:%s", conn, pMob[conn].MOB.MobName);
	}

	else
	{
		memcpy(AccountName, pUser[conn].AccountName, sizeof(pUser[conn].AccountName));

		pUser[conn].AccountName[15] = 0;
		pUser[conn].AccountName[14] = 0;

		sprintf_s(temp, "conn:%d mode:%d name:%s", conn, pUser[conn].Mode, AccountName);
	}

	strcat(temp, str);

	//Log(temp, "-system", 0);

	SetWindowTextA(hWndMain, temp);
}

void StartSystemLog()
{
	if (g_pSystemLog && g_pSystemLog.get()->m_pStream.get()->is_open()) {
		g_pSystemLog.get()->m_pStream.get()->close();
		g_pSystemLog.get()->m_pStream.get()->clear();
		g_pSystemLog.get()->m_pStream.release();
	}

	if (g_pSystemLog)
		g_pSystemLog.release();

	g_pSystemLog = std::make_unique<LogControl>();

	struct tm when;
	time_t now;
	time(&now);
	when = *localtime(&now);
	char temp[1024];
	snprintf(temp, sizeof(temp), ".\\Logs\\server_log\\TM_%02d_%02d_%04d_%02d_%02d_%02d.txt", when.tm_mday, when.tm_mon + 1, when.tm_year + 1900, when.tm_hour, when.tm_min, when.tm_sec);

	char tmg[256];
	snprintf(tmg, sizeof(tmg), "chat logs started successfully");
	SystemLog("-system", "-", 0, tmg);

	g_pSystemLog.get()->Initialize(std::string(temp));

	LastSystemLogDay = when.tm_mday;
}

void SystemLog(char* AccountName, char* MacAddress, unsigned int IPAddress, char* Message)
{
	char temp_str[64] = { 0, };

	if (IPAddress != 0) //for some reason the ip address isn't working properly...
	{
		//Vamo do jeito hard
		sprintf_s(temp_str, "%d.%d.%d.%d",
			IPAddress & 0xFF,
			(IPAddress >> 8) & 0xFF,
			(IPAddress >> 16) & 0xFF,
			(IPAddress >> 24) & 0xFF);
	}
	else
		snprintf(temp_str, sizeof(temp_str), "NO_VALID_IP");

	if (g_pSystemLog)
		g_pSystemLog.get()->WriteLog(std::string(Message), std::string(MacAddress), std::string(temp_str), std::string(AccountName));
}

void Log(char* str1, char* str2, unsigned int ip)
{
	struct tm when;
	time_t now;
	time(&now);
	when = *localtime(&now);

	char LogTemp[1024];

	unsigned char* cIP = (unsigned char*)&ip;

	sprintf_s(LogTemp, "%2.2d%2.2d%2.2d,%2.2d%2.2d%2.2d,%8.8x", when.tm_year - 100, when.tm_mon + 1, when.tm_mday, when.tm_hour, when.tm_min, when.tm_sec, ip);
	sprintf_s(LogTemp, "%s,%s,%s \n", LogTemp, str2, str1);

	if (ip != 0)
		sprintf_s(LogTemp, "[%02d/%02d/%04d][%02d:%02d:%02d] IP: %d.%d.%d.%d.%d", when.tm_mday, when.tm_mon + 1, when.tm_year + 1900, when.tm_hour, when.tm_min, when.tm_sec, cIP[0], cIP[1], cIP[2], cIP[3], cIP[4]);
	else
		sprintf_s(LogTemp, "[%02d/%02d/%04d][%02d:%02d:%02d] ", when.tm_mday, when.tm_mon + 1, when.tm_year + 1900, when.tm_hour, when.tm_min, when.tm_sec);

	sprintf_s(LogTemp, "\n%s %s %s\n", LogTemp, str2, str1);
	printf("%s", LogTemp);  //monitor console

	if (fLogFile1)
		fprintf(fLogFile1, LogTemp);

	SetWindowText(hWndMain, LogTemp);
}

int  GetUserFromSocket(int Sock)
{
	if (Sock == 0)
		return 0;

	for (int i = 1; i < MAX_USER; i++)
	{
		if (pUser[i].cSock.Sock == (unsigned)Sock)
			return i;
	}

	return 0;
}

int  GetEmptyUser(void)
{
	for (int i = 1; i < MAX_USER; i++)
	{
		if (pUser[i].Mode == USER_EMPTY)
			return i;
	}

	return 0;
}

int  GetEmptyItem()
{
	for (int i = 1; i < MAX_ITEM; i++)
	{
		if (pItem[i].Mode == 0)
			return i;
	}

	return 0;
}

int  GetEmptyNPCMob()
{
	static int CurrentNumMob = MAX_USER;
	if (CurrentNumMob >= MAX_MOB)
		CurrentNumMob = MAX_USER;
	int tmpNumMob = CurrentNumMob;
	for (int i = 0; i < MAX_MOB - MAX_USER; ++i)
	{
		if (tmpNumMob < MAX_MOB)
		{
			if (!pMob[tmpNumMob].Mode)
			{
				CurrentNumMob = tmpNumMob;
				CurrentNumMob++;
				return tmpNumMob;
			}
		}
		else
		{
			tmpNumMob = MAX_USER;
		}
		++tmpNumMob;
	}
	return 0;

	//if (g_EmptyMob >= MAX_MOB)
	//	g_EmptyMob = MAX_USER;

	//int MaxCount = MAX_MOB - MAX_USER;
	//int EmptyMob = g_EmptyMob;

	//for (int i = 0; i < MaxCount; i++, EmptyMob++)
	//{
	//	if (EmptyMob >= MAX_MOB)
	//	{
	//		EmptyMob = MAX_USER;

	//		continue;
	//	}

	//	if (pMob[EmptyMob].Mode == MOB_EMPTY)
	//	{
	//		g_EmptyMob = EmptyMob;

	//		return EmptyMob;
	//	}
	//}

	//return 0;
}

int  GetUserByName(char *name)
{
	if (name[0] == '+')
	{
		char *tname = name + 1;

		_strupr(tname);

		for (int i = 1; i < MAX_USER; i++)
		{
			if (pMob[i].Mode == MOB_EMPTY)
				continue;

			if (pUser[i].Mode != USER_PLAY)
				continue;

			if (!strcmp(tname, pUser[i].AccountName))
				return i;
		}
		return 0;
	}

	for (int i = 1; i < MAX_USER; i++)
	{
		if (pMob[i].Mode == MOB_EMPTY)
			continue;

		if (pUser[i].Mode != USER_PLAY)
			continue;

		if (!strcmp(name, pMob[i].MOB.MobName))
			return i;
	}
	return 0;
}

int  IsImple(int user)
{
	return 0;
}

void CloseUser(int conn)
{
	int unk = 0;
	int unk2 = 0;

	if (conn < 0 || conn >= MAX_USER)
		return;

	/*
#pragma region Cubo N
	if (((pMob[conn].TargetX / 128) == 13 && (pMob[conn].TargetY / 128) == 31) && CuboN.pRoom > 0) // Cubo N
		CuboN.pRoom--;

	if (CuboN.pRoom < 0)
		CuboN.pRoom = 0;
#pragma endregion*/

	if (pUser[conn].Mode == USER_PLAY && pMob[conn].TargetX >= 0 && pMob[conn].TargetX < 4096
		&& pMob[conn].TargetY >= 0 && pMob[conn].TargetY < 4096)
		pMobGrid[pMob[conn].TargetY][pMob[conn].TargetX] = 0;

	if (pUser[conn].IsBillConnect)
		SendBilling(conn, pUser[conn].AccountName, 2, 0);

	pUser[conn].cSock.CloseSocket();

	auto& pc = cSQL::instance();
	sprintf(xQuery, "UPDATE accounts SET online = '%d' WHERE username = '%s' ", 0, pUser[conn].AccountName);
	pc.wQuery(xQuery);

	int Mode = pUser[conn].Mode;

	if (Mode && Mode != USER_ACCEPT)
	{
		if (Mode != USER_PLAY && Mode != USER_SAVING4QUIT)
		{
			MSG_STANDARD sm;
			memset(&sm, 0, sizeof(MSG_STANDARD));

			sm.Type = _MSG_DBNoNeedSave;
			sm.ID = conn;

			DBServerSocket.SendOneMessage((char*)&sm, sizeof(MSG_STANDARD));

			pMob[conn].Mode = USER_EMPTY;

			pUser[conn].CloseUser();
		}

		else
		{
			RemoveParty(conn);

			int tradeOpponentID = pUser[conn].Trade.OpponentID;

			if (tradeOpponentID > 0 && tradeOpponentID < MAX_USER && pUser[tradeOpponentID].Mode == USER_PLAY && pUser[tradeOpponentID].Trade.OpponentID == conn)
				RemoveTrade(tradeOpponentID);

			pUser[conn].Trade.OpponentID = 0;

			MSG_SavingQuit sm; 
			memset(&sm, 0, sizeof(MSG_SavingQuit));

			sm.Type = _MSG_SavingQuit;

			if (conn < 0 || conn > MAX_MOB)
			{
				CrackLog(conn, " SaveAndQuitMobidx");
				return;
			}

			int Slot = pUser[conn].Slot;

			if (Slot < 0 || Slot >= MAX_CLASS)
			{
				CrackLog(conn, " SaveAndQuitWrongSlot");
				return;
			}

			memcpy(&sm.MOB, &pMob[conn], sizeof(STRUCT_MOB));
			memcpy(sm.Cargo, &pUser[conn].Cargo, sizeof(pUser[conn].Cargo));

			sm.chave1 = pUser[conn].chave1;
			sm.chave2 = pUser[conn].chave2;
			sm.chave3 = pUser[conn].chave3;

			sm.Timer.RwdTime = pUser[conn].Timer.RwdTime;
			sm.Timer.VipTime = pUser[conn].Timer.VipTime;
			sm.Timer.Time1 = pUser[conn].Timer.Time1;
			sm.Timer.Time2 = pUser[conn].Timer.Time2;
			sm.Timer.Time3 = pUser[conn].Timer.Time3;
			sm.Timer.Time4 = pUser[conn].Timer.Time4;
			sm.Timer.Time5 = pUser[conn].Timer.Time5;
			sm.Timer.Time6 = pUser[conn].Timer.Time6;

			for (int i = 0; i < 50; i++) {
				sm.Keys[i] = pUser[conn].Keys[i];
			}

			for (int c = 0; c < MAX_AFFECT; c++)
			{
				if (pMob[conn].Affect[c].Type != 33)
				{
					if ((pMob[conn].MOB.Equip[0].sIndex == 316 || pMob[conn].MOB.Equip[0].sIndex == 317 || pMob[conn].MOB.Equip[0].sIndex == 297 ||
						pMob[conn].MOB.Equip[0].sIndex == 202 || pMob[conn].MOB.Equip[0].sIndex == 297 || pMob[conn].MOB.Equip[0].sIndex == 209 ||
						pMob[conn].MOB.Equip[0].sIndex == 212 || pMob[conn].MOB.Equip[0].sIndex == 230 || pMob[conn].MOB.Equip[0].sIndex == 228))
						pMob[conn].MOB.Equip[0].sIndex = pMob[conn].extra.ClassMaster == MORTAL ? pMob[conn].extra.MortalFace : pMob[conn].extra.MortalFace + 5 + pMob[conn].MOB.Class;
				}
			}

			if (pMob[conn].MOB.Class == 1)
			{
				for (int o = 0; o < 4; o++)
				{
					if (pMob[conn].MOB.SkillBar[o] == 106 || pMob[conn].MOB.SkillBar[o] == 109 || pMob[conn].MOB.SkillBar[o] == 114)
					{
						if (pMob[conn].MOB.SkillBar[o] == 106) {
							sm.MOB.SkillBar[o] = 118;
						}

						if (pMob[conn].MOB.SkillBar[o] == 109) {
							sm.MOB.SkillBar[o] = 121;
						}

						if (pMob[conn].MOB.SkillBar[o] == 114) {
							sm.MOB.SkillBar[o] = 126;
						}
					}
					else
						sm.MOB.SkillBar[o] = pMob[conn].MOB.SkillBar[o];
				}
			}

			if (pMob[conn].MOB.Class == 1)
			{
				for (int i = 0; i < 16; i++)
				{
					if (pUser[conn].CharShortSkill[i] >= 0 || pUser[conn].CharShortSkill[i] <= 152)
					{
						// Prote��o Absoluta
						if (pUser[conn].CharShortSkill[i] == 106) {
							sm.ShortSkill[i] = 118;
						}

						// Magia Misteriosa
						if (pUser[conn].CharShortSkill[i] == 109) {
							sm.ShortSkill[i] = 121;
						}

						// Incapacitador
						if (pUser[conn].CharShortSkill[i] == 114) {
							sm.ShortSkill[i] = 126;
						}

						sm.ShortSkill[i] = pUser[conn].CharShortSkill[i];
					}
				}
			}
			else
				memcpy(sm.ShortSkill, pUser[conn].CharShortSkill, 16);

			memcpy(sm.affect, pMob[conn].Affect, sizeof(sm.affect));
			sm.extra = pMob[conn].extra;

			strncpy((char*)&sm.AccountName, pUser[conn].AccountName, ACCOUNTNAME_LENGTH);

			sm.Coin = pUser[conn].Coin;
			sm.Donate = pUser[conn].Donate;
			sm.Honra = pUser[conn].Honra;

			sm.DonateBuyItem = pUser[conn].Ingame.DonateBuyItem;
			sm.MobDonateStore = pUser[conn].Ingame.MobDonateStore;

			sm.GemaX = pUser[conn].GemaX;
			sm.GemaY = pUser[conn].GemaY;

			pMob[conn].MOB.SPX = pMob[conn].TargetX;
			pMob[conn].MOB.SPY = pMob[conn].TargetY;

			sm.MOB.SPX = pMob[conn].MOB.SPX;
			sm.MOB.SPY = pMob[conn].MOB.SPY;

			pUser[conn].File.Char[pUser[conn].Slot].SPX = sm.MOB.SPX;
			pUser[conn].File.Char[pUser[conn].Slot].SPY = sm.MOB.SPY;

			pUser[conn].SelChar.SPX[pUser[conn].Slot] = pUser[conn].File.Char[pUser[conn].Slot].SPX;
			pUser[conn].SelChar.SPY[pUser[conn].Slot] = pUser[conn].File.Char[pUser[conn].Slot].SPY;

			sm.Slot = pUser[conn].Slot;

			sm.ID = conn;

			DBServerSocket.SendOneMessage((char*)&sm, sizeof(MSG_SavingQuit));

			pUser[conn].Mode = USER_SAVING4QUIT;
			pMob[conn].CheckLojinha = 0;
			strncpy(pMob[conn].Tab, "", 26);
			DeleteMob(conn, 2);
		}

	}

	else
		pUser[conn].CloseUser();
}

CMob *GetMobFromIndex(unsigned int index)
{
	if (index < 0 || index >= MAX_MOB)
		return NULL;

	return &pMob[index];
}

int  GetAngle(int x, int y)
{
	if (x == 0 || y == 0)
		return 0;

	double tangle = atan2((FLOAT)y, (FLOAT)x);

	int angle = (int)((tangle * 3600) / 6.283184);

	if (angle < 0)
		angle += 3600;

	if (angle > 3600)
		angle -= 3600;

	return angle;
}

int  GetLength(int x, int y)
{
	FLOAT valx = (FLOAT)(x * x);
	FLOAT valy = (FLOAT)(y * y);

	FLOAT valxy = valx + valy;

	if (valxy > 100)
		return 100;

	if (valxy <= 0)
		return 0;

	double fout = sqrt(valxy);

	int out = (int)fout;

	return out;
}

int  ReadMob(STRUCT_MOB *mob, char *dir)
{
	sprintf_s(temp, "./%s/%s", dir, mob->MobName);

	int Handle = _open(temp, O_RDONLY | O_BINARY);

	if (Handle == -1)
	{
		if (errno == EINVAL)
			sprintf_s(temp, "err,ReadMob EEXIST %s", mob->MobName);

		else if (errno == EMFILE)
			sprintf_s(temp, "err,ReadMob EMFILE %s", mob->MobName);

		else if (errno == ENOENT)
			sprintf_s(temp, "err,ReadMob ENOENTN %s", mob->MobName);

		else
			sprintf_s(temp, "err,ReadMob UNKNOW %s", mob->MobName);

		//Log(temp, "-system", 0);
		return FALSE;
	}

	strncpy(temp, mob->MobName, NAME_LENGTH);

	int ret = _read(Handle, mob, sizeof(STRUCT_MOB));

	if (ret == -1)
	{
		_close(Handle);

		return FALSE;
	}

	_close(Handle);

	strncpy(mob->MobName, temp, NAME_LENGTH);

	BASE_GetEnglish(mob->MobName);

	mob->BaseScore = mob->CurrentScore;

	return TRUE;
} 

void DeleteMob(int conn, int Type)
{
	MSG_RemoveMob sm;
	memset(&sm, 0, sizeof(MSG_RemoveMob));

	sm.Type = _MSG_RemoveMob;
	sm.Size = sizeof(MSG_RemoveMob);
	sm.ID = conn;
	sm.RemoveType = Type;

	GridMulticast(pMob[conn].TargetX, pMob[conn].TargetY, (MSG_STANDARD*)&sm, conn);

	if (Type != 0)
	{
		if (conn >= MAX_USER)
		{
			int geneidx = pMob[conn].GenerateIndex;

			if (geneidx >= 0 && geneidx < MAX_NPCGENERATOR)
			{
				mNPCGen.pList[geneidx].CurrentNumMob--;

				if (mNPCGen.pList[geneidx].CurrentNumMob < 0)
					mNPCGen.pList[geneidx].CurrentNumMob = 0;
			}
		}

		pMob[conn].MOB.CurrentScore.Hp = 0;
		pMob[conn].Mode = 0;
		pMobGrid[pMob[conn].TargetY][pMob[conn].TargetX] = 0;

		RemoveParty(conn);
	}

}

void SaveUser(int conn, int Export)
{
	MSG_DBSaveMob sm;
	memset(&sm, 0, sizeof(MSG_DBSaveMob));

	sm.Type = _MSG_DBSaveMob;

	memcpy(&sm.MOB, &pMob[conn].MOB, sizeof(STRUCT_MOB));

	memcpy(&sm.Cargo, pUser[conn].Cargo, sizeof(STRUCT_ITEM)* MAX_CARGO);

	sm.Coin = pUser[conn].Coin;

	sm.ID = conn;
	sm.Export = Export;

	sm.Slot = pUser[conn].Slot;
	sm.Donate = pUser[conn].Donate;
	sm.Honra = pUser[conn].Honra;

	sm.DonateBuyItem = pUser[conn].Ingame.DonateBuyItem;
	sm.MobDonateStore = pUser[conn].Ingame.MobDonateStore;

	sm.chave1 = pUser[conn].chave1;
	sm.chave2 = pUser[conn].chave2;
	sm.chave3 = pUser[conn].chave3; 
	sm.chave4 = pUser[conn].chave4;

	sm.Timer.RwdTime = pUser[conn].Timer.RwdTime;
	sm.Timer.VipTime = pUser[conn].Timer.VipTime;
	sm.Timer.Time1 = pUser[conn].Timer.Time1;
	sm.Timer.Time2 = pUser[conn].Timer.Time2;
	sm.Timer.Time3 = pUser[conn].Timer.Time3;
	sm.Timer.Time4 = pUser[conn].Timer.Time4;
	sm.Timer.Time5 = pUser[conn].Timer.Time5;
	sm.Timer.Time6 = pUser[conn].Timer.Time6;

	/*sm.QuestDiaria.Count1 = pUser[conn].CountMob1;
	sm.QuestDiaria.Count2 = pUser[conn].CountMob2;
	sm.QuestDiaria.Count3 = pUser[conn].CountMob3;

	sm.QuestDiaria.CountMax1 = QuestDiaria[pUser[conn].QuestAtiva].QtdMob1;
	sm.QuestDiaria.CountMax2 = QuestDiaria[pUser[conn].QuestAtiva].QtdMob2;
	sm.QuestDiaria.CountMax3 = QuestDiaria[pUser[conn].QuestAtiva].QtdMob3;

	sm.QuestDiaria.QtdItem = QuestDiaria[pUser[conn].QuestAtiva].Item->stEffect[0].cValue;
	sm.QuestDiaria.ExpReward = QuestDiaria[pUser[conn].QuestAtiva].ExpReward;
	sm.QuestDiaria.GoldReward = QuestDiaria[pUser[conn].QuestAtiva].GoldReward;

	sm.QuestDiaria.IndexQuest = pUser[conn].QuestAtiva;
	sm.QuestDiaria.LastTimeQuest = pUser[conn].LastQuestDay;

	strcpy(sm.QuestDiaria.QuestMobName[0], g_pItemList[QuestDiaria[pUser[conn].QuestAtiva].IdMob1].Name);
	strcpy(sm.QuestDiaria.QuestMobName[1], g_pItemList[QuestDiaria[pUser[conn].QuestAtiva].IdMob2].Name);
	strcpy(sm.QuestDiaria.QuestMobName[2], g_pItemList[QuestDiaria[pUser[conn].QuestAtiva].IdMob3].Name);
	strcpy(sm.QuestDiaria.ItemName, g_pItemList[QuestDiaria[pUser[conn].QuestAtiva].Item->sIndex].Name);*/

	for (int i = 0; i < 50; i++) {
		sm.Keys[i] = pUser[conn].Keys[i];
	}

	sm.GemaX = pUser[conn].GemaX;
	sm.GemaY = pUser[conn].GemaY;
	strncpy(sm.AccountName, pUser[conn].AccountName, ACCOUNTNAME_LENGTH);

	if (pMob[conn].MOB.Class == 1)
	{
		for (int o = 0; o < 4; o++)
		{
			if (pMob[conn].MOB.SkillBar[o] == 106 || pMob[conn].MOB.SkillBar[o] == 109 || pMob[conn].MOB.SkillBar[o] == 114)
			{
				if (pMob[conn].MOB.SkillBar[o] == 106) {
					sm.MOB.SkillBar[o] = 118;
				}

				if (pMob[conn].MOB.SkillBar[o] == 109) {
					sm.MOB.SkillBar[o] = 121;
				}

				if (pMob[conn].MOB.SkillBar[o] == 114) {
					sm.MOB.SkillBar[o] = 126;
				}
			}
			else
				sm.MOB.SkillBar[o] = pMob[conn].MOB.SkillBar[o];
		}
	}

	if (pMob[conn].MOB.Class == 1)
	{
		for (int i = 0; i < 16; i++)
		{
			if (pUser[conn].CharShortSkill[i] == 106 || pUser[conn].CharShortSkill[i] == 109 || pUser[conn].CharShortSkill[i] == 114)
			{
				// Prote��o Absoluta
				if (pUser[conn].CharShortSkill[i] == 106) {
					sm.ShortSkill[i] = 118;
				}

				// Magia Misteriosa
				if (pUser[conn].CharShortSkill[i] == 109) {
					sm.ShortSkill[i] = 121;
				}

				// Incapacitador
				if (pUser[conn].CharShortSkill[i] == 114) {
					sm.ShortSkill[i] = 126;
				}
			}
			else
				sm.ShortSkill[i] = pUser[conn].CharShortSkill[i];
		}
	}
	else
		memcpy(sm.ShortSkill, pUser[conn].CharShortSkill, 16);


	memcpy(sm.affect, pMob[conn].Affect, sizeof(sm.affect));
	sm.extra = pMob[conn].extra;

	sm.MOB.SPX = pMob[conn].MOB.SPX;
	sm.MOB.SPY = pMob[conn].MOB.SPY;

	pUser[conn].File.Char[pUser[conn].Slot].SPX = sm.MOB.SPX;
	pUser[conn].File.Char[pUser[conn].Slot].SPY = sm.MOB.SPY;

	pUser[conn].SelChar.SPX[pUser[conn].Slot] = pUser[conn].File.Char[pUser[conn].Slot].SPX;
	pUser[conn].SelChar.SPY[pUser[conn].Slot] = pUser[conn].File.Char[pUser[conn].Slot].SPY;

	pMob[conn].MissPlayer = FALSE;

	DBServerSocket.SendOneMessage((char*)&sm, sizeof(MSG_DBSaveMob));
}

void CharLogOut(int conn)
{
	if (conn < 0 || conn >= MAX_USER)
	{
		//Log("err,char logout - not conn valid", "-system", 0);
		return;
	}
	if (pUser[conn].Mode != USER_PLAY)
	{
		//Log("err,char logout - not user_play", pUser[conn].AccountName, pUser[conn].IP);

		SendClientSignal(conn, conn, _MSG_CNFCharacterLogout);

		return;
	}

	pUser[conn].Ingame.MobDonateStore = FALSE;
	pUser[conn].Mode = USER_CHARWAIT;

	if (pUser[conn].IsBillConnect && CHARSELBILL == 0)
		SendBilling(conn, pUser[conn].AccountName, 2, 0);

	int trade = pUser[conn].Trade.OpponentID;

	if (trade > 0 && trade < MAX_USER)
	{
		if (pUser[trade].Mode == USER_PLAY && pUser[trade].Trade.OpponentID == conn)
			RemoveTrade(trade);
	}


	//pUser[conn].Mode = USER_SELCHAR;

	pUser[conn].SelChar.Score[pUser[conn].Slot].Level = pMob[conn].MOB.BaseScore.Level;

	pMob[conn].MOB.SPX = pMob[conn].TargetX;
	pMob[conn].MOB.SPY = pMob[conn].TargetY;

	pUser[conn].File.Char[pUser[conn].Slot].SPX = pMob[conn].MOB.SPX;
	pUser[conn].File.Char[pUser[conn].Slot].SPY = pMob[conn].MOB.SPY;

	pUser[conn].SelChar.SPX[pUser[conn].Slot] = pUser[conn].File.Char[pUser[conn].Slot].SPX;
	pUser[conn].SelChar.SPY[pUser[conn].Slot] = pUser[conn].File.Char[pUser[conn].Slot].SPY;

	for (int c = 0; c < MAX_AFFECT; c++)
	{
		if (pMob[conn].Affect[c].Type != 33)
		{
			if ((pMob[conn].MOB.Equip[0].sIndex == 316 || pMob[conn].MOB.Equip[0].sIndex == 317 || pMob[conn].MOB.Equip[0].sIndex == 297 ||
				pMob[conn].MOB.Equip[0].sIndex == 202 || pMob[conn].MOB.Equip[0].sIndex == 297 || pMob[conn].MOB.Equip[0].sIndex == 209 ||
				pMob[conn].MOB.Equip[0].sIndex == 212 || pMob[conn].MOB.Equip[0].sIndex == 230 || pMob[conn].MOB.Equip[0].sIndex == 228))
				pMob[conn].MOB.Equip[0].sIndex = pMob[conn].extra.ClassMaster == MORTAL ? pMob[conn].extra.MortalFace : pMob[conn].extra.MortalFace + 5 + pMob[conn].MOB.Class;
		}
	}

	SaveUser(conn, 1);
	DeleteMob(conn, 2);

	pUser[conn].chave4 = 0;
	pMob[conn].Mode = 0;

	SendClientSignal(conn, conn, _MSG_CNFCharacterLogout);
}

void Reboot()
{
	for (int y = 0; y < MAX_GRIDY; y++)
	{
		for (int x = 0; x < MAX_GRIDX; x++)
		{
			pMobGrid[y][x] = 0;
			pItemGrid[y][x] = 0;
			pHeightGrid[y][x] = 0;
		}
	}

	for (int i = 0; i < 3; i++)
		LiveTower[i] = 0;

	BASE_InitializeMobname("MobName.txt", 0);

	mNPCGen.ReadNPCGenerator();

	int Handle = _open("./heightmap.dat", _O_RDONLY | _O_BINARY, NULL);

	if (Handle == -1)
	{
		Log("err Load height grid fail", "-system", 0);

		return;
	}

	_read(Handle, (void*)pHeightGrid, sizeof(pHeightGrid));
	_close(Handle);

	BASE_InitializeBaseDef();
	BASE_ApplyAttribute((char*)pHeightGrid, MAX_GRIDX);
	BASE_InitializeMessage("Language.txt");

	mSummon.Initialize();

	Log("sys,start server", "-system", 0);

	for (int i = 0; i < g_dwInitItem; i++)
	{
		STRUCT_ITEM Item;
		memset(&Item, 0, sizeof(STRUCT_ITEM));

		Item.sIndex = g_pInitItem[i].ItemIndex;

		int ID = CreateItem(g_pInitItem[i].PosX, g_pInitItem[i].PosY, &Item, g_pInitItem[i].Rotate, 1);

		if (ID >= MAX_ITEM || ID <= 0)
			continue;

		int ret = BASE_GetItemAbility(&Item, EF_KEYID);

		if (ret != 0 && ret < 15)
		{
			int Height;

			UpdateItem(ID, STATE_LOCKED, &Height);
		}
	}

	WeekMode = 4;

	struct tm when;
	time_t now;
	time(&now);
	when = *localtime(&now);

	int GDay = GuildDay - 1;

	if (GDay < 0)
		GDay += 7;

	if (when.tm_wday == GDay)
		WeekMode = 5;

	if (when.tm_wday == GuildDay && when.tm_hour < GuildHour)
		WeekMode = 0;

	SetColoseumDoor(1);
}

void ClearChallanger0()
{
	for (int i = 0; i < ValidGuild; i++)
	{
		if (i == 1 || i == 2 || i == 3 || i == 4)
			continue;

		g_pGuildZone[i].ChallangeGuild = 0;
		pChallangerMoney[i] = 0;
	}
}

void ClearChallanger1()
{
	for (int i = 0; i < ValidGuild; i++)
	{
		if (i == 0 || i == 2 || i == 3 || i == 4)
			continue;

		g_pGuildZone[i].ChallangeGuild = 0;
		pChallangerMoney[i] = 0;
	}
}

void ClearChallanger2()
{
	for (int i = 0; i < ValidGuild; i++)
	{
		if (i == 0 || i == 1 || i == 3 || i == 4)
			continue;

		g_pGuildZone[i].ChallangeGuild = 0;
		pChallangerMoney[i] = 0;
	}
}

void ClearChallanger3()
{
	for (int i = 0; i < ValidGuild; i++)
	{
		if (i == 0 || i == 1 || i == 2 || i == 4)
			continue;

		g_pGuildZone[i].ChallangeGuild = 0;
		pChallangerMoney[i] = 0;
	}
}

void SetBattle(int mob, int target)
{
	if (mob <= 0 || target <= 0 || mob >= MAX_MOB || target >= MAX_MOB)
		return;

	if (pMob[mob].Mode == MOB_EMPTY)
		return;

	if (pMob[target].Mode == MOB_EMPTY)
		return;

	if (mob == target)
		return;

	if (mob >= MAX_USER && (target >= MAX_USER || pUser[target].Mode == USER_PLAY))
	{
		if (pMob[mob].TargetX >= pMob[target].TargetX - 23 && pMob[mob].TargetX <= pMob[target].TargetX + 23 && pMob[mob].TargetY >= pMob[target].TargetY - 23 && pMob[mob].TargetY <= pMob[target].TargetY + 23)
		{
			pMob[mob].Mode = MOB_COMBAT;

			pMob[mob].AddEnemyList(target);

			int generateindex = pMob[mob].GenerateIndex;
			int say = rand() % 4;

			if (generateindex < 0 || generateindex >= MAX_NPCGENERATOR)
				return;

			if (mNPCGen.pList[generateindex].FightAction[say][0] && !pMob[mob].Leader)
				SendChat(mob, mNPCGen.pList[generateindex].FightAction[say]);
		}
	}
}

int  CreateItem(int x, int y, STRUCT_ITEM *item, int rotate, int Create)
{
	if (item->sIndex <= 0 || item->sIndex >= MAX_ITEMLIST)
		return FALSE;

	GetEmptyItemGrid(&x, &y);

	//	if (pHeightGrid[y][x] >= -15 || pHeightGrid[y][x] >= 90)
	//		return FALSE;

	if (pItemGrid[y][x])
		return FALSE;

	int empty = GetEmptyItem();

	if (empty == 0)
		return FALSE;

	pItem[empty].Mode = 1;

	pItem[empty].PosX = x;
	pItem[empty].PosY = y;

	memcpy(&pItem[empty].ITEM, item, sizeof(STRUCT_ITEM));

	pItem[empty].Rotate = rotate;
	pItem[empty].State = STATE_OPEN;

	pItem[empty].Delay = 90;
	pItem[empty].Decay = 0;

	pItem[empty].GridCharge = BASE_GetItemAbility(item, EF_GROUND);

	pItemGrid[y][x] = empty;

	pItem[empty].Height = pHeightGrid[y][x];

	MSG_CreateItem sm;
	memset(&sm, 0, sizeof(MSG_CreateItem));

	sm.Type = _MSG_CreateItem;
	sm.Size = sizeof(MSG_CreateItem);
	sm.ID = ESCENE_FIELD;

	sm.ItemID = empty + 10000;

	memcpy(&sm.Item, &pItem[empty].ITEM, sizeof(STRUCT_ITEM));

	sm.GridX = x;
	sm.GridY = y;

	sm.Rotate = rotate;
	sm.State = pItem[empty].State;
	//	sm.Create = Create;

	//	sm.Height = pItem[empty].Height;

	if (Create == 2)//Bau
		sm.Height = -204;

	GridMulticast(x, y, (MSG_STANDARD*)&sm, 0);

	return TRUE;
}

void RemoveTrade(int conn)
{
	if (conn <= 0 || conn >= MAX_USER)
		return;

	memset(&pUser[conn].Trade, 0, sizeof(MSG_Trade));

	for (int i = 0; i < MAX_TRADE; i++)
		pUser[conn].Trade.InvenPos[i] = -1;

	memset(&pUser[conn].AutoTrade, 0, sizeof(MSG_SendAutoTrade));

	for (int i = 0; i < MAX_AUTOTRADE; i++)
		pUser[conn].AutoTrade.CarryPos[i] = -1;

	if (pUser[conn].Mode != USER_PLAY)
		return;

	SendClientSignal(conn, conn, 900);

	if (pUser[conn].TradeMode)
	{
		int posX = pMob[conn].TargetX;
		int posY = pMob[conn].TargetY;

		MSG_CreateMob sm;
		memset(&sm, 0, sizeof(MSG_CreateMob));

		GetCreateMob(conn, &sm);
		GridMulticast(posX, posY, (MSG_STANDARD*)&sm, 0);

		pUser[conn].TradeMode = 0;
	}
}

void RemoveParty(int conn)
{
	int leader = pMob[conn].Leader;

	if (leader < 0 || leader >= MAX_MOB)
	{
		//Log("err,RemoveParty but worng leader", pUser[conn].AccountName, pUser[conn].IP);
		return;
	}

	if (leader && leader < MAX_USER && pUser[leader].Mode != USER_PLAY)
	{
		//Log("err,removeparty - conn mode", pUser[conn].AccountName, pUser[conn].IP);
		//Log("err,removeparty - leader mode", pUser[conn].AccountName, pUser[conn].IP);

		pMob[conn].Leader = 0;
	}
	else
	{
		if (conn > 0 && conn < MAX_USER)
			SendRemoveParty(conn, 0);

		if (leader)
		{
			SendRemoveParty(leader, conn);
			pMob[conn].Leader = 0;

			for (int i = 0; i < MAX_PARTY; i++)
			{
				int partyconn = pMob[leader].PartyList[i];

				if (partyconn)
				{
					if (partyconn == conn)
						pMob[leader].PartyList[i] = 0;

					if (pMob[partyconn].Summoner && pMob[partyconn].Summoner == conn)
						DeleteMob(partyconn, 3);

					if (!pMob[partyconn].Summoner && partyconn >= MAX_USER && leader < MAX_USER)
						DeleteMob(partyconn, 3);

					if (partyconn > 0 && partyconn <= MAX_USER && pUser[partyconn].Mode == USER_PLAY)
						SendRemoveParty(partyconn, conn);
				}
			}
		}

		else
		{
			int novolider = 0;

			for (int i = 0; i < MAX_PARTY; i++)
			{
				int partyconn = pMob[conn].PartyList[i];

				if (partyconn != 0 && partyconn < MAX_USER)
				{
					novolider = partyconn;

					for (int s = 0; s < 7; s++)
					{
						for (int t = 0; t < 3; t++)
						{
							if (Pista[s].Party[t].LeaderID == conn && strcmp(Pista[s].Party[t].LeaderName, pMob[conn].MOB.MobName) == 0)
							{
								strncpy(Pista[s].Party[t].LeaderName, pMob[novolider].MOB.MobName, NAME_LENGTH);
								Pista[s].Party[t].LeaderID = novolider;
							}
						}
					}

					break;
				}
			}

			for (int i = 0; i < MAX_PARTY; i++)
			{
				int partyconn = pMob[conn].PartyList[i];

				if (partyconn > 0 && partyconn <= MAX_MOB)
				{
					pMob[conn].PartyList[i] = 0;
					pMob[partyconn].Leader = 0;

					if (partyconn > 0 && partyconn < MAX_USER && pUser[partyconn].Mode == USER_PLAY)
						SendRemoveParty(partyconn, 0);

					if (partyconn > MAX_USER)
					{
						if (conn < MAX_USER && pMob[partyconn].Summoner && pMob[partyconn].Summoner == conn)
							DeleteMob(partyconn, 3);

						pMob[partyconn].Summoner = 0;
					}
					if (novolider != 0 && novolider != partyconn && partyconn < MAX_USER && novolider < MAX_USER)
					{
						MSG_AcceptParty sm;
						memset(&sm, 0, sizeof(MSG_AcceptParty));

						sm.Size = sizeof(MSG_AcceptParty);
						sm.Type = _MSG_AcceptParty;
						sm.ID = 0;

						sm.LeaderID = novolider;

						strncpy(sm.MobName, pMob[novolider].MOB.MobName, NAME_LENGTH);

						pMob[partyconn].LastReqParty = novolider;

						ProcessClientMessage(partyconn, (char*)&sm, TRUE);
					}
				}
			}
		}
	}
}

void RemoveEvocation(int conn)
{
	int leader = pMob[conn].Leader;

	if (leader < 0 || leader >= MAX_MOB)
	{
		//Log("err,RemoveParty but worng leader", pUser[conn].AccountName, pUser[conn].IP);
		return;
	}

	if (leader && leader < MAX_USER && pUser[leader].Mode != USER_PLAY)
	{
		//Log("err,removeparty - conn mode", pUser[conn].AccountName, pUser[conn].IP);
		//Log("err,removeparty - leader mode", pUser[conn].AccountName, pUser[conn].IP);

		pMob[conn].Leader = 0;
		pMob[conn].Evocation = 0;
	}
	else
	{
		if (conn > 0 && conn < MAX_USER)
			memset(&pMob[conn].Evocations, 0, sizeof(pMob[conn].Evocations));

		if (leader)
		{
			SendRemoveParty(leader, conn);
			pMob[conn].Leader = 0;
			pMob[conn].Evocation = 0;

			for (int i = 0; i < MAX_PARTY; i++)
			{
				int partyconn = pMob[leader].Evocations[i];

				if (partyconn)
				{
					if (partyconn == conn)
						pMob[leader].Evocations[i] = 0;

					if (pMob[partyconn].Summoner && pMob[partyconn].Summoner == conn)
						DeleteMob(partyconn, 3);

					if (!pMob[partyconn].Summoner && partyconn >= MAX_USER && leader < MAX_USER)
						DeleteMob(partyconn, 3);
				}
			}
		}
	}
}

int UpdateItem(int Gate, int state, int *height)
{
	int rotate = pItem[Gate].Rotate;

	int update = BASE_UpdateItem(pItem[Gate].GridCharge, pItem[Gate].State, state, pItem[Gate].PosX, pItem[Gate].PosY, (char*)&pHeightGrid, rotate, height);

	if (update == 0)
		return FALSE;

	pItem[Gate].State = state;
	pItem[Gate].Height = *height;

	int GridCharge = pItem[Gate].GridCharge;
	int itemstate = pItem[Gate].State;

	pItem[Gate].Delay = 0;

	if (GridCharge >= 6 || GridCharge < 0)
	{
		//Log("err,updateItem maskidx illegal", "-system", 0);
		return TRUE;
	}

	if (itemstate == state)
	{
		int keyid = BASE_GetItemAbility(&pItem[Gate].ITEM, EF_KEYID);

		if (keyid == 15 && itemstate == 1 && state == 3)
			CreateMob("GATE", pItem[Gate].PosX, pItem[Gate].PosY, "npc", 0);

		pItem[Gate].State = state;

		return TRUE;
	}

	int posX = pItem[Gate].PosX;
	int posY = pItem[Gate].PosY;

	for (int i = 0; i <= MAX_GROUNDMASK - 2; i++)
	{
		for (int j = 0; j <= MAX_GROUNDMASK - 2; j++)
		{
			int val = g_pGroundMask[GridCharge][rotate][i][j];

			int iX = posX + j - 2;
			int jY = posY + i - 2;

			if (iX >= 1 && jY >= 1 && iX <= 4094 && jY <= 4094 && val)
			{
				int tmob = pMobGrid[jY][iX];

				if (tmob != 0)
				{
					if (pMob[tmob].MOB.Equip[0].sIndex == 220)
						DeleteMob(tmob, 3);

					else
					{
						int mobgrid = GetEmptyMobGrid(tmob, &iX, &jY);

						if (mobgrid != 0)
						{
							pMob[tmob].Route[0] = 0;

							MSG_Action sm;
							memset(&sm, 0, sizeof(MSG_Action));

							GetAction(tmob, iX, jY, &sm);

							int unk = 20;
							int unk2 = 0;

							GridMulticast(iX, jY, (MSG_STANDARD*)&sm, 0);

							if (tmob < MAX_USER)
								pUser[tmob].cSock.SendOneMessage((char*)&sm, sizeof(sm));
						}
					}
				}
			}
		}
	}

	return TRUE;
}

void DoRecall(int conn)
{

	int x = pMob[conn].MOB.SPX;
	int y = pMob[conn].MOB.SPY;
	int CityID = (pMob[conn].MOB.Merchant & 0xC0) >> 6;

	x = rand() % 15 + g_pGuildZone[CityID].CitySpawnX;
	y = rand() % 15 + g_pGuildZone[CityID].CitySpawnY;

	int Guild = pMob[conn].MOB.Guild;

	pMob[conn].LanNFlag = 0;
	pMob[conn].LanMFlag = 0;
	pMob[conn].LanAFlag = 0;
	pUser[conn].DiariaState = 0;

	if (Guild > 0)
	{
		for (int i = 0; i < MAX_GUILDZONE; i++)
		{
			if (Guild == g_pGuildZone[i].ChargeGuild)
			{
				x = g_pGuildZone[i].GuildSpawnX;
				y = g_pGuildZone[i].GuildSpawnY;

				break;
			}
		}
	}	

	int j = 0;
	for (j = 0; j < pMob[conn].MaxCarry; j++)
	{
		if (pMob[conn].MOB.Carry[j].sIndex != 5675)
			continue;

		if (pMob[conn].MOB.Carry[j].sIndex == 5675) {
			BASE_ClearItem(&pMob[conn].MOB.Carry[j]);
			SendItem(conn, ITEM_PLACE_CARRY, j, &pMob[conn].MOB.Carry[j]);
			SendCarry(conn);
		}

	}

	if (pMob[conn].extra.ClassMaster == MORTAL && pMob[conn].MOB.CurrentScore.Level < FREEEXP)
	{
		x = 2112 + rand() % 5 - 3;
		y = 2042 + rand() % 5 - 3;
	}

	int tret = GetEmptyMobGrid(conn, &x, &y);

	MSG_Action sm;
	memset(&sm, 0, sizeof(MSG_Action));

	GetAction(conn, x, y, &sm);

	sm.Effect = 1;

	if (conn < MAX_USER)
		pUser[conn].cSock.SendOneMessage((char*)&sm, sizeof(sm));

	GridMulticast(conn, x, y, (MSG_STANDARD*)&sm);
}

void DoWar(int myguild, int target)
{
	int max_guild = 65536;

	if (myguild <= 0 || target < 0 || myguild >= max_guild || target >= max_guild)
	{
		//sprintf(temp, "err,dowar my: %d ta:%d", myguild, target);
		//Log(temp, "-system", 0);
		return;
	}

	char myGuildName[16];
	char targetGuildName[16];

	BASE_GetGuildName(ServerGroup, myguild, myGuildName);
	BASE_GetGuildName(ServerGroup, target, targetGuildName);

	int myGuildWar = g_pGuildWar[myguild];

	if (myGuildWar < 0 || myGuildWar >= max_guild)
		myGuildWar = 0;

	int targetGuildWar = g_pGuildWar[target];

	if (target)
	{
		if (myGuildWar || !target || targetGuildWar == myguild)
		{
			if (myGuildWar || !target || targetGuildWar != myguild)
			{
				//sprintf(temp, "err,dowar my:%d ta:%d ct:%d et:%d", myguild, target, myGuildWar, targetGuildWar);
				//Log(temp, "-system", 0);
			}
			else
			{
				SendNotice(strFmt(g_pMessageStringTable[_SS_War_Started], myGuildName, targetGuildName));

				g_pGuildWar[myguild] = target;

				for (int i = 0; i < MAX_USER; i++)
				{
					if (pUser[i].Mode == USER_PLAY && (pMob[i].MOB.Guild == myguild || pMob[i].MOB.Guild == target))
						SendWarInfo(i, g_pGuildZone[4].Clan);

				}
			}
		}

		else
		{
			SendGuildNotice(myguild, strFmt(g_pMessageStringTable[_SS_War_Declared], myGuildName, targetGuildName));
			SendGuildNotice(target, strFmt(g_pMessageStringTable[_SS_War_Declared], myGuildName, targetGuildName));

			g_pGuildWar[myguild] = target;
		}
	}
	else
	{
		if (myGuildWar <= 0 || myGuildWar >= max_guild)
			return;

		targetGuildWar = g_pGuildWar[myGuildWar];

		BASE_GetGuildName(ServerGroup, myGuildWar, targetGuildName);

		if (targetGuildWar == myguild)
		{
			sprintf_s(temp, g_pMessageStringTable[_SS_War_Canceled], myGuildName, targetGuildName);

			g_pGuildWar[myGuildWar] = 0;
			g_pGuildWar[myguild] = 0;

			for (int j = 0; j < MAX_USER; j++)
			{
				if (pUser[j].Mode == USER_PLAY && (pMob[j].MOB.Guild == myguild || pMob[j].MOB.Guild == myGuildWar))
					SendWarInfo(j, g_pGuildZone[4].Clan);
			}
		}

		else
		{
			sprintf_s(temp, g_pMessageStringTable[_SS_War_declare_canceled], myGuildName, targetGuildName);
			g_pGuildWar[myguild] = 0;
		}

		SendGuildNotice(myguild, temp);
		SendGuildNotice(myGuildWar, temp);
	}
}

void DoAlly(int myguild, int target)
{
	int max_guild = 65536;

	if (myguild <= 0 || target < 0 || myguild >= max_guild || target >= max_guild)
	{
		//sprintf(temp, "err,doally my: %d ta:%d", myguild, target);
		//Log(temp, "-system", 0);
		return;
	}

	char myGuildName[16];
	char targetGuildName[16];

	BASE_GetGuildName(ServerGroup, myguild, myGuildName);
	BASE_GetGuildName(ServerGroup, target, targetGuildName);

	int myGuildAlly = g_pGuildAlly[myguild];

	if (myGuildAlly < 0 || myGuildAlly >= max_guild)
		myGuildAlly = 0;

	int targetGuildAlly = g_pGuildAlly[target];

	if (!myGuildAlly)
	{
		if (!myGuildAlly && target)
		{
			SendNotice(strFmt(g_pMessageStringTable[_SS_Ally_Declared], myGuildName, targetGuildName));

			g_pGuildAlly[myguild] = target;
		}
	}
	else
	{
		myGuildAlly = g_pGuildAlly[myguild];

		if (myGuildAlly > 0 && myGuildAlly < max_guild)
		{
			BASE_GetGuildName(ServerGroup, myGuildAlly, targetGuildName);

			SendNotice(strFmt(g_pMessageStringTable[_SS_Ally_Canceled], myGuildName, targetGuildName));

			g_pGuildAlly[myguild] = 0;
		}
	}

	for (int i = 0; i < MAX_USER; i++)
	{
		if (pUser[i].Mode == USER_PLAY && pMob[i].MOB.Guild == myguild)
			SendWarInfo(i, g_pGuildZone[4].Clan);
	}
}

void DoDeprivate(int conn, int target)
{
	if (conn <= 0 || conn > MAX_USER)
	{
		//Log("err,dodeprivate - conn", "-system", 0);

		return;
	}

	int Guild = pMob[conn].MOB.Guild;
	int GuildLevel = pMob[conn].MOB.GuildLevel;


	if (target <= 0 || target > MAX_USER || pUser[target].Mode != USER_PLAY)
	{
		SendClientMessage(conn, g_pMessageStringTable[_NN_Not_Connected]);

		return;
	}

	if (GuildLevel <= pMob[target].MOB.GuildLevel)
	{
		 SendMsgExp(conn, g_pMessageStringTable[_NN_Only_Guild_Master_Can], TNColor::Default, false);
		return;
	}

	int sub = pMob[conn].MOB.GuildLevel;
	int Disqualified = FALSE;


	int gGuild = pMob[target].MOB.Guild;

	if (Guild != gGuild)
		return;

	if (sub >= 6 && sub <= 8 && pMob[target].MOB.GuildLevel < 6 || sub == 9)
	{
		Disqualified = TRUE;

		if (pMob[target].MOB.GuildLevel >= 6 && pMob[target].MOB.GuildLevel <= 8)
		{
			if (GuildInfo[gGuild].Sub1 != 0)
				GuildInfo[gGuild].Sub1 = 0;
			else if (GuildInfo[gGuild].Sub2 != 0)
				GuildInfo[gGuild].Sub2 = 0;

			else if (GuildInfo[gGuild].Sub3 != 0)
				GuildInfo[gGuild].Sub3 = 0;


			//sprintf(temp, "etc,subdelete subname:%s guild:%d ", pMob[target].MOB.MobName, Guild);
			//Log(temp, pUser[conn].AccountName, pUser[conn].IP);

			MSG_GuildInfo sm_gi;
			memset(&sm_gi, 0, sizeof(MSG_GuildInfo));

			sm_gi.Type = _MSG_GuildInfo;
			sm_gi.Size = sizeof(MSG_GuildInfo);
			sm_gi.ID = conn;

			sm_gi.Guild = Guild;
			sm_gi.GuildInfo = GuildInfo[Guild];

			DBServerSocket.SendOneMessage((char*)&sm_gi, sizeof(MSG_GuildInfo));
		}

		pMob[target].MOB.Guild = 0;
		pMob[target].MOB.GuildLevel = 0;

		doRanking(target);
		
		MSG_CreateMob sm;
		memset(&sm, 0, sizeof(MSG_CreateMob));

		GetCreateMob(target, &sm);

		GridMulticast(pMob[target].TargetX, pMob[target].TargetY, (MSG_STANDARD*)&sm, 0);
	}


	if (Disqualified == FALSE)
	{
		 
		SendMsgExp(conn, g_pMessageStringTable[_NN_Deprivate], TNColor::Default, false);
		return;
	}

	SendScore(target);

	SendClientMessage(target, g_pMessageStringTable[_NN_Disqualified_By_Guild_Master]);
	SendClientMessage(conn, g_pMessageStringTable[_NN_Disqualify]);
}

void ProcessRanking()
{
	if (RankingTime <= 0)
		return;

	RankingTime--;

	if (RankingTime % 5 == 0)
	{
		int Rank1 = 0;
		int Rank2 = 0;

		for (int i = 1; i < MAX_USER; i++)
		{
			if (pUser[i].Mode != USER_PLAY)
				continue;

			if (pMob[i].MOB.CurrentScore.Hp <= 0)
				continue;

			int posX = pMob[i].TargetX;
			int posY = pMob[i].TargetY;

			if (posX >= kRanking1X && posX <= kRanking2X && posY >= kRanking1Y && posY <= kRanking2Y)
			{
				if (RankingProgress == 1)
				{
					if (i == Ranking1)
						Rank1++;

					if (i == Ranking2)
						Rank2++;
				}

				else
				{
					if (pMob[i].MOB.Guild == Ranking1)
						Rank1++;

					if (pMob[i].MOB.Guild == Ranking2)
						Rank2++;
				}
			}
		}

		if (Rank1 == 0 || Rank2 == 0)
			RankingTime = 0;
	}

	if (RankingTime >= 60)
	{
		if (RankingTime >= 120)
		{
			if (RankingTime < 180)
			{
				SendDamage(142, 4007, 195, 4019);
				SendDamage(142, 4070, 195, 4082);

				SendEnvEffect(142, 4007, 168, 4018, 32, 0);
				SendEnvEffect(142, 4071, 168, 4082, 32, 0);
				SendEnvEffect(169, 4007, 195, 4018, 32, 0);
				SendEnvEffect(169, 4071, 195, 4082, 32, 0);
			}
		}
		else
		{
			SendDamage(142, 4007, 195, 4034);
			SendDamage(142, 4055, 195, 4082);

			SendEnvEffect(142, 4007, 168, 4018, 32, 0);
			SendEnvEffect(142, 4071, 168, 4082, 32, 0);
			SendEnvEffect(142, 4019, 168, 4030, 32, 0);
			SendEnvEffect(142, 4059, 168, 4070, 32, 0);
			SendEnvEffect(168, 4007, 195, 4018, 32, 0);
			SendEnvEffect(168, 4071, 195, 4082, 32, 0);
			SendEnvEffect(168, 4019, 195, 4030, 32, 0);
			SendEnvEffect(168, 4059, 195, 4070, 32, 0);
		}
	}
	else
	{
		SendDamage(142, 4007, 195, 4042);
		SendDamage(142, 4046, 195, 4082);
		SendEnvEffect(142, 4007, 168, 4018, 32, 0);
		SendEnvEffect(142, 4071, 168, 4082, 32, 0);
		SendEnvEffect(142, 4019, 168, 4030, 32, 0);
		SendEnvEffect(142, 4059, 168, 4070, 32, 0);
		SendEnvEffect(142, 4031, 168, 4042, 32, 0);
		SendEnvEffect(142, 4047, 168, 4058, 32, 0);
		SendEnvEffect(168, 4007, 195, 4018, 32, 0);
		SendEnvEffect(168, 4071, 195, 4082, 32, 0);
		SendEnvEffect(168, 4019, 195, 4030, 32, 0);
		SendEnvEffect(168, 4059, 195, 4070, 32, 0);
		SendEnvEffect(168, 4031, 195, 4042, 32, 0);
		SendEnvEffect(168, 4047, 195, 4058, 32, 0);
	}

	if (RankingTime <= 0)
	{
		int Rank1 = 0;
		int Rank2 = 0;

		for (int i = 1; i < MAX_USER; i++)
		{
			if (pUser[i].Mode != USER_PLAY)
				continue;

			if (pMob[i].MOB.CurrentScore.Hp <= 0)
				continue;

			int posX = pMob[i].TargetX;
			int posY = pMob[i].TargetY;

			if (posX >= kRanking1X && posX <= kRanking2X && posY >= kRanking1Y && posY <= kRanking2Y)
			{
				if (RankingProgress == 1)
				{
					if (i == Ranking1)
						Rank1++;

					if (i == Ranking2)
						Rank2++;
				}

				else
				{
					if (pMob[i].MOB.Guild == Ranking1)
						Rank1++;

					if (pMob[i].MOB.Guild == Ranking2)
						Rank2++;
				}
			}
		}

		nRanking1[15] = 0;
		nRanking1[16] = 0;
		nRanking2[15] = 0;
		nRanking2[16] = 0;

		nTitle1[15] = 0;
		nTitle1[16] = 0;
		nTitle2[15] = 0;
		nTitle2[16] = 0;


		if (Rank1 == Rank2)
		{
			SendNoticeArea(strFmt(g_pMessageStringTable[_SS_S_S_Draw], nRanking1, nRanking2), cRanking1X, cRanking1Y, cRanking2X, cRanking2Y);
			SendNoticeArea(strFmt(g_pMessageStringTable[_SS_S_S_Draw], nRanking1, nRanking2), kRanking1X, kRanking1Y, kRanking2X, kRanking2Y);
		}

		else
		{
			if (Rank1 <= Rank2)
				sprintf_s(temp, g_pMessageStringTable[_SS_S_WinBy_S], nRanking2, nRanking1);
			else
				sprintf_s(temp, g_pMessageStringTable[_SS_S_WinBy_S], nRanking1, nRanking2);

			SendNoticeArea(temp, cRanking1X, cRanking1Y, cRanking2X, cRanking2Y);
			SendNoticeArea(temp, kRanking1X, kRanking1Y, kRanking2X, kRanking2Y);

			MSG_MessageDBRecord sm;
			memset(&sm, 0, sizeof(MSG_MessageDBRecord));

			sm.Type = _MSG_MessageDBRecord;
			sm.ID = 0;
			sm.Size = sizeof(MSG_MessageDBRecord);

			if (RankingProgress != 1 || Ranking1 <= 0 || Ranking1 >= MAX_USER || Ranking2 <= 0 || Ranking2 >= MAX_USER)
			{
				if (Rank1 <= Rank2)
					sprintf_s(temp, "RNK %d %d %s %d %d %s %d %d", ServerIndex, RankingProgress, nRanking2, lTitle2, Ranking2, nRanking1, lTitle1, Ranking1);
				else
					sprintf_s(temp, "RNK %d %d %s %d %d %s %d %d", ServerIndex, RankingProgress, nRanking1, lTitle1, Ranking1, nRanking2, lTitle2, Ranking2);
			}

			else
			{
				int GuildR1 = pMob[Ranking1].MOB.Guild;
				int GuildR2 = pMob[Ranking2].MOB.Guild;

				if (Rank1 <= Rank2)
					sprintf_s(temp, "RNK %d %d %s %d %d %s %d %d", ServerIndex, RankingProgress, nRanking2, lTitle2, GuildR2, nRanking1, lTitle1, GuildR1);
				else
					sprintf_s(temp, "RNK %d %d %s %d %d %s %d %d", ServerIndex, RankingProgress, nRanking1, lTitle1, GuildR1, nRanking2, lTitle2, GuildR2);
			}

			DBServerSocket.SendOneMessage((char*)&sm, sm.Size);
		}

		RankingProgress = 0;
		RankingTime = 0;
		Ranking1 = 0;
		Ranking2 = 0;

		nRanking1[0] = 0;
		nRanking2[0] = 0;

		ClearAreaTeleport(kRanking1X, kRanking1Y, kRanking2X, kRanking2Y, 2572, 1752);
	}
}

void DoRanking(int tDuel, int conn, int enemy)
{
	if (tDuel == 0)
	{
		int duelTime = 121;

		if (conn < 0 || conn >= MAX_USER || enemy < 0 || enemy >= MAX_USER)
			return;

		strncpy(nRanking1, pMob[conn].MOB.MobName, NAME_LENGTH);
		strncpy(nRanking2, pMob[enemy].MOB.MobName, NAME_LENGTH);

		lTitle1 = pMob[conn].MOB.CurrentScore.Level;
		lTitle2 = pMob[enemy].MOB.CurrentScore.Level;

		DoTeleport(conn, Ranking2X, Ranking2Y);
		DoTeleport(enemy, Ranking1X, Ranking1Y);

		sprintf_s(temp, g_pMessageStringTable[_NN_Battle_Started], pMob[conn].MOB.MobName, pMob[enemy].MOB.MobName);

		SendClientMessage(conn, temp);
		SendClientMessage(enemy, temp);

		SendClientSignalParm(conn, ESCENE_FIELD, _MSG_StartTime, 2 * duelTime - 2);
		SendClientSignalParm(enemy, ESCENE_FIELD, _MSG_StartTime, 2 * duelTime - 2);

		RankingProgress = 1;
		Ranking1 = conn;
		Ranking2 = enemy;
		RankingTime = duelTime;

		return;
	}

	int duelTime = 301;

	int GuildR1 = pMob[conn].MOB.Guild;
	int GuildR2 = pMob[enemy].MOB.Guild;

	if (GuildR1 <= 0 || GuildR2 <= 0)
		return;

	if (GuildR1 == GuildR2)
		return;

	RankingProgress = tDuel + 1;
	Ranking1 = GuildR1;
	Ranking2 = GuildR2;
	RankingTime = duelTime;

	BASE_GetGuildName(ServerGroup, Ranking1, nRanking1);
	BASE_GetGuildName(ServerGroup, Ranking2, nRanking2);

	strncpy(nTitle1, pMob[conn].MOB.MobName, NAME_LENGTH);

	lTitle1 = pMob[conn].MOB.CurrentScore.Level;

	strncpy(nTitle2, pMob[enemy].MOB.MobName, NAME_LENGTH);

	lTitle2 = pMob[enemy].MOB.CurrentScore.Level;

	int jRank1 = 5;
	int jRank2 = 5;

	if (tDuel == 2)
	{
		jRank1 = 10;
		jRank2 = 10;
	}

	else if (tDuel == 3)
	{
		jRank1 = 100;
		jRank2 = 100;

		SummonGuild(Ranking1, Ranking1X, Ranking1Y, 100, 3);
		SummonGuild(Ranking2, Ranking1X, Ranking1Y, 100, 3);
	}

	else
	{
		for (int i = cRanking1Y; i <= cRanking2Y; i++)
		{
			for (int j = cRanking1X; j <= cRanking2X; j++)
			{
				int tmob = pMobGrid[i][j];

				if (tmob <= 0 || tmob >= MAX_USER)
					continue;

				if (jRank1 > 0 && pMob[tmob].MOB.Guild == Ranking1)
				{
					jRank1--;

					DoTeleport(tmob, Ranking1X, Ranking1Y);

					SendClientMessage(tmob, g_pMessageStringTable[194]);
					SendClientSignalParm(tmob, ESCENE_FIELD, _MSG_StartTime, 2 * duelTime - 2);
				}

				if (jRank2 > 0 && pMob[tmob].MOB.Guild == Ranking2)
				{
					jRank2--;

					DoTeleport(tmob, Ranking2X, Ranking2Y);

					SendClientMessage(tmob, g_pMessageStringTable[194]);
					SendClientSignalParm(tmob, ESCENE_FIELD, _MSG_StartTime, 2 * duelTime - 2);
				}
				if (jRank1 <= 0 || jRank2 <= 0)
					break;
			}
		}
	}
}

void DoRemoveHide(int conn)
{
	if (conn <= 0 || conn >= MAX_USER)
		return;

	for (int i = 0; i < MAX_AFFECT; i++)
	{
		if (pMob[conn].Affect[i].Type != 28)
			continue;

		pMob[conn].Affect[i].Type = 0;
		pMob[conn].Affect[i].Value = 0;
		pMob[conn].Affect[i].Level = 0;
		pMob[conn].Affect[i].Time = 0;

		pMob[conn].GetCurrentScore(conn);
		SendScore(conn);

		break;
	}
}


void DoRemoveMutation(int conn)
{
	if (conn <= 0 || conn >= MAX_USER)
		return;

	for (int i = 0; i < MAX_AFFECT; i++)
	{
		if (pMob[conn].Affect[i].Type != 33)
			continue;

		pMob[conn].Affect[i].Type = 0;
		pMob[conn].Affect[i].Value = 0;
		pMob[conn].Affect[i].Level = 0;
		pMob[conn].Affect[i].Time = 0;

		if ((pMob[conn].MOB.Equip[0].sIndex == 316 || pMob[conn].MOB.Equip[0].sIndex == 317 || pMob[conn].MOB.Equip[0].sIndex == 297 ||
			pMob[conn].MOB.Equip[0].sIndex == 202 || pMob[conn].MOB.Equip[0].sIndex == 297 || pMob[conn].MOB.Equip[0].sIndex == 209 ||
			pMob[conn].MOB.Equip[0].sIndex == 212 || pMob[conn].MOB.Equip[0].sIndex == 230 || pMob[conn].MOB.Equip[0].sIndex == 228))
			pMob[conn].MOB.Equip[0].sIndex = pMob[conn].extra.ClassMaster == MORTAL ? pMob[conn].extra.MortalFace : pMob[conn].extra.MortalFace + 5 + pMob[conn].MOB.Class;

		pMob[conn].GetCurrentScore(conn);
		SendScore(conn);
		SendEquip(conn, 0);

		break;
	}
}


void DoRemoveAbsoluteProtection(int conn)
{
	if (conn <= 0 || conn >= MAX_USER)
		return;

	for (int i = 0; i < MAX_AFFECT; i++)
	{
		if (pMob[conn].Affect[i].Type != 6)
			continue;

		pMob[conn].Affect[i].Type = 0;
		pMob[conn].Affect[i].Value = 0;
		pMob[conn].Affect[i].Level = 0;
		pMob[conn].Affect[i].Time = 0;

		pMob[conn].GetCurrentScore(conn);
		SendScore(conn);

		break;
	}
}

void DoRemoveAllBuffs(int conn)
{
	if (conn <= 0 || conn >= MAX_USER)
		return;

	for (int i = 0; i < MAX_AFFECT; i++)
	{
		if  (pMob[conn].Affect[i].Type != 2 || pMob[conn].Affect[i].Type !=  6 || pMob[conn].Affect[i].Type != 9 ||
			pMob[conn].Affect[i].Type != 11 || pMob[conn].Affect[i].Type != 13 || pMob[conn].Affect[i].Type != 14 ||
			pMob[conn].Affect[i].Type != 15 || pMob[conn].Affect[i].Type != 16 || pMob[conn].Affect[i].Type != 17 ||
			pMob[conn].Affect[i].Type != 18 || pMob[conn].Affect[i].Type != 19 || pMob[conn].Affect[i].Type != 21 ||
			pMob[conn].Affect[i].Type != 22 || pMob[conn].Affect[i].Type != 23 || pMob[conn].Affect[i].Type != 24 ||
			pMob[conn].Affect[i].Type != 25 || pMob[conn].Affect[i].Type != 26 || pMob[conn].Affect[i].Type != 27 ||
			pMob[conn].Affect[i].Type != 31 || pMob[conn].Affect[i].Type != 36 || pMob[conn].Affect[i].Type != 37 ||
			pMob[conn].Affect[i].Type != 38 || pMob[conn].Affect[i].Type != 42 || pMob[conn].Affect[i].Type != 43)
			continue;

		pMob[conn].Affect[i].Type = 0;
		pMob[conn].Affect[i].Value = 0;
		pMob[conn].Affect[i].Level = 0;
		pMob[conn].Affect[i].Time = 0;

		pMob[conn].GetCurrentScore(conn);
		SendScore(conn);

		break;
	}
}

void DoRemoveSamaritano(int conn)
{
	if (conn <= 0 || conn >= MAX_USER)
		return;

	for (int i = 0; i < MAX_AFFECT; i++)
	{
		if (pMob[conn].Affect[i].Type != 24)
			continue;

		pMob[conn].Affect[i].Type = 0;
		pMob[conn].Affect[i].Value = 0;
		pMob[conn].Affect[i].Level = 0;
		pMob[conn].Affect[i].Time = 0;

		pMob[conn].GetCurrentScore(conn);
		SendScore(conn);

		break;
	}
}

void DoTeleport(int mob, int x, int y)
{
	MSG_Action sm;
	memset(&sm, 0, sizeof(MSG_Action));

	int ret = GetEmptyMobGrid(mob, &x, &y);

	pMob[mob].LanNFlag = 0;
	pMob[mob].LanMFlag = 0;
	pMob[mob].LanAFlag = 0;

	if (mob < MAX_USER && mob > 0)
		pUser[mob].DiariaState = 0;

	if (ret)
	{
		GetAction(mob, x, y, &sm);

		sm.Effect = 1; // teleport effect

		if (mob < MAX_USER && mob > 0)
			if (!pUser[mob].cSock.AddMessage((char*)&sm, sizeof(MSG_Action)))
				CloseUser(mob);

		GridMulticast(mob, x, y, (MSG_STANDARD*)&sm);
	}
}

void DoSummon(int target, int x, int y)
{
	MSG_Action sm;

	memset(&sm, 0, sizeof(MSG_Action));

	int tret = GetEmptyMobGrid(target, &x, &y);

	GetAction(target, x, y, &sm);

	sm.Effect = 1; // teleport effect

	if (target < MAX_USER)
		pUser[target].cSock.SendOneMessage((char*)&sm, sizeof(sm));

	GridMulticast(target, x, y, (MSG_STANDARD*)&sm);
}

void DoGreatTeleport(int mob, int x, int y)
{
	MSG_Action sm;
	memset(&sm, 0, sizeof(MSG_Action));

	int ret = GetEmptyMobGridGreat(mob, &x, &y);

	if (ret)
	{
		GetAction(mob, x, y, &sm);

		sm.Effect = 1; // teleport effect

		if (mob < MAX_USER)
			pUser[mob].cSock.SendOneMessage((char*)&sm, sizeof(sm));

		GridMulticast(mob, x, y, (MSG_STANDARD*)&sm);
	}
}

BOOL SetAffect1(int conn, int skillnum, int time, int Level)
{
	if (skillnum < 104)
	{
		if (pMob[conn].MOB.Merchant != 1 || conn <= MAX_USER)
		{
			int sAffectType = g_pSpell[skillnum].AffectType;
			int sAggressive = g_pSpell[skillnum].Aggressive;
			int sAffectTime = g_pSpell[skillnum].AffectTime;
			int unk = skillnum / 24 % 4;
			int unk2 = skillnum % 24 / 8;
			int sTickType = g_pSpell[skillnum].TickType;
			int unk3 = 0;

			if (skillnum != 47 && pMob[conn].MOB.Rsv & 0x200 && sAggressive)
				return FALSE;
			else
			{
				if (skillnum == 47 && pMob[conn].MOB.Rsv & 0x200)
				{
					for (int i = 1; i < MAX_AFFECT; i++)
					{
						if (pMob[conn].Affect[i].Type == 19)
						{
							pMob[conn].Affect[i].Type = 0;
							pMob[conn].Affect[i].Time = 0;
							pMob[conn].GetCurrentScore(conn);
							SendScore(conn);
							//Level = 0;
							//return Level;

							return FALSE;
						}
					}
				}

				if (skillnum == 102)
					unk3 = 15;
				else
				{
					unk3 = GetEmptyAffect(conn, sAffectType);

					if (sAffectType > 0)
						unk3 = GetEmptyAffect(conn, sAffectType);

					if (sTickType > 0)
						unk3 = GetEmptyAffect(conn, sTickType);
				}

				if (unk3 < 0 || unk3 >= 16)
					return FALSE;
				else
				{
					if (sTickType)
					{

					}
					else
					{

					}
				}
			}
		}
	}
}
BOOL SetAffect(int conn, int skillnum, int time, int Level)
{
	if (pMob[conn].MOB.Merchant == 1 || conn > MAX_USER)
		return FALSE;

	int sAffectType = g_pSpell[skillnum].AffectType;
	int sAggressive = g_pSpell[skillnum].Aggressive;

	if (pMob[conn].MOB.Rsv & RSV_BLOCK && sAggressive)
		return FALSE;

	int EmptyAffect = 0;

	if (skillnum == 102)
		EmptyAffect = 15;
	else
		EmptyAffect = GetEmptyAffect(conn, sAffectType);

	if (sAffectType <= 0 || EmptyAffect < 0 || EmptyAffect >= MAX_AFFECT)
		return FALSE;

	int sType = pMob[conn].Affect[EmptyAffect].Type;

	pMob[conn].Affect[EmptyAffect].Type = sAffectType;
	pMob[conn].Affect[EmptyAffect].Value = g_pSpell[skillnum].AffectValue;

	int sTime = (g_pSpell[skillnum].AffectTime + 1) * time / 100;

	if (sType == 1 || sType == 3 || sType == 10)
		sTime = 4;

	if (sType == sAffectType && (unsigned int)sTime > pMob[conn].Affect[EmptyAffect].Time)
		pMob[conn].Affect[EmptyAffect].Time = sTime;
	else
		pMob[conn].Affect[EmptyAffect].Time = sTime;

	if (sType == sAffectType && Level > pMob[conn].Affect[EmptyAffect].Level)
		pMob[conn].Affect[EmptyAffect].Level = Level;
	else
		pMob[conn].Affect[EmptyAffect].Level = Level;

	if (time >= 2139062143)
		pMob[conn].Affect[EmptyAffect].Time = 2139062143;

	pMob[conn].GetCurrentScore(conn);

	return TRUE;
}

BOOL SetTick(int mob, int skillnum, int Delay, int Level)
{
	if (pMob[mob].MOB.Merchant == 1 && mob > MAX_USER)
		return FALSE;

	int sTickType = g_pSpell[skillnum].TickType;
	int sAggressive = g_pSpell[skillnum].Aggressive;

	if ((pMob[mob].MOB.Rsv & RSV_BLOCK) && (sAggressive != 0))
		return 0;

	int EmptyAffect = 0;

	if (skillnum == 102)
		EmptyAffect = 15;
	else
		EmptyAffect = GetEmptyAffect(mob, sTickType);

	if (sTickType > 0 && EmptyAffect >= 0 && EmptyAffect < MAX_AFFECT) //EmptyAffect >= 0
	{
		pMob[mob].Affect[EmptyAffect].Type = sTickType;
		pMob[mob].Affect[EmptyAffect].Value = g_pSpell[skillnum].TickValue;
		pMob[mob].Affect[EmptyAffect].Time = (Delay * (g_pSpell[skillnum].AffectTime + 1)) / 100;

		if (Delay >= 500000000)
			pMob[mob].Affect[EmptyAffect].Time = 500000000;

		if (pMob[mob].Affect[EmptyAffect].Time >= 3 && (sTickType == 1 || sTickType == 3 || sTickType == 10))
			pMob[mob].Affect[EmptyAffect].Time = 2;

		pMob[mob].Affect[EmptyAffect].Level = Level;

		pMob[mob].GetCurrentScore(mob);

		return TRUE;
	}

	return FALSE;
}

void ProcessDecayItem()
{
	for (int i = 0; i < ItemCount; i++)
	{
		ItemCount++;

		if (ItemCount >= 5000)
			ItemCount = g_dwInitItem + 1;

		if (pItem[ItemCount].ITEM.sIndex == 1727)
			continue;

		if (pItem[ItemCount].Mode == 0 || pItem[ItemCount].Mode == 2)
			continue;

		if (pItem[ItemCount].Delay >= 1)
		{
			pItem[ItemCount].Delay--;
			continue;
		}

		if (pItem[ItemCount].Decay != -1)
		{
			int itemPosX = pItem[ItemCount].PosX;
			int itemPosY = pItem[ItemCount].PosY;

			BASE_ClearItem(&pItem[ItemCount].ITEM);

			pItemGrid[itemPosX][itemPosY] = 0;
			pItem[ItemCount].Mode = 0;

			MSG_DecayItem sm;
			memset(&sm, 0, sizeof(MSG_DecayItem));

			sm.Type = _MSG_DecayItem;
			sm.Size = sizeof(MSG_DecayItem);
			sm.ID = ESCENE_FIELD;

			sm.ItemID = ItemCount + 10000;

			GridMulticast(itemPosX, itemPosY, (MSG_STANDARD*)&sm, 0);
		}
	}
}

int  CombineTreasureMap(int conn)
{
	for (int i = 0; i < MAX_CARRY; i++)
	{
		if (pMob[conn].MOB.Carry[i].sIndex != 788)
			continue;

		if (i + 1 >= MAX_CARRY)
			continue;

		if (pMob[conn].MOB.Carry[i + 1].sIndex != 789)
			continue;

		if (i + 9 >= MAX_CARRY)
			continue;

		if (pMob[conn].MOB.Carry[i + 9].sIndex != 790)
			continue;

		if (i + 10 >= MAX_CARRY)
			continue;

		if (pMob[conn].MOB.Carry[i + 10].sIndex != 791)
			continue;

		if (i + 18 >= MAX_CARRY)
			continue;

		if (pMob[conn].MOB.Carry[i + 18].sIndex != 792)
			continue;

		if (i + 19 >= MAX_CARRY)
			continue;

		if (pMob[conn].MOB.Carry[i + 19].sIndex != 793)
			continue;

		MSG_MessageDBRecord sm;
		memset(&sm, 0, sizeof(MSG_MessageDBRecord));

		sm.Type = _MSG_MessageDBRecord;
		sm.ID = 0;

		sm.Size = sizeof(MSG_MessageDBRecord);

		sprintf_s(sm.Record, "ETC treasure_map %d %s %s", ServerIndex, pUser[conn].AccountName, pMob[conn].MOB.MobName);

		DBServerSocket.SendOneMessage((char*)&sm, sizeof(MSG_MessageDBRecord));

		if (i >= MAX_CARRY)
			continue;

		pMob[conn].MOB.Carry[i].sIndex = 0;
		SendItem(conn, ITEM_PLACE_CARRY, i, &pMob[conn].MOB.Carry[i]);

		if (i + 1 >= MAX_CARRY)
			continue;

		pMob[conn].MOB.Carry[i + 1].sIndex = 0;
		SendItem(conn, ITEM_PLACE_CARRY, i + 1, &pMob[conn].MOB.Carry[i + 1]);

		if (i + 9 >= MAX_CARRY)
			continue;

		pMob[conn].MOB.Carry[i + 9].sIndex = 0;
		SendItem(conn, ITEM_PLACE_CARRY, i + 9, &pMob[conn].MOB.Carry[i + 9]);

		if (i + 10 >= MAX_CARRY)
			continue;

		pMob[conn].MOB.Carry[i + 10].sIndex = 0;
		SendItem(conn, ITEM_PLACE_CARRY, i + 10, &pMob[conn].MOB.Carry[i + 10]);

		if (i + 18 >= MAX_CARRY)
			continue;

		pMob[conn].MOB.Carry[i + 18].sIndex = 0;
		SendItem(conn, ITEM_PLACE_CARRY, i + 18, &pMob[conn].MOB.Carry[i + 18]);

		if (i + 19 >= MAX_CARRY)
			continue;

		pMob[conn].MOB.Carry[i + 19].sIndex = 0;
		SendItem(conn, ITEM_PLACE_CARRY, i + 19, &pMob[conn].MOB.Carry[i + 19]);

		SendClientMessage(conn, g_pMessageStringTable[_NN_Treasure_Map]);

		return TRUE;
	}

	int itemCount = 0;

	for (int i = 0; i < MAX_CARRY; i++)
	{
		if (pMob[conn].MOB.Carry[i].sIndex >= 788 && pMob[conn].MOB.Carry[i].sIndex <= 793)
		{
			pMob[conn].MOB.Carry[i].sIndex = 485;

			SendItem(conn, ITEM_PLACE_CARRY, i, &pMob[conn].MOB.Carry[i]);

			itemCount++;
		}
	}

	if (itemCount <= 0)
		return 0;

	SendClientMessage(conn, g_pMessageStringTable[_NN_Congratulations]);
	return TRUE;
}

void Combine(int conn, int item, int PrizeItem)
{
	int founditem = 0;

	if (conn < 0 || conn >= MAX_USER)
		return;

	for (int i = 0; i < MAX_CARRY; i++)
	{
		int index = pMob[conn].MOB.Carry[i].sIndex;

		if (index == item)
			founditem += pMob[conn].MOB.Carry[i].stEffect[0].cEffect == 61 ? pMob[conn].MOB.Carry[i].stEffect[0].cValue : 1;

		if (founditem >= 10)
			break;
	}

	if (founditem < 10)
		return;

	int clearitem = 0;

	for (int i = 0; i < MAX_CARRY; i++)
	{
		int index = pMob[conn].MOB.Carry[i].sIndex;

		if (index != item)
			continue;

		if (clearitem >= founditem)
			break;

		clearitem += pMob[conn].MOB.Carry[i].stEffect[0].cEffect == 61 ? pMob[conn].MOB.Carry[i].stEffect[0].cValue : 1;

		if (pMob[conn].MOB.Carry[i].stEffect[0].cEffect == 61 && pMob[conn].MOB.Carry[i].stEffect[0].cValue > 10)
			pMob[conn].MOB.Carry[i].stEffect[0].cValue -= 10;

		else
			BASE_ClearItem(&pMob[conn].MOB.Carry[i]);


		if (clearitem < 10)
			continue;
	}

	STRUCT_ITEM Prize;

	Prize.sIndex = PrizeItem;

	Prize.stEffect[0].cEffect = 59;
	Prize.stEffect[0].cValue = rand() % 100;

	Prize.stEffect[1].cEffect = 59;
	Prize.stEffect[1].cValue = rand() % 100;

	Prize.stEffect[2].cEffect = 59;
	Prize.stEffect[2].cValue = rand() % 50 + 50;

	int i = 0;

	for (i = 0; i < MAX_CARRY; i++)
	{
		int error = -1;

		//if (BASE_CanCarry(&Prize, pMob[conn].MOB.Carry, i % 9, i / 9, &error) == 1)
		//	break;

		if (pMob[conn].MOB.Carry[i].sIndex == 0)
			break;
	}

	if (i >= 0 && i < MAX_CARRY)
	{
		*(int*)&pMob[conn].MOB.Carry[i] = *(int*)&Prize;
		*(int*)((int)&pMob[conn].MOB.Carry[i] + 4) = *(int*)((int)&Prize + 4);
	}

	else
		CreateItem(pMob[conn].TargetX, pMob[conn].TargetY, &Prize, rand() % 4, 1);
}

int RemoveItem(int a_iMob, int a_iObject, int a_iCount)
{
	if (a_iCount < TRUE) a_iCount = TRUE;

	int FindCount = 0;

	int ProcSlot = -1;

	for (int i = 0; i < pMob[a_iMob].MaxCarry; i++)
	{
		if (pMob[a_iMob].MOB.Carry[i].sIndex == 0)
		{
			ProcSlot = i;

			break;
		}
	}

	if (ProcSlot == -1)
	{
		SendClientMessage(a_iMob, g_pMessageStringTable[_NN_You_Have_No_Space_To_Trade]);

		return FALSE;
	}

	for (int i = 0; i < pMob[a_iMob].MaxCarry; i++)
	{
		if (pMob[a_iMob].MOB.Carry[i].sIndex != a_iObject) continue;

		int byCount = BASE_GetItemAmount(&pMob[a_iMob].MOB.Carry[i]);

		if (byCount == FALSE) byCount = TRUE;

		FindCount += byCount;
	}

	if (FindCount < a_iCount) return FALSE; int RemoveCount = a_iCount;

	for (int i = 0; i < pMob[a_iMob].MaxCarry && RemoveCount > FALSE; i++)
	{
		if (pMob[a_iMob].MOB.Carry[i].sIndex != a_iObject) continue;

		int byCount = BASE_GetItemAmount(&pMob[a_iMob].MOB.Carry[i]);

		if (byCount == FALSE) byCount = TRUE;

		if (byCount > RemoveCount)
		{
			byCount -= RemoveCount;

			BASE_SetItemAmount(&pMob[a_iMob].MOB.Carry[i], byCount); SendItem(a_iMob, ITEM_PLACE_CARRY, i, &pMob[a_iMob].MOB.Carry[i]);

			return TRUE;
		}

		RemoveCount -= byCount;

		memset(&pMob[a_iMob].MOB.Carry[i], 0, sizeof(STRUCT_ITEM)); SendItem(a_iMob, ITEM_PLACE_CARRY, i, &pMob[a_iMob].MOB.Carry[i]);
	}

	return TRUE;
}

int ApplyHp(int conn)
{
	int retnValue = FALSE;

	if (pUser[conn].ReqHp > pMob[conn].MOB.CurrentScore.MaxHp)
		pUser[conn].ReqHp = pMob[conn].MOB.CurrentScore.MaxHp;

	int hp = pMob[conn].MOB.CurrentScore.Hp;
	int reqhp = pUser[conn].ReqHp;

	if (reqhp > hp)
	{
		int hpdif = reqhp - hp;
		if (reqhp - hp > 2000)
			hpdif = 2000;

		hp += hpdif;

		if (hp > 2000000000)
			hp = 2000000000;

		pMob[conn].MOB.CurrentScore.Hp = hp;

		if (pMob[conn].MOB.CurrentScore.Hp > reqhp)
			pMob[conn].MOB.CurrentScore.Hp = reqhp;

		retnValue = TRUE;
	}
	else
		retnValue = FALSE;

	return retnValue;
}

int ApplyMp(int conn)
{
	int retnValue = FALSE;

	if (pUser[conn].ReqMp > pMob[conn].MOB.CurrentScore.MaxMp)
		pUser[conn].ReqMp = pMob[conn].MOB.CurrentScore.MaxMp;

	int mp = pMob[conn].MOB.CurrentScore.Mp;
	int reqmp = pUser[conn].ReqMp;

	if (reqmp > mp)
	{
		int mpdif = reqmp - mp;
		if (reqmp - mp > 2000)
			mpdif = 2000;

		mp += mpdif;

		if (mp > 2000000000)
			mp = 2000000000;

		pMob[conn].MOB.CurrentScore.Mp = mp;

		if (pMob[conn].MOB.CurrentScore.Mp > reqmp)
			pMob[conn].MOB.CurrentScore.Mp = reqmp;

		retnValue = TRUE;
	}
	else
		retnValue = FALSE;

	return retnValue;
}

void SetReqHp(int conn)
{
	if (conn <= 0 || conn >= MAX_USER)
		return;

	if (pUser[conn].ReqHp < 0)
		pUser[conn].ReqHp = 0;

	if (pMob[conn].MOB.CurrentScore.Hp > pMob[conn].MOB.CurrentScore.MaxHp)
		pMob[conn].MOB.CurrentScore.Hp = pMob[conn].MOB.CurrentScore.MaxHp;

	if (pUser[conn].ReqHp < pMob[conn].MOB.CurrentScore.Hp)
		pUser[conn].ReqHp = pMob[conn].MOB.CurrentScore.Hp;
}

void SetReqMp(int conn)
{
	if (conn <= 0 || conn >= MAX_USER)
		return;

	if (pUser[conn].ReqMp < 0)
		pUser[conn].ReqMp = 0;

	if (pMob[conn].MOB.CurrentScore.Mp > pMob[conn].MOB.CurrentScore.MaxMp)
		pMob[conn].MOB.CurrentScore.Mp = pMob[conn].MOB.CurrentScore.MaxMp;

	if (pUser[conn].ReqMp < pMob[conn].MOB.CurrentScore.Mp)
		pUser[conn].ReqMp = pMob[conn].MOB.CurrentScore.Mp;
}

void ClearMapa(int x, int y)
{
	for (int i = 0; i < MAX_USER; i++)
	{
		if (pUser[i].Mode != USER_PLAY)
			continue;

		if (pMob[i].Mode == MOB_EMPTY)
			continue;

		if ((pMob[i].TargetX / 128) != x || (pMob[i].TargetY / 128) != y)
			continue;

		if (pMob[i].MOB.CurrentScore.Hp == 0)
		{
			pMob[i].MOB.CurrentScore.Hp = 2;

			pUser[i].NumError = 0;

			SendScore(i);
			SendSetHpMp(i);
		}

		DoRecall(i);
	}
}

void DeleteMobMapa(int x, int y)
{
	for (int i = MAX_USER; i < MAX_MOB; i++)
	{
		if (pMob[i].Mode == USER_EMPTY)
			continue;

		if ((pMob[i].TargetX / 128) != x || (pMob[i].TargetY / 128) != y)
			continue;

		DeleteMob(i, 1);
	}
}

// evento txt por txt PINHEIRO
void ReadEvent(void) {
	FILE* fp = NULL;

	fp = fopen("Event.txt", "rt");

	if (fp == NULL)
	{
		MessageBox(hWndMain, "no Event.txt", "Error", MB_OK | MB_SYSTEMMODAL);

		return;
	}

	int Linha = 1;
	int Item = 1;

	while (1)
	{
		char tmp[256];
		char* ret = fgets(tmp, 256, fp);

		if (ret == NULL)
			break;

		int ItemID = 0;
		int ItemQt = 0;


		sscanf(tmp, "%d %d", &ItemID, &ItemQt);

		if (Linha >= 2 && Linha <= 5) {
			EvItemId[1][Item] = ItemID;
			EvItemQt[1][Item] = ItemQt;
		}
		if (Linha >= 7 && Linha <= 10) {
			EvItemId[2][Item] = ItemID;
			EvItemQt[2][Item] = ItemQt;
		}
		if (Linha >= 12 && Linha <= 15) {
			EvItemId[3][Item] = ItemID;
			EvItemQt[3][Item] = ItemQt;
		}
		if (Linha >= 17 && Linha <= 20) {
			EvItemId[4][Item] = ItemID;
			EvItemQt[4][Item] = ItemQt;
		}

		Item++;
		Linha++;
		if (Item == 5)
			Item = 1;
	}
	fclose(fp);
}

void ReadEvent2(void) {
	FILE* fp = NULL;

	fp = fopen("Event2.txt", "rt");

	if (fp == NULL)
	{
		MessageBox(hWndMain, "no Event2.txt", "Error", MB_OK | MB_SYSTEMMODAL);

		return;
	}

	int Linha = 1;
	int Item = 1;

	while (1)
	{
		char tmp[256];
		char* ret = fgets(tmp, 256, fp);

		if (ret == NULL)
			break;

		int ItemID = 0;
		int ItemQt = 0;


		sscanf(tmp, "%d %d", &ItemID, &ItemQt);

		if (Linha >= 2 && Linha <= 5) {
			EvItemId2[1][Item] = ItemID;
			EvItemQt2[1][Item] = ItemQt;
		}
		if (Linha >= 7 && Linha <= 10) {
			EvItemId2[2][Item] = ItemID;
			EvItemQt2[2][Item] = ItemQt;
		}
		if (Linha >= 12 && Linha <= 15) {
			EvItemId2[3][Item] = ItemID;
			EvItemQt2[3][Item] = ItemQt;
		}
		if (Linha >= 17 && Linha <= 20) {
			EvItemId2[4][Item] = ItemID;
			EvItemQt2[4][Item] = ItemQt;
		}

		Item++;
		Linha++;
		if (Item == 5)
			Item = 1;
	}
	fclose(fp);
}
void ReadGuildPoints(void) {
	FILE* fp = NULL;

	fp = fopen("GuildPoints.txt", "rt");

	if (fp == NULL)
	{
		MessageBox(hWndMain, "no GuildPoints.txt", "Error", MB_OK | MB_SYSTEMMODAL);

		return;
	}

	while (1)
	{
		char tmp[256];
		char* ret = fgets(tmp, 256, fp);

		if (ret == NULL)
			break;

		int points = 0;
		int Id = 0;

		sscanf(tmp, "%d %d", &Id, &points);

		GuildPoints[Id][1] = points;
	}
	fclose(fp);
}
void ReadGItens(void) {
	FILE* fp = NULL;

	fp = fopen("GuildItens.txt", "rt");

	if (fp == NULL)
	{
		MessageBox(hWndMain, "no GuildItens.txt", "Error", MB_OK | MB_SYSTEMMODAL);

		return;
	}

	int Item = 0;

	while (1)
	{
		char tmp[256];
		char* ret = fgets(tmp, 256, fp);

		if (ret == NULL)
			break;
		
		int points = 0;
		int Id = 0;

		sscanf(tmp, "%d %d", &Id, &points);

		GShopItens[Item][0] = Id;
		GShopItens[Item][1] = points;
		Item++;
	}
	fclose(fp);
}

void SaveGuildPoints(void) {
	FILE* fp = NULL;

	fp = fopen("GuildPoints.txt", "w+");

	for (int k = 0; k < 100; k++) {
		if (GuildPoints[k][1] == 0)
			continue;

		if (GuildPoints[k][1] > 0)
		{
			fprintf(fp, "%d %d \n", k, GuildPoints[k][1]);
		}

	}
	fclose(fp);
}

void ReadMarket(void) {
	FILE* fp = NULL;

	fp = fopen("Market.txt", "rt");

	if (fp == NULL)
	{
		MessageBox(hWndMain, "no Market.txt", "Error", MB_OK | MB_SYSTEMMODAL);

		return;
	}

	char tmp[4096];
	char* ret = fgets(tmp, 4096, fp);

	if (ret == NULL)
		return;
			
	sscanf(tmp, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", &pOriRest, &pLacRest, &pOriPounder, &pLacPounder, &pSabio, &pDiamante, &pEsmeralda, &pCoral, &pGarnet, &pBarraDn, &pBarraMg, &pBarraAc, &pBarraCr, &pClasseD, &pClasseE, &pLuz, &pUnk, &pUnk2, &pUnk3, &pUnk4);

	fclose(fp);
}

void SaveMarket(void) {
	FILE* fp = NULL;

	fp = fopen("Market.txt", "w+");
	char String[4096];

	sprintf_s(String, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", pOriRest, pLacRest, pOriPounder, pLacPounder, pSabio, pDiamante, pEsmeralda, pCoral, pGarnet, pBarraDn, pBarraMg, pBarraAc, pBarraCr, pClasseD, pClasseE, pLuz, pUnk, pUnk2, pUnk3, pUnk4);

	fprintf(fp, "%s\n", String);

	fclose(fp);
}

void ReadLevelItemConfig(void)
{
	FILE* fp = NULL;

	fp = fopen("LevelItem.txt", "rt");

	if (fp == NULL)
	{
		MessageBox(hWndMain, "no LevelItem.txt", "Error", MB_OK | MB_SYSTEMMODAL);

		return;
	}

	memset(&LevelItem, 0, sizeof(LevelItem));

	while (1)
	{
		char tmp[256];
		char* ret = fgets(tmp, 256, fp);

		if (ret == NULL)
			break;

		int cls = 0;
		int type = 0;
		int level = 0;
		STRUCT_ITEM Item;
		memset(&Item, 0, sizeof(STRUCT_ITEM));

		int ival1 = 0, ival2 = 0, ival3 = 0;
		int ival4 = 0, ival5 = 0, ival6 = 0, ival7 = 0, id = 0;

		//sscanf(tmp, "%d %d %d %d %d %d %d %d %d %d", &cls, &type, &level, &ival1, &ival2, &ival3, &ival4, &ival5, &ival6, &ival7);
		sscanf(tmp, "%d %d %d %d %d %d %d %d %d %d", &id, &level, &cls, &type, &ival1, &ival2, &ival3, &ival4, &ival5, &ival6, &ival7);

		Item.sIndex = ival1;
		Item.stEffect[0].cEffect = ival2;
		Item.stEffect[0].cValue = ival3;
		Item.stEffect[1].cEffect = ival4;
		Item.stEffect[1].cValue = ival5;
		Item.stEffect[2].cEffect = ival6;
		Item.stEffect[2].cValue = ival7;

		if (cls == 4 && type != 4)//Item para todas as classes mais n�o para todas build
		{
			LevelItem[0][type][level] = Item;
			LevelItem[1][type][level] = Item;
			LevelItem[2][type][level] = Item;
			LevelItem[3][type][level] = Item;
		}

		else if (cls == 4 && type == 4)//Item para todas as classes e todas as build
		{
			for (int j = 0; j < 4; j++)
			{
				for (int k = 0; k < 4; k++)
					LevelItem[j][k][level] = Item;
			}

		}

		else if (type == 4)//Item para todas as build
		{
			LevelItem[cls][0][level] = Item;
			LevelItem[cls][1][level] = Item;
			LevelItem[cls][2][level] = Item;
			LevelItem[cls][3][level] = Item;
		}

		else
			LevelItem[cls][type][level] = Item;
	}

	fclose(fp);
}

void DoItemLevel(int conn)
{
	int type = 0;

	if (pMob[conn].MOB.BaseScore.Str > pMob[conn].MOB.BaseScore.Int && pMob[conn].MOB.BaseScore.Str > pMob[conn].MOB.BaseScore.Dex && pMob[conn].MOB.BaseScore.Str > pMob[conn].MOB.BaseScore.Con)
		type = 0;

	else if (pMob[conn].MOB.BaseScore.Int > pMob[conn].MOB.BaseScore.Str && pMob[conn].MOB.BaseScore.Int > pMob[conn].MOB.BaseScore.Dex && pMob[conn].MOB.BaseScore.Int > pMob[conn].MOB.BaseScore.Con)
		type = 1;

	else if (pMob[conn].MOB.BaseScore.Dex > pMob[conn].MOB.BaseScore.Str && pMob[conn].MOB.BaseScore.Dex > pMob[conn].MOB.BaseScore.Int && pMob[conn].MOB.BaseScore.Dex > pMob[conn].MOB.BaseScore.Con)
		type = 2;

	else
		type = 3;

	if (pMob[conn].MOB.BaseScore.Str > pMob[conn].MOB.BaseScore.Int && pMob[conn].MOB.BaseScore.Str > pMob[conn].MOB.BaseScore.Dex && pMob[conn].MOB.BaseScore.Str > pMob[conn].MOB.BaseScore.Con)
		type = 0;

	else if (pMob[conn].MOB.BaseScore.Int > pMob[conn].MOB.BaseScore.Str && pMob[conn].MOB.BaseScore.Int > pMob[conn].MOB.BaseScore.Dex && pMob[conn].MOB.BaseScore.Int > pMob[conn].MOB.BaseScore.Con)
		type = 1;

	else if (pMob[conn].MOB.BaseScore.Dex > pMob[conn].MOB.BaseScore.Str && pMob[conn].MOB.BaseScore.Dex > pMob[conn].MOB.BaseScore.Int && pMob[conn].MOB.BaseScore.Dex > pMob[conn].MOB.BaseScore.Con)
		type = 2;

	else
		type = 3;

	if (LevelItem[pMob[conn].MOB.Class][type][pMob[conn].MOB.BaseScore.Level].sIndex != 0)
	{
		for (int i = 0; i < MAX_CARGO - 2; i++)
		{
			int retsour = pUser[conn].Cargo[i].sIndex;

			if (retsour != 0)
				continue;

			pUser[conn].Cargo[i] = LevelItem[pMob[conn].MOB.Class][type][pMob[conn].MOB.BaseScore.Level];

			SendItem(conn, ITEM_PLACE_CARGO, i, &LevelItem[pMob[conn].MOB.Class][type][pMob[conn].MOB.BaseScore.Level]);

			char cMsg[128];

			sprintf_s(cMsg, "%s [%s]", g_pMessageStringTable[_NN_Item_Arrived], g_pItemList[LevelItem[pMob[conn].MOB.Class][type][pMob[conn].MOB.BaseScore.Level].sIndex].Name);

			SendClientMessage(conn, cMsg);

			char ItemCode[256];

			//sprintf(temp, "tra,%s %d", pUser[conn].AccountName, i);
			BASE_GetItemCode(&LevelItem[pMob[conn].MOB.Class][type][pMob[conn].MOB.BaseScore.Level], ItemCode);
			strcat(temp, ItemCode);
			//Log(temp, "_lvlreward_", pUser[conn].IP);

			if (pUser[conn].Mode == USER_SELCHAR)
				SaveUser(conn, 0);

			return;
		}
	}
}

/*void SetCircletSubGod(int conn)
{
	int type1 = pMob[conn].MOB.Equip[1].stEffect[0].cEffect = EF_SANC;
	int typefv1 = pMob[conn].MOB.Equip[1].stEffect[0].cValue;
	int type2 = pMob[conn].MOB.Equip[1].stEffect[1].cEffect = EF_SANC;
	int typefv2 = pMob[conn].MOB.Equip[1].stEffect[1].cValue;
	int type3 = pMob[conn].MOB.Equip[1].stEffect[2].cEffect = EF_SANC;
	int typefv3 = pMob[conn].MOB.Equip[1].stEffect[2].cValue;

	if (pMob[conn].extra.ClassMaster == SCELESTIAL && pMob[conn].MOB.Equip[1].sIndex >= 3500 && pMob[conn].MOB.Equip[1].sIndex <= 3507)
	{
		if (pMob[conn].MOB.BaseScore.Level == 119 && pMob[conn].extra.QuestInfo.Celestial.Add120 == 0) // N�vel 120
		{
			if (type1)
			{
				pMob[conn].MOB.Equip[1].stEffect[0].cValue = typefv1;
				pMob[conn].MOB.Equip[1].stEffect[1].cEffect = EF_AC;
				pMob[conn].MOB.Equip[1].stEffect[1].cValue = 30;
				pMob[conn].MOB.Equip[1].stEffect[2].cEffect = EF_HP;
				pMob[conn].MOB.Equip[1].stEffect[2].cValue = 40;

				pMob[conn].extra.QuestInfo.Celestial.Add120 = TRUE;

				SendItem(conn, ITEM_PLACE_EQUIP, 1, &pMob[conn].MOB.Equip[1]);
			}
			else if (type2)
			{
				pMob[conn].MOB.Equip[1].stEffect[0].cEffect = EF_AC;
				pMob[conn].MOB.Equip[1].stEffect[0].cValue = 30;
				pMob[conn].MOB.Equip[1].stEffect[1].cValue = typefv2;
				pMob[conn].MOB.Equip[1].stEffect[2].cEffect = EF_HP;
				pMob[conn].MOB.Equip[1].stEffect[2].cValue = 40;

				pMob[conn].extra.QuestInfo.Celestial.Add120 = TRUE;

				SendItem(conn, ITEM_PLACE_EQUIP, 1, &pMob[conn].MOB.Equip[1]);
			}
			else if (type3)
			{
				pMob[conn].MOB.Equip[1].stEffect[0].cEffect = EF_AC;
				pMob[conn].MOB.Equip[1].stEffect[0].cValue = 30;
				pMob[conn].MOB.Equip[1].stEffect[1].cEffect = EF_HP;
				pMob[conn].MOB.Equip[1].stEffect[1].cValue = 40;
				pMob[conn].MOB.Equip[1].stEffect[2].cValue = typefv3;

				pMob[conn].extra.QuestInfo.Celestial.Add120 = TRUE;

				SendItem(conn, ITEM_PLACE_EQUIP, 1, &pMob[conn].MOB.Equip[1]);
			}
		}
		if (pMob[conn].MOB.BaseScore.Level == 149 && pMob[conn].extra.QuestInfo.Celestial.Add150 == 0) // N�vel 150
		{
			if (type1)
			{
				pMob[conn].MOB.Equip[1].stEffect[0].cValue = typefv1;
				pMob[conn].MOB.Equip[1].stEffect[1].cEffect = EF_AC;
				pMob[conn].MOB.Equip[1].stEffect[1].cValue = 35;
				pMob[conn].MOB.Equip[1].stEffect[2].cEffect = EF_HP;
				pMob[conn].MOB.Equip[1].stEffect[2].cValue = 50;

				pMob[conn].extra.QuestInfo.Celestial.Add150 = TRUE;

				SendItem(conn, ITEM_PLACE_EQUIP, 1, &pMob[conn].MOB.Equip[1]);
			}
			else if (type2)
			{
				pMob[conn].MOB.Equip[1].stEffect[0].cEffect = EF_AC;
				pMob[conn].MOB.Equip[1].stEffect[0].cValue = 35;
				pMob[conn].MOB.Equip[1].stEffect[1].cValue = typefv2;
				pMob[conn].MOB.Equip[1].stEffect[2].cEffect = EF_HP;
				pMob[conn].MOB.Equip[1].stEffect[2].cValue = 50;

				pMob[conn].extra.QuestInfo.Celestial.Add150 = TRUE;

				SendItem(conn, ITEM_PLACE_EQUIP, 1, &pMob[conn].MOB.Equip[1]);
			}
			else if (type3)
			{
				pMob[conn].MOB.Equip[1].stEffect[0].cEffect = EF_AC;
				pMob[conn].MOB.Equip[1].stEffect[0].cValue = 35;
				pMob[conn].MOB.Equip[1].stEffect[1].cEffect = EF_HP;
				pMob[conn].MOB.Equip[1].stEffect[1].cValue = 50;
				pMob[conn].MOB.Equip[1].stEffect[2].cValue = typefv3;

				pMob[conn].extra.QuestInfo.Celestial.Add150 = TRUE;

				SendItem(conn, ITEM_PLACE_EQUIP, 1, &pMob[conn].MOB.Equip[1]);
			}
		}
		if (pMob[conn].MOB.BaseScore.Level == 179 && pMob[conn].extra.QuestInfo.Celestial.Add180 == 0) // N�vel 180
		{
			if (type1)
			{
				pMob[conn].MOB.Equip[1].stEffect[0].cValue = typefv1;
				pMob[conn].MOB.Equip[1].stEffect[1].cEffect = EF_AC;
				pMob[conn].MOB.Equip[1].stEffect[1].cValue = 45;
				pMob[conn].MOB.Equip[1].stEffect[2].cEffect = EF_HP;
				pMob[conn].MOB.Equip[1].stEffect[2].cValue = 60;

				pMob[conn].extra.QuestInfo.Celestial.Add180 = TRUE;

				SendItem(conn, ITEM_PLACE_EQUIP, 1, &pMob[conn].MOB.Equip[1]);
			}
			else if (type2)
			{
				pMob[conn].MOB.Equip[1].stEffect[0].cEffect = EF_AC;
				pMob[conn].MOB.Equip[1].stEffect[0].cValue = 45;
				pMob[conn].MOB.Equip[1].stEffect[1].cValue = typefv2;
				pMob[conn].MOB.Equip[1].stEffect[2].cEffect = EF_HP;
				pMob[conn].MOB.Equip[1].stEffect[2].cValue = 60;

				pMob[conn].extra.QuestInfo.Celestial.Add180 = TRUE;

				SendItem(conn, ITEM_PLACE_EQUIP, 1, &pMob[conn].MOB.Equip[1]);
			}
			else if (type3)
			{
				pMob[conn].MOB.Equip[1].stEffect[0].cEffect = EF_AC;
				pMob[conn].MOB.Equip[1].stEffect[0].cValue = 45;
				pMob[conn].MOB.Equip[1].stEffect[1].cEffect = EF_HP;
				pMob[conn].MOB.Equip[1].stEffect[1].cValue = 60;
				pMob[conn].MOB.Equip[1].stEffect[2].cValue = typefv3;

				pMob[conn].extra.QuestInfo.Celestial.Add180 = TRUE;

				SendItem(conn, ITEM_PLACE_EQUIP, 1, &pMob[conn].MOB.Equip[1]);
			}
		}
		if (pMob[conn].MOB.BaseScore.Level == 199 && pMob[conn].extra.QuestInfo.Celestial.Add200 == 0) // N�vel 200
		{
			if (type1)
			{
				pMob[conn].MOB.Equip[1].stEffect[0].cValue = typefv1;
				pMob[conn].MOB.Equip[1].stEffect[1].cEffect = EF_AC;
				pMob[conn].MOB.Equip[1].stEffect[1].cValue = 50;
				pMob[conn].MOB.Equip[1].stEffect[2].cEffect = EF_HP;
				pMob[conn].MOB.Equip[1].stEffect[2].cValue = 70;

				pMob[conn].extra.QuestInfo.Celestial.Add200 = TRUE;

				SendItem(conn, ITEM_PLACE_EQUIP, 1, &pMob[conn].MOB.Equip[1]);
			}
			else if (type2)
			{
				pMob[conn].MOB.Equip[1].stEffect[0].cEffect = EF_AC;
				pMob[conn].MOB.Equip[1].stEffect[0].cValue = 50;
				pMob[conn].MOB.Equip[1].stEffect[1].cValue = typefv2;
				pMob[conn].MOB.Equip[1].stEffect[2].cEffect = EF_HP;
				pMob[conn].MOB.Equip[1].stEffect[2].cValue = 70;

				pMob[conn].extra.QuestInfo.Celestial.Add200 = TRUE;

				SendItem(conn, ITEM_PLACE_EQUIP, 1, &pMob[conn].MOB.Equip[1]);
			}
			else if (type3)
			{
				pMob[conn].MOB.Equip[1].stEffect[0].cEffect = EF_AC;
				pMob[conn].MOB.Equip[1].stEffect[0].cValue = 50;
				pMob[conn].MOB.Equip[1].stEffect[1].cEffect = EF_HP;
				pMob[conn].MOB.Equip[1].stEffect[1].cValue = 70;
				pMob[conn].MOB.Equip[1].stEffect[2].cValue = typefv3;

				pMob[conn].extra.QuestInfo.Celestial.Add200 = TRUE;

				SendItem(conn, ITEM_PLACE_EQUIP, 1, &pMob[conn].MOB.Equip[1]);
			}
		}
	}
}*/

void SetCircletSubGod(int conn)
{
	if (pMob[conn].extra.ClassMaster == SCELESTIAL && pMob[conn].MOB.BaseScore.Level == 120 && pMob[conn].extra.QuestInfo.Celestial.Add120 == 0)
	{
		if (PutAddOnItem(&pMob[conn].MOB.Equip[1], EF_AC, EF_HP, 30, 40))
		{
			pMob[conn].extra.QuestInfo.Celestial.Add120 = 1;
			SendItem(conn, ITEM_PLACE_EQUIP, 1, &pMob[conn].MOB.Equip[1]);
		}
	}

	if (pMob[conn].extra.ClassMaster == SCELESTIAL && pMob[conn].MOB.BaseScore.Level == 150 && pMob[conn].extra.QuestInfo.Celestial.Add150 == 0)
	{
		if (PutAddOnItem(&pMob[conn].MOB.Equip[1], EF_AC, EF_HP, 35, 50))
		{
			pMob[conn].extra.QuestInfo.Celestial.Add150 = 1;
			SendItem(conn, ITEM_PLACE_EQUIP, 1, &pMob[conn].MOB.Equip[1]);
		}
	}

	if (pMob[conn].extra.ClassMaster == SCELESTIAL && pMob[conn].MOB.BaseScore.Level == 180 && pMob[conn].extra.QuestInfo.Celestial.Add180 == 0)
	{
		if (PutAddOnItem(&pMob[conn].MOB.Equip[1], EF_AC, EF_HP, 45, 60))
		{
			pMob[conn].extra.QuestInfo.Celestial.Add180 = 1;
			SendItem(conn, ITEM_PLACE_EQUIP, 1, &pMob[conn].MOB.Equip[1]);
		}
	}

	if (pMob[conn].extra.ClassMaster == SCELESTIAL && pMob[conn].MOB.BaseScore.Level == 199 && pMob[conn].extra.QuestInfo.Celestial.Add200 == 0)
	{
		if (PutAddOnItem(&pMob[conn].MOB.Equip[1], EF_AC, EF_HP, 50, 70))
		{
			pMob[conn].extra.QuestInfo.Celestial.Add200 = 1;
			SendItem(conn, ITEM_PLACE_EQUIP, 1, &pMob[conn].MOB.Equip[1]);
		}
	}

}

bool PutAddOnItem(STRUCT_ITEM *Item, UINT8 ef1, UINT8 ef2, UINT8 efv1, UINT8 efv2)
{
	if (Item->sIndex < 0 || Item->sIndex > 6500) // Id inv�lido
		return false;
	else if (ef1 && !efv1) // Diz que vai por add mas n�o tem o valor
		return false;
	else if (ef2 && !efv2) // '''''''''''''''''''''''''''''''''''''''
		return false;
	else if (!ef1 && efv1) // '''''''''''''''''''''''''''''''''''''''
		return false;
	else if (!ef2 && efv2) // '''''''''''''''''''''''''''''''''''''''
		return false;

	// Salva a sanc do item
	UINT8 Sanc = 0;

	Sanc = GetItemSanc(Item);

	// Zera os adds pr�vios do item
	memset(Item->stEffect, 0x0, 6);

	INT8 value = 0;

	if (Sanc)
	{
		value++;

		// P�e a sanc anterior do item nele novamente
		SetItemSanc(Item, Sanc);
	}
	// Seta os novos adicionais
	Item->stEffect[value].cEffect = ef1;
	Item->stEffect[value].cValue = efv1;

	Item->stEffect[value + 1].cEffect = ef2;
	Item->stEffect[value + 1].cValue = efv2;

	return true;
}

void SummonServer(int tx, int ty)
{
	int summons = 0;

	for (int i = 0; i < MAX_USER; i++)
	{
		if (pUser[i].Mode != USER_PLAY || pMob[i].Mode == USER_EMPTY)
			continue;

		DoGreatTeleport(i, tx, ty);
	}
}

void MobAttack(int attacker, MSG_Attack sm)
{
	int _rd = rand() % 100;

	if (sm.SkillIndex == 109)
	{
		if (_rd < 40)
			sm.SkillIndex = 110;

		else if (_rd < 80)
			sm.SkillIndex = 111;
	}

	for (int i = 0; i < MAX_TARGET; i++)
	{
		int skillbase = sm.SkillIndex;
		int Target = sm.Dam[i].TargetID;

		if (Target <= 0 || Target >= MAX_MOB)
			continue;

		if (pMob[Target].MOB.CurrentScore.Hp <= 0)
			continue;

		sm.FlagLocal = 0;

		Target = sm.Dam[i].TargetID;

		if (skillbase != 109)
			sm.Dam[i].Damage = 500 + rand() % 200;

		sm.SkillIndex = skillbase;

		int skill = sm.SkillIndex;

		if (skill >= 0 && skill < MAX_SKILLINDEX && sm.SkillParm == 0)
		{
			if (skill == 33)
				sm.Motion = 253;

			int kind = ((skill % MAX_SKILL / 8) + 1);

			if (kind >= 1 && kind <= 3)
			{
				int special = pMob[attacker].MOB.CurrentScore.Special[kind];

				int NeedUpdate = 0;

				if (SetAffect(Target, skill, 100, special) != FALSE)
					NeedUpdate = 1;

				if (SetTick(Target, skill, 100, special) != FALSE)
					NeedUpdate = 1;

				if (NeedUpdate)
					SendScore(Target);
			}
		}
		if (Target < MAX_USER && sm.Dam[i].Damage > 0)
		{
			int attackdex = pMob[attacker].MOB.CurrentScore.Dex / 5;

			if (pMob[attacker].MOB.LearnedSkill & 0x1000000)
				attackdex += 100;

			if (pMob[attacker].MOB.Rsv & 0x40)
				attackdex += 500;

			int parryretn = WGetParryRate(&pMob[Target].MOB, pMob[Target].Parry, attackdex, pMob[attacker].MOB.Rsv);

			if (sm.SkillIndex == 79 || sm.SkillIndex == 22)
				parryretn = 30 * parryretn / 100;

			int rd = rand() % 1000 + 1;

			if (rd < parryretn)
			{
				sm.Dam[i].Damage = -3;

				if ((pMob[Target].MOB.Rsv & 0x200) != 0 && rd < 100)
					sm.Dam[i].Damage = -4;
			}

			else if (pMob[attacker].MOB.Clan == 4)
				sm.Dam[i].Damage = (2 * sm.Dam[i].Damage) / 5;
		}

		int TargetLeader = pMob[Target].CurrentTarget;

		if (sm.Dam[i].Damage > 0)
		{
			if (TargetLeader <= MOB_EMPTY)
				TargetLeader = Target;

			SetBattle(TargetLeader, attacker);

			if (pMob[attacker].MOB.Clan != 4)
				SetBattle(attacker, TargetLeader);

			for (int z = 0; z < MAX_PARTY; z++)
			{
				int partyconn = pMob[TargetLeader].PartyList[z];
				if (partyconn <= MAX_USER)
					continue;

				if (pMob[partyconn].Mode == MOB_EMPTY || pMob[partyconn].MOB.CurrentScore.Hp <= 0)
				{
					if (pMob[partyconn].Mode != MOB_EMPTY)
					{
						pMob[partyconn].MOB.CurrentScore.Hp = 0;
						DeleteMob(partyconn, 1);
					}

					pMob[TargetLeader].PartyList[attacker] = MOB_EMPTY;
					continue;
				}

				SetBattle(partyconn, attacker);
				SetBattle(attacker, partyconn);
			}

			for (int z = 0; z < MAX_PARTY; z++)
			{
				int partyconn = pMob[TargetLeader].Evocations[z];
				if (partyconn <= MAX_USER)
					continue;

				if (pMob[partyconn].Mode == MOB_EMPTY || pMob[partyconn].MOB.CurrentScore.Hp <= 0)
				{
					if (pMob[partyconn].Mode != MOB_EMPTY)
					{
						pMob[partyconn].MOB.CurrentScore.Hp = 0;
						DeleteMob(partyconn, 1);
					}

					pMob[TargetLeader].Evocations[attacker] = MOB_EMPTY;
					continue;
				}

				SetBattle(partyconn, attacker);
				SetBattle(attacker, partyconn);
			}

			int Summoner = pMob[attacker].Summoner;

			if (pMob[attacker].MOB.Clan == 4 && Target >= MAX_USER && Summoner > 0 && Summoner < MAX_USER && pUser[Summoner].Mode == USER_PLAY)
			{
				int posX = pMob[Summoner].TargetX;
				int posY = pMob[Summoner].TargetY;
				int num = 46;
				int dam = 0;
				int exp = 0;
				int setDam = 0;

				if (pMob[attacker].TargetX > posX - num && pMob[attacker].TargetX < posX + num && pMob[attacker].TargetY > posY - num && pMob[attacker].TargetY < posY + num)
				{
					if (pMob[Target].MOB.CurrentScore.Hp < sm.Dam[i].Damage)
						setDam = pMob[Target].MOB.CurrentScore.Hp;
					else
						setDam = sm.Dam[i].Damage;

					dam = setDam;
					exp = (int)(pMob[Target].MOB.Exp * dam / pMob[Target].MOB.CurrentScore.MaxHp);

					if (pMob[Summoner].MOB.CurrentScore.Level == pMob[attacker].MOB.CurrentScore.Level)
					{
						exp = GetExpApply(pMob[attacker].extra, exp, pMob[attacker].MOB.CurrentScore.Level, pMob[Target].MOB.CurrentScore.Level);

						if (exp > 12000)
							exp = 12000;

						if (pMob[Target].MOB.Clan == 4)
							exp = 0;

						pMob[Summoner].MOB.Exp = pMob[Summoner].MOB.Exp + exp;
					}
				}
			}
		}

		if (sm.Dam[i].Damage > 0 || sm.Dam[i].Damage <= -5)
		{
			int DamageNow = sm.Dam[i].Damage;
			int damage = 0;
			int mountindex = pMob[Target].MOB.Equip[14].sIndex;

			if (Target < MAX_USER && mountindex >= 2360 && mountindex < 2390 && pMob[Target].MOB.Equip[14].stEffect[0].sValue > 0)
			{
				DamageNow = (3 * sm.Dam[i].Damage) / 4;
				damage = sm.Dam[i].Damage - DamageNow;

				if (DamageNow <= 0)
					DamageNow = 1;

				sm.Dam[i].Damage = DamageNow;
			}

			for (int c = 0; c < MAX_AFFECT; c++)
			{
				if (pMob[Target].Affect[c].Type == 18)
				{
					if (pMob[Target].MOB.CurrentScore.Mp > ((pMob[Target].MOB.CurrentScore.MaxMp / 100) * 10))
					{
						int mana = pMob[Target].MOB.CurrentScore.Mp - (DamageNow >> 1);

						if (mana < 0)
						{
							DamageNow -= mana;
							mana = 0;
						}

						pMob[Target].MOB.CurrentScore.Mp = mana;

						pUser[Target].ReqMp = pUser[Target].ReqMp - (DamageNow >> 1);
						SetReqMp(Target);

						DamageNow = ((DamageNow >> 1) + (DamageNow << 4)) / 80;
						sm.Dam[i].Damage = DamageNow;
					}
				}
			}

			if (pMob[Target].MOB.Equip[13].sIndex == 786)
			{
				int sanc = pMob[Target].MOB.Equip[13].stEffect[0].cValue;

				if (sanc < 2)
					sanc = 2;

				pMob[Target].MOB.CurrentScore.Hp = pMob[Target].MOB.CurrentScore.Hp - ((sm.Dam[i].Damage) / sanc);
			}
			else if (pMob[Target].MOB.Equip[13].sIndex == 1936)
			{
				int sanc = pMob[Target].MOB.Equip[13].stEffect[0].cValue;

				if (sanc < 2)
					sanc = 2;

				sanc *= 10;

				pMob[Target].MOB.CurrentScore.Hp = pMob[Target].MOB.CurrentScore.Hp - ((sm.Dam[i].Damage) / sanc);
			}
			else if (pMob[Target].MOB.Equip[13].sIndex == 1937)
			{
				int sanc = pMob[Target].MOB.Equip[13].stEffect[0].cValue;

				if (sanc < 2)
					sanc = 2;

				sanc *= 1000;

				pMob[Target].MOB.CurrentScore.Hp = pMob[Target].MOB.CurrentScore.Hp - ((sm.Dam[i].Damage) / sanc);
			}
			else
			{

				if (pMob[Target].MOB.CurrentScore.Hp < sm.Dam[i].Damage)
					pMob[Target].MOB.CurrentScore.Hp = 0;

				else
					pMob[Target].MOB.CurrentScore.Hp = pMob[Target].MOB.CurrentScore.Hp - sm.Dam[i].Damage;

			}

			if (Target > MAX_USER)
				SendScore(Target);

			if (Target > MAX_USER && pMob[Target].MOB.Clan == 4)
				LinkMountHp(Target);

			if (damage > 0)
				ProcessAdultMount(Target, damage);
		}

		GridMulticast(pMob[Target].TargetX, pMob[Target].TargetY, (MSG_STANDARD*)&sm, 0);

		if (Target > 0 && Target < MAX_USER)
		{
			if (pUser[Target].ReqHp < sm.Dam[i].Damage)
				pUser[Target].ReqHp = 0;

			else
				pUser[Target].ReqHp = pUser[Target].ReqHp - sm.Dam[i].Damage;

			if (sm.SkillIndex == 109)
			{
				pMob[Target].MOB.CurrentScore.Hp = 0;
				pUser[Target].ReqHp = 0;
			}

			SetReqHp(Target);
			SendSetHpMp(Target);
		}

		if (pMob[Target].MOB.CurrentScore.Hp <= 0)
		{
			pMob[Target].MOB.CurrentScore.Hp = 0;

			MobKilled(Target, attacker, 0, 0);
		}
	}
}

void StartChatLog()
{
	if (g_pChatLog && g_pChatLog.get()->m_pStream.get()->is_open()) {
		g_pChatLog.get()->m_pStream.get()->close();
		g_pChatLog.get()->m_pStream.get()->clear();
		g_pChatLog.get()->m_pStream.release();
	}

	if (g_pChatLog)
		g_pChatLog.release();

	g_pChatLog = std::make_unique<LogControl>();

	struct tm when;
	time_t now;
	time(&now);
	when = *localtime(&now);

	sprintf_s(temp, ".\\Logs\\chat_log\\TM_%02d_%02d_%04d_%02d_%02d_%02d.txt", when.tm_mday, when.tm_mon + 1, when.tm_year + 1900, when.tm_hour, when.tm_min, when.tm_sec);

	char tmg[256];
	sprintf_s(tmg, "chat logs started successfully");
	Log(tmg, "-system", 0);

	g_pChatLog.get()->Initialize(std::string(temp));

	LastChatLogDay = when.tm_mday;
}

void ChatLog(char* AccountName, char* MacAddress, unsigned int IPAddress, char* Message)
{
	char temp_str[64] = { 0, };

	if (IPAddress != 0) //for some reason the ip address isn't working properly...
	{
		sprintf_s(temp_str, "%d.%d.%d.%d",
			IPAddress & 0xFF,
			(IPAddress >> 8) & 0xFF,
			(IPAddress >> 16) & 0xFF,
			(IPAddress >> 24) & 0xFF);
	}
	else
		sprintf_s(temp_str, "NO_VALID_IP");

	if (g_pChatLog)
		g_pChatLog.get()->WriteLog(std::string(Message), std::string(MacAddress), std::string(temp_str), std::string(AccountName));
}

void Starthacklog()
{
	if (g_phackLog && g_phackLog.get()->m_pStream.get()->is_open()) {
		g_phackLog.get()->m_pStream.get()->close();
		g_phackLog.get()->m_pStream.get()->clear();
		g_phackLog.get()->m_pStream.release();
	}


	if (g_phackLog)
		g_phackLog.release();

	g_phackLog = std::make_unique<LogControl>();

	struct tm when;
	time_t now;
	time(&now);
	when = *localtime(&now);

	sprintf_s(temp, ".\\Logs\\hack_log\\TM_%02d_%02d_%04d_%02d_%02d_%02d.txt", when.tm_mday, when.tm_mon + 1, when.tm_year + 1900, when.tm_hour, when.tm_min, when.tm_sec);

	char tmg[256];
	sprintf_s(tmg, "chat logs started successfully");
	Log(tmg, "-system", 0);

	g_phackLog.get()->Initialize(std::string(temp));

	LasthackLogDay = when.tm_mday;
}

void HackLog(char* AccountName, char* MacAddress, unsigned int IPAddress, char* Message)
{
	char temp_str[64] = { 0, };

	if (IPAddress != 0) //for some reason the ip address isn't working properly...
	{
		//Vamo do jeito hard
		sprintf_s(temp_str, "%d.%d.%d.%d",
			IPAddress & 0xFF,
			(IPAddress >> 8) & 0xFF,
			(IPAddress >> 16) & 0xFF,
			(IPAddress >> 24) & 0xFF);
	}
	else
		sprintf_s(temp_str, "NO_VALID_IP");

	if (g_phackLog)
		g_phackLog.get()->WriteLog(std::string(Message), std::string(MacAddress), std::string(temp_str), std::string(AccountName));
}

void MobDropLogs()
{
	if (g_pMobdropLog && g_pMobdropLog.get()->m_pStream.get()->is_open()) {
		g_pMobdropLog.get()->m_pStream.get()->close();
		g_pMobdropLog.get()->m_pStream.get()->clear();
		g_pMobdropLog.get()->m_pStream.release();
	}

	if (g_pMobdropLog)
		g_pMobdropLog.release();

	g_pMobdropLog = std::make_unique<LogControl>();

	struct tm when;
	time_t now;
	time(&now);
	when = *localtime(&now);

	sprintf_s(temp, ".\\Logs\\Mobdrop\\TM_%02d_%02d_%04d_%02d_%02d_%02d.txt", when.tm_mday, when.tm_mon + 1, when.tm_year + 1900, when.tm_hour, when.tm_min, when.tm_sec);

	char tmg[256];
	sprintf_s(tmg, "chat logs started successfully");
	Log(tmg, "-system", 0);

	g_pMobdropLog.get()->Initialize(std::string(temp));

	fIMobDropLogFileDay = when.tm_mday;
}

void MobDropLog(char* AccountName, char* MacAddress, unsigned int IPAddress, char* Message)
{
	char temp_str[64] = { 0, };

	if (IPAddress != 0) //for some reason the ip address isn't working properly...
	{
		//Vamo do jeito hard
		sprintf_s(temp_str, "%d.%d.%d.%d",
			IPAddress & 0xFF,
			(IPAddress >> 8) & 0xFF,
			(IPAddress >> 16) & 0xFF,
			(IPAddress >> 24) & 0xFF);
	}
	else
		sprintf_s(temp_str, "NO_VALID_IP");

	if (g_pMobdropLog)
		g_pMobdropLog.get()->WriteLog(std::string(Message), std::string(MacAddress), std::string(temp_str), std::string(AccountName));
}

void CompositorLog()
{
	if (g_pCompositorLog && g_pCompositorLog.get()->m_pStream.get()->is_open()) {
		g_pCompositorLog.get()->m_pStream.get()->close();
		g_pCompositorLog.get()->m_pStream.get()->clear();
		g_pCompositorLog.get()->m_pStream.release();
	}

	if (g_pCompositorLog)
		g_pCompositorLog.release();

	g_pCompositorLog = std::make_unique<LogControl>();

	struct tm when;
	time_t now;
	time(&now);
	when = *localtime(&now);

	sprintf_s(temp, ".\\Logs\\Compositor_Logs\\TM_%02d_%02d_%04d_%02d_%02d_%02d.txt", when.tm_mday, when.tm_mon + 1, when.tm_year + 1900, when.tm_hour, when.tm_min, when.tm_sec);

	char tmg[256];
	sprintf_s(tmg, "chat logs started successfully");
	Log(tmg, "-system", 0);

	g_pCompositorLog.get()->Initialize(std::string(temp));

	LastCompositorLogsDay = when.tm_mday;
}

void Combinelogsitem(char* AccountName, char* MacAddress, unsigned int IPAddress, char* Message)
{
	char temp_str[64] = { 0, };

	if (IPAddress != 0) //for some reason the ip address isn't working properly...
	{
		//Vamo do jeito hard
		sprintf_s(temp_str, "%d.%d.%d.%d",
			IPAddress & 0xFF,
			(IPAddress >> 8) & 0xFF,
			(IPAddress >> 16) & 0xFF,
			(IPAddress >> 24) & 0xFF);
	}
	else
		sprintf_s(temp_str, "NO_VALID_IP");

	if (g_pCompositorLog)
		g_pCompositorLog.get()->WriteLog(std::string(Message), std::string(MacAddress), std::string(temp_str), std::string(AccountName));
}

void trade_item()
{
	if (g_pItradeLog && g_pItradeLog.get()->m_pStream.get()->is_open()) {
		g_pItradeLog.get()->m_pStream.get()->close();
		g_pItradeLog.get()->m_pStream.get()->clear();
		g_pItradeLog.get()->m_pStream.release();
	}

	if (g_pItradeLog)
		g_pItradeLog.release();

	g_pItradeLog = std::make_unique<LogControl>();

	struct tm when;
	time_t now;
	time(&now);
	when = *localtime(&now);

	sprintf_s(temp, ".\\Logs\\trade_item\\TM_%02d_%02d_%04d_%02d_%02d_%02d.txt", when.tm_mday, when.tm_mon + 1, when.tm_year + 1900, when.tm_hour, when.tm_min, when.tm_sec);

	char tmg[256];
	sprintf_s(tmg, "chat logs started successfully");
	Log(tmg, "-system", 0);

	g_pItradeLog.get()->Initialize(std::string(temp));

	trade_itemLogsFileDay = when.tm_mday;
}

void Tradelogs(char* AccountName, char* MacAddress, unsigned int IPAddress, char* Message)
{
	char temp_str[64] = { 0, };

	if (IPAddress != 0) //for some reason the ip address isn't working properly...
	{
		//Vamo do jeito hard
		sprintf_s(temp_str, "%d.%d.%d.%d",
			IPAddress & 0xFF,
			(IPAddress >> 8) & 0xFF,
			(IPAddress >> 16) & 0xFF,
			(IPAddress >> 24) & 0xFF);
	}
	else
		sprintf_s(temp_str, "NO_VALID_IP");

	if (g_pItradeLog)
		g_pItradeLog.get()->WriteLog(std::string(Message), std::string(MacAddress), std::string(temp_str), std::string(AccountName));
}

void StartItemLog()
{
	if (g_pItemLog && g_pItemLog.get()->m_pStream.get()->is_open()) {
		g_pItemLog.get()->m_pStream.get()->close();
		g_pItemLog.get()->m_pStream.get()->clear();
		g_pItemLog.get()->m_pStream.release();
	}

	if (g_pItemLog)
		g_pItemLog.release();

	g_pItemLog = std::make_unique<LogControl>();

	struct tm when;
	time_t now;
	time(&now);
	when = *localtime(&now);

	sprintf_s(temp, ".\\Logs\\item_log\\TM_%02d_%02d_%04d_%02d_%02d_%02d.txt", when.tm_mday, when.tm_mon + 1, when.tm_year + 1900, when.tm_hour, when.tm_min, when.tm_sec);

	char tmg[256];
	sprintf_s(tmg, "chat logs started successfully");
	Log(tmg, "-system", 0);

	g_pItemLog.get()->Initialize(std::string(temp));

	LastItemLogDay = when.tm_mday;
}

void ItemLog(char* AccountName, char* MacAddress, unsigned int IPAddress, char* Message)
{
	char temp_str[64] = { 0, };

	if (IPAddress != 0) //for some reason the ip address isn't working properly...
	{
		//Vamo do jeito hard
		sprintf_s(temp_str, "%d.%d.%d.%d",
			IPAddress & 0xFF,
			(IPAddress >> 8) & 0xFF,
			(IPAddress >> 16) & 0xFF,
			(IPAddress >> 24) & 0xFF);
	}
	else
		sprintf_s(temp_str, "NO_VALID_IP");

	if (g_pItemLog)
		g_pItemLog.get()->WriteLog(std::string(Message), std::string(MacAddress), std::string(temp_str), std::string(AccountName));
}

//void ChatLog(char* str1, char* str2, char* str3)
//{
//	struct tm when;
//	time_t now;
//	time(&now);
//	when = *localtime(&now);
//
//	char LogTemp[1024];
//
//	sprintf(LogTemp, "%02d.%02d.%04d.%02d.%02d.%02d IP-MAC: %s", when.tm_mday, when.tm_mon + 1, when.tm_year + 1900, when.tm_hour, when.tm_min, when.tm_sec, str3);
//
//	sprintf(LogTemp, "%s %s %s \n", LogTemp, str2, str1);
//
//	if (fChatLogFile)
//		fprintf(fChatLogFile, LogTemp);
//}
//
//void StartItemLog()
//{
//	if (fItemLogFile != NULL)
//		fclose(fItemLogFile);
//
//	struct tm when;
//	time_t now;
//	time(&now);
//	when = *localtime(&now);
//
//	sprintf(temp, ".\\Logs\\item_log\\TM_%02d_%02d_%04d_%02d_%02d_%02d.txt", when.tm_mday, when.tm_mon + 1, when.tm_year + 1900, when.tm_hour, when.tm_min, when.tm_sec);
//
//	char tmg[256];
//	sprintf(tmg, "item logs started successfully");
//	Log(tmg, "-system", 0);
//
//	fItemLogFile = fopen(temp, "wt");
//
//	LastItemLogDay = when.tm_mday;
//}
//
//void trade_item() // 23/02
//{
//	if (trade_itemLogsFile != NULL)
//		fclose(trade_itemLogsFile);
//
//	struct tm when;
//	time_t now;
//	time(&now);
//	when = *localtime(&now);
//
//	sprintf(temp, ".\\Logs\\trade_item\\TM_%02d_%02d_%04d_%02d_%02d_%02d.txt", when.tm_mday, when.tm_mon + 1, when.tm_year + 1900, when.tm_hour, when.tm_min, when.tm_sec);
//
//	char tmg[256];
//	sprintf(tmg, "Trades logs started successfully");
//	Log(tmg, "-system", 0);
//
//	trade_itemLogsFile = fopen(temp, "wt");
//
//	trade_itemLogsFileDay = when.tm_mday;
//}
//
//void MobDropLogs() // 23/02
//{
//	if (fIMobDropLogLogsFile != NULL)
//		fclose(fIMobDropLogLogsFile);
//
//	struct tm when;
//	time_t now;
//	time(&now);
//	when = *localtime(&now);
//
//	sprintf(temp, ".\\Logs\\Mobdrop\\TM_%02d_%02d_%04d_%02d_%02d_%02d.txt", when.tm_mday, when.tm_mon + 1, when.tm_year + 1900, when.tm_hour, when.tm_min, when.tm_sec);
//
//	char tmg[256];
//	sprintf(tmg, "MobDrops logs started successfully");
//	Log(tmg, "-system", 0);
//
//	fIMobDropLogLogsFile = fopen(temp, "wt");
//
//	fIMobDropLogFileDay = when.tm_mday;
//}
//
//void MobDropLog(char* str1, char* str2, char* str3) //23/02
//{
//	struct tm when;
//	time_t now;
//	time(&now);
//	when = *localtime(&now);
//
//	char LogTemp[1024];
//
//	sprintf(LogTemp, "%02d.%02d.%04d.%02d.%02d.%02d IP-MAC : %s", when.tm_mday, when.tm_mon + 1, when.tm_year + 1900, when.tm_hour, when.tm_min, when.tm_sec, str3);
//
//	sprintf(LogTemp, "%s %s %s \n", LogTemp, str2, str1);
//
//	if (fIMobDropLogLogsFile)
//		fprintf(fIMobDropLogLogsFile, LogTemp);
//}
//
//void CompositorLog() // 23/02
//{
//	if (fICompositorLogsFile != NULL)
//		fclose(fICompositorLogsFile);
//
//	struct tm when;
//	time_t now;
//	time(&now);
//	when = *localtime(&now);
//
//	sprintf(temp, ".\\Logs\\Compositor_Logs\\TM_%02d_%02d_%04d_%02d_%02d_%02d.txt", when.tm_mday, when.tm_mon + 1, when.tm_year + 1900, when.tm_hour, when.tm_min, when.tm_sec);
//
//	char tmg[256];
//	sprintf(tmg, "Compositor logs started successfully");
//	Log(tmg, "-system", 0);
//
//	fICompositorLogsFile = fopen(temp, "wt");
//
//	LastCompositorLogsDay = when.tm_mday;
//}
//
//void Combinelogsitem(char* str1, char* str2, char* str3) //23/02
//{
//	struct tm when;
//	time_t now;
//	time(&now);
//	when = *localtime(&now);
//
//	char LogTemp[1024];
//
//	sprintf(LogTemp, "%02d.%02d.%04d.%02d.%02d.%02d IP-MAC : %s", when.tm_mday, when.tm_mon + 1, when.tm_year + 1900, when.tm_hour, when.tm_min, when.tm_sec, str3);
//
//	sprintf(LogTemp, "%s %s %s \n", LogTemp, str2, str1);
//
//	if (fICompositorLogsFile)
//		fprintf(fICompositorLogsFile, LogTemp);
//}
//
//void Tradelogs(char* str1, char* str2, char* str3)
//{
//	struct tm when;
//	time_t now;
//	time(&now);
//	when = *localtime(&now);
//
//	char LogTemp[1024];
//
//	sprintf(LogTemp, "%02d.%02d.%04d.%02d.%02d.%02d IP-MAC : %s", when.tm_mday, when.tm_mon + 1, when.tm_year + 1900, when.tm_hour, when.tm_min, when.tm_sec, str3);
//
//	sprintf(LogTemp, "%s %s %s \n", LogTemp, str2, str1);
//
//	if (trade_itemLogsFile)
//		fprintf(trade_itemLogsFile, LogTemp);
//}
//
//void ItemLog(char* str1, char* str2, char* str3)
//{
//	struct tm when;
//	time_t now;
//	time(&now);
//	when = *localtime(&now);
//
//	char LogTemp[1024];
//
//	sprintf(LogTemp, "%02d.%02d.%04d.%02d.%02d.%02d IP-MAC : %s", when.tm_mday, when.tm_mon + 1, when.tm_year + 1900, when.tm_hour, when.tm_min, when.tm_sec, str3);
//
//	sprintf(LogTemp, "%s %s %s \n", LogTemp, str2, str1);
//
//	if (fItemLogFile)
//		fprintf(fItemLogFile, LogTemp);
//}

int  ParseMobMercString(int Num, char *str)
{
	char str1[128];
	str1[0] = 0;

	char str2[128];
	str2[0] = 0;

	char str3[128];
	str3[0] = 0;

	int  value = 0;
	int secondvalue = 0;

	sscanf(str, "%s %s %s", str1, str2, str3);

	if (str[0] == 47)
		return FALSE;

	if (str[0] == 0)
		return FALSE;

	STRUCT_ITEM Item;
	memset(&Item, 0, sizeof(STRUCT_ITEM));

	char item_str1[256];
	char item_str2[256];
	char item_str3[256];
	char item_str4[256];
	char item_str5[256];
	char item_str6[256];
	char item_str7[256];
	char item_str8[256];

	int item_value[8] = { 0, 0, 0, 0, 0, 0, 0 , 0 };

	sscanf(str2, "%s %s %s %s %s %s %s - %s", item_str1, item_str2, item_str3, item_str4, item_str5, item_str6, item_str7, item_str8);
	item_value[0] = atoi(item_str1);
	item_value[1] = atoi(item_str2);
	item_value[2] = atoi(item_str3);
	item_value[3] = atoi(item_str4);
	item_value[4] = atoi(item_str5);
	item_value[5] = atoi(item_str6);
	item_value[6] = atoi(item_str7);
	item_value[7] = atoi(item_str8);

	value = atoi(str2);
	secondvalue = atoi(str3);

	if (strlen(str2) > 80)
		return FALSE;

	_strupr(str1);

	if (!strcmp(str1, "MOBNAME:"))
		strncpy(pMobMerc[Num].MobName, str2, NAME_LENGTH);

	else if (!strcmp(str1, "GENERATEINDEX:"))
		pMobMerc[Num].GenerateIndex = value;

	else if (!strcmp(str1, "RENEWTIME:"))
		pMobMerc[Num].RenewTime = value * 2;

	else if (!strcmp(str1, "REBORNTIME:"))
		pMobMerc[Num].RebornTime = value * 2;

	else
	{
		for (int i = 0; i < MAX_CARRY; i++)
		{
			sprintf_s(temp, "ITEM_%d:", i);

			if (!strcmp(str1, temp))
			{
				pMobMerc[Num].Carry[i].sIndex = item_value[0];
				pMobMerc[Num].Carry[i].stEffect[0].cEffect = item_value[1];
				pMobMerc[Num].Carry[i].stEffect[0].cValue = item_value[2];
				pMobMerc[Num].Carry[i].stEffect[1].cEffect = item_value[3];
				pMobMerc[Num].Carry[i].stEffect[1].cValue = item_value[4];
				pMobMerc[Num].Carry[i].stEffect[2].cEffect = item_value[5];
				pMobMerc[Num].Carry[i].stEffect[2].cValue = item_value[6];

				pMobMerc[Num].MaxStock[i] = item_value[7];
				pMobMerc[Num].Stock[i] = item_value[7];

				return TRUE;
			}
		}
	}
	return TRUE;
}

void DeleteGenerateMob(int generate)
{
	for (int i = MAX_USER; i < MAX_MOB; i++)
	{
		if (pMob[i].Mode == MOB_EMPTY)
			continue;

		if (pMob[i].GenerateIndex != generate)
			continue;

		DeleteMob(i, 3);
	}
}

int  CreateTreasureBox(int x, int y, STRUCT_ITEM *item, int rotate, int State)
{
	if (item->sIndex <= 0 || item->sIndex >= MAX_ITEMLIST)
		return FALSE;

	GetEmptyItemGrid(&x, &y);


	if (pItemGrid[y][x])
		return FALSE;

	int empty = GetEmptyItem();

	if (empty == 0)
		return FALSE;

	pItem[empty].Mode = 2;

	pItem[empty].PosX = x;
	pItem[empty].PosY = y;

	memcpy(&pItem[empty].ITEM, item, sizeof(STRUCT_ITEM));

	pItem[empty].Rotate = rotate;
	pItem[empty].State = State;

	pItem[empty].Delay = 0;
	pItem[empty].Decay = 0;

	pItem[empty].GridCharge = BASE_GetItemAbility(item, EF_GROUND);

	pItemGrid[y][x] = empty;

	pItem[empty].Height = pHeightGrid[y][x];

	MSG_CreateItem sm;
	memset(&sm, 0, sizeof(MSG_CreateItem));

	sm.Type = _MSG_CreateItem;
	sm.Size = sizeof(MSG_CreateItem);
	sm.ID = ESCENE_FIELD;

	sm.ItemID = empty + 10000;

	memcpy(&sm.Item, &pItem[empty].ITEM, sizeof(STRUCT_ITEM));

	sm.GridX = x;
	sm.GridY = y;

	sm.Rotate = rotate;
	sm.State = pItem[empty].State;

	sm.Height = -204;

	GridMulticast(x, y, (MSG_STANDARD*)&sm, 0);

	return TRUE;
}

void RefinarItemMais(STRUCT_ITEM *item, int value)
{
	if (item->stEffect[1].cEffect == EF_SANC || (item->stEffect[1].cEffect >= 116 && item->stEffect[1].cEffect <= 125))
		item->stEffect[1].cValue += value;
	else if (item->stEffect[2].cEffect == EF_SANC || (item->stEffect[2].cEffect >= 116 && item->stEffect[2].cEffect <= 125))
		item->stEffect[2].cValue += value;
	else if (item->stEffect[3].cEffect == EF_SANC || (item->stEffect[3].cEffect >= 116 && item->stEffect[3].cEffect <= 125))
		item->stEffect[1].cValue += value;
	else
	{
		if (!item->stEffect[1].cEffect)
		{
			item->stEffect[1].cEffect = EF_SANC;
			item->stEffect[1].cValue = value;
		}
		else if (!item->stEffect[2].cEffect)
		{
			item->stEffect[2].cEffect = EF_SANC;
			item->stEffect[2].cValue = value;
		}
		else if (!item->stEffect[3].cEffect)
		{
			item->stEffect[3].cEffect = EF_SANC;
			item->stEffect[3].cValue = value;
		}
	}

	return;
}

int GetItemSanc(STRUCT_ITEM *item)
{
	for (int i = 0; i < 3; i++)
		if (item->stEffect[i].cEffect == EF_SANC || (item->stEffect[i].cEffect >= 116 && item->stEffect[i].cEffect <= 125))
			return item->stEffect[i].cValue;

	return 0;
}

bool CheckArchItem(int id)
{
	int retorno = false;
	///SET'S
	if (id >= 1221 && id <= 1224) retorno = true;
	else if (id >= 1356 && id <= 1359) retorno = true;
	else if (id >= 1506 && id <= 1509) retorno = true;
	else if (id >= 1656 && id <= 1659) retorno = true;
	///ARMAS ARCH
	else if (id == 811 || id == 826 || id == 841) retorno = true;
	else if (id == 856 || id == 871 || id == 886) retorno = true;
	else if (id == 871 || id == 886 || id == 903 || id == 904) retorno = true;
	else if (id == 912 || id == 937 || id == 2379 || id == 2380) retorno = true;
	///ARMAS ARCH ANCT
	else if ((id >= 2491 && id <= 2494) || (id >= 2551 && id <= 2554)) retorno = true;
	else if ((id >= 2611 && id <= 2614) || (id >= 2671 && id <= 2674)) retorno = true;
	else if ((id >= 2791 && id <= 2794) || (id >= 2859 && id <= 2866)) retorno = true;
	else if ((id >= 2895 && id <= 2898) || (id >= 2935 && id <= 2938)) retorno = true;
	else if ((id >= 2731 && id <= 2734)) retorno = true;
	return retorno;
}

bool CheckHardItem(int id)
{
	int retorno = false;
	///SET'S
	if (id >= 1901 && id <= 1910) {
		retorno = true;
	}

	///ARMAS ARCH
	else if (id == 1230 || id == 1231 || id == 1232 || id == 1667)
		retorno = true;
	else if (id == 1233 || id == 1365 || id == 1366 || id == 1668)
		retorno = true;
	else if (id == 1367 || id == 1368 || id == 1515 || id == 1516)
		retorno = true;
	else if (id == 1517 || id == 1518 || id == 1665 || id == 1666)
		retorno = true;

	return retorno;
}

void AmountMinus(STRUCT_ITEM *item)
{
	int index = 0;
	int amount = 0;
	for (int i = 0; i < 3; i++)
	{
		if (item->stEffect[i].cEffect == 61)
		{
			index = i;
			amount = item->stEffect[i].cValue;
			break;
		}
	}

	if (amount <= 1)
		memset(item, 0, sizeof STRUCT_ITEM);
	else
		item->stEffect[index].cValue--;
}

bool CheckMount(STRUCT_ITEM *Item, INT16 Mount)
{
	int number = Item->sIndex - 3351;

	for (INT8 e = 0; e < 4; e++)
		if (MountCheck[number][e] && MountCheck[number][e] == Mount)
			return true;

	return false;
}

bool CheckMount2(STRUCT_ITEM *Item, INT16 Mount)
{
	int number = Item->sIndex - 3344;

	for (INT8 e = 0; e < 4; e++)
		if (MountCheck2[number][e] && MountCheck2[number][e] == Mount)
			return true;

	return false;
}

void SetItemSanc(STRUCT_ITEM *item, int value)
{
	if (item->stEffect[0].cEffect == EF_SANC || (item->stEffect[0].cEffect >= 116 && item->stEffect[0].cEffect <= 125))
		item->stEffect[0].cValue = value;
	else if (item->stEffect[1].cEffect == EF_SANC || (item->stEffect[1].cEffect >= 116 && item->stEffect[1].cEffect <= 125))
		item->stEffect[1].cValue = value;
	else if (item->stEffect[2].cEffect == EF_SANC || (item->stEffect[2].cEffect >= 116 && item->stEffect[2].cEffect <= 125))
		item->stEffect[2].cValue = value;
	else
	{
		for (int i = 0; i < 3; i++)
		{
			if (!item->stEffect[i].cEffect)
			{
				item->stEffect[i].cEffect = EF_SANC;
				item->stEffect[i].cValue = value;
				return;
			}
		}
	}
}

 

bool ReadQuiz()
{
	FILE *fp;

	fopen_s(&fp, "RandomQuiz.txt", "rt");

	if (fp == NULL)
	{
		MessageBoxA(0, "Missing RandomQuiz.txt file", "Error", MB_ICONERROR | MB_OK);
		fclose(fp);
		return false;
	}

	QuizLineCounter = -1;

	char line[256];
	while (fgets(line, sizeof(line), fp))
	{
		MSG_Quiz UsedQuiz;
		memset(&UsedQuiz, 0, sizeof(MSG_Quiz));

		char *p = line;

		for (int o = 0; o < 1024; o++)
		{
			if (line[o] == ',') { line[o] = ' '; }
			if (line[o] == '[') { break; }
		}

		if (line[0] == '#')
			continue;

		char title[128], str0[32], str1[32], str2[32], str3[32];
		int test = -1;

		if (sscanf(line, "%s %s %s %s %s %d", title, str0, str1, str2, str3, &test))
		{
			strncpy(UsedQuiz.Title, title, 128);
			strncpy(UsedQuiz.Answer[0], str0, 32);
			strncpy(UsedQuiz.Answer[1], str1, 32);
			strncpy(UsedQuiz.Answer[2], str2, 32);
			strncpy(UsedQuiz.Answer[3], str3, 32);
			UsedQuiz.CorrectAlternative = test;
			memcpy(&QuizList[QuizLineCounter], &UsedQuiz, sizeof UsedQuiz);
			QuizLineCounter++;
		}
		else
		{
			MessageBoxA(0, "Missing data in quiz", "Error", MB_ICONERROR | MB_OK);
			fclose(fp);
			return false;
		}
	}

	fclose(fp);
	return true;
}

bool ReadCuboQuiz()
{
	FILE *fp;

	fopen_s(&fp, "CuboQuiz.txt", "rt");

	if (fp == NULL)
	{
		MessageBoxA(0, "Missing CuboQuiz.txt file", "Error", MB_ICONERROR | MB_OK);
		fclose(fp);
		return false;
	}

	CuboQuizLine = -1;

	char line[256];
	while (fgets(line, sizeof(line), fp))
	{
		MSG_BigQuiz qq;
		memset(&qq, 0, sizeof(MSG_BigQuiz));

		char *p = line;

		for (int o = 0; o < 1024; o++)
		{
			if (line[o] == ',') { line[o] = ' '; }
			if (line[o] == '[') { break; }
		}

		if (line[0] == '#')
			continue;

		int num, k;
		char title[128], string[128];

		int test = -1;

		if (sscanf(line, "%d %d %s", &num, &k, string))
		{
			qq.Unknow = num;
			sprintf_s(title, "<<_No._%d_>>", num);
			strncpy(qq.Title, title, 128);
			strncpy(qq.Line[0], string, 128);
			memcpy(&CuboList[CuboQuizLine], &qq, sizeof qq);
			CuboQuizLine++;
		}
		else
		{
			MessageBoxA(0, "Missing data in quiz", "Error", MB_ICONERROR | MB_OK);
			fclose(fp);
			return false;
		}
	}

	fclose(fp);
	return true;
}

/*
bool LoadCuboCoord()
{
	FILE *fp = fopen("CuboCord.txt", "r+");

	if (fp == NULL)
		return FALSE;

	char line[1024];
	int Xr = 0;
	int Or = 0;

	while (fgets(line, sizeof(line), fp))
	{
		if (*line == '\n' || *line == '#')
			continue;

		char *p = line;

		while (*p != '\0')
		{
			if (*p == ',')
				*p = ' ';
			else if (*p == '[')
				*p = ' ';
			else if (*p == ']')
				*p = ' ';

			p++;
		}

		char VF;
		int indessx;

		sPoint Cord;
		memset(&Cord, 0, sizeof(sPoint));
		sscanf(line, "%c %d %4d %4d", &VF, &indessx, &Cord.PosX, &Cord.PosY);

		if (VF == 'O')
		{
			Cubo.O[Or].PosX = Cord.PosX;
			Cubo.O[Or].PosY = Cord.PosY;
			Or++;
		}
		else if (VF == 'X')
		{
			Cubo.X[Xr].PosX = Cord.PosX;
			Cubo.X[Xr].PosY = Cord.PosY;
			Xr++;
		}
	}

	fclose(fp);
	return TRUE;
}

bool LoadCubo()
{
	FILE *fp = fopen("Cubo.txt", "r+");

	if (fp == NULL)
		return false;

	char line[1024];

	for (int x = 0; x < 25; x++)
	{
		int index = 0, num = 0;

		fgets(line, sizeof(line), fp);

		sscanf(line, "%d %d %100[^=]", &num, &index, Cubo.Question[x]);

		Cubo.CurrentQuestion[x] = num;
		Cubo.Question[x][strlen(Cubo.Question[x]) - 1] = '\0';

		if (index == 0)
			Cubo.Answer[x] = FALSE;
		else if (index == 1)
			Cubo.Answer[x] = TRUE;
		else
			return FALSE;
	}

	fclose(fp);
	return TRUE;
}*/

void ReadDirectory()
{
	if ((fReadDir = fopen("Account_Directory.txt", "r")) == NULL)
	{
		MessageBox(hWndMain, "N�o foi possivel abrir Account_Directory.txt!", "Erro ao iniciar", NULL);
		return;
	}
	else
	{
		fscanf(fReadDir, "%s", ACCOUNT_DIRECTORY);
		fclose(fReadDir);
	}
}

void SendSpkMsg(int conn, char* Msg, TNColor Color32, bool ToAll = false)
{
	if (conn <= 0 || conn >= MAX_USER) return;

	MSG_ChatColor sm_mt;
	memset(&sm_mt, 0, sizeof(MSG_STANDARDPARM));

	sm_mt.Size = sizeof(MSG_ChatColor);
	sm_mt.ID = 0;
	sm_mt.Type = _MSG_MagicTrumpet;
	strncpy(sm_mt.Message, Msg, sizeof(sm_mt.Message));
	sm_mt.Color = Color32;

	if (ToAll)
	{
		for (int i = 1; i < MAX_USER; i++)
		{
			if (pUser[i].Mode != USER_PLAY) continue;

			pUser[i].cSock.SendOneMessage((char*)&sm_mt, sizeof(sm_mt));
		}
	}
	else
	{
		pUser[conn].cSock.SendOneMessage((char*)&sm_mt, sizeof(sm_mt));
	}


}

void SendMsgExp(int conn, char* Msg, TNColor Color32, bool ToAll = false)
{
	if (conn <= 0 || conn >= MAX_USER) return;

	MSG_Exp_Msg_Panel_ sm;
	memset(&sm, 0, sizeof(MSG_Exp_Msg_Panel_));

	sm.Type = _MSG_Exp_Msg_Panel_;
	sm.Size = sizeof(MSG_Exp_Msg_Panel_);
	sm.ID = conn;

	strncpy(sm.Msg, Msg, sizeof(sm.Msg));

	sm.Color32 = Color32;

	if (ToAll)
	{
		for (int i = 0; i < MAX_USER; i++)
		{
			if (pUser[i].Mode != USER_PLAY) continue;

			pUser[i].cSock.SendOneMessage((char*)&sm, sizeof(sm));
		}
	}
	else
	{
		pUser[conn].cSock.SendOneMessage((char*)&sm, sizeof(sm));
	}
}