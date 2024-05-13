#pragma once
#include <stdio.h>
#include "UITextControl.h"
#include "UITextControl.h"
#include "UIControl.h"
#include "Functions.h"

class UIClick : UIControl
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

public:


    //----- (004B23B4) --------------------------------------------------------
    int Click(int a2, int a3) {
        printf("004B23B4 -> ");
        return callThiscall(0x4B23B4, int, UIControl*, int, int)(this, a2, a3);
    }


    //void __thiscall sub_40C714(int this, int a2)
    //{
    //    int v2; // [sp+0h] [bp-Ch]@1
    //    int v3; // [sp+4h] [bp-8h]@11
    //    int v4; // [sp+8h] [bp-4h]@8
    //    v2 = this;
    //    if (dword_277C068 != 1 || a2 && *(_DWORD*)(a2 + 64) == 13)
    //    {
    //        if (*(_DWORD*)(this + 300))
    //            (*(void(__thiscall**)(_DWORD, _DWORD))(**(_DWORD**)(this + 300) + 104))(*(_DWORD*)(this + 300), 0);
    //        *(_DWORD*)(v2 + 300) = a2;
    //        if (*(_DWORD*)(v2 + 300))
    //            (*(void(__thiscall**)(_DWORD, signed int))(**(_DWORD**)(v2 + 300) + 104))(*(_DWORD*)(v2 + 300), 1);
    //        v4 = dword_6F0AB0;
    //        if (dword_6F0AB0)
    //        {
    //            if (*(_DWORD*)(v2 + 300) && *(_DWORD*)(*(_DWORD*)(v2 + 300) + 64) == 13)
    //            {
    //                (*(void(__thiscall**)(_DWORD, signed int))(**(_DWORD**)(dword_6F0AB0 + 96) + 96))(
    //                    *(_DWORD*)(dword_6F0AB0 + 96),
    //                    1);
    //                sub_4B58C4();
    //                v3 = (*(int(__thiscall**)(_DWORD, signed int))(**(_DWORD**)(dword_6F0AB0 + 40) + 72))(
    //                    *(_DWORD*)(dword_6F0AB0 + 40),
    //                    65670);
    //                if (v3 && *(_DWORD*)(v3 + 40) && *(_DWORD*)(v4 + 36) == 30000)
    //                    (*(void(__thiscall**)(_DWORD, signed int))(**(_DWORD**)(v4 + 162892) + 96))(*(_DWORD*)(v4 + 162892), 1);
    //            }
    //            else
    //            {
    //                (*(void(__thiscall**)(_DWORD, _DWORD))(**(_DWORD**)(dword_6F0AB0 + 96) + 96))(
    //                    *(_DWORD*)(dword_6F0AB0 + 96),
    //                    0);
    //                if (*(_DWORD*)(v4 + 36) == 30000)
    //                {
    //                    (*(void(__thiscall**)(_DWORD, _DWORD))(**(_DWORD**)(v4 + 162892) + 96))(*(_DWORD*)(v4 + 162892), 0);
    //                    (*(void(__thiscall**)(_DWORD, _DWORD))(**(_DWORD**)(v4 + 162896) + 96))(*(_DWORD*)(v4 + 162896), 0);
    //                }
    //            }
    //            if (*(_DWORD*)(v2 + 300)
    //                && (*(int(__thiscall**)(_DWORD))(**(_DWORD**)(v2 + 300) + 64))(*(_DWORD*)(v2 + 300)))
    //            {
    //                if (dword_63DAE8)
    //                    sub_4B4ECA(dword_63DAE8);
    //            }
    //            else if (dword_63DAE8)
    //            {
    //                sub_4B4F2B(dword_63DAE8);
    //            }
    //        }
    //    }
    //}

     //----- (0040C714) --------------------------------------------------------
    void ClickButton(int a2) {
        printf("0040C714 -> ");
        return callThiscall(0x40C714, void, UIControl*, int)(this, a2);
    }
};

