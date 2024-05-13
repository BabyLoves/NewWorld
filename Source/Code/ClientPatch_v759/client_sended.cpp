#include "main.h" 
#include "VirtualizerSDK.h"


void ClientSended(MSG_STANDARD* pBuffer, int a_iSize)
{  
	VIRTUALIZER_TIGER_WHITE_START
	if (pBuffer->Type == 0x20D)
	{
		UUID uuid;
		UuidCreateSequential(&uuid);
		int sContexto = g_pInterface->SceneContext();
		auto old = reinterpret_cast<MSG_AccountLogin*>(pBuffer);

		old->Version = APP_VERSION;

		memset(&old->MacAddres[0], 0, 52);

		sprintf_s(old->MacAddres, 18, "%02X:%02X:%02X:%02X:%02X:%02X", uuid.Data4[2], uuid.Data4[3], uuid.Data4[4], uuid.Data4[5], uuid.Data4[6], uuid.Data4[7]);

		int len = strlen(old->MacAddres); 

		if (len < 12)
			ExitProcess(1);  
		 //18/11
		old->Encode(); 
	}		
	VIRTUALIZER_TIGER_WHITE_END
}