// chat Client
#include <iostream>
#include <winsock2.h>
#include <cstring>
#include <process.h>
using namespace std;


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
	printf("[%s] %s", msg, (LPCTSTR)lpMsgBuf);
	LocalFree(lpMsgBuf);
}


void recvthread(void* p);


void main()
{

	//=================================================================

	int			retval;
	WSADATA		wsa;
	WSAStartup(MAKEWORD(2,2), &wsa);

	SOCKET	client_sock = socket(AF_INET, SOCK_STREAM, 0);

	
	SOCKADDR_IN addr_server; 
	addr_server.sin_family		= AF_INET; 
	addr_server.sin_port		= htons(4000);
	addr_server.sin_addr.s_addr = inet_addr("61.81.99.31"); // ���� ip
	int namelen = sizeof(addr_server);

	cout << "conneting Server...." << endl;

	retval = connect(client_sock, (SOCKADDR*)&addr_server, namelen);
	if( retval == SOCKET_ERROR)
		err_quit("connect");

	cout << "connected server" << endl;

	//=================================================================

	// printf�� scanf�� ��Ƽ  thread�� ���� ������.
	// ���� �ɼǿ��� multithread�� �����������.
	// project setting ���� c/c++ ���� general 
	// code generation =>user run_time library����
	// debug Multithread ����
	_beginthread(recvthread, 0, (void*)client_sock);
	
	char buf[256];
	while(1)
	{
		cin >> buf;
		send(client_sock, buf, strlen(buf), 0);
	}
	WSACleanup();
}


// �������Լ� �������� ���� data�� �޴´�.
void recvthread(void* p)
{
	SOCKET client_sock = (SOCKET)p;

	char buf[256];
	while(1){
		int n = recv(client_sock, buf, 256, 0);
		if (n >0)
		{
			buf[n] = '\0';
			cout << buf << endl;
		}		
	}
}