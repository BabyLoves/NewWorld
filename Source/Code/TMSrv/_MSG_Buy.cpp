
#include "ProcessClientMessage.h"
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <random>
#include <ctime>
#include "SendFunc.h"
#include "Functions.h"

void Exec_MSG_Buy(int conn, char* pMsg)
{
	MSG_Buy* m = (MSG_Buy*)pMsg;

	int Size = m->Size;

	if (Size > sizeof(MSG_Buy)) //CONTROLE DE SIZE
	{
		SendClientMessage(conn, "Impossível executar ação7, tente mais tarde. ");
		return;
	}

	if (m->TargetID != 0 && m->TargetID < MAX_USER || m->TargetID >= MAX_MOB) {
		return;
	}

	int invpos = (m->TargetInvenPos % 9);

	if (m->TargetInvenPos < 0 || m->TargetInvenPos > 62 || invpos < 0 || invpos > 9) {
		return;
	}

	if (m->MyInvenPos < 0 || m->MyInvenPos >= MAX_CARRY - 4) {
		return;
	}

	if (m->Coin < 0 || m->Coin > 2000000000) {
		return;
	}

	int TargetID = m->TargetID;
	int TargetInvenPos = m->TargetInvenPos;
	int MyInvenPos = m->MyInvenPos;



	if (pMob[conn].MOB.CurrentScore.Hp == 0 || pUser[conn].Mode != USER_PLAY)
	{
		SendHpMode(conn);
		//AddCrackError(conn, 10, 21);
		return;
	}

	if (pUser[conn].TradeMode)
	{
		RemoveTrade(pUser[conn].Trade.OpponentID);
		RemoveTrade(conn);
		return;
	}

	if (pUser[conn].Trade.OpponentID)
	{
		RemoveTrade(conn);
		return;
	}

	if (pUser[conn].Ingame.DonateBuyItem > 1000)
		TargetID = pUser[conn].Ingame.DonateBuyItem;

	int itemIndex = pMob[TargetID].MOB.Carry[TargetInvenPos].sIndex;

	if (itemIndex <= 0 || itemIndex >= MAX_ITEMLIST) {
		return;
	}

	if (pUser[conn].Ingame.DonateBuyItem <= 0)
	{
		if (TargetID < MAX_USER || TargetID >= MAX_MOB || TargetInvenPos < 0 || TargetInvenPos >= MAX_CARRY || MyInvenPos < 0 || MyInvenPos >= MAX_CARRY)
		{
			if (TargetID < MAX_USER && TargetID == conn)
			{
				if (TargetInvenPos > 27)
					return;

				if (TargetInvenPos < 0)
					return;

				if (TargetInvenPos >= 9)
					TargetInvenPos = 27;

				if (TargetInvenPos == 27)
					TargetInvenPos = 9;

				if (TargetInvenPos < 10)
				{
					auto My = pMob[conn].Rebuy[TargetInvenPos].Item;

					if (My.sIndex <= 0 || My.sIndex >= MAX_ITEMLIST)
						return;

					int szPrice = g_pItemList[My.sIndex].Price;

					int Qnt = 1;

					for (int i = 0; i < 3; i++) {
						if (My.stEffect[i].cEffect == 61)
							Qnt = My.stEffect[i].sValue;
					}

					szPrice = szPrice * Qnt;

					if (szPrice > pMob[conn].MOB.Coin)
					{
						SendClientMessage(conn, g_pMessageStringTable[_NN_Havent_Money_So_Much]);

						return;
					}

					if (PutItem(conn, &My))
					{
						memset(&pMob[conn].Rebuy[TargetInvenPos].Item, 0, sizeof(STRUCT_ITEM));
						pMob[conn].Rebuy[TargetInvenPos].Price = 0;
						pMob[conn].Rebuy[TargetInvenPos].Ticks = 0;

						SendRecycle(conn);

						pMob[conn].MOB.Coin -= szPrice;

						SendEtc(conn);
					}
				}
				return;
			}
		}
	}

	if (pUser[conn].Ingame.CanBuy == 0) {
		return;
	}

	if (pUser[conn].Ingame.DonateBuyItem <= 0 && pMob[TargetID].MOB.Merchant != 1)
	{
		SendClientMessage(conn, g_pMessageStringTable[_NN_Only_Merchant_Sells]);
		return;
	}
	if (pUser[conn].Ingame.DonateBuyItem <= 0)
	{

		if (!GetInHalf(conn, TargetID))
		{
			SendClientSignal(conn, ESCENE_FIELD, _MSG_CloseShop);
			return;
		}
	}

	int pos = 0;
	int i = 0;
	int amount = 0;
	int Loop = 30;


	STRUCT_ITEM* ItemMob = &pMob[TargetID].MOB.Carry[TargetInvenPos];
	unsigned int Donate = BASE_GetItemAbility(ItemMob, EF_DONATE);
	unsigned int Honra = BASE_GetItemAbility(ItemMob, EF_HONRA);


	// SISTEMAS DE BUY
	/*if (strcmp(pMob[TargetID].MOB.MobName, "Jephi") == 0) {
		NewJephi(conn, TargetID, TargetInvenPos, itemIndex);
		return;
	}*/

	if (strcmp(pMob[TargetID].MOB.MobName, "Armas F") == 0 || strcmp(pMob[TargetID].MOB.MobName, "Sets F") == 0 ||
		strcmp(pMob[TargetID].MOB.MobName, "Refinaveis F") == 0 || strcmp(pMob[TargetID].MOB.MobName, "Quests F") == 0) {
		FiltroDrop(conn, ItemMob->sIndex);
		return;
	}

	if (strcmp(pMob[TargetID].MOB.MobName, "Thorin") == 0) //npc pvp armia batalha real
	{
		if (itemIndex == 5661)// ID DO ITEM DA LOJA
		{
			if (pMob[conn].extra.ClassMaster > MORTAL)
			{
				SendClientMessage(conn, "Quest apenas para Morais.");
				return;
			}

			time_t rawnow = time(NULL);
			struct tm now;
			localtime_s(&now, &rawnow);

			for (int i = 0; i < 20; i++) // i = maximo de player na batalha = 20
			{
				if (p_BatalhaReal.Members[i].Id == conn && strcmp(p_BatalhaReal.Members[i].Name, pMob[conn].MOB.MobName) == 0 && p_BatalhaReal.start == false)
				{
					SendSay(itemIndex, strFmt("Aguarde [%d] minutos para o início da batalha.", 5 - now.tm_min));
					return;
				}

			}

			if (pMob[conn].Leader || pMob[conn].Leader == -1)
			{
				SendClientMessage(conn, "Não é permitido registro em grupo.");
				return;
			}
			int i = 0;
			if (now.tm_wday > 0 && now.tm_wday < 7)
			{
				if (now.tm_min <= 5)
				{
					if (p_BatalhaReal.NumMembers < 20)
					{
						p_BatalhaReal.NumMembers += 1;

						for (int i = 1; i < MAX_USER; i++)
						{
							if (pUser[i].Mode != USER_PLAY) continue;

							
							snprintf(temp, sizeof(temp), "[%s] Registrou-se na Batalha Real - Vagas [0%d/20].", pMob[conn].MOB.MobName, p_BatalhaReal.NumMembers);
							SendSpkMsg(i, temp, TNColor::Speak, false);
						}
						int Num;

						for (Num = 0; Num < 20; Num++)//Numero de Vagas Disponiveis
						{
							if (p_BatalhaReal.Members[Num].Id == 0x0)
							{
								p_BatalhaReal.Members[Num].Id = conn;
								memmove_s(&p_BatalhaReal.Members[Num].Name, 16, &pMob[conn].MOB.MobName, 16);
								break;
							}
						}
						return;
					}
					else
					{
						SendClientMessage(conn, "Limite de jogadores foi atingido. Desculpe.");
						return;
					}
				}
				else
				{
					SendClientMessage(conn, "O registro é permitido de segunda a sábado do minuto 0 ao 5");
					return;
				}

			}
			else
			{
				SendClientMessage(conn, "Não é possível batalhar nos fins de semana.");
				return;
			}
			return;
		}
	}


	/* Donate funciona puxando o id da gener do npc */
	if (Donate)
	{
		/*SendClientMessage(conn, "A compra de itens donate será liberado no sábado 12h");
		return;*/

		if (Donate > pUser[conn].Donate)
		{
			SendClientMessage(conn, strFmt(g_pMessageStringTable[_DN_NeedDonate], Donate));
			return;
		}

		if (pUser[conn].Lasclick != itemIndex)
		{
			pUser[conn].Lasclick = itemIndex;
			SendClientMessage(conn, strFmt("Deseja realmente comprar [ %s ] por [ %d ] Donate ?", g_pItemList[itemIndex].Name, Donate));
			return;
		}

		if (itemIndex == 0)
		{
			SystemLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, "err,buy request null item from shop donate - MSG_BUY");
			return;
		}

		if (pMob[conn].MOB.Carry[m->MyInvenPos].sIndex != 0)
		{
			SendItem(conn, ITEM_PLACE_CARRY, m->MyInvenPos, &pMob[conn].MOB.Carry[m->MyInvenPos]);
			return;
		}

		int pos = 0;

		for (pos = 0; pos < pMob[conn].MaxCarry && pos < MAX_CARRY; pos++)
		{
			if (pMob[conn].MOB.Carry[pos].sIndex == 0)
				break;
		}

		if (pos >= 0 && pos < pMob[conn].MaxCarry && pos < MAX_CARRY)
		{
			pUser[conn].Donate -= Donate;
			SendEtc(conn);
			UpdateDonate(conn);

			SendEtc(conn);
			PutItem(conn, ItemMob);
			SendCarry(conn);
			SaveUser(conn, 0);
		}

		else
		{
			SendClientMessage(conn, g_pMessageStringTable[_NN_You_Have_No_Space_To_Trade]);
			return;
		}

		SendClientMessage(conn, strFmt("Comprou o item [ %s ] por [ %d] restam [ %d ] de Donate", g_pItemList[itemIndex].Name, Donate, pUser[conn].Donate));
		
		snprintf(temp, sizeof(temp), "%s comprou o item %s por %d donate e restou %d de Donate", pMob[conn].MOB.MobName, g_pItemList[itemIndex].Name, Donate, pUser[conn].Donate);
		ItemLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, temp);
		return;
	}

	if (Honra)
	{
		if (Honra > pUser[conn].Honra)
		{
			SendClientMessage(conn, "Honra Insuficiente!");
			return;
		}

		if (itemIndex == 0)
		{
			SystemLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, "err,buy request null item from shop honra - MSG_BUY");
			return;
		}

		if (pMob[conn].MOB.Carry[m->MyInvenPos].sIndex != 0)
		{
			SendItem(conn, ITEM_PLACE_CARRY, m->MyInvenPos, &pMob[conn].MOB.Carry[m->MyInvenPos]);
			return;
		}

		int pos = 0;

		for (pos = 0; pos < pMob[conn].MaxCarry && pos < MAX_CARRY; pos++)
		{
			if (pMob[conn].MOB.Carry[pos].sIndex == 0)
				break;
		}

		if (pos >= 0 && pos < pMob[conn].MaxCarry && pos < MAX_CARRY)
		{

			pUser[conn].Honra -= Honra;
			SendEtc(conn);

			int Eff = ItemMob->stEffect[1].cEffect;
			int Qnt = ItemMob->stEffect[1].cValue;

			STRUCT_ITEM Item;
			memset(&Item, 0, sizeof(Item));

			Item.sIndex = ItemMob->sIndex;
			Item.stEffect[0].cEffect = ItemMob->stEffect[0].cEffect;
			Item.stEffect[0].cValue = ItemMob->stEffect[0].cValue;
			Item.stEffect[1].cEffect = ItemMob->stEffect[1].cEffect;
			Item.stEffect[1].cValue = ItemMob->stEffect[1].cValue;
			Item.stEffect[2].cEffect = ItemMob->stEffect[2].cEffect;
			Item.stEffect[2].cValue = ItemMob->stEffect[2].cValue;

			if (Item.stEffect[0].cEffect == 92) {
				Item.stEffect[0].cEffect = 0;
				Item.stEffect[0].cValue = 0;
			}
			if (Item.stEffect[1].cEffect == 92) {
				Item.stEffect[1].cEffect = 0;
				Item.stEffect[1].cValue = 0;
			}
			if (Item.stEffect[2].cEffect == 92) {
				Item.stEffect[2].cEffect = 0;
				Item.stEffect[2].cValue = 0;
			}

			if (Eff == 61 && (pMob[conn].MOB.Equip[13].sIndex == 3901 || pMob[conn].MOB.Equip[13].sIndex == 3902))
			{
				while (Qnt >= 1) {
					SendItemagrupar(conn, ItemMob->sIndex);
					Qnt -= 1;
				}
			}
			else
				PutItem(conn, &Item);

			SendCarry(conn);
			SaveUser(conn, 0);
		}

		else
		{
			SendClientMessage(conn, g_pMessageStringTable[_NN_You_Have_No_Space_To_Trade]);
			return;
		}
		SendClientMessage(conn, strFmt("Comprou o item [ %s ] por [ %d] restam [ %d ] de Honra", g_pItemList[itemIndex].Name, Honra, pUser[conn].Honra));

		
		snprintf(temp, sizeof(temp), "%s comprou o item %s por %d honra e restou %d de Honra", pMob[conn].MOB.MobName, g_pItemList[itemIndex].Name, Honra, pUser[conn].Honra);
		ItemLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, temp);

		return;
	}

	int Price = g_pItemList[itemIndex].Price;

	int Qnt = 1;

	for (int i = 0; i < 3; i++) {
		if (pMob[TargetID].MOB.Carry[TargetInvenPos].stEffect[i].cEffect == 61)
			Qnt = pMob[TargetID].MOB.Carry[TargetInvenPos].stEffect[i].cValue;
	}

	Price = Price * Qnt;


	int Price2 = Price;
	int Village = BASE_GetVillage(pMob[TargetID].TargetX, pMob[TargetID].TargetY);
	int CityTax = g_pGuildZone[Village].CityTax;

	if (Village < 0 || Village >= 5 || CityTax <= 0 || CityTax >= 30)
		goto LABEL_BUY1;

	if (Price < 100000)
		Price += Price * CityTax / 100;

	else
		Price += Price * CityTax / 100;

	if (Price < 0)
		return;

	int GuildTax = (Price - Price2) / 2;
LABEL_BUY1:

	int bPrice = Price;
	int Desconto = 0;
	int TargetVillage = BASE_GetVillage(pMob[TargetID].TargetX, pMob[TargetID].TargetY);
	int Guild = pMob[conn].MOB.Guild;

	if (Price <= 1999999999 && TargetVillage >= 0 && TargetVillage < 5 && Guild > 0 && g_pGuildZone[TargetVillage].ChargeGuild == Guild)
	{
		Desconto = 30;
		Price = 7 * Price / 10;
	}

	if (Price <= 1999999999 && !Desconto && pMob[conn].MOB.Class == 3 && pMob[conn].MOB.LearnedSkill & 0x800)
	{
		int special = (pMob[conn].MOB.CurrentScore.Special[2] / 10) + 6;

		if ((pMob[conn].MOB.CurrentScore.Special[2] / 10) + 6 >= 26)
			special = 26;

		Desconto = special;
		special /= 2;

	}

	if (Price > pMob[conn].MOB.Coin)
	{
		SendClientMessage(conn, g_pMessageStringTable[_NN_Not_Enough_Money]);
		return;
	}

	if (itemIndex == 0)
	{
		return;
	}

	if (pMob[conn].MOB.Carry[m->MyInvenPos].sIndex != 0)
	{
		SendItem(conn, ITEM_PLACE_CARRY, m->MyInvenPos, &pMob[conn].MOB.Carry[m->MyInvenPos]);
		return;
	}

	if (itemIndex == 508 || itemIndex == 509 || itemIndex == 446 || itemIndex >= 526 && itemIndex <= 531)
	{
		if (ServerIndex == -1)
		{
			return;
		}

		if (!GuildCounter)
		{
			return;
		}

		if (itemIndex == 508 || itemIndex == 446 || itemIndex >= 526 && itemIndex <= 531)
		{
			if (!pMob[conn].MOB.GuildLevel)
			{
				SendClientMessage(conn, g_pMessageStringTable[114]);
				return;
			}
			if (pMob[conn].MOB.GuildLevel < 2 && itemIndex >= 526 && itemIndex <= 531)
			{
				SendClientMessage(conn, g_pMessageStringTable[114]);
				return;
			}
			ItemMob->stEffect[0].cEffect = 56;
			ItemMob->stEffect[0].cValue = Guild;
			ItemMob->stEffect[1].cEffect = 57;
			ItemMob->stEffect[1].cValue = Guild;

			if (itemIndex == 508)
			{
				int sub = BASE_GetSubGuild(pMob[conn].MOB.Equip[12].sIndex);

				ItemMob->stEffect[2].cEffect = 85;
				ItemMob->stEffect[2].cValue = sub;

				if (sub >= 1 && sub <= 3)
					ItemMob->sIndex = sub + 531;
			}
		}

		if (itemIndex == 509)
		{
			ItemMob->stEffect[0].cEffect = 56;
			ItemMob->stEffect[0].cValue = (GuildCounter + (ServerIndex << 12)) >> 8;

			ItemMob->stEffect[1].cEffect = 57;
			ItemMob->stEffect[1].cValue = GuildCounter;

			ItemMob->stEffect[2].cEffect = 59;
			ItemMob->stEffect[2].cValue = rand();

			int GCount = GuildCounter + (ServerIndex << 12);

			GuildCounter++;

			if (GuildCounter >= 4096)
			{
				GuildCounter = 2048;
			}
			CReadFiles::WriteGuild();
		}
	}

	if (itemIndex >= 2300 && itemIndex < 2330)
	{
		ItemMob->stEffect[1].cEffect = EF_INCUBATE;
		ItemMob->stEffect[1].cValue = (rand() % 7 + 1);
	}


	if (Price >= 0)
	{
		int x = 0;

		for (x = 0; x < MAX_MOB_MERC; x++)
		{
			//Verifica se o vendedor é um mob mercador especial.
			if (pMob[TargetID].GenerateIndex == pMobMerc[x].GenerateIndex)
				break;
		}

		if (x != MAX_MOB_MERC)
		{//O Vendedor é um mob mercador especial, portanto ele verifica se ainda possui unidades daquele item 
		 //se tiver ele diminui do stock caso contrário ele avisa que não tem.
			if (pMobMerc[x].Stock[TargetInvenPos] == 0)
			{
				SendClientMessage(conn, g_pMessageStringTable[_NN_NOSTOCK]);
				return;
			}
			pMobMerc[x].Stock[TargetInvenPos]--;
		}

		if (TargetVillage >= 0 && TargetVillage < 5 && CityTax > 0 && CityTax < 30)
		{
			if (GuildImpostoID[TargetVillage] >= MAX_USER && GuildImpostoID[TargetVillage] < MAX_MOB && pMob[GuildImpostoID[TargetVillage]].Mode != USER_EMPTY && pMob[GuildImpostoID[TargetVillage]].MOB.Guild == g_pGuildZone[TargetVillage].ChargeGuild)
			{
				if (pMob[GuildImpostoID[TargetVillage]].MOB.Exp < 200000000000)
					pMob[GuildImpostoID[TargetVillage]].MOB.Exp += GuildTax / 2;


			}
			if (GuildImpostoID[4] >= MAX_USER && GuildImpostoID[4] < MAX_MOB && GuildTax > 0 && pMob[GuildImpostoID[4]].Mode != USER_EMPTY && pMob[GuildImpostoID[4]].MOB.Guild == g_pGuildZone[4].ChargeGuild)
			{
				if (pMob[GuildImpostoID[4]].MOB.Exp < 200000000000)
					pMob[GuildImpostoID[4]].MOB.Exp += GuildTax;

			}
		}

		if (MyInvenPos >= 0 && MyInvenPos < pMob[conn].MaxCarry && MyInvenPos < MAX_CARRY)
			pMob[conn].MOB.Coin -= Price;

		m->Coin = pMob[conn].MOB.Coin;

		m->ID = ESCENE_FIELD;

		int Size = m->Size;

		if (Size > sizeof(MSG_Buy))
		{
			m->Size = 0;
			return;
		}
		if (!pUser[conn].cSock.AddMessage((char*)m, m->Size))
			CloseUser(conn);

		SendEtc(conn);
	DonateBuy:

		if (MyInvenPos >= 0 && MyInvenPos < pMob[conn].MaxCarry && MyInvenPos < MAX_CARRY)
		{
			memmove_s(&pMob[conn].MOB.Carry[MyInvenPos], sizeof(STRUCT_ITEM), ItemMob, sizeof(STRUCT_ITEM));

			//PutItem(conn, ItemMob);

			char tmplog[2048];
			BASE_GetItemCode(ItemMob, tmplog);


			SendItem(conn, ITEM_PLACE_CARRY, m->MyInvenPos, &pMob[conn].MOB.Carry[m->MyInvenPos]);
		}
		else
		{
			SendClientMessage(conn, g_pMessageStringTable[_NN_You_Have_No_Space_To_Trade]);
			return;
		}

		if (FREEEXP == -2)
		{
			SendSay(TargetID, strFmt("%s base:%d tax:%d(%d%%) discount:%d(%d%%)", g_pItemList[itemIndex].Name, Price2, bPrice, CityTax, Price, Desconto));
		}

		if (itemIndex == 787 || itemIndex == 481)
		{
			pMob[TargetID].PotionCount++;

			if (pMob[TargetID].PotionCount > POTIONCOUNT)
				DeleteMob(TargetID, 3);
		}
		if (pMob[TargetID].MOB.Equip[0].sIndex == 259 || pMob[TargetID].MOB.Equip[0].sIndex == 230)
			DeleteMob(TargetID, 3);
	}
	else
		SystemLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, "err,MSG_ReqBuy  <><><> MINUS <><><>");


}