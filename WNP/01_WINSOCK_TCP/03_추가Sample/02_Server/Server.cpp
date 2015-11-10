#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <windows.h>	
#include <winsock2.h>	
#pragma comment(lib, "ws2_32.lib")

#include <vector> // STL ��vector
using namespace std;

vector<SOCKET> client_list;


DWORD WINAPI foo( void* p)
{
	SOCKET s = (SOCKET)p;

	char buf[1024] = {0};
	int  nRead = 0;

	while ( 1 )
	{
		memset( buf, 0,1024);

		int nRead = recv( s, buf, 1024, 0);
		if ( nRead <= 0) break;
		// ���� data�� list �� �ִ� ��� client���� ������.
		for ( int i = 0; i < client_list.size(); ++i )
		{
			if( client_list[i] != s)
				send( client_list[i], buf, nRead, 0);
		}	
	}


















	// ������ ���� �� ��� list ���� �����Ѵ�.
	for( int i = 0; i < client_list.size(); ++i )
	{
		if ( client_list[i] == s ) 
		{
			vector<SOCKET>::iterator p = client_list.begin();
			p = p + i;
			client_list.erase( p );
			break;
		}
	}



	closesocket(s );
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
	// 1. socket ���� : TCP : SOCK_STREAM     UDP : SOCK_DGRAM
	SOCKET s = socket( AF_INET, SOCK_STREAM, 0);

	// 2. ������ ���Ͽ� �ּҸ� ����
	SOCKADDR_IN addr = { 0 };
	addr.sin_family = AF_INET;		 // �ּ� ����(AF_INET : IP �ּҶ�� �ǹ�)
	addr.sin_port   = htons( 5252 ); // Port #
	addr.sin_addr.s_addr = INADDR_ANY;	// �ڽ��� ��� IP ��� 

	if ( bind( s, (SOCKADDR*)&addr, sizeof(addr)) == -1 )
	{
		printf("Can't bind \n"); return;
	}




	// 3. ������ ��� ���·� ��ȯ�Ѵ�.
	if ( listen( s, 5) == -1 )
	{
		printf("Can't Listen\n"); return;
	}






	printf("Ŭ���̾�Ʈ�� ����մϴ�. \n");

	// 4. ���� Client ���� ���� ���޵� ��û�� ����Ѵ�.
	while ( 1 )
	{
		SOCKADDR_IN c_addr;
		int  size = sizeof(c_addr);
		
		SOCKET c_s = accept( s, (SOCKADDR*)&c_addr, &size );



















		printf("Ŭ���̾�Ʈ �� �����߽��ϴ�. IP : %s\n", 
												inet_ntoa( c_addr.sin_addr));

		// linked list �� socket�� �ִ´�.
		client_list.push_back( c_s );




















		// ���ο� �����带 �����ؼ� Ŭ���� ��Ʈ�� ��û�� ó���Ѵ�.
		HANDLE hThread = CreateThread( 0, 0, foo, (void*)c_s, 0, 0);
		CloseHandle( hThread );
	}


















	//--------------------------------------------
	closesocket( s ); // ���� �ݱ�.
	WSACleanup();
}









