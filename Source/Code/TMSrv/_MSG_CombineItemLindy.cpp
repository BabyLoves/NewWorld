
#include "ProcessClientMessage.h"

void Exec_MSG_CombineItemLindy(int conn, char* pMsg)
{
	MSG_CombineItem* m = (MSG_CombineItem*)pMsg;

	int Size = m->Size;

	if (Size > sizeof(MSG_CombineItem)) //CONTROLE DE SIZE
	{
		SendClientMessage(conn, "Impossível executar ação18, tente mais tarde. ");
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

	for (int i = 0; i < MAX_COMBINE; i++)
	{
		int invPos = m->InvenPos[i];

		if (m->Item[i].sIndex == 0)
			continue;

		if (invPos == -1) {
			Combinelogsitem(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, "dup,Tentativa de Dup CombineLindy");
			return;
		}

		if (invPos < 0 || invPos >= pMob[conn].MaxCarry)
		{
			RemoveTrade(conn);
			return;
		}

		if (memcmp(&pMob[conn].MOB.Carry[invPos], &m->Item[i], sizeof(STRUCT_ITEM)))
		{
			Combinelogsitem(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, "err,msg_CombineLindy - item remove or changed.");
			SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 0);
			return;
		}
	}

	if (pMob[conn].extra.ClassMaster != ARCH)
		return;

	if (pMob[conn].MOB.CurrentScore.Level != 369 && pMob[conn].MOB.CurrentScore.Level != 354)
		return;

	if (pMob[conn].extra.QuestInfo.Arch.Level355 == 1 && pMob[conn].MOB.CurrentScore.Level == 354)
		return;

	if (pMob[conn].extra.QuestInfo.Arch.Level370 == 0 && pMob[conn].MOB.CurrentScore.Level == 369 && pMob[conn].extra.Fame <= 0)
	{
		SendClientMessage(conn, "Necessário 01 de fame");
		return;
	}

	if (pMob[conn].extra.QuestInfo.Arch.Level370 == 1 && pMob[conn].MOB.CurrentScore.Level == 369)
		return;


	if (m->Item[0].sIndex == 413 && BASE_GetItemAmount(&m->Item[0]) == 10 && m->Item[1].sIndex == 413 && BASE_GetItemAmount(&m->Item[1]) == 10
		&& m->Item[2].sIndex == 4127 && m->Item[3].sIndex == 413 && m->Item[4].sIndex == 413 && m->Item[5].sIndex == 413 && m->Item[6].sIndex == 413)
	{

		for (int i = 0; i < MAX_COMBINE; i++)
		{
			if (m->Item[i].sIndex == 0)
				continue;

			memset(&pMob[conn].MOB.Carry[m->InvenPos[i]], 0, sizeof(STRUCT_ITEM));
			SendItem(conn, ITEM_PLACE_CARRY, m->InvenPos[i], &pMob[conn].MOB.Carry[m->InvenPos[i]]);
		}

		if (pMob[conn].MOB.CurrentScore.Level == 354)
		{
			pMob[conn].extra.QuestInfo.Arch.Level355 = 1;

			memset(&pMob[conn].MOB.Equip[15], 0, sizeof(STRUCT_ITEM));

			if (pMob[conn].MOB.Clan == 7) {
				pMob[conn].MOB.Equip[15].sIndex = 3191;
				pMob[conn].MOB.Equip[15].stEffect[0].cEffect = 54;
				pMob[conn].MOB.Equip[15].stEffect[0].cValue = 16;
			}
			else if (pMob[conn].MOB.Clan == 8) {
				pMob[conn].MOB.Equip[15].sIndex = 3192;
				pMob[conn].MOB.Equip[15].stEffect[0].cEffect = 54;
				pMob[conn].MOB.Equip[15].stEffect[0].cValue = 16;
			}
			else
				pMob[conn].MOB.Equip[15].sIndex = 3193;
			pMob[conn].MOB.Equip[15].stEffect[0].cEffect = 54;
			pMob[conn].MOB.Equip[15].stEffect[0].cValue = 16;
			
			SendItem(conn, ITEM_PLACE_EQUIP, 15, &pMob[conn].MOB.Equip[15]);
		}

		if (pMob[conn].MOB.CurrentScore.Level == 369)
		{
			pMob[conn].extra.QuestInfo.Arch.Level370 = 1;
			pMob[conn].extra.Fame -= 1;

		}
		SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 1);

		SendEmotion(conn, 14, 3);
		SendClientMessage(conn, g_pMessageStringTable[_NN_Processing_Complete]);
		SaveUser(conn, 0);
		return;
	}
}