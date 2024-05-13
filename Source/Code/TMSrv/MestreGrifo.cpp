#include "ProcessClientMessage.h"

struct      MSG_MestreGrifo
{
	_MSG;
	int WarpID;
	int Typpe;

};


void Exec_MSG_MestreGrifo(int conn, char *pMsg)
	{
		MSG_MestreGrifo *m = (MSG_MestreGrifo*)pMsg;

		int Size = m->Size;

		if (Size > sizeof(MSG_MestreGrifo)) //CONTROLE DE SIZE
		{
			SendClientMessage(conn, "Impossível executar ação1, tente mais tarde.");
			return;
		}

		if (m->Typpe == 1)
		{
			SendClientMessage(conn, "Obrigado por viajar comigo!");
			return;
		}
		switch (m->WarpID)
		{
		case 0:
			DoTeleport(conn, 2112, 2051);
			break;

		case 1:
			DoTeleport(conn, 2372, 2099);
			break;

		case 2:
			DoTeleport(conn, 2220, 1714);
			break;

		case 3:
			DoTeleport(conn, 2365, 2249);
			break;

		case 4:
			DoTeleport(conn, 1826, 1771);
			break;
		}

	}
