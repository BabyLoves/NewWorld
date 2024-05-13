#include "main.h"
int teste;

#define COLORBASE	0xFF000000
enum ClientColor
{
	Ouro = COLORBASE + 0xFFD700,
	Roxo = COLORBASE + 0xFF00FF,
	AzulEscuro = COLORBASE + 0x00008B,
	Preto = COLORBASE + 0x000000,
	Branco = COLORBASE + 0xFFFFFF,
	Vermelho = COLORBASE + 0xFF6347,
	Azul = COLORBASE + 0x00CED1,
	Amarelo = COLORBASE + 0xFFFF00,
	Verde = COLORBASE + 0x00FF00,
	Laranja = COLORBASE + 0xCD6600,
	Rosa = COLORBASE + 0xFF6EB4,
	Cinza = COLORBASE + 0x696969,
	AmareloPalido = COLORBASE + 0xEEE8AA,
	RoxoRosa = COLORBASE + 0xDDA0DD // Global cor composição
};

int AddItemDescription(STRUCT_ITEM* item, char* line1, char* line2, char* line3, char* line4, char* line5, char* line6, char* line7, char* line8, char* line9, char* line10, int* line1Color, int* line2Color, int* line3Color, int* line4Color, int* line5Color, int* line6Color, int* line7Color, int* line8Color, int* line9Color, int* line10Color)
{
	memset(line1, 0x0, sizeof(line1));
	memset(line2, 0x0, sizeof(line2));
	memset(line3, 0x0, sizeof(line3));
	memset(line4, 0x0, sizeof(line4));
	memset(line5, 0x0, sizeof(line5));
	memset(line6, 0x0, sizeof(line6));
	memset(line7, 0x0, sizeof(line7));
	memset(line8, 0x0, sizeof(line8));
	memset(line9, 0x0, sizeof(line9));
	memset(line10, 0x0, sizeof(line10));

#pragma region Trajes	
	if (item->sIndex >= 4200 && item->sIndex <= 4250)
	{
		char Porcentagem[2] = "%";
		sprintf_s(line4, 128, "EXP BÔNUS[+10%s]", Porcentagem);
		*line4Color = RoxoRosa;
		sprintf_s(line5, 128, "EXP BÔNUS C/ TRAJE MONTARIA[+5%s]", Porcentagem);
		*line5Color = RoxoRosa;
		return 10;
	}
	if (item->sIndex >= 4500 && item->sIndex <= 4549)
	{
		sprintf_s(line3, 128, "[CLICK COM BOTÃO DIREITO PARA USAR]");
		*line3Color = Laranja;
		char Porcentagem[2] = "%";
		sprintf_s(line4, 128, "DROP BÔNUS[+10%s]", Porcentagem);
		*line4Color = Azul;
		sprintf_s(line5, 128, "DROP BÔNUS C/ TRAJE PERSO. [+5%s]", Porcentagem);
		*line5Color = Azul;
		return 10;
	}
	if (item->sIndex == 5614)
	{
		sprintf_s(line2, 128, "[ITEM PREMIUM]");
		*line2Color = Laranja;

		sprintf_s(line3, 128, "Troca de classe, altere a classe");
		*line3Color = RoxoRosa;

		sprintf_s(line4, 128, "atual sua para a que desejar,");
		*line4Color = RoxoRosa;

		sprintf_s(line5, 128, "Equipe uma saphirot da classe desejada");
		*line5Color = RoxoRosa;

		sprintf_s(line6, 128, "e ative o item.");
		*line6Color = RoxoRosa;

		sprintf_s(line7, 128, "[ATENÇÃO, TROCA DE CLASSE NÃO]");
		*line7Color = Roxo;

		sprintf_s(line8, 128, "[ESTÁ DISPONÍVEL PARA PERSONAGEM MORTAL]");
		*line8Color = Roxo;
		return 10;
	}
#pragma endregion

#pragma region item Info
	switch (item->sIndex)
	{
	case 3331:
		sprintf(line1, "[PASSE DO EVENTO]");
		*line1Color = Verde;

		sprintf_s(line2, 128, "Habilita Double Hit");
		*line2Color = Ouro;

		sprintf_s(line3, 128, "Agrupa itens recebidos nos NPCs");
		*line3Color = Azul;

		sprintf_s(line4, 128, "");
		*line4Color = Azul;

		sprintf_s(line5, 128, "");
		*line5Color = Azul;

		sprintf_s(line6, 128, "");
		*line6Color = Azul;

		sprintf_s(line7, 128, "");
		*line7Color = Azul;

		sprintf_s(line8, 128, "");
		*line8Color = Azul;

		sprintf_s(line9, 128, "");
		*line9Color = Azul;

		sprintf_s(line10, 128, "Válido Durante o Evento Festa Junina");
		*line10Color = RoxoRosa;
		return 10;
	case 5752:
		sprintf(line1, "[*MISSION 1*]");
		*line1Color = Verde;

		sprintf_s(line2, 128, "Entregue: [02] Baus III e [01] Medalha Roxa");
		*line2Color = Laranja;

		sprintf_s(line3, 128, "Receba: [01] Ôvo de Unicórnio");
		*line3Color = Azul;

		sprintf_s(line4, 128, "");
		*line4Color = Azul;

		sprintf_s(line5, 128, "");
		*line5Color = Azul;

		sprintf_s(line6, 128, "");
		*line6Color = Azul;

		sprintf_s(line7, 128, "");
		*line7Color = Azul;

		sprintf_s(line8, 128, "");
		*line8Color = Azul;

		sprintf_s(line9, 128, "");
		*line9Color = Azul;

		sprintf_s(line10, 128, "");
		*line10Color = Azul;
		return 10;
	case 5753:
		sprintf(line1, "[*MISSION 2*]");
		*line1Color = Verde;

		sprintf_s(line2, 128, "Entregue: [02] Baus III e [01] Medalha Azul");
		*line2Color = Laranja;

		sprintf_s(line3, 128, "Receba: [01] Ôvo de Unisus");
		*line3Color = Azul;

		sprintf_s(line4, 128, "");
		*line4Color = Azul;

		sprintf_s(line5, 128, "");
		*line5Color = Azul;

		sprintf_s(line6, 128, "");
		*line6Color = Azul;

		sprintf_s(line7, 128, "");
		*line7Color = Azul;

		sprintf_s(line8, 128, "");
		*line8Color = Azul;

		sprintf_s(line9, 128, "");
		*line9Color = Azul;

		sprintf_s(line10, 128, "");
		*line10Color = Azul;
		return 10;
	case 5754:
		sprintf(line1, "[*MISSION 3*]");
		*line1Color = Verde;

		sprintf_s(line2, 128, "Entregue: [03] Baus III");
		*line2Color = Laranja;

		sprintf_s(line3, 128, "Receba: [01] Ôvo de Pégasus");
		*line3Color = Azul;

		sprintf_s(line4, 128, "");
		*line4Color = Azul;

		sprintf_s(line5, 128, "");
		*line5Color = Azul;

		sprintf_s(line6, 128, "");
		*line6Color = Azul;

		sprintf_s(line7, 128, "");
		*line7Color = Azul;

		sprintf_s(line8, 128, "");
		*line8Color = Azul;

		sprintf_s(line9, 128, "");
		*line9Color = Azul;

		sprintf_s(line10, 128, "");
		*line10Color = Azul;
		return 10;
	case 5755:
		sprintf(line1, "[*MISSION 4*]");
		*line1Color = Verde;

		sprintf_s(line2, 128, "Entregue: [02] Baus III e [01] Medalha Dourada");
		*line2Color = Laranja;

		sprintf_s(line3, 128, "Receba: [01] Caixa de Planeta");
		*line3Color = Azul;

		sprintf_s(line4, 128, "");
		*line4Color = Azul;

		sprintf_s(line5, 128, "");
		*line5Color = Azul;

		sprintf_s(line6, 128, "");
		*line6Color = Azul;

		sprintf_s(line7, 128, "");
		*line7Color = Azul;

		sprintf_s(line8, 128, "");
		*line8Color = Azul;

		sprintf_s(line9, 128, "");
		*line9Color = Azul;

		sprintf_s(line10, 128, "");
		*line10Color = Azul;
		return 10;
	case 5756:
		sprintf(line1, "[*MISSION 5*]");
		*line1Color = Verde;

		sprintf_s(line2, 128, "Entregue: [01] Medalha Roxa e [01] Medalha Dourada");
		*line2Color = Laranja;

		sprintf_s(line3, 128, "Receba: [01] Arma Aleatória (72/32) Anct +9");
		*line3Color = Azul;

		sprintf_s(line4, 128, "");
		*line4Color = Azul;

		sprintf_s(line5, 128, "");
		*line5Color = Azul;

		sprintf_s(line6, 128, "");
		*line6Color = Azul;

		sprintf_s(line7, 128, "");
		*line7Color = Azul;

		sprintf_s(line8, 128, "");
		*line8Color = Azul;

		sprintf_s(line9, 128, "");
		*line9Color = Azul;

		sprintf_s(line10, 128, "");
		*line10Color = Azul;
		return 10;
	case 5757:
		sprintf(line1, "[*MISSION 6*]");
		*line1Color = Verde;

		sprintf_s(line2, 128, "Entregue: [03] Baus III,");
		*line2Color = Laranja;

		sprintf_s(line3, 128, "[01] Medalha Vermelha e [01] Planeta +9");
		*line3Color = Laranja;

		sprintf_s(line4, 128, "Receba: Adicional 36 Dano no Planeta");
		*line4Color = Azul;

		sprintf_s(line5, 128, "");
		*line5Color = Azul;

		sprintf_s(line6, 128, "");
		*line6Color = Azul;

		sprintf_s(line7, 128, "");
		*line7Color = Azul;

		sprintf_s(line8, 128, "");
		*line8Color = Azul;

		sprintf_s(line9, 128, "");
		*line9Color = Azul;

		sprintf_s(line10, 128, "");
		*line10Color = Azul;
		return 10;
	case 5758:
		sprintf(line1, "[*MISSION 7*]");
		*line1Color = Verde;

		sprintf_s(line2, 128, "Entregue: [03] Baus III,");
		*line2Color = Laranja;

		sprintf_s(line3, 128, "[01] Medalha Verde e [01] Planeta +9");
		*line3Color = Laranja;

		sprintf_s(line4, 128, "Receba: Adicional 16 Mágico no Planeta");
		*line4Color = Azul;

		sprintf_s(line5, 128, "");
		*line5Color = Azul;

		sprintf_s(line6, 128, "");
		*line6Color = Azul;

		sprintf_s(line7, 128, "");
		*line7Color = Azul;

		sprintf_s(line8, 128, "");
		*line8Color = Azul;

		sprintf_s(line9, 128, "");
		*line9Color = Azul;

		sprintf_s(line10, 128, "");
		*line10Color = Azul;
		return 10;
	case 5759:
		sprintf(line1, "[*MISSION 8*]");
		*line1Color = Verde;

		sprintf_s(line2, 128, "Entregue: [03] Baus III e [01] Medalha Verde");
		*line2Color = Laranja;

		sprintf_s(line3, 128, "Receba: [01] Secreta Aleatória");
		*line3Color = Azul;

		sprintf_s(line4, 128, "");
		*line4Color = Azul;

		sprintf_s(line5, 128, "");
		*line5Color = Azul;

		sprintf_s(line6, 128, "");
		*line6Color = Azul;

		sprintf_s(line7, 128, "");
		*line7Color = Azul;

		sprintf_s(line8, 128, "");
		*line8Color = Azul;

		sprintf_s(line9, 128, "");
		*line9Color = Azul;

		sprintf_s(line10, 128, "");
		*line10Color = Azul;
		return 10;
	case 5720:
		sprintf(line1, "[ITENS INCLUSOS NO FILTRO]");
		*line1Color = Verde;

		sprintf_s(line2, 128, "s/ Sela, Fantasma, leve,");
		*line2Color = Azul;

		sprintf_s(line3, 128, "Equip, Andaluz, Fenrir");
		*line3Color = Azul;

		sprintf_s(line4, 128, "Unicórnio, Pégasus, Unisus");
		*line4Color = Azul;

		sprintf_s(line5, 128, "Porco, Javali,");
		*line5Color = Azul;

		sprintf_s(line6, 128, "Lobo, Urso, Dragão Menor");
		*line6Color = Azul;

		sprintf_s(line7, 128, "Dente de Sabre");
		*line7Color = Azul;

		sprintf_s(line8, 128, "");
		*line8Color = Azul;

		sprintf_s(line9, 128, "Limite de 4 Categorias Ativas");
		*line9Color = Laranja;

		sprintf_s(line10, 128, "Libera o Drop dos Itens Citados");
		*line10Color = Laranja;
		return 10;
	case 5721:
		sprintf(line1, "[ITENS INCLUSOS NO FILTRO]");
		*line1Color = Verde;

		sprintf_s(line2, 128, "Diamante, Esmeralda, Coral, Garnet,");
		*line2Color = Azul;

		sprintf_s(line3, 128, "Pedra do Sábio");
		*line3Color = Azul;

		sprintf_s(line4, 128, "");
		*line4Color = Azul;

		sprintf_s(line5, 128, "");
		*line5Color = Azul;

		sprintf_s(line6, 128, "");
		*line6Color = Azul;

		sprintf_s(line7, 128, "");
		*line7Color = Azul;

		sprintf_s(line8, 128, "");
		*line8Color = Azul;

		sprintf_s(line9, 128, "Limite de 4 Categorias Ativas");
		*line9Color = Laranja;

		sprintf_s(line10, 128, "Libera o Drop dos Itens Citados");
		*line10Color = Laranja;
		return 10;
	case 5722:
		sprintf(line1, "[ITENS INCLUSOS NO FILTRO]");
		*line1Color = Verde;

		sprintf_s(line2, 128, "Poeira de Oriharucom");
		*line2Color = Azul;

		sprintf_s(line3, 128, "Poeira de Lactolerium");
		*line3Color = Azul;

		sprintf_s(line4, 128, "Resto de Oriharucom");
		*line4Color = Azul;

		sprintf_s(line5, 128, "Resto de Lactolerium");
		*line5Color = Azul;

		sprintf_s(line6, 128, "");
		*line6Color = Azul;

		sprintf_s(line7, 128, "");
		*line7Color = Azul;

		sprintf_s(line8, 128, "");
		*line8Color = Azul;

		sprintf_s(line9, 128, "Limite de 4 Categorias Ativas");
		*line9Color = Laranja;

		sprintf_s(line10, 128, "Libera o Drop dos Itens Citados");
		*line10Color = Laranja;
		return 10;
	case 5723:
		sprintf(line1, "[ITENS INCLUSOS NO FILTRO]");
		*line1Color = Verde;

		sprintf_s(line2, 128, "Classe D");
		*line2Color = Azul;

		sprintf_s(line3, 128, "Classe E");
		*line3Color = Azul;

		sprintf_s(line4, 128, "");
		*line4Color = Azul;

		sprintf_s(line5, 128, "");
		*line5Color = Azul;

		sprintf_s(line6, 128, "");
		*line6Color = Azul;

		sprintf_s(line7, 128, "");
		*line7Color = Azul;

		sprintf_s(line8, 128, "");
		*line8Color = Azul;

		sprintf_s(line9, 128, "Limite de 4 Categorias Ativas");
		*line9Color = Laranja;

		sprintf_s(line10, 128, "Libera o Drop dos Itens Citados");
		*line10Color = Laranja;
		return 10;
	case 5724:
		sprintf(line1, "[ITENS INCLUSOS NO FILTRO]");
		*line1Color = Verde;

		sprintf_s(line2, 128, "Vela do Coveiro");
		*line2Color = Azul;

		sprintf_s(line3, 128, "Colheira do Jardineiro");
		*line3Color = Azul;

		sprintf_s(line4, 128, "Cura do Batedor");
		*line4Color = Azul;

		sprintf_s(line5, 128, "Mana do Batedor");
		*line5Color = Azul;

		sprintf_s(line6, 128, "Emblema do Guarda");
		*line6Color = Azul;

		sprintf_s(line7, 128, "Pista de Runas");
		*line7Color = Azul;

		sprintf_s(line8, 128, "");
		*line8Color = Azul;

		sprintf_s(line9, 128, "Limite de 4 Categorias Ativas");
		*line9Color = Laranja;

		sprintf_s(line10, 128, "Libera o Drop dos Itens Citados");
		*line10Color = Laranja;
		return 10;
	case 5725:
		sprintf(line1, "[ITENS INCLUSOS NO FILTRO]");
		*line1Color = Verde;

		sprintf_s(line2, 128, "Caixa da Sabedoria");
		*line2Color = Azul;

		sprintf_s(line3, 128, "Lágrima Angelical");
		*line3Color = Azul;

		sprintf_s(line4, 128, "Coração do Kaizen");
		*line4Color = Azul;

		sprintf_s(line5, 128, "Olho de Sangue");
		*line5Color = Azul;

		sprintf_s(line6, 128, "Pedra Espiritual dos Elfos");
		*line6Color = Azul;

		sprintf_s(line7, 128, "Molar do Gárgula");
		*line7Color = Azul;

		sprintf_s(line8, 128, "");
		*line8Color = Azul;

		sprintf_s(line9, 128, "Limite de 4 Categorias Ativas");
		*line9Color = Laranja;

		sprintf_s(line10, 128, "Libera o Drop dos Itens Citados");
		*line10Color = Laranja;
		return 10;
	case 5726:
		sprintf(line1, "[ITENS INCLUSOS NO FILTRO]");
		*line1Color = Verde;

		sprintf_s(line2, 128, "Alma da Fênix");
		*line2Color = Azul;

		sprintf_s(line3, 128, "Alma do Unicórnio");
		*line3Color = Azul;

		sprintf_s(line4, 128, "Imortalidade");
		*line4Color = Azul;

		sprintf_s(line5, 128, "Pedras Sephiroth");
		*line5Color = Azul;

		sprintf_s(line6, 128, "");
		*line6Color = Azul;

		sprintf_s(line7, 128, "");
		*line7Color = Azul;

		sprintf_s(line8, 128, "");
		*line8Color = Azul;

		sprintf_s(line9, 128, "Limite de 4 Categorias Ativas");
		*line9Color = Laranja;

		sprintf_s(line10, 128, "Libera o Drop dos Itens Citados");
		*line10Color = Laranja;
		return 10;
	case 5727:
		sprintf(line1, "[ITENS INCLUSOS NO FILTRO]");
		*line1Color = Verde;

		sprintf_s(line2, 128, "Ansuz, Uraz, Thurisaz, Fehu");
		*line2Color = Azul;

		sprintf_s(line3, 128, "Raidho, Kenaz, Naudhiz, Gebo");
		*line3Color = Azul;

		sprintf_s(line4, 128, "Wunjo, Hagalaz, Isa, Jara");
		*line4Color = Azul;

		sprintf_s(line5, 128, "Eihwaz, Perthro, Elhaz, Sowilo");
		*line5Color = Azul;

		sprintf_s(line6, 128, "Berkano, Ehwaz, Tiwaz, Mannaz");
		*line6Color = Azul;

		sprintf_s(line7, 128, "Laguz, Dagaz, Ing, Othel");
		*line7Color = Azul;

		sprintf_s(line8, 128, "");
		*line8Color = Azul;

		sprintf_s(line9, 128, "Limite de 4 Categorias Ativas");
		*line9Color = Laranja;

		sprintf_s(line10, 128, "Libera o Drop dos Itens Citados");
		*line10Color = Laranja;
		return 10;
	case 5728:
		sprintf(line1, "[ITENS INCLUSOS NO FILTRO]");
		*line1Color = Verde;

		sprintf_s(line2, 128, "Chapéu de Teia (N/M/A)");
		*line2Color = Azul;

		sprintf_s(line3, 128, "Peitoral de Teia (N/M/A)");
		*line3Color = Azul;

		sprintf_s(line4, 128, "Calça de Teia (N/M/A)");
		*line4Color = Azul;

		sprintf_s(line5, 128, "Braçadeira de Teia (N/M/A)");
		*line5Color = Azul;

		sprintf_s(line6, 128, "Botas de Teia (N/M/A)");
		*line6Color = Azul;

		sprintf_s(line7, 128, "");
		*line7Color = Azul;

		sprintf_s(line8, 128, "");
		*line8Color = Azul;

		sprintf_s(line9, 128, "Limite de 4 Categorias Ativas");
		*line9Color = Laranja;

		sprintf_s(line10, 128, "Libera o Drop dos Itens Citados");
		*line10Color = Laranja;
		return 10;
	case 5729:
		sprintf(line1, "[ITENS INCLUSOS NO FILTRO]");
		*line1Color = Verde;

		sprintf_s(line2, 128, "Elmo Legionário");
		*line2Color = Azul;

		sprintf_s(line3, 128, "Armadura Legionária");
		*line3Color = Azul;

		sprintf_s(line4, 128, "Calça Legionária");
		*line4Color = Azul;

		sprintf_s(line5, 128, "Manoplas Legionária");
		*line5Color = Azul;

		sprintf_s(line6, 128, "Botas Legionária");
		*line6Color = Azul;

		sprintf_s(line7, 128, "");
		*line7Color = Azul;

		sprintf_s(line8, 128, "");
		*line8Color = Azul;

		sprintf_s(line9, 128, "Limite de 4 Categorias Ativas");
		*line9Color = Laranja;

		sprintf_s(line10, 128, "Libera o Drop dos Itens Citados");
		*line10Color = Laranja;
		return 10;
	case 5730:
		sprintf(line1, "[ITENS INCLUSOS NO FILTRO]");
		*line1Color = Verde;

		sprintf_s(line2, 128, "Armadura Rake");
		*line2Color = Azul;

		sprintf_s(line3, 128, "Calça Rake");
		*line3Color = Azul;

		sprintf_s(line4, 128, "Manopla Rake");
		*line4Color = Azul;

		sprintf_s(line5, 128, "Bota Rake");
		*line5Color = Azul;

		sprintf_s(line6, 128, "");
		*line6Color = Azul;

		sprintf_s(line7, 128, "");
		*line7Color = Azul;

		sprintf_s(line8, 128, "");
		*line8Color = Azul;

		sprintf_s(line9, 128, "Limite de 4 Categorias Ativas");
		*line9Color = Laranja;

		sprintf_s(line10, 128, "Libera o Drop dos Itens Citados");
		*line10Color = Laranja;
		return 10;
	case 5731:
		sprintf(line1, "[ITENS INCLUSOS NO FILTRO]");
		*line1Color = Verde;

		sprintf_s(line2, 128, "Arco Divino");
		*line2Color = Azul;

		sprintf_s(line3, 128, "Garra Draconiana");
		*line3Color = Azul;

		sprintf_s(line4, 128, "Espada Vorpal");
		*line4Color = Azul;

		sprintf_s(line5, 128, "");
		*line5Color = Azul;

		sprintf_s(line6, 128, "");
		*line6Color = Azul;

		sprintf_s(line7, 128, "");
		*line7Color = Azul;

		sprintf_s(line8, 128, "");
		*line8Color = Azul;

		sprintf_s(line9, 128, "Limite de 4 Categorias Ativas");
		*line9Color = Laranja;

		sprintf_s(line10, 128, "Libera o Drop dos Itens Citados");
		*line10Color = Laranja;
		return 10;
	case 5732:
		sprintf(line1, "[ITENS INCLUSOS NO FILTRO]");
		*line1Color = Verde;

		sprintf_s(line2, 128, "Arco Guardião");
		*line2Color = Azul;

		sprintf_s(line3, 128, "Dianus");
		*line3Color = Azul;

		sprintf_s(line4, 128, "Vingadora");
		*line4Color = Azul;

		sprintf_s(line5, 128, "");
		*line5Color = Azul;

		sprintf_s(line6, 128, "");
		*line6Color = Azul;

		sprintf_s(line7, 128, "");
		*line7Color = Azul;

		sprintf_s(line8, 128, "");
		*line8Color = Azul;

		sprintf_s(line9, 128, "Limite de 4 Categorias Ativas");
		*line9Color = Laranja;

		sprintf_s(line10, 128, "Libera o Drop dos Itens Citados");
		*line10Color = Laranja;
		return 10;
	case 5733:
		sprintf(line1, "[ITENS INCLUSOS NO FILTRO]");
		*line1Color = Verde;

		sprintf_s(line2, 128, "Skytalos");
		*line2Color = Azul;

		sprintf_s(line3, 128, "Khyrius");
		*line3Color = Azul;

		sprintf_s(line4, 128, "Caliburn");
		*line4Color = Azul;

		sprintf_s(line5, 128, "");
		*line5Color = Azul;

		sprintf_s(line6, 128, "");
		*line6Color = Azul;

		sprintf_s(line7, 128, "");
		*line7Color = Azul;

		sprintf_s(line8, 128, "");
		*line8Color = Azul;

		sprintf_s(line9, 128, "Limite de 4 Categorias Ativas");
		*line9Color = Laranja;

		sprintf_s(line10, 128, "Libera o Drop dos Itens Citados");
		*line10Color = Laranja;
		return 10;
	case 5734:
		sprintf(line1, "[ITENS INCLUSOS NO FILTRO]");
		*line1Color = Verde;

		sprintf_s(line2, 128, "Elmo Embutido (N/M/A)");
		*line2Color = Azul;

		sprintf_s(line3, 128, "Armadura Embutida (N/M/A)");
		*line3Color = Azul;

		sprintf_s(line4, 128, "Calça Embutida (N/M/A)");
		*line4Color = Azul;

		sprintf_s(line5, 128, "Manopla Embutida (N/M/A)");
		*line5Color = Azul;

		sprintf_s(line6, 128, "Bota Embutida (N/M/A)");
		*line6Color = Azul;

		sprintf_s(line7, 128, "");
		*line7Color = Azul;

		sprintf_s(line8, 128, "");
		*line8Color = Azul;

		sprintf_s(line9, 128, "Limite de 4 Categorias Ativas");
		*line9Color = Laranja;

		sprintf_s(line10, 128, "Libera o Drop dos Itens Citados");
		*line10Color = Laranja;
		return 10;
	case 5735:
		sprintf(line1, "[ITENS INCLUSOS NO FILTRO]");
		*line1Color = Verde;

		sprintf_s(line2, 128, "Elmo Mortal");
		*line2Color = Azul;

		sprintf_s(line3, 128, "Armadura Mortal");
		*line3Color = Azul;

		sprintf_s(line4, 128, "Calça Mortal");
		*line4Color = Azul;

		sprintf_s(line5, 128, "Manopla Mortal");
		*line5Color = Azul;

		sprintf_s(line6, 128, "Bota Mortal");
		*line6Color = Azul;

		sprintf_s(line7, 128, "");
		*line7Color = Azul;

		sprintf_s(line8, 128, "");
		*line8Color = Azul;

		sprintf_s(line9, 128, "Limite de 4 Categorias Ativas");
		*line9Color = Laranja;

		sprintf_s(line10, 128, "Libera o Drop dos Itens Citados");
		*line10Color = Laranja;
		return 10;
	case 5736:
		sprintf(line1, "[ITENS INCLUSOS NO FILTRO]");
		*line1Color = Verde;

		sprintf_s(line2, 128, "Armadura Flamejante");
		*line2Color = Azul;

		sprintf_s(line3, 128, "Calça Flamejante");
		*line3Color = Azul;

		sprintf_s(line4, 128, "Manopla Flamejante");
		*line4Color = Azul;

		sprintf_s(line5, 128, "Bota Flamejante");
		*line5Color = Azul;

		sprintf_s(line6, 128, "");
		*line6Color = Azul;

		sprintf_s(line7, 128, "");
		*line7Color = Azul;

		sprintf_s(line8, 128, "");
		*line8Color = Azul;

		sprintf_s(line9, 128, "Limite de 4 Categorias Ativas");
		*line9Color = Laranja;

		sprintf_s(line10, 128, "Libera o Drop dos Itens Citados");
		*line10Color = Laranja;
		return 10;
	case 5737:
		sprintf(line1, "[ITENS INCLUSOS NO FILTRO]");
		*line1Color = Verde;

		sprintf_s(line2, 128, "Martelo Assassino");
		*line2Color = Azul;

		sprintf_s(line3, 128, "Lança do Triunfo");
		*line3Color = Azul;

		sprintf_s(line4, 128, "Solaris");
		*line4Color = Azul;

		sprintf_s(line5, 128, "");
		*line5Color = Azul;

		sprintf_s(line6, 128, "");
		*line6Color = Azul;

		sprintf_s(line7, 128, "");
		*line7Color = Azul;

		sprintf_s(line8, 128, "");
		*line8Color = Azul;

		sprintf_s(line9, 128, "Limite de 4 Categorias Ativas");
		*line9Color = Laranja;

		sprintf_s(line10, 128, "Libera o Drop dos Itens Citados");
		*line10Color = Laranja;
		return 10;
	case 5738:
		sprintf(line1, "[ITENS INCLUSOS NO FILTRO]");
		*line1Color = Verde;

		sprintf_s(line2, 128, "Asa Draconiana");
		*line2Color = Azul;

		sprintf_s(line3, 128, "Éden");
		*line3Color = Azul;

		sprintf_s(line4, 128, "Demolidor Celestial");
		*line4Color = Azul;

		sprintf_s(line5, 128, "Foice Platinada");
		*line5Color = Azul;

		sprintf_s(line6, 128, "");
		*line6Color = Azul;

		sprintf_s(line7, 128, "");
		*line7Color = Azul;

		sprintf_s(line8, 128, "");
		*line8Color = Azul;

		sprintf_s(line9, 128, "Limite de 4 Categorias Ativas");
		*line9Color = Laranja;

		sprintf_s(line10, 128, "Libera o Drop dos Itens Citados");
		*line10Color = Laranja;
		return 10;
	case 5739:
		sprintf(line1, "[ITENS INCLUSOS NO FILTRO]");
		*line1Color = Verde;

		sprintf_s(line2, 128, "Balmung");
		*line2Color = Azul;

		sprintf_s(line3, 128, "Gleipnir");
		*line3Color = Azul;

		sprintf_s(line4, 128, "Thrasytes");
		*line4Color = Azul;

		sprintf_s(line5, 128, "");
		*line5Color = Azul;

		sprintf_s(line6, 128, "");
		*line6Color = Azul;

		sprintf_s(line7, 128, "");
		*line7Color = Azul;

		sprintf_s(line8, 128, "");
		*line8Color = Azul;

		sprintf_s(line9, 128, "Limite de 4 Categorias Ativas");
		*line9Color = Laranja;

		sprintf_s(line10, 128, "Libera o Drop dos Itens Citados");
		*line10Color = Laranja;
		return 10;
	case 5740:
		sprintf(line1, "[ITENS INCLUSOS NO FILTRO]");
		*line1Color = Verde;

		sprintf_s(line2, 128, "Elmo Elemental (N/M/A)");
		*line2Color = Azul;

		sprintf_s(line3, 128, "Armadura Elemental (N/M/A)");
		*line3Color = Azul;

		sprintf_s(line4, 128, "Calça Elemental (N/M/A)");
		*line4Color = Azul;

		sprintf_s(line5, 128, "Manopla Elemental (N/M/A)");
		*line5Color = Azul;

		sprintf_s(line6, 128, "Bota Elemental (N/M/A)");
		*line6Color = Azul;

		sprintf_s(line7, 128, "");
		*line7Color = Azul;

		sprintf_s(line8, 128, "");
		*line8Color = Azul;

		sprintf_s(line9, 128, "Limite de 4 Categorias Ativas");
		*line9Color = Laranja;

		sprintf_s(line10, 128, "Libera o Drop dos Itens Citados");
		*line10Color = Laranja;
		return 10;
	case 5741:
		sprintf(line1, "[ITENS INCLUSOS NO FILTRO]");
		*line1Color = Verde;

		sprintf_s(line2, 128, "Elmo do Corvo");
		*line2Color = Azul;

		sprintf_s(line3, 128, "Armadura do Corvo");
		*line3Color = Azul;

		sprintf_s(line4, 128, "Calça do Corvo");
		*line4Color = Azul;

		sprintf_s(line5, 128, "Manopla do Corvo");
		*line5Color = Azul;

		sprintf_s(line6, 128, "Bota do Corvo");
		*line6Color = Azul;

		sprintf_s(line7, 128, "");
		*line7Color = Azul;

		sprintf_s(line8, 128, "");
		*line8Color = Azul;

		sprintf_s(line9, 128, "Limite de 4 Categorias Ativas");
		*line9Color = Laranja;

		sprintf_s(line10, 128, "Libera o Drop dos Itens Citados");
		*line10Color = Laranja;
		return 10;
	case 5742:
		sprintf(line1, "[ITENS INCLUSOS NO FILTRO]");
		*line1Color = Verde;

		sprintf_s(line2, 128, "Armadura da Destruição");
		*line2Color = Azul;

		sprintf_s(line3, 128, "Calça da Destruição");
		*line3Color = Azul;

		sprintf_s(line4, 128, "Manopla da Destruição");
		*line4Color = Azul;

		sprintf_s(line5, 128, "Bota da Destruição");
		*line5Color = Azul;

		sprintf_s(line6, 128, "");
		*line6Color = Azul;

		sprintf_s(line7, 128, "");
		*line7Color = Azul;

		sprintf_s(line8, 128, "");
		*line8Color = Azul;

		sprintf_s(line9, 128, "Limite de 4 Categorias Ativas");
		*line9Color = Laranja;

		sprintf_s(line10, 128, "Libera o Drop dos Itens Citados");
		*line10Color = Laranja;
		return 10;
	case 5743:
		sprintf(line1, "[ITENS INCLUSOS NO FILTRO]");
		*line1Color = Verde;

		sprintf_s(line2, 128, "Martelo Assassino");
		*line2Color = Azul;

		sprintf_s(line3, 128, "Lança do Triunfo");
		*line3Color = Azul;

		sprintf_s(line4, 128, "Cruz Sagrada");
		*line4Color = Azul;

		sprintf_s(line5, 128, "");
		*line5Color = Azul;

		sprintf_s(line6, 128, "");
		*line6Color = Azul;

		sprintf_s(line7, 128, "");
		*line7Color = Azul;

		sprintf_s(line8, 128, "");
		*line8Color = Azul;

		sprintf_s(line9, 128, "Limite de 4 Categorias Ativas");
		*line9Color = Laranja;

		sprintf_s(line10, 128, "Libera o Drop dos Itens Citados");
		*line10Color = Laranja;
		return 10;
	case 5744:
		sprintf(line1, "[ITENS INCLUSOS NO FILTRO]");
		*line1Color = Verde;

		sprintf_s(line2, 128, "Asa Draconiana");
		*line2Color = Azul;

		sprintf_s(line3, 128, "Foice Platinada");
		*line3Color = Azul;

		sprintf_s(line4, 128, "Karikas");
		*line4Color = Azul;

		sprintf_s(line5, 128, "");
		*line5Color = Azul;

		sprintf_s(line6, 128, "");
		*line6Color = Azul;

		sprintf_s(line7, 128, "");
		*line7Color = Azul;

		sprintf_s(line8, 128, "");
		*line8Color = Azul;

		sprintf_s(line9, 128, "Limite de 4 Categorias Ativas");
		*line9Color = Laranja;

		sprintf_s(line10, 128, "Libera o Drop dos Itens Citados");
		*line10Color = Laranja;
		return 10;
	case 5745:
		sprintf(line1, "[ITENS INCLUSOS NO FILTRO]");
		*line1Color = Verde;

		sprintf_s(line2, 128, "Balmung");
		*line2Color = Azul;

		sprintf_s(line3, 128, "Gleipnir");
		*line3Color = Azul;

		sprintf_s(line4, 128, "Hermai");
		*line4Color = Azul;

		sprintf_s(line5, 128, "");
		*line5Color = Azul;

		sprintf_s(line6, 128, "");
		*line6Color = Azul;

		sprintf_s(line7, 128, "");
		*line7Color = Azul;

		sprintf_s(line8, 128, "");
		*line8Color = Azul;

		sprintf_s(line9, 128, "Limite de 4 Categorias Ativas");
		*line9Color = Laranja;

		sprintf_s(line10, 128, "Libera o Drop dos Itens Citados");
		*line10Color = Laranja;
		return 10;
	case 5746:
		sprintf(line1, "[ITENS INCLUSOS NO FILTRO]");
		*line1Color = Verde;

		sprintf_s(line2, 128, "Chapéu de Mytril (N/M/A)");
		*line2Color = Azul;

		sprintf_s(line3, 128, "Túnica de Mytril (N/M/A)");
		*line3Color = Azul;

		sprintf_s(line4, 128, "Calça de Mytril (N/M/A)");
		*line4Color = Azul;

		sprintf_s(line5, 128, "Luva de Mytril (N/M/A)");
		*line5Color = Azul;

		sprintf_s(line6, 128, "Bota de Mytril (N/M/A)");
		*line6Color = Azul;

		sprintf_s(line7, 128, "");
		*line7Color = Azul;

		sprintf_s(line8, 128, "");
		*line8Color = Azul;

		sprintf_s(line9, 128, "Limite de 4 Categorias Ativas");
		*line9Color = Laranja;

		sprintf_s(line10, 128, "Libera o Drop dos Itens Citados");
		*line10Color = Laranja;
		return 10;
	case 5747:
		sprintf(line1, "[ITENS INCLUSOS NO FILTRO]");
		*line1Color = Verde;

		sprintf_s(line2, 128, "Elmo Templário");
		*line2Color = Azul;

		sprintf_s(line3, 128, "Armadura Templária");
		*line3Color = Azul;

		sprintf_s(line4, 128, "Calça Templária");
		*line4Color = Azul;

		sprintf_s(line5, 128, "Manopla Templária");
		*line5Color = Azul;

		sprintf_s(line6, 128, "Bota Templária");
		*line6Color = Azul;

		sprintf_s(line7, 128, "");
		*line7Color = Azul;

		sprintf_s(line8, 128, "");
		*line8Color = Azul;

		sprintf_s(line9, 128, "Limite de 4 Categorias Ativas");
		*line9Color = Laranja;

		sprintf_s(line10, 128, "Libera o Drop dos Itens Citados");
		*line10Color = Laranja;
		return 10;
	case 5748:
		sprintf(line1, "[ITENS INCLUSOS NO FILTRO]");
		*line1Color = Verde;

		sprintf_s(line2, 128, "Túnica Guardiã");
		*line2Color = Azul;

		sprintf_s(line3, 128, "Calça Guardiã");
		*line3Color = Azul;

		sprintf_s(line4, 128, "Manopla Guardiã");
		*line4Color = Azul;

		sprintf_s(line5, 128, "Bota Guardiã");
		*line5Color = Azul;

		sprintf_s(line6, 128, "");
		*line6Color = Azul;

		sprintf_s(line7, 128, "");
		*line7Color = Azul;

		sprintf_s(line8, 128, "");
		*line8Color = Azul;

		sprintf_s(line9, 128, "Limite de 4 Categorias Ativas");
		*line9Color = Laranja;

		sprintf_s(line10, 128, "Libera o Drop dos Itens Citados");
		*line10Color = Laranja;
		return 10;
	case 5749:
		sprintf(line1, "[ITENS INCLUSOS NO FILTRO]");
		*line1Color = Verde;

		sprintf_s(line2, 128, "Arco Divino");
		*line2Color = Azul;

		sprintf_s(line3, 128, "Espada Vorpal");
		*line3Color = Azul;

		sprintf_s(line4, 128, "Cajado de Âmbar");
		*line4Color = Azul;

		sprintf_s(line5, 128, "Fúria Divina");
		*line5Color = Azul;

		sprintf_s(line6, 128, "");
		*line6Color = Azul;

		sprintf_s(line7, 128, "");
		*line7Color = Azul;

		sprintf_s(line8, 128, "");
		*line8Color = Azul;

		sprintf_s(line9, 128, "Limite de 4 Categorias Ativas");
		*line9Color = Laranja;

		sprintf_s(line10, 128, "Libera o Drop dos Itens Citados");
		*line10Color = Laranja;
		return 10;
	case 5750:
		sprintf(line1, "[ITENS INCLUSOS NO FILTRO]");
		*line1Color = Verde;

		sprintf_s(line2, 128, "Arco Guardião");
		*line2Color = Azul;

		sprintf_s(line3, 128, "Vingadora");
		*line3Color = Azul;

		sprintf_s(line4, 128, "Cajado Caótico");
		*line4Color = Azul;

		sprintf_s(line5, 128, "Força Eterna");
		*line5Color = Azul;

		sprintf_s(line6, 128, "");
		*line6Color = Azul;

		sprintf_s(line7, 128, "");
		*line7Color = Azul;

		sprintf_s(line8, 128, "");
		*line8Color = Azul;

		sprintf_s(line9, 128, "Limite de 4 Categorias Ativas");
		*line9Color = Laranja;

		sprintf_s(line10, 128, "Libera o Drop dos Itens Citados");
		*line10Color = Laranja;
		return 10;
	case 5751:
		sprintf(line1, "[ITENS INCLUSOS NO FILTRO]");
		*line1Color = Verde;

		sprintf_s(line2, 128, "Skytalos");
		*line2Color = Azul;

		sprintf_s(line3, 128, "Caliburn");
		*line3Color = Azul;

		sprintf_s(line4, 128, "Eirenus");
		*line4Color = Azul;

		sprintf_s(line5, 128, "Neorion");
		*line5Color = Azul;

		sprintf_s(line6, 128, "");
		*line6Color = Azul;

		sprintf_s(line7, 128, "");
		*line7Color = Azul;

		sprintf_s(line8, 128, "");
		*line8Color = Azul;

		sprintf_s(line9, 128, "Limite de 4 Categorias Ativas");
		*line9Color = Laranja;

		sprintf_s(line10, 128, "Libera o Drop dos Itens Citados");
		*line10Color = Laranja;
		return 10;



	case 3021:
	case 3022:
	case 3023:
	case 3024:
	case 3025:
	case 3026:
		sprintf(line1, "");
		*line1Color = Branco;

		sprintf_s(line2, 128, "");
		*line2Color = Amarelo;

		sprintf_s(line3, 128, "");
		*line3Color = Amarelo;

		sprintf_s(line4, 128, "[Item_de_Redefinição]");
		*line4Color = Amarelo;

		sprintf_s(line5, 128, "Item_quem_contém_uma_redefinição_de_Atributos.");
		*line5Color = Branco;

		sprintf_s(line6, 128, "Quando_clicado_com_botão_direito,_esta_opção");
		*line6Color = Branco;

		sprintf_s(line7, 128, "será_adicionada_ao_Item_de_mesmo_nível.");
		*line7Color = Branco;

		sprintf_s(line8, 128, "Uso_para_Itens_equipados_e_de_refinação_igual");
		*line8Color = Branco;

		sprintf_s(line9, 128, "ou_superior_a_+9.");
		*line9Color = Branco;

		sprintf_s(line10, 128, "");
		*line10Color = Amarelo;
		return 10;
			
	case 4127:
		sprintf(line1, "");
		*line1Color = Branco;

		sprintf_s(line2, 128, "[Item Especial]");
		*line2Color = Amarelo;

		sprintf_s(line3, 128, "");
		*line3Color = Amarelo;

		sprintf_s(line4, 128, "Usado Para:");
		*line4Color = Vermelho;

		sprintf_s(line5, 128, "Desbloqueio do Level 355/370 do Arch.");
		*line5Color = Branco;

		sprintf_s(line6, 128, "Refinação de Capa Celestail");
		*line6Color = Branco;

		sprintf_s(line7, 128, "Obter entradas para Hall do Kefra");
		*line7Color = Branco;

		sprintf_s(line8, 128, "Criação de Joias Especiais");
		*line8Color = Branco;

		sprintf_s(line9, 128, "");
		*line9Color = Branco;

		sprintf_s(line10, 128, "");
		*line10Color = Amarelo;
		return 10;

	case 5135:
		sprintf(line1, "");
		*line1Color = Amarelo;

		sprintf_s(line2, 128, "");
		*line2Color = Branco;

		sprintf_s(line3, 128, "[Item Especial]");
		*line3Color = Amarelo;

		sprintf_s(line4, 128, "");
		*line4Color = Branco;

		sprintf_s(line5, 128, "Usado Para:");
		*line5Color = Vermelho;

		sprintf_s(line6, 128, "Desbloquio do Level 40 do Celestial.");
		*line6Color = Branco;

		sprintf_s(line7, 128, "Refinação de capa Celestial.");
		*line7Color = Branco;

		sprintf_s(line8, 128, "");
		*line8Color = Branco;

		sprintf_s(line9, 128, "");
		*line9Color = Amarelo;

		sprintf_s(line10, 128, "");
		*line10Color = Amarelo;
		return 10;


	case 3140:
		sprintf(line1, "");
		*line1Color = Amarelo;

		sprintf_s(line2, 128, "");
		*line2Color = Branco;

		sprintf_s(line3, 128, "[Item Especial]");
		*line3Color = Amarelo;

		sprintf_s(line4, 128, "");
		*line4Color = Branco;

		sprintf_s(line5, 128, "");
		*line5Color = Laranja;

		sprintf_s(line6, 128, "Usado_na_transferência_de_adicionais,");
		*line6Color = Branco;

		sprintf_s(line7, 128, "dos_equipamentos_de_defesa.");
		*line7Color = Branco;

		sprintf_s(line8, 128, "");
		*line8Color = Branco;

		sprintf_s(line9, 128, "Equipamentos_de_Mortal_para_Arch.");
		*line9Color = Amarelo;

		sprintf_s(line10, 128, "");
		*line10Color = Amarelo;
		return 10;

	case 3444:
		sprintf(line1, "");
		*line1Color = Branco;

		sprintf_s(line2, 128, "[Item de Contrato]");
		*line2Color = Amarelo;

		sprintf_s(line3, 128, "");
		*line3Color = Amarelo;

		sprintf_s(line4, 128, "Item necessário para fazer contrato");
		*line4Color = Branco;

		sprintf_s(line5, 128, "com um auxiliar.");
		*line5Color = Branco;

		sprintf_s(line6, 128, "");
		*line6Color = Branco;

		sprintf_s(line7, 128, "");
		*line7Color = Branco;

		sprintf_s(line8, 128, "Obs: Necessita de um contrato,");
		*line8Color = Amarelo;

		sprintf_s(line9, 128, "para realizar o contrato");
		*line9Color = Amarelo;

		sprintf_s(line10, 128, "");
		*line10Color = Amarelo;
		return 10;



	case 2420: case 2421: case 2422: case 2423: case 2424: case 2425:
	case 2426: case 2427: case 2428: case 2429: case 2430: case 2431:
	case 2432: case 2433: case 2434: case 2435: case 2436: case 2437:
	case 2438: case 2439:

		sprintf(line1, "");
		*line1Color = Branco;

		sprintf_s(line2, 128, "");
		*line2Color = Branco;

		sprintf_s(line2, 128, "[Item de Cura]");
		*line2Color = Amarelo;

		sprintf_s(line4, 128, "As rações servem para recuperar a");
		*line4Color = Branco;

		sprintf_s(line5, 128, "vida da sua montaria, evitando que");
		*line5Color = Branco;

		sprintf_s(line6, 128, "não morra  e não perca vitalidade.");
		*line6Color = Branco;

		sprintf_s(line7, 128, "");
		*line7Color = Branco;

		sprintf_s(line8, 128, "OBS: Utilizar no atalho do teclado ''V'',");
		*line8Color = Amarelo;

		sprintf_s(line9, 128, "ou no modo automatico ''Rações''");
		*line9Color = Amarelo;
		return 9;

	case 3381:
	case 3380:
	case 3379:
		sprintf(line1, "");
		*line1Color = Branco;

		sprintf_s(line2, 128, "");
		*line2Color = Branco;

		sprintf_s(line3, 128, "[Item Premium]");
		*line3Color = Amarelo;

		sprintf_s(line4, 128, "Aumenta seu Ataque e seu Hp,");
		*line4Color = Branco;

		sprintf_s(line5, 128, "consideravelmente tanto para PvP,");
		*line5Color = Branco;

		sprintf_s(line6, 128, "como para PvM.");
		*line6Color = Branco;

		sprintf_s(line7, 128, "");
		*line7Color = Branco;

		sprintf_s(line8, 128, "OBS: Uso unico efeito não acumulativo.");
		*line8Color = Amarelo;

		sprintf_s(line9, 128, "OBS: Use com o direito do mause.");
		*line9Color = Amarelo;
		return 9;

	case 3364:
	case 3365:
	case 3366:
		sprintf(line1, "");
		*line1Color = Branco;

		sprintf_s(line2, 128, "");
		*line2Color = Branco;

		sprintf_s(line3, 128, "[Item Premium]");
		*line3Color = Amarelo;

		sprintf_s(line4, 128, "Ao utilizar você recebe um bônus");
		*line4Color = Branco;

		sprintf_s(line5, 128, "extra de aumento de  HP e MP");
		*line5Color = Branco;

		sprintf_s(line6, 128, "");
		*line6Color = Branco;

		sprintf_s(line7, 128, "");
		*line7Color = Branco;

		sprintf_s(line8, 128, "OBS: Uso unico efeito não acumulativo..");
		*line8Color = Amarelo;

		sprintf_s(line9, 128, "OBS: Use com o direito do mause.");
		*line9Color = Amarelo;
		return 9;


	case 3312:
	case 787:
		sprintf(line1, "");
		*line1Color = Branco;

		sprintf_s(line2, 128, "");
		*line2Color = Branco;

		sprintf_s(line3, 128, "[Item Premium]");
		*line3Color = Amarelo;

		sprintf_s(line4, 128, "Ao utilizar você recebe um bônus,");
		*line4Color = Branco;

		sprintf_s(line5, 128, "extra de ataque.");
		*line5Color = Branco;

		sprintf_s(line6, 128, "");
		*line6Color = Branco;

		sprintf_s(line7, 128, "");
		*line7Color = Branco;

		sprintf_s(line8, 128, "OBS: Uso unico efeito não acumulativo..");
		*line8Color = Amarelo;

		sprintf_s(line9, 128, "OBS: Use com o direito do mause.");
		*line9Color = Amarelo;
		return 9;

	case 3378:
		sprintf(line1, "");
		*line1Color = Branco;

		sprintf_s(line2, 128, "");
		*line2Color = Branco;

		sprintf_s(line3, 128, "[Item_Premium]");
		*line3Color = Amarelo;

		sprintf_s(line4, 128, "");
		*line4Color = Branco;

		sprintf_s(line5, 128, "Aumento de Bônus PvM");
		*line5Color = Branco;

		sprintf_s(line6, 128, "");
		*line6Color = Branco;

		sprintf_s(line7, 128, "");
		*line7Color = Branco;

		sprintf_s(line8, 128, "Duração:_30_dias.");
		*line8Color = Amarelo;

		sprintf_s(line9, 128, "OBS: Use com o direito do mause.");
		*line9Color = Amarelo;
		return 9;

	case 3467:
		sprintf(line1, "");
		*line1Color = Branco;

		sprintf_s(line2, 128, "");
		*line2Color = Branco;

		sprintf_s(line3, 128, "[Item_Premium]");
		*line3Color = Amarelo;

		sprintf_s(line4, 128, "");
		*line4Color = Branco;

		sprintf_s(line5, 128, "Usando uma bolsa libera um inventario");
		*line5Color = Branco;

		sprintf_s(line6, 128, "Usando outra libera mais um inventario.");
		*line6Color = Branco;

		sprintf_s(line7, 128, "");
		*line7Color = Branco;

		sprintf_s(line8, 128, "Duração:_30_dias.");
		*line8Color = Amarelo;

		sprintf_s(line9, 128, "OBS: Use com o direito do mause.");
		*line9Color = Amarelo;
		return 9;


	case 1740:
		sprintf(line1, "");
		*line1Color = Branco;

		sprintf_s(line2, 128, "");
		*line2Color = Branco;

		sprintf_s(line3, 128, "[Item_de_Classe]");
		*line3Color = Amarelo;

		sprintf_s(line4, 128, "");
		*line4Color = Branco;

		sprintf_s(line5, 128, "Item_que_permite_a_criação_da_Pedra.");
		*line5Color = Branco;

		sprintf_s(line6, 128, "da_Imortalidade.");
		*line6Color = Branco;

		sprintf_s(line7, 128, "");
		*line7Color = Branco;

		sprintf_s(line8, 128, "Obs._Junte_com_a_alma_da_Fenix.");
		*line8Color = Amarelo;

		sprintf_s(line9, 128, "Obs._Leve_ao_Oraculo_do_seu_Reino.");
		*line9Color = Amarelo;
		return 9;

	case 1741:
		sprintf(line1, "");
		*line1Color = Branco;

		sprintf_s(line2, 128, "");
		*line2Color = Branco;

		sprintf_s(line3, 128, "[Item_de_Classe]");
		*line3Color = Amarelo;

		sprintf_s(line4, 128, "");
		*line4Color = Branco;

		sprintf_s(line5, 128, "Item_que_permite_a_criação_da_Pedra.");
		*line5Color = Branco;

		sprintf_s(line6, 128, "da_Imortalidade.");
		*line6Color = Branco;

		sprintf_s(line7, 128, "");
		*line7Color = Branco;

		sprintf_s(line8, 128, "Obs._Junte_com_a_alma_do_Unicornio.");
		*line8Color = Amarelo;

		sprintf_s(line9, 128, "Obs._Leve_ao_Oraculo_do_seu_Reino.");
		*line9Color = Amarelo;
		return 9;

	case 1760:
	case 1761:
	case 1762:
	case 1763:
		sprintf(line1, "");
		*line1Color = Branco;

		sprintf_s(line2, 128, "");
		*line2Color = Branco;

		sprintf_s(line3, 128, "[Item_de_Classe]");
		*line3Color = Amarelo;

		sprintf_s(line4, 128, "");
		*line4Color = Branco;

		sprintf_s(line5, 128, "Item_que_permite_a_mudança_de_classe.");
		*line5Color = Branco;

		sprintf_s(line6, 128, "equipe_no_slot_correspondente..");
		*line6Color = Branco;

		sprintf_s(line7, 128, "");
		*line7Color = Branco;

		sprintf_s(line8, 128, "Obs._Apos_juntar_todos_os_itens..");
		*line8Color = Amarelo;

		sprintf_s(line9, 128, "vá_reino_falar_com_o_rei..");
		*line9Color = Amarelo;
		return 9;

	case 1742:
		sprintf(line1, "");
		*line1Color = Branco;

		sprintf_s(line2, 128, "");
		*line2Color = Branco;

		sprintf_s(line3, 128, "[Item_de_Classe]");
		*line3Color = Amarelo;

		sprintf_s(line4, 128, "");
		*line4Color = Branco;

		sprintf_s(line5, 128, "Item composto feito atravéz das 2 almas.");
		*line5Color = Branco;

		sprintf_s(line6, 128, "equipe_no_slot_correspondente junto com o sephirot.");
		*line6Color = Branco;

		sprintf_s(line7, 128, "");
		*line7Color = Branco;

		sprintf_s(line8, 128, "Obs._Apos_juntar_todos_os_itens..");
		*line8Color = Amarelo;

		sprintf_s(line9, 128, "vá_reino_falar_com_o_rei..");
		*line9Color = Amarelo;
		return 9;

	case 4097:
		sprintf(line1, "");
		*line1Color = Branco;

		sprintf_s(line2, 128, "");
		*line2Color = Branco;

		sprintf_s(line3, 128, "[Item_Premium]");
		*line3Color = Amarelo;

		sprintf_s(line4, 128, "");
		*line4Color = Branco;

		sprintf_s(line5, 128, "Poção_alta_qualidade_que");
		*line5Color = Branco;

		sprintf_s(line6, 128, "recupera_MP_e_HP.");
		*line6Color = Branco;

		sprintf_s(line7, 128, "");
		*line7Color = Branco;

		sprintf_s(line8, 128, "Efeito_HP_1000_e_MP_1000.");
		*line8Color = Amarelo;

		sprintf_s(line9, 128, "OBS: Item não negóciavel.");
		*line9Color = Vermelho;
		return 9;

	case 3431:
		sprintf(line1, "");
		*line1Color = Branco;

		sprintf_s(line2, 128, "");
		*line2Color = Branco;

		sprintf_s(line3, 128, "[Item_Premium]");
		*line3Color = Amarelo;

		sprintf_s(line4, 128, "");
		*line4Color = Branco;

		sprintf_s(line5, 128, "Poção_alta_qualidade_que");
		*line5Color = Branco;

		sprintf_s(line6, 128, "recupera_MP_e_HP.");
		*line6Color = Branco;

		sprintf_s(line7, 128, "");
		*line7Color = Branco;

		sprintf_s(line8, 128, "Efeito_HP_1000_e_MP_1000.");
		*line8Color = Amarelo;

		sprintf_s(line9, 128, "");
		*line9Color = Vermelho;
		return 9;

	case 3314:
	case 3318:
		sprintf(line1, "");
		*line1Color = Branco;

		sprintf_s(line2, 128, "");
		*line2Color = Branco;

		sprintf_s(line3, 128, "[Item_Premium]");
		*line3Color = Amarelo;

		sprintf_s(line4, 128, "");
		*line4Color = Branco;

		sprintf_s(line5, 128, "");
		*line5Color = RoxoRosa;

		sprintf_s(line6, 128, "Com o frango assado você terá um");
		*line6Color = Branco;

		sprintf_s(line7, 128, "bônus extra de 2000 para PvM.");
		*line7Color = Branco;

		sprintf_s(line8, 128, "Tempo ativo: 4 horas");
		*line8Color = Amarelo;

		sprintf_s(line9, 128, "");
		*line9Color = Amarelo;
		return 9;

	case 3216:
		sprintf(line1, "");
		*line1Color = Branco;

		sprintf_s(line2, 128, "");
		*line2Color = Branco;

		sprintf_s(line3, 128, "[Item_Premium]");
		*line3Color = Amarelo;

		sprintf_s(line4, 128, "");
		*line4Color = Branco;

		sprintf_s(line5, 128, "Com o frango assado você terá um");
		*line5Color = Branco;

		sprintf_s(line6, 128, "bônus extra de 2000 para PvM.");
		*line6Color = Branco;

		sprintf_s(line7, 128, "");
		*line7Color = Branco;

		sprintf_s(line8, 128, "Tempo ativo: 4 horas");
		*line8Color = Amarelo;

		sprintf_s(line9, 128, "OBS: Este item não é negociavel.");
		*line9Color = Vermelho;
		return 9;


	case 4140:
	case 4144:
		sprintf(line1, "");
		*line1Color = Branco;

		sprintf_s(line2, 128, "");
		*line2Color = Branco;

		sprintf_s(line3, 128, "[Item_Premium]");
		*line3Color = Amarelo;

		sprintf_s(line4, 128, "");
		*line4Color = Branco;

		sprintf_s(line5, 128, "Com o bau de experiência você obterá");
		*line5Color = Branco;

		sprintf_s(line6, 128, " 2 horas de experiência dobrada.");
		*line6Color = Branco;

		sprintf_s(line7, 128, "");
		*line7Color = Branco;

		sprintf_s(line8, 128, "Tempo_ativo:_2_horas.");
		*line8Color = Amarelo;

		sprintf_s(line9, 128, "");
		*line9Color = Amarelo;
		return 9;

	case 3215:
		sprintf(line1, "");
		*line1Color = Branco;

		sprintf_s(line2, 128, "");
		*line2Color = Branco;

		sprintf_s(line3, 128, "[Item_Premium]");
		*line3Color = Amarelo;

		sprintf_s(line4, 128, "");
		*line4Color = Branco;

		sprintf_s(line5, 128, "Com o bau de experiência você obterá");
		*line5Color = Branco;

		sprintf_s(line6, 128, " 2 horas de experiência dobrada.");
		*line6Color = Branco;

		sprintf_s(line7, 128, "");
		*line7Color = Branco;

		sprintf_s(line8, 128, "Tempo_ativo:_2_horas.");
		*line8Color = Amarelo;

		sprintf_s(line9, 128, "OBS: Este item não é negociavel.");
		*line9Color = Vermelho;
		return 9;

	case 4128:
	case 4129:
	case 4130:
		sprintf(line1, "");
		*line1Color = Branco;

		sprintf_s(line2, 128, "");
		*line2Color = Branco;

		sprintf_s(line3, 128, "[Item_Premium]");
		*line3Color = Amarelo;

		sprintf_s(line4, 128, "");
		*line4Color = Branco;

		sprintf_s(line5, 128, "Após_comprar_procure_uns_dos perzens");
		*line5Color = Branco;

		sprintf_s(line6, 128, "localizados em cada cidade.");
		*line6Color = Branco;

		sprintf_s(line7, 128, "");
		*line7Color = Branco;

		sprintf_s(line8, 128, "");
		*line8Color = Amarelo;

		sprintf_s(line9, 128, "");
		*line9Color = Amarelo;
		return 9;

	case 1774:
		sprintf(line1, "");
		*line1Color = Branco;

		sprintf_s(line2, 128, "");
		*line2Color = Branco;

		sprintf_s(line3, 128, "[Item_Especial]");
		*line3Color = Amarelo;

		sprintf_s(line4, 128, "");
		*line4Color = Branco;

		sprintf_s(line5, 128, "Usado_na_composição_de_itens +10,");
		*line5Color = Branco;

		sprintf_s(line6, 128, "e na criação de cristal de extração.");
		*line6Color = Branco;

		sprintf_s(line7, 128, "");
		*line7Color = Branco;

		sprintf_s(line8, 128, "OBS: Usar com os demais itens,");
		*line8Color = Amarelo;

		sprintf_s(line9, 128, "no caso de falha os itens serão excluidos");
		*line9Color = Amarelo;
		return 9;

	case 4043:
		sprintf(line1, "");
		*line1Color = Branco;

		sprintf_s(line2, 128, "");
		*line2Color = Branco;

		sprintf_s(line3, 128, "[Item_Especial]");
		*line3Color = Amarelo;

		sprintf_s(line4, 128, "");
		*line4Color = Branco;

		sprintf_s(line5, 128, "Usado_para_evitar_a_quebra de_item,");
		*line5Color = Branco;

		sprintf_s(line6, 128, "em_determinadas_refinações.");
		*line6Color = Branco;

		sprintf_s(line7, 128, "");
		*line7Color = Branco;

		sprintf_s(line8, 128, "OBS: Usar com os demais itens,");
		*line8Color = Amarelo;

		sprintf_s(line9, 128, "no NPC Alquimista Odin em HallKefra");
		*line9Color = Amarelo;
		return 9;

	case 4146:
		sprintf(line1, "");
		*line1Color = Branco;

		sprintf_s(line2, 128, "");
		*line2Color = Branco;

		sprintf_s(line3, 128, "[Item_Premium]");
		*line3Color = Amarelo;

		sprintf_s(line4, 128, "");
		*line4Color = Branco;

		sprintf_s(line5, 128, "Ao_usar_receberá_10_pontos_de_Fame.");
		*line5Color = Branco;

		sprintf_s(line6, 128, "");
		*line6Color = Branco;

		sprintf_s(line7, 128, "");
		*line7Color = Branco;

		sprintf_s(line8, 128, "Obs._Este_item_não_aumenta_a,");
		*line8Color = Amarelo;

		sprintf_s(line9, 128, "Guild_Fame_de_sua_guild.");
		*line9Color = Amarelo;
		return 9;		
	}
	

#pragma endregion


	return 0;
}