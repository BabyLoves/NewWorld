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
#include "ProcessClientMessage.h"

void Exec_MSG_Restart(int conn, char *pMsg)
{
	MSG_STANDARD *m = (MSG_STANDARD*)pMsg;

	int Size = m->Size;

	if (Size > sizeof(MSG_STANDARD)) //CONTROLE DE SIZE
	{
		SendClientMessage(conn, "Impossível executar ação45, tente mais tarde. ");
		return;
	}

	if (pUser[conn].Mode == USER_PLAY)
	{

		if (pUser[conn].Atraso != 0)
		{
			int isTime = GetTickCount64() - pUser[conn].Atraso; // ATRASO PACOTE DE MORTE

			if (isTime < 4000)
			{
				return;
			}
			
		}
		pUser[conn].Atraso = GetTickCount64();

		if (pMob[conn].MOB.CurrentScore.Hp > 0) {
			CloseUser(conn);
			return;
		}

		pMob[conn].MOB.CurrentScore.Hp = 200;

		pUser[conn].NumError = 0;

		SendScore(conn);
		SendSetHpMp(conn);


		if(pMob[conn].TargetX >= 1017 && pMob[conn].TargetX <= 1290 && pMob[conn].TargetY >= 1911 && pMob[conn].TargetY <= 2183 && pMob[conn].MOB.Clan == 7)
			DoTeleport(conn, 1061+ rand()%3, 2129+rand()%3);
			
		else if(pMob[conn].TargetX >= 1017 && pMob[conn].TargetX <= 1290 && pMob[conn].TargetY >= 1911 && pMob[conn].TargetY <= 2183 && pMob[conn].MOB.Clan == 8)
			DoTeleport(conn, 1237+ rand()%3, 1966+rand()%3);
			
		else
			DoRecall(conn);
				
		SendEtc(conn);
	}
	else
		SendHpMode(conn);
}