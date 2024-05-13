#pragma once

extern int gText;

enum class TMEGRIDTYPE
{
	GRID_DEFAULT = 0,
	GRID_SHOP = 1,
	GRID_CARGO = 2,
	GRID_SELL = 3,
	GRID_SKILLM = 4,
	GRID_SKILLB = 5,
	GRID_TRADEMY = 6,
	GRID_TRADEINV = 7,
	GRID_TRADENONE = 8,
	GRID_TRADEOP = 9,
	GRID_TRADEINV2 = 10,
	GRID_TRADEMY2 = 11,
	GRID_ITEMMIX = 12,
	GRID_TRADEINV3 = 13,
	GRID_ITEMMIX4 = 14,
	GRID_TRADEINV6 = 15,
	GRID_TRADEINV8 = 16,
	GRID_CUBEBOX = 17,
	GRID_QUICKSLOAT1 = 18,
	GRID_QUICKSLOAT2 = 19,
	GRID_QUICKSLOAT3 = 20,
	GRID_QUICKSLOAT4 = 21,
	GRID_QUICKSLOAT5 = 22,
	GRID_DELETE = 23,
	GRID_ITEMMIXRESULT = 24,
	GRID_ITEMMIXNEED = 25,
	GRID_MISSION_RESULT = 26,
	GRID_MISSION_NEED = 27,
	GRID_MISSION_NEEDLIST = 28,
};

class UIControl
{
protected:
	UIControl* MainClass;
	UIControl* pad_0004;
	UIControl* NextWindows;
	UIControl* LastWindow;
public:
	UINT32 Unk_01;
	UINT32 Unk_02;
	UINT32 Unk_03;
	UINT32 Unk_04;
	UINT32 Unk_05;
	UINT32 IsVisible;
	UINT32 Unk_06;
	UINT32 Unk_07;
	UINT32 MouseOver;
	UINT32 TextureID;
	UINT32 Unk_08;
	UINT32 ControlType;
	UINT32 Handle;
	UINT32 Unk_09;
	float Left;
	float Top;
	float Width;
	float Height;

	UINT32 pad_005C[3]; //0x005C
	float ViewLeft; //0x0068
	float ViewTop; //0x006C
	float ViewWidth; //0x0070
	float ViewHeight; //0x0074
	UINT32 pad_0078[8]; //0x0078
	UINT32 Opacity; //0x0094
	UINT32 pad_0098[2]; //0x0098
	UINT32 SpriteIndex; //0x00A0
	UINT32 MouseStats; //0x00A4
	UINT32 pad_00a4[73]; //0x00A4
	UINT32 PosX;
	UINT32 PosY;
	UINT32 Unk;

protected:
	UIControl* ReferencedClass;
public:
	unsigned int ScreenMove;
	virtual void above(void);

	UIControl* getMainClass()
	{
		if (!this->MainClass)
			return NULL;

		return this->MainClass;
	}

	int getMainHandle()
	{
		if (auto main = this->getMainClass())
			return main->Handle;

		return NULL;
	}


	template<class T> int  addElement(T* Componente)
	{
		return callThiscall(0x005351E9, int, UIControl*, T*)(this, Componente);
	}



	void setHandle(int hand) {
		this->Handle = hand;
	}

	void moveWindow(float X, float Y) {
		this->Left = X;
		this->Top = Y;
	}

	void Show() {
		this->IsVisible != this->IsVisible;
	}

	//----- (0040E586) --------------------------------------------------------
	//----- (0040E6E3) --------------------------------------------------------
	//----- (0040E586) --------------------------------------------------------
	int sub_40E6E3(int a2, int a3, int a4)
	{
		return callThiscall(0x40E586, int, UIControl*, int, int, int)(this, a2, a3, a4);
	}

	//----- (004128BD) --------------------------------------------------------
	int sub_4128BD(int a2, int a3, int a4, int a5) {
		return callThiscall(0x4128BD, int, UIControl*, int, int, int, int)(this, a2, a3, a5, a5);
	}

	// ---- - (0040D3DE)--------------------------------------------------------
	UIControl* New(STRUCT_ITEM pSlot, float x, float y)
	{
		DWORD pAllocItem = callCdecl(0x5C5DD3, DWORD, DWORD)(0x8u);

		auto STRC_ITEM = reinterpret_cast<STRUCT_ITEM*>(pAllocItem);
		memcpy(STRC_ITEM, &pSlot, sizeof(STRUCT_ITEM));


		DWORD pAlloc = callCdecl(0x5C5DD3, DWORD, DWORD)(0x678u);
		return callThiscall(0x40D3DE, UIControl*, DWORD, DWORD, DWORD, FLOAT, FLOAT)(pAlloc, 0, pAllocItem, x, y);
	}


};