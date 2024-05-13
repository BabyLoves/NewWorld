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
#include "ProcessClientMessage.h"

void Exec_MSG_GetItem(int conn, char *pMsg)
{
	MSG_GetItem* m = (MSG_GetItem*)pMsg;

	if (m->DestPos < 0 || m->DestPos > 60)
		return;

	if (m->DestType < 0 || m->DestType > 2)
		return;

	if (m->GridX < 0 || m->GridX > CARGOGRIDX)
		return;

	if (m->GridY < 0 || m->GridY > CARGOGRIDY)
		return;

	if (m->ItemID < 0 || m->ItemID > MAX_ITEMLIST)
		return;

	int Size = m->Size;

	if (Size > sizeof(MSG_GetItem)) //CONTROLE DE SIZE
	{
		SendClientMessage(conn, "Impossível executar ação28, tente mais tarde. ");
		return;
	}

	if (pMob[conn].MOB.CurrentScore.Hp <= 0 || pUser[conn].Mode != USER_PLAY)
	{
		AddCrackError(conn, 1, 13);
		SendHpMode(conn);
		return;
	}

	if (pUser[conn].Trade.OpponentID)
	{
		RemoveTrade(pUser[conn].Trade.OpponentID);
		RemoveTrade(conn);
		return;
	}

	if (pUser[conn].TradeMode)
	{
		SendClientMessage(conn, g_pMessageStringTable[_NN_CantWhenAutoTrade]);
		return;
	}

	if (m->DestType != ITEM_PLACE_CARRY)
	{
		//Log("DEBUG:GetItem with wrong desttype", pUser[conn].AccountName, pUser[conn].IP);
		return;
	}

	int itemID = m->ItemID - 10000;

	if (itemID <= 0 || itemID >= MAX_ITEM)
		return;

	if (itemID <= 0 || itemID >= MAX_ITEM || pItem[itemID].Mode == 0)
	{
		if (pItem[itemID].Mode)
		{
			sprintf_s(temp, "GetItemFail idx:%d mode:%d", itemID, pItem[itemID].Mode);
			SystemLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, temp);
		}
		MSG_DecayItem sm_deci;
		memset(&sm_deci, 0, sizeof(MSG_DecayItem));

		sm_deci.Type = _MSG_DecayItem;
		sm_deci.Size = sizeof(MSG_DecayItem);
		sm_deci.ID = ESCENE_FIELD;
		sm_deci.ItemID = m->ItemID;
		sm_deci.unk = 0;

		int Size = sm_deci.Size;

		if (Size > sizeof(MSG_DecayItem))
		{
			sm_deci.Size = 0;
			return;
		}
		if (!pUser[conn].cSock.AddMessage((char*)&sm_deci, sizeof(MSG_DecayItem)))
			CloseUser(conn);
		return;
	}

	if (pMob[conn].TargetX < pItem[itemID].PosX - 3 || pMob[conn].TargetY < pItem[itemID].PosY - 3
		|| pMob[conn].TargetX > pItem[itemID].PosX + 3 || pMob[conn].TargetY > pItem[itemID].PosY + 3)
	{
		sprintf_s(temp, "GetItemFail posx:%d posx:%d tx:%d ty:%d", pItem[itemID].PosX, pItem[itemID].PosY,
			pMob[conn].TargetX, pMob[conn].TargetY);

		SystemLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, temp);
		return;
	}

	if (itemID == 1727 && pMob[conn].MOB.CurrentScore.Level < 1000)
		return;


	STRUCT_ITEM* ditem = &pItem[itemID].ITEM;
	int sIndex = ditem->sIndex;

	if (sIndex <= 0 || sIndex >= MAX_ITEMLIST)
		return;

	if (ditem->sIndex == 470)
	{
		if (pMob[conn].extra.QuestInfo.Mortal.PilulaOrc)
		{
			BASE_GetLanguage(temp, _NN_Youve_Done_It_Already);
			SendClientMessage(conn, temp);
		}
		else
		{
			SendClientMessage(conn, g_pMessageStringTable[_NN_Get_Skill_Point]);

			pMob[conn].extra.QuestInfo.Mortal.PilulaOrc = 1;
			BASE_ClearItem(ditem);

			pItemGrid[pItem[itemID].PosY][pItem[itemID].PosX] = 0;
			pItem[itemID].Mode = 0;

			MSG_DecayItem sm_deci;
			memset(&sm_deci, 0, sizeof(MSG_DecayItem));

			sm_deci.Type = _MSG_DecayItem;
			sm_deci.Size = sizeof(MSG_DecayItem);
			sm_deci.ID = ESCENE_FIELD;
			sm_deci.ItemID = m->ItemID;
			sm_deci.unk = 0;
			GridMulticast(pItem[itemID].PosX, pItem[itemID].PosY, (MSG_STANDARD*)&sm_deci, 0);

			pMob[conn].MOB.SkillBonus += 9;

			SendEmotion(conn, 14, 3);
			SendEtc(conn);
		}
		return;
	}

	if (sIndex >= 490 && sIndex < 500)
	{
		sprintf_s(temp, g_pMessageStringTable[_SSD_S_get_S], pMob[conn].MOB.MobName, g_pItemList[sIndex].Name);
		SendNotice(temp);

		MSG_DecayItem sm_deci;
		memset(&sm_deci, 0, sizeof(MSG_DecayItem));

		sm_deci.Type = _MSG_DecayItem;
		sm_deci.Size = sizeof(MSG_DecayItem);
		sm_deci.ID = ESCENE_FIELD;
		sm_deci.ItemID = m->ItemID;
		sm_deci.unk = 0;
		GridMulticast(pItem[itemID].PosX, pItem[itemID].PosY, (MSG_STANDARD*)&sm_deci, 0);
	}

	int itemX = pItem[itemID].PosX;
	int itemY = pItem[itemID].PosY;

	MSG_DecayItem sm_deci;
	memset(&sm_deci, 0, sizeof(MSG_DecayItem));

	sm_deci.Type = _MSG_DecayItem;
	sm_deci.Size = sizeof(MSG_DecayItem);
	sm_deci.ID = ESCENE_FIELD;
	sm_deci.ItemID = m->ItemID;
	sm_deci.unk = 0;

	if (itemX < 0 || itemX >= MAX_GRIDX || itemY <= 0 || itemY >= MAX_GRIDY)
	{
		int Size = sm_deci.Size;

		if (Size > sizeof(MSG_DecayItem))
		{
			sm_deci.Size = 0;
			return;
		}
		if (!pUser[conn].cSock.AddMessage((char*)&sm_deci, sizeof(MSG_DecayItem)))
			CloseUser(conn);

		pItem[itemID].Mode = 0;
		return;
	}

	if (pItemGrid[itemY][itemX] != itemID)
	{
		int Size = sm_deci.Size;

		if (Size > sizeof(MSG_DecayItem))
		{
			sm_deci.Size = 0;
			return;
		}
		if (!pUser[conn].cSock.AddMessage((char*)&sm_deci, sizeof(MSG_DecayItem)))
			CloseUser(conn);

		if (!pItemGrid[itemY][itemX])
			pItemGrid[itemY][itemX] = itemID;

		return;
	}

	if (itemX != m->GridX || itemY != m->GridY)
	{
		int Size = sm_deci.Size;

		if (Size > sizeof(MSG_DecayItem))
		{
			sm_deci.Size = 0;
			return;
		}
		if (!pUser[conn].cSock.AddMessage((char*)&sm_deci, sizeof(MSG_DecayItem)))
			CloseUser(conn);
		return;
	}

	int Vol = BASE_GetItemAbility(ditem, EF_VOLATILE);

	if (Vol == 2)
	{
		int HWORDCOIN = BASE_GetItemAbility((STRUCT_ITEM*)ditem, EF_HWORDCOIN);
		int coin1 = HWORDCOIN << 8;

		HWORDCOIN = BASE_GetItemAbility((STRUCT_ITEM*)ditem, EF_LWORDCOIN);

		coin1 += HWORDCOIN;
		int tcoin = coin1 + pMob[conn].MOB.Coin;

		if (tcoin >= 2000000000)
		{
			SendClientMessage(conn, g_pMessageStringTable[273]);
			return;
		}
		pMob[conn].MOB.Coin += coin1;

		int Size = sm_deci.Size;

		if (Size > sizeof(MSG_DecayItem))
		{
			sm_deci.Size = 0;
			return;
		}
		if (!pUser[conn].cSock.AddMessage((char*)&sm_deci, sizeof(MSG_DecayItem)))
			CloseUser(conn);

		BASE_ClearItem(ditem);
	}

	else
	{
		if (m->DestPos < 0 || m->DestPos >= MAX_CARRY)
		{
			//Log("DEBUG:Trading Fails.(Wrong source position)", pUser[conn].AccountName, pUser[conn].IP);
			return;
		}

		STRUCT_ITEM* bItem = &pMob[conn].MOB.Carry[m->DestPos];

		int error = -2;
		int can = bItem->sIndex == 0 ? 1 : 0;

		if (can == 0)
		{
			if (m->DestPos > 0 && m->DestPos <= pMob[conn].MaxCarry)
			{
				m->DestPos--;
				SendItem(conn, ITEM_PLACE_CARRY, m->DestPos, &pMob[conn].MOB.Carry[m->DestPos]);
			}
			return;
		}
		memcpy(bItem, ditem, sizeof(STRUCT_ITEM));

		char itemLog[2048];
		BASE_GetItemCode(bItem, itemLog);
		sprintf_s(temp, "getitem, %s", itemLog);
		SystemLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, temp);

	}

	MSG_CNFGetItem cnfGet;
	memset(&cnfGet, 0, sizeof(MSG_CNFGetItem));

	cnfGet.Type = _MSG_CNFGetItem;
	cnfGet.Size = sizeof(MSG_CNFGetItem);
	cnfGet.ID = ESCENE_FIELD;

	cnfGet.DestPos = m->DestPos;
	cnfGet.DestType = m->DestType;

	if (Size > sizeof(MSG_CNFGetItem))
	{
		m->Size = 0;
		return;
	}

	if (!pUser[conn].cSock.AddMessage((char*)&cnfGet, sizeof(MSG_CNFGetItem)))
		CloseUser(conn);

	GridMulticast(itemX, itemY, (MSG_STANDARD*)&sm_deci, 0);

	pItemGrid[itemY][itemX] = 0;
	pItem[itemID].Mode = 0;

	SendItem(conn, ITEM_PLACE_CARRY, m->DestPos, &pMob[conn].MOB.Carry[m->DestPos]);
}