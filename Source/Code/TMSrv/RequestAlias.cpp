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

void RequestAlias(int conn, char* pMsg)
{
	if (conn <= 0 || conn >= MAX_USER)
		return;

	if (pUser[conn].Mode != USER_PLAY)
		return;

	if (pUser[conn].cSock.Sock == 0)
		return;

	MSG_ReqAlias* m = (MSG_ReqAlias*)pMsg;

	int Size = m->Size;

	if (Size > sizeof(MSG_ReqAlias)) //CONTROLE DE SIZE
	{
		SendClientMessage(conn, "Impossível executar ação, tente mais tarde.");
		return;
	}

	if (m->Tipo < 0)
		return;

	int Type = m->Tipo;
	int Captcha = 0;
	if (Type >= 100) {
		Captcha = m->Tipo - 100;
		Type = 5;
	}

	switch (Type) {
		case 1:
		{			
			UpdateDonate(conn);
		}break;
		case 2:
		{
			SendShopDonate(conn);
		}break;
		case 3:
		{
			SendMailItem(conn);
		}break;
		case 4:
		{
			sendRanking(conn, 0);
		}break;
		case 5:
		{
			VerificarRecaptcha(conn, Captcha);
		}break;
		case 6:
		{
			sendRanking(conn, 1);
		}break;
	}
}