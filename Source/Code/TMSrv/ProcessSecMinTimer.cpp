
#include <Windows.h>
#include <stdio.h>
#include <fcntl.h>
#include <time.h>
#include <math.h>
#include <io.h>
#include <errno.h>

#include "..\Basedef.h"
#include "..\CPSock.h"
#include "..\ItemEffect.h"
#include "Language.h"

#include "CItem.h"
#include "Server.h"
#include "GetFunc.h"
#include "SendFunc.h"
#include "ProcessClientMessage.h"
#include "ProcessDBMessage.h"
#include "CWarTower.h"
#include "IPControl.h"
#include "Functions.h"

void ProcessSecTimer()
{
	if (ServerDown == 120) // two minutes untill the server closes
	{
		if (BILLING != 0)
		{
			_AUTH_GAME Unk;

			memset(&Unk, 0, 196);

			SendBilling2(&Unk, 4);

			BILLING = 0;
		}

		while (TRUE)
		{
			if (UserCount >= MAX_USER)
			{
				SystemLog("-system", "-", 0, "server down complete");

				if (hFont != 0)
				{
					DeleteObject(hFont);

					hFont = NULL;
				}

				PostQuitMessage(NULL);

				return;
			}

			if (pUser[UserCount].Mode == USER_EMPTY)
			{
				UserCount++;

				continue;
			}

			break;
		}

		pUser[UserCount].AccountName[ACCOUNTNAME_LENGTH - 1] = 0;
		pUser[UserCount].AccountName[ACCOUNTNAME_LENGTH - 2] = 0;


		CloseUser(UserCount);

		UserCount++;

		return;
	}

	if (ServerDown > -1000)
	{
		if (ServerDown <= 0)
		{
			ServerDown++;

			goto lbl_PST1;
		}

		if (ServerDown % 20 == 1)
		{
			int messageId = ServerDown / 20;
			SendNotice(g_pMessageStringTable[messageId + 17]);
		}

		ServerDown++;

		if (ServerDown == 120)
		{
			SetTimer(hWndMain, TIMER_SEC, 200, 0);

			return;
		}
	}

lbl_PST1:

	SecCounter++;

#pragma region Sistema de bloqueio de ip por requisições de conexão.
	for (auto i = 0; i < g_pBlockIP.size(); i++)
	{
		g_pBlockIP[i].countdown--;
		if (g_pBlockIP[i].countdown <= 0)
		{
			g_pBlockIP.erase(g_pBlockIP.begin() + i);
		}
	}
#pragma endregion

	CurrentTime = timeGetTime();

	if (SecCounter % 600 == 0) {
		GerarRecaptcha();
	}

	if (BILLING != 0 && BillCounter > 0 && BillServerSocket.Sock == 0)
	{
		BillCounter--;

		if (BillCounter <= 0)
		{
			CurrentTime = timeGetTime();


			int* pip = (int*)LocalIP;

			int ret = BillServerSocket.ConnectBillServer(BillServerAddress, BillServerPort, *pip, WSA_READBILL);

			CurrentTime = timeGetTime();


			if (ret == 0)
			{

				BILLING = 0;
			}
			else
			{
				_AUTH_GAME Unk;

				memset(&Unk, 0, 196);

				SendBilling2(&Unk, 4);
			}
		}
	}
	else
		BillCounter = 0;

#pragma region Save User
	if (SecCounter % 8 == 0)
	{
		for (int i = 1; i < MAX_USER; i++)
		{
			if (SaveCount >= MAX_USER)
				SaveCount = 1;

			if (pUser[SaveCount].Mode == USER_PLAY && pMob[SaveCount].Mode != MOB_EMPTY)
			{
				if (BILLING == 2 && pUser[SaveCount].Unk_2728 == 1 && pMob[SaveCount].MOB.CurrentScore.Level >= FREEEXP && (g_Hour <= 12 || g_Hour >= 19))
				{
					SendClientMessage(SaveCount, g_pMessageStringTable[_NN_Child_Pay]);

					CharLogOut(SaveCount);

					SaveCount++;

					break;
				}
				else
				{
					SaveUser(SaveCount, 0);

					SaveCount++;

					break;
				}
			}

			SaveCount++;
		}
	}
#pragma endregion
#pragma region User Loop
	for (int bb = 1; bb < MAX_USER; bb++)
	{

		if (pUser[bb].Mode)
		{
			if (pUser[bb].cSock.nSendPosition)
			{
				BOOL bSend = pUser[bb].cSock.SendMessageA();
				if (!bSend)
				{
					
					snprintf(temp, sizeof(temp), "err,send fail close %d/%d %d/%d",
						bb, pUser[bb].cSock.Sock, pUser[bb].cSock.nSendPosition, pUser[bb].cSock.nSentPosition);

					pUser[bb].AccountName[ACCOUNTNAME_LENGTH - 1] = 0;
					pUser[bb].AccountName[ACCOUNTNAME_LENGTH - 2] = 0;

					SystemLog(pUser[bb].AccountName, pUser[bb].MacAddress, pUser[bb].IP, temp);

					CloseUser(bb);
				}
			}
		}

		if (pUser[bb].Mode == USER_PLAY)
			pMob[bb].ProcessorSecTimer();

		/*if(GTorreState == 2) {
			if (pMob[bb].TargetX >= 2452 && pMob[bb].TargetY >= 1854 && pMob[bb].TargetX <= 2542 && pMob[bb].TargetY <= 1919) {
				UpdateGTower(bb);
			}
		}*/
		//Celestial Lv181 dentro da zona do pesadelo
		if ((pMob[bb].TargetX / 128) == 9 && (pMob[bb].TargetY / 128) == 1 || (pMob[bb].TargetX / 128) == 8 && (pMob[bb].TargetY / 128) == 2 || (pMob[bb].TargetX / 128) == 10 && (pMob[bb].TargetY / 128) == 2)
		{
			if ((pMob[bb].extra.ClassMaster == CELESTIAL || pMob[bb].extra.ClassMaster == CELESTIALCS || pMob[bb].extra.ClassMaster == SCELESTIAL) && pMob[bb].MOB.CurrentScore.Level > 199)
				DoRecall(bb);
			//SendClientMessage(bb, "desculpe");
			//return;
		}
		//ANTI CASSINO
		if (((pMob[bb].TargetX) / 128) == 31 && ((pMob[bb].TargetY) / 128) == 31) {
			if (pUser[bb].Admin != 1)
				DoRecall(bb);
		}
		//faz com que quando tire a Fada do Vale vc seja teleportado para fora
#pragma region Vale Perdido
		if (((pMob[bb].TargetX) / 128) == 17 && ((pMob[bb].TargetY) / 128) == 28)
		{
			if (pMob[bb].MOB.Equip[13].sIndex != 3916)
				DoRecall(bb);
		}
#pragma endregion

#pragma region Anti Pulo Lan
		//CHECA O LV DAS QUESTS
		if (pMob[bb].MOB.BaseScore.Level > 115 || pMob[bb].MOB.BaseScore.Level < 39)
		{
			if (pMob[bb].TargetX > 2379 && pMob[bb].TargetY > 2076 &&
				pMob[bb].TargetX < 2426 && pMob[bb].TargetY < 2133)

				ClearAreaQuest(bb, 2379, 2076, 2426, 2133);// Coveiro

			/*if (pMob[bb].QuestFlag && pUser[bb].Mode == USER_PLAY)
				pMob[bb].QuestFlag = 0;*/

		}
		if (pMob[bb].MOB.BaseScore.Level > 190 || pMob[bb].MOB.BaseScore.Level < 115)
		{
			if (pMob[bb].TargetX > 2228 && pMob[bb].TargetY > 1700 &&
				pMob[bb].TargetX < 2257 && pMob[bb].TargetY < 1728)


				ClearAreaQuest(bb, 2228, 1700, 2257, 1728);//Carbuncle  
			/*if (pMob[bb].QuestFlag && pUser[bb].Mode == USER_PLAY)
				pMob[bb].QuestFlag = 0;*/

		}
		if (pMob[bb].MOB.BaseScore.Level > 265 || pMob[bb].MOB.BaseScore.Level < 190)
		{
			if (pMob[bb].TargetX > 459 && pMob[bb].TargetY > 3887 &&
				pMob[bb].TargetX < 497 && pMob[bb].TargetY < 3916)


				ClearAreaQuest(bb, 459, 3887, 497, 3916);//Kaizen  
			/*if (pMob[bb].QuestFlag && pUser[bb].Mode == USER_PLAY)
				pMob[bb].QuestFlag = 0;*/

		}
		if (pMob[bb].MOB.BaseScore.Level > 321 || pMob[bb].MOB.BaseScore.Level < 265)
		{
			if (pMob[bb].TargetX > 658 && pMob[bb].TargetY > 3728 &&
				pMob[bb].TargetX < 703 && pMob[bb].TargetY < 3762)


				ClearAreaQuest(bb, 658, 3728, 703, 3762);//Hidras  
			/*if (pMob[bb].QuestFlag && pUser[bb].Mode == USER_PLAY)
				pMob[bb].QuestFlag = 0;*/

		}
		if (pMob[bb].MOB.BaseScore.Level > 351 || pMob[bb].MOB.BaseScore.Level < 320)
		{
			if (pMob[bb].TargetX > 1312 && pMob[bb].TargetY > 4027 &&
				pMob[bb].TargetX < 1348 && pMob[bb].TargetY < 4055)

				ClearAreaQuest(bb, 1312, 4027, 1348, 4055);//Elfos 
			/*if (pMob[bb].QuestFlag && pUser[bb].Mode == USER_PLAY)
				pMob[bb].QuestFlag = 0;*/
		}
#pragma endregion
		//zona de guilda
		if (pMob[bb].TargetX >= 1020 && pMob[bb].TargetY >= 1916 && pMob[bb].TargetX <= 1286 && pMob[bb].TargetY <= 2178 && pMob[bb].MOB.Guild <= 0)
		{
			SendClientMessage(bb, "Somente para Membros de Guild");
			DoRecall(bb);
		}	

#pragma region Pista de Runas Balrog Portais
		int xv = (pMob[bb].TargetX) & 0xFFFC;
		int yv = (pMob[bb].TargetY) & 0xFFFC;

		for (int x = 0; x < 3; x++)
		{
			if (pUser[bb].Mode != USER_PLAY || pMob[bb].MOB.CurrentScore.Hp <= 0 || Pista[5].Party[x].LeaderID == 0 || Pista[5].Party[x].LeaderID != bb || strcmp(Pista[5].Party[x].LeaderName, pMob[bb].MOB.MobName))
				continue;

			if (pMob[Pista[5].Party[x].LeaderID].Leader != -1 && pMob[Pista[5].Party[x].LeaderID].Leader)
				continue;

			int _rd = rand() % 3;

			int tx = 2100;
			int ty = 2100;

			//Sala 1 Portal 1
			if (xv == PistaBalrogPortalPos[0][0][0] && yv == PistaBalrogPortalPos[0][0][1])
			{
				if (_rd <= 1)
				{
					tx = PistaBalrogPos[1][0];
					ty = PistaBalrogPos[1][1];
				}

				else
				{
					tx = PistaBalrogPos[0][0];
					ty = PistaBalrogPos[0][1];
				}
			}

			//Sala 2 Portal 1
			else if (xv == PistaBalrogPortalPos[1][0][0] && yv == PistaBalrogPortalPos[1][0][1])
			{
				if (_rd <= 1)
				{
					tx = PistaBalrogPos[1][0];
					ty = PistaBalrogPos[1][1];
				}
				else if (_rd == 2)
				{
					tx = PistaBalrogPos[2][0];
					ty = PistaBalrogPos[2][1];
				}

				else
				{
					tx = PistaBalrogPos[0][0];
					ty = PistaBalrogPos[0][1];
				}
			}

			//Sala 2 Portal 2
			else if (xv == PistaBalrogPortalPos[1][1][0] && yv == PistaBalrogPortalPos[1][1][1])
			{
				if (_rd >= 2)
				{
					tx = PistaBalrogPos[1][0];
					ty = PistaBalrogPos[1][1];
				}
				else if (_rd == 0)
				{
					tx = PistaBalrogPos[2][0];
					ty = PistaBalrogPos[2][1];
				}

				else
				{
					tx = PistaBalrogPos[0][0];
					ty = PistaBalrogPos[0][1];
				}
			}

			//Sala 3 Portal 1
			else if (xv == PistaBalrogPortalPos[2][0][0] && yv == PistaBalrogPortalPos[2][0][1])
			{
				if (_rd <= 1)
				{
					tx = PistaBalrogPos[2][0];
					ty = PistaBalrogPos[2][1];
				}
				else if (_rd == 2)
				{
					tx = PistaBalrogPos[3][0];
					ty = PistaBalrogPos[3][1];
				}

				else
				{
					tx = PistaBalrogPos[1][0];
					ty = PistaBalrogPos[1][1];
				}
			}

			//Sala 3 Portal 2
			else if (xv == PistaBalrogPortalPos[2][1][0] && yv == PistaBalrogPortalPos[2][1][1])
			{
				if (_rd >= 2)
				{
					tx = PistaBalrogPos[2][0];
					ty = PistaBalrogPos[2][1];
				}
				else if (_rd == 0)
				{
					tx = PistaBalrogPos[3][0];
					ty = PistaBalrogPos[3][1];
				}

				else
				{
					tx = PistaBalrogPos[1][0];
					ty = PistaBalrogPos[1][1];
				}
			}

			//Sala 3 Portal 3
			else if (xv == PistaBalrogPortalPos[2][2][0] && yv == PistaBalrogPortalPos[2][2][1])
			{
				if (_rd <= 1)
				{
					tx = PistaBalrogPos[2][0];
					ty = PistaBalrogPos[2][1];
				}
				else if (_rd == 2)
				{
					tx = PistaBalrogPos[3][0];
					ty = PistaBalrogPos[3][1];
				}

				else
				{
					tx = PistaBalrogPos[1][0];
					ty = PistaBalrogPos[1][1];
				}
			}

			//Sala 4 Portal 1
			else if (xv == PistaBalrogPortalPos[3][0][0] && yv == PistaBalrogPortalPos[3][0][1])
			{
				if (_rd <= 1)
				{
					tx = PistaBalrogPos[3][0];
					ty = PistaBalrogPos[3][1];
				}
				else if (_rd == 2)
				{
					tx = PistaBalrogPos[4][0];
					ty = PistaBalrogPos[4][1];

					if (Pista[5].Party[0].MobCount == 0)
						GenerateMob(RUNEQUEST_LV5_MOB_BOSS, 0, 0);
				}

				else
				{
					tx = PistaBalrogPos[2][0];
					ty = PistaBalrogPos[2][1];
				}
			}

			//Sala 4 Portal 2
			else if (xv == PistaBalrogPortalPos[3][1][0] && yv == PistaBalrogPortalPos[3][1][1])
			{
				if (_rd >= 2)
				{
					tx = PistaBalrogPos[3][0];
					ty = PistaBalrogPos[3][1];
				}
				else if (_rd == 0)
				{
					tx = PistaBalrogPos[4][0];
					ty = PistaBalrogPos[4][1];

					if (Pista[5].Party[0].MobCount == 0)
						GenerateMob(RUNEQUEST_LV5_MOB_BOSS, 0, 0);
				}

				else
				{
					tx = PistaBalrogPos[2][0];
					ty = PistaBalrogPos[2][1];
				}
			}

			//Sala 4 Portal 3
			else if (xv == PistaBalrogPortalPos[3][2][0] && yv == PistaBalrogPortalPos[3][2][1])
			{
				if (_rd <= 1)
				{
					tx = PistaBalrogPos[3][0];
					ty = PistaBalrogPos[3][1];
				}
				else if (_rd == 2)
				{
					tx = PistaBalrogPos[4][0];
					ty = PistaBalrogPos[4][1];

					if (Pista[5].Party[0].MobCount == 0)
						GenerateMob(RUNEQUEST_LV5_MOB_BOSS, 0, 0);
				}

				else
				{
					tx = PistaBalrogPos[2][0];
					ty = PistaBalrogPos[2][1];
				}
			}

			//Sala 4 Portal 4
			else if (xv == PistaBalrogPortalPos[3][3][0] && yv == PistaBalrogPortalPos[3][3][1])
			{
				if (_rd <= 1)
				{
					tx = PistaBalrogPos[3][0];
					ty = PistaBalrogPos[3][1];
				}
				else if (_rd == 2)
				{
					tx = PistaBalrogPos[4][0];
					ty = PistaBalrogPos[4][1];

					if (Pista[5].Party[0].MobCount == 0)
						GenerateMob(RUNEQUEST_LV5_MOB_BOSS, 0, 0);
				}

				else
				{
					tx = PistaBalrogPos[2][0];
					ty = PistaBalrogPos[2][1];
				}
			}
			else
				continue;

			int inv = 0;
			for (inv = 0; inv < pMob[bb].MaxCarry && inv < MAX_CARRY; inv++)
			{
				if (pMob[bb].MOB.Carry[inv].sIndex == 4032)
				{
					BASE_ClearItem(&pMob[bb].MOB.Carry[inv]);
					SendItem(bb, ITEM_PLACE_CARRY, inv, &pMob[bb].MOB.Carry[inv]);
					break;
				}
			}

			if (inv == pMob[bb].MaxCarry)
				continue;

			DoTeleport(Pista[5].Party[x].LeaderID, tx, ty);

			for (int c = 0; c < MAX_PARTY; c++)
			{
				int partyconn = pMob[Pista[5].Party[x].LeaderID].PartyList[c];

				if (partyconn > 0 && partyconn < MAX_USER && partyconn != Pista[5].Party[x].LeaderID && pUser[partyconn].Mode == USER_PLAY)
					DoTeleport(partyconn, tx, ty);
			}
		}

#pragma endregion
	}
#pragma endregion
#pragma region Quest Verification
	if (SecCounter % 4 == 0)
	{
		//Carta Sala 1
		int Sala1 = mNPCGen.pList[SECRET_ROOM_N_SALA1_MOB_1].CurrentNumMob + mNPCGen.pList[SECRET_ROOM_N_SALA1_MOB_2].CurrentNumMob + mNPCGen.pList[SECRET_ROOM_M_SALA1_MOB_1].CurrentNumMob + mNPCGen.pList[SECRET_ROOM_M_SALA1_MOB_2].CurrentNumMob + mNPCGen.pList[SECRET_ROOM_A_SALA1_MOB_1].CurrentNumMob + mNPCGen.pList[SECRET_ROOM_A_SALA1_MOB_2].CurrentNumMob;
		int Sala2 = mNPCGen.pList[SECRET_ROOM_N_SALA2_MOB_1].CurrentNumMob + mNPCGen.pList[SECRET_ROOM_N_SALA2_MOB_2].CurrentNumMob + mNPCGen.pList[SECRET_ROOM_M_SALA2_MOB_1].CurrentNumMob + mNPCGen.pList[SECRET_ROOM_M_SALA2_MOB_2].CurrentNumMob + mNPCGen.pList[SECRET_ROOM_A_SALA2_MOB_1].CurrentNumMob + mNPCGen.pList[SECRET_ROOM_A_SALA2_MOB_2].CurrentNumMob;
		int Sala3 = mNPCGen.pList[SECRET_ROOM_N_SALA3_MOB_1].CurrentNumMob + mNPCGen.pList[SECRET_ROOM_N_SALA3_MOB_2].CurrentNumMob + mNPCGen.pList[SECRET_ROOM_M_SALA3_MOB_1].CurrentNumMob + mNPCGen.pList[SECRET_ROOM_M_SALA3_MOB_2].CurrentNumMob + mNPCGen.pList[SECRET_ROOM_A_SALA3_MOB_1].CurrentNumMob + mNPCGen.pList[SECRET_ROOM_A_SALA3_MOB_2].CurrentNumMob;
		int Sala4 = mNPCGen.pList[SECRET_ROOM_N_SALA4_MOB_1].CurrentNumMob + mNPCGen.pList[SECRET_ROOM_N_SALA4_MOB_2].CurrentNumMob + mNPCGen.pList[SECRET_ROOM_N_SALA4_MOB_3].CurrentNumMob + mNPCGen.pList[SECRET_ROOM_N_SALA4_MOB_4].CurrentNumMob + mNPCGen.pList[SECRET_ROOM_M_SALA4_MOB_1].CurrentNumMob + mNPCGen.pList[SECRET_ROOM_M_SALA4_MOB_2].CurrentNumMob + mNPCGen.pList[SECRET_ROOM_M_SALA4_MOB_3].CurrentNumMob + mNPCGen.pList[SECRET_ROOM_M_SALA4_MOB_4].CurrentNumMob + mNPCGen.pList[SECRET_ROOM_A_SALA4_MOB_1].CurrentNumMob + mNPCGen.pList[SECRET_ROOM_A_SALA4_MOB_2].CurrentNumMob + mNPCGen.pList[SECRET_ROOM_A_SALA4_MOB_3].CurrentNumMob + mNPCGen.pList[SECRET_ROOM_A_SALA4_MOB_4].CurrentNumMob;

		int PesadeloA = mNPCGen.pList[Erin].CurrentNumMob +
			mNPCGen.pList[Escuridao].CurrentNumMob +
			mNPCGen.pList[Fenix].CurrentNumMob +
			mNPCGen.pList[Kara].CurrentNumMob +
			mNPCGen.pList[Kei].CurrentNumMob +
			mNPCGen.pList[Kemi].CurrentNumMob +
			mNPCGen.pList[Leao].CurrentNumMob +
			mNPCGen.pList[Yue].CurrentNumMob;

		int PesadeloM = mNPCGen.pList[Arnold_].CurrentNumMob +
			mNPCGen.pList[Lainy].CurrentNumMob +
			mNPCGen.pList[Reimers].CurrentNumMob +
			mNPCGen.pList[RoPerion].CurrentNumMob +
			mNPCGen.pList[Irena].CurrentNumMob;

		int PesadeloN = mNPCGen.pList[Martin].CurrentNumMob +
			mNPCGen.pList[Balmers].CurrentNumMob +
			mNPCGen.pList[Rubyen].CurrentNumMob +
			mNPCGen.pList[Naomi].CurrentNumMob +
			mNPCGen.pList[Arnold].CurrentNumMob;

		int MOBS = mNPCGen.pList[4069].CurrentNumMob +
			mNPCGen.pList[4041].CurrentNumMob +
			mNPCGen.pList[4042].CurrentNumMob +
			mNPCGen.pList[4043].CurrentNumMob +
			mNPCGen.pList[4044].CurrentNumMob +
			mNPCGen.pList[4045].CurrentNumMob +
			mNPCGen.pList[4046].CurrentNumMob +
			mNPCGen.pList[4047].CurrentNumMob +
			mNPCGen.pList[4048].CurrentNumMob +
			mNPCGen.pList[4049].CurrentNumMob +
			mNPCGen.pList[4050].CurrentNumMob +
			mNPCGen.pList[4051].CurrentNumMob +
			mNPCGen.pList[4052].CurrentNumMob +
			mNPCGen.pList[4053].CurrentNumMob +
			mNPCGen.pList[4054].CurrentNumMob +
			mNPCGen.pList[4055].CurrentNumMob +
			mNPCGen.pList[4056].CurrentNumMob +
			mNPCGen.pList[4057].CurrentNumMob +
			mNPCGen.pList[4058].CurrentNumMob +
			mNPCGen.pList[4059].CurrentNumMob +
			mNPCGen.pList[4060].CurrentNumMob +
			mNPCGen.pList[4061].CurrentNumMob +
			mNPCGen.pList[4062].CurrentNumMob +
			mNPCGen.pList[4063].CurrentNumMob +
			mNPCGen.pList[4064].CurrentNumMob +
			mNPCGen.pList[4065].CurrentNumMob +
			mNPCGen.pList[4066].CurrentNumMob;

		int Quadra_1 = mNPCGen.pList[6076].CurrentNumMob +
			mNPCGen.pList[6077].CurrentNumMob +
			mNPCGen.pList[6078].CurrentNumMob +
			mNPCGen.pList[6079].CurrentNumMob +
			mNPCGen.pList[6080].CurrentNumMob +
			mNPCGen.pList[6081].CurrentNumMob +
			mNPCGen.pList[6082].CurrentNumMob +
			mNPCGen.pList[6083].CurrentNumMob +
			mNPCGen.pList[6084].CurrentNumMob;

		int Quadra_2 = mNPCGen.pList[6086].CurrentNumMob +
			mNPCGen.pList[6087].CurrentNumMob +
			mNPCGen.pList[6088].CurrentNumMob +
			mNPCGen.pList[6089].CurrentNumMob +
			mNPCGen.pList[6090].CurrentNumMob +
			mNPCGen.pList[6091].CurrentNumMob +
			mNPCGen.pList[6092].CurrentNumMob +
			mNPCGen.pList[6093].CurrentNumMob +
			mNPCGen.pList[6094].CurrentNumMob;

		int Quadra_3 = mNPCGen.pList[6096].CurrentNumMob +
			mNPCGen.pList[6097].CurrentNumMob +
			mNPCGen.pList[6098].CurrentNumMob +
			mNPCGen.pList[6099].CurrentNumMob +
			mNPCGen.pList[6100].CurrentNumMob +
			mNPCGen.pList[6101].CurrentNumMob +
			mNPCGen.pList[6102].CurrentNumMob +
			mNPCGen.pList[6103].CurrentNumMob +
			mNPCGen.pList[6104].CurrentNumMob;

		int Quadra_4 = mNPCGen.pList[6106].CurrentNumMob +
			mNPCGen.pList[6107].CurrentNumMob +
			mNPCGen.pList[6108].CurrentNumMob +
			mNPCGen.pList[6109].CurrentNumMob +
			mNPCGen.pList[6110].CurrentNumMob +
			mNPCGen.pList[6111].CurrentNumMob +
			mNPCGen.pList[6112].CurrentNumMob +
			mNPCGen.pList[6113].CurrentNumMob +
			mNPCGen.pList[6114].CurrentNumMob;

		/*int  MOBDESERTO = mNPCGen.pList[3139].CurrentNumMob +
			mNPCGen.pList[3140].CurrentNumMob +
			mNPCGen.pList[3141].CurrentNumMob +
			mNPCGen.pList[3142].CurrentNumMob +
			mNPCGen.pList[3143].CurrentNumMob +
			mNPCGen.pList[3144].CurrentNumMob +
			mNPCGen.pList[3145].CurrentNumMob +
			mNPCGen.pList[3146].CurrentNumMob +
			mNPCGen.pList[3147].CurrentNumMob +
			mNPCGen.pList[3148].CurrentNumMob +
			mNPCGen.pList[3149].CurrentNumMob +
			mNPCGen.pList[3150].CurrentNumMob +
			mNPCGen.pList[3151].CurrentNumMob +
			mNPCGen.pList[3152].CurrentNumMob +
			mNPCGen.pList[3153].CurrentNumMob +
			mNPCGen.pList[3154].CurrentNumMob +
			mNPCGen.pList[3155].CurrentNumMob +
			mNPCGen.pList[3156].CurrentNumMob +
			mNPCGen.pList[3157].CurrentNumMob +
			mNPCGen.pList[3158].CurrentNumMob +
			mNPCGen.pList[3159].CurrentNumMob;*/

		int Lichs = mNPCGen.pList[LICHBOSS2].CurrentNumMob +
			mNPCGen.pList[LICHBOSS4].CurrentNumMob;

		
		int Users = GetUserInArea(1295, 1480, 1385, 1520, temp);

		SendSignalParmArea(778, 3651, 832, 3699, ESCENE_FIELD, _MSG_MobLeft, Sala1);
		//Carta Sala 2
		SendSignalParmArea(836, 3651, 890, 3699, ESCENE_FIELD, _MSG_MobLeft, Sala2);
		//Carta Sala 3
		SendSignalParmArea(832, 3594, 890, 3644, ESCENE_FIELD, _MSG_MobLeft, Sala3);
		//Carta Sala 4
		SendSignalParmArea(780, 3594, 832, 3645, ESCENE_FIELD, _MSG_MobLeft, Sala4);

		//Pesadelo A
		SendShortSignalParm2Area(1152, 128, 1280, 256, ESCENE_FIELD, _MSG_MobCount, PesadeloA, 8);

		//Pesadelo M
		SendShortSignalParm2Area(1024, 256, 1152, 384, ESCENE_FIELD, _MSG_MobCount, PesadeloM, 7);

		//Pesadelo N
		SendShortSignalParm2Area(1280, 256, 1408, 384, ESCENE_FIELD, _MSG_MobCount, PesadeloN, 5);

		//Pista de runas +6 - Coelho
		SendSignalParmArea(3330, 1475, 3448, 1525, ESCENE_FIELD, _MSG_MobLeft, Pista[6].Party[0].MobCount);

		//RvR
		SendShortSignalParm2Area(1017, 1911, 1290, 2183, ESCENE_FIELD, _MSG_MobCount, RvRRedPoint + 0, RvRBluePoint + 0);

		//SendSignalParmArea(1295, 1480, 1385, 1520, ESCENE_FIELD, _MSG_MobLeft, Users);

		if (EspelhoLive == 2 && SecCounter % 5 == 0)
		{
			SendShortSignalParm2Area(3725, 2831, 3833, 2914, ESCENE_FIELD, _MSG_MobCount, MOBS, 70);
		}
		int Users1 = GetUserInArea(136, 4000, 200, 4100, temp);
		SendSignalParmArea(136, 4000, 200, 4100, ESCENE_FIELD, _MSG_MobLeft, Users1);

		if (SecCounter % 10 == 0)
		{
			for (int i = 1; i < MAX_USER; i++)
			{
				if (BrState == 1 && pMob[i].TargetX > 140 && pMob[i].TargetY > 4000 && pMob[i].TargetX < 200 && pMob[i].TargetY < 4100)
				{
					if (Users1 == 1)
					{
						
						SendClientMessage(i, "Parabens, Voce venceu a [Batalha Real].");
						p_BatalhaReal.start = false;
						memset(&p_BatalhaReal, 0, sizeof(p_BatalhaReal));
						BrState = 0;
						//pUser[i].Honra += 15;
						int x = 0;
						if (x != pMob[i].MaxCarry)
						{
							STRUCT_ITEM Item;
							memset(&Item, 0, sizeof(STRUCT_ITEM));
							int _rd = rand() % 1;
							if (_rd < 100) //25%
							{
								Item.sIndex = 480; //item opçao 1
								Item.stEffect[0].cEffect = 0; //efeito REF
								Item.stEffect[0].cValue = 0; //valor
								Item.stEffect[1].cEffect = 0; //efeito ADD
								Item.stEffect[1].cValue = 0; //valor
							}
							PutItem(i, &Item);
							SendClientMessage(i, strFmt(g_pMessageStringTable[_SN_Item_Arrived], g_pItemList[Item.sIndex].Name));
						}
						ClearArea(140, 4000, 200, 4100);
						SendScore(i);
						SendEtc(i);
					}
				}
			}
		}

		if (SecCounter % 2 == 0)
		{
			for (int i = 1; i < MAX_USER; i++)
			{
				if (pUser[i].Mode != USER_PLAY)
					continue;
				if (pMob[i].TargetX >= 1153 && pMob[i].TargetY >= 1681 && pMob[i].TargetX <= 1205 && pMob[i].TargetY <= 1771)
				{
					if (pUser[i].BossLocal1 == 0)
					{
						pUser[i].BossLocal1 = 1;
						SendEtc(i);
					}
				}
				else if (pUser[i].BossLocal1 == true)
				{
					pUser[i].BossLocal1 = 0;
					SendEtc(i);
				}
			}
		}



#pragma region >> Verifica se o usuário está com várias contas abertas

		/* Batalha Real */
		//GetUserInAreaMac(0, 140, 4000, 200, 4100);

		/* Lan House (A) */
		//GetUserInAreaMac(0, 3860, 3602, 3946, 3690);

		/* Lan House (M) */
		//GetUserInAreaMac(0, 3734, 3476, 3818, 3561);

		/* Lan House (N) */
		//GetUserInAreaMac(0, 3604, 3601, 3690, 3690);

		/* Área de evento */
		/*GetUserInAreaMac(0, 2560, 2560, 2687, 2687); */


#pragma endregion

#pragma region Quest Castelo de Gelo
		if (EspelhoLive == 2)
		{
			if (MOBS == 1)
			{
				//DarkShadow
				GenerateMob(SOMBRANEGRA, 0, 0);
				EspelhoLive = 0;
				SendNoticeArea(g_pMessageStringTable[_ND_GenDarkShadow], 3703, 2829, 3967, 2942);
			}
		}
#pragma endregion
#pragma region Contador Laranja
		if (SecCounter % 1 == 0)
		{
			int Quadra_1 =
				mNPCGen.pList[4661].CurrentNumMob +
				mNPCGen.pList[4662].CurrentNumMob +
				mNPCGen.pList[4663].CurrentNumMob +
				mNPCGen.pList[4664].CurrentNumMob +
				mNPCGen.pList[4665].CurrentNumMob +
				mNPCGen.pList[4666].CurrentNumMob +
				mNPCGen.pList[4667].CurrentNumMob +
				mNPCGen.pList[4668].CurrentNumMob +
				mNPCGen.pList[4669].CurrentNumMob;

			int Quadra_2 =
				mNPCGen.pList[4671].CurrentNumMob +
				mNPCGen.pList[4672].CurrentNumMob +
				mNPCGen.pList[4673].CurrentNumMob +
				mNPCGen.pList[4674].CurrentNumMob +
				mNPCGen.pList[4675].CurrentNumMob +
				mNPCGen.pList[4676].CurrentNumMob +
				mNPCGen.pList[4677].CurrentNumMob +
				mNPCGen.pList[4678].CurrentNumMob +
				mNPCGen.pList[4679].CurrentNumMob;

			int Quadra_3 =
				mNPCGen.pList[4681].CurrentNumMob +
				mNPCGen.pList[4682].CurrentNumMob +
				mNPCGen.pList[4683].CurrentNumMob +
				mNPCGen.pList[4684].CurrentNumMob +
				mNPCGen.pList[4685].CurrentNumMob +
				mNPCGen.pList[4686].CurrentNumMob +
				mNPCGen.pList[4687].CurrentNumMob +
				mNPCGen.pList[4688].CurrentNumMob +
				mNPCGen.pList[4689].CurrentNumMob;

			int Quadra_4 =
				mNPCGen.pList[4691].CurrentNumMob +
				mNPCGen.pList[4692].CurrentNumMob +
				mNPCGen.pList[4693].CurrentNumMob +
				mNPCGen.pList[4694].CurrentNumMob +
				mNPCGen.pList[4695].CurrentNumMob +
				mNPCGen.pList[4696].CurrentNumMob +
				mNPCGen.pList[4697].CurrentNumMob +
				mNPCGen.pList[4698].CurrentNumMob +
				mNPCGen.pList[4699].CurrentNumMob;

			int Lichs =
				mNPCGen.pList[LICHBOSS2].CurrentNumMob +
				mNPCGen.pList[LICHBOSS4].CurrentNumMob;

#pragma region Portao Infernal // Quadras
			if (TarantulaKilled == TRUE)
			{
				if (RandBoss == 1)
				{
					if (Quadra_1 == 0 && Lich_1 == 1)
						GenerateMob(LICHBOSS1, 1811, 3606);

					if (Quadra_2 == 0 && Lich_2 == 1)
						GenerateMob(LICHBOSS2, 1876, 3606);

					if (Quadra_3 == 0 && Lich_3 == 1)
						GenerateMob(LICHBOSS3, 1876, 3692);

					if (Quadra_4 == 0 && Lich_4 == 1)
						GenerateMob(LICHBOSS4, 1811, 3692);

					if (Lich_2 == 2 && Lich_4 == 2)
					{
						Lich_2 = 0;
						Lich_4 = 0;
						SendNoticeArea(g_pMessageStringTable[_NN_Killed_Boss], 1664, 3584, 1919, 3711);

						SendNoticeArea(g_pMessageStringTable[_NN_Hell_Clear], 1664, 3584, 1919, 3711);

						for (int x = PI_INITIAL6; x <= PI_END6; x++)
							GenerateMob(x, 0, 0);

						CreateMob("Aki", 1852, 3650, "npc", 0);
					}
				}

				if (RandBoss == 2)
				{
					if (Quadra_1 == 0 && Lich_1 == 1)
						GenerateMob(LICHBOSS2, 1811, 3606);

					if (Quadra_2 == 0 && Lich_2 == 1)
						GenerateMob(LICHBOSS1, 1876, 3606);

					if (Quadra_3 == 0 && Lich_3 == 1)
						GenerateMob(LICHBOSS4, 1876, 3692);

					if (Quadra_4 == 0 && Lich_4 == 1)
						GenerateMob(LICHBOSS3, 1811, 3692);

					if (Lich_1 == 2 && Lich_3 == 2)
					{
						Lich_1 = 0;
						Lich_3 = 0;
						SendNoticeArea(g_pMessageStringTable[_NN_Killed_Boss], 1664, 3584, 1919, 3711);

						SendNoticeArea(g_pMessageStringTable[_NN_Hell_Clear], 1664, 3584, 1919, 3711);

						for (int x = PI_INITIAL6; x <= PI_END6; x++)
							GenerateMob(x, 0, 0);

						CreateMob("Aki", 1851, 3647, "npc", 0);
					}
				}
			}
#pragma endregion
		}
	}
#pragma endregion 
#pragma region Itens Time
	if (SecCounter % 120 == 0)
	{

		for (int user = 1; user < MAX_USER; user++)
		{
			if (pUser[user].Mode != USER_PLAY)
				continue;

			//novas esferas
			if (pMob[user].MOB.Equip[14].sIndex >= 3980 && pMob[user].MOB.Equip[14].sIndex <= 3992 && BASE_CheckItemDate(&pMob[user].MOB.Equip[14]))
			{


				BASE_ClearItem(&pMob[user].MOB.Equip[14]);
				SendItem(user, ITEM_PLACE_EQUIP, 14, &pMob[user].MOB.Equip[14]);
			}
			if (pMob[user].MOB.Equip[14].sIndex >= 3995 && pMob[user].MOB.Equip[14].sIndex <= 3999 && BASE_CheckItemDate(&pMob[user].MOB.Equip[14]))
			{


				BASE_ClearItem(&pMob[user].MOB.Equip[14]);
				SendItem(user, ITEM_PLACE_EQUIP, 14, &pMob[user].MOB.Equip[14]);
			}


			//trajes
			if (pMob[user].MOB.Equip[12].sIndex >= 4150 && pMob[user].MOB.Equip[12].sIndex <= 4188 && BASE_CheckItemDate(&pMob[user].MOB.Equip[12]))
			{


				BASE_ClearItem(&pMob[user].MOB.Equip[12]);
				SendItem(user, ITEM_PLACE_EQUIP, 12, &pMob[user].MOB.Equip[12]);
			}
			if (pMob[user].MOB.Equip[12].sIndex >= 4200 && pMob[user].MOB.Equip[12].sIndex <= 4499 && BASE_CheckItemDate(&pMob[user].MOB.Equip[12]))
			{


				BASE_ClearItem(&pMob[user].MOB.Equip[12]);
				SendItem(user, ITEM_PLACE_EQUIP, 12, &pMob[user].MOB.Equip[12]);
			}

			//fadas
			if (pMob[user].MOB.Equip[13].sIndex >= 3900 && pMob[user].MOB.Equip[13].sIndex <= 3916)
			{
				BASE_CheckFairyDate(&pMob[user].MOB.Equip[13]);
				SendItem(user, ITEM_PLACE_EQUIP, 13, &pMob[user].MOB.Equip[13]);
				pMob[user].GetCurrentScore(user);
			}

			//bolsa andarilho
			if (pMob[user].MOB.Carry[60].sIndex == 3467 && BASE_CheckItemDate(&pMob[user].MOB.Carry[60]))
			{
				BASE_ClearItem(&pMob[user].MOB.Carry[60]);
				SendItem(user, ITEM_PLACE_CARRY, 60, &pMob[user].MOB.Carry[60]);

				pMob[user].MaxCarry = 30;

				if (pMob[user].MOB.Carry[60].sIndex == 3467)
					pMob[user].MaxCarry += 15;

				if (pMob[user].MOB.Carry[61].sIndex == 3467)
					pMob[user].MaxCarry += 15;
			}
			if (pMob[user].MOB.Carry[61].sIndex == 3467 && BASE_CheckItemDate(&pMob[user].MOB.Carry[61]))
			{
				BASE_ClearItem(&pMob[user].MOB.Carry[61]);
				SendItem(user, ITEM_PLACE_CARRY, 61, &pMob[user].MOB.Carry[61]);

				pMob[user].MaxCarry = 30;

				if (pMob[user].MOB.Carry[60].sIndex == 3467)
					pMob[user].MaxCarry += 15;

				if (pMob[user].MOB.Carry[61].sIndex == 3467)
					pMob[user].MaxCarry += 15;
			}
		}
	}
#pragma endregion
#pragma region Unknown Functions
	if (SecCounter % 2 == 0)
	{
		for (int i = 1; i < MAX_USER; i++)
		{
			if (pUser[i].Mode == USER_PLAY && pMob[i].MOB.CurrentScore.Hp > 0)
			{
				pUser[i].Unk_2688 = 0;

				int retHp = ApplyHp(i);
				int retMp = ApplyMp(i);

				if (retHp != 0)
					SendScore(i);

				else if (retMp != 0)
					SendSetHpMp(i);
			}
		}
	}

	if (SecCounter % 20 == 0)
	{
		for (int i = 1; i < MAX_USER; i++)
		{
			if (pUser[i].Mode == USER_PLAY && pMob[i].MOB.CurrentScore.Hp > 0)
			{
				//regen de hp automatico
				pUser[i].ReqHp += pMob[i].MOB.BaseScore.Level + 30;
				pUser[i].ReqMp += pMob[i].MOB.BaseScore.Level + 30;

				int retHp = ApplyHp(i);
				int retMp = ApplyMp(i);

				if (retHp != 0)
					SendScore(i);

				else if (retMp != 0)
					SendSetHpMp(i);
			}
		}
	}
#pragma endregion


#pragma region Boss Time
	if (SecCounter % 2 == 0)
	{
		struct tm when;
		time_t now;
		time(&now);
		when = *localtime(&now);
		//
		//#pragma region DOUBLE EXP AUTOMATIC
		//		
		//		 if ((((when.tm_wday == 1 && when.tm_wday == 2 && when.tm_wday == 3 && when.tm_wday == 4 && when.tm_wday == 5) && when.tm_hour == 13 && when.tm_hour == 18) && when.tm_min == 20) && when.tm_sec == 0)
		//		 if (DOUBLEMODE == 0)
		//		 {
		//			DOUBLEMODE = 1;
		//			DrawConfig(TRUE);
		//			SendMsgExp(1, "![Evento]:Double Exp On", TNColor::NewYellow, false);
		//		 }
		//		
		//		 if ((((when.tm_wday == 1 && when.tm_wday == 2 && when.tm_wday == 3 && when.tm_wday == 4 && when.tm_wday == 5) && when.tm_hour == 13 && when.tm_hour == 19) && when.tm_min == 0) && when.tm_sec == 0)
		//		 {
		//			if (DOUBLEMODE == 1)
		//			{
		//				DOUBLEMODE = 0;
		//				DrawConfig(TRUE);
		//				SendMsgExp(1, "![Evento]:Double Exp Off", TNColor::NewYellow, false);
		//			}
		//		 }
		//		
		//#pragma endregion

				//portão infernal
		if ((when.tm_min == 25 || when.tm_min == 55) && when.tm_sec >= 0 && when.tm_sec <= 2)
		{
			SendNoticeArea("Os Cavaleiros Esqueleto estão atacando a estrutura central!", 1664, 3584, 1919, 3711);

			for (int x = PI_INITIAL6; x <= PI_END6; x++)
				GenerateMob(x, 0, 0);
		}


#pragma region Kefra BOSS Initialize
		if ((when.tm_wday == 2 && when.tm_hour == 19 && when.tm_min == 0) && when.tm_sec >= 0 && when.tm_sec <= 2 && KefraLive)
		{
			KefraLive = 0;

			//Kefra
			GenerateMob(KEFRA_BOSS, 0, 0);

			for (int xx = KEFRA_MOB_INITIAL; xx <= KEFRA_MOB_END; xx++)
				GenerateMob(xx, 0, 0);
		}
#pragma endregion
		//#pragma region Batalha Real GreenTime
		//		if (SecCounter % 1 == 0)
		//		{
		//			if (p_BatalhaReal.start == true)
		//			{
		//				for (int i = 0; i < 20; i++)
		//				{
		//					if (pUser[i].Mode != USER_PLAY)
		//						continue;
		//
		//					if (BrTime > 0)
		//						BrTime--;
		//					SendClientSignalParmCoord(i, ESCENE_FIELD, _MSG_StartTime, BrTime, 140, 4000, 200, 4100);
		//				}
		//			}
		//		}
		//#pragma endregion

				//evento lojinha
#pragma region  >> MAXUSER - LOJINHA

		if (SecCounter % 2 == 0)
		{
			for (int i = 1; i < MAX_USER; i++)
			{
				if (pUser[i].Mode != USER_PLAY)
					continue;

				/*GetUserLojinhaAreaMac(i);*/
				if (pMob[i].CheckLojinha > 0)
					pMob[i].CheckLojinha--;

				/*Armia*/
				SendClientSignalParmCoord(i, ESCENE_FIELD, _MSG_StartTime, pMob[i].CheckLojinha, 2064, 2056, 2154, 2160);
				/*Erion*/
				SendClientSignalParmCoord(i, ESCENE_FIELD, _MSG_StartTime, pMob[i].CheckLojinha, 2449, 1984, 2475, 2023);
				/*Azran*/
				SendClientSignalParmCoord(i, ESCENE_FIELD, _MSG_StartTime, pMob[i].CheckLojinha, 2443, 1678, 2559, 1748);
				/*Gelo*/
				SendClientSignalParmCoord(i, ESCENE_FIELD, _MSG_StartTime, pMob[i].CheckLojinha, 3609, 3101, 3689, 3147);
				/*Noatun*/
				SendClientSignalParmCoord(i, ESCENE_FIELD, _MSG_StartTime, pMob[i].CheckLojinha, 1039, 1704, 1075, 1754);

				if (pUser[i].TradeMode == 1 && Limitadordelojinha(pUser[i].MacAddress) > 1)
				{
					SendClientMessage(i, "Limite de [01] lojinha por máquina.");
					RemoveTrade(i);
					return;
				}
				/////////////////////////////////////////////////
				//Limitador de Lojinhas por IP
				/*int Connections = 0;
				for (int z = 0; z < MAX_USER; z++)
				{
					if (pUser[z].Mode != USER_PLAY)
						continue;

					if (!pUser[z].cSock.Sock)
						continue;

					if (pUser[z].TradeMode == 1)
					{
						if (pUser[z].IP == pUser[i].IP)
							Connections++;
					}
				}
				if (Connections > 2) {
					SendClientMessage(i, "Limite de [02] lojinha por endereço de IP");
					RemoveTrade(i);
					return;
				}*/
				////////////////////////////////////////////////
				if (pUser[i].TradeMode == 1 && pMob[i].CheckLojinha <= 0)
				{
					pUser[i].Honra += 1;						

					/*if (EventStatus == 1) {
						STRUCT_ITEM item;
						memset(&item, 0, sizeof(STRUCT_ITEM));						
						item.sIndex = 475;

						if (pMob[i].MOB.Equip[13].sIndex == 3901 || pMob[i].MOB.Equip[13].sIndex == 3902)
						{
							SendItemagrupar(i, item.sIndex);
							SendItemagrupar(i, item.sIndex);
						}
						else
							SendItemagrupar(i, item.sIndex);

					}*/
					pMob[i].CheckLojinha = 600;//600 = 10 minutos
					
					SendClientMessage(i, "Você Recebeu sua recompensa");
					SendEtc(i);
				}

#pragma region >>Func Fix

				ClearCrown(i);
				//LimiteBsWepom(i);

#pragma endregion


			}
		}


#pragma endregion

#pragma region >> Resete Pistas precaução
		if ((when.tm_min == 15 || when.tm_min == 35 || when.tm_min == 55) && when.tm_sec >= 10)
		{
			if (SecCounter % 2 == 0)
			{
				ClearAreaTeleport(3320, 1016, 3448, 1656, 3290, 1685);
			}
		}

#pragma region >> rvr boss
		if (when.tm_wday == 1 || when.tm_wday == 2 || when.tm_wday == 3 || when.tm_wday == 4 || when.tm_wday == 5)
		{
			if (when.tm_hour == 20)
			{
				if ((when.tm_min == 15) && when.tm_sec == 0)
				{
					if (SecCounter % 2 == 0)
					{

						GenerateMob(BARAO_AZUL, 0, 0);
						SendNoticeArea(" O Barão Acabou de Renascer !!!", 1053, 1949, 1246, 2148);

					}
					if (SecCounter % 2 == 0)
					{
						GenerateMob(BARAO_VERMELHO, 0, 0);
					}
				}
			}
		}
		if (when.tm_wday == 1 || when.tm_wday == 2 || when.tm_wday == 3 || when.tm_wday == 4 || when.tm_wday == 5)
		{
			if (when.tm_hour == 20)
			{
				if ((when.tm_min == 5 || when.tm_min == 10 || when.tm_min == 20 || when.tm_min == 25) && when.tm_sec == 0)
				{
					if (SecCounter % 2 == 0)
					{
						GenerateMob(ENT_OBSCURO_BLUE, 0, 0);
						SendNoticeArea(" O Ent Obscuro Acabou de Renascer !!!", 1053, 1949, 1246, 2148);
					}
					if (SecCounter % 2 == 0)
					{
						GenerateMob(ENT_OBSCURO_RED, 0, 0);
					}
				}
			}
		}

#pragma endregion
#pragma region >> Reset Quest
		if (SecCounter % 1200 == 0)
		{
			ClearArea(2232, 1564, 2263, 1592);// Capa Verde
			ClearArea(2640, 1966, 2670, 2004);//Reset habilidades
			ClearArea(1950, 1586, 1988, 1614);//Reset habilidades
			ClearArea(793, 4046, 827, 4080);//Quest Gargula

			ClearArea(2379, 2076, 2426, 2133);// Coveiro
			ClearArea(2228, 1700, 2257, 1728);//Carbuncle
			ClearArea(459, 3887, 497, 3916);//Kaizen
			ClearArea(658, 3728, 703, 3762);//Hidras
			ClearArea(1312, 4027, 1348, 4055);//Elfos

			ClearArea(3602, 3602, 3693, 3692);//Lanhouse N  
			ClearArea(3730, 3474, 3821, 3565);//Lanhouse M  
			ClearArea(3602, 3858, 3949, 3692);//Lanhouse A 

			/*for (int x = 1; x < MAX_USER; x++)
			{
				if (pMob[x].QuestFlag && pUser[x].Mode == USER_PLAY) {
					pMob[x].QuestFlag = 0;
					pMob[x].LanNFlag = 0;
					pMob[x].LanMFlag = 0;
					pMob[x].LanAFlag = 0;
				}
			}*/
		}


#pragma region BOSS GLOBAL
		if (((when.tm_wday != 0 && when.tm_wday != 6) && (when.tm_hour == 0 || when.tm_hour == 4 || when.tm_hour == 8 || when.tm_hour == 12 || when.tm_hour == 16 || when.tm_hour == 20) && when.tm_min == 0 && when.tm_sec <= 3) && g_BSombraNegra == FALSE) // HORARIO DO BOSS - Segunda à Sexta de 4 em 4 horas
		{
			GenerateMob(SOMBRANEGRA, 0, 0);
			SendNotice("Sombra Negra Nasceu!");
			g_BSombraNegra = TRUE;
		}
		//if (((when.tm_wday != 0 && when.tm_wday != 6) && when.tm_hour == 18 && when.tm_min == 40 && when.tm_sec <= 3) && g_BVerid == FALSE) // HORARIO DO BOSS - Segunda à Sexta 18:40 da noite
		//{
		//	GenerateMob(VERIDNEGRO, 0, 0);
		//	SendNotice("O Verid Negro acabou de renascer!");
		//	g_BVerid = TRUE;
		//}
		if (((when.tm_wday != 0 && when.tm_wday != 6) && when.tm_hour == 19 && when.tm_min == 40 && when.tm_sec <= 3) && g_RainhaG == FALSE) // HORARIO DO BOSS - Segunda à Sexta 19:40 da noite		
		{
			GenerateMob(ESPELHO_RAINHAG, 0, 0);
			SendNotice("The Mirror Queen Reborn!");
			g_RainhaG = TRUE;
		}
#pragma endregion

		//#pragma region Boss 1 Castelo de Gelo
		//		if ((when.tm_hour == 22 && when.tm_min ==59) && when.tm_sec >= 58 && when.tm_sec <= 59 && (EspelhoLive == 0)) // HORARIO DO BOSS - Todos os dias 22:59
		//		{
		//			// BOSS PARTE 1
		//			for (int w = BOSS1_INITIAL; w <= BOSS1_END; w++)
		//				mNPCGen.pList[w].MinuteGenerate = -1;
		//			// BOSS PARTE 2
		//			for (int x = BOSS1_INITIAL2; x <= BOSS1_END2; x++)
		//				mNPCGen.pList[x].MinuteGenerate = -1;
		//
		//			EspelhoLive = 1;
		//
		//			int rand_ = rand() % 100;
		//			if (rand_ <= 25)
		//			GenerateMob(ESPELHO_RAINHAG, 3746, 2978);
		//			else if (rand_ <= 50)
		//				GenerateMob(ESPELHO_RAINHAG, 3619, 2788);
		//			else if (rand_ <= 75)
		//				GenerateMob(ESPELHO_RAINHAG, 3622, 3023);
		//			else
		//				GenerateMob(ESPELHO_RAINHAG, 3538, 2982);
		//
		//			SendNotice("Espelho RainhaG acaba de nascer em Karden!");
		//		}
		//#pragma endregion
		//#pragma region Boss 1 Castelo de Gelo Parte 2
		//		if ((when.tm_hour == 23 && when.tm_min == 20) && when.tm_sec >= 0 && when.tm_sec <= 2 && (EspelhoLive == 1)) // HORARIO DO BOSS - Todos os dias 23:20
		//		{
		//			// BOSS PARTE 1
		//			for (int w = BOSS1_INITIAL; w <= BOSS1_END; w++)
		//				mNPCGen.pList[w].MinuteGenerate = 3;
		//			// BOSS PARTE 2
		//			for (int x = BOSS1_INITIAL2; x <= BOSS1_END2; x++)
		//				mNPCGen.pList[x].MinuteGenerate = 3;
		//
		//			EspelhoLive = 0;
		//
		//			for (int i = MAX_USER; i < MAX_MOB; i++)
		//			{
		//				if (!strcmp(pMob[i].MOB.MobName, "Espelho RainhaG"))
		//					DeleteMob(i, 1);
		//			}
		//
		//			SendNotice("Ninguém foi confrontar a Rainha");
		//		}
		//#pragma endregion
		//#pragma region Boss 1 Castelo de Gelo Parte 3
		//		if ((when.tm_hour == 23 && when.tm_min == 30) && when.tm_sec >= 0 && when.tm_sec <= 2) // HORARIO DO BOSS - Todos os dias 23:30
		//		{
		//			for (int i = MAX_USER; i < MAX_MOB; i++)
		//			{
		//				if (!strcmp(pMob[i].MOB.MobName, "VeridRainhaG") || !strcmp(pMob[i].MOB.MobName, "Sombra Negra"))
		//				{
		//					if (mNPCGen.pList[pMob[i].GenerateIndex].CurrentNumMob > 0)
		//					{
		//						// BOSS PARTE 1
		//						for (int w = BOSS1_INITIAL; w <= BOSS1_END; w++)
		//							mNPCGen.pList[w].MinuteGenerate = 3;
		//						// BOSS PARTE 2
		//						for (int x = BOSS1_INITIAL2; x <= BOSS1_END2; x++)
		//							mNPCGen.pList[x].MinuteGenerate = 3;
		//
		//						EspelhoLive = 0;
		//
		//						DeleteMob(i, 1);
		//					}
		//				}
		//			}
		//			SendNotice("A quest do Gelo foi resetada!");
		//		}
		//#pragma endregion

#pragma region Portão Reset
		if ((when.tm_min == 29 || when.tm_min == 59) && when.tm_sec == 0)
		{
			DeleteMobMapa(13, 28);
			//ClearMapa(13, 28);//Portão Infernal
			ClearArea(1664, 3584, 1919, 3711);
			PartyPortao[0] = 0;
			TarantulaKilled = FALSE;
			RandBoss = 0;
			Lich_1 = 0;
			Lich_2 = 0;
			Lich_3 = 0;
			Lich_4 = 0;


		}
#pragma endregion

#pragma region >> Auto Restart de Logs
		if ((when.tm_min == 00) && when.tm_sec == 0)
		{
			StartSystemLog();
			StartChatLog();
			StartItemLog();
			CompositorLog();
			MobDropLogs();
			trade_item();
		}
#pragma endregion
#pragma region Pesa Reset
		if ((when.tm_min == 9 || when.tm_min == 29 || when.tm_min == 49) && when.tm_sec == 0)
		{
			DeleteMobMapa(9, 1);
			ClearMapa(9, 1);//Pesa A
			PartyPesa[2] = 0;

		}
		if ((when.tm_min == 4 || when.tm_min == 24 || when.tm_min == 44) && when.tm_sec == 0)
		{
			DeleteMobMapa(8, 2);
			ClearMapa(8, 2);//Pesa M
			PartyPesa[1] = 0;


		}

		if ((when.tm_min == 19 || when.tm_min == 39 || when.tm_min == 59) && when.tm_sec == 0)
		{
			DeleteMobMapa(10, 2);
			ClearMapa(10, 2);//Pesa N
			PartyPesa[0] = 0;


		}
#pragma endregion
		if (BatalhaRealStatus == 1) {
#pragma region Start Batalha Real
			if (when.tm_wday != 0 && when.tm_wday != 7 && when.tm_min == 0 && when.tm_sec == 0)
			{
				SendNotice("Registro para a Batalha Real iniciada !");
			}
#pragma region Start Batalha Real
			if (when.tm_min == 1 && when.tm_sec > 58)
			{
				SendNotice("Batalha Real! Restam [180] segundos para o fim do Registro ");
			}
#pragma region Start Batalha Real
			if (when.tm_min == 2 && when.tm_sec > 58)
			{
				SendNotice("Batalha Real! Restam [120] segundos para o fim do Registro ");
			}
#pragma region Start Batalha Real
			if (when.tm_min == 3 && when.tm_sec > 58)
			{
				SendNotice("Batalha Real! Restam [60] segundos para o fim do Registro ");
			}
#pragma region Start Batalha Real

			if ((p_BatalhaReal.start == false) && when.tm_min == 6)
			{
				if (BrState == 0)
				{
					MSG_Action sm;
					if (p_BatalhaReal.NumMembers >= 2)
					{
						SendNotice(strFmt("Batalha Real Iniciada - Total de jogadores na arena: [%d].", p_BatalhaReal.NumMembers));
						// i = maximo de player na batalha = 20
						for (int i = 0; i < 20; i++)
						{
							int rand_ = rand() % 100;
							if (rand_ <= 10)
								DoTeleport(p_BatalhaReal.Members[i].Id, 148, 4010);
							else if (rand_ <= 20)
								DoTeleport(p_BatalhaReal.Members[i].Id, 148, 4044);
							else if (rand_ <= 30)
								DoTeleport(p_BatalhaReal.Members[i].Id, 148, 4077);
							else if (rand_ <= 40)
								DoTeleport(p_BatalhaReal.Members[i].Id, 168, 4061);
							else if (rand_ <= 50)
								DoTeleport(p_BatalhaReal.Members[i].Id, 168, 4028);
							else if (rand_ <= 60)
								DoTeleport(p_BatalhaReal.Members[i].Id, 191, 4080);
							else if (rand_ <= 70)
								DoTeleport(p_BatalhaReal.Members[i].Id, 191, 4063);
							else if (rand_ <= 80)
								DoTeleport(p_BatalhaReal.Members[i].Id, 191, 4044);
							else if (rand_ <= 90)
								DoTeleport(p_BatalhaReal.Members[i].Id, 191, 4027);
							else
								DoTeleport(p_BatalhaReal.Members[i].Id, 191, 4010);

							pUser[p_BatalhaReal.Members[i].Id].Vidas = 3;

							p_BatalhaReal.start = true;
							BrState = 1;
							BrTime = 900;
						}
					}
					if (p_BatalhaReal.NumMembers <= 0)
					{
						SendNotice(strFmt("Batalha Real Cancelada por falta de jogadores - Total: [%d].", p_BatalhaReal.NumMembers));
						memset(&p_BatalhaReal, 0x0, sizeof(p_BatalhaReal));
						BrState = 0;
					}
				}
			}
#pragma endregion
			if (BrState == 1 && when.tm_min == 9 && when.tm_sec > 58)
			{
				snprintf(temp, sizeof(temp), "Penalidade Iniciada !!!");
				SendNoticeArea(temp, 140, 4000, 200, 4100);
			}
			if (BrState == 1 && when.tm_min >= 10 && when.tm_min <= 15)
			{
				SendDamage(142, 4007, 162, 4082);
				SendDamage(162, 4021, 174, 4034);
				SendDamage(174, 4007, 195, 4082);
				SendDamage(162, 4055, 174, 4082);
				SendEnvEffect(142, 4007, 162, 4082, 32, 0);
				SendEnvEffect(162, 4021, 174, 4034, 32, 0);
				SendEnvEffect(174, 4007, 195, 4082, 32, 0);
				SendEnvEffect(162, 4055, 174, 4082, 32, 0);
			}
#pragma region >> Resete arena real
			if (BrState == 1 && BrTime == 0 && p_BatalhaReal.start == true)
			{
				if (when.tm_min == 15)
				{
					ClearAreaTeleport(140, 4000, 200, 4100, 2133, 2147);
					SendNotice("Batalha Real Finalizada! - Não houve ganhadores");
					BrState = 0;
					BrTime = 0;
				}
			}
		}
#pragma region Pista de runas entrada
		if ((when.tm_min == 20 || when.tm_min == 40 || when.tm_min == 00) && PistaPlaying == false)
		{//Pista de Runas entrada

			Pista[4].Party[0].MobCount = 1;
			Pista[4].Party[1].MobCount = 1;
			Pista[4].Party[2].MobCount = 1;

			Pista[6].Party[0].MobCount = 100;

			Pista[1].Party[0].MobCount = 0;
			Pista[1].Party[1].MobCount = 0;
			Pista[1].Party[2].MobCount = 0;

			Pista[3].Party[0].MobCount = 1;
			Pista[3].Party[1].MobCount = 1;
			Pista[3].Party[2].MobCount = 1;

			for (int s = 0; s < 7; s++)
			{
				for (int t = 0; t < 3; t++)
				{
					if (Pista[s].Party[t].LeaderID == 0 || strcmp(pMob[Pista[s].Party[t].LeaderID].MOB.MobName, Pista[s].Party[t].LeaderName) != 0)
						continue;

					if (checkCord(Pista[s].Party[t].LeaderID, 3275, 1674, 3317, 1711) == FALSE)
						continue;

					if (pMob[Pista[s].Party[t].LeaderID].Leader != -1 && pMob[Pista[s].Party[t].LeaderID].Leader)
						continue;

					DoTeleport(Pista[s].Party[t].LeaderID, PistaPos[Pista[s].Party[t].Sala][t][0], PistaPos[Pista[s].Party[t].Sala][t][1]);


					for (int i = 0; i < MAX_PARTY; i++)
					{
						int partyconn = pMob[Pista[s].Party[t].LeaderID].PartyList[i];

						if (partyconn <= 0 || partyconn >= MAX_USER) continue;

						if (partyconn > 0 && partyconn < MAX_USER && partyconn != Pista[s].Party[t].LeaderID && pUser[partyconn].Mode == USER_PLAY)
						{
							if (checkCord(partyconn, 3275, 1674, 3317, 1711) == TRUE)
							{
								DoTeleport(partyconn, PistaPos[Pista[s].Party[t].Sala][t][0], PistaPos[Pista[s].Party[t].Sala][t][1]);

							}
						}
					}

					//Pista+0 Lich
					if (s == 0 && t == 0)
						GenerateMob(RUNEQUEST_LV0_LICH2, 0, 0);

					if (s == 0 && t == 1)
						GenerateMob(RUNEQUEST_LV0_LICH1, 0, 0);

					//Pista +1 Torre
					if (s == 1)
					{
						GenerateMob(RUNEQUEST_LV1_TORRE1, 3358, 1582);
						GenerateMob(RUNEQUEST_LV1_TORRE2, 3386, 1548);
						GenerateMob(RUNEQUEST_LV1_TORRE3, 3418, 1582);

						for (int generateindex = RUNEQUEST_LV1_MOB_INITIAL; generateindex <= RUNEQUEST_LV1_MOB_END; generateindex++)
							GenerateMob(generateindex, 0, 0);
					}


					if (s == 2)
						GenerateMob(RUNEQUEST_LV2_MOB_BOSS, 0, 0);

					if (s == 4)
						Pista[s].Party[t].MobCount = 6;

					if (s == 4 && t == 0)
					{
						for (int generateindex = RUNEQUEST_LV4_MOB_INITIAL; generateindex <= RUNEQUEST_LV4_MOB_END; generateindex++)
							GenerateMob(generateindex, 0, 0);
					}
				}
			}

			PistaPlaying = true;
		}
#pragma endregion
#pragma region Pista de runas saída
		if ((when.tm_min == 15 || when.tm_min == 35 || when.tm_min == 55) && PistaPlaying == true)
		{//Pista de Runas saida

			for (int c = MAX_USER; c < MAX_MOB; c++)
			{
				if (pMob[c].Mode == USER_EMPTY)
					continue;

				if (pMob[c].TargetX < 3310 || pMob[c].TargetX > 3588 || pMob[c].TargetY < 1005 || pMob[c].TargetY > 1663)
					continue;

				DeleteMob(c, 3);
			}

			for (int x = 0; x < MAX_USER; x++)
			{
				if (pUser[x].Mode != USER_PLAY)
					continue;

				if (pMob[x].Mode == USER_EMPTY)
					continue;

				if (pMob[x].TargetX < 3310 || pMob[x].TargetX > 3588 || pMob[x].TargetY < 1005 || pMob[x].TargetY > 1663)
					continue;

				if (pMob[x].MOB.CurrentScore.Hp <= 0)
				{
					pMob[x].MOB.CurrentScore.Hp = 1;

					SendScore(x);
				}

				DoTeleport(x, 3294, rand() % 1 == 0 ? 1701 : 1686);
				pUser[x].Ingame.CheckPista = FALSE;
			}
			//Pista +1 - Torre

			//Grupo 1 ganhou
			if (Pista[1].Party[0].MobCount > Pista[1].Party[1].MobCount && Pista[1].Party[0].MobCount > Pista[1].Party[2].MobCount)
			{
				if (Pista[1].Party[0].MobCount != 0) {
					if (Pista[1].Party[0].LeaderID != 0 && strcmp(pMob[Pista[1].Party[0].LeaderID].MOB.MobName, Pista[1].Party[0].LeaderName) == 0)
					{
						STRUCT_ITEM Runa;
						memset(&Runa, 0, sizeof(STRUCT_ITEM));

						Runa.sIndex = PistaRune[1][rand() % 5]; // aqui tambem tem que estar 6 por conta da matriz

						if (Pista[1].Party[0].LeaderID > 0 && Pista[1].Party[0].LeaderID < MAX_USER) {
								PutItem(Pista[1].Party[0].LeaderID, &Runa);
						}

						for (int i = 0; i < MAX_PARTY; i++)
						{
							int partymember = pMob[Pista[1].Party[0].LeaderID].PartyList[i];

							if (partymember >= MAX_USER) continue;

							if (pUser[partymember].Mode != USER_PLAY)
								continue;

							Runa.sIndex = PistaRune[1][rand() % 5];
							PutItem(partymember, &Runa);
						}

						STRUCT_ITEM Prize;
						memset(&Prize, 0, sizeof(STRUCT_ITEM));

						Prize.sIndex = 5134;
						Prize.stEffect[0].cEffect = 43;
						Prize.stEffect[0].cValue = 2;

						PutItem(Pista[1].Party[0].LeaderID, &Prize);
						SystemLog("-system", "-", 0, "etc,questRune complete +1 party1");
					}
				}
			}

			//Grupo 2 ganhou
			else if (Pista[1].Party[1].MobCount > Pista[1].Party[0].MobCount && Pista[1].Party[1].MobCount > Pista[1].Party[2].MobCount)
			{
				if (Pista[1].Party[1].MobCount != 0) {
					if (Pista[1].Party[1].LeaderID != 0 && strcmp(pMob[Pista[1].Party[1].LeaderID].MOB.MobName, Pista[1].Party[1].LeaderName) == 0)
					{
						STRUCT_ITEM Runa;
						memset(&Runa, 0, sizeof(STRUCT_ITEM));

						Runa.sIndex = PistaRune[1][rand() % 5];

						if (Pista[1].Party[1].LeaderID > 0 && Pista[1].Party[1].LeaderID < MAX_USER) {
								PutItem(Pista[1].Party[1].LeaderID, &Runa);
						}

						for (int i = 0; i < MAX_PARTY; i++)
						{
							int partymember = pMob[Pista[1].Party[1].LeaderID].PartyList[i];

							if (partymember >= MAX_USER) continue;

							if (pUser[partymember].Mode != USER_PLAY)
								continue;

							Runa.sIndex = PistaRune[1][rand() % 5];
							PutItem(partymember, &Runa);
						}

						STRUCT_ITEM Prize;
						memset(&Prize, 0, sizeof(STRUCT_ITEM));

						Prize.sIndex = 5134;
						Prize.stEffect[0].cEffect = 43;
						Prize.stEffect[0].cValue = 2;

						PutItem(Pista[1].Party[1].LeaderID, &Prize);
						SystemLog("-system", "-", 0, "etc,questRune complete +1 party2");
					}
				}
			}

			//Grupo 3 ganhou
			else if (Pista[1].Party[2].MobCount > Pista[1].Party[0].MobCount && Pista[1].Party[2].MobCount > Pista[1].Party[1].MobCount)
			{
				if (Pista[1].Party[2].MobCount != 0) {
					if (Pista[1].Party[2].LeaderID != 0 && strcmp(pMob[Pista[1].Party[2].LeaderID].MOB.MobName, Pista[1].Party[2].LeaderName) == 0)
					{
						STRUCT_ITEM Runa;
						memset(&Runa, 0, sizeof(STRUCT_ITEM));

						Runa.sIndex = PistaRune[1][rand() % 5];

						if (Pista[1].Party[2].LeaderID > 0 && Pista[1].Party[2].LeaderID < MAX_USER) {
								PutItem(Pista[1].Party[2].LeaderID, &Runa);
						}

						for (int i = 0; i < MAX_PARTY; i++)
						{
							int partymember = pMob[Pista[1].Party[2].LeaderID].PartyList[i];

							if (partymember >= MAX_USER) continue;

							if (pUser[partymember].Mode != USER_PLAY)
								continue;

							Runa.sIndex = PistaRune[1][rand() % 5];
							PutItem(partymember, &Runa);
						}

						STRUCT_ITEM Prize;
						memset(&Prize, 0, sizeof(STRUCT_ITEM));

						Prize.sIndex = 5134;
						Prize.stEffect[0].cEffect = 43;
						Prize.stEffect[0].cValue = 2;

						PutItem(Pista[1].Party[2].LeaderID, &Prize);
						SystemLog("-system", "-", 0, "etc,questRune complete +1 party3");
					}
				}
			}

			//Pista +3 - Sulrang

			//Grupo 1 ganhou
			if (Pista[3].Party[0].MobCount > Pista[3].Party[1].MobCount && Pista[3].Party[0].MobCount > Pista[3].Party[2].MobCount)
			{
				if (Pista[3].Party[0].MobCount != 0) {
					if (Pista[3].Party[0].LeaderID != 0 && strcmp(pMob[Pista[3].Party[0].LeaderID].MOB.MobName, Pista[3].Party[0].LeaderName) == 0)
					{
						STRUCT_ITEM Runa;
						memset(&Runa, 0, sizeof(STRUCT_ITEM));

						Runa.sIndex = PistaRune[3][rand() % 5];

						if (Pista[3].Party[0].LeaderID > 0 && Pista[3].Party[0].LeaderID < MAX_USER)
							PutItem(Pista[3].Party[0].LeaderID, &Runa);

						for (int i = 0; i < MAX_PARTY; i++)
						{
							int partymember = pMob[Pista[3].Party[0].LeaderID].PartyList[i];

							if (partymember >= MAX_USER) continue;

							if (pUser[partymember].Mode != USER_PLAY)
								continue;

							Runa.sIndex = PistaRune[3][rand() % 5];
							PutItem(partymember, &Runa);
						}

						STRUCT_ITEM Prize;
						memset(&Prize, 0, sizeof(STRUCT_ITEM));

						Prize.sIndex = 5134;
						Prize.stEffect[0].cEffect = 43;
						Prize.stEffect[0].cValue = 4;

						PutItem(Pista[3].Party[0].LeaderID, &Prize);
						SystemLog("-system", "-", 0, "etc,questRune complete +3 party1");
					}
				}
			}

			//Grupo 2 ganhou
			else if (Pista[3].Party[1].MobCount > Pista[3].Party[0].MobCount && Pista[3].Party[1].MobCount > Pista[3].Party[2].MobCount)
			{
				if (Pista[3].Party[1].MobCount != 0) {
					if (Pista[3].Party[1].LeaderID != 0 && strcmp(pMob[Pista[3].Party[1].LeaderID].MOB.MobName, Pista[3].Party[1].LeaderName) == 0)
					{
						STRUCT_ITEM Runa;
						memset(&Runa, 0, sizeof(STRUCT_ITEM));

						Runa.sIndex = PistaRune[3][rand() % 5];

						if (Pista[3].Party[1].LeaderID > 0 && Pista[3].Party[1].LeaderID < MAX_USER)
							PutItem(Pista[3].Party[1].LeaderID, &Runa);

						for (int i = 0; i < MAX_PARTY; i++)
						{
							int partymember = pMob[Pista[3].Party[1].LeaderID].PartyList[i];

							if (partymember >= MAX_USER) continue;

							if (pUser[partymember].Mode != USER_PLAY)
								continue;

							Runa.sIndex = PistaRune[3][rand() % 5];
							PutItem(partymember, &Runa);
						}

						STRUCT_ITEM Prize;
						memset(&Prize, 0, sizeof(STRUCT_ITEM));

						Prize.sIndex = 5134;
						Prize.stEffect[0].cEffect = 43;
						Prize.stEffect[0].cValue = 4;

						PutItem(Pista[3].Party[3].LeaderID, &Prize);
						SystemLog("-system", "-", 0, "etc,questRune complete +3 party2");
					}
				}
			}

			//Grupo 3 ganhou
			else if (Pista[3].Party[2].MobCount > Pista[3].Party[0].MobCount && Pista[3].Party[2].MobCount > Pista[3].Party[1].MobCount)
			{
				if (Pista[3].Party[2].MobCount != 0) {
					if (Pista[3].Party[2].LeaderID != 0 && strcmp(pMob[Pista[3].Party[2].LeaderID].MOB.MobName, Pista[3].Party[2].LeaderName) == 0)
					{
						STRUCT_ITEM Runa;
						memset(&Runa, 0, sizeof(STRUCT_ITEM));

						Runa.sIndex = PistaRune[3][rand() % 5];

						if (Pista[3].Party[2].LeaderID > 0 && Pista[3].Party[2].LeaderID < MAX_USER)
							PutItem(Pista[3].Party[2].LeaderID, &Runa);

						for (int i = 0; i < MAX_PARTY; i++)
						{
							int partymember = pMob[Pista[3].Party[2].LeaderID].PartyList[i];

							if (partymember >= MAX_USER) continue;

							if (pUser[partymember].Mode != USER_PLAY)
								continue;

							Runa.sIndex = PistaRune[3][rand() % 5];
							PutItem(partymember, &Runa);
						}

						STRUCT_ITEM Prize;
						memset(&Prize, 0, sizeof(STRUCT_ITEM));

						Prize.sIndex = 5134;
						Prize.stEffect[0].cEffect = 43;
						Prize.stEffect[0].cValue = 4;

						PutItem(Pista[3].Party[2].LeaderID, &Prize);
						SystemLog("-system", "-", 0, "etc,questRune complete +3 party3");
					}
				}
			}

			for (int x = 0; x < 7; x++)
			{
				for (int z = 0; z < 3; z++)
				{
					Pista[x].Party[z].LeaderID = 0;
					strncpy(Pista[x].Party[z].LeaderName, " ", 16);
					Pista[x].Party[z].MobCount = 0;
					Pista[x].Party[z].Sala = 0;
				}
			}
			PistaPlaying = false;

		}
#pragma endregion

#pragma region Portao Infernal Start
		if (GetUserInArea(1664, 3584, 1919, 3711, temp) && (when.tm_min == 4 && when.tm_sec == 2 || when.tm_min == 34 && when.tm_sec == 2))
		{
			MSG_STANDARDPARM sm;
			memset(&sm, 0, sizeof(MSG_STANDARDPARM));

			sm.Type = _MSG_StartTime;
			sm.ID = ESCENE_FIELD;
			sm.Size = sizeof(MSG_STANDARDPARM);
			sm.Parm = 1500;

			MapaMulticast(13, 28, (MSG_STANDARD*)&sm, 0);

			int _rand = rand() % 100;
			int __rand = rand() % 100;
			int ___rand = rand() % 100;

			if (_rand < 50)
				CreateMob("Tarantula", 1754, 3674, "npc", 0);
			else
				CreateMob("Tarantula", 1728, 3646, "npc", 0);

			if (__rand < 50)
				CreateMob("Tarantula", 1703, 3635, "npc", 0);
			else
				CreateMob("Tarantula", 1752, 3618, "npc", 0);

			if (___rand < 25)
				GenerateMob(CTARANTULA, 1754, 3674);
			else if (___rand >= 25 && ___rand < 50)
				GenerateMob(CTARANTULA, 1728, 3646);
			else if (___rand >= 50 && ___rand < 75)
				GenerateMob(CTARANTULA, 1703, 3635);
			else
				GenerateMob(CTARANTULA, 1752, 3618);
		}
#pragma endregion
#pragma region Pesa Start
		if (GetUserInArea(1152, 128, 1280, 256, temp) && (when.tm_min == 14 && when.tm_sec == 0 || when.tm_min == 34 && when.tm_sec == 0 || when.tm_min == 54 && when.tm_sec == 0))
		{
			MSG_STANDARDPARM sm;
			memset(&sm, 0, sizeof(MSG_STANDARDPARM));

			sm.Type = _MSG_StartTime;
			sm.ID = ESCENE_FIELD;
			sm.Size = sizeof(MSG_STANDARDPARM);
			sm.Parm = 900;

			MapaMulticast(9, 1, (MSG_STANDARD*)&sm, 0);

			//Pesa A
			for (int i = NIGHTMARE_A_INITIAL; i <= NIGHTMARE_A_END; i++)
				GenerateMob(i, 0, 0);

		}

		if (GetUserInArea(1024, 256, 1152, 384, temp) > 0 && (when.tm_min == 9 && when.tm_sec == 0 || when.tm_min == 29 && when.tm_sec == 0 || when.tm_min == 49 && when.tm_sec == 0))
		{
			MSG_STANDARDPARM sm;
			memset(&sm, 0, sizeof(MSG_STANDARDPARM));

			sm.Type = _MSG_StartTime;
			sm.ID = ESCENE_FIELD;
			sm.Size = sizeof(MSG_STANDARDPARM);
			sm.Parm = 900;

			MapaMulticast(8, 2, (MSG_STANDARD*)&sm, 0);

			//Pesa M
			for (int i = NIGHTMARE_M_INITIAL; i <= NIGHTMARE_M_END; i++)
				GenerateMob(i, 0, 0);


		}

		if (GetUserInArea(1280, 256, 1408, 384, temp) > 0 && (when.tm_min == 24 && when.tm_sec == 0 || when.tm_min == 44 && when.tm_sec == 0 || when.tm_min == 4 && when.tm_sec == 0))
		{
			MSG_STANDARDPARM sm;
			memset(&sm, 0, sizeof(MSG_STANDARDPARM));

			sm.Type = _MSG_StartTime;
			sm.ID = ESCENE_FIELD;
			sm.Size = sizeof(MSG_STANDARDPARM);
			sm.Parm = 900;

			MapaMulticast(10, 2, (MSG_STANDARD*)&sm, 0);

			//Pesa N
			for (int i = NIGHTMARE_N_INITIAL; i <= NIGHTMARE_N_END; i++)
				GenerateMob(i, 0, 0);

		}
#pragma endregion
#pragma region Avisos
		/*if ((when.tm_min == 40) && when.tm_sec == 0)
		{
			SendNotice("Seja bem vindo");
			return;
		}*/

		/*if ((when.tm_min == 40) && when.tm_sec == 10)
		{
			SendNotice("Você é NOVATO por aqui ? Digite /novato");
			return;
		}*/

		/*if ((when.tm_min == 40) && when.tm_sec == 20)
		{
			SendNotice("Bom Jogo a Todos!");
			return;
		}*/
#pragma endregion
	}
#pragma endregion
#pragma region Item Decay and Quest Event Time
	if ((SecCounter % 2) == 0)
		ProcessDecayItem();

	int UsersDie = 0;

	int Sec4 = SecCounter % 4;

	if (SecCounter % 4 == 0)
	{
		ProcessRanking();

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if (WaterClear1[i][j] > 1)
					WaterClear1[i][j]--;

				else if (WaterClear1[i][j] == 1 && j <= 7)
				{
					ClearAreaTeleport(WaterScrollPosition[i][j][0] - 8, WaterScrollPosition[i][j][1] - 8, WaterScrollPosition[i][j][0] + 8, WaterScrollPosition[i][j][1] + 8, 1965, 1769);
					WaterClear1[i][j] = 0;
				}
				else if (WaterClear1[i][j] == 1 && j > 7)
				{
					ClearAreaTeleport(WaterScrollPosition[i][j][0] - 12, WaterScrollPosition[i][j][1] - 12, WaterScrollPosition[i][j][0] + 12, WaterScrollPosition[i][j][1] + 12, 1965, 1769);
					WaterClear1[i][j] = 0;
				}
			}
		}

		if (CartaTime > 1)
			CartaTime--;

		if (CartaTime == 1)
		{
			CartaTime = 60;

			if (CartaSala == 1)
				ClearAreaTeleport(778, 3652, 832, 3698, CartaPos[1][0], CartaPos[1][1]);

			else if (CartaSala == 2)
				ClearAreaTeleport(836, 3652, 890, 3698, CartaPos[2][0], CartaPos[2][1]);

			else if (CartaSala == 3)
				ClearAreaTeleport(834, 3595, 889, 3645, CartaPos[3][0], CartaPos[3][1]);


			if (CartaSala == 4)
			{
				ClearArea(776, 3595, 834, 3648);
				CartaTime = 0;
				CartaSala = 0;
			}

			else
				CartaSala++;

			MSG_STANDARDPARM sm;

			sm.Type = _MSG_StartTime;
			sm.ID = ESCENE_FIELD;
			sm.Size = sizeof(MSG_STANDARDPARM);
			sm.Parm = CartaTime * 2;

			MapaMulticast(6, 28, (MSG_STANDARD*)&sm, 0);
		}
	}
#pragma endregion

	CCastleZakum::ProcessSecTimer();
	//CCubo::ProcessSecTimer();

	int Sec16 = SecCounter % 16;
	int Sec32 = SecCounter % 32;

	int i = 0;

	for (i = 1; i < MAX_USER; i++)
	{
		/*if (i % 32 == Sec32 && pUser[i].Mode && pUser[i].Mode != USER_SAVING4QUIT)
			CheckIdle(i);*/

		if (i % 16 == Sec16 && pMob[i].MOB.CurrentScore.Hp > 0 && pUser[i].Mode == USER_PLAY)
		{
			RegenMob(i);
			ProcessAffect(i);
			UsersDie++;
		}

	}

	if (BrState == 2 && i % 8 == Sec16 && BRItem > 0)
	{
		if (BrMod < 9)
		{
			if (BrMod >= 7)
			{
				SendDamage(2608, 1708, 2622, 1711);
				SendDamage(2608, 1739, 2622, 1743);
				SendEnvEffect(2608, 1708, 2622, 1711, 32, 0);
				SendEnvEffect(2608, 1739, 2622, 1743, 32, 0);
			}
		}
		else
		{
			SendDamage(2608, 1708, 2622, 1718);
			SendDamage(2608, 1733, 2622, 1743);
			SendEnvEffect(2608, 1708, 2622, 1718, 32, 0);
			SendEnvEffect(2608, 1733, 2622, 1743, 32, 0);
		}
	}

	if (RankingProgress <= 1) // dano em area apartir de certo tempo
	{
		if (RankingProgress == 1 && SecCounter % 6 == 0)
		{
			if (SecCounter % 6 == 0)
			{
				SendDamage(2124, 2140, 2147, 2143);
				SendDamage(2124, 2152, 2147, 2155);
				SendDamage(2141, 2140, 2147, 2155);
				SendDamage(2124, 2140, 2129, 2155);
				SendEnvEffect(2124, 2140, 2147, 2143, 32, 0);
				SendEnvEffect(2124, 2152, 2147, 2155, 32, 0);
				SendEnvEffect(2141, 2140, 2147, 2155, 32, 0);
				SendEnvEffect(2124, 2140, 2130, 2155, 32, 0);
			}
		}
	}

	if (SecCounter % 6 == 0)
	{
		SendEnvEffectKingdom(1050, 2108, 1070, 2146, 32, 0, REINO_BLUE);
		SendEnvEffectKingdom(1066, 2133, 1098, 2146, 32, 0, REINO_BLUE);
		SendDamageKingdom(1050, 2108, 1070, 2146, REINO_BLUE);
		SendDamageKingdom(1066, 2133, 1098, 2146, REINO_BLUE);

		SendEnvEffectKingdom(1230, 1947, 1245, 1988, 32, 0, REINO_RED);
		SendEnvEffectKingdom(1204, 1948, 1231, 1962, 32, 0, REINO_RED);
		SendDamageKingdom(1230, 1947, 1245, 1988, REINO_RED);
		SendDamageKingdom(1204, 1948, 1231, 1962, REINO_RED);
	}

	if (SecCounter % 5 == 0)
	{
		SendEnvEffectLeader(3436, 1285, 3450, 1299, 32, 0);
		SendDamageLeader(3436, 1285, 3450, 1299);
		SendEnvEffectLeader(3368, 1285, 3382, 1299, 32, 0);
		SendDamageLeader(3368, 1285, 3382, 1299);
		SendEnvEffectLeader(3384, 1302, 3398, 1316, 32, 0);
		SendDamageLeader(3384, 1302, 3398, 1316);
		SendEnvEffectLeader(3438, 1320, 3452, 1334, 32, 0);
		SendDamageLeader(3438, 1320, 3452, 1334);
		SendEnvEffectLeader(3369, 1320, 3383, 1334, 32, 0);
		SendDamageLeader(3369, 1320, 3383, 1334);
		SendEnvEffectLeader(3385, 1336, 3399, 1350, 32, 0);
		SendDamageLeader(3385, 1336, 3399, 1350);
		SendEnvEffectLeader(3402, 1353, 3416, 1367, 32, 0);
		SendDamageLeader(3402, 1353, 3416, 1367);
		SendEnvEffectLeader(3436, 1371, 3450, 1385, 32, 0);
		SendDamageLeader(3436, 1371, 3450, 1385);
		SendEnvEffectLeader(3368, 1371, 3382, 1385, 32, 0);
		SendDamageLeader(3368, 1371, 3382, 1385);
		SendEnvEffectLeader(3402, 1387, 3416, 1401, 32, 0);
		SendDamageLeader(3402, 1387, 3416, 1401);
		SendEnvEffectLeader(3420, 1286, 3434, 1300, 32, 0);
		SendDamageLeader(3420, 1286, 3434, 1300);
		SendEnvEffectLeader(3351, 1286, 3365, 1300, 32, 0);
		SendDamageLeader(3351, 1286, 3365, 1300);
		SendEnvEffectLeader(3402, 1302, 3416, 1316, 32, 0);
		SendDamageLeader(3402, 1302, 3416, 1316);
		SendEnvEffectLeader(3420, 1320, 3434, 1334, 32, 0);
		SendDamageLeader(3420, 1320, 3434, 1334);
		SendEnvEffectLeader(3371, 1337, 3385, 1351, 32, 0);
		SendDamageLeader(3371, 1337, 3385, 1351);
		SendEnvEffectLeader(3436, 1337, 3450, 1351, 32, 0);
		SendDamageLeader(3436, 1337, 3450, 1351);
		SendEnvEffectLeader(3385, 1353, 3399, 1367, 32, 0);
		SendDamageLeader(3385, 1353, 3399, 1367);
		SendEnvEffectLeader(3352, 1370, 3366, 1384, 32, 0);
		SendDamageLeader(3352, 1370, 3366, 1384);
		SendEnvEffectLeader(3419, 1370, 3433, 1384, 32, 0);
		SendDamageLeader(3419, 1370, 3433, 1384);
		SendEnvEffectLeader(3385, 1387, 3399, 1401, 32, 0);
		SendDamageLeader(3385, 1387, 3399, 1401);
		SendEnvEffectLeader(3402, 1286, 3416, 1300, 32, 0);
		SendDamageLeader(3402, 1286, 3416, 1300);
		SendEnvEffectLeader(3352, 1302, 3366, 1316, 32, 0);
		SendDamageLeader(3352, 1302, 3366, 1316);
		SendEnvEffectLeader(3420, 1302, 3434, 1316, 32, 0);
		SendDamageLeader(3420, 1302, 3434, 1316);
		SendEnvEffectLeader(3401, 1320, 3415, 1334, 32, 0);
		SendDamageLeader(3401, 1320, 3415, 1334);
		SendEnvEffectLeader(3420, 1336, 3434, 1350, 32, 0);
		SendDamageLeader(3420, 1336, 3434, 1350);
		SendEnvEffectLeader(3436, 1353, 3450, 1367, 32, 0);
		SendDamageLeader(3436, 1353, 3450, 1367);
		SendEnvEffectLeader(3368, 1353, 3382, 1367, 32, 0);
		SendDamageLeader(3368, 1353, 3382, 1367);
		SendEnvEffectLeader(3401, 1370, 3415, 1384, 32, 0);
		SendDamageLeader(3401, 1370, 3415, 1384);
		SendEnvEffectLeader(3435, 1387, 3449, 1401, 32, 0);
		SendDamageLeader(3435, 1387, 3449, 1401);
		SendEnvEffectLeader(3369, 1387, 3383, 1401, 32, 0);
		SendDamageLeader(3369, 1387, 3383, 1401);
		SendEnvEffectLeader(3387, 1285, 3401, 1299, 32, 0);
		SendDamageLeader(3387, 1285, 3401, 1299);
		SendEnvEffectLeader(3368, 1302, 3382, 1316, 32, 0);
		SendDamageLeader(3368, 1302, 3382, 1316);
		SendEnvEffectLeader(3436, 1302, 3450, 1316, 32, 0);
		SendDamageLeader(3436, 1302, 3450, 1316);
		SendEnvEffectLeader(3384, 1319, 3398, 1333, 32, 0);
		SendDamageLeader(3384, 1319, 3398, 1333);
		SendEnvEffectLeader(3402, 1335, 3416, 1349, 32, 0);
		SendDamageLeader(3402, 1335, 3416, 1349);
		SendEnvEffectLeader(3419, 1353, 3433, 1367, 32, 0);
		SendDamageLeader(3419, 1353, 3433, 1367);
		SendEnvEffectLeader(3352, 1353, 3366, 1367, 32, 0);
		SendDamageLeader(3352, 1353, 3366, 1367);
		SendEnvEffectLeader(3385, 1370, 3399, 1384, 32, 0);
		SendDamageLeader(3385, 1370, 3399, 1384);
		SendEnvEffectLeader(3419, 1387, 3433, 1401, 32, 0);
		SendDamageLeader(3419, 1387, 3433, 1401);
		SendEnvEffectLeader(3352, 1387, 3366, 1401, 32, 0);
		SendDamageLeader(3352, 1387, 3366, 1401);
		SendEnvEffectLeader(3335, 1286, 3349, 1300, 32, 0);
		SendDamageLeader(3335, 1286, 3349, 1300);
		SendEnvEffectLeader(3335, 1302, 3349, 1316, 32, 0);
		SendDamageLeader(3335, 1302, 3349, 1316);
		SendEnvEffectLeader(3335, 1354, 3349, 1368, 32, 0);
		SendDamageLeader(3335, 1354, 3349, 1368);
		SendEnvEffectLeader(3335, 1371, 3349, 1385, 32, 0);
		SendDamageLeader(3335, 1371, 3349, 1385);
	}

	for (int k = 0; k < MAX_MOB_MERC; k++)
	{
		if (pMobMerc[k].RenewTime == 0 || pMobMerc[k].RebornTime == 0 || pMobMerc[k].GenerateIndex == 0)
			continue;

		if (SecCounter % pMobMerc[k].RenewTime == 0)
			memmove_s(pMobMerc[k].Stock, sizeof(pMobMerc[k].Stock), pMobMerc[k].MaxStock, sizeof(pMobMerc[k].Stock));

		if (SecCounter % pMobMerc[k].RebornTime == 0)
			GenerateMob(pMobMerc[k].GenerateIndex, 0, 0);
	}

	int Sec6 = SecCounter % 6;

#pragma region Movimento / fala dos NPCS 
	int initial = Sec6 + MAX_USER;
	for (int index = initial; index < MAX_MOB; index += 6)
	{
		int Mode = pMob[index].Mode;
		int Clan = pMob[index].MOB.Clan;

		if (Mode)
		{
			if (Mode == MOB_IDLE)
			{
				if (pMob[index].MOB.CurrentScore.Hp <= 0)
				{
					//Log("err,standingby processer delete hp zero mob", "-system", 0);
					DeleteMob(index, 1);
					continue;
				}
				ProcessAffect(index);
				pMobGrid[pMob[index].TargetY][pMob[index].TargetX] = index;
			}

			if (Mode == MOB_PEACE)
			{
				int chp = pMob[index].MOB.CurrentScore.Hp;
				if (chp <= 0)
				{
					//Log("err,standingby processer delete hp zero mob", "-system", 0);
					DeleteMob(index, 1);
					continue;
				}

				ProcessAffect(index);

				if (pMob[index].GenerateIndex != RUNEQUEST_LV6_MOB_BOSS && pMob[index].TargetX >= 3423 && pMob[index].TargetX <= 3442 && pMob[index].TargetY >= 1492 && pMob[index].TargetY <= 1511)
				{
					if (pMob[index].GenerateIndex >= RUNEQUEST_LV6_MOB_INITIAL2 && pMob[index].GenerateIndex <= RUNEQUEST_LV6_MOB_END2)
					{
						if (Pista[6].Party[0].MobCount < 100 && Pista[6].Party[0].MobCount != 0)
							Pista[6].Party[0].MobCount++;
					}

					DeleteMob(index, 3);
					continue;
				}
				int Progress = pMob[index].SegmentProgress;

				if (Progress < 0 || Progress > MAX_SEGMENT)
				{
					pMob[index].SegmentProgress = 0;
					Progress = 0;
				}
				int Processor = pMob[index].StandingByProcessor();

				if (Processor & 0x10000000)
				{
					int Target = Processor & 0xFFFFFFF;

					SetBattle(index, Processor & 0xFFFFFFF);

					int Leader = pMob[index].Leader;

					if (Leader <= 0)
						Leader = index;

					for (int l = 0; l < MAX_PARTY; ++l)
					{
						int party = pMob[Leader].PartyList[l];

						if (party > MAX_USER)
						{
							if (pMob[party].Mode && pMob[party].MOB.CurrentScore.Hp > 0)
								SetBattle(party, Target);

							else
							{
								if (pMob[party].Mode)
									DeleteMob(party, 1);

								pMob[Leader].PartyList[l] = 0;
							}
						}
					}

					for (int l = 0; l < MAX_PARTY; ++l)
					{
						int party = pMob[Leader].Evocations[l];

						if (party > MAX_USER)
						{
							if (pMob[party].Mode && pMob[party].MOB.CurrentScore.Hp > 0)
								SetBattle(party, Target);

							else
							{
								if (pMob[party].Mode)
									DeleteMob(party, 1);

								pMob[Leader].Evocations[l] = 0;
							}
						}
					}

					if (Target < MAX_USER)
					{
						int leader = pMob[Target].Leader;

						if (leader <= 0)
							leader = Target;

						for (int n = 0; n < MAX_PARTY; n++)
						{
							int party = pMob[leader].PartyList[n];
							if (party > MAX_USER)
							{
								if (pMob[party].Mode && pMob[party].MOB.CurrentScore.Hp > 0)
									SetBattle(party, index);

								else
								{
									if (pMob[party].Mode)
										DeleteMob(party, 1);

									pMob[leader].PartyList[n] = 0;
								}
							}
						}

						for (int n = 0; n < MAX_PARTY; n++)
						{
							int party = pMob[leader].Evocations[n];
							if (party > MAX_USER)
							{
								if (pMob[party].Mode && pMob[party].MOB.CurrentScore.Hp > 0)
									SetBattle(party, index);

								else
								{
									if (pMob[party].Mode)
										DeleteMob(party, 1);

									pMob[leader].Evocations[n] = 0;
								}
							}
						}
					}
				}
				else
				{
					if (Processor & 1)
					{
						//SendSay(index, "Processor 0x1");
						MSG_Action sm;

						if (GetEmptyMobGrid(index, &pMob[index].NextX, &pMob[index].NextY) == FALSE)
							continue;

						GetAction(index, pMob[index].NextX, pMob[index].NextY, (MSG_Action*)&sm);

						if (pMob[index].NextX == pMob[index].TargetX && pMob[index].NextY == pMob[index].TargetY)
							continue;

						sm.Speed = BASE_GetSpeed(&pMob[index].MOB.CurrentScore);
						sm.Effect = 0;

						GridMulticast(index, pMob[index].NextX, pMob[index].NextY, (MSG_STANDARD*)&sm);

						int progres = pMob[index].SegmentProgress;

						if (Progress != progres)
						{
							if (progres >= 0 && progres < MAX_SEGMENT && pMob[index].GenerateIndex >= 0 && pMob[index].GenerateIndex < MAX_NPCGENERATOR && mNPCGen.pList[pMob[index].GenerateIndex].SegmentAction[Progress][0])
								SendSay(index, mNPCGen.pList[pMob[index].GenerateIndex].SegmentAction[Progress]);
						}

						if (pMob[index].GenerateIndex >= RUNEQUEST_LV2_MOB_INITIAL && pMob[index].GenerateIndex <= RUNEQUEST_LV2_MOB_END)
						{
							if (pMob[index].TargetX >= 3373 && pMob[index].TargetX <= 3407 && pMob[index].TargetY >= 1420 && pMob[index].TargetY <= 1453)
								DeleteMob(index, 3);
						}
					}
					if (Processor & 0x10)
					{
						//SendSay(index, "Processor 0x10");
						int progres = pMob[index].SegmentProgress;

						if (Progress != progres)
						{
							if (progres >= 0 && progres < MAX_SEGMENT && pMob[index].GenerateIndex >= 0 && pMob[index].GenerateIndex < MAX_NPCGENERATOR && mNPCGen.pList[pMob[index].GenerateIndex].FleeAction[Progress][0])
								SendSay(index, mNPCGen.pList[pMob[index].GenerateIndex].FleeAction[Progress]);
						}
					}
					else
					{
						if (Processor & 0x100)
						{
							DeleteMob(index, 3);
							continue;
						}
						if (Processor & 0x1000)
						{
							//SendSay(index, "Processor 0x1000");
							pMob[index].GetRandomPos();

							if (pMob[index].NextX == pMob[index].TargetX && pMob[index].NextY == pMob[index].TargetY)
								continue;

							MSG_Action sm;

							if (GetEmptyMobGrid(index, &pMob[index].NextX, &pMob[index].NextY) == FALSE)
								continue;

							GetAction(index, pMob[index].NextX, pMob[index].NextY, (MSG_Action*)&sm);

							sm.Speed = BASE_GetSpeed(&pMob[index].MOB.CurrentScore);
							sm.Effect = 0;

							GridMulticast(index, pMob[index].NextX, pMob[index].NextY, (MSG_STANDARD*)&sm);
						}

						if (Processor & 2)
							DoTeleport(index, pMob[index].NextX, pMob[index].NextY);

						if (Processor & 0x10000)
						{
							//SendSay(index, "Processor 0x10000");
							if (pMob[index].GenerateIndex >= RUNEQUEST_LV6_MOB_INITIAL && pMob[index].GenerateIndex <= RUNEQUEST_LV6_MOB_END)
							{
								if (Pista[6].Party[0].MobCount < 100 && Pista[6].Party[0].MobCount != 0)
									Pista[6].Party[0].MobCount++;
							}

							DeleteMob(index, 3);
							continue;
						}
					}
				}
			}
		}
	}
#pragma endregion

	Sec4 = SecCounter % 4;

//#pragma region Ataque / fala em ação dos mobs
//	for (int index = Sec4 + MAX_USER; index < MAX_MOB; index += 4)
//	{
//		if (pMob[index].Mode != MOB_COMBAT)
//			continue;
//
//		int flag = 0;
//
//		if (pMob[index].MOB.Clan == 4)
//			flag = FALSE;
//
//		if (pMob[index].MOB.CurrentScore.Hp <= 0)
//		{
//			pMob[index].MOB.CurrentScore.Hp = 0;
//
//
//			DeleteMob(index, 1);
//			continue;
//		}
//
//		if (index % 16 == Sec16)
//			ProcessAffect(index);
//
//		if (pMob[index].GenerateIndex != RUNEQUEST_LV6_MOB_BOSS && pMob[index].TargetX >= 3423 && pMob[index].TargetX <= 3442 && pMob[index].TargetY >= 1492 && pMob[index].TargetY <= 1511)
//		{
//			if (pMob[index].GenerateIndex >= RUNEQUEST_LV6_MOB_INITIAL2 && pMob[index].GenerateIndex <= RUNEQUEST_LV6_MOB_END2)
//			{
//				if (Pista[6].Party[0].MobCount < 100 && Pista[6].Party[0].MobCount != 0)
//					Pista[6].Party[0].MobCount++;
//			}
//
//			DeleteMob(index, 3);
//			continue;
//		}
//
//		int Target = pMob[index].CurrentTarget;
//
//		if (Target > 0 && Target < MAX_MOB)
//		{
//			int leader = pMob[index].Leader;
//			if (leader == MOB_EMPTY)
//				leader = index;
//
//			int targetLeader = pMob[Target].Leader;
//
//			if (targetLeader == MOB_EMPTY)
//				targetLeader = Target;
//
//			int indexguild = pMob[index].MOB.Guild;
//			if (pMob[index].GuildDisable)
//				indexguild = 0;
//
//			int targetguild = pMob[Target].MOB.Guild;
//			if (pMob[Target].GuildDisable)
//				targetguild = 0;
//
//			if (indexguild == 0 && targetguild == 0)
//				indexguild = -1;
//
//			if (leader == targetLeader || indexguild == targetguild)
//				pMob[index].RemoveEnemyList(Target);
//		}
//
//		int BattleMode = pMob[index].BattleProcessor();
//
//		if (BattleMode & 0x20)
//		{
//			DeleteMob(index, 3);
//			continue;
//		}
//
//		if (BattleMode & 0x1000)
//		{
//			if (pMob[index].MOB.Equip[0].sIndex == 206)
//				pMob[index].CitizenDrop = 0;
//
//			//SendSay(index, "BattleMode 0x1000");
//
//			if (Target <= MOB_EMPTY || Target >= MAX_MOB)
//				continue;
//
//			if (pMob[Target].MOB.CurrentScore.Hp <= 0)
//				continue;
//
//			//MSG_AttackOne sm;
//
//			p39D sm{ 0 };
//
//			int village = BASE_GetVillage(pMob[Target].TargetX, pMob[Target].TargetY);
//
//			unsigned char mapatt = GetAttribute(pMob[Target].TargetX, pMob[Target].TargetY);
//
//			/*if (village >= 0 && village <= 4 && Target < MAX_USER && index >= MAX_USER)   //DESATIVAR BUG
//			{
//				if ((mapatt & 4) == 0 && (mapatt & 0x40) == 0)
//				{
//					FILE *fpp = NULL;
//
//					fpp = fopen("AttackDieTeste.txt", "a+");
//
//					//fprintf(fpp, "nome:%s x:%d y:%d conn:%d mode:%d atname:%s atx:%d aty:%d idx:%d\n", pMob[Target].MOB.MobName, pMob[Target].TargetX, pMob[Target].TargetY, Target, pUser[Target].Mode, pMob[index].MOB.MobName, pMob[index].TargetX, pMob[index].TargetY, index);
//
//					fclose(fpp);
//				}
//			}*/
//			
//
//			GetAttack(index, Target, &sm);
//
//			sm.FlagLocal = 0;
//
//			int targetbackup = Target;
//
//			Target = sm.Target.TargetID;
//
//			//if (GetInHalf(Target, index) == 0)
//			//{
//			//	FILE* fp = NULL;
//
//			//	fp = fopen("Gethalf.txt", "a+");
//
//			//	if (fp != NULL)
//			//	{
//			//		//fprintf(fp, "Attacker(%s, %d, %d, %d, %d, %d, %d) Targetbackup(%s, %d, %d, %d, %d, %d, %d) Target(%s, %d, %d, %d, %d, %d, %d)\n",
//			//		//pMob[index].MOB.MobName, index, pMob[index].TargetX, pMob[index].TargetY, targetbackup, Target, pMob[index].CurrentTarget,
//			//		//pMob[targetbackup].MOB.MobName, targetbackup, pMob[targetbackup].TargetX, pMob[targetbackup].TargetY, index, Target, pMob[targetbackup].CurrentTarget,
//			//		//pMob[Target].MOB.MobName, Target, pMob[Target].TargetX, pMob[Target].TargetY, targetbackup, Target, pMob[Target].CurrentTarget);
//
//			//		int sx1 = pMob[index].TargetX - HALFGRIDX;
//			//		int sy1 = pMob[index].TargetY - HALFGRIDY;
//			//		int sx2 = pMob[index].TargetX + HALFGRIDX;
//			//		int sy2 = pMob[index].TargetY + HALFGRIDY;
//
//			//		for (int y = sy1; y < sy2; y++)
//			//		{
//			//			for (int x = sx1; x < sx2; x++)
//			//			{
//			//				if (x < 0 || x >= MAX_GRIDX || y < 0 || y >= MAX_GRIDY)
//			//					continue;
//
//			//				int tmob = pMobGrid[y][x];
//
//			//				if (tmob <= 0 || tmob >= MAX_MOB)
//			//					continue;
//
//			//				//"fprintf(fp, "\tindex:%d nome:%s \r\n", tmob, pMob[tmob].MOB.MobName);
//			//			}
//			//		}
//
//			//		fclose(fp);
//			//	}
//
//			//	continue;
//			//}
//
//			int skill = sm.SkillIndex;
//
//			//109 : Raio Vermelho
//			//110 : Empurrão
//			//111 : Chão de espinhos
//			if (skill == 109 || skill == 110 || skill == 111)
//				goto KefraAttackLabel;
//
//			if (skill >= 0 && skill < MAX_SKILLINDEX && sm.SkillParm == 0)
//			{
//				if (skill == 33)
//					sm.Motion = 253;
//
//				int kind = ((skill % MAX_SKILL / 8) + 1);
//
//				if (kind >= 1 && kind <= 3)
//				{
//					int special = pMob[index].MOB.CurrentScore.Special[kind];
//					BOOL NeedUpdate = FALSE;
//
//					if (SetAffect(Target, skill, 100, special))
//						NeedUpdate = TRUE;
//
//					if (SetTick(Target, skill, 100, special))
//						NeedUpdate = TRUE;
//
//					if (NeedUpdate == TRUE)
//						SendScore(Target);
//				}
//			}
//
//			if (Target < MAX_USER && sm.Dam[0].Damage > 0)
//			{
//				int attackdex = pMob[index].MOB.CurrentScore.Dex / 5;
//
//				if (pMob[index].MOB.LearnedSkill & 0x1000000)
//					attackdex += 100;
//
//				if (pMob[index].MOB.Rsv & 0x40)
//					attackdex += 500;
//
//				int parryretn = WGetParryRate(&pMob[Target].MOB, pMob[Target].Parry, attackdex, pMob[index].MOB.Rsv);
//
//				if (sm.SkillIndex == 79 || sm.SkillIndex == 22)
//					parryretn = 30 * parryretn / 100;
//
//				int rd = rand() % 1000 + 1;
//
//				if (rd < parryretn)
//				{
//					sm.Dam[0].Damage = -3;
//
//					if ((pMob[Target].MOB.Rsv & 0x200) != 0 && rd < 100)
//						sm.Dam[0].Damage = -4;
//				}
//
//				else if (pMob[index].MOB.Clan == 4)
//					sm.Dam[0].Damage = (2 * sm.Dam[0].Damage) / 5;
//			}
//
//			int TargetLeader = pMob[Target].Leader;
//
//			if (sm.Dam[0].Damage > 0)
//			{
//				if (TargetLeader <= MOB_EMPTY)
//					TargetLeader = Target;
//
//				SetBattle(TargetLeader, index);
//
//				if (pMob[index].MOB.Clan != 4)
//					SetBattle(index, TargetLeader);
//
//				for (int z = 0; z < MAX_PARTY; z++)
//				{
//					int partyconn = pMob[TargetLeader].PartyList[z];
//					if (partyconn <= MAX_USER)
//						continue;
//
//					if (pMob[partyconn].Mode == MOB_EMPTY || pMob[partyconn].MOB.CurrentScore.Hp <= 0)
//					{
//						if (pMob[partyconn].Mode != MOB_EMPTY)
//						{
//							pMob[partyconn].MOB.CurrentScore.Hp = 0;
//							DeleteMob(partyconn, 1);
//						}
//
//						pMob[TargetLeader].PartyList[z] = MOB_EMPTY;
//						continue;
//					}
//
//					SetBattle(partyconn, index);
//					SetBattle(index, partyconn);
//				}
//
//				for (int z = 0; z < MAX_PARTY; z++)
//				{
//					int partyconn = pMob[TargetLeader].Evocations[z];
//					if (partyconn <= MAX_USER)
//						continue;
//
//					if (pMob[partyconn].Mode == MOB_EMPTY || pMob[partyconn].MOB.CurrentScore.Hp <= 0)
//					{
//						if (pMob[partyconn].Mode != MOB_EMPTY)
//						{
//							pMob[partyconn].MOB.CurrentScore.Hp = 0;
//							DeleteMob(partyconn, 1);
//						}
//
//						pMob[TargetLeader].Evocations[z] = MOB_EMPTY;
//						continue;
//					}
//
//					SetBattle(partyconn, index);
//					SetBattle(index, partyconn);
//				}
//
//				int Summoner = pMob[index].Summoner;
//
//				if (pMob[index].MOB.Clan == 4 && Target >= MAX_USER && Summoner > 0 && Summoner < MAX_USER && pUser[Summoner].Mode == USER_PLAY)
//				{
//					int posX = pMob[Summoner].TargetX;
//					int posY = pMob[Summoner].TargetY;
//					int num = 46;
//					int dam = 0;
//					int exp = 0;
//					int summdam = 0;
//
//					if (pMob[index].TargetX > posX - num && pMob[index].TargetX < posX + num && pMob[index].TargetY > posY - num && pMob[index].TargetY < posY + num)
//					{
//						if (pMob[Target].MOB.CurrentScore.Hp < sm.Dam[0].Damage)
//							summdam = pMob[Target].MOB.CurrentScore.Hp;
//
//						else
//							summdam = sm.Dam[0].Damage;
//					}
//				}
//			}
//
//			if (sm.Dam[0].Damage > 0 || sm.Dam[0].Damage <= -5)
//			{
//				int DamageNow = sm.Dam[0].Damage;
//				int damage = 0;
//				int mountindex = pMob[Target].MOB.Equip[14].sIndex;
//
//				if (Target < MAX_USER && mountindex >= 2360 && mountindex < 2390 && pMob[Target].MOB.Equip[14].stEffect[0].sValue > 0)
//				{
//					DamageNow = (3 * sm.Dam[0].Damage) / 4;
//					damage = sm.Dam[0].Damage - DamageNow;
//
//					if (DamageNow <= 0)
//						DamageNow = 1;
//
//					sm.Dam[0].Damage = DamageNow;
//				}
//
//				for (int c = 0; c < MAX_AFFECT && Target < MAX_USER; c++)
//				{
//					if (pMob[Target].Affect[c].Type == 18)
//					{
//						if (pMob[Target].MOB.CurrentScore.Mp > ((pMob[Target].MOB.CurrentScore.MaxMp / 100) * 10))
//						{
//							int mana = pMob[Target].MOB.CurrentScore.Mp - (DamageNow >> 1);
//
//							if (mana < 0)
//							{
//								DamageNow -= mana;
//								mana = 0;
//							}
//
//							pMob[Target].MOB.CurrentScore.Mp = mana;
//
//							pUser[Target].ReqMp = pUser[Target].ReqMp - (DamageNow >> 1);
//							SetReqMp(Target);
//
//							SendSetHpMp(Target);
//
//							DamageNow = ((DamageNow >> 1) + (DamageNow << 4)) / 80;
//							sm.Dam[0].Damage = DamageNow;
//						}
//					}
//				}
//
//
//				if (pMob[Target].MOB.Equip[13].sIndex == 786)
//				{
//					int sanc = pMob[Target].MOB.Equip[13].stEffect[0].cValue;
//
//					if (sanc < 2)
//						sanc = 2;
//
//					sanc *= 2;
//
//					pMob[Target].MOB.CurrentScore.Hp = pMob[Target].MOB.CurrentScore.Hp - (sm.Dam[0].Damage / sanc);
//				}
//				else if (pMob[Target].MOB.Equip[13].sIndex == 1936)
//				{
//					int sanc = pMob[Target].MOB.Equip[13].stEffect[0].cValue;
//
//					if (sanc < 2)
//						sanc = 2;
//
//					sanc *= 10;
//
//					pMob[Target].MOB.CurrentScore.Hp = pMob[Target].MOB.CurrentScore.Hp - (sm.Dam[0].Damage / sanc);
//				}
//				else if (pMob[Target].MOB.Equip[13].sIndex == 1937)
//				{
//					int sanc = pMob[Target].MOB.Equip[13].stEffect[0].cValue;
//
//					if (sanc < 2)
//						sanc = 2;
//
//					sanc *= 1000;
//
//					pMob[Target].MOB.CurrentScore.Hp = pMob[Target].MOB.CurrentScore.Hp - (sm.Dam[0].Damage / sanc);
//				}
//				else
//				{
//					if (pMob[Target].MOB.CurrentScore.Hp < sm.Dam[0].Damage)
//						pMob[Target].MOB.CurrentScore.Hp = 0;
//
//					else
//						pMob[Target].MOB.CurrentScore.Hp = pMob[Target].MOB.CurrentScore.Hp - sm.Dam[0].Damage;
//				}
//
//				if (Target > MAX_USER && pMob[Target].MOB.Clan == 4)
//					LinkMountHp(Target);
//
//				if (damage > 0)
//					ProcessAdultMount(Target, damage);
//			}
//
//			GridMulticast(pMob[Target].TargetX, pMob[Target].TargetY, (MSG_STANDARD*)&sm, 0);
//
//			if (Target > 0 && Target < MAX_USER)
//			{
//				if (pUser[Target].ReqHp < sm.Dam[0].Damage)
//					pUser[Target].ReqHp = 0;
//
//				else
//					pUser[Target].ReqHp = pUser[Target].ReqHp - sm.Dam[0].Damage;
//
//				SetReqHp(Target);
//				SendSetHpMp(Target);
//			}
//			else
//				SendScore(Target);
//
//			if (pMob[Target].MOB.CurrentScore.Hp <= 0)
//			{
//				pMob[Target].MOB.CurrentScore.Hp = 0;
//
//				MobKilled(Target, index, 0, 0);
//			}
//		}
//
//		//Kefra
//		if (0 == 1)
//		{
//		KefraAttackLabel:
//			MSG_Attack sm;
//			memset(&sm, 0, sizeof(MSG_Attack));
//
//			GetAttackArea(index, &sm);
//			MobAttack(index, sm);
//		}
//
//		if (BattleMode & 0x100)
//		{
//			int TargetID = pMob[index].CurrentTarget;
//			pMob[index].GetTargetPosDistance(TargetID);
//
//			if (pMob[index].NextX == pMob[index].TargetX && pMob[index].NextY == pMob[index].TargetY)
//				continue;
//
//			MSG_Action sm;
//
//			if (GetEmptyMobGrid(index, &pMob[index].NextX, &pMob[index].NextY) == FALSE)
//				continue;
//
//			GetAction(index, pMob[index].NextX, pMob[index].NextY, (MSG_Action*)&sm);
//
//			sm.Speed = BASE_GetSpeed(&pMob[index].MOB.CurrentScore);
//			sm.Effect = 0;
//
//			GridMulticast(index, pMob[index].NextX, pMob[index].NextY, (MSG_STANDARD*)&sm);
//		}
//
//		if (BattleMode & 1)
//		{
//			//SendSay(index, "BattleMode 0x1");
//			Target = pMob[index].CurrentTarget;
//			pMob[index].GetTargetPos(Target);
//
//			if (pMob[index].NextX == pMob[index].TargetX && pMob[index].NextY == pMob[index].TargetY)
//				continue;
//
//			MSG_Action sm;
//
//			if (GetEmptyMobGrid(index, &pMob[index].NextX, &pMob[index].NextY) == FALSE)
//				continue;
//
//			GetAction(index, pMob[index].NextX, pMob[index].NextY, (MSG_Action*)&sm);
//
//			sm.Speed = BASE_GetSpeed(&pMob[index].MOB.CurrentScore);
//			sm.Effect = 0;
//
//			GridMulticast(index, pMob[index].NextX, pMob[index].NextY, (MSG_STANDARD*)&sm);
//		}
//
//		if (BattleMode & 2)
//			DoTeleport(index, pMob[index].NextX, pMob[index].NextY);
//
//		if (BattleMode & 0x10)
//		{
//			//SendSay(index, "BattleMode 0x10");
//			MSG_Action sm;
//
//			if (GetEmptyMobGrid(index, &pMob[index].NextX, &pMob[index].NextY) == FALSE)
//				continue;
//
//			GetAction(index, pMob[index].NextX, pMob[index].NextY, (MSG_Action*)&sm);
//
//			if (pMob[index].NextX == pMob[index].TargetX && pMob[index].NextY == pMob[index].TargetY)
//				continue;
//
//			sm.Speed = BASE_GetSpeed(&pMob[index].MOB.CurrentScore);
//			sm.Effect = 0;
//
//			GridMulticast(index, pMob[index].NextX, pMob[index].NextY, (MSG_STANDARD*)&sm);
//		}
//	}
//#pragma endregion

#pragma region Ataque / fala em ação dos mobs
for (int index = Sec4 + MAX_USER; index < MAX_MOB; index += 4)
{
	if (pMob[index].Mode != MOB_COMBAT)
		continue;

	int flag = 0;

	if (pMob[index].MOB.Clan == 4)
		flag = FALSE;

	if (pMob[index].MOB.CurrentScore.Hp <= 0)
	{
		pMob[index].MOB.CurrentScore.Hp = 0;

		sprintf_s(temp, "err, battleprocessor delete hp 0 idx:%d leader:%d fol0:%d fol1:%d", index, pMob[index].Leader, pMob[index].PartyList[0], pMob[index].PartyList[1]);
		Log(temp, "-system", NULL);

		DeleteMob(index, 1);
		continue;
	}

	if (index % 16 == Sec16)
		ProcessAffect(index);

	if (pMob[index].GenerateIndex != RUNEQUEST_LV6_MOB_BOSS && pMob[index].TargetX >= 3423 && pMob[index].TargetX <= 3442 && pMob[index].TargetY >= 1492 && pMob[index].TargetY <= 1511)
	{
		if (pMob[index].GenerateIndex >= RUNEQUEST_LV6_MOB_INITIAL2 && pMob[index].GenerateIndex <= RUNEQUEST_LV6_MOB_END2)
		{
			if (Pista[6].Party[0].MobCount < 100 && Pista[6].Party[0].MobCount != 0)
				Pista[6].Party[0].MobCount++;
		}

		DeleteMob(index, 3);
		continue;
	}

	int Target = pMob[index].CurrentTarget;

	if (Target > 0 && Target < MAX_MOB)
	{
		int leader = pMob[index].Leader;
		if (leader == MOB_EMPTY)
			leader = index;

		int targetLeader = pMob[Target].Leader;

		if (targetLeader == MOB_EMPTY)
			targetLeader = Target;

		int indexguild = pMob[index].MOB.Guild;
		if (pMob[index].GuildDisable)
			indexguild = 0;

		int targetguild = pMob[Target].MOB.Guild;
		if (pMob[Target].GuildDisable)
			targetguild = 0;

		if (indexguild == 0 && targetguild == 0)
			indexguild = -1;

		if (leader == targetLeader || indexguild == targetguild)
			pMob[index].RemoveEnemyList(Target);
	}

	int BattleMode = pMob[index].BattleProcessor();

	if (BattleMode & 0x20)
	{
		DeleteMob(index, 3);
		continue;
	}

	if (BattleMode & 0x1000)
	{
		if (pMob[index].MOB.Equip[0].sIndex == 206)
			pMob[index].CitizenDrop = 0;

		if (Target <= MOB_EMPTY || Target >= MAX_MOB)
			continue;

		if (pMob[Target].MOB.CurrentScore.Hp <= 0)
			continue;

		p39D sm{ 0 };

		int village = BASE_GetVillage(pMob[Target].TargetX, pMob[Target].TargetY);

		unsigned char mapatt = GetAttribute(pMob[Target].TargetX, pMob[Target].TargetY);

		GetAttack(index, Target, &sm);

		sm.FlagLocal = 0;

		int targetbackup = Target;

		Target = sm.Target.TargetID;

		if (GetInHalf(Target, index) == 0)
		{
			continue;
		}

		int skill = sm.skillId;

		//109 : Raio Vermelho
		//110 : Empurrão
		//111 : Chão de espinhos
		if (skill == 109 || skill == 110 || skill == 111)
			goto KefraAttackLabel;

		if (skill >= 0 && skill < MAX_SKILLINDEX && sm.skillParm == 0)
		{
			if (skill == 33)
				sm.Motion = 253;

			int kind = ((skill % MAX_SKILL / 8) + 1);

			if (kind >= 1 && kind <= 3)
			{
				int special = pMob[index].MOB.CurrentScore.Special[kind];
				BOOL NeedUpdate = FALSE;

				if (SetAffect(Target, skill, 100, special))
					NeedUpdate = TRUE;

				if (SetTick(Target, skill, 100, special))
					NeedUpdate = TRUE;

				if (NeedUpdate == TRUE)
					SendScore(Target);
			}
		}

		if (Target < MAX_USER && sm.Target.Damage > 0)
		{
			int attackdex = pMob[index].MOB.CurrentScore.Dex / 5;

			if (pMob[index].MOB.LearnedSkill & 0x1000000)
				attackdex += 100;

			if (pMob[index].MOB.Rsv & 0x40)
				attackdex += 500;

			int parryretn = WGetParryRate(&pMob[Target].MOB, pMob[Target].Parry, attackdex, pMob[index].MOB.Rsv);


			if (sm.skillId == 79 || sm.skillId == 22)
				parryretn = 30 * parryretn / 100;

			int rd = rand() % 1000 + 1;

			if (rd < parryretn)
			{
				sm.Target.Damage = -3;

				if ((pMob[Target].MOB.Rsv & 0x200) != 0 && rd < 100)
					sm.Target.Damage = -4;
			}

			else if (pMob[index].MOB.Clan == 4)
				sm.Target.Damage = (2 * sm.Target.Damage) / 5;
		}

		int TargetLeader = pMob[Target].Leader;

		if (sm.Target.Damage > 0)
		{
			if (TargetLeader <= MOB_EMPTY)
				TargetLeader = Target;

			SetBattle(TargetLeader, index);

			if (pMob[index].MOB.Clan != 4)
				SetBattle(index, TargetLeader);

			for (int z = 0; z < MAX_PARTY; z++)
			{
				int partyconn = pMob[TargetLeader].PartyList[z];
				if (partyconn <= MAX_USER)
					continue;

				if (pMob[partyconn].Mode == MOB_EMPTY || pMob[partyconn].MOB.CurrentScore.Hp <= 0)
				{
					if (pMob[partyconn].Mode != MOB_EMPTY)
					{
						pMob[partyconn].MOB.CurrentScore.Hp = 0;
						DeleteMob(partyconn, 1);
					}

					pMob[TargetLeader].PartyList[z] = MOB_EMPTY;
					continue;
				}

				SetBattle(partyconn, index);
				SetBattle(index, partyconn);
			}

			for (int z = 0; z < MAX_PARTY; z++)
			{
				int partyconn = pMob[TargetLeader].Evocations[z];
				if (partyconn <= MAX_USER)
					continue;

				if (pMob[partyconn].Mode == MOB_EMPTY || pMob[partyconn].MOB.CurrentScore.Hp <= 0)
				{
					if (pMob[partyconn].Mode != MOB_EMPTY)
					{
						pMob[partyconn].MOB.CurrentScore.Hp = 0;
						DeleteMob(partyconn, 1);
					}

					pMob[TargetLeader].Evocations[z] = MOB_EMPTY;
					continue;
				}

				SetBattle(partyconn, index);
				SetBattle(index, partyconn);
			}

			int Summoner = pMob[index].Summoner;

			if (pMob[index].MOB.Clan == 4 && Target >= MAX_USER && Summoner > 0 && Summoner < MAX_USER && pUser[Summoner].Mode == USER_PLAY)
			{
				int posX = pMob[Summoner].TargetX;
				int posY = pMob[Summoner].TargetY;
				int num = 46;
				int dam = 0;
				int exp = 0;
				int summdam = 0;

				if (pMob[index].TargetX > posX - num && pMob[index].TargetX < posX + num && pMob[index].TargetY > posY - num && pMob[index].TargetY < posY + num)
				{
					if (pMob[Target].MOB.CurrentScore.Hp < sm.Target.Damage)
						summdam = pMob[Target].MOB.CurrentScore.Hp;

					else
						summdam = sm.Target.Damage;
				}
			}
		}

		if (sm.Target.Damage > 0 || sm.Target.Damage <= -5)
		{
			int DamageNow = sm.Target.Damage;
			int damage = 0;
			int mountindex = pMob[Target].MOB.Equip[14].sIndex;

			if (Target > 0 && Target < MAX_USER)///olhar aqui
			{
				if (Target < MAX_USER && mountindex >= 2360 && mountindex < 2390 && pMob[Target].MOB.Equip[14].stEffect[0].sValue > 0)
				{
					if (pMob[Target].MOB.Equip[14].stEffect[0].sValue > 0)
					{
						DamageNow = (3 * sm.Target.Damage) / 4;
						damage = sm.Target.Damage - DamageNow;

						if (DamageNow <= 0)
							DamageNow = 1;

						sm.Target.Damage = DamageNow;
					}
				}
			}

			if (pMob[Target].MOB.Class == 1)
			{
				for (int c = 0; c < MAX_AFFECT && Target < MAX_USER; c++)
				{
					if (pMob[Target].Affect[c].Type == 18)
					{
						if (pMob[Target].MOB.CurrentScore.Mp > ((pMob[Target].MOB.CurrentScore.MaxMp / 100) * 10))
						{
							int mana = pMob[Target].MOB.CurrentScore.Mp - (DamageNow >> 1);

							if (mana < 0)
							{
								DamageNow -= mana;
								mana = 0;
							}

							pMob[Target].MOB.CurrentScore.Mp = mana;

							pUser[Target].ReqMp = pUser[Target].ReqMp - (DamageNow >> 1);
							SetReqMp(Target);

							SendSetHpMp(Target);

							DamageNow = ((DamageNow >> 1) + (DamageNow << 4)) / 80;
							sm.Target.Damage = DamageNow;
						}
					}
				}
			}

			// Target
			auto multHpMob = pMob[Target].MOB.Equip[13].sIndex;
			auto _tDamage = DamageNow;
			if (multHpMob == 786 || multHpMob == 1936 || multHpMob == 1937)
			{
				int HpItem = GetItemSancNew(&pMob[Target].MOB.Equip[13]);
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
				default:
					break;
				}
				multHp *= HpItem;

				_tDamage /= multHp;

			}
			if (_tDamage > pMob[Target].MOB.CurrentScore.Hp)
				pMob[Target].MOB.CurrentScore.Hp = 0;
			else
				pMob[Target].MOB.CurrentScore.Hp -= _tDamage;

			if (Target > MAX_USER && pMob[Target].MOB.Clan == 4)
				LinkMountHp(Target);

			if (damage > 0)
				ProcessAdultMount(Target, damage);
		}

		GridMulticast(pMob[Target].TargetX, pMob[Target].TargetY, (MSG_STANDARD*)&sm, 0);

		if (Target > 0 && Target < MAX_USER)
		{
			if (pUser[Target].ReqHp < sm.Target.Damage)
				pUser[Target].ReqHp = 0;

			else
				pUser[Target].ReqHp = pUser[Target].ReqHp - sm.Target.Damage;

			SetReqHp(Target);
			SendSetHpMp(Target);
		}

		if (pMob[Target].MOB.CurrentScore.Hp <= 0)
		{
			pMob[Target].MOB.CurrentScore.Hp = 0;

			MobKilled(Target, index, 0, 0);
		}
	}

	//Kefra
	if (0 == 1)
	{
	KefraAttackLabel:
		MSG_Attack sm;
		memset(&sm, 0, sizeof(MSG_Attack));

		GetAttackArea(index, &sm);
		MobAttack(index, sm);
	}

	if (BattleMode & 0x100)
	{
		int TargetID = pMob[index].CurrentTarget;
		pMob[index].GetTargetPosDistance(TargetID);

		if (pMob[index].NextX == pMob[index].TargetX && pMob[index].NextY == pMob[index].TargetY)
			continue;

		MSG_Action sm;

		if (GetEmptyMobGrid(index, &pMob[index].NextX, &pMob[index].NextY) == FALSE)
			continue;

		GetAction(index, pMob[index].NextX, pMob[index].NextY, (MSG_Action*)&sm);

		sm.Speed = BASE_GetSpeed(&pMob[index].MOB.CurrentScore);
		sm.Effect = 0;

		GridMulticast(index, pMob[index].NextX, pMob[index].NextY, (MSG_STANDARD*)&sm);
	}

	if (BattleMode & 1)
	{
		//SendSay(index, "BattleMode 0x1");
		Target = pMob[index].CurrentTarget;
		pMob[index].GetTargetPos(Target);

		if (pMob[index].NextX == pMob[index].TargetX && pMob[index].NextY == pMob[index].TargetY)
			continue;

		MSG_Action sm;

		if (GetEmptyMobGrid(index, &pMob[index].NextX, &pMob[index].NextY) == FALSE)
			continue;

		GetAction(index, pMob[index].NextX, pMob[index].NextY, (MSG_Action*)&sm);

		sm.Speed = BASE_GetSpeed(&pMob[index].MOB.CurrentScore);
		sm.Effect = 0;

		GridMulticast(index, pMob[index].NextX, pMob[index].NextY, (MSG_STANDARD*)&sm);
	}

	if (BattleMode & 2)
		DoTeleport(index, pMob[index].NextX, pMob[index].NextY);

	if (BattleMode & 0x10)
	{
		//SendSay(index, "BattleMode 0x10");
		MSG_Action sm;

		if (GetEmptyMobGrid(index, &pMob[index].NextX, &pMob[index].NextY) == FALSE)
			continue;

		GetAction(index, pMob[index].NextX, pMob[index].NextY, (MSG_Action*)&sm);

		if (pMob[index].NextX == pMob[index].TargetX && pMob[index].NextY == pMob[index].TargetY)
			continue;

		sm.Speed = BASE_GetSpeed(&pMob[index].MOB.CurrentScore);
		sm.Effect = 0;

		GridMulticast(index, pMob[index].NextX, pMob[index].NextY, (MSG_STANDARD*)&sm);
	}
}
#pragma endregion

#pragma region Limpa as propriedades do mob caso não foram removidas pelo método padrão
if (SecCounter % 30 == 0)
{
	for (int nY = 0; nY < MAX_GRIDY; nY++)
	{
		for (int nX = 0; nX < MAX_GRIDX; nX++)
		{
			int Target = pMobGrid[nY][nX];

			if (Target < MAX_USER)
				continue;

			if (pMob[Target].Mode == MOB_EMPTY || pMob[Target].MOB.CurrentScore.Hp <= 0)
			{
				if (pMob[Target].TargetX != 0 && pMob[Target].TargetY != 0)
				{
					MSG_RemoveMob sm;
					memset(&sm, 0, sizeof(MSG_RemoveMob));
					sm.Size = sizeof(MSG_RemoveMob);

					sm.Type = _MSG_RemoveMob;
					sm.ID = Target;
					sm.RemoveType = 0;

					GridMulticast(pMob[Target].TargetX, pMob[Target].TargetY, (MSG_STANDARD*)&sm, Target < MAX_USER ? Target : 0);
				}

				pMob[Target].Clear();

				pMobGrid[nY][nX] = 0;
			}
		}
	}
}
#pragma endregion

}

void ProcessMinTimer()
{
	time_t rawtime;
	tm* timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	if (timeinfo->tm_mday != LastSystemLogDay)
		StartSystemLog();

	if (timeinfo->tm_mday != LastChatLogDay)
		StartChatLog();

	if (timeinfo->tm_mday != LastItemLogDay)
		StartItemLog();

	if (timeinfo->tm_mday != LastCompositorLogsDay)  //23/02
		CompositorLog();

	if (timeinfo->tm_mday != trade_itemLogsFileDay)  //23/02
		trade_item();

	if (timeinfo->tm_mday != fIMobDropLogFileDay)  //23/02
		MobDropLogs();

	if ((MinCounter % 2) == 0)
	{
		int NewbieServerID = (timeinfo->tm_mday - 1) % NumServerInGroup;

		if (LOCALSERVER != 0 || ServerIndex == NewbieServerID)
			NewbieEventServer = 1;

		else if (NewbieEventServer == 1 && ServerIndex != NewbieServerID)
		{
			for (int i = 1; i < MAX_USER; i++)
			{
				if (pUser[i].Mode == USER_EMPTY || pUser[i].cSock.Sock == 0)
					continue;

				if (pUser[i].TradeMode == 1)
					RemoveTrade(i);
			}

			NewbieEventServer = 0;
		}

		if (timeinfo->tm_wday == 0) // Domingo
			CastleServer = 1;

		if (timeinfo->tm_wday == 0) // Domingo
			RvRBonus = 0;

		/*if (1 != 0) // Likely to be a debug flag of sorts.. TODO: Check and decide if it stays
		{
		int wNum = BASE_GetWeekNumber();
		int wMod = wNum % 7;
		int wDay = wNum / 7;

		if (wMod == 0 && ((wDay % 2) == (ServerIndex % 2)))
		CastleServer = 1;
		else
		CastleServer = 0;

		}*/
	}

	for (int i = 0; i < MAX_GUILDZONE; i++)
	{
		if (GuildImpostoID[i] == 0)
			continue;

		if (pMob[GuildImpostoID[i]].MOB.CurrentScore.Hp <= 0)
			continue;

		//char temp[4096];
		strncpy(temp, "./npc/", sizeof(temp));

		char name[NAME_LENGTH];

		snprintf(name, sizeof(name), "%s", pMob[GuildImpostoID[i]].MOB.MobName);

		for (int j = 0; j < NAME_LENGTH; j++)
		{
			if (name[j] == ' ')
				name[j] = '_';
		}

		strcat(temp, name);

		int handle = _open(temp, _O_CREAT | _O_RDWR | _O_BINARY, _S_IREAD | _S_IWRITE);

		if (handle == -1)
		{
			SystemLog("-system", "-", 0, "fail - save npc imposto file");
			return;
		}
		_write(handle, (void*)&pMob[GuildImpostoID[i]].MOB, sizeof(pMob[GuildImpostoID[i]].MOB));
		_close(handle);
	}


	if (ForceWeekMode != -1)
		timeinfo->tm_wday = -1;

	CCastleZakum::ProcessMinTimer();

#pragma region Clear Area
	if (Kingdom1Clear == 1)
	{
		Kingdom1Clear = 2;
	}
	else if (Kingdom1Clear == 2)
	{
		Kingdom1Clear = 0;

		ClearArea(1676, 1556, 1776, 1636);
	}

	if (Kingdom2Clear == 1)
	{
		Kingdom2Clear = 2;
	}
	else if (Kingdom2Clear == 2)
	{
		Kingdom2Clear = 0;

		ClearArea(1676, 1816, 1776, 1892);
	}
#pragma endregion

	if ((MinCounter % 10) == 0)
		memset(FailAccount, 0, sizeof(FailAccount));

	CurrentTime = timeGetTime();

#pragma region Close Gates
	if (BigCubo == 1)
	{
		for (int i = 17; i < g_dwInitItem - 10; i++)
		{
			int ipx = g_pInitItem[i].PosX; // Item Pos X
			int ipy = g_pInitItem[i].PosY; // Item Pos Y
			int ipg = pItemGrid[ipy][ipx]; // Item Pos Grid

			if (pItem[ipg].ITEM.sIndex <= 0 || pItem[ipg].ITEM.sIndex >= MAX_ITEMLIST)
				continue;

			CItem* tItem = &pItem[ipg];

			int iKey = BASE_GetItemAbility(&pItem[ipg].ITEM, 39);

			if (iKey != 0)
			{
				if (pItem[ipg].State == STATE_OPEN && iKey < 15)
				{
					if (pItem[ipg].Delay == 0)
					{
						pItem[ipg].Delay = 1;

						continue;
					}

					UpdateItem(ipg, 3, &pItem[ipg].Height);
					/*
					MSG_UpdateItem sm;

					sm.ID = ESCENE_FIELD;
					sm.Type = _MSG_UpdateItem;

					sm.ItemID = ipg + 10000;

					sm.Size = sizeof(MSG_UpdateItem);

					//sm.Height = pItem[ipg].Height;
					*/
					pItem[ipg].State = STATE_LOCKED;
					/*
					sm.State = pItem[ipg].State;

					GridMulticast(ipx, ipy, (MSG_STANDARD*)&sm, 0);
					*/
					pItem[ipg].Delay = 0;

					MSG_CreateItem sm;

					sm.Type = _MSG_CreateItem;
					sm.Size = sizeof(MSG_CreateItem);
					sm.ID = ESCENE_FIELD;

					sm.ItemID = ipg + 10000;

					memmove_s(&sm.Item, sizeof(STRUCT_ITEM), &pItem[ipg].ITEM, sizeof(STRUCT_ITEM));

					sm.GridX = ipx;
					sm.GridY = ipy;

					sm.Rotate = pItem[ipg].Rotate;
					sm.State = pItem[ipg].State;
					//sm.Create = Create;

					//sm.Height = pItem[empty].Height;

					GridMulticast(ipx, ipy, (MSG_STANDARD*)&sm, 0);
				}
			}
		}
	}
	else
	{
		for (int i = 17; i < g_dwInitItem; i++)
		{
			int ipx = g_pInitItem[i].PosX; // Item Pos X
			int ipy = g_pInitItem[i].PosY; // Item Pos Y
			int ipg = pItemGrid[ipy][ipx]; // Item Pos Grid

			if (pItem[ipg].ITEM.sIndex <= 0 || pItem[ipg].ITEM.sIndex >= MAX_ITEMLIST)
				continue;

			CItem* tItem = &pItem[ipg];

			int iKey = BASE_GetItemAbility(&pItem[ipg].ITEM, 39);

			if (iKey != 0)
			{
				if (pItem[ipg].State == STATE_OPEN && iKey < 15)
				{
					if (pItem[ipg].Delay == 0)
					{
						pItem[ipg].Delay = 1;

						continue;
					}

					UpdateItem(ipg, 3, &pItem[ipg].Height);
					/*
					MSG_UpdateItem sm;

					sm.ID = ESCENE_FIELD;
					sm.Type = _MSG_UpdateItem;

					sm.ItemID = ipg + 10000;

					sm.Size = sizeof(MSG_UpdateItem);

					//sm.Height = pItem[ipg].Height;
					*/
					pItem[ipg].State = STATE_LOCKED;
					/*
					sm.State = pItem[ipg].State;

					GridMulticast(ipx, ipy, (MSG_STANDARD*)&sm, 0);
					*/
					pItem[ipg].Delay = 0;

					MSG_CreateItem sm;

					sm.Type = _MSG_CreateItem;
					sm.Size = sizeof(MSG_CreateItem);
					sm.ID = ESCENE_FIELD;

					sm.ItemID = ipg + 10000;

					memmove_s(&sm.Item, sizeof(STRUCT_ITEM), &pItem[ipg].ITEM, sizeof(STRUCT_ITEM));

					sm.GridX = ipx;
					sm.GridY = ipy;

					sm.Rotate = pItem[ipg].Rotate;
					sm.State = pItem[ipg].State;
					//sm.Create = Create;

					//sm.Height = pItem[empty].Height;

					GridMulticast(ipx, ipy, (MSG_STANDARD*)&sm, 0);
				}
			}
		}
	}
#pragma endregion
#pragma region GenerateMobs
	for (int i = 0; i < mNPCGen.NumList; i++)
	{
		int MinuteGenerate = mNPCGen.pList[i].MinuteGenerate;

		if (i != 0 && i != 1 && i != 2 && i != 5 && i != 6 && i != 7 && i != -1)
		{
			if (MinuteGenerate <= 0)
				continue;

			int mod = i % MinuteGenerate;

			if (MinCounter % MinuteGenerate == mod)
			{
				GenerateMob(i, 0, 0);

				if (MinuteGenerate >= 500 && MinuteGenerate < 1000)
				{
					mNPCGen.pList[i].MinuteGenerate = rand() % 500 + 500;

					continue;
				}

				if (MinuteGenerate >= 1000 && MinuteGenerate < 2000)
				{
					mNPCGen.pList[i].MinuteGenerate = rand() % 1000 + 1000;

					continue;
				}

				if (MinuteGenerate >= 2000 && MinuteGenerate < 3800)
				{
					mNPCGen.pList[i].MinuteGenerate = rand() % 1800 + 2000;

					continue;
				}

				if (MinuteGenerate >= 3800)
				{
					mNPCGen.pList[i].MinuteGenerate = rand() % 1000 + 3800;

					if (DUNGEONEVENT)
					{
						int RndPos = rand() % 30;
						int dpX = DungeonPos[RndPos][0];
						int dpY = DungeonPos[RndPos][1];

						int RndL = rand() % 5 + 5;

						for (int j = 0; j < RndL; j++)
						{
							STRUCT_ITEM PrizeItem;

							memset(&PrizeItem, 0, sizeof(STRUCT_ITEM));

							PrizeItem.sIndex = DungeonItem[rand() % 10];

							SetItemBonus(&PrizeItem, 0, 0, 0);

							int rnd = rand() % 4;

							CreateItem(dpX, dpY, &PrizeItem, rnd, 1);
						}
					}
				}

			}
		}
	}
#pragma endregion
	MinCounter++;

	int rndWeather = rand() % 1200;

	if (ForceWeather == -1)
	{
		if (rndWeather >= 0 && rndWeather < 260 && CurrentWeather != 0)
		{
			CurrentWeather = 0;
			SendWeather();
		}
		else if (rndWeather >= 30 && rndWeather < 50 && CurrentWeather != 1)
		{
			CurrentWeather = 1;
			SendWeather();
		}
		else if (rndWeather >= 55 && rndWeather < 60 && CurrentWeather != 2)
		{
			CurrentWeather = 2;
			SendWeather();
		}
	}
	else
	{
		if (ForceWeather != CurrentWeather)
		{
			CurrentWeather = ForceWeather;
			SendWeather();
		}
	}

	GuildProcess();
}
