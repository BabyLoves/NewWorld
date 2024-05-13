#include "main.h"

//agora vamo testar o loop
void GameInterface::MainLoop(UIControl* Controller)
{
	if (!Controller)
		return;

	int sContexto = g_pInterface->SceneContext(); 

	//if (Controller->Handle && Controller->ControlType == 12)// 12 é exclusivo pra texto
	//{
	//	if (auto texto = reinterpret_cast<UITextControl*>(Controller))
	//	{
	//		 if (Controller->Handle == 769) //texto login de créditos
	//		{
	//			texto->setConstString("                All rights reserved AGE OF GOLD 7.62 2021");
	//		}
	//		/* texto->setConstString("%d", Controller->Handle);*/
	//	} 
	//}
	////if (auto Tela = g_pInterface->Instance()->getGuiFromHandle<UIControl>(65870))
	////{
	////	//500 - 193
	////	Tela->Top = 300;
	////	Tela->Left = 103;
	////	 
	////} 
#pragma region todos os compontes apos entrar no mundo
	if (eSceneType::SceneWorld == sContexto)
	{

	}
#pragma endregion

#pragma region todos os compontes na seleção de canal
	if (eSceneType::SceneLogin == sContexto)
	{
		
	} 
#pragma endregion
#pragma region todos os compontes na seleção de personagem
	if (eSceneType::SceneSelChar == sContexto)
	{
		
	}
#pragma endregion
	/*if (ConfigR::FixHPMP == TRUE)
	{
		if (auto HPJogador = g_pInterface->Instance()->getGuiFromHandle<UIProgressControl>(65621))
		{
			HPJogador->setFull(100000);
		}

		if (auto MPJogador = g_pInterface->Instance()->getGuiFromHandle<UIProgressControl>(65623))
		{
			MPJogador->setFull(100000);
		}
	}*/
}



_declspec(naked) void GameInterface::NKD_MainLoop()
{
	__asm
	{
		PUSH DWORD PTR SS : [EBP - 0x4]
		CALL  GameInterface::MainLoop

		MOV ECX, DWORD PTR SS : [EBP - 0x4]
		CMP DWORD PTR DS : [ECX + 0x10] , 0
		JE pulo

		MOV EDX, DWORD PTR SS : [EBP - 0x4]
		FLD DWORD PTR SS : [EBP - 0x14]
		FADD DWORD PTR DS : [EDX + 0x4c]
		FSTP DWORD PTR SS : [EBP - 0x14]

		MOV EAX, DWORD PTR SS : [EBP - 0x4]
		FLD DWORD PTR SS : [EBP - 0x10]
		FADD DWORD PTR DS : [EAX + 0x50]
		FSTP DWORD PTR SS : [EBP - 0x10]

		MOV ECX, DWORD PTR SS : [EBP - 0x8]
		ADD ECX, 1
		MOV  DWORD PTR SS : [EBP - 0x8] , ECX
		MOV EDX, DWORD PTR SS : [EBP - 0x4]
		MOV EAX, DWORD PTR SS : [EDX + 0x10]
		MOV  DWORD PTR SS : [EBP - 0x4] , EAX


		MOV ECX, 0x0040CFD2
		JMP ECX


		pulo :
		MOV ECX, 0x0040CF83
			JMP ECX
	}
}