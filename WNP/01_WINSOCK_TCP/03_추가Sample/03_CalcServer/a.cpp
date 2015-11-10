#include "CalcPacket.h"

#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <windows.h>	
#include <winsock2.h>	
#pragma comment(lib, "ws2_32.lib")

DWORD WINAPI foo( void* p)
{
	SOCKET s = (SOCKET)p;

	// Ŭ���� ��Ʈ�� ������ ����ü�� �����Ѵ�. 
	CALCPACKET packet;
	int total = sizeof(packet); // �����ؾ� �ϴ� ũ��
	int current = 0;            // ���� ������ �� ũ��
	int nRead = 0;

	while ( total > current ) // ���� �� ���� ���� ���
	{
		nRead = recv( s, (char*)&packet + current, total - current, 0 );

		if ( nRead > 0 )
		{
			current += nRead;
			continue; // ��� �����Ѵ�
		}
		else if ( nRead == 0 ) // ������ ���� �� ���
		{
			break;
		}
		else if ( nRead < 0 ) // ���ſ��� �߻�
		{
			break;
		}
	}

	//------------------------------------------------------------


	// ������ �����Ѵ�.
	int sum = 0;
	switch( packet.cmd )
	{
	case PLUS :    sum = packet.first + packet.second; break;
	case MINUS:    sum = packet.first - packet.second; break;
	case DIVIDE:   sum = packet.first / packet.second; break;
	case MULTIPLY: sum = packet.first * packet.second; break;
	}
	// ����� first �� �־ ���� ������.
	packet.first = sum;
	
	send( s, (char*)&packet, sizeof(packet), 0);

	closesocket(s );
	return 0;
}





//----------------------------------------------------------------
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
	addr.sin_port   = htons( 4000 ); // Port #
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

		// ���ο� �����带 �����ؼ� Ŭ���� ��Ʈ�� ��û�� ó���Ѵ�.
		HANDLE hThread = CreateThread( 0, 0, foo, (void*)c_s, 0, 0);
		CloseHandle( hThread );
	}

	//--------------------------------------------
	closesocket( s ); // ���� �ݱ�.
	WSACleanup();
}









