#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <process.h>

#define PORT 25000
#define BUFSIZE 100

typedef struct
{
	int num1;
	int num2;
}DATA;

typedef struct
{
	SOCKET hClntSock; // ����
	SOCKADDR_IN clntAddr; // ������ �ּҰ�
}PER_HANDLE_DATA, *LPPER_HANDLE_DATA;

typedef struct
{
	OVERLAPPED overlapped;
	char buffer[BUFSIZE];
	WSABUF wsaBuf;
	DATA data;
}PER_IO_DATA, *LPPER_IO_DATA;

DWORD WINAPI CompletionThread(LPVOID CompletionPortIO);
void ErrorHandling(char *message);

int main()
{
	WSADATA wsaData;
	HANDLE hCompletionPort;
	SYSTEM_INFO SystemInfo;
	SOCKADDR_IN servAddr;
	LPPER_IO_DATA PerIoData;
	LPPER_HANDLE_DATA PerHandleData;

	SOCKET hServSock;
	int RecvBytes;
	int i, Flags;
	char str[100];

	if(WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error!");

	//1. �Ϸ� ��Ʈ ����
	hCompletionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
	
	GetSystemInfo(&SystemInfo);
	for(i=0; i<(int)SystemInfo.dwNumberOfProcessors; i++)
		_beginthreadex(NULL, 0, CompletionThread, (LPVOID)hCompletionPort, 0, NULL);

	hServSock = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);

	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(PORT);

	bind(hServSock, (SOCKADDR*)&servAddr, sizeof(servAddr));
	listen(hServSock, 5);

	while(TRUE)
	{
		SOCKET hClntSock;
		SOCKADDR_IN clntAddr;
		int addrLen = sizeof(clntAddr);

		//============= ���Ӵ�� ==============================================================
		hClntSock = accept(hServSock, (SOCKADDR*)&clntAddr, &addrLen);

		//1) ���ϰ� �ּҰ��� ���� ����ü ���� ����, �ʱ�ȭ
		PerHandleData = (LPPER_HANDLE_DATA)malloc(sizeof(PER_HANDLE_DATA));
		PerHandleData->hClntSock = hClntSock;
		memcpy(&(PerHandleData->hClntSock), &clntAddr, addrLen);
		printf("Socket number %d connected\n", PerHandleData->hClntSock);

		//2) ���ϰ� �Ϸ���Ʈ ����
		if(CreateIoCompletionPort((HANDLE)hClntSock, hCompletionPort, (DWORD)PerHandleData, 0) == NULL)
		{
			printf("CreateIoCompletionPort error");
			exit(1);
		}

		//3) �񵿱� I/O ����(WSARecv)
		PerIoData = (LPPER_IO_DATA)malloc(sizeof(PER_IO_DATA));
		memset(&(PerIoData->overlapped), 0, sizeof(OVERLAPPED));
		PerIoData->wsaBuf.len = BUFSIZE;
		PerIoData->wsaBuf.buf = PerIoData->buffer;
		Flags=0;

		WSARecv(PerHandleData->hClntSock, &(PerIoData->wsaBuf), 1, &RecvBytes, &Flags, &(PerIoData->overlapped), NULL);
		if(RecvBytes > 0)
		{
			memcpy(&PerIoData->data, (DATA*)PerIoData->buffer, sizeof(DATA));
			
			wsprintf(str, "�� ������ ������ %d�Դϴ�", PerIoData->data.num1 + PerIoData->data.num2);
			puts(str);
		}
	}

	return 0;
}

DWORD WINAPI CompletionThread(LPVOID pComPort)
{
	HANDLE hCompletionPort = (HANDLE)pComPort;
	DWORD BytesTransferred;
	LPPER_HANDLE_DATA PerHandleData;
	LPPER_IO_DATA PerIoData;
	DWORD flags;
	char str[100];

	while(1)
	{
		//1) ���(PerHandleData, PerIoData);
		GetQueuedCompletionStatus(hCompletionPort, &BytesTransferred, (LPDWORD)&PerHandleData,
					(LPOVERLAPPED*)&PerIoData, INFINITE);

		if(BytesTransferred == 0)
		{
			closesocket(PerHandleData->hClntSock);
			free(PerHandleData);
			free(PerIoData);
			continue;
		}
		else
		{
			//2) I/O ��� Ȯ��
			PerIoData->wsaBuf.len = BytesTransferred;
			wsprintf(str, "�� ������ ������ %d�Դϴ�", PerIoData->data.num1 + PerIoData->data.num2);
			strcpy(PerIoData->wsaBuf.buf, str);
			WSASend(PerHandleData->hClntSock, &(PerIoData->wsaBuf), 1, NULL, 0, NULL, NULL);
		}

		//3) �񵿱� �Լ� ȣ��(WSARecv)
		memset(&(PerIoData->overlapped), 0, sizeof(OVERLAPPED));
		PerIoData->wsaBuf.len = BUFSIZE;
		PerIoData->wsaBuf.buf = PerIoData->buffer;

		flags = 0;
		if(WSARecv(PerHandleData->hClntSock, &(PerIoData->wsaBuf), 1, NULL, &flags,
					&(PerIoData->overlapped), NULL) == SOCKET_ERROR)
		{
			if(WSAGetLastError( ) != ERROR_IO_PENDING)
			{
				printf("WSARecv( ) error");
				exit(1);
			}
			if(PerIoData->wsaBuf.len != 0)
			{
				memcpy(&PerIoData->data, (DATA*)PerIoData->buffer, sizeof(DATA));
			
				wsprintf(str, "�� ������ ������ %d�Դϴ�", PerIoData->data.num1 + PerIoData->data.num2);
				puts(str);
			}
		}
	}

	return 0;
}

void ErrorHandling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}



