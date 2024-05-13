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

void FiltroDrop(int conn, int Index) {

	if (conn <= 0 || conn >= MAX_USER)
		return;

	if (pUser[conn].Mode != USER_PLAY)
		return;

	if (pUser[conn].cSock.Sock == 0)
		return;

	if (Index <= 0 || Index > MAX_ITEMLIST)
		return;

	if (pUser[conn].FiltroDelay != 0)
	{
		int isTime = GetTickCount64() - pUser[conn].FiltroDelay;

		if (isTime < 600)
			return;

	}
	pUser[conn].FiltroDelay = GetTickCount64();

	if (pMob[conn].FiltroState == 0) {
		SendClientMessage(conn, "Ative o filtro para adicionar itens");
		return;
	}

	if (pMob[conn].MOB.Equip[13].sIndex != 3901 && pMob[conn].MOB.Equip[13].sIndex != 3902) {
		SendClientMessage(conn, "Precisa de uma Fada Azul ou Vermelha para usar essa função!");
		return;
	}

	int Lista = Index - 5720;

	if (pMob[conn].FiltroID[Lista] == 1) {
		SendClientMessage(conn, strFmt("Categoria [%s] Desativada", g_pItemList[Index].Name));
		pMob[conn].FiltroID[Lista] = 0;
		return;
	}
	int x = 0;
	for (int i = 0; i < 50; i++) {
		if (pMob[conn].FiltroID[i] == 1)
			x++;

		if (x == 10) {
			SendClientMessage(conn, "Limite de categorias ativas é 10");
			return;
		}
	}
	pMob[conn].FiltroID[Lista] = 1;
	SendClientMessage(conn, strFmt("Categoria [%s] Ativada", g_pItemList[Index].Name));
	return;
}