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

bool StoreAgroup(int itemId)
{
	int List[] = {
		3314, 4140, 3312, 3343, 3336, 3310, 3311, 3407, 3408, 3409, 3410, 3411, 3412, 3413, 3414, 3415, 3416, 3417, 2426, 3330, 777
	};

	for (int i = 0; i < (sizeof(List) / 4); i++) {
		if (itemId == List[i])
			return true;
	}
	return false;
}

void ReqDonateShop(int conn, char* pMsg)
{
	if (conn <= 0 || conn >= MAX_USER)
		return;

	if (pUser[conn].Mode != USER_PLAY)
		return;

	if (pUser[conn].cSock.Sock == 0)
		return;

	MSG_ReqShopDonate* m = (MSG_ReqShopDonate*)pMsg;

	int Size = m->Size;

	if (Size > sizeof(MSG_ReqShopDonate)) //CONTROLE DE SIZE
	{
		SendClientMessage(conn, "Impossível executar ação, tente mais tarde.");
		return;
	}

	if (pUser[conn].DonateShopDelay != 0)
	{
		int isTime = GetTickCount64() - pUser[conn].DonateShopDelay; // ATRASO PACOTE

		if (isTime < 3000)
		{
			SendClientMessage(conn, "Aguarde 3 segundo para uma nova Tentativa.");
			return;
		}

	}
	pUser[conn].DonateShopDelay = GetTickCount64();

	int nShop = m->Store;
	int nPage = m->Page;
	int nItemPos = m->ItemPos;
	int nQnt = m->Qnt;

	if (nShop < 0 || nShop > 2)
		return;

	if (nPage < 0 || nPage > 2)
		return;

	if (nItemPos < 0 || nItemPos > 14)
		return;

	if (nQnt <= 0 || nQnt > 120)
		return;

	int ItemIndex = cStoreItens[nShop][nPage][nItemPos][0];
	int Price = (cStoreItens[nShop][nPage][nItemPos][1] * nQnt);

	if (ItemIndex <= 0 || ItemIndex >= MAX_ITEMLIST)
		return;

	auto& pc = cSQL::instance();

	int Donate = 0;

	sprintf(hQuery, "SELECT * FROM `accounts` WHERE `username` = '%s'", pUser[conn].AccountName);
	MYSQL_ROW row;
	MYSQL* wSQL = pc.wStart();
	MYSQL_RES* result = pc.wRes(wSQL, hQuery);

	if (result == NULL)
		return;

	while ((row = mysql_fetch_row(result)) != NULL)
	{
		Donate = atoi(row[6]);
	}

	if (Donate < Price)
	{
		SendClientMessage(conn, "Saldo de Diamantes Insuficiente");
		return;
	}

	int FreeSlot = 0;
	int slotsInv = 30;
	int SlotReq = 1;

	bool Agroup = false;

	if (StoreAgroup(ItemIndex) == true)
		Agroup = true;

	if (Agroup == false)
		SlotReq = nQnt;

	if (pMob[conn].MOB.Carry[60].sIndex == 3467)
		slotsInv += 15;
	if (pMob[conn].MOB.Carry[61].sIndex == 3467)
		slotsInv += 15;

	for (int i = 0; i < slotsInv; i++) {
		if (pMob[conn].MOB.Carry[i].sIndex == 0)
			FreeSlot += 1;
	}
	if (FreeSlot < SlotReq) {
		SendClientMessage(conn, "Não há espaço disponível no Inventário");
		return;
	}

	STRUCT_ITEM item;
	memset(&item, 0, sizeof(STRUCT_ITEM));
	item.sIndex = ItemIndex;
	item.stEffect[0].cEffect = Agroup ? 61 : 0;
	item.stEffect[0].cValue = Agroup ? nQnt : 0;

	int tQnt = nQnt;

	if (Agroup == false)
	{
		while (nQnt >= 1) {
			PutItem(conn, &item);
			nQnt -= 1;
		}
	}
	else {
		PutItem(conn, &item);
	}
	
	sprintf(xQuery, "UPDATE accounts SET donate = '%d' WHERE username = '%s' ", (Donate - Price), pUser[conn].AccountName);
	pc.wQuery(xQuery);

	SendClientMessage(conn, strFmt("Comprou [x%d] %s por [%d] Diamantes", tQnt, g_pItemList[ItemIndex].Name, Price));
	ItemLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, strFmt("Comprou [x%d] %s por [%d] Diamantes | Restantes: %d", tQnt, g_pItemList[ItemIndex].Name, Price, Donate - Price));
	UpdateDonate(conn);
}

void TradeDonate(int conn, char* pMsg)
{

	MSG_SendPix* m = (MSG_SendPix*)pMsg;

	int Size = m->Size;

	if (Size > 24) //CONTROLE DE SIZE
	{
		SendClientMessage(conn, "Impossível executar ação, tente mais tarde.");
		return;
	}

	if (conn <= 0 || conn >= MAX_USER)
		return;

	if (pUser[conn].Mode != USER_PLAY)
		return;

	if (pUser[conn].cSock.Sock == 0)
		return;

	int value = m->qnt;	

	if (value < 100)
		return;

	if (pUser[conn].Atraso != 0)
	{
		int isTime = GetTickCount64() - pUser[conn].Atraso; // ATRASO PACOTE

		if (isTime < 3000)
		{
			SendClientMessage(conn, "Aguarde 3 segundo para uma nova Tentativa.");
			return;
		}

	}
	pUser[conn].Atraso = GetTickCount64();

	auto& pc = cSQL::instance();

	int Donate = 0;
	std::string mypix;
	sprintf(hQuery, "SELECT * FROM `accounts` WHERE `username` = '%s'", pUser[conn].AccountName);
	MYSQL_ROW row;
	MYSQL* wSQL = pc.wStart();
	MYSQL_RES* result = pc.wRes(wSQL, hQuery);

	if (result == NULL)
		return;

	while ((row = mysql_fetch_row(result)) != NULL)
	{
		mypix = row[20];
		Donate = atoi(row[6]);
	}
	pc.wQuery(xQuery);

	if (Donate < value)
	{
		SendClientMessage(conn, "Saldo Insuficiente");
		return;
	}

	auto& pc2 = cSQL::instance();

	int Donate2 = 0;
	std::string pixrecive;
	std::string pixkey = { m->chave };
	
	sprintf(hQuery, "SELECT * FROM `accounts` WHERE `pix` = '%s'", m->chave);
	MYSQL_ROW row2;
	MYSQL* wSQL2 = pc2.wStart();
	MYSQL_RES* result2 = pc2.wRes(wSQL2, hQuery);

	if (result2 == NULL)
		return;

	while ((row2 = mysql_fetch_row(result2)) != NULL)
	{
		pixrecive = row2[20];
		Donate2 = atoi(row2[6]);
	}

	if (pixrecive != pixkey) {
		SendClientMessage(conn, "Jogador Não Encontrado");
		return;
	}

	if (mypix == pixrecive)	{
		SendClientMessage(conn, "Não pode enviar para si mesmo");
		return;
	}

	int Value = value;

	sprintf(xQuery, "UPDATE accounts SET donate = '%d' WHERE pix = '%s' ", (Donate2 + Value), m->chave);
	pc2.wQuery(xQuery);

	auto& pc3 = cSQL::instance();
	sprintf(xQuery, "UPDATE accounts SET donate = '%d' WHERE username = '%s' ", (Donate - value), pUser[conn].AccountName);
	pc3.wQuery(xQuery);

	SendClientMessage(conn, strFmt("[%d] Diamantes enviados para a chave[%s]", value, m->chave));
	ItemLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, strFmt("[%d] Diamantes enviados para a chave[%s] | Saldo: %d", value, m->chave, Donate - value));
	UpdateDonate(conn);
	return;
}

void UpdateShopDonate1() {
	auto& pc = cSQL::instance();

	int Index[45] = {};
	int Value[45] = {};
	int Estoque[45] = {};
	int i = 0;

	sprintf(hQuery, "SELECT * FROM `donatestore1` LIMIT 45");
	MYSQL_ROW row;
	MYSQL* wSQL = pc.wStart();
	MYSQL_RES* result = pc.wRes(wSQL, hQuery);

	if (result == NULL)
		return;

	while ((row = mysql_fetch_row(result)) != NULL)
	{		
		Index[i] = atoi(row[2]);
		Value[i] = atoi(row[3]);
		Estoque[i] = atoi(row[4]);
		i++;
	}

	for (int y = 0; y < 15; y++) {		
		cStoreItens[0][0][y][0] = Index[y];
		cStoreItens[0][0][y][1] = Value[y];
		cStoreItens[0][0][y][2] = Estoque[y];
	}
	for (int z = 15; z < 30; z++) {
		cStoreItens[0][1][z - 15][0] = Index[z];
		cStoreItens[0][1][z - 15][1] = Value[z];
		cStoreItens[0][1][z - 15][2] = Estoque[z];
	}
	for (int x = 30; x < 45; x++) {
		cStoreItens[0][2][x - 30][0] = Index[x];
		cStoreItens[0][2][x - 30][1] = Value[x];
		cStoreItens[0][2][x - 30][2] = Estoque[x];
	}
}
void UpdateShopDonate2() {
	auto& pc = cSQL::instance();

	int Index[45] = {};
	int Value[45] = {};
	int Estoque[45] = {};
	int i = 0;

	sprintf(hQuery, "SELECT * FROM `donatestore2` LIMIT 45");
	MYSQL_ROW row;
	MYSQL* wSQL = pc.wStart();
	MYSQL_RES* result = pc.wRes(wSQL, hQuery);

	if (result == NULL)
		return;

	while ((row = mysql_fetch_row(result)) != NULL)
	{
		Index[i] = atoi(row[2]);
		Value[i] = atoi(row[3]);
		Estoque[i] = atoi(row[4]);
		i++;
	}

	for (int y = 0; y < 15; y++) {
		cStoreItens[1][0][y][0] = Index[y];
		cStoreItens[1][0][y][1] = Value[y];
		cStoreItens[1][0][y][2] = Estoque[y];
	}
	for (int z = 15; z < 30; z++) {
		cStoreItens[1][1][z - 15][0] = Index[z];
		cStoreItens[1][1][z - 15][1] = Value[z];
		cStoreItens[1][1][z - 15][2] = Estoque[z];
	}
	for (int x = 30; x < 45; x++) {
		cStoreItens[1][2][x - 30][0] = Index[x];
		cStoreItens[1][2][x - 30][1] = Value[x];
		cStoreItens[1][2][x - 30][2] = Estoque[x];
	}
}
void UpdateShopDonate3() {
	auto& pc = cSQL::instance();

	int Index[45] = {};
	int Value[45] = {};
	int Estoque[45] = {};
	int i = 0;

	sprintf(hQuery, "SELECT * FROM `donatestore3` LIMIT 45");
	MYSQL_ROW row;
	MYSQL* wSQL = pc.wStart();
	MYSQL_RES* result = pc.wRes(wSQL, hQuery);

	if (result == NULL)
		return;

	while ((row = mysql_fetch_row(result)) != NULL)
	{
		Index[i] = atoi(row[2]);
		Value[i] = atoi(row[3]);
		Estoque[i] = atoi(row[4]);
		i++;
	}

	for (int y = 0; y < 15; y++) {
		cStoreItens[2][0][y][0] = Index[y];
		cStoreItens[2][0][y][1] = Value[y];
		cStoreItens[2][0][y][2] = Estoque[y];
	}
	for (int z = 15; z < 30; z++) {
		cStoreItens[2][1][z - 15][0] = Index[z];
		cStoreItens[2][1][z - 15][1] = Value[z];
		cStoreItens[2][1][z - 15][2] = Estoque[z];
	}
	for (int x = 30; x < 45; x++) {
		cStoreItens[2][2][x - 30][0] = Index[x];
		cStoreItens[2][2][x - 30][1] = Value[x];
		cStoreItens[2][2][x - 30][2] = Estoque[x];
	}
}

void SendShopDonate(int conn) {

	if (conn <= 0 || conn >= MAX_USER)
		return;

	if (pUser[conn].Mode != USER_PLAY)
		return;

	if (pUser[conn].cSock.Sock == 0)
		return;

	if (pUser[conn].RequestShopDelay != 0)
	{
		int isTime = GetTickCount64() - pUser[conn].RequestShopDelay; // ATRASO PACOTE

		if (isTime < 15000)
		{
			return;
		}

	}
	pUser[conn].RequestShopDelay = GetTickCount64();


	MSG_UpdateDonateStore sm;
	memset(&sm, 0, sizeof(MSG_UpdateDonateStore));

	sm.Type = _MSG_UpdateDonateStore;
	sm.Size = sizeof(MSG_UpdateDonateStore);
	sm.ID = conn;

	for (int i = 0; i < 3; i++) {
		for (int x = 0; x < 3; x++) {
			for (int z = 0; z < 15; z++) {
				for (int c = 0; c < 3; c++) {
					sm.cStoreItens[i][x][z][c] = cStoreItens[i][x][z][c];
				}
			}
		}
	}

	int Size = sm.Size;

	if (Size > sizeof(MSG_UpdateDonateStore))
	{
		sm.Size = 0;
		return;
	}

	if (!pUser[conn].cSock.AddMessage((char*)&sm, sizeof(MSG_UpdateDonateStore)))
		CloseUser(conn);
}