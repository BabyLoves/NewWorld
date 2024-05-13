
#include "ProcessClientMessage.h"

void Exec_MSG_EventoMissions(int conn, char* pMsg)
{
	MSG_CombineItem* m = (MSG_CombineItem*)pMsg;

	int Size = m->Size;

	if (Size > sizeof(MSG_CombineItem)) //CONTROLE DE SIZE
	{
		SendClientMessage(conn, "Impossível executar ação12, tente mais tarde. ");
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
			Combinelogsitem(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, "dup,Tentativa de Dup EventoMissions");
			return;
		}

		if (invPos < 0 || invPos >= pMob[conn].MaxCarry)
		{
			RemoveTrade(conn);
			return;
		}

		if (memcmp(&pMob[conn].MOB.Carry[invPos], &m->Item[i], sizeof(STRUCT_ITEM)))
		{
			Combinelogsitem(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, "err,msg_EventoMission - item remove or changed.");
			SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 0);
			return;
		}

		if (m->Item[i].sIndex == 747)
			return;
	}

	int combine = GetMatchCombineEvent(m->Item);

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

	if (combine == 1) {
		int ipos = m->InvenPos[0];

		pMob[conn].MOB.Carry[ipos].sIndex = 2321;
		pMob[conn].MOB.Carry[ipos].stEffect[0].cEffect = 78;
		pMob[conn].MOB.Carry[ipos].stEffect[0].cValue = 2;
		pMob[conn].MOB.Carry[ipos].stEffect[1].cEffect = 0;
		pMob[conn].MOB.Carry[ipos].stEffect[1].cValue = 0;
		pMob[conn].MOB.Carry[ipos].stEffect[2].cEffect = 0;
		pMob[conn].MOB.Carry[ipos].stEffect[2].cValue = 0;

		memset(&pMob[conn].MOB.Carry[m->InvenPos[1]], 0, sizeof(STRUCT_ITEM));
		SendItem(conn, ITEM_PLACE_CARRY, m->InvenPos[1], &pMob[conn].MOB.Carry[m->InvenPos[1]]);

		SendClientMessage(conn, g_pMessageStringTable[_NN_Processing_Complete]);

		SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 1);

		Combinelogsitem(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, strFmt("%s Concluiu a Missão do Evento 1 e recebeu: %s.", pMob[conn].MOB.MobName, g_pItemList[pMob[conn].MOB.Carry[m->InvenPos[0]].sIndex].Name));

		SendItem(conn, ITEM_PLACE_CARRY, ipos, &pMob[conn].MOB.Carry[ipos]);
		SaveUser(conn, 0);
		return;
	}
	if (combine == 2) {
		int ipos = m->InvenPos[0];

		pMob[conn].MOB.Carry[ipos].sIndex = 2323;
		pMob[conn].MOB.Carry[ipos].stEffect[0].cEffect = 78;
		pMob[conn].MOB.Carry[ipos].stEffect[0].cValue = 2;
		pMob[conn].MOB.Carry[ipos].stEffect[1].cEffect = 0;
		pMob[conn].MOB.Carry[ipos].stEffect[1].cValue = 0;
		pMob[conn].MOB.Carry[ipos].stEffect[2].cEffect = 0;
		pMob[conn].MOB.Carry[ipos].stEffect[2].cValue = 0;

		memset(&pMob[conn].MOB.Carry[m->InvenPos[1]], 0, sizeof(STRUCT_ITEM));
		SendItem(conn, ITEM_PLACE_CARRY, m->InvenPos[1], &pMob[conn].MOB.Carry[m->InvenPos[1]]);

		SendClientMessage(conn, g_pMessageStringTable[_NN_Processing_Complete]);

		SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 1);

		Combinelogsitem(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, strFmt("%s Concluiu a Missão do Evento 2 e recebeu: %s.", pMob[conn].MOB.MobName, g_pItemList[pMob[conn].MOB.Carry[m->InvenPos[0]].sIndex].Name));

		SendItem(conn, ITEM_PLACE_CARRY, ipos, &pMob[conn].MOB.Carry[ipos]);
		SaveUser(conn, 0);
		return;
	}
	if (combine == 3) {
		int ipos = m->InvenPos[0];

		pMob[conn].MOB.Carry[ipos].sIndex = 2322;
		pMob[conn].MOB.Carry[ipos].stEffect[0].cEffect = 78;
		pMob[conn].MOB.Carry[ipos].stEffect[0].cValue = 2;
		pMob[conn].MOB.Carry[ipos].stEffect[1].cEffect = 0;
		pMob[conn].MOB.Carry[ipos].stEffect[1].cValue = 0;
		pMob[conn].MOB.Carry[ipos].stEffect[2].cEffect = 0;
		pMob[conn].MOB.Carry[ipos].stEffect[2].cValue = 0;

		memset(&pMob[conn].MOB.Carry[m->InvenPos[1]], 0, sizeof(STRUCT_ITEM));
		SendItem(conn, ITEM_PLACE_CARRY, m->InvenPos[1], &pMob[conn].MOB.Carry[m->InvenPos[1]]);

		SendClientMessage(conn, g_pMessageStringTable[_NN_Processing_Complete]);

		SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 1);

		Combinelogsitem(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, strFmt("%s Concluiu a Missão do Evento 3 e recebeu: %s.", pMob[conn].MOB.MobName, g_pItemList[pMob[conn].MOB.Carry[m->InvenPos[0]].sIndex].Name));

		SendItem(conn, ITEM_PLACE_CARRY, ipos, &pMob[conn].MOB.Carry[ipos]);
		SaveUser(conn, 0);
		return;
	}
	if (combine == 4) {
		int ipos = m->InvenPos[0];

		pMob[conn].MOB.Carry[ipos].sIndex = 5773;
		pMob[conn].MOB.Carry[ipos].stEffect[0].cEffect = 0;
		pMob[conn].MOB.Carry[ipos].stEffect[0].cValue = 0;
		pMob[conn].MOB.Carry[ipos].stEffect[1].cEffect = 0;
		pMob[conn].MOB.Carry[ipos].stEffect[1].cValue = 0;
		pMob[conn].MOB.Carry[ipos].stEffect[2].cEffect = 0;
		pMob[conn].MOB.Carry[ipos].stEffect[2].cValue = 0;

		memset(&pMob[conn].MOB.Carry[m->InvenPos[1]], 0, sizeof(STRUCT_ITEM));
		SendItem(conn, ITEM_PLACE_CARRY, m->InvenPos[1], &pMob[conn].MOB.Carry[m->InvenPos[1]]);

		SendClientMessage(conn, g_pMessageStringTable[_NN_Processing_Complete]);

		SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 1);

		Combinelogsitem(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, strFmt("%s Concluiu a Missão do Evento 4 e recebeu: %s.", pMob[conn].MOB.MobName, g_pItemList[pMob[conn].MOB.Carry[m->InvenPos[0]].sIndex].Name));

		SendItem(conn, ITEM_PLACE_CARRY, ipos, &pMob[conn].MOB.Carry[ipos]);
		SaveUser(conn, 0);
		return;
	}
	if (combine == 5) {
		int ipos = m->InvenPos[0];

		pMob[conn].MOB.Carry[ipos].sIndex = 5772;
		pMob[conn].MOB.Carry[ipos].stEffect[0].cEffect = 0;
		pMob[conn].MOB.Carry[ipos].stEffect[0].cValue = 0;
		pMob[conn].MOB.Carry[ipos].stEffect[1].cEffect = 0;
		pMob[conn].MOB.Carry[ipos].stEffect[1].cValue = 0;
		pMob[conn].MOB.Carry[ipos].stEffect[2].cEffect = 0;
		pMob[conn].MOB.Carry[ipos].stEffect[2].cValue = 0;

		memset(&pMob[conn].MOB.Carry[m->InvenPos[1]], 0, sizeof(STRUCT_ITEM));
		SendItem(conn, ITEM_PLACE_CARRY, m->InvenPos[1], &pMob[conn].MOB.Carry[m->InvenPos[1]]);

		SendClientMessage(conn, g_pMessageStringTable[_NN_Processing_Complete]);

		SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 1);

		Combinelogsitem(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, strFmt("%s Concluiu a Missão do Evento 5 e recebeu: %s.", pMob[conn].MOB.MobName, g_pItemList[pMob[conn].MOB.Carry[m->InvenPos[0]].sIndex].Name));

		SendItem(conn, ITEM_PLACE_CARRY, ipos, &pMob[conn].MOB.Carry[ipos]);
		SaveUser(conn, 0);
		return;
	}
	if (combine == 6) {
		int ipos = m->InvenPos[0];

		pMob[conn].MOB.Carry[ipos].sIndex = m->Item[4].sIndex;
		pMob[conn].MOB.Carry[ipos].stEffect[0].cEffect = 43;
		pMob[conn].MOB.Carry[ipos].stEffect[0].cValue = 9;
		pMob[conn].MOB.Carry[ipos].stEffect[1].cEffect = 2;
		pMob[conn].MOB.Carry[ipos].stEffect[1].cValue = 36;
		pMob[conn].MOB.Carry[ipos].stEffect[2].cEffect = 0;
		pMob[conn].MOB.Carry[ipos].stEffect[2].cValue = 0;

		memset(&pMob[conn].MOB.Carry[m->InvenPos[1]], 0, sizeof(STRUCT_ITEM));
		SendItem(conn, ITEM_PLACE_CARRY, m->InvenPos[1], &pMob[conn].MOB.Carry[m->InvenPos[1]]);

		SendClientMessage(conn, g_pMessageStringTable[_NN_Processing_Complete]);

		SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 1);

		Combinelogsitem(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, strFmt("%s Concluiu a Missão do Evento 6 e recebeu: %s.", pMob[conn].MOB.MobName, g_pItemList[pMob[conn].MOB.Carry[m->InvenPos[0]].sIndex].Name));

		SendItem(conn, ITEM_PLACE_CARRY, ipos, &pMob[conn].MOB.Carry[ipos]);
		SaveUser(conn, 0);
		return;
	}
	if (combine == 7) {
		int ipos = m->InvenPos[0];

		pMob[conn].MOB.Carry[ipos].sIndex = m->Item[4].sIndex;
		pMob[conn].MOB.Carry[ipos].stEffect[0].cEffect = 43;
		pMob[conn].MOB.Carry[ipos].stEffect[0].cValue = 9;
		pMob[conn].MOB.Carry[ipos].stEffect[1].cEffect = 60;
		pMob[conn].MOB.Carry[ipos].stEffect[1].cValue = 16;
		pMob[conn].MOB.Carry[ipos].stEffect[2].cEffect = 0;
		pMob[conn].MOB.Carry[ipos].stEffect[2].cValue = 0;

		memset(&pMob[conn].MOB.Carry[m->InvenPos[1]], 0, sizeof(STRUCT_ITEM));
		SendItem(conn, ITEM_PLACE_CARRY, m->InvenPos[1], &pMob[conn].MOB.Carry[m->InvenPos[1]]);

		SendClientMessage(conn, g_pMessageStringTable[_NN_Processing_Complete]);

		SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 1);

		Combinelogsitem(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, strFmt("%s Concluiu a Missão do Evento 7 e recebeu: %s.", pMob[conn].MOB.MobName, g_pItemList[pMob[conn].MOB.Carry[m->InvenPos[0]].sIndex].Name));

		SendItem(conn, ITEM_PLACE_CARRY, ipos, &pMob[conn].MOB.Carry[ipos]);
		SaveUser(conn, 0);
		return;
	}
	if (combine == 8) {
		int ipos = m->InvenPos[0];

		int Secretas[4] = { 5334, 5335, 5336, 5337};
		int srand = rand() % 4;

		pMob[conn].MOB.Carry[ipos].sIndex = Secretas[srand];
		pMob[conn].MOB.Carry[ipos].stEffect[0].cEffect = 0;
		pMob[conn].MOB.Carry[ipos].stEffect[0].cValue = 0;
		pMob[conn].MOB.Carry[ipos].stEffect[1].cEffect = 0;
		pMob[conn].MOB.Carry[ipos].stEffect[1].cValue = 0;
		pMob[conn].MOB.Carry[ipos].stEffect[2].cEffect = 0;
		pMob[conn].MOB.Carry[ipos].stEffect[2].cValue = 0;

		memset(&pMob[conn].MOB.Carry[m->InvenPos[1]], 0, sizeof(STRUCT_ITEM));
		SendItem(conn, ITEM_PLACE_CARRY, m->InvenPos[1], &pMob[conn].MOB.Carry[m->InvenPos[1]]);

		SendClientMessage(conn, g_pMessageStringTable[_NN_Processing_Complete]);

		SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 1);

		Combinelogsitem(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, strFmt("%s Concluiu a Missão do Evento 8 e recebeu: %s.", pMob[conn].MOB.MobName, g_pItemList[pMob[conn].MOB.Carry[m->InvenPos[0]].sIndex].Name));

		SendItem(conn, ITEM_PLACE_CARRY, ipos, &pMob[conn].MOB.Carry[ipos]);
		SaveUser(conn, 0);
		return;
	}
}