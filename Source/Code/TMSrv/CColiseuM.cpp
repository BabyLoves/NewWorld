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

void CCOLISEU::ColoProcessM(tm* timeinfo)
{//bySexycode
	int Rand = rand() % 100;
	 
#pragma region Coliseu (M)

	if (timeinfo->tm_wday != 0 && timeinfo->tm_wday != 6 && timeinfo->tm_hour == ColoHourM)
	{
		if (ColoStateM == 0 && timeinfo->tm_min == 00 && timeinfo->tm_sec >= 0)
		{
			//sprintf(temp, "Os portões do Coliseu será fechado em %d minutos.", 3);
			//SendNotice(temp);
			//Log("Coliseu[M]-log Anuncio fechamento de portao", 0, 0);
			ColoStateM = 1; 
		}

		if (ColoStateM == 1 && timeinfo->tm_min >= 3)
		{
			SetColoseumDoor(3);
			//Log("Coliseu[M]-log Fechou os portoes da frente", 0, 0);
			ColoStateM = 2;
		}

		if (ColoStateM == 2 && timeinfo->tm_min >= 4)
		{
			if (Rand >= 50)
				GenerateColoseum(COLISEU_M_INITIAL);
			if (Rand <= 49)
				GenerateColoseum(COLISEU_M_END);

			//sprintf(temp, "Os Monstros do Coliseu resurgiram.");
			//SendNotice(temp);
			//Log("Coliseu[M]-log WAVE 01 DE MOBS", 0, 0);
			ColoStateM = 3;
		}

		if (ColoStateM == 3 && timeinfo->tm_min >= 5)
		{
			SetColoseumDoor2(1);
			//SendNotice(temp);
			//Log("Coliseu[M]-log Liberou os muros de dentro", 0, 0);
			ColoStateM = 4;
		}


		if (ColoStateM == 4 && timeinfo->tm_min >= 6)
		{
			if (Rand >= 50)
				GenerateColoseum(COLISEU_M_INITIAL);
			GenerateColoseum(COLISEU_M_INITIAL);
			if (Rand <= 49)
				GenerateColoseum(COLISEU_M_END);
			GenerateColoseum(COLISEU_M_END);
			//Log("Coliseu[M]-log WAVE 02 DE MOBS", 0, 0);
			ColoStateM = 5;
		}
		if (ColoStateM == 5 && timeinfo->tm_min >= 7)
		{
			if (Rand >= 50)
				GenerateColoseum(COLISEU_M_INITIAL);
			GenerateColoseum(COLISEU_M_INITIAL);
			if (Rand <= 49)
				GenerateColoseum(COLISEU_M_END);
			GenerateColoseum(COLISEU_M_END);
			//Log("Coliseu[M]-log WAVE 03 DE MOBS", 0, 0);
			ColoStateM = 6;
		}
		if (ColoStateM == 6 && timeinfo->tm_min >= 9)
		{
			if (Rand >= 50)
				GenerateColoseum(COLISEU_M_INITIAL);
			GenerateColoseum(COLISEU_M_INITIAL);
			if (Rand <= 49)
				GenerateColoseum(COLISEU_M_END);
			GenerateColoseum(COLISEU_M_END);
			//Log("Coliseu[M]-log WAVE 04 DE MOBS", 0, 0);
			ColoStateM = 7;
		}

		if (ColoStateM == 7 && timeinfo->tm_min >= 13)
		{
			if (Rand >= 50)
				GenerateColoseum(COLISEU_M_INITIAL);
			GenerateColoseum(COLISEU_M_INITIAL);
			if (Rand <= 49)
				GenerateColoseum(COLISEU_M_END);
			GenerateColoseum(COLISEU_M_END);
			//Log("Coliseu[M]-log WAVE 05 DE MOBS", 0, 0);
			ColoStateM = 8;
		}
		if (ColoStateM == 8 && timeinfo->tm_min >= 15)
		{
			SetColoseumDoor(1);
			SetColoseumDoor2(2);
			DeleteColoseum();
			ClearArea(2604, 1708, 2648, 1744);
			//Log("Coliseu[M]-log Encerrou o Coliseu", 0, 0);
			ColoStateM = 0; 
		}
	}
#pragma endregion
	 

}

