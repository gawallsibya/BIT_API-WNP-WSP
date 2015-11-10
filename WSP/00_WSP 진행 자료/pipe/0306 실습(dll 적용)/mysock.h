// mysock.h

// �� ��� �Ѱ��� DLL�� ���鶧�� DLL�� ����Ҷ� ��� ����ϱ� ���� ���Ǻ�
// ������ ���

#ifdef DLL_SOURCE
	#define DLLFUNC	__declspec(dllexport)   
#else
	#define DLLFUNC __declspec(dllimport)
#endif

#define WIN32_LEAN_AND_MEAN
#include <stdlib.h>	
#include <stdio.h>
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")

typedef void (*RecvFun)(char*,int,SOCKET);

EXTERN_C DLLFUNC int mysock_initlibraty();
EXTERN_C DLLFUNC void mysock_init(RecvFun rfun);
EXTERN_C DLLFUNC void mysock_exitlibrary();

EXTERN_C DLLFUNC SOCKET mysock_sendsock(int port);
EXTERN_C DLLFUNC SOCKET mysock_recvsock(int port);
EXTERN_C DLLFUNC void mysock_closesock(SOCKET sock);

EXTERN_C DLLFUNC int mysock_send(SOCKET sock,char* temp,int size);
DWORD WINAPI recvthread(void* p);

void err_quit(char *msg);
void err_display(char *msg);

//--------------------------------------------------------