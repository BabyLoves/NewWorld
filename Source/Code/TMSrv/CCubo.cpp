/*
*   Copyright (C) {2015}  {Victor Klafke, Charles TheHouse}
*
*   This program is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program.  If not, see [http://www.gnu.org/licenses/].
*
*   Contact at: victor.klafke@ecomp.ufsm.br
*/
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

#include "CCubo.h"

STRUCT_CUBOFILE CuboN;
STRUCT_CUBOFILE CuboM;
STRUCT_CUBOFILE CuboA;

const char* const CCubo::CUBO_QUEST_PATH = "../../Common/Settings/Cubo.txt";
const char* const CCubo::CUBON_QUEST_PATH = "../../Common/Settings/CuboCoordN.txt";
const char* const CCubo::CUBOM_QUEST_PATH = "../../Common/Settings/CuboCoordM.txt";
const char* const CCubo::CUBOA_QUEST_PATH = "../../Common/Settings/CuboCoordA.txt";

void CCubo::Initialize()
{
	memset(&CuboN, 0, sizeof(STRUCT_CUBOFILE));
	memset(&CuboM, 0, sizeof(STRUCT_CUBOFILE));
	memset(&CuboA, 0, sizeof(STRUCT_CUBOFILE));

	LoadCubo();
	LoadCuboCoordN();
	LoadCuboCoordM();
	LoadCuboCoordA();

	CuboN.Room = 0;
	CuboN.pRoom = 0;
	CuboM.Room = 0;
	CuboM.pRoom = 0;
	CuboA.Room = 0;
	CuboA.pRoom = 0;

	for (int room = 0; room < 25; room++)
	{
		CuboN.Mobs[room] = CUBO_N_INITIAL + room;
		CuboN.Status[room] = FALSE;
	}

	GenerateMob(CUBO_N_INITIAL, 0, 0);
}

void CCubo::MobKilled(int target, int conn, int PosX, int PosY)
{
	int GenerateIndex = pMob[target].GenerateIndex;

	if (GenerateIndex == CuboN.Mobs[CuboN.Room])
	{
		int CurrentNumMob = mNPCGen.pList[CuboN.Mobs[CuboN.Room]].CurrentNumMob;

		if (CurrentNumMob == 1)
		{
			CuboN.Status[CuboN.Room] = TRUE;

			struct tm when;
			time_t now;
			time(&now);
			when = *localtime(&now);

			int TimeNow = when.tm_sec, TimeBack = when.tm_sec;
			TimeNow += 14;

			if (TimeNow > 59)
			{
				int Sec = TimeNow - 59;
				TimeNow = Sec;
			}

			CuboN.Time[CuboN.Room] = TimeNow;

			printf("Tempo Atual: %d e Tempo do Teleporte: %d\n", TimeBack, CuboN.Time[CuboN.Room]);

			if (pUser[conn].Mode == USER_PLAY && (pMob[conn].TargetX / 128) == 13 && (pMob[conn].TargetY / 128) == 31)
			{
				char Title[96];
				sprintf_s(Title, "<<_No._%d_>>", CuboN.CurrentQuestion[CuboN.Room] + 1);
				SendBigMessage(conn, Title, CuboN.Question[CuboN.Room]);
			}

			MSG_STANDARDPARM sm;
			memset(&sm, 0, sizeof(MSG_STANDARDPARM));

			sm.Type = _MSG_StartTime;
			sm.ID = ESCENE_FIELD;
			sm.Size = sizeof(MSG_STANDARDPARM);
			sm.Parm = 14;

			MapaMulticast(13, 31, (MSG_STANDARD*)&sm, 0);
		}
	}
}

void CCubo::ProcessSecTimer()
{
	if (SecCounter % 2 == 0)
	{
		struct tm when;
		time_t now;
		time(&now);
		when = *localtime(&now);

		char UserName[NAME_LENGTH];

#pragma region Cubo N
		int Users_CuboN = GetUserInArea(1664, 3968, 1792, 4096, UserName);

		if (Users_CuboN > 0 && CuboN.pRoom > Users_CuboN)
			CuboN.pRoom = Users_CuboN;

		if (CuboN.Status[CuboN.Room] == TRUE)
		{
			if (when.tm_sec == CuboN.Time[CuboN.Room])
			{
				for (int i = 1; i < MAX_USER; i++)
				{
					if (pUser[i].Mode == USER_PLAY && (pMob[i].TargetX / 128) == 13 && (pMob[i].TargetY / 128) == 31)
					{
						int ReqTeleport = GetCuboTeleportPositionN(i, CuboN.Room);

						if (ReqTeleport)
						{
							if (CuboN.Room >= 24)
							{
								DoRecall(i);
								 
								SendMsgExp(i, "Você concluiu a Quest!", TNColor::Default, false);
								CuboN.Room = 0;
								CuboN.pRoom = 0;

								printf("Finalizou - Sala: %d / Players: %d\n", CuboN.Room, CuboN.pRoom);
							}
							else
							{
								int Bonus = 8000 + (CuboN.Room * 1000);

								DoTeleport(i, *mNPCGen.pList[CuboN.Mobs[CuboN.Room + 1]].SegmentListX, *mNPCGen.pList[CuboN.Mobs[CuboN.Room + 1]].SegmentListY);							 
								SendMsgExp(i, strFmt("Correto! Andar %d. (Bônus %d EXP)", CuboN.Room + 2, Bonus), TNColor::Default, false);
								pMob[i].MOB.Exp += Bonus;

								GenerateMob(CuboN.Mobs[CuboN.Room + 1], 0, 0);

								printf("Correto - Sala: %d / Players: %d\n", CuboN.Room, CuboN.pRoom);
							}
						}
						else
						{
							DoRecall(i);
							 
							SendMsgExp(i, "Errou!", TNColor::Default, false);
							CuboN.pRoom--;

							if (CuboN.pRoom < 0)
								CuboN.pRoom = 0;

							//int User = GetUserInArea(1664, 3968, 1792, 4096, UserName);

							if (CuboN.pRoom == 0)
							{
								CuboN.Room = 0;
								CuboN.pRoom = 0;
								ClearArea(1664, 3968, 1792, 4096);//Cubo N

								GenerateMob(CUBO_N_INITIAL, 0, 0);

								printf("Foi tudo zerado!");
							}

							printf("Errou - Sala: %d / Players: %d\n", CuboN.Room, CuboN.pRoom);
						}
					}
				}

				CuboN.Status[CuboN.Room] = FALSE;

				if (CuboN.pRoom > 0)
					CuboN.Room++;
			}
		}
	}
#pragma endregion
}

bool CCubo::LoadCubo()
{
	FILE *fp = fopen(CUBO_QUEST_PATH, "r+");

	if (fp == NULL)
		return FALSE;

	char line[1024];

	for (int x = 0; x < 25; x++)
	{
		int index = 0, num = 0;

		fgets(line, sizeof(line), fp);

		sscanf(line, "%d %d %100[^=]", &num, &index, CuboN.Question[x]);
		sscanf(line, "%d %d %100[^=]", &num, &index, CuboM.Question[x]);
		sscanf(line, "%d %d %100[^=]", &num, &index, CuboA.Question[x]);

		CuboN.CurrentQuestion[x] = num;
		CuboN.Question[x][strlen(CuboN.Question[x]) - 1] = '\0';

		CuboM.CurrentQuestion[x] = num;
		CuboM.Question[x][strlen(CuboM.Question[x]) - 1] = '\0';

		CuboA.CurrentQuestion[x] = num;
		CuboA.Question[x][strlen(CuboA.Question[x]) - 1] = '\0';

		if (index == 0)
		{
			CuboN.Answer[x] = FALSE;
			CuboM.Answer[x] = FALSE;
			CuboA.Answer[x] = FALSE;
		}
		else if (index == 1)
		{
			CuboN.Answer[x] = TRUE;
			CuboM.Answer[x] = TRUE;
			CuboA.Answer[x] = TRUE;
		}
		else
			return FALSE;
	}

	fclose(fp);
	return TRUE;
}

bool CCubo::LoadCuboCoordN()
{
	FILE *fp = fopen(CUBON_QUEST_PATH, "r+");

	if (fp == NULL)
		return FALSE;

	char line[1024];
	int Xr = 0;
	int Or = 0;

	while (fgets(line, sizeof(line), fp))
	{
		if (*line == '\n' || *line == '#')
			continue;

		char *p = line;

		while (*p != '\0')
		{
			if (*p == ',')
				*p = ' ';
			else if (*p == '[')
				*p = ' ';
			else if (*p == ']')
				*p = ' ';

			p++;
		}

		char VF;
		int indessx;

		sPoint Cord;
		memset(&Cord, 0, sizeof(sPoint));
		sscanf(line, "%c %d %4d %4d", &VF, &indessx, &Cord.PosX, &Cord.PosY);

		if (VF == 'O')
		{
			CuboN.O[Or].PosX = Cord.PosX;
			CuboN.O[Or].PosY = Cord.PosY;
			Or++;
		}
		else if (VF == 'X')
		{
			CuboN.X[Xr].PosX = Cord.PosX;
			CuboN.X[Xr].PosY = Cord.PosY;
			Xr++;
		}
	}

	fclose(fp);
	return TRUE;
}

bool CCubo::LoadCuboCoordM()
{
	FILE *fp = fopen(CUBOM_QUEST_PATH, "r+");

	if (fp == NULL)
		return FALSE;

	char line[1024];
	int Xr = 0;
	int Or = 0;

	while (fgets(line, sizeof(line), fp))
	{
		if (*line == '\n' || *line == '#')
			continue;

		char *p = line;

		while (*p != '\0')
		{
			if (*p == ',')
				*p = ' ';
			else if (*p == '[')
				*p = ' ';
			else if (*p == ']')
				*p = ' ';

			p++;
		}

		char VF;
		int indessx;

		sPoint Cord;
		memset(&Cord, 0, sizeof(sPoint));
		sscanf(line, "%c %d %4d %4d", &VF, &indessx, &Cord.PosX, &Cord.PosY);

		if (VF == 'O')
		{
			CuboM.O[Or].PosX = Cord.PosX;
			CuboM.O[Or].PosY = Cord.PosY;
			Or++;
		}
		else if (VF == 'X')
		{
			CuboM.X[Xr].PosX = Cord.PosX;
			CuboM.X[Xr].PosY = Cord.PosY;
			Xr++;
		}
	}

	fclose(fp);
	return TRUE;
}

bool CCubo::LoadCuboCoordA()
{
	FILE *fp = fopen(CUBOA_QUEST_PATH, "r+");

	if (fp == NULL)
		return FALSE;

	char line[1024];
	int Xr = 0;
	int Or = 0;

	while (fgets(line, sizeof(line), fp))
	{
		if (*line == '\n' || *line == '#')
			continue;

		char *p = line;

		while (*p != '\0')
		{
			if (*p == ',')
				*p = ' ';
			else if (*p == '[')
				*p = ' ';
			else if (*p == ']')
				*p = ' ';

			p++;
		}

		char VF;
		int indessx;

		sPoint Cord;
		memset(&Cord, 0, sizeof(sPoint));
		sscanf(line, "%c %d %4d %4d", &VF, &indessx, &Cord.PosX, &Cord.PosY);

		if (VF == 'O')
		{
			CuboA.O[Or].PosX = Cord.PosX;
			CuboA.O[Or].PosY = Cord.PosY;
			Or++;
		}
		else if (VF == 'X')
		{
			CuboA.X[Xr].PosX = Cord.PosX;
			CuboA.X[Xr].PosY = Cord.PosY;
			Xr++;
		}
	}

	fclose(fp);
	return TRUE;
}