#include "ProcessClientMessage.h"

void Exec_MSG_Quiz(int conn, char* pMsg)
{
	if (conn <= 0 || conn >= MAX_USER)
		return;

	MSG_STANDARDPARM* m = (MSG_STANDARDPARM*)pMsg;

	int Size = m->Size;

	if (m->Parm < 0 || m->Parm > 3)
		return;

	if (Size > sizeof(MSG_STANDARDPARM)) //CONTROLE DE SIZE
	{
		SendClientMessage(conn, "Impossível executar ação37, tente mais tarde. ");
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

	SendClientMessage(conn, "Desativado");

	/*if (SendQuiz[conn].Status)
	{
		if (m->Parm == SendQuiz[conn].RespostaCorreta)
		{
			pMob[conn].MOB.Coin += 500000;
			pMob[conn].MOB.Exp += 700000;
			SendEtc(conn);
			SendClientMessage(conn, "+ + 500.000 EXP / 700.000 GOLD + +");
			SendEmotion(conn, 14, 3);
		}

		else
			SendEmotion(conn, 20, 0);

		SendQuiz[conn].Status = FALSE;
	}

	if (SendQuiz[conn].StatusN)
	{
		if (m->Parm == SendQuiz[conn].RespostaCorretaLanN) {
			DoTeleport(conn, (3639 + rand() % 5 - 3), (3639 + rand() % 5 - 3));
			pMob[conn].LanNFlag = 1;
		}
		else
		{
			SendCarry(conn);
			SendEmotion(conn, 20, 0);
		}
		SendQuiz[conn].StatusN = FALSE;
	}

	if (SendQuiz[conn].StatusM)
	{
		if (m->Parm == SendQuiz[conn].RespostaCorretaLanM) {
			DoTeleport(conn, (3782 + rand() % 5 - 3), (3527 + rand() % 5 - 3));
			pMob[conn].LanMFlag = 1;
		}
		else
		{
			SendCarry(conn);
			SendEmotion(conn, 20, 0);

		}

		SendQuiz[conn].StatusM = FALSE;
	}

	if (SendQuiz[conn].StatusA)
	{
		if (m->Parm == SendQuiz[conn].RespostaCorretaLanA) {
			DoTeleport(conn, (3911 + rand() % 5 - 3), (3655 + rand() % 5 - 3));
			pMob[conn].LanAFlag = 1;
		}
		else
		{
			SendCarry(conn);
			SendEmotion(conn, 20, 0);

		}

		SendQuiz[conn].StatusA = FALSE;
	}*/
	return;
}