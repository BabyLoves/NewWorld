#include "main.h"
enum Costumes
{
	Quebrado,
	Valquiria,
	Esqeleto,
	Romana,
	KalintzM,
	KalintzF,
	Draco,
	Feiticeira,
	AnjoRed,
	AnjoWhite,
	RudolfRoxo,
	RudolfAzul,
	MilitarPreto,
	MilitarBranco,
	OcultoM,
	OcultoF,
	Skull,
	Anfitria,
	Charmosa,
	ReinoRed,
	ReinoBlue,
	Poseidon,
	Poseidon2,
	NoelM,
	Obscuro,
	Dancarina,
	Nordica,
	Zyra,
	Oriental,
	Praiana,
	Hera,
	CoelinhaRoxo,
	AnubisF,
	Futurista,
	BrazilF,
	Vazio,
	Teste,
	Teste2,
	Teste3,
	Teste4,
	Teste5,
	Teste6,
	Teste7,
	Teste8,
	Teste9,
	Teste10,
	Teste11,
	Teste12,
	Teste13,
	Teste14,
	Teste15,
	Teste16,
	Teste17,
	Teste18,
	Teste19,
	Teste20,
	Teste21,
	Teste22,
	Teste23,
	Teste24,
	Teste25,
	Teste26,
	Teste27,
	Teste28,
	Teste29,
	Teste30,
	Teste31,
	Teste32,
	Teste33,
	Teste34,
	Teste35,
	Teste36,
	Teste37,
	Teste38,
	Teste39,
	Teste40,
	Teste41,
	Teste42,
	Teste43,
	Teste44,
	Teste45,
	Teste46,
	Teste47,
	Teste48,
	Teste49,
	Teste50
};

enum Bones
{
	Masculino,
	Feminino
};

bool BoneTrajeFemino(INT32 Item)
{
	if (Item == 4200 && Item >= 4431 && Item <= 4499)
		return false;

}

bool BoneTrajeMasculino(INT32 Item)
{

	if (Item >= 4331 && Item <= 4399)
		return false;

}

void HKD_FixIndex(DWORD* sTraje, int32_t* Costume)
{
	int ItemID = *(WORD*)((int)sTraje + 2656);

	switch (ItemID)
	{
	case 4200:
	{
		*Costume = Valquiria;
		break;
	}
	case 4201:
	{
		*Costume = Romana;
		break;
	}
	case 4202:
	{
		*Costume = KalintzM;
		break;
	}
	case 4203:
	{
		*Costume = KalintzF;
		break;
	}
	case 4204:
	{
		*Costume = Draco;
		break;
	}
	case 4205:
	{
		*Costume = Teste6;
		break;
	}
	case 4206:
	{
		*Costume = Teste7;
		break;
	}
	case 4207:
	{
		*Costume = Teste8;
		break;
	}
	case 4208:
	{
		*Costume = Teste9;
		break;
	}
	case 4209:
	{
		*Costume = Teste10;
		break;
	}
	case 4210:
	{
		*Costume = Teste11;
		break;
	}
	case 4211:
	{
		*Costume = Teste12;
		break;
	}
	case 4212:
	{
		*Costume = Teste13;
		break;
	}
	case 4213:
	{
		*Costume = Teste14;
		break;
	}
	case 4214:
	{
		*Costume = Skull;
		break;
	}
	case 4215:
	{
		*Costume = Teste16;
		break;
	}
	case 4216:
	{
		*Costume = Teste17;
		break;
	}
	case 4217:
	{
		*Costume = Teste18;
		break;
	}
	case 4218:
	{
		*Costume = Teste19;
		break;
	}
	case 4219:
	{
		*Costume = Teste20;
		break;
	}
	case 4220:
	{
		*Costume = Teste21;
		break;
	}
	case 4221:
	{
		*Costume = Teste22;
		break;
	}
	case 4222:
	{
		*Costume = Teste23;
		break;
	}
	case 4223:
	{
		*Costume = Teste24;
		break;
	}
	case 4224:
	{
		*Costume = Teste25;
		break;
	}
	case 4225:
	{
		*Costume = Teste26;
		break;
	}
	case 4226:
	{
		*Costume = Teste27;
		break;
	}
	case 4227:
	{
		*Costume = Teste28;
		break;
	}
	case 4228:
	{
		*Costume = Teste29;
		break;
	}
	case 4229:
	{
		*Costume = Teste30;
		break;
	}
	case 4230:
	{
		*Costume = Anfitria;
		break;
	}
	case 4231:
	{
		*Costume = Teste32;
		break;
	}
	case 4232:
	{
		*Costume = Teste33;
		break;
	}
	case 4233:
	{
		*Costume = Teste34;
		break;
	}
	case 4234:
	{
		*Costume = Teste35;
		break;
	}
	case 4235:
	{
		*Costume = Teste36;
		break;
	}
	case 4236:
	{
		*Costume = Teste37;
		break;
	}
	case 4237:
	{
		*Costume = Teste38;
		break;
	}
	case 4238:
	{
		*Costume = ReinoRed;
		break;
	}
	case 4239:
	{
		*Costume = ReinoBlue;
		break;
	}
	case 4240:
	{
		*Costume = Poseidon;
		break;
	}
	case 4241:
	{
		*Costume = Dancarina;
		break;
	}
	case 4242:
	{
		*Costume = Teste43;
		break;
	}
	case 4243:
	{
		*Costume = Teste44;
		break;
	}
	case 4244:
	{
		*Costume = Teste45;
		break;
	}
	case 4245:
	{
		*Costume = Zyra;
		break;
	}
	case 4246:
	{
		*Costume = AnubisF;
		break;
	}
	case 4247:
	{
		*Costume = Futurista;
		break;
	}
	case 4248:
	{
		*Costume = Hera;
		break;
	}
	case 4249:
	{
		*Costume = MilitarBranco;
		break;
	}
	case 4250:
	{
		*Costume = MilitarPreto;
		break;
	}
	default:
		break;
	}
}

void HKD_CorrectBone(int32_t index, int32_t* bone)
{
	/*Hook feito por [GUGARMP] */
	switch (index)
	{
	case Valquiria:
		*bone = Feminino;
		break;
	case Esqeleto:
		*bone = Masculino;
		break;
	case Romana:
		*bone = Feminino;
		break;
	case KalintzM:
		*bone = Masculino;
		break;
	case KalintzF:
		*bone = Feminino;
		break;
	case Draco:
		*bone = Masculino;
		break;
	case Feiticeira:
		*bone = Feminino;
		break;
	case AnjoRed:
		*bone = Feminino;
		break;
	case AnjoWhite:
		*bone = Feminino;
		break;
	case RudolfRoxo:
		*bone = Feminino;
		break;
	case RudolfAzul:
		*bone = Feminino;
		break;
	case MilitarPreto:
		*bone = Feminino;
		break;
	case MilitarBranco:
		*bone = Feminino;
		break;
	case OcultoM:
		*bone = Masculino;
		break;
	case OcultoF:
		*bone = Feminino;
		break;
	case Skull:
		*bone = Masculino;
		break;
	case Anfitria:
		*bone = Feminino;
		break;
	case Charmosa:
		*bone = Feminino;
		break;
	case ReinoRed:
		*bone = Masculino;
		break;
	case ReinoBlue:
		*bone = Masculino;
		break;
	case Poseidon:
		*bone = Masculino;
		break;
	case Poseidon2:
		*bone = Masculino;
		break;
	case NoelM:
		*bone = Masculino;
		break;
	case Obscuro:
		*bone = Masculino;
		break;
	case Dancarina:
		*bone = Feminino;
		break;
	case Nordica:
		*bone = Feminino;
		break;
	case Zyra:
		*bone = Feminino;
		break;
	case Oriental:
		*bone = Masculino;
		break;
	case Praiana:
		*bone = Feminino;
		break;
	case Hera:
		*bone = Feminino;
		break;
	case CoelinhaRoxo:
		*bone = Feminino;
		break;
	case AnubisF:
		*bone = Feminino;
		break;
	case Futurista:
		*bone = Feminino;
		break;
	case BrazilF:
		*bone = Feminino;
		break;
	case Vazio:
		*bone = Masculino;
		break;
	case Teste:
		*bone = Masculino;
		break;
	case Teste2:
		*bone = Masculino;
		break;
	case Teste3:
		*bone = Masculino;
		break;
	case Teste4:
		*bone = Masculino;
		break;
	case Teste5:
		*bone = Masculino;
		break;
	case Teste6:
		*bone = Masculino;
		break;
	case Teste7:
		*bone = Feminino;
		break;
	case Teste8:
		*bone = Masculino;
		break;
	case Teste9:
		*bone = Masculino;
		break;
	case Teste10:
		*bone = Masculino;
		break;
	case Teste11:
		*bone = Masculino;
		break;
	case Teste12:
		*bone = Feminino;
		break;
	case Teste13:
		*bone = Masculino;
		break;
	case Teste14:
		*bone = Feminino;
		break;
	case Teste15:
		*bone = Masculino;
		break;
	case Teste16:
		*bone = Masculino;
		break;
	case Teste17:
		*bone = Masculino;
		break;
	case Teste18:
		*bone = Masculino;
		break;
	case Teste19:
		*bone = Masculino;
		break;
	case Teste20:
		*bone = Feminino;
		break;
	case Teste21:
		*bone = Feminino;
		break;
	case Teste22:
		*bone = Masculino;
		break;
	case Teste23:
		*bone = Masculino;
		break;
	case Teste24:
		*bone = Feminino;
		break;
	case Teste25:
		*bone = Feminino;
		break;
	case Teste26:
		*bone = Feminino;
		break;
	case Teste27:
		*bone = Feminino;
		break;
	case Teste28:
		*bone = Masculino;
		break;
	case Teste29:
		*bone = Feminino;
		break;
	case Teste30:
		*bone = Masculino;
		break;
	case Teste31:
		*bone = Masculino;
		break;
	case Teste32:
		*bone = Feminino;
		break;
	case Teste33:
		*bone = Feminino;
		break;
	case Teste34:
		*bone = Feminino;
		break;
	case Teste35:
		*bone = Feminino;
		break;
	case Teste36:
		*bone = Feminino;
		break;
	case Teste37:
		*bone = Feminino;
		break;
	case Teste38:
		*bone = Masculino;
		break;
	case Teste39:
		*bone = Feminino;
		break;
	case Teste40:
		*bone = Masculino;
		break;
	case Teste41:
		*bone = Masculino;
		break;
	case Teste42:
		*bone = Masculino;
		break;
	case Teste43:
		*bone = Feminino;
		break;
	case Teste44:
		*bone = Feminino;
		break;
	case Teste45:
		*bone = Masculino;
		break;
	case Teste46:
		*bone = Feminino;
		break;
	case Teste47:
		*bone = Feminino;
		break;
	case Teste48:
		*bone = Feminino;
		break;
	case Teste49:
		*bone = Feminino;
		break;
	case Teste50:
		*bone = Feminino;
		break;

	default:
		break;
	}

}

void HKD_LoadFile(int32_t index, char* textureName, char* meshName)
{
	/*Hook feito por [GUGARMP] */
	auto loadCostume = [textureName, meshName](char* texture, char* msh1, char* msh2, char* msh3, char* msh4, char* msh5, char* msh6)
	{
		auto counter = reinterpret_cast<int32_t*>(0x616D18);

		strcpy(textureName, texture);

		switch (*counter)
		{
		case 1:
			strcpy(meshName, msh1); *counter = 2;
			break;
		case 2:
			strcpy(meshName, msh2); *counter = 3;
			break;
		case 3:
			strcpy(meshName, msh3); *counter = 4;
			break;
		case 4:
			strcpy(meshName, msh4); *counter = 5;
			break;
		case 5:
			strcpy(meshName, msh5); *counter = 6;
			break;
		case 6:
			strcpy(meshName, msh6); *counter = 1;
			break;
		}
	};


	switch (index)
	{
	case Teste:
		loadCostume("mesh\\ch010144.wys",
			"mesh\\ch010144.msh",
			"mesh\\ch010244.msh",
			"mesh\\ch010344.msh",
			"mesh\\ch010444.msh",
			"mesh\\ch010544.msh",
			"mesh\\ch010144.msh");
		break;

	case Teste2:
		loadCostume("mesh\\ch010145.wys",
			"mesh\\ch010145.msh",
			"mesh\\ch010245.msh",
			"mesh\\ch010345.msh",
			"mesh\\ch010445.msh",
			"mesh\\ch010545.msh",
			"mesh\\ch010145.msh");
		break;

	case Teste3:
		loadCostume("mesh\\ch010165.wys",
			"mesh\\ch010165.msh",
			"mesh\\ch010265.msh",
			"mesh\\ch010365.msh",
			"mesh\\ch010465.msh",
			"mesh\\ch010565.msh",
			"mesh\\ch010165.msh");
		break;

	case Teste4:
		loadCostume("mesh\\ch010180.wys",
			"mesh\\ch010180.msh",
			"mesh\\ch010280.msh",
			"mesh\\ch010380.msh",
			"mesh\\ch010480.msh",
			"mesh\\ch010580.msh",
			"mesh\\ch010180.msh");
		break;

	case Teste5:
		loadCostume("mesh\\ch0101119.wys",
			"mesh\\ch0101119.msh",
			"mesh\\ch0102119.msh",
			"mesh\\ch0103119.msh",
			"mesh\\ch0104119.msh",
			"mesh\\ch0105119.msh",
			"mesh\\ch0106119.msh");
		break;

	case Teste6:
		loadCostume("mesh\\ch0101119.wys",
			"mesh\\ch0101119.msh",
			"mesh\\ch0102119.msh",
			"mesh\\ch0103119.msh",
			"mesh\\ch0104119.msh",
			"mesh\\ch0105119.msh",
			"mesh\\ch0106119.msh");
		break;

	case Teste7:
		loadCostume("mesh\\ch0101120.wys",
			"mesh\\ch0101120.msh",
			"mesh\\ch0102120.msh",
			"mesh\\ch0103120.msh",
			"mesh\\ch0104120.msh",
			"mesh\\ch0105120.msh",
			"mesh\\ch0106120.msh");
		break;

	case Teste8:
		loadCostume("mesh\\ch0101122.wys",
			"mesh\\ch0101122.msh",
			"mesh\\ch0102122.msh",
			"mesh\\ch0103122.msh",
			"mesh\\ch0104122.msh",
			"mesh\\ch0105122.msh",
			"mesh\\ch0106122.msh");
		break;

	case Teste9:
		loadCostume("mesh\\ch0101123.wys",
			"mesh\\ch0101123.msh",
			"mesh\\ch0102123.msh",
			"mesh\\ch0103123.msh",
			"mesh\\ch0104123.msh",
			"mesh\\ch0105123.msh",
			"mesh\\ch0106123.msh");
		break;

	case Teste10:
		loadCostume("mesh\\ch0101124.wys",
			"mesh\\ch0101124.msh",
			"mesh\\ch0102124.msh",
			"mesh\\ch0103124.msh",
			"mesh\\ch0104124.msh",
			"mesh\\ch0105124.msh",
			"mesh\\ch0106124.msh");
		break;

	case Teste11:
		loadCostume("mesh\\ch0101125.wys",
			"mesh\\ch0101125.msh",
			"mesh\\ch0102125.msh",
			"mesh\\ch0103125.msh",
			"mesh\\ch0104125.msh",
			"mesh\\ch0105125.msh",
			"mesh\\ch0106125.msh");
		break;

	case Teste12:
		loadCostume("mesh\\ch0101127.wys",
			"mesh\\ch0101127.msh",
			"mesh\\ch0102127.msh",
			"mesh\\ch0103127.msh",
			"mesh\\ch0104127.msh",
			"mesh\\ch0105127.msh",
			"mesh\\ch0106127.msh");
		break;

	case Teste13:
		loadCostume("mesh\\ch0101132.wys",
			"mesh\\ch0101132.msh",
			"mesh\\ch0102132.msh",
			"mesh\\ch0103132.msh",
			"mesh\\ch0104132.msh",
			"mesh\\ch0105132.msh",
			"mesh\\ch0106132.msh");
		break;

	case Teste14:
		loadCostume("mesh\\ch0101133.wys",
			"mesh\\ch0101133.msh",
			"mesh\\ch0102133.msh",
			"mesh\\ch0103133.msh",
			"mesh\\ch0104133.msh",
			"mesh\\ch0105133.msh",
			"mesh\\ch0106133.msh");
		break;

	case Teste15:
		loadCostume("mesh\\ch0101134.wys",
			"mesh\\ch0101134.msh",
			"mesh\\ch0102134.msh",
			"mesh\\ch0103134.msh",
			"mesh\\ch0104134.msh",
			"mesh\\ch0105134.msh",
			"mesh\\ch0106134.msh");
		break;

	case Teste16:
		loadCostume("mesh\\ch0101138.wys",
			"mesh\\ch0101138.msh",
			"mesh\\ch0102138.msh",
			"mesh\\ch0103138.msh",
			"mesh\\ch0104138.msh",
			"mesh\\ch0105138.msh",
			"mesh\\ch0106138.msh");
		break;

	case Teste17:
		loadCostume("mesh\\ch0101140.wys",
			"mesh\\ch0101140.msh",
			"mesh\\ch0102140.msh",
			"mesh\\ch0103140.msh",
			"mesh\\ch0104140.msh",
			"mesh\\ch0105140.msh",
			"mesh\\ch0106140.msh");
		break;

	case Teste18:
		loadCostume("mesh\\ch0101141.wys",
			"mesh\\ch0101141.msh",
			"mesh\\ch0102141.msh",
			"mesh\\ch0103141.msh",
			"mesh\\ch0104141.msh",
			"mesh\\ch0105141.msh",
			"mesh\\ch0106141.msh");
		break;

	case Teste19:
		loadCostume("mesh\\ch0101141red.wys",
			"mesh\\ch0101141.msh",
			"mesh\\ch0102141.msh",
			"mesh\\ch0103141.msh",
			"mesh\\ch0104141.msh",
			"mesh\\ch0105141.msh",
			"mesh\\ch0106141.msh");
		break;

	case Teste20:
		loadCostume("mesh\\ch0101152.wys",
			"mesh\\ch0101152.msh",
			"mesh\\ch0102152.msh",
			"mesh\\ch0103152.msh",
			"mesh\\ch0104152.msh",
			"mesh\\ch0105152.msh",
			"mesh\\ch0106152.msh");
		break;

	case Teste21:
		loadCostume("mesh\\ch0101163.wys",
			"mesh\\ch0101163.msh",
			"mesh\\ch0102163.msh",
			"mesh\\ch0103163.msh",
			"mesh\\ch0104163.msh",
			"mesh\\ch0105163.msh",
			"mesh\\ch0106163.msh");
		break;

	case Teste22:
		loadCostume("mesh\\ch0101164blue.wys",
			"mesh\\ch0101164.msh",
			"mesh\\ch0102164.msh",
			"mesh\\ch0103164.msh",
			"mesh\\ch0104164.msh",
			"mesh\\ch0105164.msh",
			"mesh\\ch0106164.msh");
		break;

	case Teste23:
		loadCostume("mesh\\ch0101164red.wys",
			"mesh\\ch0101164.msh",
			"mesh\\ch0102164.msh",
			"mesh\\ch0103164.msh",
			"mesh\\ch0104164.msh",
			"mesh\\ch0105164.msh",
			"mesh\\ch0106164.msh");
		break;

	case Teste24:
		loadCostume("mesh\\ch0101165red.wys",
			"mesh\\ch0101165.msh",
			"mesh\\ch0102165.msh",
			"mesh\\ch0103165.msh",
			"mesh\\ch0104165.msh",
			"mesh\\ch0105165.msh",
			"mesh\\ch0106165.msh");
		break;

	case Teste25:
		loadCostume("mesh\\ch0101165blue.wys",
			"mesh\\ch0101165.msh",
			"mesh\\ch0102165.msh",
			"mesh\\ch0103165.msh",
			"mesh\\ch0104165.msh",
			"mesh\\ch0105165.msh",
			"mesh\\ch0106165.msh");
		break;

	case Teste26:
		loadCostume("mesh\\ch0101166.wys",
			"mesh\\ch0101166.msh",
			"mesh\\ch0102166.msh",
			"mesh\\ch0103166.msh",
			"mesh\\ch0104166.msh",
			"mesh\\ch0105166.msh",
			"mesh\\ch0106166.msh");
		break;

	case Teste27:
		loadCostume("mesh\\ch0101178.wys",
			"mesh\\ch0101178.msh",
			"mesh\\ch0102178.msh",
			"mesh\\ch0103178.msh",
			"mesh\\ch0104178.msh",
			"mesh\\ch0105178.msh",
			"mesh\\ch0106178.msh");
		break;

	case Teste28:
		loadCostume("mesh\\ch0101179.wys",
			"mesh\\ch0101179.msh",
			"mesh\\ch0102179.msh",
			"mesh\\ch0103179.msh",
			"mesh\\ch0104179.msh",
			"mesh\\ch0105179.msh",
			"mesh\\ch0106179.msh");
		break;

	case Teste29:
		loadCostume("mesh\\ch0101563.wys",
			"mesh\\ch0101563.msh",
			"mesh\\ch0102563.msh",
			"mesh\\ch0103563.msh",
			"mesh\\ch0104563.msh",
			"mesh\\ch0105563.msh",
			"mesh\\ch0106563.msh");
		break;

	case Teste30:
		loadCostume("mesh\\ch0101664.wys",
			"mesh\\ch0101664.msh",
			"mesh\\ch0102664.msh",
			"mesh\\ch0103664.msh",
			"mesh\\ch0104664.msh",
			"mesh\\ch0105664.msh",
			"mesh\\ch0106664.msh");
		break;

	case Teste31:
		loadCostume("mesh\\ch0101564.wys",
			"mesh\\ch0101564.msh",
			"mesh\\ch0102564.msh",
			"mesh\\ch0103564.msh",
			"mesh\\ch0104564.msh",
			"mesh\\ch0105564.msh",
			"mesh\\ch0106564.msh");
		break;

	case Teste32:
		loadCostume("mesh\\ch0201100.wys",
			"mesh\\ch0201100.msh",
			"mesh\\ch0202100.msh",
			"mesh\\ch0203100.msh",
			"mesh\\ch0204100.msh",
			"mesh\\ch0205100.msh",
			"mesh\\ch0206100.msh");
		break;

	case Teste33:
		loadCostume("mesh\\ch0201110.wys",
			"mesh\\ch0201110.msh",
			"mesh\\ch0202110.msh",
			"mesh\\ch0203110.msh",
			"mesh\\ch0204110.msh",
			"mesh\\ch0205110.msh",
			"mesh\\ch0206110.msh");
		break;

	case Teste34:
		loadCostume("mesh\\ch0201111.wys",
			"mesh\\ch0201111.msh",
			"mesh\\ch0202111.msh",
			"mesh\\ch0203111.msh",
			"mesh\\ch0204111.msh",
			"mesh\\ch0205111.msh",
			"mesh\\ch0206111.msh");
		break;

	case Teste35:
		loadCostume("mesh\\ch0201115.wys",
			"mesh\\ch0201115.msh",
			"mesh\\ch0202115.msh",
			"mesh\\ch0203115.msh",
			"mesh\\ch0204115.msh",
			"mesh\\ch0205115.msh",
			"mesh\\ch0206115.msh");
		break;

	case Teste36:
		loadCostume("mesh\\ch0201116.wys",
			"mesh\\ch0201116.msh",
			"mesh\\ch0202116.msh",
			"mesh\\ch0203116.msh",
			"mesh\\ch0204116.msh",
			"mesh\\ch0205116.msh",
			"mesh\\ch0206116.msh");
		break;

	case Teste37:
		loadCostume("mesh\\ch0201114.wys",
			"mesh\\ch0201114.msh",
			"mesh\\ch0202114.msh",
			"mesh\\ch0203114.msh",
			"mesh\\ch0204114.msh",
			"mesh\\ch0205114.msh",
			"mesh\\ch0206114.msh");
		break;

	case Teste38:
		loadCostume("mesh\\ch0201113.wys",
			"mesh\\ch0201113.msh",
			"mesh\\ch0202113.msh",
			"mesh\\ch0203113.msh",
			"mesh\\ch0204113.msh",
			"mesh\\ch0205113.msh",
			"mesh\\ch0206113.msh");
		break;

	case Teste39:
		loadCostume("mesh\\ch0101156.wys",
			"mesh\\ch0101156.msh",
			"mesh\\ch0102156.msh",
			"mesh\\ch0103156.msh",
			"mesh\\ch0104156.msh",
			"mesh\\ch0105156.msh",
			"mesh\\ch0106156.msh");
		break;

	case Teste40:
		loadCostume("mesh\\ch0101157.wys",
			"mesh\\ch0101157.msh",
			"mesh\\ch0102157.msh",
			"mesh\\ch0103157.msh",
			"mesh\\ch0104157.msh",
			"mesh\\ch0105157.msh",
			"mesh\\ch0106157.msh");
		break;

	case Teste41:
		loadCostume("mesh\\ch0101119.wys",
			"mesh\\ch0101119.msh",
			"mesh\\ch0102119.msh",
			"mesh\\ch0103119.msh",
			"mesh\\ch0104119.msh",
			"mesh\\ch0105119.msh",
			"mesh\\ch0106119.msh");
		break;

	case Teste42:
		loadCostume("mesh\\ch0101160.wys",
			"mesh\\ch0101160.msh",
			"mesh\\ch0102160.msh",
			"mesh\\ch0103160.msh",
			"mesh\\ch0104160.msh",
			"mesh\\ch0105160.msh",
			"mesh\\ch0106160.msh");
		break;

	case Teste43:
		loadCostume("mesh\\ch0201108.wys",
			"mesh\\ch0201108.msh",
			"mesh\\ch0202108.msh",
			"mesh\\ch0203108.msh",
			"mesh\\ch0204108.msh",
			"mesh\\ch0205108.msh",
			"mesh\\ch0206108.msh");
		break;

	case Teste44:
		loadCostume("mesh\\ch0201102.wys",
			"mesh\\ch0201102.msh",
			"mesh\\ch0202102.msh",
			"mesh\\ch0203102.msh",
			"mesh\\ch0204102.msh",
			"mesh\\ch0205102.msh",
			"mesh\\ch0206102.msh");
		break;

	case Teste45:
		loadCostume("mesh\\ch0101116.wys",
			"mesh\\ch0101116.msh",
			"mesh\\ch0102116.msh",
			"mesh\\ch0103116.msh",
			"mesh\\ch0104116.msh",
			"mesh\\ch0105116.msh",
			"mesh\\ch0106116.msh");
		break;

	default:
		break;
	}
}

