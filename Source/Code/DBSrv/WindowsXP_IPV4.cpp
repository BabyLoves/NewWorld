#include <ws2tcpip.h>
#include <stdio.h>   

#include "CFileDB.h"

const char* inet_ntop2(int af, const void* src, char* dst, int cnt){

	struct sockaddr_in srcaddr;

	memset(&srcaddr, 0, sizeof(struct sockaddr_in));
	memcpy(&(srcaddr.sin_addr), src, sizeof(srcaddr.sin_addr));

	srcaddr.sin_family = af;
	if (WSAAddressToString((struct sockaddr*) &srcaddr, sizeof(struct sockaddr_in), 0, dst, (LPDWORD) &cnt) != 0) {
		DWORD rv = WSAGetLastError();
		printf("WSAAddressToString() : %d\n",rv);
		return NULL;
	}
	return dst;
}