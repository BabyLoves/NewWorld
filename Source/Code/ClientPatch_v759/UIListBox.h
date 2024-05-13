#pragma once
#include "Functions.h"
#include "UIControl.h"

class UIListBox : UIControl
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
	////----- (005351E9) --------------------------------------------------------
	UIListBox* addElement(UIListBox* element) {
		return callThiscall(0x5351E9, UIListBox*, UIListBox*, UIListBox*)(this, element);
	}

	////----- (0040933E) --------------------------------------------------------
	UIListBox* ClearElements()
	{
		return callThiscall(0x40933E, UIListBox*, UIListBox*)(this);
	}

	////----- (00408E53) --------------------------------------------------------
	bool InsertElement(int  element)
	{
		callThiscall(0x408E53, UIListBox*, UIListBox*, int)(this, element);
		return true;
	}


	//----- (004088D0) --------------------------------------------------------
	static UIListBox* SListBox(int a2, int a3, int a4, float a5, float a6, float a7, float a8, int a9, int a10, int a11, char a12, char a13)
	{
		DWORD pAllocWindow = callCdecl(0x5C5DD3, DWORD, DWORD)(0x11BC);
		return callThiscall(0x4088D0, UIListBox*, DWORD, int, int, int, float, float, float, float, int, int, int, char, char)(
			pAllocWindow, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13);
	}

	//----- (0049D105) --------------------------------------------------------
	UIListBox* sub_49D105(const char* a2) {
		return callThiscall(0x49D105, UIListBox*, UIListBox*, const char*)(
			this, a2);
	}

	//----- (0042B772) --------------------------------------------------------
	void sub_5C6515(const char* a1, int a2) {
		return callCdecl(0x5C6515, void, UIListBox*, const char*, int)(this, a1, a2);
	}

};