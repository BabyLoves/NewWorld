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
#include <regex>
#include <mysql.h>
#include "wMySQL.h"

void Exec_MSG_CreateCharacter(int conn, char *pMsg)
{
	MSG_CreateCharacter* m = (MSG_CreateCharacter*)pMsg;

	if (m->Size > sizeof(MSG_CreateCharacter))
		return;


	if (pUser[conn].Mode != USER_CHARWAIT)
	{
		SystemLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, strFmt("err,createchar not user_selchar %d %d", conn, pUser[conn].Mode));

		SendClientSignal(conn, 0, _MSG_NewCharacterFail);
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
	m->MobName[NAME_LENGTH - 2] = 0;

	if (pUser[conn].WaitDB) {
		SendClientMessage(conn, "Aguarde um momento");
		return;
	}

	//validação de string
	std::string name = { m->MobName };
	std::regex int_regex("^[A-Za-z0-9-]{4,12}$");

	if (!std::regex_match(name, int_regex))
	{
		SendClientSignal(conn, 0, _MSG_NewCharacterFail);
		SystemLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, strFmt("err,createchar not user_selchar %d", conn, pUser[conn].Mode));
		CloseUser(conn);
		return;
	}

	pUser[conn].NumCreated++;

	if (pUser[conn].NumCreated > 5)
	{
		//HackLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, "Desconectado por criar 5 personagens na mesma conta seguidos");
		pUser[conn].NumCreated = 0;
		CloseUser(conn);
		return;
	}

	if (BASE_CheckValidString(m->MobName))
	{
		m->Type = _MSG_DBCreateCharacter;
		m->ID = conn;

		pUser[conn].Mode = USER_WAITDB;
		pUser[conn].WaitDB = true;

		auto& pc = cSQL::instance();

		sprintf(xQuery, "SELECT * FROM `accounts` WHERE `username` = '%s'", pUser[conn].AccountName);

		MYSQL_ROW row;
		MYSQL* wSQL = pc.wStart();
		MYSQL_RES* result = pc.wRes(wSQL, xQuery);

		int Id = 0;

		if (result == NULL)
		{
			return;
		}

		while ((row = mysql_fetch_row(result)) != NULL)
		{
			Id = atoi(row[0]);
		}

		int Evolution = 1;

		sprintf(xQuery, "INSERT INTO `characteres` (`slug`, `account_id`, `nick`, `slot_char`) VALUES ('%d', '%d', '%s', '%d')",
			1, Id, m->MobName, m->Slot);
		pc.wQuery(xQuery);

		DBServerSocket.SendOneMessage((char*)m, sizeof(MSG_CreateCharacter));
		SystemLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, strFmt("etc,createchar name:%s %d %d", m->MobName, conn, pUser[conn].Mode));
	}

	else
		SendClientSignal(conn, 0, _MSG_NewCharacterFail);
}