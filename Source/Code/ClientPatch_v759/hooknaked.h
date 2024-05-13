#include "../Basedef.h"

#ifndef _HOOKNAKED_H_
#define _HOOKNAKED_H_

class HookNaked
{
private:

	HookNaked() = delete;
	virtual ~HookNaked() = delete;
	HookNaked(const HookNaked&) = delete;
	HookNaked& operator=(const HookNaked&) = delete;
public:

	static void HookFunction(DWORD* pointer_gameinterface);
	static bool Start();
	static void NKD_ScrollMouseController();
	static void NKD_NPCClick();
	static void NKD_ClientReceiver();
	static void NKD_ClientSended();
	static void NKD_FixItemDescription();
	static void NKD_GreenTime_NewArea();
	static void NKD_CallBack_Event_Esc();
	static bool __stdcall HKD_CallBack_Event_Esc();
	static void NKD_ItemPrice_FormatDecimal_03();
	static void NKD_ItemPrice_FormatDecimal_02();
	static void NKD_ItemPrice_FormatDecimal();
	static void NKD_ChangeTabColor();
	static void NKD_NewItensDays_1();
	static void NKD_NewItensDays_2();
	static void NKD_FixMageMacro();
	static void NKD_ItemPriceString();
	static void NKD_ProcessClientMessage_03BBh();
	static void NKD_AddAmountItem();

	static void NKD_CorrectBones();
	static void NKD_LoadFiles();
	static void NKD_FixIndex();

	static void NKD_ValidadeFadas();
	static void NKD_ValidadeTrajes();
	static void NKD_ValidadeEsferas();
	static void NKD_GetItemAbility_Esfera();
	static void NKD_SendChat();
	static void NKD_KeyPress_NewButton();
	static void NKD_Cam();
	static void NKD_UpdateResources();
	static void NKD_SpeakChatColor();
	static void NKD_NewEffectTraje();
	static void NKD_noSancFace();
	static void NKD_noSancID();
	static void NKD_AddVolatileMessageItem();
	static void NKD_AddVolatileMessageBox();
	static void NKD_HandleScene();
	static void NKD_ControlEventClick();
	static void NKD_FixSkillBar();
	static void NKD_SGrid_OnMouseMove_SkinName();
	static void NKD_ProcessViewMount_Skins();
	static void NKD_SetDefaultLocation();
	static int HKD_GetSkillType(int skillId);
	static void NKD_GetAttackType();
	static void NKD_GetAttackType2();
	static void NKD_ChangeTextureFont();
	static void NKD_SetHPNumberOnMonsterHP();
	static void NKD_GetCreateMob_ChangeHPText();

	static void ToPrettySize(int value, char* str);
	static bool __stdcall HKD_SetHPNumberOnMosterHP(int pointer);
	static void FormatIntegerToStringWithDots(char* string, int value);
	static void SetStringOnHP(int pointer, char* str);
	static void NKD_NewNPCComp();
};


#endif