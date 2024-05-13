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

void Exec_MSG_OpenDonate(int conn, char* pMsg)
{
	MSG_REQShopList* m = (MSG_REQShopList*)pMsg;
	MSG_DonateStore p;
	auto Packet = (MSG_DonateStore*)pMsg;

	int mobID = 0;
	int mobDropID = 0;

	int Size = m->Size;

	if (Packet->Warp < 0)
		return;

	if (Packet->npcID < 0 && Packet->npcID > MAX_MOB)
		return;

	if (Packet->Face < 0 || Packet->Face > 10000)
		return;

	if (Packet->Effect < 0 || Packet->Effect > 6500)
		return;

	if (pUser[conn].Atraso != 0)
	{
		int isTime = GetTickCount64() - pUser[conn].Atraso; // ATRASO PACOTE

		if (isTime < 200)
		{
			SendClientMessage(conn, "Aguarde um segundo antes de enviar nova solicitação");
			return;
		}

	}
	pUser[conn].Atraso = GetTickCount64();

	if (Packet->npcID == 1010)
	{		
		for (int i = 1000; i < 12800; i++)
		{
			auto Mob = GetMobFromIndex(i);
			int Effect = Packet->Effect;
			int Face = Packet->Face;

			if (Mob->GenerateIndex == Effect) {
				mobID = i;
				break;
			}
		}
		if (mobID != 0)
		{
			memset(&p, 0, sizeof(MSG_DonateStore));
			p.ID = conn;
			p.Type = _MSG_REQShopList;
			p.Size = sizeof(MSG_DonateStore);
			p.npcID = mobID;
			p.Warp = 17669;
			pUser[conn].Ingame.DonateBuyItem = mobID;
			pUser[conn].Ingame.MobDonateStore = TRUE;
			pUser[conn].Ingame.CanBuy = FALSE;
			Exec_MSG_REQShopList(conn, (char*)&p);
		}
	}

	else if (Packet->npcID == 1000)
	{
		for (int i = 1000; i < 12800; i++)
		{
			if (Packet->Warp == 100)
				if (!strcmp(pMob[i].MOB.MobName, "Armas F"))
				{
					mobID = i;
					break;
				}
			if (Packet->Warp == 101)
				if (!strcmp(pMob[i].MOB.MobName, "Sets F"))
				{
					mobID = i;
					break;
				}
			if (Packet->Warp == 102)
				if (!strcmp(pMob[i].MOB.MobName, "Refinaveis F"))
				{
					mobID = i;
					break;
				}
			if (Packet->Warp == 103)
				if (!strcmp(pMob[i].MOB.MobName, "Quests F"))
				{
					mobID = i;
					break;
				}
			
		}
		if (mobID != 0)
		{
			memset(&p, 0, sizeof(MSG_DonateStore));
			p.ID = conn;
			p.Type = _MSG_REQShopList;
			p.Size = sizeof(MSG_DonateStore);
			p.npcID = mobID;
			p.Warp = 17669;
			pUser[conn].Ingame.DonateBuyItem = mobID;
			pUser[conn].Ingame.MobDonateStore = TRUE;
			pUser[conn].Ingame.CanBuy = TRUE;
			Exec_MSG_REQShopList(conn, (char*)&p);
			SendEtc(conn);
			//SendDonateShop(conn, m->Target, 1);
		}
	}
	else
		pUser[conn].Ingame.DonateBuyItem = 0;
	return;
}

/*REQUSHOPLIST*/
void Exec_MSG_REQShopList(int conn, char* pMsg)
{
	MSG_REQShopList* m = (MSG_REQShopList*)pMsg;

	if (conn < 0 || conn >= MAX_USER)
		return;

	if (pMob[conn].MOB.CurrentScore.Hp == 0 || pUser[conn].Mode != USER_PLAY)
	{
		SendHpMode(conn);
		return;
	}

	int target = m->Target;

	if (pUser[conn].Ingame.DonateBuyItem <= 0 && target < MAX_USER || target >= MAX_MOB)
		return;

	int view = GetInView(conn, target);

	if (pUser[conn].Ingame.DonateBuyItem <= 0 && view == 0) {
		pUser[conn].Ingame.CanBuy = 0;
		return;
	}

	if (pMob[target].MOB.Merchant == 0) {
		pUser[conn].Ingame.CanBuy = 0;
		SendItemList(conn, target, 1);
		return;
	}
	else if (pMob[target].MOB.Merchant == 1) {
		pUser[conn].Ingame.CanBuy = 1;
		SendShopList(conn, target, 1);
		return;
	}
	else if ((pMob[target].MOB.Merchant) == 19) {
		pUser[conn].Ingame.CanBuy = 1;
		SendShopList(conn, target, 3);
		return;
	}
	return;
}