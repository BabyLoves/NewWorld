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
#include <time.h>
#include <random>
#include <ctime>

void Exec_MSG_CombineItemExtracao(int conn, char *pMsg)
{
	MSG_STANDARDPARM2 *m = (MSG_STANDARDPARM2*)pMsg;

	int ItemSlot = m->Parm2;

	int Size = m->Size;

	if (Size > sizeof(MSG_STANDARDPARM2)) //CONTROLE DE SIZE
	{
		SendClientMessage(conn, "Impossível executar ação17, tente mais tarde. ");
		return;
	}
	if (pUser[conn].Atraso != 0)
	{
		int isTime = GetTickCount64() - pUser[conn].Atraso; // ATRASO PACOTE

		if (isTime < 800)
		{
			SendClientMessage(conn, "Aguarde 1 segundo para uma nova Tentativa.");
			return;
		}

	}
	pUser[conn].Atraso = GetTickCount64();

	if (ItemSlot < 0 || ItemSlot >= pMob[conn].MaxCarry)
		return;

	int item = pMob[conn].MOB.Carry[ItemSlot].sIndex;

	if(item <= 0 || item >= MAX_ITEMLIST)
		return;

	int itemlevel = BASE_GetItemAbility(&pMob[conn].MOB.Carry[ItemSlot], EF_ITEMLEVEL);

	if(itemlevel >= 5)
		return;

	if(BASE_GetItemSanc(&pMob[conn].MOB.Carry[ItemSlot]) < 0)
		return;

	if((g_pItemList[item].nPos != 2 && g_pItemList[item].nPos != 4 && g_pItemList[item].nPos != 8 && g_pItemList[item].nPos != 16 && g_pItemList[item].nPos != 32) || BASE_GetItemAbility(&pMob[conn].MOB.Carry[ItemSlot], EF_MOBTYPE) != 0)
		return;

	int i = 0;

	for (i = 0; i < pMob[conn].MaxCarry; i++)
	{
		if (pMob[conn].MOB.Carry[i].sIndex != 1774)
			continue;

		BASE_ClearItem(&pMob[conn].MOB.Carry[i]);
		SendItem(conn, ITEM_PLACE_CARRY, i, &pMob[conn].MOB.Carry[i]);
		SaveUser(conn, 0);
		break;
	}

	if (i == pMob[conn].MaxCarry)
		return;
		
	std::mt19937 generator;
	generator.seed((unsigned int)std::time(0));
	std::uniform_int_distribution<uint32_t> dice(1, 100);
	int random = dice(generator);

	int rate = (pMob[conn].MOB.CurrentScore.Special[2] - 20) / 5; //60% com 320 pontos
	// remover depois

	if(random < rate)
	{
		pMob[conn].MOB.Carry[ItemSlot].stEffect[0].cEffect = EF_ITEMLEVEL;
		pMob[conn].MOB.Carry[ItemSlot].stEffect[0].cValue = itemlevel;

		if(pMob[conn].MOB.Carry[ItemSlot].stEffect[1].cEffect == EF_DAMAGE)
			pMob[conn].MOB.Carry[ItemSlot].stEffect[1].cValue += BASE_GetStaticItemAbility(&pMob[conn].MOB.Carry[ItemSlot], EF_DAMAGE);

		if(pMob[conn].MOB.Carry[ItemSlot].stEffect[2].cEffect == EF_DAMAGE)
			pMob[conn].MOB.Carry[ItemSlot].stEffect[2].cValue += BASE_GetStaticItemAbility(&pMob[conn].MOB.Carry[ItemSlot], EF_DAMAGE);

		pMob[conn].MOB.Carry[ItemSlot].sIndex = 3021;

		if(g_pItemList[item].nPos == 4)
			pMob[conn].MOB.Carry[ItemSlot].sIndex++;

		else if(g_pItemList[item].nPos == 8)
			pMob[conn].MOB.Carry[ItemSlot].sIndex += 2;

		else if(g_pItemList[item].nPos == 16)
			pMob[conn].MOB.Carry[ItemSlot].sIndex += 3;

		else if(g_pItemList[item].nPos == 32)
			pMob[conn].MOB.Carry[ItemSlot].sIndex += 4;

		SendItem(conn, ITEM_PLACE_CARRY, ItemSlot, &pMob[conn].MOB.Carry[ItemSlot]);
		SaveUser(conn, 0);

		char tt[256];
		sprintf(temp, "%s ", pUser[conn].AccountName);
		BASE_GetItemCode(&pMob[conn].MOB.Carry[ItemSlot], tt);
		strcat(temp, tt);

		//ItemLog(temp, "*** Combine ht_skill_extração sucess ***", pUser[conn].IP);
	}
	else
	{
		BASE_ClearItem(&pMob[conn].MOB.Carry[ItemSlot]);
		SendItem(conn, ITEM_PLACE_CARRY, ItemSlot, &pMob[conn].MOB.Carry[ItemSlot]);
		SaveUser(conn, 0);

		//ItemLog("*** Combine ht_skill_extração fail ***", pMob[conn].MOB.MobName, pUser[conn].IP);
	}
}