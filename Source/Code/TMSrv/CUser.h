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
#ifndef __CUSER__
#define __CUSER__

#include "..\Basedef.h"
#include "..\CPSock.h"

//-------Connecting User Modes----------------------------------------------------------------------------
#define USER_EMPTY       0 // There's no user on this slot
#define USER_ACCEPT      1
#define USER_LOGIN       2
//-------SelScreen User Modes----------------------------------------------------------------------------
#define USER_SELCHAR     11   // Waiting DB to send the SELCHAR struct
#define USER_CHARWAIT    12   // Waiting DB confirmation of char login
#define USER_WAITDB		 13	  // Waiting DB response to confirm
//#define USER_CREWAIT     14   // Waiting DB confirmation of character creation

//-------Ingame User Modes----------------------------------------------------------------------
#define USER_PLAY        22 // User is ingame playing with a character
#define USER_SAVING4QUIT 24 // User is saving game right before quitting

class CUser
{
public:
	char AccountName[ACCOUNTNAME_LENGTH]; // 0 - 16
	int Slot; // 16 // Number of the slot of the selected character
	unsigned int IP; // 20

	int IsAutoTrading; //28

	int chave1; //novato
	int chave2;
	int chave3;
	int chave4;
	int Keys[50];
	// 0 = Level
	// 1 a 15 = Trajes de Montaria
	// 49 = CheckEvento

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

	int CountMob1;
	int CountMob2;
	int CountMob3;
	int QuestAtiva;

	time_t LastQuestDay;

	int Mode; // 24
	int TradeMode; // 28 // TradeMode ?
	CPSock cSock; // 32 - 32
	char Unk2[400]; // 64
	int Unk3; // 464
	STRUCT_ITEM Cargo[MAX_CARGO]; // 468 - 1024
	int Coin; // 1492
	unsigned short cProgress; // 1496
	short Unk_1498; // 1498
	bool WaitDB;

	////////////////////////////////////////////////
	// Trade ?									 //
	//////////////////////////////////////////////

	MSG_Trade Trade; // 1500 // size correto, deve ser uma struct //    Trade; ???

	////////////////////////////////////////////
	// AutoTrade ?							 //
	//////////////////////////////////////////

	MSG_SendAutoTrade AutoTrade;

	/////////////////////////////////////////

	int LastAttack; // 1788 // LastAttack ??
	int LastAttackTick; // 1792 // LastAttackTick ???
	int LastMove; // 1796 // LastMove ??
	int LastAction; // 1800 // LastAction ??
	int LastActionTick; // 1804 // LastActionTick??
	int LastIllusionTick; // 1808 // LastIllusionTick??
	int NumError; // 1812 // NumError ??
	int Unk_1816; // 1816
	STRUCT_SELCHAR SelChar; // 1820 - 744
	char LastChat[16]; // 2564 // LastChat ?
	int IsBillConnect; // 2580
	char Unk5[36]; // 2584
	unsigned char CharShortSkill[16]; // 2620
	int GemaX; // 2628
	int GemaY; // 2632
	int Whisper; // 2636 // Whisper ?
	int Guildchat; // 2640 // Guildchat ?
	int PartyChat; // 2644 // PartyChat ?
	int Chatting; //2648 Chatting??
	char Unk_2648[24]; // 2652
	int PKMode; // 2676 // PKMode ??
	int ReqHp; // 2680
	int ReqMp; // 2684
	int Unk_2688; // 2688
	char MacAddress[18];
	int Unk_2708; // 2708
	int RankingTarget; // 2712 // RankingTarget ???
	int RankingType; // 2716 // RankingType ???
	int LastReceiveTime; // 2720
	int Admin; // 2724
	int Unk_2728; // 2728 // Related to BILLING (Child!?!)
	unsigned int Unk_2732; // 2732 // Something related to BILLING (ReqBillSec?????)
	int Unk_2736; // 2736
	int Range; // 2740
	int CastleStatus; // 2744
	char Unk9[400]; // 2748 // LastSkillTick // size correto é 400.
	 int Donate;
	 int Honra;
	 int BossLocal1;
	int MuteChat;
	int KingChat;

	unsigned int UseItemTime;
	unsigned int Message;
	unsigned int DroplistTime;
	unsigned int AttackTime;
	unsigned int LastClientTick;
	ULONGLONG PotionTime;
	unsigned int PergaState;
	unsigned int PergaCount;
	unsigned int MoveItemTime;
	unsigned int Lasclick;
	ULONGLONG EventDelay;
	ULONGLONG CaptchaDelay;
	unsigned int Carptcha;
	unsigned int Territorio;
	time_t TempoDiario;

	ULONGLONG Atraso;
	ULONGLONG FiltroDelay;
	ULONGLONG MailItemDelay;
	ULONGLONG SendMailItemDelay;
	ULONGLONG RankingDelay;
	ULONGLONG TowerWarDelay;
	ULONGLONG DonateDelay;
	ULONGLONG DonateShopDelay;
	ULONGLONG RequestShopDelay;
	ULONGLONG DropListDelay;
	unsigned int QuestDiaria;
	unsigned int DiariaState;
	ULONGLONG AtrasocharLogout;
	int NumCreated;
	 
	int OnlyTrade;
	int TimeLojinha;
	STRUCT_ACCOUNTFILE File;
	int Vidas;


	struct _Ingame
	{
		struct {
			unsigned int IntervalTime;
		} Skill[103];
		int AttackMode;
		unsigned int LastAttackTime;
		char PartyPassword[6];



		char PassWord[16];

		char Login[16];


		bool autoStore; 

		bool GrupoAceitarSolicitação;

		int CheckPista;
		int CheckPesa;
		int CheckAgua;

		int DonateBuyItem;
		bool MobDonateStore;
		bool CanBuy;
		char MobName[10][16];
		int MobFace[10];
		int MobEffect[10];
		int Window;
		int MarketState;
	} Ingame;

public:
	CUser();
	~CUser();
	int   AcceptUser(int ListenSocket);
	int CloseUser();
};


#endif