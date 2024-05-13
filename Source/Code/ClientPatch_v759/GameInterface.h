#pragma once

enum eSceneType : int
{
	SceneBeforeLogin = 30005,
	SceneLogin = 30004,
	SceneSelChar = 30001,
	SceneWorld = 30000,

}; 
#define BUFFGRUPOS 569004
#define BUFFTEMPO 568620
#define BUFFICONES 568876
#define LOGINPOPUP 65537
#define LEGENDABUFF 568496
#define BOLSAANDARILHO 565992

#define OCULTARCHAT 10 
#define MOSTRARCHAT 11
#define ENTERWORLD 1 
#define ATIVARPINCODE 2 
#define ABRIRPAINELPINCODE 3 
#define FECHARPAINELPINCODE 4 
#define ABREDONATESTORE 5
#define ABRECONFIGGRUPO 6   
#define FECHARCONFIGGRUPO 7  
#define RECOMPENSANOVATO 8  
#define TECLAESC 9
#define OPENSTORE 12  
#define OPT1 13  
#define OPT2 14  
#define OPT3 15  
#define OPT4 16 
#define OPT5 17
#define OPT6 18
#define OPT7 19  
#define OPT8 20  
#define OPT9 21  
#define OPT10 22  
#define SKILLMASTER 23
#define FILTRO 24
#define TELE 25
#define BTNRESETSKILL 43
#define PPT1 50
#define PPT2 51
#define PPT3 52

class GameInterface
{
public:
	// Singleton
	static GameInterface* Instance()
	{
		PDWORD pointer = (PDWORD)0x6F0AB0;
		return reinterpret_cast<GameInterface*>(pointer);
	}

	template <class T> T* getGuiFromHandle(int Handle)
	{
		static DWORD  rtnValue = 0;
		__asm
		//by seitbnao
		{
			PUSH Handle
			MOV EDX, DWORD PTR SS : [0x6F0AB0]
			MOV ECX, DWORD PTR DS : [EDX + 0x28]
			MOV EAX, DWORD PTR DS : [ECX]
			CALL DWORD PTR DS : [EAX + 0x48]

			MOV rtnValue, EAX
		}

		if (rtnValue == 0)
			return NULL;

		return reinterpret_cast<T*>(rtnValue);
	}
	//retorna um componente pela variavell global do jogo
	template <class T> T* getGuiFromVariableIndex(int dwIndex){
		return reinterpret_cast<T>(**(DWORD**)(this + dwIndex));
	}

	template <class T> T* getGuiFromValue(signed int value)
	{//att by seitbnao
		return reinterpret_cast<T*>(*(DWORD*)(reinterpret_cast<DWORD>(this) + value));
	}

	void setLabel(int handle, char *Text, ...)
	{
		if (auto label = this->getGuiFromHandle<UITextControl>(handle))
			label->setConstString(Text);
	}

	void setLabel(int handle, DWORD Color, char* Text, ...)
	{
		static char buffer[128] = { 0, };
		if (auto label = this->getGuiFromHandle<UITextControl>(handle))
		{
			va_list va;
			va_start(va, Text);
			int size = vsprintf_s(buffer, Text, va);

			if (size >= sizeof buffer || size == -1)
				return;

			va_end(Text);

			label->setText(Text);
			if (Color)
				label->setTextColor(Color);
		}
	}

	static int  SceneContext()
	{//by seitbnao
		static int rtnValue = 0;
		static int getSceneFieldAddr = 0x49A7FC;
		__asm
		{
			MOV EAX, 0x6F0AB0
			MOV EDX, DWORD PTR DS : [EAX]
			MOV ECX, EDX
			MOV EAX, getSceneFieldAddr
			CALL EAX
			MOV rtnValue, EAX
		}

		return rtnValue;
	}

	template<typename T>void Send(T* Packet)
	{
		return callCdecl(0x054DA23, void, char*, int)((char*)&Packet, Packet->Size);
	}
	template<typename T>void Send(T* Packet,int size)
	{
		return callCdecl(0x054DA23, void, char*, int)((char*)&Packet,size);
	}

	template<class T>T* getElementByIndex(int i, int dwIndex) {
		return reinterpret_cast<T*>(*(DWORD*)(reinterpret_cast<DWORD>(this) + 4 * i + dwIndex));
	}

	void ItemToolTipe(STRUCT_ITEM* Item); 
	static void ControlMouseController(UIControl* Control, int mouseStatus, int posX, int posY);
	static void MainLoop(UIControl* Controller);
	static void NKD_MainLoop(); 
};

static GameInterface* g_pInterface;

