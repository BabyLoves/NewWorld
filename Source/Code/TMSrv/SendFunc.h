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
#ifndef __SENDFUNC__
#define __SENDFUNC__

int checkCord(int conn, int cX, int cY, int cX2, int cY2);
BOOL bFile_exists(const char *filename);
void SendClientMsg(int conn, char* Message);
void SendClientMessage(int conn, char *Message);
void SendDerrubarCliente(int conn, short Modelo);
void SendMessageBox(int conn, char *Message);
void SendNotice(char *Message);
void SendNoticeChief(char *Message);
void SendSummonChief();
void SendNoticeArea(char *Message, int x1, int y1, int x2, int y2);
void SendGuildNotice(int Guild, char *Message);
void SendClientMessageOk(int conn, char *Message, int Useless1, int Useless2);
void SendWindowMessage(int conn, char *Message);
void SendClientSignal(int conn, int id, unsigned short signal);
void SendClientSignalParm(int conn, int id, unsigned short signal, int parm);
void SendClientSignalParm2(int conn, int id, unsigned short signal, int parm, int parm2);
void SendClientSignalParm3(int conn, int id, unsigned short signal, int parm, int parm2, int parm3);
void SyncMulticast(int conn, MSG_STANDARD *m, int bSend);
void SyncKingdomMulticast(int conn, int Kingdom, MSG_STANDARD *m, int bSend);
void SendCreateMob(int conn, int otherconn, int bSend);
void SendCreateItem(int conn, int item, int bSend);
void SendChat(int conn, char *Message);
void SendEnvEffect(int x1, int y1, int x2, int y2, int Effect, int EffectParm);
void SendEnvEffectKingdom(int x1, int y1, int x2, int y2, int Effect, int EffectParm, int Clan);
void SendEnvEffectLeader(int x1, int y1, int x2, int y2, int Effect, int EffectParm);
void SendRemoveMob(int dest, int sour, int Type, int bSend);
void SendRemoveItem(int dest, int itemid, int bSend);
void SendAutoTrade(int conn, int otherconn);
void SendGridMob(int conn);

//void GridMulticast(int conn, int tx, int ty, MSG_STANDARD *msg);
void GridMulticast(int Index, unsigned int posX, unsigned int posY, MSG_STANDARD* msg);
void SendEmotion(int conn, int Motion, int Parm);
//void GridMulticast(int tx, int ty, MSG_STANDARD *msg, int skip);
void GridMulticast(int posX, int posY, MSG_STANDARD* sendPak, int Index);
void PartyGridMulticast(int tx, int ty, MSG_STANDARD *msg, int skip, int Leaderconn);
void SendItem(int conn, int Type, int Slot, STRUCT_ITEM *item);
void SendEquip(int conn, int skip);
void SendScore(int conn);
void SendGuildChat(int conn, char *Message);
void SendClientChat(int conn, char *pMsg, int color);
void SendEtc(int conn);
void SendServerInfo(int conn);
void SellMarket(int ItemId, int Qnt);
void UpdateDonate(int conn);
void UpdateDropList(int conn);
void SendCargoCoin(int conn);
void SendGuildList(int conn);
void SendShopList(int conn, int MobIndex, int ShopType);
void SendDonateShop(int conn, int MobIndex, int ShopType);
void SendItemList(int conn, int MobIndex, int ShopType);
void SendWarInfo(int conn, int Clan);
void SendAddParty(int Leaderconn, int conn, int PartyID);
void SendAddPartyEvocation(int Leaderconn);
void SendRemoveParty(int conn, int connExit);
bool IsVip(int conn);
void SendCarry(int conn);
void SendWeather();
void SendSetHpMp(int conn);
void SendHpMode(int conn);
void SendSay(int mob, char *Message);
void MapaMulticastArea(int x1, int y1, int x2, int y2, MSG_STANDARD *m, int bSend);
void MapaMulticast(int tx, int ty, MSG_STANDARD *m, int bSend);
void SendMessageArea(int x1, int y1, int x2, int y2, MSG_STANDARD *m, int bSend);
void SendSignalParmArea(int x1, int y1, int x2, int y2, int id, unsigned short signal, int parm);
void SendClientSignalShortParm2(int conn, int id, unsigned short signal, int parm, int parm2);
void SendShortSignalParm2Area(int x1, int y1, int x2, int y2, int id, unsigned short signal, int parm1, int parm2);
void SendPKInfo(int conn, int target);
void SendAffect(int conn);
void SendQuizMessage(int conn, char* Title, char* Answer0, char* Answer1, char* Answer2, char* Answer3, char correct);
void SendQuizLanN(int conn, char* Title, char* Answer0, char* Answer1, char* Answer2, char* Answer3, char correct);
void SendQuizLanM(int conn, char* Title, char* Answer0, char* Answer1, char* Answer2, char* Answer3, char correct);
void SendQuizLanA(int conn, char* Title, char* Answer0, char* Answer1, char* Answer2, char* Answer3, char correct);
void SendRecycle(int conn);
char* strFmt(const char* str, ...);
void SendClientSignalParmCoord(int conn, int id, unsigned short signal, int parm, int x1, int y1, int x2, int y2);
void SendBigMessage(int conn, char *Title, char *String); 
bool SendSaveBanned(int conn);
void SendBanAccount(int conn, int type);
char* strFmt(const char* str, ...);
void SendEventCount(int conn);//evento hit evento
void SendEventCount2(int conn);//evento hit pesca
void SendLanCount(int conn);

int DamageBalancing(int conn, int idx, int tDamage);
int DamageCalc(int signal, int pValue, int iValue);
void BalanceioPvP();
int Limitadordelojinha(char* Mac);
int Limitadordeconexoes(char* Mac);
void SendReqParty(int Leaderconn, int conn, int PartyID);
#endif