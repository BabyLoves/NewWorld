
#ifndef _BASEDEF_ // Last updated 2017
#define _BASEDEF_

#include <time.h>
#include <Windows.h>
#include <cstdint>

#pragma region Defines

//Color
#define Snow                    0xFFFFFAFA
#define GhostWhite              0xFFF8F8FF
#define WhiteSmoke              0xFFF5F5F5
#define Gainsboro               0xFFDCDCDC
#define FloralWhite             0xFFFFFAF0
#define OldLace                 0xFFFDF5E6
#define Linen                   0xFFFAF0E6
#define AntiqueWhite            0xFFFAEBD7
#define PapayaWhip              0xFFFFEFD5
#define BlanchedAlmond			0xFFFFEBCD
#define Bisque					0xFFFFE4C4
#define PeachPuff				0xFFFFDAB9
#define NavajoWhite				0xFFFFDEAD
#define Moccasin				0xFFFFE4B5
#define Cornsilk				0xFFFFF8DC
#define Ivory					0xFFFFFFF0
#define LemonChiffon			0xFFFFFACD
#define Seashell				0xFFFFF5EE
#define Honeydew				0xFFF0FFF0
#define MintCream				0xFFF5FFFA
#define Azure					0xFFF0FFFF
#define AliceBlue				0xFFF0F8FF
#define lavender				0xFFE6E6FA
#define LavenderBlush			0xFFFFF0F5
#define MistyRose				0xFFFFE4E1
#define White					0xFFFFFFFF
#define Black					0xFF000000
#define DarkSlateGray			0xFF2F4F4F
#define DimGrey					0xFF696969
#define SlateGrey				0xFF708090
#define LightSlateGray			0xFF778899
#define Grey					0xFFBEBEBE
#define LightGray				0xFFD3D3D3
#define MidnightBlue			0xFF191970
#define NavyBlue				0xFF000080
#define CornflowerBlue			0xFF6495ED
#define DarkSlateBlue			0xFF483D8B
#define SlateBlue				0xFF6A5ACD
#define MediumSlateBlue			0xFF7B68EE
#define LightSlateBlue			0xFF8470FF
#define MediumBlue				0xFF0000CD
#define RoyalBlue				0xFF4169E1
#define Blue					0xFF0000FF
#define DodgerBlue				0xFF1E90FF
#define DeepSkyBlue				0xFF00BFFF
#define SkyBlue					0xFF87CEEB
#define LightSkyBlue			0xFF87CEFA
#define SeaGreen				0xFF2E8B57
#define MediumSeaGreen			0xFF3CB371
#define LightSeaGreen			0xFF20B2AA
#define PaleGreen				0xFF98FB98
#define SpringGreen				0xFF00FF7F
#define LawnGreen				0xFF7CFC00
#define Green					0xFF00FF00

//BUFS INDEX
#define LENTIDAO                1
#define FM_VELOCIDADE           2
#define RESISTENCIA_N           3
#define EVASAO_N                5
#define POCAO_ATK               6
#define VELOCIDADE_N            7
#define ADD_                    8
#define FM_BUFFATK              9
#define ATKMENOS                10
#define FM_ESCUDO_MAGICO        11
#define DEFESA_N                12
#define TK_ASSALTO              13
#define TK_POSSUIDO             14
#define FM_SKILLS               15
#define BM_MUTACAO              16
#define TK_AURAVIDA             17
#define FM_CONTROLE_MANA        18
#define HT_IMUNIDADE            19
#define VENENO                  20
#define HT_MEDITACAO            21
#define FM_TROVAO               22
#define BM_AURA_BESTIAL         23
#define TK_SAMARITANO           24
#define BM_PROTELEMENT          25
#define HT_EVASAO_APRIMORADA    26
#define HT_GELO                 27
#define HT_INIVISIBILIDADE      28
#define LIMITE_DA_ALMA          29
#define PvM                     30
#define HT_ESCUDO_DOURADO       31
#define CANCELAMENTO            32
#define MUTACAO2                33
#define COMIDA                  34
#define BONUS_HP_MP             35
#define HT_VENENO               36
#define HT_LIGACAO_ESPCTRAL     37
#define HT_TROCAESP             38
#define BAU_EXP                 39

//#define PKDrop

#define IDC_EXIT 9000
#define IDC_MOBRELOAD 9001
#define IDC_REBOOT 9002
#define IDC_SAVEALL 9003
#define IDC_READGUILD 9004
#define IDC_READGUILDNAME 9005
#define IDC_READGAMECONFIG 9006
#define IDC_READSKILLDATA 9007
#define IDC_READITEMLIST 9008

#define IDC_SHUTDOWNNP 9050


#define		APP_VERSION				18120 

#define		GAME_PORT				8281	  // Game server listening port, client connects to it
#define		DB_PORT					7514      // DB server listening port, Game server connects to it
#define		ADMIN_PORT				3695	  // DB server listening port, NPTool connects to it  //8895

#define		MAX_SERVER				10      // Max number of game servers that can connect to DB server
#define		MAX_SERVERGROUP			10		// Max number of servers that can exist
#define		MAX_SERVERNUMBER		(MAX_SERVER+1) // DB + TMSrvs + BISrv

#define		MAX_IP_LENGTH			16

#define		SECSTANDINGBY			8
#define		SECBATTLE				8
#define		MAX_USER				1000      // Max users on CUser pUser and starting index of npcs and mobs
#define		ADMIN_RESERV			1		// Max reserv slot in gameserver for admin's
#define		MAX_ADMIN				1       // Max number of NP that can connect to DB server

#define		MAX_DBACCOUNT			(MAX_USER * MAX_SERVER) // Max players connected to a single DBSrv at the same time
#define		MAX_RANK_INDEX			50

#pragma region Account related defines191 _NN_Reconnect

#define		ACCOUNTNAME_LENGTH		16		// Max length of the account login
#define		ACCOUNTPASS_LENGTH		12      // Max length of the account password
#define		REALNAME_LENGTH			24      // Max length of the name of the account owner
#define		EMAIL_LENGTH			48      // Max length of the email address of the account owner
#define		ADDRESS_LENGTH			78      // Max length of the real address of the account owner
#define		TELEPHONE_LENGTH		16      // Max length of the telephone number of the account owner
#define		MOB_PER_ACCOUNT			4       // Max number of mobs an account can have

#pragma endregion

#define		MAX_EQUIP				16
#define		MAX_CARRY				64
#define		MAX_CARGO				128

#define		MAX_TRADE				15
#define		MAX_AUTOTRADE			12
#define		MAX_AUTOTRADETITLE		24
#define		MAX_SHOPLIST			27

#define		MAX_GROUNDMASK			6

#define		ITEM_PLACE_EQUIP		0
#define		ITEM_PLACE_CARRY		1
#define		ITEM_PLACE_CARGO		2

#define		CARGOGRIDX				9
#define		CARGOGRIDY				14
#define		CARRYGRIDX				9
#define		CARRYGRIDY				7

#define		VIEWGRIDX				33
#define		VIEWGRIDY				33
#define		HALFGRIDX				16
#define		HALFGRIDY				16

#define		MAX_GRIDX				4096
#define		MAX_GRIDY				4096

#define		MAX_ITEM				5000

#define		MAX_SUMMONLIST			50

#define		MAX_MOB					25000

#define		MAX_NPCGENERATOR		8192

#define		MAX_SKILL				24
#define		MAX_CSKILL				12

#define		MAX_COMBINE				8

#define		MAX_CLASS				4

#define		MAX_LEVEL				399
#define		MAX_CLEVEL				399 // 199  //PARA TRAVAR LEVEL

#define		MAX_CLASSMASTER			4

#define		MAX_AFFECT				32

#define		MAX_ROUTE				24

#define		MAX_TRANS				20480

#define		MAX_ITEM_REBUY			10

#define		MAX_NOTIFY_LENGTH		96
#define		MESSAGE_LENGTH			96 
#define		MESSAGEWHISPER_LENGTH	100
#define		MESSAGECHAT_LENGTH		128

#define		NAME_LENGTH				16

#define		MH						8

#define		TIMER_SEC				0
#define		TIMER_MIN				1

#define		ELMO_TYPE				2 
#define		PEITO_TYPE				4
#define		CALCA_TYPE				8
#define		LUVA_TYPE				16
#define		LUVA_TYPE1				16
#define		BOTA_TYPE				32
#define		ARMA_TYPE1				192
#define		ARMA_TYPE2				64
#define		ESCUDO_TYPE				128	

#define		MAX_ITEMLIST			6500
#define		MAX_SKILLINDEX			248 //103
#define		MAX_INITITEM			256
#define		MAX_EFFECTINDEX			128
#define		ITEMNAME_LENGTH			64
#define		MAX_STATICEFFECT		12

#define		GUILDNAME_LENGTH		12
#define		MAX_GUILD				4096
#define		MAX_GUILDZONE			5

#define		MAX_STRING				2000
#define		MAX_ENGLISH				600
#define		MAX_MAC					200
#define		MAX_ACCOUNTMAC			2

#define     MAX_CASTLE_POS			9
#define		MAX_CASTLE_QUEST		64

#define		MAX_MOB_MERC			128

#define		MAX_CAMP_QUEST			64

#define		MAX_CAMP_PRIZE			12

#define		MAX_PIN_LENGTH			37

#define		KILL_MARK				63

#define		KILL_MARK_CHAOS_POINTS	0		// cEffect used to control the chaos points of the mob

#define		MAX_PARTY				12

#define		ESCENE_FIELD			30000 // Identifier for the server sent messages

#define		SKIPCHECKTICK			235543242 // base number for the tick checking so people don't get kicked out before doing something
#define		MAX_TARGET				13

#define		REINO_RED				8
#define		REINO_BLUE				7

#define		MORTAL					2
#define		ARCH					1
#define		CELESTIAL				3
#define		CELESTIALCS				4
#define		SCELESTIAL				5
#define     HARDCORE                6
#define		HARDCOREA				7
#define		HARDCORECS				8
#define		SHARDCORE				9

#define		RSV_FROST    0x01
#define		RSV_DRAIN    0x02
#define		RSV_VISION   0x04
#define		RSV_PARRY    0x08
#define		RSV_HIDE	 0x10
#define		RSV_HASTE    0x20
#define		RSV_CAST     0x40
#define		RSV_BLOCK    0x80
#define		RSV_IMUNIDADE 0x100

#define		MSV_SNOOP	0x01

#define		REF_10					10
#define		REF_11					12
#define		REF_12					15
#define		REF_13					18
#define		REF_14					22
#define		REF_15					27

#define		MAX_HP					100000
#define		MAX_MP					100000
#define		MAX_DAMAGE				500000// Não alterar pois calculo é multiplicado por 20
#define		MAX_DAMAGE_MG			190000000//  não alterar calculo multiplicado por 13
#define		AFFECT_1D				10800
#define		AFFECT_1H				450
#define		MAX_VELOATK				32000
#define		MAX_CRITICAL			186000 //102 16/02/2017

#define		LIMT_STR				32000
#define		LIMT_INT				32000
#define		LIMT_DEX				32000
#define		LIMT_CON				32000
#define		LIMT_DAM				186000
#define		LIMT_DAM_MG				190000000
#define		MAX_ESCUDOS				21
#define		MAX_ARCOS				19
#define		MAX_RAD_ARCOS			4

#define		SOUL_NULL				0
#define		SOUL_KIBITA				1

#define		SOUL_F					2
#define		SOUL_I					3
#define		SOUL_D					4
#define		SOUL_C					5

#define		SOUL_FI					6
#define		SOUL_FD					7
#define		SOUL_FC					8

#define		SOUL_IF					9
#define		SOUL_ID					10
#define		SOUL_IC					11

#define		SOUL_DF					12
#define		SOUL_DI					13
#define		SOUL_DC					14

#define		SOUL_CF					15
#define		SOUL_CI					16
#define		SOUL_CD					17

//////////////////// ModeIngame ////////////////////////////////////

#define		TIMERLOJINHA		    600//600 É 10 MINUTOS.

//////////////////// QST ////////////////////////////////////

#define	QST_AMUMISTICO			1

////////////////////MSG_Quest NPC's//////////////////////////

#define GOLD_DRAGON				1
#define AMU_MISTICO				2
#define MESTREHAB				3
#define EXPLOIT_LEADER			4
#define ARZAN_DRAGON			5
#define TREINADORNEWBIE1		6
#define TREINADORNEWBIE2		7
#define TREINADORNEWBIE3		8
#define CHEFE_DE_TREINO		    9
#define COMP_SEPHI				10
#define CAPAVERDE_TELEPORT		11
#define MOUNT_MASTER			12
#define ZAKUM					13
#define JEFFI					14
#define SHAMA					15
#define KING					16
#define KINGDOM					17
#define URNAMMU					18
#define CAPAVERDE_TRADE			19
#define QUEST_COVEIRO			20
#define QUEST_JARDINEIRO		21
#define QUEST_KAIZEN			22
#define QUEST_HIDRA				23
#define QUEST_ELFOS				24
#define UXMAL					25
#define MOLARGARGULA			26
#define BLACKORACLE				27
#define QUEST_CAPAREAL			28
#define CARBUNCLE_WIND			29
#define PERZEN					30
#define KIBITA					31
#define GODGOVERNMENT			32
#define SOBREVIVENTE			33
#define LIDER_APRENDIZ			34
#define GUARDA_REAL_I			35
#define GUARDA_REAL_II  		36
#define GUARDA_REAL_III 		37
#define GUARDA_REAL_IV  		38
#define GUARDA_REAL_V   		39
#define GUARDA_REAL_VI  		40
#define EVENTO_HIT  		    80
#define CURANDEIRA				41
#define MESTREHAB2				42
#define UPADOR   				43
#define QUEST_BENCAODEDEUS  	44
#define KRUNO                   45
#define MESTREGRIFO             46
#define QUEST_EQUILIBRIO        47
#define AMELIA                  48
#define JULIARZAN               49
#define JULIGELO                50
#define UNICORNIO_PURO          51
#define EVENTO_DROP				52
#define BATALHA_REAL			53
#define XAMACOLISEU				54
#define TELEPORTEVENTO1  		55
#define TELEPORTEVENTO2  		56
#define TELEPORTEVENTO3  		57
#define TELEPORTEVENTO4  		58
#define LANHOUSEN  				59
#define LANHOUSEM		  		60
#define LANHOUSEA		  		61
#define GUARDACARGA		  		62
#define FRAGMENTODAALMA  		63
#define TROCADEFADA		        64

/////////////////////////////////////////////////////////////

#pragma region Others Spawn

#define ZAKUM_LORD							4
#define ORC_GUERREIRO						1694

#pragma endregion

#pragma region KINGDASCAPAS

#define REI_HARABARD						4744
#define REI_GLANTUAR						4745

#pragma endregion

#pragma region TORRE NOATUN

#define TORRE_NOATUM1						22
#define TORRE_NOATUM2						23
#define TORRE_NOATUM3						24

#pragma endregion

#pragma region ALL SPAWN PERGAMINHO AGUA

#define WATER_M_INITIAL						9
#define WATER_N_INITIAL						170
#define WATER_A_INITIAL						182

#pragma endregion

#pragma region SPAWN COLISEU

#define COLISEU_N_INITIAL					0
#define COLISEU_N_END						1
#define COLISEU_M_INITIAL					2
#define COLISEU_M_END						4
#define COLISEU_A_INITIAL					5 
#define COLISEU_A_END						6

#pragma endregion

#pragma region NPC PESADELO [N]

#define PESANPC_N_INITIAL					267
#define PESANPC_N_END						271

#define Martin 								267
#define Balmers 							268
#define Rubyen								269
#define Naomi								270
#define Arnold								271 

#pragma endregion 

#pragma region NPC PESADELO [M]

#define PESANPC_M_INITIAL					282
#define PESANPC_M_END						288

#define Arnold_ 							282
#define	Lainy								283
#define	Reimers 							284
#define	RoPerion 							285
#define	Irena								286
#define	Danad								287
#define	Smith								288

#pragma endregion

#pragma region NPC PESADELO [A]

#define PESANPC_A_INITIAL					299
#define PESANPC_A_END						306

#define Escuridao							299
#define Kara								300
#define Kei									301
#define Erin								302
#define Kemi								303
#define Fenix								304
#define Yue									305
#define Leao								306

#pragma endregion

#pragma region CLASSES MAIN

#define TransKnight							0
#define Foema								1
#define BeastMaster							2
#define Huntress							3

#pragma endregion

#pragma region ALLSPAWN CARTA DUELO

#define SECRET_ROOM_N_SALA1_MOB_1			2391
#define SECRET_ROOM_N_SALA1_MOB_2			2392
#define SECRET_ROOM_N_SALA2_MOB_1			2393
#define SECRET_ROOM_N_SALA2_MOB_2			2394
#define SECRET_ROOM_N_SALA3_MOB_1			2395
#define SECRET_ROOM_N_SALA3_MOB_2			2396
#define SECRET_ROOM_N_SALA4_MOB_1			2397
#define SECRET_ROOM_N_SALA4_MOB_2			2398
#define SECRET_ROOM_N_SALA4_MOB_3			2397
#define SECRET_ROOM_N_SALA4_MOB_4			2398

#define SECRET_ROOM_N_INITIAL				2391
#define SECRET_ROOM_N_END					2398

#define SECRET_ROOM_N_BOSS_INITIAL			2399

#define SECRET_ROOM_M_SALA1_MOB_1			2401
#define SECRET_ROOM_M_SALA1_MOB_2			2402
#define SECRET_ROOM_M_SALA2_MOB_1			2403
#define SECRET_ROOM_M_SALA2_MOB_2			2404
#define SECRET_ROOM_M_SALA3_MOB_1			2405
#define SECRET_ROOM_M_SALA3_MOB_2			2406
#define SECRET_ROOM_M_SALA4_MOB_1			2407
#define SECRET_ROOM_M_SALA4_MOB_2			2408
#define SECRET_ROOM_M_SALA4_MOB_3			2407
#define SECRET_ROOM_M_SALA4_MOB_4			2408

#define SECRET_ROOM_M_INITIAL				2401
#define SECRET_ROOM_M_END					2408

#define SECRET_ROOM_M_BOSS_INITIAL			2409


#define SECRET_ROOM_A_SALA1_MOB_1			2411
#define SECRET_ROOM_A_SALA1_MOB_2			2412
#define SECRET_ROOM_A_SALA2_MOB_1			2413
#define SECRET_ROOM_A_SALA2_MOB_2			2414
#define SECRET_ROOM_A_SALA3_MOB_1			2415
#define SECRET_ROOM_A_SALA3_MOB_2			2416
#define SECRET_ROOM_A_SALA4_MOB_1			2417
#define SECRET_ROOM_A_SALA4_MOB_2			2418
#define SECRET_ROOM_A_SALA4_MOB_3			2417
#define SECRET_ROOM_A_SALA4_MOB_4			2418

#define SECRET_ROOM_A_INITIAL				2411
#define SECRET_ROOM_A_END					2418

#define SECRET_ROOM_A_BOSS_INITIAL			2419

#pragma endregion

#pragma region ALL SPAWN PESADELO

#define NIGHTMARE_N_INITIAL					2364
#define NIGHTMARE_N_END						2372

#define NIGHTMARE_M_INITIAL					2373
#define NIGHTMARE_M_END						2380

#define NIGHTMARE_A_INITIAL					2381
#define NIGHTMARE_A_END						2390

#pragma endregion

#pragma region ALL SPAWN PISTA RUNAS

#define RUNEQUEST_LV0_LICH1					4159
#define RUNEQUEST_LV0_LICH2					4160

#define RUNEQUEST_LV1_TORRE1				4213
#define RUNEQUEST_LV1_TORRE2				4214
#define RUNEQUEST_LV1_TORRE3				4215

#define RUNEQUEST_LV1_MOB_INITIAL			4216
#define RUNEQUEST_LV1_MOB_END				4271

#define RUNEQUEST_LV2_MOB_BOSS				4295
#define RUNEQUEST_LV2_MOB_INITIAL			4297
#define RUNEQUEST_LV2_MOB_END				4354

#define RUNEQUEST_LV3_MOB_SULRANG_INITIAL	4479
#define RUNEQUEST_LV3_MOB_SULRANG_END		4482

#define RUNEQUEST_LV3_MOB_BOSS_INITIAL		4455
#define RUNEQUEST_LV3_MOB_BOSS_END			4462

#define RUNEQUEST_LV4_MOB_INITIAL			4357
#define RUNEQUEST_LV4_MOB_END				4404
#define RUNEQUEST_LV4_MOB_BOSS				4355

#define RUNEQUEST_LV5_MOB_BOSS				4405

#define RUNEQUEST_LV6_MOB_INITIAL			4281
#define RUNEQUEST_LV6_MOB_END				4291
#define RUNEQUEST_LV6_MOB_INITIAL2			4274
#define RUNEQUEST_LV6_MOB_END2				4280
#define RUNEQUEST_LV6_MOB_BOSS				4273

#pragma endregion

#pragma region SPAWN CUBO DA MALDADE

#define CUBO_N_INITIAL						194
#define CUBO_N_END							219

#pragma endregion

#pragma region SPAW GUERRAS

#define RVRTORRE_1							287
#define RVRTORRE_2							288

#define GTORRE								1075

#pragma endregion

#pragma region ALL SPAWN BOSS

#define SICARIO                             4961
#define CARONTE                             4960
#define KINGTAURON                          4959
#define TAURONDESERTO1                      3139
#define TAURONDESERTO2                      3159
//RVR
#define BARAO_AZUL                          4952
#define BARAO_VERMELHO                      4953
#define ENT_OBSCURO_BLUE                    4954
#define ENT_OBSCURO_RED                     4955

#define BOSS_EVT_PASCOA                     4901
#define MOB_EVT_PASCOA_INITIAL              4907
#define MOB_EVT_PASCOA                      4950
#define MOB_EVT_PASCOA_INITIAL1             4951
#define MOB_EVT_PASCOA1                     4955

#define BOSS_SOMBRA_NEGRA_GELO              4100

#define KEFRA_BOSS							393
#define KEFRA_MOB_INITIAL					394
#define KEFRA_MOB_END						397
//////////////////////////////////castelo do gelo//////////////////////////////////////
#define SOMBRANEGRA							4655
#define ESPELHO_RAINHAG						4653
#define VERIDNEGRO							4654

#define BOSS1_INITIAL						4041
#define BOSS1_END							4066
#define BOSS1_INITIAL2						4041
#define BOSS1_END2							4066
//////////////////////////////////zona inf//////////////////////////////////////
#define PI_INITIAL1							4656 // Inicio
#define PI_END1								4665
#define TARANTULA							4666
#define CTARANTULA							4667

#define PI_INITIAL2							4668 // Quadra 1
#define PI_END2								4676
#define LICHBOSS1							4677

#define PI_INITIAL3							4678 // Quadra 2
#define PI_END3								4686
#define LICHBOSS2							4687

#define PI_INITIAL4							4689 // Quadra 3
#define PI_END4								4697
#define LICHBOSS3							4698

#define PI_INITIAL5							4688 // Quadra 4
#define PI_END5								4696
#define LICHBOSS4							4697

#define PI_INITIAL6							4708
#define PI_END6								4721

// NOVOS BOSS
#define SOMBRANEGRAB						4099

#pragma endregion


////////////////////////////////////////////////////////////
/*//////////////////////MODE INGAME////////////////////////*/
 


/*/////////////////////////////////////////////////////////*/
#pragma endregion

#pragma region Enum



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

struct MSG_BattleReal
{
	short NumMembers;
	int Reward;
	short Timer;
	char WeekWinner[16];
	char WinningSpree;
	bool start;
	struct
	{
		short Id;
		char Name[16];
	} Members[60];
};

typedef struct
{
	char min, hora, dia, mes, ano;

	char Permanente, Analyze;



	char Grade[102];

}AccountBanned;

struct STRUCT_USER
{
	int CounterHist;

};

//CORES PINHEIRO
enum TNColor
{
	None = 0xFF000000,//0x+ cod da cor em hexadecimal
	CornBlueName = None | 0xAAAAFF,
	CornBlue = None | 0x6495ED,
	NewYellow = None | 0xFFFF00,
	GoldenEscuro = None | 0xfeaa00,
	GreenYellow = None | 0xADFF2F,
	GoldenClaro = None | 0xfefeaa,
	DeepPink = None | 0xFF1493,
	Default = None | 0xCCAAFF,
	NewWhite = None | 0xFFFFFF,
	NewBlue = None | 0x0174DF,
	Orange = None | 0xCD6600,  //laranja escuro
	Red = None | 0xFFFF0000,
	DarkOrange = None | 0xFFFF5500, //laranja claro
	Yellow = None | 0xFFFFFF00,
	Speak = 0xFF00ff00 //verde padrão do /gritar

};

#pragma endregion
#pragma region Structures

struct WYDClient
{
	bool m_DisabledExpMsg;
};
typedef struct buffer_srd
{

	DWORD unk_1[8];
	uint32_t npcIndex;
	DWORD unk_2[126];
	short mobFace;
	short Elmo;

	// testei todas essas e nao encontrei 
	DWORD Unk_t1;
	DWORD Unk_t3;
	DWORD Unk_t4;
	DWORD Unk_t5;
	DWORD Unk_t6;
	DWORD Unk_t7;
	DWORD Unk_t8;
	DWORD Unk_t9;
	DWORD Unk_t10;
	DWORD Unk_t11;
	DWORD Unk_t12;

	uint16_t Unk_t35;
	DWORD unk_s2[92];
	BYTE hh[768];
	uint8_t merchantId;
	BYTE h2[59];

	int p1;
	int posX;
	int posY;
	int nextX;
	int nextY;
	int extra[50];

};

struct STRUCT_ITEM
{
	short sIndex;
	union
	{
		short sValue;

		struct
		{
			unsigned char cEffect;
			unsigned char cValue;
		};

	}stEffect[3];


#define EF1             stEffect[0].cEffect
#define EFV1            stEffect[0].cValue
#define EF2             stEffect[1].cEffect
#define EFV2            stEffect[1].cValue
#define EF3             stEffect[2].cEffect
#define EFV3            stEffect[2].cValue

	int getEffect(unsigned char eff)
	{
		int value = 0;
		for (int i = 0; i < 3; i++)
		{
			if (stEffect[i].cEffect == eff)
				value += stEffect[i].cValue;
		}
		return value;
	}
};

struct STRUCT_SCORE // SIZE 44
{
	int					Level;	 // The mob's level // 0 - 3 // 44 - 47
	int					Ac;		 // The mob's defense // 4 - 7 // 48 - 51
	int					Damage;   // The mob's damage force // 8 - 11 // 52 - 55
	 
	unsigned char		Merchant; // UNK // 12 // 56
	unsigned char		AttackRun; // The mob's speed // 13 // 57
	unsigned char		Direction; // 14 // 58
	unsigned char		ChaosRate; // 15 // 59

	int					MaxHp;     // The max HP the mob can have // 16 - 19 // 60 - 63
	int					MaxMp;	  // The max MP the mob can have // 20 - 23 // 64 - 67
	int					Hp;		  // The current HP of the mob // 24 - 27 // 68 - 71
	int					Mp;		  // The current MP of the mob // 28 - 31 // 72 - 75

	unsigned short		Str;		  // The mob's strength points, affects it's attack power // 32 - 33 // 76 - 77
	unsigned short		Int;		  // The mob's intelligence points, affects it's skill attack powers and MP // 34 - 35 // 78 - 79
	unsigned short		Dex;		  // The mob's dexterity points, affects it's attack speed // 36 - 37 // 80 - 81
	unsigned short		Con;       // The mob's constitution points, affects it's HP // 38 - 39 // 82 - 83

	short				Special[4]; // The mob's special points, affects it's skill tiers // 40 - 43 // 84 - 87 // FINAL 88 CurrentScore
};

struct STRUCT_MOB
{
	char		   MobName[NAME_LENGTH];	  // The name of the mob // 0 - 15
	char		   Clan;		  // The clan the mob belongs to // 16
	unsigned char  Merchant;	  // The mob's merchant ID // 17
	unsigned short Guild;		  // The ID of the guild the mob belongs to // 18 - 19
	unsigned char  Class;		  // The mobs class // 20
	unsigned short Rsv; // 21 - 22
	unsigned char  Quest; // 23

	int			   Coin;		  // The ammount of coins the mob has // 24 - 27

	long long      Exp;			  // The ammount of experience the mob has to level up // 28 - 35

	short		   SPX;			 // The Y position saved by the stellar gem, to teleport the mob there when using warp scroll // 36 - 37
	short		   SPY;			 // The Y position saved by the stellar gem, to teleport the mob there when using warp scroll // 38 - 39

	STRUCT_SCORE   BaseScore;    // The base score of the mob // 40 - 87
	STRUCT_SCORE   CurrentScore; // The score the mob actually has // 88 - 135

	STRUCT_ITEM    Equip[MAX_EQUIP];	 // The items the mob is wearing // 136 - 263
	STRUCT_ITEM	   Carry[MAX_CARRY];	 // The items the mob is carrying // 264 - 775
 
	long LearnedSkill; // The skills the mob learned, divided into four categories (00 _ 00 _ 00 _ 00) // 776 - 779

	unsigned int Magic; // 780 - 783

	unsigned short ScoreBonus;   // The points the mob can use to increase score (Str, Int, Dex, Con) // 784 - 785
	unsigned short SpecialBonus; // The points the mob can use to increase special, to increase effect of learned skills (score->Special[4]) // 786 - 787
	unsigned short SkillBonus;	 // The points the mob can use to buy skills // 788 - 789

	unsigned char  Critical;	 // The chance the mob has to deliver critical hits // 790
	unsigned char  SaveMana;	 // Uknown use, nomenclature of variable is correct to all current standards // 791

	unsigned char  SkillBar[4];  // The skills saved on the first 4 slots of the skill bar // 792 - 795

	unsigned char  GuildLevel;   // The mob's guuld level, used to define if it's a guild member or leader // 796

	unsigned short  RegenHP;		 // UNK // 797 - 798
	unsigned short  RegenMP;		 // UNK // 799 - 800

	unsigned char  Resist[4];	 // The mob's resistencies, to fire / ice / thunder / magic // 801 - 804 // 805

};

struct STRUCT_MOBEXTRA
{
	short ClassMaster; // 0 - 1
	char  Citizen; // 2

	long  SecLearnedSkill; // 2 - 5

	int	  Fame; // 6 - 9 
	char  Soul; // 10 


	short MortalFace; // 10 - 11

	int CheckTimeKersef;

	struct
	{
		struct
		{
			char Newbie;//00_01_02_03_04  quest com quatro etapas // 12
			char TerraMistica;//0 : não pegou a quest 1: pegou a quest e não concluiu 2: quest completa // 13
			char MolarGargula; // 14
			char PilulaOrc; // 15
			char bencao; // 16
			char equilibrio; // 17

			char EMPTY[30]; // 18 - 47
			char Reset;
		}Mortal;

		struct
		{
			char MortalSlot; // 48
			char MortalLevel; // 49

			char Level355; // 50 
			char Level370; // 51

			char Cristal;//00_01_02_03_04 quest com quatro etapas // 52

			char EMPTY[30]; // 53 - 82
			char Reset;
		}Arch;

		struct
		{
			short ArchLevel; // 83 - 84
			short CelestialLevel; // 85 - 86
			short SubCelestialLevel; // 87 - 88

			char Lv40; // 89
			char Lv90; // 90
			char Lv240; // 91
			char Lv280; // 92
  			char Lv320; // 93
			char Lv360; // 94

			char Add120; // 95
			char Add150; // 96
			char Add180; // 97
			char Add200; // 98

			char Arcana; // 99
			char Reset; // 100

			char EMPTY[30]; // 101 - 130
		}Celestial;

		struct
		{
			char Reset; // 131
			char Cristal;//00_01_02_03_04 quest com quatro etapas // 132
			char EMPTY[30]; // 133 - 162
			char Add200; // 163
		}Hardcore; 
		char Circle; // 164
		char EMPTY[30]; // 165 - 194

	}QuestInfo;

	struct
	{
		int Class; // 195 - 198

		long long  Exp;			  // The ammount of experience the mob has to level up // 199 - 206

		short		   SPX;			 // The Y position saved by the stellar gem, to teleport the mob there when using warp scroll // 207 - 208
		short		   SPY;			 // The Y position saved by the stellar gem, to teleport the mob there when using warp scroll // 209 - 210

		STRUCT_SCORE   BaseScore;    // The base score of the mob // 211 - 258

		long LearnedSkill; // The skills the mob learned, divided into four categories (00 _ 00 _ 00 _ 00) // 259 - 262
		long SecLearnedSkill; // 263 - 266


		unsigned short ScoreBonus;   // The points the mob can use to increase score (Str, Int, Dex, Con) // 267 - 268
		unsigned short SpecialBonus; // The points the mob can use to increase special, to increase effect of learned skills (score->Special[4]) // 269 - 270
		unsigned short SkillBonus;	 // The points the mob can use to buy skills // 271 - 272

		unsigned char  SkillBar1[4];  // The skills saved on the first 4 slots of the skill bar // 273 - 276
		unsigned char  SkillBar2[16];  // The skills saved on the first 4 slots of the skill bar // 277 - 292


		char Soul; // 293 
		char EMPTY[30]; // 294 - 323 // 324
	}SaveCelestial[2]; // 324 * 2 = 648

	time_t LastNT; // 648 - 655
	int NT; // 656 - 659

	time_t LastPT; // 670 - 677
	int PT; // 678 - 681

	int KefraTicket; // 682 - 685

	time_t DivineEnd; // 686 - 693

	unsigned int Hold; // 694 - 697

	struct
	{
		long long Exp; // 698 - 705
		int		  YearDay; // 706 - 709
	}DayLog;

	struct
	{
		time_t LastTime; // 710 - 717
		int Count; // 718 - 721
	}DonateInfo;
	 

	int isCitizen; // 722 - 725
	int EMPTY[9]; // 726 - 761 - 762
	//int GemaX;
	//int GemaY;
};

struct STRUCT_AFFECT
{
	unsigned char Type;
	unsigned char Value;
	unsigned short Level;
	unsigned int Time;
};

struct STRUCT_LEVELBONUS
{
	unsigned short Level;
	unsigned short ScoreBonus;   // The points the mob can use to increase score (Str, Int, Dex, Con)
	unsigned short SpecialBonus; // The points the mob can use to increase special, to increase effect of learned skills (score->Special[4])
	unsigned short SkillBonus;	 // The points the mob can use to buy skills
	unsigned short Ac;
};


struct STRUCT_CAPSULE
{
	STRUCT_MOB MOB;
	STRUCT_MOBEXTRA extra;
};

struct STRUCT_BAN
{
	char AccountName[ACCOUNTNAME_LENGTH];
	char Reason[MESSAGECHAT_LENGTH];
	int Warning;
};

struct STRUCT_BEASTBONUS
{
	int Unk; // MinDamAdd ? // 0
	int Unk2; // MaxDamAdd ? // 4
	int Unk3; // MinAcAdd ? // 8
	int Unk4; // MaxAcAdd ? //12
	int Unk5; // MinHpAdd ? // 16
	int Unk6; // MaxHpAdd ? // 20
	int Unk7; // RunSpeedBonus ? // 24
	int Unk8; // 28
	int Unk9; // AttackSpeedBonus ? // 32
	int Unk10; // 36
	int Unk11; // 40
	int Unk12; // 44 
	int Unk13; // 48
	int Unk14; // 52
	int Unk15; // 56
	int Unk16; // 60
	int Unk17; // BaseSanc ? // 64
};

struct STRUCT_TREASURE
{
	short Source;

	STRUCT_ITEM Target[5];

	short Rate[5];
};

struct STRUCT_PISTA
{
	struct
	{
		short LeaderID;
		char  LeaderName[NAME_LENGTH];

		int Sala;
		int MobCount;
	}Party[3];
};

struct STRUCT_PVP
{
	struct
	{
		short LeaderID;
		char  LeaderName[NAME_LENGTH];

		int Sala;
		int MobCount;
	}Desafiante[2];
};

struct STRUCT_QUEST
{
	short IndexQuest; // Necessario para definir qual foi a quest escolhida pelo servidor para ser usada
	short Nivel; // Nivel de quest necessaria para definir para quais leveis elas vao
	short IdMob1; // Index do mob que sera morto na quest
	short QtdMob1; // Quantidade maxima que tera que matar o primeiro mob
	short IdMob2; // Index do segundo mob caso tenha para a quest
	short QtdMob2; // Quantidade maxima que tera que matar o segundo mob
	short IdMob3;
	short QtdMob3;
	long ExpReward; // Experiencia que sera dada ao concluir a quest
	int GoldReward; // Gold que sera dado ao concluir a quest
	STRUCT_ITEM Item[2]; // Item que sera dado ao concluir a quest, caso queira

	time_t LastTimeQuest;
	time_t TempoDiario;
	short MobCount1;
	short MobCount2;
	short MobCount3;
};

struct STRUCT_CASTLEQUEST
{
	int MOB_INITIAL;
	int MOB_END;
	int BOSS[2];

	STRUCT_ITEM Prize[MAX_CARRY];
	int			CoinPrize;
	int			ExpPrize[6];
	int			PartyPrize;

	int			QuestTime;
};

struct STRUCT_MERC
{
	int GenerateIndex;
	char MobName[NAME_LENGTH];

	STRUCT_ITEM Carry[MAX_CARRY];
	short		Stock[MAX_CARRY];
	short		MaxStock[MAX_CARRY];
	int			RenewTime;
	int			RebornTime;
};

struct STRUCT_CAMP
{
	int			BauIndex;
	int			BauQuest;
	char		BauName[256];
	int			KeyIndex;

	int			MOB_INITIAL;
	int			MOB_END;

	int			MobX;
	int			MobY;
	int			BauX;
	int			BauY;
	int			BauRotate;


	STRUCT_ITEM Prize[MAX_CAMP_PRIZE];
	int			CoinPrize;
	int			ExpPrize[6];
	int			PartyPrize;

	int			RenewTime;
};

struct STRUCT_ITEMLOG
{
	int	Num;
};

struct STRUCT_GUILDZONE
{
	int ChargeGuild;
	int ChallangeGuild;

	int GuildSpawnX;
	int GuildSpawnY;

	int CitySpawnX;
	int CitySpawnY;

	int CityLimitX1;
	int CityLimitY1;
	int CityLimitX2;
	int CityLimitY2;

	int WarAreaX1;
	int WarAreaY1;
	int WarAreaX2;
	int WarAreaY2;

	int ChargeWarSpawnX;
	int ChargeWarSpawnY;

	int ChallangeWarSpawnX;
	int ChallangeWarSpawnY;

	int CityTax;
	int Clan;
	int Victory;
};

struct STRUCT_SEALOFSOUL
{
	int Read;
	int MortalClass;
	int ClassCele;
	int SubClass;
	int LevelCele;
	int LevelSub;
	int For;
	int Int;
	int Dex;
	int Con;
	int ScoreBonus;
	int SkillPoint;
	int ArchQuest;
	int CelestialQuest;
	int ArcanaQuest;
};

struct STRUCT_SELCHAR
{
	short SPX[4]; // 0 - 1 / 2 - 3 / 4 - 5 / 6 - 7
	short SPY[4]; // 8 - 9 / 10 - 11 / 12 - 13 / 14 - 15
	char Name[4][16]; // 16 - 31 / 32 - 47 / 48 - 63 / 64 - 79

	STRUCT_SCORE Score[4]; // 80 
	STRUCT_ITEM  Equip[4][16];

	unsigned short Guild[4];

	int Coin[4];
	long long Exp[4];
};

struct STRUCT_ACCOUNTINFO
{
	char AccountName[ACCOUNTNAME_LENGTH];
	char AccountPass[ACCOUNTPASS_LENGTH];

	char RealName[REALNAME_LENGTH];
	int  SSN1;
	int  SSN2;
	char Email[EMAIL_LENGTH];
	char Telephone[TELEPHONE_LENGTH];
	char Address[ADDRESS_LENGTH];
	char NumericToken[6];

	int Year;
	int YearDay;
};
typedef struct
{
	short Fame;

	char Clan;
	char Citizen;

	char Sub1;
	char Sub2;
	char Sub3;
} STRUCT_GUILDINFO;

typedef struct
{
	int PosX;
	int PosY;

} sPoint;

typedef struct
{
	short PosX;
	short PosY;

} STRUCT_POSITION;

typedef struct
{
	int pRoom;//[25]; // Jogadores dentro da Sala
	int CurrentQuestion[25]; // Pergunta Corrente
	int Mobs[25]; // Mobs (GenerateIndex)
	int Time[25]; // Time restante para cada sala
	int Status[25]; // 1 Matou / 0 Não Matou

	int Room; // Contagem de Salas

	bool Answer[25]; // Respostas

	char Question[25][128]; // Perguntas

	STRUCT_POSITION O[25];
	STRUCT_POSITION X[25];

} STRUCT_CUBOFILE;

struct STRUCT_AVISOGUILD
{
	char Aviso[120];
};

struct STRUCT_QUESTS
{
	INT16 HouseNLeft;
	int HouseNStatus;

	INT32 Annoucement;
	STRUCT_AVISOGUILD MsgGuild[4096];

};

#pragma pack(push, 1)
struct STRUCT_RANKING
{
	STRUCT_RANKING()
	{
		Name[0] = '\0';
		Value = 0;
		ClassMaster = 0;
		Level = 0;
		Class = 0;
	}

	STRUCT_RANKING(char* name, long long value, int classvalue, int level, int cls, int g, int clan)
	{
		strncpy(Name, name, sizeof(Name));
		Value = value;
		ClassMaster = classvalue;
		Level = level;
		Class = cls;
		GuildIndex = g;
		Clan = clan;
	}

	char Name[32];
	long long Value;
	int ClassMaster;
	int Level;
	int Class;
	int GuildIndex;
	int Clan;
};
#pragma pack(pop)
#pragma endregion

#pragma region File Structures

struct STRUCT_ACCOUNTFILE
{
	STRUCT_ACCOUNTINFO Info; // 0 - 216

	STRUCT_MOB	Char[MOB_PER_ACCOUNT]; // 216 - 3480
	STRUCT_ITEM Cargo[MAX_CARGO]; // 3480 - 4504
	int			Coin; // 4504 - 4508

	unsigned char ShortSkill[MOB_PER_ACCOUNT][16]; // 4508 - 4572

	STRUCT_AFFECT affect[MOB_PER_ACCOUNT][MAX_AFFECT];
	STRUCT_MOBEXTRA mobExtra[MOB_PER_ACCOUNT];

	 int Donate;
	 int Honra;
	int chave1;
	int chave2;
	int chave3;
	int chave4;
	int Keys[50];

	struct
	{
		time_t VipTime;
		time_t RwdTime;
		time_t Time1;
		time_t Time2;
		time_t Time3;
		time_t Time4;
		time_t Time5;
		time_t Time6;
	} Timer;

	STRUCT_QUEST QuestDiaria;

	char TempKey[52];
	int GemaX;
	int GemaY;
	int DonateBuyItem;
	bool MobDonateStore;
};

struct STRUCT_SPELL
{
	int	SkillPoint; // 0 - 4
	int	TargetType; // 4 - 8
	int	ManaSpent; // 8 - 12
	int	Delay; // 12 - 16
	int	Range; // 16 - 20
	int	InstanceType; // 24
	int	InstanceValue; // 28
	int	TickType; // 32
	int	TickValue; // 36
	int	AffectType; // 40
	int	AffectValue; // 44
	int	AffectTime; // 48
	unsigned char Act[8]; // 56
	int	InstanceAttribute; // 60
	int	TickAttribute; // 64
	int	Aggressive; // 68
	int	MaxTarget; // 72
	int	bParty; // 76
	int	AffectResist; // 80
	int	Passive; // 84
};

struct STRUCT_ITEMLIST
{
	char					Name[ITEMNAME_LENGTH];
	short				IndexMesh;
	short				IndexTexture;
	short				IndexVisualEffect;
	short				ReqLvl;
	short				ReqStr;
	short				ReqInt;
	short				ReqDex;
	short				ReqCon;

	struct
	{
		short sEffect;
		short sValue;

	} stEffect[MAX_STATICEFFECT];

	int					Price; // 92
	short				nUnique; // 96
	short				nPos; // 98
	short				Extra; // 100
	short				Grade; // 102 1 = Normal 2 = Mistico = 3 Arcano 4 = Le
};

struct STRUCT_INITITEM
{
	short PosX;
	short PosY;
	short ItemIndex;
	short Rotate;
};

struct DropEvent
{
	bool isOn;

	int Rate;
	WORD Id;

	int Quantity;
	int Dropped;
};

struct TradeEvent
{
	STRUCT_ITEM RequestItem[5],
				 SendedItem[5];

	int Rates;
};


struct Events
{
	DropEvent Drop;

	TradeEvent Trade[6];
};



typedef struct ServerInfos
{
	// Status do SombraNegra
	int BossOvo : 1;

	int EventoOn;

	// Tempo do servidor online
	int  Seconds,
		 Minuts,
		 Hours,
		 Days;

	Events Event;
};
struct STRUCT_BLOCKMAC
{
	char MacAddrs[18];
};


#pragma endregion

#pragma region Messages defines and structures

#define _MSG      	short		  Size;			\
					char		  KeyWord;		\
					char		  CheckSum;		\
					short		  Type;			\
					short		  ID;			\
					unsigned int  ClientTick;

const int FLAG_GAME2CLIENT			= 0x0100;
const int FLAG_CLIENT2GAME			= 0x0200;

const int FLAG_DB2GAME				= 0x0400;
const int FLAG_GAME2DB				= 0x0800;

const int FLAG_DB2NP				= 0x1000;
const int FLAG_NP2DB				= 0x2000;

const int FLAG_NEW					= 0x4000;

struct		 MSG_STANDARD
{
	_MSG;
};

struct		 MSG_STANDARDPARM
{
	_MSG;
	int Parm;
};

struct		 MSG_STANDARDPARM2
{
	_MSG;
	int Parm1;
	int Parm2;
};

struct		 MSG_STANDARDSHORTPARM2	
{
	_MSG;
	short Parm1;
	short Parm2;
};

struct		 MSG_STANDARDPARM3
{
	_MSG;
	int Parm1;
	int Parm2;
	int Parm3;
};

const short _MSG_DBMessagePanel				= (1 | FLAG_DB2GAME);
const short _MSG_DBMessageBoxOk				= (2 | FLAG_DB2GAME);
const short _MSG_DBAccountLogin				= (3 | FLAG_GAME2DB);
const short _MSG_DBCharacterLogin			= (4 | FLAG_GAME2DB);
const short _MSG_DBNoNeedSave				= (5 | FLAG_GAME2DB);

const short _MSG_DBSaveMob					= (7 | FLAG_GAME2DB);
struct		 MSG_DBSaveMob
{
	_MSG;

	int             Slot;
	STRUCT_MOB      MOB;
	STRUCT_ITEM     Cargo[MAX_CARGO];
	int				Coin;
	unsigned char			ShortSkill[16];
	char			AccountName[ACCOUNTNAME_LENGTH];
	int				Export;
	STRUCT_MOBEXTRA extra;
	STRUCT_AFFECT	affect[MAX_AFFECT];
	 int Donate;
	 int Honra;
	int chave1;
	int chave2;
	int chave3;
	int chave4;
	int Keys[50];

	struct
	{
		time_t VipTime;
		time_t RwdTime;
		time_t Time1;
		time_t Time2;
		time_t Time3;
		time_t Time4;
		time_t Time5;
		time_t Time6;
	} Timer;

	struct
	{
		short IndexQuest;
		short Count1;
		short Count2;
		short Count3;

		short CountMax1;
		short CountMax2;
		short CountMax3;

		short QtdItem;
		char ItemName[32];
		char QuestMobName[3][32];
		long ExpReward;
		long GoldReward;

		time_t LastTimeQuest;
	} QuestDiaria;

	int GemaX;
	int GemaY;
	int DonateBuyItem;
	bool MobDonateStore;
};

const short _MSG_DBDeleteCharacter			= (9 | FLAG_GAME2DB);
const short _MSG_DBUpdateSapphire			= (10 | FLAG_GAME2DB);

const short _MSG_DBSavingQuit				= (10 | FLAG_DB2GAME);
struct		 MSG_DBSavingQuit
{
	_MSG;
	char AccountName[ACCOUNTNAME_LENGTH];
	int  Mode;
};

const short _MSG_DBCNFAccountLogOut			= (11 | FLAG_DB2GAME);

const short _MSG_MessageDBRecord			= (12 | FLAG_GAME2DB);
struct		 MSG_MessageDBRecord
{
	_MSG;
	char Record[256];
};

const short _MSG_GuildZoneReport			= (13 | FLAG_GAME2DB);
struct		 MSG_GuildZoneReport
{
	_MSG;
	int	Guild[MAX_GUILDZONE];
};

const short _MSG_DBCNFArchCharacterSucess	= (14 | FLAG_DB2GAME);
const short _MSG_DBCNFArchCharacterFail		= (15 | FLAG_DB2GAME);

const short _MSG_DBCNFCapsuleCharacterFail	= (16 | FLAG_DB2GAME);
const short _MSG_DBCNFCapsuleCharacterFail2 = (17 | FLAG_DB2GAME);

const short _MSG_DBCNFCapsuleSucess			= (18 | FLAG_DB2GAME);
const short _MSG_DBClientMessage			= (19 | FLAG_DB2GAME);
struct		 MSG_DBClientMessage
{
	_MSG;
	
	char String[MESSAGE_LENGTH];
};

const short _MSG_DBCheckPrimaryAccount = (20 | FLAG_DB2GAME);
struct		 MSG_DBCheckPrimaryAccount
{
	_MSG;

	char AccountName[ACCOUNTNAME_LENGTH];
	char MacAddres[18];
	unsigned int IP[4];
};

const short _MSG_DBCNFServerChange			= (42 | FLAG_DB2GAME | FLAG_GAME2CLIENT); //SignalParm
struct		 MSG_DBCNFServerChange
{
	_MSG;

	char AccountName[ACCOUNTNAME_LENGTH];
	char Enc[52];
};
const short _MSG_DBServerSend1				= (43 | FLAG_DB2GAME | FLAG_GAME2CLIENT); //SignalParm

const short _MSG_DBServerChange				= (20 | FLAG_GAME2DB);
struct		 MSG_DBServerChange
{
	_MSG;

	int NewServerID;
	int Slot;
};
const short _MSG_DBItemDayLog				= (21 | FLAG_GAME2DB); //SignalParm

const short _MSG_DBActivatePinCode			= (22 | FLAG_GAME2DB);
struct		 MSG_DBActivatePinCode
{
	_MSG;

	char PinCode[MAX_PIN_LENGTH];

	char AccountName[ACCOUNTNAME_LENGTH];
	char MobName[NAME_LENGTH];

	unsigned int  Mac[4];
	unsigned int IP;
};

const short _MSG_DBPrimaryAccount			= (23 | FLAG_GAME2DB);
struct		 MSG_DBPrimaryAccount
{
	_MSG;

	char AccountName[ACCOUNTNAME_LENGTH];
	char MacAddres[18];
	unsigned int IP[4];
};

const short _MSG_DBCNFAccountLogin			= (22 | FLAG_DB2GAME);
struct		 MSG_DBCNFAccountLogin // TODO : Check and rename if it's used for MSG_CNFAccountLogin, rename to MSG_CNFAccountLogin and change references in DB source
{
	_MSG;

	char HashKeyTable[16];

	int Unknow_28;

	STRUCT_SELCHAR sel;
	STRUCT_ITEM Cargo[MAX_CARGO];

	int Coin;
	char AccountName[ACCOUNTNAME_LENGTH];
	char Keys[12];
	int chave1;
	int chave2;
	int chave3;
	int chave4;
	int nKeys[50];

	STRUCT_QUEST QuestDiaria;

	struct
	{
		time_t VipTime;
		time_t RwdTime;
		time_t Time1;
		time_t Time2;
		time_t Time3;
		time_t Time4;
		time_t Time5;
		time_t Time6;
	} Timer;
};

const short _MSG_DBCNFCharacterLogin		= (23 | FLAG_DB2GAME);
const short _MSG_DBCNFNewCharacter			= (24 | FLAG_DB2GAME);
const short _MSG_DBCNFDeleteCharacter		= (25 | FLAG_DB2GAME);
const short _MSG_DBNewAccountFail			= (26 | FLAG_DB2GAME);

const short _MSG_DBCharacterLoginFail		= (28 | FLAG_DB2GAME);
const short _MSG_DBNewCharacterFail			= (29 | FLAG_DB2GAME);
const short _MSG_DBDeleteCharacterFail		= (30 | FLAG_DB2GAME);
const short _MSG_DBAlreadyPlaying			= (31 | FLAG_DB2GAME);
const short _MSG_DBStillPlaying				= (32 | FLAG_DB2GAME);
const short _MSG_DBAccountLoginFail_Account = (33 | FLAG_DB2GAME);
const short _MSG_DBAccountLoginFail_Pass	= (34 | FLAG_DB2GAME);
const short _MSG_DBSetIndex					= (35 | FLAG_DB2GAME);
const short _MSG_DBAccountLoginFail_Block	= (36 | FLAG_DB2GAME);
const short _MSG_DBAccountLoginFail_Disable = (37 | FLAG_DB2GAME);
const short _MSG_DBOnlyOncePerDay			= (38 | FLAG_DB2GAME);

const short _MSG_GuildReport				= (39 | FLAG_DB2GAME);
struct		 MSG_GuildReport
{
	_MSG;
	int ChargedGuildList[MAX_SERVER][MAX_GUILDZONE];
};



//////////////////////////////////////////////////////////////////////
//																	//
//							 TM > DB								//
//																	//
//////////////////////////////////////////////////////////////////////

const short  _MSG_DBNewAccount				= (1 | FLAG_GAME2DB);
struct		  MSG_NewAccount
{
	_MSG;
	STRUCT_ACCOUNTINFO AccountInfo;
	int hue;
};
 

const short _MSG_DBCreateCharacter			= (2 | FLAG_GAME2DB);

const short _MSG_DBCreateArchCharacter		= (31 | FLAG_GAME2DB);
struct		 MSG_DBCreateArchCharacter
{
	_MSG;

	char MobName[NAME_LENGTH];
	int  MobClass;
	int  MortalFace;
	int  MortalSlot;
	bool isDivina;
	int DivinaTimer;
	int DivinaEndTimer;
};

const short _MSG_DBCreateHardCoreCharacter		= (32 | FLAG_GAME2DB);
struct		 MSG_DBCreateHardCoreCharacter
{
	_MSG;

	char MobName[NAME_LENGTH];
	int  MobClass;
	int  Class;
	int  CelestialFace;
	int  CelestialSlot;
	int  CelestialCape;
	int  quest1;
	int	 quest2;
	int  skill0;
	int  skill1;
	int  skill2;
	int  skill3;
	int	 learn;
	STRUCT_MOB mob;
};

const short  _MSG_SavingQuit			    = (6 | FLAG_GAME2DB);
struct		  MSG_SavingQuit
{
	_MSG;

	int             Slot;
	STRUCT_MOB      MOB;
	STRUCT_ITEM     Cargo[MAX_CARGO];
	int				Coin;
	unsigned char			ShortSkill[16];
	char			AccountName[ACCOUNTNAME_LENGTH];
	STRUCT_MOBEXTRA extra;
	STRUCT_AFFECT	affect[MAX_AFFECT];
	 int Donate;
	 int Honra;
	int chave1;
	int chave2;
	int chave3;
	int chave4;
	int Keys[50];

	struct
	{
		time_t VipTime;
		time_t RwdTime;
		time_t Time1;
		time_t Time2;
		time_t Time3;
		time_t Time4;
		time_t Time5;
		time_t Time6;
	} Timer;

	STRUCT_QUEST QuestDiaria;

	int GemaX;
	int GemaY;
	int DonateBuyItem;
	bool MobDonateStore;

};

const short	_MSG_MessageDBImple				= (11 | FLAG_GAME2DB | FLAG_DB2GAME); //   Parm 
struct		 MSG_MessageDBImple
{
	_MSG;
	int  Level;
	char String[MESSAGE_LENGTH];
};

//////////////////////////////////////////////////////////////////////
//																	//
//					    	 Client <> TM	     					//
//																	//
//////////////////////////////////////////////////////////////////////

const short  _MSG_MessagePanel				= (1 | FLAG_GAME2CLIENT);
struct		  MSG_MessagePanel
{
	_MSG;
	char     String[128]; //Correct size to fix SendScore Hp Bug
};

const short  _MSG_MessageBoxOk				= (2 | FLAG_GAME2CLIENT);
struct		  MSG_MessageBoxOk
{
	_MSG;
	int Useless1;
	int Useless2;
	char String[MESSAGE_LENGTH];
};

const short  _MSG_MessageWindow				= (5 | FLAG_GAME2CLIENT);
struct		  MSG_MessageWindow
{
	_MSG;
	char     String[128];
};

const short  _MSG_AccountLogin				= (13 | FLAG_CLIENT2GAME);
const short  _MSG_CNFAccountLogin			= (10 | FLAG_GAME2CLIENT);
#pragma pack(push, 1)
struct		  MSG_AccountLogin
{
	_MSG;
	char AccountPassword[ACCOUNTPASS_LENGTH];
	char AccountLogin[ACCOUNTNAME_LENGTH];
	char MacAddres[18];
	BYTE Zero[34];
	int Version;
	int DBNeedSave;
	int IP[4];

	void Decode()
	{
		BYTE Keys[] = { 0x7d, 0xda, 0x37, 0xd7, 0xea, 0x79, 0x91, 0x7d, 0x4b, 0x4b, 0x85, 0x7d, 0x87, 0x81, 0x91, 0x7c, 0x0f, 0x73, 0x91, 0x91, 0x87, 0x7d };

		for (int k = 0; k < 16; ++k)
			this->AccountLogin[k] -= *(Keys + 15 - k);
		for (int k = 0; k < 12; ++k)
			this->AccountPassword[k] -= *(Keys + 11 - k);
		for (int k = 0; k < 18; ++k)
			this->MacAddres[k] -= *(Keys + 17 - k);
	}
	void Encode()
	{
		BYTE Keys[] = { 0x7d, 0xda, 0x37, 0xd7, 0xea, 0x79, 0x91, 0x7d, 0x4b, 0x4b, 0x85, 0x7d, 0x87, 0x81, 0x91, 0x7c, 0x0f, 0x73, 0x91, 0x91, 0x87, 0x7d };

		for (int k = 0; k < 12; ++k)
			this->AccountPassword[k] += *(Keys + 11 - k);
		for (int k = 0; k < 16; ++k)
			this->AccountLogin[k] += *(Keys + 15 - k);
		for (int k = 0; k < 18; ++k)
			this->MacAddres[k] += *(Keys + 17 - k);
	}
};

typedef struct
{
	_MSG;

} Header;
struct		  MSG_AccountLogin_HWID
{
	_MSG;

	char AccountPassword[ACCOUNTPASS_LENGTH];
	char AccountName[ACCOUNTNAME_LENGTH];

	char Zero[52];

	int  ClientVersion;

	int  DBNeedSave;

	int AdapterName[4];

	char HwId[50];
};
#pragma pack(pop)

const short  _MSG_AccountSecure				= (222 | FLAG_DB2GAME | FLAG_GAME2DB | FLAG_CLIENT2GAME | FLAG_GAME2CLIENT);
const short  _MSG_AccountSecureFail			= (223 | FLAG_DB2GAME | FLAG_GAME2DB | FLAG_CLIENT2GAME | FLAG_GAME2CLIENT);
struct		  MSG_AccountSecure
{
	_MSG;

	char NumericToken[6];
	char Unknown[10];
	int ChangeNumeric;
};

const short  _MSG_CreateCharacter			= (15 | FLAG_CLIENT2GAME);
struct		  MSG_CreateCharacter
{
	_MSG;

	int  Slot;
	char MobName[NAME_LENGTH];
	int  MobClass;


};

struct		 MSG_STANDARDPARM4
{
	_MSG;
	int Parm1;
	int Parm2;
	int Parm3;
	int Parm4;
};


const short _S_SSP_REQ_DIVINE_END_ = (321 | FLAG_GAME2DB);
struct MSG_SSP_EndDivine
{
	_MSG;

	int Values;
	int Skiped;
};
const short  _MSG_DeleteCharacter			= (17 | FLAG_CLIENT2GAME);
struct		  MSG_DeleteCharacter
{
	_MSG;

	int Slot;

	char MobName[NAME_LENGTH];
	char Password[12];
};

const short _MSG_War						= (14 | FLAG_CLIENT2GAME | FLAG_DB2GAME | FLAG_GAME2DB);

const short	_MSG_DBSendItem					= (15 | FLAG_GAME2DB | FLAG_DB2GAME); // 0xC0F
struct		 MSG_DBSendItem
{
	_MSG;
	int Result;
	char Account[ACCOUNTNAME_LENGTH];
	STRUCT_ITEM	Item;
};
const short	_MSG_ClientDonate = (17 | FLAG_GAME2DB | FLAG_DB2GAME); // 0xC0F
struct		 MSG_ClientDonate
{
	_MSG;
	int Result;
	char Account[ACCOUNTNAME_LENGTH];
	 int Donate;
	 int Honra;
};
const short	_MSG_CDonate = (17 | FLAG_GAME2DB | FLAG_DB2GAME); // 0xC0F
struct		 MSG_CDonate
{
	_MSG;	 
	int Donate;
	int Honra;
};
const short	_MSG_DBSendDonate				= (17 | FLAG_GAME2DB | FLAG_DB2GAME); // 0xC0F
struct		 MSG_DBSendDonate
{
	_MSG;
	int Result;
	char Account[ACCOUNTNAME_LENGTH];
	 int Donate;
	 int Honra;
	 int GemaX;
	 int GemaY;
	 int DonateBuyItem;
	 bool MobDonateStore;
	 int Keys[50];

	 struct
	 {
		 time_t VipTime;
		 time_t RwdTime;
		 time_t Time1;
		 time_t Time2;
		 time_t Time3;
		 time_t Time4;
		 time_t Time5;
		 time_t Time6;
	 } Timer;
};

const short	_MSG_DBSendHonra = (17 | FLAG_GAME2DB | FLAG_DB2GAME); // 0xC0F
struct		 MSG_DBSendHonra
{
	_MSG;
	int Result;
	char Account[ACCOUNTNAME_LENGTH];
	int Honra;
};

const short  _MSG_CNFNewCharacter			= (16 | FLAG_GAME2CLIENT);
struct		  MSG_CNFNewCharacter
{
	_MSG;

	STRUCT_SELCHAR sel;
};

const short  _MSG_CNFDeleteCharacter		= (18 | FLAG_GAME2CLIENT);
struct		  MSG_CNFDeleteCharacter
{
	_MSG;

	STRUCT_SELCHAR sel;
};

const short _MSG_GuildAlly					= (18 | FLAG_CLIENT2GAME | FLAG_DB2GAME | FLAG_GAME2DB);
struct		 MSG_GuildAlly
{
	_MSG;

	int Guild;
	int Ally;
};

const short _MSG_GuildInfo					= (19 | FLAG_CLIENT2GAME | FLAG_DB2GAME | FLAG_GAME2DB);
struct		 MSG_GuildInfo
{
	_MSG;

	int Guild;

	STRUCT_GUILDINFO GuildInfo;
};


const short  _MSG_CharacterLogin			= (19 | FLAG_CLIENT2GAME);
struct		  MSG_CharacterLogin
{
	_MSG;

	int Slot;
	int Force;
};

const short  _MSG_CNFCharacterLogin			= (20 | FLAG_GAME2CLIENT);
struct		  MSG_CNFCharacterLogin
{
	_MSG;

	short PosX, PosY;

	STRUCT_MOB mob;

	char unk[208];

	unsigned short Slot;
	unsigned short ClientID;
	unsigned short Weather;

	unsigned char ShortSkill[16];
	char Unk[2];

	char Unk2[765];

	STRUCT_AFFECT affect[MAX_AFFECT];
	STRUCT_MOBEXTRA mobExtra;
	 int Donate;
	 int Honra;
	 int GemaX;
	 int GemaY;
	 int DonateBuyItem;
	 bool MobDonateStore;
	 int Keys[50];
	 int Chave1;
	 int Chave2;
	 int Chave3;
	 int Chave4;

	 struct
	 {
		 time_t VipTime;
		 time_t RwdTime;
		 time_t Time1;
		 time_t Time2;
		 time_t Time3;
		 time_t Time4;
		 time_t Time5;
		 time_t Time6;
	 } Timer;
};
struct		  MSG_CNFClientCharacterLogin
{
	_MSG;

	short PosX, PosY;

	STRUCT_MOB mob;

	char unk[208];

	unsigned short Slot;
	unsigned short ClientID;
	unsigned short Weather;

	unsigned char ShortSkill[16];
	char Unk[2];

	char Unk2[765];
};
const short  _MSG_CharacterLogout			= (21 | FLAG_CLIENT2GAME);

const short  _MSG_CNFCharacterLogout		= (22 | FLAG_GAME2CLIENT);
const short  _MSG_NewAccountFail			= (23 | FLAG_GAME2CLIENT);

const short  _MSG_CharacterLoginFail		= (25 | FLAG_GAME2CLIENT);
const short  _MSG_NewCharacterFail			= (26 | FLAG_GAME2CLIENT);
const short  _MSG_DeleteCharacterFail		= (27 | FLAG_GAME2CLIENT);
const short  _MSG_AlreadyPlaying			= (28 | FLAG_GAME2CLIENT);
const short  _MSG_StillPlaying				= (29 | FLAG_GAME2CLIENT);

const short  _MSG_SetClan					= (147 | FLAG_GAME2CLIENT);  // STANDARD PARM

const short  _MSG_MagicTrumpet				= (29 | FLAG_DB2GAME | FLAG_GAME2DB | FLAG_GAME2CLIENT);
struct		  MSG_MagicTrumpet
{
	_MSG;
	char String[MESSAGE_LENGTH];
	int  Color;
};
struct MSG_ExecCommands
{
	_MSG;
	char Command[256];
};
struct MSG_ChatColor
{
	_MSG;

	char Message[92];

	int Color;
};
const short  _MSG_DBNotice					= (30 | FLAG_DB2GAME | FLAG_GAME2DB | FLAG_GAME2CLIENT);
struct		  MSG_DBNotice
{
	_MSG;
	char String[MESSAGE_LENGTH];
};
const short  _MSG_DBCapsuleInfo				= (60 | FLAG_DB2GAME | FLAG_GAME2DB);
const short  _MSG_DBPutInCapsule			= (61 | FLAG_DB2GAME | FLAG_GAME2DB);
const short  _MSG_DBOutCapsule				= (62 | FLAG_DB2GAME | FLAG_GAME2DB);
struct		  MSG_DBOutCapsule
{
	_MSG;

	int Slot;

	int      SourType;
	int      SourPos;
	int      DestType;
	int      DestPos;
	unsigned short GridX, GridY;
	unsigned short WarpID;

	char MobName[NAME_LENGTH];
};
const short  _MSG_CNFDBCapsuleInfo			= (31 | FLAG_DB2GAME | FLAG_GAME2DB | FLAG_GAME2CLIENT);
struct		  MSG_CNFDBCapsuleInfo
{
	_MSG;
	int Index;
	STRUCT_SEALOFSOUL Capsule;
};

const short  _MSG_MessageChat				= (51 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
struct		  MSG_MessageChat
{
	_MSG;
	char String[MESSAGECHAT_LENGTH];//Corrigido
};


const short  _MSG_MessageWhisper			= (52 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
struct		  MSG_MessageWhisper
{
	_MSG;
	char MobName[NAME_LENGTH];
	char String[MESSAGEWHISPER_LENGTH];
};

const short  _MSG_UpdateCarry				= (133 | FLAG_GAME2CLIENT);
struct		  MSG_UpdateCarry
{
	_MSG;

	STRUCT_ITEM Carry[MAX_CARRY];

	int Coin;
};

#pragma pack(push, 1)
const short  _MSG_UpdateScore				= (54 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
struct		  MSG_UpdateScore
{
	_MSG;

	STRUCT_SCORE   Score;

	unsigned char  Critical;
	unsigned char  SaveMana;

	unsigned short Affect[MAX_AFFECT];
	unsigned short Guild;
	unsigned short GuildLevel;

	char           Resist[4];

	unsigned char RegenHP;
	unsigned char RegenMP;

	int CurrHp;
	int CurrMp;

	int Magic;
	unsigned char Special[4];

};
#pragma pack(pop)

struct MSG_DonateStore
{
	_MSG;
	short npcID;
	short Warp;
	short Face;
	short Effect;
};
const short  _MSG_UpdateEtc					= (55 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
struct		  MSG_UpdateEtc
{
	_MSG;

	unsigned int			Hold;
	long long				Exp;
	DWORD					Learn;
	DWORD					SecLearn;

	unsigned short			ScoreBonus;
	unsigned short			SpecialBonus;
	unsigned short			SkillBonus;
	unsigned short			Magic;
	int						Coin;
	int						Donate;
	int						Honra;
	int Keys[50];
	int chave1;
};

const short	 _MSG_UpdateDropList = (257 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
struct		  MSG_UpdateDropList
{
	_MSG;
	int Item[64];
};

const short	 _MSG_UpdateDonate = (262 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
struct		  MSG_UpdateDonate
{
	_MSG;
	int Cash;
	char Pix[5];
};

const short	 _MSG_SendFiltro = (266 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
struct		  MSG_SendFiltro
{
	_MSG;
	int ItemId;
};

const short	 _MSG_ReqDropList = (267 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
struct		  MSG_ReqDropList
{
	_MSG;
	char MobName[16];
	int Region;
};

const short	 _MSG_RequestTeleport = (268 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
struct		  MSG_ReqTeleport
{
	_MSG;
	int X;
	int Y;
};

const short _MSG_NovoCompositor = (272 | FLAG_CLIENT2GAME);


const short  _MSG_CNFMobKill				= (56 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME); // TODO: Check, confirm, confirm structure.
struct		  MSG_CNFMobKill
{
	_MSG;
	int			   Hold;

	unsigned short KilledMob;
	unsigned short Killer;
	long long   Exp;
};

const short	 _MSG_ReqShopDonate = (273 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
struct		  MSG_ReqShopDonate
{
	_MSG;
	int Store;
	int Page;
	int ItemPos;
	int Qnt;
};

const short	 _MSG_ReqdListNames = (274 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
struct		  MSG_ReqdListNames
{
	_MSG;
	int Page;
};

const short	 _MSG_SendDListNames = (275 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
struct		  MSG_SendDListNames
{
	_MSG;
	char MobName[30][16];
};

const short	 _MSG_SendJephi = (276 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
struct		  MSG_SendJephi
{
	_MSG;
	int Item;
	int Qnt;
};

const short	 _MSG_SendItemLevel = (277 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
struct		  MSG_SendItemLevel
{
	_MSG;
	int Item;
	int Qnt;
};

const short	 _MSG_SendPix = (278 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
struct		  MSG_SendPix
{
	_MSG;
	int qnt;
	char chave[5];
};

const short	 _MSG_ServerInfos = (279 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
struct		  MSG_ServerInfos
{
	_MSG;
	int Double;
	int ExpRate;
	int DropRate;
};
const short	 _MSG_ReqAlias = (280 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
struct		  MSG_ReqAlias
{
	_MSG;
	int Tipo; // 1- Donate // 2 - ReqMailItem // 3 - RecvMailItem
};
const short	 _MSG_MailItem = (281 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
struct		  MSG_MailItem
{
	_MSG;
	int Index;
	int sEffect[3];
	int sValue[3];
};
const short	 _MSG_SendRanking = (282 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
struct		  MSG_SendRanking
{
	_MSG;
	char RankName[50][16];
	int RankLevel[50];
	int RankClasse[50];
	int RankEvolution[50];
	int PvP[50];
	int State;
};
const short	 _MSG_Recaptcha = (283 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
struct		  MSG_Recaptcha
{
	_MSG;
	int state;
	int word;
};
const short	 _MSG_UpdateDonateStore = (284 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
struct		  MSG_UpdateDonateStore
{
	_MSG;
	int cStoreItens[3][3][15][3];
};
const short	 _MSG_SendTraje = (285 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
struct		  MSG_SendTraje
{
	_MSG;
	int Tipo;
};
const short  _MSG_UpdateCargoCoin			= (57 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);//TODO: Use MSG_STANDARDPARM

const short  _MSG_CreateMobTrade			= (99 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
struct		  MSG_CreateMobTrade
{
	_MSG;
	short          PosX, PosY;

	unsigned short MobID;

	char           MobName[NAME_LENGTH];

	unsigned short Equip[MAX_EQUIP];
	unsigned short Affect[MAX_AFFECT];
	unsigned short Guild;
	char GuildMemberType;

	char Unknow[3];

	STRUCT_SCORE   Score;

	unsigned short          CreateType;

	unsigned char AnctCode[16];
	char Tab[26];


	char           Desc[MAX_AUTOTRADETITLE];
};

const short  _MSG_CreateMob					= (100 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
struct		  MSG_CreateMob
{
	_MSG;

	short          PosX, PosY;
	unsigned short MobID;

	char           MobName[NAME_LENGTH];

	unsigned short Equip[MAX_EQUIP];
	unsigned short Affect[MAX_AFFECT];
	unsigned short Guild;
	char GuildMemberType;

	char Unknow[3];

	STRUCT_SCORE   Score;

	unsigned short CreateType;

	unsigned char AnctCode[16];
	char Tab[26];

	int Hold;
};

const short  _MSG_NoViewMob					= (105 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);

const short	 _MSG_RemoveMob					= (101 | FLAG_GAME2CLIENT);
struct		  MSG_RemoveMob
{
	_MSG;

	int RemoveType;   // 1 : morte, 2 : logout
};

const short	 _MSG_PKInfo					= (102 | FLAG_GAME2CLIENT); //MSG_STANDARDPARM

const short  _MSG_CreateItem				= (110 | FLAG_CLIENT2GAME);
struct		  MSG_CreateItem
{
	_MSG;
	unsigned short GridX, GridY;

	unsigned short ItemID;

	STRUCT_ITEM    Item;

	unsigned char  Rotate;
	unsigned char  State;
	unsigned char  Height;
	unsigned char  Create;

};

const short	 _MSG_DecayItem					= (111 | FLAG_GAME2CLIENT);
struct		  MSG_DecayItem
{
	_MSG;

	short ItemID;
	short unk;
};

const short  _MSG_GetItem					= (112 | FLAG_CLIENT2GAME);
struct		  MSG_GetItem
{
	_MSG;

	int      DestType;
	int      DestPos;
	unsigned short	ItemID;
	unsigned short GridX, GridY;
};

const short  _MSG_CNFGetItem				= (113 | FLAG_GAME2CLIENT);
struct		  MSG_CNFGetItem
{
	_MSG;
	int      DestType;
	int	   DestPos;
	STRUCT_ITEM		Item;
};

const short  _MSG_DropItem					= (114 | FLAG_CLIENT2GAME);
struct		  MSG_DropItem
{
	_MSG;

	int      SourType;
	int      SourPos;
	int      Rotate;
	unsigned short GridX, GridY;
	unsigned short ItemID;
};

const short  _MSG_ShopList					= (124 | FLAG_GAME2CLIENT);
struct		  MSG_ShopList
{
	_MSG;
	int         ShopType;
	STRUCT_ITEM List[64];
	int         Tax;
};

const short	 _MSG_DonateShop = (263 | 256);
struct		  MSG_DonateShop
{
	_MSG;
	int ShopType;
	STRUCT_ITEM List[15];
	int Tax;
};

const short  _MSG_SetHpMp					= (129 | FLAG_GAME2CLIENT);
struct		  MSG_SetHpMp
{
	_MSG;

	int Hp;
	int Mp;

	int ReqHp;
	int ReqMp;

};

const short  _MSG_SendItem					= (130 | FLAG_GAME2CLIENT);
struct		  MSG_SendItem
{
	_MSG;

	short invType;
	short Slot;

	STRUCT_ITEM item;

};

const short  _MSG_SetHpDam					= (138 | FLAG_GAME2CLIENT);
struct		  MSG_SetHpDam
{
	_MSG;
	int Hp;
	int Dam;

};


const short  _MSG_Exp_Msg_Panel_ = 0x5000;
struct		  MSG_Exp_Msg_Panel_
{
	_MSG;
	char Msg[96];
	int Color32;
};
const short	_MSG_Action						= (108 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
const short	_MSG_Action2					= (102 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
const short	_MSG_Action3					= (104 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
struct		 MSG_Action
{
	_MSG;

	short PosX, PosY;

	int Effect; // 0 = walking, 1 = teleporting
	int Speed;

	char Route[MAX_ROUTE];

	short TargetX, TargetY;
};

const short  _MSG_Motion					= (106 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
struct		  MSG_Motion
{
	_MSG;

	short Motion;
	short Parm;
	int   NotUsed;
};

const short  _MSG_UpdateEquip				= (107 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
struct		  MSG_UpdateEquip
{
	_MSG;
	unsigned short  Equip[MAX_EQUIP];
	unsigned char AnctCode[MAX_EQUIP];
};

const short _MSG_TradingItem				= (118 | FLAG_CLIENT2GAME | FLAG_GAME2CLIENT);
struct		 MSG_TradingItem
{
	_MSG;

	unsigned char DestPlace;
	unsigned char DestSlot;
	unsigned char SrcPlace;
	unsigned char SrcSlot;

	int WarpID;
};

const short _MSG_SetShortSkill				= (120 | FLAG_CLIENT2GAME | FLAG_GAME2CLIENT);
struct		 MSG_SetShortSkill
{
	_MSG;
	unsigned char  Skill1[4];
	unsigned char  Skill2[16];
};

const short _MSG_Buy						= (121 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
struct		 MSG_Buy
{
	_MSG;

	unsigned short TargetID;
	short TargetInvenPos;
	short MyInvenPos;
	int   Coin;
};

const short _MSG_Sell						= (122 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
struct		 MSG_Sell
{
	_MSG;
	unsigned short TargetID;
	short MyType;
	short MyPos;
};

const short _MSG_ApplyBonus					= (119 | FLAG_CLIENT2GAME);
struct		 MSG_ApplyBonus
{
	_MSG;
	short      BonusType;    // 0:ScoreBonus 1:Special  2:Skill
	short      Detail;       // 0:Str        1:Int      2:Dex      3:Con

	unsigned short TargetID;
};

const short _MSG_REQShopList				= (123 | FLAG_CLIENT2GAME); //STARNDARDPARM
struct		 MSG_REQShopList
{
	_MSG;
	unsigned short Target;
	unsigned short Unk;
	//retirar se bugar
	unsigned short Face;
	unsigned short Effect;
};

constexpr auto _MSG_REQDonateShop = (264 | FLAG_CLIENT2GAME);
struct MSG_REQDonateShop
{
	_MSG;
	unsigned short Target;
	unsigned short Unk;
	//retirar se bugar
	unsigned short Face;
	unsigned short Effect;
};

const short _MSG_Restart					= (137 | FLAG_CLIENT2GAME); // STANDARD
const short _MSG_Withdraw					= (135 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME); // STANDARDPARM
const short _MSG_Deposit					= (136 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME); // STANDARDPARM
const short _MSG_PKMode						= (153 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME); // STANDARDPARM
const short _MSG_ReqTradeList				= (154 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME); // STANDARDPARM

const short  _MSG_UpdateWeather				= (139 | FLAG_GAME2CLIENT);
struct		  MSG_UpdateWeather
{
	_MSG;

	int CurrentWeather;
};

const short _MSG_Quest						= (139 | FLAG_CLIENT2GAME); // STANDARDPARM2
//struct STRUCT_QUESTDIARIA
//{
//	_MSG;
//
//	short IndexQuest;
//	short Count1;
//	short Count2;
//	short Count3;
//
//	short CountMax1;
//	short CountMax2;
//	short CountMax3;
//
//	short QtdItem;
//	long ExpReward;
//	long GoldReward;
//};
const short _MSG_Deprivate					= (140 | FLAG_CLIENT2GAME); // STANDARDPARM
const short _MSG_ReqChallange				= (141 | FLAG_GAME2CLIENT); // STANDARD
const short _MSG_Challange					= (142 | FLAG_CLIENT2GAME);  // STANDARDPARM
const short _MSG_ChallangeConfirm			= (143 | FLAG_CLIENT2GAME);  // ReqChallange
const short _MSG_ReqTeleport				= (144 | FLAG_CLIENT2GAME);
const short _MSG_ChangeCity					= (145 | FLAG_CLIENT2GAME);  //STANDARD



const short _MSG_SetHpMode					= (146 | FLAG_CLIENT2GAME);
struct		 MSG_SetHpMode
{
	_MSG;
	unsigned int Hp;
	short Mode;

};
const short _MSG_CloseShop					= (150 | FLAG_GAME2CLIENT);  // STANDARD

const short  _MSG_UseItem					= (115 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
struct		  MSG_UseItem
{
	_MSG;
	int      SourType;
	int      SourPos;
	int      DestType;
	int      DestPos;

	unsigned short GridX, GridY;
	unsigned short WarpID;
};

const short   STATE_NOTHING					= 0;
const short   STATE_OPEN					= 1;
const short   STATE_CLOSED					= 2;
const short   STATE_LOCKED					= 3;

const short  _MSG_UpdateItem				= (116 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
struct		  MSG_UpdateItem
{
	_MSG;
	int ItemID;

	//short  Height;
	int State;
};


const short  _MSG_CNFDropItem				= (117 | FLAG_GAME2CLIENT);
struct		  MSG_CNFDropItem
{
	_MSG;
	int      SourType;
	int      SourPos;
	int      Rotate;

	unsigned short GridX, GridY;
};

const short  _MSG_CNFAddParty				= (125 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
struct		  MSG_CNFAddParty
{
	_MSG;

	short Leaderconn;
	short Level;
	short MaxHp;
	short Hp;

	short PartyID;

	char MobName[NAME_LENGTH];

	short Target;
};

const short  _MSG_SendReqParty				= (127 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
struct		  MSG_SendReqParty
{
	_MSG;

	char Class;
	char PartyPos;

	short Level;
	short MaxHp;
	short Hp;

	short PartyID;

	char MobName[NAME_LENGTH];

	int unk;
	short Target;
};

const short  _MSG_RemoveParty				= (126 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
struct		  MSG_RemoveParty
{
	_MSG;

	short Leaderconn;
	short unk;
};


const short  _MSG_SendAutoTrade				= (151 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
struct		  MSG_SendAutoTrade
{
	_MSG;

	char Title[MAX_AUTOTRADETITLE];

	STRUCT_ITEM Item[MAX_AUTOTRADE];

	char CarryPos[MAX_AUTOTRADE];

	int Coin[MAX_AUTOTRADE];

	short Tax;
	short Index;
};

const short _MSG_ReqBuy						= (152 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
struct		 MSG_ReqBuy
{
	_MSG;

	int Pos;

	unsigned short TargetID;

	int Price;
	int Tax;

	STRUCT_ITEM item;
};

const short _MSG_MestreGrifo				= (217 | FLAG_GAME2DB | FLAG_CLIENT2GAME);
struct       MSG_MestreGrifo
{
	_MSG;
	int WarpID;
	int Typpe;

};
const short _MSG_ItemSold					= (155 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME); // Standard Parm2  Parm1:Seller Parm2:Pos


const short _MSG_CombineItem				= (166 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
const short _MSG_CombineItemTiny			= (192 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
const short _MSG_CombineItemLindy			= (195 | FLAG_CLIENT2GAME);
const short _MSG_CombineItemShany			= (196 | FLAG_CLIENT2GAME);
const short _MSG_CapsuleInfo				= (205 | FLAG_CLIENT2GAME);
const short _MSG_CombineItemOdin			= (210 | FLAG_CLIENT2GAME);
const short _MSG_CombineDedekinto           = (230 | FLAG_CLIENT2GAME);
const short _MSG_CombineDedekinto2          = (233 | FLAG_CLIENT2GAME);
const short _MSG_CombineItemExtracao		= (212 | FLAG_CLIENT2GAME);
const short _MSG_CombineItemAlquimia		= (225 | FLAG_CLIENT2GAME);
const short _MSG_CombineItemOdin2			= (226 | FLAG_CLIENT2GAME);
const short _MSG_CombineItemEhre			= (211 | FLAG_CLIENT2GAME);
const short _MSG_CombineItemAilyn			= (181 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
const short _MSG_CombineItemAgatha			= (186 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);

struct		 MSG_CombineItem
{
	_MSG;

	STRUCT_ITEM    Item[MAX_COMBINE];

	char           InvenPos[MAX_COMBINE];
};

const short _MSG_CombineComplete			= (167 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);  // STANDARDPARM
const short _MSG_InviteGuild				= (213 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);  // STANDARDPARM2

const short  _MSG_PutoutSeal				= (204 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
struct		  MSG_PutoutSeal
{
	_MSG;
	int      SourType;
	int      SourPos;
	int      DestType;
	int      DestPos;
	unsigned short GridX, GridY;
	unsigned short WarpID;

	char MobName[16];
};

const short _MSG_DeleteItem					= (228 | FLAG_CLIENT2GAME);
struct		 MSG_DeleteItem
{
	_MSG;

	int Slot;

	int sIndex;
};

const short _MSG_SplitItem					= (229 | FLAG_CLIENT2GAME);
struct		 MSG_SplitItem
{
	_MSG;

	int Slot;

	int sIndex;

	int Num;
};

struct	STRUCT_DAM
{
	int		TargetID;
	int		Damage;

};

const short  _MSG_Attack					= (103 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
struct		  MSG_Attack
{
	_MSG; // 0 - 11

	char Unk_1[4]; // 12 - 15

	int  CurrentHp; // 16 - 19
	 
	char Unk_2[4]; // 20 - 23

	long long CurrentExp; // 24 - 31
	short unk0; // 32 - 33

	unsigned short		PosX, PosY; // 34 - 37
	unsigned short		TargetX, TargetY; // 38 - 41

	unsigned short		AttackerID; // 42 - 43
	unsigned short		Progress; // 44 - 45

	unsigned char		Motion; // 46
	unsigned char		SkillParm;  // 47
	unsigned char		DoubleCritical; // 48
	unsigned char		FlagLocal; // 49

	short				Rsv; // 50 - 51

	int					CurrentMp; // 52 - 55

	short 				SkillIndex; // 56 - 57
	short				ReqMp; // 58 - 59

	STRUCT_DAM			Dam[MAX_TARGET]; // 60 - 163

	// TOTALSIZE 164
};

const short _MSG_Trade						= (131 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
struct		 MSG_Trade
{
	_MSG;

	STRUCT_ITEM		Item[MAX_TRADE];

	char			InvenPos[MAX_TRADE];
	int				TradeMoney;
	unsigned char	MyCheck;
	unsigned short	OpponentID;
};

const short _MSG_QuitTrade					= (132 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
const short _MSG_CNFCheck					= (134 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME); // STANDARD

const short  _MSG_AttackOne					= (157 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
#pragma pack(push, 1)
struct		  MSG_AttackOne
{
	_MSG;

	char Unk_1[4];

	int  CurrentMp;

	char Unk_2[4];

	long long CurrentExp;
	short unk0;

	unsigned short		PosX, PosY;
	unsigned short		TargetX, TargetY;

	unsigned short		AttackerID;
	unsigned short		Progress;

	unsigned char		Motion;
	unsigned char		SkillParm;
	unsigned char		DoubleCritical;
	unsigned char		FlagLocal;

	short				Rsv;

	int					CurrentHp;

	short 				SkillIndex;
	short				ReqMp;

	STRUCT_DAM			Dam[1];
};
#pragma pack(pop)

typedef struct
{
	_MSG; // 0 - 11
	INT32 Hold; // 12 - 15
	INT32 reqMP;  // 16 - 19
	INT32 Unk; // 20 - 23
	INT64 currentExp;  // 24 - 27
	short unknow;  // 28 - 31
	STRUCT_POSITION attackerPos;  // 32 - 35
	STRUCT_POSITION targetPos;  // 36 - 39
	short attackerId;  // 40 - 41
	short attackCount;  // 42 - 43
	unsigned char Motion; // 44
	unsigned char skillParm;  // 45
	unsigned char doubleCritical; // 46
	unsigned char FlagLocal;
	//char flagLocal;  // 47
	short Rsv;

	int currentMp;
	short skillId;  // 48 - 51
	short reqMp;
	STRUCT_DAM Target;
} p39D;

const short  _MSG_AttackTwo					= (158 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
struct		  MSG_AttackTwo
{
	_MSG;

	char Unk_1[4];

	int  CurrentMp;

	char Unk_2[4];

	long long CurrentExp;
	short unk0;

	unsigned short		PosX, PosY;
	unsigned short		TargetX, TargetY;

	unsigned short		AttackerID;
	unsigned short		Progress;

	unsigned char		Motion;
	unsigned char		SkillParm;
	unsigned char		DoubleCritical;
	unsigned char		FlagLocal;

	short				Rsv;

	int					CurrentHp;

	short 				SkillIndex;
	short				ReqMp;


	STRUCT_DAM			Dam[2];
};

const short	 _MSG_ReqRanking				= (159 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);  // STANDARD_PARM2  PARM1:TargetID, PARM2: 0:1vs1 1:5vs5   2:10vs10  3:Ok
const short  _MSG_Ping						= (160 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);

const short  _MSG_StartTime					= (161 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);

const short  _MSG_EnvEffect					= (162 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
struct		  MSG_EnvEffect
{
	_MSG;
	short		x1;
	short		y1;

	short		x2;
	short		y2;

	short		Effect;
	short		EffectParm;
};

const short	 _MSG_SoundEffect				= (163 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);  // STANDARDPARM
const short  _MSG_GuildDisable				= (164 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
const short  _MSG_GuildBoard				= (165 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);  // STANDARDPARM2
const short  _MSG_SendWarInfo				= (168 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);

const short  _MSG_AcceptParty				= (171 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
struct		  MSG_AcceptParty
{
	_MSG;

	short LeaderID;
	char MobName[NAME_LENGTH];
};

const short _MSG_TransperCharacter			= (169 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME | FLAG_DB2GAME);
const short _MSG_ReqTransper				= (170 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME | FLAG_DB2GAME | FLAG_GAME2DB);  // STANDARDPARM2 
struct		 MSG_ReqTransper
{
	_MSG;
	int		Result;							// 0:Success		1:Same Name Exist		2:No Space at Transper Server   3:Unknown Error	
	int		Slot;
	char	OldName[NAME_LENGTH];
	char	NewName[NAME_LENGTH];
};

const short _MSG_SendCastleState			= (172 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME); // SignalParm
const short _MSG_SendCastleState2			= (173 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME); // SignalParm	

const short  _MSG_MobLeft					= (176 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME); //SignalParm

const short _MSG_SendArchEffect				= (180 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME); // SignalParm	
const short _MSG_SendCelestialEffect		= (181 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME); // SignalParm	

const short  _MSG_SendAffect				= (185 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
struct		  MSG_SendAffect
{
	_MSG;
	STRUCT_AFFECT Affect[MAX_AFFECT];
};


const short  _MSG_MobCount					= (187 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME); //SignalParm2

const short _MSG_GrindRankingData			= (1 | FLAG_NEW | FLAG_DB2GAME | FLAG_GAME2CLIENT);
struct		 MSG_SendExpRanking
{
	_MSG;

	int RankPosition;

	STRUCT_RANKING PlayerAbove;
	STRUCT_RANKING PlayerRank;
	STRUCT_RANKING PlayerUnder;

	MSG_SendExpRanking(int myID) :
	RankPosition(0), PlayerAbove(),
	PlayerRank(), PlayerUnder()
	{
		Type = _MSG_GrindRankingData;
		ID = myID;
		Size = sizeof(MSG_SendExpRanking);
	}
};

const short _MSG_UpdateExpRanking			= (2 | FLAG_NEW | FLAG_DB2GAME | FLAG_GAME2DB | FLAG_GAME2CLIENT);
struct		 MSG_UpdateExpRanking
{
	_MSG;

	STRUCT_RANKING RankInfo;

	MSG_UpdateExpRanking(int myID, STRUCT_RANKING rankInfo) :
	RankInfo()
	{
		Type = _MSG_UpdateExpRanking;
		ID = myID;
		Size = sizeof(MSG_UpdateExpRanking);

		RankInfo = rankInfo;
	}
};

struct STRUCT_REBUY
{
	int Price; // 0 - 3

	STRUCT_ITEM Item; // 4 - 11

	int Ticks; // 12 - 15 - 16
};

const short _MSG_Rebuy						= (232 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
struct		 MSG_Rebuy
{
	_MSG;

	STRUCT_REBUY Rebuy[MAX_ITEM_REBUY];

	int Not;
	int Pot;
	int Dot;
};

const short _MSG_PartyEvocation				= (234 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
struct		 MSG_PartyEvocation
{
	_MSG; // 0 - 11
 
	short Leader; // 12 - 13
	short EvocationList[MAX_PARTY]; // 14 - 37

	char Unknown[2]; // 38 - 39
};

struct QuizInfo
{
	int RespostaCorreta; //de 0 a 3
	int RespostaCorretaLanN; //de 0 a 3
	int RespostaCorretaLanM; //de 0 a 3
	int RespostaCorretaLanA; //de 0 a 3
	bool Status;
	bool StatusN;
	bool StatusM;
	bool StatusA;
};
struct MSG_FreyjaAposta
{
	_MSG;

	int aposta;
};

const short _MSG_AnswerQuiz					= (199 | FLAG_CLIENT2GAME);
const short _MSG_Quiz						= (198 | FLAG_GAME2CLIENT);
struct       MSG_Quiz
{
	_MSG;

	char Title[MESSAGECHAT_LENGTH];
	char Answer[4][32];
	int CorrectAlternative;
};

const short _MSG_BigQuiz					= (177 | FLAG_DB2GAME | FLAG_CLIENT2GAME | FLAG_GAME2CLIENT);
struct		 MSG_BigQuiz
{
	_MSG;			// 0 - 12

	int Unknow;		// 12 - 16

	char Title[128];// 16 - 144

	char Line[3][128]; // 144 - 528
};


const short _MSG_Firework					= (201 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
struct		 MSG_Firework
{
	_MSG;


};
const short _MSG_Firework_2					= (202 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
struct		 MSG_Firework_2
{
	_MSG;


};

//////////////////////////////////////////////////////////////////////
//																	//
//					         	 NP			     					//
//																	//
//////////////////////////////////////////////////////////////////////


const short  _MSG_NPReqIDPASS				= (1 | FLAG_DB2NP);
const short  _MSG_NPIDPASS					= (2 | FLAG_NP2DB);
struct		  MSG_NPIDPASS
{
	_MSG;
	char Account[ACCOUNTNAME_LENGTH];
	int  Encode1;
	char Pass[ACCOUNTPASS_LENGTH];
	int  Encode2;
};

const short  _MSG_NPReqAccount				= (3 | FLAG_NP2DB);
struct		  MSG_NPReqAccount
{
	_MSG;
	char Account[ACCOUNTNAME_LENGTH];
	char Char[NAME_LENGTH];
};

const short  _MSG_NPNotFound				= (4 | FLAG_DB2NP); //   Signal

const short  _MSG_NPAccountInfo				= (5 | FLAG_DB2NP);
struct		  MSG_NPAccountInfo
{
	_MSG;
	STRUCT_ACCOUNTFILE account;
	short Session;
	short State;  // 0:Normal  1:Blocked= (@);  2:Deleted= (_);  3:Disabled= (#);
};

const short  _MSG_NPReqSaveAccount			= (6 | FLAG_NP2DB); //   MSG_NPAccountInfo

const short  _MSG_NPDisable					= (7 | FLAG_NP2DB | FLAG_DB2NP);

const short  _MSG_NPEnable					= (8 | FLAG_NP2DB | FLAG_DB2NP); //   NPEnableParm 
struct		  MSG_NPEnable
{
	_MSG;
	char AccountName[ACCOUNTNAME_LENGTH];
	int Year;
	int YearDay;
};

const short  _MSG_NPNotice					= (9 | FLAG_NP2DB | FLAG_DB2NP | FLAG_DB2GAME); //   Parm 
struct		  MSG_NPNotice
{
	_MSG;
	int  Parm1;
	int  Parm2;
	char AccountName[ACCOUNTNAME_LENGTH];
	char String[MAX_NOTIFY_LENGTH];
};

const short  _MSG_NPState					= (10 | FLAG_NP2DB | FLAG_DB2NP); //   Parm 

const short _MSG_NPCreateCharacter			= (11 | FLAG_NP2DB | FLAG_DB2NP);
struct		 MSG_NPCreateCharacter
{
	_MSG;
	int  Slot;
	char Account[ACCOUNTNAME_LENGTH];
	STRUCT_MOB Mob;
};

const short _MSG_NPCreateCharacter_Reply	= (12 | FLAG_DB2NP | FLAG_NP2DB);
struct		 MSG_NPCreateCharacter_Reply
{
	_MSG;
	int  Slot;
	char Account[ACCOUNTNAME_LENGTH];
	int  Result;
	char Name[NAME_LENGTH];
};

const short  _MSG_NPDonate					= (13 | FLAG_NP2DB | FLAG_DB2NP);
struct		  MSG_NPDonate
{
	_MSG;
	char AccountName[ACCOUNTNAME_LENGTH];
	 int Donate;
};

const short  _MSG_NPHonra = (13 | FLAG_NP2DB | FLAG_DB2NP);
struct		  MSG_NPHonra
{
	_MSG;
	char AccountName[ACCOUNTNAME_LENGTH];
	int Honra;
};

const short _MSG_NPAppeal					= (16 | FLAG_DB2GAME | FLAG_GAME2DB | FLAG_DB2NP);

struct STRUCT_CLIENTPAC
{
	_MSG;

	INT32 Points[2];
};

struct TMP_BLOCKIP
{
	unsigned int IPAddress;
	short countdown;

	TMP_BLOCKIP(int ip, int cd)
	{
		this->IPAddress = ip;
		this->countdown = cd;
	};
};

#pragma endregion

#pragma region Basedef functions prototypes

int  BASE_NeedLog(STRUCT_ITEM *item, int money);
int  BASE_GetBonusSkillPoint(STRUCT_MOB *mob, STRUCT_MOBEXTRA *extra);
int  BASE_GetBonusScorePoint(STRUCT_MOB *mob, STRUCT_MOBEXTRA *extra);
int  BASE_GetHpMp(STRUCT_MOB *mob, STRUCT_MOBEXTRA *extra);
int  BASE_GetSpeed(STRUCT_SCORE *score);
int  BASE_GetDamage(int dam, int ac, int combat);
void BASE_GetLanguage(char *str, int idx);
void BASE_GetLanguage(char *str, int idx, char *parm1);
void BASE_GetLanguage(char *str, int idx, char *parm1, char *parm2);
void BASE_GetLanguage(char *str, int idx, int parm1);
void BASE_GetLanguage(char *str, int idx, int parm1, int parm2);
void BASE_GetLanguage(char *str, int idx, char * parm1, int parm2);
void BASE_GetLanguage(char *str, int idx, int parm1, char *parm2);
void BASE_GetGuildName(int ServerGroup, unsigned short usGuild, char *szGuildName);
void BASE_GetClientGuildName(int ServerGroup, unsigned short usGuild, char *szGuildName, int Sub = 0);
int  BASE_GetSkillDamage(int dam, int ac, int combat);
void BASE_GetItemCode(STRUCT_ITEM * item, char * str);
int  BASE_GetItemAbilityNosanc(STRUCT_ITEM *item, unsigned char Type);
int  BASE_GetItemAbility(STRUCT_ITEM *item, unsigned char Type);
int  BASE_GetStaticItemAbility(STRUCT_ITEM *item, unsigned char Type);
int  BASE_GetBonusItemAbility(STRUCT_ITEM *item, unsigned char Type);
int  BASE_GetBonusItemAbilityNosanc(STRUCT_ITEM *item, unsigned char Type);
int  BASE_GetItemSanc(STRUCT_ITEM *item);
int BASE_GetItemGem(STRUCT_ITEM *item);
int  BASE_GetItemSancSuccess(STRUCT_ITEM *item);
int  BASE_GetSuccessRate(STRUCT_ITEM *item, int OriLacto);
int  BASE_GetGrowthRate(STRUCT_ITEM *item);
int  BASE_SetItemSanc(STRUCT_ITEM *dest, int sanc, int success);
int  BASE_GetItemAmount(STRUCT_ITEM *item);
void BASE_SetItemAmount(STRUCT_ITEM *item, int amount);
STRUCT_ITEM *GetItemPointer(STRUCT_MOB *mob, STRUCT_ITEM *cargo, int type, int pos);
int  BASE_GetMobAbility(STRUCT_MOB *mob, unsigned char Type);
int  BASE_GetMaxAbility(STRUCT_MOB *mob, unsigned char Type);
int  BASE_GetMobCheckSum(STRUCT_MOB *mob);
bool BASE_CheckValidString(char *name);
bool BASE_CheckHangul(unsigned short word);
int  BASE_InitializeBaseDef();
void BASE_ApplyAttribute(char *pHeight, int size);
void BASE_InitModuleDir();
int  BASE_GetSum(char * p, int size);
int  BASE_GetSum2(char *p, int size);
void BASE_WriteSkillBin();
void BASE_WriteItemList(int nItemList);
int  BASE_ReadSkillBin();
int  BASE_ReadItemList();
void BASE_SpaceToUnderBar(char *szStr);
void BASE_UnderBarToSpace(char *szStr);
void BASE_ClearMob(STRUCT_MOB *mob);
void BASE_ClearMobExtra(STRUCT_MOBEXTRA *extra);
void BASE_GetCurrentScore(STRUCT_MOB & MOB, STRUCT_AFFECT *Affect, STRUCT_MOBEXTRA *extra, int *ExpBonus, int *ForceMobDamage, int isSummon, int *Accuracy, int *AbsHp, int *ForceDamage);
void BASE_GetFirstKey(char * source, char * dest);
int  BASE_GetGuild(int x, int y);
int  BASE_GetIndex(STRUCT_ITEM *item);
int  BASE_GetGuild(STRUCT_ITEM *item);
int  BASE_GetSubGuild(int item);
int  BASE_GetArena(int x, int y);
int  BASE_GetVillage(int x, int y);
void BASE_GetKorFirst(int temp, int *a);
void BASE_ClearItem(STRUCT_ITEM *item);
int  BASE_CanEquip(STRUCT_ITEM *item, STRUCT_SCORE *score, int Pos, int Class, STRUCT_ITEM *pBaseEquip, STRUCT_MOBEXTRA *extra);
int  BASE_CanCarry(STRUCT_ITEM *item, STRUCT_ITEM *carry, int DestX, int DestY, int *error);
int  BASE_CanCargo(STRUCT_ITEM *item, STRUCT_ITEM *cargo, int DestX, int DestY);
void BASE_SortTradeItem(STRUCT_ITEM *Item, int Type);
int  BASE_CanTrade(STRUCT_ITEM *Dest, STRUCT_ITEM *Carry, unsigned char *MyTrade, STRUCT_ITEM *OpponentTrade, int MaxCarry);
void BASE_InitializeMessage(char *file);
void BASE_InitializeMobname(char *file, int offset);
void BASE_WriteMessageBin();
int  BASE_ReadMessageBin();
void BASE_InitializeItemList();
int  BASE_ReadItemListFile(char *filename, int Build);
void BASE_InitializeEffectName();
void BASE_InitializeHitRate();
int  BASE_UpdateItem(int maskidx, int CurrentState, int NextState, int xx, int yy, char *pHeight, int rotate, int *height);
int  BASE_UpdateItem2(int maskidx, int CurrentState, int NextState, int xx, int yy, char *pHeight, int rotate, int height);
void BASE_GetDestByAction(unsigned short *x, unsigned short *y, struct MSG_Action *mv);
int  BASE_GetManaSpent(int SkillNumber, int SaveMana, int Special);
int  BASE_GetHitRate(STRUCT_SCORE *att, STRUCT_SCORE *def);
int  BASE_GetDamageRate(STRUCT_SCORE* att, int skill);
int  BASE_GetAccuracyRate(STRUCT_SCORE *att);
int  BASE_GetDoubleCritical(STRUCT_MOB *mob, unsigned short *sProgress, unsigned short *cProgress, unsigned char *bDoubleCritical);
int  BASE_GetRoute(int x, int y, int *targetx, int *targety, char *Route, int distance, char *pHeight);
int  BASE_GetDistance(int x1, int y1, int x2, int y2);
void BASE_GetHitPosition(int sx, int sy, int *tx, int *ty, char *pHeight);
void BASE_WriteInitItem();
int  BASE_ReadInitItem();
void BASE_InitializeInitItem();
void BASE_InitializeSkill();
int  IsClearString3(char *str, int nTarget);
void BASE_InitializeClientGuildName(int group);
void BASE_InitializeGuildName();
int  BASE_InitializeServerList();
int  BASE_InitializeAttribute();
int  BASE_GetHttpRequest(char *httpname, char *Request, int MaxBuffer);
int  BASE_GetSkillDamage(int skillnum, STRUCT_MOB *mob, int weather, int weapondamage);
int  BASE_GetSkillDamage(int skillnum, STRUCT_MOB *mob, int weather, int weapondamage, int master);
int	 GetSkillDamage_PvP(int skillnum, STRUCT_MOB* mob, int weather, int weapondamage);
int  BASE_GetEnglish(char *name);
int  BASE_GetWeekNumber();
int  BASE_CheckPacket(struct MSG_STANDARD* m);

int  BASE_VisualItemCode(STRUCT_ITEM *Item, int mnt);
int  BASE_VisualAnctCode(STRUCT_ITEM *Item);

void BASE_SetItemDate(STRUCT_ITEM *Item, int day);
void BASE_FadaDate(STRUCT_ITEM *Item, int Time);
int  BASE_CheckItemDate(STRUCT_ITEM *Item);
void BASE_CheckFairyDate(STRUCT_ITEM *Item);

#pragma endregion

#pragma region Basedef Externs


#pragma region Balanceio Novo

extern int ClassVsClass[5][50];
extern int pClassVsClass[5][50];

#define        TK 0
#define        FM 1
#define        BM 2
#define        HT 3
#define        JOGADOR_FISICO 0
#define        JOGADOR_MAGO 1

#pragma endregion
extern ServerInfos Server;
extern STRUCT_GUILDZONE g_pGuildZone[MAX_GUILDZONE];

extern int				g_pIncrementHp[4];
extern int				g_pIncrementMp[4];

extern int				g_pIncrementHp_2[4];
extern int				g_pIncrementMp_2[4];

extern int				g_pIncrementHp_3[4];
extern int				g_pIncrementMp_3[4];

extern int				BaseArcos[4][19];
extern int				BaseGarras[4][19];

extern int				g_pGroundMask[MAX_GROUNDMASK][4][6][6];

extern int				g_pDropBonus[64];
extern int				g_pDropRate[64];

extern int				DungeonPos[30][2];
extern int				DungeonItem[10];

extern long long		g_pNextLevel[MAX_LEVEL + 2];
extern long long	    g_pNextLevel_2[MAX_CLEVEL + 2];
extern STRUCT_BEASTBONUS pSummonBonus[MAX_SUMMONLIST];
extern STRUCT_BEASTBONUS pTransBonus[5];
extern STRUCT_AVISOGUILD AvisarGuild[4096];
extern STRUCT_QUEST QuestDiaria[36];

extern int  ChargedGuildList[MAX_SERVER][MAX_GUILDZONE];
extern char g_pGuildName[10][16][MAX_GUILD][GUILDNAME_LENGTH];
extern char g_pMessageStringTable[MAX_STRING][128];
extern char EffectNameTable[MAX_EFFECTINDEX][24];

extern STRUCT_SPELL g_pSpell[MAX_SKILLINDEX];
extern STRUCT_INITITEM g_pInitItem[MAX_INITITEM];

extern STRUCT_ITEMLIST g_pItemList[MAX_ITEMLIST];

extern unsigned char g_pAttribute[1024][1024];

extern char g_pServerList[MAX_SERVERGROUP][MAX_SERVERNUMBER][64];

extern int g_dwInitItem;

extern int g_HeightWidth;
extern int g_HeightHeight;
extern int g_HeightPosX;
extern int g_HeightPosY;
extern char g_pFormation[5][12][2];
extern int g_pClanTable[9][9];

extern int g_pSancRate[3][12];
extern int g_pSancGrade[2][5];
extern int g_pEhreRate[10];
extern int g_pDedekintoRate[3];
extern int g_pOdinRate[12];
extern int g_pCelestialRate[15];
extern int g_pAmuletoRate[15];
extern int g_pAmuletoRate2[15];
extern int g_pTinyBase;
extern int g_pShanyBase;
extern int g_pAilynBase;
extern int g_pAgathaBase;
extern int g_pAnctChance[3];
extern int g_pItemSancRate12[11];
extern int g_pItemSancRate12Minus[4];
extern int BaseSIDCHM[4][6];

extern int g_pBonusValue[10][2][2];
extern int g_pBonusType[10];
extern int g_pBonusValue2[69][4];//Peito calça
extern int g_pBonusValue3[25][4];//Elmo
extern int g_pBonusValue4[30][4];//Luva
extern int g_pBonusValue5[30][4];//Bota

#pragma endregion

#endif
