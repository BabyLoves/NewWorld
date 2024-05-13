
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
#include "ProcessClientMessage.h"
#include "GetFunc.h"
#include "SendFunc.h"
#include "wMySQL.h"
#include "Functions.h"


void ProcessDBMessage(char* Msg)
{
	MSG_STANDARD* std = (MSG_STANDARD*)Msg;

	//printf("DB Pacote: %X - Tamanho: %d - Index: %d\n", std->Type, std->Size, std->ID);  //pacotes print


	if (!(std->Type & FLAG_DB2GAME) || (std->ID < 0) || (std->ID >= MAX_USER))
	{
		MSG_STANDARD* m = (MSG_STANDARD*)Msg;
		
		snprintf(temp, sizeof(temp), "err,packet Type:%d ID:%d Size:%d KeyWord:%d", m->Type, m->ID, m->Size, m->KeyWord);

		SystemLog("-system", "-", 0, temp);

		return;
	}

	int conn = std->ID;
#pragma region DB - TM
	if (conn == 0)
	{
		switch (std->Type)
		{

		case _MSG_TransperCharacter:
		{

			TransperCharacter = 1;
			SystemLog("-system", "-", 0, "TransperCharacter mode");

		} break;

		case _MSG_DBSetIndex:
		{
			MSG_STANDARDPARM3* m = (MSG_STANDARDPARM3*)Msg;

			if (m->Parm1 != -1)
			{
				ServerGroup = m->Parm1;
				ServerIndex = m->Parm3;
			}

			Sapphire = m->Parm2;

		} break; // TODO: Check if it isn't a break (must compile and check against the original TM

		case _MSG_War:
		{
			MSG_STANDARDPARM2* m = (MSG_STANDARDPARM2*)Msg;

			DoWar(m->Parm1, m->Parm2);

		} break;

		case _MSG_GuildAlly:
		{
			MSG_STANDARDPARM2* m = (MSG_STANDARDPARM2*)Msg;

			DoAlly(m->Parm1, m->Parm2);

		} break;

		case _MSG_GuildInfo:
		{
			MSG_GuildInfo* m = (MSG_GuildInfo*)Msg;

			GuildInfo[m->Guild] = m->GuildInfo;

		} break;

		case _MSG_GuildReport:
		{
			MSG_GuildReport* m = (MSG_GuildReport*)Msg;

			memmove_s(ChargedGuildList, sizeof(ChargedGuildList), m->ChargedGuildList, sizeof(ChargedGuildList));
		} break;

		case _MSG_NPNotice:
		{
			MSG_NPNotice* m = (MSG_NPNotice*)Msg;

			if (m->Parm1 == 1)
				SendNotice(m->String);

		} break;

		case _MSG_MessageDBImple:
		{
			MSG_MessageDBImple* m = (MSG_MessageDBImple*)Msg;

			m->String[MESSAGE_LENGTH - 1] = 0;
			m->String[MESSAGE_LENGTH - 2] = 0;

			SystemLog("-system", "-", 0, m->String);

			ProcessImple(0, m->Level, m->String);

		} break; // TODO: Check if it isn't a break (must compile and check against the original TM

		case _MSG_MagicTrumpet:
		{
			SyncMulticast(0, (MSG_STANDARD*)Msg, 0);
		} break;

		case _MSG_DBNotice:
		{
			MSG_DBNotice* m = (MSG_DBNotice*)Msg;

			SendNotice(m->String);
		} break;


		}
	}
#pragma endregion
#pragma region DB - TM - CLIENT
	else
	{
		if ((conn > 0 && conn < MAX_USER) && pUser[conn].Mode == 0)
		{
			MSG_STANDARD sm;

			sm.Type = _MSG_DBNoNeedSave;
			sm.ID = conn;

			DBServerSocket.SendOneMessage((char*)&sm, sizeof(MSG_STANDARD));

			return;
		}

		if (conn <= 0 || conn > MAX_USER)
		{
			
			snprintf(temp, sizeof(temp), "Unknown DB Message - conn:%d - type:%d", conn, std->Type);
			SystemLog("-system", "-", 0, temp);

			return;
		}

		switch (std->Type)
		{
#pragma region _MSG_ReqTransper
		case _MSG_ReqTransper:
		{
			if (TransperCharacter == 0)
				return;

			MSG_ReqTransper* m = (MSG_ReqTransper*)Msg;

			m->ID = ESCENE_FIELD + 1;

			pUser[conn].cSock.SendOneMessage((char*)&m, sizeof(MSG_ReqTransper));

			pUser[conn].Mode = USER_CHARWAIT;

		} break;
#pragma endregion

#pragma region _MSG_DBSendItem
		case _MSG_DBSendItem:
		{
			MSG_DBSendItem* m = (MSG_DBSendItem*)Msg;

			if (pUser[conn].Mode < USER_CHARWAIT)
			{
				/*char ItemCode[256];
				snprintf(temp, sizeof(temp), "tra,%s", pUser[conn].AccountName);
				BASE_GetItemCode(&m->Item, ItemCode);
				strcat(temp, ItemCode);
				SystemLog("_fail_play_", "-", pUser[conn].IP, temp);*/

				break;
			}

			if (strcmp(pUser[conn].AccountName, m->Account) != 0)
			{
				/*char ItemCode[256];
				snprintf(temp, sizeof(temp), "tra,%s", pUser[conn].AccountName);
				BASE_GetItemCode(&m->Item, ItemCode);
				strcat(temp, ItemCode);
				SystemLog("_fail_play_", "-", pUser[conn].IP, temp);*/

				break;
			}

			int i = 0;


			for (; i < MAX_CARGO - 8; i++)
			{
				if (pUser[conn].Cargo[i].sIndex != 0)
					continue;

				memmove_s(&pUser[conn].Cargo[i], sizeof(STRUCT_ITEM), &m->Item, sizeof(STRUCT_ITEM));

				SendItem(conn, ITEM_PLACE_CARGO, i, &m->Item);

				SendClientMessage(conn, strFmt("%s [%s]", g_pMessageStringTable[_NN_Item_Arrived], g_pItemList[m->Item.sIndex].Name));
				
				snprintf(temp, sizeof(temp), "Jogador [%s] recebeu pela import item: %s %d %d %d %d %d %d %d", pMob[conn].MOB.MobName, g_pItemList[m->Item.sIndex].Name, m->Item.sIndex,
					m->Item.stEffect[0].cValue, m->Item.stEffect[0].cEffect, //EF1 EFV1
					m->Item.stEffect[1].cValue, m->Item.stEffect[1].cEffect, //EF2 EFV2
					m->Item.stEffect[2].cValue, m->Item.stEffect[2].cEffect); //EF3 EFV3
				ItemLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, temp);

				m->Result = 0;
				m->Size = sizeof(m);

				DBServerSocket.SendOneMessage((char*)m, sizeof(m));

				/*char ItemCode[256];
				snprintf(temp, sizeof(temp), "tra,%s %d", pUser[conn].AccountName, i);
				BASE_GetItemCode(&m->Item, ItemCode);
				strcat(temp, ItemCode);
				SystemLog("_web1_", "-", pUser[conn].IP, temp2);*/


				if (pUser[conn].Mode == USER_CHARWAIT)
					SaveUser(conn, 0);

				return;
			}



			m->Result = 3;
			m->Size = sizeof(m);
			DBServerSocket.SendOneMessage((char*)m, sizeof(m));

			char ItemCode[256];

			SaveUser(conn, 1);
			/*
			snprintf(temp, sizeof(temp), "tra,%s", pUser[conn].AccountName);
			BASE_GetItemCode(&m->Item, ItemCode);
			strcat(temp, ItemCode);
			SystemLog("_fail_empty_", "-", pUser[conn].IP, temp);*/

		} break;
#pragma endregion
#pragma region _MSG_NPNotice
		case _MSG_NPNotice:
		{
			MSG_NPNotice* m = (MSG_NPNotice*)Msg;

			if (m->Parm1 == 0)
			{
				if (pUser[conn].Mode == USER_PLAY)
					SendClientMessage(conn, m->String);
			}

		} break;
#pragma endregion
#pragma region _MSG_DBCNFAccountLogin
		case _MSG_DBCNFAccountLogin:
		{
			MSG_DBCNFAccountLogin* m = (MSG_DBCNFAccountLogin*)Msg;

			if (strcmp(m->AccountName, pUser[conn].AccountName) != 0)
			{
				SendClientMessage(conn, g_pMessageStringTable[_NN_Try_Reconnect]);

				pUser[conn].cSock.SendMessageA();

				CloseUser(conn);

				return;
			}


			pUser[conn].IsBillConnect = 0;
			pUser[conn].Whisper = 0;
			pUser[conn].Guildchat = 0;
			pUser[conn].PartyChat = 0;
			pUser[conn].KingChat = 0;
			pUser[conn].Admin = 0;
			pUser[conn].Chatting = 0;
			pUser[conn].Unk_2732 = 0;
			pUser[conn].Unk_2728 = 0;
			pUser[conn].OnlyTrade = 0;
			pUser[conn].chave1 = m->chave1;
			pUser[conn].chave2 = m->chave2;
			pUser[conn].chave3 = m->chave3;
			pUser[conn].Lasclick = -1;

			for (int i = 0; i < 50; i++) {
				pUser[conn].Keys[i] = m->nKeys[i];
			}

			m->ID = ESCENE_FIELD + 2;
			m->Type = _MSG_CNFAccountLogin;

			pUser[conn].Mode = USER_SELCHAR;

			for (int i = 0; i < MAX_CARGO; i++)
			{
				STRUCT_ITEM* tempsour = &m->Cargo[i];

				if (tempsour->sIndex > 0 && tempsour->sIndex < MAX_ITEMLIST)
				{
					int nPos = g_pItemList[tempsour->sIndex].nPos;

					if (nPos == 64 || nPos == 192)
					{
						if (tempsour->stEffect[0].cEffect == EF_DAMAGEADD || tempsour->stEffect[0].cEffect == EF_DAMAGE2)
							tempsour->stEffect[0].cEffect = EF_DAMAGE;

						if (tempsour->stEffect[1].cEffect == EF_DAMAGEADD || tempsour->stEffect[1].cEffect == EF_DAMAGE2)
							tempsour->stEffect[1].cEffect = EF_DAMAGE;

						if (tempsour->stEffect[2].cEffect == EF_DAMAGEADD || tempsour->stEffect[2].cEffect == EF_DAMAGE2)
							tempsour->stEffect[2].cEffect = EF_DAMAGE;
					}
				}
			}

			if (evDelete != 0)
			{
				for (int i = 0; i < MAX_CARGO; i++)
				{
					if (m->Cargo[i].sIndex >= 470 && m->Cargo[i].sIndex <= 500)
						m->Cargo[i].sIndex = 0;
				}
			}

			pUser[conn].cSock.SendOneMessage((char*)m, sizeof(MSG_DBCNFAccountLogin));

			memmove_s(pUser[conn].Cargo, sizeof(STRUCT_ITEM) * MAX_CARGO, m->Cargo, sizeof(STRUCT_ITEM) * MAX_CARGO);

			pUser[conn].Coin = m->Coin;
			pUser[conn].Unk_1816 = 0;
			pUser[conn].SelChar = m->sel;


			if (BILLING > 0 && IsFree(&m->sel) != 0)
			{
				if (CHARSELBILL == 0)
					SendBilling(conn, m->AccountName, 8, 1);
				else
					SendBilling(conn, m->AccountName, 1, 1);

				pUser[conn].Unk_2732 = SecCounter;
			}

			pUser[conn].Unk5[0] = 0;
			pUser[conn].LastClientTick = 0;

			SystemLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, "CNFAccountLogin");

			if (TransperCharacter != 0)
			{
				MSG_STANDARDPARM2 sm;

				sm.Type = _MSG_TransperCharacter;
				sm.ID = ESCENE_FIELD + 1;
				sm.Parm1 = 0;
				sm.Parm2 = 0;
				sm.Size = sizeof(MSG_STANDARDPARM2);

				pUser[conn].cSock.SendOneMessage((char*)&sm, sizeof(MSG_STANDARDPARM2));
			}
		} break;
#pragma endregion
#pragma region _MSG_DBNewAccountFail
		case _MSG_DBNewAccountFail:
		{
			MSG_STANDARD* m = (MSG_STANDARD*)Msg;

			m->ID = ESCENE_FIELD + 3;

			SendClientSignal(conn, 0, _MSG_NewAccountFail);

			CloseUser(conn);
		} break;
#pragma endregion
#pragma region _MSG_DBAccountLoginFail_Account
		case _MSG_DBAccountLoginFail_Account:
		{
			MSG_STANDARD* m = (MSG_STANDARD*)Msg;

			int ID = m->ID;

			SendClientMessage(conn, g_pMessageStringTable[_NN_No_Account_With_That_Name]);
			pUser[conn].cSock.SendMessageA();

			CloseUser(conn);

		} break;
#pragma endregion
#pragma region _MSG_DBAccountLoginFail_Block
		case _MSG_DBAccountLoginFail_Block:
		{
			MSG_STANDARDPARM* m = (MSG_STANDARDPARM*)Msg;

			int ID = m->ID;

			if (m->Parm == 0)
				snprintf(temp, sizeof(temp), g_pMessageStringTable[_SN_Blocked_Account], "X");

			else if (m->Parm == 1)
				snprintf(temp, sizeof(temp), g_pMessageStringTable[_SN_Blocked_Account], "A");

			else if (m->Parm == 2)
				snprintf(temp, sizeof(temp), g_pMessageStringTable[_SN_Blocked_Account], "B");

			else if (m->Parm == 3)
				snprintf(temp, sizeof(temp), g_pMessageStringTable[_SN_Blocked_Account], "C");

			SendClientMessage(conn, temp);
			pUser[conn].cSock.SendMessageA();

			CloseUser(conn);

		} break;
#pragma endregion
#pragma region _MSG_DBAccountLoginFail_Disable
		case _MSG_DBAccountLoginFail_Disable:
		{
			MSG_STANDARD* m = (MSG_STANDARD*)Msg;

			int ID = m->ID;

			SendClientMessage(conn, g_pMessageStringTable[_NN_Disabled_Account]);
			pUser[conn].cSock.SendMessageA();

			CloseUser(conn);

		} break;
#pragma endregion
#pragma region _MSG_AccountSecure
		case _MSG_AccountSecure:
		{
			pUser[conn].Mode = USER_CHARWAIT;
			SendClientSignal(std->ID, ESCENE_FIELD, _MSG_AccountSecure);
		} break;
#pragma endregion
#pragma region _MSG_AccountSecureFail
		case _MSG_AccountSecureFail:
		{
			pUser[conn].Mode = USER_CHARWAIT;
			SendClientSignal(std->ID, ESCENE_FIELD, _MSG_AccountSecureFail);
		} break;
#pragma endregion
#pragma region _MSG_DBOnlyOncePerDay
		case _MSG_DBOnlyOncePerDay:
		{
			MSG_STANDARD* m = (MSG_STANDARD*)Msg;

			int ID = m->ID;

			SendClientMessage(conn, g_pMessageStringTable[_NN_Only_Once_Per_Day]);
			pUser[conn].cSock.SendMessageA();

		} break;
#pragma endregion
#pragma region _MSG_DBAccountLoginFail_Pass
		case _MSG_DBAccountLoginFail_Pass:
		{
			MSG_STANDARD* m = (MSG_STANDARD*)Msg;

			int ID = m->ID;

			SendClientMessage(conn, g_pMessageStringTable[_NN_Wrong_Password]);
			pUser[conn].cSock.SendMessageA();

			CloseUser(conn);

		} break;
#pragma endregion
#pragma region _MSG_DBCNFNewCharacter
		case _MSG_DBCNFNewCharacter:
		{
			MSG_CNFNewCharacter* m = (MSG_CNFNewCharacter*)Msg;

			m->Type = _MSG_CNFNewCharacter;
			m->ID = ESCENE_FIELD + 1;

			pUser[conn].cSock.SendOneMessage((char*)m, sizeof(MSG_CNFNewCharacter));

			pUser[conn].Mode = USER_CHARWAIT;
			pUser[conn].WaitDB = false;


		} break;
#pragma endregion
#pragma region _MSG_DBCNFDeleteCharacter
		case _MSG_DBCNFDeleteCharacter:
		{
			MSG_CNFDeleteCharacter* m = (MSG_CNFDeleteCharacter*)Msg;

			m->Type = _MSG_CNFDeleteCharacter;
			m->ID = ESCENE_FIELD + 1;

			pUser[conn].cSock.SendOneMessage((char*)m, sizeof(MSG_CNFDeleteCharacter));

			pUser[conn].Mode = USER_CHARWAIT;

		} break;
#pragma endregion
#pragma region _MSG_DBDeleteCharacterFail
		case _MSG_DBDeleteCharacterFail:
		{
			MSG_STANDARD* m = (MSG_STANDARD*)Msg;

			m->ID = ESCENE_FIELD + 1;

			SendClientSignal(conn, 0, _MSG_DeleteCharacterFail);

			pUser[conn].Mode = USER_CHARWAIT;

		} break;
#pragma endregion
#pragma region _MSG_DBNewCharacterFail
		case _MSG_DBNewCharacterFail:
		{
			MSG_STANDARD* m = (MSG_STANDARD*)Msg;

			m->ID = ESCENE_FIELD + 1;

			SendClientSignal(conn, 0, _MSG_NewCharacterFail);

			pUser[conn].Mode = USER_CHARWAIT;
			pUser[conn].WaitDB = false;

		} break;
#pragma endregion
#pragma region _MSG_DBCNFCharacterLogin
		case _MSG_DBCNFCharacterLogin:
		{
			MSG_CNFCharacterLogin* m = (MSG_CNFCharacterLogin*)Msg;


			MSG_CNFClientCharacterLogin sm;

			memmove_s(&sm, sizeof(MSG_CNFClientCharacterLogin), m, sizeof(MSG_CNFClientCharacterLogin));

			if (conn == 0)
			{
				SystemLog("-system", "-", 0, "CNFCharLogin Crack Log");
				CloseUser(conn);

				break; // return; ?
			}

			int i;

			for (i = 0; i < MAX_EQUIP; i++)
			{
				STRUCT_ITEM* tempsour = &sm.mob.Equip[i];

				if (tempsour->sIndex > 0 && tempsour->sIndex < MAX_ITEMLIST)
				{
					int nPos = g_pItemList[tempsour->sIndex].nPos;

					if (nPos == 64 || nPos == 192)
					{
						if (tempsour->stEffect[0].cEffect == EF_DAMAGE2 || tempsour->stEffect[0].cEffect == EF_DAMAGEADD)
							tempsour->stEffect[0].cEffect = EF_DAMAGE;

						if (tempsour->stEffect[1].cEffect == EF_DAMAGE2 || tempsour->stEffect[1].cEffect == EF_DAMAGEADD)
							tempsour->stEffect[1].cEffect = EF_DAMAGE;

						if (tempsour->stEffect[2].cEffect == EF_DAMAGE2 || tempsour->stEffect[2].cEffect == EF_DAMAGEADD)
							tempsour->stEffect[2].cEffect = EF_DAMAGE;
					}
				}
			}

			for (i = 0; i < MAX_CARRY - 1; i++)
			{
				STRUCT_ITEM* tempsour = &sm.mob.Carry[i];

				if (tempsour->sIndex > 0 && tempsour->sIndex < MAX_ITEMLIST)
				{
					int nPos = g_pItemList[tempsour->sIndex].nPos;

					if (nPos == 64 || nPos == 192)
					{
						if (tempsour->stEffect[0].cEffect == EF_DAMAGE2 || tempsour->stEffect[0].cEffect == EF_DAMAGEADD)
							tempsour->stEffect[0].cEffect = EF_DAMAGE;

						if (tempsour->stEffect[1].cEffect == EF_DAMAGE2 || tempsour->stEffect[1].cEffect == EF_DAMAGEADD)
							tempsour->stEffect[1].cEffect = EF_DAMAGE;

						if (tempsour->stEffect[2].cEffect == EF_DAMAGE2 || tempsour->stEffect[2].cEffect == EF_DAMAGEADD)
							tempsour->stEffect[2].cEffect = EF_DAMAGE;
					}
				}
			}

			if (evDelete)
			{
				for (int j = 0; j < MAX_CARRY - 1; j++)
				{
					if (sm.mob.Carry[j].sIndex >= 470 && sm.mob.Carry[j].sIndex <= 500)
						sm.mob.Carry[j].sIndex = 0;
				}
			}
			//m->mobExtra.Citizen = pMob[conn].extra.Citizen;

			if (m->mobExtra.ClassMaster == MORTAL)
			{
				m->mob.Equip[0].stEffect[1].cEffect = 98;
				m->mob.Equip[0].stEffect[1].cValue = 0;
				m->mob.Equip[0].stEffect[2].cEffect = 86;
				m->mob.Equip[0].stEffect[2].cValue = m->mob.CurrentScore.Level - 298;
			}
			else if (m->mobExtra.ClassMaster == ARCH)
			{
				m->mob.Equip[0].stEffect[1].cEffect = 98;
				m->mob.Equip[0].stEffect[1].cValue = 0;
				m->mob.Equip[0].stEffect[2].cEffect = 86;


				if (pMob[conn].extra.QuestInfo.Arch.MortalSlot >= 0 && pMob[conn].extra.QuestInfo.Arch.MortalSlot < 3)
					m->mob.Equip[0].stEffect[2].cValue = pUser[conn].SelChar.Score[pMob[conn].extra.QuestInfo.Arch.MortalSlot].Level - 299;
				else
					m->mob.Equip[0].stEffect[2].cValue = 99;

				/*printf("mSlot %d mLevel %d value %d\n", pMob[conn].extra.QuestInfo.Arch.MortalSlot,
					pUser[conn].SelChar.Score[pMob[conn].extra.QuestInfo.Arch.MortalSlot].Level,
					m->mob.Equip[0].stEffect[2].cValue
				);*/
			}
			else if (m->mobExtra.ClassMaster == CELESTIAL || m->mobExtra.ClassMaster == SCELESTIAL || m->mobExtra.ClassMaster == CELESTIALCS)
			{
				m->mob.Equip[0].stEffect[1].cEffect = 98;
				m->mob.Equip[0].stEffect[1].cValue = 3;
				m->mob.Equip[0].stEffect[2].cEffect = 86;
				m->mob.Equip[0].stEffect[2].cValue = m->mob.CurrentScore.Level - 298;
			}


			pUser[conn].Donate = m->Donate;
			pUser[conn].Honra = m->Honra;

			for (int i = 0; i < 50; i++) {
				pUser[conn].Keys[i] = m->Keys[i];
			}


			pUser[conn].GemaX = m->GemaX;
			pUser[conn].GemaY = m->GemaY;

			if (m->mob.CurrentScore.Hp <= 0)
				m->mob.CurrentScore.Hp = 2;

			pMob[conn].MOB = m->mob;
			pUser[conn].Message = 0;
			pUser[conn].UseItemTime = 0;
			pUser[conn].PotionTime = 0;
			pMob[conn].LastReqParty = 0;
			pMob[conn].ProcessorCounter = 1;
			//pMob[conn].QuestFlag = 0;
			pMob[conn].MissPlayer = 0;
			pMob[conn].DivineBlessing = 0;
			pMob[conn].RateRegen = 0;
			pMob[conn].sPremioNovato[0] = ' ';
			pUser[conn].Ingame.MobDonateStore = FALSE;
			pUser[conn].Ingame.CheckPista = FALSE;
			pUser[conn].Ingame.CheckPesa = FALSE;
			pUser[conn].Ingame.CheckAgua = FALSE;
			pMob[conn].extra.EMPTY[3] = 0;
			pMob[conn].JoiaOn = FALSE;
			//memset(&pMob[conn].Evocations, 0, sizeof(pMob[conn].Evocations));
			memmove_s(&pMob[conn].extra, sizeof(STRUCT_MOBEXTRA), &m->mobExtra, sizeof(STRUCT_MOBEXTRA));

			for (int q = 0; q < MAX_ITEM_REBUY; q++)
			{
				memset(&pMob[conn].Rebuy[q].Item, 0, sizeof(STRUCT_ITEM));
				pMob[conn].Rebuy[q].Price = 0;
				pMob[conn].Rebuy[q].Ticks = 0;
			}

			if (m->mob.Guild)
				pMob[conn].extra.Citizen = GuildInfo[m->mob.Guild].Citizen;

			pMob[conn].MOB.Equip[0].stEffect[2].cEffect = 28;
			pMob[conn].MOB.Equip[0].stEffect[2].cValue = pMob[conn].extra.Citizen;

			memmove_s(pUser[conn].CharShortSkill, 16, m->ShortSkill, 16);

			memmove_s(pMob[conn].Affect, sizeof(m->affect), m->affect, sizeof(m->affect));

			pMob[conn].MaxCarry = 30;

			if (pMob[conn].MOB.Carry[60].sIndex == 3467)
				pMob[conn].MaxCarry += 15;

			if (pMob[conn].MOB.Carry[61].sIndex == 3467)
				pMob[conn].MaxCarry += 15;

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
			strncpy(pMob[conn].Tab, "", sizeof(pMob[conn].Tab));

			strncpy(pMob[conn].Snd, "", sizeof(pMob[conn].Snd));

			memset(sm.Unk2, 0, sizeof(sm.Unk2));

			pMob[conn].MOB.BaseScore.Merchant = 0;

			if (pMob[conn].extra.ClassMaster == ARCH && pMob[conn].extra.QuestInfo.Arch.MortalSlot >= 0 && pMob[conn].extra.QuestInfo.Arch.MortalSlot < 3)
				pMob[conn].extra.QuestInfo.Arch.MortalLevel = pUser[conn].SelChar.Score[pMob[conn].extra.QuestInfo.Arch.MortalSlot].Level - 299;

			else
				pMob[conn].extra.QuestInfo.Arch.MortalLevel = 99;


			BASE_GetHpMp(&pMob[conn].MOB, &pMob[conn].extra);

			pMob[conn].GetCurrentScore(conn);

			GetGuild(conn);

			//	pMob[conn].extra.Citizen = m->mobExtra.Citizen;

			BASE_GetBonusSkillPoint(&pMob[conn].MOB, &pMob[conn].extra);
			BASE_GetBonusScorePoint(&pMob[conn].MOB, &pMob[conn].extra);

			pMob[conn].Mode = MOB_USER;

			sm.mob = pMob[conn].MOB;
			sm.mob.SPX = sm.mob.SPX;
			sm.mob.SPY = sm.mob.SPY;
			sm.Type = _MSG_CNFCharacterLogin;

			if (NewbieEventServer == 1)
				sm.ID = ESCENE_FIELD + 1;
			else
				sm.ID = ESCENE_FIELD;

			sm.PosX = sm.mob.SPX;
			sm.PosY = sm.mob.SPY;
			sm.ClientID = conn;
			sm.Weather = CurrentWeather;

			memset(sm.Unk2, 0, sizeof(sm.Unk2));
			memset(sm.Unk, 0, sizeof(sm.Unk));
			memset(sm.unk, 0, sizeof(sm.unk));

			strncpy(&sm.Unk2[448], pUser[conn].AccountName, 12);

			pMob[conn].LastTime = CurrentTime;
			pMob[conn].LastX = pMob[conn].TargetX = sm.mob.SPX;
			pMob[conn].LastY = pMob[conn].TargetY = sm.mob.SPY;

			if (pMob[conn].MOB.Carry[KILL_MARK].sIndex == 0)
			{
				memset(&pMob[conn].MOB.Carry[KILL_MARK], 0, sizeof(STRUCT_ITEM));

				pMob[conn].MOB.Carry[KILL_MARK].sIndex = 547;
				pMob[conn].MOB.Carry[KILL_MARK].stEffect[0].cEffect = EF_CURKILL;
				pMob[conn].MOB.Carry[KILL_MARK].stEffect[1].cEffect = EF_LTOTKILL;
				pMob[conn].MOB.Carry[KILL_MARK].stEffect[2].cEffect = EF_HTOTKILL;
			}

			pUser[conn].Unk_2708 = 0;
			pUser[conn].LastChat[0] = 0;
			pUser[conn].Slot = m->Slot;
			pUser[conn].NumError = 0;
			pUser[conn].LastMove = 0;
			pUser[conn].LastAction = _MSG_Action;
			pUser[conn].LastActionTick = SKIPCHECKTICK;
			pUser[conn].LastAttack = 0;
			pUser[conn].LastAttackTick = SKIPCHECKTICK;
			pUser[conn].LastIllusionTick = SKIPCHECKTICK;
			pUser[conn].RankingTarget = 0;
			pUser[conn].RankingType = 0;
			pUser[conn].CastleStatus = 0;

			memset(pUser[conn].Unk9, -1, sizeof(pUser[conn].Unk9));
			memset(&pUser[conn].Trade, 0, sizeof(pUser[conn].Trade));

			int k;

			for (k = 0; k < MAX_TRADE; k++)
				pUser[conn].Trade.InvenPos[k] = -1;

			for (k = 0; k < MAX_AUTOTRADE; k++)
				pUser[conn].AutoTrade.CarryPos[k] = -1;

			pUser[conn].TradeMode = 0;
			pUser[conn].PKMode = 0;

			int tx = sm.PosX;
			int ty = sm.PosY;

			int CityID = (pMob[conn].MOB.Merchant & 0xC0) >> 6;

			tx = g_pGuildZone[CityID].CitySpawnX + rand() % 15;
			ty = g_pGuildZone[CityID].CitySpawnY + rand() % 15;

			int MobGuild = pMob[conn].MOB.Guild;
			int MobCLS = pMob[conn].MOB.Class;

			if (MobCLS < 0 || MobCLS > MAX_CLASS - 1)
			{
				//Log("err,login Undefined class", pUser[conn].AccountName, pUser[conn].IP);

				CloseUser(conn);

				break; // TODO: compile and check if it's break or return
			}

			int n;

			for (n = 0; n < MAX_GUILDZONE; n++)
			{
				if (MobGuild != 0 && MobGuild == g_pGuildZone[n].ChargeGuild)
				{
					tx = g_pGuildZone[n].GuildSpawnX;
					ty = g_pGuildZone[n].GuildSpawnY;

					break;
				}
			}

			if (Limitadordeconexoes(pUser[conn].MacAddress) >= 10)
			{
				CloseUser(conn);//força a saida da conn
				break;
			}

			if (pMob[conn].MOB.BaseScore.Level < FREEEXP && pMob[conn].extra.ClassMaster == MORTAL)
			{
				tx = 2112 + rand() % 5 - 2;
				ty = 2042 + rand() % 5 - 2;
			}

			int ret = GetEmptyMobGrid(conn, &tx, &ty);

			if (ret == 0)
			{
				//Log("Can't start can't get mobgrid", pUser[conn].AccountName, pUser[conn].IP);

				CloseUser(conn);

				break; // TODO: compile and check if it's break or return
			}

			sm.PosX = tx;
			sm.PosY = ty;

			pMob[conn].TargetX = tx;
			pMob[conn].LastX = tx;
			pMob[conn].TargetY = ty;
			pMob[conn].LastY = ty;

			pUser[conn].Mode = USER_PLAY;
			pUser[conn].Trade.OpponentID = 0;

			pMob[conn].GetCurrentScore(conn);

			pMob[conn].GuildDisable = 0;

			if (pMob[conn].MOB.Guild)
			{
				int Group = ServerGroup;
				int Server = pMob[conn].MOB.Guild / MAX_GUILD;
				int usGuild = pMob[conn].MOB.Guild & MAX_GUILD - 1;

				if (pMob[conn].MOB.Clan != GuildInfo[usGuild].Clan)
				{
					int mantle = pMob[conn].MOB.Equip[15].sIndex;

					if (GuildInfo[usGuild].Clan == 7)
					{
						if (m->mobExtra.ClassMaster == CELESTIAL || m->mobExtra.ClassMaster == SCELESTIAL || m->mobExtra.ClassMaster == CELESTIALCS || m->mobExtra.ClassMaster == HARDCORE || m->mobExtra.ClassMaster == HARDCOREA || m->mobExtra.ClassMaster == HARDCORECS || m->mobExtra.ClassMaster == SHARDCORE)
							pMob[conn].MOB.Equip[15].sIndex = 3197;

						else if (mantle >= 543 && mantle <= 544)
							pMob[conn].MOB.Equip[15].sIndex = 543;

						else if (mantle >= 545 && mantle <= 546)
							pMob[conn].MOB.Equip[15].sIndex = 545;

						else if (mantle == 548)
							pMob[conn].MOB.Equip[15].sIndex = 543;

						else if (mantle == 549)
							pMob[conn].MOB.Equip[15].sIndex = 545;

						else if (mantle >= 3191 && mantle <= 3193)
							pMob[conn].MOB.Equip[15].sIndex = 3191;

						else if (mantle >= 3194 && mantle <= 3196)
							pMob[conn].MOB.Equip[15].sIndex = 3194;

					}

					else if (GuildInfo[usGuild].Clan == 8)
					{
						if (m->mobExtra.ClassMaster == CELESTIAL || m->mobExtra.ClassMaster == SCELESTIAL || m->mobExtra.ClassMaster == CELESTIALCS || m->mobExtra.ClassMaster == HARDCORE || m->mobExtra.ClassMaster == HARDCOREA || m->mobExtra.ClassMaster == HARDCORECS || m->mobExtra.ClassMaster == SHARDCORE)
							pMob[conn].MOB.Equip[15].sIndex = 3198;

						else if (mantle >= 543 && mantle <= 544)
							pMob[conn].MOB.Equip[15].sIndex = 544;

						else if (mantle >= 545 && mantle <= 546)
							pMob[conn].MOB.Equip[15].sIndex = 546;

						else if (mantle == 548)
							pMob[conn].MOB.Equip[15].sIndex = 544;

						else if (mantle == 549)
							pMob[conn].MOB.Equip[15].sIndex = 546;

						else if (mantle >= 3191 && mantle <= 3193)
							pMob[conn].MOB.Equip[15].sIndex = 3192;

						else if (mantle >= 3194 && mantle <= 3196)
							pMob[conn].MOB.Equip[15].sIndex = 3195;
					}

					memmove_s(&sm.mob.Equip[15], sizeof(STRUCT_ITEM), &pMob[conn].MOB.Equip[15], sizeof(STRUCT_ITEM));
				}
			}

			char tt[512];

			pUser[conn].cProgress = 0;
			pUser[conn].ReqHp = pMob[conn].MOB.CurrentScore.Hp;
			pUser[conn].ReqMp = pMob[conn].MOB.CurrentScore.Mp;
			pUser[conn].Unk_2688 = 0;

			pUser[conn].cSock.SendOneMessage((char*)&sm, sizeof(MSG_CNFClientCharacterLogin));

			///////////////////////////////////////////////
			// Packet that will be sent to other players //
			///////////////////////////////////////////////

			MSG_CreateMob sm2;

			GetCreateMob(conn, &sm2);

			sm2.CreateType = 2;

			pMobGrid[sm.PosY][sm.PosX] = conn;

			GridMulticast(sm.PosX, sm.PosY, (MSG_STANDARD*)&sm2, 0);

			for (int i = 0; i < pMob[conn].MaxCarry; i++)
			{
				if ((pMob[conn].MOB.Carry[i].sIndex < 0) || (pMob[conn].MOB.Carry[i].sIndex > MAX_ITEMLIST))
				{
					
					snprintf(temp, sizeof(temp), " $s Slots Desbugados Inventario", pMob[conn].MOB.MobName);
					SystemLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, temp);
					BASE_ClearItem(&pMob[conn].MOB.Carry[i]);
					SendItem(conn, ITEM_PLACE_CARRY, i, &pMob[conn].MOB.Carry[i]);
					SendCarry(conn);
				}
			}
			for (int i = 0; i < MAX_CARGO; i++)
			{
				if ((pUser[conn].Cargo[i].sIndex < 0) || (pUser[conn].Cargo[i].sIndex > MAX_ITEMLIST))
				{
					
					snprintf(temp, sizeof(temp), " $s Slots Desbugados Bau", pMob[conn].MOB.MobName);
					SystemLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, temp);
					BASE_ClearItem(&pUser[conn].Cargo[i]);
					SendItem(conn, ITEM_PLACE_CARRY, i, &pUser[conn].Cargo[i]);
				}
			}

			SendPKInfo(conn, conn);
			SendGridMob(conn);

			if (pMob[n].MOB.CurrentScore.Level >= 999)
				pUser[n].Admin = 1;

			MountProcess(conn, 0);
			SendWarInfo(conn, g_pGuildZone[4].Clan);

			if (CastleState != 0)
				SendClientSignalParm(conn, ESCENE_FIELD, _MSG_SendCastleState, CastleState);

			ClearCrown(conn);

			int curlvl = pMob[conn].MOB.BaseScore.Level;

			int max_level = 0;

			if (pMob[conn].extra.ClassMaster == MORTAL || pMob[conn].extra.ClassMaster == ARCH)
				max_level = MAX_LEVEL;

			else if (pMob[conn].extra.ClassMaster == CELESTIAL || pMob[conn].extra.ClassMaster == SCELESTIAL || pMob[conn].extra.ClassMaster == CELESTIALCS ||
				pMob[conn].extra.ClassMaster == HARDCORE || pMob[conn].extra.ClassMaster == HARDCOREA || pMob[conn].extra.ClassMaster == HARDCORECS || pMob[conn].extra.ClassMaster == SHARDCORE)
				max_level = MAX_CLEVEL;


			if (curlvl < max_level - 1)
			{
				long long exp = pMob[conn].MOB.Exp;
				long long curexp = max_level == MAX_LEVEL ? g_pNextLevel[curlvl] : g_pNextLevel_2[curlvl];
				long long nextexp = max_level == MAX_LEVEL ? g_pNextLevel[curlvl + 1] : g_pNextLevel_2[curlvl + 1];
				long long deltaexp = (nextexp - curexp) / 4;
				long long Segment1 = curexp + deltaexp;
				long long Segment2 = curexp + (deltaexp * 2);
				long long Segment3 = curexp + (deltaexp * 3);
				long long Segment4 = nextexp;

				if (exp > Segment3)
					pMob[conn].Segment = 3;
				else if (exp > Segment2)
					pMob[conn].Segment = 2;
				else if (exp > Segment1)
					pMob[conn].Segment = 1;
				else
					pMob[conn].Segment = 0;

				pUser[conn].Unk_2736 = 0;

				if (pMob[conn].MOB.BaseScore.Level >= FREEEXP)
				{
					if (CHARSELBILL == 0)
						SendBilling(conn, pUser[conn].AccountName, 1, 1);
				}

			}

			if (pMob[conn].extra.Citizen != 0)
			{
				snprintf(tt, sizeof(tt), g_pMessageStringTable[_DN_TOWNSPEOPLE], pMob[conn].CitizenDrop);
				SendClientMessage(conn, tt);
			}

			/*if (KefraLive != 0)
			{
				BASE_GetGuildName(ServerGroup, KefraLive, KefraKiller);
				SendMsgExp(conn, strFmt(g_pMessageStringTable[_SN_End_Khepra], KefraKiller), NewWhite, FALSE);

				if (DOUBLEMODE == 1) {
					SendMsgExp(conn, strFmt("Double EXP [ATIVADO]"), Speak, FALSE);
				}
				if (DOUBLEMODE == 0) {
					SendMsgExp(conn, strFmt("Double EXP [DESATIVADO]"), Orange, FALSE);
				}
			}

			if (KefraLive == 0) {
				SendMsgExp(conn, "Kefra está Vivo!", Orange, FALSE);
			}*/

			/*if (RvRBonus == pMob[conn].MOB.Clan && RvRBonus)
			{
				
				if (pMob[conn].MOB.Clan == 8)
					snprintf(temp, sizeof(temp), g_pMessageStringTable[_SN_KINGDOMWAR_DROP_], g_pMessageStringTable[_NN_KINGDOM_RED]);

				else if (pMob[conn].MOB.Clan == 7)
					snprintf(temp, sizeof(temp), g_pMessageStringTable[_SN_KINGDOMWAR_DROP_], g_pMessageStringTable[_NN_KINGDOM_BLUE]);

				SendClientMessage(conn, temp);
			}

			if (pMob[conn].MOB.Guild != 0)
			{
				if (AvisarGuild[pMob[conn].MOB.Guild].Aviso[0] != '\0' && AvisarGuild[pMob[conn].MOB.Guild].Aviso[0] != ' ')
				{
					SendClientMessage(conn, strFmt("[Mensagem da Guild]> %s", AvisarGuild[pMob[conn].MOB.Guild].Aviso));
				}
			}*/


			// CORRIGIR BO RETIRAR TODOS OS ITENS DENTRO DO SV AQUI

			//bool Reboot = false;
			//for (int i = 0; i < 16; i++) {
			//	if (pMob[conn].MOB.Equip[i].sIndex == 632 || pMob[conn].MOB.Equip[i].sIndex == 671 || pMob[conn].MOB.Equip[i].sIndex == 670) // ABS - ESPECTRAL - CONCENTRAÇÃO
			//	{

			//		memset(&pMob[conn].MOB.Equip[i], 0x0, sizeof(STRUCT_ITEM));
			//		SendCarry(conn);
			//		SendClientMessage(conn, "Seu Item foi removido!");
			//		Reboot = true;
			//	}
			//}

			//for (int i = 0; i < 64; i++) {
			//	if (pMob[conn].MOB.Carry[i].sIndex == 632 || pMob[conn].MOB.Carry[i].sIndex == 671 || pMob[conn].MOB.Carry[i].sIndex == 670) // ABS - ESPECTRAL - CONCENTRAÇÃO
			//	{

			//		memset(&pMob[conn].MOB.Carry[i], 0x0, sizeof(STRUCT_ITEM));
			//		SendCarry(conn);
			//		SendClientMessage(conn, "Seu Item foi removido!");
			//		Reboot = true;
			//	}
			//}
			//for (int i = 0; i < 128; i++) {
			//	if (pUser[conn].Cargo[i].sIndex == 632 || pUser[conn].Cargo[i].sIndex == 671 || pUser[conn].Cargo[i].sIndex == 670) // ABS - ESPECTRAL - CONCENTRAÇÃO
			//	{

			//		memset(&pUser[conn].Cargo[i], 0x0, sizeof(STRUCT_ITEM));
			//		SendCarry(conn);
			//		SendClientMessage(conn, "Seu Item foi removido!");
			//		Reboot = true;
			//	}
			//}
			//if (Reboot == true) {
			//	SaveUser(conn, 0);
			//	CharLogOut(conn);
			//}

			// CHAR LOGANDO NO SERVIDOR
						
			//MailItem(conn);
			SendScore(conn);
			SendEtc(conn);
			UpdateDonate(conn);
			doRanking(conn);

			//Retira divinas duplas
			int div = 0;
			for (int i = 0; i < MAX_AFFECT; i++)
			{
				if (pMob[conn].Affect[i].Type == 34)
				{
					if (div >= 1) {
						pMob[conn].Affect[i].Type = 0;
						pMob[conn].Affect[i].Level = 0;
						pMob[conn].Affect[i].Time = 0;
						pMob[conn].Affect[i].Value = 0;

						pMob[conn].GetCurrentScore(conn);
						SendScore(conn);
						CharLogOut(conn);
					}
					div++;					
				}
			}			


		} break;
#pragma endregion
#pragma region _MSG_DBCharacterLoginFail
		case _MSG_DBCharacterLoginFail:
		{
			MSG_STANDARD* m = (MSG_STANDARD*)Msg;

			m->ID = ESCENE_FIELD;

			SendClientSignal(conn, 0, _MSG_CharacterLoginFail);

			pUser[conn].Mode = USER_CHARWAIT;
			SystemLog("-system", "-", 0, "CharLoginFail Crack Log");

		} break;
#pragma endregion
#pragma region _MSG_DBMessageBoxOk
		case _MSG_DBMessageBoxOk:
		{
			MSG_MessageBoxOk* m = (MSG_MessageBoxOk*)Msg;

			m->Type = _MSG_MessageBoxOk;
			m->ID = 0;

			pUser[conn].cSock.SendOneMessage((char*)m, sizeof(MSG_MessageBoxOk));

		} break;
#pragma endregion
#pragma region _MSG_DBAlreadyPlaying
		case _MSG_DBAlreadyPlaying:
		{
			MSG_STANDARD* m = (MSG_STANDARD*)Msg;

			SendClientSignal(m->ID, ESCENE_FIELD + 2, _MSG_AlreadyPlaying);

			pUser[m->ID].cSock.SendMessageA();

			CloseUser(conn);

		} break;
#pragma endregion
#pragma region _MSG_DBStillPlaying
		case _MSG_DBStillPlaying:
		{
			MSG_STANDARD* m = (MSG_STANDARD*)Msg;

			SendClientSignal(m->ID, ESCENE_FIELD + 2, _MSG_StillPlaying);

			pUser[m->ID].cSock.SendMessageA();

			CloseUser(conn);

		} break;
#pragma endregion
#pragma region _MSG_DBSavingQuit
		case _MSG_DBSavingQuit:
		{
			MSG_DBSavingQuit* m = (MSG_DBSavingQuit*)Msg;

			if (m->ID <= 0 || m->ID >= MAX_USER)
			{
				SystemLog("-system", "-", 0, "err,DBsavingquit - id range");

				break;
			}

			if (pUser[m->ID].Mode != USER_PLAY && pUser[m->ID].Mode != USER_SAVING4QUIT)
			{
				MSG_STANDARD sm;

				sm.Type = _MSG_DBNoNeedSave;
				sm.ID = conn;

				DBServerSocket.SendOneMessage((char*)&sm, sizeof(MSG_STANDARD));
			}

			if (pUser[m->ID].Mode == USER_PLAY || pUser[m->ID].Mode == USER_CHARWAIT)
			{
				if (m->Mode == 0)
					SendClientMessage(m->ID, g_pMessageStringTable[_NN_Your_Account_From_Others]);
				else if (m->Mode == 1)
					SendClientMessage(m->ID, g_pMessageStringTable[_NN_Disabled_Account]);

				pUser[conn].cSock.SendMessage();
			}

			CloseUser(m->ID);
		} break;
#pragma endregion
#pragma region _MSG_DBCNFAccountLogOut
		case _MSG_DBCNFAccountLogOut:
		{
			MSG_STANDARD* m = (MSG_STANDARD*)Msg;
			
			snprintf(temp, sizeof(temp), "etc,charlogout conn:%d name:%s", conn, pMob[conn].MOB.MobName);
			SystemLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, temp);

			pMob[conn].Mode = MOB_EMPTY;
			pUser[conn].Mode = USER_ACCEPT;
			pUser[conn].Ingame.MobDonateStore = FALSE;
			pUser[conn].Ingame.CheckPista = FALSE;
			pUser[conn].Ingame.CheckPesa = FALSE;
			pUser[conn].Ingame.CheckAgua = FALSE;
			pMob[conn].JoiaOn = FALSE;
			CloseUser(conn);
		} break;
#pragma endregion

#pragma region _MSG_DBCNFArchCharacterSucess
		case _MSG_DBCNFArchCharacterSucess:
		{
			MSG_STANDARDPARM* m = (MSG_STANDARDPARM*)Msg;

			SendClientMessage(conn, g_pMessageStringTable[_NN_My_King_Bless1]);

			memset(&pMob[conn].MOB.Equip[10], 0, sizeof(STRUCT_ITEM));
			SendItem(conn, ITEM_PLACE_EQUIP, 10, &pMob[conn].MOB.Equip[10]);

			memset(&pMob[conn].MOB.Equip[11], 0, sizeof(STRUCT_ITEM));
			SendItem(conn, ITEM_PLACE_EQUIP, 11, &pMob[conn].MOB.Equip[11]);

			SaveUser(conn, 0);

			CharLogOut(conn);

			SendClientSignalParm(conn, ESCENE_FIELD, _MSG_SendArchEffect, m->Parm);
			
			snprintf(temp, sizeof(temp), "etc,arch create name:%s slot:%d", pMob[conn].MOB.MobName, m->Parm);
			SystemLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, temp);
		} break;
#pragma endregion
#pragma region _MSG_DBCNFArchCharacterFail
		case _MSG_DBCNFArchCharacterFail:
		{
			pMob[conn].Mode = MOB_USER;
			SendClientMessage(conn, g_pMessageStringTable[_NN_NoEmptySlot]);
			break;
		} break;
#pragma endregion

#pragma region _MSG_DBSendDonate
		case _MSG_DBSendDonate:
		{
			MSG_DBSendDonate* m = (MSG_DBSendDonate*)Msg;

			if (pUser[conn].Mode < USER_CHARWAIT)
			{

				SystemLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, "_fail_play_ charwiat mode");

				break;
			}

			if (strcmp(pUser[conn].AccountName, m->Account) != 0)
			{
				SystemLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, "_fail_name_");

				break;
			}
			pUser[conn].Donate += m->Donate;
			//pUser[conn].Honra += m->Honra; 

			SendClientMessage(conn, g_pMessageStringTable[_NN_Cash_ChargeOk]);
			SendEtc(conn);
			m->Result = 0;

			DBServerSocket.SendOneMessage((char*)m, m->Size);

			SystemLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, strFmt("recv, %d donate", m->Donate));

		} break;
#pragma endregion

#pragma region _MSG_CNFDBCapsuleInfo
		case _MSG_CNFDBCapsuleInfo:
		{
			pUser[conn].cSock.SendOneMessage((char*)Msg, sizeof(MSG_CNFDBCapsuleInfo));
		} break;
#pragma endregion
#pragma region _MSG_DBCNFCapsuleCharacterFail
		case _MSG_DBCNFCapsuleCharacterFail:
		{
			SendCarry(conn);
			SendClientMessage(conn, g_pMessageStringTable[_NN_NoEmptySlot]);
		} break;
#pragma endregion
#pragma region _MSG_DBCNFCapsuleCharacterFail2
		case _MSG_DBCNFCapsuleCharacterFail2:
		{
			SendCarry(conn);
			SendClientMessage(conn, g_pMessageStringTable[_NN_CANT_USE_ID]);
		} break;
#pragma endregion
#pragma region _MSG_DBCNFCapsuleSucess
		case _MSG_DBCNFCapsuleSucess:
		{
			memset(&pMob[conn].MOB, 0, sizeof(STRUCT_MOB));
			memset(&pMob[conn].extra, 0, sizeof(STRUCT_MOBEXTRA));
			SaveUser(conn, 1);
		} break;
#pragma endregion
#pragma region _MSG_GrindRankingData
		case _MSG_GrindRankingData:
		{
			/*
			Some change have happened in the ranking, notify the client.
			*/
			MSG_SendExpRanking* m = (MSG_SendExpRanking*)Msg;

			/* In the char sel Mode (0xC) the tmsrv still don't have the player data, so ignore the playerRank.Name check */
			if (pUser[conn].Mode == USER_PLAY && m->PlayerRank.Name[0] != '\0' && !strcmp(pMob[conn].MOB.MobName, m->PlayerRank.Name))
				pUser[conn].cSock.SendOneMessage((char*)m, sizeof(MSG_SendExpRanking));

		} break;
#pragma endregion
#pragma region _MSG_DBClientMessage
		case _MSG_DBClientMessage:
		{
			MSG_DBClientMessage* m = (MSG_DBClientMessage*)Msg;

			SendClientMessage(conn, m->String);
		} break;
#pragma endregion
#pragma region _MSG_DBServerSend1
		case _MSG_DBServerSend1:
		{
			MSG_STANDARDPARM* m = (MSG_STANDARDPARM*)Msg;

			m->ID = ESCENE_FIELD;

			if (!pUser[conn].cSock.SendOneMessage((char*)m, sizeof(MSG_STANDARDPARM)))
				CloseUser(conn);

		} break;
#pragma endregion
#pragma region _MSG_DBCNFServerChange
		case _MSG_DBCNFServerChange:
		{
			MSG_DBCNFServerChange* m = (MSG_DBCNFServerChange*)Msg;

			pUser[conn].cSock.SendOneMessage((char*)m, sizeof(MSG_DBCNFServerChange));
			CloseUser(conn);
		} break;
#pragma endregion

		}
	}
#pragma endregion
}