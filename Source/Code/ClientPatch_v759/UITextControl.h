#pragma once


class UITextControl : UIControl
{
public:
	static UITextControl* CreateLabel(int SpriteIndex, const char* Text, int v288, float x, float y, float width, float height, int v292, int v284, int v310, int v311)
	{
		DWORD pAllocWindow = callCdecl(0x5C5DD3, DWORD, DWORD)(0xE4C);//alocate
		return callThiscall(0x401CD9, UITextControl*, DWORD, int, const char*, int, float, float, float, float, int, int, int, int)(
			pAllocWindow, SpriteIndex, Text, v288, x, y, width, height, v292, v284, v310, v311);
	}
	
	//----- (0040210B) --------------------------------------------------------
	int  UITextControl::setTextColor(DWORD Color)
	{
		return callThiscall(0x0040210B, int, UIControl*, DWORD)(this, Color);
	}

	void UITextControl::setText(const char* text) {
		return callThiscall(0x0040232B, void, UIControl*, const char*, int)(this, text, 0);
	}
	//----- (0040232B) --------------------------------------------------------
	void UITextControl::setConstString(const char* a2, ...)
	{
		static char buffer[128] = { 0, };
		va_list va;
		va_start(va, a2);
		int size = vsprintf_s(buffer, a2, va);

		if (size >= sizeof buffer || size == -1)
			return;

		va_end(va);
		return this->setText(buffer);
	}

	void UITextControl::setConstString(TNColor color,const char* a2, ...){
		this->setConstString(a2);
		this->setTextColor(color);
	}

	//----- (004029B8) --------------------------------------------------------
	char* UITextControl::getText()
	{
		return  callThiscall(0x004029B8, char*, UIControl*)(this);
	}

	//----- (0040210B) --------------------------------------------------------
	int  UITextControl::setTextColor(TNColor color)
	{
		return callThiscall(0x0040210B, int, UIControl*, DWORD)(this, color);
	}
};

