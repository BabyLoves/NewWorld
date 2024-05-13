#include "..\Basedef.h"
#include "..\ItemEffect.h"
#include "Language.h"
#include "Server.h"
#include "GetFunc.h"
#include "SendFunc.h"
#include "CCastleZakum.h"
#include "Functions.h"


int ControleDropGold(int conn, int target, int DropedGold)
{
	int GoldFinal = DropedGold;





	return GoldFinal;
}

STRUCT_ITEM* ControleDropItem(int conn, int target, int bonus, int PosX, int PosY, STRUCT_ITEM* Item)
{
	STRUCT_ITEM* ItemDrop = Item;

	if (ItemDrop->sIndex != 0 && CCastleZakum::KeyDrop(target, conn, PosX, PosY, ItemDrop) == TRUE)
	{
		SetItemBonus(ItemDrop, pMob[target].MOB.CurrentScore.Level, 0, bonus);

		//Filtro de Drop
		if (AutoDrop(conn, ItemDrop->sIndex) == false)
			return ItemDrop;

		//Retira o drop duplo da lan
		if ((pMob[conn].TargetX > 3604 && pMob[conn].TargetY > 3604 && pMob[conn].TargetX < 3691 && pMob[conn].TargetY < 3690) ||
			(pMob[conn].TargetX > 3732 && pMob[conn].TargetY > 3476 && pMob[conn].TargetX < 3819 && pMob[conn].TargetY < 3563) ||
			(pMob[conn].TargetX > 3860 && pMob[conn].TargetY > 3604 && pMob[conn].TargetX < 3946 && pMob[conn].TargetY < 3690)
			) {

			int List[]{
				419, 420, 4019, 2404, 2399, 4026, 2400, 2405, 4020
			};
			for (int i = 0; i < (sizeof(List) / 4); i++) {
				if (ItemDrop->sIndex == List[i])
					return ItemDrop;
			}
		}

		/*if (ItemDrop->sIndex == 1740 || ItemDrop->sIndex == 1741)
			SendNotice(strFmt("O jogador [%s] dropou uma [%s]", pMob[conn].MOB.MobName, g_pItemList[ItemDrop->sIndex].Name));*/

		//agrupador automatico teste
		if (AgroupList(conn, ItemDrop->sIndex) == true) {
			SendItemagrupar(conn, ItemDrop->sIndex);

			if (LogList(ItemDrop->sIndex) == true) {
				snprintf(temp, sizeof(temp), "MobName:%s dropou o item: %s:%d %d.%d.%d.%d.%d.%d do mob:%s", pMob[conn].MOB.MobName, g_pItemList[ItemDrop->sIndex].Name, ItemDrop->sIndex, ItemDrop->stEffect[0].cEffect, ItemDrop->stEffect[0].cValue, ItemDrop->stEffect[1].cEffect, ItemDrop->stEffect[1].cValue, ItemDrop->stEffect[2].cEffect, ItemDrop->stEffect[2].cValue, pMob[target].MOB.MobName);
				MobDropLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, temp);
			}

			return ItemDrop;
		}

		if (PutItem(conn, ItemDrop))
		{
			if (LogList(ItemDrop->sIndex) == true) {
				snprintf(temp, sizeof(temp), "MobName:%s dropou o item: %s:%d %d.%d.%d.%d.%d.%d do mob:%s", pMob[conn].MOB.MobName, g_pItemList[ItemDrop->sIndex].Name, ItemDrop->sIndex, ItemDrop->stEffect[0].cEffect, ItemDrop->stEffect[0].cValue, ItemDrop->stEffect[1].cEffect, ItemDrop->stEffect[1].cValue, ItemDrop->stEffect[2].cEffect, ItemDrop->stEffect[2].cValue, pMob[target].MOB.MobName);
				MobDropLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, temp);
			}
		}

		int PedacoEquilibrio = ItemDrop->sIndex == 4125;
		if (PedacoEquilibrio)
			DoTeleport(conn, 1970 + rand() % 2, 1580 + rand() % 2);
	}
	return ItemDrop;
}

bool AutoDrop(int conn, int itemId)
{
	if ((pMob[conn].MOB.Equip[13].sIndex == 3901 || pMob[conn].MOB.Equip[13].sIndex == 3902 || pMob[conn].MOB.Equip[13].sIndex == 3916) && pMob[conn].FiltroState == 1) {
		
		if (pMob[conn].FiltroID[0] == 1) {
			int Amagos[] = {
				2396, //Âmago_de_Cav_s/Sela_N
				2397, //Âmago_de_Cav_Fantasm_N
				2398, //Âmago_de_Cavalo_Leve_N
				2399, //Âmago_de_Cavalo_Equip_N
				2400, //Âmago_de_Andaluz_N
				2401, //Âmago_de_Ca_s/Sela_B
				2402, //Âmago_de_Cav_Fantasm_B
				2403, //Âmago_de_Cavalo_Leve_B
				2404, //Âmago_de_Cavalo_Equip_B
				2405, //Âmago_de_Andaluz_B
				2406, //Âmago_de_Fenrir
				2411, //Âmago_de_Unicórnio
				2412, //Âmago_de_Pégasus
				2413, //Âmago_de_Unisus
				2390, //Âmago_de_Porco
				2391, //Âmago_de_Javali
				2392, //Âmago_de_Lobo
				2393, //Âmago_de_Dragão_Menor
				2394, //Âmago_de_Urso
				2395 //Âmago_de_Dente_de_Sabre
			};
			for (int i = 0; i < (sizeof(Amagos) / 4); i++) {
				if (Amagos[i] == itemId)
					return true;
			}
		}
		if (pMob[conn].FiltroID[1] == 1) {
			int Kit10[] = {
				2441, //Diamante
				2442, //Esmeralda
				2443, //Coral
				2444, //Garnet
				1774 //Pedra_do_Sábio
			};
			for (int i = 0; i < (sizeof(Kit10) / 4); i++) {
				if (Kit10[i] == itemId)
					return true;
			}
		}
		if (pMob[conn].FiltroID[2] == 1) {
			int Poeiras[] = {
				419, //Resto_de_Oriharucon
				420, //Resto_de_Lactolerium
				412, //Poeira_de_Oriharucon
				413, //Poeira_de_Lactolerium
				4026 //Moeda_de_1kk
			};
			for (int i = 0; i < (sizeof(Poeiras) / 4); i++) {
				if (Poeiras[i] == itemId)
					return true;
			}
		}
		if (pMob[conn].FiltroID[3] == 1) {
			int Classe[] = {
				4019, //Classe_D
				4020 //Classe_E
			};
			for (int i = 0; i < (sizeof(Classe) / 4); i++) {
				if (Classe[i] == itemId)
					return true;
			}
		}
		if (pMob[conn].FiltroID[4] == 1) {
			int Entradas[] = {
				4038, //Vela_do_Coveiro
				4039, //Colheita_do_Jardineiro
				4040, //Cura_do_Batedor
				4041, //Mana_do_Batedor
				4042, //Emblema_do_Guarda
				5134 //Pista_da_Runas
			};
			for (int i = 0; i < (sizeof(Entradas) / 4); i++) {
				if (Entradas[i] == itemId)
					return true;
			}
		}
		if (pMob[conn].FiltroID[5] == 1) {
			int BoxQuest[] = {
				4117, //Caixa_da_Sabedoria
				4118, //Lágrima_Angelical
				4119, //Coração_do_Kaizen
				4120, //Olho_de_Sangue
				4121, //Pedra_Espiritual_dos_Elfos
				4122 //Molar_de_Gárgula
			};
			for (int i = 0; i < (sizeof(BoxQuest) / 4); i++) {
				if (BoxQuest[i] == itemId)
					return true;
			}
		}
		if (pMob[conn].FiltroID[6] == 1) {
			int ItensEvolução[] = {
				1740, //Alma_do_Unicórnio
				1741, //Alma_da_Fênix
				1742, //Pedra_da_Imortalidade
				1744, //Pedra_da_Inteligência
				1745, //Pedra_da_Sabedoria
				1746, //Pedra_da_Misericórdia
				1747, //Pedra_do_Abismo
				1748, //Pedra_da_Beleza
				1749, //Pedra_da_Vitória
				1750, //Pedra_da_Originalidade
				1751, //Pedra_do_Reino
				1752, //Pedra_do_Lorde_Orc
				1753, //Pedra_do_Esqueleto
				1754, //Pedra_de_Dragão_Lich
				1755, //Pedra_do_Demonlord
				1756, //Pedra_de_Mantícora
				1757, //Pedra_de_Gárgula_de_Fogo
				1758, //Pedra_do_Lugefer
				1759 //Pedra_do_Rei_Demonlord
			};
			for (int i = 0; i < (sizeof(ItensEvolução) / 4); i++) {
				if (ItensEvolução[i] == itemId)
					return true;
			}
		}
		if (pMob[conn].FiltroID[7] == 1) {
			int Runas[] = {
				5110, //Ansuz
				5111, //Uraz
				5112, //Thurisaz
				5113, //Fehu
				5114, //Raidho
				5115, //Kenaz
				5116, //Naudhiz
				5117, //Gebo
				5118, //Wunjo
				5119, //Hagalaz
				5120, //Isa
				5121, //Jara
				5122, //Eihwaz
				5123, //Perthro
				5124, //Elhaz
				5125, //Sowilo
				5126, //Berkano
				5127, //Ehwaz
				5128, //Tiwaz
				5129, //Mannaz
				5130, //Laguz
				5131, //Dagaz
				5132, //Ing
				5133 //Othel
			};
			for (int i = 0; i < (sizeof(Runas) / 4); i++) {
				if (Runas[i] == itemId)
					return true;
			}
		}
		if (pMob[conn].FiltroID[8] == 1) {
			int SetDHT[] = {
				1641, //Chapéu_de_Teia(N),7.0,136.114.0.0.168,37,138000,2,2246,1,EF_CLASS,8,EF_GRID,0,EF_AC,81,EF_SAVEMANA,7,EF_ITEMLEVEL,4
				1642, //Chapéu_de_Teia(M),7.0,144.121.0.0.177,37,142000,2,2246,2,EF_CLASS,8,EF_GRID,0,EF_AC,86,EF_SAVEMANA,8,EF_ITEMLEVEL,4
				1643, //Chapéu_de_Teia(A),7.0,153.128.0.0.188,37,145000,2,2246,3,EF_CLASS,8,EF_GRID,0,EF_AC,91,EF_SAVEMANA,8,EF_MPADD,10,EF_ITEMLEVEL,4
				1644, //Peitoral_de_Teia(N),7.0,142.119.0.0.175,37,188000,4,2247,1,EF_CLASS,8,EF_GRID,0,EF_AC,106,EF_HPADD,4,EF_ITEMLEVEL,4
				1645, //Peitoral_de_Teia(M),7.0,150.126.0.0.185,37,191000,4,2247,2,EF_CLASS,8,EF_GRID,0,EF_AC,112,EF_CRITICAL,45,EF_HPADD,4,EF_ITEMLEVEL,4
				1646, //Peitoral_de_Teia(A),7.0,159.133.0.0.195,37,195000,4,2247,3,EF_CLASS,8,EF_GRID,0,EF_AC,119,EF_CRITICAL,35,EF_HPADD,5,EF_ITEMLEVEL,4
				1647, //Calça_de_Teia(N),7.0,139.117.0.0.171,37,170000,8,2248,1,EF_CLASS,8,EF_GRID,0,EF_AC,92,EF_HPADD,4,EF_ITEMLEVEL,4
				1648, //Calça_de_Teia(M),7.0,147.123.0.0.181,37,173000,8,2248,2,EF_CLASS,8,EF_GRID,0,EF_AC,97,EF_CRITICAL,45,EF_HPADD,4,EF_ITEMLEVEL,4
				1649, //Calça_de_Teia(A),7.0,156.130.0.0.192,37,176000,8,2248,3,EF_CLASS,8,EF_GRID,0,EF_AC,103,EF_CRITICAL,35,EF_HPADD,5,EF_ITEMLEVEL,4
				1650, //Braçadeira_de_Teia(N),7.0,129.109.0.0.159,37,126000,16,2249,1,EF_CLASS,8,EF_GRID,0,EF_AC,73,EF_MPADD,6,EF_ITEMLEVEL,4
				1651, //Braçadeira_de_Teia(M),7.0,137.115.0.0.169,37,129000,16,2249,2,EF_CLASS,8,EF_GRID,0,EF_AC,75,EF_ACADD,17,EF_MPADD,6,EF_ITEMLEVEL,4
				1652, //Braçadeira_de_Teia(A),7.0,146.122.0.0.180,37,131000,16,2249,3,EF_CLASS,8,EF_GRID,0,EF_AC,78,EF_ACADD,17,EF_MPADD,7,EF_ITEMLEVEL,4
				1653, //Botas_de_Teia(N),7.0,132.111.0.0.163,37,141000,32,2250,1,EF_CLASS,8,EF_GRID,0,EF_AC,73,EF_RUNSPEED,2,EF_REGENMP,30,EF_ITEMLEVEL,4
				1654, //Botas_de_Teia(M),7.0,140.118.0.0.173,37,144000,32,2250,2,EF_CLASS,8,EF_GRID,0,EF_AC,77,EF_RUNSPEED,2,EF_REGENMP,30,EF_ITEMLEVEL,4
				1655 //Botas_de_Teia(A),7.0,149.125.0.0.183,37,148000,32,2250,3,EF_CLASS,8,EF_GRID,0,EF_AC,81,EF_RUNSPEED,2,EF_REGENMP,35,EF_ITEMLEVEL,4
			};
			for (int i = 0; i < (sizeof(SetDHT) / 4); i++) {
				if (SetDHT[i] == itemId)
					return true;
			}
		}
		if (pMob[conn].FiltroID[9] == 1) {
			int SetEHT[] = {
				1660, //Elmo_Legionário,19.0,283.0.0.0.0,40,160000,2,3861,1,EF_CLASS,8,EF_GRID,0,EF_AC,102,EF_SAVEMANA,10,EF_MPADD,10,EF_ITEMLEVEL,5
				1661, //Armadura_Legionária,19.0,283.0.0.0.0,40,160000,4,3862,1,EF_CLASS,8,EF_GRID,0,EF_AC,132,EF_CRITICAL,45,EF_HPADD,8,EF_ITEMLEVEL,5
				1662, //Calça_Legionária,19.0,283.0.0.0.0,40,160000,8,3863,1,EF_CLASS,8,EF_GRID,0,EF_AC,112,EF_CRITICAL,45,EF_HPADD,9,EF_ITEMLEVEL,5
				1663, //Manoplas_Legionárias,19.0,283.0.0.0.0,40,160000,16,3864,1,EF_CLASS,8,EF_GRID,0,EF_AC,88,EF_ACADD,20,EF_MPADD,9,EF_ITEMLEVEL,5
				1664 //Botas_Legionárias,19.0,283.0.0.0.0,40,160000,32,3865,1,EF_CLASS,8,EF_GRID,0,EF_AC,90,EF_RUNSPEED,2,EF_REGENMP,45,EF_ITEMLEVEL,5
			};
			for (int i = 0; i < (sizeof(SetEHT) / 4); i++) {
				if (SetEHT[i] == itemId)
					return true;
			}
		}
		if (pMob[conn].FiltroID[10] == 1) {
			int SetArchHT[] = {
				1656, //Armadura_Rake,41.0,227.0.0.0.0,39,178000,4,2247,1,EF_CLASS,8,EF_GRID,0,EF_AC,156,EF_CRITICAL,45,EF_HPADD,8,EF_ITEMLEVEL,5,EF_MOBTYPE,1
				1657, //Calça_Rake,41.0,230.0.0.0.0,39,178000,8,2248,1,EF_CLASS,8,EF_GRID,0,EF_AC,135,EF_CRITICAL,45,EF_HPADD,8,EF_ITEMLEVEL,5,EF_MOBTYPE,1
				1658, //Manoplas_Rake,41.0,220.0.0.0.0,39,176000,16,2249,1,EF_CLASS,8,EF_GRID,0,EF_AC,104,EF_ACADD,17,EF_MPADD,8,EF_ITEMLEVEL,5,EF_MOBTYPE,1
				1659 //Botas_Rake,41.0,223.0.0.0.0,39,174000,32,2250,1,EF_CLASS,8,EF_GRID,0,EF_AC,106,EF_RUNSPEED,2,EF_REGENMP,40,EF_ITEMLEVEL,5,EF_MOBTYPE,1
			};
			for (int i = 0; i < (sizeof(SetArchHT) / 4); i++) {
				if (SetArchHT[i] == itemId)
					return true;
			}
		}
		if (pMob[conn].FiltroID[11] == 1) {
			int ArmaDHT[] = {
				825, //Arco_Divino,32.0,156.162.0.240.0,42,125000,64,2547,0,EF_CLASS,10,EF_GRID,0,EF_DAMAGE,258,EF_RANGE,5,EF_WTYPE,101,EF_ATTSPEED,1,EF_ITEMLEVEL,4
				840, //Garra_Draconiana,34.0,158.219.0.0.192,43,129000,64,2607,0,EF_CLASS,9,EF_GRID,0,EF_DAMAGE,307,EF_RANGE,0,EF_WTYPE,41,EF_AC,34,EF_ITEMLEVEL,4,EF_DEX,45
				870 //Espada_Vorpal,36.0,156.395.0.268.0,45,123000,192,2727,0,EF_CLASS,255,EF_GRID,0,EF_DAMAGE,228,EF_RANGE,2,EF_WTYPE,1,EF_ITEMLEVEL,4

			};
			for (int i = 0; i < (sizeof(ArmaDHT) / 4); i++) {
				if (ArmaDHT[i] == itemId)
					return true;
			}
		}
		if (pMob[conn].FiltroID[12] == 1) {
			int ArmaEHT[] = {
				3556, //Arco_Guardião,2809.0,260.0.0.0.0,42,251000,64,3621,0,EF_CLASS,10,EF_GRID,0,EF_DAMAGE,290,EF_RANGE,5,EF_WTYPE,101,EF_ATTSPEED,1,EF_MOBTYPE,2,EF_ITEMLEVEL,5
				3561, //Dianus,2810.0,254.0.0.0.0,43,251000,64,3641,0,EF_CLASS,9,EF_GRID,0,EF_DAMAGE,340,EF_RANGE,0,EF_WTYPE,41,EF_AC,40,EF_MOBTYPE,2,EF_ITEMLEVEL,5,EF_DEX,60
				3571 //Vingadora,2813.0,257.0.0.0.0,45,251000,192,3681,0,EF_CLASS,255,EF_GRID,0,EF_DAMAGE,245,EF_RANGE,2,EF_WTYPE,1,EF_MOBTYPE,2,EF_ITEMLEVEL,5

			};
			for (int i = 0; i < (sizeof(ArmaEHT) / 4); i++) {
				if (ArmaEHT[i] == itemId)
					return true;
			}
		}
		if (pMob[conn].FiltroID[13] == 1) {
			int ArmaArchHT[] = {
				826, //Skytalos,762.0,290.0.0.0.0,42,270000,64,2551,0,EF_CLASS,10,EF_GRID,0,EF_DAMAGE,305,EF_RANGE,5,EF_WTYPE,101,EF_ATTSPEED,1,EF_MOBTYPE,1,EF_ITEMLEVEL,5
				841, //Khyrius,763.0,282.0.0.0.0,43,270000,64,2611,0,EF_CLASS,9,EF_GRID,0,EF_DAMAGE,354,EF_RANGE,1,EF_WTYPE,41,EF_AC,45,EF_MOBTYPE,1,EF_ITEMLEVEL,5,EF_DEX,75
				871 //Caliburn,766.0,285.0.0.0.0,45,270000,192,2731,0,EF_CLASS,255,EF_GRID,0,EF_DAMAGE,255,EF_RANGE,2,EF_WTYPE,1,EF_MOBTYPE,1,EF_ITEMLEVEL,5

			};
			for (int i = 0; i < (sizeof(ArmaArchHT) / 4); i++) {
				if (ArmaArchHT[i] == itemId)
					return true;
			}
		}
		if (pMob[conn].FiltroID[14] == 1) {
			int SetDTK[] = {
				1206, //Elmo_Embutido(N),14.0,141.219.0.0.147,8,138000,2,2186,1,EF_CLASS,1,EF_GRID,0,EF_AC,83,EF_SAVEMANA,8,EF_ITEMLEVEL,4
				1207, //Elmo_Embutido(M),14.0,148.230.0.0.154,8,142000,2,2186,2,EF_CLASS,1,EF_GRID,0,EF_AC,87,EF_SAVEMANA,9,EF_ITEMLEVEL,4
				1208, //Elmo_Embutido(A),14.0,154.239.0.0.160,8,145000,2,2186,3,EF_CLASS,1,EF_GRID,0,EF_AC,92,EF_SAVEMANA,9,EF_MPADD,10,EF_ITEMLEVEL,4
				1209, //Armadura_Embutida(N),14.0,147.228.0.0.153,8,188000,4,2187,1,EF_CLASS,1,EF_GRID,0,EF_AC,108,EF_HPADD,5,EF_ITEMLEVEL,4
				1210, //Armadura_Embutida(M),14.0,152.236.0.0.158,8,191000,4,2187,2,EF_CLASS,1,EF_GRID,0,EF_AC,114,EF_CRITICAL,45,EF_HPADD,5,EF_ITEMLEVEL,4
				1211, //Armadura_Embutida(A),14.0,159.246.0.0.165,8,195000,4,2187,3,EF_CLASS,1,EF_GRID,0,EF_AC,120,EF_CRITICAL,35,EF_HPADD,6,EF_ITEMLEVEL,4
				1212, //Calça_Embutida(N),14.0,144.224.0.0.150,8,170000,8,2188,1,EF_CLASS,1,EF_GRID,0,EF_AC,94,EF_HPADD,5,EF_ITEMLEVEL,4
				1213, //Calça_Embutida(M),14.0,150.233.0.0.156,8,173000,8,2188,2,EF_CLASS,1,EF_GRID,0,EF_AC,99,EF_CRITICAL,45,EF_HPADD,5,EF_ITEMLEVEL,4
				1214, //Calça_Embutida(A),14.0,157.243.0.0.163,8,176000,8,2188,3,EF_CLASS,1,EF_GRID,0,EF_AC,104,EF_CRITICAL,35,EF_HPADD,6,EF_ITEMLEVEL,4
				1215, //Manoplas_Embutidas(N),14.0,136.212.0.0.142,8,126000,16,2189,1,EF_CLASS,1,EF_GRID,0,EF_AC,73,EF_MPADD,7,EF_ITEMLEVEL,4
				1216, //Manoplas_Embutidas(M),14.0,142.221.0.0.148,8,129000,16,2189,2,EF_CLASS,1,EF_GRID,0,EF_AC,76,EF_ACADD,17,EF_MPADD,7,EF_ITEMLEVEL,4
				1217, //Manoplas_Embutidas(A),14.0,149.231.0.0.155,8,131000,16,2189,3,EF_CLASS,1,EF_GRID,0,EF_AC,80,EF_ACADD,17,EF_MPADD,8,EF_ITEMLEVEL,4
				1218, //Botas_Embutidas(N),14.0,139.216.0.0.145,8,141000,32,2190,1,EF_CLASS,1,EF_GRID,0,EF_AC,74,EF_RUNSPEED,2,EF_REGENMP,35,EF_ITEMLEVEL,4
				1219, //Botas_Embutidas(M),14.0,145.225.0.0.151,8,144000,32,2190,2,EF_CLASS,1,EF_GRID,0,EF_AC,78,EF_RUNSPEED,2,EF_REGENMP,35,EF_ITEMLEVEL,4
				1220 //Botas_Embutidas(A),14.0,151.234.0.0.157,8,148000,32,2190,3,EF_CLASS,1,EF_GRID,0,EF_AC,82,EF_RUNSPEED,2,EF_REGENMP,40,EF_ITEMLEVEL,4
			};
			for (int i = 0; i < (sizeof(SetDTK) / 4); i++) {
				if (SetDTK[i] == itemId)
					return true;
			}
		}
		if (pMob[conn].FiltroID[15] == 1) {
			int SetETK[] = {
				1225, //Elmo_Mortal,19.0,285.0.0.0.0,10,160000,2,3801,1,EF_CLASS,1,EF_GRID,0,EF_AC,108,EF_SAVEMANA,10,EF_MPADD,10,EF_ITEMLEVEL,5
				1226, //Armadura_Mortal,19.0,285.0.0.0.0,10,160000,4,3802,1,EF_CLASS,1,EF_GRID,0,EF_AC,138,EF_CRITICAL,50,EF_HPADD,9,EF_ITEMLEVEL,5
				1227, //Calça_Mortal,19.0,285.0.0.0.0,10,160000,8,3803,1,EF_CLASS,1,EF_GRID,0,EF_AC,122,EF_CRITICAL,50,EF_HPADD,9,EF_ITEMLEVEL,5
				1228, //Monaplas_Mortais,19.0,285.0.0.0.0,10,160000,16,3804,1,EF_CLASS,1,EF_GRID,0,EF_AC,94,EF_ACADD,20,EF_MPADD,8,EF_ITEMLEVEL,5
				1229, //Botas_Mortais,19.0,285.0.0.0.0,10,160000,32,3805,1,EF_CLASS,1,EF_GRID,0,EF_AC,96,EF_RUNSPEED,2,EF_REGENMP,40,EF_ITEMLEVEL,5
			};
			for (int i = 0; i < (sizeof(SetETK) / 4); i++) {
				if (SetETK[i] == itemId)
					return true;
			}
		}
		if (pMob[conn].FiltroID[16] == 1) {
			int SetArchTK[] = {
				1221, //Armadura_Flamejante,41.0,227.0.0.0.0,9,178000,4,2187,1,EF_CLASS,1,EF_GRID,0,EF_AC,156,EF_CRITICAL,45,EF_HPADD,8,EF_ITEMLEVEL,5,EF_MOBTYPE,1
				1222, //Calça_Flamejante,41.0,230.0.0.0.0,9,178000,8,2188,1,EF_CLASS,1,EF_GRID,0,EF_AC,135,EF_CRITICAL,45,EF_HPADD,8,EF_ITEMLEVEL,5,EF_MOBTYPE,1
				1223, //Manoplas_Flamejantes,41.0,220.0.0.0.0,9,176000,16,2189,1,EF_CLASS,1,EF_GRID,0,EF_AC,104,EF_ACADD,17,EF_MPADD,8,EF_ITEMLEVEL,5,EF_MOBTYPE,1
				1224, //Botas_Flamejantes,41.0,223.0.0.0.0,9,174000,32,2190,1,EF_CLASS,1,EF_GRID,0,EF_AC,106,EF_RUNSPEED,3,EF_REGENMP,40,EF_ITEMLEVEL,5,EF_MOBTYPE,1
			};
			for (int i = 0; i < (sizeof(SetArchTK) / 4); i++) {
				if (SetArchTK[i] == itemId)
					return true;
			}
		}
		if (pMob[conn].FiltroID[17] == 1) {
			int ArmaDTK[] = {
				810, //Martelo_Assassino,31.0,157.552.0.0.0,41,130000,192,2487,0,EF_CLASS,255,EF_GRID,0,EF_DAMAGE,229,EF_RANGE,2,EF_WTYPE,11,EF_ITEMLEVEL,4
				855, //Lança_do_Triunfo,35.0,158.145.243.0.0,44,133000,64,2667,0,EF_CLASS,5,EF_GRID,0,EF_DAMAGE,232,EF_RANGE,2,EF_WTYPE,21,EF_MAGIC,50,EF_ITEMLEVEL,4
				911 //Solaris,38.0,159.522.0.158.0,48,150000,64,2891,0,EF_CLASS,1,EF_GRID,0,EF_DAMAGE,333,EF_RANGE,2,EF_WTYPE,3,EF_ITEMLEVEL,4,EF_INT,60
			};
			for (int i = 0; i < (sizeof(ArmaDTK) / 4); i++) {
				if (ArmaDTK[i] == itemId)
					return true;
			}
		}
		if (pMob[conn].FiltroID[18] == 1) {
			int ArmaETK[] = {
				3551, //Asa_Draconiana,2805.0,257.0.0.0.0,41,251000,192,3601,0,EF_CLASS,255,EF_GRID,0,EF_DAMAGE,246,EF_RANGE,2,EF_WTYPE,11,EF_MOBTYPE,2,EF_ITEMLEVEL,5
				3591, //Éden,2807.0,259.0.0.0.0,48,251000,64,3761,0,EF_CLASS,1,EF_GRID,0,EF_DAMAGE,380,EF_RANGE,2,EF_WTYPE,3,EF_MOBTYPE,2,EF_ITEMLEVEL,5,EF_INT,75
				3596, //Demolidor_Celestial,2806.0,260.0.0.0.0,49,251000,64,3781,0,EF_CLASS,1,EF_GRID,0,EF_DAMAGE,382,EF_RANGE,2,EF_WTYPE,13,EF_MOBTYPE,2,EF_ITEMLEVEL,5,EF_CRITICAL,30
				3566 //Foice_Platinada,2812.0,260.0.0.0.0,44,251000,64,3661,0,EF_CLASS,5,EF_GRID,0,EF_DAMAGE,252,EF_RANGE,2,EF_WTYPE,21,EF_MAGIC,53,EF_MOBTYPE,2,EF_ITEMLEVEL,5
			};
			for (int i = 0; i < (sizeof(ArmaETK) / 4); i++) {
				if (ArmaETK[i] == itemId)
					return true;
			}
		}
		if (pMob[conn].FiltroID[19] == 1) {
			int ArmaArchTK[] = {
				811, //Balmung,758.0,285.0.0.0.0,41,270000,192,2491,0,EF_CLASS,255,EF_GRID,0,EF_DAMAGE,256,EF_RANGE,2,EF_WTYPE,11,EF_MOBTYPE,1,EF_ITEMLEVEL,5
				856, //Gleipnir,765.0,290.0.0.0.0,44,270000,64,2671,0,EF_CLASS,5,EF_GRID,0,EF_DAMAGE,258,EF_RANGE,2,EF_WTYPE,21,EF_MAGIC,55,EF_MOBTYPE,1,EF_ITEMLEVEL,5
				912 //Thrasytes,760.0,290.0.0.0.0,48,270000,64,2895,0,EF_CLASS,1,EF_GRID,0,EF_DAMAGE,396,EF_RANGE,2,EF_WTYPE,3,EF_MOBTYPE,1,EF_ITEMLEVEL,5,EF_INT,90
			};
			for (int i = 0; i < (sizeof(ArmaArchTK) / 4); i++) {
				if (ArmaArchTK[i] == itemId)
					return true;
			}
		}
		if (pMob[conn].FiltroID[20] == 1) {
			int SetDBM[] = {
				1491, //Elmo_Elemental(N),12.0,136.155.154.0.0,27,138000,2,2226,1,EF_CLASS,4,EF_GRID,0,EF_AC,80,EF_SAVEMANA,7,EF_ITEMLEVEL,4
				1492, //Elmo_Elemental(M),12.0,144.164.163.0.0,27,142000,2,2226,2,EF_CLASS,4,EF_GRID,0,EF_AC,85,EF_SAVEMANA,8,EF_ITEMLEVEL,4
				1493, //Elmo_Elemental(A),12.0,153.174.173.0.0,27,145000,2,2226,3,EF_CLASS,4,EF_GRID,0,EF_AC,90,EF_SAVEMANA,8,EF_MPADD,10,EF_ITEMLEVEL,4
				1494, //Armadura_Elemental(N),12.0,142.162.161.0.0,27,188000,4,2227,1,EF_CLASS,4,EF_GRID,0,EF_AC,104,EF_HPADD,5,EF_ITEMLEVEL,4
				1495, //Armadura_Elemental(M),12.0,150.171.170.0.0,27,191000,4,2227,2,EF_CLASS,4,EF_GRID,0,EF_AC,111,EF_CRITICAL,45,EF_HPADD,5,EF_ITEMLEVEL,4
				1496, //Armadura_Elemental(A),12.0,159.180.179.0.0,27,195000,4,2227,3,EF_CLASS,4,EF_GRID,0,EF_AC,118,EF_CRITICAL,35,EF_HPADD,6,EF_ITEMLEVEL,4
				1497, //Calça_Elemental(N),12.0,139.158.157.0.0,27,170000,8,2228,1,EF_CLASS,4,EF_GRID,0,EF_AC,91,EF_HPADD,5,EF_ITEMLEVEL,4
				1498, //Calça_Elemental(M),12.0,147.167.166.0.0,27,173000,8,2228,2,EF_CLASS,4,EF_GRID,0,EF_AC,96,EF_CRITICAL,45,EF_HPADD,5,EF_ITEMLEVEL,4
				1499, //Calça_Elemental(A),12.0,156.177.176.0.0,27,176000,8,2228,3,EF_CLASS,4,EF_GRID,0,EF_AC,101,EF_CRITICAL,35,EF_HPADD,6,EF_ITEMLEVEL,4
				1500, //Manoplas_Elementais(N),12.0,129.147.146.0.0,27,126000,16,2229,1,EF_CLASS,4,EF_GRID,0,EF_AC,72,EF_MPADD,6,EF_ITEMLEVEL,4
				1501, //Manoplas_Elementais(M),12.0,137.156.155.0.0,27,129000,16,2229,2,EF_CLASS,4,EF_GRID,0,EF_AC,74,EF_ACADD,17,EF_MPADD,6,EF_ITEMLEVEL,4
				1502, //Manoplas_Elementais(A),12.0,146.166.165.0.0,27,131000,16,2229,3,EF_CLASS,4,EF_GRID,0,EF_AC,78,EF_ACADD,17,EF_MPADD,7,EF_ITEMLEVEL,4
				1503, //Botas_Elementais(N),12.0,132.151.150.0.0,27,141000,32,2230,1,EF_CLASS,4,EF_GRID,0,EF_AC,73,EF_RUNSPEED,2,EF_REGENMP,30,EF_ITEMLEVEL,4
				1504, //Botas_Elementais(M),12.0,140.160.159.0.0,27,144000,32,2230,2,EF_CLASS,4,EF_GRID,0,EF_AC,76,EF_RUNSPEED,2,EF_REGENMP,30,EF_ITEMLEVEL,4
				1505 //Botas_Elementais(A),12.0,149.169.168.0.0,27,148000,32,2230,3,EF_CLASS,4,EF_GRID,0,EF_AC,79,EF_RUNSPEED,2,EF_REGENMP,35,EF_ITEMLEVEL,4
			};
			for (int i = 0; i < (sizeof(SetDBM) / 4); i++) {
				if (SetDBM[i] == itemId)
					return true;
			}
		}
		if (pMob[conn].FiltroID[21] == 1) {
			int SetEBM[] = {
				1510, //Elmo_do_Corvo,19.0,284.0.0.0.0,30,160000,2,3841,1,EF_CLASS,4,EF_GRID,0,EF_AC,100,EF_SAVEMANA,10,EF_MPADD,11,EF_ITEMLEVEL,5
				1511, //Armadura_do_Corvo,19.0,284.0.0.0.0,30,160000,4,3842,1,EF_CLASS,4,EF_GRID,0,EF_AC,128,EF_CRITICAL,45,EF_HPADD,8,EF_ITEMLEVEL,5
				1512, //Calça_do_Corvo,19.0,284.0.0.0.0,30,160000,8,3843,1,EF_CLASS,4,EF_GRID,0,EF_AC,110,EF_CRITICAL,45,EF_HPADD,8,EF_ITEMLEVEL,5
				1513, //Manoplas_do_Corvo,19.0,284.0.0.0.0,30,160000,16,3844,1,EF_CLASS,4,EF_GRID,0,EF_AC,86,EF_ACADD,20,EF_MPADD,9,EF_ITEMLEVEL,5
				1514 //Botas_do_Corvo,19.0,284.0.0.0.0,30,160000,32,3845,1,EF_CLASS,4,EF_GRID,0,EF_AC,88,EF_RUNSPEED,2,EF_REGENMP,45,EF_ITEMLEVEL,5
			};
			for (int i = 0; i < (sizeof(SetEBM) / 4); i++) {
				if (SetEBM[i] == itemId)
					return true;
			}
		}
		if (pMob[conn].FiltroID[22] == 1) {
			int SetArchBM[] = {
				1506, //Armadura_da_Destruição,41.0,227.0.0.0.0,29,178000,4,2227,1,EF_CLASS,4,EF_GRID,0,EF_AC,156,EF_CRITICAL,45,EF_HPADD,8,EF_ITEMLEVEL,5,EF_MOBTYPE,1
				1507, //Calça_da_Destruição,41.0,230.0.0.0.0,29,178000,8,2228,1,EF_CLASS,4,EF_GRID,0,EF_AC,135,EF_CRITICAL,45,EF_HPADD,8,EF_ITEMLEVEL,5,EF_MOBTYPE,1
				1508, //Manoplas_da_Derstruição,41.0,220.0.0.0.0,29,176000,16,2229,1,EF_CLASS,4,EF_GRID,0,EF_AC,104,EF_ACADD,17,EF_MPADD,8,EF_ITEMLEVEL,5,EF_MOBTYPE,1
				1509 //Botas_da_Destruição,41.0,223.0.0.0.0,29,174000,32,2230,1,EF_CLASS,4,EF_GRID,0,EF_AC,106,EF_RUNSPEED,2,EF_REGENMP,40,EF_ITEMLEVEL,5,EF_MOBTYPE,1
			};
			for (int i = 0; i < (sizeof(SetArchBM) / 4); i++) {
				if (SetArchBM[i] == itemId)
					return true;
			}
		}
		if (pMob[conn].FiltroID[23] == 1) {
			int ArmaDBM[] = {
				810, //Martelo_Assassino,31.0,157.552.0.0.0,41,130000,192,2487,0,EF_CLASS,255,EF_GRID,0,EF_DAMAGE,229,EF_RANGE,2,EF_WTYPE,11,EF_ITEMLEVEL,4
				855, //Lança_do_Triunfo,35.0,158.145.243.0.0,44,133000,64,2667,0,EF_CLASS,5,EF_GRID,0,EF_DAMAGE,232,EF_RANGE,2,EF_WTYPE,21,EF_MAGIC,50,EF_ITEMLEVEL,4
				885 //Cruz_Sagrada,37.0,158.256.0.237.0,46,122000,64,2787,0,EF_CLASS,5,EF_GRID,0,EF_DAMAGE,228,EF_RANGE,4,EF_WTYPE,103,EF_ATTSPEED,1,EF_ITEMLEVEL,4
			};
			for (int i = 0; i < (sizeof(ArmaDBM) / 4); i++) {
				if (ArmaDBM[i] == itemId)
					return true;
			}
		}
		if (pMob[conn].FiltroID[24] == 1) {
			int ArmaEBM[] = {
				3551, //Asa_Draconiana,2805.0,257.0.0.0.0,41,251000,192,3601,0,EF_CLASS,255,EF_GRID,0,EF_DAMAGE,246,EF_RANGE,2,EF_WTYPE,11,EF_MOBTYPE,2,EF_ITEMLEVEL,5
				3566, //Foice_Platinada,2812.0,260.0.0.0.0,44,251000,64,3661,0,EF_CLASS,5,EF_GRID,0,EF_DAMAGE,252,EF_RANGE,2,EF_WTYPE,21,EF_MAGIC,53,EF_MOBTYPE,2,EF_ITEMLEVEL,5
				3576 //Karikas,2814.0,258.0.0.0.0,46,251000,64,3701,0,EF_CLASS,5,EF_GRID,0,EF_DAMAGE,254,EF_RANGE,4,EF_WTYPE,103,EF_ATTSPEED,1,EF_MOBTYPE,2,EF_ITEMLEVEL,5
			};
			for (int i = 0; i < (sizeof(ArmaEBM) / 4); i++) {
				if (ArmaEBM[i] == itemId)
					return true;
			}
		}
		if (pMob[conn].FiltroID[25] == 1) {
			int ArmaArchBM[] = {
				811, //Balmung,758.0,285.0.0.0.0,41,270000,192,2491,0,EF_CLASS,255,EF_GRID,0,EF_DAMAGE,256,EF_RANGE,2,EF_WTYPE,11,EF_MOBTYPE,1,EF_ITEMLEVEL,5
				856, //Gleipnir,765.0,290.0.0.0.0,44,270000,64,2671,0,EF_CLASS,5,EF_GRID,0,EF_DAMAGE,258,EF_RANGE,2,EF_WTYPE,21,EF_MAGIC,55,EF_MOBTYPE,1,EF_ITEMLEVEL,5
				886 //Hermai,767.0,284.0.0.0.0,46,270000,64,2791,0,EF_CLASS,5,EF_GRID,0,EF_DAMAGE,264,EF_RANGE,4,EF_WTYPE,103,EF_ATTSPEED,1,EF_MOBTYPE,1,EF_ITEMLEVEL,5
			};
			for (int i = 0; i < (sizeof(ArmaArchBM) / 4); i++) {
				if (ArmaArchBM[i] == itemId)
					return true;
			}
		}
		if (pMob[conn].FiltroID[26] == 1) {
			int SetDFM[] = {
				1341,//Chapéu_de_Mytril(N),11.0,136.113.198.0.0,17,138000,2,2206,1,EF_CLASS,2,EF_GRID,0,EF_AC,79,EF_SAVEMANA,7,EF_ITEMLEVEL,4
				1342,//Chapéu_de_Mytril(M),11.0,144.120.209.0.0,17,142000,2,2206,2,EF_CLASS,2,EF_GRID,0,EF_AC,83,EF_SAVEMANA,8,EF_ITEMLEVEL,4
				1343,//Chapéu_de_Mytril(A),11.0,153.127.222.0.0,17,145000,2,2206,3,EF_CLASS,2,EF_GRID,0,EF_AC,89,EF_SAVEMANA,8,EF_MPADD,10,EF_ITEMLEVEL,4
				1344,//Túnica_de_Mytril(N),11.0,142.118.206.0.0,17,188000,4,2207,1,EF_CLASS,2,EF_GRID,0,EF_AC,103,EF_HPADD,5,EF_ITEMLEVEL,4
				1345,//Túnica_de_Mytril(M),11.0,150.125.218.0.0,17,191000,4,2207,2,EF_CLASS,2,EF_GRID,0,EF_AC,110,EF_CRITICAL,45,EF_HPADD,5,EF_ITEMLEVEL,4
				1346,//Túnica_de_Mytril(A),11.0,159.132.230.0.0,17,195000,4,2207,3,EF_CLASS,2,EF_GRID,0,EF_AC,117,EF_CRITICAL,35,EF_HPADD,6,EF_ITEMLEVEL,4
				1347,//Calça_de_Mytril(N),11.0,139.116.202.0.0,17,170000,8,2208,1,EF_CLASS,2,EF_GRID,0,EF_AC,90,EF_HPADD,5,EF_ITEMLEVEL,4
				1348,//Calça_de_Mytril(M),11.0,147.122.213.0.0,17,173000,8,2208,2,EF_CLASS,2,EF_GRID,0,EF_AC,95,EF_CRITICAL,45,EF_HPADD,5,EF_ITEMLEVEL,4
				1349,//Calça_de_Mytril(A),11.0,156.129.226.0.0,17,176000,8,2208,3,EF_CLASS,2,EF_GRID,0,EF_AC,100,EF_CRITICAL,35,EF_HPADD,6,EF_ITEMLEVEL,4
				1350,//Luvas_de_Mytril(N),11.0,129.108.188.0.0,17,126000,16,2209,1,EF_CLASS,2,EF_GRID,0,EF_AC,71,EF_MPADD,6,EF_ITEMLEVEL,4
				1351,//Luvas_de_Mytril(M),11.0,137.114.199.0.0,17,129000,16,2209,2,EF_CLASS,2,EF_GRID,0,EF_AC,73,EF_ACADD,17,EF_MPADD,6,EF_ITEMLEVEL,4
				1352,//Luvas_de_Mytril(A),11.0,146.121.212.0.0,17,131000,16,2209,3,EF_CLASS,2,EF_GRID,0,EF_AC,76,EF_ACADD,17,EF_MPADD,7,EF_ITEMLEVEL,4
				1353,//Botas_de_Mytril(N),11.0,132.110.192.0.0,17,141000,32,2210,1,EF_CLASS,2,EF_GRID,0,EF_AC,73,EF_RUNSPEED,2,EF_REGENMP,30,EF_ITEMLEVEL,4
				1354,//Botas_de_Mytril(M),11.0,140.117.204.0.0,17,144000,32,2210,2,EF_CLASS,2,EF_GRID,0,EF_AC,75,EF_RUNSPEED,2,EF_REGENMP,30,EF_ITEMLEVEL,4
				1355//Botas_de_Mytril(A),11.0,149.124.216.0.0,17,148000,32,2210,3,EF_CLASS,2,EF_GRID,0,EF_AC,78,EF_RUNSPEED,2,EF_REGENMP,35,EF_ITEMLEVEL,4
			};
			for (int i = 0; i < (sizeof(SetDFM) / 4); i++) {
				if (SetDFM[i] == itemId)
					return true;
			}
		}
		if (pMob[conn].FiltroID[27] == 1) {
			int SetEFM[] = {
				1360,//Elmo_Templário,19.0,281.0.0.0.0,20,160000,2,3821,1,EF_CLASS,2,EF_GRID,0,EF_AC,102,EF_SAVEMANA,10,EF_MPADD,11,EF_ITEMLEVEL,5
				1361,//Túnica_Templária,19.0,281.0.0.0.0,20,160000,4,3822,1,EF_CLASS,2,EF_GRID,0,EF_AC,132,EF_CRITICAL,45,EF_HPADD,8,EF_ITEMLEVEL,5
				1362,//Calça_Templária,19.0,281.0.0.0.0,20,160000,8,3823,1,EF_CLASS,2,EF_GRID,0,EF_AC,112,EF_CRITICAL,45,EF_HPADD,8,EF_ITEMLEVEL,5
				1363,//Manoplas_Templárias,19.0,281.0.0.0.0,20,160000,16,3824,1,EF_CLASS,2,EF_GRID,0,EF_AC,88,EF_ACADD,20,EF_MPADD,9,EF_ITEMLEVEL,5
				1364//Botas_Templárias,19.0,281.0.0.0.0,20,160000,32,3825,1,EF_CLASS,2,EF_GRID,0,EF_AC,90,EF_RUNSPEED,2,EF_REGENMP,45,EF_ITEMLEVEL,5
			};
			for (int i = 0; i < (sizeof(SetEFM) / 4); i++) {
				if (SetEFM[i] == itemId)
					return true;
			}
		}
		if (pMob[conn].FiltroID[28] == 1) {
			int SetArchFM[] = {
				1356,//Túnica_Guardiã,41.0,227.0.0.0.0,19,178000,4,2207,1,EF_CLASS,2,EF_GRID,0,EF_AC,156,EF_CRITICAL,45,EF_HPADD,8,EF_ITEMLEVEL,5,EF_MOBTYPE,1
				1357,//Calça_Guardiã,41.0,230.0.0.0.0,19,178000,8,2208,1,EF_CLASS,2,EF_GRID,0,EF_AC,135,EF_CRITICAL,45,EF_HPADD,8,EF_ITEMLEVEL,5,EF_MOBTYPE,1
				1358,//Manoplas_Guardiãs,41.0,220.0.0.0.0,19,176000,16,2209,1,EF_CLASS,2,EF_GRID,0,EF_AC,104,EF_ACADD,17,EF_MPADD,8,EF_ITEMLEVEL,5,EF_MOBTYPE,1
				1359//Botas_Guardiãs,41.0,223.0.0.0.0,19,174000,32,2210,1,EF_CLASS,2,EF_GRID,0,EF_AC,106,EF_RUNSPEED,2,EF_REGENMP,40,EF_ITEMLEVEL,5,EF_MOBTYPE,1
			};
			for (int i = 0; i < (sizeof(SetArchFM) / 4); i++) {
				if (SetArchFM[i] == itemId)
					return true;
			}
		}	
		if (pMob[conn].FiltroID[29] == 1) {
			int ArmaDFM[] = {
				825, //Arco_Divino,32.0,156.162.0.240.0,42,125000,64,2547,0,EF_CLASS,10,EF_GRID,0,EF_DAMAGE,258,EF_RANGE,5,EF_WTYPE,101,EF_ATTSPEED,1,EF_ITEMLEVEL,4
				870, //Espada_Vorpal,36.0,156.395.0.268.0,45,123000,192,2727,0,EF_CLASS,255,EF_GRID,0,EF_DAMAGE,228,EF_RANGE,2,EF_WTYPE,1,EF_ITEMLEVEL,4
				902, //Cajado_de_Âmbar,916.0,150.81.231.0.0,47,85000,192,2855,0,EF_CLASS,2,EF_GRID,0,EF_DAMAGE,162,EF_RANGE,1,EF_WTYPE,31,EF_MAGIC,24,EF_ITEMLEVEL,4
				900 //Fúria_Divina,33.0,157.147.446.0.0,47,128000,64,2847,0,EF_CLASS,2,EF_GRID,0,EF_DAMAGE,223,EF_RANGE,2,EF_WTYPE,32,EF_MAGIC,50,EF_ITEMLEVEL,4
			};
			for (int i = 0; i < (sizeof(ArmaDFM) / 4); i++) {
				if (ArmaDFM[i] == itemId)
					return true;
			}
		}
		if (pMob[conn].FiltroID[30] == 1) {
			int ArmaEFM[] = {
				3556, //Arco_Guardião,2809.0,260.0.0.0.0,42,251000,64,3621,0,EF_CLASS,10,EF_GRID,0,EF_DAMAGE,290,EF_RANGE,5,EF_WTYPE,101,EF_ATTSPEED,1,EF_MOBTYPE,2,EF_ITEMLEVEL,5
				3571, //Vingadora,2813.0,257.0.0.0.0,45,251000,192,3681,0,EF_CLASS,255,EF_GRID,0,EF_DAMAGE,245,EF_RANGE,2,EF_WTYPE,1,EF_MOBTYPE,2,EF_ITEMLEVEL,5
				3582, //Cajado_Caótico,2808.0,259.0.0.0.0,47,251000,64,3725,0,EF_CLASS,2,EF_GRID,0,EF_DAMAGE,226,EF_RANGE,2,EF_WTYPE,32,EF_MAGIC,55,EF_MOBTYPE,2,EF_ITEMLEVEL,5
				3581, //Força_Eterna,2815.0,255.0.0.0.0,47,251000,192,3721,0,EF_CLASS,2,EF_GRID,0,EF_DAMAGE,164,EF_RANGE,1,EF_WTYPE,31,EF_MAGIC,30,EF_MOBTYPE,2,EF_ITEMLEVEL,5
			};
			for (int i = 0; i < (sizeof(ArmaEFM) / 4); i++) {
				if (ArmaEFM[i] == itemId)
					return true;
			}
		}
		if (pMob[conn].FiltroID[31] == 1) {
			int ArmaArchFM[] = {
				826, //Skytalos,762.0,290.0.0.0.0,42,270000,64,2551,0,EF_CLASS,10,EF_GRID,0,EF_DAMAGE,305,EF_RANGE,5,EF_WTYPE,101,EF_ATTSPEED,1,EF_MOBTYPE,1,EF_ITEMLEVEL,5
				871, //Caliburn,766.0,285.0.0.0.0,45,270000,192,2731,0,EF_CLASS,255,EF_GRID,0,EF_DAMAGE,255,EF_RANGE,2,EF_WTYPE,1,EF_MOBTYPE,1,EF_ITEMLEVEL,5
				903, //Eirenus,761.0,288.0.0.0.0,47,270000,64,2863,0,EF_CLASS,2,EF_GRID,0,EF_DAMAGE,230,EF_RANGE,2,EF_WTYPE,32,EF_MAGIC,57,EF_MOBTYPE,1,EF_ITEMLEVEL,5
				904 //Neorion,768.0,284.0.0.0.0,47,270000,192,2859,0,EF_CLASS,2,EF_GRID,0,EF_DAMAGE,170,EF_RANGE,1,EF_WTYPE,31,EF_MAGIC,32,EF_MOBTYPE,1,EF_ITEMLEVEL,5
			};
			for (int i = 0; i < (sizeof(ArmaArchFM) / 4); i++) {
				if (ArmaArchFM[i] == itemId)
					return true;
			}
		}

		//SendMsgExp(conn, strFmt("Item [%s - ID [%d]] foi deletado pelo autodrop.", g_pItemList[itemId].Name, itemId), TNColor::GreenYellow, false);
		return false;
	}
	else
		return true;
}

bool AgroupList(int conn, int itemId)
{
	//Box Quest
	if (itemId >= 4117 && itemId <= 4121)
		return true;

	//Olho Crescente
	if (itemId == 481)
		return true;

	if (pMob[conn].MOB.Equip[13].sIndex == 3901 || pMob[conn].MOB.Equip[13].sIndex == 3902 || pMob[conn].MOB.Equip[13].sIndex == 3916) {

		int List[] = {
			4026, //Moeda 1kk
			4019, //Classe_D
			4020, //Classe_E
			419, //Resto_de_Oriharucon
			420, //Resto_de_Lactolerium
			412, //Poeira_de_Oriharucon
			413, //Poeira_de_Lactolerium
			578, //Pedra_de_Adamantita
			2441, //Diamante
			2442, //Esmeralda
			2443, //Coral
			2444, //Garnet
			1774, //Pedra_do_Sábio
			3140, //Pedra_da_Luz
			2396, //Âmago_de_Cav_s/Sela_N
			2397, //Âmago_de_Cav_Fantasm_N
			2398, //Âmago_de_Cavalo_Leve_N
			2399, //Âmago_de_Cavalo_Equip_N
			2400, //Âmago_de_Andaluz_N
			2401, //Âmago_de_Ca_s/Sela_B
			2402, //Âmago_de_Cav_Fantasm_B
			2403, //Âmago_de_Cavalo_Leve_B
			2404, //Âmago_de_Cavalo_Equip_B
			2405, //Âmago_de_Andaluz_B
			2406, //Âmago_de_Fenrir
			2411, //Âmago_de_Unicórnio
			2412, //Âmago_de_Pégasus
			2413, //Âmago_de_Unisus
			2390, //Âmago_de_Porco
			2391, //Âmago_de_Javali
			2392, //Âmago_de_Lobo
			2393, //Âmago_de_Dragão_Menor
			2394, //Âmago_de_Urso
			2395 //Âmago_de_Dente_de_Sabre
		};

		for (int i = 0; i < (sizeof(List) / 4); i++) {
			if (itemId == List[i])
				return true;
		}
		return false;
	}
	return false;
}

bool LogList(int itemId)
{
	int List[] = {
		4026, //Moeda 1kk
		412, //Poeira_de_Oriharucon
		413, //Poeira_de_Lactolerium
		1774, //Pedra_do_Sábio
		2441, //Diamante
		2442, //Esmeralda
		2443, //Coral
		2444, //Garnet
		3140, //Pedra_da_Luz
		2399, //Âmago_de_Cavalo_Equip_N
		2404, //Âmago_de_Cavalo_Equip_B
		2400, //Âmago_de_Andaluz_N
		2405, //Âmago_de_Andaluz_B
		2411, //Âmago_de_Unicórnio
		2412, //Âmago_de_Pégasus
		2413, //Âmago_de_Unisus
		2414, //Âmago_de_Grifo
		2416, //Âmago_de_Grifo_Sang
		2417, //Âmago_de_Svadilfari
		2418, //Âmago_de_Sleipnir
		2409, //Âmago_de_Tigre_de_Fogo
		2410, //Âmago_de_Dragão_Verm
		1741, //Alma_da_Fênix
		1740, //Alma_do_Unicórnio
		1742, //Pedra_da_Imortalidade
		5110, //Ansuz
		5111, //Uraz
		5112, //Thurisaz
		5113, //Fehu
		5114, //Raidho
		5115, //Kenaz
		5116, //Naudhiz
		5117, //Gebo
		5118, //Wunjo
		5119, //Hagalaz
		5120, //Isa
		5121, //Jara
		5122, //Eihwaz
		5123, //Perthro
		5124, //Elhaz
		5125, //Sowilo
		5126, //Berkano
		5127, //Ehwaz
		5128, //Tiwaz
		5129, //Mannaz
		5130, //Laguz
		5131, //Dagaz
		5132, //Ing
		5133, //Othel
	};

	for (int i = 0; i < (sizeof(List) / 4); i++) {
		if (itemId == List[i])
			return true;
	}
	return false;
}

void CartaDrop(int conn, int target, int type)
{
	if (type == 1) {
		STRUCT_ITEM item;
		memset(&item, 0, sizeof(STRUCT_ITEM));

		int _rand = rand() % 16;

		if (_rand == 0 || _rand == 1 || _rand == 2)
			item.sIndex = 412; //Poeira Ori

		else if (_rand == 5)
			item.sIndex = 413; //Poeira Lac

		else if (_rand == 12)
			item.sIndex = 421; //cristal i

		else if (_rand == 15)
			item.sIndex = 422; //cristal ii

		SetItemBonus(&item, 0, 0, 0);

		//agrupador automatico teste
		if (AgroupList(conn, item.sIndex) == true && item.sIndex != 0) {
			SendItemagrupar(conn, item.sIndex);

			if (LogList(item.sIndex) == true) {
				snprintf(temp, sizeof(temp), "MobName:%s dropou o item: %s:%d %d.%d.%d.%d.%d.%d do mob:%s", pMob[conn].MOB.MobName, g_pItemList[item.sIndex].Name, item.sIndex, item.stEffect[0].cEffect, item.stEffect[0].cValue, item.stEffect[1].cEffect, item.stEffect[1].cValue, item.stEffect[2].cEffect, item.stEffect[2].cValue, pMob[target].MOB.MobName);
				MobDropLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, temp);
			}

			return;
		}

		if (PutItem(conn, &item) && item.sIndex != 0)
		{
			if (LogList(item.sIndex) == true) {
				snprintf(temp, sizeof(temp), "MobName:%s dropou o item: %s:%d %d.%d.%d.%d.%d.%d do mob:%s", pMob[conn].MOB.MobName, g_pItemList[item.sIndex].Name, item.sIndex, item.stEffect[0].cEffect, item.stEffect[0].cValue, item.stEffect[1].cEffect, item.stEffect[1].cValue, item.stEffect[2].cEffect, item.stEffect[2].cValue, pMob[target].MOB.MobName);
				MobDropLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, temp);
			}

			return;
		}
	}

	if (type == 2) {
		STRUCT_ITEM item;
		memset(&item, 0, sizeof(STRUCT_ITEM));

		int _rand = rand() % 16;

		if (_rand == 0 || _rand == 1)
			item.sIndex = 412; //Poeira Ori

		else if (_rand == 5)
			item.sIndex = 413; //Poeira Lac

		else if (_rand == 15)
			item.sIndex = 423; // cristal iii

		SetItemBonus(&item, 0, 0, 0);

		//agrupador automatico teste
		if (AgroupList(conn, item.sIndex) == true && item.sIndex != 0) {
			SendItemagrupar(conn, item.sIndex);

			if (LogList(item.sIndex) == true) {
				snprintf(temp, sizeof(temp), "MobName:%s dropou o item: %s:%d %d.%d.%d.%d.%d.%d do mob:%s", pMob[conn].MOB.MobName, g_pItemList[item.sIndex].Name, item.sIndex, item.stEffect[0].cEffect, item.stEffect[0].cValue, item.stEffect[1].cEffect, item.stEffect[1].cValue, item.stEffect[2].cEffect, item.stEffect[2].cValue, pMob[target].MOB.MobName);
				MobDropLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, temp);
			}

			return;
		}

		if (PutItem(conn, &item) && item.sIndex != 0)
		{
			if (LogList(item.sIndex) == true) {
				snprintf(temp, sizeof(temp), "MobName:%s dropou o item: %s:%d %d.%d.%d.%d.%d.%d do mob:%s", pMob[conn].MOB.MobName, g_pItemList[item.sIndex].Name, item.sIndex, item.stEffect[0].cEffect, item.stEffect[0].cValue, item.stEffect[1].cEffect, item.stEffect[1].cValue, item.stEffect[2].cEffect, item.stEffect[2].cValue, pMob[target].MOB.MobName);
				MobDropLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, temp);
			}

			return;
		}
	}
	if (type == 3) {
		STRUCT_ITEM item;
		memset(&item, 0, sizeof(STRUCT_ITEM));

		int _rand = rand() % 23;

		if (_rand == 0 || _rand == 1)
			item.sIndex = 2444; //Garnet

		else if (_rand == 2 || _rand == 3)
			item.sIndex = 2443; //Coral

		else if (_rand == 4 || _rand == 5)
			item.sIndex = 2442; //Diamante

		else if (_rand == 6 || _rand == 7)
			item.sIndex = 2441; //Esmeralda

		else if (_rand == 17 || _rand == 18)
			item.sIndex = 424; //cristal iv

		else if (_rand == 22)
			item.sIndex = 425; //cristal v

		SetItemBonus(&item, 0, 0, 0);

		//agrupador automatico teste
		if (AgroupList(conn, item.sIndex) == true && item.sIndex != 0) {
			SendItemagrupar(conn, item.sIndex);

			if (LogList(item.sIndex) == true) {
				snprintf(temp, sizeof(temp), "MobName:%s dropou o item: %s:%d %d.%d.%d.%d.%d.%d do mob:%s", pMob[conn].MOB.MobName, g_pItemList[item.sIndex].Name, item.sIndex, item.stEffect[0].cEffect, item.stEffect[0].cValue, item.stEffect[1].cEffect, item.stEffect[1].cValue, item.stEffect[2].cEffect, item.stEffect[2].cValue, pMob[target].MOB.MobName);
				MobDropLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, temp);
			}

			return;
		}

		if (PutItem(conn, &item) && item.sIndex != 0)
		{
			if (LogList(item.sIndex) == true) {
				snprintf(temp, sizeof(temp), "MobName:%s dropou o item: %s:%d %d.%d.%d.%d.%d.%d do mob:%s", pMob[conn].MOB.MobName, g_pItemList[item.sIndex].Name, item.sIndex, item.stEffect[0].cEffect, item.stEffect[0].cValue, item.stEffect[1].cEffect, item.stEffect[1].cValue, item.stEffect[2].cEffect, item.stEffect[2].cValue, pMob[target].MOB.MobName);
				MobDropLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, temp);
			}

			return;
		}
	}
	if (type == 4) {
		STRUCT_ITEM item;
		memset(&item, 0, sizeof(STRUCT_ITEM));

		int _rand = rand() % 18;

		if (_rand == 0 || _rand == 1 || _rand == 2 || _rand == 3)
			item.sIndex = 412; //Poeira Ori

		else if (_rand == 5 || _rand == 6)
			item.sIndex = 413; //Poeira Lac

		else if (_rand == 14)
			item.sIndex = 427; //cristal vii

		else if (_rand == 17)
			item.sIndex = 426; //cristal vi


		SetItemBonus(&item, 0, 0, 0);

		//agrupador automatico teste
		if (AgroupList(conn, item.sIndex) == true && item.sIndex != 0) {
			SendItemagrupar(conn, item.sIndex);

			if (LogList(item.sIndex) == true) {
				snprintf(temp, sizeof(temp), "MobName:%s dropou o item: %s:%d %d.%d.%d.%d.%d.%d do mob:%s", pMob[conn].MOB.MobName, g_pItemList[item.sIndex].Name, item.sIndex, item.stEffect[0].cEffect, item.stEffect[0].cValue, item.stEffect[1].cEffect, item.stEffect[1].cValue, item.stEffect[2].cEffect, item.stEffect[2].cValue, pMob[target].MOB.MobName);
				MobDropLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, temp);
			}

			return;
		}

		if (PutItem(conn, &item) && item.sIndex != 0)
		{
			if (LogList(item.sIndex) == true) {
				snprintf(temp, sizeof(temp), "MobName:%s dropou o item: %s:%d %d.%d.%d.%d.%d.%d do mob:%s", pMob[conn].MOB.MobName, g_pItemList[item.sIndex].Name, item.sIndex, item.stEffect[0].cEffect, item.stEffect[0].cValue, item.stEffect[1].cEffect, item.stEffect[1].cValue, item.stEffect[2].cEffect, item.stEffect[2].cValue, pMob[target].MOB.MobName);
				MobDropLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, temp);
			}

			return;
		}
	}
}
void LanDrop(int conn, int target)
{
	int Lan = 0;

	if (pMob[conn].TargetX > 3604 && pMob[conn].TargetY > 3604 && pMob[conn].TargetX < 3691 && pMob[conn].TargetY < 3690)
		Lan = 0;

	if (pMob[conn].TargetX > 3732 && pMob[conn].TargetY > 3476 && pMob[conn].TargetX < 3819 && pMob[conn].TargetY < 3563)
		Lan = 1;

	if (pMob[conn].TargetX > 3860 && pMob[conn].TargetY > 3604 && pMob[conn].TargetX < 3946 && pMob[conn].TargetY < 3690)
		Lan = 2;


	STRUCT_ITEM item;
	memset(&item, 0, sizeof(STRUCT_ITEM));
		
	int _rand = rand() % 100;

	if (Lan == 0) {

		// resto ori 30%
		if (_rand > 0 && _rand < 30) {
			item.sIndex = 419;
			item.stEffect[0].cEffect = 0;
			item.stEffect[0].cValue = 0;
			item.stEffect[1].cEffect = 0;
			item.stEffect[1].cValue = 0;
			item.stEffect[2].cEffect = 0;
			item.stEffect[2].cValue = 0;
		}

		// resto de lac 20%
		if (_rand > 31 && _rand < 50) {
			item.sIndex = 420;
			item.stEffect[0].cEffect = 0;
			item.stEffect[0].cValue = 0;
			item.stEffect[1].cEffect = 0;
			item.stEffect[1].cValue = 0;
			item.stEffect[2].cEffect = 0;
			item.stEffect[2].cValue = 0;
		}

		//classe D 10%
		if (_rand > 50 && _rand < 60) {
			item.sIndex = 4019;
			item.stEffect[0].cEffect = 0;
			item.stEffect[0].cValue = 0;
			item.stEffect[1].cEffect = 0;
			item.stEffect[1].cValue = 0;
			item.stEffect[2].cEffect = 0;
			item.stEffect[2].cValue = 0;
		}

		// Amago 5%
		if (_rand > 70 && _rand < 76) {
			item.sIndex = 2404;
			item.stEffect[0].cEffect = 0;
			item.stEffect[0].cValue = 0;
			item.stEffect[1].cEffect = 0;
			item.stEffect[1].cValue = 0;
			item.stEffect[2].cEffect = 0;
			item.stEffect[2].cValue = 0;
		}

		// Amago 5%
		if (_rand > 80 && _rand < 86) {
			item.sIndex = 2399;
			item.stEffect[0].cEffect = 0;
			item.stEffect[0].cValue = 0;
			item.stEffect[1].cEffect = 0;
			item.stEffect[1].cValue = 0;
			item.stEffect[2].cEffect = 0;
			item.stEffect[2].cValue = 0;
		}

		// Barra 1kk 10%
		if (_rand > 89 && _rand < 99) {
			item.sIndex = 4026;
			item.stEffect[0].cEffect = 0;
			item.stEffect[0].cValue = 0;
			item.stEffect[1].cEffect = 0;
			item.stEffect[1].cValue = 0;
			item.stEffect[2].cEffect = 0;
			item.stEffect[2].cValue = 0;
		}
	}

	if (Lan == 1) {

		// resto ori 30%
		if (_rand > 0 && _rand < 30) {
			item.sIndex = 419;
			item.stEffect[0].cEffect = 0;
			item.stEffect[0].cValue = 0;
			item.stEffect[1].cEffect = 0;
			item.stEffect[1].cValue = 0;
			item.stEffect[2].cEffect = 0;
			item.stEffect[2].cValue = 0;
		}

		// resto de lac 20%
		if (_rand > 31 && _rand < 50) {
			item.sIndex = 420;
			item.stEffect[0].cEffect = 0;
			item.stEffect[0].cValue = 0;
			item.stEffect[1].cEffect = 0;
			item.stEffect[1].cValue = 0;
			item.stEffect[2].cEffect = 0;
			item.stEffect[2].cValue = 0;
		}

		//classe E 5%
		if (_rand > 51 && _rand < 57) {
			item.sIndex = 4020;
			item.stEffect[0].cEffect = 0;
			item.stEffect[0].cValue = 0;
			item.stEffect[1].cEffect = 0;
			item.stEffect[1].cValue = 0;
			item.stEffect[2].cEffect = 0;
			item.stEffect[2].cValue = 0;
		}

		// Amago 4%
		if (_rand > 60 && _rand < 65) {
			item.sIndex = 2400;
			item.stEffect[0].cEffect = 0;
			item.stEffect[0].cValue = 0;
			item.stEffect[1].cEffect = 0;
			item.stEffect[1].cValue = 0;
			item.stEffect[2].cEffect = 0;
			item.stEffect[2].cValue = 0;
		}
		// Amago 4%
		if (_rand > 70 && _rand < 75) {
			item.sIndex = 2405;
			item.stEffect[0].cEffect = 0;
			item.stEffect[0].cValue = 0;
			item.stEffect[1].cEffect = 0;
			item.stEffect[1].cValue = 0;
			item.stEffect[2].cEffect = 0;
			item.stEffect[2].cValue = 0;
		}
		// Barra 1kk 10%
		if (_rand > 89 && _rand < 99) {
			item.sIndex = 4026;
			item.stEffect[0].cEffect = 0;
			item.stEffect[0].cValue = 0;
			item.stEffect[1].cEffect = 0;
			item.stEffect[1].cValue = 0;
			item.stEffect[2].cEffect = 0;
			item.stEffect[2].cValue = 0;
		}
	}

	//Filtro de Drop
	if (AutoDrop(conn, item.sIndex) == false && item.sIndex != 0)
		return;

	//agrupador automatico teste
	if (AgroupList(conn, item.sIndex) == true && item.sIndex != 0) {
		SendItemagrupar(conn, item.sIndex);

		if (LogList(item.sIndex) == true) {
			snprintf(temp, sizeof(temp), "MobName:%s dropou o item: %s:%d %d.%d.%d.%d.%d.%d do mob:%s", pMob[conn].MOB.MobName, g_pItemList[item.sIndex].Name, item.sIndex, item.stEffect[0].cEffect, item.stEffect[0].cValue, item.stEffect[1].cEffect, item.stEffect[1].cValue, item.stEffect[2].cEffect, item.stEffect[2].cValue, pMob[target].MOB.MobName);
			MobDropLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, temp);
		}

		return;
	}

	if (PutItem(conn, &item) && item.sIndex != 0)
	{
		if (LogList(item.sIndex) == true) {
			snprintf(temp, sizeof(temp), "MobName:%s dropou o item: %s:%d %d.%d.%d.%d.%d.%d do mob:%s", pMob[conn].MOB.MobName, g_pItemList[item.sIndex].Name, item.sIndex, item.stEffect[0].cEffect, item.stEffect[0].cValue, item.stEffect[1].cEffect, item.stEffect[1].cValue, item.stEffect[2].cEffect, item.stEffect[2].cValue, pMob[target].MOB.MobName);
			MobDropLog(pUser[conn].AccountName, pUser[conn].MacAddress, pUser[conn].IP, temp);
		}

		return;
	}
}