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
#include <string.h>
#include <string>
#include <vector>
#include <list>
#include <map>

#include "CNPCGene.h"
#include "Server.h"
#include "wMySQL.h"

using namespace std;

CNPCGenerator::CNPCGenerator()
{
	NumList = 0;
	NumRegion = 0;

	memset(pList, 0, sizeof(NPCGENLIST)* MAX_NPCGENERATOR);
	memset(pRegion, 0, sizeof(MAPREGION)* MAX_NPCGENERATOR);
}

CNPCGenerator::~CNPCGenerator()
{
}

int CNPCGenerator::ReadNPCGenerator()
{
	FILE *fp = fopen("NPCGener.new.txt", "wt");
	FILE *fs = fopen("NPCGener.txt", "rt");

	if (fs == NULL)
	{
		MessageBoxA(hWndMain, "NPCGener.txt¦í ¥", "+-¦Ô+¡ ¢Ããð", MB_OK);

		return 0;
	}

	int Num = -1;

	char tp[1024];

	memset(tp, 0, 1023);

	while (1)
	{
		char *getret = fgets(tp, 1024, fs);

		if (getret == NULL)
			break;


		if (tp[0] == 47) //'\ '
		{
			char tmp1[128];
			char tmp2[128];

			sscanf(tp, "%s %s", &tmp1, &tmp2);

			if (tmp1 && tmp2 && tmp2[0] != '*')
				fprintf(fp, "\n\n%s", &tp);
		}

		else if (tp[0] == '#')
		{
			Num++;

			for (int i = 0; i < 5; i++)
			{
				pList[Num].SegmentListX[i] = 0;
				pList[Num].SegmentListY[i] = 0;
				pList[Num].SegmentRange[i] = 0;
			}
			fprintf(fp, "// ********************************************\n");

			if (tp[1] == '*')
				fprintf(fp, "#*\t[%4d]\n", Num);

			else
				fprintf(fp, "#\t[%4d]\n", Num);
		}

		else if (tp[0] != 13)
		{
			int pars = ParseString(Num, tp);

			if (pars == 0)
				continue;

			char tmp1[128];
			char tmp2[128];

			sscanf(tp, "%s %s", &tmp1, &tmp2);

			int len = strlen(tmp1);

			if (len > 8 && tmp1[0] != 'Í')
				fprintf(fp, "\t%s\t%s\n", &tmp1, &tmp2);

			else if(tmp1[0] != 'Í')
				fprintf(fp, "\t%s\t\t%s\n", &tmp1, &tmp2);
		}
	}

	NumList = Num + 1;

	fclose(fs);
	fclose(fp);

	return 1;
}

int CNPCGenerator::ParseString(int i, char *str)
{
	char str1[128];
	str1[0] = 0;

	char str2[128];
	str2[0] = 0;

	char str3[128];
	str3[0] = 0;

	int  value = 0;
	int secondvalue = 0;

	sscanf(str, "%s %s %s", str1, str2, str3);

	if (str[0] == 47)
		return FALSE;

	if (str[0] == 0) 
		return FALSE;

	value = atoi(str2);
	secondvalue = atoi(str3);

	if (strlen(str2) > 80)
		return FALSE;


	if (!strcmp(str1, "MinuteGenerate:"))
		pList[i].MinuteGenerate = value;

	else if (!strcmp(str1, "MaxNumMob:"))
		pList[i].MaxNumMob = value;

	else if (!strcmp(str1, "MinGroup:"))
		pList[i].MinGroup = value;

	else if (!strcmp(str1, "MaxGroup:"))
		pList[i].MaxGroup = value;

	else if (!strcmp(str1, "Leader:"))
	{
		if (!strcmp(str2, "0"))
			return FALSE;

		strncpy(pList[i].Leader.MobName, str2, NAME_LENGTH);

		BOOL ret = ReadMob(&pList[i].Leader, "npc");

		if (ret == FALSE)
			MessageBox(hWndMain, str2, "Can't read NPC file in NPCGener.txt", NULL);

		else
			pList[i].Mode = MOB_USE;
	}

	else if (!strcmp(str1, "Follower:"))
	{
		if (!strcmp(str2, "0"))
			return FALSE;

		strncpy(pList[i].Follower.MobName, str2, NAME_LENGTH);

		BOOL ret = ReadMob(&pList[i].Follower, "npc");

		if (ret == FALSE)
			MessageBox(hWndMain, str2, "Can't read NPC file in NPCGener.txt", NULL);

		else
			pList[i].Mode = MOB_USE;
	}
	else if (!strcmp(str1, "RouteType:"))
		pList[i].RouteType = value;

	else if (!strcmp(str1, "Formation:"))
		pList[i].Formation = value;

	else if (!strcmp(str1, "StartWait:"))
		pList[i].SegmentWait[0] = value;

	else if (!strcmp(str1, "StartRange:"))
		pList[i].SegmentRange[0] = value;

	else if (!strcmp(str1, "StartX:"))
	{
		if(value <= 0 || value >= MAX_GRIDX)
			MessageBoxA(NULL, str1, pList[i].Leader.MobName, MB_OK);

		pList[i].SegmentListX[0] = value;
	}
	else if (!strcmp(str1, "StartY:"))
	{
		if(value <= 0 || value >= MAX_GRIDX)
			MessageBoxA(NULL, str1, pList[i].Leader.MobName, MB_OK);
		pList[i].SegmentListY[0] = value;
	}
	else if (!strcmp(str1, "DestRange:"))
		pList[i].SegmentRange[4] = value;

	else if (!strcmp(str1, "DestX:"))
		pList[i].SegmentListX[4] = value;

	else if (!strcmp(str1, "DestY:"))
		pList[i].SegmentListY[4] = value;

	else if (!strcmp(str1, "DestWait:"))
		pList[i].SegmentWait[4] = value;

	else if (!strcmp(str1, "Segment1Range:"))
		pList[i].SegmentRange[1] = value;

	else if (!strcmp(str1, "Segment1X:"))
		pList[i].SegmentListX[1] = value;

	else if (!strcmp(str1, "Segment1Y:"))
		pList[i].SegmentListY[1] = value;

	else if (!strcmp(str1, "Segment1Wait:"))
		pList[i].SegmentWait[1] = value;

	else if (!strcmp(str1, "Segment2Range:"))
		pList[i].SegmentRange[2] = value;

	else if (!strcmp(str1, "Segment2X:"))
		pList[i].SegmentListX[2] = value;

	else if (!strcmp(str1, "Segment2Y:"))
		pList[i].SegmentListY[2] = value;

	else if (!strcmp(str1, "Segment2Wait:"))
		pList[i].SegmentWait[2] = value;

	else if (!strcmp(str1, "Segment3Range:"))
		pList[i].SegmentRange[3] = value;

	else if (!strcmp(str1, "Segment3X:"))
		pList[i].SegmentListX[3] = value;

	else if (!strcmp(str1, "Segment3Y:"))
		pList[i].SegmentListY[3] = value;

	else if (!strcmp(str1, "Segment3Wait:"))
		pList[i].SegmentWait[3] = value;

	else if (!strcmp(str1, "StartAction:"))
		SetAct(pList[i].SegmentAction[0], str2);

	else if (!strcmp(str1, "Segment1Action:"))
		SetAct(pList[i].SegmentAction[1], str2);

	else if (!strcmp(str1, "Segment2Action:"))
		SetAct(pList[i].SegmentAction[2], str2);

	else if (!strcmp(str1, "Segment3Action:"))
		SetAct(pList[i].SegmentAction[3], str2);

	else
		return FALSE;

	return TRUE;
}

void CNPCGenerator::ReadRegion()
{
	FILE *fp = NULL;

	fp = fopen("Regions.txt", "rb");

	if (fp == NULL)
	{
		MessageBoxA(hWndMain, "Não foi possivel carregar regions.txt", "WARNING!", MB_OK);
		return;
	}

	while (1)
	{
		char *ret = fgets(temp, 1023, fp);

		if (ret == NULL)
			break;

		sscanf(temp, "%d, %d, %d, %d = %s", &pRegion[NumRegion].minX, &pRegion[NumRegion].minY, &pRegion[NumRegion].maxX, &pRegion[NumRegion].maxY, pRegion[NumRegion].RegionName);

		NumRegion++;
	}
	fclose(fp);
}

void CNPCGenerator::DropList()
{
	list<char*> MobList;
	int Number = 0;

	auto& pc = cSQL::instance();
	sprintf(xQuery, "TRUNCATE `droplist`");
	pc.wQuery(xQuery);

	for (int i = 0; i < NumList; i++)
	{
		int Leader = 1;
		int Follower = 1;

		for (list<char*>::iterator l = MobList.begin(); l != MobList.end(); ++l)
		{
			if (strncmp(*l, pList[i].Leader.MobName, strlen(pList[i].Leader.MobName)) == 0)
				Leader = 0;

			if (strncmp(*l, pList[i].Follower.MobName, strlen(pList[i].Leader.MobName)) == 0)
				Follower = 0;
		}

		if (Leader == 0 && Follower == 0)
			continue;

		if (pList[i].MinuteGenerate == -1)
			continue;

		STRUCT_MOB* MOB = &pList[i].Leader;

		if (MOB->Merchant != 0)
			continue;

		int EmptyMob = 0;

		for (int x = 0; x < MAX_CARRY; x++) {
			if (MOB->Carry[x].sIndex != 0)
				EmptyMob = 1;
		}

		if (EmptyMob == 0)
			continue;

		if (Leader)
		{	
			
			sprintf(xQuery, "INSERT INTO `droplist` (`nome`) VALUES ('%s')", pList[i].Leader.MobName);
			pc.wQuery(xQuery);

			int region = 0;

			int x = mNPCGen.pList[i].SegmentListX[0];
			int y = mNPCGen.pList[i].SegmentListY[0];

			//armia
			if ((x >= 2171 && y >= 2045 && x <= 2720 && y <= 2322) ||
				(x >= 2055 && y >= 1927 && x <= 2166 && y <= 2059) || 
				(x >= 2164 && y >= 2054 && x <= 2684 && y <= 2170) || 
				(x >= 2313 && y >= 2170 && x <= 2428 && y <= 2296))
				region = 1;

			//erion
			else if (x >= 2435 && y >= 1914 && x <= 2680 && y <= 2168)
				region = 2;

			//arzan
			else if ((x >= 1788 && y >= 1538 && x <= 2185 && y <= 1785) ||
				(x >= 2180 && y >= 1533 && x <= 2435 && y <= 1787) ||
				(x >= 2187 && y >= 1155 && x <= 2298 && y <= 1297) ||
				(x >= 2179 && y >= 1293 && x <= 2295 && y <= 1534))
				region = 3;

			//deserto
			else if ((x >= 1137 && y >= 1669 && x <= 1282 && y <= 1786) ||
				(x >= 1282 && y >= 1664 && x <= 1396 && y <= 1785) ||
				(x >= 1283 && y >= 1788 && x <= 1397 && y <= 1910) ||
				(x >= 1397 && y >= 1671 && x <= 1521 && y <= 1785) ||
				(x >= 1522 && y >= 1675 && x <= 1669 && y <= 1787))
				region = 4;

			//gelo
			else if (x >= 3391 && y >= 2649 && x <= 4027 && y <= 3255)
				region = 5;

			//dungeon
			else if ((x >= 127 && y >= 3710 && x <= 767 && y <= 6841) ||
				(x >= 381 && y >= 3841 && x <= 511 && y <= 4086) ||
				(x >= 632 && y >= 3847 && x <= 1022 && y <= 4091) ||
				(x >= 898 && y >= 3712 && x <= 1143 && y <= 3830))
				region = 6;

			//submundo
			else if ((x >= 1283 && y >= 3714 && x <= 1538 && y <= 3838) ||
				(x >= 1153 && y >= 3966 && x <= 1533 && y <= 4089))
				region = 7;

			//kefra
			else if ((x >= 2179 && y >= 3850 && x <= 2303 && y <= 4091) ||
				(x >= 2304 && y >= 3850 && x <= 2435 && y <= 4091) ||
				(x >= 2436 && y >= 3850 && x <= 2551 && y <= 4093))
				region = 8;

			//lan n
			else if (x >= 3581 && y >= 3583 && x <= 3705 && y <= 3705)
				region = 9;

			//lan m
			else if (x >= 3717 && y >= 3463 && x <= 3833 && y <= 3577)
				region = 10;

			//lan a
			else if (x >= 3851 && y >= 3595 && x <= 3977 && y <= 3707)
				region = 11;

			//vale
			else if (x >= 2191 && y >= 3600 && x <= 2291 && y <= 3695)
				region = 12;

			
			sprintf(xQuery, "UPDATE droplist SET region = '%d' WHERE nome = '%s'", region, pList[i].Leader.MobName);
			pc.wQuery(xQuery);

			int Slot = 0;

			for (int k = 0; k < MAX_CARRY; k++)
			{									
				sprintf(xQuery, "UPDATE droplist SET slot%d = '%d' WHERE nome = '%s'", k, MOB->Carry[k].sIndex, pList[i].Leader.MobName);
				pc.wQuery(xQuery);
				dListItem[Number][Slot] = MOB->Carry[k].sIndex;
				Slot++;
			}
			Number++;
			MobList.push_back(MOB->MobName);
		}
	}
}

void CNPCGenerator::UpdateDropList()
{
	list<char*> MobList;
	int Number = 0;
	
	auto& pc = cSQL::instance();

	for (int i = 0; i < NumList; i++)
	{
		int Leader = 1;
		int Follower = 1;

		for (list<char*>::iterator l = MobList.begin(); l != MobList.end(); ++l)
		{
			if (strncmp(*l, pList[i].Leader.MobName, strlen(pList[i].Leader.MobName)) == 0)
				Leader = 0;

			if (strncmp(*l, pList[i].Follower.MobName, strlen(pList[i].Leader.MobName)) == 0)
				Follower = 0;
		}

		if (Leader == 0 && Follower == 0)
			continue;

		if (pList[i].MinuteGenerate == -1)
			continue;

		STRUCT_MOB* MOB = &pList[i].Leader;

		if (MOB->Merchant != 0)
			continue;

		int EmptyMob = 0;

		for (int x = 0; x < MAX_CARRY; x++) {
			if (MOB->Carry[x].sIndex != 0)
				EmptyMob = 1;
		}

		if (EmptyMob == 0)
			continue;

		if (Leader)
		{

			int region = 0;

			int x = mNPCGen.pList[i].SegmentListX[0];
			int y = mNPCGen.pList[i].SegmentListY[0];

			//armia
			if ((x >= 2171 && y >= 2045 && x <= 2720 && y <= 2322) ||
				(x >= 2055 && y >= 1927 && x <= 2166 && y <= 2059) ||
				(x >= 2164 && y >= 2054 && x <= 2684 && y <= 2170) ||
				(x >= 2313 && y >= 2170 && x <= 2428 && y <= 2296))
				region = 1;

			//erion
			else if (x >= 2435 && y >= 1914 && x <= 2680 && y <= 2168)
				region = 2;

			//arzan
			else if ((x >= 1788 && y >= 1538 && x <= 2185 && y <= 1785) ||
				(x >= 2180 && y >= 1533 && x <= 2435 && y <= 1787) ||
				(x >= 2187 && y >= 1155 && x <= 2298 && y <= 1297) ||
				(x >= 2179 && y >= 1293 && x <= 2295 && y <= 1534))
				region = 3;

			//deserto
			else if ((x >= 1137 && y >= 1669 && x <= 1282 && y <= 1786) ||
				(x >= 1282 && y >= 1664 && x <= 1396 && y <= 1785) ||
				(x >= 1283 && y >= 1788 && x <= 1397 && y <= 1910) ||
				(x >= 1397 && y >= 1671 && x <= 1521 && y <= 1785) ||
				(x >= 1522 && y >= 1675 && x <= 1669 && y <= 1787))
				region = 4;

			//gelo
			else if (x >= 3391 && y >= 2649 && x <= 4027 && y <= 3255)
				region = 5;

			//dungeon
			else if ((x >= 127 && y >= 3710 && x <= 767 && y <= 6841) ||
				(x >= 381 && y >= 3841 && x <= 511 && y <= 4086) ||
				(x >= 632 && y >= 3847 && x <= 1022 && y <= 4091) ||
				(x >= 898 && y >= 3712 && x <= 1143 && y <= 3830))
				region = 6;

			//submundo
			else if ((x >= 1283 && y >= 3714 && x <= 1538 && y <= 3838) ||
				(x >= 1153 && y >= 3966 && x <= 1533 && y <= 4089))
				region = 7;

			//kefra
			else if ((x >= 2179 && y >= 3850 && x <= 2303 && y <= 4091) ||
				(x >= 2304 && y >= 3850 && x <= 2435 && y <= 4091) ||
				(x >= 2436 && y >= 3850 && x <= 2551 && y <= 4093))
				region = 8;

			//lan n
			else if (x >= 3581 && y >= 3583 && x <= 3705 && y <= 3705)
				region = 9;

			//lan m
			else if (x >= 3717 && y >= 3463 && x <= 3833 && y <= 3577)
				region = 10;

			//lan a
			else if (x >= 3851 && y >= 3595 && x <= 3977 && y <= 3707)
				region = 11;

			//vale
			else if (x >= 2173 && y >= 3583 && x <= 2307 && y <= 3711)
				region = 12;


			sprintf(xQuery, "UPDATE droplist SET region = '%d' WHERE nome = '%s'", region, pList[i].Leader.MobName);
			pc.wQuery(xQuery);

			int Slot = 0;

			for (int k = 0; k < MAX_CARRY; k++)
			{
				if (MOB->Carry[k].sIndex != dListItem[Number][Slot]) {
					sprintf(xQuery, "UPDATE droplist SET slot%d = '%d' WHERE nome = '%s'", k, MOB->Carry[k].sIndex, pList[i].Leader.MobName);
					pc.wQuery(xQuery);
				}
				dListItem[Number][Slot] = MOB->Carry[k].sIndex;
				Slot++;
			}
			Number++;
			MobList.push_back(MOB->MobName);
		}
	}
}

//void CNPCGenerator::DropList()
//{
//	list<char*> MobList;
//	int Number = 0;
//
//	char filename[256];
//	strncpy(filename, "Zona_Desconhecida", sizeof(filename));
//	sprintf_s(temp, "./Drop/%s.txt", filename);
//	FILE* fp = fopen(temp, "a+");
//
//	for (int y = 0; y < 170; y++) {
//		for (int x = 0; x < 64; x++)
//			dListItem[y][x] = 0;
//
//		strncpy(dListMobName[y], "", 16);
//	}
//
//	for (int i = 0; i < NumList; i++)
//	{
//		int Leader = 1;
//		int Follower = 1;
//		
//		for (list<char*>::iterator l = MobList.begin(); l != MobList.end(); ++l)
//		{
//			if (strncmp(*l, pList[i].Leader.MobName, strlen(pList[i].Leader.MobName)) == 0)
//				Leader = 0;
//
//			if (strncmp(*l, pList[i].Follower.MobName, strlen(pList[i].Leader.MobName)) == 0)
//				Follower = 0;
//		}
//
//		if (Leader == 0 && Follower == 0)
//			continue;
//
//		if (pList[i].MinuteGenerate == -1)
//			continue;
//
//		STRUCT_MOB* MOB = &pList[i].Leader;
//
//		if (MOB->Merchant != 0)
//			continue;
//
//		int EmptyMob = 0;
//
//		for (int x = 0; x < MAX_CARRY; x++) {
//			if (MOB->Carry[x].sIndex != 0)
//				EmptyMob = 1;
//		}
//
//		if (EmptyMob == 0)
//			continue;
//		
//		if (Number == 169)
//			break;
//
//		if (Leader)
//		{	
//			fprintf(fp, "----------------------\n");
//			fprintf(fp, "MobName: %s, X:%d, Y:%d\n", MOB->MobName, pList[i].SegmentListX[0], pList[i].SegmentListY[0]);
//
//			int Slot = 0;
//
//			for (int k = 0; k < MAX_CARRY; k++)
//			{			
//				if (MOB->Carry[k].sIndex == 0)
//					continue;
//
//				bool Exist = false;
//				for (int z = 0; z < MAX_CARRY; z++) {
//					if (MOB->Carry[k].sIndex == dListItem[Number][z]) {
//						Exist = true;
//						break;
//					}
//				}
//
//				if (Exist)
//					continue;
//
//				dListItem[Number][Slot] = MOB->Carry[k].sIndex;
//				fprintf(fp, "%d,", MOB->Carry[k].sIndex);
//				Slot++;
//			}
//			strncpy(dListMobName[Number], MOB->MobName, 16);
//			fprintf(fp, "\nMob: %d\n", Number);
//			Number++;
//			MobList.push_back(MOB->MobName);
//		}
//	}
//	fclose(fp);
//}


void CNPCGenerator::LevelList()
{
	list<char*> MobList;

	for (int i = 0; i < NumList; i++)
	{
		int Leader = 1;
		int Follower = 1;

		for (list<char*>::iterator l = MobList.begin(); l != MobList.end(); ++l)
		{
			if (strncmp(*l, pList[i].Leader.MobName, strlen(pList[i].Leader.MobName)) == 0)
				Leader = 0;

			if (strncmp(*l, pList[i].Follower.MobName, strlen(pList[i].Leader.MobName)) == 0)
				Follower = 0;
		}

		if (Leader == 0 && Follower == 0)
			continue;

		char filename[256];

		int j = 0;

		for (j = 0; j < NumRegion; j++)
		{
			if (pList[i].SegmentListX[0] >= pRegion[j].minX && pList[i].SegmentListY[0] >= pRegion[j].minY &&
				pList[i].SegmentListX[0] <= pRegion[j].maxX && pList[i].SegmentListY[0] <= pRegion[j].maxY)
			{
				strncpy(filename, pRegion[j].RegionName, sizeof(filename));
				break;
			}
		}

		if (j == NumRegion)
			strncpy(filename, "Zona_Desconhecida", sizeof(filename));

		sprintf_s(temp, "./LevelList/%s.txt", filename);
		FILE *fp = fopen(temp, "a+");

		if (Leader)
		{
			STRUCT_MOB *MOB = &pList[i].Leader;

			fprintf(fp, "MobName: %s Level:%d\r\n\n", MOB->MobName, MOB->BaseScore.Level);

			fputs("\r\n", fp);

			MobList.push_back(MOB->MobName);
		}

		for (list<char*>::iterator l = MobList.begin(); l != MobList.end(); ++l)
		{
			if (strncmp(*l, pList[i].Follower.MobName, strlen(pList[i].Leader.MobName)) == 0)
				Follower = 0;
		}

		if (Follower)
		{
			STRUCT_MOB *MOB = &pList[i].Follower;

			fprintf(fp, "MobName: %s Level:%d\r\n\n", MOB->MobName, MOB->BaseScore.Level);

			fputs("\r\n", fp);

			MobList.push_back(MOB->MobName);
		}

		fclose(fp);
	}
}


CNPCSummon::CNPCSummon()
{
}

CNPCSummon::~CNPCSummon()
{
}

void CNPCSummon::Initialize()
{
	int MobFound = 0;

	BASE_InitModuleDir();

	strncpy((char*)Mob[0].MobName, "Condor", sizeof(Mob[0].MobName));

	MobFound = ReadMob(&Mob[0], "BaseSummon");

	if (!MobFound)
		MessageBoxA(hWndMain, Mob[0].MobName, "Can't read NPC 0", MB_OK);

	strncpy((char*)Mob[1].MobName, "Javali", sizeof(Mob[1].MobName));

	MobFound = ReadMob(&Mob[1], "BaseSummon");

	if (!MobFound)
		MessageBoxA(hWndMain, Mob[1].MobName, "Can't read NPC 1", MB_OK);

	strncpy((char*)Mob[2].MobName, "Lobo", sizeof(Mob[2].MobName));

	MobFound = ReadMob(&Mob[2], "BaseSummon");

	if (!MobFound)
		MessageBoxA(hWndMain, Mob[2].MobName, "Can't read NPC 2", MB_OK);

	strncpy((char*)Mob[3].MobName, "Urso", sizeof(Mob[3].MobName));

	MobFound = ReadMob(&Mob[3], "BaseSummon");

	if (!MobFound)
		MessageBoxA(hWndMain, Mob[3].MobName, "Can't read NPC 3", MB_OK);

	strncpy((char*)Mob[4].MobName, "Tigre", sizeof(Mob[4].MobName));

	MobFound = ReadMob(&Mob[4], "BaseSummon");

	if (!MobFound)
		MessageBoxA(hWndMain, Mob[4].MobName, "Can't read NPC 4", MB_OK);

	strncpy((char*)Mob[5].MobName, "Gorila", sizeof(Mob[5].MobName));

	MobFound = ReadMob(&Mob[5], "BaseSummon");

	if (!MobFound)
		MessageBoxA(hWndMain, Mob[5].MobName, "Can't read NPC 5", MB_OK);

	strncpy((char*)Mob[6].MobName, "Dragao_Negro", sizeof(Mob[6].MobName));

	MobFound = ReadMob(&Mob[6], "BaseSummon");

	if (!MobFound)
		MessageBoxA(hWndMain, Mob[6].MobName, "Can't read NPC 6", MB_OK);

	strncpy((char*)Mob[7].MobName, "Succubus", sizeof(Mob[7].MobName));

	MobFound = ReadMob(&Mob[7], "BaseSummon");

	if (!MobFound)
		MessageBoxA(hWndMain, Mob[7].MobName, "Can't read NPC 7", MB_OK);

	strncpy((char*)Mob[8].MobName, "Porco", sizeof(Mob[8].MobName));

	MobFound = ReadMob(&Mob[8], "BaseSummon");

	if (!MobFound)
		MessageBoxA(hWndMain, Mob[8].MobName, "Can't read NPC 8", MB_OK);

	strncpy((char*)Mob[9].MobName, "Javali_", sizeof(Mob[9].MobName));

	MobFound = ReadMob(&Mob[9], "BaseSummon");

	if (!MobFound)
		MessageBoxA(hWndMain, Mob[9].MobName, "Can't read NPC 9", MB_OK);

	strncpy((char*)Mob[10].MobName, "Porco", sizeof(Mob[10].MobName));

	MobFound = ReadMob(&Mob[10], "BaseSummon");

	if (!MobFound)
		MessageBoxA(hWndMain, Mob[10].MobName, "Can't read NPC 10", MB_OK);

	strncpy((char*)Mob[11].MobName, "Javali", sizeof(Mob[11].MobName));

	MobFound = ReadMob(&Mob[11], "BaseSummon");

	if (!MobFound)
		MessageBoxA(hWndMain, Mob[11].MobName, "Can't read NPC 11", MB_OK);

	strncpy((char*)Mob[12].MobName, "Lobo", sizeof(Mob[12].MobName));

	MobFound = ReadMob(&Mob[12], "BaseSummon");

	if (!MobFound)
		MessageBoxA(hWndMain, Mob[12].MobName, "Can't read NPC 12", MB_OK);

	strncpy((char*)Mob[13].MobName, "Dragao_menor", sizeof(Mob[13].MobName));

	MobFound = ReadMob(&Mob[13], "BaseSummon");

	if (!MobFound)
		MessageBoxA(hWndMain, Mob[13].MobName, "Can't read NPC 13", MB_OK);

	strncpy((char*)Mob[14].MobName, "Urso", sizeof(Mob[14].MobName));

	MobFound = ReadMob(&Mob[14], "BaseSummon");

	if (!MobFound)
		MessageBoxA(hWndMain, Mob[14].MobName, "Can't read NPC 14", MB_OK);

	strncpy((char*)Mob[15].MobName, "Dente_de_Sabre", sizeof(Mob[15].MobName));

	MobFound = ReadMob(&Mob[15], "BaseSummon");

	if (!MobFound)
		MessageBoxA(hWndMain, Mob[15].MobName, "Can't read NPC 15", MB_OK);

	strncpy((char*)Mob[16].MobName, "Sem_Sela_N", sizeof(Mob[16].MobName));

	MobFound = ReadMob(&Mob[16], "BaseSummon");

	if (!MobFound)
		MessageBoxA(hWndMain, Mob[16].MobName, "Can't read NPC 16", MB_OK);

	strncpy((char*)Mob[17].MobName, "Fantasma_N", sizeof(Mob[17].MobName));

	MobFound = ReadMob(&Mob[17], "BaseSummon");

	if (!MobFound)
		MessageBoxA(hWndMain, Mob[17].MobName, "Can't read NPC 17", MB_OK);

	strncpy((char*)Mob[18].MobName, "Leve_N", sizeof(Mob[18].MobName));

	MobFound = ReadMob(&Mob[18], "BaseSummon");

	if (!MobFound)
		MessageBoxA(hWndMain, Mob[18].MobName, "Can't read NPC 18", MB_OK);

	strncpy((char*)Mob[19].MobName, "Equip_N", sizeof(Mob[19].MobName));

	MobFound = ReadMob(&Mob[19], "BaseSummon");

	if (!MobFound)
		MessageBoxA(hWndMain, Mob[19].MobName, "Can't read NPC 19", MB_OK);

	strncpy((char*)Mob[20].MobName, "Andaluz_N", sizeof(Mob[20].MobName));

	MobFound = ReadMob(&Mob[20], "BaseSummon");

	if (!MobFound)
		MessageBoxA(hWndMain, Mob[20].MobName, "Can't read NPC 20", MB_OK);

	strncpy((char*)Mob[21].MobName, "Sem_Sela_B", sizeof(Mob[21].MobName));

	MobFound = ReadMob(&Mob[21], "BaseSummon");

	if (!MobFound)
		MessageBoxA(hWndMain, Mob[21].MobName, "Can't read NPC 21", MB_OK);

	strncpy((char*)Mob[22].MobName, "Fantasma_B", sizeof(Mob[22].MobName));

	MobFound = ReadMob(&Mob[22], "BaseSummon");

	if (!MobFound)
		MessageBoxA(hWndMain, Mob[22].MobName, "Can't read NPC 22", MB_OK);

	strncpy((char*)Mob[23].MobName, "Leve_B", sizeof(Mob[23].MobName));

	MobFound = ReadMob(&Mob[23], "BaseSummon");

	if (!MobFound)
		MessageBoxA(hWndMain, Mob[23].MobName, "Can't read NPC 23", MB_OK);

	strncpy((char*)Mob[24].MobName, "Equip_B", sizeof(Mob[24].MobName));

	MobFound = ReadMob(&Mob[24], "BaseSummon");

	if (!MobFound)
		MessageBoxA(hWndMain, Mob[24].MobName, "Can't read NPC 24", MB_OK);

	strncpy((char*)Mob[25].MobName, "Andaluz_B", sizeof(Mob[25].MobName));

	MobFound = ReadMob(&Mob[25], "BaseSummon");

	if (!MobFound)
		MessageBoxA(hWndMain, Mob[25].MobName, "Can't read NPC 25", MB_OK);

	strncpy((char*)Mob[26].MobName, "Fenrir", sizeof(Mob[26].MobName));

	MobFound = ReadMob(&Mob[26], "BaseSummon");

	if (!MobFound)
		MessageBoxA(hWndMain, Mob[26].MobName, "Can't read NPC 26", MB_OK);

	strncpy((char*)Mob[27].MobName, "Dragao", sizeof(Mob[27].MobName));

	MobFound = ReadMob(&Mob[27], "BaseSummon");

	if (!MobFound)
		MessageBoxA(hWndMain, Mob[27].MobName, "Can't read NPC 27", MB_OK);

	strncpy((char*)Mob[28].MobName, "FenrirSombra", sizeof(Mob[28].MobName));

	MobFound = ReadMob(&Mob[28], "BaseSummon");

	if (!MobFound)
		MessageBoxA(hWndMain, Mob[28].MobName, "Can't read NPC 28", MB_OK);

	strncpy((char*)Mob[29].MobName, "Tigre_de_Fogo", sizeof(Mob[29].MobName));

	MobFound = ReadMob(&Mob[29], "BaseSummon");

	if (!MobFound)
		MessageBoxA(hWndMain, Mob[29].MobName, "Can't read NPC 29", MB_OK);

	strncpy((char*)Mob[30].MobName, "Dragao_Vermelho", sizeof(Mob[30].MobName));

	MobFound = ReadMob(&Mob[30], "BaseSummon");

	if (!MobFound)
		MessageBoxA(hWndMain, Mob[30].MobName, "Can't read NPC 30", MB_OK);

	strncpy((char*)Mob[31].MobName, "Unicornio", sizeof(Mob[31].MobName));

	MobFound = ReadMob(&Mob[31], "BaseSummon");

	if (!MobFound)
		MessageBoxA(hWndMain, Mob[31].MobName, "Can't read NPC 31", MB_OK);

	strncpy((char*)Mob[32].MobName, "Pegasus", sizeof(Mob[32].MobName));

	MobFound = ReadMob(&Mob[32], "BaseSummon");

	if (!MobFound)
		MessageBoxA(hWndMain, Mob[32].MobName, "Can't read NPC 32", MB_OK);

	strncpy((char*)Mob[33].MobName, "Unisus", sizeof(Mob[33].MobName));

	MobFound = ReadMob(&Mob[33], "BaseSummon");

	if (!MobFound)
		MessageBoxA(hWndMain, Mob[33].MobName, "Can't read NPC 33", MB_OK);

	strncpy((char*)Mob[34].MobName, "Grifo", sizeof(Mob[34].MobName));

	MobFound = ReadMob(&Mob[34], "BaseSummon");

	if (!MobFound)
		MessageBoxA(hWndMain, Mob[34].MobName, "Can't read NPC 34", MB_OK);

	strncpy((char*)Mob[35].MobName, "Hipogrifo", sizeof(Mob[35].MobName));

	MobFound = ReadMob(&Mob[35], "BaseSummon");

	if (!MobFound)
		MessageBoxA(hWndMain, Mob[35].MobName, "Can't read NPC 35", MB_OK);

	strncpy((char*)Mob[36].MobName, "Grifo_Sangrento", sizeof(Mob[36].MobName));

	MobFound = ReadMob(&Mob[36], "BaseSummon");

	if (!MobFound)
		MessageBoxA(hWndMain, Mob[36].MobName, "Can't read NPC 36", MB_OK);

	strncpy((char*)Mob[37].MobName, "Svadilfire", sizeof(Mob[37].MobName));

	MobFound = ReadMob(&Mob[37], "BaseSummon");

	if (!MobFound)
		MessageBoxA(hWndMain, Mob[37].MobName, "Can't read NPC 37", MB_OK);

	strncpy((char*)Mob[38].MobName, "Sleipnir", sizeof(Mob[38].MobName));

	MobFound = ReadMob(&Mob[38], "BaseSummon");

	if (!MobFound)
		MessageBoxA(hWndMain, Mob[38].MobName, "Can't read NPC 38", MB_OK);

	strncpy((char*)Mob[39].MobName, "Pantera_Negra", sizeof(Mob[39].MobName));

	MobFound = ReadMob(&Mob[39], "BaseSummon");

	if (!MobFound)
		MessageBoxA(hWndMain, Mob[39].MobName, "Can't read NPC 39", MB_OK);

	strncpy((char*)Mob[40].MobName, "VeridFinal", sizeof(Mob[40].MobName));

	MobFound = ReadMob(&Mob[40], "BaseSummon");

	if (!MobFound)
		MessageBoxA(hWndMain, Mob[40].MobName, "Can't read NPC 40", MB_OK);
}

void SetAct(char *dest, char *act)
{
	if (strlen(act) >= 79)
	{
		MessageBox(hWndMain, act, "NPC Generater's Action can't be larger than 80.", NULL);

		return;
	}

	strcpy(dest, act);
}