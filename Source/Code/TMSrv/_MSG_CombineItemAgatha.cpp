
#include "ProcessClientMessage.h"

void Exec_MSG_CombineItemAgatha(int conn, char* pMsg)
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
			Combinelogsitem(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, "dup,Tentativa de Dup CombineAgatha");
			return;
		}

		if (invPos < 0 || invPos >= pMob[conn].MaxCarry)
		{
			RemoveTrade(conn);
			return;
		}

		if (memcmp(&pMob[conn].MOB.Carry[invPos], &m->Item[i], sizeof(STRUCT_ITEM)))
		{
			Combinelogsitem(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, "err,msg_CombineAgatha - item remove or changed.");
			SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 0);
			return;
		}

		if (m->Item[i].sIndex == 747)
			return;
	}

	int combine = GetMatchCombineAgatha(m->Item);

	if (combine == 0)
	{
		SendClientMessage(conn, g_pMessageStringTable[_NN_Wrong_Combination]);
		SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 0);
		return;
	}

	if (combine == 77)
	{
		SendClientMessage(conn, "Não é possivel com Pedra da Luz em Pack");
		SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 0);
		return;
	}

	for (int i = 0; i < MAX_COMBINE; i++)
	{
		if (m->Item[i].sIndex == 0)
			continue;

		if (i == 1)
			continue;

		memset(&pMob[conn].MOB.Carry[m->InvenPos[i]], 0, sizeof(STRUCT_ITEM));
		SendItem(conn, ITEM_PLACE_CARRY, m->InvenPos[i], &pMob[conn].MOB.Carry[m->InvenPos[i]]);
	}

	int _rand = rand() % 115;
	if (_rand >= 100)
		_rand -= 15;


	int ipos = m->InvenPos[0];

	if (_rand <= combine || LOCALSERVER)
	{
		pMob[conn].MOB.Carry[ipos].sIndex = m->Item[0].sIndex;
		pMob[conn].MOB.Carry[ipos].stEffect[0].cEffect = m->Item[1].stEffect[0].cEffect;
		pMob[conn].MOB.Carry[ipos].stEffect[0].cValue = m->Item[1].stEffect[0].cValue;
		pMob[conn].MOB.Carry[ipos].stEffect[1].cEffect = m->Item[1].stEffect[1].cEffect;
		pMob[conn].MOB.Carry[ipos].stEffect[1].cValue = m->Item[1].stEffect[1].cValue;
		pMob[conn].MOB.Carry[ipos].stEffect[2].cEffect = m->Item[1].stEffect[2].cEffect;
		pMob[conn].MOB.Carry[ipos].stEffect[2].cValue = m->Item[1].stEffect[2].cValue;

		BASE_SetItemSanc(&pMob[conn].MOB.Carry[ipos], 7, 0);

		memset(&pMob[conn].MOB.Carry[m->InvenPos[1]], 0, sizeof(STRUCT_ITEM));
		SendItem(conn, ITEM_PLACE_CARRY, m->InvenPos[1], &pMob[conn].MOB.Carry[m->InvenPos[1]]);

		SendClientMessage(conn, g_pMessageStringTable[_NN_Processing_Complete]);

		SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 1);


		Combinelogsitem(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, strFmt("%s Teve sucesso na passar add para item %s.", pMob[conn].MOB.MobName, g_pItemList[pMob[conn].MOB.Carry[m->InvenPos[0]].sIndex].Name));
		//SendSpkMsg(1, temp, TNColor::GreenYellow, true);		 

		SendItem(conn, ITEM_PLACE_CARRY, ipos, &pMob[conn].MOB.Carry[ipos]);
		SaveUser(conn, 0);
		return;
	}
	else
	{
		SendClientMessage(conn, strFmt("%s(%d/%d)", g_pMessageStringTable[_NN_CombineFailed], _rand, combine));
		Combinelogsitem(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, strFmt("%s(%d/%d)", g_pMessageStringTable[_NN_CombineFailed], _rand, combine));
		/*snprintf(temp, sizeof(temp), "%s Teve falha ao tentar passar add.", pMob[conn].MOB.MobName);
		Combinelogsitem(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, temp);
		SendSpkMsg(1, temp, TNColor::Red, true);
		SendClientMessage(conn, temp);*/


		SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 2);
		SaveUser(conn, 0);
		return;
	}
}