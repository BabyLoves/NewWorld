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

void Exec_MSG_SplitItem(int conn, char* pMsg)
{
	MSG_SplitItem* m = (MSG_SplitItem*)pMsg;

	int Size = m->Size;

	if (Size > sizeof(MSG_SplitItem)) //CONTROLE DE SIZE
	{
		SendClientMessage(conn, "Impossível executar ação50, tente mais tarde. ");
		return;
	}
	if (pUser[conn].Atraso != 0)
	{
		int isTime = GetTickCount64() - pUser[conn].Atraso; // ATRASO PACOTE

		if (isTime < 500)
		{
			SendClientMessage(conn, "Separe os itens devagar Meu Filho!");
			return;
		}

	}
	pUser[conn].Atraso = GetTickCount64();

	if (m->Slot < 0 || m->Slot >= MAX_CARRY - 4)
		return;

	if (m->Num <= 0 || m->Num >= 120)
		return;

	if (m->sIndex < 0 || m->sIndex == MAX_ITEMLIST)
		return;

	if (pUser[conn].Mode != USER_PLAY)
	{
		SendHpMode(conn);
		return;
	}

	if (pUser[conn].Trade.OpponentID)
	{
		RemoveTrade(conn);
		return;
	}

	int slot = m->Slot; //DESAGRUPAR ITENS MANUAL

	if (pMob[conn].MOB.Carry[slot].sIndex != 412 && pMob[conn].MOB.Carry[slot].sIndex != 413
		&& pMob[conn].MOB.Carry[slot].sIndex != 3140 && pMob[conn].MOB.Carry[slot].sIndex != 1774
		&& pMob[conn].MOB.Carry[slot].sIndex != 3200 && pMob[conn].MOB.Carry[slot].sIndex != 3201
		&& pMob[conn].MOB.Carry[slot].sIndex != 3202 && pMob[conn].MOB.Carry[slot].sIndex != 3203
		&& pMob[conn].MOB.Carry[slot].sIndex != 3204 && pMob[conn].MOB.Carry[slot].sIndex != 3205
		&& pMob[conn].MOB.Carry[slot].sIndex != 3206 && pMob[conn].MOB.Carry[slot].sIndex != 3207
		&& pMob[conn].MOB.Carry[slot].sIndex != 3208 && pMob[conn].MOB.Carry[slot].sIndex != 3209
		&& pMob[conn].MOB.Carry[slot].sIndex != 4011 && pMob[conn].MOB.Carry[slot].sIndex != 787
		&& pMob[conn].MOB.Carry[slot].sIndex != 4010 && pMob[conn].MOB.Carry[slot].sIndex != 4028
		&& pMob[conn].MOB.Carry[slot].sIndex != 4026 && pMob[conn].MOB.Carry[slot].sIndex != 4027
		&& pMob[conn].MOB.Carry[slot].sIndex != 4029 && pMob[conn].MOB.Carry[slot].sIndex != 3326
		&& pMob[conn].MOB.Carry[slot].sIndex != 3321 && pMob[conn].MOB.Carry[slot].sIndex != 3431
		&& pMob[conn].MOB.Carry[slot].sIndex != 3182 && pMob[conn].MOB.Carry[slot].sIndex != 777 && pMob[conn].MOB.Carry[slot].sIndex != 482 // bau IV
		&& pMob[conn].MOB.Carry[slot].sIndex != 3173 && pMob[conn].MOB.Carry[slot].sIndex != 475 && pMob[conn].MOB.Carry[slot].sIndex != 480 // bau III
		&& pMob[conn].MOB.Carry[slot].sIndex != 4144 && pMob[conn].MOB.Carry[slot].sIndex != 4140 && pMob[conn].MOB.Carry[slot].sIndex != 476 // bau II
		&& pMob[conn].MOB.Carry[slot].sIndex != 3326 && pMob[conn].MOB.Carry[slot].sIndex != 4016 && pMob[conn].MOB.Carry[slot].sIndex != 475 // bau I
		&& pMob[conn].MOB.Carry[slot].sIndex != 4017 && pMob[conn].MOB.Carry[slot].sIndex != 4018 && pMob[conn].MOB.Carry[slot].sIndex != 3140 // pedra da luz
		&& pMob[conn].MOB.Carry[slot].sIndex != 4146 && pMob[conn].MOB.Carry[slot].sIndex != 4019 && pMob[conn].MOB.Carry[slot].sIndex != 484 // bau VI
		&& pMob[conn].MOB.Carry[slot].sIndex != 4020 && pMob[conn].MOB.Carry[slot].sIndex != 4097 && pMob[conn].MOB.Carry[slot].sIndex != 483 // bau V
		&& pMob[conn].MOB.Carry[slot].sIndex != 419 && pMob[conn].MOB.Carry[slot].sIndex != 420 && pMob[conn].MOB.Carry[slot].sIndex != 4051
		&& pMob[conn].MOB.Carry[slot].sIndex != 578 && pMob[conn].MOB.Carry[slot].sIndex != 4051 && pMob[conn].MOB.Carry[slot].sIndex != 415
		&& (pMob[conn].MOB.Carry[slot].sIndex < 4038 || pMob[conn].MOB.Carry[slot].sIndex > 4042)
		&& (pMob[conn].MOB.Carry[slot].sIndex < 4051 || pMob[conn].MOB.Carry[slot].sIndex > 4055)
		&& (pMob[conn].MOB.Carry[slot].sIndex < 4117 || pMob[conn].MOB.Carry[slot].sIndex > 4121)
		&& (pMob[conn].MOB.Carry[slot].sIndex < 2441 || pMob[conn].MOB.Carry[slot].sIndex > 2444)
		&& (pMob[conn].MOB.Carry[slot].sIndex < 1760 || pMob[conn].MOB.Carry[slot].sIndex > 1743))
	{
		//Log("splititem, no validitem", pUser[conn].AccountName, pUser[conn].IP);
		return;
	}

	int amount = BASE_GetItemAmount(&pMob[conn].MOB.Carry[slot]);

	if (m->Num < 0 || m->Num > 120)
	{
		//Log("splititem, invalid num", pUser[conn].AccountName, pUser[conn].IP);
		return;
	}

	int x = 0;
	int invfree = 0;

	for (x = 0; x < pMob[conn].MaxCarry; x++)
	{
		if (pMob[conn].MOB.Carry[x].sIndex == 0)
			invfree++;
	}

	if (invfree < 1)
		return;

	if (amount == 0 || amount == 1 || amount <= m->Num)
		return;

	
	snprintf(temp, sizeof(temp), "splititem, itemindex:%d amount:%d num:%d", pMob[conn].MOB.Carry[slot].sIndex, amount, m->Num);
	ItemLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, temp);

	if (amount > 1)
		BASE_SetItemAmount(&pMob[conn].MOB.Carry[slot], amount - m->Num);

	else
		memset(&pMob[conn].MOB.Carry[slot], 0, sizeof(STRUCT_ITEM));

	STRUCT_ITEM nItem;

	memset(&nItem, 0, sizeof(STRUCT_ITEM));

	nItem.sIndex = pMob[conn].MOB.Carry[slot].sIndex;

	BASE_SetItemAmount(&nItem, m->Num);

	PutItem(conn, &nItem);
	SendItem(conn, ITEM_PLACE_CARRY, slot, &pMob[conn].MOB.Carry[slot]);
	return;
}