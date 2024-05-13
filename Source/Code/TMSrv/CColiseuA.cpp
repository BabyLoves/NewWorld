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

void CCOLISEU::ColoProcessA(tm* timeinfo)
{//bySexycode
	int Rand = rand() % 100; 
#pragma region Coliseu (A)

	if (timeinfo->tm_wday != 0 && timeinfo->tm_wday != 6 && timeinfo->tm_hour == ColoHourA)
	{
		if (ColoStateA == 0 && timeinfo->tm_min == 00 && timeinfo->tm_sec >= 0)
		{
			//sprintf(temp, "Os portões do Coliseu será fechado em %d minutos.", 3);
			//SendNotice(temp);
			//Log("Coliseu[A]-log Anuncio fechamento de portao", 0, 0);
			ColoStateA = 1; 
		}

		if (ColoStateA == 1 && timeinfo->tm_min >= 3)
		{
			SetColoseumDoor(3);
			//Log("Coliseu[A]-log Fechou os portoes da frente", 0, 0);
			ColoStateA = 2;
		}

		if (ColoStateA == 2 && timeinfo->tm_min >= 4)
		{
			if (Rand >= 50)
				GenerateColoseum(COLISEU_A_INITIAL);
			if (Rand <= 49)
				GenerateColoseum(COLISEU_A_END);

			//sprintf(temp, "Os Monstros do Coliseu resurgiram.");
			//SendNotice(temp);
			//Log("Coliseu[A]-log WAVE 01 DE MOBS", 0, 0);
			ColoStateA = 3;
		}

		if (ColoStateA == 3 && timeinfo->tm_min >= 5)
		{
			SetColoseumDoor2(1);
			//SendNotice(temp);
			//Log("Coliseu[A]-log Liberou os muros de dentro", 0, 0);
			ColoStateA = 4;
		}


		if (ColoStateA == 4 && timeinfo->tm_min >= 6)
		{
			if (Rand >= 50)
				GenerateColoseum(COLISEU_A_INITIAL);
			GenerateColoseum(COLISEU_A_INITIAL);
			if (Rand <= 49)
				GenerateColoseum(COLISEU_A_END);
			GenerateColoseum(COLISEU_A_END);
			//Log("Coliseu[A]-log WAVE 02 DE MOBS", 0, 0);
			ColoStateA = 5;
		}
		if (ColoStateA == 5 && timeinfo->tm_min >= 7)
		{
			if (Rand >= 50)
				GenerateColoseum(COLISEU_A_INITIAL);
			GenerateColoseum(COLISEU_A_INITIAL);
			if (Rand <= 49)
				GenerateColoseum(COLISEU_A_END);
			GenerateColoseum(COLISEU_A_END);
			//Log("Coliseu[A]-log WAVE 03 DE MOBS", 0, 0);
			ColoStateA = 6;
		}
		if (ColoStateA == 6 && timeinfo->tm_min >= 9)
		{
			if (Rand >= 50)
				GenerateColoseum(COLISEU_A_INITIAL);
			GenerateColoseum(COLISEU_A_INITIAL);
			if (Rand <= 49)
				GenerateColoseum(COLISEU_A_END);
			GenerateColoseum(COLISEU_A_END);
			//Log("Coliseu[A]-log WAVE 04 DE MOBS", 0, 0);
			ColoStateA = 7;
		}

		if (ColoStateA == 7 && timeinfo->tm_min >= 13)
		{
			if (Rand >= 50)
				GenerateColoseum(COLISEU_A_INITIAL);
			GenerateColoseum(COLISEU_A_INITIAL);
			if (Rand <= 49)
				GenerateColoseum(COLISEU_A_END);
			GenerateColoseum(COLISEU_A_END);
			//Log("Coliseu[A]-log WAVE 05 DE MOBS", 0, 0);
			ColoStateA = 8;
		}
		if (ColoStateA == 8 && timeinfo->tm_min >= 15)
		{
			SetColoseumDoor(1);
			SetColoseumDoor2(2);
			DeleteColoseum();
			ClearArea(2604, 1708, 2648, 1744);
			//Log("Coliseu[A]-log Encerrou o Coliseu", 0, 0);
			ColoStateA = 0; 
		}
	}
#pragma endregion

}

