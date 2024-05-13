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
#include "CWarTower.h"
#include "wMySQL.h"

void CWarTower::GuildProcess(tm* timeinfo)
{
	if (NewbieEventServer == 1 && timeinfo->tm_wday != 0 && timeinfo->tm_wday != 6 && timeinfo->tm_hour == GTorreHour && GTorreStatus == 1)
	{
		if (GTorreState == 0 && timeinfo->tm_min == 0 && timeinfo->tm_sec >= 0)
		{
			SendNotice(strFmt(g_pMessageStringTable[_DN_CHANNELWAR_BEGIN], 5));
			GTorreState = 1;
			GTorreGuild = 0;
		}

		if (GTorreState == 1 && timeinfo->tm_min == 5 && timeinfo->tm_sec >= 0)
		{
			ClearArea(2445, 1850, 2546, 1920);

			GenerateMob(GTORRE, 0, 0);

			SendNotice(g_pMessageStringTable[_DN_BASEWORSTART]);
			GTorreState = 2;
		}

		//A Guerra acabou a guilda que está defendendo a torre recebe 100 de fama.
		if (GTorreState == 2 && timeinfo->tm_min == 35)
		{
			ClearArea(2445, 1850, 2546, 1920);

			for (int i = MAX_USER; i < MAX_MOB; i++)
			{
				if (pMob[i].GenerateIndex == GTORRE)
				{
					if (pMob[i].MOB.Guild)
					{
						int Group = ServerGroup;
						int Server = pMob[i].MOB.Guild / MAX_GUILD;
						int usGuild = pMob[i].MOB.Guild;

						char guildname[256];

						BASE_GetGuildName(Group, usGuild, guildname);

						MSG_GuildInfo sm;

						sm.Type = _MSG_GuildInfo;
						sm.Size = sizeof(MSG_GuildInfo);
						sm.ID = 0;

						sm.Guild = usGuild;
						GuildInfo[usGuild].Fame += 100;

						auto& pc = cSQL::instance();
						sprintf(xQuery, "UPDATE `guilds` SET fame = '%d' WHERE `guild` = '%d'", GuildInfo[usGuild].Fame + 100, usGuild);
						pc.wQuery(xQuery);

						sm.GuildInfo = GuildInfo[usGuild];

						DBServerSocket.SendOneMessage((char*)&sm, sizeof(MSG_GuildInfo));

						SystemLog("-system", "-", 0, strFmt("etc,war_tower1 guild:%d guild_fame:%d", usGuild, GuildInfo[usGuild].Fame));

						BASE_GetGuildName(ServerGroup, usGuild, guildname);
						SendNotice(strFmt("Guerra de torre finalizada! Vencedor: %s", guildname));
					}

					DeleteMob(i, 1);
				}
			}

			GTorreState = 0;
			GTorreGuild = 0;
		}
	}
}

void CWarTower::MobKilled(int target, int conn, int PosX, int PosY)
{
	int GenerateID = pMob[target].GenerateIndex;

	if (GenerateID == GTORRE && GTorreState)
	{
		if (pMob[conn].MOB.Guild)
		{
			int Group = ServerGroup;
			int Server = pMob[conn].MOB.Guild / MAX_GUILD;
			int usGuild = pMob[conn].MOB.Guild;

			char guildname[256];

			BASE_GetGuildName(Group, usGuild, guildname);

			SendNotice(strFmt("O player %s da guilda %s derrubou a torre!", pMob[conn].MOB.MobName, guildname));

			GTorreGuild = pMob[conn].MOB.Guild;
		}

		ClearArea(2445, 1850, 2546, 1920);

		GenerateMob(GTORRE, 0, 0);
	}
}

void CWarTower::GGenerateMob(int index, int PosX, int PosY, int tmob)
{
	if (index == GTORRE && GTorreGuild)
	{
		pMob[tmob].MOB.Guild = GTorreGuild;
		pMob[tmob].MOB.GuildLevel = 0;
	}
}

BOOL CWarTower::TowerAttack(int conn, int idx)
{
	if (pMob[idx].GenerateIndex != GTORRE)
		return TRUE;

	if (pMob[conn].MOB.Guild == 0 || pMob[conn].MOB.Guild == pMob[idx].MOB.Guild)
		return FALSE;

	return TRUE;
}