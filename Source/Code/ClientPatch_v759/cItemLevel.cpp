#include "main.h" 
#include "UISlot.h"
#include "UIItem.h"
#include "UIControl.h"

void ExecItemLevel()
{

	auto player = GetChar();

	if (g_pClientInfo->Info.chave1 == 0 && g_pClientInfo->Info.Keys[0] >= 0) {
		ConfigR::WindowControl = 9;

		ConfigR::ShopItemQnt = 1;

		auto PainelJephi = g_pInterface->Instance()->getGuiFromHandle<UIControl>(117900);
		PainelJephi->IsVisible = true;

		auto Text = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(117930);
		Text->setConstString("Escolha um dos itens para receber");
		Text->setTextColor(TNColor::CornBlue);

		STRUCT_ITEM item[5];
		int Index[5] = { 0, 0, 0, 0, 0 };

		if (player.Class == 0) //TK
		{
			Index[0] = 938;
			Index[1] = 941;
			Index[2] = 942;
			Index[3] = 944;
			Index[4] = 945;
		}
		if (player.Class == 1) //FM
		{
			Index[0] = 940;
			Index[1] = 943;
			Index[2] = 0;
			Index[3] = 0;
			Index[4] = 0;
		}
		if (player.Class == 2) //BM
		{
			Index[0] = 938;
			Index[1] = 941;
			Index[2] = 942;
			Index[3] = 939;
			Index[4] = 0;
		}
		if (player.Class == 3) //HT
		{
			Index[0] = 939;
			Index[1] = 938;
			Index[2] = 943;
			Index[3] = 0;
			Index[4] = 0;
		}

		for (int i = 0; i < 5; i++) {
			auto JephiGrid = g_pInterface->Instance()->getGuiFromHandle<UISlot>(117901 + i);
			*(int*)((int)JephiGrid + 0x400) = 0x5;
			JephiGrid->deleteItemGui(0, 0);

			memset(&item[i], 0, sizeof(STRUCT_ITEM));
			item[i].sIndex = Index[i];
			ConfigR::ItemLevel[i] = Index[i];

			if (Index[i] == 938 || Index[i] == 939)
				ConfigR::ShopItemQnt = 2;

			if (item[i].sIndex != 0)
				JephiGrid->setGui((int)JephiGrid->New(item[i], 0, 0), 0, 0);
		}
		return;
	}
	if (g_pClientInfo->Info.chave1 == 1 && g_pClientInfo->Info.Keys[0] >= 0) {
		ConfigR::WindowControl = 9;

		ConfigR::ShopItemQnt = 1;

		auto PainelJephi = g_pInterface->Instance()->getGuiFromHandle<UIControl>(117900);
		PainelJephi->IsVisible = true;

		auto Text = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(117930);
		Text->setConstString("Clique no item para receber");
		Text->setTextColor(TNColor::CornBlue);

		STRUCT_ITEM item[5];
		int Index[5] = { 3980, 0, 0, 0, 0 };

		for (int i = 0; i < 5; i++) {
			auto JephiGrid = g_pInterface->Instance()->getGuiFromHandle<UISlot>(117901 + i);
			*(int*)((int)JephiGrid + 0x400) = 0x5;
			JephiGrid->deleteItemGui(0, 0);

			memset(&item[i], 0, sizeof(STRUCT_ITEM));
			item[i].sIndex = Index[i];
			ConfigR::ItemLevel[i] = Index[i];

			if (item[i].sIndex != 0)
				JephiGrid->setGui((int)JephiGrid->New(item[i], 0, 0), 0, 0);
		}
		return;
	}
	if (g_pClientInfo->Info.chave1 == 2 && g_pClientInfo->Info.Keys[0] >= 113) {
		ConfigR::WindowControl = 9;

		ConfigR::ShopItemQnt = 1;

		auto PainelJephi = g_pInterface->Instance()->getGuiFromHandle<UIControl>(117900);
		PainelJephi->IsVisible = true;

		auto Text = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(117930);
		Text->setConstString("Escolha um dos itens para receber");
		Text->setTextColor(TNColor::CornBlue);

		STRUCT_ITEM item[5];
		int Index[5] = { 2373, 2368, 0, 0, 0 };		

		for (int i = 0; i < 5; i++) {
			
			auto JephiGrid = g_pInterface->Instance()->getGuiFromHandle<UISlot>(117901 + i);
			*(int*)((int)JephiGrid + 0x400) = 0x5;
			JephiGrid->deleteItemGui(0, 0);

			memset(&item[i], 0, sizeof(STRUCT_ITEM));
			item[i].sIndex = Index[i];
			ConfigR::ItemLevel[i] = Index[i];

			if (item[i].sIndex != 0) {
				item[i].stEffect[0].cEffect = 10;
				item[i].stEffect[0].cValue = 10;
				item[i].stEffect[1].cEffect = 10;
				item[i].stEffect[1].cValue = 10;
				item[i].stEffect[2].cEffect = 100;
				item[i].stEffect[2].cValue = 0;

				JephiGrid->setGui((int)JephiGrid->New(item[i], 0, 0), 0, 0);
			}
		}
		return;
	}
	if (g_pClientInfo->Info.chave1 == 3 && g_pClientInfo->Info.Keys[0] >= 124) {
		ConfigR::WindowControl = 9;

		ConfigR::ShopItemQnt = 1;

		auto PainelJephi = g_pInterface->Instance()->getGuiFromHandle<UIControl>(117900);
		PainelJephi->IsVisible = true;

		auto Text = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(117930);
		Text->setConstString("Clique em um dos itens para receber");
		Text->setTextColor(TNColor::CornBlue);

		STRUCT_ITEM Item[5];

		int Index[5] = { 0, 0, 0, 0, 0 };

		if (player.Class == 0) //TK
		{
			Index[0] = 1216;
			Index[1] = 1219;
			Index[2] = 1207;
			Index[3] = 1213;
			Index[4] = 1210;
		}
		if (player.Class == 1) //FM
		{
			Index[0] = 1351;
			Index[1] = 1354;
			Index[2] = 1342;
			Index[3] = 1348;
			Index[4] = 1345;
		}
		if (player.Class == 2) //BM
		{
			Index[0] = 1501;
			Index[1] = 1504;
			Index[2] = 1492;
			Index[3] = 1498;
			Index[4] = 1495;
		}
		if (player.Class == 3) //HT
		{
			Index[0] = 1651;
			Index[1] = 1654;
			Index[2] = 1642;
			Index[3] = 1648;
			Index[4] = 1645;
		}

		for (int i = 0; i < 5; i++) {
			auto JephiGrid = g_pInterface->Instance()->getGuiFromHandle<UISlot>(117901 + i);
			*(int*)((int)JephiGrid + 0x400) = 0x5;
			JephiGrid->deleteItemGui(0, 0);

			memset(&Item[i], 0, sizeof(STRUCT_ITEM));
			Item[i].sIndex = Index[i];
			ConfigR::ItemLevel[i] = Index[i];

			if (Item[i].sIndex != 0) {
				Item[i].stEffect[0].cEffect = 43;
				Item[i].stEffect[0].cValue = 3;
				Item[i].stEffect[1].cEffect = 0;
				Item[i].stEffect[1].cValue = 0;
				Item[i].stEffect[2].cEffect = 0;
				Item[i].stEffect[2].cValue = 0;
				JephiGrid->setGui((int)JephiGrid->New(Item[i], 0, 0), 0, 0);
			}
		}
		return;
	}
	if (g_pClientInfo->Info.chave1 == 4 && g_pClientInfo->Info.Keys[0] >= 143) {
		ConfigR::WindowControl = 9;

		ConfigR::ShopItemQnt = 1;

		auto PainelJephi = g_pInterface->Instance()->getGuiFromHandle<UIControl>(117900);
		PainelJephi->IsVisible = true;

		auto Text = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(117930);
		Text->setConstString("Escolha um dos itens para receber");
		Text->setTextColor(TNColor::CornBlue);

		STRUCT_ITEM Item[5];

		for (int i = 0; i < 5; i++)
			memset(&Item[i], 0, sizeof(STRUCT_ITEM));

		int Index[5] = { 0, 0, 0, 0, 0 };

		if (player.Class == 0) //TK
		{
			//MAGO
			if (player.BaseScore.Int > (player.BaseScore.Dex + player.BaseScore.Str)) {
				Index[0] = 854;
				Item[0].sIndex = 854;
				Item[0].stEffect[0].cEffect = 43;
				Item[0].stEffect[0].cValue = 5;
				Item[0].stEffect[1].cEffect = 60;
				Item[0].stEffect[1].cValue = 16;
				Item[0].stEffect[2].cEffect = 0;
				Item[0].stEffect[2].cValue = 0;
			}
			//DANO
			if (player.BaseScore.Int < (player.BaseScore.Dex + player.BaseScore.Str)) {
				Index[0] = 809;
				Index[1] = 809;
				Item[0].sIndex = 809;
				Item[1].sIndex = 809;

				for (int i = 0; i < 2; i++) {
					Item[i].stEffect[0].cEffect = 43;
					Item[i].stEffect[0].cValue = 5;
					Item[i].stEffect[1].cEffect = 2;
					Item[i].stEffect[1].cValue = 36;
					Item[i].stEffect[2].cEffect = 0;
					Item[i].stEffect[2].cValue = 0;
				}
			}
		}
		if (player.Class == 1) //FM
		{
			//MAGO
			if (player.BaseScore.Int > (player.BaseScore.Dex + player.BaseScore.Str)) {
				Index[0] = 2127;
				Item[0].sIndex = 2127;
				Item[0].stEffect[0].cEffect = 43;
				Item[0].stEffect[0].cValue = 5;
				Item[0].stEffect[1].cEffect = 60;
				Item[0].stEffect[1].cValue = 16;
				Item[0].stEffect[2].cEffect = 0;
				Item[0].stEffect[2].cValue = 0;
			}
			//DANO
			if (player.BaseScore.Int < (player.BaseScore.Dex + player.BaseScore.Str)) {
				Index[0] = 2122;
				Item[0].sIndex = 2122;
				Item[0].stEffect[0].cEffect = 43;
				Item[0].stEffect[0].cValue = 5;
				Item[0].stEffect[1].cEffect = 2;
				Item[0].stEffect[1].cValue = 36;
				Item[0].stEffect[2].cEffect = 0;
				Item[0].stEffect[2].cValue = 0;
			}
		}
		if (player.Class == 2) //BM
		{
			//MAGO
			if (player.BaseScore.Int > (player.BaseScore.Dex + player.BaseScore.Str)) {
				Index[0] = 854;
				Item[0].sIndex = 854;
				Item[0].stEffect[0].cEffect = 43;
				Item[0].stEffect[0].cValue = 5;
				Item[0].stEffect[1].cEffect = 60;
				Item[0].stEffect[1].cValue = 16;
				Item[0].stEffect[2].cEffect = 0;
				Item[0].stEffect[2].cValue = 0;
			}
			//DANO
			if (player.BaseScore.Int < (player.BaseScore.Dex + player.BaseScore.Str)) {
				Index[0] = 809;
				Index[1] = 809;
				Item[0].sIndex = 809;
				Item[1].sIndex = 809;

				for (int i = 0; i < 2; i++) {
					Item[i].stEffect[0].cEffect = 43;
					Item[i].stEffect[0].cValue = 5;
					Item[i].stEffect[1].cEffect = 2;
					Item[i].stEffect[1].cValue = 36;
					Item[i].stEffect[2].cEffect = 0;
					Item[i].stEffect[2].cValue = 0;
				}
			}
		}
		if (player.Class == 3) //HT
		{
			Index[0] = 2122;
			Item[0].sIndex = 2122;
			Item[0].stEffect[0].cEffect = 43;
			Item[0].stEffect[0].cValue = 5;
			Item[0].stEffect[1].cEffect = 2;
			Item[0].stEffect[1].cValue = 36;
			Item[0].stEffect[2].cEffect = 0;
			Item[0].stEffect[2].cValue = 0;
		}

		for (int i = 0; i < 5; i++) {
			auto JephiGrid = g_pInterface->Instance()->getGuiFromHandle<UISlot>(117901 + i);
			*(int*)((int)JephiGrid + 0x400) = 0x5;
			JephiGrid->deleteItemGui(0, 0);

			Item[i].sIndex = Index[i];
			ConfigR::ItemLevel[i] = Index[i];

			if (Item[i].sIndex != 0) {
				JephiGrid->setGui((int)JephiGrid->New(Item[i], 0, 0), 0, 0);
			}
		}
		return;
	}
	if (g_pClientInfo->Info.chave1 == 5 && g_pClientInfo->Info.Keys[0] >= 255) {
		ConfigR::WindowControl = 9;

		ConfigR::ShopItemQnt = 1;

		auto PainelJephi = g_pInterface->Instance()->getGuiFromHandle<UIControl>(117900);
		PainelJephi->IsVisible = true;

		auto Text = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(117930);
		Text->setConstString("Escolha um dos itens para receber");
		Text->setTextColor(TNColor::CornBlue);

		STRUCT_ITEM Item[5];

		for (int i = 0; i < 5; i++)
			memset(&Item[i], 0, sizeof(STRUCT_ITEM));

		int Index[5] = { 0, 0, 0, 0, 0 };

		if (player.Class == 0) //TK
		{
			//MAGO
			if (player.BaseScore.Int > (player.BaseScore.Dex + player.BaseScore.Str)) {
				Index[0] = 3566;
				Item[0].sIndex = 3566;
				Item[0].stEffect[0].cEffect = 43;
				Item[0].stEffect[0].cValue = 5;
				Item[0].stEffect[1].cEffect = 60;
				Item[0].stEffect[1].cValue = 16;
				Item[0].stEffect[2].cEffect = 0;
				Item[0].stEffect[2].cValue = 0;
			}
			//DANO
			if (player.BaseScore.Int < (player.BaseScore.Dex + player.BaseScore.Str)) {
				Index[0] = 3551;
				Index[1] = 3551;
				Item[0].sIndex = 3551;
				Item[1].sIndex = 3551;

				for (int i = 0; i < 2; i++) {
					Item[i].stEffect[0].cEffect = 43;
					Item[i].stEffect[0].cValue = 5;
					Item[i].stEffect[1].cEffect = 2;
					Item[i].stEffect[1].cValue = 36;
					Item[i].stEffect[2].cEffect = 0;
					Item[i].stEffect[2].cValue = 0;
				}
			}
		}
		if (player.Class == 1) //FM
		{
			//MAGO
			if (player.BaseScore.Int > (player.BaseScore.Dex + player.BaseScore.Str)) {
				Index[0] = 3582;
				Item[0].sIndex = 3582;
				Item[0].stEffect[0].cEffect = 43;
				Item[0].stEffect[0].cValue = 5;
				Item[0].stEffect[1].cEffect = 60;
				Item[0].stEffect[1].cValue = 16;
				Item[0].stEffect[2].cEffect = 0;
				Item[0].stEffect[2].cValue = 0;
			}
			//DANO
			if (player.BaseScore.Int < (player.BaseScore.Dex + player.BaseScore.Str)) {
				Index[0] = 3556;
				Item[0].sIndex = 3556;
				Item[0].stEffect[0].cEffect = 43;
				Item[0].stEffect[0].cValue = 5;
				Item[0].stEffect[1].cEffect = 2;
				Item[0].stEffect[1].cValue = 36;
				Item[0].stEffect[2].cEffect = 0;
				Item[0].stEffect[2].cValue = 0;
			}
		}
		if (player.Class == 2) //BM
		{
			//MAGO
			if (player.BaseScore.Int > (player.BaseScore.Dex + player.BaseScore.Str)) {
				Index[0] = 3566;
				Item[0].sIndex = 3566;
				Item[0].stEffect[0].cEffect = 43;
				Item[0].stEffect[0].cValue = 5;
				Item[0].stEffect[1].cEffect = 60;
				Item[0].stEffect[1].cValue = 16;
				Item[0].stEffect[2].cEffect = 0;
				Item[0].stEffect[2].cValue = 0;
			}
			//DANO
			if (player.BaseScore.Int < (player.BaseScore.Dex + player.BaseScore.Str)) {
				Index[0] = 3551;
				Index[1] = 3551;
				Item[0].sIndex = 3551;
				Item[1].sIndex = 3551;

				for (int i = 0; i < 2; i++) {
					Item[i].stEffect[0].cEffect = 43;
					Item[i].stEffect[0].cValue = 5;
					Item[i].stEffect[1].cEffect = 2;
					Item[i].stEffect[1].cValue = 36;
					Item[i].stEffect[2].cEffect = 0;
					Item[i].stEffect[2].cValue = 0;
				}
			}
		}
		if (player.Class == 3) //HT
		{
			Index[0] = 3556;
			Item[0].sIndex = 3556;
			Item[0].stEffect[0].cEffect = 43;
			Item[0].stEffect[0].cValue = 5;
			Item[0].stEffect[1].cEffect = 2;
			Item[0].stEffect[1].cValue = 36;
			Item[0].stEffect[2].cEffect = 0;
			Item[0].stEffect[2].cValue = 0;
		}

		for (int i = 0; i < 5; i++) {
			auto JephiGrid = g_pInterface->Instance()->getGuiFromHandle<UISlot>(117901 + i);
			*(int*)((int)JephiGrid + 0x400) = 0x5;
			JephiGrid->deleteItemGui(0, 0);

			Item[i].sIndex = Index[i];
			ConfigR::ItemLevel[i] = Index[i];

			if (Item[i].sIndex != 0) {
				JephiGrid->setGui((int)JephiGrid->New(Item[i], 0, 0), 0, 0);
			}
		}
		return;
	}
}