#include "main.h"

void OpenStore(int Warp) {

	struct
	{
		_MSG;
		short npcID;
		short Warp;
		short Face;
		short Effect;
	}Packet;

	memset(&Packet, 0x0, sizeof(Packet));

	Packet.Size = sizeof(Packet);
	Packet.Type = _MSG_REQShopList;
	Packet.ID = GetClientID();
	Packet.npcID = 1000;
	Packet.Warp = Warp;
	Packet.Face = 0;
	Packet.Effect = 0;
	SendPacket((char*)&Packet, sizeof Packet);
}

void RequestDropList(int Page) {

	struct
	{
		_MSG;
		short Page;
	}Packet;

	memset(&Packet, 0x0, sizeof(Packet));

	Packet.Size = sizeof(Packet);
	Packet.Type = _MSG_ReqdListNames;
	Packet.ID = GetClientID();
	Packet.Page = Page;
	SendPacket((char*)&Packet, sizeof Packet);
}

void SendPix(int qnt, const char* chave) {

	struct
	{
		_MSG;
		int qnt;
		char chave[5];
	}Packet;

	memset(&Packet, 0x0, sizeof(Packet));

	Packet.Size = sizeof(Packet);
	Packet.Type = _MSG_SendPix;
	Packet.ID = GetClientID();
	Packet.qnt = qnt;
	strncpy(Packet.chave, chave, sizeof(Packet.chave));
	SendPacket((char*)&Packet, sizeof Packet);
}

void OpenDroplist(const char* mobname, int region) {

	struct
	{
		_MSG;
		char Mobname[16];
		int Region;
	}Packet;
	memset(&Packet, 0x0, sizeof(Packet));
	
	Packet.Size = sizeof(Packet);
	Packet.Type = _MSG_ReqDropList;
	Packet.ID = GetClientID();
	strncpy(Packet.Mobname, mobname, sizeof(Packet.Mobname));
	Packet.Region = region;
	SendPacket((char*)&Packet, sizeof Packet);

}

void Sendteleport(int X, int Y) {
	struct
	{
		_MSG;
		int X;
		int Y;
	}Packet;
	memset(&Packet, 0x0, sizeof(Packet));

	Packet.Size = sizeof(Packet);
	Packet.Type = _MSG_RequestTeleport;
	Packet.ID = GetClientID();
	Packet.X = X;
	Packet.Y = Y;
	SendPacket((char*)&Packet, sizeof Packet);
}

void SendReqDonateShop(int Shop, int Page, int ItemPos, int Qnt) {

	struct
	{
		_MSG;
		int Store;
		int Page;
		int ItemPos;
		int Qnt;
	}Packet;
	memset(&Packet, 0x0, sizeof(Packet));

	Packet.Size = sizeof(Packet);
	Packet.Type = _MSG_ReqShopDonate;
	Packet.ID = GetClientID();
	Packet.Store = Shop;
	Packet.Page = Page;
	Packet.ItemPos = ItemPos;
	Packet.Qnt = Qnt;
	SendPacket((char*)&Packet, sizeof Packet);
}

void SendFiltro(int Index) {

	struct
	{
		_MSG;
		int ItemId;
	}Packet;

	memset(&Packet, 0x0, sizeof(Packet));

	Packet.Size = sizeof(Packet);
	Packet.Type = _MSG_SendFiltro;
	Packet.ID = GetClientID();
	Packet.ItemId = Index;
	SendPacket((char*)&Packet, sizeof Packet);

}

void SendJephi(int Item, int Qnt)
{
	struct
	{
		_MSG;
		int Item;
		int Qnt;
	}Packet;

	memset(&Packet, 0x0, sizeof(Packet));

	Packet.Size = sizeof(Packet);
	Packet.Type = _MSG_SendJephi;
	Packet.ID = GetClientID();
	Packet.Item = Item;
	Packet.Qnt = Qnt;
	SendPacket((char*)&Packet, sizeof Packet);
}

void SendItemLevel(int Item, int Qnt)
{
	struct
	{
		_MSG;
		int Item;
		int Qnt;
	}Packet;

	memset(&Packet, 0x0, sizeof(Packet));

	Packet.Size = sizeof(Packet);
	Packet.Type = _MSG_SendItemLevel;
	Packet.ID = GetClientID();
	Packet.Item = Item;
	Packet.Qnt = Qnt;
	SendPacket((char*)&Packet, sizeof Packet);
}

void ReqAlias(int Type)
{
	struct
	{
		_MSG;
		int Tipo;
	}Packet;

	memset(&Packet, 0x0, sizeof(Packet));

	Packet.Size = sizeof(Packet);
	Packet.Type = _MSG_ReqAlias;
	Packet.ID = GetClientID();
	Packet.Tipo = Type;
	SendPacket((char*)&Packet, sizeof Packet);
}

void AttTraje(int Type)
{
	struct
	{
		_MSG;
		int Tipo;
	}Packet;

	memset(&Packet, 0x0, sizeof(Packet));

	Packet.Size = sizeof(Packet);
	Packet.Type = _MSG_SendTraje;
	Packet.ID = GetClientID();
	Packet.Tipo = Type;
	SendPacket((char*)&Packet, sizeof Packet);
}

void SendTextServer(const char* Text) {

	MSG_MessageWhisper  m;

	m.Size = sizeof(m);
	m.Type = _MSG_MessageWhisper;
	m.ID = GetClientID();
	strncpy(m.MobName, Text, sizeof(m.MobName));
	strncpy(m.String, "", sizeof(m.String));
	SendPacket((char*)&m, sizeof m);
}