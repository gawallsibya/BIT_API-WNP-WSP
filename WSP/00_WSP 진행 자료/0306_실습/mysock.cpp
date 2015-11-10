//mysock.cpp

#include <winsock2.h>	
#pragma comment(lib, "ws2_32.lib")
#include <process.h>
//#include <stdlib.h>	
#include <stdio.h>
#include "mysock.h"

int		g_port;			// ������ ���۽� ���
SOCKET	g_sendsock;
int		g_size;

RECVFUN g_recvfun;

int mysock_init()
{
	WSADATA wsa;
	if(WSAStartup(MAKEWORD(2,2), &wsa) != 0)		
		return -1;
	return 0;
}

void mysock_exit()
{
	WSACleanup();
}

void mysock_inirproc(RECVFUN OnRecv)
{
	g_recvfun = OnRecv;
}


void mysock_recvsock(int size, int port)
{
	int retval;

	SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);
	if(sock == INVALID_SOCKET) err_quit("socket()");

	SOCKADDR_IN			localaddr;
	ZeroMemory(&localaddr, sizeof(localaddr));
	localaddr.sin_family		= AF_INET;
	localaddr.sin_port			= htons(port);
	localaddr.sin_addr.s_addr   = htonl(INADDR_ANY);
	retval		= bind(sock, (SOCKADDR*)&localaddr, 
							sizeof(localaddr));
	g_size		= size;

	_beginthread(recvthread, 0, (void*)sock);
}


void recvthread(void* p)
{
	SOCKET sock = (SOCKET)p;
	int retval;

	// ������ ��ſ� ����� ����
	SOCKADDR_IN		peeraddr;
	int				addrlen;
	char*			buf = (char*)malloc(g_size);
	
	// ��Ƽĳ��Ʈ ������ �ޱ�
	while(1)
	{
		// ������ �ޱ�
		addrlen		= sizeof(peeraddr);
		retval		= recvfrom(sock, buf, g_size, 0, 
					(SOCKADDR*)&peeraddr, &addrlen);

		if(retval == SOCKET_ERROR)
		{
			err_display("recvfrom");
			continue;
		}
#ifndef MY_DEBUG
	printf("%dbyte recv\n",  retval);
#endif
		g_recvfun(buf, g_size);
	}

	closesocket(sock);
}

void mysock_sendsock(int size, int port)
{
	int retval;

	g_port		= port;
	g_sendsock	= socket(AF_INET, SOCK_DGRAM, 0);
	if(g_sendsock == INVALID_SOCKET) err_quit("socket()");	
	
	// ��ε�ĳ���� Ȱ��ȭ
	BOOL		bEnable		= TRUE;
	retval	= setsockopt(g_sendsock, SOL_SOCKET, SO_BROADCAST, 
				(char*)&bEnable, sizeof(bEnable));
	if( retval == SOCKET_ERROR)
		err_quit("setsockopt()");
}


void mysock_senddata(char* data, int length)
{
	// ���� �ּ� ����ü �ʱ�ȭ
	SOCKADDR_IN remoteaddr;
	int retval;

	ZeroMemory(&remoteaddr, sizeof(remoteaddr));
	remoteaddr.sin_family = AF_INET;
	remoteaddr.sin_port = htons(g_port);
	//-------------------------------------------------------
	remoteaddr.sin_addr.s_addr = htonl(INADDR_BROADCAST);
	//-------------------------------------------------------

	// ������ ������
	retval	= sendto(g_sendsock, data, length, 0, 
				(SOCKADDR*)&remoteaddr, sizeof(remoteaddr));
	if( retval == SOCKET_ERROR)
	{
		err_display("sendto");
	}
	
#ifndef MY_DEBUG
	printf("%dbyte send\n",  retval);
#endif
}


// ���� �Լ� ���� ��� �� ����
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
	MessageBox(NULL, (LPCTSTR)lpMsgBuf, msg, MB_ICONERROR);
	LocalFree(lpMsgBuf);
}


