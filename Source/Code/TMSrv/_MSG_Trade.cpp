
#include "ProcessClientMessage.h"

void Exec_MSG_Trade(int conn, char* pMsg)
{
	MSG_Trade* m = (MSG_Trade*)pMsg;

	int Size = m->Size;

	if (m->TradeMoney < 0 || m->TradeMoney > 2000000000)
		return;

	if (m->MyCheck < 0)
		return;

	if (Size > sizeof(MSG_Trade)) //CONTROLE DE SIZE
	{
		SendClientMessage(conn, "Impossível executar ação51, tente mais tarde. ");
		return;
	}

	if (pUser[conn].Mode != USER_PLAY)
		return;

	if (pMob[conn].MOB.CurrentScore.Hp == 0 || pUser[conn].Mode != USER_PLAY)
	{
		SendHpMode(conn);
		//AddCrackError(conn, 5, 18);
		RemoveTrade(conn);
		return;
	}

	int OpponentID = m->OpponentID;

	if (OpponentID <= 0 || OpponentID >= MAX_USER)
	{
		//Log("err,msg_trade - target out of bound.", pUser[conn].AccountName, pUser[conn].IP);
		SendClientMessage(conn, g_pMessageStringTable[_NN_Wrong_Trade_Packet1]);
		RemoveTrade(conn);
		return;
	}

	if (pUser[OpponentID].Mode != USER_PLAY)
	{
		RemoveTrade(OpponentID);
		RemoveTrade(conn);
		return;
	}

	if (m->TradeMoney < 0 || m->TradeMoney > pMob[conn].MOB.Coin)
	{
		RemoveTrade(conn);
		RemoveTrade(OpponentID);
		return;
	}

	for (int i = 0; i < MAX_TRADE; i++)
	{
		if (m->Item[i].sIndex)
		{
			if (m->InvenPos[i] < 0 || m->InvenPos[i] >= MAX_CARRY - 4)
				return;

			if (memcmp(&pMob[conn].MOB.Carry[m->InvenPos[i]], &m->Item[i], sizeof(STRUCT_ITEM)))
			{
				//Log("err,msg_trade - item remove or changed.", pUser[conn].AccountName, pUser[conn].IP);
				RemoveTrade(conn);
				RemoveTrade(OpponentID);
				return;
			}
		}

		if (pUser[OpponentID].Trade.Item[i].sIndex)
		{
			if (pUser[OpponentID].Trade.InvenPos[i] < 0 || pUser[OpponentID].Trade.InvenPos[i] >= MAX_CARRY - 4)
				return;

			if (memcmp(&pMob[OpponentID].MOB.Carry[pUser[OpponentID].Trade.InvenPos[i]], &pUser[OpponentID].Trade.Item[i], sizeof(STRUCT_ITEM)))
			{
				//Log("err,msg_trade - item remove or changed.", pUser[conn].AccountName, pUser[conn].IP);
				RemoveTrade(conn);
				RemoveTrade(OpponentID);
				return;
			}
		}
	}

	int lastOpponent = pUser[conn].Trade.OpponentID;

	if (lastOpponent == OpponentID)
	{
		for (int i = 0; i < MAX_TRADE; i++)
		{
			int Check = 0;

			if (pUser[conn].Trade.Item[i].sIndex)
				Check = memcmp(&pUser[conn].Trade.Item[i], &m->Item[i], sizeof(STRUCT_ITEM));

			if (pUser[conn].Trade.TradeMoney && m->TradeMoney != pUser[conn].Trade.TradeMoney)
				Check = 1;

			if (Check)
			{
				//Log("err,msg_trade - item remove or changed.", pUser[conn].AccountName, pUser[conn].IP);
				RemoveTrade(conn);
				RemoveTrade(OpponentID);
				return;
			}
		}
	}
	else
	{
		if (lastOpponent)
		{
			SendClientMessage(conn, g_pMessageStringTable[_NN_Already_Trading]);
			RemoveTrade(conn);
			return;
		}
	}

	if (pUser[conn].PKMode || pUser[OpponentID].PKMode)
	{
		SendClientMessage(conn, g_pMessageStringTable[_NN_Cant_trade_pkmode]);
		SendClientMessage(OpponentID, g_pMessageStringTable[_NN_Cant_trade_pkmode]);

		RemoveTrade(conn);
		RemoveTrade(OpponentID);
		return;
	}

	/*if (pUser[conn].Whisper || pUser[OpponentID].Whisper)
	{
		SendClientMessage(conn, g_pMessageStringTable[_NN_Deny_Whisper]);
		SendClientMessage(OpponentID, g_pMessageStringTable[_NN_Deny_Whisper]);

		RemoveTrade(conn);
		RemoveTrade(OpponentID);
		return;
	}
	*/
	int MyGuild = pMob[conn].MOB.Guild;
	int OpponentGuild = pMob[OpponentID].MOB.Guild;
	int MyGuildLevel = pMob[conn].MOB.GuildLevel;
	int OpponentGuildLevel = pMob[OpponentID].MOB.GuildLevel;

	for (int i = 0; i < MAX_TRADE; i++)
	{



		if (m->Item[i].sIndex == 747 || m->Item[i].sIndex == 3993 || m->Item[i].sIndex == 3994)
		{
			SendClientMessage(conn, g_pMessageStringTable[_NN_Only_With_Guild_Master]);
			SendClientMessage(OpponentID, g_pMessageStringTable[_NN_Only_With_Guild_Master]);

			RemoveTrade(conn);

			if (pUser[OpponentID].Trade.OpponentID == conn)
				RemoveTrade(OpponentID);

			return;
		}

		if (m->Item[i].sIndex == 508 || m->Item[i].sIndex == 522 || m->Item[i].sIndex >= 526 && m->Item[i].sIndex <= 537 || m->Item[i].sIndex == 446)
		{
			int getGuild = GetGuild(&m->Item[i]);
			if (getGuild != MyGuild || !MyGuildLevel)
			{
				if (getGuild != OpponentGuild || !OpponentGuildLevel)
				{
					SendClientMessage(conn, g_pMessageStringTable[_NN_Only_With_Guild_Master]);
					SendClientMessage(OpponentID, g_pMessageStringTable[_NN_Only_With_Guild_Master]);
					RemoveTrade(conn);

					if (pUser[OpponentID].Trade.OpponentID == conn)
						RemoveTrade(OpponentID);

					return;
				}
			}
		}

		if (m->Item[i].sIndex && BASE_GetItemAbility(&m->Item[i], EF_NOTRADE) != 0)
		{
			SendClientMessage(conn, g_pMessageStringTable[_NN_Cant_MoveItem]);
			SendClientMessage(OpponentID, g_pMessageStringTable[_NN_Cant_MoveItem]);
			RemoveTrade(conn);

			if (pUser[OpponentID].Trade.OpponentID == conn)
				RemoveTrade(OpponentID);

			return;
		}
	}

	if (pUser[OpponentID].Trade.OpponentID)
	{
		if (pUser[OpponentID].Trade.OpponentID == conn)
		{
			for (int i = 0; i < MAX_TRADE; i++)
			{
				int iPos = m->InvenPos[i];

				if (iPos == -1)
					memset(&m->Item[i], 0, sizeof(STRUCT_ITEM));

				else
				{
					if (iPos < -1 || iPos >= MAX_CARRY - 4)
					{
						SendClientMessage(conn, g_pMessageStringTable[_NN_Wrong_Trade_Packet1]);
						RemoveTrade(conn);
						break;
					}
					for (int j = 0; j < MAX_TRADE; j++)
					{
						if (j != i && iPos == m->InvenPos[j])
						{
							SendClientMessage(conn, g_pMessageStringTable[_NN_Wrong_Trade_Packet1]);
							RemoveTrade(conn);
							return;
						}
					}

					memmove_s(&m->Item[i], sizeof(STRUCT_ITEM), &pMob[conn].MOB.Carry[iPos], sizeof(STRUCT_ITEM));
				}
			}

			if (m->MyCheck == 1)
			{
				pUser[conn].Trade.MyCheck = 1;
				pUser[conn].Trade.KeyWord = m->KeyWord;
				pUser[conn].Trade.CheckSum = m->CheckSum;
				pUser[conn].Trade.ClientTick = m->ClientTick;

				if (memcmp(&pUser[conn].Trade, m, sizeof(MSG_Trade)))
				{
					RemoveTrade(conn);
					RemoveTrade(OpponentID);
					//Log("err,msg_trade - Click check button but diffrent data", pUser[conn].AccountName, pUser[conn].IP);
					return;
				}

				if (pUser[OpponentID].Trade.MyCheck == 0)
				{
					SendClientSignal(conn, conn, _MSG_CNFCheck);

					m->ID = OpponentID;
					m->OpponentID = conn;

					if (!pUser[OpponentID].cSock.AddMessage((char*)m, sizeof(MSG_Trade)))
						CloseUser(conn);

					return;
				}

				if (pUser[conn].Trade.TradeMoney < 0 || pUser[conn].Trade.TradeMoney  > 2000000000)
				{
					RemoveTrade(conn);
					RemoveTrade(OpponentID);

					return;
				}

				if (pUser[OpponentID].Trade.TradeMoney < 0 || pUser[OpponentID].Trade.TradeMoney  > 2000000000)
				{
					RemoveTrade(conn);
					RemoveTrade(OpponentID);

					return;
				}

				unsigned int fGold = pUser[OpponentID].Trade.TradeMoney + pMob[conn].MOB.Coin - pUser[conn].Trade.TradeMoney;

				if (fGold > 2000000000 || fGold < 0)
				{
					SendClientMessage(conn, g_pMessageStringTable[_NN_Cant_get_more_than_2G]);
					RemoveTrade(conn);
					RemoveTrade(OpponentID);
					return;
				}

				unsigned int opfGold = pUser[conn].Trade.TradeMoney + pMob[OpponentID].MOB.Coin - pUser[OpponentID].Trade.TradeMoney;

				if (opfGold > 2000000000 || opfGold < 0)
				{
					SendClientMessage(conn, g_pMessageStringTable[_NN_Cant_get_more_than_2G]);
					RemoveTrade(conn);
					RemoveTrade(OpponentID);
					return;
				}

				if (pUser[conn].Trade.TradeMoney > pMob[conn].MOB.Coin)
				{
					SendClientMessage(conn, g_pMessageStringTable[_NN_Havent_Money_So_Much]);
					SendClientMessage(OpponentID, g_pMessageStringTable[_NN_Opponent_Havent_Money]);
					return;
				}

				if (pUser[OpponentID].Trade.TradeMoney > pMob[OpponentID].MOB.Coin)
				{
					SendClientMessage(OpponentID, g_pMessageStringTable[_NN_Havent_Money_So_Much]);
					SendClientMessage(conn, g_pMessageStringTable[_NN_Opponent_Havent_Money]);
					return;
				}

				STRUCT_ITEM mydest[MAX_CARRY];
				STRUCT_ITEM oppdest[MAX_CARRY];

				int mytrade = BASE_CanTrade(mydest, pMob[conn].MOB.Carry, (unsigned char*)&pUser[conn].Trade.InvenPos, pUser[OpponentID].Trade.Item, pMob[conn].MaxCarry);
				int opptrade = BASE_CanTrade(oppdest, pMob[OpponentID].MOB.Carry, (unsigned char*)&pUser[OpponentID].Trade.InvenPos, pUser[conn].Trade.Item, pMob[OpponentID].MaxCarry);

				if (mytrade == 0 && opptrade == 0)
				{
					SendClientMessage(conn, g_pMessageStringTable[_NN_Each_Of_You_Havent_Space]);
					SendClientMessage(OpponentID, g_pMessageStringTable[_NN_Each_Of_You_Havent_Space]);
					return;
				}

				if (mytrade == 0)
				{
					SendMsgExp(conn, g_pMessageStringTable[_NN_You_Have_No_Space_To_Trade], TNColor::Red, false);
					SendMsgExp(OpponentID, g_pMessageStringTable[_NN_Opponent_Have_No_Space_To], TNColor::Red, false);
					return;
				}

				if (opptrade == 0)
				{
					SendMsgExp(conn, g_pMessageStringTable[_NN_You_Have_No_Space_To_Trade], TNColor::Red, false);
					SendMsgExp(OpponentID, g_pMessageStringTable[_NN_Opponent_Have_No_Space_To], TNColor::Red, false);
					return;
				}

				memmove_s(pMob[conn].MOB.Carry, sizeof(mydest), mydest, sizeof(mydest));
				memmove_s(pMob[OpponentID].MOB.Carry, sizeof(oppdest), oppdest, sizeof(oppdest));

				pMob[conn].MOB.Coin = fGold;
				pMob[OpponentID].MOB.Coin = opfGold;

				SendCarry(conn);
				SendCarry(OpponentID);

				int MyTradeMoney = pUser[conn].Trade.TradeMoney;
				int OppTradeMoney = pUser[OpponentID].Trade.TradeMoney;

				int MyLog = 0;
				int OppLog = 0;
				
				snprintf(temp, sizeof(temp), "Troca entre conta[%s] jogador[%s] e conta[%s] jogador[%s] foi iniciada.", pUser[OpponentID].AccountName, pMob[OpponentID].MOB.MobName, pUser[conn].AccountName, pMob[conn].MOB.MobName);
				Tradelogs(pUser[OpponentID].AccountName, pUser[OpponentID].MacAddress, pUser[OpponentID].IP, temp);

				snprintf(temp, sizeof(temp), "Troca ,conta[%s] jogador[%s] colocou na troca coin[%d] ", pUser[OpponentID].AccountName, pMob[OpponentID].MOB.MobName, OppTradeMoney);
				Tradelogs(pUser[OpponentID].AccountName, pUser[OpponentID].MacAddress, pUser[OpponentID].IP, temp);

				snprintf(temp, sizeof(temp), "Troca ,conta[%s] Jogador[%s] colocou na troca coin[%d] ", pUser[conn].AccountName, pMob[conn].MOB.MobName, MyTradeMoney);
				Tradelogs(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, temp);

				for (int i = 0; i < MAX_TRADE; i++)
				{
					if (pUser[conn].Trade.Item[i].sIndex == 0)
						continue;

					

					BASE_GetItemCode(&pUser[conn].Trade.Item[i], temp);

					Tradelogs(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, temp);
				}

				for (int i = 0; i < MAX_TRADE; i++)
				{
					if (pUser[OpponentID].Trade.Item[i].sIndex == 0)
						continue;

					

					BASE_GetItemCode(&pUser[OpponentID].Trade.Item[i], temp);
					Tradelogs(pUser[OpponentID].AccountName, pUser[OpponentID].MacAddress, pUser[OpponentID].IP, temp);
				}

				snprintf(temp, sizeof(temp), "Troca entre Login[%s] jogador[%s] recebeu coin[%d] e Login[%s] jogador[%s] recebeu coin[%d], foi finalizada.", pUser[OpponentID].AccountName, pMob[OpponentID].MOB.MobName, MyTradeMoney, pUser[conn].AccountName, pMob[conn].MOB.MobName, OppTradeMoney);
				Tradelogs(pUser[OpponentID].AccountName, pUser[OpponentID].MacAddress, pUser[OpponentID].IP, temp);

				SaveUser(conn, 1);
				SaveUser(OpponentID, 1);

				RemoveTrade(conn);
				RemoveTrade(OpponentID);
				return;
			}

			else
			{
				memmove_s(&pUser[conn].Trade, sizeof(MSG_Trade), m, sizeof(MSG_Trade));

				pUser[conn].Trade.MyCheck = 0;
				pUser[OpponentID].Trade.MyCheck = 0;

				m->ID = OpponentID;
				m->OpponentID = conn;

				if (!pUser[OpponentID].cSock.AddMessage((char*)m, sizeof(MSG_Trade)))
					CloseUser(conn);
				return;
			}

		}
		else
		{
			SendClientMessage(conn, g_pMessageStringTable[_NN_Already_Trading]);
			RemoveTrade(conn);
			return;
		}
	}
	else
	{
		memmove_s(&pUser[conn].Trade, sizeof(MSG_Trade), m, sizeof(MSG_Trade));

		pUser[conn].Trade.MyCheck = 0;
		pUser[conn].Trade.TradeMoney = 0;

		m->ID = OpponentID;

		m->OpponentID = conn;

		if (!pUser[OpponentID].cSock.AddMessage((char*)m, sizeof(MSG_Trade)))
			CloseUser(conn);

		pUser[OpponentID].Trade.MyCheck = 0;
		pUser[OpponentID].Trade.TradeMoney = 0;
	}
}