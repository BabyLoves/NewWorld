
#include "ProcessClientMessage.h"

void Exec_MSG_DeleteItem(int conn, char* pMsg)
{
	MSG_DeleteItem* m = (MSG_DeleteItem*)pMsg;

	int Size = m->Size;

	if (Size > sizeof(MSG_DeleteItem)) //CONTROLE DE CLIENTE SIZE
	{
		SendClientMessage(conn, "Impossível executar ação24, tente mais tarde. ");
		return;
	}

	if (m->Slot < 0 || m->Slot >= MAX_CARRY - 4)
		return;

	if (m->sIndex <= 0 || m->sIndex >= MAX_ITEMLIST)
		return;

	if (pUser[conn].Mode != USER_PLAY)
	{
		SendHpMode(conn);
		return;
	}

	if (pUser[conn].Trade.OpponentID)
	{
		RemoveTrade(pUser[conn].Trade.OpponentID);
		RemoveTrade(conn);
		return;
	}
	//BASE_GetItemCode(&pMob[conn].MOB.Carry[m->Slot], temp);
	snprintf(temp, sizeof(temp), "deleteitem, %d.%d,%d,%d,%d,%d,%d", pMob[conn].MOB.Carry[m->Slot].sIndex,
		pMob[conn].MOB.Carry[m->Slot].stEffect[0].cEffect, pMob[conn].MOB.Carry[m->Slot].stEffect[0].cValue,
		pMob[conn].MOB.Carry[m->Slot].stEffect[1].cEffect, pMob[conn].MOB.Carry[m->Slot].stEffect[1].cValue, 
		pMob[conn].MOB.Carry[m->Slot].stEffect[2].cEffect, pMob[conn].MOB.Carry[m->Slot].stEffect[2].cValue);
	ItemLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, temp);

	memset(&pMob[conn].MOB.Carry[m->Slot], 0, sizeof(STRUCT_ITEM));
}