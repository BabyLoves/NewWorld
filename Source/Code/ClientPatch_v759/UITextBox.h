#pragma once
#include "Functions.h"
#include "UIControl.h"
#include <stdio.h>

class UITextBox : UIControl
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
    virtual UITextBox* setHandle(int a2); //0x40B860
    virtual int getHandle(void); //0x40B880
    virtual float getLeft(void); //0x40B8A0
    virtual float setGuiRef(int);  //0x40B8C0 
    virtual int func21(void); //0x406872 esse methodo qnd coloco o mouse em cima, ele arma
    virtual void func22(int gui, float viewx, float viewy, int dois, int zero); //0x406942 break
    virtual void setAlgo2(int a2); //0x40B900 break set pos 36 (0x24)
    virtual UITextBox* setVisible(int a2); //0x40B920 break
    virtual UITextBox* setAlgo3(int a2); //0x40B940 break //o loop passa frenetico aqui
    virtual UITextBox* setAlgo4(int a2); //0x406AB2 break
    virtual void func27(void); //0x401419 0
    virtual int setLeftTop(float a2, float a3); //0x401233
    virtual int setWidthHeight(int a2, int a3); //0x401267
    virtual void func30(void); //0x40B9D0 -1
    virtual void setAlgo7(int handle, float x, float y, float largura, float altura); //0x401188 action = evento handle, 
    virtual void setText(const char* txt, int zero); //0x40231F break
    virtual void setColor(unsigned int a2); //0x4020FF break
    virtual char* getText(void); //0x4062C6
    virtual UITextBox* func35(int a2); //0x40220B break
    virtual void setText2(const char* txt); //0x40621F break

public:
    UITextBox* addElement(UITextBox* element) {
        // overElement = 0x534584, aboveElement = 0x5345E1
        return callThiscall(0x5351E9, UITextBox*, UITextBox*, UITextBox*)(this, element);
    }

    //----- (004029B8) --------------------------------------------------------
    char* UITextBox::gText() {
        return  callThiscall(0x40632C, char*, UIControl*)(this);
    }


    //int __thiscall sub_40232B(void* this, int a2, int a3)
    //{
    //    int result; // eax@5
    //    int v4; // eax@19
    //    int v5; // eax@22
    //    int v6; // eax@27
    //    int v7; // eax@28
    //    char v8; // [sp+0h] [bp-190h]@0
    //    int v9; // [sp+4h] [bp-18Ch]@1
    //    int v10; // [sp+8h] [bp-188h]@43
    //    int k; // [sp+14h] [bp-17Ch]@43
    //    char v12; // [sp+1Ch] [bp-174h]@34
    //    char v13; // [sp+1Dh] [bp-173h]@34
    //    __int16 v14; // [sp+99h] [bp-F7h]@34
    //    char v15; // [sp+9Bh] [bp-F5h]@34
    //    char v16; // [sp+9Ch] [bp-F4h]@34
    //    char v17; // [sp+9Dh] [bp-F3h]@34
    //    __int16 v18; // [sp+119h] [bp-77h]@34
    //    char v19; // [sp+11Bh] [bp-75h]@34
    //    char v20; // [sp+11Ch] [bp-74h]@18
    //    char v21[99]; // [sp+11Dh] [bp-73h]@18
    //    __int16 v22; // [sp+17Dh] [bp-13h]@18
    //    char v23; // [sp+17Fh] [bp-11h]@18
    //    int v24; // [sp+180h] [bp-10h]@38
    //    int j; // [sp+184h] [bp-Ch]@4
    //    int i; // [sp+188h] [bp-8h]@4
    //    int v27; // [sp+18Ch] [bp-4h]@4
    //    v9 = (int)this;
    //    if (a2)
    //    {
    //        sub_53AF03((char*)a2);
    //        if (!sub_5C5AA0((_BYTE*)a2, &unk_60F29C))
    //            a2 = 0;
    //    }
    //    i = 0;
    //    j = 0;
    //    v27 = 0;
    //    if (a2)
    //    {
    //        result = sub_5C5AA0((_BYTE*)(v9 + 1900), (_BYTE*)a2);
    //        if (!result && !*(_BYTE*)(v9 + 3293))
    //            return result;
    //        if (sub_5C5A20((char*)a2) && (*(_BYTE*)(v9 + 3293) == 2 || *(_BYTE*)(v9 + 3293) == 1))
    //        {
    //            for (i = 0; i < sub_5C5A20((char*)a2); ++i)
    //            {
    //                if (!sub_5C5D28(*(_BYTE*)(i + a2)) && *(_BYTE*)(i + a2) != 32)
    //                    ++v27;
    //            }
    //            if (!v27 && sub_5C5C63((_BYTE*)a2))
    //            {
    //                v20 = 0;
    //                memset(v21, 0, 0x60u);
    //                v22 = 0;
    //                v23 = 0;
    //                for (i = 0; ; ++i)
    //                {
    //                    v4 = sub_5C5A20((char*)a2);
    //                    if (i >= v4)
    //                        break;
    //                    if (*(_BYTE*)(i + a2) == 32)
    //                    {
    //                        ++v27;
    //                        for (j = i; ; ++j)
    //                        {
    //                            v5 = sub_5C5A20((char*)a2);
    //                            if (j >= v5)
    //                                break;
    //                            *(_BYTE*)(j + a2) = *(_BYTE*)(j + a2 + 1);
    //                        }
    //                        i = -1;
    //                    }
    //                }
    //                i = 0;
    //                j = 0;
    //                while (1)
    //                {
    //                    v6 = sub_5C5A20((char*)a2);
    //                    if (i >= v6)
    //                        break;
    //                    v7 = sub_5C5A20((char*)a2);
    //                    if ((v7 - i) % 3u || !i)
    //                    {
    //                        *(&v20 + j++) = *(_BYTE*)(i + a2);
    //                    }
    //                    else
    //                    {
    //                        *(&v20 + j) = 44;
    //                        v21[j] = *(_BYTE*)(i + a2);
    //                        j += 2;
    //                    }
    //                    ++i;
    //                }
    //                sub_5C5930(a2);
    //                if (v27 > 0)
    //                {
    //                    v16 = 0;
    //                    memset(&v17, 0, 0x7Cu);
    //                    v18 = 0;
    //                    v19 = 0;
    //                    v12 = 0;
    //                    memset(&v13, 0, 0x7Cu);
    //                    v14 = 0;
    //                    v15 = 0;
    //                    sub_5C5930((int)&v16);
    //                    sub_5C5930((int)&v12);
    //                    sub_5C5B80((unsigned __int8*)&v12, 0, 0x80u);
    //                    for (i = 0; i < v27; ++i)
    //                        *(&v12 + i) = 32;
    //                    sub_5C5940(&v12, &v16);
    //                    sub_5C5930(a2);
    //                }
    //            }
    //        }
    //        v24 = sub_5C5A20((char*)a2);
    //        if (v24 > 255)
    //            *(_BYTE*)(a2 + 255) = 0;
    //        sub_5C5930(v9 + 1900);
    //        sub_42231F(v9 + 100, (char*)(v9 + 1900), *(_DWORD*)(v9 + 1876), a3);
    //    }
    //    else
    //    {
    //        sub_5C5B24((_BYTE*)(v9 + 1900), (unsigned __int8*)&unk_636624, v8);
    //        sub_42231F(v9 + 100, (char*)(v9 + 1900), *(_DWORD*)(v9 + 1876), a3);
    //    }
    //    result = *(_BYTE*)(v9 + 3293);
    //    if (result == 2)
    //    {
    //        v10 = sub_5C5A20((char*)a2);
    //        for (k = 0; k < v10 && *(_BYTE*)(k + a2) == 32; ++k)
    //            ;
    //        sub_5C5B80((unsigned __int8*)(v9 + 1900), 0, 0x100u);
    //        sub_5C5B80((unsigned __int8*)(v9 + 2264), 0, 0x100u);
    //        sub_5C5B80((unsigned __int8*)(v9 + 2628), 0, 0x100u);
    //        sub_5C5B80((unsigned __int8*)(v9 + 2992), 0, 0x100u);
    //        i = 0;
    //        v27 = 0;
    //        while (i < v10)
    //        {
    //            if (*(_BYTE*)(i + a2) == 44)
    //                ++v27;
    //            if (i >= 255)
    //                break;
    //            if (v27)
    //                *(_BYTE*)(i + v9 + 1900) = 32;
    //            else
    //                *(_BYTE*)(i + v9 + 1900) = *(_BYTE*)(i + a2);
    //            if (v27 == 1)
    //                *(_BYTE*)(i + v9 + 2264) = *(_BYTE*)(i + a2);
    //            else
    //                *(_BYTE*)(i + v9 + 2264) = 32;
    //            if (v27 == 2)
    //                *(_BYTE*)(i + v9 + 2628) = *(_BYTE*)(i + a2);
    //            else
    //                *(_BYTE*)(i + v9 + 2628) = 32;
    //            if (v27 <= 2)
    //                *(_BYTE*)(i + v9 + 2992) = 32;
    //            else
    //                *(_BYTE*)(i + v9 + 2992) = *(_BYTE*)(i + a2);
    //            ++i;
    //        }
    //        sub_42231F(v9 + 100, (char*)(v9 + 1900), -2228259, a3);
    //        sub_42231F(v9 + 532, (char*)(v9 + 2264), -7798904, a3);
    //        sub_42231F(v9 + 964, (char*)(v9 + 2628), -154, a3);
    //        result = sub_42231F(v9 + 1396, (char*)(v9 + 2992), -1, a3);
    //    }
    //    return result;
    //}
    //// 40232B: using guessed type char var_73[99];

     //----- (0040232B) --------------------------------------------------------
    void UITextBox::setText(const char* text) {
        return callThiscall(0x40232B, void, UIControl*, const char*, int)(this, text, 0);
    }


    //----- (00406285) --------------------------------------------------------
    //int __thiscall sub_406285(int this, LPCSTR lpString)
    //{
    //    int result; // eax@2
    //    int v3; // [sp+0h] [bp-Ch]@4
    //    int v4; // [sp+4h] [bp-8h]@1
    //    v4 = this;
    //    if (*lpString)
    //    {
    //        if (lstrlenA(lpString) <= *(_DWORD*)(this + 4176))
    //            v3 = lstrlenA(lpString);
    //        else
    //            v3 = *(_DWORD*)(v4 + 4176);
    //        sub_5C5DF0((_BYTE*)(v4 + 3660), (char*)lpString, v3);
    //        *(_BYTE*)(v3 + v4 + 3660) = 0;
    //        result = (*(int(__thiscall**)(int))(*(_DWORD*)v4 + 84))(v4);
    //    }
    //    else
    //    {
    //        sub_5C5B80((unsigned __int8*)(this + 3660), 0, 0xFFu);
    //        result = (*(int(__thiscall**)(int))(*(_DWORD*)v4 + 84))(v4);
    //    }
    //    return result;
    //}

    //----- (0040232B) --------------------------------------------------------
    void UITextBox::setConstString(const char* a2, ...)
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
};
