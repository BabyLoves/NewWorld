
#include "ProcessClientMessage.h"

void Exec_MSG_MessageChat(int conn, char* pMsg)
{
	MSG_MessageChat* m = (MSG_MessageChat*)pMsg;

	m->String[MESSAGE_LENGTH - 1] = 0;
	m->String[MESSAGE_LENGTH - 2] = 0;

	m->ID = conn;

	if (pUser[conn].Mode != USER_PLAY)
		return;

	int Size = m->Size;

	if (Size > sizeof(MSG_MessageChat)) //CONTROLE DE SIZE
	{
		CloseUser(conn);
		return;
	}

	char szCmd[256];
	char szString[256];

	sscanf(m->String, "%s %s", szCmd, szString);



	if (strcmp(szCmd, "guildon") == 0)
	{
		if (pMob[conn].GuildDisable == 1)
		{
			pMob[conn].GuildDisable = 0;

			SendScore(conn);

			SendClientSignalParm(conn, ESCENE_FIELD, _MSG_GuildDisable, 0);
		}
		return;
	}

	else if (strcmp(szCmd, "guildoff") == 0)
	{
		if (pMob[conn].GuildDisable == 0)
		{
			pMob[conn].GuildDisable = 1;

			SendScore(conn);

			SendClientSignalParm(conn, ESCENE_FIELD, _MSG_GuildDisable, 1);
		}
		return;
	}
	else if (strcmp(szCmd, "guildtax") == 0)
	{
		if (pMob[conn].MOB.GuildLevel != 9)
			return;

		//int Guild = pMob[conn].MOB.Guild;

		//for (int i = 0; i < MAX_GUILDZONE; i++)
		//{
		//	if (g_pGuildZone[i].ChargeGuild != Guild)
		//		continue;

		//	int tax = atoi(szString);

		//	if (tax < 0 || tax > 30 || szString[0] != 48 && !tax)
		//	{
		//		SendClientMessage(conn, g_pMessageStringTable[_NN_Guild_Tax_0_to_30]);
		//		break;
		//	}

		//	if (TaxChanged[i] == 1)
		//	{
		//		SendClientMessage(conn, g_pMessageStringTable[_NN_Only_Once_Per_Day]);
		//		break;
		//	}

		//	g_pGuildZone[i].CityTax = tax;
		//	TaxChanged[i] = 1;
		//	SendClientMessage(conn, strFmt(g_pMessageStringTable[169], tax, 0));

		//	CReadFiles::WriteGuild();

		//	/*snprintf(temp, sizeof(temp), "sys,%s", m->String);
		//	SystemLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, temp);*/

		//	break;
		//}
		SendClientMessage(conn, "Imposto nesse servidor é fixado em 10%");
		return;
	}

	/*else if (strcmp(szCmd, "guild") == 0)
	{
		SendGuildList(conn);

		return;
	}*/

	/*else if (strcmp(szCmd, "joaocrashador") == 0)
	{
		ServerDown = 1;
	}*/

	// Anti Hacker ban whook automatico se usar palavras de comando hacker de whook
	/*else if (strcmp(szCmd, "#allon") == 0)
	{
		SendBanAccount(conn, Banned::Permanente); return;
	}
	else if (strcmp(szCmd, "#move") == 0)
	{
		SendBanAccount(conn, Banned::Permanente); return;
	}
	else if (strcmp(szCmd, "#moved") == 0)
	{
		SendBanAccount(conn, Banned::Permanente); return;
	}
	else if (strcmp(szCmd, "#fastkillon") == 0)
	{
		SendBanAccount(conn, Banned::Permanente); return;
	}
	else if (strcmp(szCmd, "#rangeon") == 0)
	{
		SendBanAccount(conn, Banned::Permanente); return;
	}
	else if (strcmp(szCmd, "#wallon") == 0)
	{
		SendBanAccount(conn, Banned::Permanente); return;
	}
	else if (strcmp(szCmd, "#speedatkon") == 0)
	{
		SendBanAccount(conn, Banned::Permanente); return;
	}
	else if (strcmp(szCmd, "#skill") == 0)
	{
		SendBanAccount(conn, Banned::Permanente); return;
	}
	else if (strcmp(szCmd, "#opencargo") == 0)
	{
		SendBanAccount(conn, Banned::Permanente); return;
	}
	else if (strcmp(szCmd, "#bau") == 0)
	{
		SendBanAccount(conn, Banned::Permanente); return;
	}
	else if (strcmp(szCmd, "#indexon") == 0)
	{
		SendBanAccount(conn, Banned::Permanente); return;
	}
	else if (strcmp(szCmd, "#lanon") == 0)
	{
		SendBanAccount(conn, Banned::Permanente); return;
	}
	else if (strcmp(szCmd, "#searchon") == 0)
	{
		SendBanAccount(conn, Banned::Permanente); return;
	}
	else if (strcmp(szCmd, "#separar") == 0)
	{
		SendBanAccount(conn, Banned::Permanente); return;
	}
	else if (strcmp(szCmd, "#Modificado") == 0)
	{
		SendBanAccount(conn, Banned::Permanente); return;
	}
	else if (strcmp(szCmd, "#macroeventon") == 0)
	{
		SendBanAccount(conn, Banned::Permanente); return;
	}
	else if (strcmp(szCmd, "#Comprado") == 0)
	{
		SendBanAccount(conn, Banned::Permanente); return;
	}
	else if (strcmp(szCmd, "#mover_gelo") == 0)
	{
		SendBanAccount(conn, Banned::Permanente); return;
	}
	else if (strcmp(szCmd, "#mover_kefra") == 0)
	{
		SendBanAccount(conn, Banned::Permanente); return;
	}
	else if (strcmp(szCmd, "#mover_bau") == 0)
	{
		SendBanAccount(conn, Banned::Permanente); return;
	}
	else if (strcmp(szCmd, "#mover_flash") == 0)
	{
		SendBanAccount(conn, Banned::Permanente); return;
	}
	else if (strcmp(szCmd, "#juntar") == 0)
	{
		SendBanAccount(conn, Banned::Permanente); return;
	}
	else if (strcmp(szCmd, "#vender") == 0)
	{
		SendBanAccount(conn, Banned::Permanente); return;
	}
	else if (strcmp(szCmd, "#comprar") == 0)
	{
		SendBanAccount(conn, Banned::Permanente); return;
	}
	else if (strcmp(szCmd, "#comprar_kefra") == 0)
	{
		SendBanAccount(conn, Banned::Permanente); return;
	}
	else if (strcmp(szCmd, "#speedon") == 0)
	{
		SendBanAccount(conn, Banned::Permanente); return;
	}
	else if (strcmp(szCmd, "#smo") == 0)
	{
		SendBanAccount(conn, Banned::Permanente); return;
	}
	else if (strcmp(szCmd, "#speedmoveon") == 0)
	{
		SendBanAccount(conn, Banned::Permanente); return;
	}
	else if (strcmp(szCmd, "#quest") == 0)
	{
		SendBanAccount(conn, Banned::Permanente); return;
	}
	else if (strcmp(szCmd, "#invon") == 0)
	{
		SendBanAccount(conn, Banned::Permanente); return;
	}
	else if (strcmp(szCmd, "#soulon") == 0)
	{
		SendBanAccount(conn, Banned::Permanente); return;
	}
	else if (strcmp(szCmd, "#list_npc") == 0)
	{
		SendBanAccount(conn, Banned::Permanente); return;
	}
	else if (strcmp(szCmd, "#atkinvon") == 0)
	{
		SendBanAccount(conn, Banned::Permanente); return;
	}
	else if (strcmp(szCmd, "#buff") == 0)
	{
		SendBanAccount(conn, Banned::Permanente); return;
	}
	else if (strcmp(szCmd, "#atkon") == 0)
	{
		SendBanAccount(conn, Banned::Permanente); return;
	}
	else if (strcmp(szCmd, "#coord") == 0)
	{
		SendBanAccount(conn, Banned::Permanente); return;
	}
	else if (strcmp(szCmd, "#face") == 0)
	{
		SendBanAccount(conn, Banned::Permanente); return;
	}
	else if (strcmp(szCmd, "#skill") == 0)
	{
		SendBanAccount(conn, Banned::Permanente); return;
	}
	else if (strcmp(szCmd, "#onehiton") == 0)
	{
		SendBanAccount(conn, Banned::Permanente); return;
	}
	else if (strcmp(szCmd, "#aon") == 0)
	{
		SendBanAccount(conn, Banned::Permanente); return;
	}
	else if (strcmp(szCmd, "#atk") == 0)
	{
		SendBanAccount(conn, Banned::Permanente); return;
	}
	else if (strcmp(szCmd, "#packeton") == 0)
	{
		SendBanAccount(conn, Banned::Permanente); return;
	}
	else if (strcmp(szCmd, "#indexon") == 0)
	{
		SendBanAccount(conn, Banned::Permanente); return;
	}
	else if (strcmp(szCmd, "#fakeitem") == 0)
	{
		SendBanAccount(conn, Banned::Permanente); return;
	}
	else if (strcmp(szCmd, "#apagar") == 0)
	{
		SendBanAccount(conn, Banned::Permanente); return;
	}*/

	else if (strcmp(szCmd, "whisper") == 0)
	{
		pUser[conn].Whisper = pUser[conn].Whisper == 0;

		if (pUser[conn].Whisper)
			SendClientMessage(conn, "Whisper : Off");
		else
			SendClientMessage(conn, "Whisper : On");

		return;
	}

	else if (strcmp(szCmd, "partychat") == 0)
	{
		pUser[conn].PartyChat = pUser[conn].PartyChat == 0;

		if (pUser[conn].PartyChat)
			SendClientMessage(conn, "Party Chatting : Off");
		else
			SendClientMessage(conn, "Party Chatting : On");

		return;
	}

	else if (strcmp(szCmd, "kingdomchat") == 0)
	{
		pUser[conn].KingChat = pUser[conn].KingChat == 0;

		if (pUser[conn].KingChat)
			SendClientMessage(conn, "Kingdom Chatting : Off");
		else
			SendClientMessage(conn, "Kingdom Chatting : On");

		return;
	}

	else if (strcmp(szCmd, "guildchat") == 0)
	{
		pUser[conn].Guildchat = pUser[conn].Guildchat == 0;

		if (pUser[conn].Guildchat)
			SendClientMessage(conn, "Guild Chatting : Off");
		else
			SendClientMessage(conn, "Guild Chatting : On");

		return;
	}

	else if (strcmp(szCmd, "chatting") == 0)
	{
		pUser[conn].Chatting = pUser[conn].Chatting == 0;

		if (pUser[conn].Chatting)
			SendClientMessage(conn, "Chatting : Off");
		else
			SendClientMessage(conn, "Chatting : On");

		return;
	}

	if (BrState && conn < MAX_USER && BRItem > 0)
	{
		if (pMob[conn].TargetX >= 2604 && pMob[conn].TargetY >= 1708 && pMob[conn].TargetX <= 2648 && pMob[conn].TargetY <= 1744 || pMob[conn].TargetX >= 896 && pMob[conn].TargetY >= 1405 && pMob[conn].TargetX <= 1150 && pMob[conn].TargetY <= 1538)
			strncpy(m->String, "??????", 6);

	}

	m->String[MESSAGE_LENGTH - 1] = 0;
	m->String[MESSAGE_LENGTH - 2] = 0;

	if (pUser[conn].MuteChat == 1)
	{
		SendClientMessage(conn, g_pMessageStringTable[_NN_No_Speak]);
		return;
	}

	if (pUser[conn].Mode == USER_PLAY)
	{
		int leader = pMob[conn].Leader;
		if (!leader)
			leader = conn;

		GridMulticast(pMob[conn].TargetX, pMob[conn].TargetY, (MSG_STANDARD*)pMsg, conn);
	}
	else
	{
		SendClientMessage(conn, "DEBUG:Client send chatting message with wrong status");
		//Log("err,send chatting message with wrong status", pUser[conn].AccountName, pUser[conn].IP);
	}
	/*
	snprintf(temp, sizeof(temp), "chat, %s : %s", pMob[conn].MOB.MobName, m->String);
	ChatLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, temp);*/
}