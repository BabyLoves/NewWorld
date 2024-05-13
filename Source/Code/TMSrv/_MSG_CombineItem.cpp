
#include "ProcessClientMessage.h"

void Exec_MSG_CombineItem(int conn, char* pMsg)
{
	MSG_CombineItem* m = (MSG_CombineItem*)pMsg;

	int Size = m->Size;

	if (Size > sizeof(MSG_CombineItem)) //CONTROLE DE CLIENTE SIZE
	{
		SendClientMessage(conn, "Impossível executar ação11, tente mais tarde. ");
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
			Combinelogsitem(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, "dup,Tentativa de Dup CombineItem");
			return;
		}

		if (invPos < 0 || invPos >= pMob[conn].MaxCarry)
		{
			RemoveTrade(conn);
			return;
		}

		if (memcmp(&pMob[conn].MOB.Carry[invPos], &m->Item[i], sizeof(STRUCT_ITEM)))
		{
			Combinelogsitem(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, "err,msg_CombineItem - item remove or changed.");
			SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 0);
			return;
		}
	}

	int combine = GetMatchCombine(m->Item);

	if (combine == 0)
	{
		SendClientMessage(conn, g_pMessageStringTable[_NN_Wrong_Combination]);
		SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 0);
		return;
	}

	for (int i = 0; i < MAX_COMBINE; i++)
	{
		if (m->Item[i].sIndex == 0)
			continue;

		memset(&pMob[conn].MOB.Carry[m->InvenPos[i]], 0, sizeof(STRUCT_ITEM));
		SendItem(conn, ITEM_PLACE_CARRY, m->InvenPos[i], &pMob[conn].MOB.Carry[m->InvenPos[i]]);
	}


	int _rand = rand() % 115;
	if (_rand >= 100)
		_rand -= 15;

	if (_rand <= combine || LOCALSERVER)
	{
		int itemindex = m->Item[0].sIndex;
		int extra = g_pItemList[itemindex].Extra;

		if (extra > 0 && extra < MAX_ITEMLIST)
		{
			int ipos = m->InvenPos[0];
			int joia = m->Item[1].sIndex - 2441;

			if (joia >= 0 && joia <= 3)
			{
				memmove_s(&pMob[conn].MOB.Carry[ipos].sIndex, sizeof(STRUCT_ITEM), &m->Item[0], sizeof(STRUCT_ITEM));

				pMob[conn].MOB.Carry[ipos].sIndex = joia + extra;

				BASE_SetItemSanc(&pMob[conn].MOB.Carry[ipos], 7, 0);

				
				snprintf(temp, sizeof(temp), "Jogador [%s] Sucesso no anct item: %s %d %d %d %d %d %d %d chance [%d/%d]", pMob[conn].MOB.MobName, g_pItemList[itemindex].Name, g_pItemList[itemindex].Extra,
					pMob[conn].MOB.Carry[ipos].stEffect[0].cEffect, pMob[conn].MOB.Carry[ipos].stEffect[0].cValue, //EF1 EFV1
					pMob[conn].MOB.Carry[ipos].stEffect[1].cEffect, pMob[conn].MOB.Carry[ipos].stEffect[1].cValue, //EF2 EFV2
					pMob[conn].MOB.Carry[ipos].stEffect[2].cEffect, pMob[conn].MOB.Carry[ipos].stEffect[2].cValue, _rand, combine); //EF3 EFV3
				Combinelogsitem(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, temp);

				//SendSpkMsg(1, strFmt("Jogador [%s] Sucesso no anct item: %s", pMob[conn].MOB.MobName, g_pItemList[itemindex].Name), TNColor::GreenYellow, true);

				SendClientMessage(conn, "Sucesso na Composição Anct");
				SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 1);
				SendItem(conn, ITEM_PLACE_CARRY, ipos, &pMob[conn].MOB.Carry[ipos]);
				SendCarry(conn);
				SaveUser(conn, 0);
				return;
			}
			else
			{
				Combinelogsitem(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, strFmt("err,msg_combine - stone wrong %d", joia));
				return;
			}
		}
		else
		{
			Combinelogsitem(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, strFmt("err,msg_combine - extra item index wrong %d", itemindex));
			return;
		}
	}
	else
	{
		/*
		snprintf(temp, sizeof(temp), "%s Teve falha na composição anct do item.", pMob[conn].MOB.MobName);
		SendSpkMsg(1, temp, TNColor::Red, true);*/

		SendClientMessage(conn, "Falha na Composiçao Anct");
		Combinelogsitem(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, "Falha na composição anct do item");

		SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 2);
		SaveUser(conn, 0);

		return;
	}
}