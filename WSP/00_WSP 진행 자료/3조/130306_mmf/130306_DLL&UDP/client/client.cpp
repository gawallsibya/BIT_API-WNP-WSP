//client.cpp
#define DLL_SOURCE
#include <winsock2.h>	
#pragma comment(lib, "ws2_32.lib")
#include <process.h>
//#include <stdlib.h>	
#include <stdio.h>
#include "client.h"
SOCKET sock;
SOCKADDR_IN remoteaddr;

int client_init()
{
	int retval;

	// ���� �ʱ�ȭ
	WSADATA wsa;
	if(WSAStartup(MAKEWORD(2,2), &wsa) != 0)		
		return -1;

	// socket()
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if(sock == INVALID_SOCKET) err_quit("socket()");	

	
	// ��ε�ĳ���� Ȱ��ȭ
	BOOL		bEnable		= TRUE;
	retval	= setsockopt(sock, SOL_SOCKET, SO_BROADCAST, 
				(char*)&bEnable, sizeof(bEnable));
	if( retval == SOCKET_ERROR)
		err_quit("setsockopt()");
	


	// ���� �ּ� ����ü �ʱ�ȭ
	ZeroMemory(&remoteaddr, sizeof(remoteaddr));
	remoteaddr.sin_family = AF_INET;
	remoteaddr.sin_port = htons(5252);
	//-------------------------------------------------------
	remoteaddr.sin_addr.s_addr = htonl(INADDR_BROADCAST);
	//-------------------------------------------------------

	return 1;
}

int client_exit()
{
	// closesocket()
	closesocket(sock);

	// ���� ����
	WSACleanup();
	return 1;
}

void err_quit(char *msg)
{
	LPVOID lpMsgBuf;
	FormatMessage( 
		FORMAT_MESSAGE_ALLOCATE_BUFFER|
		FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	MessageBox(NULL, (LPCTSTR)lpMsgBuf, msg, MB_ICONERROR);
	LocalFree(lpMsgBuf);
	exit(-1);
}



// ���� �Լ� ���� ���
void err_display(char *msg)
{
	LPVOID lpMsgBuf;
	FormatMessage( 
		FORMAT_MESSAGE_ALLOCATE_BUFFER|
		FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	printf("[%s] %s", msg, (LPCTSTR)lpMsgBuf);
	LocalFree(lpMsgBuf);
}


int	client_sendpack(char* p)
{
	return sendto(sock, p, 94, 0, 
				(SOCKADDR*)&remoteaddr, sizeof(remoteaddr));
}