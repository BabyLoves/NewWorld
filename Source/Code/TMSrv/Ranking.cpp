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
#include "Ranking.h"


void doRanking(int conn)
{
	if (conn <= 0 || conn >= MAX_USER)
		return;

	if (pUser[conn].Mode != USER_PLAY)
		return;

	if (pUser[conn].cSock.Sock == 0)
		return;

	auto& pc = cSQL::instance();

	int Kills = GetTotKill(conn);

	/*MORTAL			2
	ARCH			1
	CELESTIAL		3
	CELESTIALCS		4
	SCELESTIAL		5
	HARDCORE        6
	HARDCOREA		7
	HARDCORECS		8
	SHARDCORE		9*/

	int Evolution = 0;

	if (pMob[conn].extra.ClassMaster == 2)
		Evolution = 1;

	if (pMob[conn].extra.ClassMaster == 1)
		Evolution = 2;

	if (pMob[conn].extra.ClassMaster > 2)
		Evolution = pMob[conn].extra.ClassMaster;

	sprintf(xQuery, "UPDATE `characteres` SET level = '%d', class = '%d', evolution = '%d', kingdom = '%d', frags = '%d', guild_id = '%d', guildlevel = '%d' WHERE `nick` = '%s' AND `slot_char` = '%d'",
		pMob[conn].MOB.BaseScore.Level, pMob[conn].MOB.Class, Evolution, pMob[conn].MOB.Clan,
		Kills, pMob[conn].MOB.Guild, pMob[conn].MOB.GuildLevel, pMob[conn].MOB.MobName, pUser[conn].Slot);
	pc.wQuery(xQuery);
}

void sendRanking(int conn, int state) {

	if (conn <= 0 || conn >= MAX_USER)
		return;

	if (pUser[conn].Mode != USER_PLAY)
		return;

	if (pUser[conn].cSock.Sock == 0)
		return;

	if (pUser[conn].RankingDelay != 0)
	{
		int isTime = GetTickCount64() - pUser[conn].RankingDelay; // ATRASO PACOTE

		if (isTime < 200)
		{
			SendClientMessage(conn, "Aguarde 1 segundo para uma nova Tentativa.");
			return;
		}

	}
	pUser[conn].RankingDelay = GetTickCount64();

	auto& pc = cSQL::instance();

	std::string mobName[50];
	int RankLevel[50] = {};
	int RankClasse[50] = {};
	int RankEvolution[50] = {};
	int PvP[50] = {};
	int i = 0;

	if (state == 0) {
		sprintf(xQuery, "SELECT * FROM `characteres` ORDER BY `evolution` DESC, `level` DESC LIMIT 50");
		MYSQL_ROW row;
		MYSQL* wSQL = pc.wStart();
		MYSQL_RES* result = pc.wRes(wSQL, xQuery);

		if (result == NULL)
		{
			return;
		}

		while ((row = mysql_fetch_row(result)) != NULL)
		{
			mobName[i] = row[3];
			RankLevel[i] = atoi(row[4]) + 1;
			RankClasse[i] = atoi(row[5]);
			RankEvolution[i] = atoi(row[6]);
			PvP[i] = atoi(row[12]);
			i++;
		}

		MSG_SendRanking sm;
		memset(&sm, 0, sizeof(MSG_SendRanking));

		sm.Type = _MSG_SendRanking;
		sm.Size = sizeof(MSG_SendRanking);
		sm.ID = conn;
		sm.State = state;

		for (int i = 0; i < 50; i++) {
			strncpy(sm.RankName[i], mobName[i].c_str(), sizeof(sm.RankName[i]));
			sm.RankLevel[i] = RankLevel[i];
			sm.RankClasse[i] = RankClasse[i];
			sm.RankEvolution[i] = RankEvolution[i];
			sm.PvP[i] = PvP[i];
		}

		int Size = sm.Size;

		if (Size > sizeof(MSG_SendRanking))
		{
			sm.Size = 0;
			return;
		}

		if (!pUser[conn].cSock.AddMessage((char*)&sm, sizeof(MSG_SendRanking)))
			CloseUser(conn);
	}

	if (state == 1) {
		sprintf(xQuery, "SELECT * FROM `characteres` ORDER BY `frags` DESC LIMIT 50");
		MYSQL_ROW row;
		MYSQL* wSQL = pc.wStart();
		MYSQL_RES* result = pc.wRes(wSQL, xQuery);

		if (result == NULL)
		{
			return;
		}

		while ((row = mysql_fetch_row(result)) != NULL)
		{
			mobName[i] = row[3];
			RankLevel[i] = atoi(row[4]) + 1;
			RankClasse[i] = atoi(row[5]);
			RankEvolution[i] = atoi(row[6]);
			PvP[i] = atoi(row[11]);
			i++;
		}

		MSG_SendRanking sm;
		memset(&sm, 0, sizeof(MSG_SendRanking));

		sm.Type = _MSG_SendRanking;
		sm.Size = sizeof(MSG_SendRanking);
		sm.ID = conn;
		sm.State = state;

		for (int i = 0; i < 50; i++) {
			strncpy(sm.RankName[i], mobName[i].c_str(), sizeof(sm.RankName[i]));
			sm.RankLevel[i] = RankLevel[i];
			sm.RankClasse[i] = RankClasse[i];
			sm.RankEvolution[i] = RankEvolution[i];
			sm.PvP[i] = PvP[i];
		}

		int Size = sm.Size;

		if (Size > sizeof(MSG_SendRanking))
		{
			sm.Size = 0;
			return;
		}

		if (!pUser[conn].cSock.AddMessage((char*)&sm, sizeof(MSG_SendRanking)))
			CloseUser(conn);
	}
}
