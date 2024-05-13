#pragma once
class CClientInfo
{
public:
	static CClientInfo& Instance() {
		static CClientInfo _Instance;
		return _Instance;
	}
private:
	CClientInfo() = default;
	CClientInfo(const CClientInfo&) = delete;
	CClientInfo& operator=(const CClientInfo&) = delete;
	struct ST_INFO
	{
		//colocar aqui oque quer q venha do servidor
		int Cash;
		int Honra;
		int BossLocal;
		int DoubleATV;
		int Kingcontador;
		int NumMobs;
		int NumMobs1;
		int NumMobs2;
		int NumMobs3;
		int NumMobs4;
		int NumMobs5;
		int NumMobs6;
		int DiariaState;

		char GrupoSenha[6];
		char Pix[5];
		int chave1;
		int Keys[50];
		int cStoreItens[3][3][15][3];
		ULONGLONG TimeToChest;
	};
	struct DROPLIST
	{
		char MobName[30][16];
		int Item[64];
	};
	struct RANKING
	{
		char RankName[50][16];
		int RankLevel[50];
		int RankClasse[50];
		int RankEvolution[50];
		int PvP[50];
		int State;
	};
	struct TOWERWAR
	{
		int Points[10];
		char GuildID[10][12];
	};
	struct SERVER
	{
		int Double;
		int ExpRate;
		int DropRate;
	};
	struct MAILITEM
	{
		int Index;
		int sEffect[3];
		int sValue[3];
	};
public:
	ST_INFO Info;
	DROPLIST DropList;
	RANKING Ranking;
	TOWERWAR TowerWar;
	SERVER Server;
	MAILITEM MailItem;
	void Init();
	void ReceiveInfo(char* Packet);
};

static CClientInfo* g_pClientInfo = &CClientInfo::Instance();

