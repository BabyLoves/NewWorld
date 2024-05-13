
#include "ProcessClientMessage.h"

void Exec_MSG_CombineItemAilyn(int conn, char* pMsg)  //ailyn
{
	MSG_CombineItem* m = (MSG_CombineItem*)pMsg;

	int Size = m->Size;

	if (Size > sizeof(MSG_CombineItem)) //CONTROLE DE SIZE
	{
		SendClientMessage(conn, "Impossível executar ação13, tente mais tarde. ");
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

	for (int i = 0; i < MAX_COMBINE; i++)
	{
		int invPos = m->InvenPos[i];

		if (m->Item[i].sIndex == 0)
			continue;

		if (invPos == -1) {
			Combinelogsitem(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, "dup,Tentativa de Dup CombineAilyn");
			return;
		}

		if (invPos < 0 || invPos >= pMob[conn].MaxCarry)
		{
			RemoveTrade(conn);
			return;
		}

		if (memcmp(&pMob[conn].MOB.Carry[invPos], &m->Item[i], sizeof(STRUCT_ITEM)))
		{
			Combinelogsitem(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, "err,msg_CombineAilyn - item remove or changed.");
			SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 0);
			return;
		}
	}

	if (pMob[conn].MOB.Coin < 50000000)
	{
		SendClientMessage(conn, strFmt(g_pMessageStringTable[_DN_D_Cost], 50000000));

		SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 0);
		return;
	}

	if (pMob[conn].MOB.Coin < 50000000)
	{
		SendClientMessage(conn, g_pMessageStringTable[_NN_Wrong_Combination]);
		SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 0);
		return;
	}

	int combine = GetMatchCombineAilyn(m->Item);

	if (combine == 0)
	{
		SendClientMessage(conn, g_pMessageStringTable[_NN_Wrong_Combination]);

		SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 0);
		return;

	}
	if (combine == 77)
	{
		SendClientMessage(conn, "Não é possivel com Pedra do Sábio em Pack");

		SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 0);
		return;

	}

	Combinelogsitem(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, "* Item combine ailyn. *");

	for (int i = 2; i < MAX_COMBINE; i++)
	{
		if (m->Item[i].sIndex == 0)
			continue;

		memset(&pMob[conn].MOB.Carry[m->InvenPos[i]], 0, sizeof(STRUCT_ITEM));
		SendItem(conn, ITEM_PLACE_CARRY, m->InvenPos[i], &pMob[conn].MOB.Carry[m->InvenPos[i]]);
	}

	//SendEtc(conn);


	int _rand = rand() % 115;
	if (_rand >= 100)
		_rand -= 15;

	int zrand = rand() % 115;
	if (zrand >= 100)
		zrand -= 15;

	int ipos1 = 0;
	int ipos2 = 0;

	if (_rand <= combine || LOCALSERVER)
	{
		ipos1 = m->InvenPos[0];
		ipos2 = m->InvenPos[1];
		
		snprintf(temp, sizeof(temp), "Combine Ailyn. Item 1: %d - %d,%d,%d,%d,%d,%d | Item 2: %d - %d,%d,%d,%d,%d,%d",
			pMob[conn].MOB.Carry[ipos1].sIndex, pMob[conn].MOB.Carry[ipos1].stEffect[0].cEffect,
			pMob[conn].MOB.Carry[ipos1].stEffect[0].cValue, pMob[conn].MOB.Carry[ipos1].stEffect[1].cEffect,
			pMob[conn].MOB.Carry[ipos1].stEffect[1].cValue, pMob[conn].MOB.Carry[ipos1].stEffect[2].cEffect,
			pMob[conn].MOB.Carry[ipos1].stEffect[2].cValue,
			pMob[conn].MOB.Carry[ipos2].sIndex, pMob[conn].MOB.Carry[ipos2].stEffect[0].cEffect,
			pMob[conn].MOB.Carry[ipos2].stEffect[0].cValue, pMob[conn].MOB.Carry[ipos2].stEffect[1].cEffect,
			pMob[conn].MOB.Carry[ipos2].stEffect[1].cValue, pMob[conn].MOB.Carry[ipos2].stEffect[2].cEffect,
			pMob[conn].MOB.Carry[ipos2].stEffect[2].cValue);
		Combinelogsitem(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, temp);
			
		if (zrand <= 50)
		{
			pMob[conn].MOB.Carry[ipos1].stEffect[0].cEffect = pMob[conn].MOB.Carry[ipos2].stEffect[0].cEffect;
			pMob[conn].MOB.Carry[ipos1].stEffect[0].cValue = pMob[conn].MOB.Carry[ipos2].stEffect[0].cValue;
			pMob[conn].MOB.Carry[ipos1].stEffect[1].cEffect = pMob[conn].MOB.Carry[ipos2].stEffect[1].cEffect;
			pMob[conn].MOB.Carry[ipos1].stEffect[1].cValue = pMob[conn].MOB.Carry[ipos2].stEffect[1].cValue;
			pMob[conn].MOB.Carry[ipos1].stEffect[2].cEffect = pMob[conn].MOB.Carry[ipos2].stEffect[2].cEffect;
			pMob[conn].MOB.Carry[ipos1].stEffect[2].cValue = pMob[conn].MOB.Carry[ipos2].stEffect[2].cValue;
		}
		else
		{
			pMob[conn].MOB.Carry[ipos1].stEffect[0].cEffect = pMob[conn].MOB.Carry[ipos1].stEffect[0].cEffect;
			pMob[conn].MOB.Carry[ipos1].stEffect[0].cValue = pMob[conn].MOB.Carry[ipos1].stEffect[0].cValue;
			pMob[conn].MOB.Carry[ipos1].stEffect[1].cEffect = pMob[conn].MOB.Carry[ipos1].stEffect[1].cEffect;
			pMob[conn].MOB.Carry[ipos1].stEffect[1].cValue = pMob[conn].MOB.Carry[ipos1].stEffect[1].cValue;
			pMob[conn].MOB.Carry[ipos1].stEffect[2].cEffect = pMob[conn].MOB.Carry[ipos1].stEffect[2].cEffect;
			pMob[conn].MOB.Carry[ipos1].stEffect[2].cValue = pMob[conn].MOB.Carry[ipos1].stEffect[2].cValue;
		}

		snprintf(temp, sizeof(temp), "Combine Ailyn. Item result: %d - %d,%d,%d,%d,%d,%d",
			pMob[conn].MOB.Carry[ipos1].sIndex, pMob[conn].MOB.Carry[ipos1].stEffect[0].cEffect,
			pMob[conn].MOB.Carry[ipos1].stEffect[0].cValue, pMob[conn].MOB.Carry[ipos1].stEffect[1].cEffect,
			pMob[conn].MOB.Carry[ipos1].stEffect[1].cValue, pMob[conn].MOB.Carry[ipos1].stEffect[2].cEffect,
			pMob[conn].MOB.Carry[ipos1].stEffect[2].cValue);
		Combinelogsitem(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, temp);

		BASE_SetItemSanc(&pMob[conn].MOB.Carry[ipos1], 10, m->Item[3].sIndex - 2441);

		memset(&pMob[conn].MOB.Carry[ipos2], 0, sizeof(STRUCT_ITEM));
		SendItem(conn, ITEM_PLACE_CARRY, ipos2, &pMob[conn].MOB.Carry[ipos2]);

		pMob[conn].MOB.Coin -= 50000000;

		SendEtc(conn);

		SendClientMessage(conn, g_pMessageStringTable[_NN_Processing_Complete]);

		SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 1);
		SendItem(conn, ITEM_PLACE_CARRY, ipos1, &pMob[conn].MOB.Carry[ipos1]);
		SaveUser(conn, 0);
		return;
	}
	else
	{
	
		snprintf(temp, sizeof(temp), "%s(%d/%d)", g_pMessageStringTable[_NN_CombineFailed], _rand, combine);
		SendClientMessage(conn, temp);

		/*snprintf(temp, sizeof(temp), "%s Teve falha realizar (+10).", pMob[conn].MOB.MobName);
		Combinelogsitem(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, temp);*/

		//SendSpkMsg(1, temp, TNColor::Red, true);

		pMob[conn].MOB.Coin -= 50000000;
		SendEtc(conn);

		SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 2);
		SaveUser(conn, 0);
		return;
	}
}