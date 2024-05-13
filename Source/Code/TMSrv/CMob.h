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
#ifndef __CMOB__
#define __CMOB__

#include "..\Basedef.h"

#define MAX_ENEMY 13

#define MOB_EMPTY 0  // There's no mob on the slot
#define MOB_USERDOCK    1
#define MOB_USER		2
#define MOB_IDLE        3
#define MOB_PEACE		4
#define MOB_COMBAT      5
#define MOB_RETURN		6
#define MOB_FLEE		7
#define MOB_ROAM		8
#define MOB_WAITDB		9

class CMob
{
public:
	STRUCT_MOB    MOB; // 0 - 804
	STRUCT_AFFECT Affect[MAX_AFFECT]; // 805 - 1061
	int Mode; // 1062 - 1065
	int Leader; // 1066 - 1069
    int Formation; // 1070 - 1073
	int RouteType; // 1074 - 1077
	int LastX; // 1078 - 1081
	int LastY; // 1082 - 1085
	int LastTime; // 1086 - 1089
	int LastSpeed; // 1090 - 1093
	int TargetX; // 1094 - 1097
	int TargetY; // 1098 - 1101
	int NextX; // 1102 - 1105
	int NextY; // 1106 - 1109
	int NextAction; // 1110 - 1113
	char Route[MAX_ROUTE]; // 1114 - 1137
	int WaitSec; // 1138 - 1141
	char Unk5[12]; // 1142 - 1153
	int Segment; // 1154 - 1157
	int SegmentX; // 1158 - 1161
	int SegmentY; // 1162 - 1165
	int SegmentListX[5]; // 1166 - 1185
	int SegmentListY[5]; // 1186 - 1205
	int SegmentWait[5]; // 1206 - 1225
	int SegmentRange[5]; // 1226 - 1245
	int SegmentDirection; // 1246 - 1249
	int SegmentProgress; // 1250 - 1253
	int GenerateIndex; // 1254 - 1257
	short CurrentTarget; // 1258 - 1259
	short EnemyList[MAX_ENEMY]; // 1260 - 1285
	short PartyList[MAX_PARTY]; // 1286 - 1309
	short Unk7; // 1310 - 1311
	int WeaponDamage; // 1312 - 1315
	int Summoner; // 1316 - 1319
	int PotionCount; // 1320 - 1323
	int Parry; // 1324 - 1327
	int GuildDisable; // 1328 - 1331
	int DropBonus; // 1332 - 1335
	int ExpBonus; // 1336 - 1339
	int ForceDamage; // 1340 - 1343
	int ReflectDamage;  // 1344 - 1347
	int PosX; // 1348 - 1351
	int PosY; // 1352 - 1355
	//********************
	STRUCT_MOBEXTRA extra; // 1356 - 2117

	char Tab[36]; // 2118 - 2153
	char Snd[96]; // 2154 - 2249

	int ForceMobDamage; // 2250 - 2253
	int Accuracy; // 2254 - 2257
	int HpAbs; // 2258 - 2261

	int PvPDamage; // 2262 - 2265
	int ReflectPvP; // 2266 - 2269

	int MaxCarry; // 2270 - 2273
	int QuestFlag; // 2274 - 2277

	int LastReqParty; // 2278 - 2281
	unsigned int ProcessorCounter; // 2282 - 2285
	int IsSummon;

	int CitizenDrop; // 2286 - 2289

	short MissPlayer; // 2290 - 2291
	short DivineBlessing; // 2292 - 2293
	int RateRegen; // 2294 - 2297
	int JoiaOn;
	char sPremioNovato[10]; // 2298 - 2307

	STRUCT_REBUY Rebuy[MAX_ITEM_REBUY]; // 2308 - 2367

	short Evocations[MAX_PARTY];
	short Evocation;
	int CheckQuest;
	int CheckLojinha;
	int CheckEvento;
	int KillCount;
	
	int LanNFlag; // 2274 - 2277
	int LanMFlag; // 2274 - 2277
	int LanAFlag; // 2274 - 2277

	int PesaNFlag; // 2274 - 2277
	int PesaMFlag; // 2274 - 2277
	int PesaAFlag; // 2274 - 2277

	int AguaNFlag; // 2274 - 2277
	int AguaMFlag; // 2274 - 2277
	int AguaAFlag; // 2274 - 2277

	int CartaNFlag; // 2274 - 2277
	int CartaMFlag; // 2274 - 2277
	int CartaAFlag; // 2274 - 2277

	int CuboNFlag; // 2274 - 2277
	int CuboMFlag; // 2274 - 2277
	int CuboAFlag; // 2274 - 2277

	int FiltroID[50];
	int FiltroState;
	int AbrirPainel;

public:

	CMob();
	~CMob();

	void ProcessorSecTimer         ();
	int  StandingByProcessor       (void);
	int  BattleProcessor           ();
	void AddEnemyList              (short TargetId);
	void RemoveEnemyList	       (short TargetId);
	void SelectTargetFromEnemyList (void);
	int  SetSegment                (void);                // 1:ShipMove   0:DeleteObject
	void GetCurrentScore           (int idx); 
	void GetTargetPosDistance      (int tz);
	void GetRandomPos              ();
	void GetTargetPos              (int tz);
	int  GetTargetPos7556		   (int target);
	int  CheckGetLevel             ();
	void GetNextPos				   (int battle);
	void GetNextRandomPos		   ();
	void CGetNextRandomPos		   ();
   	int  GetEnemyFromView	       (void);
	void AddChaosPoints(int points);
	void Clear();
	int ClientIndex;
};

extern CMob pMob[MAX_MOB];
#endif