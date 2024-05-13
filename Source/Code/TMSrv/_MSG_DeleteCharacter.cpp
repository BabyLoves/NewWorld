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
#include <mysql.h>
#include "wMySQL.h"

void Exec_MSG_DeleteCharacter(int conn, char *pMsg)
{
	MSG_DeleteCharacter* m = (MSG_DeleteCharacter*)pMsg;

	if (m->Size > sizeof(MSG_DeleteCharacter))
		return;

	if (m->Slot < 0 || m->Slot >= MOB_PER_ACCOUNT)
	{
		return;
	}

	if (pUser[conn].Mode == USER_WAITDB || pUser[conn].Mode == USER_SELCHAR)
	{
		SendClientMessage(conn, "Deleting Character. wait a moment. #2");
		return;
	}

	if (pUser[conn].Mode != USER_CHARWAIT)
	{
		SendClientMessage(conn, "Deleting Character. wait a moment. #1");
		return;
	}

	if (pUser[conn].Atraso != 0)
	{
		int isTime = GetTickCount64() - pUser[conn].Atraso; // ATRASO PACOTE

		if (isTime < 5000)
		{
			SendClientMessage(conn, "Aguarde 5 segundos para uma nova Tentativa.");
			return;
		}

	}
	pUser[conn].Atraso = GetTickCount64();

	m->MobName[NAME_LENGTH - 1] = 0;

	if (pUser[conn].Mode == USER_CHARWAIT)
	{
		m->Type = _MSG_DBDeleteCharacter;
		m->ID = conn;

		pUser[conn].Mode = USER_WAITDB;


		auto& pc = cSQL::instance();

		sprintf(xQuery, "DELETE FROM `characteres` WHERE `nick`= '%s' AND `slot_char`= '%d'", m->MobName, m->Slot);
		pc.wQuery(xQuery);


		DBServerSocket.SendOneMessage((char*)m, sizeof(MSG_DeleteCharacter));

	}
	else
	{
		SendClientMessage(conn, "Deleting Character. wait a moment.");

	}
}