#pragma once
#include "UIControl.h"
#include <intsafe.h>
#include "Functions.h"

class UISlot : UIControl
{
public:
	UINT32 NextWindows;			 //0x0004
	UINT32 LastWindow;			 //0x0008
	UINT32 OutherElement;		 //0x000C
	UINT32 pad_0010;			 //0x0010
	UINT32 pad_0014;	    	 //0x0014
	UINT32 pad_0018;	    	 //0x0018
	UINT32 pad_001C;	    	 //0x001c
	UINT32 pad_0020;			 //0x0020
	UINT32 pad_0024;			 //0x0024
	UINT32 IsVisible;			 //0x0028
	UINT32 pad_002C;			 //0x002c
	UINT32 pad_0030;			 //0x0030
	UINT32 MouseOver;			 //0x0034
	UINT32 pad_0038;			 //0x0038
	UINT32 pad_003C;			 //0x003C
	UINT32 pad_0040;			 //0x0040
	UINT32 Handle;				 //0x0044
	UINT32 pad_0048;			 //0x0048
	float Left;					 //0x004C
	float Top;					 //0x0050
	float Width;				 //0x0054
	float Height;				 //0x0058
	UINT32 pad_005C;			 //0x005C
	UINT32 pad_0060;			 //0x0060
	UINT32 pad_0064;			 //0x0064
	float ViewLeft;				 //0x0068
	float ViewTop;				 //0x006C
	float ViewWidth;		     //0x0070 
	float ViewHeight;			 //0x0074 
	UINT32 pad_0078;			 //0x0078 
	UINT32 pad_007C;			 //0x007C 
	float Opacity;				 //0x0080 
	UINT32 pad_0084;			 //0x0084	
	UINT32 pad_0088;			 //0x0088  
	UINT32 pad_008C;			 //0x008C 
	UINT32 pad_0090;			 //0x0090 
	UINT32 pad_0094;			 //0x0094  
	UINT32 pad_0098;			 //0x0098  
	UINT32 pad_009C;			 //0x009C  
	UINT32 pad_00A0;			 //0x00A0  
	UINT32 MouseOver2;			 //0x00A4  	  
	UINT32 pad_00A8[83];		 //0x00A8
	UINT32 MouseStatus;		     //0x00FB

public:

	//VTable = 0x5CE024

	virtual void func0(void); //0x425AE0
	virtual void func1(void); //0x40B820 0
	virtual void func2(int a2, int a3, signed int a4, signed int a5); //0x423800 parece ser o evento de push
	virtual void func3(int a2); //0x40F8B5 b
	virtual void func4(void); //0x40B840 0
	virtual void func5(void); //0x40B820 0
	virtual void func6(void); //0x534415 0
	virtual void func7(void); //0x534424 0
	virtual void func8(void); //0x534433 0
	virtual void func9(void); //0x534445 0
	virtual void func10(void); //0x534455 0
	virtual void func11(void); //0x534460 0
	virtual void func12(void); //0x534476 0
	virtual void func13(void); //0x53446B 0
	virtual void func14(void); //0x40B850 0
	virtual void func15(void); //0x40B840 0
	virtual void func16(void); //0x40B850 0
	//virtual GUI_TEXTBOX* setHandle(int a2); //0x40B860
	virtual int getHandle(void); //0x40B880
	virtual void get48(void); //0x40B8A0
	virtual void set5C(int a2); //0x40B8C0
	virtual void func21(void); //0x40B8E0 0
	virtual void func22(int a2, float a3, float a4, int a5, int a6); //0x40F040 b
	virtual void set24(int a2); //0x40B900
	virtual void set28(int a2); //0x40159D
	virtual void set2C(int a2); //0x40B940
	virtual void set30(int a2); //0x40B960
	virtual void func27(void); //0x401419 0 
	virtual void setXY_4C50(float a2, float a3); //0x401233
	virtual void funcLA_5458(int a2, int a3); //0x401267
	virtual void func30(void); //0x40B9D0 -1
	virtual void setAlgo(int a2, int a3, int a4, float a5, int a6); //0x401188
	virtual void setA0(int a2); //0x401584
	virtual void NextElement(void); //0x40B9E0
	virtual void getAlgo(int a2, int a3, int a4, int a5, int a6); //0x40D90D
	virtual void setItemGUI(int ItemGuiAlooc, int coluna, int linha); //0x40D9B3 //Define o Item no Slot
	virtual void setAlgo3(int a2, int a3, int a4); //0x40DB3B b
	virtual void setAlgo4(int a2, int a3, int a4); //0x40DCCC
	virtual void setAlgo5(int a2, int a3); //0x40DE29
	virtual void setAlgo6(int a2, int a3, int a4); //0x40DEEC
	virtual void setAlgo7(int a2, int a3, int a4, int a5); //0x40E234
	virtual void setAlgo8(int a2); //0x40EAB9
	virtual int setAlgo9(int a2, int a3); //0x40E745
	virtual UISlot* delItemGUI(int coluna, int linha); //0x40E8FF a2: XSlot 0 ~4 a3: YSlot: 0~2
	virtual void setAlgo11(int a2, int a3); //0x40EB2F //call qnd cliquei no item
	virtual void getAlgo2(int a2); //0x40D8F3
	virtual int setAlgo12(int a2, int a3); //0x40ECEE  arg1 0, arg2: gui
	virtual void setAlgo13(int a2, int a3); //0x40EE97
	virtual void getAlgo(void); //0x40D7F7
	virtual short func49(int a1, int a2); //0x424AB5
	virtual short func50(int a1); //0x424AF0



public:
	int addElement(int a2) {
		// overElement = 0x534584, aboveElement = 0x5345E1
		// 756 -> 005344A9  /$ 55             PUSH EBP
		// 762 -> 005351E9  /$ 55             PUSH EBP
		return callThiscall(0x5351E9, int, UISlot*, int)(this, a2);
	}

	BOOL delElement(int coluna, int linha) {
		// 756 -> 0040D2A5  /$ 55             PUSH EBP
		// 762 -> 0040DE78  /$ 55             PUSH EBP
		return callThiscall(0x40DE78, BOOL, UISlot*, int, int)(this, coluna, linha);
	}
	
	UISlot* deleteItemGui(DWORD Coluna, DWORD Linha) {
		return callThiscall(0x40F4CB, UISlot*, UISlot*, DWORD, DWORD)(this, Coluna, Linha);
	}


	// ATRIBUI O ITEM
	//----- (0040E586) --------------------------------------------------------
	UISlot* setGui(int ItemGui, int Coluna, int Linha) {
		//DWORD pAllocLabel = callCdecl(0x5C5DD3, DWORD, DWORD)(0x1E4);
		return callThiscall(0x40E586, UISlot*, UISlot*, int, int, int)(this, ItemGui, Coluna, Linha);
	}


	//----- (0040E586) --------------------------------------------------------
	int setItem(int a2, int a3, int a4) {
		return callThiscall(0x40E864, int, UISlot*, int, int, int)(this, a2, a3, a4);
	}

	//----- (0040E586) --------------------------------------------------------
	//----- (0040E6E3) --------------------------------------------------------
	UISlot* sub_40E586(int a2, int a3, int a4)
	{
		return callThiscall(0x40E6E3, UISlot*, UISlot*, int, int, int)(this, a2, a3, a4);
	}

	//----- (0040E6E3) --------------------------------------------------------
	//----- (0040E864) --------------------------------------------------------

	
	//----- (0040D3DE) --------------------------------------------------------
	UISlot* New(STRUCT_ITEM pSlot, float x, float y)
	{
		DWORD pAllocItem = callCdecl(0x5C5DD3, DWORD, DWORD)(0x8u);

		auto STRC_ITEM = reinterpret_cast<STRUCT_ITEM*>(pAllocItem);
		memcpy(STRC_ITEM, &pSlot, sizeof(STRUCT_ITEM));


		DWORD pAlloc = callCdecl(0x5C5DD3, DWORD, DWORD)(0x678u);
		return callThiscall(0x40D3DE, UISlot*, DWORD, DWORD, DWORD, FLOAT, FLOAT)(pAlloc, 0, pAllocItem, x, y);
	}

	UISlot* deleteItems() {
		return callThiscall(0x40E3CA, UISlot*, UISlot*)(this);
	}

};

//enum class TMEGRIDTYPE
//{
//	GRID_DEFAULT = 0,
//	GRID_SHOP = 1,
//	GRID_CARGO = 2,
//	GRID_SELL = 3,
//	GRID_SKILLM = 4,
//	GRID_SKILLB = 5,
//	GRID_TRADEMY = 6,
//	GRID_TRADEINV = 7,
//	GRID_TRADENONE = 8,
//	GRID_TRADEOP = 9,
//	GRID_TRADEINV2 = 10,
//	GRID_TRADEMY2 = 11,
//	GRID_ITEMMIX = 12,
//	GRID_TRADEINV3 = 13,
//	GRID_ITEMMIX4 = 14,
//	GRID_TRADEINV6 = 15,
//	GRID_TRADEINV8 = 16,
//	GRID_CUBEBOX = 17,
//	GRID_QUICKSLOAT1 = 18,
//	GRID_QUICKSLOAT2 = 19,
//	GRID_QUICKSLOAT3 = 20,
//	GRID_QUICKSLOAT4 = 21,
//	GRID_QUICKSLOAT5 = 22,
//	GRID_DELETE = 23,
//	GRID_ITEMMIXRESULT = 24,
//	GRID_ITEMMIXNEED = 25,
//	GRID_MISSION_RESULT = 26,
//	GRID_MISSION_NEED = 27,
//	GRID_MISSION_NEEDLIST = 28,
//};