#include "main.h" 
#include "UISlot.h"
#include "UIItem.h"
#include "UIControl.h"
#include "ShopList.h"
#include <iostream>

#define DONATESTORE 1
#define FILTRODROP 2
#define DROPLIST 3
#define TELEPORT 4
#define RANKING 5
#define TOWERWAR 6
#define QUEST 7
#define JEPHI 8
#define ITEMLEVEL 9
#define SENDPIX 10
#define OPEMPIX 11

#define ARMIA 100
#define ARZAN 101
#define ERION 102
#define NOATUM 103
#define NIPPLE 104
#define OPENDROPLIST 105
#define FILTROBTN 106
#define OPENPVPRANKING 109
#define OPENRANKING 110

#define ENTERWORLD 10000
#define OPENSTORE 111
#define DONATEBUTTON 112
#define CLOSECHAT 113
#define DROPLISTBUTTON 114
#define JEPHIBUTTON 115
#define TRAJEBUTTON 116
#define CAPTCHABUTTON 117


BOOL __stdcall HKD_ControlEventClick(int Handle, int Scene)//by seitbnao
{
	//printf("\nHandle: %d Scene: %d\n", Handle, Scene);

	MSG_MessageWhisper  m;
	DWORD* pointer_gameinterface;

	auto p_Size = m.Size = sizeof(m);
	auto p_Packet = m.Type = _MSG_MessageWhisper;
	auto p_ClientID = m.ID = GetClientID();
	auto player = GetChar();
	auto isNovato = player.BaseScore.Level == 0;
	int conn = 0;
	int SendHandleID = -1;
	auto game = reinterpret_cast<GameInterface*>(pointer_gameinterface);

	auto PainelInv = g_pInterface->Instance()->getGuiFromHandle<UIControl>(589832);		

	auto painelteleport = g_pInterface->Instance()->getGuiFromHandle<UIControl>(98300);
	auto GamePainel = g_pInterface->Instance()->getGuiFromHandle<UIControl>(981300);
	auto StorePainel = g_pInterface->Instance()->getGuiFromHandle<UIControl>(199300);
	auto BuyConfirm = g_pInterface->Instance()->getGuiFromHandle<UIControl>(192500);
	auto DropList = g_pInterface->Instance()->getGuiFromHandle<UIControl>(179500);
	auto PainelPix = g_pInterface->Instance()->getGuiFromHandle<UIControl>(188500);
	auto PainelTrajes = g_pInterface->Instance()->getGuiFromHandle<UIControl>(1882000);
	//auto PainelRanking = g_pInterface->Instance()->getGuiFromHandle<UIControl>(1919400);
	auto PainelCaptcha = g_pInterface->Instance()->getGuiFromHandle<UIControl>(1319001);

	auto PainelJephi = g_pInterface->Instance()->getGuiFromHandle<UIControl>(117900);
	auto MailPainel = g_pInterface->Instance()->getGuiFromHandle<UIControl>(121200);
	auto MailButton = g_pInterface->Instance()->getGuiFromHandle<UIControl>(1212300);
	
	
	SendHandleID = Handle;

	if (SendHandleID == 65646)
		SendHandleID = ENTERWORLD;

	if (SendHandleID == 98301)
		SendHandleID = OPT1;

	if (SendHandleID == 98302)
		SendHandleID = OPT2;

	if (SendHandleID == 98303)
		SendHandleID = OPT3;

	if (SendHandleID == 98304)
		SendHandleID = OPT4;

	if (SendHandleID == 98305)
		SendHandleID = OPT5;

	if (SendHandleID == 98306)
		SendHandleID = OPT6;

	if (SendHandleID == 98307)
		SendHandleID = OPT7;

	if (SendHandleID == 98308)
		SendHandleID = OPT8;

	if (SendHandleID == 98309)
		SendHandleID = OPT9;

	if (SendHandleID == 98310)
		SendHandleID = OPT10;

	if (SendHandleID == 981301)
		SendHandleID = ARMIA;

	if (SendHandleID == 981302)
		SendHandleID = ARZAN;

	if (SendHandleID == 981303)
		SendHandleID = ERION;

	if (SendHandleID == 981304)
		SendHandleID = NOATUM;

	if (SendHandleID == 981305)
		SendHandleID = NIPPLE;

	if (SendHandleID == 981306)
		SendHandleID = OPENDROPLIST;

	if (SendHandleID == 981307)
		SendHandleID = FILTROBTN;

	if (SendHandleID == 981310)
		SendHandleID = OPENPVPRANKING;

	if (SendHandleID == 981311)
		SendHandleID = OPENRANKING;

	if (SendHandleID == 981308)
		SendHandleID = OPENSTORE;

	if (SendHandleID == 190201)
		SendHandleID = CLOSECHAT;

	if (SendHandleID == 188515)
		SendHandleID = SENDPIX;

	if (SendHandleID == 981309)
		SendHandleID = OPEMPIX;

	int DonateButton = 0;

	if (SendHandleID >= 199301 && SendHandleID <= 199315) {
		DonateButton = SendHandleID - 199301;
		SendHandleID = DONATEBUTTON;
	}

	int DropListButton = 0;

	if (SendHandleID >= 179501 && SendHandleID <= 179510) {
		DropListButton = SendHandleID - 179501;
		SendHandleID = DROPLISTBUTTON;
	}

	int JephiButton = 0;

	if (SendHandleID >= 117911 && SendHandleID <= 117915) {
		JephiButton = SendHandleID - 117911;
		SendHandleID = JEPHIBUTTON;
	}

	int TrajeButton = 0;
	if (SendHandleID >= 1883001 && SendHandleID <= 1883015) {
		TrajeButton = SendHandleID - 1883000;
		SendHandleID = TRAJEBUTTON;
	}

	int CaptchaButton = 0;
	if (SendHandleID >= 1319010 && SendHandleID <= 1319015) {
		CaptchaButton = SendHandleID - 1319010;
		SendHandleID = CAPTCHABUTTON;
	}

#pragma region Switch Botoes

	switch (SendHandleID)
	{

	case ENTERWORLD:
	{	
		StorePainel->IsVisible = false;
		painelteleport->IsVisible = false;
		GamePainel->IsVisible = false;
		BuyConfirm->IsVisible = false;
		DropList->IsVisible = false;
		PainelJephi->IsVisible = false;
		PainelPix->IsVisible = false;
		MailPainel->IsVisible = false;
		MailButton->IsVisible = false;
		PainelTrajes->IsVisible = false;
		//PainelRanking->IsVisible = false;
		//PainelCaptcha->IsVisible = false;
	}break;
	case TRAJEBUTTON :
	{
		AttTraje(g_pClientInfo->Info.Keys[TrajeButton]);
		auto PainelTrajes = g_pInterface->Instance()->getGuiFromHandle<UIControl>(1882000);
		PainelTrajes->IsVisible = false;
	}break;
	case CAPTCHABUTTON:
	{
		/*char words[24][6] = {
			"AVIÃO", "BARCO", "MOTO", "BIKE", "CARRO", "TREM",
			"CARRO", "TREM", "BIKE", "AVIÃO", "MOTO", "BARCO",
			"MOTO", "CARRO", "AVIÃO", "BARCO", "TREM", "BIKE",
			"BIKE", "AVIÃO", "TREM", "MOTO", "BARCO", "CARRO"
		};*/

		/*int Pos[4][6] = {
			{0,1,2,3,4,5},
			{6,7,8,9,10,11},
			{12,13,14,15,16,17},
			{18,19,20,21,22,23}
		};
		int Word = Pos[ConfigR::Captcha][CaptchaButton];*/
		int Alias = CaptchaButton + 100;
		ReqAlias(Alias);
		PainelCaptcha->IsVisible = false;
	}break;
	case OPENRANKING:
	{
		/*GamePainel->IsVisible = false;
		PainelRanking->IsVisible = true;
		ReqAlias(4);*/
	}break;
	case 1919430: //Ranking - Anterior
	{
		char Evolution[5][15] = { "Mortal", "Arch", "Celestial", "CelestialCS", "SubCelestial" };
		char Classe[4][4] = { "TK", "FM", "BM", "HT" };

		if (g_pClientInfo->Ranking.State == 0) {
			if (ConfigR::RankingPage >= 2) {
				auto Pos1 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(1919410);
				auto Pos2 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(1919411);
				auto Pos3 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(1919412);
				auto Pos4 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(1919413);
				auto Pos5 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(1919414);
				auto Pos6 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(1919415);
				auto Pos7 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(1919416);
				auto Pos8 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(1919417);
				auto Pos9 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(1919418);
				auto Pos10 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(1919419);
				auto Page = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(1919420);

				ConfigR::RankingPage = ConfigR::RankingPage - 1;

				int Pos = ConfigR::RankingPage * 10;
				Pos -= 10;

				Page->setConstString("%d", ConfigR::RankingPage);
				Pos1->setConstString("%d. [%s][%d][%s][%s]", 1 + Pos, g_pClientInfo->Ranking.RankName[0 + Pos], g_pClientInfo->Ranking.RankLevel[0 + Pos], Evolution[g_pClientInfo->Ranking.RankEvolution[0 + Pos] - 1], Classe[g_pClientInfo->Ranking.RankClasse[0 + Pos]]);
				Pos2->setConstString("%d. [%s][%d][%s][%s]", 2 + Pos, g_pClientInfo->Ranking.RankName[1 + Pos], g_pClientInfo->Ranking.RankLevel[1 + Pos], Evolution[g_pClientInfo->Ranking.RankEvolution[1 + Pos] - 1], Classe[g_pClientInfo->Ranking.RankClasse[1 + Pos]]);
				Pos3->setConstString("%d. [%s][%d][%s][%s]", 3 + Pos, g_pClientInfo->Ranking.RankName[2 + Pos], g_pClientInfo->Ranking.RankLevel[2 + Pos], Evolution[g_pClientInfo->Ranking.RankEvolution[2 + Pos] - 1], Classe[g_pClientInfo->Ranking.RankClasse[2 + Pos]]);
				Pos4->setConstString("%d. [%s][%d][%s][%s]", 4 + Pos, g_pClientInfo->Ranking.RankName[3 + Pos], g_pClientInfo->Ranking.RankLevel[3 + Pos], Evolution[g_pClientInfo->Ranking.RankEvolution[3 + Pos] - 1], Classe[g_pClientInfo->Ranking.RankClasse[3 + Pos]]);
				Pos5->setConstString("%d. [%s][%d][%s][%s]", 5 + Pos, g_pClientInfo->Ranking.RankName[4 + Pos], g_pClientInfo->Ranking.RankLevel[4 + Pos], Evolution[g_pClientInfo->Ranking.RankEvolution[4 + Pos] - 1], Classe[g_pClientInfo->Ranking.RankClasse[4 + Pos]]);
				Pos6->setConstString("%d. [%s][%d][%s][%s]", 6 + Pos, g_pClientInfo->Ranking.RankName[5 + Pos], g_pClientInfo->Ranking.RankLevel[5 + Pos], Evolution[g_pClientInfo->Ranking.RankEvolution[5 + Pos] - 1], Classe[g_pClientInfo->Ranking.RankClasse[5 + Pos]]);
				Pos7->setConstString("%d. [%s][%d][%s][%s]", 7 + Pos, g_pClientInfo->Ranking.RankName[6 + Pos], g_pClientInfo->Ranking.RankLevel[6 + Pos], Evolution[g_pClientInfo->Ranking.RankEvolution[6 + Pos] - 1], Classe[g_pClientInfo->Ranking.RankClasse[6 + Pos]]);
				Pos8->setConstString("%d. [%s][%d][%s][%s]", 8 + Pos, g_pClientInfo->Ranking.RankName[7 + Pos], g_pClientInfo->Ranking.RankLevel[7 + Pos], Evolution[g_pClientInfo->Ranking.RankEvolution[7 + Pos] - 1], Classe[g_pClientInfo->Ranking.RankClasse[7 + Pos]]);
				Pos9->setConstString("%d. [%s][%d][%s][%s]", 9 + Pos, g_pClientInfo->Ranking.RankName[8 + Pos], g_pClientInfo->Ranking.RankLevel[8 + Pos], Evolution[g_pClientInfo->Ranking.RankEvolution[8 + Pos] - 1], Classe[g_pClientInfo->Ranking.RankClasse[8 + Pos]]);
				Pos10->setConstString("%d. [%s][%d][%s][%s]", 10 + Pos, g_pClientInfo->Ranking.RankName[9 + Pos], g_pClientInfo->Ranking.RankLevel[9 + Pos], Evolution[g_pClientInfo->Ranking.RankEvolution[9 + Pos] - 1], Classe[g_pClientInfo->Ranking.RankClasse[9 + Pos]]);
			}
		}
	}break;
	case 1919431: //Ranking - Avançar
	{
		char Evolution[5][15] = { "Mortal", "Arch", "Celestial", "CelestialCS", "SubCelestial" };
		char Classe[4][4] = { "TK", "FM", "BM", "HT" };

		if (g_pClientInfo->Ranking.State == 0) {
			if (ConfigR::RankingPage < 5) {
				auto Pos1 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(1919410);
				auto Pos2 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(1919411);
				auto Pos3 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(1919412);
				auto Pos4 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(1919413);
				auto Pos5 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(1919414);
				auto Pos6 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(1919415);
				auto Pos7 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(1919416);
				auto Pos8 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(1919417);
				auto Pos9 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(1919418);
				auto Pos10 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(1919419);
				auto Page = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(1919420);

				ConfigR::RankingPage = ConfigR::RankingPage + 1;

				int Pos = ConfigR::RankingPage * 10;
				Pos -= 10;

				Page->setConstString("%d", ConfigR::RankingPage);
				Pos1->setConstString("%d. [%s][%d][%s][%s]", 1 + Pos, g_pClientInfo->Ranking.RankName[0 + Pos], g_pClientInfo->Ranking.RankLevel[0 + Pos], Evolution[g_pClientInfo->Ranking.RankEvolution[0 + Pos] - 1], Classe[g_pClientInfo->Ranking.RankClasse[0 + Pos]]);
				Pos2->setConstString("%d. [%s][%d][%s][%s]", 2 + Pos, g_pClientInfo->Ranking.RankName[1 + Pos], g_pClientInfo->Ranking.RankLevel[1 + Pos], Evolution[g_pClientInfo->Ranking.RankEvolution[1 + Pos] - 1], Classe[g_pClientInfo->Ranking.RankClasse[1 + Pos]]);
				Pos3->setConstString("%d. [%s][%d][%s][%s]", 3 + Pos, g_pClientInfo->Ranking.RankName[2 + Pos], g_pClientInfo->Ranking.RankLevel[2 + Pos], Evolution[g_pClientInfo->Ranking.RankEvolution[2 + Pos] - 1], Classe[g_pClientInfo->Ranking.RankClasse[2 + Pos]]);
				Pos4->setConstString("%d. [%s][%d][%s][%s]", 4 + Pos, g_pClientInfo->Ranking.RankName[3 + Pos], g_pClientInfo->Ranking.RankLevel[3 + Pos], Evolution[g_pClientInfo->Ranking.RankEvolution[3 + Pos] - 1], Classe[g_pClientInfo->Ranking.RankClasse[3 + Pos]]);
				Pos5->setConstString("%d. [%s][%d][%s][%s]", 5 + Pos, g_pClientInfo->Ranking.RankName[4 + Pos], g_pClientInfo->Ranking.RankLevel[4 + Pos], Evolution[g_pClientInfo->Ranking.RankEvolution[4 + Pos] - 1], Classe[g_pClientInfo->Ranking.RankClasse[4 + Pos]]);
				Pos6->setConstString("%d. [%s][%d][%s][%s]", 6 + Pos, g_pClientInfo->Ranking.RankName[5 + Pos], g_pClientInfo->Ranking.RankLevel[5 + Pos], Evolution[g_pClientInfo->Ranking.RankEvolution[5 + Pos] - 1], Classe[g_pClientInfo->Ranking.RankClasse[5 + Pos]]);
				Pos7->setConstString("%d. [%s][%d][%s][%s]", 7 + Pos, g_pClientInfo->Ranking.RankName[6 + Pos], g_pClientInfo->Ranking.RankLevel[6 + Pos], Evolution[g_pClientInfo->Ranking.RankEvolution[6 + Pos] - 1], Classe[g_pClientInfo->Ranking.RankClasse[6 + Pos]]);
				Pos8->setConstString("%d. [%s][%d][%s][%s]", 8 + Pos, g_pClientInfo->Ranking.RankName[7 + Pos], g_pClientInfo->Ranking.RankLevel[7 + Pos], Evolution[g_pClientInfo->Ranking.RankEvolution[7 + Pos] - 1], Classe[g_pClientInfo->Ranking.RankClasse[7 + Pos]]);
				Pos9->setConstString("%d. [%s][%d][%s][%s]", 9 + Pos, g_pClientInfo->Ranking.RankName[8 + Pos], g_pClientInfo->Ranking.RankLevel[8 + Pos], Evolution[g_pClientInfo->Ranking.RankEvolution[8 + Pos] - 1], Classe[g_pClientInfo->Ranking.RankClasse[8 + Pos]]);
				Pos10->setConstString("%d. [%s][%d][%s][%s]", 10 + Pos, g_pClientInfo->Ranking.RankName[9 + Pos], g_pClientInfo->Ranking.RankLevel[9 + Pos], Evolution[g_pClientInfo->Ranking.RankEvolution[9 + Pos] - 1], Classe[g_pClientInfo->Ranking.RankClasse[9 + Pos]]);
			}
		}
	}break;
	case 1212301:
	{
		ReqAlias(2);
		MailButton->IsVisible = false;
		MailPainel->IsVisible = true;
	}break;
	case 121201:
	{
		ReqAlias(3);
		MailButton->IsVisible = false;
		MailPainel->IsVisible = false;
	}break;
	case JEPHIBUTTON:
	{
		if (ConfigR::WindowControl == JEPHI) {
			if (JephiButton == 0 || JephiButton == 1) {
				ConfigR::Jephi = JephiButton;

				int Gold[2] = { 1000000, 500000 };
				int Index[2] = { 413, 412 };
				int sIndex[2] = { 420, 419 };

				BuyConfirm->IsVisible = true;
				PainelJephi->IsVisible = false;
				int Price = 10;

				ConfigR::ShopItemQnt = 1;

				STRUCT_ITEM item;
				memset(&item, 0, sizeof(STRUCT_ITEM));
				item.sIndex = Index[ConfigR::Jephi];

				auto BuyConfirmGrid = g_pInterface->Instance()->getGuiFromHandle<UISlot>(192520);
				*(int*)((int)BuyConfirmGrid + 0x400) = 0x5;
				BuyConfirmGrid->deleteItemGui(0, 0);
				BuyConfirmGrid->setGui((int)BuyConfirmGrid->New(item, 0, 0), 0, 0);

				int Qnt = 0;

				for (int i = 0; i < MAX_CARRY; i++) {
					if (player.Carry[i].sIndex == sIndex[ConfigR::Jephi])
						Qnt += player.Carry[i].stEffect[0].cValue;
				}

				auto ConfirmTx1 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(192530);
				ConfirmTx1->setConstString("%d", ConfigR::ShopItemQnt);
				ConfirmTx1->setTextColor(TNColor::CornBlue);

				auto ConfirmTx2 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(192531);
				ConfirmTx2->setConstString("Restos: %d", (Price * ConfigR::ShopItemQnt));
				ConfirmTx2->setTextColor(TNColor::CornBlue);

				auto ConfirmTx3 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(192532);
				ConfirmTx3->setConstString("Gold: %d", (ConfigR::ShopItemQnt * Gold[ConfigR::Jephi]));
				ConfirmTx3->setTextColor(TNColor::CornBlue);

				auto ConfirmTx4 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(192533);
				ConfirmTx4->setConstString("Restos Atual: %d", Qnt);
				ConfirmTx4->setTextColor(TNColor::CornBlue);

				if ((Qnt - Price) < 0)
					ConfirmTx4->setTextColor(TNColor::Red);
			}
			if (JephiButton == 2)
				SendJephi(692, 1);

			if (JephiButton == 3)
				SendJephi(1740, 10);

			if (JephiButton == 4)
				SendJephi(1741, 10);

		}
		if (ConfigR::WindowControl == ITEMLEVEL) {
			SendItemLevel(ConfigR::ItemLevel[JephiButton], ConfigR::ShopItemQnt);

			for (int i = 0; i < 5; i++) {
				auto JephiGrid = g_pInterface->Instance()->getGuiFromHandle<UISlot>(117901 + i);
				*(int*)((int)JephiGrid + 0x400) = 0x5;
				JephiGrid->deleteItemGui(0, 0);
			}

			PainelJephi->IsVisible = false;
		}
	}break;
	case OPEMPIX :
	{
		ConfigR::PixValue = 0;

		ReqAlias(1);

		GamePainel->IsVisible = false;
		PainelPix->IsVisible = true;
		auto PixTx1 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(188513);
		PixTx1->setConstString("%d", ConfigR::PixValue);
		PixTx1->setTextColor(TNColor::CornBlue);
				
		auto PixTx2 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(188514);
		PixTx2->setConstString("Sem Taxa");
		PixTx2->setTextColor(TNColor::CornBlue);

		auto PixTx3 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(188516);
		PixTx3->setConstString("Sua Chave: %s", g_pClientInfo->Info.Pix);
		PixTx3->setTextColor(TNColor::CornBlue);

		auto PixTx4 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(188517);
		PixTx4->setConstString("Diamantes: %d", g_pClientInfo->Info.Cash);
		PixTx4->setTextColor(TNColor::CornBlue);

	}break;
	case 188510:
	{
		ConfigR::PixValue += 100;

		auto PixTx1 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(188513);
		PixTx1->setConstString("%d", ConfigR::PixValue);
		PixTx1->setTextColor(TNColor::CornBlue);
	}break;
	case 188511:
	{
		ConfigR::PixValue += 1000;

		auto PixTx1 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(188513);
		PixTx1->setConstString("%d", ConfigR::PixValue);
		PixTx1->setTextColor(TNColor::CornBlue);
	}break;
	case 188512:
	{
		ConfigR::PixValue = 0;

		auto PixTx1 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(188513);
		PixTx1->setConstString("%d", ConfigR::PixValue);
		PixTx1->setTextColor(TNColor::CornBlue);
	}break;
	case SENDPIX:
	{
		auto Pix = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(188501);		
		SendPix(ConfigR::PixValue, Pix->getText());
	}break;
	case OPENDROPLIST:
	{
		auto Grupo = g_pInterface->Instance()->getGuiFromHandle<UIControl>(475136);
		auto Compositor = g_pInterface->Instance()->getGuiFromHandle<UIControl>(81921);
		auto Compositor2 = g_pInterface->Instance()->getGuiFromHandle<UIControl>(6432);
		auto Compositor3 = g_pInterface->Instance()->getGuiFromHandle<UIControl>(86017);
		auto xPainel = g_pInterface->Instance()->getGuiFromHandle<UIControl>(864);
		auto xPainel2 = g_pInterface->Instance()->getGuiFromHandle<UIControl>(1054256);
		auto Loja = g_pInterface->Instance()->getGuiFromHandle<UIControl>(65692);
		auto SkillLoja = g_pInterface->Instance()->getGuiFromHandle<UIControl>(65602);
		auto SkillInv = g_pInterface->Instance()->getGuiFromHandle<UIControl>(65567);
		auto cPainel = g_pInterface->Instance()->getGuiFromHandle<UIControl>(65696);
		auto Bau = g_pInterface->Instance()->getGuiFromHandle<UIControl>(65686);

		PainelInv->IsVisible = false;
		Grupo->IsVisible = false;
		Compositor->IsVisible = false;
		Compositor2->IsVisible = false;
		Compositor3->IsVisible = false;
		xPainel->IsVisible = false;
		xPainel2->IsVisible = false;
		Loja->IsVisible = false;
		SkillLoja->IsVisible = false;
		SkillInv->IsVisible = false;
		cPainel->IsVisible = false;
		Bau->IsVisible = false;		
		GamePainel->IsVisible = false;
		StorePainel->IsVisible = false;

		DropList->IsVisible = true;
		ConfigR::DropListPage = 0;
		ConfigR::DropListRegion = 0;

		auto NewWindowTX1 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(179511);
		auto NewWindowTX2 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(179512);
		auto NewWindowTX3 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(179513);
		auto NewWindowTX4 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(179514);
		auto NewWindowTX5 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(179515);
		auto NewWindowTX6 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(179516);
		auto NewWindowTX7 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(179517);
		auto NewWindowTX8 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(179518);
		auto NewWindowTX9 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(179519);
		auto NewWindowTX10 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(179520);

		NewWindowTX1->setConstString("Armia");
		NewWindowTX2->setConstString("Erion");
		NewWindowTX3->setConstString("Arzan");
		NewWindowTX4->setConstString("Deserto");
		NewWindowTX5->setConstString("Gelo");
		NewWindowTX6->setConstString("Dungeon");
		NewWindowTX7->setConstString("Submundo");
		NewWindowTX8->setConstString("Kefra");
		NewWindowTX9->setConstString("Lan N");
		NewWindowTX10->setConstString("Lan M");

		auto PageTx = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(179521);
		PageTx->setConstString("%d/2", (ConfigR::DropListPage + 1));
	}break;
	case 179531:
	{
		ConfigR::DropListPage++;

		if (ConfigR::DropListRegion == 0) {

			if (ConfigR::DropListPage > 1)
				ConfigR::DropListPage = 1;

			auto NewWindowTX1 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(179511);
			auto NewWindowTX2 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(179512);
			auto NewWindowTX3 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(179513);
			auto NewWindowTX4 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(179514);
			auto NewWindowTX5 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(179515);
			auto NewWindowTX6 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(179516);
			auto NewWindowTX7 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(179517);
			auto NewWindowTX8 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(179518);
			auto NewWindowTX9 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(179519);
			auto NewWindowTX10 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(179520);

			NewWindowTX1->setConstString("Lan A");
			NewWindowTX2->setConstString("Vale");
			NewWindowTX3->setConstString("");
			NewWindowTX4->setConstString("");
			NewWindowTX5->setConstString("");
			NewWindowTX6->setConstString("");
			NewWindowTX7->setConstString("");
			NewWindowTX8->setConstString("");
			NewWindowTX9->setConstString("");
			NewWindowTX10->setConstString("");

			auto PageTx = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(179521);
			PageTx->setConstString("%d/2", (ConfigR::DropListPage + 1));
		}
		if (ConfigR::DropListRegion != 0) {
			if (ConfigR::DropListPage >= ConfigR::DropListTpages - 1)
				ConfigR::DropListPage = ConfigR::DropListTpages - 1;

			auto NewWindowTX1 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(179511);
			auto NewWindowTX2 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(179512);
			auto NewWindowTX3 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(179513);
			auto NewWindowTX4 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(179514);
			auto NewWindowTX5 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(179515);
			auto NewWindowTX6 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(179516);
			auto NewWindowTX7 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(179517);
			auto NewWindowTX8 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(179518);
			auto NewWindowTX9 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(179519);
			auto NewWindowTX10 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(179520);

			int page = (ConfigR::DropListPage * 10);

			NewWindowTX1->setConstString("%s", g_pClientInfo->DropList.MobName[page + 0]);
			NewWindowTX2->setConstString("%s", g_pClientInfo->DropList.MobName[page + 1]);
			NewWindowTX3->setConstString("%s", g_pClientInfo->DropList.MobName[page + 2]);
			NewWindowTX4->setConstString("%s", g_pClientInfo->DropList.MobName[page + 3]);
			NewWindowTX5->setConstString("%s", g_pClientInfo->DropList.MobName[page + 4]);
			NewWindowTX6->setConstString("%s", g_pClientInfo->DropList.MobName[page + 5]);
			NewWindowTX7->setConstString("%s", g_pClientInfo->DropList.MobName[page + 6]);
			NewWindowTX8->setConstString("%s", g_pClientInfo->DropList.MobName[page + 7]);
			NewWindowTX9->setConstString("%s", g_pClientInfo->DropList.MobName[page + 8]);
			NewWindowTX10->setConstString("%s", g_pClientInfo->DropList.MobName[page + 9]);

			auto PageTx = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(179521);
			PageTx->setConstString("%d/%d", (ConfigR::DropListPage + 1), ConfigR::DropListTpages);
		}		
	}break;
	case 179530:
	{
		ConfigR::DropListPage--;

		if (ConfigR::DropListRegion == 0) {

			if (ConfigR::DropListPage < 0)
				ConfigR::DropListPage = 0;

			auto NewWindowTX1 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(179511);
			auto NewWindowTX2 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(179512);
			auto NewWindowTX3 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(179513);
			auto NewWindowTX4 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(179514);
			auto NewWindowTX5 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(179515);
			auto NewWindowTX6 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(179516);
			auto NewWindowTX7 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(179517);
			auto NewWindowTX8 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(179518);
			auto NewWindowTX9 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(179519);
			auto NewWindowTX10 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(179520);

			NewWindowTX1->setConstString("Armia");
			NewWindowTX2->setConstString("Erion");
			NewWindowTX3->setConstString("Arzan");
			NewWindowTX4->setConstString("Deserto");
			NewWindowTX5->setConstString("Gelo");
			NewWindowTX6->setConstString("Dungeon");
			NewWindowTX7->setConstString("Submundo");
			NewWindowTX8->setConstString("Kefra");
			NewWindowTX9->setConstString("Lan N");
			NewWindowTX10->setConstString("Lan M");

			auto PageTx = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(179521);
			PageTx->setConstString("%d/2", (ConfigR::DropListPage + 1));
		}

		if (ConfigR::DropListRegion != 0) {
			if (ConfigR::DropListPage <= 0)
				ConfigR::DropListPage = 0;

			auto NewWindowTX1 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(179511);
			auto NewWindowTX2 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(179512);
			auto NewWindowTX3 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(179513);
			auto NewWindowTX4 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(179514);
			auto NewWindowTX5 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(179515);
			auto NewWindowTX6 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(179516);
			auto NewWindowTX7 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(179517);
			auto NewWindowTX8 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(179518);
			auto NewWindowTX9 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(179519);
			auto NewWindowTX10 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(179520);

			int page = (ConfigR::DropListPage * 10);

			NewWindowTX1->setConstString("%s", g_pClientInfo->DropList.MobName[page + 0]);
			NewWindowTX2->setConstString("%s", g_pClientInfo->DropList.MobName[page + 1]);
			NewWindowTX3->setConstString("%s", g_pClientInfo->DropList.MobName[page + 2]);
			NewWindowTX4->setConstString("%s", g_pClientInfo->DropList.MobName[page + 3]);
			NewWindowTX5->setConstString("%s", g_pClientInfo->DropList.MobName[page + 4]);
			NewWindowTX6->setConstString("%s", g_pClientInfo->DropList.MobName[page + 5]);
			NewWindowTX7->setConstString("%s", g_pClientInfo->DropList.MobName[page + 6]);
			NewWindowTX8->setConstString("%s", g_pClientInfo->DropList.MobName[page + 7]);
			NewWindowTX9->setConstString("%s", g_pClientInfo->DropList.MobName[page + 8]);
			NewWindowTX10->setConstString("%s", g_pClientInfo->DropList.MobName[page + 9]);

			auto PageTx = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(179521);
			PageTx->setConstString("%d/%d", (ConfigR::DropListPage + 1), ConfigR::DropListTpages);
		}
	}break;
	case DROPLISTBUTTON:
	{
		if (ConfigR::DropListRegion != 0) {
			int Page = ConfigR::DropListPage * 10;
			int State = DropListButton + Page;
			OpenDroplist(g_pClientInfo->DropList.MobName[State], ConfigR::DropListRegion);
		}
		if (ConfigR::DropListRegion == 0) {
			int Page = ConfigR::DropListPage * 10;
			ConfigR::DropListRegion = DropListButton + 1 + Page;

			ConfigR::DropListPage = 0;
			RequestDropList(ConfigR::DropListRegion);
		}			
	}break;
	case CLOSECHAT:
	{
		auto CHATBTS = g_pInterface->Instance()->getGuiFromHandle<UIControl>(65672);
		auto CHATOPCOES = g_pInterface->Instance()->getGuiFromHandle<UIControl>(90128);
		auto CHATBTCOMUM = g_pInterface->Instance()->getGuiFromHandle<UIControl>(90113);
		auto CHATGUIA = g_pInterface->Instance()->getGuiFromHandle<UIControl>(65667);
		auto CHATFUNDO = g_pInterface->Instance()->getGuiFromHandle<UIControl>(65943);
		auto CHATDIGITAR = g_pInterface->Instance()->getGuiFromHandle<UIControl>(65670);

		ConfigR::gModoChat = !ConfigR::gModoChat;

		if (ConfigR::gModoChat == TRUE)
		{
			CHATBTS->IsVisible = false;
			CHATGUIA->IsVisible = false;
			CHATFUNDO->IsVisible = false;
			CHATGUIA->IsVisible = false;
			CHATDIGITAR->IsVisible = false;
			CHATBTCOMUM->IsVisible = false;
		}
		if (ConfigR::gModoChat == FALSE)
		{
			CHATBTS->IsVisible = true;
			CHATGUIA->IsVisible = true;
			CHATFUNDO->IsVisible = true;
			CHATGUIA->IsVisible = true;
		}
	}break;
	case OPENPVPRANKING:
	{
		/*GamePainel->IsVisible = false;
		PainelRanking->IsVisible = true;
		ReqAlias(6);*/
	}break;
	case DONATEBUTTON:
	{	
		ConfigR::WindowControl = DONATESTORE;
		ConfigR::ShopItemPos = DonateButton;		

		ConfigR::ShopItemQnt = 1;

		int ItemIndex = g_pClientInfo->Info.cStoreItens[ConfigR::ShopStore][ConfigR::ShopPage][ConfigR::ShopItemPos][0] * ConfigR::ShopItemQnt;

		if (ItemIndex <= 0 || ItemIndex >= MAX_ITEMLIST)
			break;

		StorePainel->IsVisible = false;
		BuyConfirm->IsVisible = true;

		int Price = g_pClientInfo->Info.cStoreItens[ConfigR::ShopStore][ConfigR::ShopPage][ConfigR::ShopItemPos][1] * ConfigR::ShopItemQnt;

		STRUCT_ITEM item;
		memset(&item, 0, sizeof(STRUCT_ITEM));
		item.sIndex = g_pClientInfo->Info.cStoreItens[ConfigR::ShopStore][ConfigR::ShopPage][ConfigR::ShopItemPos][0];

		auto BuyConfirmGrid = g_pInterface->Instance()->getGuiFromHandle<UISlot>(192520);
		*(int*)((int)BuyConfirmGrid + 0x400) = 0x5;
		BuyConfirmGrid->deleteItemGui(0, 0);
		BuyConfirmGrid->setGui((int)BuyConfirmGrid->New(item, 0, 0), 0, 0);		

		auto ConfirmTx1 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(192530);
		ConfirmTx1->setConstString("%d", ConfigR::ShopItemQnt);
		ConfirmTx1->setTextColor(TNColor::CornBlue);

		auto ConfirmTx2 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(192531);
		ConfirmTx2->setConstString("Price: %d", Price);

		if (Price >= g_pClientInfo->Info.Cash)
			ConfirmTx2->setTextColor(TNColor::Red);
		else
			ConfirmTx2->setTextColor(TNColor::CornBlue);

		auto ConfirmTx3 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(192532);
		ConfirmTx3->setConstString("Saldo Atual: %d", g_pClientInfo->Info.Cash);
		ConfirmTx3->setTextColor(TNColor::CornBlue);

		auto ConfirmTx4 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(192533);
		ConfirmTx4->setConstString("Saldo Final: %d", (g_pClientInfo->Info.Cash - Price));
		ConfirmTx4->setTextColor(TNColor::CornBlue);

		if ((g_pClientInfo->Info.Cash - Price) < 0)
			ConfirmTx4->setTextColor(TNColor::Red);

	}break;
	case 192512:
	{
		if (ConfigR::WindowControl == DONATESTORE) {
			ConfigR::ShopItemQnt += 1;

			if (ConfigR::ShopItemQnt > 120)
				ConfigR::ShopItemQnt = 120;

			int Price = g_pClientInfo->Info.cStoreItens[ConfigR::ShopStore][ConfigR::ShopPage][ConfigR::ShopItemPos][1] * ConfigR::ShopItemQnt;

			if (Price > g_pClientInfo->Info.Cash) {
				ConfigR::ShopItemQnt -= 1;
				Price -= g_pClientInfo->Info.cStoreItens[ConfigR::ShopStore][ConfigR::ShopPage][ConfigR::ShopItemPos][1];
			}

			STRUCT_ITEM item;
			memset(&item, 0, sizeof(STRUCT_ITEM));
			item.sIndex = g_pClientInfo->Info.cStoreItens[ConfigR::ShopStore][ConfigR::ShopPage][ConfigR::ShopItemPos][0];

			auto BuyConfirmGrid = g_pInterface->Instance()->getGuiFromHandle<UISlot>(192520);
			*(int*)((int)BuyConfirmGrid + 0x400) = 0x5;
			BuyConfirmGrid->deleteItemGui(0, 0);
			BuyConfirmGrid->setGui((int)BuyConfirmGrid->New(item, 0, 0), 0, 0);

			auto ConfirmTx1 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(192530);
			ConfirmTx1->setConstString("%d", ConfigR::ShopItemQnt);
			ConfirmTx1->setTextColor(TNColor::CornBlue);

			auto ConfirmTx2 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(192531);
			ConfirmTx2->setConstString("Price: %d", Price);

			if (Price >= g_pClientInfo->Info.Cash)
				ConfirmTx2->setTextColor(TNColor::Red);
			else
				ConfirmTx2->setTextColor(TNColor::CornBlue);

			auto ConfirmTx3 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(192532);
			ConfirmTx3->setConstString("Saldo Atual: %d", g_pClientInfo->Info.Cash);
			ConfirmTx3->setTextColor(TNColor::CornBlue);

			auto ConfirmTx4 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(192533);
			ConfirmTx4->setConstString("Saldo Final: %d", (g_pClientInfo->Info.Cash - Price));
			ConfirmTx4->setTextColor(TNColor::CornBlue);

			if ((g_pClientInfo->Info.Cash - Price) < 0)
				ConfirmTx4->setTextColor(TNColor::Red);
		}
		if (ConfigR::WindowControl == JEPHI) {
			ConfigR::ShopItemQnt += 1;

			int Gold[2] = { 1000000, 500000 };
			int Index[2] = { 413, 412 };
			int sIndex[2] = { 420, 419 };

			if (ConfigR::ShopItemQnt > 120)
				ConfigR::ShopItemQnt = 120;

			int Price = 10 * ConfigR::ShopItemQnt;

			int Qnt = 0;

			for (int i = 0; i < MAX_CARRY; i++) {
				if (player.Carry[i].sIndex == sIndex[ConfigR::Jephi])
					Qnt += player.Carry[i].stEffect[0].cValue;
			}

			if (Price > Qnt) {
				ConfigR::ShopItemQnt -= 1;
				Price -= 10;
			}

			STRUCT_ITEM item;
			memset(&item, 0, sizeof(STRUCT_ITEM));
			item.sIndex = Index[ConfigR::Jephi];

			auto BuyConfirmGrid = g_pInterface->Instance()->getGuiFromHandle<UISlot>(192520);
			*(int*)((int)BuyConfirmGrid + 0x400) = 0x5;
			BuyConfirmGrid->deleteItemGui(0, 0);
			BuyConfirmGrid->setGui((int)BuyConfirmGrid->New(item, 0, 0), 0, 0);

			auto ConfirmTx1 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(192530);
			ConfirmTx1->setConstString("%d", ConfigR::ShopItemQnt);
			ConfirmTx1->setTextColor(TNColor::CornBlue);

			auto ConfirmTx2 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(192531);
			ConfirmTx2->setConstString("Restos: %d", Price);
			ConfirmTx2->setTextColor(TNColor::CornBlue);

			auto ConfirmTx3 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(192532);
			ConfirmTx3->setConstString("Gold: %d", (ConfigR::ShopItemQnt* Gold[ConfigR::Jephi]));
			ConfirmTx3->setTextColor(TNColor::CornBlue);

			auto ConfirmTx4 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(192533);
			ConfirmTx4->setConstString("Restos Atual: %d", Qnt);
			ConfirmTx4->setTextColor(TNColor::CornBlue);

			if ((Qnt - Price) < 0)
				ConfirmTx4->setTextColor(TNColor::Red);
		}
	}break;
	case 192514:
	{
		if (ConfigR::WindowControl == DONATESTORE) {
			ConfigR::ShopItemQnt += 10;

			if (ConfigR::ShopItemQnt > 120)
				ConfigR::ShopItemQnt = 120;

			int Price = g_pClientInfo->Info.cStoreItens[ConfigR::ShopStore][ConfigR::ShopPage][ConfigR::ShopItemPos][1] * ConfigR::ShopItemQnt;

			if (Price > g_pClientInfo->Info.Cash) {
				ConfigR::ShopItemQnt -= 10;
				Price -= g_pClientInfo->Info.cStoreItens[ConfigR::ShopStore][ConfigR::ShopPage][ConfigR::ShopItemPos][1] * 10;
			}

			STRUCT_ITEM item;
			memset(&item, 0, sizeof(STRUCT_ITEM));
			item.sIndex = g_pClientInfo->Info.cStoreItens[ConfigR::ShopStore][ConfigR::ShopPage][ConfigR::ShopItemPos][0];

			auto BuyConfirmGrid = g_pInterface->Instance()->getGuiFromHandle<UISlot>(192520);
			*(int*)((int)BuyConfirmGrid + 0x400) = 0x5;
			BuyConfirmGrid->deleteItemGui(0, 0);
			BuyConfirmGrid->setGui((int)BuyConfirmGrid->New(item, 0, 0), 0, 0);

			auto ConfirmTx1 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(192530);
			ConfirmTx1->setConstString("%d", ConfigR::ShopItemQnt);
			ConfirmTx1->setTextColor(TNColor::CornBlue);

			auto ConfirmTx2 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(192531);
			ConfirmTx2->setConstString("Price: %d", Price);

			if (Price >= g_pClientInfo->Info.Cash)
				ConfirmTx2->setTextColor(TNColor::Red);
			else
				ConfirmTx2->setTextColor(TNColor::CornBlue);

			auto ConfirmTx3 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(192532);
			ConfirmTx3->setConstString("Saldo Atual: %d", g_pClientInfo->Info.Cash);
			ConfirmTx3->setTextColor(TNColor::CornBlue);

			auto ConfirmTx4 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(192533);
			ConfirmTx4->setConstString("Saldo Final: %d", (g_pClientInfo->Info.Cash - Price));
			ConfirmTx4->setTextColor(TNColor::CornBlue);

			if ((g_pClientInfo->Info.Cash - Price) < 0)
				ConfirmTx4->setTextColor(TNColor::Red);
		}
		if (ConfigR::WindowControl == JEPHI) {

			int Gold[2] = { 1000000, 500000 };
			int Index[2] = { 413, 412 };
			int sIndex[2] = { 420, 419 };

			ConfigR::ShopItemQnt += 10;

			if (ConfigR::ShopItemQnt > 120)
				ConfigR::ShopItemQnt = 120;

			int Price = 10 * ConfigR::ShopItemQnt;

			int Qnt = 0;

			for (int i = 0; i < MAX_CARRY; i++) {
				if (player.Carry[i].sIndex == sIndex[ConfigR::Jephi])
					Qnt += player.Carry[i].stEffect[0].cValue;
			}

			if (Price > Qnt) {
				ConfigR::ShopItemQnt -= 10;
				Price -= 100;
			}

			STRUCT_ITEM item;
			memset(&item, 0, sizeof(STRUCT_ITEM));
			item.sIndex = Index[ConfigR::Jephi];

			auto BuyConfirmGrid = g_pInterface->Instance()->getGuiFromHandle<UISlot>(192520);
			*(int*)((int)BuyConfirmGrid + 0x400) = 0x5;
			BuyConfirmGrid->deleteItemGui(0, 0);
			BuyConfirmGrid->setGui((int)BuyConfirmGrid->New(item, 0, 0), 0, 0);

			auto ConfirmTx1 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(192530);
			ConfirmTx1->setConstString("%d", ConfigR::ShopItemQnt);
			ConfirmTx1->setTextColor(TNColor::CornBlue);

			auto ConfirmTx2 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(192531);
			ConfirmTx2->setConstString("Restos: %d", Price);
			ConfirmTx2->setTextColor(TNColor::CornBlue);

			auto ConfirmTx3 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(192532);
			ConfirmTx3->setConstString("Gold: %d", (ConfigR::ShopItemQnt* Gold[ConfigR::Jephi]));
			ConfirmTx3->setTextColor(TNColor::CornBlue);

			auto ConfirmTx4 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(192533);
			ConfirmTx4->setConstString("Restos Atual: %d", Qnt);
			ConfirmTx4->setTextColor(TNColor::CornBlue);

			if ((Qnt - Price) < 0)
				ConfirmTx4->setTextColor(TNColor::Red);

		}

	}break;
	case 192515:
	{
		if (ConfigR::WindowControl == DONATESTORE) {
			ConfigR::ShopItemQnt += 120;

			if (ConfigR::ShopItemQnt > 120)
				ConfigR::ShopItemQnt = 120;

			int Price = g_pClientInfo->Info.cStoreItens[ConfigR::ShopStore][ConfigR::ShopPage][ConfigR::ShopItemPos][1] * ConfigR::ShopItemQnt;

			if (Price > g_pClientInfo->Info.Cash) {
				ConfigR::ShopItemQnt -= 120;
				Price -= g_pClientInfo->Info.cStoreItens[ConfigR::ShopStore][ConfigR::ShopPage][ConfigR::ShopItemPos][1] * 120;
			}

			STRUCT_ITEM item;
			memset(&item, 0, sizeof(STRUCT_ITEM));
			item.sIndex = g_pClientInfo->Info.cStoreItens[ConfigR::ShopStore][ConfigR::ShopPage][ConfigR::ShopItemPos][0];

			auto BuyConfirmGrid = g_pInterface->Instance()->getGuiFromHandle<UISlot>(192520);
			*(int*)((int)BuyConfirmGrid + 0x400) = 0x5;
			BuyConfirmGrid->deleteItemGui(0, 0);
			BuyConfirmGrid->setGui((int)BuyConfirmGrid->New(item, 0, 0), 0, 0);

			auto ConfirmTx1 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(192530);
			ConfirmTx1->setConstString("%d", ConfigR::ShopItemQnt);
			ConfirmTx1->setTextColor(TNColor::CornBlue);

			auto ConfirmTx2 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(192531);
			ConfirmTx2->setConstString("Price: %d", Price);

			if (Price >= g_pClientInfo->Info.Cash)
				ConfirmTx2->setTextColor(TNColor::Red);
			else
				ConfirmTx2->setTextColor(TNColor::CornBlue);

			auto ConfirmTx3 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(192532);
			ConfirmTx3->setConstString("Saldo Atual: %d", g_pClientInfo->Info.Cash);
			ConfirmTx3->setTextColor(TNColor::CornBlue);

			auto ConfirmTx4 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(192533);
			ConfirmTx4->setConstString("Saldo Final: %d", (g_pClientInfo->Info.Cash - Price));
			ConfirmTx4->setTextColor(TNColor::CornBlue);

			if ((g_pClientInfo->Info.Cash - Price) < 0)
				ConfirmTx4->setTextColor(TNColor::Red);
		}
		if (ConfigR::WindowControl == JEPHI) {
			ConfigR::ShopItemQnt += 120;

			int Gold[2] = { 1000000, 500000 };
			int Index[2] = { 413, 412 };
			int sIndex[2] = { 420, 419 };

			if (ConfigR::ShopItemQnt > 120)
				ConfigR::ShopItemQnt = 120;

			int Price = 10 * ConfigR::ShopItemQnt;

			int Qnt = 0;

			for (int i = 0; i < MAX_CARRY; i++) {
				if (player.Carry[i].sIndex == sIndex[ConfigR::Jephi])
					Qnt += player.Carry[i].stEffect[0].cValue;
			}

			if (Price > Qnt) {
				ConfigR::ShopItemQnt = 1;
				Price = 10;
			}

			STRUCT_ITEM item;
			memset(&item, 0, sizeof(STRUCT_ITEM));
			item.sIndex = Index[ConfigR::Jephi];

			auto BuyConfirmGrid = g_pInterface->Instance()->getGuiFromHandle<UISlot>(192520);
			*(int*)((int)BuyConfirmGrid + 0x400) = 0x5;
			BuyConfirmGrid->deleteItemGui(0, 0);
			BuyConfirmGrid->setGui((int)BuyConfirmGrid->New(item, 0, 0), 0, 0);

			auto ConfirmTx1 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(192530);
			ConfirmTx1->setConstString("%d", ConfigR::ShopItemQnt);
			ConfirmTx1->setTextColor(TNColor::CornBlue);

			auto ConfirmTx2 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(192531);
			ConfirmTx2->setConstString("Restos: %d", Price);
			ConfirmTx2->setTextColor(TNColor::CornBlue);

			auto ConfirmTx3 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(192532);
			ConfirmTx3->setConstString("Gold: %d", (ConfigR::ShopItemQnt* Gold[ConfigR::Jephi]));
			ConfirmTx3->setTextColor(TNColor::CornBlue);

			auto ConfirmTx4 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(192533);
			ConfirmTx4->setConstString("Restos Atual: %d", Qnt);
			ConfirmTx4->setTextColor(TNColor::CornBlue);

			if ((Qnt - Price) < 0)
				ConfirmTx4->setTextColor(TNColor::Red);
		}
	}break;
	case 192513:
	{
		if (ConfigR::WindowControl == DONATESTORE) {
			if (ConfigR::ShopItemQnt > 1)
				ConfigR::ShopItemQnt -= 1;

			int Price = g_pClientInfo->Info.cStoreItens[ConfigR::ShopStore][ConfigR::ShopPage][ConfigR::ShopItemPos][1] * ConfigR::ShopItemQnt;

			STRUCT_ITEM item;
			memset(&item, 0, sizeof(STRUCT_ITEM));
			item.sIndex = g_pClientInfo->Info.cStoreItens[ConfigR::ShopStore][ConfigR::ShopPage][ConfigR::ShopItemPos][0];

			auto BuyConfirmGrid = g_pInterface->Instance()->getGuiFromHandle<UISlot>(192520);
			*(int*)((int)BuyConfirmGrid + 0x400) = 0x5;
			BuyConfirmGrid->deleteItemGui(0, 0);
			BuyConfirmGrid->setGui((int)BuyConfirmGrid->New(item, 0, 0), 0, 0);

			auto ConfirmTx1 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(192530);
			ConfirmTx1->setConstString("%d", ConfigR::ShopItemQnt);
			ConfirmTx1->setTextColor(TNColor::CornBlue);

			auto ConfirmTx2 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(192531);
			ConfirmTx2->setConstString("Price: %d", Price);

			if (Price >= g_pClientInfo->Info.Cash)
				ConfirmTx2->setTextColor(TNColor::Red);
			else
				ConfirmTx2->setTextColor(TNColor::CornBlue);

			auto ConfirmTx3 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(192532);
			ConfirmTx3->setConstString("Saldo Atual: %d", g_pClientInfo->Info.Cash);
			ConfirmTx3->setTextColor(TNColor::CornBlue);

			auto ConfirmTx4 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(192533);
			ConfirmTx4->setConstString("Saldo Final: %d", (g_pClientInfo->Info.Cash - Price));
			ConfirmTx4->setTextColor(TNColor::CornBlue);

			if ((g_pClientInfo->Info.Cash - Price) < 0)
				ConfirmTx4->setTextColor(TNColor::Red);
		}
		if (ConfigR::WindowControl == JEPHI) {
			
			int Gold[2] = { 1000000, 500000 };
			int Index[2] = { 413, 412 };
			int sIndex[2] = { 420, 419 };

			if (ConfigR::ShopItemQnt > 1)
				ConfigR::ShopItemQnt -= 1;

			int Price = 10 * ConfigR::ShopItemQnt;

			int Qnt = 0;

			for (int i = 0; i < MAX_CARRY; i++) {
				if (player.Carry[i].sIndex == sIndex[ConfigR::Jephi])
					Qnt += player.Carry[i].stEffect[0].cValue;
			}

			STRUCT_ITEM item;
			memset(&item, 0, sizeof(STRUCT_ITEM));
			item.sIndex = Index[ConfigR::Jephi];

			auto BuyConfirmGrid = g_pInterface->Instance()->getGuiFromHandle<UISlot>(192520);
			*(int*)((int)BuyConfirmGrid + 0x400) = 0x5;
			BuyConfirmGrid->deleteItemGui(0, 0);
			BuyConfirmGrid->setGui((int)BuyConfirmGrid->New(item, 0, 0), 0, 0);

			auto ConfirmTx1 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(192530);
			ConfirmTx1->setConstString("%d", ConfigR::ShopItemQnt);
			ConfirmTx1->setTextColor(TNColor::CornBlue);

			auto ConfirmTx2 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(192531);
			ConfirmTx2->setConstString("Restos: %d", Price);
			ConfirmTx2->setTextColor(TNColor::CornBlue);

			auto ConfirmTx3 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(192532);
			ConfirmTx3->setConstString("Gold: %d", (ConfigR::ShopItemQnt* Gold[ConfigR::Jephi]));
			ConfirmTx3->setTextColor(TNColor::CornBlue);

			auto ConfirmTx4 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(192533);
			ConfirmTx4->setConstString("Restos Atual: %d", Qnt);
			ConfirmTx4->setTextColor(TNColor::CornBlue);

			if ((Qnt - Price) < 0)
				ConfirmTx4->setTextColor(TNColor::Red);
		}
			
	}break;
	case 192511:
	{
		if (ConfigR::WindowControl == DONATESTORE) {
			SendReqDonateShop(ConfigR::ShopStore, ConfigR::ShopPage, ConfigR::ShopItemPos, ConfigR::ShopItemQnt);

			auto BuyConfirmGrid = g_pInterface->Instance()->getGuiFromHandle<UISlot>(192520);
			*(int*)((int)BuyConfirmGrid + 0x400) = 0x5;
			BuyConfirmGrid->deleteItemGui(0, 0);

			BuyConfirm->IsVisible = false;
			StorePainel->IsVisible = true;
		}
		if (ConfigR::WindowControl == JEPHI) {
			int Index[2] = { 413, 412 };
			SendJephi(ConfigR::Jephi, ConfigR::ShopItemQnt);

			auto BuyConfirmGrid = g_pInterface->Instance()->getGuiFromHandle<UISlot>(192520);
			*(int*)((int)BuyConfirmGrid + 0x400) = 0x5;
			BuyConfirmGrid->deleteItemGui(0, 0);
			BuyConfirm->IsVisible = false;
			PainelJephi->IsVisible = true;
		}

	}break;
	case OPENSTORE:
	{
		ConfigR::ShopStore = 0;
		ConfigR::ShopPage = 0;

		auto Grupo = g_pInterface->Instance()->getGuiFromHandle<UIControl>(475136);
		auto Compositor = g_pInterface->Instance()->getGuiFromHandle<UIControl>(81921);
		auto Compositor2 = g_pInterface->Instance()->getGuiFromHandle<UIControl>(6432);
		auto Compositor3 = g_pInterface->Instance()->getGuiFromHandle<UIControl>(86017);
		auto xPainel = g_pInterface->Instance()->getGuiFromHandle<UIControl>(864);
		auto xPainel2 = g_pInterface->Instance()->getGuiFromHandle<UIControl>(1054256);
		auto Loja = g_pInterface->Instance()->getGuiFromHandle<UIControl>(65692);
		auto SkillLoja = g_pInterface->Instance()->getGuiFromHandle<UIControl>(65602);
		auto SkillInv = g_pInterface->Instance()->getGuiFromHandle<UIControl>(65567);
		auto cPainel = g_pInterface->Instance()->getGuiFromHandle<UIControl>(65696);
		auto Bau = g_pInterface->Instance()->getGuiFromHandle<UIControl>(65686);

		auto bufftempo = g_pInterface->getGuiFromHandle<UIControl>(5749);
		auto ElementoModoFoto3 = g_pInterface->Instance()->getGuiFromHandle<UIControl>(69633);
		bufftempo->IsVisible = false;
		ElementoModoFoto3->IsVisible = false;

		auto CHATBTS = g_pInterface->Instance()->getGuiFromHandle<UIControl>(65672);
		auto CHATOPCOES = g_pInterface->Instance()->getGuiFromHandle<UIControl>(90128);
		auto CHATBTCOMUM = g_pInterface->Instance()->getGuiFromHandle<UIControl>(90113);
		auto CHATGUIA = g_pInterface->Instance()->getGuiFromHandle<UIControl>(65667);
		auto CHATFUNDO = g_pInterface->Instance()->getGuiFromHandle<UIControl>(65943);
		auto CHATDIGITAR = g_pInterface->Instance()->getGuiFromHandle<UIControl>(65670);

		
		CHATBTS->IsVisible = false;
		CHATGUIA->IsVisible = false;
		CHATFUNDO->IsVisible = false;
		CHATGUIA->IsVisible = false;
		CHATDIGITAR->IsVisible = false;
		CHATBTCOMUM->IsVisible = false;
		ConfigR::gModoChat = TRUE;
		
		PainelInv->IsVisible = false;
		Grupo->IsVisible = false;
		Compositor->IsVisible = false;
		Compositor2->IsVisible = false;
		Compositor3->IsVisible = false;
		xPainel->IsVisible = false;
		xPainel2->IsVisible = false;
		Loja->IsVisible = false;
		SkillLoja->IsVisible = false;
		SkillInv->IsVisible = false;
		cPainel->IsVisible = false;
		Bau->IsVisible = false;

		
		ReqAlias(1);

		GamePainel->IsVisible = false;
		StorePainel->IsVisible = true;

		SendMsgExp(TNColor::Default, "");
		SendMsgExp(TNColor::Default, "");
		SendMsgExp(TNColor::Default, "");
		SendMsgExp(TNColor::Default, "");
		SendMsgExp(TNColor::Default, "");

		int tPages = 3;

		if (ConfigR::ShopStore == 2)
			tPages = 3;

		auto TxShopPage = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(199516);
		TxShopPage->setConstString("%d/%d", (ConfigR::ShopPage + 1), tPages);

		STRUCT_ITEM item[15];

		for (int i = 0; i < 15; i++){
			auto ShopGrid = g_pInterface->Instance()->getGuiFromHandle<UISlot>(199401 + i);
			*(int*)((int)ShopGrid + 0x400) = 0x5;
			ShopGrid->deleteItemGui(0, 0);

			memset(&item[i], 0, sizeof(STRUCT_ITEM));
			item[i].sIndex = g_pClientInfo->Info.cStoreItens[ConfigR::ShopStore][ConfigR::ShopPage][i][0];

			if (item[i].sIndex != 0)
				ShopGrid->setGui((int)ShopGrid->New(item[i], 0, 0), 0, 0);

			auto TxShopGrid = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(199501 + i);
			TxShopGrid->setConstString("Price: %d", g_pClientInfo->Info.cStoreItens[ConfigR::ShopStore][ConfigR::ShopPage][i][1]);
			TxShopGrid->setTextColor(TNColor::CornBlue);

			if (g_pClientInfo->Info.cStoreItens[ConfigR::ShopStore][ConfigR::ShopPage][i][0] == 0)
				TxShopGrid->setConstString("");
		}
	}break;
	case 199322:
	{
		ConfigR::ShopStore = 0;
		ConfigR::ShopPage = 0;
		GamePainel->IsVisible = false;
		StorePainel->IsVisible = true;

		int tPages = 3;

		if (ConfigR::ShopStore == 2)
			tPages = 3;

		auto TxShopPage = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(199516);
		TxShopPage->setConstString("%d/%d", (ConfigR::ShopPage + 1), tPages);

		STRUCT_ITEM item[15];

		for (int i = 0; i < 15; i++) {
			auto ShopGrid = g_pInterface->Instance()->getGuiFromHandle<UISlot>(199401 + i);
			*(int*)((int)ShopGrid + 0x400) = 0x5;
			ShopGrid->deleteItemGui(0, 0);

			memset(&item[i], 0, sizeof(STRUCT_ITEM));
			item[i].sIndex = g_pClientInfo->Info.cStoreItens[ConfigR::ShopStore][ConfigR::ShopPage][i][0];
			
			if (item[i].sIndex != 0)
				ShopGrid->setGui((int)ShopGrid->New(item[i], 0, 0), 0, 0);

			auto TxShopGrid = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(199501 + i);			
			TxShopGrid->setConstString("Price: %d", g_pClientInfo->Info.cStoreItens[ConfigR::ShopStore][ConfigR::ShopPage][i][1]);
			TxShopGrid->setTextColor(TNColor::CornBlue);

			if (g_pClientInfo->Info.cStoreItens[ConfigR::ShopStore][ConfigR::ShopPage][i][0] == 0)
				TxShopGrid->setConstString("");
		}
	}break;
	case 199323:
	{
		ConfigR::ShopStore = 1;
		ConfigR::ShopPage = 0;
		GamePainel->IsVisible = false;
		StorePainel->IsVisible = true;

		int tPages = 3;

		if (ConfigR::ShopStore == 2)
			tPages = 3;

		auto TxShopPage = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(199516);
		TxShopPage->setConstString("%d/%d", (ConfigR::ShopPage + 1), tPages);

		STRUCT_ITEM item[15];

		for (int i = 0; i < 15; i++) {
			auto ShopGrid = g_pInterface->Instance()->getGuiFromHandle<UISlot>(199401 + i);
			*(int*)((int)ShopGrid + 0x400) = 0x5;
			ShopGrid->deleteItemGui(0, 0);

			memset(&item[i], 0, sizeof(STRUCT_ITEM));
			item[i].sIndex = g_pClientInfo->Info.cStoreItens[ConfigR::ShopStore][ConfigR::ShopPage][i][0];

			if (item[i].sIndex != 0)
				ShopGrid->setGui((int)ShopGrid->New(item[i], 0, 0), 0, 0);

			auto TxShopGrid = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(199501 + i);
			TxShopGrid->setConstString("Price: %d", g_pClientInfo->Info.cStoreItens[ConfigR::ShopStore][ConfigR::ShopPage][i][1]);
			TxShopGrid->setTextColor(TNColor::CornBlue);

			if (g_pClientInfo->Info.cStoreItens[ConfigR::ShopStore][ConfigR::ShopPage][i][0] == 0)
				TxShopGrid->setConstString("");
		}
	}break;
	case 199324:
	{
		ConfigR::ShopStore = 2;
		ConfigR::ShopPage = 0;
		GamePainel->IsVisible = false;
		StorePainel->IsVisible = true;

		int tPages = 3;

		if (ConfigR::ShopStore == 2)
			tPages = 3;

		auto TxShopPage = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(199516);
		TxShopPage->setConstString("%d/%d", (ConfigR::ShopPage + 1), tPages);

		STRUCT_ITEM item[15];

		for (int i = 0; i < 15; i++) {
			auto ShopGrid = g_pInterface->Instance()->getGuiFromHandle<UISlot>(199401 + i);
			*(int*)((int)ShopGrid + 0x400) = 0x5;
			ShopGrid->deleteItemGui(0, 0);

			memset(&item[i], 0, sizeof(STRUCT_ITEM));
			item[i].sIndex = g_pClientInfo->Info.cStoreItens[ConfigR::ShopStore][ConfigR::ShopPage][i][0];

			if (item[i].sIndex != 0)
				ShopGrid->setGui((int)ShopGrid->New(item[i], 0, 0), 0, 0);

			auto TxShopGrid = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(199501 + i);
			TxShopGrid->setConstString("Price: %d", g_pClientInfo->Info.cStoreItens[ConfigR::ShopStore][ConfigR::ShopPage][i][1]);
			TxShopGrid->setTextColor(TNColor::CornBlue);

			if (g_pClientInfo->Info.cStoreItens[ConfigR::ShopStore][ConfigR::ShopPage][i][0] == 0)
				TxShopGrid->setConstString("");
		}
	}break;
	case 199320:
	{
		if (ConfigR::ShopPage == 0)
			break;

		ConfigR::ShopPage -= 1;

		GamePainel->IsVisible = false;
		StorePainel->IsVisible = true;

		STRUCT_ITEM item[15];

		int tPages = 3;

		if (ConfigR::ShopStore == 2)
			tPages = 3;

		auto TxShopPage = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(199516);
		TxShopPage->setConstString("%d/%d", (ConfigR::ShopPage + 1), tPages);

		for (int i = 0; i < 15; i++) {
			auto ShopGrid = g_pInterface->Instance()->getGuiFromHandle<UISlot>(199401 + i);
			*(int*)((int)ShopGrid + 0x400) = 0x5;
			ShopGrid->deleteItemGui(0, 0);

			memset(&item[i], 0, sizeof(STRUCT_ITEM));
			item[i].sIndex = g_pClientInfo->Info.cStoreItens[ConfigR::ShopStore][ConfigR::ShopPage][i][0];

			if (item[i].sIndex != 0)
				ShopGrid->setGui((int)ShopGrid->New(item[i], 0, 0), 0, 0);

			auto TxShopGrid = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(199501 + i);
			TxShopGrid->setConstString("Price: %d", g_pClientInfo->Info.cStoreItens[ConfigR::ShopStore][ConfigR::ShopPage][i][1]);
			TxShopGrid->setTextColor(TNColor::CornBlue);

			if (g_pClientInfo->Info.cStoreItens[ConfigR::ShopStore][ConfigR::ShopPage][i][0] == 0)
				TxShopGrid->setConstString("");
		}
	}break;
	case 199321:
	{
		if (ConfigR::ShopPage == 2)
			break;

		if ((ConfigR::ShopStore == 0 || ConfigR::ShopStore == 1) && ConfigR::ShopPage == 2)
			break;

		ConfigR::ShopPage += 1;

		GamePainel->IsVisible = false;
		StorePainel->IsVisible = true;

		int tPages = 3;

		if (ConfigR::ShopStore == 2)
			tPages = 3;

		auto TxShopPage = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(199516);
		TxShopPage->setConstString("%d/%d", (ConfigR::ShopPage + 1), tPages);

		STRUCT_ITEM item[15];

		for (int i = 0; i < 15; i++) {
			auto ShopGrid = g_pInterface->Instance()->getGuiFromHandle<UISlot>(199401 + i);
			*(int*)((int)ShopGrid + 0x400) = 0x5;
			ShopGrid->deleteItemGui(0, 0);

			memset(&item[i], 0, sizeof(STRUCT_ITEM));
			item[i].sIndex = g_pClientInfo->Info.cStoreItens[ConfigR::ShopStore][ConfigR::ShopPage][i][0];

			if (item[i].sIndex != 0)
				ShopGrid->setGui((int)ShopGrid->New(item[i], 0, 0), 0, 0);

			auto TxShopGrid = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(199501 + i);
			TxShopGrid->setConstString("Price: %d", g_pClientInfo->Info.cStoreItens[ConfigR::ShopStore][ConfigR::ShopPage][i][1]);
			TxShopGrid->setTextColor(TNColor::CornBlue);

			if (g_pClientInfo->Info.cStoreItens[ConfigR::ShopStore][ConfigR::ShopPage][i][0] == 0)
				TxShopGrid->setConstString("");
		}
	}break;
	case ARMIA:
	{
		Sendteleport(2100,2100);
		GamePainel->IsVisible = false;
	}break;
	case ARZAN:
	{
		Sendteleport(2480, 1695);
		GamePainel->IsVisible = false;
	}break;
	case ERION:
	{
		Sendteleport(2461, 2006);
		GamePainel->IsVisible = false;
	}break;
	case NOATUM:
	{
		Sendteleport(1067, 1718);
		GamePainel->IsVisible = false;
	}break;
	case NIPPLE:
	{
		Sendteleport(3643, 3122);
		GamePainel->IsVisible = false;
	}break;
	case FILTROBTN:
	{
		auto NewWindowTX1 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(98401);
		auto NewWindowTX2 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(98402);
		auto NewWindowTX3 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(98403);
		auto NewWindowTX4 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(98404);
		auto NewWindowTX5 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(98405);
		auto NewWindowTX6 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(98406);
		auto NewWindowTX7 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(98407);
		auto NewWindowTX8 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(98408);
		auto NewWindowTX9 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(98409);
		auto NewWindowTX10 = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(98410);

		NewWindowTX1->setConstString("Armas");
		NewWindowTX2->setConstString("Sets");
		NewWindowTX3->setConstString("Refináveis");
		NewWindowTX4->setConstString("Quests");
		NewWindowTX5->setConstString("");
		NewWindowTX6->setConstString("");
		NewWindowTX7->setConstString("");
		NewWindowTX8->setConstString("");
		NewWindowTX9->setConstString("Limpar");
		NewWindowTX10->setConstString("Ativar/Desativar");

		ConfigR::WindowControl = FILTRO;
		painelteleport->IsVisible = true;
		GamePainel->IsVisible = false;
	}break;
	
	case OPT1:
	{
		if (ConfigR::WindowControl == FILTRO) {
			OpenStore(100);
		}
	}break;
	case OPT2:
	{
		if (ConfigR::WindowControl == FILTRO) {
			OpenStore(101);
		}
	}break;
	case OPT3:
	{
		if (ConfigR::WindowControl == FILTRO) {
			OpenStore(102);
		}
	}break;
	case OPT4:
	{
		if (ConfigR::WindowControl == FILTRO) {
			OpenStore(103);
		}
	}break;
	case OPT5:
	{
		
	}break;
	case OPT6:
	{
		
	}break;
	case OPT7:
	{
		
	}break;
	case OPT8:
	{
		
	}break;
	case OPT9:
	{
		if (ConfigR::WindowControl == FILTRO) {
			SendTextServer("limpar");
		}
	}break;
	case OPT10:
	{
		if (ConfigR::WindowControl == FILTRO) {
			SendTextServer("filtro");
		}
	}break;


	return FALSE;
	}


#pragma endregion

	return TRUE;
}




bool HookNaked::HKD_CallBack_Event_Esc()
{
	
	auto PainelInv = g_pInterface->Instance()->getGuiFromHandle<UIControl>(589832);
	auto painelteleport = g_pInterface->Instance()->getGuiFromHandle<UIControl>(98300);
	auto StorePainel = g_pInterface->Instance()->getGuiFromHandle<UIControl>(199300);
	auto GamePainel = g_pInterface->Instance()->getGuiFromHandle<UIControl>(981300);
	auto BuyConfirm = g_pInterface->Instance()->getGuiFromHandle<UIControl>(192500);
	auto DropList = g_pInterface->Instance()->getGuiFromHandle<UIControl>(179500);
	auto PainelJephi = g_pInterface->Instance()->getGuiFromHandle<UIControl>(117900);
	auto PainelRanking = g_pInterface->Instance()->getGuiFromHandle<UIControl>(1919400);

	auto PainelPix = g_pInterface->Instance()->getGuiFromHandle<UIControl>(188500);
	auto MailPainel = g_pInterface->Instance()->getGuiFromHandle<UIControl>(121200);

	auto PainelTrajes = g_pInterface->Instance()->getGuiFromHandle<UIControl>(1882000);
	

	bool Return = false;
		
	if (PainelInv->IsVisible == true) {
		PainelInv->IsVisible = false;
		Return = true;
	}
	if (PainelTrajes->IsVisible == true) {
		PainelTrajes->IsVisible = false;
		Return = true;
	}
	/*if (PainelRanking->IsVisible == true) {
		PainelRanking->IsVisible = false;
		Return = true;
	}*/

	if (MailPainel->IsVisible == true) {
		MailPainel->IsVisible = false;

		auto MailItem = g_pInterface->Instance()->getGuiFromHandle<UISlot>(121202);
		*(int*)((int)MailItem + 0x400) = 0x5;
		MailItem->deleteItemGui(0, 0);
		Return = true;
	}

	if (PainelPix->IsVisible == true) {
		PainelPix->IsVisible = false;
		Return = true;
	}

	if (PainelJephi->IsVisible == true) {
		PainelJephi->IsVisible = false;

		for (int i = 0; i < 5; i++) {
			auto JephiGrid = g_pInterface->Instance()->getGuiFromHandle<UISlot>(117901 + i);
			*(int*)((int)JephiGrid + 0x400) = 0x5;
			JephiGrid->deleteItemGui(0, 0);
		}
		Return = true;
	}
	
	if (painelteleport->IsVisible == true) {
		painelteleport->IsVisible = false;
		Return = true;
	}

	if (GamePainel->IsVisible == true) {
		GamePainel->IsVisible = false;
		Return = true;
	}	

	if (DropList->IsVisible == true) {
		DropList->IsVisible = false;
		auto DropListGrid = g_pInterface->Instance()->getGuiFromHandle<UISlot>(179600);
		*(int*)((int)DropListGrid + 0x400) = 0x5;
		DropListGrid->deleteItems();
		GamePainel->IsVisible = true;
		Return = true;
	}

	if (StorePainel->IsVisible == true) {
		StorePainel->IsVisible = false;

		for (int i = 0; i < 15; i++) {
			auto ShopGrid = g_pInterface->Instance()->getGuiFromHandle<UISlot>(199401 + i);
			*(int*)((int)ShopGrid + 0x400) = 0x1;
			ShopGrid->deleteItemGui(0, 0);
		}
		Return = true;

		auto bufftempo = g_pInterface->getGuiFromHandle<UIControl>(5749);
		auto ElementoModoFoto3 = g_pInterface->Instance()->getGuiFromHandle<UIControl>(69633);
		bufftempo->IsVisible = true;
		ElementoModoFoto3->IsVisible = true;
	}

	if (BuyConfirm->IsVisible == true) {
		BuyConfirm->IsVisible = false;

		auto BuyConfirmGrid = g_pInterface->Instance()->getGuiFromHandle<UISlot>(192520);
		*(int*)((int)BuyConfirmGrid + 0x400) = 0x5;
		BuyConfirmGrid->deleteItemGui(0, 0);

		BuyConfirm->IsVisible = false;

		if (ConfigR::WindowControl == DONATESTORE)
			StorePainel->IsVisible = true;

		if (ConfigR::WindowControl == JEPHI)
			PainelJephi->IsVisible = true;

		Return = true;
	}

	if (Return == true)
		return true;

	return false;
}

__declspec(naked) void HookNaked::NKD_HandleScene()
{//by seitbnao
	__asm
	{
		MOV EAX, 0x6F0AB0
		MOV EDX, DWORD PTR DS : [EAX]
		MOV ECX, EDX
		MOV EAX, 0x49A7FC
		CALL EAX
		PUSH EAX
		PUSH DWORD PTR SS : [EBP + 0x8]

		CALL HKD_ControlEventClick

		TEST EAX, EAX
		JNZ Jump

		PUSH 0x004B3E75 // Fim da função, ignora completamente os handles
		RETN;

	Jump: // retornou true então executa normalmente as funções do exe

		CMP DWORD PTR SS : [EBP + 0x8] , 0x10006
			PUSH 0x004B2435
			RETN;
	}
}

__declspec(naked) void HookNaked::NKD_ControlEventClick()
{//by seitbnao
	__asm
	{
		MOV EAX, 0x6F0AB0
		MOV EDX, DWORD PTR DS : [EAX]
		MOV ECX, EDX
		MOV EAX, 0x49A7FC
		CALL EAX
		PUSH EAX
		PUSH DWORD PTR SS : [EBP + 0x8]
		CALL HKD_ControlEventClick
		TEST EAX, EAX
		JNZ Jump

		MOV ECX, DWORD PTR SS : [EBP - 0x2460]
		PUSH 0x0046B56E// Fim da função, ignora completamente os handles
		RETN

		Jump :// retornou true então executa normalmente as funções do exe
		PUSH 0x0046B578
			RETN
	}
}
