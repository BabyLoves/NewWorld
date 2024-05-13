#include "main.h" 
#include "GameInterface.h"
#include "UISlot.h"
#define JEPHI 8

int ProcessNPCClick(DWORD* mob)
{
	auto Mob = reinterpret_cast<buffer_srd*>(mob);
	

	if (Mob->mobFace == 58 && Mob->Elmo == 115)//Jephi
	{
		ConfigR::WindowControl = JEPHI;
		auto PainelJephi = g_pInterface->Instance()->getGuiFromHandle<UIControl>(117900);
		PainelJephi->IsVisible = true;

		auto TxShopGrid = g_pInterface->Instance()->getGuiFromHandle<UITextControl>(117930);
		TxShopGrid->setConstString("Clique no item escolhido para compor");
		TxShopGrid->setTextColor(TNColor::CornBlue);

		STRUCT_ITEM item[5];
		int Index[5] = { 413, 412, 692, 1740, 1741 };

		for (int i = 0; i < 5; i++) {
			auto JephiGrid = g_pInterface->Instance()->getGuiFromHandle<UISlot>(117901 + i);
			*(int*)((int)JephiGrid + 0x400) = 0x5;
			JephiGrid->deleteItemGui(0, 0);

			memset(&item[i], 0, sizeof(STRUCT_ITEM));
			item[i].sIndex = Index[i];
			JephiGrid->setGui((int)JephiGrid->New(item[i], 0, 0), 0, 0);
		}
		return TRUE;
	}

	return FALSE;
}

__declspec(naked) void HookNaked::NKD_NPCClick()
{
	__asm
	{
		MOV EAX, DWORD PTR SS : [EBP - 0x3C]
		MOV ECX, DWORD PTR DS : [EAX + 0xBC]
		PUSH ECX
		CALL ProcessNPCClick
		ADD ESP, 0x4
		CMP EAX, 1
		JNE ContinueExec

		PUSH 0x00460C46
		RETN

		ContinueExec :
		MOV ECX, DWORD PTR SS : [EBP - 0x4]
			CMP DWORD PTR DS : [ECX + 0x20] , 0
			PUSH 0x00460535
			RETN
			//byseitbnao
	}
}