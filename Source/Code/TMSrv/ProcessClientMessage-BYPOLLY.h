//bom agora temos todo o esqueleto da ProcessClientMessage
//com a identificação dos packets, faltao alguns ain da q sao dentro dos switch
//e vao ser identificados com conforme vai evoluindo,
//se quiserem ajudar descompilar os packets.

void ProcessClientMessage(int conn, char* msg) //0042ea00
{
	__HEADER pHeader = *(__HEADER*)msg;

	if(ServerDown >= 120)
		return;

	if((pHeader.PacketId & FLAG_CLIENT2GAME) == 0 || pHeader.ClientId < MOB_EMPTY || pHeader.ClientId >= MAX_PLAYER)
	{
		//sprintf(temp, "Unknown Packet Type:%d ID:%d Size:%d KeyWord:%d", pHeader.PacketId, pHeader.ClientId, pHeader.Size, pHeader.Key);
		//Log(temp, "-system", NULL);
		return;
	}

	//0042EAB5
	if(conn > MOB_EMPTY && conn < MAX_PLAYER)
		pUser[conn].LastReceiveTime = SecCounter;

	if(pHeader.PacketId == _MSG_Ping) //0x3A0
		return;

	//0042EAEB
	int PacketOpCode = pHeader.PacketId;
	if(PacketOpCode > _MSG_GetItem) //0x270
	{
		//0042EB41
		if(PacketOpCode > _MSG_SwapItem) //0x376
		{
			//0042EBE8
			if(PacketOpCode > _MSG_AutoTrade) //0x397
			{
				//0042EC30
				if(PacketOpCode > _MSG_SendParty)
				{
					//0042EC80
					if(PacketOpCode == 0xE0E)
					{
						//0042EF8D

					}

					//0042EC90
					if(PacketOpCode == 0xE12)
					{
						//0042ECF4

					}

					//0042EC9C
					if(PacketOpCode == _MSG_ReqTransper) //0xFAA
					{
						//0042ECAD
						if(TransperCharacter != 0)
						{
							MSG_ReqTransper* pReqTransper = (MSG_ReqTransper*)msg;
							pReqTransper->Header.ClientId = conn;

							pUser[conn].Mode = USER_CREWAIT;
							DBServerSocket.SendOneMessage((char*)&pReqTransper, sizeof MSG_ReqTransper);
						}
					}

					return;
				}

				//0042EC3C
				if(PacketOpCode == _MSG_SendParty)
				{
					//00445122

				}

				//0042EC4C
				PacketOpCode = PacketOpCode - _MSG_ReqBuy;
				if(PacketOpCode > 14)
					return;

				switch(PacketOpCode)
				{
					case 0: //0x398 _MSG_ReqBuy
					{
						//0043D854

					}

					case 1: //0x399 _MSG_PKMode
					{
						//00430DBE
						MSG_STANDARDPARM* pPKMode = (MSG_STANDARDPARM*)msg;
						pUser[conn].PKMode = pPKMode->Parm1;
						return;
					}

					case 2: //0x39A _MSG_ReqTradeList
					{
						//0043E17E

					}

					case 5: //0x39D _MSG_AttackOne
					case 6: //0x39E _MSG_AttackTwo
					{
						//00430DE4

					}

					case 7: //0x39F _MSG_ReqRanking
					{
						//

					}

					case 14: //0x3Ä6 _MSG_CombineItem
					{
						//0043E6B9

					}

					default:
						return;
				}
			}

			//0042EBF4
			if(PacketOpCode == _MSG_AutoTrade)
			{
				//0043E308
				MSG_AutoTrade* pAutoTrade = (MSG_AutoTrade*)msg;
				if(pMob[conn].MOB.CurrentScore.Hp <= 0 || pMob[conn].Mode != USER_PLAY)
				{
					SendHpMode(conn);
					//AddCrackError(conn, 10, 88);
					RemoveTrade(conn);
					return;
				}

				//0043E364
				int tX = pMob[conn].TargetX;
				int tY = pMob[conn].TargetY;
				int cityId = BASE_GetVillage(tX, tY);
				if(cityId >= 0 && cityId < MAX_GUILDZONE)
				{
					SendClientMessage(conn, ""); //007CF528
					return;
				}

				//0043E3D2
				int TargetId = pAutoTrade->TargetID;
				if(TargetId <= 0 || TargetId >= MAX_PLAYER)
					return;
				
				for(int i = 0; i < MAX_AUTOTRADE; i++)
				{
					if(pAutoTrade->TradeMoney[i] < 0 || pAutoTrade->TradeMoney[i] > 999999999 || pAutoTrade->Item[i].Index == 0 && pAutoTrade->TradeMoney[i] != 0)
						return;

					if(pAutoTrade->Item[i].Index == 0)
						continue;

					if(pAutoTrade->TradeMoney[i] == 0)
						return;

					//0043E4BF
					if(pAutoTrade->Item[i].Index == 508 || pAutoTrade->Item[i].Index == 509 || pAutoTrade->Item[i].Index == 522 || pAutoTrade->Item[i].Index == 446 || (pAutoTrade->Item[i].Index >= 526 && pAutoTrade->Item[i].Index <= 531))
						return;

					//0043E55A
					int InvPos = pAutoTrade->InvenPos[i];
					if(InvPos < 0 || InvPos >= MAX_CARGO)
						return;

					int checkSlots = memcmp(&pUser[conn].Cargo[InvPos], &pAutoTrade->Item[i], sizeof STRUCT_ITEM);
					if(checkSlots != 0)
					{
						RemoveTrade(conn);
						break;
					}
				}

				//0043E5E4
				pAutoTrade->Tax = g_pGuildZone[cityId].Tax;
				pAutoTrade->Desc[24] = 0;
				pAutoTrade->Desc[23] = 0;

				strncpy(pUser[conn].AutoTradeName, pAutoTrade->Desc, MAX_DESC);
				pUser[conn].TradeMode = AUTOTRADE_ON;
				memcpy(&pUser[conn].AutoTrade, pAutoTrade, sizeof MSG_AutoTrade);
				SendAutoTrade(conn, conn);

				MSG_CreateMobTrade pCreateMobTrade;
				GetCreateMobTrade(conn, &pCreateMobTrade);
				GridMulticast(tX, tY, (MSG_STANDARD*)&pCreateMobTrade, 0);
			}
		}

		//0042EB51
		if(PacketOpCode == _MSG_SwapItem) //0x397
		{
			//0043FE71
			MSG_SwapItem* pMoveItem = (MSG_SwapItem*)msg;
			if(pMob[conn].MOB.CurrentScore.Hp == 0 || pUser[conn].Mode != USER_PLAY)
			{
				SendHpMode(conn);
				//AddCrackError(conn, 1, 0x13);
				return;
			}

			//0043FEC1
			if(pUser[conn].Trade.OpponentID != MOB_EMPTY)
			{
				//RemoveTrade(conn);
				return;
			}

			//0043FEE8
			if(pUser[conn].TradeMode != AUTOTRADE_OFF && pMoveItem->SrcType == STORAGE_TYPE || pMoveItem->DestType == STORAGE_TYPE)
			{
					SendClientMessage(conn, ""); //007CF428
					return;
			}

			//0043FF30
			if(pMoveItem->SrcType == STORAGE_TYPE || pMoveItem->DestType == STORAGE_TYPE && pMob[conn].MOB.ClassInfo != 3 || (pMob[conn].MOB.Learn & LEARN_13) == 0)
			{
				//0043FF86
				int alvo = pMoveItem->TargetID;
				if(alvo <= MAX_PLAYER || alvo >= MAX_MOB)
				{
					SendClientSignal(conn, 0x7530, _MSG_ClearMenu);
					return;
				}

				//0043FFC8
				if(pMob[alvo].Mode != MOB_PEACE || pMob[alvo].MOB.CapeInfo != 2)
				{
					SendClientSignal(conn, 0x7530, _MSG_ClearMenu);
					return;
				}

				//00440010
				int tX = pMob[conn].TargetX;
				int tY = pMob[conn].TargetY;
				int AlvoTx = pMob[alvo].TargetX;
				int AlvoTy = pMob[alvo].TargetY;
				if(tX < AlvoTx - 23 || tX > AlvoTx + 23 || tY < AlvoTy - 23 || tY > AlvoTy + 23)
				{
					SendClientSignal(conn, 0x7530, _MSG_ClearMenu);
					return;
				}
			}

			//004400C9
			STRUCT_ITEM pMount;
			memcpy(&pMount, &pMob[conn].MOB.Equip[MOUNT], sizeof STRUCT_ITEM);

			int isEquip = FALSE;
			int isGuild = FALSE;

			STRUCT_ITEM* pSrcPtr = NULL;
			STRUCT_ITEM* pDestPtr = NULL;

			//004400FC
			if(pMoveItem->SrcType == EQUIP_TYPE)
			{
				//0044010F
				if(pMoveItem->SrcPos <= FACE || pMoveItem->SrcPos >= MAX_EQUIP)
				{
					//Log("err, trading fails.SwapItem-Equip", pUser[conn].AccountName, pUser[conn].IP);
					return;
				}

				pSrcPtr = &pMob[conn].MOB.Equip[pMoveItem->SrcPos];
				isEquip = TRUE;
				isGuild = TRUE;
			}
			else if(pMoveItem->SrcType == INV_TYPE) //0044019A
			{
				//004401AA
				if(pMoveItem->SrcPos <= 0 || pMoveItem->SrcPos >= MAX_INVEN)
				{
					//Log("err, trading fails.SwapItem-Carry", pUser[conn].AccountName, pUser[conn].IP);
					return;
				}

				pSrcPtr = &pMob[conn].MOB.Inventory[pMoveItem->SrcPos];
			}
			else if(pMoveItem->SrcType == STORAGE_TYPE) //00440220
			{
				//00440230
				if(pMoveItem->SrcPos <= 0 || pMoveItem->SrcPos >= MAX_CARGO)
				{
					//Log("err, trading fails.SwapItem-Cargo", pUser[conn].AccountName, pUser[conn].IP);
					return;
				}

				pSrcPtr = &pUser[conn].Cargo[pMoveItem->SrcPos];
			}
			else //004402A7
			{
				//Log("err, trading fails.SwapItem source type", pUser[conn].AccountName, pUser[conn].IP);
				return;
			}

			//004402D9
			if(pMoveItem->DestType == EQUIP_TYPE)
			{
				//004402EC
				if(pMoveItem->DestPos <= FACE || pMoveItem->DestPos >= MAX_EQUIP)
				{
					//Log("err, trading fails.SwapItem-Equip", pUser[conn].AccountName, pUser[conn].IP);
					return;
				}

				pDestPtr = &pMob[conn].MOB.Equip[pMoveItem->DestPos];
				isEquip = 1;
				isGuild = 1;
			}
			else if(pMoveItem->DestType == INV_TYPE) //00440377
			{
				//00440387
				if(pMoveItem->DestPos <= 0 || pMoveItem->DestPos >= MAX_INVEN)
				{
					//Log("err, trading fails.SwapItem-Carry", pUser[conn].AccountName, pUser[conn].IP);
					return;
				}

				pDestPtr = &pMob[conn].MOB.Inventory[pMoveItem->SrcPos];
			}
			else if(pMoveItem->DestType == STORAGE_TYPE) //004403FD
			{
				//0044040D
				if(pMoveItem->DestPos <= 0 || pMoveItem->DestPos >= MAX_CARGO)
				{
					//Log("err, trading fails.SwapItem-Cargo", pUser[conn].AccountName, pUser[conn].IP);
					return;
				}

				pDestPtr = &pUser[conn].Cargo[pMoveItem->SrcPos];
			}
			else //00440484
			{
				//Log("err, trading fails.SwapItem source type", pUser[conn].AccountName, pUser[conn].IP);
				return;
			}

			//004404B6
			if(pSrcPtr->Index == 747 || pDestPtr->Index == 747) //Coroa de Atila
				//004404D7
				if(pMoveItem->SrcType == STORAGE_TYPE || pMoveItem->DestType == STORAGE_TYPE)
					return;

			//004404FC
			int retSrcItem = FALSE;
			if(pSrcPtr->Index == 508 || pSrcPtr->Index == 522 || (pSrcPtr->Index >= 526 && pSrcPtr->Index <= 537)) //Medalhas
				//00440548
				if(pMoveItem->SrcType == EQUIP_TYPE && pMoveItem->DestType != EQUIP_TYPE)
					retSrcItem = TRUE;

			//00440570
			int retDestItem = FALSE;
			if(pDestPtr->Index == 508 || pDestPtr->Index == 522 || (pDestPtr->Index >= 526 && pDestPtr->Index <= 537)) //Medalhas
				//004405BC
				if(pMoveItem->DestType == EQUIP_TYPE && pMoveItem->SrcType != EQUIP_TYPE)
					retDestItem = TRUE;

			//004405E4
			if(retSrcItem == TRUE || retDestItem == TRUE)
			{
				if(g_Week != 0 && pMob[conn].MOB.BaseScore.Level < 1000)
				{
					SendClientMessage(conn, ""); //007D2428
					return;
				}
			}

			//0044062C
			STRUCT_ITEM SrcItem;
			STRUCT_ITEM DestItem;
			memcpy(&SrcItem, pSrcPtr, sizeof STRUCT_ITEM);
			memcpy(&DestItem, pDestPtr, sizeof STRUCT_ITEM);

			BASE_ClearItem(pDestPtr);
			BASE_ClearItem(pSrcPtr);

			//00440678
			int canEquipDest = TRUE;
			int canEquipSrc = TRUE;
			if(DestItem.Index != 0)
			{
				//0044069B
				int destError = -2;
				if(pMoveItem->DestType == EQUIP_TYPE)
				{
					//004406B4
					canEquipDest = BASE_CanEquip(&DestItem, &pMob[conn].MOB.CurrentScore, pMoveItem->DestPos, pMob[conn].MOB.ClassInfo, pMob[conn].MOB.Equip);
				}
				else if(pMoveItem->DestType == INV_TYPE)
				{
					//0044071A
					canEquipDest = BASE_CanCarry(&DestItem, pMob[conn].MOB.Inventory, (pMoveItem->DestPos % 9), (pMoveItem->DestPos / 9), &destError);
					if(canEquipDest == 0 && destError > 0 && destError <= MAX_INVEN)
					{
						//00440789
						destError--;
						SendItem(conn, INV_TYPE, destError, &pMob[conn].MOB.Inventory[destError]);
					}
				}
				else if(pMoveItem->DestType == STORAGE_TYPE)
				{
					//004407D4
					canEquipDest = BASE_CanCargo(&DestItem, pUser[conn].Cargo, (pMoveItem->DestPos % 9), (pMoveItem->DestPos / 9));
				}
			}

			//00440823
			if(SrcItem.Index != 0)
			{
				//00440832
				int srcError = -2;
				if(pMoveItem->SrcType == EQUIP_TYPE)
				{
					//0044084B
					canEquipSrc = BASE_CanEquip(&SrcItem, &pMob[conn].MOB.CurrentScore, pMoveItem->SrcPos, pMob[conn].MOB.ClassInfo, pMob[conn].MOB.Equip);
				}
				else if(pMoveItem->SrcType == INV_TYPE)
				{
					//004408B1
					canEquipSrc = BASE_CanCarry(&SrcItem, pMob[conn].MOB.Inventory, (pMoveItem->SrcPos % 9), (pMoveItem->SrcPos / 9), &srcError);
					if(canEquipSrc == 0 && srcError > 0 && srcError <= MAX_INVEN)
					{
						//00440920
						srcError--;
						SendItem(conn, INV_TYPE, srcError, &pMob[conn].MOB.Inventory[srcError]);
					}
				}
				else if(pMoveItem->SrcType == STORAGE_TYPE)
				{
					//0044096B
					canEquipSrc = BASE_CanCargo(&SrcItem, pUser[conn].Cargo, (pMoveItem->SrcPos % 9), (pMoveItem->SrcPos / 9));
				}
			}

			//004409BA
			if(canEquipDest == 0 || canEquipSrc == 0)
			{
				memcpy(pSrcPtr, &DestItem, sizeof STRUCT_ITEM);
				memcpy(pDestPtr, &SrcItem, sizeof STRUCT_ITEM);
				return;
			}
			else
			{
				memcpy(pSrcPtr, &SrcItem, sizeof STRUCT_ITEM);
				memcpy(pDestPtr, &DestItem, sizeof STRUCT_ITEM);
			}

			//00440A2D
			if(pSrcPtr->Index <= 40) //ID das Faces
				BASE_ClearItem(pSrcPtr);

			if(pDestPtr->Index <= 40) //ID das Faces
				BASE_ClearItem(pDestPtr);

			//00440A58
			pMob[conn].GetCurrentScore(conn);
			pUser[conn].cSock.AddMessage((char*)pMoveItem, sizeof MSG_SwapItem);

			//00440A9C
			if(pMob[conn].MOB.Equip[WEAPON].Index == 0 && pMob[conn].MOB.Equip[SHIELD].Index != 0)
			{
				int ItemUnique = BASE_GetItemAbility(&pMob[conn].MOB.Equip[SHIELD], EF_POS);
				if(ItemUnique != 128)
				{
					//00440AFC
					pMoveItem->DestType = INV_TYPE;
					pMoveItem->DestPos = WEAPON;

					pMoveItem->SrcType = INV_TYPE;
					pMoveItem->SrcPos = SHIELD;

					pUser[conn].cSock.AddMessage((char*)&pMoveItem, sizeof MSG_SwapItem);

					memcpy(&pMob[conn].MOB.Equip[WEAPON], &pMob[conn].MOB.Equip[SHIELD], sizeof STRUCT_ITEM);
                    memset(&pMob[conn].MOB.Equip[SHIELD], 0, sizeof STRUCT_ITEM);
				}
			}

			//00440BA9
			if(isEquip == TRUE)
				SendEquip(conn, conn);

			if(isGuild == TRUE)
			{
				GetGuild(conn);
				SendScore(conn);
			}

			//00440BE3
			MountProcess(conn, &pMount);

			STRUCT_ITEM* penultimo = &pUser[conn].Cargo[126];
			STRUCT_ITEM* ultimo = &pUser[conn].Cargo[127];

			//00440C1F
			if(pMoveItem->SrcType == STORAGE_TYPE || pMoveItem->DestType == STORAGE_TYPE)
			{
				if(penultimo->Index == 0 || ultimo->Index == 0)
					return;

				//00440C61
				for(int i = 0; i < 126; i++)
				{
					//00440C89
					if(penultimo->Index != 0)
					{
						int canCargo = BASE_CanCargo(penultimo, pUser[conn].Cargo, i % 9, i / 9);
						if(canCargo != 0)
						{
							memcpy(&pUser[conn].Cargo[i], penultimo, sizeof STRUCT_ITEM);
							memset(penultimo, 0, sizeof STRUCT_ITEM);
							SendItem(conn, STORAGE_TYPE, i, &pUser[conn].Cargo[i]);
						}
					}

					if(ultimo->Index != 0) //00440D57
					{
						int canCargo = BASE_CanCargo(ultimo, pUser[conn].Cargo, i % 9, i / 9);
						if(canCargo != 0)
						{
							memcpy(&pUser[conn].Cargo[i], ultimo, sizeof STRUCT_ITEM);
							memset(ultimo, 0, sizeof STRUCT_ITEM);
							SendItem(conn, STORAGE_TYPE, i, &pUser[conn].Cargo[i]);
						}
					}
				}
			}
		}

		//0042EB61
		if(PacketOpCode > _MSG_EnterVillage)
		{
			//0042EBB1
			PacketOpCode = PacketOpCode - _MSG_Imple;
			if(PacketOpCode > 223)
				return;

			switch(PacketOpCode)
			{
				case 0: //0x295 _MSG_Imple
				{
					//0043D38A

				}

				case 158: //0x333 _MSG_MessageChat
				{
					//00442537

				}

				case 159: //0x334 _MSG_MessageWhisper
				{
					//00440E2A

				}

				case 161: //0x336 _MSG_UpdateScore
				{
					//0043D53D

				}

				case 209: //0x366 _MSG_Action
				case 210: //0x367 _MSG_Stop
				case 211: //0x368 _MSG_Illusion
				{
					//0042FE1A

				}

				case 212: //0x369 _MSG_REQMobByID
				{
					//00444D4A

				}

				case 213: //0x36A _MSG_Motion
				{
					//00430D38

				}

				case 215: //0x36C _MSG_Attack
				{
					//

				}

				case 222: //0x373 _MSG_UseItem
				{
					//0043A4A7

				}

				case 223: //0x374 
				{
					//0043D57E

				}

				default:
					return;
			}
		}

		//0042EB6D
		if(PacketOpCode == _MSG_EnterVillage)
		{
			//004353C1
			int tX = pMob[conn].TargetX;
			int tY = pMob[conn].TargetY;
			int cityId = BASE_GetVillage(tX, tY);

			//00435407
			if(cityId >= 0 && cityId < MAX_GUILDZONE)
			{
				//0043541E
				pMob[conn].MOB.Merchant = pMob[conn].MOB.Merchant & 0x3F;
				pMob[conn].MOB.Merchant = (pMob[conn].MOB.Merchant | (cityId << 6));
			}
		}

		//0042EB7D
		PacketOpCode = PacketOpCode - _MSG_DropItem;
		if(PacketOpCode > 30)
			return;

		switch(PacketOpCode)
		{
			case 0: //0x272 _MSG_DropItem
			{
				//00439D81

			}

			case 5: //0x277 _MSG_ApplyBonus
			{
				//00442B83

			}

			case 6: //0x278 
			{
				//00443322

			}

			case 9: //0x27B _MSG_REQShopList
			{
				//004441C7

			}

			case 23: //0x289 _MSG_Restart
			{
				// ainda nao achei o addr

			}

			case 25: //0x28B _MSG_Quest
			{
				//0043546F

			}

			case 26: //0x28C _MSG_Deprivate
			{
				// ainda nao achei o addr

			}

			case 28: //0x28E _MSG_Challange
			{
				// ainda nao achei o addr

			}

			case 29: //0x28F _MSG_ChallangeConfirm
			{
				// ainda nao achei o addr

			}

			case 30: //0x290 _MSG_ReqTeleport
			{
				// ainda nao achei o addr

			}

			default:
				return;
		}
	}

	//0042EB06
	if(PacketOpCode == _MSG_GetItem) //0x270
	{
		//0043925C
		MSG_GetItem* pItem = (MSG_GetItem*)msg;
		if(pMob[conn].MOB.CurrentScore.Hp <= 0 || pUser[conn].Mode != USER_PLAY)
		{
			SendHpMode(conn);
			//AddCrackError(conn, 1, 0xD);
			return;
		}

		//004392AC
		if(pItem->DestType != INV_TYPE)
		{
			//Log("DEBUG: GetItem with wrong DestType", pUser[conn].AccountName, pUser[conn].IP);
			return;
		}

		//004392E9
		int ItemIdx = pItem->ItemID - 10000;
		if(ItemIdx < 0 || ItemIdx > MAX_ITEMLIST || pItemBuffer[ItemIdx].Mode == 0)
		{
			if(pItemBuffer[ItemIdx].Mode != 0)
			{
				//sprintf(temp, "GetItemFail idx:%d mode:%d", ItemIdx, pItemBuffer[ItemIdx].Mode);
				//Log(temp, pUser[conn].AccountName, pUser[conn].IP);
			}

			MSG_RemoveItem rItem;
			rItem.Header.PacketId = _MSG_RemoveItem;
			rItem.Header.Size = sizeof MSG_RemoveItem;
			rItem.Header.ClientId = 0x7530;

			//004393AF
			rItem.ItemID = pItem->ItemID;

			pUser[conn].cSock.AddMessage((char*)&rItem, sizeof MSG_RemoveItem);
			return;
		}

		//004393ED
		if(pMob[conn].TargetX < (pItemBuffer[ItemIdx].PosX - 3) || pMob[conn].TargetY < (pItemBuffer[ItemIdx].PosY - 3) || pMob[conn].TargetX > (pItemBuffer[ItemIdx].PosX + 3) || pMob[conn].TargetY > (pItemBuffer[ItemIdx].PosY + 3))
		{
			//0043947D
			//sprintf(temp, "GetItemFail posx:%d posy:%d tx:% ty:%d", pItemBuffer[ItemIdx].PosX, pItemBuffer[ItemIdx].PosY, pMob[conn].TargetX, pMob[conn].TargetY);
			//Log(temp, pUser[conn].AccountName, pUser[conn].IP);
			return;
		}

		//00439501
		if(ItemIdx == 1727 || pMob[conn].MOB.CurrentScore.Level < 1000)
			return;
			
		//00439529
		STRUCT_ITEM checkItem = pItemBuffer[ItemIdx].ITEM;
		int ItemIndex = checkItem.Index;
		if(ItemIndex <= 0 || ItemIndex >= MAX_ITEMLIST)
			return;

		//00439567
		if(checkItem.Index == 470) //Pilula do poder
		{
			int temp1 = 0;
			int temp2 = 1;
			temp2 = temp2 << temp1;

			if((pMob[conn].MOB.QuestInfo & temp2) != 0)
			{
				//004395C2
				BASE_GetLanguage(temp, 71);
				SendClientMessage(conn, temp);
				return;
			}

			//004395E7
			SendClientMessage(conn, g_pMessageStringTable[temp1 + 1]);
			pMob[conn].MOB.QuestInfo = pMob[conn].MOB.QuestInfo | temp2;

			//0043962E
			int ItemPosX = pItemBuffer[ItemIdx].PosX;
			int ItemPosY = pItemBuffer[ItemIdx].PosY;
			BASE_ClearItem(&checkItem);
			pItemGrid[ItemPosX][ItemPosY] = 0;
			pItemBuffer[ItemIdx].Mode = 0;

			MSG_RemoveItem rItem;
			rItem.Header.PacketId = _MSG_RemoveItem;
			rItem.Header.Size = sizeof MSG_RemoveItem;
			rItem.Header.ClientId = 0x7530;

			//004393AF
			rItem.ItemID = ItemIdx + 10000;

			GridMulticast(ItemPosX, ItemPosY, (MSG_STANDARD*)&rItem, 0);

			pMob[conn].MOB.SkillPoint = pMob[conn].MOB.SkillPoint + 9;
			SendEmotion(conn, 0xE, 3);
			SendEtc(conn);
			return;
		}

		//00439723
		if(ItemIndex >= 490 && ItemIndex <= 500)
		{
			sprintf(temp, "PlayerName%s - ItemName%s", pMob[conn].MOB.Name, g_pItemList[ItemIndex].Name);
			SendNotice(temp);

			int ItemPosX = pItemBuffer[ItemIdx].PosX;
			int ItemPosY = pItemBuffer[ItemIdx].PosY;
			pItemGrid[ItemPosX][ItemPosY] = 0;
			pItemBuffer[ItemIdx].Mode = 0;

			MSG_RemoveItem rItem;
			rItem.Header.PacketId = _MSG_RemoveItem;
			rItem.Header.Size = sizeof MSG_RemoveItem;
			rItem.Header.ClientId = 0x7530;

			//004397F2
			rItem.ItemID = ItemIdx + 10000;

			GridMulticast(ItemPosX, ItemPosY, (MSG_STANDARD*)&rItem, 0);
		}

		//00439823
		int ItemPosX = pItemBuffer[ItemIdx].PosX;
		int ItemPosY = pItemBuffer[ItemIdx].PosY;

		MSG_RemoveItem rItem;
		rItem.Header.PacketId = _MSG_RemoveItem;
		rItem.Header.Size = sizeof MSG_RemoveItem;
		rItem.Header.ClientId = 0x7530;

		//00439868
		rItem.ItemID = pItem->ItemID;

		if(ItemPosX < 0 || ItemPosX >= MAX_GRIDX || ItemPosY < 0 || ItemPosY >= MAX_GRIDY)
		{
			//004398A3
			pUser[conn].cSock.AddMessage((char*)&rItem, sizeof MSG_RemoveItem);
			pItemBuffer[ItemIdx].Mode = 0;
			return;
		}

		//004398E3
		if(pItemGrid[ItemPosX][ItemPosY] != ItemIdx)
		{
			pUser[conn].cSock.AddMessage((char*)&rItem, sizeof MSG_RemoveItem);
			if(pItemGrid[ItemPosX][ItemPosY] == 0)
				pItemGrid[ItemPosX][ItemPosY] = ItemIdx;

			return;
		}

		//0043996C
		if(ItemPosX != pItem->PosX && ItemPosY != pItem->PosY)
			pUser[conn].cSock.AddMessage((char*)&rItem, sizeof MSG_RemoveItem);

		//004399C1
		int ItemVolatile = BASE_GetItemAbility(&checkItem, EF_VOLATILE);
		if(ItemVolatile == 2)
		{
			//004399E5
			int GetCoin = BASE_GetItemAbility(&checkItem, EF_HWORDCOIN);
			int CalcCoin = GetCoin << 8;

			GetCoin = BASE_GetItemAbility(&checkItem, EF_LWORDCOIN);
			CalcCoin = CalcCoin + GetCoin;

			int gold = pMob[conn].MOB.Gold + CalcCoin;
			if(gold >= 2000000000)
			{
				SendClientMessage(conn, "Limite de gold atingido");
				return;
			}

			//00439A7F
			pMob[conn].MOB.Gold = pMob[conn].MOB.Gold + CalcCoin;
			rItem.ItemID = checkItem.Index;
			BASE_ClearItem(&checkItem);
		}
		else
		{
			if(pItem->DestPos < 0 || pItem->DestPos >= MAX_INVEN) //00439ACE
			{
				//Log("DEBUG: Trading Fails. (wrong source position)", pUser[conn].AccountName, pUser[conn].IP);
				return;
			}

			//00439B18
			STRUCT_ITEM* Inven = &pMob[conn].MOB.Inventory[pItem->DestPos];
			int x = pItem->DestPos % 9;
			int y = pItem->DestPos / 9;
			int error = -2;
			int ret = BASE_CanCarry(&checkItem, pMob[conn].MOB.Inventory, x, y, &error);
			if(ret == 0 || error > 0 || error <= MAX_INVEN)
			{
				error = error - 1;
				SendItem(conn, INV_TYPE, error, &pMob[conn].MOB.Inventory[error]);
				return;
			}

			//00439C04
			memcpy(&rItem, &checkItem, sizeof STRUCT_ITEM);
			memcpy(Inven, &checkItem, sizeof STRUCT_ITEM);

			//00439C5F
			if(BASE_NeedLog((STRUCT_ITEM*)&rItem, 0) != 0)
			{
				char msg;
				BASE_GetItemCode((STRUCT_ITEM*)&rItem, &msg);
				//sprintf(temp, "get %s", &msg);
				//Log(temp, pUser[conn].AccountName, pUser[conn].IP);
			}
		}

		//00439CD0
		MSG_CNFGetItem respItem;
		respItem.Header.PacketId = _MSG_CNFGetItem;
		respItem.Header.Size = sizeof MSG_CNFGetItem;
		respItem.Header.ClientId = 0x7530;

		respItem.DestType = pItem->DestType;
		respItem.DestPos = pItem->DestPos;

		pUser[conn].cSock.AddMessage((char*)&respItem, sizeof MSG_CNFGetItem);
		GridMulticast(ItemPosX, ItemPosY, (MSG_STANDARD*)&rItem, 0);
		pItemGrid[ItemPosX][ItemPosY] = 0;
		pItemBuffer[ItemIdx].Mode = 0;
		return;
	}
	else
	{
		//0042EB16
		PacketOpCode = PacketOpCode - _MSG_AccountLogin;
		if(PacketOpCode > 8)
			return;

		switch(PacketOpCode)
		{
			case 0: //0x20D _MSG_AccountLogin
			{
				//0042F50F
				MSG_NewAccount* pNewAccount = (MSG_NewAccount*)msg;
				pNewAccount->Name[15] = '\0';
				pNewAccount->Pwd[11] = '\0';

				if(pNewAccount->Header.Size < sizeof MSG_NewAccount && pNewAccount->Version < CLIVER && pNewAccount->Version > CLIVER +3)
				{
					//0042F542
					sprintf(temp, "", CLIVER);
					SendClientMessage(conn, temp);
					pUser[conn].cSock.SendMessageA();
					CloseUser(conn);
					return;
				}

				//0042F58F
				if(pUser[conn].Mode != USER_ACCEPT)
				{
					//0042F5A1
					SendClientMessage(conn, "Login now, wait a moment.");
					CrackLog(conn, "accountlogin");
					pUser[conn].cSock.SendMessageA();
					return;
				}

				//0042F5DC
				pNewAccount->Header.PacketId = _MSG_DBAccountLogin;
				pNewAccount->Header.ClientId = conn;
				sscanf(pNewAccount->Name, "%s", pUser[conn].AccountName);
				strupr(pNewAccount->Name);
				strcpy(pNewAccount->Name, pUser[conn].AccountName);
				int AccountError = CheckFailAccount(pNewAccount->Name);
				if(AccountError >= 3)
				{
					SendClientMessage(conn, ""); //007CB1A8
					pUser[conn].cSock.SendMessageA();
					return;
				}

				//0042F68D
				DBServerSocket.SendOneMessage((char*)pNewAccount, sizeof MSG_NewAccount); //(msg, 0x40)
				if(pNewAccount->Header.Size < sizeof MSG_NewAccount) //0042F6A5
					memset(pUser[conn].Mac, -1, 16);
				else
					memcpy(pUser[conn].Mac, pNewAccount->Keys, 16);

				pUser[conn].Mode = USER_LOGIN;
				pMob[conn].Mode = MOB_EMPTY;
				return;
			}

			case 2: //0x20F _MSG_NewCharacter
			{
				//0042F3D2
				MSG_NewCharacter* pNewCharacter = (MSG_NewCharacter*)msg;
				pNewCharacter->szName[31] = '\0';
				pNewCharacter->szName[30] = '\0';
				if(BASE_CheckValidString(pNewCharacter->szName) == 0)
				{
					//0042F3FE
					SendClientSignal(conn, 0, _MSG_NewCharacterFail);
					return;
				}

				//0042F416
				pNewCharacter->Header.PacketId = _MSG_DBNewCharacter;
				pNewCharacter->Header.ClientId = conn;
				pUser[conn].Mode = USER_CREWAIT;

				DBServerSocket.SendOneMessage((char*)pNewCharacter, sizeof MSG_NewCharacter);
				return;
			}

			case 4: //0x211 _MSG_DeleteCharacter
			{
				//0042F452
				MSG_DeleteCharacter* pDeleteCharacter = (MSG_DeleteCharacter*)msg;
				if(pUser[conn].Mode != USER_SELCHAR)
				{
					//0042F46A
					SendClientMessage(conn, "Deleting Character. wait a moment.");
					//sprintf(temp, "err, delchar not user_selchar %d %d", conn, pUser[conn].Mode);
					//Log(temp, pUser[conn].AccountName, pUser[conn].IP);
					return;
				}

				//0042F4D3
				pDeleteCharacter->Header.PacketId = _MSG_DBDeleteCharacter;
				pDeleteCharacter->Header.ClientId = conn;
				pUser[conn].Mode = USER_CREWAIT;
				DBServerSocket.SendOneMessage((char*)pDeleteCharacter, sizeof MSG_DeleteCharacter);
				return;
			}

			case 6: //0x213 _MSG_CharacterLogin
			{
				//0042F714
				MSG_CharacterLogin* pCharacterLogin = (MSG_CharacterLogin*)msg;
				if(pCharacterLogin->CharIndex < 0 || pCharacterLogin->CharIndex >= 4)
				{
					SendClientMessage(conn, ""); //007CB028
					return;
				}

				//0042F742
				if(pUser[conn].CharList[pCharacterLogin->CharIndex].Experience >= FREEEXP || pUser[conn].CharList[pCharacterLogin->CharIndex].Experience < 999 || BILLING == 2)
				{
					//0042F79B
					if(pUser[conn].Billing <= 1)
					{
						if(pUser[conn].ReqBillSec != 0 && pUser[conn].ReqBillSec < SecCounter - 10)
						{
							pUser[conn].ReqBillSec = 0;
							pUser[conn].Billing = 5;
						}
						else //0042F805
						{
							SendClientMessage(conn, ""); //007CB228
							SendBilling(conn, pUser[conn].AccountName, TRUE, TRUE);
						}

						return;
					}

					//0042F83A
					if(pUser[conn].Billing == 3)
					{
						sprintf(temp, "", FREEEXP); //007CB2A8
						SendClientMessage(conn, temp);
						SendClientSignalParm(conn, 0, _MSG_BillingPage, 0);
						return;
					}

					//0042F88F
					if(pUser[conn].Billing == 4)
					{
						SendClientMessage(conn, ""); //007CB328
						return;
					}
				}

				//0042F8B7
				if(pUser[conn].CharList[pCharacterLogin->CharIndex].Experience >= FREEEXP && pUser[conn].CharList[pCharacterLogin->CharIndex].Experience < 999 && BILLING == 3 && pUser[conn].CharList[pCharacterLogin->CharIndex].Experience >= 1000)
				{
					//0042F936
					if(pUser[conn].Billing <= 1)
						SendClientMessage(conn, ""); //007CB228

					if(pUser[conn].Billing == 3)
					{
						sprintf(temp, "", FREEEXP); //007CB2A8
						SendClientMessage(conn, temp);
					}

					if(pUser[conn].Billing == 4)
						SendClientMessage(conn, ""); //007CB328
				}

				//0042F9B7
				if(BILLING == 2 && pUser[conn].Child == 1 && pUser[conn].CharList[pCharacterLogin->CharIndex].Experience >= FREEEXP && (g_Hour <= 7 || g_Hour >= 23))
				{
					SendClientMessage(conn, ""); //007D0628
					return;
				}
				else
				{
					if(pUser[conn].Mode != USER_SELCHAR)
					{
						//0042FA2E
						SendClientMessage(conn, "Wait a moment.");
						//sprintf(temp, "err, charlogin not user_selchar %d %d", conn, pUser[conn].Mode);
						//Log(temp, pUser[conn].AccountName, pUser[conn].IP);
						return;
					}

					pCharacterLogin->Header.PacketId = _MSG_DBCharacterLogin;
					pCharacterLogin->Header.ClientId = conn;
					pUser[conn].Mode = USER_CHARWAIT;
					pMob[conn].Mode = MOB_USER;
					pMob[conn].MOB.Merchant = 0;
					DBServerSocket.SendOneMessage((char*)pCharacterLogin, sizeof MSG_CharacterLogin);
					return;
				}
			}

			case 8: //0x215 _MSG_CharacterLogout
			{
				//0042FAF6
				CharLogOut(conn);
				return;
			}

			default:
				return;
		}
	}
}