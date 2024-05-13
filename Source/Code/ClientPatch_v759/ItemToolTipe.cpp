#include "main.h"


enum LineItem : int
{
	Panel = 258,
	Title = 772,
	Line_1 = 773,
	Line_2 = 774,
	Line_3 = 775,
	Line_4 = 776,
	Line_5 = 777,
	Line_6 = 778,
	Line_7 = 779,
	Line_8 = 780,
	Line_9 = 781,
	Price = 782
};


void GameInterface::ItemToolTipe(STRUCT_ITEM* Item)
{
	/*if (!Item)
		return;

	if ( Item->sIndex <= 0 || Item->sIndex >= MAX_ITEMLIST)
		return;
	auto player = GetChar();

	auto panel_principal = this->getGuiFromHandle<UIControl>(258);

	if (!panel_principal)
		return; 
	 
	// Descrição  para itens com feito 
	if (Item->sIndex == 443 && Item->getEffect(EF_AC)) 
	{
		this->setLabel(LineItem::Title, Yellow, "Eita mudei o nome");
	}
	// Descrição para o efeito Feijões 
	for (int i = 0; i < 3; i++)
	{
		if (Item->stEffect[i].cEffect >= 116 && Item->stEffect[i].cEffect <= 125)
		{
			if (Item->sIndex >= 2330 && Item->sIndex <= 2389)
				continue;

			switch (Item->stEffect[i].cEffect)
			{
			/*case 118:
				this->setLabel(LineItem::Line_1, Yellow, "[Cor: Verde]");
				break;
			case 119:
				this->setLabel(LineItem::Line_1, Yellow, "[Cor: Prateado]");
				break;
			case 120:
				this->setLabel(LineItem::Line_1, Yellow, "[Cor: Preto]");
				break;
			case 121:
				this->setLabel(LineItem::Line_1, Yellow, "[Cor: Roxo]");
				break;
			case 122:
				this->setLabel(LineItem::Line_1, Yellow, "[Cor: Marrom]");
				break;
			case 123:
				this->setLabel(LineItem::Line_1, Yellow, "[Cor: Rosa]");
				break;
			case 124:
				this->setLabel(LineItem::Line_1, Yellow, "[Cor: Amarelo]");
				break;
			case 125:
				this->setLabel(LineItem::Line_1, Yellow, "[Cor: Azul Claro]");
				break;
			}
		}
	}*/
}