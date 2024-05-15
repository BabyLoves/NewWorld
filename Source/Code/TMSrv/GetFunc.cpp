
#include <Windows.h>

#include "..\Basedef.h"
#include "..\ItemEffect.h"
#include "Language.h"

#include "Server.h"
#include "GetFunc.h"
#include "CMob.h"
#include "SendFunc.h"
#include "CCubo.h"

extern STRUCT_ITEMLIST g_pItemList[MAX_ITEMLIST];


int ReadAdminList(char* macAddress)
{
	FILE* arq = NULL;
	fopen_s(&arq, "../../Common/AdminList.txt", "r");

	if (!arq)
	{
		MessageBoxA(0, "Arquivo não encontrado", "../../Common/AdminList.txt", 0);
		ExitProcess(1);
	}

	char line[100];
	memset(&line, 0, 100);

	char mac[25];
	memset(&mac, 0, 25);

	while ((fscanf(arq, "%[^\n]", line)) != EOF)
	{
		fgetc(arq);
		sscanf(line, "%s", &mac);

		if (!strcmp(mac, macAddress))
		{
			fclose(arq);
			return 1;
		}
	}

	fclose(arq);
	return -1;
}

int GetMatchCombine(STRUCT_ITEM* item)
{
	int target = item[0].sIndex;

	for (int i = 0; i < MAX_COMBINE; i++)
	{
		if (item[i].sIndex == 747)
			return 0;
	}

	if (target <= 0 || target >= MAX_ITEMLIST)
		return 0;

	int	stone = item[1].sIndex;

	if (stone <= 0 || stone >= MAX_ITEMLIST)
		return 0;

	if (g_pItemList[target].nUnique < 41 || g_pItemList[target].nUnique > 49)
		return 0;

	if (g_pItemList[target].Extra <= 0)
		return 0;

	if (BASE_GetItemAbility(&item[0], EF_MOBTYPE) == 3)
		return 0;

	if ((item[1].sIndex >= 2441 && item[1].sIndex <= 2444) && item[1].stEffect[0].cEffect == 61 && item[1].stEffect[0].cValue > 1)
		return 0;

	int rate = 10;
	for (int j = 2; j < MAX_COMBINE; j++)
	{
		int idx = item[j].sIndex;

		if (idx <= 0 || idx >= MAX_ITEMLIST)
			continue;

		int eq = BASE_GetItemAbility(&item[j], EF_POS);

		if (eq == 0)
			return 0;

		int il1 = BASE_GetItemAbility(&item[0], EF_ITEMLEVEL);
		int il2 = (BASE_GetItemAbility(&item[j], EF_ITEMLEVEL));

		if (il2 <= 3 || il1 <= 3)
			return 0;

		int	sa = BASE_GetItemSanc(&item[j]);

		if (sa == 7)
		{
			rate = rate + g_pAnctChance[0];

			continue;
		}
		if (sa == 8)
		{
			rate = rate + g_pAnctChance[1];

			continue;
		}
		if (sa == 9)
		{
			rate = rate + g_pAnctChance[2];

			continue;
		}

		return 0;
	}

	return rate;
}

int GetMatchCombineDedekinto(STRUCT_ITEM* Item)
{
	int rate = 0;

	for (int i = 0; i < MAX_COMBINE; i++)
	{
		if (Item[i].sIndex == 747)
			return 0;
	}

	if (Item[0].sIndex < 0 || Item[0].sIndex >= MAX_ITEMLIST)
		return 0;

	if (Item[1].sIndex < 0 || Item[1].sIndex >= MAX_ITEMLIST)
		return 0;

	if (Item[2].sIndex < 0 || Item[2].sIndex >= MAX_ITEMLIST)
		return 0;

	if (Item[3].sIndex < 0 || Item[3].sIndex >= MAX_ITEMLIST)
		return 0;

	if (Item[4].sIndex < 0 || Item[4].sIndex >= MAX_ITEMLIST)
		return 0;

	if (Item[5].sIndex < 0 || Item[5].sIndex >= MAX_ITEMLIST)
		return 0;

	if (Item[6].sIndex < 0 || Item[6].sIndex >= MAX_ITEMLIST)
		return 0;

	if (Item[7].sIndex < 0 || Item[7].sIndex >= MAX_ITEMLIST)
		return 0;

	if (Item[0].sIndex == 673 && Item[1].sIndex == 674 && Item[2].sIndex == 675 && Item[3].sIndex == 676 && Item[4].sIndex == 677 && Item[5].sIndex == 770)
		rate = 1; //Criação de Pedra Amunra

	else if (Item[0].sIndex == 677 && Item[1].sIndex == 677 && Item[2].sIndex == 678 && Item[3].sIndex == 678)
		rate = 2; //Proteção Divina



	return rate;
}

int GetMatchCombineEhre(STRUCT_ITEM* Item)
{
	int rate = 0;

	for (int i = 0; i < MAX_COMBINE; i++)
	{
		if (Item[i].sIndex == 747)
			return 0;
	}

	if (Item[0].sIndex < 0 || Item[0].sIndex >= MAX_ITEMLIST)
		return 0;

	if (Item[1].sIndex < 0 || Item[1].sIndex >= MAX_ITEMLIST)
		return 0;

	if (Item[2].sIndex < 0 || Item[2].sIndex >= MAX_ITEMLIST)
		return 0;

	if (Item[3].sIndex < 0 || Item[3].sIndex >= MAX_ITEMLIST)
		return 0;

	if (Item[4].sIndex < 0 || Item[4].sIndex >= MAX_ITEMLIST)
		return 0;

	if (Item[5].sIndex < 0 || Item[5].sIndex >= MAX_ITEMLIST)
		return 0;

	if (Item[6].sIndex < 0 || Item[6].sIndex >= MAX_ITEMLIST)
		return 0;

	if (Item[7].sIndex < 0 || Item[7].sIndex >= MAX_ITEMLIST)
		return 0;

	if (Item[0].sIndex == 697 && Item[1].sIndex == 697 && BASE_GetItemSanc(&Item[2]) >= 9 && Item[2].sIndex != 3338)
		rate = 1;//Pacote Oriharucon

	else if (Item[0].sIndex >= 5110 && Item[0].sIndex <= 5133 && Item[1].sIndex >= 5110 && Item[1].sIndex <= 5133 && Item[2].sIndex == 413 && BASE_GetItemAmount(&Item[2]) >= 10)
		rate = 2;//Pedra Misteriosa

	else if (Item[0].sIndex >= 661 && Item[0].sIndex <= 663 && Item[1].sIndex >= 661 && Item[1].sIndex <= 663 && Item[2].sIndex == 633 && BASE_GetItemSanc(&Item[2]) >= 9)
		rate = 3;//Pedra espiritual

	else if (Item[0].sIndex >= 661 && Item[0].sIndex <= 663 && Item[1].sIndex >= 661 && Item[1].sIndex <= 663 && Item[2].sIndex == 3464 && BASE_GetItemSanc(&Item[2]) >= 9)
		rate = 4;//Pedra Amunrá

	else if (Item[0].sIndex == 697 && Item[1].sIndex == 697 && Item[2].sIndex == 3338 && BASE_GetItemSanc(&Item[2]) <= 8)
		rate = 5;//Refinação abençoada Purificada

	else if (Item[0].sIndex >= 2360 && Item[0].sIndex <= 2389 && Item[1].sIndex >= 4190 && Item[1].sIndex <= 4199)
		rate = 6;//Traje montaria

	else if (Item[0].sIndex >= 2360 && Item[0].sIndex <= 2389 && Item[1].sIndex == 4899)
		rate = 7;//Restaurar Traje montaria

	else if (Item[0].sIndex >= 2441 && Item[0].sIndex <= 2444 && Item[1].sIndex >= 2441 && Item[1].sIndex <= 2444 && Item[2].sIndex >= 2441 && Item[2].sIndex <= 2444)
		rate = 8;//Soul

	else if (Item[0].sIndex == 5643 && Item[1].sIndex == 5643 && Item[2].sIndex == 5643 && Item[3].sIndex == 5643)
		rate = 9; //brinco

	else if (Item[0].sIndex == 5643 && Item[1].sIndex == 5643 && Item[2].sIndex == 5643 && Item[3].sIndex == 5643)
		rate = 10; //brinco

	else if (Item[0].sIndex == 5643 && Item[1].sIndex == 5643 && Item[2].sIndex == 5643 && Item[3].sIndex == 5643)
		rate = 11; //brinco

	else if (Item[0].sIndex == 5643 && Item[1].sIndex == 5643 && Item[2].sIndex == 5643 && Item[3].sIndex == 5643)
		rate = 12; //brinco

	else if (Item[0].sIndex == 5643 && Item[1].sIndex == 5643 && Item[2].sIndex == 5643 && Item[3].sIndex == 5643 && Item[4].sIndex == 5643 && Item[5].sIndex == 5643 && Item[6].sIndex == 5643 && Item[7].sIndex == 5643)
		rate = 13; //brinco

	return rate;
}

int GetMatchCombineTiny(STRUCT_ITEM* Item)
{
	for (int i = 0; i < MAX_COMBINE; i++)
	{
		if (Item[i].sIndex == 747)
			return 0;
	}

	if (Item[0].sIndex <= 0 || Item[0].sIndex >= MAX_ITEMLIST)
		return 0;

	if (Item[1].sIndex <= 0 || Item[1].sIndex >= MAX_ITEMLIST)
		return 0;

	if (Item[2].sIndex <= 0 || Item[2].sIndex >= MAX_ITEMLIST)
		return 0;

	if (BASE_GetItemAbility(&Item[0], EF_MOBTYPE) != ARCH)
		return 0;

	if (g_pItemList[Item[0].sIndex].Grade < 5 || g_pItemList[Item[0].sIndex].Grade > 8)
		return 0;

	//if (BASE_GetItemAbility(&Item[1], EF_ITEMTYPE) == 1)
	//	return 0;

	// block armas C
	if (Item[1].sIndex >= 2511 && Item[1].sIndex <= 2542
		|| Item[1].sIndex >= 2571 && Item[1].sIndex <= 2602
		|| Item[1].sIndex >= 2811 && Item[1].sIndex <= 2842
		|| Item[1].sIndex >= 2851 && Item[1].sIndex <= 2854
		|| Item[1].sIndex >= 2631 && Item[1].sIndex <= 2662
		|| Item[1].sIndex >= 2691 && Item[1].sIndex <= 2722
		|| Item[1].sIndex >= 2871 && Item[1].sIndex <= 2886
		|| Item[1].sIndex >= 2471 && Item[1].sIndex <= 2482
		|| Item[1].sIndex >= 2911 && Item[1].sIndex <= 2926
		|| Item[1].sIndex >= 2751 && Item[1].sIndex <= 2782)
		return 0;

	if (g_pItemList[Item[1].sIndex].Grade < 5 || g_pItemList[Item[1].sIndex].Grade > 8)
		return 0;

	if (BASE_GetItemAbility(&Item[2], EF_ITEMTYPE) == 1)
		return 0;

	if (g_pItemList[Item[0].sIndex].nPos != g_pItemList[Item[1].sIndex].nPos)
		return 0;

	if (g_pItemList[Item[0].sIndex].nPos != 64 && g_pItemList[Item[0].sIndex].nPos != 192)
		return 0;

	if (BASE_GetItemSanc(&Item[0]) < 9)
		return 0;

	if (BASE_GetItemSanc(&Item[1]) > 237)
		return 0;

	if (BASE_GetItemSanc(&Item[2]) < 9)
		return 0;

	return g_pTinyBase + (BASE_GetItemAbility(&Item[1], EF_ITEMLEVEL) * 5);
}

int GetMatchNovoCompositor(STRUCT_ITEM* Item)
{
	for (int i = 0; i < MAX_COMBINE; i++)
	{
		if (Item[i].sIndex == 747)
			return 0;
	}

	if (Item[0].sIndex < 0 || Item[0].sIndex >= MAX_ITEMLIST)
		return 0;

	if (Item[1].sIndex < 0 || Item[1].sIndex >= MAX_ITEMLIST)
		return 0;

	if (Item[2].sIndex < 0 || Item[2].sIndex >= MAX_ITEMLIST)
		return 0;

	if (Item[3].sIndex < 0 || Item[3].sIndex >= MAX_ITEMLIST)
		return 0;

	if (Item[4].sIndex < 0 || Item[4].sIndex >= MAX_ITEMLIST)
		return 0;

	if (Item[5].sIndex < 0 || Item[5].sIndex >= MAX_ITEMLIST)
		return 0;

	if (Item[6].sIndex < 0 || Item[6].sIndex >= MAX_ITEMLIST)
		return 0;

	int rate = 0;

	for (int i = 0; i < 3; i++) {
		if (Item[0].stEffect[i].cEffect == 69) {
			if (Item[2].sIndex != 662 || Item[3].sIndex != 662 || Item[4].sIndex != 662 || Item[5].sIndex != 662)
				return 0;
		}
		if (Item[0].stEffect[i].cEffect == 70) {
			if (Item[2].sIndex != 661 || Item[3].sIndex != 661 || Item[4].sIndex != 661 || Item[5].sIndex != 661)
				return 0;
		}
	}

	if (Item[2].sIndex != Item[3].sIndex ||
		Item[2].sIndex != Item[4].sIndex ||
		Item[2].sIndex != Item[5].sIndex ||
		Item[3].sIndex != Item[4].sIndex ||
		Item[3].sIndex != Item[5].sIndex ||
		Item[4].sIndex != Item[5].sIndex)
		return 0;

	if (((Item[0].sIndex >= 591 && Item[0].sIndex <= 595) && BASE_GetItemSanc(&Item[0]) >= 9) && Item[1].sIndex == 5718 &&
		((Item[2].sIndex == 661 || Item[2].sIndex == 662) && BASE_GetItemSanc(&Item[0]) >= 9) &&
		((Item[3].sIndex == 661 || Item[3].sIndex == 662) && BASE_GetItemSanc(&Item[0]) >= 9) &&
		((Item[4].sIndex == 661 || Item[4].sIndex == 662) && BASE_GetItemSanc(&Item[0]) >= 9) &&
		((Item[5].sIndex == 661 || Item[5].sIndex == 662) && BASE_GetItemSanc(&Item[0]) >= 9))
		rate = 1;

	return rate;
}

int GetMatchCombineShany(STRUCT_ITEM* Item)
{
	int rate = 0;
	for (int i = 0; i < MAX_COMBINE; i++)
	{
		if (Item[i].sIndex == 747)
			return 0;
	}

	if (Item[0].sIndex <= 0 || Item[0].sIndex >= MAX_ITEMLIST)
		return 0;

	if (Item[1].sIndex <= 0 || Item[1].sIndex >= MAX_ITEMLIST)
		return 0;

	if (Item[2].sIndex <= 0 || Item[2].sIndex >= MAX_ITEMLIST)
		return 0;

	if (Item[3].sIndex <= 0 || Item[3].sIndex >= MAX_ITEMLIST)
		return 0;

	if (Item[4].sIndex <= 0 || Item[4].sIndex >= MAX_ITEMLIST)
		return 0;

	if (Item[5].sIndex <= 0 || Item[5].sIndex >= MAX_ITEMLIST)
		return 0;

	if (Item[6].sIndex <= 0 || Item[6].sIndex >= MAX_ITEMLIST)
		return 0;

	if (Item[0].sIndex != 540 && Item[0].sIndex != 541 || BASE_GetItemSanc(&Item[0]) < 9)
		return 0;

	if (Item[1].sIndex != 540 && Item[1].sIndex != 541 || BASE_GetItemSanc(&Item[1]) < 9)
		return 0;

	if (Item[2].sIndex != 540 && Item[2].sIndex != 541 && Item[2].sIndex != 633)
		return 0;

	if (Item[3].sIndex != 413 || Item[4].sIndex != 413 || Item[5].sIndex != 413 || Item[6].sIndex != 413)
		return 0;

	return 1;
}

int GetMatchCombineAilyn(STRUCT_ITEM* Item)
{
	for (int i = 0; i < MAX_COMBINE; i++)
	{
		if (Item[i].sIndex == 747)
			return 0;

		if ((Item[i].sIndex >= 2441 && Item[i].sIndex <= 2444) && Item[i].stEffect[0].cEffect == 61 && Item[i].stEffect[0].cValue > 1)
			return 0;
	}

	if (Item[0].sIndex <= 0 || Item[0].sIndex >= MAX_ITEMLIST)
		return 0;

	if (Item[1].sIndex <= 0 || Item[1].sIndex >= MAX_ITEMLIST)
		return 0;

	if (Item[2].sIndex <= 0 || Item[2].sIndex >= MAX_ITEMLIST)
		return 0;

	if (Item[3].sIndex <= 0 || Item[3].sIndex >= MAX_ITEMLIST)
		return 0;

	if (Item[4].sIndex <= 0 || Item[4].sIndex >= MAX_ITEMLIST)
		return 0;

	if (Item[5].sIndex <= 0 || Item[5].sIndex >= MAX_ITEMLIST)
		return 0;

	if (Item[6].sIndex <= 0 || Item[6].sIndex >= MAX_ITEMLIST)
		return 0;

	if (Item[0].sIndex != Item[1].sIndex)
		return 0;

	if (g_pItemList[Item[0].sIndex].Grade != g_pItemList[Item[1].sIndex].Grade)
		return 0;

	if (Item[2].sIndex != 1774)
		return 0;

	if (Item[2].sIndex == 1774 && Item[2].stEffect[0].cEffect == 61 && Item[2].stEffect[0].cValue > 1)
		return 77;
	int rate = 1;

	if ((g_pItemList[Item[0].sIndex].nPos != 2 && g_pItemList[Item[0].sIndex].nPos != 4 && g_pItemList[Item[0].sIndex].nPos != 8 && g_pItemList[Item[0].sIndex].nPos != 16 && g_pItemList[Item[0].sIndex].nPos != 32 && g_pItemList[Item[0].sIndex].nPos != 64 && g_pItemList[Item[0].sIndex].nPos != 192 && g_pItemList[Item[0].sIndex].nPos != 128))
		return 0;


	for (int i = 3; i < 7; i++)
	{
		if (Item[i].sIndex == 0)
			continue;

		if (Item[3].sIndex != Item[i].sIndex)
			return 0;

		rate += g_pAilynBase;
	}

	return rate;
}

int GetMatchCombineAgatha(STRUCT_ITEM* Item)
{
	if (Item[0].sIndex <= 0 || Item[0].sIndex >= MAX_ITEMLIST)
		return 0;

	if (Item[1].sIndex <= 0 || Item[1].sIndex >= MAX_ITEMLIST)
		return 0;

	if (Item[2].sIndex <= 0 || Item[2].sIndex >= MAX_ITEMLIST)
		return 0;

	if (Item[3].sIndex <= 0 || Item[3].sIndex >= MAX_ITEMLIST)
		return 0;

	if (Item[4].sIndex <= 0 || Item[4].sIndex >= MAX_ITEMLIST)
		return 0;

	if (Item[5].sIndex <= 0 || Item[5].sIndex >= MAX_ITEMLIST)
		return 0;

	int ItemArchPos = g_pItemList[Item[0].sIndex].nPos;
	int ItemMortalPos = g_pItemList[Item[1].sIndex].nPos;

	if (ItemArchPos < 2 || ItemArchPos > 32)
		return 0;

	if (ItemMortalPos < 2 || ItemMortalPos > 32)
		return 0;

	if (BASE_GetItemAbility(&Item[0], EF_MOBTYPE) != ARCH)
		return 0;

	if (BASE_GetItemAbility(&Item[1], EF_ITEMTYPE) != MORTAL && BASE_GetItemAbility(&Item[1], EF_ITEMTYPE) != 0)
		return 0;

	if (BASE_GetItemAbility(&Item[1], EF_ITEMLEVEL) < 4)
		return 0;

	if (g_pItemList[Item[0].sIndex].nPos != g_pItemList[Item[1].sIndex].nPos)
		return 0;

	if (BASE_GetItemSanc(&Item[0]) < 9)
		return 0;

	if (BASE_GetItemSanc(&Item[1]) < 9)
		return 0;

	if (Item[2].sIndex != 3140 || Item[3].sIndex != 3140 || Item[4].sIndex != 3140 || Item[5].sIndex != 3140)
		return 0;

	if (Item[2].sIndex == 3140 && Item[2].stEffect[0].cEffect == 61 && Item[2].stEffect[0].cValue > 1
		|| Item[3].sIndex == 3140 && Item[3].stEffect[0].cEffect == 61 && Item[3].stEffect[0].cValue > 1
		|| Item[4].sIndex == 3140 && Item[4].stEffect[0].cEffect == 61 && Item[4].stEffect[0].cValue > 1
		|| Item[5].sIndex == 3140 && Item[5].stEffect[0].cEffect == 61 && Item[5].stEffect[0].cValue > 1)
		return 77;

	int ItemGrade = g_pItemList[Item[1].sIndex].Grade;
	int ItemLevel = BASE_GetItemAbility(&Item[1], EF_ITEMLEVEL);

	if (ItemLevel == 5 && ItemGrade == 1) {
		ItemGrade = 3;
	}

	return g_pAgathaBase + (ItemGrade * 5) + (ItemLevel == 5 ? 6 : 1);
}

int GetMatchCombineEvent(STRUCT_ITEM* Item)
{
	for (int i = 0; i < MAX_COMBINE; i++)
	{
		if (Item[i].sIndex == 747)
			return 0;
	}

	if (Item[0].sIndex == 480 && Item[1].sIndex == 480 && Item[2].sIndex == 4052)
		return 1;

	if (Item[0].sIndex == 480 && Item[1].sIndex == 480 && Item[2].sIndex == 4054)
		return 2;

	if (Item[0].sIndex == 480 && Item[1].sIndex == 480 && Item[2].sIndex == 480 && Item[3].sIndex == 0)
		return 3;

	if (Item[0].sIndex == 480 && Item[1].sIndex == 480 && Item[2].sIndex == 4051)
		return 4;

	if (Item[0].sIndex == 4052 && Item[1].sIndex == 4051)
		return 5;

	if (Item[0].sIndex == 480 && Item[1].sIndex == 480 && Item[2].sIndex == 480 && Item[3].sIndex == 4053 && (Item[4].sIndex >= 762 && Item[4].sIndex <= 768 && BASE_GetItemSanc(&Item[4]) == 9))
		return 6;

	if (Item[0].sIndex == 480 && Item[1].sIndex == 480 && Item[2].sIndex == 480 && Item[3].sIndex == 4055 && (Item[4].sIndex >= 762 && Item[4].sIndex <= 768 && BASE_GetItemSanc(&Item[4]) == 9))
		return 7;

	if (Item[0].sIndex == 480 && Item[1].sIndex == 480 && Item[2].sIndex == 480 && Item[3].sIndex == 4055)
		return 8;

	return 0;
}

int GetMatchCombineOdin(STRUCT_ITEM* Item)
{
	for (int i = 0; i < MAX_COMBINE; i++)
	{
		if (Item[i].sIndex == 747)
			return 0;
	}

	if (Item[0].sIndex < 0 || Item[0].sIndex >= MAX_ITEMLIST)
		return 0;

	if (Item[1].sIndex < 0 || Item[1].sIndex >= MAX_ITEMLIST)
		return 0;

	if (Item[2].sIndex < 0 || Item[2].sIndex >= MAX_ITEMLIST)
		return 0;

	if (Item[3].sIndex < 0 || Item[3].sIndex >= MAX_ITEMLIST)
		return 0;

	if (Item[4].sIndex < 0 || Item[4].sIndex >= MAX_ITEMLIST)
		return 0;

	if (Item[5].sIndex < 0 || Item[5].sIndex >= MAX_ITEMLIST)
		return 0;

	if (Item[6].sIndex < 0 || Item[6].sIndex >= MAX_ITEMLIST)
		return 0;

	if (Item[7].sIndex < 0 || Item[7].sIndex >= MAX_ITEMLIST)
		return 0;

	if (Item[0].sIndex == g_pItemList[Item[1].sIndex].Extra && BASE_GetItemSanc(&Item[0]) >= 9 && BASE_GetItemSanc(&Item[1]) == REF_15
		&& (Item[2].sIndex == 542 || Item[2].sIndex == 772) && Item[3].sIndex == 5334 && Item[4].sIndex == 5335 && Item[5].sIndex == 5336 && Item[6].sIndex == 5337)
		return 1;//Item celestial

	else if ((Item[0].sIndex == 413 && BASE_GetItemAmount(&Item[0]) >= 10 && Item[1].sIndex == 413 && BASE_GetItemAmount(&Item[1]) >= 10 || Item[0].sIndex == 4043 && Item[1].sIndex == 4043)
		&& BASE_GetItemSanc(&Item[2]) > REF_10 && BASE_GetItemSanc(&Item[2]) <= REF_15 && (Item[3].sIndex >= 5334 && Item[3].sIndex <= 5337 || Item[3].sIndex == 3338) && (Item[4].sIndex >= 5334 && Item[4].sIndex <= 5337 || Item[4].sIndex == 3338)
		&& (Item[5].sIndex >= 5334 && Item[5].sIndex <= 5337 || Item[5].sIndex == 3338) && (Item[6].sIndex >= 5334 && Item[6].sIndex <= 5337 || Item[6].sIndex == 3338) && (g_pItemList[Item[2].sIndex].nPos == 2 || g_pItemList[Item[2].sIndex].nPos == 4 || g_pItemList[Item[2].sIndex].nPos == 8 || g_pItemList[Item[2].sIndex].nPos == 16 || g_pItemList[Item[2].sIndex].nPos == 32 || g_pItemList[Item[2].sIndex].nPos == 64 || g_pItemList[Item[2].sIndex].nPos == 192 || g_pItemList[Item[2].sIndex].nPos == 128))
		return 2;//Ref+12+

	else if (Item[0].sIndex == 413 && Item[1].sIndex == 413 && Item[2].sIndex == 413 && Item[3].sIndex == 413 && Item[4].sIndex == 413 && Item[5].sIndex == 413 && Item[6].sIndex == 413)
		return 3;//Pista de runas

	else if (Item[0].sIndex == 4127 && Item[1].sIndex == 4127 && Item[2].sIndex == 5135 && Item[3].sIndex == 5113 && Item[4].sIndex == 5129 && Item[5].sIndex == 5112 && Item[6].sIndex == 5110)
		return 4;//Level40 Celestial

	else if (Item[0].sIndex == 5125 && Item[1].sIndex == 5115 && Item[2].sIndex == 5111 && Item[3].sIndex == 5112 && Item[4].sIndex == 5120 && Item[5].sIndex == 5128 && Item[6].sIndex == 5119)
		return 5;//Pedra da fúria

	else if (Item[0].sIndex == 5126 && Item[1].sIndex == 5127 && Item[2].sIndex == 5121 && Item[3].sIndex == 5114 && Item[4].sIndex == 5125 && Item[5].sIndex == 5111 && Item[6].sIndex == 5118)
		return 6;//Secreta da Agua

	else if (Item[0].sIndex == 5131 && Item[1].sIndex == 5113 && Item[2].sIndex == 5115 && Item[3].sIndex == 5116 && Item[4].sIndex == 5125 && Item[5].sIndex == 5112 && Item[6].sIndex == 5114)
		return 7;//Secreta da Terra

	else if (Item[0].sIndex == 5110 && Item[1].sIndex == 5124 && Item[2].sIndex == 5117 && Item[3].sIndex == 5129 && Item[4].sIndex == 5114 && Item[5].sIndex == 5125 && Item[6].sIndex == 5128)
		return 8;//Secreta do Sol

	else if (Item[0].sIndex == 5122 && Item[1].sIndex == 5119 && Item[2].sIndex == 5132 && Item[3].sIndex == 5120 && Item[4].sIndex == 5130 && Item[5].sIndex == 5133 && Item[6].sIndex == 5123)
		return 9;//Secreta do Vento

	else if (Item[0].sIndex == 421 && Item[1].sIndex == 422 && Item[2].sIndex == 423 && Item[3].sIndex == 424 && Item[4].sIndex == 425 && Item[5].sIndex == 426 && Item[6].sIndex == 427)
		return 10;//Semente de cristal

	else if (Item[0].sIndex == 4127 && Item[1].sIndex == 4127 && Item[2].sIndex == 5135 && Item[3].sIndex == 413 && Item[4].sIndex == 413 && Item[5].sIndex == 413 && Item[6].sIndex == 413)
		return 11;//Capa

	return 0;
}

int GetMatchCombineAlquimia(STRUCT_ITEM* Item)
{
	for (int i = 0; i < MAX_COMBINE; i++)
	{
		if (Item[i].sIndex == 747)
			return 0;

		if (Item[i].stEffect[0].cEffect == 61 && Item[i].stEffect[0].cValue > 1)
			return 0;

	}
	if (Item[0].sIndex < 0 || Item[0].sIndex >= MAX_ITEMLIST)
		return -1;

	if (Item[1].sIndex < 0 || Item[1].sIndex >= MAX_ITEMLIST)
		return -1;

	if (Item[2].sIndex < 0 || Item[2].sIndex >= MAX_ITEMLIST)
		return -1;

	if (Item[3].sIndex < 0 || Item[3].sIndex >= MAX_ITEMLIST)
		return -1;

	if (Item[4].sIndex < 0 || Item[4].sIndex >= MAX_ITEMLIST)
		return -1;

	if (Item[5].sIndex < 0 || Item[5].sIndex >= MAX_ITEMLIST)
		return -1;

	if (Item[6].sIndex < 0 || Item[6].sIndex >= MAX_ITEMLIST)
		return -1;

	if (Item[7].sIndex < 0 || Item[7].sIndex >= MAX_ITEMLIST)
		return -1;

	if (Item[0].sIndex == 413 && Item[1].sIndex == 2441 && Item[2].sIndex == 2442)
		return 0;//Sagacidade

	if (Item[0].sIndex == 413 && Item[1].sIndex == 2443 && Item[2].sIndex == 2442)
		return 1;//Resistencia

	if (Item[0].sIndex == 4127 && Item[1].sIndex == 4127 && Item[2].sIndex == 4127)
		return 2;//Revelação

	if (Item[0].sIndex == 4127 && Item[1].sIndex == 4127 && Item[2].sIndex == 697)
		return 3;//Recuperação

	if (Item[0].sIndex == 412 && Item[1].sIndex == 2441 && Item[2].sIndex == 2444)
		return 4;//Absorção

	if (Item[0].sIndex == 412 && Item[1].sIndex == 2444 && Item[2].sIndex == 2443)
		return 5;//Proteção	

	if (Item[0].sIndex == 612 && BASE_GetItemSanc(&Item[0]) >= 9 && Item[1].sIndex == 2441 && Item[2].sIndex == 2442)
		return 6;//Poder

	if (Item[0].sIndex == 612 && Item[1].sIndex == 613 && Item[2].sIndex == 614 && Item[3].sIndex == 615)
		return 7;//Armazenagem

	if (Item[0].sIndex == 614 && BASE_GetItemSanc(&Item[0]) >= 9 && Item[1].sIndex == 2443 && Item[2].sIndex == 2444)
		return 8;//Precisão

	if (Item[0].sIndex == 615 && BASE_GetItemSanc(&Item[0]) >= 9 && Item[1].sIndex == 697 && Item[2].sIndex == 697 && Item[3].sIndex == 697)
		return 9;//Magia

	return -1;
}

int GetParryRate(STRUCT_MOB* conn, int attackerdex, int attackerrsv, int attackerparry, int defensordex, int defensorrsv, int defensorparry) // Parry que realmente usa no PVP
{
	int ParryChance = 0, Parry1 = 0, Parry2 = 0, PD = 0, PDFM = 0, ParryFM1 = 0, ParryFM2 = 0;

	if (defensordex >= 5000)
		defensordex = 5000;

	if (attackerdex >= 5000)
		attackerdex = 5000;

	//Destrezas iguais
	if (attackerdex == defensordex || defensordex == attackerdex)
	{
		Parry1 = (attackerdex - defensordex);
		Parry2 = (attackerdex - defensordex);
	}
	else
	{
		//Destreza do attacker e maior do que o do defensor
		if (attackerdex > defensordex) // 10000 x 10 // 5000 x 4000 // 15000 x 4000 // 2000 x 2000
		{
			if (defensordex <= 0)
				defensordex = 1;

			if (attackerdex <= 0)
				attackerdex = 1;

			PD = (attackerdex - defensordex) / 10; // 999 // 100 // 1100 // 

			if (PD <= 0)
				PD = 1; // 999 // 100 // 1100 // 1

			Parry1 = (PD / 100); // 9.99 // 10 // 11 // 1

			if (Parry1 <= 0)
				Parry1 = 1;

			if (defensordex <= 0)
				defensordex = 1;
			// 18
			Parry2 = (PD * 100) / attackerdex;  // 9.99 // 20 // 7,3 // 
			// soma = 19.98 // 30 // 18.3

			if (Parry2 <= 0)
				Parry2 = 1;
		}
		else
		{
			if (attackerdex + 600 > defensordex)
			{
				if (defensordex <= 0)
					defensordex = 1;

				if (attackerdex <= 0)
					attackerdex = 1;

				PD = (attackerdex - defensordex) / 10; // 999 // 100 // 1100 // 

				if (PD <= 0)
					PD = 1; // 999 // 100 // 1100 // 1

				Parry1 = (PD / 100); // 9.99 // 10 // 11 // 1

				if (Parry1 <= 0)
					Parry1 = 1;

				if (defensordex <= 0)
					defensordex = 1;
				// 18
				Parry2 = (PD * 100) / attackerdex;  // 9.99 // 20 // 7,3 // 
				// soma = 19.98 // 30 // 18.3

				if (Parry2 <= 0)
					Parry2 = 1;
			}
			else {
				if (defensordex <= 0) // defensor = 5000 / atk = 1000 
					defensordex = 1;

				if (attackerdex <= 0)
					attackerdex = 1;

				PD = (defensordex - attackerdex); // 4000

				if (PD <= 0)
					PD = 1; // 1

				Parry1 = (PD * 10) / 200; // 200 

				if (Parry1 <= 0)
					Parry1 = 0;

				Parry2 = (140 * defensordex) / attackerdex; // 

				if (Parry2 <= 0)
					Parry2 = 0;
			}
		}
	}

	ParryChance = (Parry1 + Parry2);

	if (attackerrsv & 0x20)
		ParryChance += 50;

	if (attackerrsv & 0x200) //Skill da ht Ligação espectral
		ParryChance -= 20;

	if (defensorrsv & 0x20)
		ParryChance -= 50;

	if (defensorrsv & 0x40)
		ParryChance -= 15;

	if (ParryChance <= 0)
		ParryChance = 1;

	if (ParryChance >= 657)
		ParryChance = 657;

	//SendNotice(strFmt("Chance atual [%d]", ParryChance));  //balanceio de pvp

	return ParryChance;
}

// Original 7556 descompilado
int CGetParryRate(int attackerdex, int attackerrsv, int attackerparry, int defensordex, int defensorrsv, int defensorparry)
{
	int ParryChance = 0, Parry1 = 0, Parry2 = 0, PD = 0, PDFM = 0, ParryFM1 = 0, ParryFM2 = 0;

	//Destrezas iguais
	if (attackerdex == defensordex || defensordex == attackerdex)
	{
		Parry1 = (attackerdex - defensordex);
		Parry2 = (attackerdex - defensordex);
	}
	else
	{
		//Destreza do attacker e maior do que o do defensor
		if (attackerdex > defensordex) // 10000 x 10 // 5000 x 4000 // 15000 x 4000 // 2000 x 2000
		{
			if (defensordex <= 0)
				defensordex = 1;

			if (attackerdex <= 0)
				attackerdex = 1;

			PD = (attackerdex - defensordex) / 10; // 999 // 100 // 1100 // 

			if (PD <= 0)
				PD = 1; // 999 // 100 // 1100 // 1

			Parry1 = (PD / 100); // 9.99 // 10 // 11 // 1

			if (Parry1 <= 0)
				Parry1 = 1;

			if (defensordex <= 0)
				defensordex = 1;
			// 18
			Parry2 = (PD * 100) / attackerdex;  // 9.99 // 20 // 7,3 // 
			// soma = 19.98 // 30 // 18.3

			if (Parry2 <= 0)
				Parry2 = 1;
		}
		else
		{
			if (defensordex <= 0) // defensor = 5000 / atk = 1000 
				defensordex = 1;

			if (attackerdex <= 0)
				attackerdex = 1;

			PD = (defensordex - attackerdex); // 4000

			if (PD <= 0)
				PD = 1; // 1

			Parry1 = (PD * 10) / 200; // 200 

			if (Parry1 <= 0)
				Parry1 = 0;

			Parry2 = (100 * defensordex) / attackerdex; // 

			if (Parry2 <= 0)
				Parry2 = 0;

		}
	}

	if (pMob[attackerdex].MOB.Class != 1)
		ParryChance = (Parry1 + Parry2);

	if (pMob[attackerdex].MOB.Class == 1 || pMob[attackerdex].MOB.Class == 2)
	{
		PDFM = (defensordex - attackerdex);

		if (PDFM <= 0)
			PDFM = 3;

		ParryFM1 = (PDFM * 100) / attackerdex; //33

		if (ParryFM1 <= 0)
			ParryFM1 = 0;

		ParryFM2 = (PDFM / 40); // 33

		ParryChance = (ParryFM1 + ParryFM2);

		if (ParryChance <= 0)
			ParryChance = 1;

		if (ParryChance > 800)
			ParryChance = 800;
	}

	if (attackerrsv & 0x20)
		ParryChance += 50;
	if (attackerrsv & 0x80)
		ParryChance += 50;
	if (attackerrsv & 0x200)
		ParryChance += 50;
	if (defensorrsv & 0x20)
		ParryChance -= 50;
	if (defensorrsv & 0x40)
		ParryChance -= 15;
	if (defensorrsv & 0x80)
		ParryChance -= 50;
	if (defensorrsv & 0x200)
		ParryChance -= 50;

	ParryChance -= attackerparry;
	ParryChance += defensorparry;

	if (attackerdex >= 9000)
		ParryChance = 1;

	if (ParryChance <= 0)
		ParryChance = 1;

	if (ParryChance > 800)
		ParryChance = 800;

	return ParryChance;
}

// W2PP Original
int WGetParryRate(STRUCT_MOB* mob, int add, int attackerdex, int attackrsv)
{
	if (add > 100)
		add = 100;

	if (add < 0)
		add = 0;

	int	targetdex = mob->CurrentScore.Dex;

	if (targetdex > 1000)
		targetdex = 1000;

	int parryrate1 = mob->CurrentScore.Dex - 1000;

	if (parryrate1 < 0)
		parryrate1 = 0;

	if (parryrate1 >= 2000)
		parryrate1 = 2000;

	int parryrate2 = mob->CurrentScore.Dex - 3000;

	if (parryrate2 < 0)
		parryrate2 = 0;

	int parryrate = targetdex / 2 + add + parryrate1 / 4 + parryrate2 / 8 - attackerdex;

	int rsv = attackrsv;

	if (rsv & 0x20)
		parryrate += 100;

	if (rsv & 0x80)
		parryrate += 50;

	if (rsv & 0x200)
		parryrate += 50;

	if (parryrate >= 650)
		parryrate = 650;

	if (parryrate < 1)
		parryrate = 1;

	return parryrate;
}


int GetEmptyAffect(int mob, int type)
{
	for (int i = 1; i < MAX_AFFECT; i++)
	{
		if (pMob[mob].Affect[i].Type == type)
			return i;
	}

	for (int i = 1; i < MAX_AFFECT; i++)
	{
		if (pMob[mob].Affect[i].Type == 0)
			return i;
	}

	return -1;
}

int GetHide(int mob)
{
	if (mob <= 0 || mob >= MAX_USER)
		return FALSE;

	for (int i = 1; i < MAX_AFFECT; i++)
	{
		if (pMob[mob].Affect[i].Type == 28)
			return TRUE;
	}
	return FALSE;
}
int GetInView(int a, int b)
{
	if (pMob[a].TargetX < pMob[b].TargetX - VIEWGRIDX || pMob[a].TargetX > pMob[b].TargetX + VIEWGRIDX ||
		pMob[a].TargetY < pMob[b].TargetY - VIEWGRIDY || pMob[a].TargetY > pMob[b].TargetY + VIEWGRIDY)
		return FALSE;

	return TRUE;
}

int GetInHalf(int a, int b)
{
	if (pMob[a].TargetX < pMob[b].TargetX - HALFGRIDX || pMob[a].TargetX > pMob[b].TargetX + HALFGRIDX ||
		pMob[a].TargetY < pMob[b].TargetY - HALFGRIDY || pMob[a].TargetY > pMob[b].TargetY + HALFGRIDY)
		return FALSE;

	return TRUE;
}

bool GetCuboTeleportPositionN(int conn, int room)
{
	if (conn > MAX_USER)
		return FALSE;

	int Question = CuboN.CurrentQuestion[room];
	bool Answer = CuboN.Answer[Question];

	if (Answer)
	{
		if (pMob[conn].TargetX >= (CuboN.O[room].PosX - 3) && pMob[conn].TargetX <= CuboN.O[room].PosX && pMob[conn].TargetY >= (CuboN.O[room].PosY - 3) && pMob[conn].TargetY <= CuboN.O[room].PosY)
			return TRUE;
		else
			return FALSE;
	}
	else
	{
		if (pMob[conn].TargetX >= (CuboN.X[room].PosX - 3) && pMob[conn].TargetX <= CuboN.X[room].PosX && pMob[conn].TargetY >= (CuboN.X[room].PosY - 3) && pMob[conn].TargetY <= CuboN.X[room].PosY)
			return TRUE;
		else
			return FALSE;
	}

	return FALSE;
}

bool GetCuboTeleportPositionM(int conn, int room)
{
	if (conn > MAX_USER)
		return FALSE;

	int Question = CuboM.CurrentQuestion[room];
	bool Answer = CuboM.Answer[Question];

	if (Answer)
	{
		if (pMob[conn].TargetX >= (CuboM.O[room].PosX - 3) && pMob[conn].TargetX <= CuboM.O[room].PosX && pMob[conn].TargetY >= (CuboM.O[room].PosY - 3) && pMob[conn].TargetY <= CuboM.O[room].PosY)
			return TRUE;
		else
			return FALSE;
	}
	else
	{
		if (pMob[conn].TargetX >= (CuboM.X[room].PosX - 3) && pMob[conn].TargetX <= CuboM.X[room].PosX && pMob[conn].TargetY >= (CuboM.X[room].PosY - 3) && pMob[conn].TargetY <= CuboM.X[room].PosY)
			return TRUE;
		else
			return FALSE;
	}

	return FALSE;
}

bool GetCuboTeleportPositionA(int conn, int room)
{
	if (conn > MAX_USER)
		return FALSE;

	int Question = CuboA.CurrentQuestion[room];
	bool Answer = CuboA.Answer[Question];

	if (Answer)
	{
		if (pMob[conn].TargetX >= (CuboA.O[room].PosX - 3) && pMob[conn].TargetX <= CuboA.O[room].PosX && pMob[conn].TargetY >= (CuboA.O[room].PosY - 3) && pMob[conn].TargetY <= CuboA.O[room].PosY)
			return TRUE;
		else
			return FALSE;
	}
	else
	{
		if (pMob[conn].TargetX >= (CuboA.X[room].PosX - 3) && pMob[conn].TargetX <= CuboA.X[room].PosX && pMob[conn].TargetY >= (CuboA.X[room].PosY - 3) && pMob[conn].TargetY <= CuboA.X[room].PosY)
			return TRUE;
		else
			return FALSE;
	}

	return FALSE;
}

int GetTeleportPosition(int conn, int* x, int* y)
{
	int xv = (*x) & 0xFFFC;
	int yv = (*y) & 0xFFFC;

	int Charge = 0;

	if (xv == 2116 && yv == 2100) // Armia to Noatum	
	{
		*x = 1044 + rand() % 3;
		*y = 1724 + rand() % 3;
		SendMsgExp(conn, "Bem vindo a [Noatum]", TNColor::Default, false);
		Charge = 700;
	}
	else if (xv == 2480 && yv == 1716) // Azran to Noatum
	{
		*x = 1044 + rand() % 3;
		*y = 1716 + rand() % 3;
		SendMsgExp(conn, "Bem vindo a [Noatum]", TNColor::Default, false);
		Charge = 700;
	}
	else if (xv == 2456 && yv == 2016) // Erion to Noatum
	{
		*x = 1044 + rand() % 3;
		*y = 1708 + rand() % 3;
		SendMsgExp(conn, "Bem vindo a [Noatum]", TNColor::Default, false);
		Charge = 700;
	}
	else if (xv == 1044 && yv == 1724) // Noatum to Armia
	{
		*x = 2116 + rand() % 3;
		*y = 2100 + rand() % 3;
		SendMsgExp(conn, "Bem vindo a [Armia]", TNColor::Default, false);
	}
	else if (xv == 1044 && yv == 1716) // Noatum to Azran
	{
		*x = 2480 + rand() % 3;
		*y = 1716 + rand() % 3;
		SendMsgExp(conn, "Bem vindo a [Azran]", TNColor::Default, false);
	}
	else if (xv == 1044 && yv == 1708) // Noatum to Erion
	{
		*x = 2456 + rand() % 3;
		*y = 2016 + rand() % 3;
		SendMsgExp(conn, "Bem vindo a [Erion]", TNColor::Default, false);
	}
	else if (xv == 1048 && yv == 1764) // Noatum guild area to Noatum siege war area
	{
		*x = 1100 + rand() % 3;
		*y = 1712 + rand() % 3;
		SendMsgExp(conn, "Bem vindo a [Noatun War]", TNColor::Default, false);
	}
	else if (xv == 1052 && yv == 1708) // Noatum to Karden
	{
		*x = 3650 + rand() % 3;
		*y = 3110 + rand() % 3;
		SendMsgExp(conn, "Bem vindo a [Karden]", TNColor::Default, false);
	}
	else if (xv == 2140 && yv == 2068) // Armia to Armia Field
	{
		*x = 2588 + rand() % 3;
		*y = 2096 + rand() % 3;
		SendMsgExp(conn, "Bem vindo ao [Campo de Armia]", TNColor::Default, false);
	}
	else if (xv == 2468 && yv == 1716) // Azran to Azran Field, near cape quest
	{
		*x = 2248 + rand() % 3;
		*y = 1556 + rand() % 3;
		SendMsgExp(conn, "Bem vindo ao [Campo de Azran]", TNColor::Default, false);
	}
	else if (xv == 2364 && yv == 2284) // Armia Field to Dungeon 1st Floor
	{
		*x = 144 + rand() % 3;
		*y = 3788 + rand() % 3;
		SendMsgExp(conn, "Bem vindo ao [Dungeon 1 Andar]", TNColor::Default, false);
	}
	else if (xv == 144 && yv == 3788) // Dungeon 1st floor to Armia Field
	{
		*x = 2364 + rand() % 3;
		*y = 2284 + rand() % 3;
		SendMsgExp(conn, "Bem vindo ao [Campo de Armia]", TNColor::Default, false);
	}
	else if (xv == 2668 && yv == 2156) // Armia Field to Dungeon 1st Floor (other locations)
	{
		*x = 148 + rand() % 2;
		*y = 3774 + rand() % 2;
		SendMsgExp(conn, "Bem vindo ao [Dungeon 1 Andar]", TNColor::Default, false);
	}
	else if (xv == 144 && yv == 3772) // Dungeon 1st floor to Armia Field (other locations)
	{
		*x = 2668 + rand() % 3;
		*y = 2156 + rand() % 3;
		SendMsgExp(conn, "Bem vindo ao [Dungeon 1 Andar]", TNColor::Default, false);
	}
	else if (xv == 148 && yv == 3780) // Dungeon 1st floor to Dungeon 2nd floor
	{
		*x = 1004 + rand() % 3;
		*y = 4028 + rand() % 3;
		SendMsgExp(conn, "Bem vindo ao [Dungeon 2 Andar]", TNColor::Default, false);
	}
	else if (xv == 144 && yv == 3780) // Dungeon 1st floor to Dungeon 2nd floor
	{
		*x = 1004 + rand() % 3;
		*y = 4028 + rand() % 3;
		SendMsgExp(conn, "Bem vindo ao [Dungeon 2 Andar]", TNColor::Default, false);
	}
	else if (xv == 1004 && yv == 4028) // Dungeon 2nd floor to Dungeon 1st Floor
	{
		*x = 148 + rand() % 3;
		*y = 3780 + rand() % 3;
		SendMsgExp(conn, "Bem vindo ao [Dungeon 1 Andar]", TNColor::Default, false);
	}
	else if (xv == 408 && yv == 4072) // Dungeon 1st floor to Dungeon 2nd floor
	{
		*x = 1004 + rand() % 3;
		*y = 4064 + rand() % 3;
		SendMsgExp(conn, "Bem vindo ao [Dungeon 2 Andar]", TNColor::Default, false);
	}
	else if (xv == 1004 && yv == 4064) // Dungeon 2nd floor to Dungeon 1st floor
	{
		*x = 408 + rand() % 3;
		*y = 4072 + rand() % 3;
		SendMsgExp(conn, "Bem vindo ao [Dungeon 1 Andar]", TNColor::Default, false);
	}
	else if (xv == 744 && yv == 3820) // Dungeon 1st floor to Dungeon 3rd floor
	{
		*x = 1004 + rand() % 3;
		*y = 3992 + rand() % 3;
		SendMsgExp(conn, "Bem vindo ao [Dungeon 3 Andar]", TNColor::Default, false);
	}
	else if (xv == 1004 && yv == 3992) // Dungeon 3rd floor to Dugeon 1st floor
	{
		*x = 744 + rand() % 3;
		*y = 3820 + rand() % 3;
		SendMsgExp(conn, "Bem vindo ao [Dungeon 1 Andar]", TNColor::Default, false);
	}
	else if (xv == 680 && yv == 4076) // Dungeon 2nd floor to Dungeon 3rd floor
	{
		*x = 916 + rand() % 3;
		*y = 3820 + rand() % 3;
		SendMsgExp(conn, "Bem vindo ao [Dungeon 3 Andar]", TNColor::Default, false);
	}
	else if (xv == 916 && yv == 3820) // Dungeon 3rd floor to Dungeon 2nd floor
	{
		*x = 680 + rand() % 3;
		*y = 4076 + rand() % 3;
		SendMsgExp(conn, "Bem vindo ao [Dungeon 2 Andar]", TNColor::Default, false);
	}
	else if (xv == 876 && yv == 3872) // Dungeon 2nd floor to Dungeon 3rd floor
	{
		*x = 932 + rand() % 3;
		*y = 3820 + rand() % 3;
		SendMsgExp(conn, "Bem vindo ao [Dungeon 3 Andar]", TNColor::Default, false);
	}
	else if (xv == 932 && yv == 3820) // Dungeon 3rd floor to Dungeon 2nd floor
	{
		*x = 876 + rand() % 3;
		*y = 3872 + rand() % 3;
		SendMsgExp(conn, "Bem vindo ao [Dungeon 2 Andar]", TNColor::Default, false);
	}
	else if (xv == 188 && yv == 188) // War area to Azran
	{
		*x = 2548 + rand() % 3;
		*y = 1740 + rand() % 3;
		SendMsgExp(conn, "Bem vindo a [Azran]", TNColor::Default, false);
	}
	else if (xv == 2548 && yv == 1740) // Azran to vale
	{
		if (pMob[conn].MOB.Equip[13].sIndex == 3916) {
			*x = 2281 + rand() % 3;
			*y = 3688 + rand() % 3;
			SendClientMessage(conn, "Bem vindo ao [Vale]");
		}
		else {
			SendClientMessage(conn, "Equipe uma Fada do Vale para ir ao Vale");
		}
	}
	else if (xv == 1824 && yv == 1772) // Azran Field to Underworld
	{
		*x = 1172 + rand() % 3;
		*y = 4080 + rand() % 3;
		SendMsgExp(conn, "Bem vindo ao [Submundo]", TNColor::Default, false);
	}
	else if (xv == 1172 && yv == 4080) // Underworld to Azran Field
	{
		*x = 1824 + rand() % 3;
		*y = 1772 + rand() % 3;
		SendMsgExp(conn, "Bem vindo a [Azran]", TNColor::Default, false);
	}
	else if (xv == 1516 && yv == 3996) // Underworld 1st floor to Underworld 2nd floor
	{
		*x = 1304 + rand() % 3;
		*y = 3816 + rand() % 3;
		SendMsgExp(conn, "Bem vindo ao [Submundo 2 Andar]", TNColor::Default, false);
	}
	else if (xv == 1304 && yv == 3816) // Underworld 2nd floor to Underworld 1st floor
	{
		*x = 1516 + rand() % 3;
		*y = 3996 + rand() % 3;
		SendMsgExp(conn, "Bem vindo ao [Submundo 1 Andar]", TNColor::Default, false);
	}
	else if (xv == 2452 && yv == 1716) // Azran 2nd teleport to Azran field
	{
		*x = 1969 + rand() % 3;
		*y = 1711 + rand() % 3;
		SendMsgExp(conn, "Bem vindo ao [Campo de Azran]", TNColor::Default, false);
	}
	else if (xv == 2452 && yv == 1988) // Erion teleport to Azran field
	{
		*x = 1989 + rand() % 3;
		*y = 1755 + rand() % 3;
		SendMsgExp(conn, "Bem vindo ao [Campo de Azran]", TNColor::Default, false);
	}

	else if (xv == 3648 && yv == 3108) // Karden teleport to Noatum
	{
		*x = 1054 + rand() % 3;
		*y = 1710 + rand() % 3;
		SendMsgExp(conn, "Bem vindo a [Noatum]", TNColor::Default, false);
	}

	else if (xv == 1056 && yv == 1724) // Noatum to RvR - Deserto
	{
		if (RvRState == 2)
		{
			if (pMob[conn].MOB.Clan == 7)//BLUE
			{
				*x = 1060 + rand() % 3;
				*y = 2098 + rand() % 3;
				SendMsgExp(conn, "Bem vindo ao [RVR BLUE]", TNColor::Default, false);
				Charge = 700;
			}
			else if (pMob[conn].MOB.Clan == 8)//RED
			{
				*x = 1238 + rand() % 3;
				*y = 1997 + rand() % 3;
				SendMsgExp(conn, "Bem vindo ao [RVR RED]", TNColor::Default, false);
				Charge = 700;
			}
		}

		/*else
		{
			*x = 1164 + rand() % 3;
			*y = 1720 + rand() % 3;
			SendMsgExp(conn, "Bem vindo ao [Pilar]", TNColor::Default, false);
		}*/

	}
	/*else if (xv == 2364 && yv == 3892 && pMob[conn].extra.KefraTicket > 0)
	{
		pMob[conn].extra.KefraTicket--;

		*x = 2364 + rand() % 3;
		*y = 3906 + rand() % 3;


		sprintf(temp, g_pMessageStringTable[_DN_CHANGE_COUNT], pMob[conn].extra.KefraTicket);

		SendMsgExp(conn, temp, TNColor::NewWhite, false);
	}*/

	else if (xv == 2364 && yv == 3892 && pMob[conn].extra.KefraTicket > 0)
	{
		pMob[conn].extra.KefraTicket--;
		*x = 2364 + rand() % 3;
		*y = 3906 + rand() % 3;
		SendMsgExp(conn, "Bem vindo ao Boss [Kefra]", TNColor::Default, false);
	}

	//Deserto - Kefra
	else if (xv == 2364 && yv == 3924 && KefraLive != 0)
	{
		*x = 3250 + rand() % 3;
		*y = 1703 + rand() % 3;
		SendMsgExp(conn, "Bem vindo a [Kefra]", TNColor::Default, false);
	}

	//Kefra - Deserto
	else if (xv == 1312 && yv == 1900)
	{
		*x = 2366 + rand() % 2;
		*y = 4073 + rand() % 2;
		SendMsgExp(conn, "Bem vindo a [Noatun Deserto]", TNColor::Default, false);
	}

	else if (xv == 2364 && yv == 4072)
	{
		*x = 1314 + rand() % 2;
		*y = 1900 + rand() % 2;
	}

	// Portal1 (Portão Infernal) - Zona 2
	else if (xv == 1756 && yv == 3672 && TarantulaKilled == TRUE)
	{
		*x = 1772 + rand() % 3;
		*y = 3648 + rand() % 3;
	}
	else if (xv == 1756 && yv == 3672 && TarantulaKilled == FALSE)

		SendMsgExp(conn, "Por favor derrote os monstros.", TNColor::Default, false);

	// Portal2 (Portão Infernal) - Zona 2
	else if (xv == 1756 && yv == 3644 && TarantulaKilled == TRUE)
	{
		*x = 1772 + rand() % 3;
		*y = 3648 + rand() % 3;
	}
	else if (xv == 1756 && yv == 3644 && TarantulaKilled == FALSE)

		SendMsgExp(conn, "Por favor derrote os monstros.", TNColor::Default, false);

	// Portal3 (Portão Infernal) - Zona 2
	else if (xv == 1756 && yv == 3616 && TarantulaKilled == TRUE)
	{
		*x = 1772 + rand() % 3;
		*y = 3648 + rand() % 3;
	}
	else if (xv == 1756 && yv == 3616 && TarantulaKilled == FALSE)

		SendMsgExp(conn, "Por favor derrote os monstros.", TNColor::Default, false);

	return Charge;
}


int	GetExpApply(STRUCT_MOBEXTRA extra, int exp, int attacker, int target)//exp cele //exp arch
{
	if ((extra.ClassMaster == MORTAL || extra.ClassMaster == ARCH || extra.ClassMaster == CELESTIAL || extra.ClassMaster == SCELESTIAL || extra.ClassMaster == CELESTIALCS ||
		extra.ClassMaster == HARDCORE || extra.ClassMaster == HARDCOREA || extra.ClassMaster == HARDCORECS ||
		extra.ClassMaster == SHARDCORE) && exp > 0)
	{
		if (attacker >= MAX_LEVEL)
			return 0;
	}

	if (extra.ClassMaster == ARCH && exp > 0)
	{
		if (attacker >= 354 && extra.QuestInfo.Arch.Level355 == 0)
			return 0;

		if (attacker >= 369 && extra.QuestInfo.Arch.Level370 == 0)
			return 0;
	}
	else if (extra.ClassMaster == CELESTIAL && exp > 0)
	{
		if (attacker >= 39 && extra.QuestInfo.Celestial.Lv40 == 0)
			return 0;

		if (attacker >= 89 && extra.QuestInfo.Celestial.Lv90 == 0)
			return 0;
	}

	else if (extra.ClassMaster == CELESTIALCS && exp > 0)
	{
		if (attacker >= 239 && extra.QuestInfo.Celestial.Lv240 == 0)
			return 0;

		if (attacker >= 279 && extra.QuestInfo.Celestial.Lv280 == 0)
			return 0;

		if (attacker >= 319 && extra.QuestInfo.Celestial.Lv320 == 0)
			return 0;

		if (attacker >= 359 && extra.QuestInfo.Celestial.Lv360 == 0)
			return 0;
	}

	if (target > MAX_LEVEL + 1 || attacker < 0 || target < 0)
		return exp;

	attacker++;
	target++;

	long long int ExpTotal = 0;
	int Multiply = 100;


	if (extra.ClassMaster == MORTAL) {
		if (attacker > 398)
			ExpTotal = (exp * 100) / ExpBaseN[11];

		else if (attacker > 395)
			ExpTotal = (exp * 100) / ExpBaseN[10];

		else if (attacker > 390)
			ExpTotal = (exp * 100) / ExpBaseN[9];

		else if (attacker > 380)
			ExpTotal = (exp * 100) / ExpBaseN[8];

		else if (attacker > 370)
			ExpTotal = (exp * 100) / ExpBaseN[7];

		else if (attacker > 360)
			ExpTotal = (exp * 100) / ExpBaseN[6];

		else if (attacker > 350)
			ExpTotal = (exp * 100) / ExpBaseN[5];

		else if (attacker > 340)
			ExpTotal = (exp * 100) / ExpBaseN[4];

		else if (attacker > 320)
			ExpTotal = (exp * 100) / ExpBaseN[3];

		else if (attacker > 300)
			ExpTotal = (exp * 100) / ExpBaseN[2];

		else if (attacker > 280)
			ExpTotal = (exp * 100) / ExpBaseN[1];

		else if (attacker > 255)
			ExpTotal = (exp * 100) / ExpBaseN[0];

		else if (attacker < 256) {
			if (attacker < 5)
				Multiply += 0;
			else
				Multiply += (attacker / 5);

			ExpTotal = (exp * 100) / Multiply;
		}
		else
			ExpTotal = exp;
	}

	if (extra.ClassMaster == ARCH) {
		if (attacker > 398)
			ExpTotal = (exp * 100) / ExpBaseM[11];

		else if (attacker > 395)
			ExpTotal = (exp * 100) / ExpBaseM[10];

		else if (attacker > 390)
			ExpTotal = (exp * 100) / ExpBaseM[9];

		else if (attacker > 380)
			ExpTotal = (exp * 100) / ExpBaseM[8];

		else if (attacker > 370)
			ExpTotal = (exp * 100) / ExpBaseM[7];

		else if (attacker > 360)
			ExpTotal = (exp * 100) / ExpBaseM[6];

		else if (attacker > 350)
			ExpTotal = (exp * 100) / ExpBaseM[5];

		else if (attacker > 340)
			ExpTotal = (exp * 100) / ExpBaseM[4];

		else if (attacker > 320)
			ExpTotal = (exp * 100) / ExpBaseM[3];

		else if (attacker > 300)
			ExpTotal = (exp * 100) / ExpBaseM[2];

		else if (attacker > 280)
			ExpTotal = (exp * 100) / ExpBaseM[1];

		else if (attacker > 255)
			ExpTotal = (exp * 100) / ExpBaseM[0];

		else if (attacker < 256) {
			if (attacker < 5)
				Multiply += 0;
			else
				Multiply += (attacker / 5);

			ExpTotal = (exp * 100) / Multiply;
		}
		else
			ExpTotal = exp;
	}

	if (extra.ClassMaster >= CELESTIAL) {
		if (attacker > 398)
			ExpTotal = (exp * 100) / 18000;

		else if (attacker > 395)
			ExpTotal = (exp * 100) / 17000;

		else if (attacker > 390)
			ExpTotal = (exp * 100) / 16000;

		else if (attacker > 385)
			ExpTotal = (exp * 100) / 15000;

		else if (attacker > 380)
			ExpTotal = (exp * 100) / 14000;

		else if (attacker > 375)
			ExpTotal = (exp * 100) / 13000;

		else if (attacker > 370)
			ExpTotal = (exp * 100) / 12000;

		else if (attacker > 365)
			ExpTotal = (exp * 100) / 11000;

		else if (attacker > 360)
			ExpTotal = (exp * 100) / 10000;

		else if (attacker > 355)
			ExpTotal = (exp * 100) / 9500;

		else if (attacker > 350)
			ExpTotal = (exp * 100) / 9300;

		else if (attacker > 340)
			ExpTotal = (exp * 100) / 9100;

		else if (attacker > 320)
			ExpTotal = (exp * 100) / 9000;

		else if (attacker > 300)
			ExpTotal = (exp * 100) / 8900;

		else if (attacker > 280)
			ExpTotal = (exp * 100) / 8800;

		else if (attacker > 255)
			ExpTotal = (exp * 100) / 8500;

		else if (attacker > 230)
			ExpTotal = (exp * 100) / 8000;

		else if (attacker > 210)
			ExpTotal = (exp * 100) / 7500;

		else if (attacker > 190)
			ExpTotal = (exp * 100) / 7000;

		else if (attacker > 150)
			ExpTotal = (exp * 100) / 6500;

		else if (attacker > 100)
			ExpTotal = (exp * 100) / 6000;

		else if (attacker > 80)
			ExpTotal = (exp * 100) / 5500;

		else if (attacker > 40)
			ExpTotal = (exp * 100) / 5000;

		else
			ExpTotal = (exp * 100) / 4000;
	}

	return ExpTotal;
}

void TiroDireto(int Attacker, int Attacked)
{
	if (pMob[Attacker].MOB.Class == 3)
	{
		for (int i = 0; i < MAX_AFFECT; i++)
		{
			int Type = pMob[Attacker].Affect[i].Type;

			if (Type == 28)
			{

				SendMsgExp(Attacker, "Oba", TNColor::Default, false);
				return;
			}
		}
	}
}

int GetCreateMob(int mob, MSG_CreateMob* sm)
{
	memset(sm, 0, sizeof(MSG_CreateMob));

	sm->Type = _MSG_CreateMob;

	strncpy(sm->MobName, pMob[mob].MOB.MobName, NAME_LENGTH);

	if (mob < MAX_USER)
	{
		int ck = GetCurKill(mob);
		int tk = GetTotKill(mob);

		unsigned char cv = ck;
		unsigned char cv1 = tk % 256;
		unsigned char cv2 = tk / 256;

		sm->MobName[13] = cv;
		sm->MobName[14] = cv1;
		sm->MobName[15] = cv2;

		int chaos = GetPKPoint(mob);
		int gv = GetGuilty(mob);

		if (gv > 0)
			chaos = 0;

		cv = chaos;
		sm->MobName[12] = chaos;
	}

	sm->PosX = pMob[mob].TargetX;
	sm->PosY = pMob[mob].TargetY;
	sm->Size = sizeof(MSG_CreateMob);
	sm->ID = ESCENE_FIELD;
	sm->MobID = mob;
	sm->ClientTick = CurrentTime;

	sm->Score = pMob[mob].MOB.CurrentScore;

	sm->Guild = pMob[mob].MOB.Guild;
	sm->GuildMemberType = pMob[mob].MOB.GuildLevel;

	if (pMob[mob].GuildDisable == 1)
	{
		sm->Guild = 0;
		sm->GuildMemberType = 0;
	}
	if (mob >= MAX_USER)
	{
		if (pMob[mob].MOB.Clan == 4)
			sm->Score.Ac = 0;

		else
			sm->Score.Ac = 1;
	}

	sm->CreateType = 0;

	if (pMob[mob].MOB.GuildLevel == 9)
		sm->CreateType = sm->CreateType | 0x80;

	else if (pMob[mob].MOB.GuildLevel >= 6)
		sm->CreateType = sm->CreateType | 0x40;


	sm->Hold = pMob[mob].extra.Hold;

	strncpy(sm->Tab, pMob[mob].Tab, 26);

	int selfdead = 0;

	int xx = pMob[mob].TargetX;
	int yy = pMob[mob].TargetY;

	for (int i = 0; i < MAX_EQUIP; i++)
	{
		STRUCT_ITEM* item = &pMob[mob].MOB.Equip[i];

		sm->Equip[i] = BASE_VisualItemCode(item, i);

		sm->AnctCode[i] = BASE_VisualAnctCode(item);

		if (i == 14 && sm->Equip[i] >= 2360 && sm->Equip[i] < 2390 && pMob[mob].MOB.Equip[i].stEffect[0].sValue <= 0)
		{
			sm->Equip[i] = 0;

			selfdead = 1;

			continue;
		}

		if (i == 14 && sm->Equip[i] >= 2360 && sm->Equip[i] < 2390)
		{
			int sanc = pMob[mob].MOB.Equip[i].stEffect[1].cEffect;
			sanc = sanc / 10;

			if (sanc > 13)
				sanc = 13;

			if (sanc < 0)
				sanc = 0;

			sanc = sanc << 12;

			sm->Equip[i] = sm->Equip[i] + sanc;

			continue;
		}
	}

	if (strcmp((char*)sm->MobName, "Balmus") == 0)
		strncpy(sm->Tab, "Informações da Guild", sizeof(sm->Tab));

	else if (strcmp((char*)sm->MobName, "Judith") == 0)
		strncpy(sm->Tab, "Informações da Guild", sizeof(sm->Tab));

	else if (strcmp((char*)sm->MobName, "Kara") == 0)
		strncpy(sm->Tab, "Informações da Guild", sizeof(sm->Tab));

	else if (strcmp((char*)sm->MobName, "Empis") == 0)
		strncpy(sm->Tab, "Informações da Guild", sizeof(sm->Tab));

	else if (strcmp((char*)sm->MobName, "Bruce") == 0)
		strncpy(sm->Tab, "Informações da Guild", sizeof(sm->Tab));

	else if (strcmp((char*)sm->MobName, "Kibita") == 0)
		strncpy(sm->Tab, "Torne-se Cidadão", sizeof(sm->Tab));

	else if (strcmp((char*)sm->MobName, "Carbuncle Wind") == 0)
		strncpy(sm->Tab, "Ajudante Mágico", sizeof(sm->Tab));

	else if (strcmp((char*)sm->MobName, "Aylin") == 0)
		strncpy(sm->Tab, "Compositor +10", sizeof(sm->Tab));

	else if (strcmp((char*)sm->MobName, "Agatha") == 0)
		strncpy(sm->Tab, "Passar Add Armadura Arch", sizeof(sm->Tab));

	else if (strcmp((char*)sm->MobName, "Compositor") == 0)
		strncpy(sm->Tab, "Compositor Anct", sizeof(sm->Tab));

	else if (strcmp((char*)sm->MobName, "Sobrevivente") == 0)
		strncpy(sm->Tab, "Fale comigo para entrar!", sizeof(sm->Tab));

	else if (strcmp((char*)sm->MobName, "Jephi") == 0)
		strncpy(sm->Tab, "Compor Poeiras e Círculos", sizeof(sm->Tab));

	else if (strcmp((char*)sm->MobName, "Perzen Mistico") == 0)
		strncpy(sm->Tab, "Esfera M", sizeof(sm->Tab));

	else if (strcmp((char*)sm->MobName, "Perzen Arcano") == 0)
		strncpy(sm->Tab, "Esfera A", sizeof(sm->Tab));

	else if (strcmp((char*)sm->MobName, "Perzen Normal") == 0)
		strncpy(sm->Tab, "Esfera N", sizeof(sm->Tab));

	else if (strcmp((char*)sm->MobName, "Guarda Carga") == 0 ||
		strcmp((char*)sm->MobName, "Hera") == 0 ||
		strcmp((char*)sm->MobName, "Angela") == 0)
		strncpy(sm->Tab, "Baú", sizeof(sm->Tab));

	else if (strcmp((char*)sm->MobName, "Xama") == 0)
		strncpy(sm->Tab, "Entrada Coliseu", sizeof(sm->Tab));

	else if (strcmp((char*)sm->MobName, "Shaman") == 0)
		strncpy(sm->Tab, "Reset Skill", sizeof(sm->Tab));

	else if (strcmp((char*)sm->MobName, "Juli") == 0)
		strncpy(sm->Tab, "Teleport", sizeof(sm->Tab));

	else if (strcmp((char*)sm->MobName, "Aki") == 0 ||
		strcmp((char*)sm->MobName, "Ferreiro") == 0 ||
		strcmp((char*)sm->MobName, "Rainy") == 0 ||
		strcmp((char*)sm->MobName, "Rapien") == 0 ||
		strcmp((char*)sm->MobName, "Arnod") == 0 ||
		strcmp((char*)sm->MobName, "Arnold") == 0 ||
		strcmp((char*)sm->MobName, "Ruti") == 0 ||
		strcmp((char*)sm->MobName, "Lucy") == 0 ||
		strcmp((char*)sm->MobName, "C. de Montaria") == 0 ||
		strcmp((char*)sm->MobName, "Rophelion") == 0 ||
		strcmp((char*)sm->MobName, "Reimers") == 0 ||
		strcmp((char*)sm->MobName, "Lubien") == 0 ||
		strcmp((char*)sm->MobName, "Reiners") == 0 ||
		strcmp((char*)sm->MobName, "Hestia") == 0 ||
		strcmp((char*)sm->MobName, "Berlund") == 0 ||
		strcmp((char*)sm->MobName, "Martin") == 0)
		strncpy(sm->Tab, "Comerciante", sizeof(sm->Tab));

	else if (strcmp((char*)sm->MobName, "Tiny") == 0)
		strncpy(sm->Tab, "Add Arma Arch", sizeof(sm->Tab));

	else if (strcmp((char*)sm->MobName, "Ehre") == 0)
		strncpy(sm->Tab, "Compositor Diverso", sizeof(sm->Tab));

	else if (strcmp((char*)sm->MobName, "M. de Montaria") == 0)
		strncpy(sm->Tab, "Reviver Montarias", sizeof(sm->Tab));

	else if (strcmp((char*)sm->MobName, "Cap.Mercenario") == 0)
		strncpy(sm->Tab, "Quest Amuleto", sizeof(sm->Tab));

	else if (strcmp((char*)sm->MobName, "Mestre Archi") == 0 ||
		strcmp((char*)sm->MobName, "Foema Ancian") == 0 ||
		strcmp((char*)sm->MobName, "Cap.Cavaleiros") == 0 ||
		strcmp((char*)sm->MobName, "ForeLearner") == 0)
		strncpy(sm->Tab, "Aprender Skill", sizeof(sm->Tab));

	GetAffect(sm->Affect, pMob[mob].Affect);

	if (BrState != 0 && xx >= 2604 && yy >= 1708 && xx <= 2648 && yy <= 1744)
	{
		memset(sm->MobName, 0, NAME_LENGTH); // MOBNAME_LEGNTH = 16
		strncpy(sm->MobName, "??????", 6);

		sm->Equip[15] = 0;
		sm->Guild = 0;
	}

	return selfdead;
}

int GetCreateMobTrade(int mob, MSG_CreateMobTrade* sm)
{
	sm->Type = _MSG_CreateMobTrade;

	strncpy(sm->MobName, pMob[mob].MOB.MobName, NAME_LENGTH);

	if (mob >= MAX_USER)
	{
		Log("err,getcreatemob request by non player %d", pMob[mob].MOB.MobName, 0);
		return 0;
	}

	if (mob < MAX_USER)
	{
		int ck = GetCurKill(mob);
		int tk = GetTotKill(mob);

		unsigned char cv = ck;
		unsigned char cv1 = tk % 256;
		unsigned char cv2 = tk / 256;

		sm->MobName[13] = cv;
		sm->MobName[14] = cv1;
		sm->MobName[15] = cv2;

		int chaos = GetPKPoint(mob);

		cv = chaos;
		sm->MobName[12] = cv;
	}

	sm->PosX = pMob[mob].TargetX;
	sm->PosY = pMob[mob].TargetY;
	sm->Size = sizeof(MSG_CreateMobTrade);
	sm->ID = ESCENE_FIELD;
	sm->MobID = mob;
	sm->ClientTick = CurrentTime;

	memcpy(&sm->Score, &pMob[mob].MOB.CurrentScore, sizeof(STRUCT_SCORE));

	sm->Guild = pMob[mob].MOB.Guild;

	if (pMob[mob].GuildDisable == 1)
		sm->Guild = 0;

	if (mob >= MAX_USER)
		sm->Score.Ac = pMob[mob].MOB.Clan != 4;

	sm->CreateType = 0;

	if (pMob[mob].MOB.GuildLevel == 9)
		sm->CreateType = sm->CreateType | 0x80;

	if (pMob[mob].MOB.GuildLevel != 0)
		sm->CreateType = sm->CreateType | 0x40;

	int selfdead = 0;

	for (int i = 0; i < MAX_EQUIP; i++)
	{
		STRUCT_ITEM* item = &pMob[mob].MOB.Equip[i];

		sm->Equip[i] = BASE_VisualItemCode(item, i);

		sm->AnctCode[i] = BASE_VisualAnctCode(item);

		if (i == 14 && sm->Equip[i] >= 2360 && sm->Equip[i] < 2390 && pMob[mob].MOB.Equip[i].stEffect[0].sValue <= 0)
		{
			sm->Equip[i] = 0;

			selfdead = 1;

			continue;
		}

		if (i == 14 && sm->Equip[i] >= 2360 && sm->Equip[i] < 2390)
		{
			int sanc = pMob[mob].MOB.Equip[i].stEffect[1].cEffect;
			sanc = sanc / 10;

			if (sanc > 13)
				sanc = 13;

			if (sanc < 0)
				sanc = 0;

			sanc = sanc << 12;

			sm->Equip[i] = sm->Equip[i] + sanc;

			continue;
		}
	}

	strncpy(sm->Tab, pMob[mob].Tab, 26);
	strncpy(sm->Desc, pUser[mob].AutoTrade.Title, MAX_AUTOTRADETITLE - 1);

	GetAffect(sm->Affect, pMob[mob].Affect);

	return selfdead;
}

void GetAffect(unsigned short* out, STRUCT_AFFECT* affect)
{
	for (int i = 0; i < MAX_AFFECT; i++) // i = 0;
	{
		int type = affect[i].Type;
		int value = affect[i].Time;

		//if(type == 0)
		//	continue;

		value = value;

		if (value > 2550000)
			value = 2550000;

		unsigned short tout = (type << 8) + (value & 0xFF);

		out[i] = tout;
	}
}

void GetCreateItem(int idx, MSG_CreateItem* sm)
{
	sm->ID = ESCENE_FIELD;
	sm->Size = sizeof(MSG_CreateItem);
	sm->Type = _MSG_CreateItem;


	sm->GridX = pItem[idx].PosX;
	sm->GridY = pItem[idx].PosY;

	sm->ItemID = idx + 10000;

	sm->Rotate = pItem[idx].Rotate;

	sm->Item = pItem[idx].ITEM;

	sm->State = pItem[idx].State;

	sm->Height = -204;

	if (pItem[idx].ITEM.sIndex == 3145)
	{
		int zone = BASE_GetVillage(pItem[idx].PosX, pItem[idx].PosY);
		sm->Item.sIndex = 3145 + g_pGuildZone[zone].Victory;

		sm->State = STATE_CLOSED;

		sm->Item.stEffect[0].cEffect = 56;
		sm->Item.stEffect[1].cEffect = 57;

		sm->Item.stEffect[0].cValue = (g_pGuildZone[zone].ChargeGuild + (ServerIndex << 12)) >> 8;
		sm->Item.stEffect[1].cValue = g_pGuildZone[zone].ChargeGuild;
	}

	if (pItem[idx].ITEM.sIndex == 5700)
		return;

	if (sm->State == STATE_OPEN)
	{
		sm->Height = pItem[idx].Height;
		sm->Create = 0;
	}
}

void GetAction(int mob, int targetx, int targety, MSG_Action* sm)
{
	sm->ID = mob;
	sm->ClientTick = CurrentTime;
	sm->Size = sizeof(MSG_Action);
	sm->Type = _MSG_Action;

	sm->TargetX = targetx;
	sm->TargetY = targety;
	sm->Route[0] = 0;

	sm->Speed = 2;
	sm->Effect = 1;
	sm->PosX = pMob[mob].TargetX;
	sm->PosY = pMob[mob].TargetY;
}

unsigned char GetAttribute(int x, int y)
{
	if (x < 0 || x > MAX_GRIDX || y < 0 || y > MAX_GRIDY)
		return 0;

	int xx = x / 4;

	xx = xx & 0x3FF;

	int yy = y / 4;

	yy = yy & 0x3FF;

	unsigned char ret = g_pAttribute[yy][xx];

	return ret;
}

union MapAttribute
{
	struct
	{
		UINT8 Village : 1; // 1
		UINT8 CantGo : 1; // 2
		UINT8 CantSummon : 1; // 4
		UINT8 House : 1; // 8
		UINT8 Teleport : 1; // 16
		UINT8 Guild : 1; // 32
		UINT8 PvP : 1; // 64
		UINT8 Newbie : 1; // 128
	};
	UINT8 Value;
};

void GetAttack(int clientId, int mobId, p39D* p)
{
	memset(p, 0, sizeof p39D);

	p->ID = 0x7531;
	p->attackerId = clientId;
	p->ClientTick = clock();

	p->attackerPos.PosX = pMob[clientId].TargetX;
	p->attackerPos.PosY = pMob[clientId].TargetY;

	p->targetPos.PosX = pMob[mobId].TargetX;
	p->targetPos.PosY = pMob[mobId].TargetY;

	//0041D27A
	p->Size = sizeof p39D;
	p->Type = 0x39D;

	p->doubleCritical = 0;
	p->currentMp = -1;
	p->currentExp = -1;

	p->Target.Damage = 0;

	//p->unknow_2 = -2;
	p->Target.TargetID = mobId;

	INT32 LOCAL_1 = -1;
	p->skillParm = 0;
	p->skillId = -1;

	p->Motion = rand() % 3 + 4;

	if (clientId >= MAX_USER)
	{
		INT32 LOCAL_2 = BASE_GetDistance(pMob[clientId].TargetX, pMob[clientId].TargetY, pMob[mobId].TargetX, pMob[mobId].TargetY);

		INT16 LOCAL_3;
		INT32 LOCAL_4;
		if (LOCAL_2 < 3)
		{
			LOCAL_3 = (char)pMob[clientId].MOB.CurrentScore.Special[0];
			LOCAL_4 = (char)pMob[clientId].MOB.CurrentScore.Special[1];
		}
		else
		{
			LOCAL_3 = (char)pMob[clientId].MOB.CurrentScore.Special[2];
			LOCAL_4 = (char)pMob[clientId].MOB.CurrentScore.Special[3];
		}

		p->Motion = 0;

		/*if ((LOCAL_3 & 0xFF) == 0xFF)
			LOCAL_3 = 0xFF;*/

			// 0041D3B1
			//LOCAL_3 &= 0xFF;

		if (LOCAL_3 == 0x79)
		{
			p->skillId = 103;
			p->skillParm = 5;
		}
		else if (LOCAL_3 == 0x7A)
		{
			p->skillId = 0x69;
			p->skillParm = 1;
		}
		else if (LOCAL_3 == 0x7B)
		{
			p->skillId = 0x65;
			p->skillParm = 1;
		}
		else if (LOCAL_3 == 0x7C)
		{
			p->skillId = 0x65;
			p->skillParm = 2;
		}
		else if (LOCAL_3 == 0x7D)
		{
			p->skillId = 0x28;
			p->skillParm = 1;
		}
		else if (LOCAL_3 == 0x7E)
		{
			p->skillId = 0x28;
			p->skillParm = 2;
		}

		else if (LOCAL_3 == 0x7F)
		{
			p->skillId = 0x28;
			p->skillParm = 3;
		}
		else if (LOCAL_3 == 0x80)
		{
			p->skillId = 0x21;
			p->skillParm = 0xFC;
			p->Motion = 0xFC;
		}
		else
			p->skillId = LOCAL_3;

		if (LOCAL_4 != 0)
		{
			p->Motion = 4;

			INT32 LOCAL_5 = rand() & 0x80000003;
			if (LOCAL_4 == 3)
			{
				if (LOCAL_5 <= 1)
					p->Motion++;
			}
			else if (LOCAL_4 == 6)
			{
				if (LOCAL_5 <= 1)
					p->Motion++;
				else
					p->Motion += 2;
			}
			else if (LOCAL_4 == 7)
			{
				if (LOCAL_5 == 1)
					p->Motion++;
				else
					p->Motion += 2;
			}
			else if (LOCAL_4 == 15)
			{
				if (LOCAL_5 == 1)
					p->Motion++;
				else if (LOCAL_5 == 2)
					p->Motion += 2;
				else if (LOCAL_5 == 3)
					p->Motion += 3;
			}
			else if (LOCAL_4 == 0x18)
			{
				if (LOCAL_5 <= 1)
					p->Motion += 3;
				else
					p->Motion += 4;
			}
			else if (LOCAL_4 == 0x1B)
			{
				if (LOCAL_5 == 1)
					p->Motion++;
				else if (LOCAL_5 == 2)
					p->Motion += 3;
				else if (LOCAL_5 == 3)
					p->Motion += 4;
			}
			else if (LOCAL_4 == 0x17)
			{
				if (LOCAL_5 == 1)
					p->Motion++;
				else if (LOCAL_5 == 2)
					p->Motion += 2;
				else if (LOCAL_5 == 3)
					p->Motion += 4;
			}
		}

		INT32 LOCAL_6 = rand() % 100;
		if (pMob[clientId].MOB.SkillBar[3] != -1 && LOCAL_6 >= 0x19 && LOCAL_6 <= 40)
		{// skillData base = 7DCDD8
			INT32 LOCAL_7 = pMob[clientId].MOB.SkillBar[3];
			INT32 LOCAL_8 = g_pSpell[LOCAL_7].InstanceType;
			INT32 LOCAL_9 = pMob[clientId].Leader;

			if (LOCAL_9 <= 0)
				LOCAL_9 = clientId;

			INT32 LOCAL_10 = pMob[clientId].MOB.CurrentScore.Hp;
			LOCAL_10 = LOCAL_10 * 10;
			LOCAL_10 = LOCAL_10 / pMob[clientId].MOB.CurrentScore.MaxHp;
			INT32 LOCAL_11 = pMob[LOCAL_9].MOB.CurrentScore.Hp;
			LOCAL_11 = LOCAL_11 * 10;
			LOCAL_11 = LOCAL_11 / pMob[clientId].MOB.CurrentScore.MaxHp;

			if (LOCAL_8 == 6 && LOCAL_10 <= 8 && LOCAL_11 <= 8)
			{
				p->skillId = LOCAL_7;

				INT32 LOCAL_12 = clientId;
				if (LOCAL_10 > LOCAL_11)
					LOCAL_12 = LOCAL_9;

				INT32 LOCAL_13 = pMob[LOCAL_12].MOB.CurrentScore.Hp / 10;

				p->Target.TargetID = LOCAL_12;
				p->Target.Damage = -LOCAL_13;

				return;
			}
		}

		if (pMob[clientId].MOB.SkillBar[0] != -1 && LOCAL_6 >= 0 && LOCAL_6 <= 49)
		{
			INT32 LOCAL_14 = pMob[clientId].MOB.SkillBar[0];
			INT32 LOCAL_15 = g_pSpell[LOCAL_14].InstanceType;

			LOCAL_1 = LOCAL_15 - 2;

			p->skillId = LOCAL_14;
		}
		else if (pMob[clientId].MOB.SkillBar[1] != -1 && LOCAL_6 >= 50 && LOCAL_6 <= 84)
		{
			INT32 LOCAL_16 = pMob[clientId].MOB.SkillBar[1];
			INT32 LOCAL_17 = g_pSpell[LOCAL_16].InstanceType;

			LOCAL_1 = LOCAL_17 - 2;

			p->skillId = LOCAL_16;
		}
		else if (pMob[clientId].MOB.SkillBar[2] != -1 && LOCAL_6 >= 85 && LOCAL_6 <= 99)
		{
			INT32 LOCAL_16 = pMob[clientId].MOB.SkillBar[1];
			INT32 LOCAL_17 = g_pSpell[LOCAL_16].InstanceType;

			LOCAL_1 = LOCAL_17 - 2;

			p->skillId = LOCAL_16;
		}
	}

	INT32 LOCAL_20 = pMob[clientId].MOB.CurrentScore.Damage;

	LOCAL_20 = BASE_GetDamage(LOCAL_20, pMob[mobId].MOB.CurrentScore.Ac, 0);



	if (LOCAL_1 >= 0 && LOCAL_1 <= 3)
		LOCAL_20 = LOCAL_20 * (100 - *(BYTE*)(&pMob[mobId].MOB.Resist + LOCAL_1)) / 100;

	if (LOCAL_20 > 0 && mobId < MAX_USER && pMob[mobId].ReflectDamage > 0)
	{
		LOCAL_20 -= pMob[mobId].ReflectDamage;

		if (LOCAL_20 < 0)
			LOCAL_20 = 0;
	}

	if (LOCAL_20 > 0)
	{
		if (clientId < MAX_USER || pMob[clientId].MOB.Clan == 4)
		{
			if (mobId < MAX_USER || pMob[mobId].MOB.Clan == 4)
			{
				LOCAL_20 = LOCAL_20 * 3 / 10;

				MapAttribute LOCAL_21{};
				auto att1 = GetAttribute(pMob[mobId].TargetX, pMob[mobId].TargetY);
				memcpy(&LOCAL_21, &att1, sizeof(MapAttribute));
				auto att2 = GetAttribute(pMob[clientId].TargetX, pMob[clientId].TargetY);
				MapAttribute LOCAL_22{};
				memcpy(&LOCAL_22, &att2, sizeof(MapAttribute));
				if (LOCAL_21.Village || !LOCAL_21.PvP)
					LOCAL_20 = 0;

				if (LOCAL_22.Village || !LOCAL_22.PvP)
					LOCAL_20 = 0;
			}
		}

		INT32 LOCAL_23 = pMob[clientId].Leader;
		if (LOCAL_23 == 0)
			LOCAL_23 = clientId;

		INT32 LOCAL_24 = pMob[mobId].Leader;
		if (LOCAL_24 == 0)
			LOCAL_24 = mobId;

		INT32 LOCAL_25 = pMob[clientId].MOB.Guild;
		INT32 LOCAL_26 = pMob[mobId].MOB.Guild;    // quem está sendo atacado
		INT32 ally = g_pGuildAlly[LOCAL_25];
		if (ally == 0)
			ally = -1;

		if (LOCAL_25 == 0 && LOCAL_26 == 0)
			LOCAL_25 = -1;

		if (mobId < MAX_USER && pMob[mobId].GuildDisable)
			LOCAL_26 = -2;


		if (LOCAL_23 == LOCAL_24 || LOCAL_25 == LOCAL_26 || ally == LOCAL_26)
		{
			LOCAL_20 = 0;
			pMob[clientId].CurrentTarget = 0;
		}
	}
	int damage = LOCAL_20;
	p->Target.Damage = damage;
	if (mobId < MAX_USER && LOCAL_20 > 0)
	{
		UINT32 LOCAL_180 = GetParryRate(&pMob[clientId].MOB, pMob[clientId].MOB.CurrentScore.Dex, pMob[clientId].MOB.Rsv, pMob[clientId].Parry, pMob[mobId].MOB.CurrentScore.Dex, pMob[mobId].MOB.Rsv, pMob[mobId].Parry);

		INT32 LOCAL_181 = (rand() % 1000) + 1;
		if (LOCAL_181 < LOCAL_180 && pMob[clientId].GenerateIndex != KEFRA_BOSS)
		{
			p->Target.Damage = -3;
			if ((pMob[mobId].MOB.Rsv & 128) && LOCAL_181 < MAX_USER)
				p->Target.Damage = -4;
		}

		if (pMob[mobId].MOB.Clan == 4)
			p->Target.Damage = (p->Target.Damage << 1) / 5;


		INT32 auxDam = p->Target.Damage;
		if (pMob[mobId].MOB.Class == 1)//controle de mana foema
		{
			for (int c = 0; c < MAX_AFFECT; c++) // Controle de Mana ( PVP )
			{
				if (pMob[mobId].Affect[c].Type == 18)
				{
					INT32 tmpDamage = auxDam / 2;
					if ((pUser[mobId].ReqMp - tmpDamage) >= 300)
					{
						pMob[mobId].MOB.CurrentScore.Mp -= tmpDamage;
						pUser[mobId].ReqMp -= tmpDamage;

						SetReqMp(mobId);
						SendScore(mobId);

						auxDam = tmpDamage;
					}
					else
						SendSetHpMp(mobId);
				}
			}
		}

		/*INT32 auxDam = p->Target.Damage;
		for (int i = 0; i < 32; i++)
		{
			if (pMob[mobId].Affect[i].Type == 18)
			{
				INT32 tmpDamage = auxDam / 2;
				if ((pUser[mobId].ReqMp - tmpDamage) >= 300)
				{
					pMob[mobId].MOB.CurrentScore.Mp -= tmpDamage;
					pUser[mobId].ReqMp -= tmpDamage;

					SetReqMp(mobId);
					SendScore(mobId);

					auxDam = tmpDamage;
				}
				else
					SendSetHpMp(mobId);

				break;
			}
		}*/

		damage = auxDam;
	}

	p->Target.Damage = damage;
}

//void GetAttack(int mob, int target, MSG_AttackOne *sm)
//{
//	memset(sm, 0, sizeof(MSG_AttackOne));
//
//	sm->ID = ESCENE_FIELD;
//	sm->AttackerID = mob;
//	sm->ClientTick = CurrentTime;
//	sm->PosX = pMob[mob].TargetX;
//	sm->PosY = pMob[mob].TargetY;
//	sm->TargetX = pMob[target].TargetX;
//	sm->TargetY = pMob[target].TargetY;
//	sm->Size = sizeof(MSG_AttackOne);
//	sm->Type = _MSG_AttackOne;
//
//	sm->DoubleCritical = 0;
//	sm->CurrentMp = -1;
//	sm->ReqMp = -1;
//
//	sm->Dam[0].TargetID = 0;
//	sm->Dam[0].Damage = 0;
//
//	sm->Dam[0].TargetID = target;
//
//	int Resist = -1;
//
//	sm->SkillParm = 0;
//	sm->SkillIndex = -1;
//	sm->Motion = rand() % 3 + 4;
//
//	int special = 0;
//	int special2 = 0;
//
//	if (mob >= MAX_USER)
//	{
//		int dis = BASE_GetDistance(pMob[mob].TargetX, pMob[mob].TargetY, pMob[target].TargetX, pMob[target].TargetY);
//		if (dis >= 3)
//		{
//			special = pMob[mob].MOB.BaseScore.Special[2];//pMob[mob].MOB.SkillBar[2];
//			special2 = pMob[mob].MOB.BaseScore.Special[3]; // pMob[mob].MOB.SkillBar[3];
//		}
//		else
//		{
//			special = pMob[mob].MOB.BaseScore.Special[0];//pMob[mob].MOB.SkillBar[0];
//			special2 = pMob[mob].MOB.BaseScore.Special[1];//pMob[mob].MOB.SkillBar[1];
//		}
//
//		sm->Motion = 0;
//
//		if (special == 255)
//			special = -1;
//
//		switch (special)
//		{
//		case 121:
//			sm->SkillIndex = 103;
//			sm->SkillParm = 5;
//			break;
//		case 122:
//			sm->SkillIndex = 105;
//			sm->SkillParm = 1;
//			break;
//		case 123:
//			sm->SkillIndex = 101;
//			sm->SkillParm = 1;
//			break;
//		case 124:
//			sm->SkillIndex = 101;
//			sm->SkillParm = 2;
//			break;
//		case 125:
//			sm->SkillIndex = 40;
//			sm->SkillParm = 1;
//			break;
//		case 126:
//			sm->SkillIndex = 40;
//			sm->SkillParm = 2;
//			break;
//		case 127:
//			sm->SkillIndex = 40;
//			sm->SkillParm = 3;
//			break;
//		case 128:
//			sm->SkillIndex = 33;
//			sm->SkillParm = -4;
//			sm->Motion = -4;
//			break;
//		default:
//			sm->SkillIndex = special;
//			sm->SkillParm = 1;
//			break;
//		}
//		if (special2)
//		{
//			sm->Motion = 4;
//			int _rand = rand() % 4;
//
//			switch (special2)
//			{
//			case 3:
//				if (_rand <= 1)
//					sm->Motion++;
//				break;
//			case 6:
//				if (_rand > 1)
//					sm->Motion += 2;
//				else
//					sm->Motion++;
//				break;
//			case 7:
//				if (_rand == 1)
//					sm->Motion++;
//				else
//					sm->Motion += 2;
//				break;
//			case 15:
//				switch (_rand)
//				{
//				case 1:
//					sm->Motion++;
//					break;
//				case 2:
//					sm->Motion += 2;
//					break;
//				case 3:
//					sm->Motion += 3;
//					break;
//				}
//				break;
//			case 24:
//				if (_rand > 1)
//					sm->Motion += 4;
//				else
//					sm->Motion += 3;
//				break;
//			case 27:
//				switch (_rand)
//				{
//				case 1:
//					sm->Motion++;
//					break;
//				case 2:
//					sm->Motion += 3;
//					break;
//				case 3:
//					sm->Motion += 4;
//					break;
//				}
//				break;
//			case 23:
//				switch (_rand)
//				{
//				case 1:
//					sm->Motion++;
//					break;
//				case 2:
//					sm->Motion += 2;
//					break;
//				case 3:
//					sm->Motion += 4;
//					break;
//				}
//				break;
//
//			default:
//				sm->SkillParm = 1;
//				break;
//			}
//		}
//		int rand_ = rand() % 100;
//		if (pMob[mob].MOB.SkillBar[3] != 255 && rand_ >= 25 && rand_ <= 64)
//		{
//			int skillb3 = pMob[mob].MOB.SkillBar[3];
//
//			int insttype = g_pSpell[skillb3].InstanceType;
//
//			int leader = pMob[mob].Leader;
//			if (leader <= 0)
//				leader = mob;
//
//			int hp = pMob[mob].MOB.CurrentScore.Hp;
//			hp *= 10;
//			hp /= pMob[mob].MOB.CurrentScore.MaxHp + 1;
//
//			int lhp = pMob[leader].MOB.CurrentScore.Hp;
//			lhp *= 10;
//			lhp /= pMob[leader].MOB.CurrentScore.MaxHp + 1;
//
//			if (insttype == 6)
//			{
//				if (hp <= 8 || lhp <= 8)
//				{
//					int _mob = 0;
//
//					sm->SkillIndex = insttype;
//
//					_mob = mob;
//					if (hp > lhp)
//						_mob = leader;
//
//
//					sm->Dam[0].TargetID = _mob;
//					sm->Dam[0].Damage = pMob[_mob].MOB.CurrentScore.MaxHp / 10;
//
//					return;
//				}
//			}
//		}
//		if (pMob[mob].MOB.SkillBar[0] == 255 || rand_ < 0 || rand_ > 49)
//		{
//			if (pMob[mob].MOB.SkillBar[1] == 255 || rand_ < 50 || rand_ > 84)
//			{
//				if (pMob[mob].MOB.SkillBar[2] != 255 && rand_ >= 85 && rand_ <= 99)
//				{
//					Resist = g_pSpell[pMob[mob].MOB.SkillBar[2]].InstanceType - 2;
//					sm->SkillIndex = pMob[mob].MOB.SkillBar[2];
//				}
//			}
//			else
//			{
//				Resist = g_pSpell[pMob[mob].MOB.SkillBar[1]].InstanceType - 2;
//				sm->SkillIndex = pMob[mob].MOB.SkillBar[1];
//			}
//		}
//		else
//		{
//			Resist = g_pSpell[pMob[mob].MOB.SkillBar[0]].InstanceType - 2;
//			sm->SkillIndex = pMob[mob].MOB.SkillBar[0];
//		}
//	}
//
//	int fisdam = pMob[mob].MOB.CurrentScore.Damage;
//	fisdam = BASE_GetDamage(fisdam, pMob[target].MOB.CurrentScore.Ac, 0);
//
//	if (Resist >= 0 && Resist <= 3)
//		fisdam = (200 - pMob[target].MOB.Resist[Resist]) * fisdam / 100;
//
//	if (fisdam > 0 && target < MAX_USER)
//	{
//		if (pMob[target].ReflectDamage > 0)
//		{
//			fisdam -= pMob[target].ReflectDamage;
//			if (fisdam <= 0)
//				fisdam = 1;
//		}
//	}
//
//	if (fisdam > 0)
//	{
//		if ((mob < MAX_USER || pMob[mob].MOB.Clan == 4) && (target < MAX_USER || pMob[target].MOB.Clan == 4))
//		{
//			fisdam = 3 * fisdam / 10;
//
//			if (GetAttribute(pMob[target].TargetX, pMob[target].TargetY) & 1 || !(GetAttribute(pMob[target].TargetX, pMob[target].TargetY) & 0x40))
//				fisdam = 0;
//			if (GetAttribute(pMob[mob].TargetX, pMob[mob].TargetY) & 1 || !(GetAttribute(pMob[mob].TargetX, pMob[mob].TargetY) & 0x40))
//				fisdam = 0;
//		}
//
//		int mob_leader = pMob[mob].Leader;
//		if (!mob_leader)
//			mob_leader = mob;
//
//		int target_leader = pMob[target].Leader;
//		if (!target_leader)
//			target_leader = target;
//
//		int mob_guild = pMob[mob].MOB.Guild;
//		int target_guild = pMob[target].MOB.Guild;
//
//		if (!mob_guild && !target_guild)
//			mob_guild = -1;
//
//		if (target < MAX_USER)
//		{
//			if (pMob[target].GuildDisable)
//				target_guild = -2;
//		}
//		if (mob_leader == target_leader || mob_guild == target_guild)
//		{
//			pMob[mob].CurrentTarget = 0;
//			fisdam = 0;
//		}
//	}
//
//	sm->CurrentHp = -1;
//	sm->Progress = 52428;
//	sm->Dam[0].Damage = fisdam;
//}

void GetAttackArea(int mob, MSG_Attack* sm)
{
	sm->ID = ESCENE_FIELD;
	sm->AttackerID = mob;
	sm->ClientTick = CurrentTime;
	sm->PosX = pMob[mob].TargetX;
	sm->PosY = pMob[mob].TargetY;
	sm->Size = sizeof(MSG_Attack);
	sm->Type = _MSG_Attack;

	sm->DoubleCritical = 0;
	sm->CurrentMp = -1;
	sm->ReqMp = -1;

	for (int i = 0; i < MAX_TARGET; i++)
	{
		sm->Dam[i].TargetID = 0;
		sm->Dam[i].Damage = 0;

		sm->Dam[i].TargetID = pMob[mob].EnemyList[i];

		if (sm->Dam[i].TargetID < 0 || sm->Dam[i].TargetID >= MAX_MOB)
			sm->Dam[i].TargetID = 0;
	}
	int Resist = -1;

	sm->SkillParm = 0;
	sm->SkillIndex = -1;
	sm->Motion = rand() % 3 + 4;

	for (int i = 0; i < MAX_TARGET; i++)
	{
		if (sm->Dam[i].TargetID == 0)
			continue;

		sm->TargetX = pMob[sm->Dam[i].TargetID].TargetX;
		sm->TargetY = pMob[sm->Dam[i].TargetID].TargetY;

		int special = 0;
		int special2 = 0;

		if (mob >= MAX_USER)
		{
			int dis = BASE_GetDistance(pMob[mob].TargetX, pMob[mob].TargetY, pMob[sm->Dam[i].TargetID].TargetX, pMob[sm->Dam[i].TargetID].TargetY);
			if (dis >= 3)
			{
				special = pMob[mob].MOB.BaseScore.Special[2];//pMob[mob].MOB.SkillBar[2];
				special2 = pMob[mob].MOB.BaseScore.Special[3]; //pMob[mob].MOB.SkillBar[3];
			}
			else
			{
				special = pMob[mob].MOB.BaseScore.Special[0];//pMob[mob].MOB.SkillBar[0];
				special2 = pMob[mob].MOB.BaseScore.Special[1];//pMob[mob].MOB.SkillBar[1];
			}

			sm->Motion = 0;

			if (special == 255)
				special = -1;

			switch (special)
			{
			case 121:
				sm->SkillIndex = 103;
				sm->SkillParm = 5;
				break;
			case 122:
				sm->SkillIndex = 105;
				sm->SkillParm = 1;
				break;
			case 123:
				sm->SkillIndex = 101;
				sm->SkillParm = 1;
				break;
			case 124:
				sm->SkillIndex = 101;
				sm->SkillParm = 2;
				break;
			case 125:
				sm->SkillIndex = 40;
				sm->SkillParm = 1;
				break;
			case 126:
				sm->SkillIndex = 40;
				sm->SkillParm = 2;
				break;
			case 127:
				sm->SkillIndex = 40;
				sm->SkillParm = 3;
				break;
			case 128:
				sm->SkillIndex = 33;
				sm->SkillParm = -4;
				sm->Motion = -4;
				break;
			default:
				sm->SkillIndex = special;
				sm->SkillParm = 1;
				break;
			}
			if (special2)
			{
				sm->Motion = 4;
				int _rand = rand() % 4;

				switch (special2)
				{
				case 3:
					if (_rand <= 1)
						sm->Motion++;
					break;
				case 6:
					if (_rand > 1)
						sm->Motion += 2;
					else
						sm->Motion++;
					break;
				case 7:
					if (_rand == 1)
						sm->Motion++;
					else
						sm->Motion += 2;
					break;
				case 15:
					switch (_rand)
					{
					case 1:
						sm->Motion++;
						break;
					case 2:
						sm->Motion += 2;
						break;
					case 3:
						sm->Motion += 3;
						break;
					}
					break;
				case 24:
					if (_rand > 1)
						sm->Motion += 4;
					else
						sm->Motion += 3;
					break;
				case 27:
					switch (_rand)
					{
					case 1:
						sm->Motion++;
						break;
					case 2:
						sm->Motion += 3;
						break;
					case 3:
						sm->Motion += 4;
						break;
					}
					break;
				case 23:
					switch (_rand)
					{
					case 1:
						sm->Motion++;
						break;
					case 2:
						sm->Motion += 2;
						break;
					case 3:
						sm->Motion += 4;
						break;
					}
					break;

				default:
					sm->SkillParm = 1;
					break;
				}
			}
			int rand_ = rand() % 100;
			if (pMob[mob].MOB.SkillBar[3] != 255 && rand_ >= 25 && rand_ <= 64)
			{
				int skillb3 = pMob[mob].MOB.SkillBar[3];

				int insttype = g_pSpell[skillb3].InstanceType;

				int leader = pMob[mob].Leader;
				if (leader <= 0)
					leader = mob;

				int hp = pMob[mob].MOB.CurrentScore.Hp;
				hp *= 10;
				hp /= pMob[mob].MOB.CurrentScore.MaxHp + 1;

				int lhp = pMob[leader].MOB.CurrentScore.Hp;
				lhp *= 10;
				lhp /= pMob[leader].MOB.CurrentScore.MaxHp + 1;

				if (insttype == 6)
				{
					if (hp <= 8 || lhp <= 8)
					{
						int _mob = 0;

						sm->SkillIndex = insttype;

						_mob = mob;
						if (hp > lhp)
							_mob = leader;


						sm->Dam[0].TargetID = _mob;
						sm->Dam[0].Damage = pMob[_mob].MOB.CurrentScore.MaxHp / 10;

						return;
					}
				}
			}
			if (pMob[mob].MOB.SkillBar[0] == 255 || rand_ < 0 || rand_ > 49)
			{
				if (pMob[mob].MOB.SkillBar[1] == 255 || rand_ < 50 || rand_ > 84)
				{
					if (pMob[mob].MOB.SkillBar[2] != 255 && rand_ >= 85 && rand_ <= 99)
					{
						Resist = g_pSpell[pMob[mob].MOB.SkillBar[2]].InstanceType - 2;
						sm->SkillIndex = pMob[mob].MOB.SkillBar[2];
					}
				}
				else
				{
					Resist = g_pSpell[pMob[mob].MOB.SkillBar[1]].InstanceType - 2;
					sm->SkillIndex = pMob[mob].MOB.SkillBar[1];
				}
			}
			else
			{
				Resist = g_pSpell[pMob[mob].MOB.SkillBar[0]].InstanceType - 2;
				sm->SkillIndex = pMob[mob].MOB.SkillBar[0];
			}
		}

		int fisdam = pMob[mob].MOB.CurrentScore.Damage;
		fisdam = BASE_GetDamage(fisdam, pMob[sm->Dam[i].TargetID].MOB.CurrentScore.Ac, 0);

		if (Resist >= 0 && Resist <= 3)
			fisdam = (200 - pMob[sm->Dam[i].TargetID].MOB.Resist[Resist]) * fisdam / 100;

		if (fisdam > 0 && sm->Dam[i].TargetID < MAX_USER)
		{
			if (pMob[sm->Dam[i].TargetID].ReflectDamage > 0)
			{
				fisdam -= pMob[sm->Dam[i].TargetID].ReflectDamage;
				if (fisdam < 0)
					fisdam = 0;
			}
		}

		if (fisdam > 0)
		{
			if ((mob < MAX_USER || pMob[mob].MOB.Clan == 4) && (sm->Dam[i].TargetID < MAX_USER || pMob[sm->Dam[i].TargetID].MOB.Clan == 4))
			{
				fisdam = 3 * fisdam / 10;

				if (GetAttribute(pMob[sm->Dam[i].TargetID].TargetX, pMob[sm->Dam[i].TargetID].TargetY) & 1 || !(GetAttribute(pMob[sm->Dam[i].TargetID].TargetX, pMob[sm->Dam[i].TargetID].TargetY) & 0x40))
					fisdam = 0;
				if (GetAttribute(pMob[mob].TargetX, pMob[mob].TargetY) & 1 || !(GetAttribute(pMob[mob].TargetX, pMob[mob].TargetY) & 0x40))
					fisdam = 0;
			}

			int mob_leader = pMob[mob].Leader;
			if (!mob_leader)
				mob_leader = mob;

			int target_leader = pMob[sm->Dam[i].TargetID].Leader;
			if (!target_leader)
				target_leader = sm->Dam[i].TargetID;

			int mob_guild = pMob[mob].MOB.Guild;
			int target_guild = pMob[sm->Dam[i].TargetID].MOB.Guild;

			if (!mob_guild && !target_guild)
				mob_guild = -1;

			if (sm->Dam[i].TargetID < MAX_USER)
			{
				if (pMob[sm->Dam[i].TargetID].GuildDisable)
					target_guild = -2;
			}
			if (mob_leader == target_leader || mob_guild == target_guild)
			{
				pMob[mob].CurrentTarget = 0;
				fisdam = 0;
			}
		}

		sm->Dam[i].Damage = fisdam;
	}
}


void GetGuild(int conn)
{
	STRUCT_ITEM* item = &pMob[conn].MOB.Equip[12];

	int guild = pMob[conn].MOB.Guild;
}

int GetGuild(STRUCT_ITEM* item)
{
	int guild = BASE_GetGuild(item);

	return guild;
}

BOOL GetEmptyItemGrid(int* gridx, int* gridy)
{
	if ((pItemGrid[*gridy][*gridx] == 0) && (pHeightGrid[*gridy][*gridx] != 127))
		return TRUE;

	for (int y = (*gridy) - 1; y <= (*gridy) + 1; y++)
	{
		for (int x = (*gridx) - 1; x <= (*gridx) + 1; x++)
		{
			if (x < 0 || y < 0 || x >= MAX_GRIDX || y >= MAX_GRIDY)
				continue;

			if (pItemGrid[y][x] == 0 && pHeightGrid[y][x] != 127)
			{
				*gridy = y;
				*gridx = x;

				return TRUE;
			}
		}
	}

	return FALSE;
}
//mob yoko
BOOL GetEmptyMobGrid(int mob, int* tx, int* ty)
{
	//int Index, unsigned int* posX, unsigned int* posY
	if (*tx < 0 || *tx >= 4096 || *ty < 0 || *ty >= 4096)
		return false;

	if (pMobGrid[*ty][*tx] == mob)
		return true;

	int LOCAL1 = pMobGrid[*ty][*tx];

	if (LOCAL1 < 0 || LOCAL1 >= MAX_MOB)
	{
		pMobGrid[*ty][*tx] = 0;
		LOCAL1 = 0;
	}

	if (pMob[LOCAL1].Mode == 0)
	{
		pMobGrid[*ty][*tx] = 0;
		LOCAL1 = 0;
	}

	if (LOCAL1 == 0)
	{
		if (pHeightGrid[*ty][*tx] != 127)
			return true;
	}

	for (unsigned int nY = (*ty - 1); nY <= (*ty + 1); nY++)
	{
		for (unsigned int nX = (*tx - 1); nX <= (*tx + 1); nX++)
		{
			if (nX >= 4096 || nY >= 4096)
				continue;

			if (pMobGrid[nY][nX] == 0)
			{
				if (pHeightGrid[nY][nX] != 127)
				{
					*tx = nX;
					*ty = nY;
					return true;
				}
			}
		}
	}

	for (unsigned int nY = (*ty - 2); nY <= (*ty + 2); nY++)
	{
		for (unsigned int nX = (*tx - 2); nX <= (*tx + 2); nX++)
		{
			if (nX >= 4096 || nY >= 4096)
				continue;

			if (pMobGrid[nY][nX] == 0)
			{
				if (pHeightGrid[nY][nX] != 127)
				{
					*tx = nX;
					*ty = nY;
					return true;
				}
			}
		}
	}

	for (unsigned int nY = (*ty - 3); nY <= (*ty + 3); nY++)
	{
		for (unsigned int nX = (*tx - 3); nX <= (*tx + 3); nX++)
		{
			if (nX < 0 || nY < 0 || nX >= 4096 || nY >= 4096)
				continue;

			if (pMobGrid[nY][nX] == 0)
			{
				if (pHeightGrid[nY][nX] != 127)
				{
					*tx = nX;
					*ty = nY;
					return true;
				}
			}
		}
	}

	for (unsigned int nY = (*ty - 4); nY <= (*ty + 4); nY++)
	{
		for (unsigned int nX = (*tx - 4); nX <= (*tx + 4); nX++)
		{
			if (nX < 0 || nY < 0 || nX >= 4096 || nY >= 4096)
				continue;

			if (pMobGrid[nY][nX] == 0)
			{
				if (pHeightGrid[nY][nX] != 127)
				{
					*tx = nX;
					*ty = nY;
					return true;
				}
			}
		}
	}

	for (unsigned int nY = (*ty - 5); nY <= (*ty + 5); nY++)
	{
		for (unsigned int nX = (*tx - 5); nX <= (*tx + 5); nX++)
		{
			if (nX < 0 || nY < 0 || nX >= 4096 || nY >= 4096)
				continue;

			if (pMobGrid[nY][nX] == 0)
			{
				if (pHeightGrid[nY][nX] != 127)
				{
					*tx = nX;
					*ty = nY;
					return true;
				}
			}
		}
	}

	return false;
}

//BOOL GetEmptyMobGrid(int mob, int *tx, int *ty)
//{
//	if (*tx < 0 || *ty < 0 || *tx >= MAX_GRIDX || *ty >= MAX_GRIDY)
//	{
//		Log("GetEmptyMobGridOut of range", "-system", 0);
//
//		return FALSE;
//	}
//
//	if (pMobGrid[*ty][*tx] == mob)
//		return TRUE;
//
//	if (pMobGrid[*ty][*tx] == 0 && pHeightGrid[*ty][*tx] != 127)
//		return TRUE;
//
//	int y = 0;
//	int x = 0;
//
//	for (y = (*ty) - 1; y <= (*ty) + 1; y++)
//	{
//		for (x = (*tx) - 1; x <= (*tx) + 1; x++)
//		{
//			if (x < 0 || y < 0 || x >= MAX_GRIDX || y >= MAX_GRIDY)
//				continue;
//
//			if (pMobGrid[y][x] != 0)
//				continue;
//
//			if (pHeightGrid[*ty][*tx] == 127)
//				continue;
//
//			*ty = y;
//			*tx = x;
//
//			return TRUE;
//		}
//	}
//
//	for (y = (*ty) - 2; y <= (*ty) + 2; y++)
//	{
//		for (x = (*tx) - 2; x <= (*tx) + 2; x++)
//		{
//			if (x < 0 || y < 0 || x >= MAX_GRIDX || y >= MAX_GRIDY)
//				continue;
//
//			if (pMobGrid[y][x] != 0)
//				continue;
//
//			if (pHeightGrid[*ty][*tx] == 127)
//				continue;
//
//			*ty = y;
//			*tx = x;
//
//			return TRUE;
//		}
//	}
//
//	for (y = (*ty) - 3; y <= (*ty) + 3; y++)
//	{
//		for (int x = (*tx) - 3; x <= (*tx) + 3; x++)
//		{
//			if (x < 0 || y < 0 || x >= MAX_GRIDX || y >= MAX_GRIDY)
//				continue;
//
//			if (pMobGrid[y][x] != 0)
//				continue;
//
//			if (pHeightGrid[*ty][*tx] == 127)
//				continue;
//
//			*ty = y;
//			*tx = x;
//
//			return TRUE;
//		}
//	}
//
//	for (y = (*ty) - 4; y <= (*ty) + 4; y++)
//	{
//		for (int x = (*tx) - 4; x <= (*tx) + 4; x++)
//		{
//			if (x < 0 || y < 0 || x >= MAX_GRIDX || y >= MAX_GRIDY)
//				continue;
//
//			if (pMobGrid[y][x] != 0)
//				continue;
//
//			if (pHeightGrid[*ty][*tx] == 127)
//				continue;
//
//			*ty = y;
//			*tx = x;
//
//			return TRUE;
//		}
//	}
//
//	for (y = (*ty) - 5; y <= (*ty) + 5; y++)
//	{
//		for (int x = (*tx) - 5; x <= (*tx) + 5; x++)
//		{
//			if (x < 0 || y < 0 || x >= MAX_GRIDX || y >= MAX_GRIDY)
//				continue;
//
//			if (pMobGrid[y][x] != 0)
//				continue;
//
//			if (pHeightGrid[*ty][*tx] == 127)
//				continue;
//
//			*ty = y;
//			*tx = x;
//
//			return TRUE;
//		}
//	}
//
//	return FALSE;
//}

BOOL GetEmptyMobGridGreat(int mob, int* tx, int* ty)
{
	if (*tx < 0 || *ty < 0 || *tx >= MAX_GRIDX || *ty >= MAX_GRIDY)
	{
		Log("GetEmptyMobGridOut of range", "-system", 0);

		return FALSE;
	}

	if (pMobGrid[*ty][*tx] == mob)
		return TRUE;

	if (pMobGrid[*ty][*tx] == 0 && pHeightGrid[*ty][*tx] != 127)
		return TRUE;

	int y = 0;
	int x = 0;

	for (int k = 0; k < 30; k++)
	{
		for (y = (*ty) - k; y <= (*ty) + k; y++)
		{
			for (x = (*tx) - k; x <= (*tx) + k; x++)
			{
				if (x < 0 || y < 0 || x >= MAX_GRIDX || y >= MAX_GRIDY)
					continue;

				if (pMobGrid[y][x] != 0)
					continue;

				if (pHeightGrid[*ty][*tx] == 127)
					continue;

				*ty = y;
				*tx = x;

				return TRUE;
			}
		}
	}
	return FALSE;
}

int GetCurKill(int conn)
{
	if (conn <= 0 || conn >= MAX_USER)
		return 0;

	unsigned char cv = pMob[conn].MOB.Carry[KILL_MARK].stEffect[0].cValue;

	int ret = cv;

	return ret;
}

int GetTotKill(int conn)
{
	if (conn <= 0 || conn >= MAX_USER)
		return 0;

	unsigned char cv1 = pMob[conn].MOB.Carry[KILL_MARK].stEffect[1].cValue;
	unsigned char cv2 = pMob[conn].MOB.Carry[KILL_MARK].stEffect[2].cValue;

	int ret = cv1 + cv2 * 256;

	return ret;
}

void SetCurKill(int conn, int value)
{
	if (conn <= 0 || conn >= MAX_USER)
		return;

	if (value < 0)
		value = 0;

	if (value > 200)
		value = 200;

	unsigned char cv = value;

	pMob[conn].MOB.Carry[KILL_MARK].stEffect[0].cValue = cv;
}

void SetTotKill(int conn, int value)
{
	if (conn <= 0 || conn >= MAX_USER)
		return;

	if (value < 0)
		value = 0;

	if (value > 32767)
		value = 32767;

	unsigned char cv1 = value % 256;
	unsigned char cv2 = value / 256;

	pMob[conn].MOB.Carry[KILL_MARK].stEffect[1].cValue = cv1;
	pMob[conn].MOB.Carry[KILL_MARK].stEffect[2].cValue = cv2;
}

int	GetPKPoint(int conn)
{
	unsigned char cv = pMob[conn].MOB.Carry[KILL_MARK].stEffect[0].cEffect;

	int ret = cv;

	return ret;
}

int GetGuilty(int conn)
{
	unsigned char cv = pMob[conn].MOB.Carry[KILL_MARK].stEffect[1].cEffect;

	int ret = cv;

	if (ret > 50)
	{
		pMob[conn].MOB.Carry[KILL_MARK].stEffect[1].cEffect = 0;
		ret = 0;
	}

	return ret;
}

void SetGuilty(int conn, int value)
{
	if (conn <= 0 || conn >= MAX_USER)
		return;

	if (value < 0)
		value = 0;

	if (value > 50)
		value = 50;

	unsigned char cv = value;

	pMob[conn].MOB.Carry[KILL_MARK].stEffect[1].cEffect = cv;
}

void SetPKPoint(int conn, int value)
{
	if (conn <= 0 || conn >= MAX_USER)
		return;

	if (value < 1)
		value = 1;

	if (value > 150)
		value = 150;

	unsigned char cv = value;

	pMob[conn].MOB.Carry[KILL_MARK].stEffect[0].cEffect = cv;
}

int GetRecycleBin(int conn, STRUCT_ITEM* kItem, int Price)
{
	if (conn <= 0 || conn >= MAX_USER)
		return 0;

	if (pUser[conn].Mode != USER_PLAY)
		return 0;

	int i = -1;

	for (int k = 0; k < MAX_ITEM_REBUY; k++)
	{
		auto My = pMob[conn].Rebuy[k];

		if (My.Item.sIndex <= 0 || My.Item.sIndex >= MAX_ITEMLIST)
		{
			i = k;

			break;
		}
	}

	if (i == -1)
	{
		for (int k = 0; k < MAX_ITEM_REBUY - 1; k++)
		{
			pMob[conn].Rebuy[k] = pMob[conn].Rebuy[k + 1];
		}

		i = 9;

		pMob[conn].Rebuy[i].Price = Price;
		memcpy(&pMob[conn].Rebuy[i].Item, kItem, sizeof(STRUCT_ITEM));
		pMob[conn].Rebuy[i].Ticks = rand() % 100000;

		return 1;
	}

	pMob[conn].Rebuy[i].Price = Price;
	memcpy(&pMob[conn].Rebuy[i].Item, kItem, sizeof(STRUCT_ITEM));
	pMob[conn].Rebuy[i].Ticks = rand() % 100000;

	return 1;
}

BOOL GetEmptyMobGridShort(int mob, int* tx, int* ty)
{
	if (*tx < 0 || *ty < 0 || *tx >= MAX_GRIDX || *ty >= MAX_GRIDY)
	{
		Log("GetEmptyMobGridOut of range", "-system", 0);

		return FALSE;
	}

	if (pMobGrid[*ty][*tx] == mob)
		return TRUE;

	if (pMobGrid[*ty][*tx] == 0 && pHeightGrid[*ty][*tx] != 127)
		return TRUE;

	int y = 0;
	int x = 0;

	for (y = (*ty) - 4; y <= (*ty) + 4; y++)
	{
		for (x = (*tx) - 4; x <= (*tx) + 4; x++)
		{
			if (x < 0 || y < 0 || x >= MAX_GRIDX || y >= MAX_GRIDY)
				continue;

			if (pMobGrid[y][x] != 0)
				continue;

			if (pHeightGrid[*ty][*tx] == 127)
				continue;

			*ty = y;
			*tx = x;

			return TRUE;
		}
	}
	/*
	for (y = (*ty) - 2; y <= (*ty) + 2; y++)
	{
	for (x = (*tx) - 2; x <= (*tx) + 2; x++)
	{
	if (x < 0 || y < 0 || x >= MAX_GRIDX || y >= MAX_GRIDY)
	continue;

	if (pMobGrid[y][x] != 0)
	continue;

	if (pHeightGrid[*ty][*tx] == 127)
	continue;

	*ty = y;
	*tx = x;

	return TRUE;
	}
	}

	for (y = (*ty) - 3; y <= (*ty) + 3; y++)
	{
	for (int x = (*tx) - 3; x <= (*tx) + 3; x++)
	{
	if (x < 0 || y < 0 || x >= MAX_GRIDX || y >= MAX_GRIDY)
	continue;

	if (pMobGrid[y][x] != 0)
	continue;

	if (pHeightGrid[*ty][*tx] == 127)
	continue;

	*ty = y;
	*tx = x;

	return TRUE;
	}
	}

	for (y = (*ty) - 4; y <= (*ty) + 4; y++)
	{
	for (int x = (*tx) - 4; x <= (*tx) + 4; x++)
	{
	if (x < 0 || y < 0 || x >= MAX_GRIDX || y >= MAX_GRIDY)
	continue;

	if (pMobGrid[y][x] != 0)
	continue;

	if (pHeightGrid[*ty][*tx] == 127)
	continue;

	*ty = y;
	*tx = x;

	return TRUE;
	}
	}
	*/
	return FALSE;
}

int ReadMacList(char* macAddress)
{
	FILE* arq = NULL;
	fopen_s(&arq, "../../Common/MacList.txt", "r");

	if (!arq)
	{
		MessageBoxA(0, "Arquivo não encontrado", "../../Common/MacList.txt", 0);
		ExitProcess(1);
	}

	char line[100];
	memset(&line, 0, 100);

	char mac[25];
	memset(&mac, 0, 25);

	while ((fscanf(arq, "%[^\n]", line)) != EOF)
	{
		fgetc(arq);
		sscanf(line, "%s", &mac);

		if (!strcmp(mac, macAddress))
		{
			fclose(arq);
			return 1;
		}
	}

	fclose(arq);
	return -1;
}

void MacBan(int conn)
{
	if (conn <= NULL || conn >= MAX_USER)
		return;

	FILE* Arquivo;

	fopen_s(&Arquivo, "../../Common/MacList.txt", "a+");

	if (!Arquivo)
	{
		MessageBoxA(0, "Arquivo não encontrado", "../../Common/MacList.txt", 0);
		ExitProcess(1);
		false;
	}

	char update[20];
	memset(update, 0, 20);
	sprintf_s(update, "%s \n", pUser[conn].MacAddress);
	fputs(update, Arquivo);
	fclose(Arquivo);

	CloseUser(conn);
	return;
}

void GetPlayerON()
{
	for (int i = 0; i < MAX_USER; i++)
	{
		if (pUser[i].Mode != USER_PLAY)
			continue;
	}
}
