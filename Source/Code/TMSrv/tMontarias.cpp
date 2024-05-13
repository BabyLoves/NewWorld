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

void attMountTraje(int conn, char* pMsg) {

	if (conn <= 0 || conn >= MAX_USER)
		return;

	if (pUser[conn].Mode != USER_PLAY)
		return;

	if (pUser[conn].cSock.Sock == 0)
		return;

	MSG_SendTraje* m = (MSG_SendTraje*)pMsg;

	int Size = m->Size;

	if (Size > sizeof(MSG_SendTraje)) //CONTROLE DE SIZE
	{
		SendClientMessage(conn, "Impossível executar ação, tente mais tarde.");
		return;
	}

	if (m->Tipo < 0 || m->Tipo > 255)
		return;

	int Type = m->Tipo;
	

	STRUCT_ITEM* dest = &pMob[conn].MOB.Equip[14];

	dest->sIndex = pMob[conn].MOB.Equip[14].sIndex;
	dest->stEffect[0].cEffect = pMob[conn].MOB.Equip[14].stEffect[0].cEffect;
	dest->stEffect[0].cValue = pMob[conn].MOB.Equip[14].stEffect[0].cValue;
	dest->stEffect[1].cEffect = pMob[conn].MOB.Equip[14].stEffect[1].cEffect;
	dest->stEffect[1].cValue = pMob[conn].MOB.Equip[14].stEffect[1].cValue;
	dest->stEffect[2].cEffect = pMob[conn].MOB.Equip[14].stEffect[2].cEffect;
	dest->stEffect[2].cValue = pMob[conn].MOB.Equip[14].stEffect[2].cValue;

	for (int i = 1; i < 16; i++) {
		if (pUser[conn].Keys[i] == Type) {
			dest->stEffect[2].cValue = Type;
			SendItem(conn, ITEM_PLACE_EQUIP, 14, dest);
			SendEquip(conn, conn);
		}
	}
	return;
}

void RemoveMountTraje(int conn) {
	pUser[conn].Keys[16] = 0;
	return;
}

void RequestTraje(int conn) {
	if (conn <= 0 || conn >= MAX_USER)
		return;

	if (pUser[conn].Mode != USER_PLAY)
		return;

	if (pUser[conn].cSock.Sock == 0)
		return;

	MSG_SendTraje sm;
	memset(&sm, 0, sizeof(MSG_SendTraje));

	sm.Type = _MSG_SendTraje;
	sm.Size = sizeof(MSG_SendTraje);
	sm.ID = conn;
	sm.Tipo = 1;

	int Size = sm.Size;

	if (Size > sizeof(MSG_SendTraje))
	{
		sm.Size = 0;
		return;
	}

	if (!pUser[conn].cSock.AddMessage((char*)&sm, sizeof(MSG_SendTraje)))
		CloseUser(conn);
}

bool MountTrajeBuy(int conn, int Index) {
	int Traje = 4000 - Index;
	
	for (int i = 1; i < 16; i++) {
		if (pUser[conn].Keys[i] == 0) {
			pUser[conn].Keys[i] = Traje;
			return true;
		}
		if (i == 15 && pUser[conn].Keys[i] != 0) {
			SendClientMessage(conn, "Não há slots de trajes disponíveis");
			return false;
		}
	}
}