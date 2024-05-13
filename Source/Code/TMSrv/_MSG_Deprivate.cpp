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

void Exec_MSG_Deprivate(int conn, char *pMsg)
{
	if (pUser[conn].Atraso != 0)
	{
		int isTime = GetTickCount64() - pUser[conn].Atraso; // ATRASO PACOTE DE MORTE

		if (isTime < 2000)
		{
			return;
		}
		
	}

	pUser[conn].Atraso = GetTickCount64();

	MSG_STANDARDPARM *m = (MSG_STANDARDPARM*)pMsg;

	int Size = m->Size;

	if (Size > sizeof(MSG_STANDARDPARM)) //CONTROLE DE SIZE
	{
		SendClientMessage(conn, "Impossível executar ação26, tente mais tarde. ");
		return;
	}

	DoDeprivate(conn, m->Parm);
}