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

void ItemLevel(int conn, char* pMsg)
{
	if (conn <= 0 || conn >= MAX_USER)
		return;

	if (pUser[conn].Mode != USER_PLAY)
		return;

	if (pUser[conn].cSock.Sock == 0)
		return;

	MSG_SendItemLevel* m = (MSG_SendItemLevel*)pMsg;

	int Size = m->Size;

	if (Size > sizeof(MSG_SendItemLevel)) //CONTROLE DE SIZE
	{
		SendClientMessage(conn, "Impossível executar ação, tente mais tarde.");
		return;
	}

	if (m->Qnt <= 0 || m->Qnt > 120)
		return;

	if (m->Item <= 0 || m->Item >= MAX_ITEMLIST)
		return;

	if (pMob[conn].extra.ClassMaster != 2) {
		pUser[conn].chave1 = 99;
		return;
	}
		

	if (pUser[conn].chave1 == 0 && pMob[conn].MOB.BaseScore.Level >= 0) {
		if (m->Item < 938 || m->Item > 945)
			return;

		if ((m->Item == 938 || m->Item == 939) && m->Qnt != 2)
			return;

		int Qnt = m->Qnt;

		if (m->Item != 938 && m->Item != 939)
			Qnt = 1;

		int SlotId = 0;
		for (int i = 0; i < pMob[conn].MaxCarry; i++)
		{
			if (pMob[conn].MOB.Carry[i].sIndex == 0)
			{
				SlotId++;
			}
		}
		if (SlotId < 2) {
			SendClientMessage(conn, "Você não possuí espaço para receber");
			return;
		}

		pUser[conn].chave1 = 1;

		STRUCT_ITEM item;
		memset(&item, 0, sizeof(STRUCT_ITEM));
		item.sIndex = m->Item;
		item.stEffect[0].cEffect = 43;
		item.stEffect[0].cValue = 0;
		item.stEffect[1].cEffect = 0;
		item.stEffect[1].cValue = 0;
		item.stEffect[2].cEffect = 0;
		item.stEffect[2].cValue = 0;

		while (Qnt >= 1) {
			PutItem(conn, &item);
			Qnt--;
		}
		SendEtc(conn);
		SendCarry(conn);
		SaveUser(conn, 0);
		return;
	}
	if (pUser[conn].chave1 == 1 && pMob[conn].MOB.BaseScore.Level >= 0)
	{
		if (m->Item != 3980 || m->Qnt != 1)
			return;

		int Qnt = m->Qnt;

		int SlotId = 0;
		for (int i = 0; i < pMob[conn].MaxCarry; i++)
		{
			if (pMob[conn].MOB.Carry[i].sIndex == 0)
			{
				SlotId++;
			}
		}
		if (SlotId < 2) {
			SendClientMessage(conn, "Você não possuí espaço para receber");
			return;
		}

		STRUCT_ITEM item;
		memset(&item, 0, sizeof(STRUCT_ITEM));
		item.sIndex = m->Item;
		item.stEffect[0].cEffect = 0;
		item.stEffect[0].cValue = 0;
		item.stEffect[1].cEffect = 0;
		item.stEffect[1].cValue = 0;
		item.stEffect[2].cEffect = 0;
		item.stEffect[2].cValue = 0;


		while (Qnt >= 1) {
			PutItem(conn, &item);
			Qnt--;
		}
		pUser[conn].chave1 = 2;

		int sAffect = GetEmptyAffect(conn, 30);

		pMob[conn].Affect[sAffect].Type = 30;
		pMob[conn].Affect[sAffect].Level = 2000;
		pMob[conn].Affect[sAffect].Value = 0;
		pMob[conn].Affect[sAffect].Time += AFFECT_1H * 4;

		if (pMob[conn].Affect[sAffect].Time >= 324000)
			pMob[conn].Affect[sAffect].Time = 324000;

		int sAffect2 = GetEmptyAffect(conn, 39);

		pMob[conn].Affect[sAffect2].Type = 39;
		pMob[conn].Affect[sAffect2].Level = 0;
		pMob[conn].Affect[sAffect2].Value = 0;
		pMob[conn].Affect[sAffect2].Time += AFFECT_1H * 4;

		pMob[conn].GetCurrentScore(conn);
		SendScore(conn);
		SendEtc(conn);
		SendCarry(conn);				
		SaveUser(conn, 0);
		return;
	}
	if (pUser[conn].chave1 == 2 && pMob[conn].MOB.BaseScore.Level >= 113)
	{
		if (m->Item != 2373 && m->Item != 2368)
			return;

		STRUCT_ITEM Item1, Item2;
		memset(&Item1, 0, sizeof(STRUCT_ITEM));

		int x = 0;
		int invfree = 0;

		for (x = 0; x < pMob[conn].MaxCarry; x++)
		{
			if (pMob[conn].MOB.Carry[x].sIndex == 0)
				invfree++;
		}
		if (invfree < 3)
		{
			SendClientMessage(conn, "Não há espaço suficiente no inventário");
			return;
		}

		//level b
		Item1.sIndex = m->Item;
		Item1.stEffect[0].cEffect = 10;
		Item1.stEffect[0].cValue = 10;
		Item1.stEffect[1].cEffect = 10;
		Item1.stEffect[1].cValue = 10;
		Item1.stEffect[2].cEffect = 100;
		Item1.stEffect[2].cValue = 0;

		pUser[conn].chave1 = 3;
		PutItem(conn, &Item1);
		SendEtc(conn);
		SendCarry(conn);		
		SaveUser(conn, 0);
		return;
	}
	if (pUser[conn].chave1 == 3 && pMob[conn].MOB.BaseScore.Level >= 124)
	{
		if (m->Item < 1207 && m->Item > 1654)
			return;

		STRUCT_ITEM Item[5];
		memset(&Item[0], 0, sizeof(STRUCT_ITEM));
		memset(&Item[1], 0, sizeof(STRUCT_ITEM));
		memset(&Item[2], 0, sizeof(STRUCT_ITEM));
		memset(&Item[3], 0, sizeof(STRUCT_ITEM));
		memset(&Item[4], 0, sizeof(STRUCT_ITEM));

		int x = 0;
		int invfree = 0;

		for (x = 0; x < pMob[conn].MaxCarry; x++)
		{
			if (pMob[conn].MOB.Carry[x].sIndex == 0)
				invfree++;
		}
		if (invfree < 6)
		{
			SendClientMessage(conn, "Não há espaço suficiente no inventário");
			return;
		}
		//CLASSES: 0=TK, 1=FM, 2=BM, 3=HT
		if (pMob[conn].MOB.Class == 0) {
			Item[0].sIndex = 1216;
			Item[1].sIndex = 1219;
			Item[2].sIndex = 1207;
			Item[3].sIndex = 1213;
			Item[4].sIndex = 1210;
			for (int i = 0; i < 5; i++) {
				Item[i].stEffect[0].cEffect = 43;
				Item[i].stEffect[0].cValue = 3;
				Item[i].stEffect[1].cEffect = 0;
				Item[i].stEffect[1].cValue = 0;
				Item[i].stEffect[2].cEffect = 0;
				Item[i].stEffect[2].cValue = 0;
				PutItem(conn, &Item[i]);
			}
		}
		if (pMob[conn].MOB.Class == 1) {
			Item[0].sIndex = 1351;
			Item[1].sIndex = 1354;
			Item[2].sIndex = 1342;
			Item[3].sIndex = 1348;
			Item[4].sIndex = 1345;
			for (int i = 0; i < 5; i++) {
				Item[i].stEffect[0].cEffect = 43;
				Item[i].stEffect[0].cValue = 3;
				Item[i].stEffect[1].cEffect = 0;
				Item[i].stEffect[1].cValue = 0;
				Item[i].stEffect[2].cEffect = 0;
				Item[i].stEffect[2].cValue = 0;
				PutItem(conn, &Item[i]);
			}
		}
		if (pMob[conn].MOB.Class == 2) {
			Item[0].sIndex = 1501;
			Item[1].sIndex = 1504;
			Item[2].sIndex = 1492;
			Item[3].sIndex = 1498;
			Item[4].sIndex = 1495;
			for (int i = 0; i < 5; i++) {
				Item[i].stEffect[0].cEffect = 43;
				Item[i].stEffect[0].cValue = 3;
				Item[i].stEffect[1].cEffect = 0;
				Item[i].stEffect[1].cValue = 0;
				Item[i].stEffect[2].cEffect = 0;
				Item[i].stEffect[2].cValue = 0;
				PutItem(conn, &Item[i]);
			}
		}
		if (pMob[conn].MOB.Class == 3) {
			Item[0].sIndex = 1651;
			Item[1].sIndex = 1654;
			Item[2].sIndex = 1642;
			Item[3].sIndex = 1648;
			Item[4].sIndex = 1645;
			for (int i = 0; i < 5; i++) {
				Item[i].stEffect[0].cEffect = 43;
				Item[i].stEffect[0].cValue = 3;
				Item[i].stEffect[1].cEffect = 0;
				Item[i].stEffect[1].cValue = 0;
				Item[i].stEffect[2].cEffect = 0;
				Item[i].stEffect[2].cValue = 0;
				PutItem(conn, &Item[i]);
			}
		}
		pUser[conn].chave1 = 4;
		SendEtc(conn);
		SendCarry(conn);
		SaveUser(conn, 0);
		return;
	}
	if (pUser[conn].chave1 == 4 && pMob[conn].MOB.BaseScore.Level >= 143)
	{
		if (m->Item != 854 && m->Item != 809 && m->Item != 2127 && m->Item != 2122)
			return;

		STRUCT_ITEM Item[2];
		memset(&Item[0], 0, sizeof(STRUCT_ITEM));
		memset(&Item[1], 0, sizeof(STRUCT_ITEM));

		int x = 0;
		int invfree = 0;

		for (x = 0; x < pMob[conn].MaxCarry; x++)
		{
			if (pMob[conn].MOB.Carry[x].sIndex == 0)
				invfree++;
		}
		if (invfree < 3)
		{
			SendClientMessage(conn, "Não há espaço suficiente no inventário");
			return;
		}
		//CLASSES: 0=TK, 1=FM, 2=BM, 3=HT
		if (pMob[conn].MOB.Class == 0) {

			//MAGO
			if (pMob[conn].MOB.BaseScore.Int > (pMob[conn].MOB.BaseScore.Dex + pMob[conn].MOB.BaseScore.Str)) {
				Item[0].sIndex = 854;
				Item[0].stEffect[0].cEffect = 43;
				Item[0].stEffect[0].cValue = 5;
				Item[0].stEffect[1].cEffect = 60;
				Item[0].stEffect[1].cValue = 16;
				Item[0].stEffect[2].cEffect = 0;
				Item[0].stEffect[2].cValue = 0;
				PutItem(conn, &Item[0]);
			}
			//DANO
			if (pMob[conn].MOB.BaseScore.Int < (pMob[conn].MOB.BaseScore.Dex + pMob[conn].MOB.BaseScore.Str)) {
				Item[0].sIndex = 809;
				Item[1].sIndex = 809;

				for (int i = 0; i < 2; i++) {
					Item[i].stEffect[0].cEffect = 43;
					Item[i].stEffect[0].cValue = 5;
					Item[i].stEffect[1].cEffect = 2;
					Item[i].stEffect[1].cValue = 36;
					Item[i].stEffect[2].cEffect = 0;
					Item[i].stEffect[2].cValue = 0;
					PutItem(conn, &Item[i]);
				}
			}
		}
		if (pMob[conn].MOB.Class == 1) {
			//MAGO
			if (pMob[conn].MOB.BaseScore.Int > (pMob[conn].MOB.BaseScore.Dex + pMob[conn].MOB.BaseScore.Str)) {
				Item[0].sIndex = 2127;
				Item[0].stEffect[0].cEffect = 43;
				Item[0].stEffect[0].cValue = 5;
				Item[0].stEffect[1].cEffect = 60;
				Item[0].stEffect[1].cValue = 16;
				Item[0].stEffect[2].cEffect = 0;
				Item[0].stEffect[2].cValue = 0;
				PutItem(conn, &Item[0]);
			}
			//DANO
			if (pMob[conn].MOB.BaseScore.Int < (pMob[conn].MOB.BaseScore.Dex + pMob[conn].MOB.BaseScore.Str)) {
				Item[0].sIndex = 2122;
				Item[0].stEffect[0].cEffect = 43;
				Item[0].stEffect[0].cValue = 5;
				Item[0].stEffect[1].cEffect = 2;
				Item[0].stEffect[1].cValue = 36;
				Item[0].stEffect[2].cEffect = 0;
				Item[0].stEffect[2].cValue = 0;
				PutItem(conn, &Item[0]);
			}
		}
		if (pMob[conn].MOB.Class == 2) {
			//MAGO
			if (pMob[conn].MOB.BaseScore.Int > (pMob[conn].MOB.BaseScore.Dex + pMob[conn].MOB.BaseScore.Str)) {
				Item[0].sIndex = 854;
				Item[0].stEffect[0].cEffect = 43;
				Item[0].stEffect[0].cValue = 5;
				Item[0].stEffect[1].cEffect = 60;
				Item[0].stEffect[1].cValue = 16;
				Item[0].stEffect[2].cEffect = 0;
				Item[0].stEffect[2].cValue = 0;
				PutItem(conn, &Item[0]);
			}
			//DANO
			if (pMob[conn].MOB.BaseScore.Int < (pMob[conn].MOB.BaseScore.Dex + pMob[conn].MOB.BaseScore.Str)) {
				Item[0].sIndex = 809;
				Item[1].sIndex = 809;

				for (int i = 0; i < 2; i++) {
					Item[i].stEffect[0].cEffect = 43;
					Item[i].stEffect[0].cValue = 5;
					Item[i].stEffect[1].cEffect = 2;
					Item[i].stEffect[1].cValue = 36;
					Item[i].stEffect[2].cEffect = 0;
					Item[i].stEffect[2].cValue = 0;
					PutItem(conn, &Item[i]);
				}
			}
		}
		if (pMob[conn].MOB.Class == 3) {
			Item[0].sIndex = 2122;
			Item[0].stEffect[0].cEffect = 43;
			Item[0].stEffect[0].cValue = 5;
			Item[0].stEffect[1].cEffect = 2;
			Item[0].stEffect[1].cValue = 36;
			Item[0].stEffect[2].cEffect = 0;
			Item[0].stEffect[2].cValue = 0;
			PutItem(conn, &Item[0]);
		}
		pUser[conn].chave1 = 5;
		SendEtc(conn);
		SaveUser(conn, 0);
		return;
	}
	if (pUser[conn].chave1 == 5 && pMob[conn].MOB.BaseScore.Level >= 255)
	{
		STRUCT_ITEM Item[5];
		memset(&Item[0], 0, sizeof(STRUCT_ITEM));
		memset(&Item[1], 0, sizeof(STRUCT_ITEM));
		memset(&Item[2], 0, sizeof(STRUCT_ITEM));

		int x = 0;
		int invfree = 0;

		for (x = 0; x < pMob[conn].MaxCarry; x++)
		{
			if (pMob[conn].MOB.Carry[x].sIndex == 0)
				invfree++;
		}
		if (invfree < 6)
		{
			SendClientMessage(conn, "Não há espaço suficiente no inventário");
			return;
		}
		//CLASSES: 0=TK, 1=FM, 2=BM, 3=HT
		if (pMob[conn].MOB.Class == 0) {

			//MAGO
			if (pMob[conn].MOB.BaseScore.Int > (pMob[conn].MOB.BaseScore.Dex + pMob[conn].MOB.BaseScore.Str)) {
				Item[0].sIndex = 3566;
				Item[0].stEffect[0].cEffect = 43;
				Item[0].stEffect[0].cValue = 5;
				Item[0].stEffect[1].cEffect = 60;
				Item[0].stEffect[1].cValue = 16;
				Item[0].stEffect[2].cEffect = 0;
				Item[0].stEffect[2].cValue = 0;
				PutItem(conn, &Item[0]);
			}
			//DANO
			if (pMob[conn].MOB.BaseScore.Int < (pMob[conn].MOB.BaseScore.Dex + pMob[conn].MOB.BaseScore.Str)) {
				Item[0].sIndex = 3551;
				Item[1].sIndex = 3551;

				for (int i = 0; i < 2; i++) {
					Item[i].stEffect[0].cEffect = 43;
					Item[i].stEffect[0].cValue = 5;
					Item[i].stEffect[1].cEffect = 2;
					Item[i].stEffect[1].cValue = 36;
					Item[i].stEffect[2].cEffect = 0;
					Item[i].stEffect[2].cValue = 0;
					PutItem(conn, &Item[i]);
				}
			}
		}
		if (pMob[conn].MOB.Class == 1) {
			//MAGO
			if (pMob[conn].MOB.BaseScore.Int > (pMob[conn].MOB.BaseScore.Dex + pMob[conn].MOB.BaseScore.Str)) {
				Item[0].sIndex = 3582;
				Item[0].stEffect[0].cEffect = 43;
				Item[0].stEffect[0].cValue = 5;
				Item[0].stEffect[1].cEffect = 60;
				Item[0].stEffect[1].cValue = 16;
				Item[0].stEffect[2].cEffect = 0;
				Item[0].stEffect[2].cValue = 0;
				PutItem(conn, &Item[0]);
			}
			//DANO
			if (pMob[conn].MOB.BaseScore.Int < (pMob[conn].MOB.BaseScore.Dex + pMob[conn].MOB.BaseScore.Str)) {
				Item[0].sIndex = 3556;
				Item[0].stEffect[0].cEffect = 43;
				Item[0].stEffect[0].cValue = 5;
				Item[0].stEffect[1].cEffect = 2;
				Item[0].stEffect[1].cValue = 36;
				Item[0].stEffect[2].cEffect = 0;
				Item[0].stEffect[2].cValue = 0;
				PutItem(conn, &Item[0]);
			}
		}
		if (pMob[conn].MOB.Class == 2) {
			//MAGO
			if (pMob[conn].MOB.BaseScore.Int > (pMob[conn].MOB.BaseScore.Dex + pMob[conn].MOB.BaseScore.Str)) {
				Item[0].sIndex = 3566;
				Item[0].stEffect[0].cEffect = 43;
				Item[0].stEffect[0].cValue = 5;
				Item[0].stEffect[1].cEffect = 60;
				Item[0].stEffect[1].cValue = 16;
				Item[0].stEffect[2].cEffect = 0;
				Item[0].stEffect[2].cValue = 0;
				PutItem(conn, &Item[0]);
			}
			//DANO
			if (pMob[conn].MOB.BaseScore.Int < (pMob[conn].MOB.BaseScore.Dex + pMob[conn].MOB.BaseScore.Str)) {
				Item[0].sIndex = 3551;
				Item[1].sIndex = 3551;

				for (int i = 0; i < 2; i++) {
					Item[i].stEffect[0].cEffect = 43;
					Item[i].stEffect[0].cValue = 5;
					Item[i].stEffect[1].cEffect = 2;
					Item[i].stEffect[1].cValue = 36;
					Item[i].stEffect[2].cEffect = 0;
					Item[i].stEffect[2].cValue = 0;
					PutItem(conn, &Item[i]);
				}
			}
		}
		if (pMob[conn].MOB.Class == 3) {
			Item[0].sIndex = 3556;
			Item[0].stEffect[0].cEffect = 43;
			Item[0].stEffect[0].cValue = 5;
			Item[0].stEffect[1].cEffect = 2;
			Item[0].stEffect[1].cValue = 36;
			Item[0].stEffect[2].cEffect = 0;
			Item[0].stEffect[2].cValue = 0;
			PutItem(conn, &Item[0]);
		}
		pUser[conn].chave1 = 6;
		SendEtc(conn);
		SaveUser(conn, 0);
		return;
	}
}
