#include "Functions.h"
#include "UIControl.h"

class UIITem : UIControl
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
	virtual UIITem* setHandle(int);  // Function 17 //0x0040b860
	virtual int getHandle(void);  // Function 18 //0x0040b880
	virtual float getLeft(void); // Function 19  //0x0040b8a0
	virtual float getTop(void);  // Function 20 //0x0040b8c0
	virtual void func21(void); // Breaked Func  //0x0040b8e0
	virtual void func22(void); // Breaked Func  //0x004015f7
	virtual void func23(void); // Breaked Func  //0x0040b900
	virtual UIITem* setVisible(BOOL visible); // Function 24 //0x0040159d
	virtual void func25(void); //0x0040b940
	virtual void func26(void); //0x0040b960
	virtual void func27(void); //0x00401419
	virtual void func28(void); //0x00401233
	virtual void func29(void); //0x00401267
	virtual void func30(void); //0x0040b9d0
	virtual void func31(void); //0x00401188
	virtual void setSprite(int index); //0x00401584 // Window = (int index), Label = (const char* text, int unknown)
public:
	UIITem* addElement(UIITem* element) {
		// 756 -> 005344A9  /$ 55             PUSH EBP
		// 762 -> 005351E9  /$ 55             PUSH EBP
		return callThiscall(0x5351E9, UIITem*, UIITem*, UIITem*)(this, element);
	}


	//----- (00401584) --------------------------------------------------------
	int Sprite(int a2) {
		return callThiscall(0x401584, int, UIITem*, int)(this, a2);
	}


	//----- (0040159D) --------------------------------------------------------
	UIITem* Visible(BOOL visible) {
		return callThiscall(0x40159D, UIITem*, UIITem*, BOOL)(this, visible);
	}


	//----- (0040D3DE) --------------------------------------------------------
	/*UIITem* New(STRUCT_ITEM pSlot, float x, float y)
	{
		DWORD pAllocItem = callCdecl(0x5C5DD3, DWORD, DWORD)(0x8u);

		auto STRC_ITEM = reinterpret_cast<STRUCT_ITEM*>(pAllocItem);
		memcpy(STRC_ITEM, &pSlot, sizeof(STRUCT_ITEM));


		DWORD pAlloc = callCdecl(0x5C5DD3, DWORD, DWORD)(0x678u);
		return callThiscall(0x40D3DE, UIITem*, DWORD, DWORD, DWORD, FLOAT, FLOAT)(pAlloc, 0, pAllocItem, x, y);
	}*/
};