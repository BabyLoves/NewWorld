
#include "ProcessClientMessage.h"
#include "Server.h" 
#include <string> 
#include <regex>
#include "Functions.h"
#include <mysql.h>
#include "wMySQL.h"

void Exec_MSG_MessageWhisper(int conn, char* pMsg)
{
	MSG_MessageWhisper* m = (MSG_MessageWhisper*)pMsg;
	std::string command{ m->MobName };
	std::string message{ m->String };
	int Clan = pMob[conn].MOB.Clan;
	int TargetX = pMob[conn].TargetX;
	int TargetY = pMob[conn].TargetY;

	auto mobOnline = pMob[conn];

	m->MobName[NAME_LENGTH - 1] = 0;
	m->String[MESSAGEWHISPER_LENGTH - 1] = 0;

	if (pUser[conn].Mode != USER_PLAY)
		return;

	std::regex int_regex1("^[A-Za-zÀ-ú0-9/+ -@_^~]{0,16}$");
	std::regex int_regex2("^[A-Za-zÀ-ú0-9/+ -@_^~]{0,100}$");
	if (!std::regex_match(command, int_regex1)) {
		SendClientMessage(conn, "Fail");
		return;
	}

	if (!std::regex_match(message, int_regex2)) {
		SendClientMessage(conn, "Fail");
		return;
	}

	if (command == "tt")
	{
		SendClientMessage(conn, strFmt("%d %d %d %d %d %d %d %d %d %d %d %d", pMob[conn].PartyList[0], pMob[conn].PartyList[1], pMob[conn].PartyList[2], pMob[conn].PartyList[3], pMob[conn].PartyList[4], pMob[conn].PartyList[5], pMob[conn].PartyList[6], pMob[conn].PartyList[7], pMob[conn].PartyList[8], pMob[conn].PartyList[9], pMob[conn].PartyList[10], pMob[conn].PartyList[11]));

	}

	if (command == "grupotransferir")
	{
		int idx = GetUserByName(m->String), i, Find = 0, NewLeader;

		if (idx >= MAX_USER)
			return;

		if (pMob[conn].Leader)
		{
			SendClientMessage(conn, g_pMessageStringTable[_NN_Party_Leader_Only]);
			return;
		}

		if (pUser[idx].Mode != USER_PLAY)
		{
			SendClientMessage(conn, g_pMessageStringTable[_NN_Not_Connected]);
			return;
		}

		for (int i = 0; i < MAX_PARTY; i++)
		{
			int partyconn = pMob[conn].PartyList[i];

			if (partyconn == idx && partyconn != 0 && partyconn < MAX_USER)
			{
				NewLeader = idx;
				Find = TRUE;
				break;
			}
		}

		if (!Find)
		{
			SendClientMessage(conn, "Este jogador não pertence ao seu grupo.");
			return;
		}

		pMob[conn].Leader = 0;
		pMob[idx].Leader = 0;

		for (int i = 0; i < MAX_PARTY; i++)
		{
			int partyconn = pMob[conn].PartyList[i];

			if (partyconn > 0 && partyconn <= MAX_MOB)
			{
				pMob[conn].PartyList[i] = 0;
				pMob[partyconn].Leader = 0;

				if (NewLeader != 0 && NewLeader != partyconn && partyconn < MAX_USER && NewLeader < MAX_USER)
				{
					MSG_AcceptParty sm;
					memset(&sm, 0, sizeof(MSG_AcceptParty));

					sm.Size = sizeof(MSG_AcceptParty);
					sm.Type = _MSG_AcceptParty;
					sm.ID = 0;

					sm.LeaderID = NewLeader;

					strncpy(sm.MobName, pMob[NewLeader].MOB.MobName, NAME_LENGTH);

					pMob[partyconn].LastReqParty = NewLeader;

					ProcessClientMessage(partyconn, (char*)&sm, TRUE);
				}
			}
		}

		if (NewLeader != 0 && NewLeader != conn && conn < MAX_USER && NewLeader < MAX_USER)
		{
			MSG_AcceptParty sm;
			memset(&sm, 0, sizeof(MSG_AcceptParty));

			sm.Size = sizeof(MSG_AcceptParty);
			sm.Type = _MSG_AcceptParty;
			sm.ID = 0;

			sm.LeaderID = NewLeader;

			strncpy(sm.MobName, pMob[NewLeader].MOB.MobName, NAME_LENGTH);

			pMob[conn].LastReqParty = NewLeader;

			ProcessClientMessage(conn, (char*)&sm, TRUE);
		}

		return;
	}

#pragma region /cp
	if (strcmp(m->MobName, "cp") == 0)
	{
		SendClientMessage(conn, strFmt(g_pMessageStringTable[_DN_Show_Chao], GetPKPoint(conn) - 75));
		return;
	}
#pragma endregion  	

#pragma endregion

#pragma endregion 
#pragma region Grupo com Senha
	if (strcmp(m->MobName, "Grupo") == 0 || strcmp(m->MobName, "grupo") == 0)
	{
		char Chave[4096] = { 0, };
		memset(Chave, 0x0, 4096);
		int valorGerado = rand() % (9999 - 1000 + 3333) + 1110;
		std::string s = std::to_string(valorGerado);
		sprintf_s(Chave, 4096, "%s", s.c_str());

		memset(&pUser[conn].Ingame.PartyPassword, 0, sizeof(pUser[conn].Ingame.PartyPassword));

		strncpy(pUser[conn].Ingame.PartyPassword, Chave, 6);
		SendEtc(conn);
		pUser[conn].Ingame.GrupoAceitarSolicitação = TRUE;
		SendClientMessage(conn, strFmt("!Sua senha :%s", pUser[conn].Ingame.PartyPassword));
		SendClientMessage(conn, strFmt("!Novo membro deve usar /entrar %s %s", pMob[conn].MOB.MobName, pUser[conn].Ingame.PartyPassword));

		pUser[conn].Ingame.GrupoAceitarSolicitação = TRUE;
		return;
	}


	if (strcmp(m->MobName, "entrar") == 0)
	{
		char TargetName[16];
		memset(TargetName, 0, sizeof(TargetName));
		char Password[7];
		memset(Password, 0, sizeof(Password));

		if (sizeof(m->String) > 100 || sizeof(m->String) <= 0)
			return;

		if (strnlen(m->MobName, 16) <= 0 || strnlen(m->String, 100) > 23)
			return;

		if (sscanf_s(m->String, "%15s %6s", TargetName, _countof(TargetName), Password, _countof(Password)))
		{
			if (sizeof(m->MobName) <= 0 || sizeof(m->MobName) > 16) {
				SendClientMessage(conn, "Nome inválido.");
				return;
			}

			if (sizeof(Password) <= 0 || sizeof(Password) > 7) {
				SendClientMessage(conn, "Senha inválida.");
				return;
			}

			//debug
			/*SendClientMessage(conn, strFmt("size password %d", sizeof(Password)));
			SendClientMessage(conn, strFmt("password %s", Password));*/

			auto idx = GetUserByName(TargetName);
			int leaderID = pMob[idx].Leader;

			if (pUser[idx].Mode != 22)
			{
				SendClientMessage(conn, "Este personagem não está conectado.");
				return;
			}
			if (pMob[idx].Leader != 0)
			{
				SendClientMessage(conn, "Este personagem não é lider de grupo.");
				return;
			}
			if (conn == idx)
			{
				SendClientMessage(conn, "Não é possivel.");
				return;
			}

			if (pMob[conn].Leader != 0)
			{
				SendClientMessage(conn, "Você já faz parte de um grupo.");
				return;
			}
			for (int i = 0; i < MAX_PARTY; i++)
			{
				if (pMob[conn].PartyList[i] != 0)
				{
					SendClientMessage(conn, "Você é lider de um grupo.");
					return;
				}
			}
			if (strcmp(pUser[idx].Ingame.PartyPassword, "") == 0)
			{
				SendClientMessage(conn, "Proibido a entrada em grupos sem senha");
				return;
			}
			if (strcmp(pUser[idx].Ingame.PartyPassword, Password) != 0)
			{
				SendClientMessage(conn, "Senha incorreta.");
				return;
			}
			SendReqParty(conn, idx, 0);
			return;
		}
		return;
	}	

#pragma region >> Aposta Pista +6

	else if (strcmp(m->MobName, "@aposta1") == 0)
	{
		if (pMob[conn].TargetX > 3330 && pMob[conn].TargetY > 1475 && pMob[conn].TargetX < 3448 && pMob[conn].TargetY < 1525)
		{

			if (pMob[conn].MOB.Coin < 25000000)
			{
				SendClientMessage(conn, "Gold Insuficiente.");
				return;
			}
			if (pMob[conn].Leader != -1 && pMob[conn].Leader)
			{
				SendClientMessage(conn, "Somente o líder.");
				return;
			}
			if (pMob[conn].extra.EMPTY[9] == 1)
			{
				SendClientMessage(conn, "Aposta já foi feita.");
				return;
			}

			Pista[6].Party[0].MobCount -= 10;
			pMob[conn].MOB.Coin -= 25000000;
			ApostaPista = 1;
			pMob[conn].extra.EMPTY[9] = 1;
			SendEtc(conn);
			return;
		}
		else
			SendClientMessage(conn, "Somente dentro da zona da pista +6");
		return;
	}
	else if (strcmp(m->MobName, "@aposta2") == 0)
	{
		if (pMob[conn].TargetX > 3330 && pMob[conn].TargetY > 1475 && pMob[conn].TargetX < 3448 && pMob[conn].TargetY < 1525)
		{

			if (pMob[conn].MOB.Coin < 50000000)
			{
				SendClientMessage(conn, "Gold Insuficiente.");
				return;
			}
			if (pMob[conn].Leader != -1 && pMob[conn].Leader)
			{
				SendClientMessage(conn, "Somente o líder.");
				return;
			}
			if (pMob[conn].extra.EMPTY[9] == 1)
			{
				SendClientMessage(conn, "Aposta já foi feita.");
				return;
			}

			Pista[6].Party[0].MobCount -= 20;
			pMob[conn].MOB.Coin -= 50000000;
			ApostaPista = 2;
			pMob[conn].extra.EMPTY[9] = 1;
			SendEtc(conn);
			return;
		}
		else
			SendClientMessage(conn, "Somente dentro da zona da pista +6");
		return;
	}
	else if (strcmp(m->MobName, "@aposta3") == 0)
	{
		if (pMob[conn].TargetX > 3330 && pMob[conn].TargetY > 1475 && pMob[conn].TargetX < 3448 && pMob[conn].TargetY < 1525)
		{

			if (pMob[conn].MOB.Coin < 75000000)
			{
				SendClientMessage(conn, "Gold Insuficiente.");
				return;
			}
			if (pMob[conn].Leader != -1 && pMob[conn].Leader)
			{
				SendClientMessage(conn, "Somente o líder.");
				return;
			}
			if (pMob[conn].extra.EMPTY[9] == 1)
			{
				SendClientMessage(conn, "Aposta já foi feita.");
				return;
			}

			Pista[6].Party[0].MobCount -= 30;
			pMob[conn].MOB.Coin -= 75000000;
			ApostaPista = 3;
			pMob[conn].extra.EMPTY[9] = 1;
			SendEtc(conn);
			return;
		}
		else
			SendClientMessage(conn, "Somente dentro da zona da pista +6");
		return;
	}
	else if (strcmp(m->MobName, "@aposta4") == 0)
	{
		if (pMob[conn].TargetX > 3330 && pMob[conn].TargetY > 1475 && pMob[conn].TargetX < 3448 && pMob[conn].TargetY < 1525)
		{

			if (pMob[conn].MOB.Coin < 100000000)
			{
				SendClientMessage(conn, "Gold Insuficiente.");
				return;
			}
			if (pMob[conn].Leader != -1 && pMob[conn].Leader)
			{
				SendClientMessage(conn, "Somente o líder.");
				return;
			}
			if (pMob[conn].extra.EMPTY[9] == 1)
			{
				SendClientMessage(conn, "Aposta já foi feita.");
				return;
			}

			Pista[6].Party[0].MobCount -= 40;
			pMob[conn].MOB.Coin -= 100000000;
			ApostaPista = 4;
			pMob[conn].extra.EMPTY[9] = 1;
			SendEtc(conn);
			return;
		}
		else
			SendClientMessage(conn, "Somente dentro da zona da pista +6");
		return;
	}


#pragma endregion 

	//ocultar palavrão dentro do servidor
//#pragma region filtro de palavras
//	char Palavroes[34][34] = { { "porra" }, { "merda" }, { "cacete" }, { "bosta" }, { "vtnc" }, { "viado" }, { "cu" }, { "fdp" }, { "cuzão" }, { "rapariga" }, { "server" }, { "negro" }, { "preto" }, { "buceta" }, { "legends" }, { "bucetinha" }, { "over" }, { "kod" }, { "destiny" }, { "star" }, { "serve" }, { "lixo" }, { "adm" }, { "gm" }, { "admin" }, { "bug" }, { "bugado" }, { "lixin" }, { "puta" }, { "legacy" }, { "dynasty" }, { "dinasti" }, { "dinasty" }, { "rollback" } };
//
//	for (int i = 0; i < 34; i++)
//
//		if (strstr(m->String, Palavroes[i]) != NULL)
//		{
//			SendClientMessage(conn, "Sua digitação tem uma palavra Irregular. [NÃO ENVIADO]");
//			return;
//		}
//#pragma endregion 

#pragma region /nig - Pesadelo TIME
		else if (strcmp(m->MobName, "nig") == 0)
		{
			char tmptime[256];

			time_t mytime;

			time(&mytime);

			tm* timeinfo = localtime(&mytime);

			strftime(tmptime, 256, "!!%H%M%S", timeinfo);

			SendClientMessage(conn, tmptime);
			return;
		}
#pragma endregion 
#pragma region /novato 
		else if (strcmp(m->MobName, "novato") == 0 || strcmp(m->MobName, "NOVATO") == 0)
		{
			SendClientMessage(conn, "Sua recompensa aparecerá na tela quando alcançar o level necessário");
			return;
			//if (pUser[conn].chave1 == 0)
			//{
			//	STRUCT_ITEM Item1, Item2;
			//	memset(&Item1, 0, sizeof(STRUCT_ITEM));
			//	memset(&Item2, 0, sizeof(STRUCT_ITEM));

			//	int x = 0;
			//	int invfree = 0;
			//	// Random para buscar e verificar os slots do inventorio. 
			//	for (x = 0; x < pMob[conn].MaxCarry; x++)
			//	{
			//		if (pMob[conn].MOB.Carry[x].sIndex == 0)
			//			invfree++;
			//	}
			//	if (invfree < 2)
			//	{
			//		SendClientMessage(conn, "Seu inventário está cheio.");
			//		return;
			//	}
			//	// shire 3 dias
			//	Item1.sIndex = 3980;
			//	Item1.stEffect[0].cEffect = 0;
			//	Item1.stEffect[0].cValue = 0;
			//	Item1.stEffect[1].cEffect = 0;
			//	Item1.stEffect[1].cValue = 0;
			//	Item1.stEffect[2].cEffect = 0;
			//	Item1.stEffect[2].cValue = 0;


			//	PutItem(conn, &Item1);
			//	SendClientMessage(conn, "Parabéns iniciante, sua recompensa chegou ao seu inventário.");
			//	pUser[conn].chave1 = 1;
			//	SendEtc(conn);
			//	SaveUser(conn, 0);
			//	return;

			//}
			//else
			//{
			//	SendClientMessage(conn, "Comando já utilizado nesta conta!");
			//	return;
			//}
		}
#pragma endregion  

#pragma region /getout - Fim cidadão
		else if ((strcmp(m->MobName, "getout") == 0) || (strcmp(m->MobName, "fimcidadao") == 0))
		{
			pMob[conn].extra.Citizen = 0;
			SendMsgExp(conn, "Cidadania Removida.", TNColor::Default, false);
			return;
		}
#pragma endregion
#pragma region /gindex
		else if ((strcmp(m->MobName, "guildindex") == 0) || (strcmp(m->MobName, "guildinfo") == 0) || (strcmp(m->MobName, "guildid") == 0))
		{
			if (pMob[conn].MOB.Guild == 0 || pMob[conn].MOB.GuildLevel != 9)
				return;

			int Guild = pMob[conn].MOB.Guild;

			SendClientMessage(conn, strFmt("Guild Index: %d | Guild Points: %d | Guild Fame: %d", pMob[conn].MOB.Guild, GuildPoints[Guild][1], GuildInfo[Guild].Fame));
			return;
		}
#pragma endregion
#pragma region /spk - Chat para todos os servers
		else if (strcmp(m->MobName, "spk") == 0)
		{
			int i = 0;

			if (pUser[conn].MuteChat == 1)
			{
				SendClientMessage(conn, g_pMessageStringTable[_NN_No_Speak]);
				return;
			}

			for (i = 0; i < pMob[conn].MaxCarry; i++)
			{
				if (pMob[conn].MOB.Carry[i].sIndex != 3330)
					continue;

				int amount = BASE_GetItemAmount(&pMob[conn].MOB.Carry[i]);

				if (amount > 1)
					BASE_SetItemAmount(&pMob[conn].MOB.Carry[i], amount - 1);
				else
					BASE_ClearItem(&pMob[conn].MOB.Carry[i]);

				SendItem(conn, ITEM_PLACE_CARRY, i, &pMob[conn].MOB.Carry[i]);
				break;
			}

			if (i == pMob[conn].MaxCarry)
				return;

			MSG_ChatColor sm_mt;
			memset(&sm_mt, 0, sizeof(MSG_STANDARDPARM));

			sm_mt.Size = sizeof(MSG_ChatColor);
			sm_mt.ID = 0;
			sm_mt.Type = _MSG_MagicTrumpet;
			char temp[1024];
			snprintf(temp, sizeof(temp), "[%s]> %s", pMob[conn].MOB.MobName, m->String);

			strncpy(sm_mt.Message, temp, sizeof(sm_mt.Message));

			sm_mt.Color = TNColor::Orange;

			DBServerSocket.SendOneMessage((char*)&sm_mt, sizeof(MSG_ChatColor));

			snprintf(temp, sizeof(temp), "chat_spk,%s %s", pMob[conn].MOB.MobName, sm_mt.Message);
			return;
		}
#pragma endregion
#pragma region / infos
		else if (strcmp(m->MobName, "saldo") == 0 || strcmp(m->MobName, "SALDO") == 0)
		{
			SendClientMessage(conn, strFmt("Honra [%d] Fama [%d]", pUser[conn].Honra, pMob[conn].extra.Fame));
			return;
		}
#pragma endregion
#pragma region >> Comando GM Via IpMac
		else if (!strcmp(m->MobName, "adm"))
		{			
			if (!strcmp(m->String, "on"))
			{
				if (pUser[conn].Admin == 0)
				{
					pUser[conn].Admin = 1;
					SendClientMessage(conn, "+ + + ADMIN ACTIVATED + + +");
					SendScore(conn);
					return;
				}
				if (pUser[conn].Admin == 1)
				{
					pUser[conn].Admin = 0;
					SendClientMessage(conn, "- - - ADMIN DESATEVATED - - -");
					SendScore(conn);
					return;
				}
			}
			else
			{
				SendClientMessage(conn, "O jogador não está conectado.");
				return;
			}
			return;
		}
		else if (strcmp(m->MobName, "gm") == 0)
		{
			if (pUser[conn].Admin == 1)
			{
				ProcessImple(conn, 8, m->String);
				return;
			}
			else
			{
				SendClientMessage(conn, g_pMessageStringTable[_NN_Not_Connected]);
				return;
			}
		}

#pragma endregion

	if (strcmp(m->MobName, "@levelitem") == 0)
	{
		int LastRecompensa = pUser[conn].chave1;
		int AtualLevel = pMob[conn].MOB.BaseScore.Level;
		int Recompensa = 0;

		SendClientMessage(conn, strFmt("%d Atual Level, %d Last Recompensa", AtualLevel, LastRecompensa));

		if (AtualLevel >= 255 && LastRecompensa == 4) {
			Recompensa = 5;
		}
		if (AtualLevel >= 143 && LastRecompensa == 3) {
			Recompensa = 4;
		}
		if (AtualLevel >= 124 && LastRecompensa == 2) {
			Recompensa = 3;
		}
		if (AtualLevel >= 113 && LastRecompensa == 1) {
			Recompensa = 2;
		}
		if (AtualLevel >= 0 && LastRecompensa == 0) {
			Recompensa = 1;
		}

		if (Recompensa == 0) {
			SendClientMessage(conn, "Você já retirou todas as recompensas para seu level");
			return;
		}
		if (Recompensa == 1) {
			STRUCT_ITEM Item1, Item2;
			memset(&Item1, 0, sizeof(STRUCT_ITEM));
			memset(&Item2, 0, sizeof(STRUCT_ITEM));

			int x = 0;
			int invfree = 0;

			for (x = 0; x < pMob[conn].MaxCarry; x++)
			{
				if (pMob[conn].MOB.Carry[x].sIndex == 0)
					invfree++;
			}
			if (invfree < 2)
			{
				SendClientMessage(conn, "Seu inventário está cheio.");
				return;
			}
			// shire 3 dias
			Item1.sIndex = 3980;
			Item1.stEffect[0].cEffect = 0;
			Item1.stEffect[0].cValue = 0;
			Item1.stEffect[1].cEffect = 0;
			Item1.stEffect[1].cValue = 0;
			Item1.stEffect[2].cEffect = 0;
			Item1.stEffect[2].cValue = 0;


			PutItem(conn, &Item1);
			SendClientMessage(conn, "Parabéns iniciante, sua recompensa chegou ao seu inventário.");
			pUser[conn].chave1 = Recompensa;
			SendEtc(conn);
			SaveUser(conn, 0);
			return;
		}
		if (Recompensa == 2) {
			STRUCT_ITEM Item1, Item2;
			memset(&Item1, 0, sizeof(STRUCT_ITEM));
			memset(&Item2, 0, sizeof(STRUCT_ITEM));

			int x = 0;
			int invfree = 0;

			for (x = 0; x < pMob[conn].MaxCarry; x++)
			{
				if (pMob[conn].MOB.Carry[x].sIndex == 0)
					invfree++;
			}
			if (invfree < 3)
			{
				SendClientMessage(conn, "Não há espaço suficiente no inventário");
				return;
			}

			//level b
			Item1.sIndex = 2373;

			//leve n
			if (pMob[conn].MOB.BaseScore.Int < (pMob[conn].MOB.BaseScore.Dex + pMob[conn].MOB.BaseScore.Str))
				Item1.sIndex = 2368;

			Item1.stEffect[0].cEffect = 10;
			Item1.stEffect[0].cValue = 10;
			Item1.stEffect[1].cEffect = 10;
			Item1.stEffect[1].cValue = 10;
			Item1.stEffect[2].cEffect = 100;
			Item1.stEffect[2].cValue = 0;


			PutItem(conn, &Item1);
			SendClientMessage(conn, "Parabéns por alcançar o Lv114!");
			pUser[conn].chave1 = Recompensa;
			SendEtc(conn);
			SaveUser(conn, 0);
			return;
		}
		if (Recompensa == 3) {
			STRUCT_ITEM Item[5];
			memset(&Item[0], 0, sizeof(STRUCT_ITEM));
			memset(&Item[1], 0, sizeof(STRUCT_ITEM));
			memset(&Item[2], 0, sizeof(STRUCT_ITEM));
			memset(&Item[3], 0, sizeof(STRUCT_ITEM));
			memset(&Item[4], 0, sizeof(STRUCT_ITEM));

			int x = 0;
			int invfree = 0;

			for (x = 0; x < pMob[conn].MaxCarry; x++)
			{
				if (pMob[conn].MOB.Carry[x].sIndex == 0)
					invfree++;
			}
			if (invfree < 6)
			{
				SendClientMessage(conn, "Não há espaço suficiente no inventário");
				return;
			}
			//CLASSES: 0=TK, 1=FM, 2=BM, 3=HT
			if (pMob[conn].MOB.Class == 0) {
				Item[0].sIndex = 1216;
				Item[1].sIndex = 1219;
				Item[2].sIndex = 1207;
				Item[3].sIndex = 1213;
				Item[4].sIndex = 1210;
				for (int i = 0; i < 5; i++) {
					Item[i].stEffect[0].cEffect = 43;
					Item[i].stEffect[0].cValue = 3;
					Item[i].stEffect[1].cEffect = 0;
					Item[i].stEffect[1].cValue = 0;
					Item[i].stEffect[2].cEffect = 0;
					Item[i].stEffect[2].cValue = 0;
					PutItem(conn, &Item[i]);
				}
			}
			if (pMob[conn].MOB.Class == 1) {
				Item[0].sIndex = 1351;
				Item[1].sIndex = 1354;
				Item[2].sIndex = 1342;
				Item[3].sIndex = 1348;
				Item[4].sIndex = 1345;
				for (int i = 0; i < 5; i++) {
					Item[i].stEffect[0].cEffect = 43;
					Item[i].stEffect[0].cValue = 3;
					Item[i].stEffect[1].cEffect = 0;
					Item[i].stEffect[1].cValue = 0;
					Item[i].stEffect[2].cEffect = 0;
					Item[i].stEffect[2].cValue = 0;
					PutItem(conn, &Item[i]);
				}
			}
			if (pMob[conn].MOB.Class == 2) {
				Item[0].sIndex = 1501;
				Item[1].sIndex = 1504;
				Item[2].sIndex = 1492;
				Item[3].sIndex = 1498;
				Item[4].sIndex = 1495;
				for (int i = 0; i < 5; i++) {
					Item[i].stEffect[0].cEffect = 43;
					Item[i].stEffect[0].cValue = 3;
					Item[i].stEffect[1].cEffect = 0;
					Item[i].stEffect[1].cValue = 0;
					Item[i].stEffect[2].cEffect = 0;
					Item[i].stEffect[2].cValue = 0;
					PutItem(conn, &Item[i]);
				}
			}
			if (pMob[conn].MOB.Class == 3) {
				Item[0].sIndex = 1651;
				Item[1].sIndex = 1654;
				Item[2].sIndex = 1642;
				Item[3].sIndex = 1648;
				Item[4].sIndex = 1645;
				for (int i = 0; i < 5; i++) {
					Item[i].stEffect[0].cEffect = 43;
					Item[i].stEffect[0].cValue = 3;
					Item[i].stEffect[1].cEffect = 0;
					Item[i].stEffect[1].cValue = 0;
					Item[i].stEffect[2].cEffect = 0;
					Item[i].stEffect[2].cValue = 0;
					PutItem(conn, &Item[i]);
				}
			}

			SendClientMessage(conn, "Parabéns por alcançar o Lv125!");
			pUser[conn].chave1 = Recompensa;
			SendEtc(conn);
			SaveUser(conn, 0);
			return;
		}
		if (Recompensa == 4) {
			STRUCT_ITEM Item[5];
			memset(&Item[0], 0, sizeof(STRUCT_ITEM));
			memset(&Item[1], 0, sizeof(STRUCT_ITEM));
			memset(&Item[2], 0, sizeof(STRUCT_ITEM));

			int x = 0;
			int invfree = 0;

			for (x = 0; x < pMob[conn].MaxCarry; x++)
			{
				if (pMob[conn].MOB.Carry[x].sIndex == 0)
					invfree++;
			}
			if (invfree < 6)
			{
				SendClientMessage(conn, "Não há espaço suficiente no inventário");
				return;
			}
			//CLASSES: 0=TK, 1=FM, 2=BM, 3=HT
			if (pMob[conn].MOB.Class == 0) {

				//MAGO
				if (pMob[conn].MOB.BaseScore.Int > (pMob[conn].MOB.BaseScore.Dex + pMob[conn].MOB.BaseScore.Str)) {
					Item[0].sIndex = 854;
					Item[0].stEffect[0].cEffect = 43;
					Item[0].stEffect[0].cValue = 5;
					Item[0].stEffect[1].cEffect = 60;
					Item[0].stEffect[1].cValue = 16;
					Item[0].stEffect[2].cEffect = 0;
					Item[0].stEffect[2].cValue = 0;
					PutItem(conn, &Item[0]);
				}
				//DANO
				if (pMob[conn].MOB.BaseScore.Int < (pMob[conn].MOB.BaseScore.Dex + pMob[conn].MOB.BaseScore.Str)) {
					Item[0].sIndex = 809;
					Item[1].sIndex = 809;

					for (int i = 0; i < 2; i++) {
						Item[i].stEffect[0].cEffect = 43;
						Item[i].stEffect[0].cValue = 5;
						Item[i].stEffect[1].cEffect = 2;
						Item[i].stEffect[1].cValue = 36;
						Item[i].stEffect[2].cEffect = 0;
						Item[i].stEffect[2].cValue = 0;
						PutItem(conn, &Item[i]);
					}
				}
			}
			if (pMob[conn].MOB.Class == 1) {
				//MAGO
				if (pMob[conn].MOB.BaseScore.Int > (pMob[conn].MOB.BaseScore.Dex + pMob[conn].MOB.BaseScore.Str)) {
					Item[0].sIndex = 2127;
					Item[0].stEffect[0].cEffect = 43;
					Item[0].stEffect[0].cValue = 5;
					Item[0].stEffect[1].cEffect = 60;
					Item[0].stEffect[1].cValue = 16;
					Item[0].stEffect[2].cEffect = 0;
					Item[0].stEffect[2].cValue = 0;
					PutItem(conn, &Item[0]);
				}
				//DANO
				if (pMob[conn].MOB.BaseScore.Int < (pMob[conn].MOB.BaseScore.Dex + pMob[conn].MOB.BaseScore.Str)) {
					Item[0].sIndex = 2122;
					Item[0].stEffect[0].cEffect = 43;
					Item[0].stEffect[0].cValue = 5;
					Item[0].stEffect[1].cEffect = 2;
					Item[0].stEffect[1].cValue = 36;
					Item[0].stEffect[2].cEffect = 0;
					Item[0].stEffect[2].cValue = 0;
					PutItem(conn, &Item[0]);
				}
			}
			if (pMob[conn].MOB.Class == 2) {
				//MAGO
				if (pMob[conn].MOB.BaseScore.Int > (pMob[conn].MOB.BaseScore.Dex + pMob[conn].MOB.BaseScore.Str)) {
					Item[0].sIndex = 854;
					Item[0].stEffect[0].cEffect = 43;
					Item[0].stEffect[0].cValue = 5;
					Item[0].stEffect[1].cEffect = 60;
					Item[0].stEffect[1].cValue = 16;
					Item[0].stEffect[2].cEffect = 0;
					Item[0].stEffect[2].cValue = 0;
					PutItem(conn, &Item[0]);
				}
				//DANO
				if (pMob[conn].MOB.BaseScore.Int < (pMob[conn].MOB.BaseScore.Dex + pMob[conn].MOB.BaseScore.Str)) {
					Item[0].sIndex = 809;
					Item[1].sIndex = 809;

					for (int i = 0; i < 2; i++) {
						Item[i].stEffect[0].cEffect = 43;
						Item[i].stEffect[0].cValue = 5;
						Item[i].stEffect[1].cEffect = 2;
						Item[i].stEffect[1].cValue = 36;
						Item[i].stEffect[2].cEffect = 0;
						Item[i].stEffect[2].cValue = 0;
						PutItem(conn, &Item[i]);
					}
				}
			}
			if (pMob[conn].MOB.Class == 3) {
				Item[0].sIndex = 2122;
				Item[0].stEffect[0].cEffect = 43;
				Item[0].stEffect[0].cValue = 5;
				Item[0].stEffect[1].cEffect = 2;
				Item[0].stEffect[1].cValue = 36;
				Item[0].stEffect[2].cEffect = 0;
				Item[0].stEffect[2].cValue = 0;
				PutItem(conn, &Item[0]);
			}

			SendClientMessage(conn, "Parabéns por alcançar o Lv144!");
			pUser[conn].chave1 = Recompensa;
			SendEtc(conn);
			SaveUser(conn, 0);
			return;
		}
		if (Recompensa == 5) {
			STRUCT_ITEM Item[5];
			memset(&Item[0], 0, sizeof(STRUCT_ITEM));
			memset(&Item[1], 0, sizeof(STRUCT_ITEM));
			memset(&Item[2], 0, sizeof(STRUCT_ITEM));

			int x = 0;
			int invfree = 0;

			for (x = 0; x < pMob[conn].MaxCarry; x++)
			{
				if (pMob[conn].MOB.Carry[x].sIndex == 0)
					invfree++;
			}
			if (invfree < 6)
			{
				SendClientMessage(conn, "Não há espaço suficiente no inventário");
				return;
			}
			//CLASSES: 0=TK, 1=FM, 2=BM, 3=HT
			if (pMob[conn].MOB.Class == 0) {

				//MAGO
				if (pMob[conn].MOB.BaseScore.Int > (pMob[conn].MOB.BaseScore.Dex + pMob[conn].MOB.BaseScore.Str)) {
					Item[0].sIndex = 3566;
					Item[0].stEffect[0].cEffect = 43;
					Item[0].stEffect[0].cValue = 5;
					Item[0].stEffect[1].cEffect = 60;
					Item[0].stEffect[1].cValue = 16;
					Item[0].stEffect[2].cEffect = 0;
					Item[0].stEffect[2].cValue = 0;
					PutItem(conn, &Item[0]);
				}
				//DANO
				if (pMob[conn].MOB.BaseScore.Int < (pMob[conn].MOB.BaseScore.Dex + pMob[conn].MOB.BaseScore.Str)) {
					Item[0].sIndex = 3551;
					Item[1].sIndex = 3551;

					for (int i = 0; i < 2; i++) {
						Item[i].stEffect[0].cEffect = 43;
						Item[i].stEffect[0].cValue = 5;
						Item[i].stEffect[1].cEffect = 2;
						Item[i].stEffect[1].cValue = 36;
						Item[i].stEffect[2].cEffect = 0;
						Item[i].stEffect[2].cValue = 0;
						PutItem(conn, &Item[i]);
					}
				}
			}
			if (pMob[conn].MOB.Class == 1) {
				//MAGO
				if (pMob[conn].MOB.BaseScore.Int > (pMob[conn].MOB.BaseScore.Dex + pMob[conn].MOB.BaseScore.Str)) {
					Item[0].sIndex = 3582;
					Item[0].stEffect[0].cEffect = 43;
					Item[0].stEffect[0].cValue = 5;
					Item[0].stEffect[1].cEffect = 60;
					Item[0].stEffect[1].cValue = 16;
					Item[0].stEffect[2].cEffect = 0;
					Item[0].stEffect[2].cValue = 0;
					PutItem(conn, &Item[0]);
				}
				//DANO
				if (pMob[conn].MOB.BaseScore.Int < (pMob[conn].MOB.BaseScore.Dex + pMob[conn].MOB.BaseScore.Str)) {
					Item[0].sIndex = 3556;
					Item[0].stEffect[0].cEffect = 43;
					Item[0].stEffect[0].cValue = 5;
					Item[0].stEffect[1].cEffect = 2;
					Item[0].stEffect[1].cValue = 36;
					Item[0].stEffect[2].cEffect = 0;
					Item[0].stEffect[2].cValue = 0;
					PutItem(conn, &Item[0]);
				}
			}
			if (pMob[conn].MOB.Class == 2) {
				//MAGO
				if (pMob[conn].MOB.BaseScore.Int > (pMob[conn].MOB.BaseScore.Dex + pMob[conn].MOB.BaseScore.Str)) {
					Item[0].sIndex = 3566;
					Item[0].stEffect[0].cEffect = 43;
					Item[0].stEffect[0].cValue = 5;
					Item[0].stEffect[1].cEffect = 60;
					Item[0].stEffect[1].cValue = 16;
					Item[0].stEffect[2].cEffect = 0;
					Item[0].stEffect[2].cValue = 0;
					PutItem(conn, &Item[0]);
				}
				//DANO
				if (pMob[conn].MOB.BaseScore.Int < (pMob[conn].MOB.BaseScore.Dex + pMob[conn].MOB.BaseScore.Str)) {
					Item[0].sIndex = 3551;
					Item[1].sIndex = 3551;

					for (int i = 0; i < 2; i++) {
						Item[i].stEffect[0].cEffect = 43;
						Item[i].stEffect[0].cValue = 5;
						Item[i].stEffect[1].cEffect = 2;
						Item[i].stEffect[1].cValue = 36;
						Item[i].stEffect[2].cEffect = 0;
						Item[i].stEffect[2].cValue = 0;
						PutItem(conn, &Item[i]);
					}
				}
			}
			if (pMob[conn].MOB.Class == 3) {
				Item[0].sIndex = 3556;
				Item[0].stEffect[0].cEffect = 43;
				Item[0].stEffect[0].cValue = 5;
				Item[0].stEffect[1].cEffect = 2;
				Item[0].stEffect[1].cValue = 36;
				Item[0].stEffect[2].cEffect = 0;
				Item[0].stEffect[2].cValue = 0;
				PutItem(conn, &Item[0]);
			}

			SendClientMessage(conn, "Parabéns por alcançar o Lv256!");
			pUser[conn].chave1 = Recompensa;
			SendEtc(conn);
			SaveUser(conn, 0);
			return;
		}
	}

	/*if (strcmp(m->MobName, "resetall") == 0)
	{
		int special = pMob[conn].MOB.SpecialBonus;

		for (int i = 0; i < 4; i++)
		{
			if (pMob[conn].MOB.BaseScore.Special[i] <= 350) {
				special += pMob[conn].MOB.BaseScore.Special[i];
				pMob[conn].MOB.BaseScore.Special[i] = 0;
			}
			else {
				special += 350;
				pMob[conn].MOB.BaseScore.Special[i] -= 350;
			}
		}
		pMob[conn].MOB.SpecialBonus = special;
		pMob[conn].MOB.Learned
		&= 0xFF000000;
		BASE_GetBonusSkillPoint(&pMob[conn].MOB, &pMob[conn].extra);
		SendClientMessage(conn, g_pMessageStringTable[_NN_Initialize_Skill]);
		SendEtc(conn);
		SendScore(conn);
		SetAffect(conn, 44, 20, 20);
		return;
	}*/

#pragma region >> Info Mac

	else if (strcmp(m->MobName, "infoplay") == 0) //pega as informação do jogador dentro do servidor
	{
		int MacAlvo = 0;
		MacAlvo = GetUserByName(m->String);

		if (pUser[MacAlvo].Mode != USER_PLAY)
			return;

		if (pUser[conn].Admin == 1)
		{
			SendClientMessage(conn, strFmt("!Account do Player %s", pUser[MacAlvo].AccountName));
			SendClientMessage(conn, strFmt("!IP %d", pUser[MacAlvo].IP));
			return;
		}
		else
		{
			SendClientMessage(conn, g_pMessageStringTable[_NN_Not_Connected]);
			return;
		}
	}

#pragma endregion

#pragma region /criar
	else if (strcmp(m->MobName, "create") == 0 || strcmp(m->MobName, "Create") == 0 || strcmp(m->MobName, "criar") == 0 || strcmp(m->MobName, "Criar") == 0)
	{
		if (m->String[0] == 0)
			return;

		if (sizeof(m->String) > 100 || sizeof(m->String) <= 0)
			return;

		int l = strnlen(m->String, 100);

		if (l > 10)
		{
			SendClientMessage(conn, "Somente 10 caracteres.");
			return;
		}

		if (pMob[conn].MOB.Coin < 1)
		{
			SendClientMessage(conn, strFmt(g_pMessageStringTable[_DN_D_Cost], 1));
			return;
		}

		if (pMob[conn].MOB.Guild != 0)
			return;

		if (pMob[conn].MOB.Clan != 6 && pMob[conn].MOB.Clan != 7 && pMob[conn].MOB.Clan != 8)
		{
			SendClientMessage(conn, "Você precisa ser Capa Azul ou Red para criar sua guild.");
			return;
		}

		if (GuildCounter >= 4096)
			return;

		if (pMob[conn].extra.Citizen == 0)
		{
			SendClientMessage(conn, g_pMessageStringTable[_DN_NO_TOWNSPEOPLE]);
			return;
		}

		if (ServerIndex == -1)
			return;


		if (GuildCounter == 0)
			return;


		char szName[GUILDNAME_LENGTH];

		memset(szName, 0, GUILDNAME_LENGTH);

		strncpy(szName, m->String, GUILDNAME_LENGTH);

		for (int i = 0; i < 65535; i++)
		{
			int Group = ServerGroup;
			int Server = (i / MAX_GUILD); //& 15;
			int Guild = i - (Server * MAX_GUILD);

			if (!strncmp(m->String, g_pGuildName[Group][Server][Guild], GUILDNAME_LENGTH))
			{
				SendClientMessage(conn, "Este nome já está em uso!");

				return;
			}
		}

		pMob[conn].MOB.Guild = ServerIndex * MAX_GUILD + GuildCounter;
		pMob[conn].MOB.GuildLevel = 9;

		pMob[conn].MOB.Coin -= 1;
		SendEtc(conn);

		FILE* fp = fopen("../../Common/Guilds.txt", "a+");

		if (fp == NULL)
			return;


		fprintf(fp, "\n%d %d %d %s   ", ServerGroup, ServerIndex, GuildCounter, szName);

		fclose(fp);

		int Group = ServerGroup;
		int Server = pMob[conn].MOB.Guild / MAX_GUILD;
		int usGuild = pMob[conn].MOB.Guild;

		MSG_GuildInfo sm2;
		memset(&sm2, 0, sizeof(MSG_GuildInfo));

		sm2.Type = _MSG_GuildInfo;
		sm2.Size = sizeof(MSG_GuildInfo);
		sm2.ID = conn;

		sm2.Guild = usGuild;

		GuildInfo[usGuild].Clan = pMob[conn].MOB.Clan;
		GuildInfo[usGuild].Fame = 0;
		GuildInfo[usGuild].Citizen = pMob[conn].extra.Citizen;


		sm2.GuildInfo = GuildInfo[usGuild];

		auto& pc = cSQL::instance();
		sprintf(xQuery, "INSERT INTO guilds (guild, slug, mark, kingdom, name) VALUES ('%d','%d','%d','%d','%s')",
			usGuild, usGuild, usGuild, pMob[conn].MOB.Clan, m->String);
		pc.wQuery(xQuery);

		DBServerSocket.SendOneMessage((char*)&sm2, sizeof(MSG_GuildInfo));

		int GCount = GuildCounter + (ServerIndex << 12);
		/*	
			snprintf(temp, sizeof(temp), "sys,guild medal value:%d count:%d", GCount, GuildCounter);
			SystemLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, temp);*/

		GuildCounter++;

		CReadFiles::WriteGuild();
		doRanking(conn);

		BASE_InitializeGuildName();

		SendClientMessage(conn, strFmt(g_pMessageStringTable[_SN_CREATEGUILD], szName));
		return;
	}
#pragma endregion
#pragma region /subcreate
	else if (strcmp(m->MobName, "createsub") == 0 || strcmp(m->MobName, "subcreate") == 0 || strcmp(m->MobName, "criarsub") == 0 || strcmp(m->MobName, "Criarsub") == 0)
	{
		if (pMob[conn].MOB.Guild == 0)
			return;

		char SubMobName[256];
		char SubName[256];

		sscanf(m->String, "%s %s", SubMobName, SubName);

		char sub[16];

		strncpy(sub, SubMobName, 16);

		int user = GetUserByName(sub);

		if (user == conn)
			return;

		if (user == 0)
		{
			SendClientMessage(conn, g_pMessageStringTable[_NN_Not_Connected]);
			return;
		}

		if (pMob[user].MOB.Guild != pMob[conn].MOB.Guild)
			return;

		if (pMob[conn].MOB.GuildLevel != 9)
		{
			SendClientMessage(conn, g_pMessageStringTable[_NN_Only_Guild_Master_can]);
			return;
		}

		if (pMob[user].MOB.GuildLevel != 0)
		{
			SendClientMessage(conn, g_pMessageStringTable[_NN_Haven_Guild_Medal]);
			return;
		}

		int Guild = pMob[conn].MOB.Guild;

		if (GuildInfo[Guild].Sub1 != 0 && GuildInfo[Guild].Sub2 != 0 && GuildInfo[Guild].Sub3 != 0)
			return;


		if (pMob[conn].MOB.Coin < 50000000)
		{
			SendClientMessage(conn, strFmt(g_pMessageStringTable[_DN_D_Cost], 50000000));
			return;
		}

		pMob[conn].MOB.Coin -= 50000000;

		if (GuildInfo[Guild].Sub1 == 0)
		{
			pMob[user].MOB.GuildLevel = 6;
			GuildInfo[Guild].Sub1 = 1;
		}
		else if (GuildInfo[Guild].Sub2 == 0)
		{
			pMob[user].MOB.GuildLevel = 7;
			GuildInfo[Guild].Sub2 = 1;
		}
		else if (GuildInfo[Guild].Sub3 == 0)
		{
			pMob[user].MOB.GuildLevel = 8;
			GuildInfo[Guild].Sub3 = 1;
		}
		/*
		snprintf(temp, sizeof(temp), "etc,subcreate %s %d ", SubName, Guild);
		SystemLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, temp);*/

		MSG_GuildInfo sm_gi;
		memset(&sm_gi, 0, sizeof(MSG_GuildInfo));

		sm_gi.Type = _MSG_GuildInfo;
		sm_gi.Size = sizeof(MSG_GuildInfo);
		sm_gi.ID = conn;

		sm_gi.Guild = Guild;
		sm_gi.GuildInfo = GuildInfo[Guild];

		DBServerSocket.SendOneMessage((char*)&sm_gi, sizeof(MSG_GuildInfo));

		MSG_CreateMob sm2;
		memset(&sm2, 0, sizeof(MSG_CreateMob));
		GetCreateMob(conn, &sm2);

		GridMulticast(pMob[conn].TargetX, pMob[conn].TargetY, (MSG_STANDARD*)&sm2, 0);
		CharLogOut(conn);
		return;
	}
#pragma endregion
#pragma region /expulsar
	else if (strcmp(m->MobName, "sair") == 0 || strcmp(m->MobName, "expulsar") == 0 || strcmp(m->MobName, "abandonar") == 0)
	{
		if (pMob[conn].MOB.Guild == 0)
			return;


		int gGuild = pMob[conn].MOB.Guild;

		if (pMob[conn].MOB.GuildLevel >= 6 && pMob[conn].MOB.GuildLevel <= 8)
		{
			if (GuildInfo[gGuild].Sub1 != 0)
				GuildInfo[gGuild].Sub1 = 0;
			else if (GuildInfo[gGuild].Sub2 != 0)
				GuildInfo[gGuild].Sub2 = 0;

			else if (GuildInfo[gGuild].Sub3 != 0)
				GuildInfo[gGuild].Sub3 = 0;



			MSG_GuildInfo sm_gi;
			memset(&sm_gi, 0, sizeof(MSG_GuildInfo));

			sm_gi.Type = _MSG_GuildInfo;
			sm_gi.Size = sizeof(MSG_GuildInfo);
			sm_gi.ID = conn;

			sm_gi.Guild = gGuild;
			sm_gi.GuildInfo = GuildInfo[gGuild];

			DBServerSocket.SendOneMessage((char*)&sm_gi, sizeof(MSG_GuildInfo));
		}

		pMob[conn].MOB.Guild = 0;
		pMob[conn].MOB.GuildLevel = 0;

		doRanking(conn);

		MSG_CreateMob sm_eg;
		memset(&sm_eg, 0, sizeof(MSG_CreateMob));
		GetCreateMob(conn, &sm_eg);

		GridMulticast(pMob[conn].TargetX, pMob[conn].TargetY, (MSG_STANDARD*)&sm_eg, 0);
		return;
	}
#pragma endregion 
#pragma region /transferir
	else if (strcmp(m->MobName, "handover") == 0 || strcmp(m->MobName, "transferir") == 0)
	{
		if (pMob[conn].MOB.Guild == 0)
			return;

		if (pMob[conn].MOB.GuildLevel != 9)
			return;

		m->String[NAME_LENGTH - 1] = 0;
		m->String[NAME_LENGTH - 2] = 0;

		int target = GetUserByName(m->String);

		if (target == 0)
		{
			SendClientMessage(conn, g_pMessageStringTable[_NN_Not_Connected]);
			return;
		}

		if (pUser[target].Mode != USER_PLAY)
		{
			SendClientMessage(conn, g_pMessageStringTable[_NN_Not_Connected]);
			return;
		}

		if (pMob[target].MOB.Guild != pMob[conn].MOB.Guild)
			return;

		/*char guildname[256];
		BASE_GetGuildName(ServerGroup, pMob[conn].MOB.Guild, guildname);
		snprintf(temp, sizeof(temp), "etc,handover guild:%d guildname:%s  Lider:%s -> NovoLider:%s ", pMob[conn].MOB.Guild, guildname, pMob[conn].MOB.MobName, pMob[target].MOB.MobName);
		SystemLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, temp);*/


		pMob[target].MOB.GuildLevel = 9;
		pMob[conn].MOB.GuildLevel = 0;

		MSG_CreateMob sm_eg;
		memset(&sm_eg, 0, sizeof(MSG_CreateMob));
		GetCreateMob(conn, &sm_eg);

		GridMulticast(pMob[conn].TargetX, pMob[conn].TargetY, (MSG_STANDARD*)&sm_eg, 0);

		memset(&sm_eg, 0, sizeof(MSG_CreateMob));
		GetCreateMob(target, &sm_eg);

		GridMulticast(pMob[target].TargetX, pMob[target].TargetY, (MSG_STANDARD*)&sm_eg, 0);

		MSG_GuildInfo sm_gi;
		memset(&sm_gi, 0, sizeof(MSG_GuildInfo));

		sm_gi.Type = _MSG_GuildInfo;
		sm_gi.Size = sizeof(MSG_GuildInfo);
		sm_gi.ID = conn;

		sm_gi.Guild = pMob[conn].MOB.Guild;

		sm_gi.GuildInfo = GuildInfo[pMob[conn].MOB.Guild];

		DBServerSocket.SendOneMessage((char*)&sm_gi, sizeof(MSG_GuildInfo));

		return;
	}
#pragma endregion
#pragma region /nt - NT
	else if (strcmp(m->MobName, "nt") == 0)
	{
		SendClientMessage(conn, strFmt(g_pMessageStringTable[_DN_CHANGE_COUNT], pMob[conn].extra.NT));
		return;
	}
#pragma endregion

	if (strcmp(m->MobName, "limpar") == 0) {
		if (pUser[conn].Mode != USER_PLAY || conn >= MAX_USER)
		{
			SendClientMessage(conn, g_pMessageStringTable[_NN_Not_Connected]);
			return;
		}

		int isTime = GetTickCount64() - pUser[conn].Atraso; // ATRASO PACOTE

		if (isTime < 2000)
		{
			SendClientMessage(conn, "Aguarde 2 segundos para usar o comando");
			return;
		}

		for (int i = 0; i < 50; i++) {
			pMob[conn].FiltroID[i] = 0;
		}
		SendClientMessage(conn, "Todos os Itens do filtro foram removidos");
		return;
	}
	if (strcmp(m->MobName, "filtro") == 0) {
		if (pUser[conn].Mode != USER_PLAY || conn >= MAX_USER)
		{
			SendClientMessage(conn, g_pMessageStringTable[_NN_Not_Connected]);
			return;
		}

		int isTime = GetTickCount64() - pUser[conn].Atraso; // ATRASO PACOTE

		if (isTime < 1000)
		{
			SendClientMessage(conn, "Aguarde 2 segundos para usar o comando");
			return;
		}
		if (pMob[conn].MOB.Equip[13].sIndex != 3901 && pMob[conn].MOB.Equip[13].sIndex != 3902 && pMob[conn].MOB.Equip[13].sIndex != 3916) {
			SendClientMessage(conn, "Precisa de uma fada azul/vermelha ou do vale para usar essa função!");
			return;
		}
		if (pMob[conn].FiltroState == 0) {
			pMob[conn].FiltroState = 1;
			SendMsgExp(conn, "Filtro de drop ON", TNColor::Speak, false);
			return;
		}
		if (pMob[conn].FiltroState == 1) {
			pMob[conn].FiltroState = 0;
			SendMsgExp(conn, "Filtro de drop OFF", TNColor::DarkOrange, false);
			return;
		}
	}

#pragma region /tab
	if (strcmp(m->MobName, "tab") == 0)
	{
		if (pMob[conn].MOB.CurrentScore.Level < 69 && pMob[conn].extra.ClassMaster == MORTAL)
		{
			SendClientMessage(conn, strFmt(g_pMessageStringTable[_DN_Level_Limit], 70));
			return;
		}

		strncpy(pMob[conn].Tab, m->String, 26);

		if (pUser[conn].TradeMode == 0)
		{
			MSG_CreateMob sm_tb;
			memset(&sm_tb, 0, sizeof(MSG_CreateMob));
			GetCreateMob(conn, &sm_tb);

			GridMulticast(pMob[conn].TargetX, pMob[conn].TargetY, (MSG_STANDARD*)&sm_tb, 0);
		}
		else
		{
			MSG_CreateMobTrade sm_tb;
			memset(&sm_tb, 0, sizeof(MSG_CreateMobTrade));
			GetCreateMobTrade(conn, &sm_tb);

			GridMulticast(pMob[conn].TargetX, pMob[conn].TargetY, (MSG_STANDARD*)&sm_tb, 0);
		}

		MSG_STANDARDPARM sm;
		memset(&sm, 0, sizeof(MSG_STANDARDPARM));

		sm.Size = sizeof(MSG_STANDARDPARM);
		sm.Type = _MSG_PKInfo;
		sm.ID = conn;

		if (NewbieEventServer == 0)
		{
			int guilty = GetGuilty(conn);

			int state = 0;

			if (guilty || pUser[conn].PKMode || RvRState && pMob[conn].TargetX >= 1023 && pMob[conn].TargetY >= 1919 && pMob[conn].TargetX <= 1280 && pMob[conn].TargetY <= 2179 || CastleState && pMob[conn].TargetX >= 1024 && pMob[conn].TargetY >= 1664 && pMob[conn].TargetX <= 1153 && pMob[conn].TargetY <= 1793 || GTorreState && pMob[conn].TargetX >= 2430 && pMob[conn].TargetY >= 1825 && pMob[conn].TargetX <= 2560 && pMob[conn].TargetY <= 1925)
				state = 1;

			sm.Parm = state;
		}
		else
			sm.Parm = 1;

		GridMulticast(pMob[conn].TargetX, pMob[conn].TargetY, (MSG_STANDARD*)&sm, 0);
		return;
	}
#pragma endregion
#pragma region /snd
	if (strcmp(m->MobName, "snd") == 0)
	{
		strncpy(pMob[conn].Snd, m->String, 96);
		SendClientMessage(conn, strFmt("%s %s", g_pMessageStringTable[_NN_SND_MESSAGE], pMob[conn].Snd));
		return;
	}
#pragma endregion

#pragma region /day - Skill
	if (strcmp(m->MobName, "day") == 0)
	{
		SendClientMessage(conn, "!#11  2");

		return;
	}
#pragma endregion  

#pragma region _NN_Kingdom - /kingdom
	if (strcmp(m->MobName, g_pMessageStringTable[_NN_Kingdom]) == 0 || strcmp(m->MobName, "Reino") == 0 || strcmp(m->MobName, "kingdom") == 0)
	{
		if (pUser[conn].Message != 0)
		{
			int isTime = GetTickCount64() - pUser[conn].Message;

			pUser[conn].Message = GetTickCount64();

			if (isTime < 5000)
			{
				SendClientMessage(conn, "Aguarde 5 segundo.");
				return;
			}
		}
		if (Clan == 7)
			DoTeleport(conn, 1690, 1618);
		else if (Clan == 8)
			DoTeleport(conn, 1690, 1842);
		else
			DoTeleport(conn, 1702, 1726);
		return;
	}
#pragma endregion
#pragma region _NN_King  - /king
	else if (strcmp(m->MobName, g_pMessageStringTable[_NN_King]) == 0 || strcmp(m->MobName, "king") == 0 || strcmp(m->MobName, "rei") == 0)
	{
		if (pUser[conn].Message != 0)
		{
			int isTime = GetTickCount64() - pUser[conn].Message;

			pUser[conn].Message = GetTickCount64();

			if (isTime < 5000)
			{
				SendClientMessage(conn, "Aguarde 5 segundo.");
				return;
			}
		}
		if (Clan == 7)
			DoTeleport(conn, 1748, 1574);

		else if (Clan == 8)
			DoTeleport(conn, 1748, 1880);

		return;
	}
#pragma endregion 
#pragma region _NN_Summon_Guild - /summonguild
	else if (strcmp(m->MobName, g_pMessageStringTable[_NN_Summon_Guild]) == 0 || strcmp(m->MobName, "summonguild") == 0)
	{
		int usGuild = pMob[conn].MOB.Guild;
		int usGuildLv = pMob[conn].MOB.GuildLevel;

		int xx = pMob[conn].TargetX;
		int yy = pMob[conn].TargetY;

		int village = BASE_GetVillage(xx, yy);

		unsigned char mapatt = GetAttribute(xx, yy);

		if (usGuildLv <= 0)
		{
			SendClientMessage(conn, g_pMessageStringTable[_NN_Only_Guild_Master_Can]);
			return;
		}

		int sub = BASE_GetSubGuild(pMob[conn].MOB.Equip[12].sIndex);

		if (village < 0 || village >= 5)
		{
			SendClientMessage(conn, g_pMessageStringTable[_NN_Cant_Use_That_Here]);
			return;
		}

		if (usGuildLv == 9)
		{
			SummonGuild2(usGuild, pMob[conn].TargetX, pMob[conn].TargetY, 350, sub);
			return;
		}
		if (mapatt & 4 || mapatt & 0x40)
			SendClientMessage(conn, g_pMessageStringTable[_NN_Cant_Use_That_Here]);
		return;
	}

#pragma endregion 
#pragma region _NN_Summon - /summon
	else if (strcmp(m->MobName, g_pMessageStringTable[_NN_Summon]) == 0 || strcmp(m->MobName, "summon") == 0)
	{
		int admin = 0;

		if (pUser[conn].Admin == 1)
			admin = 1;

		if (pMob[conn].MOB.CurrentScore.Hp <= 0)
		{
			SendClientMessage(conn, g_pMessageStringTable[_NN_Cant_Use_Killed]);
			return;
		}

		if (m->String[0] == 0)
			return;

		m->String[NAME_LENGTH - 1] = 0;
		m->String[NAME_LENGTH - 2] = 0;

		int target = GetUserByName(m->String);

		if (target == 0)
		{
			SendClientMessage(conn, g_pMessageStringTable[_NN_Not_Connected]);
			return;
		}

		if (target == conn)
		{
			SendClientMessage(conn, g_pMessageStringTable[_NN_Cant_Use_To_Yourself]);
			return;
		}

		if (pUser[target].Mode != USER_PLAY)
		{
			SendClientMessage(conn, g_pMessageStringTable[_NN_Not_Connected]);
			return;
		}

		int myguild = pMob[conn].MOB.Guild;
		int targetguild = pMob[target].MOB.Guild;

		int myleader = pMob[conn].Leader;

		if (myleader <= 0)
			myleader = conn;

		int targetleader = pMob[target].Leader;

		if (targetleader <= 0)
			targetleader = target;

		if (pMob[target].MOB.CurrentScore.Hp <= 0 && admin == 0)
		{
			SendClientMessage(conn, g_pMessageStringTable[_NN_Cant_Use_To_Killed]);
			return;
		}

		if ((myguild == 0 && myleader == 0 || myleader != targetleader || myguild != targetguild && myleader == 0) && admin == 0)
		{
			SendClientMessage(conn, g_pMessageStringTable[_NN_Only_To_Party_Or_Guild]);
			return;
		}

		if (pMob[conn].MOB.Class != 1 && admin == 0)
		{
			SendClientMessage(conn, g_pMessageStringTable[_NN_Didnt_Learn_Summon_Skill]);
			return;
		}

		int learn = pMob[conn].MOB.LearnedSkill;

		if ((learn & 0x40000) == 0 && admin == 0)
		{
			SendClientMessage(conn, g_pMessageStringTable[_NN_Didnt_Learn_Summon_Skill]);
			return;
		}

		int special = pMob[conn].MOB.CurrentScore.Special[3];

		unsigned char map_att = GetAttribute(pMob[conn].TargetX, pMob[conn].TargetY);

		if ((map_att & 4) && admin == 0)
		{
			SendClientMessage(conn, g_pMessageStringTable[_NN_Cant_Use_That_Here]);
			return;
		}

		if (pMob[target].TargetX & 0xFF00 || pMob[target].TargetY & 0xFF00)
		{
			DoSummon(target, pMob[conn].TargetX, pMob[conn].TargetY);
			SendClientMessage(target, strFmt("!Sumonado por [%s]", pMob[conn].MOB.MobName));
			return;
		}
		else
		{
			SendClientMessage(conn, g_pMessageStringTable[_NN_Cant_Use_That_Here]);
			return;
		}
		return;
	}
#pragma endregion
#pragma region /time
	else if (strcmp(m->MobName, "time") == 0)
	{
		char tmptime[256];

		time_t mytime;

		time(&mytime);

		tm* timeinfo = localtime(&mytime);

		strftime(tmptime, 256, "%H:%M:%S | %d-%m-%Y", timeinfo);

		SendClientMessage(conn, tmptime);
		return;
	}
#pragma endregion  
#pragma region _NN_Relocate - /relo
	else if (strcmp(m->MobName, g_pMessageStringTable[_NN_Relocate]) == 0 || strcmp(m->MobName, "relo") == 0)
	{
		int Class = pMob[conn].MOB.Class;
		int admin = 0;

		if (pMob[conn].MOB.CurrentScore.Level >= 999)
			admin = 1;

		if (pMob[conn].MOB.CurrentScore.Hp <= 0)
		{
			SendClientMessage(conn, g_pMessageStringTable[_NN_Cant_Use_Killed]);
			return;
		}

		if (m->String[0] == 0)
			return;

		m->String[NAME_LENGTH - 1] = 0;
		m->String[NAME_LENGTH - 2] = 0;

		int target = GetUserByName(m->String);

		if (target == 0)
		{
			SendClientMessage(conn, g_pMessageStringTable[_NN_Not_Connected]);
			return;
		}

		if (pUser[target].Mode != USER_PLAY)
		{
			SendClientMessage(conn, g_pMessageStringTable[_NN_Not_Connected]);
			return;
		}

		int myguild = pMob[conn].MOB.Guild;
		int targetguild = pMob[target].MOB.Guild;

		int myleader = pMob[conn].Leader;
		if (myleader <= 0)
			myleader = conn;

		int targetleader = pMob[target].Leader;
		if (targetleader <= 0)
			targetleader = target;

		if ((myguild == 0 && myleader == 0 || myleader != targetleader || myguild != targetguild && myleader == 0) && admin == 0)
		{
			SendClientMessage(conn, g_pMessageStringTable[_NN_Only_To_Party_Or_Guild]);
			return;
		}

		int summonmode = 0;
		int medal = pMob[conn].MOB.Equip[12].sIndex;

		if (medal == 522 || medal == 509 || medal >= 529 && medal <= 531 || medal >= 535 && medal <= 537)
			summonmode = 1;

		if (Class == 1)
		{
			int learn = pMob[conn].MOB.LearnedSkill;

			if (learn & 0x40000)
				summonmode = 2;
		}

		if (summonmode == 0 && admin == 0)
		{
			SendClientMessage(conn, g_pMessageStringTable[_NN_Didnt_Learn_Summon_Skill]);
			return;
		}

		unsigned char map_att = GetAttribute(pMob[target].TargetX, pMob[target].TargetY);

		if ((map_att & 4) && admin == 0)
		{
			SendClientMessage(conn, g_pMessageStringTable[_NN_Cant_Use_That_Here]);
			return;
		}

		int dif = pMob[conn].MOB.CurrentScore.Level;
		int myspecial = pMob[conn].MOB.CurrentScore.Special[3];

		if (summonmode == 1)
			dif += 30;

		if (summonmode == 2)
			dif += myspecial + 30;

		if (pMob[target].MOB.CurrentScore.Level > dif && admin == 0)
		{
			SendClientMessage(conn, g_pMessageStringTable[_NN_Too_High_Level]);
			return;
		}

		DoTeleport(conn, pMob[target].TargetX, pMob[target].TargetY);
		/*
		snprintf(temp, sizeof(temp), "etc,relo %s X:%d Y:%d", pMob[target].MOB.MobName, pMob[target].TargetX, pMob[target].TargetY);
		SystemLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, temp);*/

		if (admin == 0)
		{
			SendClientMessage(target, strFmt(g_pMessageStringTable[_SN_S_Relocate_To_You], pMob[conn].MOB.MobName));
		}

		return;
	}
#pragma endregion
#pragma region _NN_Deprivate - /expulsar
	else if (strcmp(m->MobName, "expulsar") == 0)
	{
		if (m->String[0] == 0)
			return;

		m->String[NAME_LENGTH - 1] = 0;
		m->String[NAME_LENGTH - 2] = 0;

		int target = GetUserByName(m->String);

		if (target)
			DoDeprivate(conn, target);
		else
			SendClientMessage(conn, g_pMessageStringTable[_NN_Not_Connected]);

		return;
	}
#pragma endregion
#pragma region /not
	else if (strcmp(m->MobName, "not") == 0)
	{

		if (pUser[conn].Admin == 1)
		{
			MSG_DBNotice sm_dbn;
			memset(&sm_dbn, 0, sizeof(MSG_DBNotice));

			sm_dbn.Size = sizeof(MSG_DBNotice);
			sm_dbn.ID = 0;
			sm_dbn.Type = _MSG_DBNotice;

			strncpy(sm_dbn.String, m->String, MESSAGE_LENGTH - 1);

			DBServerSocket.SendOneMessage((char*)&sm_dbn, sizeof(MSG_DBNotice));
			return;
		}

		else
		{
			SendClientMessage(conn, g_pMessageStringTable[_NN_Not_Connected]);
			return;
		}
	}
#pragma endregion
#pragma region /online via IP MAC
	else if (strcmp(m->MobName, "online") == 0) //saber quantos jogadores tem online dentro do game
	{
		if (pUser[conn].Atraso != 0)
		{
			int isTime = GetTickCount64() - pUser[conn].Atraso; // ATRASO

			if (isTime < 10000)
			{
				SendClientMessage(conn, "Aguarde 10 segundos para uma nova Tentativa.");
				return;
			}

		}
		pUser[conn].Atraso = GetTickCount64();
		short num = 0;
		for (int i = 0; i < MAX_USER; i++)
		{
			if (pUser[i].Mode == USER_PLAY)
			{
				num++;
			}
		}

		if (num >= 100)
			num += 50;

		if (num >= 250)
			num += 50;

		if (num >= 400)
			num += 50;

		SendClientMessage(conn, strFmt("Atualmente temos %d jogador(es) online.", num));
		return;
	}
#pragma endregion
#pragma region
	else if (strcmp(m->MobName, "spk") == 0 || strcmp(m->MobName, "gritar") == 0)
	{
		int i = 0;

		if (pUser[conn].MuteChat == 1)
		{
			SendClientMessage(conn, g_pMessageStringTable[_NN_No_Speak]);
			return;
		}

		for (i = 0; i < pMob[conn].MaxCarry; i++)
		{
			if (pMob[conn].MOB.Carry[i].sIndex != 3330)
				continue;

			int amount = BASE_GetItemAmount(&pMob[conn].MOB.Carry[i]);

			if (amount > 1)
				BASE_SetItemAmount(&pMob[conn].MOB.Carry[i], amount - 1);
			else
				BASE_ClearItem(&pMob[conn].MOB.Carry[i]);

			SendItem(conn, ITEM_PLACE_CARRY, i, &pMob[conn].MOB.Carry[i]);
			break;
		}

		if (i == pMob[conn].MaxCarry)
			return;


		SendSpkMsg(conn, m->String, TNColor::Speak, true);
		return;
	}
#pragma endregion 
#pragma region /ativar
	/*else if (strcmp(m->MobName, "pin") == 0 || strcmp(m->MobName, "PIN") == 0)
	{
		if (m->String[0] == 0)
			return;

		char innerMsg[100] = { 0, }, dir[256];
		int numCash = 0;
		FILE* fp;
		sprintf_s(dir, "../../Common/PinCode/%s.txt", m->String);
		if (!FileExist(dir))
			SendClientMessage(conn, g_pMessageStringTable[_NN_PINCODE_INVALID]);
		else
		{
			fopen_s(&fp, dir, "rt");

			if (fp)
			{
				fscanf_s(fp, "%d", &numCash);
				fclose(fp);
				remove(dir);
				pUser[conn].Donate += numCash;

				char tmg[256];
				SendClientMessage(conn, "Agradecemos a sua contribuição... Digite /saldo");
				SaveUser(conn, 0);
				SendEtc(conn);
				return;
			}
			else
				SendClientMessage(conn, "Um erro ocorreu durante a ativação, favor contatar administração.");
		}
		return;
	}*/
#pragma endregion 
	if (pUser[conn].MuteChat == 1)
	{
		SendClientMessage(conn, g_pMessageStringTable[_NN_No_Speak]);
		return;
	}

#pragma region /r - -- = Cidadao  pm
	if (m->MobName[0] == 0)
	{
#pragma region Chat Guild : -
		if (m->String[0] == '-')
		{
			strncpy(m->MobName, pMob[conn].MOB.MobName, NAME_LENGTH);

			m->String[MESSAGE_LENGTH] = 3;

			int guild = pMob[conn].MOB.Guild;

			if (guild == 0)
			{
				SendClientMessage(conn, g_pMessageStringTable[_NN_Only_Guild_Member_Can]);
				return;
			}

			int guildlevel = pMob[conn].MOB.GuildLevel;

			for (int i = 1; i < MAX_USER; i++)
			{
				if (pUser[i].Mode != USER_PLAY)
					continue;

				if (pMob[i].MOB.Guild != guild && m->String[1] != '-')
					continue;

				if (pMob[i].MOB.Guild != guild && m->String[1] == '-' && (pMob[i].MOB.Guild != g_pGuildAlly[guild] || g_pGuildAlly[guild] == 0))
					continue;

				if (i == conn)
					continue;

				if (pUser[i].Guildchat)
					continue;

				m->ID = conn;
				if (!pUser[i].cSock.AddMessage((char*)m, m->Size))
					CloseUser(conn);
			}

			char guildname[256];
			BASE_GetGuildName(ServerGroup, guild, guildname);
			snprintf(temp, sizeof(temp), "chat_guild, %s : %s guild:%s", m->MobName, m->String, guildname);
			ChatLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, temp);
			return;
		}
#pragma endregion
#pragma region Chat Party : =
		if (m->String[0] == '=')
		{
			strncpy(m->MobName, pMob[conn].MOB.MobName, NAME_LENGTH);

			int myleader = pMob[conn].Leader;

			if (myleader <= 0)
				myleader = conn;

			if (myleader <= 0 || myleader >= MAX_USER)
				return;

			if (pUser[myleader].Mode != USER_PLAY)
				return;

			if (myleader != conn)
				if (!pUser[myleader].cSock.AddMessage((char*)m, sizeof(MSG_MessageWhisper)))
					CloseUser(conn);

			for (int i = 0; i < MAX_PARTY; i++)
			{
				int partyconn = pMob[myleader].PartyList[i];

				if (partyconn <= 0 || partyconn >= MAX_USER)
					continue;

				if (partyconn == conn)
					continue;

				if (pUser[partyconn].Mode != USER_PLAY)
					continue;

				if (pUser[partyconn].PartyChat)
					continue;

				m->ID = conn;
				if (!pUser[partyconn].cSock.AddMessage((char*)m, sizeof(MSG_MessageWhisper)))
					CloseUser(conn);
			}
			snprintf(temp, sizeof(temp), "chat_party, %s : %s", m->MobName, m->String);
			ChatLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, temp);
			return;
		}
#pragma endregion
#pragma region Chat Reino
		if (m->String[0] == '@' && m->String[1] == '@')
		{
			if (pUser[conn].Message != 0)
			{
				int isTime = GetTickCount64() - pUser[conn].Message;

				pUser[conn].Message = GetTickCount64();

				if (isTime < 3000)
				{
					SendClientMessage(conn, "Aguarde 3 segundos.");
					return;
				}
			}
			pUser[conn].Message = GetTickCount64();

			strncpy(m->MobName, pMob[conn].MOB.MobName, NAME_LENGTH);

			SyncKingdomMulticast(conn, pMob[conn].MOB.Clan, (MSG_STANDARD*)m, 0);
			snprintf(temp, sizeof(temp), "chat_kingdom, %s : %s reino:%d", m->MobName, m->String, pMob[conn].MOB.Clan);
			ChatLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, temp);

			return;
		}
#pragma endregion
#pragma region Chat Cidadão
		if (m->String[0] == '@')
		{
			if (pUser[conn].Message != 0)
			{
				int isTime = GetTickCount64() - pUser[conn].Message;

				pUser[conn].Message = GetTickCount64();

				if (isTime < 3000)
				{
					SendClientMessage(conn, "Aguarde 3 segundos.");
					return;
				}
			}
			pUser[conn].Message = GetTickCount64();

			strncpy(m->MobName, pMob[conn].MOB.MobName, NAME_LENGTH);

			SyncMulticast(conn, (MSG_STANDARD*)m, 0);
			snprintf(temp, sizeof(temp), "chat_cidadao, %s : %s", m->MobName, m->String);
			ChatLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, temp);
			return;
		}
#pragma endregion
		return;
	}

#pragma region PM, /r
	if (m->MobName[0] != 0)
	{
		m->MobName[NAME_LENGTH - 1] = 0;
		m->MobName[NAME_LENGTH - 2] = 0;

		int target = 0;

		if (strcmp(m->MobName, g_pMessageStringTable[_NN_Reply]) == 0 || strcmp(m->MobName, "r") == 0)
		{
			if (!pUser[conn].LastChat[0])
			{
				SendClientMessage(conn, g_pMessageStringTable[_NN_No_One_To_Reply]);
				return;
			}
			memmove_s(m->MobName, NAME_LENGTH, pUser[conn].LastChat, NAME_LENGTH);

			m->MobName[NAME_LENGTH - 1] = 0;
			m->MobName[NAME_LENGTH - 2] = 0;
		}

		target = GetUserByName(m->MobName);

		if (target == 0)
		{
			SendClientMessage(conn, g_pMessageStringTable[_NN_Not_Connected]);
			return;
		}

		if (pUser[target].Mode != USER_PLAY)
		{
			SendClientMessage(conn, g_pMessageStringTable[_NN_Not_Connected]);
			return;
		}

		if (pUser[target].Whisper && pMob[conn].MOB.CurrentScore.Level < 1000)
		{
			SendClientMessage(conn, g_pMessageStringTable[_NN_Deny_Whisper]);
			return;
		}
		m->ID = target;

		memmove_s(pUser[conn].LastChat, NAME_LENGTH, m->MobName, NAME_LENGTH);

		if (m->String[0] == 0)
		{
			char temp[1024];
			if (pMob[target].MOB.Guild == 0)
			{
				char tt[256];
				snprintf(tt, sizeof(tt), "Cidadania: %d  Fama: %d", pMob[target].extra.Citizen, pMob[target].extra.Fame);
				snprintf(temp, sizeof(temp), "%s  %s", pMob[target].MOB.MobName, tt);
			}
			else
			{
				char guildname[256];
				char tt[256];
				char guildind[256];
				char guildindex[256];
				int usGuild = pMob[conn].MOB.Guild;
				BASE_GetGuildName(ServerGroup, pMob[target].MOB.Guild, guildname);
				BASE_GetGuildName(ServerGroup, pMob[conn].MOB.Guild, guildind);
				//guildindex = pMob[conn].MOB.GuildLevel;

				if (pMob[conn].MOB.Guild == 0 && pMob[conn].MOB.GuildLevel != 9)
				{
					snprintf(tt, sizeof(tt), "Cidadania: %d  Fama: %d", pMob[target].extra.Citizen, pMob[target].extra.Fame);
					snprintf(temp, sizeof(temp), "%s  %s [ %s ]", pMob[target].MOB.MobName, tt, guildname);

				}
				//GUILDSS
				if (pMob[conn].MOB.Guild != 0 && pMob[conn].MOB.GuildLevel == 9 && pMob[conn].MOB.Clan != pMob[target].MOB.Clan)
				{
					snprintf(tt, sizeof(tt), "[ %s (%d) ] Cidadania: %d  Fama: %d", guildind, GuildInfo[usGuild].Fame, pMob[target].extra.Citizen, pMob[target].extra.Fame, pMob[conn].MOB.Guild);
					snprintf(temp, sizeof(temp), "%s  %s %s ", pMob[target].MOB.MobName, tt, guildname);
				}
				if (pMob[conn].MOB.Clan != pMob[target].MOB.Clan)
				{
					snprintf(tt, sizeof(tt), "Cidadania %d  Fama %d", pMob[target].extra.Citizen, pMob[target].extra.Fame);
					snprintf(temp, sizeof(temp), "%s  %s [ %s ]", pMob[target].MOB.MobName, tt, guildname);
				}
				if (pMob[conn].MOB.Clan == pMob[target].MOB.Clan && pMob[conn].MOB.GuildLevel != 9)
				{
					snprintf(tt, sizeof(tt), "Cidadania %d  Fama %d", pMob[target].extra.Citizen, pMob[target].extra.Fame);
					snprintf(temp, sizeof(temp), "%s  %s [ %s ]", pMob[target].MOB.MobName, tt, guildname);
				}
				if (pMob[conn].MOB.Clan != pMob[target].MOB.Clan && pMob[conn].MOB.GuildLevel != 0)
				{
					snprintf(tt, sizeof(tt), "Cidadania %d  Fama %d", pMob[target].extra.Citizen, pMob[target].extra.Fame);
					snprintf(temp, sizeof(temp), "%s / %s [ %s ]", pMob[target].MOB.MobName, tt, guildname);
				}
				//GUILDSS
				if (pMob[conn].MOB.GuildLevel == 9 && pMob[conn].MOB.Guild == pMob[target].MOB.Guild)
				{
					snprintf(tt, sizeof(tt), "[ %s (%d) ] Cidadania: %d  Fama: %d", guildind, GuildInfo[usGuild].Fame, pMob[target].extra.Citizen, pMob[target].extra.Fame, pMob[conn].MOB.Guild);
					snprintf(temp, sizeof(temp), "%s  %s  ", pMob[target].MOB.MobName, tt);
				}
				if (pMob[conn].MOB.GuildLevel == 9 && pMob[conn].MOB.Guild != pMob[target].MOB.Guild)
				{
					snprintf(tt, sizeof(tt), "Cidadania %d  Fama %d", pMob[target].extra.Citizen, pMob[target].extra.Fame);
					snprintf(temp, sizeof(temp), "%s  %s [ %s ]", pMob[target].MOB.MobName, tt, guildname);
				}
			}
			SendClientMessage(conn, temp);

			if (pMob[target].Snd[0] != 0)
			{
				snprintf(temp, sizeof(temp), "%s %s", g_pMessageStringTable[_NN_SND_MESSAGE], pMob[target].Snd);

				SendClientMessage(conn, temp);
			}
			return;
		}

		if (m->String[0] == '-' || m->String[0] == '=')
			m->String[0] = ' ';

		m->String[MESSAGE_LENGTH] = 0;

		memmove_s(m->MobName, NAME_LENGTH, pMob[conn].MOB.MobName, NAME_LENGTH);
		memmove_s(pUser[target].LastChat, NAME_LENGTH, m->MobName, NAME_LENGTH);

		if (!pUser[target].cSock.AddMessage((char*)m, sizeof(MSG_MessageWhisper)))
			CloseUser(conn);

		snprintf(temp, sizeof(temp), "chat_sms,%s %s : %s", pMob[conn].MOB.MobName, m->MobName, m->String);
		ChatLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, temp);
		return;
	}
#pragma endregion
	snprintf(temp, sizeof(temp), "packet, MSG_MessageWhisper user: %s used command: %s", pMob[conn].MOB.MobName, m->MobName);
	SystemLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, temp);

#pragma endregion
}
