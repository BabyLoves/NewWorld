#pragma once
#include "Structs.h"
#include "Functions.h"
#include <d3d9.h>
#include <stdio.h>

//----- (0040D3DE) --------------------------------------------------------
class GUI_GRID_INV
{
public:
	static GUI_GRID_INV* New(STRUCT_ITEM pSlot, float x, float y)
	{
		DWORD pAllocItem = callCdecl(0x5C5DD3, DWORD, DWORD)(0x8);

		auto STRC_ITEM = reinterpret_cast<STRUCT_ITEM*>(pAllocItem);
		memcpy(STRC_ITEM, &pSlot, 8);


		DWORD pAlloc = callCdecl(0x5C5DD3, DWORD, DWORD)(0x678);
		return callThiscall(0x40D3DE, GUI_GRID_INV*, DWORD, DWORD, DWORD, FLOAT, FLOAT)(pAlloc, 0, pAllocItem, x, y);
	}
};

//DirectX
class DirectX
{
public:
	char Unknown_0x0000[0xFC];
	HANDLE windowHandle; // 0x00FC
	char Unknown_0x0100[0x8];
	LPDIRECT3D9 pD3D9; // 0x0108
	LPDIRECT3DDEVICE9 pDevice; // 0x010C
	char Unknown_0x0110[0x154];
	int windowStyle; // 0x0264
	LPRECT windowRect; // 0x0268
public:
	// Singleton
	static DirectX* getInstance()
	{
		// Return Instance
		return (DirectX*)(*(PDWORD)0x6075A8);
	}
};

class Gui //0x005cd418
{
public:
	UINT32 pad_0000; //0x0000
	UINT32 pad_0004; //0x0004
	UINT32 NextWindows; //0x0008
	UINT32 LastWindow; //0x000C
	UINT32 OutherElement; //0x0010
	UINT32 pad_0010; //0x0014
	UINT32 pad_0014; //0x0018
	UINT32 pad_0018; //0x01c
	UINT32 pad_001C; //0x0020
	UINT32 IsVisible; //0x0024
	UINT32 pad_002C[3]; //0x002C
	UINT32 MouseOver; //0x0034
	UINT32 pad_0038[2]; //0x0038
	UINT32 Handle; //0x0044
	UINT32 pad_0048; //0x0048
	float Left; //0x004C
	float Top; //0x0050
	float Width; //0x0054
	float Height; //0x0058
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
	UINT32 ScreenMove;
public:
	virtual void func0(void); //0x0040b200
	virtual void func1(void); //0x0040b820
	virtual void func2(void); //0x004016e6
	virtual void func3(void); //0x0040b840
	virtual void func4(void); //0x0040b840
	virtual void func5(void); //0x0040b820
	virtual void func6(void); //0x00534415
	virtual void func7(void); //0x00534424
	virtual void func8(void); //0x00534433
	virtual void func9(void); //0x00534445
	virtual void func10(void); //0x00534455
	virtual void func11(void); //0x00534460
	virtual void func12(void); //0x00534476
	virtual void func13(void); //0x0053446b
	virtual void func14(void); //0x0040b850
	virtual void func15(void); //0x0040b840
	virtual void func16(void); //0x0040b850
	virtual Gui* setHandle(int);  // Function 17 //0x0040b860
	virtual int getHandle(void);  // Function 18 //0x0040b880
	virtual float getLeft(void); // Function 19  //0x0040b8a0
	virtual float getTop(void);  // Function 20 //0x0040b8c0
	virtual void func21(void); // Breaked Func  //0x0040b8e0
	virtual void func22(void); // Breaked Func  //0x004015f7
	virtual void func23(void); // Breaked Func  //0x0040b900
	virtual Gui* setVisible(BOOL visible); // Function 24 //0x0040159d
	virtual void func25(void); //0x0040b940
	virtual void func26(void); //0x0040b960
	virtual void func27(void); //0x00401419
	virtual void func28(void); //0x00401233
	virtual void func29(void); //0x00401267
	virtual void func30(void); //0x0040b9d0
	virtual void func31(void); //0x00401188
	virtual void setSprite(int index); //0x00401584 // Window = (int index), Label = (const char* text, int unknown)
public:
	Gui* addElement(Gui* element) {
		// overElement = 0x534584, aboveElement = 0x5345E1
		// 756 -> 005344A9  /$ 55             PUSH EBP
		// 762 -> 005351E9  /$ 55             PUSH EBP
		return callThiscall(0x5351E9, Gui*, Gui*, Gui*)(this, element);
	}

	//----- (0040C714) --------------------------------------------------------
	void ClickButton(int a2) {
		printf("0040C714 -> ");
		return callThiscall(0x40C714, void, Gui*, int)(this, a2);
	}

	//----- (004B23B4) --------------------------------------------------------
	int Click(int a2, int a3) {
		printf("004B23B4 -> ");
		return callThiscall(0x4B23B4, int, Gui*, int, int)(this, a2, a3);
	}

};

class Interface
{
public:
	virtual void func0(char a2); //0x40C720
	virtual void func1(void); //0x5343CA 0
	virtual int MouseEvent(int clickorder, int clickevent, int x, int y); //0x40BF0D //MouseEvent
	virtual int TextEvent(int character); //0x40C146
	virtual int setText1(int a2); //0x40C1EC
	virtual int sendKey(char a2, int handler); //0x40C2AE //Envia a Tecla para o TextBox
	virtual void func6(void); //0x534415 0
	virtual void func7(void); //0x534424 0
	virtual int func8(int a2); //0x40C4F8
	virtual void func9(void); //0x534445 1
	virtual void func10(void); //0x534455 void
	virtual void func11(void); //0x534460 void
	virtual void func12(void); //0x534476 void
	virtual void func13(void); //0x53446B void
	virtual int func14(void); //0x40C2EA			break
	virtual int func15(int a2); //0x40C31C			break
	virtual void ClickButton(int handle); //0x40BDD4
	virtual Gui* addWindow(Gui* element); //0x40C292
	virtual Gui* getGui(int handle); //0x40C67E

};

class MessageBoxGUI
{
public:
	virtual void func0(char a2); //0x40B2F0
	virtual void func1(void); //0x40B820 0
	virtual int func2(int a2, int a3, int a4, int a5); //0x404A30 break
	virtual void func3(void); //0x40B840 0
	virtual void func4(void); //0x40B840 0
	virtual int func5(char a2, int a3); //0x404B00  break
	virtual void func6(void); //0x534415 0
	virtual void func7(void); //0x534424 0
	virtual void func8(void); //0x534433 0
	virtual void func9(void); //0x534445 0
	virtual void func10(void); //0x534455 0
	virtual void func11(void); //0x534460 0
	virtual void func12(void); //0x534476 0 
	virtual void func13(void); //0x53446B 0
	virtual void func14(void); //0x40B850  0
	virtual void func15(void); //0x40B840  0
	virtual void func16(void); //0x40B850  0
	virtual Gui* setHandle(int a2); //0x40B860
	virtual int getHandle(void); //0x40B880
	virtual float getLeft(void);//0x40B8A0
	virtual float getTop(void); //0x40B8C0
	virtual void func21(void); //0x40B8E0 0
	virtual void func22(int a2, int a3, int a4, int a5); //0x404C8B break
	virtual int func23(int a2); //0x40B900 break
	virtual void setVisible(BOOL visible); //0x4049C0 break
	virtual int func25(int a2); //0x40B940
	virtual int func26(int a2); //0x40B960
	virtual void func27(void); //0x401419
	virtual int setLeftTop(float a2, float a3); //0x401233
	virtual int setWidthHeight(int a2, int a3); //0x401267
	virtual void func30(void); //0x40B9D0
	virtual void func31(int a2, int a3, int a4, float a5, int a6); //0x401188 break
	virtual int func32(int a2); //0x401584
	virtual const char* func33(void); //0x40B9E0
	virtual int func34(int a2); //0x404993
	virtual int setMessage(const char* message1, int Action, const char* message2); //0x404865 //Action é como se fosse a checagem do que é pra fazer
	virtual int func36(void); //0x4049AC
};

class VTable_1
{
public:
	virtual void func0(void); //0x4BA120
	virtual int func1(int a2, int a3); //0x4B9937
	virtual int MouseInfor(int mousestatus, int isclicked, int x, int y); //0x4A654B
	virtual int func3(int a2); //0x4A65B6
	virtual int func4(int a2); //0x4A6609
	virtual int func5(char a2, int a3); //0x4B635B
	virtual void func6(void); //0x534415 0
	virtual void func7(void); //0x534424 0
	virtual int func8(int a2); //0x4B64B3 
	virtual void func9(void); //0x534445 1
	virtual void func10(void); //0x534455 0
	virtual void func11(void); //0x534460 0
	virtual void func12(void); //0x534476 0
	virtual void func13(void); //0x53446B 0
	virtual int get28(void); //0x4A055A
	virtual int func15(char a2); //0x4A05E2									(Deleta/Cria a cena do slot (Mundo?))
	virtual int func16(unsigned int a2, unsigned int a3, const char* a4); //0x4A071E
	virtual int func17(const char* a2); //0x4A2C88							(Criação da Cena de Login)
	virtual int func18(const char* a2); //0x4A3F78
	virtual int func19(void); //0x4B4A98									(Criação de Cena inicial? )
	virtual int func20(int a2); //0x4A66E8
	virtual bool getAlgo(void); //0x4A66B5 (Aparentemente algo sobre visibilidade)
	virtual int ClickEvent(int handle, int tipo); //0x4B7DE9
	virtual void func23(void); //0x4A6539 0
	virtual int getAlgo2(void); //0x4A058A
	virtual void func25(void); //0x4A672F 0


};

class VTable_2
{
public:
	virtual void func0(void); //0x4BF490 


	virtual void func1(void); //0x4BDC3A 0
	virtual int func2(int a2, unsigned int a3); //0x4BE0BA //seta algo
	virtual int func3(int clicktipe, int a2, int x, int y); //0x4BE1B7
	virtual int func4(int a1); //0x4BE30F // quando pressiona a tecla coisa da tecla
	virtual int func5(int a1); //0x4BE3A2 retorna algo
	virtual int func6(char a1, int a2); //0x4BE435
	virtual void func7(void); //0x4BE4CC retorna nada, mas executa algo
	virtual int func8(int a1); //0x4BE50B
	virtual int func9(int a2, int a3); //0x4BE536
	virtual void func10(int a2); //0x4BE7B1 //setar algo
	virtual int func11(int a1, int a2); //0x4BE8C2 //seta algo
	virtual int func12(int a1); //0x4BE5D1
	virtual int func13(int a1); //0x4BE66F

	virtual int func14(int a1); //0x4BE710
	virtual int func15(void); //0x4BE985 //retorna algo
	virtual int func16(void); //0x4BEA00 //retorna algo
	virtual int func17(void); //0x4BEA7B //seta
	virtual void func18(void); //0x4BEBC2 //seta algo
	virtual int func19(int a1, int a2, float a3); //0x4BEC5F
	virtual int LoadSceneWorld(int a2); //0x4BEEBD //so usar o 9 que ele da reload

	virtual int func21(int a2); //0x4BF23B //seta Algo
	virtual int func22(void); //0x4BF3C4 retorna o 6BDAF0
	virtual int func23(int a2); //0x4BDC6C
	virtual int func24(int a2); //0x4BDC45 seta algo no a2 e no this
	virtual int func25(int a1); //0x4BE256 retorna algo
	virtual int func26(void); //0x4BDCA7 // RC.Bin
	virtual int func27(void); //0x4BDDBC // AniSound.txt
	virtual char* func28(void); //0x4BDD1A //Curse.bin
	virtual int func29(void); //0x4BF560
};

class VTable_3
{
public:

	virtual void func0(char a2); //0x4C6CC0
	virtual int func1(int a2); //0x4C6BB5 //seta o timegettime no elemento da call 
	virtual int func2(void); //0x4C6BEF
	virtual int set5C(int a2); //0x4C6C99 //set 5C	
	virtual void get5C(void); //0x4C6CAF //get 5C
};

class VTable_4
{
public:

	virtual void func0(void); // 0x40B820 0
	virtual int func1(int a2, int a3, int a4, int a5); // 0x409758
	virtual void func2(void); // 0x40B840 0
	virtual void func3(void); // 0x40B840 0
	virtual void func4(void); // 0x40B820 0
	virtual void func5(void); // 0x534415 0
	virtual void func6(void); // 0x534424 0
	virtual void func7(void); // 0x534433 1
	virtual void func8(void); // 0x534445 1
	virtual void func9(void); // 0x534455 nd
	virtual void func10(void); // 0x534460 nd 
	virtual void func11(void); // 0x534476 nd
	virtual void func12(void); // 0x53446B nd
	virtual void func13(void); // 0x40B850 0
	virtual void func14(void); // 0x40B840 0
	virtual void func15(void); // 0x40B850 0
	virtual int set44(int a2); // 0x40B860
	virtual int get44(void); // 0x40B880
	virtual int get48(void); // 0x40B8A0
	virtual int set5C(int a2); // 0x40B8C0
	virtual void func16(void); // 0x40B8E0 nd
	virtual signed int func17(int a2, int a3, int a4, signed int a5, int a6); // 0x4097D1 //methodo grande
	virtual int set24(int a2); // 0x40B900
	virtual int set28(int a2); // 0x4097BB
	virtual int set2C(int a2); // 0x40B940
	virtual int set30(int a2); // 0x40B960
	virtual void func18(void); // 0x401419 0
	virtual int set4C50(float a2, float a3); // 0x401233 LEFT TOP ?
	virtual int set5458(int a2, int a3); // 0x401267 LARGURA ALTURA ?
	virtual void func19(void); // 0x40B9D0 -1
	virtual int func0(int a2, int a3, int a4, float a5, int a6); // 0x401188
	virtual int setA0(int a2); // 0x401584
	virtual char* get64(void); // 0x40B9E0
	virtual int set4C50(signed int a2, signed int a3); // 0x40979C
	virtual int set1E4(int a2); // 0x409A16
	virtual int get1E4(void); // 0x409A2F
	virtual void set1E8(int a2); // 0x409A43 porem seta mais coisa quer isso
	virtual int func20(void); // 0x409A88 troca de valores entre 1E4 e 1E8

};

class VTable_5 //005CE6CC 0049A224
{
public:
	virtual void func0(char a2); //0x4C6CC0
	virtual int func1(int a2); //0x4C6BB5
	virtual unsigned int getTimer(void); //0x4C6BEF
	virtual VTable_5* set5C(int a2); //0x4C6C99
	virtual int get5C(void); //0x4C6CAF
};

class VTable_6 //005CE1BC 006075A8
{
public:
	virtual void func0(int a2); //0x433161 Load UITextureSetList.txt
	virtual void func1(char a1); //0x42B938
	virtual void func2(void); //0x43B8D0
	virtual void func3(void); //0x42B75A
	virtual void func4(void); //0x40B850 0
	virtual void func5(void); //0x40B850 0
	virtual void func6(void); //0x433EFE
	virtual void func7(void); //0x40B850 0
	virtual void func8(void); //0x40B850 0
	virtual void func9(void); //0x435CE4
	virtual void func10(void); //0x40B850 0
	virtual void func11(void); //0x42C1C0 0
	virtual void func12(void); //0x433905
	virtual void func13(void); //0x435FD8
	virtual void func14(void); //0x43606D
	virtual void func15(void); //0x436293
	virtual void func16(void); //0x43B60F
};

class VTable_7 //
{
public:

};

class Game
{
	//public:
		//Function 22 = UI_Action
public:
	char Unknown_0x0000[0x28];

	Interface* pInterface;			//0x005cdf34
	Interface* pInterface1;			//0x005cf198    livre
	Interface* pInterface2;			//0x005cf198    livre
	Interface* pInterface3;			//0x005cf198    livre
	Interface* pInterface4;			//0x005cf198    livre
	Interface* pInterface5;			//0x005cf198    livre
	Interface* pInterface6;			//0x005cecf4	livre
	Interface* pInterface7;			//0x005cf09c	livre
	Interface* pInterface8;			//0x005d0200	livre
	Interface* pInterface9;			//0x005ce9bc	-- Analisar depois

	char Unknown_0x002C[8];
	Interface* pInterface10;		//0x005cd49c
	Interface* pInterface11;		//0x005cd5b8

	Interface* pInterface12;		//0x005cd670
	Interface* pInterface13;		//0x005cf198
	Interface* pInterface14;		//0x005cecf4
	char Unknown_0x002D[4];			//
	Interface* pInterface15;		//0x005cef24
	char Unknown_0x002E[16];		//
	Interface* pInterface16;		//0x005cd704
	Interface* pInterface17;		//0x005cd5b8
	MessageBoxGUI* pMessageBox;		// 0x005cd7a0
	Interface* pInterface18;		//0x005cd7a0
public:
	// Singleton
	static Game* getInstance()
	{
		// Instance
		PDWORD g_pGameClass = (PDWORD)0x6BDAF0;

		// Return Instance
		return (Game*)(*g_pGameClass);
	}

	static  VTable_1* getFunc()
	{
		PDWORD g_pGameClass = (PDWORD)0x6BDAF0;
		return (VTable_1*)(*g_pGameClass);
	}

	static  Gui* get()
	{
		PDWORD g_pGameClass = (PDWORD)0x6BDAF0;
		return (Gui*)(*g_pGameClass);
	}

	static  VTable_2* getFunc2()
	{
		PDWORD g_pGameClass = (PDWORD)0x13FA9D4;
		return (VTable_2*)(*g_pGameClass);
	}

	static  VTable_3* getFunc3()
	{
		PDWORD g_pGameClass = (PDWORD)0x96F20C;
		return (VTable_3*)(*g_pGameClass);
	}

	static  VTable_4* getFunc4()
	{
		PDWORD g_pGameClass = (PDWORD)0x606D80;
		return (VTable_4*)(*g_pGameClass);

	}

	static  VTable_5* getFunc5()
	{
		PDWORD g_pGameClass = (PDWORD)0x13FA9C8;
		return (VTable_5*)(*g_pGameClass);

	}

	static  VTable_6* getFunc6()
	{
		PDWORD g_pGameClass = (PDWORD)0x6075A8;
		auto T = *(int*)g_pGameClass;
		return (VTable_6*)(*(int*)T);

	}

	static  VTable_7* getFunc7()
	{
		PDWORD g_pGameClass = (PDWORD)0x13FA9C8;
		auto T = *(int*)g_pGameClass;
		return (VTable_7*)(*(int*)T);

	}




	//

};

/*Ultilizando ele pra erva E*/
class GUI_UNK
{
public:


public:

	//005CDF88 
	virtual void func0(char a2); //0x425AB0
	virtual void func1(void); //0x40B820
	virtual void func2(void); //0x401BBF
	virtual void func3(void); //0x40B840
	virtual void func4(void); //0x40B840
	virtual void func5(void); //0x40B820
	virtual void func6(void); //0x534415
	virtual void func7(void); //0x534424
	virtual void func8(void); //0x534433
	virtual void func9(void); //0x534445
	virtual void func10(void); //0x534455
	virtual void func11(void); //0x534460
	virtual void func12(void); //0x534476
	virtual void func13(void); //0x53446B
	virtual void func14(void); //0x40B850
	virtual void func15(void); //0x40B840
	virtual void func16(void); //0x40B850
	virtual void func17(void); //0x40B860
	virtual void func18(void); //0x40B880
	virtual void func19(void); //0x40B8A0
	virtual void func20(void); //0x40B8C0
	virtual void func21(void); //0x40B8E0
	virtual void func22(void); //0x40D16D
	virtual void func23(void); //0x40B900
	virtual void func24(void); //0x40B920
	virtual void func25(void); //0x40B940
	virtual void func26(void); //0x40B960
	virtual void func27(void); //0x401419
	virtual void func28(void); //0x401233
	virtual void func29(void); //0x401267
	virtual void func30(void); //0x40B9D0
	virtual void func31(void); //0x401188
	virtual void func32(void); //0x401BA6
	virtual void func33(void); //0x40B9E0
	virtual void func34(void); //0x40D206
	virtual void func35(void); //0x40D21F
	virtual void func36(void); //0x425B40
	virtual void func37(void); //0x425B60
	virtual void func38(void); //0x425B80
};

/*Conjunto de elemento*/
class GUI_CONJ
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
	UINT32 IsEnable;			 //0x003C
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
	UINT32 SpriteIndex;			 //0x00A0  
	UINT32 MouseOver2;			 //0x00A4  	  
	UINT32 pad_00A8[82];		 //0x00A8
	UINT32 pad_00FA;			 //0x00FA
	UINT32 MouseStatus;		     //0x00FE

public:
	//5CDB38
	virtual void func0(char a2); //0x40B430
	virtual int func1(int a1, int a2); //0x40B820 0
	virtual int func2(int a2, int a3, int a4, int a5); //0x4021BF
	virtual int func3(int a1); //0x40B840 0
	virtual int func4(int a1); //0x40B840 0
	virtual int func5(int a1, int a2); //0x40B820 0
	virtual void func6(void); //0x534415 0
	virtual void func7(void); //0x534424 0
	virtual void func8(void); //0x534433 1
	virtual void func9(void); //0x534445 1 
	virtual void func10(void); //0x534455 nd
	virtual void func11(void); //0x534460 nd
	virtual void func12(void); //0x534476 nd
	virtual void func13(void); //0x53446B nd
	virtual void func14(void); //0x40B850 0
	virtual void func15(void); //0x40B840 0
	virtual void func16(void); //0x40B850 0
	virtual GUI_CONJ* set44(int valor); //0x40B860
	virtual int get44(void); //0x40B880
	virtual int get48(void); //0x40B8A0
	virtual GUI_CONJ* set5C(int valor); //0x40B8C0
	virtual void func17(void); //0x40B8E0 nd
	virtual void func18(int a2, float a3, float a4, int a5, int a6); //0x407453
	virtual GUI_CONJ* set24(int valor); //0x40B900
	virtual GUI_CONJ* set28(int valor); //0x40B920
	virtual GUI_CONJ* set2C(int valor); //0x40B940
	virtual GUI_CONJ* set30(int valor); //0x40B960
	virtual void func19(void); //0x401419 0
	virtual void set4C50(float a2, float a3); //0x401233
	virtual void set5458(int a2, int a3); //0x401267
	virtual void func20(void); //0x40B9D0 -1
	virtual int func21(int a2, int a3, int a4, float a5, int a6); //0x401188
	virtual int func22(int a2, int a3); //0x40231F
	virtual unsigned int func23(unsigned int a2); //0x4020FF
	virtual char* get76C(void); //0x40296E
	virtual int setAlgo(int a2); //0x40220B //seta monte de coisa
};

class GUI_BUTTON
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
	UINT32 IsEnable;			 //0x003C
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
	UINT32 SpriteIndex;			 //0x00A0  
	UINT32 MouseOver2;			 //0x00A4  	  
	UINT32 pad_00A8[82];		 //0x00A8
	UINT32 pad_00FA;			 //0x00FA
	UINT32 MouseStatus;		     //0x00FE

public:

	//0x005cd670 
	virtual void func0(void); //0x40B290
	virtual void func1(void); //0x40B820 //sempre 0
	virtual int func2(int a2, int a3, int a4, int a5); //0x403769
	virtual int func3(void); //0x40B840 //sempre 0
	virtual int func4(void); //0x40B840 //sempre 0
	virtual int func5(void); //0x40B820 //sempre 0
	virtual int func6(void); //0x534415 //sempre 0
	virtual int func7(void); //0x534424 //sempre 0
	virtual int func8(void); //0x534433 //sempre 1
	virtual int func9(void); //0x534445 //sempre 1
	virtual void func10(void); //0x534455 0
	virtual void func11(void); //0x534460 0
	virtual void func12(void); //0x534476 0
	virtual void func13(void); //0x53446B 0
	virtual int  func14(void); //0x40B850 //sempre 0
	virtual void func15(void); //0x40B840 //sempre 0
	virtual void func16(void); //0x40B850 0
	virtual GUI_BUTTON* setHandle(int a2); //0x40B860
	virtual int getHandle(void); //0x40B880
	virtual float getLeft(void); //0x40B8A0 estranho
	virtual float getTop(void); //0x40B8C0 estranho
	virtual GUI_BUTTON* func21(void); //0x403C2C //analizar - Algo Relacionado ao Click
	virtual int func22(int a2, float a3, float a4, int a5, int a6); //0x403A86 //analisar
	virtual GUI_BUTTON* unkfuncB(int); //0x40B900
	virtual GUI_BUTTON* setVisible(int visible); //0x40159D
	virtual void set2C(void); //0x40B940
	virtual void set30(void); //0x40B960
	virtual void func27(void); //0x401419 /retorna sempre 0
	virtual int setLeftTop(float a2, float a3); //0x401233
	virtual int setWidthHeight(float a2, float a3); //0x401267
	virtual void func30(void); //0x40B9D0 //retorna sempre -1
	virtual int func31(int handle, int x, int y, float largura, int altura); //0x401188
	virtual int get64(void); //0x40B9E0
	virtual int func34(int a2); //0x4036FA
	virtual void set1E8(int a2); //0x40BA00
public:
	GUI_BUTTON* addElement(GUI_BUTTON* element) {
		// overElement = 0x534584, aboveElement = 0x5345E1
		// 756 -> 005344A9  /$ 55             PUSH EBP
		// 762 -> 005351E9  /$ 55             PUSH EBP
		return callThiscall(0x5351E9, GUI_BUTTON*, GUI_BUTTON*, GUI_BUTTON*)(this, element);
	}
};

class GUI_LABEL
{
public:
	UINT32 pad_0000;		//0x0000
	UINT32 pad_0004;		//0x0004
	UINT32 NextWindows;		//0x0008
	UINT32 LastWindow;		//0x000C
	UINT32 OutherElement;	//0x0010
	UINT32 pad_0010[4];		//0x0014
	UINT32 IsVisible;		//0x0028
	UINT32 pad_002C[3];		//0x002C
	UINT32 MouseOver;		//0x0034
	UINT32 pad_0038[2];		//0x0038
	UINT32 Handle;			//0x0044
	UINT32 pad_0048;		//0x0048
	float Left;				//0x004C
	float Top;				//0x0050
	float Width;			//0x0054
	float Height;			//0x0058
	UINT32 pad_005C[3];		//0x005C
	float ViewLeft;			//0x0068
	float ViewTop;			//0x006C
	float ViewWidth;		//0x0070
	float ViewHeight;		//0x0074
	UINT32 pad_0078[8];		//0x0078
	UINT32 Opacity;			//0x0094
	UINT32 pad_0098[2];		//0x0098
	UINT32 SpriteIndex;		//0x00A0
	UINT32 MouseStats;		//0x00A4
	UINT32 pad_00a4[73];	//0x00A4
	UINT32 PosX;
	UINT32 PosY;
	UINT32 Unk;
	UINT32 ScreenMove;
public:

	//0x005cd5b8
	virtual void func0(void); //0x40B260
	virtual int func1(void); //0x40B820 0
	virtual int func2(int a2, int a3, int a4, int a5); //0x4021BF // 
	virtual void func3(void); //0x40B840 0
	virtual void func4(void); //0x40B840 0
	virtual void func5(void); //0x40B820 0
	virtual void func6(void); //0x534415 0 
	virtual void func7(void); //0x534424 0 
	virtual void func8(void); //0x534433 1
	virtual void func9(void); //0x534445 1
	virtual void func10(void); //0x534455
	virtual void func11(void); //0x534460
	virtual void func12(void); //0x534476
	virtual void func13(void); //0x53446B
	virtual void func14(void); //0x40B850 0
	virtual void func15(void); //0x40B840
	virtual void func16(void); //0x40B850
	virtual GUI_LABEL* setHandle(int a2); //0x40B860
	virtual int getHandle(void); //0x40B880
	virtual  float getLeft(void); //0x40B8A0
	virtual  float getTop(void);  //0x40B8C0
	virtual void func21(void); //0x40B8E0
	virtual void func22(int gui, float left, float top, int s02, int s00); //0x402981 // por breakpoint
	virtual void func23(void); //0x40B900
	virtual GUI_LABEL* setVisible(int a2); //0x40B920 break
	virtual void func25(void); //0x40B940 ----
	virtual void func26(void); //0x40B960 ----
	virtual void func27(void); //0x401419 0
	virtual int setLeftTop(float x, float y); //0x401233
	virtual int setWidthHeight(int a2, int a3); //0x401267
	virtual void func30(void); //0x40B9D0 -1
	virtual void func31(void); //0x401188
	virtual int setText(const char* txt, int zero); //0x40231F -- por breapoint //Parece ser a função de atualuizar
	virtual unsigned int func33(unsigned int a2); //0x4020FF
	virtual const char* getText(void); //0x40296E
	virtual GUI_LABEL* func35(int a2); //0x40220B
public:
	GUI_LABEL* addElement(GUI_LABEL* element) {
		// overElement = 0x534584, aboveElement = 0x5345E1
		// 756 -> 005344A9  /$ 55             PUSH EBP
		// 762 -> 005351E9  /$ 55             PUSH EBP
		return callThiscall(0x5351E9, GUI_LABEL*, GUI_LABEL*, GUI_LABEL*)(this, element);
	}



};

class GUI_TEXTBOX
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
	UINT32 Reference;			 //0x005C
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
	//5CD978
	virtual void func0(char a2); //0x40B3A0
	virtual void func1(void); //0x40B820 0
	virtual void func2(int index, int zero, int a4, int cor); //0x4062D9 break //0x200 0 675  0xFFFFFFB5
	virtual void CheckShiftPress(int a2); //0x40637D break //parece ser o callback de qnd digita a é o caracter
	virtual bool getAlgo(int a2); //0x406451 a2 zero
	virtual int CallBackSendKey(char a2, int zero); //0x406470 parece que ele recebe o delete tbm
	virtual void func6(void); //0x534415 0
	virtual void func7(void); //0x534424 0
	virtual void func8(void); //0x534433 1
	virtual void func9(void); //0x534445 1
	virtual void func10(void); //0x534455
	virtual void func11(void); //0x534460
	virtual void func12(void); //0x534476
	virtual void func13(void); //0x53446B
	virtual int func14(void); //0x40678D break
	virtual int func15(char* a2); //0x406823 break
	virtual int getActive(void); //0x40BA20
	virtual GUI_TEXTBOX* setHandle(int a2); //0x40B860
	virtual int getHandle(void); //0x40B880
	virtual float getLeft(void); //0x40B8A0
	virtual float setGuiRef(int);  //0x40B8C0 
	virtual int func21(void); //0x406872 esse methodo qnd coloco o mouse em cima, ele arma
	virtual void func22(int gui, float viewx, float viewy, int dois, int zero); //0x406942 break
	virtual void setAlgo2(int a2); //0x40B900 break set pos 36 (0x24)
	virtual GUI_TEXTBOX* setVisible(int a2); //0x40B920 break
	virtual GUI_TEXTBOX* setAlgo3(int a2); //0x40B940 break //o loop passa frenetico aqui
	virtual GUI_TEXTBOX* setAlgo4(int a2); //0x406AB2 break
	virtual void func27(void); //0x401419 0
	virtual int setLeftTop(float a2, float a3); //0x401233
	virtual int setWidthHeight(int a2, int a3); //0x401267
	virtual void func30(void); //0x40B9D0 -1
	virtual void setAlgo7(int handle, float x, float y, float largura, float altura); //0x401188 action = evento handle, 
	virtual void setText(const char* txt, int zero); //0x40231F break
	virtual void setColor(unsigned int a2); //0x4020FF break
	virtual char* getText(void); //0x4062C6
	virtual GUI_TEXTBOX* func35(int a2); //0x40220B break
	virtual void setText2(const char* txt); //0x40621F break

public:
	GUI_TEXTBOX* addElement(GUI_TEXTBOX* element) {
		// overElement = 0x534584, aboveElement = 0x5345E1
		// 756 -> 005344A9  /$ 55             PUSH EBP
		// 762 -> 005351E9  /$ 55             PUSH EBP
		return callThiscall(0x5351E9, GUI_TEXTBOX*, GUI_TEXTBOX*, GUI_TEXTBOX*)(this, element);
	}
};

class GUI_LISTBOX
{
public:

	UINT32 MainGui;				 //0x0004
	UINT32 NextElement;			 //0x0008
	UINT32 LastElement;			 //0x000C
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
	float  Left;					 //0x004C
	float  Top;					 //0x0050
	float  Width;				 //0x0054
	float  Height;				 //0x0058
	UINT32 Reference;			 //0x005C
	UINT32 pad_0060;			 //0x0060
	UINT32 pad_0064;			 //0x0064
	float  ViewLeft;				 //0x0068
	float  ViewTop;				 //0x006C
	float  ViewWidth;		     //0x0070 
	float  ViewHeight;			 //0x0074 
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
	UINT32 pad_00A4;			 //0x00A4  	  
	UINT32 pad_00A8[76];		 //0x00A8
	UINT32 pad_00F4;			 //0x00F4
	UINT32 pad_00F8;			 //0x00F8
	UINT32 pad_00FC;			 //0x00FC
	UINT32 pad_0100;			 //0x0100
	UINT32 pad_0104;			 //0x0104
	UINT32 pad_0108;			 //0x0108
	UINT32 pad_010C;			 //0x010C
	UINT32 pad_0110;			 //0x0110
	UINT32 pad_0114;			 //0x0114
	UINT32 pad_0118;			 //0x0118
	UINT32 pad_011C;			 //0x011C
	UINT32 pad_0120;			 //0x0120
	UINT32 pad_0124;			 //0x0124 
	UINT32 pad_0128;			 //0x0128 
	UINT32 pad_012C;			 //0x012C 
	UINT32 pad_Sv0;			     //0x0130 texto 1
	UINT32 pad_Sv1;			     //0x0134 texto 2
	UINT32 pad_Sv2;			     //0x0138 texto 3
	UINT32 pad_013C;			 //0x013C



public:
	//0x5CDCF0


	virtual void func0(void); //0x40B4C0 
	virtual void func1(void); //0x40B820 0
	virtual void func2(int a2, int a3, int a4, signed int a5); //0x408B8C
	virtual void func3(void); //0x40B840 0
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
	virtual int setHandle(int handle); //0x40B860
	virtual int getHandle(void); //0x40B880
	virtual float getLeft(void); //0x40B8A0
	virtual float setGuiRef(int);  //0x40B8C0 
	virtual void func21(void); //0x40B8E0 0
	virtual void func22(int a2, float a3, float a4, int a5, int a6); //0x409134
	virtual int set24(int a2); //0x40B900
	virtual int set28(int a2); //0x40159D
	virtual int set2C(int a2); //0x40B940 
	virtual void set30(int a2); //0x40B960
	virtual void func27(void); //0x401419 0
	virtual int setLeftTop(float x, float y); //0x401233
	virtual int func29(int a2, int a3); //0x40904C
	virtual void func30(void); //0x40B9D0 -1
	virtual int func31(int a2, int a3, int a4, float a5, int a6); //0x401188
	virtual void setA0(int a2); //0x401584
	virtual void get64(void); //0x40B9E0

public:
	GUI_LISTBOX* addElement(GUI_LISTBOX* element) {
		// overElement = 0x534584, aboveElement = 0x5345E1

		// 756 -> 005344A9  /$ 55             PUSH EBP
		// 762 -> 005351E9  /$ 55             PUSH EBP
		return callThiscall(0x5351E9, GUI_LISTBOX*, GUI_LISTBOX*, GUI_LISTBOX*)(this, element);
	}

	/*Limpa os elementos da lista*/
	GUI_LISTBOX* ClearElements()
	{
		// 756 -> 00408A54  /$ 55             PUSH EBP
		// 762 -> 00409476  /. 55             PUSH EBP
		return callThiscall(0x0409476, GUI_LISTBOX*, GUI_LISTBOX*)(this);
	}

	/*Adicionar o Elemento na Lista*/
	bool InsertElement(int  element)
	{
		// 756 -> 00408569  /$ 55             PUSH EBP
		// 762 -> 00408E53  /$ 55             PUSH EBP
		callThiscall(0x408E53, GUI_LISTBOX*, GUI_LISTBOX*, int)(this, element);
		return true;
	}
};

class GUI_SLOT
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
	virtual GUI_TEXTBOX* setHandle(int a2); //0x40B860
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
	virtual GUI_SLOT* delItemGUI(int coluna, int linha); //0x40E8FF a2: XSlot 0 ~4 a3: YSlot: 0~2
	virtual void setAlgo11(int a2, int a3); //0x40EB2F //call qnd cliquei no item
	virtual void getAlgo2(int a2); //0x40D8F3
	virtual int setAlgo12(int a2, int a3); //0x40ECEE  arg1 0, arg2: gui
	virtual void setAlgo13(int a2, int a3); //0x40EE97
	virtual void getAlgo(void); //0x40D7F7
	virtual short func49(int a1, int a2); //0x424AB5
	virtual short func50(int a1); //0x424AF0



public:
	GUI_SLOT* addElement(GUI_SLOT* element) {
		// overElement = 0x534584, aboveElement = 0x5345E1
		// 756 -> 005344A9  /$ 55             PUSH EBP
		// 762 -> 005351E9  /$ 55             PUSH EBP
		return callThiscall(0x5351E9, GUI_SLOT*, GUI_SLOT*, GUI_SLOT*)(this, element);
	}

	BOOL delElement(int coluna, int linha) {
		// 756 -> 0040D2A5  /$ 55             PUSH EBP
		// 762 -> 0040DE78  /$ 55             PUSH EBP
		return callThiscall(0x40DE78, BOOL, GUI_SLOT*, int, int)(this, coluna, linha);
	}

};

class GUI_FORM //0x005cd49c
{
public:
	UINT32 LastElement;       //0x0004 (GUI Main)
	UINT32 NextElement;       //0x0008
	UINT32 OutherElement;     //0x000C
	UINT32 Element;           //0x0010
	UINT32 pad_0014;          //0x0014
	UINT32 pad_0018;          //0x0018
	UINT32 pad_001C;          //0x001C
	UINT32 pad_0020;          //0x0020
	UINT32 pad_0024;          //0x0024
	UINT32 IsVisible;         //0x0028
	UINT32 pad_002C;          //0x002c
	UINT32 pad_0030;          //0x0030
	UINT32 MouseOver;         //0x0034
	UINT32 pad_0038;          //0x0038
	UINT32 pad_003C;          //0x003C
	UINT32 pad_0040;          //0x0040
	UINT32 Handle;            //0x0044
	UINT32 pad_0048;          //0x0048
	float  Left;              //0x004C
	float  Top;               //0x0050
	float  Width;			  //0x0054
	float  Height;            //0x0058
	UINT32 pad_005C;          //0x005C
	UINT32 pad_0060;          //0x0060
	UINT32 pad_0064;          //0x0064
	float  pad_0068;          //0x0068
	float  pad_006C;          //0x006C
	float  ViewWidth;         //0x0070
	float  ViewHeight;        //0x0074
	UINT32 pad_0078;          //0x0078
	UINT32 pad_007C;          //0x007C
	UINT32  IsVisible2;         //0x0080
	UINT32 pad_0084;          //0x0084
	UINT32 pad_0088;          //0x0088
	UINT32 pad_008C;          //0x008C
	UINT32 pad_0090;          //0x0090
	UINT32 Opacidade;          //0x0094
	UINT32 pad_0098;          //0x0098
	UINT32 pad_009C;          //0x009C
	UINT32 SpriteIndex;       //0x00A0
	UINT32 MouseStats;		  //0x00A4
	UINT32 pad_00A8[73];      //0x00A8
	UINT32 PosX;
	UINT32 PosY;
	UINT32 Unk;
	UINT32 ScreenMove;

	/*UINT32 pad_0000;		//0x0000
	UINT32 pad_0004;		//0x0004
	UINT32 NextWindows;		//0x0008
	UINT32 LastWindow;		//0x000C
	UINT32 OutherElement;	//0x0010
	UINT32 pad_0010[4];		//0x0014
	UINT32 IsVisible;		//0x0028
	UINT32 pad_002C[3];		//0x002C
	UINT32 MouseOver;		//0x0034
	UINT32 pad_0038[2];		//0x0038
	UINT32 Handle;			//0x0044
	UINT32 pad_0048;		//0x0048
	float Left;				//0x004C
	float Top;				//0x0050
	float Width;			//0x0054
	float Height;			//0x0058
	UINT32 pad_005C[3];		//0x005C
	float ViewLeft;			//0x0068
	float ViewTop;			//0x006C
	float ViewWidth;		//0x0070
	float ViewHeight;		//0x0074
	UINT32 pad_0078[8];		//0x0078
	UINT32 Opacity;			//0x0094
	UINT32 pad_0098[2];		//0x0098
	UINT32 SpriteIndex;		//0x00A0
	UINT32 MouseStats;		//0x00A4
	UINT32 pad_00a4[73];	//0x00A8
	UINT32 PosX;
	UINT32 PosY;
	UINT32 Unk;
	UINT32 ScreenMove;*/
public:
	//VTABLE 0x005cd49c
	virtual void func0(void); //0x40B200
	virtual void func1(void); //0x40B820 0 
	virtual void func2(void); //0x4016E6 unk
	virtual void func3(void); //0x40B840 0
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
	virtual GUI_FORM* setHandle(int); //0x40B860 GUI_FORM* setHandle(int);
	virtual int getHandle(void); //0x40B880 int getHandle(void);
	virtual float getLeft(void); //0x40B8A0 float getLeft(void);
	virtual float getHeight(void); //0x40B8C0 float getTop(void);
	virtual void func21(void); //0x40B8E0 0
	virtual void func22(int a2, float a3, float a4, int a5, int a6); //0x4015F7 (parece uma func de redimensionar a janela) (GET no this + 0x1AC (Descobrir depois))
	virtual void set24(int a2); //0x40B900 
	virtual GUI_FORM* setVisible(BOOL visible); //0x40159D GUI_FORM* setVisible(BOOL visible);
	virtual void set2C(int a2); //0x40B940
	virtual void set28(int a2); //0x40B960
	virtual void func27(void); //0x401419 0
	virtual void setLeftTop(float x, float y); //0x401233 
	virtual void setWidthHeight(float a2, float a3); //0x401267
	virtual void func30(void); //0x40B9D0 -1
	virtual void func31(int a2, int a3, int a4, float a5, int a6); //0x401188 int 
	virtual void setSprite(int index); //0x401584 void setSprite(int index)
	virtual void get64(void); //0x40B9E0
public:

	GUI_FORM* addElement(GUI_FORM* element) {
		// overElement = 0x534584, aboveElement = 0x5345E1
		// 756 -> 005344A9  /$ 55             PUSH EBP
		// 762 -> 005351E9  /$ 55             PUSH EBP
		return callThiscall(0x5351E9, GUI_FORM*, GUI_FORM*, GUI_FORM*)(this, element);
	}
public:
	void Instanciar()
	{
		Game::getInstance()->pInterface->addWindow((Gui*)this);
	}

public:
	GUI_LABEL* addTitulo(const char* texto)
	{
		DWORD pAllocLabel = callCdecl(0x5C5DD3, DWORD, DWORD)(0xE4C);
		GUI_LABEL* GuiLabel = callThiscall(0x401CCD, GUI_LABEL*, DWORD, int, const char*, int, float, float, float, float, int, int, int, int)
			(pAllocLabel, -2, texto, 0xFFFFFFFF, 0.0f, 0.0f, this->ViewWidth, 26.0f, 1, 0, 1, 1);
		this->addElement((GUI_FORM*)GuiLabel);
		return GuiLabel;
	}
public:
	GUI_BUTTON* addButton(int index, float x, float y, float largura, float altura, const char* texto, int handle, int indexGUI)
	{
		// 756 -> 005B8113  /$ 6A 01          PUSH 1
		// 762 -> 005C5DD3  /$ 6A 01          PUSH 1
		DWORD pAllocButton = callCdecl(0x5C5DD3, DWORD, DWORD)(0x208);
		GUI_BUTTON* GuiButton = callThiscall(0x40332E, GUI_BUTTON*, DWORD, int, float, float, float, float, int, int, const char*)
			(pAllocButton, index, x, y, largura, altura, 0, 1, texto);

		GuiButton->setHandle(handle);
		this->addElement((GUI_FORM*)GuiButton);

		if (indexGUI > 0)
		{
			DWORD pAllocLabel = callCdecl(0x5C5DD3, DWORD, DWORD)(0xE4C);
			GUI_LABEL* GuiLabel = callThiscall(0x401CCD, GUI_LABEL*, DWORD, int, const char*, int, float, float, float, float, int, int, int, int)
				(pAllocLabel, indexGUI, "", 0xFFFFFFFF, x, y, largura, altura, 1, 0, 1, 0);
			this->addElement((GUI_FORM*)GuiLabel);
		}

		return GuiButton;
	}

	GUI_LABEL* addLabel(int index, float x, float y, float largura, float altura, const char* texto, int alinhamento, int cor, int handle)
	{

		DWORD pAllocLabel = callCdecl(0x5C5DD3, DWORD, DWORD)(0xE4C);
		GUI_LABEL* GuiLabel = callThiscall(0x401CCD, GUI_LABEL*, DWORD, int, const char*, int, float, float, float, float, int, int, int, int)
			(pAllocLabel, index, texto, cor, x, y, largura, altura, 1, 0, 1, alinhamento);
		GuiLabel->setHandle(handle);
		this->addElement((GUI_FORM*)GuiLabel);
		return GuiLabel;
	}

	GUI_TEXTBOX* addTextBox(int index, float x, float y, float largura, float altura, const char* texto, int lenght, int alinhamento, int password, int cor, int handle, int refHandle)
	{
		DWORD pAllocTextBox = callCdecl(0x5C5DD3, DWORD, DWORD)(0x1064);
		GUI_TEXTBOX* GuiTextBox = callThiscall(0x406082, GUI_TEXTBOX*, DWORD, int, const char*, int, int, int, float, float, float, float, char, int, int, int)(
			pAllocTextBox, index, texto, lenght, password, -1, x, y, largura, altura, 0, 0, 1, alinhamento);

		GuiTextBox->setHandle(handle);

		GUI_TEXTBOX* ReferenceTextBox = (GUI_TEXTBOX*)Game::getInstance()->pInterface->getGui(refHandle); //Pega a Referencia
		if (ReferenceTextBox != NULL)
			GuiTextBox->setGuiRef(ReferenceTextBox->Reference);

		this->addElement((GUI_FORM*)GuiTextBox);


		if (index > 0)
		{
			DWORD pAllocLabel = callCdecl(0x5C5DD3, DWORD, DWORD)(0xE4C);
			GUI_LABEL* GuiLabel = callThiscall(0x401CCD, GUI_LABEL*, DWORD, int, const char*, int, float, float, float, float, int, int, int, int)
				(pAllocLabel, index, "", 0xFFFFFFFF, x, y, largura, altura, 1, 0, 1, 0);
			this->addElement((GUI_FORM*)GuiLabel);
		}

		return GuiTextBox;
	}


};