
#include "ProcessClientMessage.h"
#include "Functions.h"

void Exec_MSG_TradingItem(int conn, char *pMsg)
{
	MSG_TradingItem* m = (MSG_TradingItem*)pMsg;

	int Size = m->Size;

	if (m->WarpID < 0 || m->WarpID >= MAX_MOB)
		return;

	if (m->SrcSlot < 0 || m->SrcSlot >= 120)
		return;

	if (m->SrcPlace < 0)
		return;

	if (m->DestSlot < 0 || m->DestSlot >= 120)
		return;

	if (m->DestPlace < 0)
		return;

	// correção de dup
	if (m->SrcPlace == m->DestPlace && m->SrcSlot == m->DestSlot) {
		CloseUser(conn);
		SystemLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, "Dup bug");
		return;
	}

	if (Size > sizeof(MSG_TradingItem)) //CONTROLE DE SIZE
	{
		SendClientMessage(conn, "Impossível executar ação52, tente mais tarde. ");
		return;
	}

	if (pMob[conn].MOB.CurrentScore.Hp == 0 || pUser[conn].Mode != USER_PLAY)
	{
		SendHpMode(conn);
		AddCrackError(conn, 1, 19);
		return;
	}

	if (pUser[conn].Trade.OpponentID)
	{
		RemoveTrade(pUser[conn].Trade.OpponentID);
		RemoveTrade(conn);
		return;
	}

	if (pUser[conn].TradeMode)
	{
		SendClientMessage(conn, g_pMessageStringTable[_NN_CantWhenAutoTrade]);
		return;
	}

	if(m->SrcPlace == ITEM_PLACE_CARGO && m->DestPlace == ITEM_PLACE_EQUIP)
	{
		SendClientMessage(conn, "Passe o item para o inventário antes de equipá-lo.");
		return;
	}

	if (pUser[conn].MoveItemTime != 0)
	{
		int isTime = GetTickCount64() - pUser[conn].MoveItemTime;

		if (isTime < 800)

		{
			//Log("O jogador [%s] esta tentando dupar IP: %d", pUser[conn].AccountName, pUser[conn].IP);
			return;
		}
	}
	
	pUser[conn].MoveItemTime = GetTickCount64();

	STRUCT_ITEM *item = GetItemPointer(&pMob[conn].MOB, pUser[conn].Cargo, m->SrcPlace, m->SrcSlot);

	if ((m->DestPlace == ITEM_PLACE_CARGO || m->SrcPlace == ITEM_PLACE_CARGO) && (pMob[conn].MOB.Class != 3 && pMob[conn].MOB.Class != 2 && pMob[conn].MOB.Class != 1 && pMob[conn].MOB.Class != 0 || !(pMob[conn].MOB.LearnedSkill & 0x2000)))
	{
		int WarpID = m->WarpID;

		if (WarpID <= MAX_USER && WarpID >= MAX_MOB)
		{
			//SendClientMessage(conn, "Erro 1!");
			SendClientSignal(conn, ESCENE_FIELD, 412);
			return;
		}

		//if (pMob[WarpID].Mode != MOB_PEACE || pMob[WarpID].MOB.Merchant != 2)
		//{
		//	//SendClientMessage(conn, "Erro 2!");
		//	SendClientSignal(conn, ESCENE_FIELD, 412);
		//	return;
		//}

		int PosX = pMob[conn].TargetX;
		int PosY = pMob[conn].TargetY;
		int tx = pMob[WarpID].TargetX;
		int ty = pMob[WarpID].TargetY;

		//if (PosX < tx - VIEWGRIDX || PosX > tx + VIEWGRIDX || PosY < ty - VIEWGRIDY || PosY > ty + VIEWGRIDY)
		//{
		//	//SendClientMessage(conn, "Erro 3!");
		//	SendClientSignal(conn, ESCENE_FIELD, 412);
		//	return;
		//}
	}
	STRUCT_ITEM *Mount = &pMob[conn].MOB.Equip[14];

	int DestPlace = 0;
	int SrcPlace = 0;

	STRUCT_ITEM *DestItem = GetItemPointer(&pMob[conn].MOB, pUser[conn].Cargo, m->DestPlace, m->DestSlot);
	STRUCT_ITEM *SrcItem = GetItemPointer(&pMob[conn].MOB, pUser[conn].Cargo, m->SrcPlace, m->SrcSlot);

	STRUCT_ITEM *dItem = GetItemPointer(&pMob[conn].MOB, pUser[conn].Cargo, m->DestPlace, m->DestSlot);
	STRUCT_ITEM *sItem = GetItemPointer(&pMob[conn].MOB, pUser[conn].Cargo, m->SrcPlace, m->SrcSlot);


	if (m->DestPlace)
	{
		if (m->DestPlace == ITEM_PLACE_CARRY)
		{
			if (m->DestSlot >= MAX_CARRY - 4)
			{
				//Log("err,trading fails.SwapItem-Carry", pUser[conn].AccountName, pUser[conn].IP);
				return;
			}
		}
		else
		{
			if (m->DestPlace != ITEM_PLACE_CARGO)
			{
				//Log("err,trading fails.SwapItem source type", pUser[conn].AccountName, pUser[conn].IP);
				return;
			}
			if (m->DestSlot > MAX_CARGO)
			{
				//Log("err,trading fails.SwapItem-Cargo", pUser[conn].AccountName, pUser[conn].IP);
				return;
			}
			int PosX = pMob[conn].TargetX;
			int PosY = pMob[conn].TargetY;

			bool NearCargo = false;
			if ((PosX > 1039 && PosX < 1057 && PosY > 1733 && PosY < 1749) || //deserto
				(PosX > 2135 && PosX < 2154 && PosY > 2072 && PosY < 2093) || //armia aki
				(PosX > 2094 && PosX < 2113 && PosY > 2105 && PosY < 2126) || //armia
				(PosX > 2467 && PosX < 2486 && PosY > 1679 && PosY < 1698) || //arzan
				(PosX > 2583 && PosX < 2602 && PosY > 1719 && PosY < 1734) || //arzan coliseu
				(PosX > 2457 && PosX < 2472 && PosY > 1984 && PosY < 1999) || //erion
				(PosX > 3650 && PosX < 3670 && PosY > 3144 && PosY < 3127) || //gelo
				(PosX > 3225 && PosX < 3251 && PosY > 1679 && PosY < 1692)) { //kefra
				NearCargo = true;
			}
			if (NearCargo == false) {
				SendClientMessage(conn, "Você está longe do Bau");
				return;
			}
		}
	}
	else
	{
		if (m->DestSlot < 0 || m->DestSlot >= MAX_EQUIP - 1)
		{
			//Log("err,trading fails.SwapItem-Equip", pUser[conn].AccountName, pUser[conn].IP);
			return;
		}
		DestPlace = 1;
		SrcPlace = 1;
	}
	if (m->SrcPlace)
	{
		if (m->SrcPlace == ITEM_PLACE_CARRY)
		{
			if (m->SrcSlot >= MAX_CARRY - 4)
			{
				//Log("DEBUG:Trading Fails.Swap-Carr", pUser[conn].AccountName, pUser[conn].IP);
				return;
			}
		}
		else
		{
			if (m->SrcPlace != ITEM_PLACE_CARGO)
			{
				//Log("DEBUG:Trading Fails.SwapItem dest type", pUser[conn].AccountName, pUser[conn].IP);
				return;
			}
			if (m->SrcSlot > MAX_CARGO)
			{
				//Log("DEBUG:Trading Fails.Swap-Cargo", pUser[conn].AccountName, pUser[conn].IP);
				return;
			}
			int PosX = pMob[conn].TargetX;
			int PosY = pMob[conn].TargetY;

			bool NearCargo = false;
			if ((PosX > 1039 && PosX < 1057 && PosY > 1733 && PosY < 1749) || //deserto
				(PosX > 2135 && PosX < 2154 && PosY > 2072 && PosY < 2093) || //armia aki
				(PosX > 2094 && PosX < 2113 && PosY > 2105 && PosY < 2126) || //armia
				(PosX > 2467 && PosX < 2486 && PosY > 1679 && PosY < 1698) || //arzan
				(PosX > 2583 && PosX < 2602 && PosY > 1719 && PosY < 1734) || //arzan coliseu
				(PosX > 2457 && PosX < 2472 && PosY > 1984 && PosY < 1999) || //erion
				(PosX > 3650 && PosX < 3670 && PosY > 3144 && PosY < 3127) || //gelo
				(PosX > 3225 && PosX < 3251 && PosY > 1679 && PosY < 1692)) { //kefra
				NearCargo = true;
			}
			if (NearCargo == false) {
				SendClientMessage(conn, "Você está longe do Bau");
				return;
			}
		}
	}
	else
	{
		if (m->SrcSlot <= 0 || m->SrcSlot >= MAX_EQUIP - 1)
		{
			//Log("DEBUG:Trading Fails.Swap-Equip", pUser[conn].AccountName, pUser[conn].IP);
			return;
		}
		DestPlace = 1;
		SrcPlace = 1;
	}

	if (m->DestPlace == ITEM_PLACE_CARRY && m->DestSlot >= pMob[conn].MaxCarry)
		return;

	if (DestItem == NULL || SrcItem == NULL)
	{
		//Log("DEBUG:Trading Fails.Swap-Equip", pUser[conn].AccountName, pUser[conn].IP);
		return;
	}
	/*
	if (m->SrcPlace == m->DestPlace == ITEM_PLACE_CARRY)
	{
		if (pMob[conn].MOB.Carry[m->SrcSlot].sIndex == 4011 && pMob[conn].MOB.Carry[m->DestSlot].sIndex == 4011)
		{
			int numAdd = BASE_GetItemAmount(&pMob[conn].MOB.Carry[m->SrcSlot]);
			pMob[conn].MOB.Carry[m->DestSlot].stEffect[0].cEffect = 61;
			if (pMob[conn].MOB.Carry[m->DestSlot].stEffect[0].cValue + numAdd > 50)
			{
				SendClientMessage(conn, "Limite de agrupamento atingido.");
				return;
			}
			else
			{
				pMob[conn].MOB.Carry[m->DestSlot].stEffect[0].cValue += numAdd;
				memset(&pMob[conn].MOB.Carry[m->SrcSlot], 0x0, sizeof(STRUCT_ITEM));
				SendCarry(conn);
				SendEtc(conn);
				return;
			}
		}
	}
	*/
	
	if (DestItem->sIndex != 747 && SrcItem->sIndex != 747 && SrcItem->sIndex != 3505 && SrcItem->sIndex != 3980 || m->DestPlace != ITEM_PLACE_CARGO && m->SrcPlace != ITEM_PLACE_CARGO)
	{
		if (DestItem->sIndex != 3505 && SrcItem->sIndex != 3505 && DestItem->sIndex != 4144 && SrcItem->sIndex != 4144 && DestItem->sIndex != 3980 || m->DestPlace != ITEM_PLACE_CARRY && m->SrcPlace != ITEM_PLACE_CARRY)
		{
			int isGuild = 0;

			if ((DestItem->sIndex == 508 || DestItem->sIndex == 522 || DestItem->sIndex >= 526 && DestItem->sIndex <= 537)
				&& !m->DestPlace && m->SrcPlace)
				isGuild = 1;

			int isGuildAgain = 0;

			if ((SrcItem->sIndex == 508 || SrcItem->sIndex == 522 || SrcItem->sIndex >= 526 && SrcItem->sIndex <= 537)
				&& !m->DestPlace && m->SrcPlace)
				isGuildAgain = 1;

			if ((isGuild == 1 || isGuildAgain == 1) && g_Week && pMob[conn].MOB.BaseScore.Level < 1000)
			{
				SendClientMessage(conn, g_pMessageStringTable[_NN_Only_Sunday]);
				return;
			}

			GetGuild(SrcItem);
			GetGuild(DestItem);

			int Can = 1;
			int YouCan = 1;

			if (dItem->sIndex)
			{
				int error = -2;

				if (m->SrcPlace == ITEM_PLACE_EQUIP)
					Can = BASE_CanEquip(dItem, &pMob[conn].MOB.CurrentScore, m->SrcSlot, pMob[conn].MOB.Class, pMob[conn].MOB.Equip, &pMob[conn].extra);
			
				if (m->SrcPlace == ITEM_PLACE_CARRY)
				{
					if (!Can)
					{
						if (error > 0 && error <= pMob[conn].MaxCarry)
						{
							error--;
							SendItem(conn, ITEM_PLACE_CARRY, error, &pMob[conn].MOB.Carry[error]);
						}
					}
				}
			}

			if (sItem->sIndex)
			{
				int error = -2;

				if (m->DestPlace == ITEM_PLACE_EQUIP)
					YouCan = BASE_CanEquip(sItem, &pMob[conn].MOB.CurrentScore, m->DestSlot, pMob[conn].MOB.Class, pMob[conn].MOB.Equip, &pMob[conn].extra);
				
				if (m->DestPlace == ITEM_PLACE_CARRY)
				{
					if (!YouCan)
					{
						if (error > 0 && error <= pMob[conn].MaxCarry)
						{
							error--;
							SendItem(conn, ITEM_PLACE_CARRY, error, &pMob[conn].MOB.Carry[error]);
						}
					}
				}
			}
			if (Can && YouCan)
			{

				STRUCT_ITEM save1;
				STRUCT_ITEM save2;

				save1.sIndex = SrcItem->sIndex;
				save1.stEffect[0].cEffect = SrcItem->stEffect[0].cEffect;
				save1.stEffect[0].cValue = SrcItem->stEffect[0].cValue;
				save1.stEffect[1].cEffect = SrcItem->stEffect[1].cEffect;
				save1.stEffect[1].cValue = SrcItem->stEffect[1].cValue;
				save1.stEffect[2].cEffect = SrcItem->stEffect[2].cEffect;
				save1.stEffect[2].cValue = SrcItem->stEffect[2].cValue;

				save2.sIndex = DestItem->sIndex;
				save2.stEffect[0].cEffect = DestItem->stEffect[0].cEffect;
				save2.stEffect[0].cValue = DestItem->stEffect[0].cValue;
				save2.stEffect[1].cEffect = DestItem->stEffect[1].cEffect;
				save2.stEffect[1].cValue = DestItem->stEffect[1].cValue;
				save2.stEffect[2].cEffect = DestItem->stEffect[2].cEffect;
				save2.stEffect[2].cValue = DestItem->stEffect[2].cValue;

				//AGRUPAR ITENS MANUALMENTE
				if ((save1.sIndex == save2.sIndex && save1.sIndex == 413
					|| save1.sIndex == save2.sIndex && save1.sIndex == 412
					|| save1.sIndex == save2.sIndex && save1.sIndex == 3140
					|| save1.sIndex == save2.sIndex && save1.sIndex == 419
					|| save1.sIndex == save2.sIndex && save1.sIndex == 420
					|| save1.sIndex == save2.sIndex && save1.sIndex == 697
					|| save1.sIndex == save2.sIndex && save1.sIndex == 3336
					|| save1.sIndex == save2.sIndex && save1.sIndex == 3200
					|| save1.sIndex == save2.sIndex && save1.sIndex == 3201
					|| save1.sIndex == save2.sIndex && save1.sIndex == 3202
					|| save1.sIndex == save2.sIndex && save1.sIndex == 3203
					|| save1.sIndex == save2.sIndex && save1.sIndex == 3204
					|| save1.sIndex == save2.sIndex && save1.sIndex == 3205
					|| save1.sIndex == save2.sIndex && save1.sIndex == 3206
					|| save1.sIndex == save2.sIndex && save1.sIndex == 3207
					|| save1.sIndex == save2.sIndex && save1.sIndex == 3208
					|| save1.sIndex == save2.sIndex && save1.sIndex == 3209
					|| save1.sIndex == save2.sIndex && save1.sIndex == 4011
					|| save1.sIndex == save2.sIndex && save1.sIndex == 4010
					|| save1.sIndex == save2.sIndex && save1.sIndex == 4026
					|| save1.sIndex == save2.sIndex && save1.sIndex == 4027
					|| save1.sIndex == save2.sIndex && save1.sIndex == 4028
					|| save1.sIndex == save2.sIndex && save1.sIndex == 4029
					|| save1.sIndex == save2.sIndex && save1.sIndex == 3326
					|| save1.sIndex == save2.sIndex && save1.sIndex == 4146					
					|| save1.sIndex == save2.sIndex && save1.sIndex == 4016
					|| save1.sIndex == save2.sIndex && save1.sIndex == 4017
					|| save1.sIndex == save2.sIndex && save1.sIndex == 4018
					|| save1.sIndex == save2.sIndex && save1.sIndex == 4019
					|| save1.sIndex == save2.sIndex && save1.sIndex == 4020
					|| save1.sIndex == save2.sIndex && save1.sIndex == 787
					|| save1.sIndex == save2.sIndex && save1.sIndex == 4097
					|| save1.sIndex == save2.sIndex && save1.sIndex == 3182
					|| save1.sIndex == save2.sIndex && save1.sIndex == 777
					|| save1.sIndex == save2.sIndex && save1.sIndex == 4140
					|| save1.sIndex == save2.sIndex && save1.sIndex == 3173
					|| save1.sIndex == save2.sIndex && save1.sIndex == 4046
					|| save1.sIndex == save2.sIndex && save1.sIndex == 1774
					|| save1.sIndex == save2.sIndex && save1.sIndex == 415
					|| save1.sIndex == save2.sIndex && save1.sIndex >= 2441 && save1.sIndex <= 2444
					|| save1.sIndex == save2.sIndex && save1.sIndex >= 4051 && save1.sIndex <= 4055
					|| save1.sIndex == save2.sIndex && save1.sIndex >= 2390 && save1.sIndex <= 2419
					|| save1.sIndex == save2.sIndex && save1.sIndex >= 3027 && save1.sIndex <= 3030)
					&& BASE_GetItemAmount(&save1) < 120 && BASE_GetItemAmount(&save2) < 120)
				{
					int amount1 = BASE_GetItemAmount(&save1);
					int amount2 = BASE_GetItemAmount(&save2);
					int tamount = (amount1 <= 0 ? 1 : amount1) + (amount2 <= 0 ? 1 : amount2);

					if (tamount <= 119)
					{
						save1.stEffect[0].cEffect = 61;
						save1.stEffect[0].cValue = tamount;

						BASE_ClearItem(&save2);

						SendItem(conn, m->SrcPlace, m->SrcSlot, &save1);
						SendItem(conn, m->DestPlace, m->DestSlot, &save2);
					}
					else if (tamount >= 120)
					{
						save1.stEffect[0].cEffect = 61;
						save1.stEffect[0].cValue = 120;

						tamount -= 120;

						if (tamount >= 1)
							BASE_SetItemAmount(&save2, tamount > 120 ? 120 : tamount);

						if (tamount <= 0)
							BASE_ClearItem(&save2);

						SendItem(conn, m->SrcPlace, m->SrcSlot, &save1);
						SendItem(conn, m->DestPlace, m->DestSlot, &save2);
					}
				}
				

				//CONTROLE DE FADAS

				if (save1.sIndex >= 3900 && save1.sIndex <= 3902 && save1.stEffect[0].cEffect == 0 && save1.stEffect[1].cEffect == 0 && save1.stEffect[2].cEffect == 0)
				{
					BASE_FadaDate(&save1, 2); // fadas de 3 dias
					SendItem(conn, m->SrcPlace, m->SrcSlot, &save1);
				}
				if (save1.sIndex >= 3903 && save1.sIndex <= 3905 && save1.stEffect[0].cEffect == 0 && save1.stEffect[1].cEffect == 0 && save1.stEffect[2].cEffect == 0)
				{
					BASE_FadaDate(&save1, 4); // fadas 5 dias
					SendItem(conn, m->SrcPlace, m->SrcSlot, &save1);
				}
				if (save1.sIndex >= 3906 && save1.sIndex <= 3908 && save1.stEffect[0].cEffect == 0 && save1.stEffect[1].cEffect == 0 && save1.stEffect[2].cEffect == 0)
				{
					BASE_FadaDate(&save1, 6); // fadas 7 dias
					SendItem(conn, m->SrcPlace, m->SrcSlot, &save1);
				}
				if (save1.sIndex == 3916 && save1.stEffect[0].cEffect == 0 && save1.stEffect[1].cEffect == 0 && save1.stEffect[2].cEffect == 0)
				{
					BASE_FadaDate(&save1, 6); // fadas 7 dias
					SendItem(conn, m->SrcPlace, m->SrcSlot, &save1);
				}

				//ESFERAS
				if (save1.sIndex == 3980 && save1.stEffect[0].cEffect == 0 && save1.stEffect[1].cEffect == 0 && save1.stEffect[2].cEffect == 0)
				{
					BASE_SetItemDate(&save1, 3); // shire 3 dias
					SendItem(conn, m->SrcPlace, m->SrcSlot, &save1);
				}
				if (save2.sIndex == 3980 && save2.stEffect[0].cEffect == 0 && save2.stEffect[1].cEffect == 0 && save2.stEffect[2].cEffect == 0)
				{
					BASE_SetItemDate(&save2, 3); // shire 3 dias
					SendItem(conn, m->SrcPlace, m->SrcSlot, &save2);
				}

				if (save1.sIndex >= 3981 && save1.sIndex <= 3982 && save1.stEffect[0].cEffect == 0 && save1.stEffect[1].cEffect == 0 && save1.stEffect[2].cEffect == 0)
				{
					BASE_SetItemDate(&save1, 3); // Thoroughbred e Klazedale 3 Dias
					SendItem(conn, m->SrcPlace, m->SrcSlot, &save1);
				}
				if (save2.sIndex >= 3981 && save2.sIndex <= 3982 && save2.stEffect[0].cEffect == 0 && save2.stEffect[1].cEffect == 0 && save2.stEffect[2].cEffect == 0)
				{
					BASE_SetItemDate(&save2, 3); // Thoroughbred e Klazedale 3 Dias
					SendItem(conn, m->SrcPlace, m->SrcSlot, &save2);
				}

				if (save1.sIndex >= 3983 && save1.sIndex <= 3985 && save1.stEffect[0].cEffect == 0 && save1.stEffect[1].cEffect == 0 && save1.stEffect[2].cEffect == 0)
				{
					BASE_SetItemDate(&save1, 15); //Shire, Thoroughbred, Klazedale 15 dias
					SendItem(conn, m->SrcPlace, m->SrcSlot, &save1);
				}
				if (save2.sIndex >= 3983 && save2.sIndex <= 3985 && save2.stEffect[0].cEffect == 0 && save2.stEffect[1].cEffect == 0 && save2.stEffect[2].cEffect == 0)
				{
					BASE_SetItemDate(&save2, 15);//Shire, Thoroughbred, Klazedale 15 dias
					SendItem(conn, m->DestPlace, m->DestSlot, &save2);
				}

				if (save1.sIndex >= 3986 && save1.sIndex <= 3989 && save1.stEffect[0].cEffect == 0 && save1.stEffect[1].cEffect == 0 && save1.stEffect[2].cEffect == 0)
				{
					BASE_SetItemDate(&save1, 30); //Shire, Thoroughbred, Klazedale, Gullfaxi 30 dias
					SendItem(conn, m->SrcPlace, m->SrcSlot, &save1);
				}
				if (save2.sIndex >= 3986 && save2.sIndex <= 3989 && save2.stEffect[0].cEffect == 0 && save2.stEffect[1].cEffect == 0 && save2.stEffect[2].cEffect == 0)
				{
					BASE_SetItemDate(&save2, 30); //Shire, Thoroughbred, Klazedale, Gullfaxi 30 dias
					SendItem(conn, m->DestPlace, m->DestSlot, &save2);
				}

				if (save1.sIndex >= 3995 && save1.sIndex <= 3999 && save1.stEffect[0].cEffect == 0 && save1.stEffect[1].cEffect == 0 && save1.stEffect[2].cEffect == 0)
				{
					BASE_SetItemDate(&save1, 30); //Novas Esferas 30 dias
					SendItem(conn, m->SrcPlace, m->SrcSlot, &save1);
				}
				if (save2.sIndex >= 3995 && save2.sIndex <= 3999 && save2.stEffect[0].cEffect == 0 && save2.stEffect[1].cEffect == 0 && save2.stEffect[2].cEffect == 0)
				{
					BASE_SetItemDate(&save2, 30); //Novas Esferas 30 dias
					SendItem(conn, m->DestPlace, m->DestSlot, &save2);
				}
				if (save1.sIndex >= 3990 && save1.sIndex <= 3992 && save1.stEffect[0].cEffect == 0 && save1.stEffect[1].cEffect == 0 && save1.stEffect[2].cEffect == 0)
				{
					BASE_SetItemDate(&save1, 30); //Novas Esferas 30 dias
					SendItem(conn, m->SrcPlace, m->SrcSlot, &save1);
				}
				if (save2.sIndex >= 3990 && save2.sIndex <= 3992 && save2.stEffect[0].cEffect == 0 && save2.stEffect[1].cEffect == 0 && save2.stEffect[2].cEffect == 0)
				{
					BASE_SetItemDate(&save2, 30); //Novas Esferas 30 dias
					SendItem(conn, m->DestPlace, m->DestSlot, &save2);
				}

				//TRAJES
				if (save1.sIndex >= 4150 && save1.sIndex <= 4188 && save1.stEffect[0].cEffect == 0 && save1.stEffect[1].cEffect == 0 && save1.stEffect[2].cEffect == 0)
				{
					BASE_SetItemDate(&save1, 30);
					SendItem(conn, m->SrcPlace, m->SrcSlot, &save1);
				}
				if (save2.sIndex >= 4150 && save2.sIndex <= 4188 && save2.stEffect[0].cEffect == 0 && save2.stEffect[1].cEffect == 0 && save2.stEffect[2].cEffect == 0)
				{
					BASE_SetItemDate(&save2, 30);
					SendItem(conn, m->DestPlace, m->DestSlot, &save2);
				}
				if (save1.sIndex >= 4200 && save1.sIndex <= 4467 && save1.stEffect[0].cEffect == 0 && save1.stEffect[1].cEffect == 0 && save1.stEffect[2].cEffect == 0)
				{
					BASE_SetItemDate(&save1, 30);
					SendItem(conn, m->SrcPlace, m->SrcSlot, &save1);
				}
				if (save2.sIndex >= 4200 && save2.sIndex <= 4467 && save2.stEffect[0].cEffect == 0 && save2.stEffect[1].cEffect == 0 && save2.stEffect[2].cEffect == 0)
				{
					BASE_SetItemDate(&save2, 30);
					SendItem(conn, m->DestPlace, m->DestSlot, &save2);
				}				

				//VERIFICAÇAO DE DATA
				if (save1.sIndex >= 3980 && save1.sIndex <= 3992 && BASE_CheckItemDate(&save1) || save1.sIndex >= 4150 && save1.sIndex <= 4188 && BASE_CheckItemDate(&save1))
				{
					BASE_ClearItem(&save1);
					SendItem(conn, m->SrcPlace, m->SrcSlot, &save1);
				}
				if (save2.sIndex >= 3980 && save2.sIndex <= 3992 && BASE_CheckItemDate(&save2) || save2.sIndex >= 4150 && save2.sIndex <= 4188 && BASE_CheckItemDate(&save2))
				{
					BASE_ClearItem(&save2);
					SendItem(conn, m->DestPlace, m->DestSlot, &save2);
				}
				if (save1.sIndex >= 4200 && save1.sIndex <= 4467 && BASE_CheckItemDate(&save1))
				{
					BASE_ClearItem(&save1);
					SendItem(conn, m->SrcPlace, m->SrcSlot, &save1);
				}
				if (save2.sIndex >= 4200 && save2.sIndex <= 4467 && BASE_CheckItemDate(&save2))
				{
					BASE_ClearItem(&save2);
					SendItem(conn, m->DestPlace, m->DestSlot, &save2);
				}

				char itemLog[2048];
				char itemLog2[2048];

				BASE_GetItemCode(&save1, itemLog);
				BASE_GetItemCode(&save2, itemLog2);

				//sprintf(temp, "tradingitem, SrcType:%d SrcSlot:%d Item:%s DstType:%d DstSlot:%d Item:%s", m->SrcPlace, m->SrcSlot, itemLog, m->DestPlace, m->DestSlot, itemLog2);
				//ItemLog(temp, pUser[conn].AccountName, pUser[conn].MacAddress);

				memcpy(SrcItem, &save2, sizeof(STRUCT_ITEM));
				memcpy(DestItem, &save1, sizeof(STRUCT_ITEM));


				if (save2.sIndex <= 40)
					GetGuild(SrcItem);

				if (save1.sIndex <= 40)
					GetGuild(DestItem);

				pMob[conn].GetCurrentScore(conn);

				int Size = m->Size;

				if (Size > sizeof(MSG_TradingItem))
				{
					m->Size = 0;
					return;
				}
				if (!pUser[conn].cSock.AddMessage((char*)m, sizeof(MSG_TradingItem)))
					CloseUser(conn);

				if (!pMob[conn].MOB.Equip[6].sIndex)
				{
					if (pMob[conn].MOB.Equip[7].sIndex)
					{
						int hab = BASE_GetItemAbility(&pMob[conn].MOB.Equip[7], EF_POS);

						if (hab != 128)
						{
							m->DestPlace = ITEM_PLACE_EQUIP;
							m->DestSlot = 6;
							m->SrcPlace = ITEM_PLACE_EQUIP;
							m->SrcSlot = 7;

							int Size = m->Size;

							if (Size > sizeof(MSG_TradingItem))
							{
								m->Size = 0;
								return;
							}
							if (!pUser[conn].cSock.AddMessage((char*)m, sizeof(MSG_TradingItem)))
								CloseUser(conn);

							pMob[conn].MOB.Equip[6] = pMob[conn].MOB.Equip[7];

							memset(&pMob[conn].MOB.Equip[7], 0, sizeof(STRUCT_ITEM));
						}
					}
				}

				if (DestPlace == ITEM_PLACE_CARRY)
					SendEquip(conn, conn);

				if (SrcPlace == ITEM_PLACE_CARRY)
				{
					GetGuild(conn);
					SendScore(conn);
				}

				if (DestItem->sIndex >= 2330 && DestItem->sIndex < 2360 || SrcItem->sIndex >= 2330 && SrcItem->sIndex < 2360)
					MountProcess(conn, Mount);

				//Verifica se a montaria tem traje e retira
				if (SrcItem->sIndex >= 2360 && SrcItem->sIndex < 2390) {
					if (m->SrcPlace == ITEM_PLACE_CARGO) {
						if (SrcItem->stEffect[2].cValue != 0) {
							SrcItem->stEffect[2].cValue = 0;
							RemoveMountTraje(conn);
						}
						SendItem(conn, ITEM_PLACE_CARGO, m->SrcSlot, &pUser[conn].Cargo[m->SrcSlot]);
					}
					if (m->SrcPlace == ITEM_PLACE_CARRY) {
						if (SrcItem->stEffect[2].cValue != 0) {
							SrcItem->stEffect[2].cValue = 0;
							RemoveMountTraje(conn);
						}
						SendItem(conn, ITEM_PLACE_CARRY, m->SrcSlot, &pMob[conn].MOB.Carry[m->SrcSlot]);
					}
				}
				if (DestItem->sIndex >= 2360 && DestItem->sIndex < 2390) {
					if (m->DestPlace == ITEM_PLACE_EQUIP) {
						RequestTraje(conn);
					}
					if (m->DestPlace == ITEM_PLACE_CARGO) {
						if (DestItem->stEffect[2].cValue != 0) {
							DestItem->stEffect[2].cValue = 0;
							RemoveMountTraje(conn);
						}
						SendItem(conn, ITEM_PLACE_CARGO, m->DestSlot, &pUser[conn].Cargo[m->DestSlot]);
					}
					if (m->DestPlace == ITEM_PLACE_CARRY) {
						if (DestItem->stEffect[2].cValue != 0) {
							DestItem->stEffect[2].cValue = 0;	
							RemoveMountTraje(conn);
						}
						SendItem(conn, ITEM_PLACE_CARRY, m->DestSlot, &pMob[conn].MOB.Carry[m->DestSlot]);
					}
				}
				STRUCT_ITEM *Storage2 = &pUser[conn].Cargo[MAX_CARGO - 2];
				STRUCT_ITEM *LastStorage = &pUser[conn].Cargo[MAX_CARGO - 1];

				if (m->DestPlace == ITEM_PLACE_CARGO || m->SrcPlace == ITEM_PLACE_CARGO)
				{
					if (Storage2->sIndex || LastStorage->sIndex)
					{
						for (int i = 0; i < 126; ++i)
						{
							if (Storage2->sIndex)
							{
								int cancargo = BASE_CanCargo(Storage2, pUser[conn].Cargo, i % 9, i / 9);
								if (cancargo)
								{
									memcpy(&pUser[conn].Cargo[i], Storage2, sizeof(STRUCT_ITEM));

									memset(Storage2, 0, sizeof(STRUCT_ITEM));
									SendItem(conn, ITEM_PLACE_CARGO, i, &pUser[conn].Cargo[i]);
								}
							}

							else
							{
								if (LastStorage->sIndex)
								{
									int cancargo = BASE_CanCargo(LastStorage, pUser[conn].Cargo, i % 9, i / 9);
									if (cancargo)
									{
										memcpy(&pUser[conn].Cargo[i], LastStorage, sizeof(STRUCT_ITEM));

										memset(LastStorage, 0, sizeof(STRUCT_ITEM));
										SendItem(conn, ITEM_PLACE_CARGO, i, &pUser[conn].Cargo[i]);
									}
								}
							}
						}
					}
				}
			}
			else
			{
				STRUCT_ITEM save1;
				STRUCT_ITEM save2;

				save1.sIndex = SrcItem->sIndex;
				save1.stEffect[0].cEffect = SrcItem->stEffect[0].cEffect;
				save1.stEffect[0].cValue = SrcItem->stEffect[0].cValue;
				save1.stEffect[1].cEffect = SrcItem->stEffect[1].cEffect;
				save1.stEffect[1].cValue = SrcItem->stEffect[1].cValue;
				save1.stEffect[2].cEffect = SrcItem->stEffect[2].cEffect;
				save1.stEffect[2].cValue = SrcItem->stEffect[2].cValue;

				save2.sIndex = DestItem->sIndex;
				save2.stEffect[0].cEffect = DestItem->stEffect[0].cEffect;
				save2.stEffect[0].cValue = DestItem->stEffect[0].cValue;
				save2.stEffect[1].cEffect = DestItem->stEffect[1].cEffect;
				save2.stEffect[1].cValue = DestItem->stEffect[1].cValue;
				save2.stEffect[2].cEffect = DestItem->stEffect[2].cEffect;
				save2.stEffect[2].cValue = DestItem->stEffect[2].cValue;

				memcpy(SrcItem, &save1, sizeof(STRUCT_ITEM));
				memcpy(DestItem, &save2, sizeof(STRUCT_ITEM));
			}
		}
	}

	pMob[conn].GetCurrentScore(conn);
	SendScore(conn);
	SendEtc(conn);
}