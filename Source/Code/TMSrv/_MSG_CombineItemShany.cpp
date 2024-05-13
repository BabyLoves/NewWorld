
#include "ProcessClientMessage.h"

void Exec_MSG_CombineItemShany(int conn, char* pMsg)
{
	MSG_CombineItem* m = (MSG_CombineItem*)pMsg;

	int Size = m->Size;

	if (Size > sizeof(MSG_CombineItem)) //CONTROLE DE SIZE
	{
		SendClientMessage(conn, "Impossível executar ação20, tente mais tarde. ");
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
			Combinelogsitem(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, "dup,Tentativa de Dup CombineShany");
			return;
		}

		if (invPos < 0 || invPos >= pMob[conn].MaxCarry)
		{
			RemoveTrade(conn);
			return;
		}

		if (memcmp(&pMob[conn].MOB.Carry[invPos], &m->Item[i], sizeof(STRUCT_ITEM)))
		{
			Combinelogsitem(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, "err,msg_Combineshany - item remove or changed.");
			SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 0);
			return;
		}
	}

	if (pMob[conn].extra.ClassMaster == MORTAL)
	{
		SendClientMessage(conn, "Necessário ser Arch!");
		SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 0);
		return;
	}
	int combine = GetMatchCombineShany(m->Item);

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

	Combinelogsitem(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, "*** Item combine shany. ***");


	int _rand = rand() % 115;
	if (_rand >= 100)
		_rand -= 15;

	if (_rand <= g_pShanyBase || LOCALSERVER)
	{
		if (_rand < 50)
		{
			
			STRUCT_ITEM Item;
			memset(&Item, 0, sizeof(STRUCT_ITEM));
			Item.sIndex = 633;
			PutItem(conn, &Item);
			SendClientMessage(conn, g_pMessageStringTable[_NN_Processing_Complete]);
			SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 1);
			/*snprintf(temp, sizeof(temp), "Jogador %s Teve sucesso ao Combinar Espiritual para Adicional", pMob[conn].MOB.MobName);

			SendSpkMsg(1, temp, TNColor::GreenYellow, true);*/
			SaveUser(conn, 0);
			return;

		}
		if (_rand >= 50 && _rand <= 65)
		{
			
			STRUCT_ITEM Item;
			memset(&Item, 0, sizeof(STRUCT_ITEM));
			Item.sIndex = 632;
			PutItem(conn, &Item);
			SendClientMessage(conn, g_pMessageStringTable[_NN_Processing_Complete]);
			SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 1);
			/*snprintf(temp, sizeof(temp), "Jogador %s Não Obteve Sucesso ao Combinar Espiritual", pMob[conn].MOB.MobName);
			SendNotice(temp);*/
			SaveUser(conn, 0);
			return;

		}
		if (_rand > 65 && _rand <= 80)
		{
			
			STRUCT_ITEM Item;
			memset(&Item, 0, sizeof(STRUCT_ITEM));
			Item.sIndex = 631;
			PutItem(conn, &Item);
			SendClientMessage(conn, g_pMessageStringTable[_NN_Processing_Complete]);
			SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 1);
			/*snprintf(temp, sizeof(temp), "Jogador %s Não Obteve Sucesso ao Combinar Espiritual", pMob[conn].MOB.MobName);
			SendNotice(temp);*/
			SaveUser(conn, 0);
			return;
		}
	}
	else
	{


		SendClientMessage(conn, g_pMessageStringTable[_NN_CombineFailed]);
		/*
		snprintf(temp, sizeof(temp), "Jogador %s Teve Falha ao Combinar Espiritual", pMob[conn].MOB.MobName);
		SendNotice(temp);*/
		Combinelogsitem(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, temp);

		SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 2);
		SaveUser(conn, 0);
		return;
	}
}