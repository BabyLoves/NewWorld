#include "ProcessClientMessage.h"
#include <time.h>
#include <random>
#include <ctime>

void Exec_MSG_CombineItemAlquimia(int conn, char *pMsg)
{
	MSG_CombineItem *m = (MSG_CombineItem*)pMsg;

	int Size = m->Size;

	if (Size > sizeof(MSG_CombineItem)) //CONTROLE DE SIZE
	{
		SendClientMessage(conn, "Impossível executar ação14, tente mais tarde. ");
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
		if (m->Item[i].sIndex == 0)
			continue;

		int invPos = m->InvenPos[i];

		if (invPos < 0 || invPos >= pMob[conn].MaxCarry)
		{
			RemoveTrade(conn);
			return;
		}

		if (memcmp(&pMob[conn].MOB.Carry[invPos], &m->Item[i], sizeof(STRUCT_ITEM)))
		{
			SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 0);
			return;
		}
	}

	int combine = GetMatchCombineAlquimia(m->Item);

	if (combine == 7 || combine == 8 || combine == 9)
	{
		SendClientMessage(conn, "A Composição desses itens foi Desativada");
		return;
	}

	if (combine == 0)
	{
		SendClientMessage(conn, "Composição não permitida com itens em pack");
		return;
	}

	if (combine == -1 || pMob[conn].MOB.Class != 3)
	{
		SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 0);
		return;
	}

	for (int i = 0; i < MAX_COMBINE; i++)
	{
		if (m->Item[i].sIndex == 0)
			continue;

		snprintf(temp, sizeof(temp), "Combine Alquimia. Item[%d] %d - %d,%d,%d,%d,%d,%d", i,
			pMob[conn].MOB.Carry[m->InvenPos[i]].sIndex, 
			pMob[conn].MOB.Carry[m->InvenPos[i]].stEffect[0].cEffect, 
			pMob[conn].MOB.Carry[m->InvenPos[i]].stEffect[0].cValue,
			pMob[conn].MOB.Carry[m->InvenPos[i]].stEffect[1].cEffect,
			pMob[conn].MOB.Carry[m->InvenPos[i]].stEffect[1].cValue,
			pMob[conn].MOB.Carry[m->InvenPos[i]].stEffect[2].cEffect,
			pMob[conn].MOB.Carry[m->InvenPos[i]].stEffect[2].cValue);
		Combinelogsitem(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, temp);

		memset(&pMob[conn].MOB.Carry[m->InvenPos[i]], 0, sizeof(STRUCT_ITEM));
		SendItem(conn, ITEM_PLACE_CARRY, m->InvenPos[i], &pMob[conn].MOB.Carry[m->InvenPos[i]]);
	}

	for (int i = 0; i < MAX_COMBINE; i++)
	{
		if (m->Item[i].sIndex)
		{
			char itemlog[2048];

			BASE_GetItemCode(&m->Item[i], itemlog);

			strcat(temp, itemlog);
		}
	}

	std::mt19937 generator;
	generator.seed((unsigned int)std::time(0));
	std::uniform_int_distribution<uint32_t> dice(1, 100);
	int random = dice(generator);

	int chance = (pMob[conn].MOB.CurrentScore.Special[2] - 20) / 5; //60% com 320 pontos

	if (random <= chance || LOCALSERVER)
	{
		if (pMob[conn].extra.SecLearnedSkill & 0x10) // Ponto Mestre
		{
			pMob[conn].MOB.Carry[m->InvenPos[0]].sIndex = 3200 + combine;
			pMob[conn].MOB.Carry[m->InvenPos[0]].stEffect[0].cEffect = 61;
			pMob[conn].MOB.Carry[m->InvenPos[0]].stEffect[0].cValue = 5;
			pMob[conn].MOB.Carry[m->InvenPos[0]].stEffect[1].cEffect = 0;
			pMob[conn].MOB.Carry[m->InvenPos[0]].stEffect[1].cValue = 0;
			pMob[conn].MOB.Carry[m->InvenPos[0]].stEffect[2].cEffect = 0;
			pMob[conn].MOB.Carry[m->InvenPos[0]].stEffect[2].cValue = 0;

			SendItem(conn, ITEM_PLACE_CARRY, m->InvenPos[0], &pMob[conn].MOB.Carry[m->InvenPos[0]]);
			Combinelogsitem(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, strFmt("Combine Alquimia + 5x %s", g_pItemList[3200 + combine].Name));

			SendClientMessage(conn, g_pMessageStringTable[_NN_Processing_Complete]);

			SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 1);

			return;
		}
		else
		{
			pMob[conn].MOB.Carry[m->InvenPos[0]].sIndex = 3200 + combine;
			pMob[conn].MOB.Carry[m->InvenPos[0]].stEffect[0].cEffect = 0;
			pMob[conn].MOB.Carry[m->InvenPos[0]].stEffect[0].cValue = 0;
			pMob[conn].MOB.Carry[m->InvenPos[0]].stEffect[1].cEffect = 0;
			pMob[conn].MOB.Carry[m->InvenPos[0]].stEffect[1].cValue = 0;
			pMob[conn].MOB.Carry[m->InvenPos[0]].stEffect[2].cEffect = 0;
			pMob[conn].MOB.Carry[m->InvenPos[0]].stEffect[2].cValue = 0;

			SendItem(conn, ITEM_PLACE_CARRY, m->InvenPos[0], &pMob[conn].MOB.Carry[m->InvenPos[0]]);
			Combinelogsitem(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, strFmt("Combine Alquimia + 5x %s", g_pItemList[3200 + combine].Name));

			SendClientMessage(conn, g_pMessageStringTable[_NN_Processing_Complete]);

			SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 1);

			SaveUser(conn, 0);
			return;
		}
	}
	else
	{
		SendClientMessage(conn, g_pMessageStringTable[_NN_CombineFailed]);
		Combinelogsitem(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, "Combine Alquimia Falhou");

		SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 2);
		SaveUser(conn, 0);
		return;
	}
}