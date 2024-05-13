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

void Exec_MSG_CharacterLogout(int conn, char *pMsg)
{
	if (pUser[conn].Mode != USER_PLAY)
		return;


	auto tick = GetTickCount64();
	if (pUser[conn].AtrasocharLogout != 0)
	{
		int isTime = tick - pUser[conn].AtrasocharLogout; // atraso da requisição de voltar tela de seleção de personagens

		if (isTime < 500)
		{
			pUser[conn].AtrasocharLogout = tick;
			return;
		}

	}
	pUser[conn].AtrasocharLogout = tick;

	RemoveParty(conn);
	CharLogOut(conn);
}