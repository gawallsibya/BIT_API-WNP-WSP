
#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <windows.h>	
#include <winsock2.h>	
#pragma comment(lib, "ws2_32.lib")

DWORD WINAPI foo( void* p )
{
	SOCKET s = (SOCKET)p;

	// �������� ���� data�� �����Ѵ�.
	char buf[1024];
	int nRead;
	while ( 1  )
	{
		memset( buf, 0, 1024);
		nRead = recv( s, buf, 1024, 0);

		if ( nRead <= 0 ) break;
		printf("%s\n", buf );
	}
	printf("�������� ������ ���� �����ϴ�.\n");
	closesocket( s );
	return 0;
}











void main()
{
	WSADATA wsadata;

	if ( WSAStartup( MAKEWORD(2,2), &wsadata) != 0 )
	{
		printf("Can't Initialize Socket !\n");
		return ;
	}
	//--------------------------------------------
	// 1. ���ϻ���
	SOCKET s = socket( AF_INET, SOCK_STREAM, 0);

	// 2. �����ּ� ���� -> client �� ���� ���� 
	//    ���� �ϸ� OS�� ������ ��Ʈ�� ������ �ش�

	// 3. ������ ����
	SOCKADDR_IN addr = { 0 };

	addr.sin_family = AF_INET;
	addr.sin_port   = htons( 4000 );
	addr.sin_addr.s_addr = inet_addr("61.81.99.52"); 

	if ( connect( s, (SOCKADDR*)&addr, sizeof(addr)) == -1 )
	{
		printf("Can't Connect Server\n");
		return;
	}
	printf("Connected Server \n");

	// ���ο� �����带 ���� �������� ���� data�� �����Ѵ�
	HANDLE hThread = CreateThread( 0, 0, foo, (void*)s, 0, 0);	
	CloseHandle( hThread );

	//-----------------------------------------------
	// ������� �Է��� ������ �����Ѵ�.
	char name[256] = "[asd] :";
	char data[256] = { 0 };
	char buf[1024] = { 0 };

	while ( 1 )
	{
		memset( buf, 0, 1024);
		memset( data,0, 256 );
		gets( data );
		strcpy(buf, name );
		strcat(buf, data );

		// ������ �����Ѵ�
		send( s, buf, strlen(buf)+1, 0);	//[ȫ�浿]HI~
	}

	closesocket( s );




	//--------------------------------------------
	WSACleanup();
}














