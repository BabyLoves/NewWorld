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

void ReqTeleport(int conn, char* pMsg) {
	MSG_ReqTeleport* m = (MSG_ReqTeleport*)pMsg;

	int Size = m->Size;

	int X = m->X;
	int Y = m->Y;

	if (conn <= 0 || conn >= MAX_USER)
		return;

	if (pUser[conn].Mode != USER_PLAY)
		return;

	if (pUser[conn].cSock.Sock == 0)
		return;

	if (X <= 0 || X >= 4000)
		return;

	if (Y <= 0 || Y >= 4000)
		return;

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

	if (Size > sizeof(MSG_ReqTeleport)) //CONTROLE DE SIZE
	{
		SendClientMessage(conn, "Impossível executar ação, tente mais tarde.");
		return;
	}

	if (pMob[conn].TargetX >= 2452 && pMob[conn].TargetY >= 1854 && pMob[conn].TargetX <= 2542 && pMob[conn].TargetY <= 1919)
	{
		SendClientMessage(conn, "Impossível se teleportar nesta Area");
		return;
	}

	if (pMob[conn].TargetX >= 1050 && pMob[conn].TargetY >= 1943 && pMob[conn].TargetX <= 1250 && pMob[conn].TargetY <= 1954)
	{
		SendClientMessage(conn, "Impossível se teleportar nesta Area");
		return;
	}

	int fX = X + rand() % 3;
	int fY = Y + rand() % 3;

	DoTeleport(conn, fX, fY);
	return;
}