#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include "..\Basedef.h"
#include "..\ItemEffect.h"
#include "..\CPSock.h"

/*
#define		ACCOUNTNAME_LENGTH		16		// Max length of the account login
#define		ACCOUNTPASS_LENGTH		12      // Max length of the account password
#define		REALNAME_LENGTH			24      // Max length of the name of the account owner
#define		EMAIL_LENGTH			48      // Max length of the email address of the account owner
#define		ADDRESS_LENGTH			78      // Max length of the real address of the account owner
#define		TELEPHONE_LENGTH		16      // Max length of the telephone number of the account owner
#define		MOB_PER_ACCOUNT			4       // Max number of mobs an account can have

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
};

struct STRUCT_SCORE
{
	int Level;	 // The mob's level
	int Ac;		 // The mob's defense
	int Damage;   // The mob's damage force

	unsigned char  Merchant; // UNK
	unsigned char  AttackRun; // The mob's speed
	unsigned char  Direction;
	unsigned char  ChaosRate;

	int MaxHp;     // The max HP the mob can have
	int MaxMp;	  // The max MP the mob can have
	int Hp;		  // The current HP of the mob
	int Mp;		  // The current MP of the mob

	short		   Str;		  // The mob's strength points, affects it's attack power
	short		   Int;		  // The mob's intelligence points, affects it's skill attack powers and MP
	short		   Dex;		  // The mob's dexterity points, affects it's attack speed
	short		   Con;       // The mob's constitution points, affects it's HP

	short  Special[4]; // The mob's special points, affects it's skill tiers
};

struct STRUCT_MOB
{
	char		   MobName[16];	  // The name of the mob
	char		   Clan;		  // The clan the mob belongs to
	unsigned char  Merchant;	  // The mob's merchant ID
	unsigned short Guild;		  // The ID of the guild the mob belongs to
	unsigned char  Class;		  // The mobs class
	unsigned short  Rsv;
	unsigned char Quest;

	int			   Coin;		  // The ammount of coins the mob has

	long long   Exp;			  // The ammount of experience the mob has to level up

	short		   SPX;			 // The Y position saved by the stellar gem, to teleport the mob there when using warp scroll
	short		   SPY;			 // The Y position saved by the stellar gem, to teleport the mob there when using warp scroll

	STRUCT_SCORE   BaseScore;    // The base score of the mob 
	STRUCT_SCORE   CurrentScore; // The score the mob actually has

	STRUCT_ITEM    Equip[16];	 // The items the mob is wearing
	STRUCT_ITEM	   Carry[64];	 // The items the mob is carrying

	long LearnedSkill; // The skills the mob learned, divided into four categories (00 _ 00 _ 00 _ 00)

	unsigned int Magic;

	unsigned short ScoreBonus;   // The points the mob can use to increase score (Str, Int, Dex, Con)
	unsigned short SpecialBonus; // The points the mob can use to increase special, to increase effect of learned skills (score->Special[4])
	unsigned short SkillBonus;	 // The points the mob can use to buy skills

	unsigned char  Critical;	 // The chance the mob has to deliver critical hits
	unsigned char  SaveMana;	 // Uknown use, nomenclature of variable is correct to all current standards

	unsigned char  SkillBar[4];  // The skills saved on the first 4 slots of the skill bar

	unsigned char  GuildLevel;   // The mob's guuld level, used to define if it's a guild member or leader

	unsigned short  RegenHP;		 // UNK
	unsigned short  RegenMP;		 // UNK

	char  Resist[4];	 // The mob's resistencies, to fire / ice / thunder / magic

};

struct STRUCT_MOBEXTRA
{
	short ClassMaster;
	char  Citizen;

	int	  Fame;

	char  Soul;

	short MortalFace;

	struct
	{
		struct
		{
			char Newbie;//00_01_02_03_04  quest com quatro etapas
			char TerraMistica;//0 : não pegou a quest 1: pegou a quest e não concluiu 2: quest completa
			char MolarGargula;
			char PilulaOrc;

			char EMPTY[30];
		}Mortal;

		struct
		{
			char MortalSlot;
			char MortalLevel;

			char Level355;
			char Level370;

			char Cristal;//00_01_02_03_04 quest com quatro etapas

			char EMPTY[30];
		}Arch;

		struct
		{
			short ArchLevel;
			short CelestialLevel;
			short SubCelestialLevel;

			char Lv40;
			char Lv90;

			char Add120;
			char Add150;
			char Add180;
			char Add200;

			char Arcana;
			char Reset;

			char EMPTY[30];
		}Celestial;

		char Circle;
		char EMPTY[30];

	}QuestInfo;

	struct
	{
		int Class;

		long long   Exp;			  // The ammount of experience the mob has to level up

		short		   SPX;			 // The Y position saved by the stellar gem, to teleport the mob there when using warp scroll
		short		   SPY;			 // The Y position saved by the stellar gem, to teleport the mob there when using warp scroll

		STRUCT_SCORE   BaseScore;    // The base score of the mob 

		long LearnedSkill; // The skills the mob learned, divided into four categories (00 _ 00 _ 00 _ 00)


		unsigned short ScoreBonus;   // The points the mob can use to increase score (Str, Int, Dex, Con)
		unsigned short SpecialBonus; // The points the mob can use to increase special, to increase effect of learned skills (score->Special[4])
		unsigned short SkillBonus;	 // The points the mob can use to buy skills

		unsigned char  SkillBar1[4];  // The skills saved on the first 4 slots of the skill bar
		unsigned char  SkillBar2[16];  // The skills saved on the first 4 slots of the skill bar

		char Soul;
		char EMPTY[30];
	}SaveCelestial[2];

	time_t LastNT;
	int NT;

	int KefraTicket;

	time_t DivineEnd;

	unsigned int Hold;

	struct
	{
		long long Exp;
		int		  YearDay;
	}DayLog;

	struct
	{
		time_t LastTime;
		int Count;
	}DonateInfo;

	int EMPTY[9];
};

struct STRUCT_AFFECT
{
	unsigned char Type;
	unsigned char Value;
	unsigned short Level;
	unsigned int Time;
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

struct STRUCT_ACCOUNTFILE
{
	STRUCT_ACCOUNTINFO Info; // 0 - 216

	STRUCT_MOB	Char[MOB_PER_ACCOUNT]; // 216 - 3480
	STRUCT_ITEM Cargo[128]; // 3480 - 4504
	int			Coin; // 4504 - 4508

	unsigned char ShortSkill[MOB_PER_ACCOUNT][16]; // 4508 - 4572

	STRUCT_AFFECT affect[MOB_PER_ACCOUNT][32];
	STRUCT_MOBEXTRA mobExtra[MOB_PER_ACCOUNT];

	int Donate;

	char TempKey[52];
}Account;*/

STRUCT_ACCOUNTFILE Account;

FILE *fp;
bool RETURN;

int main()
{
	do
	{
		system("cls");
		RETURN = 0;

		memset(&Account, 0, sizeof(STRUCT_ACCOUNTFILE));

		do
		{
			puts("Login (4 ~ 16 Caracteres): ");
			fflush(stdin);
			gets_s(Account.Info.AccountName);
		} while (strlen(Account.Info.AccountName) < 4);

		do
		{
			puts("Senha (4 ~ 16 Caracteres): ");
			fflush(stdin);
			gets_s(Account.Info.AccountPass);
		} while (strlen(Account.Info.AccountPass) < 4);

		for (int i = 15; i >= 12; i--)
		{
			Account.Info.AccountName[i] = '\0';
			Account.Info.AccountPass[i] = '\0';
		}

		Account.Info.NumericToken[0] = -1;

		char folder[255] = { 0, };

		if ((Account.Info.AccountName[0] >= 'a' && Account.Info.AccountName[0] <= 'z') || (Account.Info.AccountName[0] >= 'A' && Account.Info.AccountName[0] <= 'Z'))
			sprintf_s(folder, "account/%c/%s", Account.Info.AccountName[0], Account.Info.AccountName);
		else
			sprintf_s(folder, "account/etc/%s", Account.Info.AccountName);

		if (fp = fopen(folder, "rb"))
		{
			system("cls");

			RETURN = 1;

			fclose(fp);

			printf("Conta [%s] ja existe!", Account.Info.AccountName);

			getchar();
		}
		else
		{
			system("cls");

			fp = fopen(folder, "wb");

			fwrite(&Account, 7800, 1, fp);

			fclose(fp);

			printf("Conta [%s] criada com sucesso!\n\nAperte qualquer tecla para continuar...", Account.Info.AccountName);

			getchar();
		}

	} while (RETURN == 1);

	return 0;
}