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
#include "wMySQL.h"

void MailItem(int conn)
{
	if (conn <= 0 || conn >= MAX_USER)
		return;

	if (pUser[conn].Mode != USER_PLAY)
		return;

	if (pUser[conn].cSock.Sock == 0)
		return;

	if (pUser[conn].MailItemDelay != 0)
	{
		int isTime = GetTickCount64() - pUser[conn].MailItemDelay; // ATRASO PACOTE

		if (isTime < 200)
		{
			//SendClientMessage(conn, "Aguarde 1 segundo para uma nova Tentativa.");
			return;
		}

	}
	pUser[conn].MailItemDelay = GetTickCount64();

	auto& pc = cSQL::instance();

	int Index = 0;
	int sEffect[3];
	int sValue[3];

	for (int i = 0; i < 3; i++) {
		sEffect[i] = 0;
		sValue[i] = 0;
	}

	sprintf(hQuery, "SELECT * FROM `mailitem` WHERE `account` = '%s' AND `delivered` = '%d' LIMIT 1", pUser[conn].AccountName, 0);
	MYSQL_ROW row;
	MYSQL* wSQL = pc.wStart();
	MYSQL_RES* result = pc.wRes(wSQL, hQuery);

	if (result == NULL)
		return;

	while ((row = mysql_fetch_row(result)) != NULL)
	{
		Index = atoi(row[3]);
		sEffect[0] = atoi(row[4]);
		sValue[0] = atoi(row[5]);
		sEffect[1] = atoi(row[6]);
		sValue[1] = atoi(row[7]);
		sEffect[2] = atoi(row[8]);
		sValue[2] = atoi(row[9]);
	}

	MSG_MailItem sm;
	memset(&sm, 0, sizeof(MSG_MailItem));
	sm.Type = _MSG_MailItem;
	sm.Size = sizeof(MSG_MailItem);
	sm.ID = conn;

	sm.Index = Index;
	sm.sEffect[0] = sEffect[0];
	sm.sValue[0] = sValue[0];
	sm.sEffect[1] = sEffect[1];
	sm.sValue[1] = sValue[1];
	sm.sEffect[2] = sEffect[2];
	sm.sValue[2] = sValue[2];

	int Size = sm.Size;

	if (Size > sizeof(MSG_MailItem))
	{
		sm.Size = sizeof(MSG_MailItem);
		return;
	}
	if (!pUser[conn].cSock.AddMessage((char*)&sm, sizeof(MSG_MailItem)))
		CloseUser(conn);
}

void SendMailItem(int conn)
{
	if (conn <= 0 || conn >= MAX_USER)
		return;

	if (pUser[conn].Mode != USER_PLAY)
		return;

	if (pUser[conn].cSock.Sock == 0)
		return;

	if (pUser[conn].SendMailItemDelay != 0)
	{
		int isTime = GetTickCount64() - pUser[conn].SendMailItemDelay; // ATRASO PACOTE

		if (isTime < 200)
		{
			//SendClientMessage(conn, "Aguarde 1 segundo para uma nova Tentativa.");
			return;
		}

	}
	pUser[conn].SendMailItemDelay = GetTickCount64();

	int FreeSlot = 0;
	int slotsInv = 30;

	if (pMob[conn].MOB.Carry[60].sIndex == 3467)
		slotsInv += 15;
	if (pMob[conn].MOB.Carry[61].sIndex == 3467)
		slotsInv += 15;

	for (int i = 0; i < slotsInv; i++) {
		if (pMob[conn].MOB.Carry[i].sIndex == 0)
			FreeSlot += 1;
	}
	if (FreeSlot < 2) {
		SendClientMessage(conn, "Não há espaço disponível no Inventário");
		return;
	}

	auto& pc = cSQL::instance();

	int Delivered = 0;
	int RowIndex = 0;
	int Index = 0;
	int sEffect[3];
	int sValue[3];

	for (int i = 0; i < 3; i++) {
		sEffect[i] = 0;
		sValue[i] = 0;
	}

	sprintf(hQuery, "SELECT * FROM `mailitem` WHERE `account` = '%s' AND `delivered` = '%d' LIMIT 1", pUser[conn].AccountName, 0);
	MYSQL_ROW row;
	MYSQL* wSQL = pc.wStart();
	MYSQL_RES* result = pc.wRes(wSQL, hQuery);

	if (result == NULL)
		return;

	while ((row = mysql_fetch_row(result)) != NULL)
	{
		RowIndex = atoi(row[0]);
		Index = atoi(row[3]);
		sEffect[0] = atoi(row[4]);
		sValue[0] = atoi(row[5]);
		sEffect[1] = atoi(row[6]);
		sValue[1] = atoi(row[7]);
		sEffect[2] = atoi(row[8]);
		sValue[2] = atoi(row[9]);
	}

	if (Index == 0) {
		SendClientMessage(conn, "Não há itens a serem recebidos");
		return;
	}

	STRUCT_ITEM item;
	memset(&item, 0, sizeof(STRUCT_ITEM));
	item.sIndex = Index;
	item.stEffect[0].cEffect = sEffect[0];
	item.stEffect[0].cValue = sValue[0];
	item.stEffect[1].cEffect = sEffect[1];
	item.stEffect[1].cValue = sValue[1];
	item.stEffect[2].cEffect = sEffect[2];
	item.stEffect[2].cValue = sValue[2];

	PutItem(conn, &item);
	
	Delivered = 1;
	sprintf(xQuery, "UPDATE mailitem SET delivered = '%d' WHERE id = '%d' ", Delivered, RowIndex);
	pc.wQuery(xQuery);

	SendClientMessage(conn, strFmt("O item [%s] foi entregue no seu inventário!", g_pItemList[Index].Name));

	MailItem(conn);
}