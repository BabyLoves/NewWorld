/*
*   Copyright (C) {2015}  {Victor Klafke, Charles TheHouse}
*
*   This program is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program.  If not, see [http://www.gnu.org/licenses/].
*
*   Contact at: victor.klafke@ecomp.ufsm.br
*/
#include <Windows.h>
#include <stdio.h>
#include <fcntl.h>
#include <time.h>
#include <math.h>
#include <io.h>
#include <errno.h>

#include "..\Basedef.h"
#include "..\CPSock.h"
#include "..\ItemEffect.h"
#include "Language.h"

#include "CItem.h"
#include "Server.h"
#include "ProcessClientMessage.h"
#include "GetFunc.h"
#include "SendFunc.h"
#include "Functions.h"

void  ProcessClientMessage(int conn, char *pMsg, BOOL isServer)
{
	MSG_STANDARD *std = (MSG_STANDARD *)pMsg;

	/*if (std->ID < MAX_USER)
		printf("RECV-> Code: %X - Size: %d - Index: %d \n", std->Type, std->Size, std->ID);*/

	//console monitor de pacote
	//printf("Pacote: %X - Tamanho: %d - Index: %d\n", std->Type, std->Size, std->ID);  //pacotes print

	if ((std->ID < 0) || (std->ID >= MAX_USER)) 
	{	
		MSG_STANDARD *m = (MSG_STANDARD *)pMsg;

		sprintf_s(temp, "err,packet Type:%d ID:%d Size:%d KeyWord:%d", m->Type, m->ID, m->Size, m->KeyWord);

		SystemLog("-system", "-", 0, temp);

		return;
	}

	if (ServerDown >= 120)
		return;

	//if (std->Type == 0x20D && sizeof(MSG_AccountLogin)) //proteção pacote
	//	return;

	if (std->Type == 0x20D)
	{
		if (pUser[conn].Atraso != 0)
		{
			int isTime = GetTickCount64() - pUser[conn].Atraso; // ATRASO PACOTE DE LOGIN

			if (isTime < 5000)
			{
				SendClientMessage(conn, "Aguarde 5 segundos para uma nova Tentativa.");
				return;
			}

		}
		pUser[conn].Atraso = GetTickCount64();
	}

	if (std->Type == 0x213 && std->Size > 36) //proteção pacote
		return;

	if (std->Type == 0x213)
	{
		if (pUser[conn].Atraso != 0)
		{
			int isTime = GetTickCount64() - pUser[conn].Atraso; // ATRASO PACOTE DE ENTRE WORLD

			if (isTime < 500)
			{
				SendClientMessage(conn, "Aguarde 1 segundo para uma nova Tentativa.");
				return;
			}

		}
		pUser[conn].Atraso = GetTickCount64();
	}

	if (std->Type == 0x3A0 && std->Size > 12) //proteção pacote
		return;

	if (std->Type == 0x3A0)
	{
		if (pUser[conn].Atraso != 0)
		{
			int isTime = GetTickCount64() - pUser[conn].Atraso; // ATRASO PACOTE DE ENTRE SELLCHAR

			if (isTime < 1000)
			{
				//SendClientMessage(conn, "Aguarde 1 segundos para uma nova Tentativa.");
				return;
			}

		}
		pUser[conn].Atraso = GetTickCount64();
	}

	if (std->Type == 0xFDE && std->Size > 32) //proteção pacote
		return;

	if (std->Type == 0xFDE)
	{
		if (pUser[conn].Atraso != 0)
		{
			int isTime = GetTickCount64() - pUser[conn].Atraso; // ATRASO PACOTE DE ENTRE SENHA2

			if (isTime < 500)
			{
				SendClientMessage(conn, "Aguarde 1 segundo para uma nova Tentativa.");
				return;
			}

		}
		pUser[conn].Atraso = GetTickCount64();
	}

	if (std->Type == 0x3AE && std->Size > 16) //proteção pacote
		return;

	if (std->Type == 0x3AE)
	{
		if (pUser[conn].Atraso != 0)
		{
			int isTime = GetTickCount64() - pUser[conn].Atraso; // ATRASO PACOTE DE ENTRE PERSONAGEM

			if (isTime < 1000)
			{
				SendClientMessage(conn, "Aguarde 1 segundo para uma nova Tentativa.");
				return;
			}

		}
		pUser[conn].Atraso = GetTickCount64();
	}

	//pacotes que a gente não sabe

	if (std->Type == 0x2E4 && std->Size > 20) {
		return;
	}

	if (std->Type == 0x2E4)
	{
		if (pUser[conn].Atraso != 0)
		{
			int isTime = GetTickCount64() - pUser[conn].Atraso; // ATRASO PACOTE DE APAGAR OS ITENS

			if (isTime < 500)
			{
				SendClientMessage(conn, "Apague os Itens devagar!.");
				return;
			}

		}
		pUser[conn].Atraso = GetTickCount64();
	}

	if (std->Type == 0x397 && std->Size > 196) {
		return;
	}

	if (std->Type == 0x397)
	{
		if (pUser[conn].Atraso != 0)
		{
			int isTime = GetTickCount64() - pUser[conn].Atraso; // ATRASO PACOTE DE ABRIR LOJINHA

			if (isTime < 5000)
			{
				SendClientMessage(conn, "Aguarde 5 Segundos para Abrir a Lojinha Novamente");
				return;
			}

		}
		pUser[conn].Atraso = GetTickCount64();
	}


	if (ServerDown >= 120)
		return;

	if (conn > 0 && conn < MAX_USER)
		pUser[conn].LastReceiveTime = SecCounter;

	if (std->Type == _MSG_Ping)
		return;

	// Checa se o pacote foi enviado por algum jogador e possui o timestamp de controle interno.
	if (isServer == FALSE && std->ClientTick == SKIPCHECKTICK)
		return;

	switch(std->Type)
	{
	case _MSG_AccountLogin:
		Exec_MSG_AccountLogin(conn, pMsg);
		break;

	case _MSG_CharacterLogin:
		Exec_MSG_CharacterLogin(conn, pMsg);
		break;

	case _MSG_CharacterLogout:
		Exec_MSG_CharacterLogout(conn, pMsg);
		break;

	case _MSG_DeleteCharacter:
		Exec_MSG_DeleteCharacter(conn, pMsg);
		break;

	case _MSG_CreateCharacter:
		Exec_MSG_CreateCharacter(conn, pMsg);
		break;

	case _MSG_AccountSecure:
		Exec_MSG_AccountSecure(conn, pMsg);
		break;

	case _MSG_MessageChat:
		Exec_MSG_MessageChat(conn, pMsg);
		break;

	case _MSG_Action:
	case _MSG_Action2:
	case _MSG_Action3:
		Exec_MSG_Action(conn, pMsg);
		break;

	case _MSG_Motion:
		//Exec_MSG_Motion(conn, pMsg);
		break;			

	case _MSG_UpdateScore:
	{
		//Log("cra client send update score", pUser[conn].AccountName, pUser[conn].IP);
		//AddCrackError(conn, 2, 91);
	} break;

	case _MSG_NoViewMob:
		Exec_MSG_NoViewMob(conn, pMsg);
		break;

	case _MSG_Restart:
		Exec_MSG_Restart(conn, pMsg);
		break;

	case _MSG_Deprivate:
		Exec_MSG_Deprivate(conn, pMsg);
		break;

	case _MSG_Challange:
		Exec_MSG_Challange(conn, pMsg);
		break;

	case _MSG_ChallangeConfirm:
		Exec_MSG_ChallangeConfirm(conn, pMsg);
		break;

	case _MSG_ReqTeleport:
		Exec_MSG_ReqTeleport(conn, pMsg);
		break;

	case _MSG_REQShopList:
		Exec_MSG_REQShopList(conn, pMsg);
		Exec_MSG_OpenDonate(conn, pMsg);
		break;

	case _MSG_Deposit:
		Exec_MSG_Deposit(conn, pMsg);
		break;

	case _MSG_Withdraw:
		Exec_MSG_Withdraw(conn, pMsg);
		break;

	case _MSG_RemoveParty:
		Exec_MSG_RemoveParty(conn, pMsg);
		break;

	case _MSG_SendReqParty:
		Exec_MSG_SendReqParty(conn, pMsg);
		break;

	case _MSG_AcceptParty:
		Exec_MSG_AcceptParty(conn, pMsg);
		break;

	case _MSG_TradingItem:
		Exec_MSG_TradingItem(conn, pMsg);
		break;

	case _MSG_MessageWhisper:
	    Exec_MSG_MessageWhisper(conn, pMsg);
		break;

	case _MSG_ChangeCity:
		Exec_MSG_ChangeCity(conn, pMsg);
		break;

	case _MSG_PKMode:
		Exec_MSG_PKMode(conn, pMsg);
		break;

	case _MSG_ReqTradeList:
		Exec_MSG_ReqTradeList(conn, pMsg);
		break;

	case _MSG_UpdateItem:
		Exec_MSG_UpdateItem(conn, pMsg);
		break;

	case _MSG_Quest:
		Exec_MSG_Quest(conn, pMsg);
		break;

	case _MSG_SetShortSkill:
		Exec_MSG_SetShortSkill(conn, pMsg);
		break;

	case _MSG_Attack:
	case _MSG_AttackOne:
	case _MSG_AttackTwo:
		Exec_MSG_Attack(conn, pMsg);
		break;

	case _MSG_DropItem:
		Exec_MSG_DropItem(conn, pMsg);
		break;

	case _MSG_GetItem:
		Exec_MSG_GetItem(conn, pMsg);
		break;

	case _MSG_QuitTrade: 
		Exec_MSG_QuitTrade(conn, pMsg);
		break;

	case _MSG_UseItem:
		Exec_MSG_UseItem(conn, pMsg);
		break;

	case _MSG_ApplyBonus:
		Exec_MSG_ApplyBonus(conn, pMsg);
		break;

	case _MSG_SendAutoTrade:
		Exec_MSG_SendAutoTrade(conn, pMsg);
		break;

	case _MSG_ReqBuy:
		Exec_MSG_ReqBuy(conn, pMsg);
		break;

	case _MSG_Buy:
		Exec_MSG_Buy(conn, pMsg);
		break;

	case _MSG_Sell:
		Exec_MSG_Sell(conn, pMsg);
		break;

	case _MSG_Rebuy:
		Exec_MSG_Rebuy(conn, pMsg);
		break;

	case _MSG_Trade:
		Exec_MSG_Trade(conn, pMsg);
		break;

	case _MSG_CombineItem:
		Exec_MSG_CombineItem(conn, pMsg);
		break;

	case _MSG_ReqRanking:
		Exec_MSG_ReqRanking(conn, pMsg);
		break;

	case _MSG_CombineItemEhre:
		Exec_MSG_CombineItemEhre(conn, pMsg);
		break;

	case _MSG_CombineItemTiny:
		Exec_MSG_CombineItemTiny(conn, pMsg);
		break;

	case _MSG_CombineDedekinto:
	case _MSG_CombineDedekinto2:
		Exec_MSG_CombineDedekinto(conn, pMsg);
		break;

	case _MSG_CombineItemShany:
		Exec_MSG_CombineItemShany(conn, pMsg);
		break;

	case _MSG_CombineItemAilyn:
		Exec_MSG_CombineItemAilyn(conn, pMsg);
		break;

	case _MSG_CombineItemAgatha:
		Exec_MSG_CombineItemAgatha(conn, pMsg);
		break;

	case _MSG_NovoCompositor:
		Exec_MSG_EventoMissions(conn, pMsg);
		break;

	case _MSG_CombineItemOdin:
	case _MSG_CombineItemOdin2:
		Exec_MSG_CombineItemOdin(conn, pMsg);
		break;

	/*case _MSG_MestreGrifo:
		Exec_MSG_MestreGrifo(conn, pMsg);
		break;*/

	case _MSG_DeleteItem:
		Exec_MSG_DeleteItem(conn, pMsg);
		break;

	case _MSG_InviteGuild:
		Exec_MSG_InviteGuild(conn, pMsg);
		break;

	case  _MSG_SplitItem:
		Exec_MSG_SplitItem(conn, pMsg);
		break;

	case _MSG_CombineItemLindy:
		Exec_MSG_CombineItemLindy(conn, pMsg);
		break;

	case _MSG_CombineItemAlquimia:
		Exec_MSG_CombineItemAlquimia(conn, pMsg);
		break;

	case _MSG_CombineItemExtracao:
		Exec_MSG_CombineItemExtracao(conn, pMsg);
		break;

	case _MSG_GuildAlly:
		Exec_MSG_GuildAlly(conn, pMsg);
		break;

	case _MSG_War:
		Exec_MSG_War(conn, pMsg);
		break;

	case _MSG_CapsuleInfo:
		Exec_MSG_CapsuleInfo(conn, pMsg);
		break;

	case _MSG_PutoutSeal:
		Exec_MSG_PutoutSeal(conn, pMsg);
		break;

	case _MSG_AnswerQuiz:
		Exec_MSG_Quiz(conn, pMsg);
		break;

	case 0x3D1:
		Exec_MSG_onPaymentGold(conn, pMsg);
		break;

	/*case _MSG_SendFiltro:
		FiltroDrop(conn, pMsg);
		break;*/

	case _MSG_ReqDropList:
		ReqDropList(conn, pMsg);
		break;

	case _MSG_SendTraje:
		attMountTraje(conn, pMsg);
		break;

	case _MSG_RequestTeleport:
		ReqTeleport(conn, pMsg);
		break;
	case _MSG_ReqShopDonate:
		ReqDonateShop(conn, pMsg);
		break;
	case _MSG_ReqdListNames:
		ReqdListNames(conn, pMsg);
		break;
	case _MSG_SendJephi:
		Jephi(conn, pMsg);
		break;
	case _MSG_SendItemLevel:
		ItemLevel(conn, pMsg);
		break;
	case _MSG_SendPix:
		TradeDonate(conn, pMsg);
		break;
	case _MSG_ReqAlias:
		RequestAlias(conn, pMsg);
		break;
	}	
	return;
}