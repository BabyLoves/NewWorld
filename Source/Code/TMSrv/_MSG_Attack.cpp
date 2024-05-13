/*
*   Copyright (C) {2015}  {Victor Klafke, Charles TheHouse}
*
*   This program is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program.  If not, see [http://www.gnu.org/licenses/].
*
*   Contact at: victor.klafke@ecomp.ufsm.br
*/
#include "ProcessClientMessage.h"
#include <windows.h>
#include <time.h>
#include <random>
#include <ctime>

void Exec_MSG_Attack(int conn, char* pMsg)
{
	MSG_Attack* m = reinterpret_cast<MSG_Attack*>(pMsg);

	int Size = m->Size;

	if (m->PosX < 0 || m->PosX >= MAX_GRIDX)
		return;

	if (m->PosY < 0 || m->PosY >= MAX_GRIDX)
		return;

	if (m->AttackerID < 0 || m->PosY >= MAX_MOB)
		return;

	if (Size > sizeof(MSG_Attack)) //CONTROLE DE SIZE
	{
		SendClientMessage(conn, "Impossível executar ação6, tente mais tarde.");
		return;
	}

	m->ID = ESCENE_FIELD;

	if (pUser[conn].TradeMode)
	{
		SendClientMessage(conn, g_pMessageStringTable[_NN_CantWhenAutoTrade]);
		return;
	}

	if (pUser[conn].Mode != USER_PLAY)
	{
		SendHpMode(conn);
		return;
	}

	if (m->SkillIndex == 110 || m->SkillIndex == 96 || m->SkillIndex == 90) //hack use skill kefra 20/10
	{
		//pMob[conn].CrackError = SystemTime + 10800;
		/*
		snprintf(temp, sizeof(temp), "Banido por usar skill de Kefra");
		SystemLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, temp);*/
		SendBanAccount(conn, Banned::Permanente);
		return;
	}

	if (*(short*)&pMsg[48] == 7 && *(short*)&pMsg[73] == 0xBBB)  //HACK DIA 20/10   //one hit
	{
		/*
		snprintf(temp, sizeof(temp), "Banido por usar hack one hit");
		SystemLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, temp);*/
		SendBanAccount(conn, Banned::Permanente);
		return;
	}


	//Personagem morto tentando usar uma skill que não é ressureição
	if (pMob[conn].MOB.CurrentScore.Hp == 0 && m->SkillIndex != 99)
	{
		SendHpMode(conn);
		//AddCrackError(conn, 1, 8);
		return;
	}

	short TargetKilled[MAX_TARGET] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	unsigned int ClientTick = m->ClientTick;

	unsigned int LastAttackTick = 0;

	if (ClientTick != SKIPCHECKTICK && pUser[conn].LastAttackTick != SKIPCHECKTICK && m->ClientTick < (unsigned int)pUser[conn].LastAttackTick + 600)
	{
		CloseUser(conn);
		return;
	}

	if (ClientTick != SKIPCHECKTICK && pUser[conn].LastAttackTick != SKIPCHECKTICK)
	{
		if (ClientTick < static_cast<unsigned int>(pUser[conn].LastAttackTick) - 100)
			AddCrackError(conn, 4, 7);

		LastAttackTick = pUser[conn].LastAttackTick;

		pUser[conn].LastAttackTick = ClientTick;
		pUser[conn].LastAttack = m->SkillIndex;
	}

	if (ClientTick != SKIPCHECKTICK)
	{
		int ClientTick15sec = 0;

		if (CurrentTime <= 0x1D4C0)
			ClientTick15sec = 0;
		else
			ClientTick15sec = CurrentTime - 120000;

		if (static_cast<unsigned int>(ClientTick) > CurrentTime + 15000 || static_cast<int>(ClientTick) < ClientTick15sec)
		{
			//Log("etc,clienttime faster than 15 sec - MSG_ATTACK", pUser[conn].AccountName, pUser[conn].IP);
			//AddCrackError(conn, 1, 107);

			return;
		}

		pUser[conn].LastAttackTick = ClientTick;
	}

	int skillnum = m->SkillIndex;

	int tx = m->TargetX;
	int ty = m->TargetY;

	if (ClientTick != SKIPCHECKTICK && skillnum != 42 && (tx != m->TargetX || ty != m->TargetY))
	{

		return;
	}

	if (skillnum >= 0 && skillnum < MAX_SKILLINDEX && ClientTick != SKIPCHECKTICK)
	{
		if (skillnum < -1 || skillnum > MAX_SKILLINDEX)
		{
			return;
		}

		if (g_pSpell[skillnum].Passive == 1)
			return;


		if (pMob[conn].MOB.Class == 1)
		{
			for (int i = 0; i < MAX_AFFECT; i++)
			{
				if (pMob[conn].Affect[i].Type != 6)
					continue;

				pMob[conn].Affect[i].Type = 0;
				pMob[conn].Affect[i].Value = 0;
				pMob[conn].Affect[i].Level = 0;
				pMob[conn].Affect[i].Time = 0;

				pMob[conn].GetCurrentScore(conn);
				SendScore(conn);

				break;
			}
		}


		if (LastAttackTick != -1 && ClientTick != SKIPCHECKTICK)
		{
			int isTime = ClientTick - LastAttackTick;

			int skilldelay = g_pSpell[skillnum].Delay;

			if ((pMob[conn].MOB.Rsv & RSV_CAST) != 0 && skilldelay >= 2)
				skilldelay--;

			skilldelay = skilldelay * 1000;

			if (isTime < 700)
			{

				return;
			}
		}

		pUser[conn].LastAttackTick = m->ClientTick;

		if ((skillnum / 24) != pMob[conn].MOB.Class && (skillnum / 24) <= 3)
		{
			//Log("MSG_Attack, Request other class skill", pUser[conn].AccountName, pUser[conn].IP);
			return;
		}
	}

	/*	int Level = 0;
		int Delay = 100;
		int Special = 0;

		if (skillnum < 0 || skillnum >= MAX_SKILLINDEX)
		{
		if (skillnum >= 96 && skillnum <= MAX_SKILLINDEX)
		{
		if (skillnum == 97)
		{
		if (m->PosX <= 0 || m->PosX >= 4096 || m->PosY <= 0 || m->PosY >= 4096)
		{
		Log("err,mortar invalid", pUser[conn].AccountName, pUser[conn].IP);
		return;
		}

		int itemslot = pItemGrid[m->PosY][m->PosX];

		if (itemslot <= 0 || itemslot >= MAX_ITEM || pItem[itemslot].ITEM.sIndex != 746)
		{
		Log("err,mortar invalid", pUser[conn].AccountName, pUser[conn].IP);
		return;
		}
		m->Motion = 1;
		}
		else
		{
		int skill = skillnum - 72;
		int learned = 1 << (skillnum - 72);

		if (m->ClientTick != SKIPCHECKTICK && !(learned & pMob[conn].MOB.LearnedSkill))
		{
		if (AddCrackError(conn, 208, 1))
		return;
		}
		}
		Level = pMob[conn].MOB.CurrentScore.Level;
		Delay += Level;
		Special = Level;
		}
		}

		else
		{
		int skillkind = skillnum % MAX_SKILL / 8 + 1;

		if (ClientTick != SKIPCHECKTICK)
		{
		int learn = skillnum % MAX_SKILL;
		int learnedSkill = 1 << learn;

		if (m->ClientTick != SKIPCHECKTICK && !(learnedSkill & pMob[conn].MOB.LearnedSkill))
		{
		if (AddCrackError(conn, 8, 10))
		return;
		}

		if (skillkind < 0 || skillkind > 3)
		{
		Log("Skill kind out of bound - MSG_ATTACK", pUser[conn].AccountName, pUser[conn].IP);
		return;
		}
		}
		Level = pMob[conn].MOB.CurrentScore.Special[skillkind];
		Delay += Level;
		Special = Level;
		}*/


	int Level = 0;
	int Delay = 100;
	int Special = 0;

	if (skillnum >= 0 && skillnum < 96)
	{
		int getSkillMaster = ((skillnum % 24) / 8) + 1;

		if (ClientTick != SKIPCHECKTICK)
		{
			int learn = skillnum % 24;
			int learnedSkill = 1 << learn;

			if (m->ClientTick != SKIPCHECKTICK && (pMob[conn].MOB.LearnedSkill & learnedSkill) == FALSE)
			{
				//AddCrackError(conn, 8, 10);
				return;
			}

			if (getSkillMaster <= 0 || getSkillMaster > 3)
			{
				//Log("Skill kind out of bound - MSG_ATTACK", pUser[conn].AccountName, pUser[conn].IP);
				return;
			}
		}

		Level = pMob[conn].MOB.CurrentScore.Special[getSkillMaster];
		Delay = Delay + Level;
		Special = Level;
	}
	else
	{
		if (skillnum >= 96 && skillnum <= 103)
		{
			if (skillnum == 97)
			{
				if (m->PosX > 0 && m->PosX < 4096 && m->PosY > 0 && m->PosY < 4096)
				{
					int itemId = pItemGrid[m->PosX][m->PosY];
					if (itemId > 0 && itemId < MAX_ITEMLIST && pItem[itemId].ITEM.sIndex == 746)
						m->Motion = 1;
					else
					{
						//Log("err, mortar invalid", pUser[conn].AccountName, pUser[conn].IP);
						return;
					}
				}
				else
				{
					//Log("err, mortar invalid", pUser[conn].AccountName, pUser[conn].IP);
					return;
				}
			}
			else
			{
				int learn = skillnum - 72;
				int learnedSkill = 1 << learn;
				if (m->ClientTick != SKIPCHECKTICK && (pMob[conn].MOB.LearnedSkill & learnedSkill) == FALSE)
				{
					//AddCrackError(conn, 208, 1);
					return;
				}
			}

			Level = pMob[conn].MOB.CurrentScore.Level;
			Delay = Delay + Level;
			Special = Level;
		}
	}

#pragma region Escudo_dourado
	if (skillnum == 85)
	{
		int coin = 10 * Level;
		if (pMob[conn].MOB.Coin < coin)
			return;

		pMob[conn].MOB.Coin -= coin;
		SendEtc(conn);
	}
#pragma endregion

	int Alvo = m->Dam[0].TargetID;

#pragma region Range Hack  
	if (conn != Alvo)
	{
		int Spectral = -1;
		int WeaponRange = -1;
		int Range = 2;
		int Distance = -1;

		if (pMob[conn].MOB.LearnedSkill & (1 << 29))
			Spectral = 1;

		if (pMob[conn].MOB.Equip[6].sIndex != 0)
		{
			for (int i = 0; i < MAX_STATICEFFECT; i++)
			{
				if (g_pItemList[pMob[conn].MOB.Equip[6].sIndex].stEffect[i].sEffect == EF_RANGE)
					WeaponRange = g_pItemList[pMob[conn].MOB.Equip[6].sIndex].stEffect[i].sValue;
			}
		}

		if (Spectral != -1)
			Range = Range + 1;

		if (Alvo > 0 && Alvo < MAX_MOB)
			Distance = BASE_GetDistance(pMob[conn].TargetX, pMob[conn].TargetY, pMob[Alvo].TargetX, pMob[Alvo].TargetY);

		if (Distance <= 0 || Distance >= 150)
			Distance = -1;

		// Astaroth transformation
		if (pMob[conn].MOB.Equip[0].sIndex == 24 && Distance > Range + 5)
		{
			/*printf("\nPlayer using Astaroth has just attacked from a distance", pUser[conn].AccountName, pUser[conn].IP);*/
			return;
		}
		// Magic range attack
		else if (m->Motion == 255)
		{
			if (Distance > Range + g_pSpell[m->SkillIndex].Range + 3)
			{
				/*printf("\nPlayer using Magic Attack has just attacked from a distance", pUser[conn].AccountName, pUser[conn].IP);*/
				return;
			}
		}
		else
		{
			// Attacked without possessing any weapon
			if (WeaponRange == -1)
			{
				if (Distance > Range + 3)
				{
					/*printf("\nPlayer without weapon has just attacked from a distance without weapon", pUser[conn].AccountName, pUser[conn].IP);*/
					return;
				}
			}
			// Attacked too far
			else
			{
				if (Distance > Range + WeaponRange + 3)
				{
					/*printf("\nPlayer with weapon has just attacked from a distance", pUser[conn].AccountName, pUser[conn].IP);*/
					return;
				}
			}
		}
	}
#pragma endregion

#pragma region Resfriamento
	// Skill Hack
	if (skillnum >= 0 && skillnum < skillnum < 103)
	{
		int CurrentTime = GetTickCount64();
		int skilldelay = g_pSpell[skillnum].Delay;
		if (pUser[conn].Ingame.Skill[skillnum].IntervalTime)
		{
			int PreviousAttackTime = CurrentTime - pUser[conn].Ingame.Skill[skillnum].IntervalTime;
			if (&pMob[conn].MOB.Equip[4] && BASE_GetItemSanc(&pMob[conn].MOB.Equip[4]) >= 9) // Verificar se tem Manopla +9 = -1 Delay Skill
				skilldelay--;
			for (int i = 0; i < MAX_AFFECT; i++) {
				int index = pMob[conn].Affect[i].Type;
				if (index == NULL)
					continue;
				int master = pMob[conn].Affect[i].Level;
				if (index == 8) { // Sagacidade
					if ((master & (1 << 0)) != 0)
						skilldelay--;

				}
			}
			if (skillnum == 102) skilldelay = 1;
			skilldelay = skilldelay * 1000;
			if (skilldelay <= 0) skilldelay = 400;
			// correção skill cura 
			if (skillnum == 29) skilldelay = 1;
			if (skillnum == 47) skilldelay = 1;
			pUser[conn].Ingame.Skill[skillnum].IntervalTime = CurrentTime;
			// Skill Delay Hack
			if (PreviousAttackTime < (skilldelay - 300)) {
				for (int i = 0; i < 13; i++) {
					short target = m->Dam[i].TargetID;
					short damage = m->Dam[i].Damage;

					if (target <= NULL || target >= 12800)
						continue;

					m->Dam[i].TargetID = 0;
					m->Dam[i].Damage = 0;
					return;
				}
				memset(pMsg, 0, m->Size);
				return;
			}
		}
		pUser[conn].Ingame.Skill[skillnum].IntervalTime = CurrentTime;
	}
#pragma endregion 

	int Mp = pMob[conn].MOB.CurrentScore.Mp;
	int ReqMp = pUser[conn].ReqMp;
#pragma region Consumo de mana
	if (skillnum >= 0 && skillnum < MAX_SKILLINDEX)
	{
		int ManaSpent = BASE_GetManaSpent(skillnum, pMob[conn].MOB.SaveMana, Special);

		if ((pMob[conn].MOB.CurrentScore.Mp - ManaSpent) < 0)
		{
			SendSetHpMp(conn);
			return;
		}

		pMob[conn].MOB.CurrentScore.Mp = pMob[conn].MOB.CurrentScore.Mp - ManaSpent;
		pUser[conn].ReqMp = pUser[conn].ReqMp - ManaSpent;
		SetReqMp(conn);

		if (pMob[conn].MOB.Class == 1)
		{
			if (pMob[conn].extra.SecLearnedSkill & 0x1) // Cenote
			{
				pMob[conn].MOB.CurrentScore.Mp = pMob[conn].MOB.CurrentScore.Mp - ManaSpent * 2;
				pUser[conn].ReqMp = pUser[conn].ReqMp - ManaSpent * 2;
				SetReqMp(conn);
			}

			for (int i = 0; i < MAX_AFFECT; i++) // Magia Misteriosa
			{
				if (pMob[conn].Affect[i].Type == 42)
				{
					pMob[conn].MOB.CurrentScore.Mp = pMob[conn].MOB.CurrentScore.Mp - ManaSpent * 2;
					pUser[conn].ReqMp = pUser[conn].ReqMp - ManaSpent * 2;
					SetReqMp(conn);
				}
			}
		}

		if (pMob[conn].MOB.Class == 0 && (pMob[conn].extra.SecLearnedSkill & 0x100)) // Espelho Mágico
		{
			pMob[conn].MOB.CurrentScore.Mp = pMob[conn].MOB.CurrentScore.Mp - ManaSpent / 2;
			pUser[conn].ReqMp = pUser[conn].ReqMp - ManaSpent / 2;
			SetReqMp(conn);
		}
	}

	m->CurrentMp = pMob[conn].MOB.CurrentScore.Mp;
	m->ReqMp = pUser[conn].ReqMp;
#pragma endregion

	int master = 0;

	if (!pMob[conn].MOB.Class && pMob[conn].MOB.LearnedSkill & 0x4000)
	{
		master = pMob[conn].MOB.CurrentScore.Special[2] / 20;

		if (master < 0)
			master = 0;

		if (master > 15)
			master = 15;
	}

	DoRemoveSamaritano(conn);

	int Exp = 0;
	int mylevel = pMob[conn].MOB.CurrentScore.Level;

	unsigned char map_att = GetAttribute(pMob[conn].TargetX, pMob[conn].TargetY) & 0x40;

	int hp = pMob[conn].MOB.CurrentScore.Hp;

	int UNK2 = 0;
	unsigned char DoubleCritical = 0;

	/*if (skillnum == 102)
	{
	MSG_STANDARDPARM pSetClan;
	pSetClan.Type = _MSG_SetClan;
	pSetClan.Size = sizeof MSG_STANDARDPARM;
	pSetClan.ID = conn;
	pSetClan.Parm = pMob[conn].MOB.Clan;

	GridMulticast(pMob[conn].TargetX, pMob[conn].TargetY, (MSG_STANDARD*)&pSetClan, 0);
	}*/

	m->CurrentHp = pMob[conn].MOB.CurrentScore.Hp;

	if (skillnum == 79)
	{
		m->ClientTick = 0xE0A1ACA;
		m->Motion = 254;

		m->TargetX = pMob[conn].TargetX;
		m->TargetY = pMob[conn].TargetY;

		m->AttackerID = conn;
		m->SkillIndex = 79;

		for (int x = 1; x < 6; x++)
		{
			m->Dam[x].Damage = m->Dam[0].Damage;
			m->Dam[x].TargetID = m->Dam[0].TargetID;
		}
	}

#pragma region Loop Target
	for (int i = 0; i < MAX_TARGET; i++)
	{
		if (i >= MAX_TARGET && m->Size <= sizeof(MSG_Attack))
			break;
		if (i >= 1 && m->Size <= sizeof(MSG_AttackOne))
			break;
		if (i >= 2 && m->Size <= sizeof(MSG_AttackTwo))
			break;

		int idx = m->Dam[i].TargetID;

		if (idx <= 0 || idx >= MAX_MOB)
			continue;

		// Tiro Direto
		if (pMob[conn].MOB.Class == 3 && (pMob[conn].extra.SecLearnedSkill & 0x100))
		{
			for (int i = 0; i < MAX_AFFECT; i++)
			{
				if (pMob[conn].Affect[i].Type == 28)
				{
					if ((rand() % 100) < 40)
					{
						if (pMob[idx].Affect[i].Type == 44)
						{
							pMob[idx].Affect[i].Type = 44;
							pMob[idx].Affect[i].Value = 1;
							pMob[idx].Affect[i].Level = 1;
							pMob[idx].Affect[i].Time = 4;

							pMob[idx].GetCurrentScore(idx);
							SendScore(idx);
							break;
						}
						else
						{
							pMob[idx].Affect[i].Type = 44;
							pMob[idx].Affect[i].Value = 1;
							pMob[idx].Affect[i].Level = 1;
							pMob[idx].Affect[i].Time = 4;

							pMob[idx].GetCurrentScore(idx);
							SendScore(idx);
							break;
						}
					}
				}
			}
		}

		if (pMob[conn].MOB.Class == 3)
			DoRemoveHide(conn);

		if (pMob[idx].MOB.Class == 3)
			DoRemoveHide(idx);

		if (pMob[idx].Mode == MOB_EMPTY) // Checa possibilidade de Freeze
		{
			SendRemoveMob(conn, idx, 1, 0);
			continue;
		}

		if (pMobGrid[pMob[conn].TargetY][pMob[conn].TargetX] == 0)
			pMobGrid[pMob[conn].TargetY][pMob[conn].TargetX] = conn;

		if (idx >= MAX_USER && (pMob[idx].MOB.Equip[0].sIndex == 219 || pMob[idx].MOB.Equip[0].sIndex == 220) && ((pMob[idx].TargetX / 128) == 26 && (pMob[idx].TargetY / 128) == 12))
		{
			m->Dam[i].TargetID = 0;
			m->Dam[i].Damage = 0;

			continue;
		}

		if (pMob[idx].MOB.CurrentScore.Hp <= 0 && skillnum != 99 && skillnum != 31)
		{
			SendSetHpMp(idx);
			m->Dam[i].Damage = 0;
			m->Dam[i].TargetID = 0;
			continue;
		}

		if (pMob[idx].MOB.CurrentScore.Hp <= 0 && m->SkillIndex != 31 && m->SkillIndex != 99)
		{
			m->Dam[i].TargetID = 0;
			m->Dam[i].Damage = 0;

			SendRemoveMob(conn, idx, 1, 0);
			continue;
		}

		if (pMob[idx].MOB.Merchant == 4 || pMob[idx].MOB.Merchant == 43 || pMob[idx].MOB.Merchant == 1 || pMob[idx].MOB.Merchant == 100)
		{
			m->Dam[i].TargetID = 0;
			m->Dam[i].Damage = 0;
			continue;
		}

		if (skillnum != 42 && (pMob[conn].TargetX < pMob[idx].TargetX - VIEWGRIDX || pMob[conn].TargetX > pMob[idx].TargetX + VIEWGRIDX || pMob[conn].TargetY < pMob[idx].TargetY - VIEWGRIDY || pMob[conn].TargetY > pMob[idx].TargetY + VIEWGRIDY))
		{
			SendRemoveMob(conn, idx, 1, 0);
			continue;
		}

		int dam = m->Dam[i].Damage;

		if (dam != -2 && dam != -1 && dam)
		{
			m->Dam[i].Damage = 0;
			//AddCrackError(conn, 10, 77);

			continue;
		}

		int leader = pMob[conn].Leader;

		if (leader == 0)
			leader = conn;

		int mobleader = pMob[idx].Leader;

		if (mobleader == 0)
			mobleader = idx;

		int Guild = pMob[conn].MOB.Guild;

		if (pMob[conn].GuildDisable)
			Guild = 0;

		int MobGuild = pMob[idx].MOB.Guild;

		if (pMob[idx].GuildDisable)
			MobGuild = 0;

		if (Guild == 0 && MobGuild == 0)
			Guild = -1;

		if (BrState && BRItem > 0 && pMob[conn].TargetX >= 2604 && pMob[conn].TargetY >= 1708 && pMob[conn].TargetX <= 2648 && pMob[conn].TargetY <= 1744)
			Guild = -1;

		int Clan = pMob[conn].MOB.Clan;
		int MobClan = pMob[idx].MOB.Clan;

		int isFrag = 0;

		if (Clan == 7 && MobClan == 7 || Clan == 8 && MobClan == 8)
			isFrag = 1;

		if (CWarTower::TowerAttack(conn, idx) == FALSE)
		{
			m->Dam[i].TargetID = 0;
			m->Dam[i].Damage = 0;
			continue;
		}
		if (conn != idx && conn > 0 && conn < MAX_USER && idx > 0 && idx < MAX_USER && RvRState == 0 && CastleState == 0 && GTorreState == 0 && NewbieEventServer == 0)
		{
			int AttackerPK = pUser[conn].PKMode;
			int TargetPK = pUser[idx].PKMode;
			int TargetGuilty = GetGuilty(idx);

			unsigned char attributemap = GetAttribute(pMob[conn].TargetX, pMob[conn].TargetY) & 64;

			if (dam == -2 && !TargetPK && !TargetGuilty && attributemap || dam == -1 && skillnum >= 0 && skillnum <= MAX_SKILLINDEX && g_pSpell[skillnum].Aggressive && attributemap && !TargetPK && !TargetGuilty)
			{
				m->Dam[i].TargetID = 0;
				m->Dam[i].Damage = 0;
				continue;
			}
		}

		//TODO: CONTADORO DE HIST EVENTO
		if (pMob[idx].GenerateIndex == 4734 || pMob[idx].GenerateIndex == 4735)
		{
			if (conn <= 0 && conn >= MAX_USER)
				continue;

			if (pUser[conn].Mode != USER_PLAY)
				continue;

			if (EventStatus == 0)
				continue;

			if (pUser[conn].DiariaState == 0) {
				CloseUser(conn);
				m->Dam[i].TargetID = 0;
				m->Dam[i].Damage = 0;
				continue;
			}
			if (GetInView(conn, idx) == FALSE) {
				CloseUser(conn);
				m->Dam[i].TargetID = 0;
				m->Dam[i].Damage = 0;
				continue;
			}
			m->Dam[i].TargetID = 0;
			m->Dam[i].Damage = 0;
			SendEventCount(conn);			
			continue;
		}

		/*if (((pMob[conn].TargetX) / 128) == 31 && ((pMob[conn].TargetY) / 128) == 31) {

			if (conn <= 0 && conn >= MAX_USER)
				continue;

			if (pUser[conn].Mode != USER_PLAY)
				continue;

			if (pUser[conn].Admin != 1)
				DoRecall(conn);
		}*/

#pragma region ANTI PULO LAN

		if (!strcmp(pMob[idx].MOB.MobName, "AranhaAmald") || !strcmp(pMob[idx].MOB.MobName, "MorlockAmald") || !strcmp(pMob[idx].MOB.MobName, "HorizonAmald") || !strcmp(pMob[idx].MOB.MobName, "GargulaAmald"))
		{
			if (conn <= 0 && conn >= MAX_USER)
				continue;

			if (pUser[conn].Mode != USER_PLAY)
				continue;

			if (pMob[conn].LanNFlag != 1)
			{
				SystemLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, "hack, Pulo LanN");
				CloseUser(conn);
				m->Dam[i].TargetID = 0;
				m->Dam[i].Damage = 0;
				continue;
			}
		}

		if (!strcmp(pMob[idx].MOB.MobName, "KalintzAmald") || !strcmp(pMob[idx].MOB.MobName, "EntAmald") || !strcmp(pMob[idx].MOB.MobName, "LoboAmald") || !strcmp(pMob[idx].MOB.MobName, "KalintzAmald "))
		{
			if (conn <= 0 && conn >= MAX_USER)
				continue;

			if (pUser[conn].Mode != USER_PLAY)
				continue;

			if (pMob[conn].LanMFlag != 1)
			{
				SystemLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, "hack, Pulo LanM");
				CloseUser(conn);
				m->Dam[i].TargetID = 0;
				m->Dam[i].Damage = 0;
				continue;
			}
		}


		if (!strcmp(pMob[idx].MOB.MobName, "PerBerserker ") || !strcmp(pMob[idx].MOB.MobName, "PerValkyrie ") || !strcmp(pMob[idx].MOB.MobName, "PreKalintz M") || !strcmp(pMob[idx].MOB.MobName, "PreKalintz H "))
		{
			if (conn <= 0 && conn >= MAX_USER)
				continue;

			if (pUser[conn].Mode != USER_PLAY)
				continue;

			if (pMob[conn].LanAFlag != 1)
			{
				SystemLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, "hack, Pulo LanA");
				CloseUser(conn);
				m->Dam[i].TargetID = 0;
				m->Dam[i].Damage = 0;
				continue;
			}
		}

#pragma endregion ANTI PULO LAN

#pragma region Anti Pulo Quest
		//coveiro
		if (pMob[conn].TargetX > 2379 && pMob[conn].TargetY > 2076 &&
			pMob[conn].TargetX < 2426 && pMob[conn].TargetY < 2133) {

			if (conn <= 0 && conn >= MAX_USER)
				continue;

			if (pUser[conn].Mode != USER_PLAY)
				continue;

			if (pMob[conn].QuestFlag != 1)
			{
				SystemLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, "hack, Pulo Coveiro");
				CloseUser(conn);
				m->Dam[i].TargetID = 0;
				m->Dam[i].Damage = 0;
				continue;
			}

		}
		//carbuncle
		if (pMob[conn].TargetX > 2228 && pMob[conn].TargetY > 1700 &&
			pMob[conn].TargetX < 2257 && pMob[conn].TargetY < 1728) {

			if (conn <= 0 && conn >= MAX_USER)
				continue;

			if (pUser[conn].Mode != USER_PLAY)
				continue;

			if (pMob[conn].QuestFlag != 2)
			{
				SystemLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, "hack, Pulo Carbuncle");
				CloseUser(conn);
				m->Dam[i].TargetID = 0;
				m->Dam[i].Damage = 0;
				continue;
			}
		}
		//cura
		if (pMob[conn].TargetX > 459 && pMob[conn].TargetY > 3887 &&
			pMob[conn].TargetX < 497 && pMob[conn].TargetY < 3916) {

			if (conn <= 0 && conn >= MAX_USER)
				continue;

			if (pUser[conn].Mode != USER_PLAY)
				continue;

			if (pMob[conn].QuestFlag != 3)
			{
				SystemLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, "hack, Pulo Cura");
				CloseUser(conn);
				m->Dam[i].TargetID = 0;
				m->Dam[i].Damage = 0;
				continue;
			}
		}
		//mana
		if (pMob[conn].TargetX > 658 && pMob[conn].TargetY > 3728 &&
			pMob[conn].TargetX < 703 && pMob[conn].TargetY < 3762) {

			if (conn <= 0 && conn >= MAX_USER)
				continue;

			if (pUser[conn].Mode != USER_PLAY)
				continue;

			if (pMob[conn].QuestFlag != 4)
			{
				SystemLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, "hack, Pulo Mana");
				CloseUser(conn);
				m->Dam[i].TargetID = 0;
				m->Dam[i].Damage = 0;
				continue;
			}
		}
		//emblema
		if (pMob[conn].TargetX > 1312 && pMob[conn].TargetY > 4027 &&
			pMob[conn].TargetX < 1348 && pMob[conn].TargetY < 4055) {

			if (conn <= 0 && conn >= MAX_USER)
				continue;

			if (pUser[conn].Mode != USER_PLAY)
				continue;

			if (pMob[conn].QuestFlag != 5)
			{
				SystemLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, "hack, Pulo Emblema");
				CloseUser(conn);
				m->Dam[i].TargetID = 0;
				m->Dam[i].Damage = 0;
				continue;
			}
		}
#pragma endregion

#pragma region Antipulo Pista
		//Pista +0
		if (pMob[conn].TargetX > 3327 && pMob[conn].TargetY > 1595 && pMob[conn].TargetX < 3455 && pMob[conn].TargetY < 1660)
		{
			if (conn <= 0 && conn >= MAX_USER)
				continue;

			if (pUser[conn].Mode != USER_PLAY)
				continue;

			int partyleader = pMob[conn].Leader;

			if (partyleader <= 0)
				partyleader = conn;

			if (Pista[0].Party[0].LeaderID != partyleader && Pista[0].Party[1].LeaderID != partyleader && Pista[0].Party[2].LeaderID != partyleader) {
				SystemLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, "hack, Pulo Pista0");
				CloseUser(conn);
			}

		}
		//Pista +1
		if (pMob[conn].TargetX > 3340 && pMob[conn].TargetY > 1540 && pMob[conn].TargetX < 3440 && pMob[conn].TargetY < 1600)
		{
			if (conn <= 0 && conn >= MAX_USER)
				continue;

			if (pUser[conn].Mode != USER_PLAY)
				continue;

			int partyleader = pMob[conn].Leader;

			if (partyleader <= 0)
				partyleader = conn;

			if (Pista[1].Party[0].LeaderID != partyleader && Pista[1].Party[1].LeaderID != partyleader && Pista[1].Party[2].LeaderID != partyleader) {
				SystemLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, "hack, Pulo Pista1");
				CloseUser(conn);
			}
		}
		//Pista +2
		if (pMob[conn].TargetX > 3330 && pMob[conn].TargetY > 1420 && pMob[conn].TargetX < 3455 && pMob[conn].TargetY < 1470)
		{
			if (conn <= 0 && conn >= MAX_USER)
				continue;

			if (pUser[conn].Mode != USER_PLAY)
				continue;

			int partyleader = pMob[conn].Leader;

			if (partyleader <= 0)
				partyleader = conn;

			if (Pista[2].Party[0].LeaderID != partyleader && Pista[2].Party[1].LeaderID != partyleader && Pista[2].Party[2].LeaderID != partyleader) {
				SystemLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, "hack, Pulo Pista2");
				CloseUser(conn);
			}
		}
		//Pista +3
		if (pMob[conn].TargetX > 3327 && pMob[conn].TargetY > 1020 && pMob[conn].TargetX < 3455 && pMob[conn].TargetY < 1150)
		{
			if (conn <= 0 && conn >= MAX_USER)
				continue;

			if (pUser[conn].Mode != USER_PLAY)
				continue;

			int partyleader = pMob[conn].Leader;

			if (partyleader <= 0)
				partyleader = conn;

			if (Pista[3].Party[0].LeaderID != partyleader && Pista[3].Party[1].LeaderID != partyleader && Pista[3].Party[2].LeaderID != partyleader) {
				SystemLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, "hack, Pulo Pista3");
				CloseUser(conn);
			}
		}
		//Pista +4
		if (pMob[conn].TargetX > 3325 && pMob[conn].TargetY > 1280 && pMob[conn].TargetX < 3460 && pMob[conn].TargetY < 1410)
		{
			if (conn <= 0 && conn >= MAX_USER)
				continue;

			if (pUser[conn].Mode != USER_PLAY)
				continue;

			int partyleader = pMob[conn].Leader;

			if (partyleader <= 0)
				partyleader = conn;

			if (Pista[4].Party[0].LeaderID != partyleader && Pista[4].Party[1].LeaderID != partyleader && Pista[4].Party[2].LeaderID != partyleader) {
				SystemLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, "hack, Pulo Pista4");
				CloseUser(conn);
			}
		}
		//Pista +5
		if (pMob[conn].TargetX > 3325 && pMob[conn].TargetY > 1150 && pMob[conn].TargetX < 3455 && pMob[conn].TargetY < 1280)
		{
			if (conn <= 0 && conn >= MAX_USER)
				continue;

			if (pUser[conn].Mode != USER_PLAY)
				continue;

			int partyleader = pMob[conn].Leader;

			if (partyleader <= 0)
				partyleader = conn;

			if (Pista[5].Party[0].LeaderID != partyleader && Pista[5].Party[1].LeaderID != partyleader && Pista[5].Party[2].LeaderID != partyleader) {
				SystemLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, "hack, Pulo Pista5");
				CloseUser(conn);
			}
		}
		//Pista +6
		if (pMob[conn].TargetX > 3325 && pMob[conn].TargetY > 1465 && pMob[conn].TargetX < 3455 && pMob[conn].TargetY < 1535)
		{
			if (conn <= 0 && conn >= MAX_USER)
				continue;

			if (pUser[conn].Mode != USER_PLAY)
				continue;

			int partyleader = pMob[conn].Leader;

			if (partyleader <= 0)
				partyleader = conn;

			if (Pista[6].Party[0].LeaderID != partyleader && Pista[6].Party[1].LeaderID != partyleader && Pista[6].Party[2].LeaderID != partyleader) {
				SystemLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, "hack, Pulo Pista6");
				CloseUser(conn);
			}
		}
#pragma endregion


#pragma region Ataque físico
		if (dam == -2)
		{
			int dis = BASE_GetDistance(m->PosX, m->PosY, m->TargetX, m->TargetY);
			// anti hacker 
			if (dis <= 0)
			{
				m->Dam[i].TargetID = 0;
				m->Dam[i].Damage = 0;
				pMob[conn].CurrentTarget = 0;



				continue;
			}

			if (dis > pUser[conn].Range || dis > 23)
			{
				m->Dam[i].TargetID = 0;
				m->Dam[i].Damage = 0;

				pMob[conn].CurrentTarget = 0;


				continue;
			}
			// fim	antihack

			dam = 0;

			if (i > 0 && m->Size < sizeof(MSG_AttackTwo) && pMob[conn].MOB.Class != 3 && (pMob[conn].MOB.LearnedSkill & 0x40) == 0)
			{
				//AddCrackError(conn, 10, 24);
				continue;
			}

			int CriticalDouble = 0;

			if (i == 0)
				CriticalDouble = BASE_GetDoubleCritical(&pMob[conn].MOB, &pUser[conn].cProgress, &m->Progress, &DoubleCritical);

			dam = pMob[conn].MOB.CurrentScore.Damage;

			if ((DoubleCritical & 2) != 0)
			{
				if (idx < MAX_USER)
					dam = (((rand() % 2) + 13) * dam) / 10;
				else
					dam = (((rand() % 2) + 15) * dam) / 10;
			}

			int Ac = pMob[idx].MOB.CurrentScore.Ac;

			if (idx < MAX_USER)
				Ac *= 3;

			dam = BASE_GetDamage((int)dam, Ac, master);

			//balanceamento de classe
			/*if (idx > 0 && idx < MAX_USER)
				dam = DamageBalancing(conn, idx, dam);*/

			//pve
			if (idx >= MAX_USER && idx < MAX_MOB)
			{
				if (pMob[conn].extra.ClassMaster == MORTAL)
					dam = static_cast<int>(dam * 0.7);

				if (pMob[conn].extra.ClassMaster == ARCH)
					dam = static_cast<int>(dam * 0.8);
			}

			if (i == 0 && m->Size >= sizeof(MSG_AttackTwo) && pMob[conn].MOB.Class == 3 && (pMob[conn].MOB.LearnedSkill & 0x200000) && (rand() % 4) == 0)
			{
				int skilldam = (pMob[conn].MOB.CurrentScore.Special[3] + pMob[conn].MOB.CurrentScore.Str);

				int acc = pMob[idx].MOB.CurrentScore.Ac;

				skilldam = BASE_GetDamage(skilldam, acc, master);

				if (skilldam > 0)
					skilldam /= 2;

				if (skilldam < 60)
					skilldam = 60;

				m->Dam[1].TargetID = MOB_EMPTY;
				m->Dam[1].Damage = skilldam;

				DoubleCritical |= 4;
				dam += skilldam;
			}

			if ((DoubleCritical & 1) != FALSE)
				dam *= 2;

			m->DoubleCritical = DoubleCritical;
		}


#pragma endregion

#pragma region Skills
		else if (dam == -1 && skillnum >= 0 && skillnum <= MAX_SKILLINDEX)
		{
			dam = 0;

			int maxtarget = g_pSpell[skillnum].MaxTarget;

			if (ClientTick != SKIPCHECKTICK && i > maxtarget)
			{

				continue;
			}

			if (g_pSpell[skillnum].bParty != 0 && leader != mobleader && Guild != MobGuild)
			{

				continue;
			}

			int unk2 = 0;
			int InstanceType = g_pSpell[skillnum].InstanceType;

#pragma region Ataques com elementos
			if (InstanceType >= 1 && InstanceType <= 5)
			{
				int Weather = CurrentWeather;
				int ApplyWeather = 0;

				if ((pMob[conn].TargetX / 128) < 12 && (pMob[conn].TargetY / 128) > 25)
					ApplyWeather = 1;

				else
					ApplyWeather = 0;

				if (ApplyWeather != 0)
					Weather = 0;

#pragma region Ataque de Fada
				if (ClientTick == SKIPCHECKTICK && m->Motion == 254 && (m->SkillIndex == 32 || m->SkillIndex == 34 || m->SkillIndex == 36))
				{
					int Level = pMob[conn].MOB.CurrentScore.Level;
					int familiarsanc = BASE_GetItemSanc(&pMob[conn].MOB.Equip[13]);

					switch (m->SkillIndex)
					{
					case 32:
						dam = (familiarsanc * 200) + (Level * 8);
						break;
					case 34:
						dam = (familiarsanc * 300) + (Level * 8);
						break;
					case 36:
						dam = (familiarsanc * 350) + (Level * 8);
						break;
					}

					if (dam > 1000)
						dam = 1000;
				}
#pragma endregion

				else
					dam = BASE_GetSkillDamage(skillnum, &pMob[conn].MOB, Weather, pMob[conn].WeaponDamage);

				int def = pMob[idx].MOB.CurrentScore.Ac;

				if (idx < MAX_USER)
					def *= 2;

				if (pMob[idx].MOB.Class == 1)
					def = (def * 3) / 2;

				dam = BASE_GetSkillDamage((int)dam, def, master);

				/*if (idx > 0 && idx < MAX_USER)
					dam = DamageBalancing(conn, idx, dam);*/


				if (idx >= MAX_USER && idx < MAX_MOB)
				{
					if (pMob[conn].extra.ClassMaster == MORTAL)
						dam = static_cast<int>(dam * 0.7);

					if (pMob[conn].extra.ClassMaster == ARCH)
						dam = static_cast<int>(dam * 0.8);
				}

				if (InstanceType == 1)
				{
					int MobResist = pMob[idx].MOB.Resist[0];

					if (idx > MAX_USER)
						MobResist = MobResist / 2;

					dam = ((150 - MobResist) * dam) / 100;
				}
				else if (InstanceType >= 2 && InstanceType <= 5)
				{
					int skind = InstanceType - 2;

					int MobResist = pMob[idx].MOB.Resist[skind];

					if (idx >= MAX_USER)
						MobResist = MobResist / 2;

					dam = ((150 - MobResist) * dam) / 100;
				}
			}

			//if ((pMob[conn].MOB.Equip[0].sIndex == 11 || pMob[conn].MOB.Equip[0].sIndex == 16 || pMob[conn].MOB.Equip[0].sIndex == 17 || pMob[conn].MOB.Equip[0].sIndex == 18 || pMob[conn].MOB.Equip[0].sIndex == 19) && pMob[conn].MOB.LearnedSkill & 15)// colocar todos os index de class FM, são 4 verificar se 15 é a oitava de fm
			//	dam -= (dam * 0) / 100;// Aqui estamos diminuindo 40% do seu dano das skills, caso queira mudar, é só mudar o valor ali de 40 pra outro valor

			//Tempestade de flechas
			if (skillnum == 79)
			{
				if (idx < MAX_USER)
					dam = GetSkillDamage_PvP(skillnum, &pMob[conn].MOB, CurrentWeather, pMob[conn].WeaponDamage);

				else
					dam = BASE_GetSkillDamage(skillnum, &pMob[conn].MOB, CurrentWeather, pMob[conn].WeaponDamage);

				int Ac = pMob[idx].MOB.CurrentScore.Ac;

				if (idx < MAX_USER)
					Ac *= 2;

				dam = BASE_GetDamage((int)dam, Ac, master);

			}
			if (skillnum == 86) //Explosão Etéria
			{
				dam += pMob[conn].MOB.CurrentScore.Str;
				dam += pMob[conn].MOB.CurrentScore.Dex;
			}
#pragma endregion
#pragma region Cura / Recuperação
			else if (InstanceType == 6)
			{
				if (pMob[idx].MOB.Clan == 4)
					continue;

				unsigned char getAttribute = GetAttribute(pMob[idx].TargetX, pMob[idx].TargetY) & 0x40;

				if (map_att == 0 && getAttribute)
				{
					m->Dam[i].TargetID = MOB_EMPTY;
					m->Dam[i].Damage = 0;

					continue;
				}


				if (skillnum == 27)
					dam = (Special * 2) + g_pSpell[skillnum].InstanceValue;
				else
					dam = ((Special * 3) / 2) + g_pSpell[skillnum].InstanceValue;

				if (pMob[conn].extra.ClassMaster == MORTAL)
					dam *= 1.4;

				if (pMob[conn].extra.ClassMaster == ARCH)
					dam *= 2.4;

				if (pMob[conn].extra.ClassMaster >= CELESTIAL)
					dam *= 3.4;

				if (pMob[conn].extra.ClassMaster == MORTAL) {
					if (dam > 548)
						dam = 548;
				}

				if (pMob[conn].extra.ClassMaster == ARCH) {
					if (dam > 748)
						dam = 748;
				}

				if (pMob[conn].extra.ClassMaster >= CELESTIAL) {
					if (dam > 1048)
						dam = 1048;
				}

				if (pMob[conn].extra.ClassMaster >= MORTAL)
				{
					if (dam >= 80000)
						dam = 80000;
				}
				else
				{
					if (dam >= 80000)
						dam = 80000;
				}
				dam = -dam;

				if (dam < 0 && dam > -6)
					dam = -6;

				auto multHpMob = pMob[idx].MOB.Equip[13].sIndex;
				auto _tDamage = dam;
				if (multHpMob == 786 || multHpMob == 1936 || multHpMob == 1937)
				{
					int HpItem = GetItemSancNew(&pMob[idx].MOB.Equip[13]);
					if (HpItem < 2)
						HpItem = 2;
					int multHp = 1;
					switch (multHpMob)
					{
					case 1936:
						multHp = 10;
						break;
					case 1937:
						multHp = 1000;
						break;
					default:
						break;
					}
					multHp *= HpItem;

					_tDamage /= multHp;

				}

				if (_tDamage > pMob[idx].MOB.CurrentScore.Hp)
					pMob[idx].MOB.CurrentScore.Hp = 0;
				else
					pMob[idx].MOB.CurrentScore.Hp -= _tDamage;

				int MobHP = pMob[idx].MOB.CurrentScore.Hp;

				if (pMob[idx].MOB.CurrentScore.Hp > pMob[idx].MOB.CurrentScore.MaxHp)
					pMob[idx].MOB.CurrentScore.Hp = pMob[idx].MOB.CurrentScore.MaxHp;

				if (idx > 0 && idx < MAX_USER)
					SetReqHp(idx);

				//int MobHP = pMob[idx].MOB.CurrentScore.Hp;

				//if (pMob[idx].MOB.Equip[13].sIndex == 786)
				//{
				//	int sanc = pMob[idx].MOB.Equip[13].stEffect[0].cValue;
				//	if (sanc < 2)
				//		sanc = 2;

				//	pMob[idx].MOB.CurrentScore.Hp = pMob[idx].MOB.CurrentScore.Hp - ((int)dam / sanc);

				//}
				//else  if (pMob[idx].MOB.Equip[13].sIndex == 1936)
				//{
				//	int sanc = pMob[idx].MOB.Equip[13].stEffect[0].cValue;
				//	if (sanc < 2)
				//		sanc = 2;

				//	sanc *= 10;

				//	pMob[idx].MOB.CurrentScore.Hp = pMob[idx].MOB.CurrentScore.Hp - ((int)dam / (sanc * 10));

				//}

				//else  if (pMob[idx].MOB.Equip[13].sIndex == 1937)
				//{
				//	int sanc = pMob[idx].MOB.Equip[13].stEffect[0].cValue;
				//	if (sanc < 2)
				//		sanc = 2;

				//	sanc *= 1000;

				//	pMob[idx].MOB.CurrentScore.Hp = pMob[idx].MOB.CurrentScore.Hp - ((int)dam / (sanc * 20));

				//}

				//else
				//	pMob[idx].MOB.CurrentScore.Hp = pMob[idx].MOB.CurrentScore.Hp - (int)dam;


				//if (pMob[idx].MOB.CurrentScore.Hp > pMob[idx].MOB.CurrentScore.MaxHp)
				//	pMob[idx].MOB.CurrentScore.Hp = pMob[idx].MOB.CurrentScore.MaxHp;

				//if (idx > 0 && idx < MAX_USER)
				//	SetReqHp(idx);


				int calc_exp = (pMob[idx].MOB.CurrentScore.Hp - MobHP) >> 3;

				if (calc_exp > 120)
					calc_exp = 120;

				if (calc_exp < 0)
					calc_exp = 0;


				if (calc_exp > 0 && conn != idx && conn > 0 && conn < MAX_USER)
				{
					int village = BASE_GetVillage(pMob[idx].TargetX, pMob[idx].TargetY);

					if (village < 0 || village >= 5)
					{
						if (UNK2 < calc_exp)
							UNK2 = calc_exp;
					}
				}
			}
#pragma endregion
#pragma region Flash
			else if (InstanceType == 7)
			{
				pMob[idx].Mode = MOB_PEACE;
				pMob[idx].CurrentTarget = MOB_EMPTY;

				for (int j = 0; j < MAX_ENEMY; j++)
					pMob[idx].EnemyList[j] = MOB_EMPTY;
			}
#pragma endregion
#pragma region Desintoxicar
			else if (InstanceType == 8)
			{
				int NeedUpdate = 0;

				for (int k = 0; k < MAX_AFFECT; k++)
				{
					int Type = pMob[idx].Affect[k].Type;

					if (Type == 1 || Type == 3 || Type == 5 || Type == 7 || Type == 10 || Type == 12 || Type == 20 || (Type == 32 && (1 << 7) & pMob[conn].MOB.LearnedSkill))
					{
						pMob[idx].Affect[k].Type = 0;
						NeedUpdate = 1;
					}
				}

				if (NeedUpdate)
				{
					pMob[idx].GetCurrentScore(idx);
					SendScore(idx);
				}
			}
#pragma endregion
#pragma region Teleporte
			else if (InstanceType == 9)
			{
				if (pMob[idx].MOB.CurrentScore.Hp <= 0)
				{
					SendClientMessage(conn, g_pMessageStringTable[_NN_Cant_Summon_Dead_Person]);
					break;
				}

				unsigned char getAtt = GetAttribute(pMob[conn].TargetX, pMob[conn].TargetY);

				if (getAtt & 0x4 && pMob[conn].MOB.CurrentScore.Level < 1000)
				{
					SendClientMessage(conn, g_pMessageStringTable[_NN_Summon_Not_Allowed_Here]);
					continue;
				}

				if (pMob[idx].MOB.CurrentScore.Hp > pMob[conn].MOB.CurrentScore.Hp + Special + 30)
				{
					SendClientMessage(conn, g_pMessageStringTable[_NN_Too_High_Level_To_Summon]);
					continue;
				}

				unsigned char map_att = GetAttribute(pMob[conn].TargetX, pMob[conn].TargetY);

				if (map_att & 4)
				{
					SendClientMessage(conn, g_pMessageStringTable[_NN_Cant_Use_That_Here]);
					return;
				}

				if (idx < MAX_USER && pUser[idx].Mode == USER_PLAY)
				{
					DoSummon(idx, pMob[conn].TargetX, pMob[conn].TargetY);
					SendClientMessage(idx, strFmt("!Sumonado por [%s]", pMob[conn].MOB.MobName));
					return;
				}
			}
#pragma endregion

#pragma region Invisibilidade
			else if (InstanceType == 10 && idx < MAX_USER)
			{
				for (int l = MAX_USER; l < MAX_MOB; l++)
				{
					if (pMob[l].Mode == MOB_COMBAT && pMob[l].CurrentTarget == idx)
					{
						for (int m = 0; m < MAX_ENEMY; m++)
						{
							if (pMob[l].EnemyList[m] == idx)
								pMob[l].EnemyList[m] = conn;
						}

						pMob[l].CurrentTarget = conn;
					}
				}
			}
#pragma endregion
#pragma region Evock
			else if (InstanceType == 11)
			{
				int instancevalue = g_pSpell[skillnum].InstanceValue;
				if (instancevalue >= 1 && instancevalue <= 50)
				{
					int summons = 0;

					if (instancevalue == 1 || instancevalue == 2)
						summons = pMob[conn].MOB.CurrentScore.Special[2] / 30;

					else if (instancevalue == 3 || instancevalue == 4 || instancevalue == 5)
						summons = pMob[conn].MOB.CurrentScore.Special[2] / 40;

					else if (instancevalue == 6 || instancevalue == 7)
						summons = pMob[conn].MOB.CurrentScore.Special[2] / 80;

					else if (instancevalue == 8)
						summons = 1;

					if (GenerateSummon(conn, instancevalue - 1, 0, summons) == 0)
					{
						pMob[conn].MOB.CurrentScore.Mp = Mp;
						pUser[conn].ReqMp = ReqMp;
					}
				}
				dam = 0;
			}
#pragma endregion
#pragma region Chamas Etéreas
			else if (InstanceType == 12)
			{
				int Leader = pMob[conn].Leader, slot = 0, targetlevel = pMob[idx].MOB.CurrentScore.Level, level = pMob[conn].MOB.CurrentScore.Level, chance, _rand;

				if (Leader <= 0)
					Leader = conn;

				// Personagem
				if (idx < MAX_USER)
				{
					int chance = (pMob[conn].MOB.BaseScore.Special[1] + 1) / 7;
					int Rand = rand() % 100;

					if (Rand > chance)
					{
						int burnmp = ((pMob[idx].MOB.CurrentScore.Mp + 1) / 100) * (10 + rand() % 90);

						if (burnmp > pMob[idx].MOB.CurrentScore.Mp)
							pMob[idx].MOB.CurrentScore.Mp = 0;

						else
							pMob[idx].MOB.CurrentScore.Mp -= burnmp;

						SendSetHpMp(idx);
						SendScore(idx);
						continue;
					}

					for (int k = 0; k < MAX_AFFECT; k++)
					{
						int Type = pMob[idx].Affect[k].Type;

						if (Type == 18 || Type == 16 || Type == 14 || Type == 19 || Type == 32)
						{
							pMob[idx].Affect[k].Type = 0;
							pMob[idx].Affect[k].Value = 0;
							pMob[idx].Affect[k].Level = 0;
							pMob[idx].Affect[k].Time = 0;

							pMob[idx].GetCurrentScore(idx);
							SendScore(idx);
						}
					}

					SendEquip(idx, 0);
					pMob[idx].GetCurrentScore(idx);
					SendScore(idx);

					continue;
				}
			}

#pragma endregion
#pragma region Furia divina
			if (skillnum == 6)
			{
				if (idx >= MAX_USER && pMob[idx].MOB.Merchant != 0)
					break;

				if (pMob[idx].MOB.Equip[0].sIndex == 219 || pMob[idx].MOB.Equip[0].sIndex == 220 || pMob[idx].MOB.Equip[0].sIndex == 362)
					break;

				if (pMob[idx].GenerateIndex == 8 || pMob[idx].GenerateIndex == 9)
					break;

				if (pMob[idx].MOB.Clan == 6)
					break;

				pMob[idx].Route[0] = 0;

				int PosX = pMob[conn].TargetX;

				if (PosX < pMob[idx].TargetX)
					PosX++;

				if (PosX > pMob[idx].TargetX)
					PosX--;

				int PosY = pMob[conn].TargetY;

				if (PosY < pMob[idx].TargetY)
					PosY++;

				if (PosY > pMob[idx].TargetY)
					PosY--;

				if (GetEmptyMobGrid(idx, &PosX, &PosY) == FALSE)
					break;

				int kind2 = pMob[conn].MOB.CurrentScore.Special[1];

				int kindvalue = (kind2 / 10) + 20;

				if (idx > MAX_USER)
					kindvalue = (kind2 / 5) + 40;

				int leveldif = pMob[conn].extra.ClassMaster != MORTAL && pMob[conn].extra.ClassMaster != ARCH ? pMob[conn].MOB.CurrentScore.Level : pMob[conn].MOB.CurrentScore.Level + MAX_LEVEL - (pMob[idx].extra.ClassMaster != MORTAL && pMob[idx].extra.ClassMaster != ARCH ? pMob[idx].MOB.CurrentScore.Level + MAX_LEVEL : pMob[idx].MOB.CurrentScore.Level);

				leveldif = leveldif >> 2;

				int _chance = kindvalue + leveldif;

				if (_chance > 50)
					_chance = 50;

				if (rand() % 100 >= _chance)
					break;

				MSG_Action sm_act;
				memset(&sm_act, 0, sizeof(MSG_Action));

				GetAction(idx, PosX, PosY, &sm_act);

				sm_act.Effect = 2;
				sm_act.Speed = 6;

				GridMulticast(idx, PosX, PosY, (MSG_STANDARD*)&sm_act);

				if (idx < MAX_USER)
				{
					memset(&sm_act, 0, sizeof(MSG_Action));
					GetAction(idx, PosX, PosY, &sm_act);

					sm_act.Effect = 2;
					sm_act.Speed = 6;

					if (!pUser[idx].cSock.AddMessage((char*)&sm_act, sizeof(MSG_Action)))
						CloseUser(conn);
				}

				if (idx >= MAX_USER)
					SetBattle(idx, conn);

				break;
			}
#pragma endregion


#pragma region Exterminar
			else if (skillnum == 22)
			{
				int CurrentMp = pMob[conn].MOB.CurrentScore.Mp;

				pMob[conn].MOB.CurrentScore.Mp = 0;

				m->CurrentMp = 0;

				int kind4 = pMob[conn].MOB.CurrentScore.Special[3];

				int _INT = pMob[conn].MOB.CurrentScore.Int;
				dam = (dam + _INT);//+ (_INT / 3);

				int PosX = pMob[idx].TargetX;
				int PosY = pMob[idx].TargetY;

				if (GetEmptyMobGrid(conn, &PosX, &PosY) != 0 && pMob[idx].MOB.Equip[0].sIndex != 219 && pMob[idx].MOB.Equip[0].sIndex != 220)
				{
					MSG_Action sm_act;
					memset(&sm_act, 0, sizeof(MSG_Action));

					GetAction(conn, PosX, PosY, &sm_act);

					sm_act.Type = 2;
					sm_act.Speed = 2;

					GridMulticast(conn, PosX, PosY, (MSG_STANDARD*)&sm_act);

					if (!pUser[conn].cSock.AddMessage((char*)&sm_act, sizeof(MSG_Action)))
						CloseUser(conn);
				}
			}
#pragma endregion

#pragma region Julgamento divino
			else if (skillnum == 30)
			{
				dam = dam + hp;

				pMob[conn].MOB.CurrentScore.Hp = ((pMob[conn].MOB.CurrentScore.Hp) / 6) + 1;
				pUser[conn].ReqHp = pMob[conn].MOB.CurrentScore.Hp;
			}
#pragma endregion
#pragma region Renascimento 
			else if (skillnum == 31)
			{
				bool isParty = false;

				if (idx > 0 && idx < MAX_USER)
				{
					int saveLeader = pMob[idx].Leader;
					if (saveLeader == 0)
						saveLeader = idx;
					if (saveLeader > 0 && saveLeader < MAX_USER && pUser[saveLeader].Mode == USER_PLAY)
					{
						bool member1 = false;
						bool member2 = false;
						for (int i = 0; i < MAX_PARTY; i++)
						{
							if (conn <= 0 || conn >= MAX_USER)
								continue;

							if (pUser[conn].Mode != USER_PLAY)
								continue;

							if (conn == pMob[saveLeader].PartyList[i])
							{
								member1 = true;
								continue;
							}
							if (conn == saveLeader)
							{
								member1 = true;
							}
							if (idx == pMob[saveLeader].PartyList[i])
							{
								member2 = true;
							}
							if (idx == saveLeader)
							{
								member2 = true;
							}

							if (member1 && member2)
							{
								isParty = true;
								break;
							}
						}
					}

				}


				if (pMob[idx].MOB.Guild == pMob[conn].MOB.Guild && pMob[conn].MOB.Guild != 0 || isParty == true)
				{
					int hp = (rand() % 10 + 90) * ((pMob[conn].MOB.CurrentScore.MaxHp + 1) / 100);

					unsigned char getAtt = GetAttribute(pMob[conn].TargetX, pMob[conn].TargetY);

					pMob[conn].MOB.CurrentScore.Mp = 0;

					m->CurrentMp = 0;

					SendSetHpMp(conn);

					if ((rand() % 100) < 50)
					{
						pMob[idx].MOB.CurrentScore.Hp = pMob[idx].MOB.CurrentScore.MaxHp;
						pMob[idx].GetCurrentScore(idx);
						SendScore(idx);

						pMob[idx].MOB.CurrentScore.Mp = pMob[idx].MOB.CurrentScore.MaxMp;
						pMob[idx].GetCurrentScore(idx);
						SendScore(idx);
						pUser[idx].NumError = 0;
						SendScore(idx);
						SendSetHpMp(idx);
						SendEtc(idx);

						MSG_CreateMob CreateMob;
						GetCreateMob(idx, &CreateMob);
						GridMulticast(pMob[idx].TargetX, pMob[idx].TargetY, (MSG_STANDARD*)&CreateMob, 0);
					}
				}
			}
#pragma endregion
			//#pragma region Renascimento 
			//			else if (skillnum == 31)
			//			{
			//				if (pMob[idx].Leader == NULL && pMob[idx].MOB.Guild != pMob[conn].MOB.Guild)
			//				{
			//					SendClientMessage(conn, "Você não pode usar essa skill em membros que não forem da sua guild ou estejam em Grupo.");
			//					return;
			//				}
			//
			//				int hp = (rand() % 10 + 90) * ((pMob[conn].MOB.CurrentScore.MaxHp + 1) / 100);
			//
			//				unsigned char getAtt = GetAttribute(pMob[conn].TargetX, pMob[conn].TargetY);
			//
			//				pMob[conn].MOB.CurrentScore.Mp = 0;
			//				pUser[conn].ReqMp = 0;
			//
			//				m->CurrentMp = 0;
			//
			//				SendSetHpMp(conn);
			//				if ((rand() % 100) < 90)
			//				{
			//					pMob[idx].MOB.CurrentScore.Hp = pMob[idx].MOB.CurrentScore.MaxHp;
			//					pMob[idx].GetCurrentScore(idx);
			//					SendScore(idx);
			//
			//					pMob[idx].MOB.CurrentScore.Mp = pMob[idx].MOB.CurrentScore.MaxMp;
			//					pMob[idx].GetCurrentScore(idx);
			//					SendScore(idx);
			//					pUser[idx].NumError = 0;
			//					SendScore(idx);
			//					SendSetHpMp(idx);
			//					SendEtc(idx);
			//
			//					MSG_CreateMob CreateMob;
			//					GetCreateMob(idx, &CreateMob);
			//					GridMulticast(pMob[idx].TargetX, pMob[idx].TargetY, (MSG_STANDARD*)&CreateMob, 0);
			//				}
			//			}
			//#pragma endregion
#pragma region Velocidade
			else if (skillnum == 41)
			{
				int skill_target = (Special / 25) + 2;

				if (skill_target >= MAX_TARGET)
					skill_target = MAX_TARGET;

				if (skill_target <= 1)
					skill_target = 2;

				for (int q = 0; q < skill_target && ((q < MAX_TARGET && m->Size >= sizeof(MSG_Attack)) || (q < 1 && m->Size >= sizeof(MSG_AttackOne)) || (q < 2 && m->Size >= sizeof(MSG_AttackTwo))); q++)
				{
					int targetidx = m->Dam[q].TargetID;

					if (targetidx <= MOB_EMPTY || targetidx >= MAX_USER)
						continue;

					if (pUser[targetidx].Mode != USER_PLAY)
						continue;

					if (SetAffect(targetidx, skillnum, Delay, Level) == 0)
						continue;

					SendScore(targetidx);
				}

				break;
			}
#pragma endregion
#pragma region Arma Magica
			else if (skillnum == 44)
			{
				int skill_target = (Special / 25) + 2;

				if (skill_target >= MAX_TARGET)
					skill_target = MAX_TARGET;

				if (skill_target <= 1)
					skill_target = 2;

				for (int q = 0; q < skill_target && ((q < MAX_TARGET && m->Size >= sizeof(MSG_Attack)) || (q < 1 && m->Size >= sizeof(MSG_AttackOne)) || (q < 2 && m->Size >= sizeof(MSG_AttackTwo))); q++)
				{
					int targetidx = m->Dam[q].TargetID;
					if (targetidx <= MOB_EMPTY || targetidx >= MAX_USER)
						continue;

					if (pUser[targetidx].Mode != USER_PLAY)
						continue;

					if (SetAffect(targetidx, skillnum, Delay, Level) == 0)
						continue;

					SendScore(targetidx);
				}

				break;
			}
#pragma endregion
#pragma region Cancelamento
			else if (skillnum == 47)
			{
				int CancelContinue = 0;

				for (int k = 0; k < MAX_AFFECT; k++)
				{
					int Type = pMob[idx].Affect[k].Type;

					if (Type == 19)
					{
						pMob[idx].Affect[k].Type = 0;
						pMob[idx].Affect[k].Value = 0;
						pMob[idx].Affect[k].Level = 0;
						pMob[idx].Affect[k].Time = 0;
						pMob[idx].GetCurrentScore(idx);
						SendScore(idx);
						CancelContinue = 1;
						break;
					}
				}

				if (CancelContinue == 1)
					break;
			}
#pragma region Book Vinha
			else if (skillnum == 98)
			{
				if (m->TargetX < 0 || m->TargetX >= MAX_GRIDX || m->TargetY < 0 || m->TargetY >= MAX_GRIDY)
					break;

				unsigned char getAttribute = GetAttribute(m->TargetX, m->TargetY);
				getAttribute = getAttribute & 0x40;

				if (map_att == 0 && getAttribute == 1)
					continue;

				CreateMob("Vinha", m->TargetX, m->TargetY, "BaseSummon", 3);
				break;
			}

#pragma endregion

			int Aggressive = g_pSpell[skillnum].Aggressive;

			int SameLeaderGuild = 1;

			if (Aggressive != 0)
			{
				if (leader == mobleader || Guild == MobGuild)
					SameLeaderGuild = 0;

				int affectresist = g_pSpell[skillnum].AffectResist;

				int idxlevel = pMob[idx].extra.ClassMaster == MORTAL || pMob[idx].extra.ClassMaster == ARCH || pMob[idx].extra.ClassMaster == CELESTIAL || pMob[idx].extra.ClassMaster == CELESTIALCS || pMob[idx].extra.ClassMaster == SCELESTIAL ? pMob[idx].MOB.CurrentScore.Level : pMob[idx].MOB.CurrentScore.Level + MAX_LEVEL;//ByLords2
				int connlevel = pMob[conn].extra.ClassMaster == MORTAL || pMob[idx].extra.ClassMaster == ARCH || pMob[idx].extra.ClassMaster == CELESTIAL || pMob[idx].extra.ClassMaster == CELESTIALCS || pMob[idx].extra.ClassMaster == SCELESTIAL ? pMob[conn].MOB.CurrentScore.Level : pMob[conn].MOB.CurrentScore.Level + MAX_LEVEL;//ByLords2
				int difLevel = (idxlevel - connlevel) / 2;

				difLevel = -difLevel;

				if (affectresist >= 1 && affectresist <= 4)
				{
					int random = rand() % 100;

					if (random > pMob[idx].MOB.RegenMP + affectresist + difLevel)
						SameLeaderGuild = 0;
				}

				if ((pMob[idx].MOB.Rsv & 0x80) != FALSE)
					SameLeaderGuild = 0;

				if (conn < MAX_USER && pMob[idx].MOB.Clan == 6)
					SameLeaderGuild = 0;
			}

#pragma region Buff
			if (SameLeaderGuild)
			{
				if (skillnum == 102)
				{
					if (pMob[conn].extra.ClassMaster == MORTAL)
						Delay = 200;

					else if (pMob[conn].extra.ClassMaster != MORTAL && pMob[conn].extra.ClassMaster != ARCH)
					{
						Delay = 200;

						if (pMob[conn].MOB.CurrentScore.Level < 39)
							Delay -= (39 - (pMob[conn].MOB.CurrentScore.Level)) * 4;

						else if (pMob[conn].MOB.CurrentScore.Level >= 199)
							Delay = 400;

						else
							Delay = 200;
					}
				}

				if (SetAffect(idx, skillnum, Delay, Special) != 0)
					UNK2 = TRUE;

				if (SetTick(idx, skillnum, Delay, Special) != 0)
					UNK2 = TRUE;

				if (UNK2 != FALSE)
				{
					pMob[idx].GetCurrentScore(idx);
					SendScore(idx);
				}
			}
#pragma endregion

#pragma region Transformação
			if (skillnum == 64 || skillnum == 66 || skillnum == 68 || skillnum == 70 || skillnum == 71)
			{
				pMob[conn].GetCurrentScore(conn);
				SendScore(conn);
				SendEquip(conn, 0);
			}
#pragma endregion

#pragma region Book Ressureição
			if (pMob[conn].MOB.CurrentScore.Hp == 0 && skillnum == 99)
			{
				int rev = rand() % 115;

				if (rev > 100)
					rev -= 15;

				if (rev >= 80)
				{
					pMob[conn].MOB.CurrentScore.Hp = 2;
					pUser[conn].NumError = 0;
					SendScore(conn);
					SendSetHpMp(conn);
					DoRecall(conn);
					SendEtc(conn);
				}

				int hp = (rand() % 50 + 1) * ((pMob[conn].MOB.CurrentScore.MaxHp + 1) / 100);

				pMob[conn].MOB.CurrentScore.Hp = pMob[conn].MOB.CurrentScore.MaxHp;
				pUser[conn].NumError = 0;
				SendScore(conn);
				SendSetHpMp(conn);
				SendEtc(conn);

				MSG_CreateMob CreateMob;
				GetCreateMob(conn, &CreateMob);
				GridMulticast(pMob[conn].TargetX, pMob[conn].TargetY, (MSG_STANDARD*)&CreateMob, 0);
			}
#pragma endregion

		}
#pragma endregion
		else
		{
			//Log("err,dam not -2 -1 MSG_ATTACK", pUser[conn].AccountName, pUser[conn].IP);
			return;
		}

		m->Dam[i].Damage = dam;

		if (dam <= 0)
			continue;

#pragma region Perfuracao		   
		if (idx < MAX_USER || pMob[idx].MOB.Clan == 4)
		{
			if ((m->DoubleCritical & 4) != 0)
				dam = m->Dam[1].Damage + (dam >> 2);

			else
				dam = dam >> 2;
		}

		if (pMob[conn].ForceDamage != 0)
		{
			if (dam <= 1)
				dam = pMob[conn].ForceDamage;

			else if (dam > 0)
				dam = dam + pMob[conn].ForceDamage;

			m->Dam[i].Damage = dam;
		}
#pragma endregion

#pragma region Ataque PvP
		if (pMob[conn].PvPDamage != 0 && idx < MAX_USER)
		{
			if (dam < 1)
				dam += dam * pMob[conn].PvPDamage / 100;

			else if (dam > 0)
				dam += dam / 100 * pMob[conn].PvPDamage;

			m->Dam[i].Damage = dam / 2;
		}
#pragma endregion

		if (leader == mobleader || Guild == MobGuild)
			dam = 0;

		if (idx >= MAX_USER && isFrag != FALSE)
			dam = 0;

		int Summoner = idx;

		if (idx >= MAX_USER && pMob[idx].MOB.Clan == 4 && pMob[idx].Summoner > 0 && pMob[idx].Summoner < MAX_USER && pUser[pMob[idx].Summoner].Mode == USER_PLAY)
			Summoner = pMob[idx].Summoner;

#pragma region PK - War - Miss

		if (Summoner < MAX_USER)
		{
			int pointPK = GetPKPoint(conn);
			int SummonerPointPK = GetPKPoint(Summoner);

			int arena = BASE_GetArena(pMob[conn].TargetX, pMob[conn].TargetY);
			int village = BASE_GetVillage(pMob[conn].TargetX, pMob[conn].TargetY);

			int mapX = pMob[conn].TargetX >> 7;
			int mapY = pMob[conn].TargetY >> 7;

			int MapPK = 0;
			int isWar = 0;

			int connGuild = pMob[conn].MOB.Guild;
			int SummonerGuild = pMob[Summoner].MOB.Guild;
			int maxguild = 65536;

			if (connGuild > 0 && connGuild < maxguild && SummonerGuild > 0 && SummonerGuild < maxguild && g_pGuildWar[connGuild] == SummonerGuild && g_pGuildWar[SummonerGuild] == connGuild)
				isWar = 1;

			if (CastleState != 0 && mapX == 8 && mapY == 13)
				isWar = 1;

			if (mapX == 1 && mapY == 31)
				MapPK = 1;

			// PK
			if (arena == MAX_GUILDZONE && village == MAX_GUILDZONE && MapPK == FALSE && isWar == FALSE)
			{
				if (pointPK <= 10 && SummonerPointPK > 10)
				{
					SendClientMessage(conn, strFmt(g_pMessageStringTable[_DN_CantKillUser], pointPK));
					dam = 0;
				}
				else if (SummonerPointPK > 10 && dam > 0 || skillnum == 6)
				{
					int Guilty = GetGuilty(conn);
					SetGuilty(conn, 8);

					if (Guilty == 0)
					{
						MSG_CreateMob mob;
						GetCreateMob(conn, &mob);
						GridMulticast(pMob[conn].TargetX, pMob[conn].TargetY, (MSG_STANDARD*)&mob, 0);
					}

					if (skillnum == 6)
						break;
				}
			}

			// Miss
			if (idx != conn)
			{
				int attackdex = pMob[conn].MOB.CurrentScore.Dex / 5;

				if (pMob[conn].MOB.LearnedSkill & 0x1000000)
					attackdex += 100;

				if (pMob[conn].MOB.Rsv & 0x40)
					attackdex += 500;

				int parryretn = GetParryRate(&pMob[conn].MOB, pMob[conn].MOB.CurrentScore.Dex, pMob[conn].MOB.Rsv, pMob[conn].Parry, pMob[idx].MOB.CurrentScore.Dex, pMob[idx].MOB.Rsv, pMob[idx].Parry);

				if (pMob[conn].extra.SecLearnedSkill & 0x100) // Espelho Mágico
				{
					int Special = (pMob[conn].MOB.CurrentScore.Special[3] / 2);

					parryretn -= Special;
				}

				if (skillnum == 79 || skillnum == 22)
					parryretn = 30 * parryretn / 100;

				int rd = rand() % 1000 + 1;

				if (rd < parryretn)
				{
					dam = -3;

					if ((pMob[idx].MOB.Rsv & 0x200) != 0 && rd < 100)
						dam = -4;
				}

				if (dam == -4 || dam == -3)  // Verifica se o DAM é -4 ou -3;
					pMob[idx].MissPlayer = TRUE; // Define na variavel MissPlayer quando o idx ataca ele é o conn, definindo o conn eu como idx;

				if (pMob[conn].MissPlayer == TRUE && dam > 0) // Verifica se o dano da variavel MissPlayer é -4 ou -3 e compara 
				{
					if (pMob[conn].MOB.Class == 3 && (pMob[conn].extra.SecLearnedSkill & 0x1)) //Verifica a Classe juntamente a Nona;
					{
						dam *= 1.5;
						pMob[conn].MissPlayer = FALSE;
					}
				}
			}
		}
#pragma endregion

		if (mylevel <= MAX_LEVEL)
		{
			if (idx < MAX_USER)
			{
				unsigned char TargetMapAttribute = GetAttribute(pMob[idx].TargetX, pMob[idx].TargetY);
				unsigned char MapAttribute = GetAttribute(pMob[conn].TargetX, pMob[conn].TargetY);

				if (TargetMapAttribute & 0x1 || (TargetMapAttribute & 64) == 0)
					dam = 0;

				if (MapAttribute & 0x1 || (MapAttribute & 64) == 0)
					dam = 0;
			}
		}

		if (pMob[idx].MOB.Class == 0) // Proteção Divina
		{
			for (int i = 0; i < MAX_AFFECT; i++)
			{
				if (pMob[idx].Affect[i].Type == 6 && dam > 0)
					dam = 0;
			}
		}

		if (pMob[idx].MOB.Class == 1) // Proteção Absoluta
		{
			for (int i = 0; i < MAX_AFFECT; i++)
			{
				if (pMob[idx].Affect[i].Type == 6 && dam > 0)
					dam = 0;
			}
		}

		if (pMob[idx].MOB.Clan == 6 && Level < MAX_LEVEL)
			dam = 0;

		if (idx > MAX_USER && dam > 1)
			dam += pMob[conn].ForceMobDamage;

		if (dam > MAX_DAMAGE)
			dam = MAX_DAMAGE;

		///if (dam > MAX_DAMAGE_MG)
		//dam = MAX_DAMAGE_MG

		m->Dam[i].Damage = dam;

		if (dam < 0)
			continue;

		//GELO
		if ((pMob[conn].MOB.Rsv & RSV_FROST) != 0)
		{
			bool Tempestade = false;
			if (skillnum == 79)
				Tempestade = true;

			if (rand() % 2 == 0 && Tempestade == false)
			{
				int skind2 = pMob[conn].MOB.CurrentScore.Special[1];

				if (SetAffect(idx, 36, skind2 + 150, skind2) != 0)
					SendScore(idx);

				if (SetTick(idx, 36, skind2 + 150, skind2) != 0)
					SendScore(idx);
			}
		}

		if ((pMob[conn].MOB.Rsv & RSV_DRAIN) != 0)
		{
			if (rand() % 2 == 0)
			{
				int skind2 = pMob[conn].MOB.CurrentScore.Special[1];

				if (SetAffect(idx, 40, skind2 + 150, skind2) != 0)
					SendScore(idx);

				if (SetTick(idx, 40, skind2 + 150, skind2) != 0)
					SendScore(idx);
			}
		}

		if (idx > 0 && idx < MAX_USER && dam > 0)
		{
			if (pMob[idx].ReflectDamage > 0)// Absorcao
				dam = dam - pMob[idx].ReflectDamage;

			if (dam <= 0)
				dam = 1;


			if (pMob[idx].ReflectPvP > 0)
				dam = dam - (dam / 100 * pMob[idx].ReflectPvP);

			if (dam < 0)
				dam = 1;

			m->Dam[i].Damage = dam;
		}

		if (pMob[conn].TargetX >= 1017 && pMob[conn].TargetX <= 1290 && pMob[conn].TargetY >= 1911 && pMob[conn].TargetY <= 2183 && dam > 0 && pMob[conn].MOB.Clan == pMob[idx].MOB.Clan)
		{
			m->Dam[i].Damage = 0;
			m->Dam[i].TargetID = 0;

			continue;
		}

		int _pDamage = dam;
		int _calcDamage = 0;
		int pTargetMountId = pMob[idx].MOB.Equip[14].sIndex;

		if (idx < MAX_USER && pTargetMountId >= 2360 && pTargetMountId < 2390 && pMob[idx].MOB.Equip[14].stEffect[0].sValue > 0)
		{

			_pDamage = (dam * 3) >> 2;
			_calcDamage = dam - _pDamage;
			if (_pDamage <= 0)
				_pDamage = 1;

			m->Dam[i].Damage = _pDamage;
		}

		int tDamage = _pDamage;


#pragma region Controle de Mana
		if (pMob[idx].MOB.Class == 1) {
			for (int c = 0; c < MAX_AFFECT; c++) // Controle de Mana ( PVP )
			{
				if (pMob[idx].Affect[c].Type == 18)
				{
					if (pMob[idx].MOB.CurrentScore.Mp > pMob[idx].MOB.CurrentScore.MaxMp / 100 * 5)
					{
						int mana = pMob[idx].MOB.CurrentScore.Mp - (tDamage / 100) * 90;

						if (mana < 0)
						{
							tDamage -= mana / 10;
							mana = 0;
							pMob[idx].MOB.CurrentScore.Mp = mana;
							pUser[idx].ReqMp = mana;
							SetReqMp(idx);
							SendScore(idx);
						}
						else {

							pMob[idx].MOB.CurrentScore.Mp -= tDamage;
							pUser[idx].ReqMp -= tDamage;
							if (pMob[idx].MOB.CurrentScore.Mp <= 0)
							{
								mana = 0;
								pMob[idx].MOB.CurrentScore.Mp = mana;
								pUser[idx].ReqMp = mana;
							}
							SetReqMp(idx);
							SendScore(idx);
						}


						int abs = (1 << 23) & pMob[conn].MOB.LearnedSkill ? 55 : 60;

						tDamage = ((tDamage >> 1) + (tDamage << 4)) / abs;
						m->Dam[i].Damage = tDamage;

						if ((DoubleCritical & 4) != FALSE)
							m->Dam[1].Damage = tDamage;
					}
				}
			}
		}
#pragma endregion

		auto multHpMob = pMob[idx].MOB.Equip[13].sIndex;
		auto _tDamage = tDamage;
		if (multHpMob == 786 || multHpMob == 1936 || multHpMob == 1937)
		{
			int HpItem = GetItemSancNew(&pMob[idx].MOB.Equip[13]);
			if (HpItem < 2)
				HpItem = 2;
			int multHp = 1;
			switch (multHpMob)
			{
				case 1936:
					multHp = 10;
					break;
				case 1937:
					multHp = 1000;
					break;
				default:
					break;
			}
			multHp *= HpItem;

			_tDamage /= multHp;

		}

		if (_tDamage > pMob[idx].MOB.CurrentScore.Hp)
			pMob[idx].MOB.CurrentScore.Hp = 0;
		else
			pMob[idx].MOB.CurrentScore.Hp -= _tDamage;

		if (_calcDamage > 0)
			ProcessAdultMount(idx, _calcDamage / 2);

		if (idx > 0 && idx < MAX_USER)
		{
			pUser[idx].ReqHp = pUser[idx].ReqHp - tDamage;
			SetReqHp(idx);
		}

		if (idx > MAX_USER && pMob[idx].MOB.Clan == 4)
			LinkMountHp(idx);

		//if (pMob[idx].MOB.Equip[13].sIndex == 786)
		//{

		//	int itemSanc = pMob[idx].MOB.Equip[13].stEffect[0].cValue;
		//	if (itemSanc < 2)
		//		itemSanc = 2;


		//	tDamage = _pDamage / itemSanc;
		//	if (tDamage > pMob[idx].MOB.CurrentScore.Hp)
		//		tDamage = pMob[idx].MOB.CurrentScore.Hp;

		//	pMob[idx].MOB.CurrentScore.Hp = pMob[idx].MOB.CurrentScore.Hp - tDamage;
		//}

		//else if (pMob[idx].MOB.Equip[13].sIndex == 1936)//10X HP MONSTRO
		//{

		//	int itemSanc = pMob[idx].MOB.Equip[13].stEffect[0].cValue;
		//	if (itemSanc < 2)
		//		itemSanc = 2;

		//	itemSanc *= 10;

		//	tDamage = _pDamage / itemSanc;

		//	if (tDamage > pMob[idx].MOB.CurrentScore.Hp)
		//		tDamage = pMob[idx].MOB.CurrentScore.Hp;

		//	pMob[idx].MOB.CurrentScore.Hp = pMob[idx].MOB.CurrentScore.Hp - tDamage;
		//}

		//else if (pMob[idx].MOB.Equip[13].sIndex == 1937)//20X HP MONSTRO
		//{
		//	int itemSanc = pMob[idx].MOB.Equip[13].stEffect[0].cValue;
		//	if (itemSanc < 2)
		//		itemSanc = 2;

		//	itemSanc *= 1000;

		//	tDamage = _pDamage / itemSanc;

		//	if (tDamage > pMob[idx].MOB.CurrentScore.Hp)
		//		tDamage = pMob[idx].MOB.CurrentScore.Hp;

		//	pMob[idx].MOB.CurrentScore.Hp = pMob[idx].MOB.CurrentScore.Hp - tDamage;
		//}

		//else
		//{
		//	if (tDamage > pMob[idx].MOB.CurrentScore.Hp)
		//		tDamage = pMob[idx].MOB.CurrentScore.Hp;


		//	pMob[idx].MOB.CurrentScore.Hp = pMob[idx].MOB.CurrentScore.Hp - tDamage;
		//}

		//if (_calcDamage > 0)
		//	ProcessAdultMount(idx, _calcDamage / 2);

		//if (idx > 0 && idx < MAX_USER)
		//{
		//	pUser[idx].ReqHp = pUser[idx].ReqHp - tDamage;

		//	SetReqHp(idx);
		//}


		//if (idx > MAX_USER && pMob[idx].MOB.Clan == 4)
		//	LinkMountHp(idx);


#pragma region Joia Abs
		if (pMob[conn].HpAbs != 0 && (rand() % 2) == 0 && dam >= 1)
		{
			int RecHP = (int)((dam * pMob[conn].HpAbs + 1) / 50);

			/*int RecMP = (int)((dam * pMob[conn].HpAbs + 1) / 50);*/

			if (RecHP > 350)
				RecHP = 350;

			/*if (RecMP > 350)
				RecMP = 350;*/


				/*int reqmp = pUser[conn].ReqMp + RecMP;

				if (reqmp > pMob[conn].MOB.CurrentScore.MaxMp)
					pUser[conn].ReqMp = pMob[conn].MOB.CurrentScore.MaxMp;
				else
					pUser[conn].ReqMp = reqmp;*/



			int reqhp = pUser[conn].ReqHp + RecHP;

			if (reqhp > pMob[conn].MOB.CurrentScore.MaxHp)
				pUser[conn].ReqHp = pMob[conn].MOB.CurrentScore.MaxHp;
			else
				pUser[conn].ReqHp = reqhp;


			SetReqHp(conn);
			SendSetHpMp(conn);
		}
#pragma endregion


#pragma region Anti Freze Player
		if (pMob[idx].MOB.CurrentScore.Hp <= 0)
		{
			pMob[idx].MOB.CurrentScore.Hp = 0;
			MSG_CreateMob sm_tb;
			memset(&sm_tb, 0, sizeof(MSG_CreateMob));
			GridMulticast(pMob[idx].TargetX, pMob[idx].TargetY, (MSG_STANDARD*)&sm_tb, 0);
		}
#pragma endregion
#pragma endregion

		if (pMob[idx].MOB.CurrentScore.Hp <= 0)
		{
			pMob[idx].MOB.CurrentScore.Hp = 0;
			TargetKilled[i] = idx;
			continue;
		}

		// Evocation and Party mob group
		if (pMob[idx].Mode != MOB_EMPTY && pMob[idx].MOB.CurrentScore.Hp > 0)
		{
			SetBattle(idx, conn);

			pMob[conn].CurrentTarget = idx;

			int mleader = pMob[conn].Leader;
			if (mleader <= MOB_EMPTY)
				mleader = conn;

			int r = 0;
			for (r = MOB_EMPTY; r < MAX_PARTY; r++)
			{
				int partyMemberId = pMob[mleader].PartyList[r];
				if (partyMemberId <= MAX_USER)
					continue;

				if (pMob[partyMemberId].Mode == MOB_EMPTY || pMob[partyMemberId].MOB.CurrentScore.Hp <= 0)
				{
					if (pMob[partyMemberId].Mode != MOB_EMPTY)
						DeleteMob(partyMemberId, 1);

					pMob[mleader].PartyList[r] = MOB_EMPTY;
				}
				else
					SetBattle(partyMemberId, idx);
			}

			for (r = MOB_EMPTY; r < MAX_PARTY; r++)
			{
				int partyMemberId = pMob[mleader].Evocations[r];
				if (partyMemberId <= MAX_USER)
					continue;

				if (pMob[partyMemberId].Mode == MOB_EMPTY || pMob[partyMemberId].MOB.CurrentScore.Hp <= 0)
				{
					if (pMob[partyMemberId].Mode != MOB_EMPTY)
						DeleteMob(partyMemberId, 1);

					pMob[mleader].Evocations[r] = MOB_EMPTY;
				}
				else
					SetBattle(partyMemberId, idx);
			}

			mleader = pMob[idx].Leader;

			if (mleader <= 0)
				mleader = idx;

			for (r = 0; r < MAX_PARTY; r++)
			{
				int ptMemberId = pMob[mleader].PartyList[r];
				if (ptMemberId <= MAX_USER)
					continue;

				if (pMob[ptMemberId].Mode == MOB_EMPTY || pMob[ptMemberId].MOB.CurrentScore.Hp <= 0)
				{
					if (pMob[ptMemberId].Mode != MOB_EMPTY)
						DeleteMob(ptMemberId, 1);

					pMob[mleader].PartyList[r] = MOB_EMPTY;
				}
				else
					SetBattle(ptMemberId, conn);
			}

			for (r = 0; r < MAX_PARTY; r++)
			{
				int ptMemberId = pMob[mleader].Evocations[r];
				if (ptMemberId <= MAX_USER)
					continue;

				if (pMob[ptMemberId].Mode == MOB_EMPTY || pMob[ptMemberId].MOB.CurrentScore.Hp <= 0)
				{
					if (pMob[ptMemberId].Mode != MOB_EMPTY)
						DeleteMob(ptMemberId, 1);

					pMob[mleader].Evocations[r] = MOB_EMPTY;
				}
				else
					SetBattle(ptMemberId, conn);
			}
		}
	}
#pragma endregion

	if (UNK2 > 0)
		Exp = UNK2;

	if (DOUBLEMODE)
		Exp = Exp * 2;

	if (Exp <= 0)
		Exp = 0;

	if (Exp > 200)
		Exp = 200;

	//Espectral
	if ((pMob[conn].MOB.LearnedSkill & 0x20000000) != 0)
		m->DoubleCritical = m->DoubleCritical | 8;

	m->CurrentExp = pMob[conn].MOB.Exp;
	m->CurrentHp = pMob[conn].MOB.CurrentScore.Hp;

	if (ClientTick == SKIPCHECKTICK)
		m->ClientTick = CurrentTime;

	if (skillnum != 102)
		GridMulticast(pMob[conn].TargetX, pMob[conn].TargetY, (MSG_STANDARD*)m, 0);

	if (skillnum == 30)
		SendSetHpMp(conn);

#pragma region MobKilled Check
	for (int i = 0; i < MAX_TARGET; i++)
	{
		if (TargetKilled[i] > 0 && TargetKilled[i] < MAX_MOB && pMob[TargetKilled[i]].Mode != MOB_EMPTY)
			MobKilled(TargetKilled[i], conn, 0, 0);
	}
#pragma endregion
#pragma region Level Check

	int Segment = pMob[conn].CheckGetLevel();

	if (Segment >= 1 && Segment <= 4)
	{
		if (Segment == 4)
		{/*
			SendClientMessage(conn, g_pMessageStringTable[_NN_Level_Up]);*/
			SetCircletSubGod(conn);
			//SendEtc(conn);

			/*if (pMob[conn].extra.ClassMaster == MORTAL) {
				DoItemLevel(conn);
				
			}*/
		}
		if (Segment == 3)/*
			SendClientMessage(conn, g_pMessageStringTable[_NN_3_Quarters_Bonus]);*/

			if (Segment == 2)/*
				SendClientMessage(conn, g_pMessageStringTable[_NN_2_Quarters_Bonus]);*/

				if (Segment == 1)/*
					SendClientMessage(conn, g_pMessageStringTable[_NN_1_Quarters_Bonus]);*/

					SendScore(conn);
		SendEmotion(conn, 14, 3);

		if (Segment == 4)
		{
			//SendEtc(conn);

			int PKPoint = GetPKPoint(conn) + 5;
			SetPKPoint(conn, PKPoint);

			MSG_CreateMob sm_lup;
			memset(&sm_lup, 0, sizeof(MSG_CreateMob));
			GetCreateMob(conn, &sm_lup);

			GridMulticast(pMob[conn].TargetX, pMob[conn].TargetY, (MSG_STANDARD*)&sm_lup, 0);

		}
	}
#pragma endregion
}
