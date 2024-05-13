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

void Exec_MSG_Rebuy(int conn, char *pMsg)
{
	MSG_Rebuy *m = (MSG_Rebuy*)pMsg;

	int Size = m->Size;

	if (Size > sizeof(MSG_Rebuy)) //CONTROLE DE SIZE
	{
		SendClientMessage(conn, "Impossível executar ação38, tente mais tarde. ");
		return;
	}
	if (pUser[conn].Atraso != 0)
	{
		int isTime = GetTickCount64() - pUser[conn].Atraso; // ATRASO PACOTE

		if (isTime < 800)
		{
			SendClientMessage(conn, "Aguarde 1 segundo para uma nova Tentativa.");
			return;
		}

	}
	pUser[conn].Atraso = GetTickCount64();
	if (m->ID != conn)
	{
		CloseUser(conn);

		return;
	}

	pUser[conn].Ingame.MobDonateStore = !pUser[conn].Ingame.MobDonateStore;


	if (pUser[conn].Mode != USER_PLAY) 
		return;

	for (int i = 0; i < MAX_ITEM_REBUY; i++)
		m->Rebuy[i] = pMob[conn].Rebuy[i];

	if (Size > sizeof(MSG_Rebuy))
	{
		m->Size = 0;
		return;
	}
	if (!pUser[conn].cSock.AddMessage((char*)m, m->Size))
		CloseUser(conn);
}