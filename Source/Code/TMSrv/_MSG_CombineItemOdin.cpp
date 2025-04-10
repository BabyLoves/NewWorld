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

void Exec_MSG_CombineItemOdin(int conn, char* pMsg)
{
	MSG_CombineItem* m = (MSG_CombineItem*)pMsg;

	int Size = m->Size;

	if (Size > sizeof(MSG_CombineItem)) //CONTROLE DE SIZE
	{
		SendClientMessage(conn, "Imposs�vel executar a��o19, tente mais tarde. ");
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
			Combinelogsitem(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, "dup,Tentativa de Dup CombineOdin");
			continue;
		}

		if (invPos < 0 || invPos >= pMob[conn].MaxCarry)
		{
			RemoveTrade(conn);
			return;
		}

		if (memcmp(&pMob[conn].MOB.Carry[invPos], &m->Item[i], sizeof(STRUCT_ITEM)))
		{
			Combinelogsitem(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, "err,msg_CombineOdin - item remove or changed.");
			SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 0);
			return;
		}
	}

	int combine = GetMatchCombineOdin(m->Item);

	if (combine == 2)
	{
		int sAgua = 0;
		int sTerra = 0;
		int sSol = 0;
		int sVento = 0;

		if (m->Item[3].sIndex == 5334 || m->Item[4].sIndex == 5334 || m->Item[5].sIndex == 5334 || m->Item[6].sIndex == 5334)
			sAgua = 1;

		if (m->Item[3].sIndex == 5335 || m->Item[4].sIndex == 5335 || m->Item[5].sIndex == 5335 || m->Item[6].sIndex == 5335)
			sTerra = 1;

		if (m->Item[3].sIndex == 5336 || m->Item[4].sIndex == 5336 || m->Item[5].sIndex == 5336 || m->Item[6].sIndex == 5336)
			sSol = 1;

		if (m->Item[3].sIndex == 5337 || m->Item[4].sIndex == 5337 || m->Item[5].sIndex == 5337 || m->Item[6].sIndex == 5337)
			sVento = 1;

		if ((sAgua && (sTerra == 0 || sSol == 0 || sVento == 0)) || (sTerra && (sAgua == 0 || sSol == 0 || sVento == 0)) || (sSol && (sAgua == 0 || sTerra == 0 || sVento == 0)) || (sVento && (sAgua == 0 || sTerra == 0 || sSol == 0)))
		{
			SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 0);
			SaveUser(conn, 0);
			return;
		}
	}

	if (combine == 2 && (BASE_GetItemSanc(&m->Item[2]) >= REF_15 || BASE_GetItemAbility(&m->Item[2], EF_MOBTYPE) == 3))
	{
		SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 0);
		SaveUser(conn, 0);
		return;
	}

	if (combine == 4 && (pMob[conn].MOB.CurrentScore.Level != 39 || pMob[conn].extra.QuestInfo.Celestial.Lv40 == 1 || pMob[conn].extra.ClassMaster != CELESTIAL))
	{
		SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 0);
		SaveUser(conn, 0);
		return;
	}

	if (combine == 11 && (pMob[conn].extra.ClassMaster == MORTAL || pMob[conn].extra.ClassMaster == ARCH || BASE_GetItemSanc(&pMob[conn].MOB.Equip[15]) >= 9))
	{
		SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 0);
		SaveUser(conn, 0);
		return;
	}


	for (int i = 0; i < MAX_COMBINE; i++)
	{
		if (m->Item[i].sIndex == 0)
			continue;

		memset(&pMob[conn].MOB.Carry[m->InvenPos[i]], 0, sizeof(STRUCT_ITEM));
		SendItem(conn, ITEM_PLACE_CARRY, m->InvenPos[i], &pMob[conn].MOB.Carry[m->InvenPos[i]]);
	}

	//ItemLog("*** Item combine odin. ***", pUser[conn].AccountName, pUser[conn].IP);

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

	//srand(time(NULL) / 5 * (rand() % 500) * 5);//Garante valores realmente aleatorio
	srand(time(NULL) / 5 * (rand() % 500) * 5);//Garante valores realmente aleatorio
	int _rand = rand() % 199;;
	if (_rand > 100)
	{
		_rand = _rand - 99;
	}

	if (combine == 0)//Composi��o de Sets ??????
	{
		SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 0);
		return;

		//srand(time(NULL) / 5 * (rand() % 500) * 5);//Garante valores realmente aleatorio
		//if (_rand <= 50 || LOCALSERVER)

		//{

		//	memcpy(&pMob[conn].MOB.Carry[m->InvenPos[1]], &m->Item[1], sizeof(STRUCT_ITEM));

		//	pMob[conn].MOB.Carry[m->InvenPos[1]].sIndex = g_pItemList[m->Item[0].sIndex].Extra;//Usa o n�mero referente ao Extra na itemlist para definir o item a ser entregue:
		//	//Exemplo :1902,Eithna_selado,2892.1,0.0.0.0.0,42,270000,1,3626,0,EF_CLASS,255,EF_GRID,0,EF_ITEMLEVEL,5 >> 3626 � o item a ser entregue caso use Eithna Selado
		//	BASE_SetItemSanc(&pMob[conn].MOB.Carry[m->InvenPos[1]], 0, 0);

		//	char tt[256];

		//	SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 1);

		//	sprintf_s(temp, "%s ", pUser[conn].AccountName);
		//	BASE_GetItemCode(&pMob[conn].MOB.Carry[m->InvenPos[1]], tt);
		//	strcat(temp, tt);

		//	Combinelogsitem(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, temp);
		//	sprintf_s(temp, "Jogador [%s] obteve sucesso na composi��o do Item [%s]", pMob[conn].MOB.MobName, g_pItemList[pMob[conn].MOB.Carry[m->InvenPos[1]].sIndex].Name);
		//	Combinelogsitem(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, temp);

		//	SendItem(conn, ITEM_PLACE_CARRY, m->InvenPos[1], &pMob[conn].MOB.Carry[m->InvenPos[1]]);

		//	SendClientMessage(conn, "Obteve Sucesso na Composi��o");

		//	SaveUser(conn, 0);
		//	return;
		//}
		//else
		//{
		//	memcpy(&pMob[conn].MOB.Carry[m->InvenPos[1]], &m->Item[1], sizeof(STRUCT_ITEM));
		//	SendItem(conn, ITEM_PLACE_CARRY, m->InvenPos[1], &pMob[conn].MOB.Carry[m->InvenPos[1]]);

		//	SendClientMessage(conn, "Falha ao Combinar");

		//	sprintf_s(temp, "Jogador [%s] falhou na composi��o do Item [%s]", pMob[conn].MOB.MobName, g_pItemList[pMob[conn].MOB.Carry[m->InvenPos[1]].sIndex].Name);
		//	Combinelogsitem(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, temp);

		//	SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 2);
		//	SaveUser(conn, 0);
		//	return;
		//}
	}

	else if (combine == 1)//Composi��o de armas
	{

		srand(time(NULL) / 5 * (rand() % 500) * 5);//Garante valores realmente aleatorio
		int _chance_r = (g_pOdinRate[combine] + rand() % 5);
		if (_rand <= 50 || LOCALSERVER)

		{

			memcpy(&pMob[conn].MOB.Carry[m->InvenPos[1]], &m->Item[1], sizeof(STRUCT_ITEM));

			pMob[conn].MOB.Carry[m->InvenPos[1]].sIndex = g_pItemList[m->Item[0].sIndex].Extra;
			BASE_SetItemSanc(&pMob[conn].MOB.Carry[m->InvenPos[1]], 0, 0);

			char tt[256];

			SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 1);

			printf(temp, "%s ", pUser[conn].AccountName);
			BASE_GetItemCode(&pMob[conn].MOB.Carry[m->InvenPos[1]], tt);
			strcat(temp, tt);

			SendClientMessage(conn, "Sucesso na composi��o");

			Combinelogsitem(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, temp);
			sprintf_s(temp, "Jogador [%s] obteve sucesso na composi��o do Item [%s]", pMob[conn].MOB.MobName, g_pItemList[pMob[conn].MOB.Carry[m->InvenPos[1]].sIndex].Name);
			Combinelogsitem(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, temp);

			SendItem(conn, ITEM_PLACE_CARRY, m->InvenPos[1], &pMob[conn].MOB.Carry[m->InvenPos[1]]);
			SaveUser(conn, 0);
			return;
		}
		else
		{
			memcpy(&pMob[conn].MOB.Carry[m->InvenPos[1]], &m->Item[1], sizeof(STRUCT_ITEM));
			SendItem(conn, ITEM_PLACE_CARRY, m->InvenPos[1], &pMob[conn].MOB.Carry[m->InvenPos[1]]);

			SendClientMessage(conn, "Falha na composi��o");

			SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 2);

			sprintf_s(temp, "Jogador [%s] falhou na composi��o do Item [%s]", pMob[conn].MOB.MobName, g_pItemList[pMob[conn].MOB.Carry[m->InvenPos[1]].sIndex].Name);
			Combinelogsitem(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, temp);
			SaveUser(conn, 0);
			return;
		}
	}

	/*
	if (combine == 1)//Item celestial
	{
		if (_rand <= 35)
		{
			memcpy(&pMob[conn].MOB.Carry[m->InvenPos[1]], &m->Item[1], sizeof(STRUCT_ITEM));

			pMob[conn].MOB.Carry[m->InvenPos[1]].sIndex = g_pItemList[m->Item[0].sIndex].Extra;
			BASE_SetItemSanc(&pMob[conn].MOB.Carry[m->InvenPos[1]], 0, 0);

			char tt[256];

			sprintf(temp, "Combina��o Bem Sucedida [ %s / 35 ]", _rand);
			SendClientMessage(conn, temp);

			SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 1);

			sprintf(temp, "%s ", pUser[conn].AccountName);
			BASE_GetItemCode(&pMob[conn].MOB.Carry[m->InvenPos[1]], tt);
			strcat(temp, tt);

			ItemLog(temp, "*** Combine odin sucess ***", pUser[conn].MacAddress);
			SendItem(conn, ITEM_PLACE_CARRY, m->InvenPos[1], &pMob[conn].MOB.Carry[m->InvenPos[1]]);

			return;
		}
		else
		{
			//memcpy(&pMob[conn].MOB.Carry[m->InvenPos[1]], &m->Item[1], sizeof(STRUCT_ITEM));
			SendItem(conn, ITEM_PLACE_CARRY, m->InvenPos[1], &pMob[conn].MOB.Carry[m->InvenPos[1]]);

			sprintf(temp, "Combina��o Bem Sucedida [ %s / 35 ]", _rand);
			SendClientMessage(conn, temp);

			SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 2);
			ItemLog("*** Combine odin fail ***", pUser[conn].AccountName, pUser[conn].MacAddress);

			return;
		}
	}*/

	else if (combine == 2)//Item +12+
	{
		int rate = 1;

		int protect = 0;

		for (int i = 0; i < MAX_COMBINE; i++)
		{
			if (m->Item[i].sIndex >= 5334 && m->Item[i].sIndex <= 5337)
				rate += g_pItemSancRate12[0];

			if (m->Item[i].sIndex == 4043)
				protect++;

			if (m->Item[i].sIndex == 3338 && BASE_GetItemSanc(&m->Item[i]) == 0)
				rate += g_pItemSancRate12[1];

			else if (m->Item[i].sIndex == 3338 && BASE_GetItemSanc(&m->Item[i]) == 1)
				rate += g_pItemSancRate12[2];

			else if (m->Item[i].sIndex == 3338 && BASE_GetItemSanc(&m->Item[i]) == 2)
				rate += g_pItemSancRate12[3];

			else if (m->Item[i].sIndex == 3338 && BASE_GetItemSanc(&m->Item[i]) == 3)
				rate += g_pItemSancRate12[4];

			else if (m->Item[i].sIndex == 3338 && BASE_GetItemSanc(&m->Item[i]) == 4)
				rate += g_pItemSancRate12[5];

			else if (m->Item[i].sIndex == 3338 && BASE_GetItemSanc(&m->Item[i]) == 5)
				rate += g_pItemSancRate12[6];

			else if (m->Item[i].sIndex == 3338 && BASE_GetItemSanc(&m->Item[i]) == 6)
				rate += g_pItemSancRate12[7];

			else if (m->Item[i].sIndex == 3338 && BASE_GetItemSanc(&m->Item[i]) == 7)
				rate += g_pItemSancRate12[8];

			else if (m->Item[i].sIndex == 3338 && BASE_GetItemSanc(&m->Item[i]) == 8)
				rate += g_pItemSancRate12[9];

			else if (m->Item[i].sIndex == 3338 && BASE_GetItemSanc(&m->Item[i]) == 9)
				rate += g_pItemSancRate12[10];
		}

		if (BASE_GetItemSanc(&m->Item[2]) <= REF_10 || BASE_GetItemSanc(&m->Item[2]) >= REF_15)
		{
			SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 0);
			SaveUser(conn, 0);
			return;
		}

		if (BASE_GetItemSanc(&m->Item[2]) == REF_12)
			rate -= g_pItemSancRate12Minus[0];

		else if (BASE_GetItemSanc(&m->Item[2]) == REF_13)
			rate -= g_pItemSancRate12Minus[1];

		else if (BASE_GetItemSanc(&m->Item[2]) == REF_14)
			rate -= g_pItemSancRate12Minus[2];

		else if (BASE_GetItemSanc(&m->Item[2]) == REF_15)
			rate -= g_pItemSancRate12Minus[3];

		if (rate >= _rand || LOCALSERVER)
		{
			memcpy(&pMob[conn].MOB.Carry[m->InvenPos[2]], &m->Item[2], sizeof(STRUCT_ITEM));

			int sanc = BASE_GetItemSanc(&m->Item[2]);
			int gem = BASE_GetItemGem(&m->Item[2]);

			int NewSanc = 0;

			if (sanc == REF_11)
			{
				BASE_SetItemSanc(&pMob[conn].MOB.Carry[m->InvenPos[2]], 12, gem);
				NewSanc = 12;
			}
			else if (sanc == REF_12)
			{
				BASE_SetItemSanc(&pMob[conn].MOB.Carry[m->InvenPos[2]], 13, gem);
				NewSanc = 13;
			}
			else if (sanc == REF_13)
			{
				BASE_SetItemSanc(&pMob[conn].MOB.Carry[m->InvenPos[2]], 14, gem);
				NewSanc = 14;
			}
			else if (sanc == REF_14)
			{
				BASE_SetItemSanc(&pMob[conn].MOB.Carry[m->InvenPos[2]], 15, gem);
				NewSanc = 15;
			}
			char tt[256];

			SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 1);


			BASE_GetItemCode(&pMob[conn].MOB.Carry[m->InvenPos[2]], tt);
			strcat(temp, tt);

			SendClientMessage(conn, "Voc� obteve sucesso na refina��o");

			SendItem(conn, ITEM_PLACE_CARRY, m->InvenPos[2], &pMob[conn].MOB.Carry[m->InvenPos[2]]);


			Combinelogsitem(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, temp);
			sprintf_s(temp, "Jogador [%s] obteve sucesso na composi��o do Item [%s +%d]", pMob[conn].MOB.MobName, g_pItemList[pMob[conn].MOB.Carry[m->InvenPos[2]].sIndex].Name, NewSanc);
			Combinelogsitem(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, temp);
			return;
		}
		else
		{
			if (rate <= 9 && BASE_GetItemAbility(&m->Item[2], EF_MOBTYPE) == 1)
			{//Possivel quebra

				//Escudos
				if (g_pItemList[m->Item[2].sIndex].nPos == 128)
					goto Label_VoltaRef;

				if (rate <= 9)//Tentou com secretas
				{
					if (rand() % 1 == 0)
					{
						//corre��o extra��o entregue pelo odin
						if (protect == 2)
						{
							memcpy(&pMob[conn].MOB.Carry[m->InvenPos[2]], &m->Item[2], sizeof(STRUCT_ITEM));

							pMob[conn].MOB.Carry[m->InvenPos[2]].sIndex = 3021;

							pMob[conn].MOB.Carry[m->InvenPos[2]].stEffect[0].cValue = 10;

							if (g_pItemList[m->Item[2].sIndex].nPos == 4)
								pMob[conn].MOB.Carry[m->InvenPos[2]].sIndex++;

							else if (g_pItemList[m->Item[2].sIndex].nPos == 8)
								pMob[conn].MOB.Carry[m->InvenPos[2]].sIndex += 2;

							else if (g_pItemList[m->Item[2].sIndex].nPos == 16)
								pMob[conn].MOB.Carry[m->InvenPos[2]].sIndex += 3;

							else if (g_pItemList[m->Item[2].sIndex].nPos == 32)
								pMob[conn].MOB.Carry[m->InvenPos[2]].sIndex += 4;

							else if (g_pItemList[m->Item[2].sIndex].nPos == 64)
								pMob[conn].MOB.Carry[m->InvenPos[2]].sIndex += 5;

							else
							{
								pMob[conn].MOB.Carry[m->InvenPos[2]].sIndex = 3026;
								pMob[conn].MOB.Carry[m->InvenPos[2]].stEffect[0].cValue = 11;
							}



							SendItem(conn, ITEM_PLACE_CARRY, m->InvenPos[2], &pMob[conn].MOB.Carry[m->InvenPos[2]]);
						}
						else
						{
							memset(&pMob[conn].MOB.Carry[m->InvenPos[2]], 0, sizeof(STRUCT_ITEM));
							SendItem(conn, ITEM_PLACE_CARRY, m->InvenPos[2], &pMob[conn].MOB.Carry[m->InvenPos[2]]);
						}
					}
					else
						goto Label_VoltaRef;
				}
			}
			else
			{
			Label_VoltaRef:
				memcpy(&pMob[conn].MOB.Carry[m->InvenPos[2]], &m->Item[2], sizeof(STRUCT_ITEM));

				int sanc = BASE_GetItemSanc(&m->Item[2]);
				int gem = BASE_GetItemGem(&m->Item[2]);

				int Extra = BASE_GetItemAbility(&m->Item[2], EF_ITEMLEVEL); //TRAVAR ITEMS C

				if (Extra <= 4)
				{
					SendClientMessage(conn, "Items de Rank B ou Inferior Proibidos de fazer +12"); //TRAVAR ITEMS C
					SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 0);
					SendEtc(conn);
					SendCarry(conn);
					return;
				}

				if (sanc == REF_11)
					BASE_SetItemSanc(&pMob[conn].MOB.Carry[m->InvenPos[2]], 10, gem);

				else if (sanc == REF_12)
					BASE_SetItemSanc(&pMob[conn].MOB.Carry[m->InvenPos[2]], 11, gem);

				else if (sanc == REF_13)
					BASE_SetItemSanc(&pMob[conn].MOB.Carry[m->InvenPos[2]], 12, gem);

				else if (sanc == REF_14)
					BASE_SetItemSanc(&pMob[conn].MOB.Carry[m->InvenPos[2]], 13, gem);

				SendItem(conn, ITEM_PLACE_CARRY, m->InvenPos[2], &pMob[conn].MOB.Carry[m->InvenPos[2]]);
			}
			SendClientMessage(conn, g_pMessageStringTable[_NN_CombineFailed]);

			SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 2);

			int lsanc = BASE_GetItemSanc(&m->Item[2]);
			sprintf_s(temp, "Jogador [%s] obteve FALHA na composi��o do Item. Item: %s+%d Chance: [%d/%d]", pMob[conn].MOB.MobName, g_pItemList[m->Item[0].sIndex].Name, lsanc, _rand, combine);
			Combinelogsitem(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, temp);
			SaveUser(conn, 0);
			return;
		}

	}

	else if (combine == 3)//Pista de runas
	{
		/*if (_rand <= g_pOdinRate[combine] || LOCALSERVER)
		{*/
		pMob[conn].MOB.Carry[m->InvenPos[0]].sIndex = 5134;

		char tt[256];

		SendClientMessage(conn, g_pMessageStringTable[_NN_Processing_Complete]);

		SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 1);

		sprintf_s(temp, "%s ", pUser[conn].AccountName);
		BASE_GetItemCode(&pMob[conn].MOB.Carry[m->InvenPos[0]], tt);
		strcat(temp, tt);
		Combinelogsitem(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, temp);

		//ItemLog(temp, "*** Combine odin sucess ***", pUser[conn].MacAddress);
		SendItem(conn, ITEM_PLACE_CARRY, m->InvenPos[0], &pMob[conn].MOB.Carry[m->InvenPos[0]]);
		SaveUser(conn, 0);
		return;
		//}
		/*else
		{
			sprintf(temp, "%s - Pista de Runas", g_pMessageStringTable[_NN_CombineFailed]);
			SendClientMessage(conn, temp);

			SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 2);
			ItemLog("*** Combine odin fail ***", pUser[conn].AccountName, pUser[conn].MacAddress);
			SaveUser(conn, 0);
			return;
		}*/
	}

	else if (combine == 4)//Destrave Lv40
	{
		if (_rand <= g_pOdinRate[combine] || LOCALSERVER)
		{
			SendClientMessage(conn, g_pMessageStringTable[_NN_Processing_Complete]);

			SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 1);

			sprintf(temp, "destrave,mobname:%s lv:40", pMob[conn].MOB.MobName);
			Combinelogsitem(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, temp);

			pMob[conn].extra.QuestInfo.Celestial.Lv40 = 1;
			SaveUser(conn, 0);
			return;
		}
		else
		{
			SendClientMessage(conn, strFmt("%s - Destrave Lv40", g_pMessageStringTable[_NN_CombineFailed]));
			Combinelogsitem(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, strFmt("%s - Destrave Lv40", g_pMessageStringTable[_NN_CombineFailed]));
			SaveUser(conn, 0);
			return;
		}
	}

	else if (combine == 5)//Pedra da f�ria
	{
		if (_rand <= g_pOdinRate[combine] || LOCALSERVER)
		{
			pMob[conn].MOB.Carry[m->InvenPos[0]].sIndex = 3020;

			char tt[512];

			SendClientMessage(conn, g_pMessageStringTable[_NN_Processing_Complete]);

			SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 1);

			sprintf_s(temp, "%s ", pUser[conn].AccountName);
			BASE_GetItemCode(&pMob[conn].MOB.Carry[m->InvenPos[0]], tt);
			strcat(temp, tt);

			Combinelogsitem(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, temp);
			SendItem(conn, ITEM_PLACE_CARRY, m->InvenPos[0], &pMob[conn].MOB.Carry[m->InvenPos[0]]);
			SaveUser(conn, 0);
			return;
		}
		else
		{
			SendClientMessage(conn, strFmt("%s - Pedra da Furia", g_pMessageStringTable[_NN_CombineFailed]));

			SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 2);
			Combinelogsitem(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, strFmt("%s - Pedra da Furia", g_pMessageStringTable[_NN_CombineFailed]));
			SaveUser(conn, 0);
			return;
		}
	}

	else if (combine >= 6 && combine <= 9)//Pedra da agua - terra - sol - vento
	{
		if (_rand <= g_pOdinRate[combine] || LOCALSERVER)
		{
			pMob[conn].MOB.Carry[m->InvenPos[0]].sIndex = 5334 + (combine - 6);

			char tt[512];

			SendClientMessage(conn, g_pMessageStringTable[_NN_Processing_Complete]);

			SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 1);

			sprintf_s(temp, "%s ", pUser[conn].AccountName);
			BASE_GetItemCode(&pMob[conn].MOB.Carry[m->InvenPos[0]], tt);
			strcat(temp, tt);

			Combinelogsitem(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, temp);
			SendItem(conn, ITEM_PLACE_CARRY, m->InvenPos[0], &pMob[conn].MOB.Carry[m->InvenPos[0]]);
			SaveUser(conn, 0);
			return;
		}
		else
		{
			SendClientMessage(conn, strFmt("%s - Secretas", g_pMessageStringTable[_NN_CombineFailed]));

			SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 2);
			Combinelogsitem(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, strFmt("%s - Secretas", g_pMessageStringTable[_NN_CombineFailed]));
			SaveUser(conn, 0);
			return;
		}
	}

	else if (combine == 10)//Semente de cristal
	{
		if (_rand <= g_pOdinRate[combine] || LOCALSERVER)
		{
			pMob[conn].MOB.Carry[m->InvenPos[0]].sIndex = 4032;

			char tt[512];

			SendClientMessage(conn, g_pMessageStringTable[_NN_Processing_Complete]);

			SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 1);

			sprintf_s(temp, "%s ", pUser[conn].AccountName);
			BASE_GetItemCode(&pMob[conn].MOB.Carry[m->InvenPos[0]], tt);
			strcat(temp, tt);

			Combinelogsitem(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, temp);
			SendItem(conn, ITEM_PLACE_CARRY, m->InvenPos[0], &pMob[conn].MOB.Carry[m->InvenPos[0]]);
			SaveUser(conn, 0);
			return;
		}
		else
		{
			SendClientMessage(conn, strFmt("%s - Semente de Cristal", g_pMessageStringTable[_NN_CombineFailed]));

			SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 2);
			Combinelogsitem(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, strFmt("%s - Semente de Cristal", g_pMessageStringTable[_NN_CombineFailed]));
			SaveUser(conn, 0);
			return;
		}
	}

	else if (combine == 11)//Capa celestial
	{
		if (_rand <= g_pOdinRate[combine] || LOCALSERVER)
		{
			int sanc = BASE_GetItemSanc(&pMob[conn].MOB.Equip[15]);

			if (sanc == 0)
			{
				if (pMob[conn].MOB.Equip[15].stEffect[0].cEffect && pMob[conn].MOB.Equip[15].stEffect[0].cEffect != 43 && (pMob[conn].MOB.Equip[15].stEffect[0].cEffect && pMob[conn].MOB.Equip[15].stEffect[0].cEffect < 116 || pMob[conn].MOB.Equip[15].stEffect[0].cEffect && pMob[conn].MOB.Equip[15].stEffect[0].cEffect > 125))
				{
					if (pMob[conn].MOB.Equip[15].stEffect[1].cEffect && pMob[conn].MOB.Equip[15].stEffect[1].cEffect != 43 && (pMob[conn].MOB.Equip[15].stEffect[1].cEffect && pMob[conn].MOB.Equip[15].stEffect[1].cEffect < 116 || pMob[conn].MOB.Equip[15].stEffect[1].cEffect && pMob[conn].MOB.Equip[15].stEffect[1].cEffect > 125))
					{
						if (pMob[conn].MOB.Equip[15].stEffect[2].cEffect && pMob[conn].MOB.Equip[15].stEffect[2].cEffect != 43 && (pMob[conn].MOB.Equip[15].stEffect[2].cEffect && pMob[conn].MOB.Equip[15].stEffect[2].cEffect < 116 || pMob[conn].MOB.Equip[15].stEffect[2].cEffect && pMob[conn].MOB.Equip[15].stEffect[2].cEffect > 125))
						{
							SendClientMessage(conn, g_pMessageStringTable[_NN_Cant_Refine_More]);
							return;
						}
						pMob[conn].MOB.Equip[15].stEffect[2].cEffect = 43;
						pMob[conn].MOB.Equip[15].stEffect[2].cValue = 0;
					}
					else
					{
						pMob[conn].MOB.Equip[15].stEffect[1].cEffect = 43;
						pMob[conn].MOB.Equip[15].stEffect[1].cValue = 0;
					}
				}
				else
				{
					pMob[conn].MOB.Equip[15].stEffect[0].cEffect = 43;
					pMob[conn].MOB.Equip[15].stEffect[0].cValue = 0;
				}
			}

			BASE_SetItemSanc(&pMob[conn].MOB.Equip[15], sanc + 1, 0);

			char tt[256];

			SendClientMessage(conn, g_pMessageStringTable[_NN_Processing_Complete]);

			SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 1);

			sprintf_s(temp, "%s ", pUser[conn].AccountName);
			BASE_GetItemCode(&pMob[conn].MOB.Carry[m->InvenPos[0]], tt);
			strcat(temp, tt);

			Combinelogsitem(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, temp);
			SendItem(conn, ITEM_PLACE_EQUIP, 15, &pMob[conn].MOB.Equip[15]);
			SaveUser(conn, 0);
			return;
		}
		else
		{
			SendClientMessage(conn, strFmt("%s - Capa Celestial", g_pMessageStringTable[_NN_CombineFailed]));

			SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 2);
			Combinelogsitem(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, strFmt("%s - Capa Celestial", g_pMessageStringTable[_NN_CombineFailed]));
			SaveUser(conn, 0);
			return;
		}
	}

	else
	{
		SendClientMessage(conn, strFmt("%s - Nenhuma Fun��o", g_pMessageStringTable[_NN_CombineFailed]));

		SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 2);
		Combinelogsitem(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, strFmt("%s - Nenhuma Fun��o", g_pMessageStringTable[_NN_CombineFailed]));
		SaveUser(conn, 0);
		return;
	}
}