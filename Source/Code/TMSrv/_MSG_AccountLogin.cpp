
#include "ProcessClientMessage.h"
#include <regex>

void Exec_MSG_AccountLogin(int conn, char *pMsg)
{

	MSG_AccountLogin* m = (MSG_AccountLogin*)pMsg;

	if (m->Size > sizeof(MSG_AccountLogin))
	{
		CloseUser(conn);
		return;
	}

	m->Decode();

	m->AccountLogin[NAME_LENGTH - 1] = 0;
	m->AccountPassword[ACCOUNTPASS_LENGTH - 1] = 0;


	pUser[conn].AccountName[NAME_LENGTH - 1] = 0;


	if (conn <= 0 || (conn >= (MAX_USER - ADMIN_RESERV)))
	{
		SendClientMessage(conn, strFmt(g_pMessageStringTable[_NN_Reconnect]));

		pUser[conn].cSock.SendMessageA();

		CloseUser(conn);
		return;
	}

	std::string login = { m->AccountLogin };
	std::regex int_regex("^[A-Za-z0-9]{4,16}$");

	if (!std::regex_match(login, int_regex))
	{
		pUser[conn].cSock.SendMessageA();
		CloseUser(conn);
		return;
	}

	std::string password = { m->AccountPassword };
	std::regex int_regex2("^[A-Za-z0-9]{4,16}$");

	if (!std::regex_match(password, int_regex2))
	{
		pUser[conn].cSock.SendMessageA();
		CloseUser(conn);
		return;
	}

	std::string macaddress{ m->MacAddres };
	std::regex int_regex3("^[A-ZA-Z0-9:]{17,18}$");

	if (!std::regex_match(macaddress, int_regex3)) {
		pUser[conn].cSock.SendMessageA();
		CloseUser(conn);		
		return;
	}

	if (pUser[conn].Mode != USER_ACCEPT)
	{
		SendClientMessage(conn, "Login now, wait a moment.");
		CloseUser(conn);
		//CrackLog(conn, " accountlogin");
		//pUser[conn].cSock.SendMessageA();
		return;
	}

	if (Limitadordeconexoes(m->MacAddres) >= 5)
	{
		SendClientMessage(conn, "Limite de [5] conexões por máquina.");
		return;
	}

	/*     Copia o Mac      */
	memcpy(pUser[conn].MacAddress, m->MacAddres, sizeof(pUser[conn].MacAddress));

	/* até o presente momento estamos fazendo cliver manualmente atraves da define APP_VERSION , futuramente será sql. */
	if (m->Version > 6518 && m->Version != APP_VERSION) // ATT CLIENTE
	{
		SendClientMessage(conn, "Atualização disponível no Launcher! Atualize seu jogo para logar!");
		return;
	}

	/* Faz a leitura no txt se o mac estiver lá vai bloquear o acesso */
	/*int macBan = ReadMacList(pUser[conn].MacAddress);

	if (macBan == TRUE)
	{
		SendClientMessage(conn, "Você foi impedido de acessar esse servidor.");
		return;
	}*/

	time_t rawnow = time(NULL);
	struct tm* now = localtime(&rawnow);

	auto min = now->tm_min;
	auto sec = now->tm_sec;
	auto hour = now->tm_hour;

	FILE* fs = nullptr;
	fs = fopen(strFmt("Ban/%s.bin", m->AccountLogin), "rb");

	if (fs)
	{
		fread(&BannedUser[conn], 1, sizeof(AccountBanned), fs);
		fclose(fs);
		memcpy(&BannedUser[conn], &BannedUser[conn], sizeof(AccountBanned));
		auto account = &BannedUser[conn];
		auto mac = &BannedUser[conn];

		if (account->Permanente == TRUE)
		{
			SendClientMessage(conn, "Conta permanentemente. Entre em contato com o suporte para mais informações.");
			pUser[conn].cSock.SendMessageA();
			return;
		}


		if (account->Analyze == TRUE)
		{
			SendClientMessage(conn, "Estamos analizando a sua conta. Entre em contato com o suporte.");
			pUser[conn].cSock.SendMessageA();
			return;
		}

		if (now->tm_mon < account->mes || now->tm_mon == account->mes &&
			now->tm_mday < account->dia || now->tm_mon == account->mes &&
			now->tm_mday == account->dia && now->tm_hour < account->hora ||
			now->tm_mon == account->mes && now->tm_mday == account->dia &&
			now->tm_hour == account->hora && now->tm_min < account->min)
		{
			SendClientMessage(conn, strFmt("Conta bloqueada até as: [%02d:%02d] de [%02d/%02d/%04d] ", account->hora, account->min, account->dia, account->mes + 1, account->ano + 1900));
			pUser[conn].cSock.SendMessageA();
			return;
		}
		remove(strFmt("Ban/%s.bin", m->AccountLogin));
	}

	m->Type = _MSG_DBAccountLogin;
	m->ID = conn;

	sscanf(m->AccountLogin, "%s", pUser[conn].AccountName);

	_strupr(pUser[conn].AccountName);

	strncpy(m->AccountLogin, pUser[conn].AccountName, NAME_LENGTH);

	int check = CheckFailAccount(m->AccountLogin);

	if (check >= 3)
	{
		SendClientMessage(conn, g_pMessageStringTable[_NN_3_Tims_Wrong_Pass]);

		pUser[conn].cSock.SendMessageA();
		return;
	}

	DBServerSocket.SendOneMessage((char*)m, sizeof(MSG_AccountLogin));

	pUser[conn].Mode = USER_LOGIN;
	pMob[conn].Mode = MOB_EMPTY;
}