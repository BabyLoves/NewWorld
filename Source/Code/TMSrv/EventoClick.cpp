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
#include "Chests.h"
#include "wMySQL.h"

#define GUARDA_REAL_I			35
#define GUARDA_REAL_II  		36
#define GUARDA_REAL_III 		37
#define GUARDA_REAL_IV  		38
#define GUARDA_REAL_V   		39
#define GUARDA_REAL_VI  		40

int NumbGen(int Initial, int Final) {
	static std::mt19937 rng(std::random_device{}());
	static std::uniform_int_distribution<int> dist(Initial, Final);
	return dist(rng);
}

void LoadEvent() {

	auto& pc = cSQL::instance();

	sprintf(xQuery, "SELECT * FROM `evento`");
	MYSQL_ROW row;
	MYSQL* wSQL = pc.wStart();
	MYSQL_RES* result = pc.wRes(wSQL, xQuery);

	if (result == NULL)
	{
		return;
	}
	int i = 0;
	while ((row = mysql_fetch_row(result)) != NULL)
	{
		if (i == 5)
			i = 0;
		int npc = atoi(row[2]);
		int Qnt = atoi(row[5]);
		Evento[npc][i].sIndex = atoi(row[4]);
		Evento[npc][i].stEffect[0].cEffect = 0;
		Evento[npc][i].stEffect[0].cValue = 0;
		if (Qnt > 0) {
			Evento[npc][i].stEffect[0].cEffect = 61;
			Evento[npc][i].stEffect[0].cValue = Qnt;
		}
		Evento[npc][i].stEffect[1].cEffect = 0;
		Evento[npc][i].stEffect[1].cValue = 0;
		Evento[npc][i].stEffect[2].cEffect = 0;
		Evento[npc][i].stEffect[2].cValue = 0;
		rate[npc][i] = atoi(row[6]);
		i++;
	}

	auto& pc2 = cSQL::instance();

	sprintf(xQuery, "SELECT * FROM `eventoconfig`");
	MYSQL_ROW row2;
	MYSQL* wSQL2 = pc2.wStart();
	MYSQL_RES* result2 = pc2.wRes(wSQL2, xQuery);

	if (result2 == NULL)
	{
		return;
	}
	while ((row2 = mysql_fetch_row(result2)) != NULL)
	{
		int Npc = atoi(row2[2]);
		BausIndex[Npc] = atoi(row2[3]);
		
	}
}


void EventoClick(int conn, int npc)
{
	if (conn <= 0 || conn >= MAX_USER)
		return;

	if (pUser[conn].Mode != USER_PLAY)
		return;

	if (pUser[conn].cSock.Sock == 0)
		return;

	int NPC = npc;	
	int npcid = 0;
	bool Check = false;
	
	if (NPC == GUARDA_REAL_I) {
		npcid = 0;
		Check = true;
	}
	if (NPC == GUARDA_REAL_II){
		npcid = 1;
		Check = true;
	}
	if (NPC == GUARDA_REAL_III){
		npcid = 2;
		Check = true;
	}
	if (NPC == GUARDA_REAL_IV){
		npcid = 3;
		Check = true;
	}
	if (NPC == GUARDA_REAL_V){
		npcid = 4;
		Check = true;
	}

	if (Check == true) {
		int FreeSlot = 0;
		int slotsInv = 30;
		int ItemCount = 0;
		if (pMob[conn].MOB.Carry[60].sIndex == 3467)
			slotsInv += 15;
		if (pMob[conn].MOB.Carry[61].sIndex == 3467)
			slotsInv += 15;

		int rand_ = NumbGen(0, 99);

		int itemIndex = BausIndex[npcid];

		for (int i = 0; i < slotsInv; i++) {
			if (pMob[conn].MOB.Carry[i].sIndex == itemIndex)
				ItemCount += pMob[conn].MOB.Carry[i].stEffect[0].cEffect == 61 ? pMob[conn].MOB.Carry[i].stEffect[0].cValue : 1;

			if (pMob[conn].MOB.Carry[i].sIndex == 0)
				FreeSlot += 1;
		}
		if (ItemCount < 1) {
			SendClientMessage(conn, "Você precisa de pelo menos 1 Item para efetuar a troca");
			return;
		}
		if (FreeSlot < 1) {
			SendClientMessage(conn, "Não há espaço disponível no Inventário");
			return;
		}

		STRUCT_ITEM item;
		memset(&item, 0, sizeof(STRUCT_ITEM));

		if (rand_ >= 0 && rand_ < rate[npcid][0]) {
			memcpy(&item, &Evento[npcid][0], sizeof(STRUCT_ITEM));
		}
		if (rand_ >= rate[npcid][0] && rand_ < rate[npcid][1]) {
			memcpy(&item, &Evento[npcid][1], sizeof(STRUCT_ITEM));
		}
		if (rand_ >= rate[npcid][1] && rand_ < rate[npcid][2]) {
			memcpy(&item, &Evento[npcid][2], sizeof(STRUCT_ITEM));
		}
		if (rand_ >= rate[npcid][2] && rand_ < rate[npcid][3]) {
			memcpy(&item, &Evento[npcid][3], sizeof(STRUCT_ITEM));
		}
		if (rand_ >= rate[npcid][3] && rand_ < rate[npcid][4]) {
			memcpy(&item, &Evento[npcid][4], sizeof(STRUCT_ITEM));
		}

		if (item.sIndex == 2441) {
			item.sIndex = 2441 + rand() % 4;
		}

		int Eff = item.stEffect[0].cEffect;
		int Qnt = item.stEffect[0].cValue;
		RemoveItem(conn, itemIndex, 1);

		if (Eff == 61 && (pUser[conn].Keys[49] == 1))
		{
			while (Qnt >= 1) {
				SendItemagrupar(conn, item.sIndex);
				Qnt -= 1;
			}
		}
		else
			PutItem(conn, &item);

		SendMsgExp(conn, strFmt("Recebeu [%s]", g_pItemList[item.sIndex].Name), TNColor::CornBlue, false);
	}
}

//void EventoClick(int conn, int npc)
//{
//	if (conn <= 0 || conn >= MAX_USER)
//		return;
//
//	if (pUser[conn].Mode != USER_PLAY)
//		return;
//
//	if (pUser[conn].cSock.Sock == 0)
//		return;
//
//	int NPC = npc;
//
//	int FreeSlot = 0;
//	int slotsInv = 30;
//	int ItemCount = 0;
//	int ItemCount2 = 0;
//	int ItemCount3 = 0;
//	if (pMob[conn].MOB.Carry[60].sIndex == 3467)
//		slotsInv += 15;
//	if (pMob[conn].MOB.Carry[61].sIndex == 3467)
//		slotsInv += 15;
//
//	STRUCT_ITEM item;
//	memset(&item, 0, sizeof(STRUCT_ITEM));
//
//	srand(time(NULL) / 5 * (rand() % 500) * 5);
//	int _rand = rand() % 199;
//	if (_rand > 100)
//	{
//		_rand = _rand - 99;
//	}
//
//	if (NPC == GUARDA_REAL_I)
//	{
//		int itemIndex = 5710;
//
//		for (int i = 0; i < slotsInv; i++) {
//			if (pMob[conn].MOB.Carry[i].sIndex == itemIndex)
//				ItemCount += pMob[conn].MOB.Carry[i].stEffect[0].cEffect == 61 ? pMob[conn].MOB.Carry[i].stEffect[0].cValue : 1;
//
//			if (pMob[conn].MOB.Carry[i].sIndex == 0)
//				FreeSlot += 1;
//		}
//		if (ItemCount < 1) {
//			SendClientMessage(conn, "Você precisa de pelo menos 1 Item para efetuar a troca");
//			return;
//		}
//		if (FreeSlot < 1) {
//			SendClientMessage(conn, "Não há espaço disponível no Inventário");
//			return;
//		}
//
//		if (_rand < 25) { //25%
//			item.sIndex = 420;
//			item.stEffect[0].cEffect = 61;
//			item.stEffect[0].cValue = 3;
//		}
//		else if (_rand < 60) { //35%
//			item.sIndex = 419;
//			item.stEffect[0].cEffect = 61;
//			item.stEffect[0].cValue = 5;
//		}
//		else if (_rand < 85) { //25%
//			item.sIndex = 4019;
//			item.stEffect[0].cEffect = 61;
//			item.stEffect[0].cValue = 3;
//		}
//		else if (_rand < 100) { //15%
//			item.sIndex = 5711;
//			item.stEffect[0].cEffect = 61;
//			item.stEffect[0].cValue = 1;
//		}
//		int Eff = item.stEffect[0].cEffect;
//		int Qnt = item.stEffect[0].cValue;
//		RemoveItem(conn, itemIndex, 1);
//
//		if (Eff == 61 && (pMob[conn].MOB.Equip[13].sIndex == 3901 || pMob[conn].MOB.Equip[13].sIndex == 3902))
//		{
//			while (Qnt >= 1) {
//				SendItemagrupar(conn, item.sIndex);
//				Qnt -= 1;
//			}
//		}
//		else
//			PutItem(conn, &item);
//	}
//	if (NPC == GUARDA_REAL_II)
//	{
//		int itemIndex = 5711;
//
//		for (int i = 0; i < slotsInv; i++) {
//			if (pMob[conn].MOB.Carry[i].sIndex == itemIndex)
//				ItemCount += pMob[conn].MOB.Carry[i].stEffect[0].cEffect == 61 ? pMob[conn].MOB.Carry[i].stEffect[0].cValue : 1;
//
//			if (pMob[conn].MOB.Carry[i].sIndex == 0)
//				FreeSlot += 1;
//		}
//		if (ItemCount < 1) {
//			SendClientMessage(conn, "Você precisa de pelo menos 1 Item para efetuar a troca");
//			return;
//		}
//		if (FreeSlot < 1) {
//			SendClientMessage(conn, "Não há espaço disponível no Inventário");
//			return;
//		}
//
//		int Amagos[3] = { 2399, 2404, 2406 };
//
//		if (_rand < 25) { //25%
//			item.sIndex = Amagos[rand() % 3];
//			item.stEffect[0].cEffect = 61;
//			item.stEffect[0].cValue = 3;
//		}
//		else if (_rand < 60) { //35%
//			item.sIndex = rand() % 4 + 2441;
//			item.stEffect[0].cEffect = 61;
//			item.stEffect[0].cValue = 1;
//		}
//		else if (_rand < 85) { //25%
//			item.sIndex = 4020;
//			item.stEffect[0].cEffect = 61;
//			item.stEffect[0].cValue = 2;
//		}
//		else if (_rand < 100) { //15%
//			item.sIndex = 5712;
//			item.stEffect[0].cEffect = 61;
//			item.stEffect[0].cValue = 1;
//		}
//		int Eff = item.stEffect[0].cEffect;
//		int Qnt = item.stEffect[0].cValue;
//		RemoveItem(conn, itemIndex, 1);
//
//		if (Eff == 61 && (pMob[conn].MOB.Equip[13].sIndex == 3901 || pMob[conn].MOB.Equip[13].sIndex == 3902))
//		{
//			while (Qnt >= 1) {
//				SendItemagrupar(conn, item.sIndex);
//				Qnt -= 1;
//			}
//		}
//		else
//			PutItem(conn, &item);
//	}
//	if (NPC == GUARDA_REAL_III)
//	{
//		int itemIndex = 5712;
//
//		for (int i = 0; i < slotsInv; i++) {
//			if (pMob[conn].MOB.Carry[i].sIndex == itemIndex)
//				ItemCount += pMob[conn].MOB.Carry[i].stEffect[0].cEffect == 61 ? pMob[conn].MOB.Carry[i].stEffect[0].cValue : 1;
//
//			if (pMob[conn].MOB.Carry[i].sIndex == 0)
//				FreeSlot += 1;
//		}
//		if (ItemCount < 1) {
//			SendClientMessage(conn, "Você precisa de pelo menos 1 Item para efetuar a troca");
//			return;
//		}
//		if (FreeSlot < 1) {
//			SendClientMessage(conn, "Não há espaço disponível no Inventário");
//			return;
//		}
//
//		int Joias[5] = { 3200, 3201, 3202, 3204, 3205 };
//
//		if (_rand < 25) { //25%
//			item.sIndex = Joias[rand() % 5];
//			item.stEffect[0].cEffect = 61;
//			item.stEffect[0].cValue = 1;
//		}
//		else if (_rand < 60) { //35%
//			item.sIndex = 3314;
//			item.stEffect[0].cEffect = 61;
//			item.stEffect[0].cValue = 1;
//		}
//		else if (_rand < 85) { //25%
//			item.sIndex = 3140;
//			item.stEffect[0].cEffect = 61;
//			item.stEffect[0].cValue = 3 + rand() % 3;
//		}
//		else if (_rand < 100) { //15%
//			item.sIndex = 5717;
//			item.stEffect[0].cEffect = 61;
//			item.stEffect[0].cValue = 1;
//		}
//		int Eff = item.stEffect[0].cEffect;
//		int Qnt = item.stEffect[0].cValue;
//		RemoveItem(conn, itemIndex, 1);
//
//		if (Eff == 61 && (pMob[conn].MOB.Equip[13].sIndex == 3901 || pMob[conn].MOB.Equip[13].sIndex == 3902))
//		{
//			while (Qnt >= 1) {
//				SendItemagrupar(conn, item.sIndex);
//				Qnt -= 1;
//			}
//		}
//		else
//			PutItem(conn, &item);
//	}
//	if (NPC == GUARDA_REAL_IV)
//	{
//		int itemIndex = 5717;
//
//		for (int i = 0; i < slotsInv; i++) {
//			if (pMob[conn].MOB.Carry[i].sIndex == itemIndex)
//				ItemCount += pMob[conn].MOB.Carry[i].stEffect[0].cEffect == 61 ? pMob[conn].MOB.Carry[i].stEffect[0].cValue : 1;
//
//			if (pMob[conn].MOB.Carry[i].sIndex == 0)
//				FreeSlot += 1;
//		}
//		if (ItemCount < 1) {
//			SendClientMessage(conn, "Você precisa de pelo menos 1 Item para efetuar a troca");
//			return;
//		}
//		if (FreeSlot < 1) {
//			SendClientMessage(conn, "Não há espaço disponível no Inventário");
//			return;
//		}
//
//
//
//		if (_rand < 25) { //25%
//			item.sIndex = 4140;
//			item.stEffect[0].cEffect = 61;
//			item.stEffect[0].cValue = 1;
//		}
//		else if (_rand < 60) { //35%
//			item.sIndex = 5643;
//			item.stEffect[0].cEffect = 61;
//			item.stEffect[0].cValue = 2;
//		}
//		else if (_rand < 85) { //25%
//			item.sIndex = 3207 + rand() % 3;
//			item.stEffect[0].cEffect = 61;
//			item.stEffect[0].cValue = 1;
//		}
//		else if (_rand < 100) { //15%
//			item.sIndex = 5716;
//			item.stEffect[0].cEffect = 61;
//			item.stEffect[0].cValue = 1;
//		}
//		int Eff = item.stEffect[0].cEffect;
//		int Qnt = item.stEffect[0].cValue;
//		RemoveItem(conn, itemIndex, 1);
//
//		if (Eff == 61 && (pMob[conn].MOB.Equip[13].sIndex == 3901 || pMob[conn].MOB.Equip[13].sIndex == 3902))
//		{
//			while (Qnt >= 1) {
//				SendItemagrupar(conn, item.sIndex);
//				Qnt -= 1;
//			}
//		}
//		else
//			PutItem(conn, &item);
//	}
//	if (NPC == GUARDA_REAL_V)
//	{
//		int itemIndex = 5713;
//		int itemIndex2 = 5714;
//		int itemIndex3 = 5715;
//
//		for (int i = 0; i < slotsInv; i++) {
//			if (pMob[conn].MOB.Carry[i].sIndex == itemIndex)
//				ItemCount += pMob[conn].MOB.Carry[i].stEffect[0].cEffect == 61 ? pMob[conn].MOB.Carry[i].stEffect[0].cValue : 1;
//
//			if (pMob[conn].MOB.Carry[i].sIndex == itemIndex2)
//				ItemCount2 += pMob[conn].MOB.Carry[i].stEffect[0].cEffect == 61 ? pMob[conn].MOB.Carry[i].stEffect[0].cValue : 1;
//
//			if (pMob[conn].MOB.Carry[i].sIndex == itemIndex3)
//				ItemCount3 += pMob[conn].MOB.Carry[i].stEffect[0].cEffect == 61 ? pMob[conn].MOB.Carry[i].stEffect[0].cValue : 1;
//
//			if (pMob[conn].MOB.Carry[i].sIndex == 0)
//				FreeSlot += 1;
//		}
//		if (ItemCount < 1 || ItemCount2 < 1 || ItemCount3 < 1) {
//			SendClientMessage(conn, "Você precisa dos Três Pirulitos para efetuar a troca");
//			return;
//		}
//		if (FreeSlot < 1) {
//			SendClientMessage(conn, "Não há espaço disponível no Inventário");
//			return;
//		}
//
//		if (_rand < 35) { //35%
//			item.sIndex = 5643;
//			item.stEffect[0].cEffect = 61;
//			item.stEffect[0].cValue = 2;
//		}
//		else if (_rand < 70) { //35%
//			item.sIndex = 3172;
//			item.stEffect[0].cEffect = 61;
//			item.stEffect[0].cValue = 1;
//		}
//		else if (_rand < 100) { //30%
//			item.sIndex = 5718;
//			item.stEffect[0].cEffect = 61;
//			item.stEffect[0].cValue = 3;
//		}
//
//		int Eff = item.stEffect[0].cEffect;
//		int Qnt = item.stEffect[0].cValue;
//		RemoveItem(conn, itemIndex, 1);
//		RemoveItem(conn, itemIndex2, 1);
//		RemoveItem(conn, itemIndex3, 1);
//
//		if (Eff == 61 && (pMob[conn].MOB.Equip[13].sIndex == 3901 || pMob[conn].MOB.Equip[13].sIndex == 3902))
//		{
//			while (Qnt >= 1) {
//				SendItemagrupar(conn, item.sIndex);
//				Qnt -= 1;
//			}
//		}
//		else
//			PutItem(conn, &item);
//	}
//	if (NPC == GUARDA_REAL_VI)
//	{
//		int itemIndex = 5716;
//
//		for (int i = 0; i < slotsInv; i++) {
//			if (pMob[conn].MOB.Carry[i].sIndex == itemIndex)
//				ItemCount += pMob[conn].MOB.Carry[i].stEffect[0].cEffect == 61 ? pMob[conn].MOB.Carry[i].stEffect[0].cValue : 1;
//
//			if (pMob[conn].MOB.Carry[i].sIndex == 0)
//				FreeSlot += 1;
//		}
//		if (ItemCount < 1) {
//			SendClientMessage(conn, "Traga o Saco de Doces para receber um Pirulito");
//			return;
//		}
//		if (FreeSlot < 1) {
//			SendClientMessage(conn, "Não há espaço disponível no Inventário");
//			return;
//		}
//
//		if (_rand < 34) { //33%
//			item.sIndex = 5713;
//			item.stEffect[0].cEffect = 61;
//			item.stEffect[0].cValue = 1;
//		}
//		else if (_rand < 67) { //33%
//			item.sIndex = 5714;
//			item.stEffect[0].cEffect = 61;
//			item.stEffect[0].cValue = 1;
//		}
//		else if (_rand < 100) { //33%
//			item.sIndex = 5715;
//			item.stEffect[0].cEffect = 61;
//			item.stEffect[0].cValue = 1;
//		}
//
//		int Eff = item.stEffect[0].cEffect;
//		int Qnt = item.stEffect[0].cValue;
//		RemoveItem(conn, itemIndex, 1);
//
//		if (Eff == 61 && (pMob[conn].MOB.Equip[13].sIndex == 3901 || pMob[conn].MOB.Equip[13].sIndex == 3902))
//		{
//			while (Qnt >= 1) {
//				SendItemagrupar(conn, item.sIndex);
//				Qnt -= 1;
//			}
//		}
//		else
//			PutItem(conn, &item);
//	}
//}