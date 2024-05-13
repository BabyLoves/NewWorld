#include "ProcessClientMessage.h"


void Exec_MSG_CombineDedekinto(int conn, char *pMsg)
{
	MSG_CombineItem *m = (MSG_CombineItem*)pMsg;

	int Size = m->Size;

	if (Size > sizeof(MSG_CombineItem)) //CONTROLE DE SIZE
	{
		SendClientMessage(conn, "Impossível executar ação15, tente mais tarde. ");
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
			Combinelogsitem(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, "dup,Tentativa de Dup DedeKinto");
			return;
		}

		if (invPos < 0 || invPos >= pMob[conn].MaxCarry)
		{
			RemoveTrade(conn);
			return;
		}

		if (memcmp(&pMob[conn].MOB.Carry[invPos], &m->Item[i], sizeof(STRUCT_ITEM)))
		{
			Combinelogsitem(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, "err,msg_CombineDedeKinto - item remove or changed.");
			SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 0);
			return;
		}
	}

	int combine = GetMatchCombineDedekinto(m->Item);

	if (combine == 1 && (pMob[conn].MOB.Exp < 8200000000 || pMob[conn].extra.ClassMaster == MORTAL || pMob[conn].extra.ClassMaster == ARCH || pMob[conn].MOB.CurrentScore.Level <= 238 || (!pMob[conn].extra.ClassMaster >= HARDCORE && (pMob[conn].MOB.Equip[1].sIndex >= 3500 && pMob[conn].MOB.Equip[1].sIndex <= 3507))))
	{	 //Pedra Amunra
		SendClientMessage(conn, "Nescessário ser Celestial Level 240");
		SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 0);
		return;
	}

	if (combine == 2 && (pMob[conn].extra.ClassMaster == MORTAL || pMob[conn].extra.ClassMaster == ARCH || pMob[conn].MOB.CurrentScore.Level <= 238))
	{	 //Proteção Divina
		SendClientMessage(conn, "Nescessário ser Celestial Level 240");
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

	//ItemLog("*** Item combine ehre. ***", pUser[conn].AccountName, pUser[conn].IP);

	for (int i = 0; i < MAX_COMBINE; i++)
	{
		if (m->Item[i].sIndex)
		{
			char itemlog[2048];
									 
			BASE_GetItemCode(&m->Item[i], itemlog);
									 
			strcat(temp, itemlog);
		}
	}
	//ItemLog(temp, pUser[conn].AccountName, pUser[conn].IP);
	//ItemLog("*** ------------------- ***", pUser[conn].AccountName, pUser[conn].IP);

	int _rand = rand() % 115;
	if (_rand >= 100)
		_rand -= 15;

	int rate = g_pEhreRate[combine];
	
	if (_rand <= rate || LOCALSERVER)
	{
		if (combine == 1)
		{
			if (pMob[conn].extra.ClassMaster >= CELESTIAL && pMob[conn].extra.ClassMaster <= SCELESTIAL)
			{
				pMob[conn].MOB.Carry[m->InvenPos[0]].sIndex = 3464;

				char tt[512];

				SendClientMessage(conn, g_pMessageStringTable[_NN_Processing_Complete]);

				SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 1);

				sprintf_s(temp, "%s ", pUser[conn].AccountName);
				BASE_GetItemCode(&pMob[conn].MOB.Carry[m->InvenPos[0]], tt);

				pMob[conn].MOB.BaseScore.Level = 0;
				pMob[conn].MOB.Exp = 0;

				pMob[conn].MOB.BaseScore.Str = BaseSIDCHM[pMob[conn].MOB.Class][0];
				pMob[conn].MOB.BaseScore.Int = BaseSIDCHM[pMob[conn].MOB.Class][1];
				pMob[conn].MOB.BaseScore.Dex = BaseSIDCHM[pMob[conn].MOB.Class][2];
				pMob[conn].MOB.BaseScore.Con = BaseSIDCHM[pMob[conn].MOB.Class][3];

				pMob[conn].MOB.BaseScore.Special[0] = 0;
				pMob[conn].MOB.BaseScore.Special[1] = 0;
				pMob[conn].MOB.BaseScore.Special[2] = 0;
				pMob[conn].MOB.BaseScore.Special[3] = 0;

				pMob[conn].MOB.BaseScore.Ac = 1004;
				pMob[conn].MOB.BaseScore.Damage = 400;
				pMob[conn].MOB.BaseScore.Hp = BaseSIDCHM[pMob[conn].MOB.Class][4];
				pMob[conn].MOB.BaseScore.MaxHp = BaseSIDCHM[pMob[conn].MOB.Class][4];
				pMob[conn].MOB.BaseScore.Mp = BaseSIDCHM[pMob[conn].MOB.Class][5];
				pMob[conn].MOB.BaseScore.MaxMp = BaseSIDCHM[pMob[conn].MOB.Class][5];

				pMob[conn].MOB.SpecialBonus = 855;

				SendEtc(conn);

				strcat(temp, tt);

				for (int i = 1; i < MAX_COMBINE; i++)
				{
					if (m->Item[i].sIndex == 0)
						continue;

					memset(&pMob[conn].MOB.Carry[m->InvenPos[i]], 0, sizeof(STRUCT_ITEM));
					SendItem(conn, ITEM_PLACE_CARRY, m->InvenPos[i], &pMob[conn].MOB.Carry[m->InvenPos[i]]);
				}

				/*ItemLog(temp, "*** Combine odin sucess ***", pUser[conn].MacAddress);*/
				SendItem(conn, ITEM_PLACE_CARRY, m->InvenPos[0], &pMob[conn].MOB.Carry[m->InvenPos[0]]);

				CharLogOut(conn);

				SendClientSignalParm(conn, ESCENE_FIELD, _MSG_SendArchEffect, pUser[conn].Slot);

				return;
			}

			else if (pMob[conn].extra.ClassMaster >= HARDCORE)
			{
				pMob[conn].MOB.Carry[m->InvenPos[0]].sIndex = 3464;

				char tt[512];

				SendClientMessage(conn, g_pMessageStringTable[_NN_Processing_Complete]);

				SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 1);

				sprintf_s(temp, "%s ", pUser[conn].AccountName);
				BASE_GetItemCode(&pMob[conn].MOB.Carry[m->InvenPos[0]], tt);

				pMob[conn].MOB.BaseScore.Level = 0;
				pMob[conn].MOB.Exp = 0;

				pMob[conn].MOB.BaseScore.Str = BaseSIDCHM[pMob[conn].MOB.Class][0];
				pMob[conn].MOB.BaseScore.Int = BaseSIDCHM[pMob[conn].MOB.Class][1];
				pMob[conn].MOB.BaseScore.Dex = BaseSIDCHM[pMob[conn].MOB.Class][2];
				pMob[conn].MOB.BaseScore.Con = BaseSIDCHM[pMob[conn].MOB.Class][3];

				pMob[conn].MOB.BaseScore.Special[0] = 0;
				pMob[conn].MOB.BaseScore.Special[1] = 0;
				pMob[conn].MOB.BaseScore.Special[2] = 0;
				pMob[conn].MOB.BaseScore.Special[3] = 0;

				pMob[conn].MOB.BaseScore.Ac = 954;
				pMob[conn].MOB.BaseScore.Damage = 800;
				pMob[conn].MOB.BaseScore.Hp = BaseSIDCHM[pMob[conn].MOB.Class][4];
				pMob[conn].MOB.BaseScore.MaxHp = BaseSIDCHM[pMob[conn].MOB.Class][4];
				pMob[conn].MOB.BaseScore.Mp = BaseSIDCHM[pMob[conn].MOB.Class][5];
				pMob[conn].MOB.BaseScore.MaxMp = BaseSIDCHM[pMob[conn].MOB.Class][5];

				pMob[conn].MOB.SpecialBonus = 855;

				SendEtc(conn);

				strcat(temp, tt);

				for (int i = 1; i < MAX_COMBINE; i++)
				{
					if (m->Item[i].sIndex == 0)
						continue;

					memset(&pMob[conn].MOB.Carry[m->InvenPos[i]], 0, sizeof(STRUCT_ITEM));
					SendItem(conn, ITEM_PLACE_CARRY, m->InvenPos[i], &pMob[conn].MOB.Carry[m->InvenPos[i]]);
				}

				//ItemLog(temp, "*** Combine odin sucess ***", pUser[conn].IP);
				SendItem(conn, ITEM_PLACE_CARRY, m->InvenPos[0], &pMob[conn].MOB.Carry[m->InvenPos[0]]);

				CharLogOut(conn);

				SendClientSignalParm(conn, ESCENE_FIELD, _MSG_SendArchEffect, pUser[conn].Slot);

				return;
			}
		}

		else if (combine == 2)
		{
			pMob[conn].MOB.Carry[m->InvenPos[0]].sIndex = 679;

			char tt[512];

			SendClientMessage(conn, g_pMessageStringTable[_NN_Processing_Complete]);

			SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 1);

			sprintf_s(temp, "%s ", pUser[conn].AccountName);
			BASE_GetItemCode(&pMob[conn].MOB.Carry[m->InvenPos[0]], tt);

			strcat(temp, tt);

			for (int i = 1; i < MAX_COMBINE; i++)
			{
				if (m->Item[i].sIndex == 0)
					continue;

				memset(&pMob[conn].MOB.Carry[m->InvenPos[i]], 0, sizeof(STRUCT_ITEM));
				SendItem(conn, ITEM_PLACE_CARRY, m->InvenPos[i], &pMob[conn].MOB.Carry[m->InvenPos[i]]);
			}

			//ItemLog(temp, "*** Combine odin sucess ***", pUser[conn].IP);
			SendItem(conn, ITEM_PLACE_CARRY, m->InvenPos[0], &pMob[conn].MOB.Carry[m->InvenPos[0]]);

			return;
		}

		char tt[256];

		SendClientMessage(conn, g_pMessageStringTable[_NN_Processing_Complete]);

		SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 1);

		strcat(temp, tt);

		//ItemLog(temp, "-- FALHOU! --", pUser[conn].IP);

		return;
	}
	else
	{

		SendClientMessage(conn, strFmt("%s(%d/%d)", g_pMessageStringTable[_NN_CombineFailed], _rand, rate));

		SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 2);
		//ItemLog("-- FALHOU! --", pUser[conn].AccountName, pUser[conn].IP);

		return;
	}
}