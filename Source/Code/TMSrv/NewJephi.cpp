#pragma once

#include "ProcessClientMessage.h"
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <random>
#include <ctime>
#include "SendFunc.h"
#include "Functions.h"


void Jephi(int conn, char* pMsg) {

	if (conn <= 0 || conn >= MAX_USER)
		return;

	if (pUser[conn].Mode != USER_PLAY)
		return;

	if (pUser[conn].cSock.Sock == 0)
		return;

	MSG_SendJephi* m = (MSG_SendJephi*)pMsg;

	int Size = m->Size;

	if (Size > sizeof(MSG_SendJephi)) //CONTROLE DE SIZE
	{
		SendClientMessage(conn, "Impossível executar ação, tente mais tarde.");
		return;
	}

	if (m->Qnt <= 0 || m->Qnt > 120)
		return;

	if (m->Item < 0 || m->Item >= MAX_ITEMLIST)
		return;

	int itemIndex = m->Item;
	int Quantidade = m->Qnt;

	if (itemIndex == 0)
		itemIndex = 413;

	if (itemIndex == 1)
		itemIndex = 412;

	//circulo divino
	if (itemIndex == 447 || itemIndex == 692)
	{
		int price = 0;
		if (pMob[conn].MOB.Equip[13].sIndex != 447 && pMob[conn].MOB.Equip[13].sIndex != 692) {
			SendClientMessage(conn, "Equipe o pedaço do círculo Divino!");
			return;
		}
		if (pMob[conn].MOB.Equip[13].sIndex == 447) {
			price = 1000000;
		}

		if (pMob[conn].MOB.Equip[13].sIndex == 692) {
			price = 5000000;
		}
		if (pMob[conn].MOB.Coin < price) {
			SendClientMessage(conn, "Você não possui gold suficiente!");
			return;
		}
		if (pMob[conn].MOB.Coin >= price)
		{
			if (price == 1000000)
			{
				pMob[conn].MOB.Coin -= 1000000;
				pMob[conn].MOB.Equip[13].sIndex = rand() % 3 + 448;
			}
			else
			{
				pMob[conn].MOB.Coin -= 5000000;
				pMob[conn].MOB.Equip[13].sIndex = rand() % 3 + 693;
			}

			SendItem(conn, ITEM_PLACE_EQUIP, 13, &pMob[conn].MOB.Equip[13]);
			SendEtc(conn);
			SendClientMessage(conn, g_pMessageStringTable[_NN_Processing_Complete]);
			SendScore(conn);
			return;
		}
	}

	//poeira de ori
	if (itemIndex == 412) {

		int Ori = 0;
		for (int i = 0; i < pMob[conn].MaxCarry; i++)
		{
			if (pMob[conn].MOB.Carry[i].sIndex == 419)
				Ori += pMob[conn].MOB.Carry[i].stEffect[0].cEffect == 61 ? pMob[conn].MOB.Carry[i].stEffect[0].cValue : 1;
		}

		int SlotId = 0;
		for (int i = 0; i < pMob[conn].MaxCarry; i++)
		{
			if (pMob[conn].MOB.Carry[i].sIndex == 0)
			{
				SlotId++;
			}
		}
		if (Ori < (Quantidade * 10)) {
			SendClientMessage(conn, "Restos Insuficientes");
			return;
		}

		if (pMob[conn].MOB.Coin > (Quantidade * 100000)) //100k
		{
			if (SlotId > 2)
			{
				RemoveItem(conn, 419, Quantidade * 10);
				pMob[conn].MOB.Coin -= (Quantidade * 100000); //100k

				STRUCT_ITEM item;
				memset(&item, 0, sizeof(STRUCT_ITEM));

				item.sIndex = 412;
				item.stEffect[0].cEffect = 61;
				item.stEffect[0].cValue = Quantidade;
				item.stEffect[1].cEffect = 0;
				item.stEffect[1].cValue = 0;
				item.stEffect[2].cEffect = 0;
				item.stEffect[2].cValue = 0;

				PutItem(conn, &item);
				SendCarry(conn);
				SendScore(conn);
				SendEtc(conn);
				SendClientMessage(conn, strFmt("Criou %d Poeiras de Ori", Quantidade));
				ItemLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, strFmt("Criou %d Poeiras de Ori", Quantidade));
				return;
			}
			else
			{
				SendClientMessage(conn, g_pMessageStringTable[_NN_You_Have_No_Space_To_Trade]);
				return;
			}
		}
		SendClientMessage(conn, "Gold Insuficiente");
		return;
	}

	//poeira de lac
	if (itemIndex == 413) {

		int lac = 0;
		for (int i = 0; i < pMob[conn].MaxCarry; i++)
		{
			if (pMob[conn].MOB.Carry[i].sIndex == 420)
				lac += pMob[conn].MOB.Carry[i].stEffect[0].cEffect == 61 ? pMob[conn].MOB.Carry[i].stEffect[0].cValue : 1;
		}

		int SlotId = 0;
		for (int i = 0; i < pMob[conn].MaxCarry; i++)
		{
			if (pMob[conn].MOB.Carry[i].sIndex == 0)
			{
				SlotId++;
			}
		}
		if (lac < (Quantidade * 10)) {
			SendClientMessage(conn, "Restos Insuficientes");
			return;
		}

		if (pMob[conn].MOB.Coin > (Quantidade * 250000)) //250k
		{
			if (SlotId > 2)
			{
				RemoveItem(conn, 420, Quantidade * 10);
				pMob[conn].MOB.Coin -= (Quantidade * 250000); //250k

				STRUCT_ITEM item;
				memset(&item, 0, sizeof(STRUCT_ITEM));

				item.sIndex = 413;
				item.stEffect[0].cEffect = 61;
				item.stEffect[0].cValue = Quantidade;
				item.stEffect[1].cEffect = 0;
				item.stEffect[1].cValue = 0;
				item.stEffect[2].cEffect = 0;
				item.stEffect[2].cValue = 0;

				PutItem(conn, &item);
				SendCarry(conn);
				SendScore(conn);
				SendEtc(conn);
				SendClientMessage(conn, strFmt("Criou %d Poeiras de Lac", Quantidade));
				ItemLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, strFmt("Criou %d Poeiras de Lac", Quantidade));
				return;
			}
			else
			{
				SendClientMessage(conn, g_pMessageStringTable[_NN_You_Have_No_Space_To_Trade]);
				return;
			}
		}
		SendClientMessage(conn, "Gold Insuficiente");
		return;
	}

	//alma
	if (itemIndex == 1740 || itemIndex == 1741) {

		int Fragmento = 0;
		for (int i = 0; i < pMob[conn].MaxCarry; i++)
		{
			if (pMob[conn].MOB.Carry[i].sIndex == 5643)
				Fragmento += pMob[conn].MOB.Carry[i].stEffect[0].cEffect == 61 ? pMob[conn].MOB.Carry[i].stEffect[0].cValue : 1;
		}

		int SlotId = 0;
		for (int i = 0; i < pMob[conn].MaxCarry; i++)
		{
			if (pMob[conn].MOB.Carry[i].sIndex == 0)
			{
				SlotId++;
			}
		}
		if (Fragmento < 10) {
			SendClientMessage(conn, "Precisa de pelo menos 10 Fragmentos para Compor");
			return;
		}
		if (SlotId > 2)
		{
			RemoveItem(conn, 5643, 10);

			STRUCT_ITEM item;
			memset(&item, 0, sizeof(STRUCT_ITEM));

			item.sIndex = itemIndex;
			item.stEffect[0].cEffect = 0;
			item.stEffect[0].cValue = 0;
			item.stEffect[1].cEffect = 0;
			item.stEffect[1].cValue = 0;
			item.stEffect[2].cEffect = 0;
			item.stEffect[2].cValue = 0;

			PutItem(conn, &item);
			SendCarry(conn);
			SendScore(conn);
			SendEtc(conn);
			SendClientMessage(conn, "Sua alma foi entregue");
			ItemLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, "Criou uma Alma no Jephi");
			return;
		}
		else
		{
			SendClientMessage(conn, g_pMessageStringTable[_NN_You_Have_No_Space_To_Trade]);
			return;
		}
	}
}

//void NewJephi(int conn, int target, int targetPos, int itemId) {
//
//	int TargetID = target;
//	int TargetInvenPos = targetPos;
//	int itemIndex = itemId;
//
//	if (strcmp(pMob[TargetID].MOB.MobName, "Jephi") == 0) {
//
//
//		// Pedaço do Círculo
//		if (itemIndex == 447 || itemIndex == 692)
//		{
//			if (pUser[conn].Lasclick != itemIndex) {
//				pUser[conn].Lasclick = itemIndex;
//				SendClientMessage(conn, "Deseja compor esse item?");
//				return;
//			}
//			int price = 0;
//			if (pMob[conn].MOB.Equip[13].sIndex != 447 && pMob[conn].MOB.Equip[13].sIndex != 692) {
//				SendClientMessage(conn, "Equipe o pedaço do círculo Divino!");
//				return;
//			}
//			if (pMob[conn].MOB.Equip[13].sIndex == 447) {
//				price = 1000000;
//			}
//
//			if (pMob[conn].MOB.Equip[13].sIndex == 692) {
//				price = 5000000;
//			}
//			if (pMob[conn].MOB.Coin < price) {
//				SendClientMessage(conn, "Você não possui gold suficiente!");
//				return;
//			}
//			if (pMob[conn].MOB.Coin >= price)
//			{
//				if (price == 1000000)
//				{
//					pMob[conn].MOB.Coin -= 1000000;
//					pMob[conn].MOB.Equip[13].sIndex = rand() % 3 + 448;
//				}
//				else
//				{
//					pMob[conn].MOB.Coin -= 5000000;
//					pMob[conn].MOB.Equip[13].sIndex = rand() % 3 + 693;
//				}
//
//				SendItem(conn, ITEM_PLACE_EQUIP, 13, &pMob[conn].MOB.Equip[13]);
//				SendEtc(conn);
//				SendClientMessage(conn, g_pMessageStringTable[_NN_Processing_Complete]);
//				SendScore(conn);
//				return;
//			}
//			return;
//		}
//
//		// Poeira de Ori
//		if (itemIndex == 412) {
//
//			int Ori = 0;
//			for (int i = 0; i < pMob[conn].MaxCarry; i++)
//			{
//				if (pMob[conn].MOB.Carry[i].sIndex == 419)
//					Ori += pMob[conn].MOB.Carry[i].stEffect[0].cEffect == 61 ? pMob[conn].MOB.Carry[i].stEffect[0].cValue : 1;
//			}
//
//			int SlotId = 0;
//			for (int i = 0; i < pMob[conn].MaxCarry; i++)
//			{
//				if (pMob[conn].MOB.Carry[i].sIndex == 0)
//				{
//					SlotId++;
//				}
//			}
//			if (Ori < 10) {
//				SendClientMessage(conn, "Precisa de pelo menos 10 restos para conversão");
//				return;
//			}
//			if (Ori > 1200) {
//				Ori = 1200;
//			}
//			int PoeiraTotal = (Ori / 10);
//			int ValorTotal = PoeiraTotal * 500000;
//			if (pUser[conn].Lasclick != itemIndex) {
//				pUser[conn].Lasclick = itemIndex;
//				SendClientMessage(conn, strFmt("Deseja compor [%d] Poeiras de Ori por [%d]?", PoeiraTotal, ValorTotal));
//				return;
//			}
//			if (pMob[conn].MOB.Coin <= ValorTotal) {
//				SendClientMessage(conn, strFmt("Vai lhe custar [%d] em Gold", ValorTotal));
//				return;
//			}
//
//			if (pMob[conn].MOB.Coin > ValorTotal)
//			{
//				if (SlotId > 2)
//				{
//					int TotalResto = PoeiraTotal * 10;
//					RemoveItem(conn, 419, TotalResto);
//					pMob[conn].MOB.Coin -= ValorTotal;
//
//					STRUCT_ITEM item;
//					memset(&item, 0, sizeof(STRUCT_ITEM));
//
//					item.sIndex = 412;
//					item.stEffect[0].cEffect = 61;
//					item.stEffect[0].cValue = PoeiraTotal;
//					item.stEffect[1].cEffect = 0;
//					item.stEffect[1].cValue = 0;
//					item.stEffect[2].cEffect = 0;
//					item.stEffect[2].cValue = 0;
//
//					PutItem(conn, &item);
//					SendCarry(conn);
//					SendScore(conn);
//					SendEtc(conn);
//					SendClientMessage(conn, strFmt("Criou %d Poeiras de Ori", PoeiraTotal));
//					ItemLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, strFmt("Criou %d Poeiras de Ori", PoeiraTotal));
//					return;
//				}
//				else
//				{
//					SendClientMessage(conn, g_pMessageStringTable[_NN_You_Have_No_Space_To_Trade]);
//					return;
//				}
//			}
//			SendClientMessage(conn, "Traga-me 10 restos de Ori e 500k para compor uma poeira");
//			return;
//		}
//
//		//Poeira de Lac
//		if (itemIndex == 413) {
//
//			int Lac = 0;
//			for (int i = 0; i < pMob[conn].MaxCarry; i++)
//			{
//				if (pMob[conn].MOB.Carry[i].sIndex == 420)
//					Lac += pMob[conn].MOB.Carry[i].stEffect[0].cEffect == 61 ? pMob[conn].MOB.Carry[i].stEffect[0].cValue : 1;
//			}
//
//			int SlotId = 0;
//			for (int i = 0; i < pMob[conn].MaxCarry; i++)
//			{
//				if (pMob[conn].MOB.Carry[i].sIndex == 0)
//				{
//					SlotId++;
//				}
//			}
//			if (Lac < 10) {
//				SendClientMessage(conn, "Precisa de pelo menos 10 restos para conversão");
//				return;
//			}
//			if (Lac > 1200) {
//				Lac = 1200;
//			}
//			int PoeiraTotal = (Lac / 10);
//			int ValorTotal = PoeiraTotal * 1000000;
//			if (pUser[conn].Lasclick != itemIndex) {
//				pUser[conn].Lasclick = itemIndex;
//				SendClientMessage(conn, strFmt("Deseja compor [%d] Poeiras de Lac por [%d]?", PoeiraTotal, ValorTotal));
//				return;
//			}
//			if (pMob[conn].MOB.Coin <= ValorTotal) {
//				SendClientMessage(conn, strFmt("Vai lhe custar [%d] em Gold", ValorTotal));
//				return;
//			}
//
//			if (pMob[conn].MOB.Coin > ValorTotal)
//			{
//				if (SlotId > 2)
//				{
//					int TotalResto = PoeiraTotal * 10;
//					RemoveItem(conn, 420, TotalResto);
//					pMob[conn].MOB.Coin -= ValorTotal;
//
//					STRUCT_ITEM item;
//					memset(&item, 0, sizeof(STRUCT_ITEM));
//
//					item.sIndex = 413;
//					item.stEffect[0].cEffect = 61;
//					item.stEffect[0].cValue = PoeiraTotal;
//					item.stEffect[1].cEffect = 0;
//					item.stEffect[1].cValue = 0;
//					item.stEffect[2].cEffect = 0;
//					item.stEffect[2].cValue = 0;
//
//					PutItem(conn, &item);
//					SendCarry(conn);
//					SendScore(conn);
//					SendEtc(conn);
//					SendClientMessage(conn, strFmt("Criou %d Poeiras de Lac", PoeiraTotal));
//					ItemLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, strFmt("Criou %d Poeiras de Lac", PoeiraTotal));
//					return;
//				}
//				else
//				{
//					SendClientMessage(conn, g_pMessageStringTable[_NN_You_Have_No_Space_To_Trade]);
//					return;
//				}
//			}
//			SendClientMessage(conn, "Traga-me 10 restos de Lac e 1kk para compor uma poeira");
//			return;
//		}
//
//		//alma
//		if (itemIndex == 1740 || itemIndex == 1741) {
//
//			int Fragmento = 0;
//			for (int i = 0; i < pMob[conn].MaxCarry; i++)
//			{
//				if (pMob[conn].MOB.Carry[i].sIndex == 5643)
//					Fragmento += pMob[conn].MOB.Carry[i].stEffect[0].cEffect == 61 ? pMob[conn].MOB.Carry[i].stEffect[0].cValue : 1;
//			}
//
//			int SlotId = 0;
//			for (int i = 0; i < pMob[conn].MaxCarry; i++)
//			{
//				if (pMob[conn].MOB.Carry[i].sIndex == 0)
//				{
//					SlotId++;
//				}
//			}
//			if (Fragmento < 10) {
//				SendClientMessage(conn, "Precisa de pelo menos 10 Fragmentos para conversão");
//				return;
//			}
//			if (pUser[conn].Lasclick != itemIndex) {
//				pUser[conn].Lasclick = itemIndex;
//				SendClientMessage(conn, "Deseja compor essa Alma?");
//				return;
//			}
//			if (SlotId > 2)
//			{
//				RemoveItem(conn, 5643, 10);
//
//				STRUCT_ITEM item;
//				memset(&item, 0, sizeof(STRUCT_ITEM));
//
//				item.sIndex = itemIndex;
//				item.stEffect[0].cEffect = 0;
//				item.stEffect[0].cValue = 0;
//				item.stEffect[1].cEffect = 0;
//				item.stEffect[1].cValue = 0;
//				item.stEffect[2].cEffect = 0;
//				item.stEffect[2].cValue = 0;
//
//				PutItem(conn, &item);
//				SendCarry(conn);
//				SendScore(conn);
//				SendEtc(conn);
//				SendClientMessage(conn, "Sua alma foi entregue");
//				ItemLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, "Criou uma Alma no Jephi");
//				return;
//			}
//			else
//			{
//				SendClientMessage(conn, g_pMessageStringTable[_NN_You_Have_No_Space_To_Trade]);
//				return;
//			}
//		}
//	}
//}