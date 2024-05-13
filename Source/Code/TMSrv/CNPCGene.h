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
#ifndef __CNPCGENE__
#define __CNPCGENE__

#include "..\Basedef.h"

#define MOB_FREE 0
#define MOB_USE 1

#define MAX_SEGMENT 5

struct NPCGENLIST // BDEA94
{
	int  Mode; //  0 - 3
	int  MinuteGenerate;  // 4 - 7
	int  MaxNumMob;     // 8 - 11
	int  CurrentNumMob;     // 12 - 15
	int  MinGroup;     // 16 - 19
	int  MaxGroup;     // 20 - 23
	int  SegmentListX[MAX_SEGMENT]; // 24
	int  SegmentListY[MAX_SEGMENT]; 
	int  SegmentRange[MAX_SEGMENT]; 
	int  SegmentWait[MAX_SEGMENT]; 
	char SegmentAction[MAX_SEGMENT][80]; 
	char FightAction[4][80]; 
	char FleeAction[4][80];
	char DieAction[4][80];
	int  Formation;
	int  RouteType;
	int	 Offset;

	STRUCT_MOB   Leader;                    // 맙의 세부 내용.
	STRUCT_MOB   Follower;                  // 똘마니 세부내용
};

struct MAPREGION
{
	int minX;
	int minY;
	int maxX;
	int maxY;

	char RegionName[128];
};

class CNPCSummon
{	
public:
	STRUCT_MOB Mob[MAX_SUMMONLIST];

public:

	CNPCSummon(); 
	~CNPCSummon();
	void Initialize();	
};

class CNPCGenerator 
{	
public:

	NPCGENLIST pList [MAX_NPCGENERATOR];
	int NumOld		 [MAX_NPCGENERATOR];
	int NumList;

	MAPREGION pRegion[MAX_NPCGENERATOR];
	int NumRegion;

public:

	CNPCGenerator();  
	~CNPCGenerator();

	int  ReadNPCGenerator();
	int  ParseString(int i, char *str);
	void ReadRegion();
	void DropList();
	void UpdateDropList();
	void LevelList();
};

void SetAct(char *dest, char *act);


#endif