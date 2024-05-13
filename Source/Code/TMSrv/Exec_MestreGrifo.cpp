#include "ProcessClientMessage.h"

void Exec_MSG_MestreGrifo(int conn, int warp, int type)
{
	switch (warp)
	{
	case 0:
		SendClientMessage(conn, "!Przyby³ do miejsca przeznaczenia [Obóz_treningowy].");
		DoTeleport(conn, 2112, 2051);
		break;
	case 1:
		SendClientMessage(conn, "!Przyby³ do miejsca przeznaczenia [Defensor da alma].");
		DoTeleport(conn, 2372, 2099);
		break;
	case 2:
		SendClientMessage(conn, "!Przyby³ do miejsca przeznaczenia [Jardin de deus].");
		DoTeleport(conn, 2220, 1714);
		break;
	case 3:
		SendClientMessage(conn, "!Przyby³ do miejsca przeznaczenia [Dungeon].");
		DoTeleport(conn, 2365, 2249);
		break;
	case 4:
		SendClientMessage(conn, "!Przyby³ do miejsca przeznaczenia [SubMundo].");
		DoTeleport(conn, 1826, 1771);
		break;
	case 5:
		SendClientMessage(conn, "!Przyby³ do miejsca przeznaczenia [SubMundo].");
		DoTeleport(conn, 1826, 1771);
		break;
	}
}