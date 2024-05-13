

//é sempre assim q começa
class UIProgressControl : UIControl
{
public:


	static UIProgressControl* CreateProgress(int a2, int a3, int a4, float a5, float a6, float a7, float a8, int a9, int a10, int a11)//ainda n sabemos de nada
	{
		//sabemos q tem o alocate
		//v91 = (float *)sub_5C5DD3(0x374u);// aqui é o alocate vou te mostar
		DWORD pAllocWindow = callCdecl(0x5C5DD3, DWORD, DWORD)(0x374u);//alocate //ta vendo o addr ai vc troca
		//sub_404D20(v91, v217, v222, v195, v48, v47, v46, v45, v196, v198, v223);
		//vamo achar essa fun la
		//aqui apenas trocamos os addr e e os parametros

		//aki ela
//----- (00404D20) --------------------------------------------------------
		//int __thiscall sub_404D20(float* this,, this = ela msm entao n usamos isso, int a2, int a3, int a4, float a5, float a6, float a7, float a8, int a9, int a10, int a11)
		return callThiscall(0x404D20, UIProgressControl*, DWORD, int, int, int, float, float, float, float, int, int, int)(
			pAllocWindow, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11);

	}//agora vamos usar o id la do hp pra gente ver oq o client faz com ele


	//----- (00405015) --------------------------------------------------------
	//esse __thiscall vai mostrar qual macro vamos usar
	//ai vc apaga sempre o thisscall e o primeiro arg *this
	int  setValorAtual(int a2)//agora vamo descobri o q isso faz pera ja venho //sabemos q isso é o valor atual
	{//o retorno é int testar
		return callThiscall(0x405015, int, UIProgressControl*, int)(this, a2);
	}
	//continuando as funcs debaixo
	//sub_405090


	int getValorAtual()// olha la é int msm ? certo mas ainda falta 
	{

		return callThiscall(0x405090, int, UIProgressControl*)(this);// ta errado mt  sim kk
	}
	int setValorTotal(int a2)// aqui posso colocar um nome depois de saber oq faz? pode e é bom ate renomear no .c lá tb pra facilitar
	{
		return callThiscall(0x40505C, int, UIProgressControl*, int)(this, a2);
	}
	int sub_4050B8()//não sei ainda
	{
		return callThiscall(0x4050B8, int, UIProgressControl*)(this);
	}
	int sub_405C70(int a2)//não sei ainda
	{
		return callThiscall(0x405C70, int, UIProgressControl*, int)(this, a2);
	}
};

