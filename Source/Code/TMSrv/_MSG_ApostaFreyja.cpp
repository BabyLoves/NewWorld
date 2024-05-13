#include "ProcessClientMessage.h" 


void Exec_MSG_onPaymentGold(int conn, char* pMsg)
{
	MSG_FreyjaAposta* p = (MSG_FreyjaAposta*)pMsg;

	auto mob = GetMobFromIndex(conn);
	int level = -1; 

	if (mob->TargetX >= 3332 && mob->TargetY >= 1471 && mob->TargetX <= 3449 && mob->TargetY <= 1529)
	{ 
		SendClientMessage(conn, "Essa função esta em manutenção.");
		return;
	}
}