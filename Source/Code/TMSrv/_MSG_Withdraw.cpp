
#include "ProcessClientMessage.h"

void Exec_MSG_Withdraw(int conn, char *pMsg)
{
	MSG_STANDARDPARM *m = (MSG_STANDARDPARM*)pMsg;

	int Size = m->Size;

	if (Size > sizeof(MSG_STANDARDPARM)) //CONTROLE DE SIZE
	{
		SendClientMessage(conn, "Impossível executar ação56, tente mais tarde. ");
		return;
	}

	if (pMob[conn].MOB.CurrentScore.Hp == 0 || pUser[conn].Mode != USER_PLAY)
	{
		SendHpMode(conn);
		AddCrackError(conn, 10, 2);
		return;
	}

	int coin = m->Parm;

	if (coin < 0 || coin > 2000000000)
		return;

	if (pUser[conn].Coin >= coin && coin >= 0 && coin <= 2000000000)
	{
		int tcoin = coin + pMob[conn].MOB.Coin;

		if (tcoin >= 0 && tcoin <= 2000000000)
		{
			pMob[conn].MOB.Coin = tcoin;
			pUser[conn].Coin -= coin;

			m->ID = 30000;

			int Size = m->Size;

			if (Size > sizeof(MSG_STANDARDPARM))
			{
				m->Size = 0;
				return;
			}
			if (!pUser[conn].cSock.AddMessage((char*)m, sizeof(MSG_STANDARDPARM)))
				CloseUser(conn);

			SendCargoCoin(conn);

			sprintf_s(temp, "etc,retirada do bau V:%d R:%d", coin, pUser[conn].Coin);
			SystemLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, temp);
		}
		else
			SendClientMessage(conn, g_pMessageStringTable[_NN_Cant_get_more_than_2G]);
	}
	else
		SendClientMessage(conn, g_pMessageStringTable[_NN_Cant_Withdraw_That_Much]);
}