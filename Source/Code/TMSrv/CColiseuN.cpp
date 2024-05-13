#include <Windows.h>
#include <stdio.h>
#include <fcntl.h>
#include <time.h>
#include <math.h>
#include <io.h>
#include <errno.h>

#include "..\Basedef.h"
#include "..\CPSock.h"
#include "..\ItemEffect.h"
#include "Language.h"

#include "CItem.h"
#include "Server.h"
#include "GetFunc.h"
#include "SendFunc.h"
#include "ProcessClientMessage.h"
#include "ProcessDBMessage.h"
#include "CReadFiles.h"
#include "CColiseu.h"

void CCOLISEU::ColoProcessN(tm* timeinfo)
{//bySexycode
	int Rand = rand() % 100;

#pragma region Coliseu (N)

	if (timeinfo->tm_wday != 0 && timeinfo->tm_wday != 6 && timeinfo->tm_hour == ColoHourN)
	{
		if (ColoStateN == 0 && timeinfo->tm_min == 00 && timeinfo->tm_sec >= 0)
		{
			SendNotice(strFmt("Os portões do Coliseu será fechado em %d minutos.", 3));
			//Log("Coliseu[N]-log Anuncio fechamento de portao", 0, 0);
			ColoStateN = 1; 
		}

		if (ColoStateN == 1 && timeinfo->tm_min >= 3)
		{
			SetColoseumDoor(3);
			//Log("Coliseu[N]-log Fechou os portoes da frente", 0, 0);
			ColoStateN = 2;
		}

		if (ColoStateN == 2 && timeinfo->tm_min >= 4)
		{
			if (Rand >= 50)
				GenerateColoseum(COLISEU_N_INITIAL);
			if (Rand <= 49)
				GenerateColoseum(COLISEU_N_END);

			SendNotice("Os Monstros do Coliseu resurgiram.");
			//Log("Coliseu[N]-log WAVE 01 DE MOBS", 0, 0);
			ColoStateN = 3;
		}

		if (ColoStateN == 3 && timeinfo->tm_min >= 5)
		{
			SetColoseumDoor2(1);
			//SendNotice(temp);
			//Log("Coliseu[N]-log Liberou os muros de dentro", 0, 0);
			ColoStateN = 4;
		}


		if (ColoStateN == 4 && timeinfo->tm_min >= 6)
		{
			if (Rand >= 50)
				GenerateColoseum(COLISEU_N_INITIAL);
			GenerateColoseum(COLISEU_N_INITIAL);
			if (Rand <= 49)
				GenerateColoseum(COLISEU_N_END);
			GenerateColoseum(COLISEU_N_END);
			//Log("Coliseu[N]-log WAVE 02 DE MOBS", 0, 0);
			ColoStateN = 5;
		}
		if (ColoStateN == 5 && timeinfo->tm_min >= 7)
		{
			if (Rand >= 50)
				GenerateColoseum(COLISEU_N_INITIAL);
			GenerateColoseum(COLISEU_N_INITIAL);
			if (Rand <= 49)
				GenerateColoseum(COLISEU_N_END);
			GenerateColoseum(COLISEU_N_END);
			//Log("Coliseu[N]-log WAVE 03 DE MOBS", 0, 0);
			ColoStateN = 6;
		}
		if (ColoStateN == 6 && timeinfo->tm_min >= 9)
		{
			if (Rand >= 50)
				GenerateColoseum(COLISEU_N_INITIAL);
			GenerateColoseum(COLISEU_N_INITIAL);
			if (Rand <= 49)
				GenerateColoseum(COLISEU_N_END);
			GenerateColoseum(COLISEU_N_END);
			//Log("Coliseu[N]-log WAVE 04 DE MOBS", 0, 0);
			ColoStateN = 7;
		}

		if (ColoStateN == 7 && timeinfo->tm_min >= 13)
		{
			if (Rand >= 50)
				GenerateColoseum(COLISEU_N_INITIAL);
			GenerateColoseum(COLISEU_N_INITIAL);
			if (Rand <= 49)
				GenerateColoseum(COLISEU_N_END);
			GenerateColoseum(COLISEU_N_END);
			//Log("Coliseu[N]-log WAVE 05 DE MOBS", 0, 0);
			ColoStateN = 8;
		} 
		if (ColoStateN == 8 && timeinfo->tm_min >= 15)
		{
			SetColoseumDoor(1);
			SetColoseumDoor2(2);
			DeleteColoseum(); 
			ClearArea(2604, 1708, 2648, 1744);
			//Log("Coliseu[N]-log Encerrou o Coliseu", 0, 0);
			ColoStateN = 0; 
		}
	}
#pragma endregion 
}

 