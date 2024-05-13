#include "main.h"
#include "UISlot.h"
#define DONATESTORE 1
#define FILTRODROP 2
#define DROPLIST 3
#define TELEPORT 4
#define RANKING 5
#define TOWERWAR 6
#define QUEST 7

INT32 HKD_KeyPress_NewButton(BYTE button)
{
	auto player = GetChar();

	if (button == 'd' || button == 'D')
	{
		ReqAlias(2);
		auto GamePainel = g_pInterface->Instance()->getGuiFromHandle<UIControl>(981300);
		GamePainel->IsVisible = !GamePainel->IsVisible;
	}
	if (button == 'u' || button == 'U')
	{
		auto CHATBTS = g_pInterface->Instance()->getGuiFromHandle<UIControl>(65672);
		auto CHATOPCOES = g_pInterface->Instance()->getGuiFromHandle<UIControl>(90128);
		auto CHATBTCOMUM = g_pInterface->Instance()->getGuiFromHandle<UIControl>(90113);
		auto CHATGUIA = g_pInterface->Instance()->getGuiFromHandle<UIControl>(65667);
		auto CHATFUNDO = g_pInterface->Instance()->getGuiFromHandle<UIControl>(65943);
		auto CHATDIGITAR = g_pInterface->Instance()->getGuiFromHandle<UIControl>(65670);
		auto personagem = g_pInterface->getGuiFromHandle<UIControl>(65696);
		auto CloseChat = g_pInterface->getGuiFromHandle<UIControl>(190200);
		auto GamePainel = g_pInterface->Instance()->getGuiFromHandle<UIControl>(981300);

		auto ElementoModoFoto1 = g_pInterface->Instance()->getGuiFromHandle<UIControl>(65628);
		auto ElementoModoFoto3 = g_pInterface->Instance()->getGuiFromHandle<UIControl>(69633);
		auto ElementoModoFoto6 = g_pInterface->Instance()->getGuiFromHandle<UIControl>(65796);
		auto ElementoModoFoto7 = g_pInterface->Instance()->getGuiFromHandle<UIControl>(65795);
		auto ElementoModoFoto8 = g_pInterface->Instance()->getGuiFromHandle<UIControl>(65794);
		auto ElementoModoFoto9 = g_pInterface->Instance()->getGuiFromHandle<UIControl>(65793);
		auto ElementoModoFoto10 = g_pInterface->Instance()->getGuiFromHandle<UIControl>(65790);
		auto ElementoModoFoto11 = g_pInterface->Instance()->getGuiFromHandle<UIControl>(65791);
		auto bufftempo = g_pInterface->getGuiFromHandle<UIControl>(5749);

		auto PainelInv = g_pInterface->Instance()->getGuiFromHandle<UIControl>(589832);
		auto painelteleport = g_pInterface->Instance()->getGuiFromHandle<UIControl>(98300);

		ConfigR::gModoFoto = !ConfigR::gModoFoto;
		SendMsgExp(TNColor::Default, "___");
		SendMsgExp(TNColor::Default, "___");
		SendMsgExp(TNColor::Default, "___");
		SendMsgExp(TNColor::Default, "___");
		SendMsgExp(TNColor::Default, "___");
		SendMsgExp(TNColor::Default, "___");
		if (ConfigR::gModoFoto == TRUE)
		{
			CHATBTS->IsVisible = false;
			CHATGUIA->IsVisible = false;
			CHATFUNDO->IsVisible = false;
			CHATGUIA->IsVisible = false;
			CHATDIGITAR->IsVisible = false;
			CHATBTCOMUM->IsVisible = false;
			personagem->IsVisible = false;
			ElementoModoFoto1->IsVisible = false;
			ElementoModoFoto3->IsVisible = false;
			ElementoModoFoto6->IsVisible = false;
			ElementoModoFoto7->IsVisible = false;
			ElementoModoFoto8->IsVisible = false;
			ElementoModoFoto9->IsVisible = false;
			ElementoModoFoto10->IsVisible = false;
			ElementoModoFoto11->IsVisible = false;
			bufftempo->IsVisible = false;
			GamePainel->IsVisible = false;
			CloseChat->IsVisible = false;
		}
		if (ConfigR::gModoFoto == FALSE)
		{
			CHATBTS->IsVisible = true;
			CHATGUIA->IsVisible = true;
			CHATFUNDO->IsVisible = true;
			CHATGUIA->IsVisible = true;
			ElementoModoFoto1->IsVisible = true;
			ElementoModoFoto3->IsVisible = true;
			ElementoModoFoto6->IsVisible = true;
			ElementoModoFoto7->IsVisible = true;
			ElementoModoFoto8->IsVisible = true;
			ElementoModoFoto9->IsVisible = true;
			ElementoModoFoto10->IsVisible = true;
			ElementoModoFoto11->IsVisible = true;
			bufftempo->IsVisible = true;
			CloseChat->IsVisible = true;
		}
	}

	if (button == 'f' || button == 'F')
	{
		if (player.Equip[13].sIndex == 3901 || player.Equip[13].sIndex == 3902) {
			auto painelteleport = g_pInterface->Instance()->getGuiFromHandle<UIControl>(98300);
			auto GamePainel = g_pInterface->Instance()->getGuiFromHandle<UIControl>(981300);
		
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
		}
		else {
			SendMsgExp(TNColor::Default, "Equipe a fada Azul ou Vermelha");
		}
	}
	
	return 0;
}