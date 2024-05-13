
#include <Windows.h>
#include <stdio.h>
#include <fcntl.h>
#include <time.h>
#include <math.h>
#include <io.h>
#include <errno.h>

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
#include "CCastleZakum.h"
#include "CWarTower.h"
#include "CCubo.h" 
#include "Functions.h"
#include "wMySQL.h"

void MobKilled(int target, int conn, int PosX, int PosY)
{
	if (conn <= 0 || conn >= MAX_MOB || target <= 0 || target >= MAX_MOB || pMob[target].Mode == USER_EMPTY)
		return;

	STRUCT_ITEM* FairySlot = &pMob[target].MOB.Equip[13];

	MSG_CreateMob sCreateMob;

	if (pMob[target].MOB.CurrentScore.Level >= 1000)
	{
		pMob[target].MOB.CurrentScore.Hp = pMob[target].MOB.CurrentScore.MaxHp;

		if (target < MAX_USER)
			SetReqHp(target);

		GetCreateMob(target, &sCreateMob);
		GridMulticast(pMob[target].TargetX, pMob[target].TargetY, (MSG_STANDARD*)&sCreateMob, 0);

		SendScore(conn);

		return;
	}

	if (pMob[target].MOB.Equip[13].sIndex == 769 && RvRState == 0 && GTorreState == 0 && CastleState == 0) // Nyerds
	{
		int sanc = BASE_GetItemSanc(FairySlot);

		if (sanc > 0)
		{
			sanc--;

			if (FairySlot->stEffect[0].cEffect == 43)
				FairySlot->stEffect[0].cValue = sanc;

			else if (FairySlot->stEffect[1].cEffect == 43)
				FairySlot->stEffect[1].cValue = sanc;

			else if (FairySlot->stEffect[2].cEffect == 43)
				FairySlot->stEffect[2].cValue = sanc;
		}
		else
			BASE_ClearItem(FairySlot);

		if (target > 0 && target <= MAX_USER)
		{
			SendItem(target, ITEM_PLACE_EQUIP, 13, &pMob[target].MOB.Equip[13]);
			SendEmotion(target, 14, 2);
		}

		SendEquip(target, 0);

		pMob[target].MOB.CurrentScore.Hp = pMob[target].MOB.CurrentScore.MaxHp;

		if (target < MAX_USER)
			SetReqHp(target);

		GetCreateMob(target, &sCreateMob);
		GridMulticast(pMob[target].TargetX, pMob[target].TargetY, (MSG_STANDARD*)&sCreateMob, 0);

		SendScore(conn);

		return;
	}
	if (CastleState > 1 && pMob[target].TargetX == 1046 && pMob[target].TargetY == 1690 && target > 0 && target < MAX_USER)
	{
		DoTeleport(target, 1066, 1717);
		return;
	}
	#pragma region >> Batalha Real func
		if (BrState >= 1)
		{
	#pragma region >> Func para quem morreu
			if (p_BatalhaReal.start == true)
			{		
				if ((conn > 0 && conn < MAX_USER) && (target > 0 && target < MAX_USER)) {
	
					if (pMob[target].TargetX >= 140 && pMob[target].TargetY >= 4000 && pMob[target].TargetX <= 200 && pMob[target].TargetY <= 4100)
					{
						//p_BatalhaReal.Members[target].Id -= 1;
						p_BatalhaReal.NumMembers -= 1;
						if (pUser[target].Vidas >= 1)
						{
							pUser[target].Vidas -= 1;
							int rand_ = rand() % 100;
							if (rand_ <= 10)
								DoTeleport(target, 148 + rand() % 2, 4010 + rand() % 2);
							else if (rand_ <= 20)
								DoTeleport(target, 148 + rand() % 2, 4044 + rand() % 2);
							else if (rand_ <= 30)
								DoTeleport(target, 148 + rand() % 2, 4077 + rand() % 2);
							else if (rand_ <= 40)
								DoTeleport(target, 168 + rand() % 2, 4061 + rand() % 2);
							else if (rand_ <= 50)
								DoTeleport(target, 168 + rand() % 2, 4028 + rand() % 2);
							else if (rand_ <= 60)
								DoTeleport(target, 191 + rand() % 2, 4080 + rand() % 2);
							else if (rand_ <= 70)
								DoTeleport(target, 191 + rand() % 2, 4063 + rand() % 2);
							else if (rand_ <= 80)
								DoTeleport(target, 191 + rand() % 2, 4044 + rand() % 2);
							else if (rand_ <= 90)
								DoTeleport(target, 191 + rand() % 2, 4027 + rand() % 2);
							else
								DoTeleport(target, 191 + rand() % 2, 4010 + rand() % 2);
							pMob[target].MOB.CurrentScore.Hp = pMob[target].MOB.CurrentScore.MaxHp;
							pMob[target].MOB.CurrentScore.Mp = pMob[target].MOB.CurrentScore.MaxMp;
							SendScore(target);
							SendSetHpMp(target);
							return;
						}
	
	
						STRUCT_ITEM presente = { 476, 0, 0, 0 };
						PutItem(target, &presente);
						//pUser[conn].Honra += 5;
						SendClientMessage(target, "Recebeu um prêmio de consolo da Arena Real.");
						DoRecall(target);
						pMob[target].MOB.CurrentScore.Hp = pMob[target].MOB.CurrentScore.MaxHp;
						pMob[target].MOB.CurrentScore.Mp = pMob[target].MOB.CurrentScore.MaxMp;
						pMob[target].GetCurrentScore(target);
						SendScore(target);
						SendSetHpMp(target);
						DoTeleport(target, 2132 + rand() % 5, 2147 + rand() % 5);
						return;
					}
				}
			}
	#pragma endregion
			
		}


#pragma region Morte nas quests
	//Coveiro
	if (pMob[conn].TargetX > 2379 && pMob[conn].TargetY > 2076 && pMob[conn].TargetX < 2426 && pMob[conn].TargetY < 2133)
		pMob[conn].extra.CheckTimeKersef = 0;

	//Jardin
	if (pMob[conn].TargetX > 2228 && pMob[conn].TargetY > 1700 && pMob[conn].TargetX < 2257 && pMob[conn].TargetY < 1728)
		pMob[conn].extra.CheckTimeKersef = 0;

	//Kaizen
	if (pMob[conn].TargetX > 459 && pMob[conn].TargetY > 3887 && pMob[conn].TargetX < 497 && pMob[conn].TargetY < 3916)
		pMob[conn].extra.CheckTimeKersef = 0;

	//Hidra
	if (pMob[conn].TargetX > 658 && pMob[conn].TargetY > 3728 && pMob[conn].TargetX < 703 && pMob[conn].TargetY < 3762)
		pMob[conn].extra.CheckTimeKersef = 0;

	//Elfos
	if (pMob[conn].TargetX > 1312 && pMob[conn].TargetY > 4027 && pMob[conn].TargetX < 1348 && pMob[conn].TargetY < 4055)
		pMob[conn].extra.CheckTimeKersef = 0;
#pragma endregion	

#pragma region Morte nas Lans
	//LAN N	 
	if (pMob[conn].TargetX > 3604 && pMob[conn].TargetY > 3604 && pMob[conn].TargetX < 3691 && pMob[conn].TargetY < 3690)
		pMob[conn].extra.CheckTimeKersef = 0;

	//LAN M 
	if (pMob[conn].TargetX > 3732 && pMob[conn].TargetY > 3476 && pMob[conn].TargetX < 3819 && pMob[conn].TargetY < 3563)
		pMob[conn].extra.CheckTimeKersef = 0;

	//LAN A
	if (pMob[conn].TargetX > 3860 && pMob[conn].TargetY > 3604 && pMob[conn].TargetX < 3946 && pMob[conn].TargetY < 3690)
		pMob[conn].extra.CheckTimeKersef = 0;

#pragma endregion	 

	int Face = pMob[conn].MOB.Equip[0].sIndex;

#pragma region Crias EXP
	if (conn >= MAX_USER && pMob[conn].MOB.Clan == 4 && Face >= 315 && Face <= 345 && target > MAX_USER && pMob[target].MOB.Clan != 4)
	{
		int summoner = pMob[conn].Summoner;

		if (summoner > 0 && summoner < MAX_USER && pUser[summoner].Mode && pMob[summoner].Mode)
		{
			STRUCT_ITEM* Mount = &pMob[summoner].MOB.Equip[14];

			if (pMob[summoner].MOB.Equip[14].sIndex >= 2330 && pMob[summoner].MOB.Equip[14].sIndex < 2390)
			{
				unsigned char XP = Mount->stEffect[1].cEffect;
				unsigned char Crescimento = Mount->stEffect[2].cValue;

				unsigned char exp = XP + 100;

				if (Mount->sIndex == 2330)
					exp = XP + 25;

				else if (Mount->sIndex == 2331)
					exp = XP + 35;

				else if (Mount->sIndex == 2332)
					exp = XP + 45;

				else if (Mount->sIndex == 2333)
					exp = XP + 55;

				else if (Mount->sIndex == 2334)
					exp = XP + 65;

				else if (Mount->sIndex == 2335)
					exp = XP + 75;

				if (XP < pMob[target].MOB.CurrentScore.Level && XP < 100)
				{
					Crescimento = Crescimento + 1;

					if (Crescimento < exp)
					{
						Mount->stEffect[2].cValue = Crescimento;
						SendItem(summoner, ITEM_PLACE_EQUIP, 14, &pMob[summoner].MOB.Equip[14]);
					}
					else
					{
						Crescimento = 1;
						XP = XP + 1;
						Mount->stEffect[2].cValue = 1;
						Mount->stEffect[1].cEffect = XP;

						SendMsgExp(summoner, g_pMessageStringTable[_NN_Mount_Level], TNColor::Default, false);
						SendItem(summoner, ITEM_PLACE_EQUIP, 14, &pMob[summoner].MOB.Equip[14]);
						MountProcess(summoner, &pMob[conn].MOB.Equip[14]);
					}
				}
			}
		}
	}

#pragma endregion

#pragma region Invocações
	MSG_CNFMobKill sm;
	memset(&sm, 0, sizeof(MSG_CNFMobKill));

	sm.Type = _MSG_CNFMobKill;
	sm.Size = sizeof(MSG_CNFMobKill);
	sm.ID = ESCENE_FIELD;

	sm.KilledMob = target;
	sm.Killer = conn;

	pMob[target].MOB.CurrentScore.Hp = 0;

	int Leader = pMob[conn].Leader;

	if (Leader == 0)
		Leader = conn;

	if (conn >= MAX_USER && pMob[conn].MOB.Clan == 4)
	{
		int Summoner = pMob[conn].Summoner;

		if (Summoner <= 0 || Summoner >= MAX_USER || pUser[Summoner].Mode != USER_PLAY)
		{
			GridMulticast(pMob[target].TargetX, pMob[target].TargetY, (MSG_STANDARD*)&sm, 0);

			if (target > MAX_USER)
				DeleteMob(target, 1);

			return;
		}

		conn = Summoner;
	}
#pragma endregion 
#pragma region PvE
	if (target >= MAX_USER || pMob[target].MOB.BaseScore.Level > MAX_LEVEL + 5)
	{
		if (target >= MAX_USER || pMob[target].MOB.BaseScore.Level <= MAX_LEVEL)
		{
			if (conn < MAX_USER && pMob[target].MOB.Clan != 4)
			{
#pragma region Distribuição da EXP
				int MobExp = GetExpApply(pMob[conn].extra, (int)pMob[target].MOB.Exp, pMob[conn].MOB.CurrentScore.Level, pMob[target].MOB.CurrentScore.Level);
				int FinalExp = 0;

				// TODO: Change this UNK_s to something else.
				int UNK_1 = 30;
				int UNK_2 = 0;
				int UNK_3 = pMob[conn].extra.ClassMaster;

				int tx = pMob[conn].TargetX;
				int ty = pMob[conn].TargetY;

				int party = 0;

				if (UNK_3 > 0 && UNK_3 <= MAX_PARTY)
				{
					int NumMob = g_EmptyMob + UNK_3;

					if (UNK_3 > 1)
						NumMob = NumMob + PARTYBONUS - 100;

					int eMob = MobExp;
					int isExp = NumMob * MobExp / 100;

					struct tm when;
					time_t now;
					time(&now);
					when = *localtime(&now);

					for (int i = 0; i < MAX_PARTY + 1; ++i)
					{
						party = 0;

						if (Leader && i < MAX_PARTY)
							party = pMob[Leader].PartyList[i];
						else
							party = Leader;
#pragma region Pesa A
						if (party > 0 && party < MAX_USER && pMob[party].MOB.CurrentScore.Hp > 0 && (tx / 128) == 9 && (pMob[party].TargetX / 128) == 9
							&& (ty / 128) == 1 && (pMob[party].TargetY / 128) == 1)
						{
							isExp = GetExpApply(pMob[party].extra, (int)pMob[target].MOB.Exp, pMob[party].MOB.CurrentScore.Level, pMob[target].MOB.CurrentScore.Level);

							int myLevel = pMob[party].MOB.CurrentScore.Level;

							//if (pMob[party].extra.ClassMaster != MORTAL && pMob[party].extra.ClassMaster != ARCH)
							//	myLevel += MAX_LEVEL + 1;

							long long int exp = (UNK_1 + myLevel) * isExp / (UNK_1 + myLevel);
							if (exp > 0 && exp <= 10000000)
							{
								if (pMob[conn].ExpBonus > 0 && pMob[conn].ExpBonus < 500)
									exp += exp * pMob[conn].ExpBonus / 100;

								if (RvRBonus && RvRBonus == pMob[party].MOB.Clan)
									exp += (exp * 20) / 100;

								if (NewbieEventServer && pMob[party].MOB.CurrentScore.Level < 100 && pMob[party].extra.ClassMaster != CELESTIAL && pMob[party].extra.ClassMaster != CELESTIALCS && pMob[party].extra.ClassMaster != SCELESTIAL)
									exp += exp / 4;

								if (DOUBLEMODE)
									exp *= 2;


								if (KefraLive == 0)
									exp /= 2;

								if (NewbieEventServer)
									exp += (exp * 15) / 100;
								else
									exp -= (exp * 15) / 100;

								int ESCURIDAO = mNPCGen.pList[Escuridao].CurrentNumMob;
								int ERIN = mNPCGen.pList[Erin].CurrentNumMob;
								int FENIX = mNPCGen.pList[Fenix].CurrentNumMob;
								int KARA = mNPCGen.pList[Kara].CurrentNumMob;
								int KEI = mNPCGen.pList[Kei].CurrentNumMob;
								int KEMI = mNPCGen.pList[Kemi].CurrentNumMob;
								int LEAO = mNPCGen.pList[Leao].CurrentNumMob;
								int UIE = mNPCGen.pList[Yue].CurrentNumMob;

								if (ESCURIDAO == 0)
									exp -= (exp * 10) / 100;

								if (ERIN == 0)
									exp -= (exp * 10) / 100;

								if (FENIX == 0)
									exp -= (exp * 10) / 100;

								if (KARA == 0)
									exp -= (exp * 10) / 100;

								if (KEI == 0)
									exp -= (exp * 10) / 100;

								if (KEMI == 0)
									exp -= (exp * 10) / 100;

								if (LEAO == 0)
									exp -= (exp * 10) / 100;

								if (UIE == 0)
									exp -= (exp * 10) / 100;


#pragma region Log de Experiência diário
								if (when.tm_yday != pMob[party].extra.DayLog.YearDay)
									pMob[party].extra.DayLog.Exp = 0;

								pMob[party].extra.DayLog.YearDay = when.tm_yday;
								pMob[party].extra.DayLog.Exp += exp;
#pragma endregion

								if (pMob[party].extra.Hold > 0 && (unsigned int)exp >= pMob[party].extra.Hold)
								{
									int nhold = pMob[party].extra.Hold - exp;

									if (nhold < 0)
										nhold = 0;

									exp -= pMob[party].extra.Hold;
									pMob[party].extra.Hold = nhold;
								}

								else if (pMob[party].extra.Hold > 0 && (unsigned int)exp < pMob[party].extra.Hold)
								{
									pMob[party].extra.Hold -= exp;
									continue;
								}

								pMob[party].MOB.Exp += exp;

#pragma region RankingUpdateExp
								STRUCT_RANKING rankInfo = STRUCT_RANKING(pMob[party].MOB.MobName, pMob[party].MOB.Exp, pMob[party].extra.ClassMaster, pMob[party].MOB.CurrentScore.Level, pMob[party].MOB.Class, pMob[party].MOB.Guild, pMob[party].MOB.Clan);
								//doRanking(party);
								MSG_UpdateExpRanking expRankingPacket = MSG_UpdateExpRanking(party, rankInfo);
								DBServerSocket.SendOneMessage((char*)&expRankingPacket, sizeof(expRankingPacket));
#pragma endregion
							}
						}
#pragma endregion

#pragma region Pesa M
						else if (party > 0 && party < MAX_USER && pMob[party].MOB.CurrentScore.Hp > 0 && (tx / 128) == 8 && (pMob[party].TargetX / 128) == 8 && (ty / 128) == 2 && (pMob[party].TargetY / 128) == 2)

						{
							isExp = GetExpApply(pMob[party].extra, (int)pMob[target].MOB.Exp, pMob[party].MOB.CurrentScore.Level, pMob[target].MOB.CurrentScore.Level);

							int myLevel = pMob[party].MOB.CurrentScore.Level;

							//if (pMob[party].extra.ClassMaster != MORTAL && pMob[party].extra.ClassMaster != ARCH)
							//	myLevel += MAX_LEVEL + 1;

							long long int exp = (UNK_1 + myLevel) * isExp / (UNK_1 + myLevel);
							if (exp > 0 && exp <= 10000000)
							{
								if (pMob[party].extra.ClassMaster != MORTAL && pMob[party].extra.ClassMaster != ARCH)
									exp = 0;

								if (pMob[conn].ExpBonus > 0 && pMob[conn].ExpBonus < 500)
									exp += exp * pMob[conn].ExpBonus / 100;

								if (RvRBonus && RvRBonus == pMob[party].MOB.Clan)
									exp += (exp * 20) / 100;

								if (NewbieEventServer && pMob[party].MOB.CurrentScore.Level < 100 && pMob[party].extra.ClassMaster != CELESTIAL && pMob[party].extra.ClassMaster != CELESTIALCS && pMob[party].extra.ClassMaster != SCELESTIAL)
									exp += exp / 4;

								if (DOUBLEMODE)
									exp *= 2;

								if (KefraLive == 0)
									exp /= 2;

								if (NewbieEventServer)
									exp += (exp * 15) / 100;
								else
									exp -= (exp * 15) / 100;

								int ARNOLD_ = mNPCGen.pList[Arnold_].CurrentNumMob;
								int LAINY = mNPCGen.pList[Lainy].CurrentNumMob;
								int REIMERS = mNPCGen.pList[Reimers].CurrentNumMob;
								int ROPERION = mNPCGen.pList[RoPerion].CurrentNumMob;
								int IRENA = mNPCGen.pList[Irena].CurrentNumMob;

								if (ARNOLD_ == 0)
									exp -= (exp * 10) / 100;

								if (LAINY == 0)
									exp -= (exp * 10) / 100;

								if (REIMERS == 0)
									exp -= (exp * 10) / 100;

								if (ROPERION == 0)
									exp -= (exp * 10) / 100;

								if (IRENA == 0)
									exp -= (exp * 10) / 100;



#pragma region Log de Experiência diário
								if (when.tm_yday != pMob[party].extra.DayLog.YearDay)
									pMob[party].extra.DayLog.Exp = 0;

								pMob[party].extra.DayLog.YearDay = when.tm_yday;
								pMob[party].extra.DayLog.Exp += exp;
#pragma endregion

								if (pMob[party].extra.Hold > 0 && (unsigned int)exp >= pMob[party].extra.Hold)
								{
									int nhold = pMob[party].extra.Hold - exp;

									if (nhold < 0)
										nhold = 0;

									exp -= pMob[party].extra.Hold;
									pMob[party].extra.Hold = nhold;
								}

								else if (pMob[party].extra.Hold > 0 && (unsigned int)exp < pMob[party].extra.Hold)
								{
									pMob[party].extra.Hold -= exp;
									continue;
								}

								pMob[party].MOB.Exp += exp;
#pragma region RankingUpdateExp
								STRUCT_RANKING rankInfo = STRUCT_RANKING(pMob[party].MOB.MobName, pMob[party].MOB.Exp, pMob[party].extra.ClassMaster, pMob[party].MOB.CurrentScore.Level, pMob[party].MOB.Class, pMob[party].MOB.Guild, pMob[party].MOB.Clan);
								//doRanking(party);
								MSG_UpdateExpRanking expRankingPacket = MSG_UpdateExpRanking(party, rankInfo);
								DBServerSocket.SendOneMessage((char*)&expRankingPacket, sizeof(expRankingPacket));
#pragma endregion
							}
						}
#pragma endregion
#pragma region Pesa N
						else if (party > 0 && party < MAX_USER && pMob[party].MOB.CurrentScore.Hp > 0 && (tx / 128) == 10 && (pMob[party].TargetX / 128) == 10 && (ty / 128) == 2 && (pMob[party].TargetY / 128) == 2)
						{
							isExp = GetExpApply(pMob[party].extra, (int)pMob[target].MOB.Exp, pMob[party].MOB.CurrentScore.Level, pMob[target].MOB.CurrentScore.Level);

							int myLevel = pMob[party].MOB.CurrentScore.Level;

							//if (pMob[party].extra.ClassMaster != MORTAL && pMob[party].extra.ClassMaster != ARCH)
							//	myLevel += MAX_LEVEL + 1;

							long long int exp = (UNK_1 + myLevel) * isExp / (UNK_1 + myLevel);
							if (exp > 0 && exp <= 10000000)
							{
								if (pMob[party].extra.ClassMaster != MORTAL && pMob[party].extra.ClassMaster != ARCH)
									exp = 0;

								if (pMob[conn].ExpBonus > 0 && pMob[conn].ExpBonus < 500)
									exp += exp * pMob[conn].ExpBonus / 100;

								if (RvRBonus && RvRBonus == pMob[party].MOB.Clan)
									exp += (exp * 20) / 100;

								if (NewbieEventServer && pMob[party].MOB.CurrentScore.Level < 100 && pMob[party].extra.ClassMaster != CELESTIAL && pMob[party].extra.ClassMaster != CELESTIALCS && pMob[party].extra.ClassMaster != SCELESTIAL)
									exp += exp / 4;

								if (DOUBLEMODE)
									exp *= 2;

								if (KefraLive == 0)
									exp /= 2;

								if (NewbieEventServer)
									exp += (exp * 15) / 100;
								else
									exp -= (exp * 15) / 100;

								int MARTIN = mNPCGen.pList[Martin].CurrentNumMob;
								int BALMERS = mNPCGen.pList[Balmers].CurrentNumMob;
								int RUBYEN = mNPCGen.pList[Rubyen].CurrentNumMob;
								int NAOMI = mNPCGen.pList[Naomi].CurrentNumMob;
								int ARNOLD = mNPCGen.pList[Arnold].CurrentNumMob;

								if (MARTIN == 0)
									exp -= (exp * 10) / 100;

								if (BALMERS == 0)
									exp -= (exp * 10) / 100;

								if (RUBYEN == 0)
									exp -= (exp * 10) / 100;

								if (NAOMI == 0)
									exp -= (exp * 10) / 100;

								if (ARNOLD == 0)
									exp -= (exp * 10) / 100;

#pragma region Log de Experiência diário
								if (when.tm_yday != pMob[party].extra.DayLog.YearDay)
									pMob[party].extra.DayLog.Exp = 0;

								pMob[party].extra.DayLog.YearDay = when.tm_yday;
								pMob[party].extra.DayLog.Exp += exp;


								if (pMob[party].extra.Hold > 0 && (unsigned int)exp >= pMob[party].extra.Hold)
								{
									int nhold = pMob[party].extra.Hold - exp;

									if (nhold < 0)
										nhold = 0;

									exp -= pMob[party].extra.Hold;
									pMob[party].extra.Hold = nhold;
								}

								else if (pMob[party].extra.Hold > 0 && (unsigned int)exp < pMob[party].extra.Hold)
								{
									pMob[party].extra.Hold -= exp;
									continue;
								}

								pMob[party].MOB.Exp += exp;
#pragma region RankingUpdateExp
								STRUCT_RANKING rankInfo = STRUCT_RANKING(pMob[party].MOB.MobName, pMob[party].MOB.Exp, pMob[party].extra.ClassMaster, pMob[party].MOB.CurrentScore.Level, pMob[party].MOB.Class, pMob[party].MOB.Guild, pMob[party].MOB.Clan);
								//doRanking(party);
								MSG_UpdateExpRanking expRankingPacket = MSG_UpdateExpRanking(party, rankInfo);
								DBServerSocket.SendOneMessage((char*)&expRankingPacket, sizeof(expRankingPacket));

							}
						}
#pragma endregion
#pragma region >> EXP GERAL
						else if (party > 0 && party < MAX_USER && pMob[party].MOB.CurrentScore.Hp > 0 && tx >= pMob[party].TargetX - HALFGRIDX
							&& tx <= pMob[party].TargetX + HALFGRIDX && ty >= pMob[party].TargetY - HALFGRIDY && ty <= pMob[party].TargetY + HALFGRIDY)
						{
							isExp = GetExpApply(pMob[party].extra, (int)pMob[target].MOB.Exp, pMob[party].MOB.CurrentScore.Level, pMob[target].MOB.CurrentScore.Level);

							int myLevel = pMob[party].MOB.CurrentScore.Level;

							/*if (pMob[party].extra.ClassMaster != MORTAL && pMob[party].extra.ClassMaster != ARCH)
								myLevel += MAX_LEVEL + 1;*/

							long long int exp = isExp;

							if (exp > 0 && exp <= 10000000)
							{
								/*if (pMob[party].extra.ClassMaster == ARCH)
									exp /= 2;

								if (pMob[party].extra.ClassMaster != MORTAL && pMob[party].extra.ClassMaster != ARCH)
									exp /= 5;*/

								if (pMob[conn].ExpBonus > 0 && pMob[conn].ExpBonus < 500)
									exp += exp * pMob[conn].ExpBonus / 100;

								if (RvRBonus == pMob[party].MOB.Clan)
									exp += (exp * 10) / 100;

								if (DOUBLEMODE)
									exp *= 2;

								/*if (NewbieEventServer)
									exp += (exp * 15) / 100;
								else
									exp -= (exp * 15) / 100;*/

#pragma region Log de Experiência diário
								if (when.tm_yday != pMob[party].extra.DayLog.YearDay)
									pMob[party].extra.DayLog.Exp = 0;

								pMob[party].extra.DayLog.YearDay = when.tm_yday;
								pMob[party].extra.DayLog.Exp += exp;
#pragma endregion

								if (pMob[party].extra.Hold > 0 && (unsigned int)exp >= pMob[party].extra.Hold)
								{
									int nhold = pMob[party].extra.Hold - exp;

									if (nhold < 0)
										nhold = 0;

									exp -= pMob[party].extra.Hold;
									pMob[party].extra.Hold = nhold;
								}

								else if (pMob[party].extra.Hold > 0 && (unsigned int)exp < pMob[party].extra.Hold)
								{
									pMob[party].extra.Hold -= exp;
									continue;
								}

								pMob[party].MOB.Exp += exp;
#pragma region RankingUpdateExp
								STRUCT_RANKING rankInfo = STRUCT_RANKING(pMob[party].MOB.MobName, pMob[party].MOB.Exp, pMob[party].extra.ClassMaster, pMob[party].MOB.CurrentScore.Level, pMob[party].MOB.Class, pMob[party].MOB.Guild, pMob[party].MOB.Clan);
								//doRanking(party);
								MSG_UpdateExpRanking expRankingPacket = MSG_UpdateExpRanking(party, rankInfo);
								DBServerSocket.SendOneMessage((char*)&expRankingPacket, sizeof(expRankingPacket));
#pragma endregion
							}
						}
					}

#pragma endregion

#pragma region Targets Monstros
					int GenerateIndex = pMob[target].GenerateIndex;
					int DieSay = rand() % 4;

					if (GenerateIndex >= 0 && mNPCGen.pList[GenerateIndex].DieAction[DieSay][0] && pMob[target].Leader == 0)
						SendChat(target, mNPCGen.pList[GenerateIndex].DieAction[DieSay]);

					GridMulticast(pMob[target].TargetX, pMob[target].TargetY, (MSG_STANDARD*)&sm, 0);

					if (pMob[conn].MOB.Clan && pMob[conn].MOB.Clan != 4 && pMob[conn].MOB.Clan != 7 && pMob[conn].MOB.Clan != 8)
						DeleteMob(target, 1);

					else
					{
						int AlvoX = PosX;
						if (!PosX)
							AlvoX = pMob[target].TargetX;

						int AlvoY = PosY;
						if (!PosY)
							AlvoY = pMob[target].TargetY;

						if (pMob[target].GenerateIndex == CARONTE)
						{
							GenerateMob(SICARIO, 1124, 1471);
						}

						if (pMob[target].GenerateIndex == SICARIO)
						{

							int partyleader = pMob[conn].Leader;

							if (partyleader <= 0)
								partyleader = conn;

							STRUCT_ITEM gift;
							memset(&gift, 0, sizeof(STRUCT_ITEM));

							int _rand = rand() % 6;

							int Gift[6][7] = {
							{ 1773, 0, 0, 0, 0, 0, 0 },
							{ 1773, 0, 0, 0, 0, 0, 0 },
							{ 1773, 0, 0, 0, 0, 0, 0 },
							{ 1773, 0, 0, 0, 0, 0, 0 },
							{ 1773, 0, 0, 0, 0, 0, 0 },
							{ 1773, 0, 0, 0, 0, 0, 0 },
							};

							gift.sIndex = Gift[rand() % 6][0];
							gift.stEffect[0].cEffect = Gift[_rand][1];
							gift.stEffect[0].cValue = Gift[_rand][2];
							gift.stEffect[1].cEffect = Gift[_rand][3];
							gift.stEffect[1].cValue = Gift[_rand][4];
							gift.stEffect[2].cEffect = Gift[_rand][5];
							gift.stEffect[2].cValue = Gift[_rand][6];

							if (partyleader > 0 && partyleader < MAX_USER);
							DoTeleport(partyleader, 2100, 2100);

							for (int i = 0; i < MAX_PARTY; i++)
							{
								int partymember = pMob[partyleader].PartyList[i];
								if (pUser[partymember].Mode != USER_PLAY)
									continue;
								DoTeleport(partymember, 2100, 2100);
								PutItem(partymember, &gift);
								PutItem(partyleader, &gift);

								pUser[partymember].Honra += 5;
								pUser[partyleader].Honra += 5;
								SendMsgExp(partymember, "+ 5 pontos de Honra", TNColor::NewYellow, false);
								SendMsgExp(partyleader, "+ 5 pontos de Honra", TNColor::NewYellow, false);
							}


						}




#pragma region Sombra Negra
						if (pMob[target].GenerateIndex == SOMBRANEGRA)
						{
							STRUCT_ITEM item;
							memset(&item, 0, sizeof(STRUCT_ITEM));

							item.sIndex = 3172;
							item.stEffect[0].cEffect = 0;
							item.stEffect[0].cValue = 0;
							item.stEffect[1].cEffect = 0;
							item.stEffect[1].cValue = 0;
							item.stEffect[2].cEffect = 0;
							item.stEffect[2].cValue = 0;

							if (PutItem(conn, &item)){
								SendClientMessage(conn, "Você recebeu [01][Carta Duelo N]");
							}
							g_BSombraNegra = FALSE;
						}
#pragma endregion
#pragma region Verid Negro
						if (pMob[target].GenerateIndex == VERIDNEGRO)
						{
							STRUCT_ITEM item;
							memset(&item, 0, sizeof(STRUCT_ITEM));

							item.sIndex = 3172;
							item.stEffect[0].cEffect = 61;
							item.stEffect[0].cValue = 2;
							item.stEffect[1].cEffect = 0;
							item.stEffect[1].cValue = 0;
							item.stEffect[2].cEffect = 0;
							item.stEffect[2].cValue = 0;

							if (PutItem(conn, &item))
								SendClientMessage(conn, "Você recebeu [02][Carta Duelo N]");
							g_BVerid = FALSE;
						}
#pragma endregion
#pragma region Verid Negro
						if (pMob[target].GenerateIndex == ESPELHO_RAINHAG)
						{
							int Group = ServerGroup;
							int Server = pMob[conn].MOB.Guild / MAX_GUILD;
							int usGuild = pMob[conn].MOB.Guild;

							char guildname[256];

							BASE_GetGuildName(Group, usGuild, guildname);

							MSG_GuildInfo sm_gi;
							memset(&sm_gi, 0, sizeof(MSG_GuildInfo));

							sm_gi.Type = _MSG_GuildInfo;
							sm_gi.Size = sizeof(MSG_GuildInfo);
							sm_gi.ID = conn;

							sm_gi.Guild = usGuild;
							GuildInfo[usGuild].Fame += 15;

							auto& pc = cSQL::instance();
							sprintf(xQuery, "UPDATE `guilds` SET fame = '%d' WHERE `guild` = '%d'", GuildInfo[usGuild].Fame + 15, usGuild);
							pc.wQuery(xQuery);

							sm_gi.GuildInfo = GuildInfo[usGuild];

							SendNotice(strFmt("O jogador %s derrotou a Rainha do Gelo! A Guild %s recebeu 15 de Fama !", pMob[conn].MOB.MobName, guildname));

							DBServerSocket.SendOneMessage((char*)&sm_gi, sizeof(MSG_GuildInfo));
							g_RainhaG = FALSE;
						}
#pragma endregion


						//#pragma region Espelho Rainha
						//						if (pMob[target].GenerateIndex == ESPELHO_RAINHAG && EspelhoLive == 1)
						//						{
						//							// BOSS PARTE 1
						//							for (int w = BOSS1_INITIAL; w <= BOSS1_END; w++)
						//								GenerateMob(w, 0, 0);
						//
						//							// BOSS PARTE 2
						//							for (int x = BOSS1_INITIAL2; x <= BOSS1_END2; x++)
						//								GenerateMob(x, 0, 0);
						//
						//							STRUCT_ITEM tItem;
						//							memset(&tItem, 0, sizeof(STRUCT_ITEM));
						//
						//							//tItem.sIndex = 676;
						//
						//							//PutItem(conn, &tItem);
						//
						//							EspelhoLive = 2;
						//						}
						//#pragma endregion
						//#pragma region Sombra Negra
						//						if (pMob[target].GenerateIndex == SOMBRANEGRA)
						//						{
						//							int partyleader = pMob[conn].Leader;
						//
						//							if (partyleader <= 0)
						//								partyleader = conn;
						//							int i = 0;
						//							int partymember = pMob[partyleader].PartyList[i];
						//
						//							if (partyleader > 0 && partyleader < MAX_USER)
						//								DoTeleport(partyleader, 3844, 2879);
						//
						//							for (int i = 0; i < MAX_PARTY; i++)
						//							{
						//								int partymember = pMob[partyleader].PartyList[i];
						//								if (pUser[partymember].Mode != USER_PLAY)
						//									continue;
						//									DoTeleport(partymember, 3844, 2879);
						//							}
						//							
						//							GenerateMob(VERIDRAINHAG, 0, 0);
						//						}
						//#pragma endregion
						//#pragma region VeridRainhaG
						//						if (pMob[target].GenerateIndex == VERIDRAINHAG)
						//						{
						//							// BOSS PARTE 1
						//							for (int w = BOSS1_INITIAL; w <= BOSS1_END; w++)
						//								mNPCGen.pList[w].MinuteGenerate = 3;
						//							// BOSS PARTE 2
						//							for (int x = BOSS1_INITIAL2; x <= BOSS1_END2; x++)
						//								mNPCGen.pList[x].MinuteGenerate = 3;
						//
						//							DoRecall(conn);
						//
						//							SendClientMessage(conn, "Parabéns você concluiu a Quest.");
						//							for (int i = 0; i < MAX_PARTY; i++)
						//							{
						//								int partyconn = pMob[conn].PartyList[i];
						//
						//								if (partyconn > 0 && partyconn < MAX_USER && partyconn != conn && pUser[partyconn].Mode == USER_PLAY)
						//								{
						//									DoRecall(partyconn);
						//									EspelhoLive = 0;
						//									SendMsgExp(partyconn, "Parabéns vocês concluiram a Quest.", TNColor::Default, false);
						//								}
						//							}
						//						}
						//#pragma endregion
#pragma region Tarantula
						if (pMob[target].GenerateIndex == CTARANTULA)
						{
							
							TarantulaKilled = TRUE;

							for (int w = PI_INITIAL2; w <= PI_END2; w++)
								GenerateMob(w, 0, 0);

							for (int x = PI_INITIAL3; x <= PI_END3; x++)
								GenerateMob(x, 0, 0);

							for (int y = PI_INITIAL4; y <= PI_END4; y++)
								GenerateMob(y, 0, 0);

							for (int z = PI_INITIAL5; z <= PI_END5; z++)
								GenerateMob(z, 0, 0);

							RandBoss = rand() % 2 + 1;

							Lich_1 = 1;
							Lich_2 = 1;
							Lich_3 = 1;
							Lich_4 = 1;

						}

						if (RandBoss == 1)
						{
							if (pMob[target].GenerateIndex == LICHBOSS1)
								Lich_1 = 0;

							if (pMob[target].GenerateIndex == LICHBOSS2)
								Lich_2 = 2;

							if (pMob[target].GenerateIndex == LICHBOSS3)
								Lich_3 = 0;

							if (pMob[target].GenerateIndex == LICHBOSS4)
								Lich_4 = 2;
						}

						if (RandBoss == 2)
						{
							if (pMob[target].GenerateIndex == LICHBOSS1)
								Lich_2 = 0;

							if (pMob[target].GenerateIndex == LICHBOSS2)
								Lich_1 = 2;

							if (pMob[target].GenerateIndex == LICHBOSS3)
								Lich_4 = 0;

							if (pMob[target].GenerateIndex == LICHBOSS4)
								Lich_3 = 2;
						}
#pragma endregion
#pragma region Kefra
						if (pMob[target].GenerateIndex == KEFRA_BOSS)
						{
							if (pMob[conn].MOB.Guild)
							{
								int Group = ServerGroup;
								int Server = pMob[conn].MOB.Guild / MAX_GUILD;
								int usGuild = pMob[conn].MOB.Guild;

								char guildname[256];

								BASE_GetGuildName(Group, usGuild, guildname);

								KefraLive = usGuild;

								MSG_GuildInfo sm_gi;
								memset(&sm_gi, 0, sizeof(MSG_GuildInfo));

								sm_gi.Type = _MSG_GuildInfo;
								sm_gi.Size = sizeof(MSG_GuildInfo);
								sm_gi.ID = conn;

								sm_gi.Guild = usGuild;
								GuildInfo[usGuild].Fame += 100; // A GUILD QUE MATAR KEFRA GANHA 100 DE FAMA

								sm_gi.GuildInfo = GuildInfo[usGuild];

								auto& pc = cSQL::instance();
								sprintf(xQuery, "UPDATE `guilds` SET fame = '%d' WHERE `guild` = '%d'", GuildInfo[usGuild].Fame + 100, usGuild);
								pc.wQuery(xQuery);

								DBServerSocket.SendOneMessage((char*)&sm_gi, sizeof(MSG_GuildInfo));
								SendNotice(strFmt(g_pMessageStringTable[_SN_End_Khepra], guildname));

								DrawConfig(TRUE);
							}

							else
							{
								KefraLive = 1;
								SendNotice(strFmt(g_pMessageStringTable[_SN_End_Khepra], "FD"));

								DrawConfig(TRUE);
							}

							for (int xx = 2335; xx < 2395; xx++)
							{
								for (int yy = 3896; yy < 3955; yy++)
								{
									int tmob = pMobGrid[yy][xx];

									if (tmob < MAX_USER)
										continue;

									int itemrand = rand() % 60;

									int DropKefra[1][14] =
									{
										{
										  413, 413, 413, 1740, 1741, 1760, 1761, 1762, 1763, 3172, 3172, 3140, 3140, 3140
										},
									};
									STRUCT_ITEM Item; // DROP KEFRA
									Item.sIndex = DropKefra[0][rand() % 14];
									CreateItem(2354, 3919, &Item, rand() % 100, 5);
									CreateItem(2365, 3914, &Item, rand() % 100, 5);
									CreateItem(2380, 3920, &Item, rand() % 100, 5);
									CreateItem(2380, 3946, &Item, rand() % 100, 5);
									CreateItem(2350, 3945, &Item, rand() % 100, 5);
									CreateItem(2366, 3944, &Item, rand() % 100, 5);
									CreateItem(2350, 3945, &Item, rand() % 100, 5);
									CreateItem(2381, 3932, &Item, rand() % 100, 5);
									CreateItem(2352, 3932, &Item, rand() % 100, 5);
								}
							}

							SystemLog("-system", "-", 0, strFmt("etc,kefra killed player %d", pMob[conn].MOB.MobName));
						}
#pragma endregion

						if (pHeightGrid[AlvoY][AlvoX] >= -105 && pHeightGrid[AlvoY][AlvoX] < 115)
						{
							int GenerateID = pMob[target].GenerateIndex;

#pragma region Portões de Noatum
							if (pMob[target].MOB.Equip[0].sIndex == 220 && CastleState)
							{
								if (pMob[target].TargetX < 0 || pMob[target].TargetX >= MAX_GRIDX || pMob[target].TargetY < 0 || pMob[target].TargetY >= MAX_GRIDY)
								{
									SystemLog("-system", "-", 0, "err,no castle gate to open pos");
									return;
								}

								int ItemID = pItemGrid[pMob[target].TargetY][pMob[target].TargetX];
								if (ItemID >= 0 && ItemID < MAX_ITEM && pItem[ItemID].Mode)
								{
									int heigth = 0;
									int isUpdate = UpdateItem(ItemID, 1, &heigth);
									if (isUpdate)
									{
										MSG_UpdateItem UpdateIt;

										UpdateIt.ID = ESCENE_FIELD;
										UpdateIt.Type = _MSG_UpdateItem;

										UpdateIt.ItemID = ItemID + 10000;

										UpdateIt.Size = sizeof(MSG_UpdateItem);

										//UpdateIt.Height = heigth;

										UpdateIt.State = pItem[ItemID].State;

										GridMulticast(pItem[ItemID].PosX, pItem[ItemID].PosY, (MSG_STANDARD*)&UpdateIt, 0);

										pItem[ItemID].Delay = 0;
									}
								}

								else
									SystemLog("-system", "-", 0, "err,no castle gate to open pos");
							}
#pragma endregion
#pragma region Drops especiais - IMP - NYERDS - AGUA - REI - ZAKUM
							else
							{
#pragma region Agua M
								//AguaM
								if (GenerateID >= WATER_M_INITIAL && GenerateID <= WATER_M_INITIAL + 7)
								{
									int CurrentNumMob = mNPCGen.pList[GenerateID].CurrentNumMob;

									if (CurrentNumMob == 1)
									{
										int Sala = GenerateID - WATER_M_INITIAL;

										if (WaterClear1[1][Sala] > 15)
											WaterClear1[1][Sala] = 15;


										int partyleader = pMob[conn].Leader;

										if (partyleader <= 0)
											partyleader = conn;

										int slot_free = -1;

										STRUCT_ITEM Perga;
										memset(&Perga, 0, sizeof(STRUCT_ITEM));

										Perga.sIndex = 778 + Sala;

										if (partyleader > 0 && partyleader < MAX_USER)
											PutItem(partyleader, &Perga);

										SendClientSignalParm(partyleader, ESCENE_FIELD, _MSG_StartTime, WaterClear1[1][Sala] * 2);

										for (int i = 0; i < MAX_PARTY; i++)
										{
											int partymember = pMob[partyleader].PartyList[i]; // tu não pagou mas vou corrigir, isso acontece na agua tbm

											if (partymember >= MAX_USER) continue;

											if (pUser[partymember].Mode == USER_PLAY)
											{

												SendClientSignalParm(partymember, ESCENE_FIELD, _MSG_StartTime, WaterClear1[1][Sala] * 2);
											}
										}
									}
								}

								else if (GenerateID >= WATER_M_INITIAL + 8 && GenerateID <= WATER_M_INITIAL + 11)
								{
									int CurrentNumMob = mNPCGen.pList[GenerateID].CurrentNumMob;

									if (CurrentNumMob == 1)
									{
										int Sala = 9;

										if (WaterClear1[1][Sala] > 5)
											WaterClear1[1][Sala] = 5;


										int partyleader = pMob[conn].Leader;

										if (partyleader <= 0)
											partyleader = conn;

										SendClientSignalParm(partyleader, ESCENE_FIELD, _MSG_StartTime, WaterClear1[1][Sala] * 2);

										for (int i = 0; i < MAX_PARTY; i++)
										{
											int partymember = pMob[partyleader].PartyList[i];

											if (partymember >= MAX_USER) continue;

											if (pUser[partymember].Mode == USER_PLAY)
											{

												SendClientSignalParm(partymember, ESCENE_FIELD, _MSG_StartTime, WaterClear1[1][Sala] * 2);
											}
										}
									}
								}
#pragma endregion
#pragma region Agua N
								else if (GenerateID >= WATER_N_INITIAL && GenerateID <= WATER_N_INITIAL + 7)
								{
									int CurrentNumMob = mNPCGen.pList[GenerateID].CurrentNumMob;

									if (CurrentNumMob == 1)
									{
										int Sala = GenerateID - WATER_N_INITIAL;

										if (WaterClear1[0][Sala] > 15)
											WaterClear1[0][Sala] = 15;


										int partyleader = pMob[conn].Leader;

										if (partyleader <= 0)
											partyleader = conn;

										int slot_free = -1;

										STRUCT_ITEM Perga;
										memset(&Perga, 0, sizeof(STRUCT_ITEM));

										Perga.sIndex = 3174 + Sala;

										if (partyleader > 0 && partyleader < MAX_USER)
											PutItem(partyleader, &Perga);

										SendClientSignalParm(partyleader, ESCENE_FIELD, _MSG_StartTime, WaterClear1[0][Sala] * 2);

										for (int i = 0; i < MAX_PARTY; i++)
										{
											int partymember = pMob[partyleader].PartyList[i];

											if (partymember >= MAX_USER) continue;

											if (pUser[partymember].Mode == USER_PLAY)
											{

												SendClientSignalParm(partymember, ESCENE_FIELD, _MSG_StartTime, WaterClear1[0][Sala] * 2);
											}
										}
									}
								}

								else if (GenerateID >= WATER_N_INITIAL + 8 && GenerateID <= WATER_N_INITIAL + 11)
								{
									int CurrentNumMob = mNPCGen.pList[GenerateID].CurrentNumMob;

									if (CurrentNumMob == 1)
									{
										int Sala = 9;

										if (WaterClear1[0][Sala] > 5)
											WaterClear1[0][Sala] = 5;


										int partyleader = pMob[conn].Leader;

										if (partyleader <= 0)
											partyleader = conn;

										SendClientSignalParm(partyleader, ESCENE_FIELD, _MSG_StartTime, WaterClear1[0][Sala] * 2);

										for (int i = 0; i < MAX_PARTY; i++)
										{
											int partymember = pMob[partyleader].PartyList[i];

											if (partymember >= MAX_USER) continue;

											if (pUser[partymember].Mode == USER_PLAY)
											{

												SendClientSignalParm(partymember, ESCENE_FIELD, _MSG_StartTime, WaterClear1[0][Sala] * 2);
											}
										}
									}
								}
#pragma endregion
#pragma region Agua A
								else if (GenerateID >= WATER_A_INITIAL && GenerateID <= WATER_A_INITIAL + 7)
								{
									int CurrentNumMob = mNPCGen.pList[GenerateID].CurrentNumMob;

									if (CurrentNumMob == 1)
									{
										int Sala = GenerateID - WATER_A_INITIAL;

										if (WaterClear1[2][Sala] > 15)
											WaterClear1[2][Sala] = 15;


										int partyleader = pMob[conn].Leader;

										if (partyleader <= 0)
											partyleader = conn;

										int slot_free = -1;

										STRUCT_ITEM Perga;
										memset(&Perga, 0, sizeof(STRUCT_ITEM));

										Perga.sIndex = 3183 + Sala;

										if (partyleader > 0 && partyleader < MAX_USER)
											PutItem(partyleader, &Perga);

										SendClientSignalParm(partyleader, ESCENE_FIELD, _MSG_StartTime, WaterClear1[2][Sala] * 2);

										for (int i = 0; i < MAX_PARTY; i++)
										{
											int partymember = pMob[partyleader].PartyList[i];

											if (partymember >= MAX_USER) continue;

											if (pUser[partymember].Mode == USER_PLAY)
											{


												SendClientSignalParm(partymember, ESCENE_FIELD, _MSG_StartTime, WaterClear1[2][Sala] * 2);
											}
										}
									}
								}

								else if (GenerateID >= WATER_A_INITIAL + 8 && GenerateID <= WATER_A_INITIAL + 11)
								{
									int CurrentNumMob = mNPCGen.pList[GenerateID].CurrentNumMob;

									if (CurrentNumMob == 1)
									{
										int Sala = 9;

										if (WaterClear1[2][Sala] > 5)
											WaterClear1[2][Sala] = 5;


										int partyleader = pMob[conn].Leader;

										if (partyleader <= 0)
											partyleader = conn;

										SendClientSignalParm(partyleader, ESCENE_FIELD, _MSG_StartTime, WaterClear1[2][Sala] * 2);

										for (int i = 0; i < MAX_PARTY; i++)
										{
											int partymember = pMob[partyleader].PartyList[i];

											if (partymember >= MAX_USER) continue;

											if (pUser[partymember].Mode == USER_PLAY)
											{

												SendClientSignalParm(partymember, ESCENE_FIELD, _MSG_StartTime, WaterClear1[2][Sala] * 2);
											}
										}
									}
								}
#pragma endregion
								CCastleZakum::MobKilled(target, conn, PosX, PosY);
								//CCubo::MobKilled(target, conn, PosX, PosY);
								//CEncampment::MobKilled(target, conn, PosX, PosY);



								if (GenerateID >= TORRE_NOATUM1 && GenerateID <= TORRE_NOATUM3)
									LiveTower[GenerateID - TORRE_NOATUM1] = 0;


								else if (GenerateID == REI_HARABARD)
								{
									Kingdom1Clear = 1;
									SendNoticeArea(g_pMessageStringTable[_NN_King1_Killed], 1676, 1556, 1776, 1636);
								}
								else if (GenerateID == REI_GLANTUAR)
								{
									Kingdom2Clear = 1;
									SendNoticeArea(g_pMessageStringTable[_NN_King2_Killed], 1676, 1816, 1776, 1892);
								}
#pragma region Boss R Lac R Ori Circulo divino
								else if (GenerateID == 0 || GenerateID == 1 || GenerateID == 2)
								{
									STRUCT_ITEM item;
									memset(&item, 0, sizeof(STRUCT_ITEM));

									int _rand = rand() % 14;

									if (_rand == 0)
										item.sIndex = 419;

									else if (_rand == 1)
										item.sIndex = 420;

									if (item.sIndex)
									{
										SetItemBonus(&item, 0, 0, 0);

										PutItem(conn, &item);
									}
								}

								else if (GenerateID == 5 || GenerateID == 6 || GenerateID == 7)
								{
									STRUCT_ITEM item;
									memset(&item, 0, sizeof(STRUCT_ITEM));

									int _rand = rand() % 14;

									if (_rand == 0)
										item.sIndex = 421 + (rand() % 7);

									else if (_rand == 1)
										item.sIndex = 419;

									if (item.sIndex)
									{
										SetItemBonus(&item, 0, 0, 0);

										if (pHeightGrid[AlvoY][AlvoX] > -40 && pHeightGrid[AlvoY][AlvoX] < 36)
											PutItem(conn, &item);
										//CreateItem(AlvoX, AlvoY, &item, rand() % 4, 1);
									}
								}
#pragma endregion

								else if (GenerateID == 3)
								{
									STRUCT_ITEM item;
									memset(&item, 0, sizeof(STRUCT_ITEM));

									int _rand = rand() % 7;

									if (_rand == 0)
										item.sIndex = 1106;

									else if (_rand == 1)
										item.sIndex = 1256;

									else if (_rand == 2)
										item.sIndex = 1418;

									else if (_rand == 3)
										item.sIndex = 1568;

									if (item.sIndex)
									{
										SetItemBonus(&item, 75, 1, 0);

										if (pHeightGrid[AlvoY][AlvoX] > -40 && pHeightGrid[AlvoY][AlvoX] < 36)
											PutItem(conn, &item);
										//CreateItem(AlvoX, AlvoY, &item, rand() % 4, 1);
									}
								}
#pragma region Pesas
								else if (GenerateIndex >= NIGHTMARE_M_INITIAL && GenerateIndex <= NIGHTMARE_M_END)
								{
									int ARNOLD_ = mNPCGen.pList[Arnold_].CurrentNumMob;
									int LAINY = mNPCGen.pList[Lainy].CurrentNumMob;
									int REIMERS = mNPCGen.pList[Reimers].CurrentNumMob;
									int ROPERION = mNPCGen.pList[RoPerion].CurrentNumMob;
									int IRENA = mNPCGen.pList[Irena].CurrentNumMob;


									if (ARNOLD_ == 1)
										GenerateMob(GenerateIndex, 0, 0);//Pesa M

									if (LAINY == 1)
										GenerateMob(GenerateIndex, 0, 0);//Pesa M

									if (REIMERS == 1)
										GenerateMob(GenerateIndex, 0, 0);//Pesa M

									if (ROPERION == 1)
										GenerateMob(GenerateIndex, 0, 0);//Pesa M

									if (IRENA == 1)
										GenerateMob(GenerateIndex, 0, 0);//Pesa M

								}
								else if (GenerateIndex >= NIGHTMARE_N_INITIAL && GenerateIndex <= NIGHTMARE_N_END)
								{
									int MARTIN = mNPCGen.pList[Martin].CurrentNumMob;
									int BALMERS = mNPCGen.pList[Balmers].CurrentNumMob;
									int RUBYEN = mNPCGen.pList[Rubyen].CurrentNumMob;
									int NAOMI = mNPCGen.pList[Naomi].CurrentNumMob;
									int ARNOLD = mNPCGen.pList[Arnold].CurrentNumMob;

									if (MARTIN == 1)
										GenerateMob(GenerateIndex, 0, 0);//Pesa N

									if (BALMERS == 1)
										GenerateMob(GenerateIndex, 0, 0);//Pesa N

									if (RUBYEN == 1)
										GenerateMob(GenerateIndex, 0, 0);//Pesa N

									if (NAOMI == 1)
										GenerateMob(GenerateIndex, 0, 0);//Pesa N

									if (ARNOLD == 1)
										GenerateMob(GenerateIndex, 0, 0);//Pesa N
								}
								else if (GenerateIndex >= NIGHTMARE_A_INITIAL && GenerateIndex <= NIGHTMARE_A_END)
								{
									int ESCURIDAO = mNPCGen.pList[Escuridao].CurrentNumMob;
									int ERIN = mNPCGen.pList[Erin].CurrentNumMob;
									int FENIX = mNPCGen.pList[Fenix].CurrentNumMob;
									int KARA = mNPCGen.pList[Kara].CurrentNumMob;
									int KEI = mNPCGen.pList[Kei].CurrentNumMob;
									int KEMI = mNPCGen.pList[Kemi].CurrentNumMob;
									int LEAO = mNPCGen.pList[Leao].CurrentNumMob;
									int UIE = mNPCGen.pList[Yue].CurrentNumMob;

									if (ESCURIDAO == 1)
										GenerateMob(GenerateIndex, 0, 0);//Pesa A

									if (ERIN == 1)
										GenerateMob(GenerateIndex, 0, 0);//Pesa A

									if (FENIX == 1)
										GenerateMob(GenerateIndex, 0, 0);//Pesa A

									if (KARA == 1)
										GenerateMob(GenerateIndex, 0, 0);//Pesa A
									 
									if (KEI == 1)
										GenerateMob(GenerateIndex, 0, 0);//Pesa A

									if (KEMI == 1)
										GenerateMob(GenerateIndex, 0, 0);//Pesa A

									if (LEAO == 1)
										GenerateMob(GenerateIndex, 0, 0);//Pesa A

									if (UIE == 1)
										GenerateMob(GenerateIndex, 0, 0);//Pesa A
								}
#pragma endregion
#pragma region Portão Infernal Parte 1
								else if (GenerateIndex >= PI_INITIAL1 && GenerateIndex <= PI_END1)
								{
									// Portão Infernal Parte 1
									GenerateMob(GenerateIndex, 0, 0);
								}
#pragma endregion
#pragma region Carta de duelo N
								//Carta N
								if (GenerateID >= SECRET_ROOM_N_SALA1_MOB_1 && GenerateID <= SECRET_ROOM_N_SALA1_MOB_2)
								{
									int CurrentNumMob = mNPCGen.pList[SECRET_ROOM_N_SALA1_MOB_1].CurrentNumMob;
									CurrentNumMob += mNPCGen.pList[SECRET_ROOM_N_SALA1_MOB_2].CurrentNumMob;

									if (CurrentNumMob == 1)
									{
										CartaTime = 60;

										ClearAreaTeleport(778, 3652, 832, 3698, CartaPos[1][0], CartaPos[1][1]);

										CartaSala++;

										MSG_STANDARDPARM sm;

										sm.Type = _MSG_StartTime;
										sm.ID = ESCENE_FIELD;
										sm.Size = sizeof(MSG_STANDARDPARM);
										sm.Parm = CartaTime * 2;

										MapaMulticast(6, 28, (MSG_STANDARD*)&sm, 0);
									}
								}

								if (GenerateID >= SECRET_ROOM_N_SALA2_MOB_1 && GenerateID <= SECRET_ROOM_N_SALA2_MOB_2)
								{
									int CurrentNumMob = mNPCGen.pList[SECRET_ROOM_N_SALA2_MOB_1].CurrentNumMob;
									CurrentNumMob += mNPCGen.pList[SECRET_ROOM_N_SALA2_MOB_2].CurrentNumMob;

									if (CurrentNumMob == 1)
									{
										CartaTime = 60;

										ClearAreaTeleport(836, 3652, 890, 3698, CartaPos[2][0], CartaPos[2][1]);

										CartaSala++;

										MSG_STANDARDPARM sm;

										sm.Type = _MSG_StartTime;
										sm.ID = ESCENE_FIELD;
										sm.Size = sizeof(MSG_STANDARDPARM);
										sm.Parm = CartaTime * 2;

										MapaMulticast(6, 28, (MSG_STANDARD*)&sm, 0);
									}
								}

								if (GenerateID >= SECRET_ROOM_N_SALA3_MOB_1 && GenerateID <= SECRET_ROOM_N_SALA3_MOB_2)
								{
									int CurrentNumMob = mNPCGen.pList[SECRET_ROOM_N_SALA3_MOB_1].CurrentNumMob;
									CurrentNumMob += mNPCGen.pList[SECRET_ROOM_N_SALA3_MOB_2].CurrentNumMob;

									if (CurrentNumMob == 1)
									{
										CartaTime = 60;

										ClearAreaTeleport(834, 3595, 889, 3645, CartaPos[3][0], CartaPos[3][1]);

										CartaSala++;

										MSG_STANDARDPARM sm;

										sm.Type = _MSG_StartTime;
										sm.ID = ESCENE_FIELD;
										sm.Size = sizeof(MSG_STANDARDPARM);
										sm.Parm = CartaTime * 2;

										MapaMulticast(6, 28, (MSG_STANDARD*)&sm, 0);
									}
								}

								if (GenerateID >= SECRET_ROOM_N_SALA4_MOB_1 && GenerateID <= SECRET_ROOM_N_SALA4_MOB_4)
								{
									int CurrentNumMob = mNPCGen.pList[SECRET_ROOM_N_SALA4_MOB_1].CurrentNumMob;
									CurrentNumMob += mNPCGen.pList[SECRET_ROOM_N_SALA4_MOB_2].CurrentNumMob;
									CurrentNumMob += mNPCGen.pList[SECRET_ROOM_N_SALA4_MOB_3].CurrentNumMob;
									CurrentNumMob += mNPCGen.pList[SECRET_ROOM_N_SALA4_MOB_4].CurrentNumMob;

									if (CurrentNumMob == 1)
									{
										//ClearArea(776, 3595, 834, 3648);
										CartaTime = 3;
										CartaSala = 4;
									}
								}
#pragma endregion
#pragma region Carta de duelo M
								//Carta M
								if (GenerateID >= SECRET_ROOM_M_SALA1_MOB_1 && GenerateID <= SECRET_ROOM_M_SALA1_MOB_2)
								{
									int CurrentNumMob = mNPCGen.pList[SECRET_ROOM_M_SALA1_MOB_1].CurrentNumMob;
									CurrentNumMob += mNPCGen.pList[SECRET_ROOM_M_SALA1_MOB_2].CurrentNumMob;

									if (CurrentNumMob == 1)
									{
										CartaTime = 60;

										ClearAreaTeleport(778, 3652, 832, 3698, CartaPos[1][0], CartaPos[1][1]);

										CartaSala++;

										MSG_STANDARDPARM sm;

										sm.Type = _MSG_StartTime;
										sm.ID = ESCENE_FIELD;
										sm.Size = sizeof(MSG_STANDARDPARM);
										sm.Parm = CartaTime * 2;

										MapaMulticast(6, 28, (MSG_STANDARD*)&sm, 0);
									}
								}

								if (GenerateID >= SECRET_ROOM_M_SALA2_MOB_1 && GenerateID <= SECRET_ROOM_M_SALA2_MOB_2)
								{
									int CurrentNumMob = mNPCGen.pList[SECRET_ROOM_M_SALA2_MOB_1].CurrentNumMob;
									CurrentNumMob += mNPCGen.pList[SECRET_ROOM_M_SALA2_MOB_2].CurrentNumMob;

									if (CurrentNumMob == 1)
									{
										CartaTime = 60;

										ClearAreaTeleport(836, 3652, 890, 3698, CartaPos[2][0], CartaPos[2][1]);

										CartaSala++;

										MSG_STANDARDPARM sm;

										sm.Type = _MSG_StartTime;
										sm.ID = ESCENE_FIELD;
										sm.Size = sizeof(MSG_STANDARDPARM);
										sm.Parm = CartaTime * 2;

										MapaMulticast(6, 28, (MSG_STANDARD*)&sm, 0);
									}
								}

								if (GenerateID >= SECRET_ROOM_M_SALA3_MOB_1 && GenerateID <= SECRET_ROOM_M_SALA3_MOB_2)
								{
									int CurrentNumMob = mNPCGen.pList[SECRET_ROOM_M_SALA3_MOB_1].CurrentNumMob;
									CurrentNumMob += mNPCGen.pList[SECRET_ROOM_M_SALA3_MOB_2].CurrentNumMob;

									if (CurrentNumMob == 1)
									{
										CartaTime = 60;

										ClearAreaTeleport(834, 3595, 889, 3645, CartaPos[3][0], CartaPos[3][1]);

										CartaSala++;

										MSG_STANDARDPARM sm;

										sm.Type = _MSG_StartTime;
										sm.ID = ESCENE_FIELD;
										sm.Size = sizeof(MSG_STANDARDPARM);
										sm.Parm = CartaTime * 2;

										MapaMulticast(6, 28, (MSG_STANDARD*)&sm, 0);
									}
								}

								if (GenerateID >= SECRET_ROOM_M_SALA4_MOB_1 && GenerateID <= SECRET_ROOM_M_SALA4_MOB_4)
								{
									int CurrentNumMob = mNPCGen.pList[SECRET_ROOM_M_SALA4_MOB_1].CurrentNumMob;
									CurrentNumMob += mNPCGen.pList[SECRET_ROOM_M_SALA4_MOB_2].CurrentNumMob;
									CurrentNumMob += mNPCGen.pList[SECRET_ROOM_M_SALA4_MOB_3].CurrentNumMob;
									CurrentNumMob += mNPCGen.pList[SECRET_ROOM_M_SALA4_MOB_4].CurrentNumMob;

									if (CurrentNumMob == 1)
									{
										//ClearArea(776, 3595, 834, 3648);
										CartaTime = 3;
										CartaSala = 4;
									}
								}
#pragma endregion
#pragma region Carta de duelo A
								//Carta A
								if (GenerateID >= SECRET_ROOM_A_SALA1_MOB_1 && GenerateID <= SECRET_ROOM_A_SALA1_MOB_2)
								{
									int CurrentNumMob = mNPCGen.pList[SECRET_ROOM_A_SALA1_MOB_1].CurrentNumMob;
									CurrentNumMob += mNPCGen.pList[SECRET_ROOM_A_SALA1_MOB_2].CurrentNumMob;

									if (CurrentNumMob == 1)
									{
										CartaTime = 60;

										ClearAreaTeleport(778, 3652, 832, 3698, CartaPos[1][0], CartaPos[1][1]);

										CartaSala++;

										MSG_STANDARDPARM sm;

										sm.Type = _MSG_StartTime;
										sm.ID = ESCENE_FIELD;
										sm.Size = sizeof(MSG_STANDARDPARM);
										sm.Parm = CartaTime * 2;

										MapaMulticast(6, 28, (MSG_STANDARD*)&sm, 0);
									}
								}

								if (GenerateID >= SECRET_ROOM_A_SALA2_MOB_1 && GenerateID <= SECRET_ROOM_A_SALA2_MOB_2)
								{
									int CurrentNumMob = mNPCGen.pList[SECRET_ROOM_A_SALA2_MOB_1].CurrentNumMob;
									CurrentNumMob += mNPCGen.pList[SECRET_ROOM_A_SALA2_MOB_2].CurrentNumMob;

									if (CurrentNumMob == 1)
									{
										CartaTime = 60;

										ClearAreaTeleport(836, 3652, 890, 3698, CartaPos[2][0], CartaPos[2][1]);

										CartaSala++;

										MSG_STANDARDPARM sm;

										sm.Type = _MSG_StartTime;
										sm.ID = ESCENE_FIELD;
										sm.Size = sizeof(MSG_STANDARDPARM);
										sm.Parm = CartaTime * 2;

										MapaMulticast(6, 28, (MSG_STANDARD*)&sm, 0);
									}
								}

								if (GenerateID >= SECRET_ROOM_A_SALA3_MOB_1 && GenerateID <= SECRET_ROOM_A_SALA3_MOB_2)
								{
									int CurrentNumMob = mNPCGen.pList[SECRET_ROOM_A_SALA3_MOB_1].CurrentNumMob;
									CurrentNumMob += mNPCGen.pList[SECRET_ROOM_A_SALA3_MOB_2].CurrentNumMob;

									if (CurrentNumMob == 1)
									{
										CartaTime = 60;

										ClearAreaTeleport(834, 3595, 889, 3645, CartaPos[3][0], CartaPos[3][1]);

										CartaSala++;

										MSG_STANDARDPARM sm;

										sm.Type = _MSG_StartTime;
										sm.ID = ESCENE_FIELD;
										sm.Size = sizeof(MSG_STANDARDPARM);
										sm.Parm = CartaTime * 2;

										MapaMulticast(6, 28, (MSG_STANDARD*)&sm, 0);
									}
								}

								if (GenerateID >= SECRET_ROOM_A_SALA4_MOB_1 && GenerateID <= SECRET_ROOM_A_SALA4_MOB_4)
								{
									int CurrentNumMob = mNPCGen.pList[SECRET_ROOM_A_SALA4_MOB_1].CurrentNumMob;
									CurrentNumMob += mNPCGen.pList[SECRET_ROOM_A_SALA4_MOB_2].CurrentNumMob;
									CurrentNumMob += mNPCGen.pList[SECRET_ROOM_A_SALA4_MOB_3].CurrentNumMob;
									CurrentNumMob += mNPCGen.pList[SECRET_ROOM_A_SALA4_MOB_4].CurrentNumMob;

									if (CurrentNumMob == 1)
									{
										//ClearArea(776, 3595, 834, 3648);
										CartaTime = 3;
										CartaSala = 4;
									}
								}
#pragma endregion
#pragma region Pista de Runas
#pragma region Pista Nv0 Lich_Crunt
								if (GenerateID == RUNEQUEST_LV0_LICH1 || GenerateID == RUNEQUEST_LV0_LICH2)
								{
									int _rand = rand() % 100;

									if (_rand < 20)
									{
										for (int c = MAX_USER; c < MAX_MOB; c++)
										{
											if (pMob[c].Mode == USER_EMPTY)
												continue;

											if (pMob[c].GenerateIndex != RUNEQUEST_LV0_LICH1 && pMob[c].GenerateIndex != RUNEQUEST_LV0_LICH2)
												continue;

											DeleteMob(c, 3);
										}

										int partyleader = pMob[conn].Leader;

										if (partyleader <= 0)
											partyleader = conn;

										STRUCT_ITEM Runa;
										memset(&Runa, 0, sizeof(STRUCT_ITEM));

										Runa.sIndex = PistaRune[0][rand() % 5];

										//correção
										if (checkCord(partyleader, 3330, 1600, 3450, 1660) == TRUE)
										{

											if (partyleader > 0 && partyleader < MAX_USER)
												PutItem(partyleader, &Runa);
										}

										for (int i = 0; i < MAX_PARTY; i++)
										{
											int partymember = pMob[partyleader].PartyList[i];

											if (partymember >= MAX_USER) continue;

											if (pUser[partymember].Mode == USER_PLAY)
											{
												//correção
												if (checkCord(partymember, 3330, 1600, 3450, 1660) == FALSE)
													continue;

												Runa.sIndex = PistaRune[0][rand() % 5];
												PutItem(partymember, &Runa);
											}
										}

										STRUCT_ITEM NextPista;
										memset(&NextPista, 0, sizeof(STRUCT_ITEM));

										NextPista.sIndex = 5134;
										NextPista.stEffect[0].cEffect = 43;
										NextPista.stEffect[0].cValue = 1;

										PutItem(partyleader, &NextPista);
										SystemLog("-system", "-", 0, strFmt("etc,questRune +0 complete leader:%s", pMob[partyleader].MOB.MobName));
									}
									else
									{
										for (int c = MAX_USER; c < MAX_MOB; c++)
										{
											if (pMob[c].Mode == USER_EMPTY)
												continue;

											if (pMob[c].GenerateIndex != RUNEQUEST_LV0_LICH1 && pMob[c].GenerateIndex != RUNEQUEST_LV0_LICH2)
												continue;

											DeleteMob(c, 3);
										}

										GenerateMob(RUNEQUEST_LV0_LICH1, 0, 0);
										GenerateMob(RUNEQUEST_LV0_LICH1, 0, 0);

										GenerateMob(RUNEQUEST_LV0_LICH2, 0, 0);
										GenerateMob(RUNEQUEST_LV0_LICH2, 0, 0);
									}
								}
#pragma endregion
#pragma region Pista Nv1 Torre
								if (GenerateID == RUNEQUEST_LV1_TORRE1 || GenerateID == RUNEQUEST_LV1_TORRE2 || GenerateID == RUNEQUEST_LV1_TORRE3)
								{
									int party = GenerateID - RUNEQUEST_LV1_TORRE1;

									Pista[1].Party[party].MobCount = 0;

									DoTeleport(Pista[1].Party[party].LeaderID, 3294, rand() % 1 == 0 ? 1701 : 1686);

									for (int i = 0; i < MAX_PARTY; i++)
									{
										int partymember = pMob[Pista[1].Party[0].LeaderID].PartyList[i];

										if (partymember >= MAX_USER) continue;

										if (pUser[partymember].Mode != USER_PLAY)
											continue;

										DoTeleport(partymember, 3294, rand() % 1 == 0 ? 1701 : 1686);
									}
								}

								if (GenerateID >= RUNEQUEST_LV1_MOB_INITIAL && GenerateID <= RUNEQUEST_LV1_MOB_END)
								{
									int partyleader = pMob[conn].Leader;

									if (partyleader <= 0)
										partyleader = conn;

									if (Pista[1].Party[0].LeaderID == partyleader)
										Pista[1].Party[0].MobCount++;

									else if (Pista[1].Party[1].LeaderID == partyleader)
										Pista[1].Party[1].MobCount++;

									else if (Pista[1].Party[2].LeaderID == partyleader)
										Pista[1].Party[2].MobCount++;
								}
#pragma endregion
#pragma region Pista Nv2 Amon
								if (GenerateID == RUNEQUEST_LV2_MOB_BOSS)
								{
									int partyleader = pMob[conn].Leader;

									if (partyleader <= 0)
										partyleader = conn;

									STRUCT_ITEM Runa;
									memset(&Runa, 0, sizeof(STRUCT_ITEM));

									Runa.sIndex = PistaRune[2][rand() % 6];

									//correção

									if (checkCord(partyleader, 3340, 1425, 3449, 1463) == TRUE)
									{
										if (partyleader > 0 && partyleader < MAX_USER) {
											PutItem(partyleader, &Runa);

											STRUCT_ITEM NextPista;
											memset(&NextPista, 0, sizeof(STRUCT_ITEM));

											NextPista.sIndex = 5134;
											NextPista.stEffect[0].cEffect = 43;
											NextPista.stEffect[0].cValue = 3;

											PutItem(partyleader, &NextPista);
										}
									}
									for (int i = 0; i < MAX_PARTY; i++)
									{
										int partymember = pMob[partyleader].PartyList[i];

										if (partymember >= MAX_USER) continue;

										if (pUser[partymember].Mode == USER_PLAY)
										{
											//correção
											if (checkCord(partymember, 3340, 1425, 3449, 1463) == FALSE)
												continue;

											Runa.sIndex = PistaRune[2][rand() % 6];
											PutItem(partymember, &Runa);

										}
									}


									SystemLog("-system", "-", 0, strFmt("etc,questRune +2 complete leader:%s", pMob[partyleader].MOB.MobName));
								}
#pragma endregion
#pragma region Pista Nv3 Sulrang
								if (GenerateID >= RUNEQUEST_LV3_MOB_SULRANG_INITIAL && GenerateID <= RUNEQUEST_LV3_MOB_SULRANG_END)
								{
									GenerateMob(RUNEQUEST_LV3_MOB_BOSS_INITIAL + rand() % 7, 0, 0);
								}
								if (GenerateID >= RUNEQUEST_LV3_MOB_BOSS_INITIAL && GenerateID <= RUNEQUEST_LV3_MOB_BOSS_END)
								{
									int partyleader = pMob[conn].Leader;

									if (partyleader <= 0)
										partyleader = conn;

									if (Pista[3].Party[0].LeaderID == partyleader)
										Pista[3].Party[0].MobCount++;

									else if (Pista[3].Party[1].LeaderID == partyleader)
										Pista[3].Party[1].MobCount++;

									else if (Pista[3].Party[2].LeaderID == partyleader)
										Pista[3].Party[2].MobCount++;
								}
#pragma endregion
#pragma region Pista Nv4 Labirinto
								if (GenerateID >= RUNEQUEST_LV4_MOB_INITIAL && GenerateID <= RUNEQUEST_LV4_MOB_END && mNPCGen.pList[GenerateID].CurrentNumMob == 1)
								{
									int leader = pMob[conn].Leader;

									int partyleader = pMob[conn].Leader;

									if (partyleader <= 0)
										partyleader = conn;

									if (partyleader == Pista[4].Party[0].LeaderID && Pista[4].Party[1].MobCount >= 1 && Pista[4].Party[2].MobCount >= 1)
									{									
										if (Pista[4].Party[0].MobCount == 1)
										{
											DoTeleport(partyleader, 3351, 1334);

											for (int i = 0; i < MAX_PARTY; i++)
											{
												int partyconn = pMob[partyleader].PartyList[i];

												if (partyconn > 0 && partyconn < MAX_USER && partyconn != partyleader && pUser[partyconn].Mode == USER_PLAY)
													DoTeleport(partyconn, 3352, 1334);
											}

											GenerateMob(RUNEQUEST_LV4_MOB_BOSS, 3351, 1336);
										}
										if (Pista[4].Party[0].MobCount >= 1)
											Pista[4].Party[0].MobCount--;
									}
									else if (partyleader == Pista[4].Party[1].LeaderID && Pista[4].Party[0].MobCount >= 1 && Pista[4].Party[2].MobCount >= 1)
									{
										if (Pista[4].Party[1].MobCount == 1)
										{
											DoTeleport(partyleader, 3351, 1334);

											for (int i = 0; i < MAX_PARTY; i++)
											{
												int partyconn = pMob[partyleader].PartyList[i];

												if (partyconn > 0 && partyconn < MAX_USER && partyconn != partyleader && pUser[partyconn].Mode == USER_PLAY)
													DoTeleport(partyconn, 3351, 1334);
											}

											GenerateMob(RUNEQUEST_LV4_MOB_BOSS, 3351, 1336);
										}
										if (Pista[4].Party[1].MobCount >= 1)
											Pista[4].Party[1].MobCount--;
									}
									else if (partyleader == Pista[4].Party[2].LeaderID && Pista[4].Party[1].MobCount >= 1 && Pista[4].Party[0].MobCount >= 1)
									{
										if (Pista[4].Party[2].MobCount == 1)
										{
											DoTeleport(partyleader, 3351, 1334);

											for (int i = 0; i < MAX_PARTY; i++)
											{
												int partyconn = pMob[partyleader].PartyList[i];

												if (partyconn >= MAX_USER) continue;

												if (partyconn > 0 && partyconn < MAX_USER && partyconn != partyleader && pUser[partyconn].Mode == USER_PLAY)
													DoTeleport(partyconn, 3351, 1334);
											}

											GenerateMob(RUNEQUEST_LV4_MOB_BOSS, 3351, 1336);
										}
										if (Pista[4].Party[2].MobCount >= 1)
											Pista[4].Party[2].MobCount--;
									}
								}

								if (GenerateID == RUNEQUEST_LV4_MOB_BOSS)
								{
									int partyleader = pMob[conn].Leader;

									if (partyleader <= 0)
										partyleader = conn;

									STRUCT_ITEM Runa;
									memset(&Runa, 0, sizeof(STRUCT_ITEM));

									Runa.sIndex = PistaRune[4][rand() % 4];

									//correção

									if (checkCord(partyleader, 3333, 1320, 3365, 1349) == TRUE)
									{

										if (partyleader > 0 && partyleader < MAX_USER) {
											PutItem(partyleader, &Runa);

											STRUCT_ITEM NextPista;
											memset(&NextPista, 0, sizeof(STRUCT_ITEM));

											NextPista.sIndex = 5134;
											NextPista.stEffect[0].cEffect = 43;
											NextPista.stEffect[0].cValue = 5;

											PutItem(partyleader, &NextPista);
											DoTeleport(partyleader, 3294, rand() % 1 == 0 ? 1701 : 1686);
										}
									}

									for (int i = 0; i < MAX_PARTY; i++)
									{
										int partymember = pMob[partyleader].PartyList[i];

										if (partymember >= MAX_USER) continue;

										if (pUser[partymember].Mode == USER_PLAY)
										{
											//correção
											if (checkCord(partymember, 3333, 1320, 3365, 1349) == TRUE)
											{
												Runa.sIndex = PistaRune[4][rand() % 4];
												PutItem(partymember, &Runa);
												DoTeleport(partymember, 3294, rand() % 1 == 0 ? 1701 : 1686);
											}
										}

									}
									SystemLog("-system", "-", 0, strFmt("etc,questRune +4 complete leader:%s", pMob[partyleader].MOB.MobName));
								}
#pragma endregion
#pragma region Pista Nv5 Balrog
								if (GenerateID == RUNEQUEST_LV5_MOB_BOSS)
								{
									Pista[5].Party[0].MobCount = 1;

									int partyleader = pMob[conn].Leader;

									if (partyleader <= 0)
										partyleader = conn;

									STRUCT_ITEM Runa;
									memset(&Runa, 0, sizeof(STRUCT_ITEM));

									Runa.sIndex = PistaRune[5][rand() % 7];

									//correção

									if (checkCord(partyleader, 3333, 1157, 3448, 1271) == TRUE)
									{

										if (partyleader > 0 && partyleader < MAX_USER) {
											PutItem(partyleader, &Runa);

											STRUCT_ITEM NextPista;
											memset(&NextPista, 0, sizeof(STRUCT_ITEM));

											NextPista.sIndex = 5134;
											NextPista.stEffect[0].cEffect = 43;
											NextPista.stEffect[0].cValue = 6;

											PutItem(partyleader, &NextPista);
											DoTeleport(partyleader, 3294, rand() % 1 == 0 ? 1701 : 1686);
										}
									}

									for (int i = 0; i < MAX_PARTY; i++)
									{
										int partymember = pMob[partyleader].PartyList[i];

										if (partymember >= MAX_USER) continue;

										if (pUser[partymember].Mode == USER_PLAY)
										{
											//correção
											if (checkCord(partymember, 3333, 1157, 3448, 1271) == FALSE)
												continue;
											Runa.sIndex = PistaRune[5][rand() % 7];
											PutItem(partymember, &Runa);
											DoTeleport(partymember, 3294, rand() % 1 == 0 ? 1701 : 1686);
										}

									}

									SystemLog("-system", "-", 0, strFmt("etc,questRune +5 complete leader:%s", pMob[partyleader].MOB.MobName));
								}
#pragma endregion
#pragma region Pista Nv6 Coelho
								if (GenerateID >= RUNEQUEST_LV6_MOB_INITIAL && GenerateID <= RUNEQUEST_LV6_MOB_END)
								{
									if (Pista[6].Party[0].MobCount == 1)
									{
										Pista[6].Party[0].MobCount--;

										GenerateMob(RUNEQUEST_LV6_MOB_BOSS, 0, 0);
									}

									else if (Pista[6].Party[0].MobCount > 0)
										Pista[6].Party[0].MobCount--;
								}

								if (GenerateID == RUNEQUEST_LV6_MOB_BOSS)
								{
									int partyleader = pMob[conn].Leader;

									if (partyleader <= 0)
										partyleader = conn;

									STRUCT_ITEM Runa;
									memset(&Runa, 0, sizeof(STRUCT_ITEM));

									Runa.sIndex = PistaRune[6][rand() % 9];

									//correção
									if (checkCord(partyleader, 3332, 1471, 3449, 1529) == TRUE)
									{

										if (partyleader > 0 && partyleader < MAX_USER)
											PutItem(partyleader, &Runa);
									}


									for (int i = 0; i < MAX_PARTY; i++)
									{
										int partymember = pMob[partyleader].PartyList[i];

										if (partymember >= MAX_USER) continue;

										if (pUser[partymember].Mode == USER_PLAY)
										{
											//correção
											if (checkCord(partymember, 3332, 1471, 3449, 1529) == FALSE)
												continue;

											Runa.sIndex = PistaRune[6][rand() % 9];
											PutItem(partymember, &Runa);
										}
									}
									SystemLog("-system", "-", 0, strFmt("etc,questRune +6 complete leader:%s", pMob[partyleader].MOB.MobName));
								}
#pragma endregion

							}
#pragma region Drop Gold
							int MobCoin = pMob[target].MOB.Coin;
							int UNKGOLD = 18;

							if (pMob[target].MOB.BaseScore.Level < 10)
								UNKGOLD = 2;
							else if (pMob[target].MOB.BaseScore.Level < 20)
								UNKGOLD = 4;
							else if (pMob[target].MOB.BaseScore.Level < 30)
								UNKGOLD = 6;
							else if (pMob[target].MOB.BaseScore.Level < 50)
								UNKGOLD = 9; // aparentementer corrigido man, ta igual ao meu e eu não tenho mais esse b.o se ainda causar, me avisa que a gente vê :) ok

							UNKGOLD = rand() % (UNKGOLD + 1);

							if (MobCoin && UNKGOLD == 0)
							{
								MobCoin = 4 * (rand() % (((MobCoin + 1) / 4) + 1) + (MobCoin + 1) / 4 + MobCoin);

								if (MobCoin > 2000)
									MobCoin = 2000;

								if (MobCoin + pMob[conn].MOB.Coin > 2000000000)

									SendClientMessage(conn, g_pMessageStringTable[_NN_Cant_get_more_than_2G]);

								else
								{
									MobCoin = ControleDropGold(conn, target, MobCoin);
									pMob[conn].MOB.Coin += MobCoin;
									SendEtc(conn);
								}
							}
#pragma endregion
#pragma region Drop Evento em todos os mobs
							if (evOn && evStartIndex && evEndIndex && evItem && evRate && evCurrentIndex < evEndIndex && rand() % evRate == 0)
							{
								STRUCT_ITEM item;
								memset(&item, 0, sizeof(STRUCT_ITEM));

								item.sIndex = evItem;
								
								if (evIndex)
								{
									item.stEffect[0].cEffect = 62;
									item.stEffect[0].cValue = evCurrentIndex / 256;
									item.stEffect[1].cEffect = 63;
									item.stEffect[1].cValue = evCurrentIndex;
									item.stEffect[2].cEffect = 59;
									item.stEffect[2].cValue = rand();

									//snprintf(temp, sizeof(temp), " [%s] Dropou [%s] já foram dropados [%d].", pMob[conn].MOB.MobName, g_pItemList[evItem].Name, evCurrentIndex);
								}
								else {
									//snprintf(temp, sizeof(temp), "[%s] Dropou [%s]", pMob[conn].MOB.MobName, g_pItemList[evItem].Name);
								}

								if (evNotice)
									//SendNotice(temp);

									evCurrentIndex++;

								int bonus = 0;

								if (conn > 0 && conn < MAX_USER)
									bonus = pMob[conn].DropBonus;

								ControleDropItem(conn, target, bonus, PosX, PosY, &item);

								DrawConfig(1);
							}
#pragma endregion

#pragma region DropLanhouse

							if ((pMob[conn].TargetX > 3604 && pMob[conn].TargetY > 3604 && pMob[conn].TargetX < 3691 && pMob[conn].TargetY < 3690) ||
								(pMob[conn].TargetX > 3732 && pMob[conn].TargetY > 3476 && pMob[conn].TargetX < 3819 && pMob[conn].TargetY < 3563) ||
								(pMob[conn].TargetX > 3860 && pMob[conn].TargetY > 3604 && pMob[conn].TargetX < 3946 && pMob[conn].TargetY < 3690)
								)
								LanDrop(conn, target);
#pragma endregion

							int target_level = pMob[target].MOB.CurrentScore.Level;
#pragma region Drop comum
							for (int i = 0; i < MAX_CARRY; i++)
							{
								if (pMob[target].MOB.Carry[i].sIndex == 0)
									continue;

								int droprate = g_pDropRate[i];
								int dropbonus = g_pDropBonus[i] + pMob[conn].DropBonus;

								if (dropbonus != 100)
								{
									dropbonus = 10000 / (dropbonus + 1);
									droprate = dropbonus * droprate / 100;
								}

								int pos = i / 8;

								if (i < 60)
								{
									if (pos == 0 || pos == 1 || pos == 2)
									{
										if (target_level < 10)
											droprate = 4 * droprate / 100;

										else if (target_level < 20)
											droprate = 5 * droprate / 100;

										else if (target_level < 30)
											droprate = 6 * droprate / 100;

										else if (target_level < 40)
											droprate = 7 * droprate / 100;

										else if (target_level < 60)
											droprate = 8 * droprate / 100;

										else
											droprate = 99 * droprate / 100;
									}
								}

								else
								{
									if (target_level < 170)
										droprate = 90 * droprate / 100;

									else if (target_level < 200)
										droprate = 60 * droprate / 100;

									else if (target_level < 230)
										droprate = 50 * droprate / 100;

									else if (target_level < 255)
										droprate = 43 * droprate / 100;

									else if (target_level < 320)
										droprate = 38 * droprate / 100;

									else
										droprate = 50 * droprate / 100;
								}

								if (TESTSERVER)
									droprate /= 2;

								if (LOCALSERVER)
									droprate /= 100;

								if (pMob[conn].MOB.Rsv & 4)
								{
									int special2 = pMob[conn].MOB.CurrentScore.Special[2];
									special2 = special2 / 10 + 10;
									special2 = 100 - special2;
									droprate = special2 * droprate / 100;
								}

								if (i == 8 || i == 9 || i == 10)
									droprate = 4;

								if (i == 11)
									droprate = 1;

								if (droprate >= 32000)
									droprate = 32000;

								if (droprate <= 0)
									droprate = 0;
								else
									droprate = rand() % droprate;

								if (droprate == 0 || i == 11)
								{
									bool isFlag = false;
									STRUCT_ITEM* item = &pMob[target].MOB.Carry[i];

									if (item->sIndex <= 390 || item->sIndex >= MAX_ITEMLIST)
										continue;

									if (item->sIndex == 454)
										continue;

									int reqlv = g_pItemList[item->sIndex].ReqLvl;

									if (reqlv < 140 || (droprate % 2) != 1)
									{
										int bonus = 0;

										if (conn > 0 && conn < MAX_USER)
											bonus = pMob[conn].DropBonus;

										item = ControleDropItem(conn, target, bonus, PosX, PosY, item);

										MSG_STANDARDPARM updateItemDayLog;
										memset(&updateItemDayLog, 0, sizeof(MSG_STANDARDPARM));

										updateItemDayLog.Size = sizeof(MSG_STANDARDPARM);
										updateItemDayLog.Type = _MSG_DBItemDayLog;
										updateItemDayLog.ID = 0;
										updateItemDayLog.Parm = item->sIndex;

										DBServerSocket.SendOneMessage((char*)&updateItemDayLog, sizeof(MSG_STANDARDPARM));


										if (LOCALSERVER)
										{
											int item_index = item->sIndex;

											int reqlv = g_pItemList[item_index].ReqLvl;
											int itempos = g_pItemList[item_index].nPos;

											if (itempos & 0xFE && itempos != 128 && conn < MAX_USER)
											{
												SendSay(conn, strFmt("%-12s - %s(%d:%d) %d(%d:%d)",
													pMob[target].MOB.MobName, g_pItemList[item_index].Name,
													pMob[target].MOB.CurrentScore.Level, reqlv, g_dLevel, g_dLevel1,
													g_dLevel2));
											}
										}

										if (i == 8 || i == 9 || i == 10)
											i = 11;
									}
								}
							}
#pragma endregion
#pragma region Quest Amuleto mistico
							if (conn < MAX_USER && (pMob[target].MOB.Equip[0].sIndex == 239 || pMob[target].MOB.Equip[0].sIndex == 241) && !(rand() % 20))
							{
								if (pMob[conn].extra.QuestInfo.Mortal.TerraMistica == 1)
								{

									SendClientMessage(conn, g_pMessageStringTable[_NN_Watching_Town_Success]);
									pMob[conn].extra.QuestInfo.Mortal.TerraMistica = 2;
								}
							}
#pragma endregion

							//#pragma region Drenagem de HP do mob com skill de HT
							//							if (pMob[conn].MOB.Rsv & 2)
							//							{
							//							int mob_maxhp = pMob[target].MOB.CurrentScore.MaxHp;
							//							int myspecial = pMob[conn].MOB.CurrentScore.Special[3];
							//
							//							mob_maxhp = myspecial + mob_maxhp / 30;
							//							int myhp = pMob[conn].MOB.CurrentScore.Hp;
							//
							//							pMob[conn].MOB.CurrentScore.Hp += mob_maxhp;
							//
							//							if (pMob[conn].MOB.CurrentScore.Hp > pMob[conn].MOB.CurrentScore.MaxHp)
							//							pMob[conn].MOB.CurrentScore.Hp = pMob[conn].MOB.CurrentScore.MaxHp;
							//
							//							if (myhp != pMob[conn].MOB.CurrentScore.Hp)
							//							{
							//							if (conn > 0 && conn < MAX_USER)
							//							{
							//							SetReqHp(conn);
							//							SetReqMp(conn);
							//							}
							//
							//							MSG_SetHpDam hpDam;
							//							MSG_SetHpDam hpDam;
							//
							//							hpDam.Type = _MSG_SetHpDam;
							//							hpDam.Size = sizeof(MSG_SetHpDam);
							//							hpDam.ID = conn;
							//							hpDam.Hp = pMob[conn].MOB.CurrentScore.Hp;
							//							hpDam.Dam = pMob[conn].MOB.CurrentScore.Hp - myhp;
							//
							//							GridMulticast(pMob[conn].TargetX, pMob[conn].TargetY, (MSG_STANDARD*)&hpDam, 0);
							//							}
							//							}
#pragma endregion
							DeleteMob(target, 1);



							if (GenerateID == BARAO_AZUL)
							{
								//char temp[1024];
								//snprintf(temp, sizeof(temp), "O Jogador %s Derrotou o Barao Azul !!!", pMob[conn].MOB.MobName);
								RvRBluePoint += 100;
							}
							if (GenerateID == BARAO_VERMELHO)
							{
								//char temp[1024];
								//snprintf(temp, sizeof(temp), "O Jogador %s Derrotou o Barao Vermelho !!!", pMob[conn].MOB.MobName);
								RvRRedPoint += 100;
							}
							if (GenerateID == ENT_OBSCURO_BLUE)
							{
								//char temp[1024];
								//snprintf(temp, sizeof(temp), "O Jogador %s Derrotou o Ent Obscuro !!!", pMob[conn].MOB.MobName);
								RvRBluePoint += 25;
							}
							if (GenerateID == ENT_OBSCURO_RED)
							{
								//char temp[1024];
								//snprintf(temp, sizeof(temp), "O Jogador %s Derrotou o Ent Obscuro !!!", pMob[conn].MOB.MobName);
								RvRRedPoint += 25;
							}


#pragma region carta (N)
							if (GenerateID >= SECRET_ROOM_N_SALA1_MOB_1 && GenerateID <= SECRET_ROOM_N_SALA1_MOB_2)
								CartaDrop(conn, target, 1);

							if (GenerateID >= SECRET_ROOM_N_SALA2_MOB_1 && GenerateID <= SECRET_ROOM_N_SALA2_MOB_2)
								CartaDrop(conn, target, 2);

							if (GenerateID >= SECRET_ROOM_N_SALA3_MOB_1 && GenerateID <= SECRET_ROOM_N_SALA3_MOB_2)
								CartaDrop(conn, target, 3);

							if (GenerateID >= SECRET_ROOM_N_SALA4_MOB_1 && GenerateID <= SECRET_ROOM_N_SALA4_MOB_2)
								CartaDrop(conn, target, 4);
#pragma endregion

#pragma region carta (M)
							if (GenerateID >= SECRET_ROOM_M_SALA1_MOB_1 && GenerateID <= SECRET_ROOM_M_SALA1_MOB_2)
							{
								STRUCT_ITEM item;
								memset(&item, 0, sizeof(STRUCT_ITEM));

								int _rand = rand() % 10;


								if (_rand == 0)
									item.sIndex = 420;

								else if (_rand == 1)
									item.sIndex = 419;

								/*else if (_rand == 2)
									item.sIndex = 412;

								else if (_rand == 3)
									item.sIndex = 413;*/

								if (item.sIndex)
								{
									SetItemBonus(&item, 0, 0, 0);

									PutItem(conn, &item);
								}
							}
#pragma endregion

#pragma region carta (M)
							if (GenerateID >= SECRET_ROOM_M_SALA2_MOB_1 && GenerateID <= SECRET_ROOM_M_SALA2_MOB_2)
							{
								STRUCT_ITEM item;
								memset(&item, 0, sizeof(STRUCT_ITEM));

								int _rand = rand() % 10;


								if (_rand == 0)
									item.sIndex = 413;

								else if (_rand == 1)
									item.sIndex = 419;

								else if (_rand == 2)
									item.sIndex = 412;

								else if (_rand == 3)
									item.sIndex = 413;

								if (item.sIndex)
								{
									SetItemBonus(&item, 0, 0, 0);

									PutItem(conn, &item);
								}
							}
#pragma endregion

#pragma region carta (M)
							if (GenerateID >= SECRET_ROOM_M_SALA3_MOB_1 && GenerateID <= SECRET_ROOM_M_SALA3_MOB_2)
							{
								STRUCT_ITEM item;
								memset(&item, 0, sizeof(STRUCT_ITEM));

								int _rand = rand() % 10;


								if (_rand == 0)
									item.sIndex = 2444;

								else if (_rand == 1)
									item.sIndex = 2443;

								else if (_rand == 2)
									item.sIndex = 2442;

								else if (_rand == 3)
									item.sIndex = 2441;

								if (item.sIndex)
								{
									SetItemBonus(&item, 0, 0, 0);

									PutItem(conn, &item);
								}
							}
#pragma endregion

#pragma region carta (M)
							if (GenerateID >= SECRET_ROOM_M_SALA4_MOB_1 && GenerateID <= SECRET_ROOM_M_SALA4_MOB_2)
							{
								STRUCT_ITEM item;
								memset(&item, 0, sizeof(STRUCT_ITEM));

								int _rand = rand() % 10;


								if (_rand == 0)
									item.sIndex = 412;

								else if (_rand == 1)
									item.sIndex = 413;

								else if (_rand == 2)
									item.sIndex = 412;

								else if (_rand == 3)
									item.sIndex = 413;

								if (item.sIndex)
								{
									SetItemBonus(&item, 0, 0, 0);

									PutItem(conn, &item);
								}
							}
#pragma endregion
#pragma region carta (A)
							if (GenerateID >= SECRET_ROOM_A_SALA1_MOB_1 && GenerateID <= SECRET_ROOM_A_SALA1_MOB_2)
							{
								STRUCT_ITEM item;
								memset(&item, 0, sizeof(STRUCT_ITEM));

								int _rand = rand() % 5;


								if (_rand == 0)
									item.sIndex = 413;

								else if (_rand == 1)
									item.sIndex = 412;


								if (item.sIndex)
								{
									SetItemBonus(&item, 0, 0, 0);

									PutItem(conn, &item);
								}
							}
#pragma endregion
#pragma region carta (A)
							if (GenerateID >= SECRET_ROOM_A_SALA2_MOB_1 && GenerateID <= SECRET_ROOM_A_SALA2_MOB_2)
							{
								STRUCT_ITEM item;
								memset(&item, 0, sizeof(STRUCT_ITEM));

								int _rand = rand() % 5;


								if (_rand == 0)
									item.sIndex = 413;

								else if (_rand == 1)
									item.sIndex = 412;


								if (item.sIndex)
								{
									SetItemBonus(&item, 0, 0, 0);

									PutItem(conn, &item);
								}
							}
#pragma endregion
#pragma region carta (A)
							if (GenerateID >= SECRET_ROOM_A_SALA3_MOB_1 && GenerateID <= SECRET_ROOM_A_SALA3_MOB_2)
							{
								STRUCT_ITEM item;
								memset(&item, 0, sizeof(STRUCT_ITEM));

								int _rand = rand() % 5;


								if (_rand == 0)
									item.sIndex = 612;

								else if (_rand == 1)
									item.sIndex = 613;

								else if (_rand == 2)
									item.sIndex = 614;

								else if (_rand == 3)
									item.sIndex = 615;


								if (item.sIndex)
								{
									SetItemBonus(&item, 0, 0, 0);

									PutItem(conn, &item);
								}
							}
#pragma endregion

#pragma region carta (A)
							if (GenerateID >= SECRET_ROOM_A_SALA4_MOB_1 && GenerateID <= SECRET_ROOM_A_SALA4_MOB_2)
							{
								STRUCT_ITEM item;
								memset(&item, 0, sizeof(STRUCT_ITEM));

								int _rand = rand() % 5;

								if (_rand == 0)
									item.sIndex = 413;

								else if (_rand == 1)
									item.sIndex = 413;

								else if (_rand == 2)
									item.sIndex = 413;

								else if (_rand == 3)
									item.sIndex = 413;

								if (item.sIndex)
								{
									SetItemBonus(&item, 0, 0, 0);

									PutItem(conn, &item);
								}
							}
#pragma endregion

#pragma region Coliseu (N)
							if (GenerateID >= COLISEU_N_INITIAL && GenerateID <= COLISEU_N_END)
							{
								STRUCT_ITEM item;
								memset(&item, 0, sizeof(STRUCT_ITEM));

								int _rand = rand() % 20;

								if (_rand == 0 || _rand == 1 || _rand == 2 || _rand == 3)
									item.sIndex = 419;

								else if (_rand == 4 || _rand == 5)
									item.sIndex = 420;

								else if (_rand == 6)
									item.sIndex = 4019;

								SetItemBonus(&item, 0, 0, 0);

								if (pMob[conn].MOB.Equip[13].sIndex == 3901 || pMob[conn].MOB.Equip[13].sIndex == 3902) {
									SendItemagrupar(conn, item.sIndex);
								}
								else {
									PutItem(conn, &item);
								}
							}
#pragma endregion

#pragma region Coliseu (M)
							if (GenerateID >= COLISEU_M_INITIAL && GenerateID <= COLISEU_M_END)
							{
								STRUCT_ITEM item;
								memset(&item, 0, sizeof(STRUCT_ITEM));

								int _rand = rand() % 20;

								if (_rand == 0 || _rand == 1 || _rand == 2 || _rand == 3)
									item.sIndex = 419;

								else if (_rand == 4 || _rand == 5)
									item.sIndex = 420;

								else if (_rand == 6)
									item.sIndex = 4020;

								SetItemBonus(&item, 0, 0, 0);

								if (pMob[conn].MOB.Equip[13].sIndex == 3901 || pMob[conn].MOB.Equip[13].sIndex == 3902) {
									SendItemagrupar(conn, item.sIndex);
								}
								else {
									PutItem(conn, &item);
								}
							}
#pragma endregion

#pragma region Coliseu (A)
							if (GenerateID >= COLISEU_A_INITIAL && GenerateID <= COLISEU_A_END)
							{
								STRUCT_ITEM item;
								memset(&item, 0, sizeof(STRUCT_ITEM));

								int _rand = rand() % 20;

								if (_rand == 0 || _rand == 1 || _rand == 2 || _rand == 3)
									item.sIndex = 419;

								else if (_rand == 4 || _rand == 5)
									item.sIndex = 420;

								SetItemBonus(&item, 0, 0, 0);

								if (pMob[conn].MOB.Equip[13].sIndex == 3901 || pMob[conn].MOB.Equip[13].sIndex == 3902) {
									SendItemagrupar(conn, item.sIndex);
								}
								else {
									PutItem(conn, &item);
								}
							}
#pragma endregion

#pragma region Pista +1 - Lugefer_Inf
							if (GenerateID >= RUNEQUEST_LV1_MOB_INITIAL && GenerateID <= RUNEQUEST_LV1_MOB_END)
								GenerateMob(GenerateID, 0, 0);
#pragma endregion
#pragma region Pista +2 - Amon_Inf
							if (GenerateID >= RUNEQUEST_LV2_MOB_INITIAL && GenerateID <= RUNEQUEST_LV2_MOB_END)
								GenerateMob(GenerateID, 0, 0);
#pragma endregion
#pragma region Kefra - Mago_Negro
							if (GenerateIndex >= KEFRA_MOB_INITIAL && GenerateIndex <= KEFRA_MOB_END && KefraLive == 0)
								GenerateMob(GenerateIndex, 0, 0);
#pragma endregion

							CWarTower::MobKilled(target, conn, PosX, PosY);
						}
						else
							DeleteMob(target, 1);
					}
				}

				else
				{
					GridMulticast(pMob[target].TargetX, pMob[target].TargetY, (MSG_STANDARD*)&sm, 0);
					DeleteMob(target, 1);
				}
			}

			else
			{
				GridMulticast(pMob[target].TargetX, pMob[target].TargetY, (MSG_STANDARD*)&sm, 0);
				DeleteMob(target, 1);
			}
		}
		else
		{
			pUser[target].ReqHp = pMob[target].MOB.CurrentScore.MaxHp;
			SetReqHp(target);

			pMob[target].MOB.CurrentScore.Hp = pMob[target].MOB.CurrentScore.MaxHp;
			SendScore(target);
		}
	}
#pragma endregion


#pragma region PvP
	else
	{
		int tlevel = pMob[target].MOB.BaseScore.Level;

		if (tlevel < 0 || tlevel > MAX_LEVEL)
			return;

#pragma region Lose EXP
		unsigned int curexp = (unsigned int)(pMob[target].extra.ClassMaster == MORTAL || pMob[target].extra.ClassMaster == ARCH ? g_pNextLevel[tlevel] : g_pNextLevel_2[tlevel]);
		unsigned int nextexp = (unsigned int)(pMob[target].extra.ClassMaster == MORTAL || pMob[target].extra.ClassMaster == ARCH ? g_pNextLevel[tlevel + 1] : g_pNextLevel_2[tlevel + 1]);
		unsigned int alphaexp = (nextexp - curexp);
		unsigned int deltaexp = (nextexp - curexp) / 20;

		if (tlevel >= 30)
			deltaexp = alphaexp / 22;

		if (tlevel >= 40)
			deltaexp = alphaexp / 25;

		if (tlevel >= 50)
			deltaexp = alphaexp / 30;

		if (tlevel >= 60)
			deltaexp = alphaexp / 35;

		if (tlevel >= 70)
			deltaexp = alphaexp / 40;

		if (tlevel >= 80)
			deltaexp = alphaexp / 45;

		if (tlevel >= 90)
			deltaexp = alphaexp / 50;

		if (tlevel >= 100)
			deltaexp = alphaexp / 55;

		if (tlevel >= 150)
			deltaexp = alphaexp / 70;

		if (tlevel >= 200)
			deltaexp = alphaexp / 85;

		if (tlevel >= 250)
			deltaexp = alphaexp / 100;

		if (deltaexp < 0)
			deltaexp = 0;
		if (deltaexp > 150000)
			deltaexp = 150000;
#pragma endregion

		int killer_curkill = GetCurKill(conn);
		int killer_totkill = GetTotKill(conn);
		int killer_pkpoint = GetPKPoint(conn);
		int killed_pkpoint = GetPKPoint(target);
		int killed_guilty = GetGuilty(target);
		int killed_curkill = GetCurKill(target);
		int killed_clan = pMob[target].MOB.Clan;
		int killer_clan = pMob[conn].MOB.Clan;
		int SameClan = 0;
		int AtWar = 0;

		if (killed_pkpoint > 10 && killed_pkpoint <= 25)
			deltaexp *= 3;
		else
			deltaexp *= 5;

		int killed_x = pMob[target].TargetX / 128;
		int killed_y = pMob[target].TargetY / 128;

#pragma region No lose At war
		if (conn < MAX_USER)
		{
			if (pMob[conn].TargetX >= 128 && pMob[conn].TargetY <= 4000)
			{
				if (killer_pkpoint >= 31 && killer_pkpoint <= 74)// 12
				{

					pMob[conn].extra.EMPTY[0] = 1;
					SendEtc(conn);
					pMob[conn].GetCurrentScore(conn);
					SendScore(conn);
				}
				if (killer_pkpoint <= 30) //-56
				{

					pMob[conn].extra.EMPTY[1] = 1;
					pMob[conn].extra.EMPTY[0] = 0;
					SendEtc(conn);
					pMob[conn].GetCurrentScore(conn);
					SendScore(conn);
				}

			}
			if (TESTSERVER)
				deltaexp /= 3;

			else
				deltaexp /= 6;

			if (killed_clan == 7 && killer_clan == 8 || killed_clan == 8 && killer_clan == 7)
				SameClan = 1;

			if (killed_clan == 7 && killer_clan == 8 || killed_clan == 8 && killer_clan == 7)
				SameClan = 1;

			int killed_guild = pMob[target].MOB.Guild;
			int killer_guild = pMob[conn].MOB.Guild;
			int max_guild = 65536;

			if (killed_guild > 0 && killed_guild < max_guild && killer_guild > 0 && killer_guild < max_guild
				&& g_pGuildWar[killed_guild] == killer_guild && g_pGuildWar[killer_guild] == killed_guild)
				AtWar = 1;

			if (CastleState && killed_x == 8 && killed_y == 13)
				AtWar = 1;

			if (RvRState != 0)
				AtWar = 1;

			if (GTorreState != 0)
				AtWar = 1;

		}
#pragma endregion

		GridMulticast(pMob[target].TargetX, pMob[target].TargetY, (MSG_STANDARD*)&sm, 0);

		int arena = BASE_GetArena(pMob[target].TargetX, pMob[target].TargetY);
		int village = BASE_GetVillage(pMob[target].TargetX, pMob[target].TargetY);
		int ZoneUnk = 0;

		if (killed_x == 1 && killed_y == 31)
			ZoneUnk = 1;

		if (arena != 5 || village != 5 || ZoneUnk || (pMob[target].TargetX > 1078 && pMob[target].TargetY > 1725 && pMob[target].TargetX < 1102 && pMob[target].TargetY < 1737))
		{


			//pMob[conn].extra.EMPTY[3] = 1;
			if (arena == 5 && village != 5)
			{
				FILE* fpp = NULL;

				fpp = fopen("TesteDie.txt", "a+");
				
				printf(temp, "%s %s %d %d %d %d\n", pMob[conn].MOB.MobName, pMob[target].MOB.MobName, conn, target, pMob[target].TargetX, pMob[target].TargetY);

				fclose(fpp);
			}
			/*
						if (arena >= 0 && arena < MAX_GUILDZONE)
						{
							STRUCT_ITEM item;
							memset(&item, 0, sizeof(STRUCT_ITEM));

							item.sIndex = 431;
							SetItemBonus(&item, 0, 0, 0);

							CreateItem(pMob[target].TargetX, pMob[target].TargetY, &item, rand() % 4, 1);
						}*/
		}

		else
		{
			if (TESTSERVER)
				deltaexp /= 4;

			if (SameClan)
				deltaexp += killed_curkill * deltaexp / 4;

			if (deltaexp > 30000)
				deltaexp = 30000;

			if (deltaexp < 0)
				deltaexp = 0;


			if ((tlevel >= 35 || pMob[target].extra.ClassMaster != MORTAL) && NewbieEventServer == 0)
			{
				if (conn >= MAX_USER)
				{
					if (DEADPOINT)
						pMob[target].extra.Hold += (unsigned int)(pMob[target].MOB.Exp > deltaexp ? deltaexp : pMob[target].MOB.Exp);
				}
				else
					pMob[target].extra.Hold += (unsigned int)(pMob[target].MOB.Exp > deltaexp ? deltaexp : pMob[target].MOB.Exp);

				if (DEADPOINT || conn < MAX_USER)
				{
					SendMsgExp(target, strFmt(g_pMessageStringTable[_DN_lose_D_exp], deltaexp), TNColor::Speak, false);
					SendEtc(target);
				}
			}
			else if (pMob[target].MOB.CurrentScore.Level < FREEEXP && pMob[target].extra.ClassMaster == MORTAL && NewbieEventServer == 0) {
				GridMulticast(pMob[target].TargetX, pMob[target].TargetY, (MSG_STANDARD*)&sm, 0);
				SendMsgExp(target, g_pMessageStringTable[_NN_Below_lv20_No_Exp_Loss], TNColor::Default, false);
			}
			if (SameClan)
			{
				SendEtc(conn);

				++killer_curkill;
				SetCurKill(conn, killer_curkill);

				++killer_totkill;
				SetTotKill(conn, killer_totkill);

				if (AtWar == 0 && killed_guilty == 0)
				{
					int Lostpk = 3 * killed_pkpoint / -20;
					if (Lostpk < -3)
						Lostpk = -3;

					if (Lostpk > 0)
						Lostpk = 0;

					if (killed_guilty > 0)
						Lostpk = 0;

					killer_pkpoint += Lostpk;
					SetPKPoint(conn, killer_pkpoint);
					SendClientMessage(conn, strFmt(g_pMessageStringTable[_DD_PKPointMinus], killer_pkpoint - 75, Lostpk));
					GridMulticast(pMob[target].TargetX, pMob[target].TargetY, (MSG_STANDARD*)&sm, 0);
				}

				if (pMob[target].TargetX >= 1017 && pMob[target].TargetX <= 1290 && pMob[target].TargetY >= 1911 && pMob[target].TargetY <= 2183)
				{
					if (pMob[target].MOB.Clan == 7)
					{
						pMob[target].MOB.CurrentScore.Hp = 200;
						pMob[target].GetCurrentScore(target);
						SendScore(target);
						DoTeleport(target, 1072 + rand() % 2, 2140 + rand() % 2);
						RvRRedPoint++;
					}

					else if (pMob[target].MOB.Clan == 8)
					{
						pMob[target].MOB.CurrentScore.Hp = 200;
						pMob[target].GetCurrentScore(target);
						SendScore(target);
						DoTeleport(target, 1237 + rand() % 2, 1971 + rand() % 2);
						RvRBluePoint++;
					}
					GridMulticast(pMob[target].TargetX, pMob[target].TargetY, (MSG_STANDARD*)&sm, 0);
				}
			}
#pragma region Perca de CP
			else
			{
				int AtWarMap = 0;

				//torre
				if (AtWar == 1 && pMob[target].TargetX >= 2445 && pMob[target].TargetX <= 1850 && pMob[target].TargetY >= 1850 && pMob[target].TargetY <= 1920)
					AtWarMap = 1;

				//rvr
				if (AtWar == 1 && pMob[target].TargetX >= 1017 && pMob[target].TargetX <= 1290 && pMob[target].TargetY >= 1911 && pMob[target].TargetY <= 2183)
					AtWarMap = 1;

				//batalha real
				if (pMob[target].TargetX >= 140 && pMob[target].TargetX <= 200 && pMob[target].TargetY >= 4000 && pMob[target].TargetY <= 4100)
					AtWarMap = 1;

				//batalha de castelo
				if (AtWar == 1 && pMob[target].TargetX >= 1024 && pMob[target].TargetY >= 1664 && pMob[target].TargetX <= 1153 && pMob[target].TargetY <= 1793)
					AtWarMap = 1;

				if (AtWarMap != 1) {
					int LostPk = 3 * killed_pkpoint / -25;

					if (LostPk < -3)
						LostPk = -3;

					if (LostPk > 0)
						LostPk = 0;

					if (killed_guilty > 0)
						LostPk = 0;

					//aumenta o pk quando mata mortal
					if (pMob[target].MOB.Equip[15].sIndex == 548 || pMob[target].MOB.Equip[15].sIndex == 549 || pMob[conn].MOB.Equip[15].sIndex == 548 || pMob[conn].MOB.Equip[15].sIndex == 549)
						LostPk *= 1;

					killer_pkpoint += LostPk;

					SetPKPoint(conn, killer_pkpoint);

					if (LostPk)
					{
						SendClientMessage(conn, strFmt(g_pMessageStringTable[_DD_PKPointMinus], killer_pkpoint - 75, -LostPk));
						SendEtc(conn);
					}

#pragma region  Perca de itens, cp negativo
					if (killed_pkpoint >= 31 && killed_pkpoint <= 74)// 12
					{
						pMob[target].extra.EMPTY[0] = 1;
						SendEtc(target);
						pMob[target].GetCurrentScore(target);
						SendScore(target);
					}
					if (killed_pkpoint <= 30) //-56
					{

						pMob[target].extra.EMPTY[1] = 1;
						pMob[target].extra.EMPTY[0] = 0;
						SendEtc(target);
						pMob[target].GetCurrentScore(target);
						SendScore(target);
					}
					GridMulticast(pMob[target].TargetX, pMob[target].TargetY, (MSG_STANDARD*)&sm, 0);
#pragma endregion
				}

			}
			GetCreateMob(conn, &sCreateMob);
			GridMulticast(pMob[conn].TargetX, pMob[conn].TargetY, (MSG_STANDARD*)&sCreateMob, 0);

			if (SameClan)
				SetCurKill(target, 0);

			if (killed_pkpoint < 75 && !AtWar && conn < MAX_USER)
			{
				killed_pkpoint++;
				SetPKPoint(target, killed_pkpoint);
				SendMsgExp(target, strFmt(g_pMessageStringTable[_DD_PKPointPlus], killed_pkpoint - 75, 1), TNColor::Red, false);
			}
			GetCreateMob(target, &sCreateMob);
			GridMulticast(pMob[target].TargetX, pMob[target].TargetY, (MSG_STANDARD*)&sCreateMob, 0);
		}

		if (pMob[target].MOB.Equip[13].sIndex == 753 || pMob[target].MOB.Equip[13].sIndex == 1726)//10X HP MOB  - 20X HP MOB
		{
			int sanc = BASE_GetItemSanc(&pMob[target].MOB.Equip[13]);
			if (sanc > 0)
			{
				sanc--;

				if (pMob[target].MOB.Equip[13].stEffect[0].cEffect == 43)
					pMob[target].MOB.Equip[13].stEffect[0].cValue = sanc;

				else if (pMob[target].MOB.Equip[13].stEffect[1].cEffect == 43)
					pMob[target].MOB.Equip[13].stEffect[1].cValue = sanc;

				else if (pMob[target].MOB.Equip[13].stEffect[2].cEffect == 43)
					pMob[target].MOB.Equip[13].stEffect[2].cValue = sanc;
			}
			else
				BASE_ClearItem(&pMob[target].MOB.Equip[13]);

			SendItem(target, ITEM_PLACE_EQUIP, 13, &pMob[target].MOB.Equip[13]);
		}
		GridMulticast(pMob[target].TargetX, pMob[target].TargetY, (MSG_STANDARD*)&sm, 0);
	}
	//pMob[target].extra.EMPTY[3] = 1;
#pragma endregion
}
