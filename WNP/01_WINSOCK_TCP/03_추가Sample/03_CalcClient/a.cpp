
#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <windows.h>	
#include <winsock2.h>	
#pragma comment(lib, "ws2_32.lib")
#include <stdlib.h>

#include "CalcPacket.h"   // ��� ������ ������..

void main( int argc, char** argv)
{
	if ( argc != 4 )
	{
		printf("usage : CalcClient  <first number>  <+,-,*,/> <second number>\n");
		return;
	}
	int first = atoi(argv[1]);
	int second = atoi(argv[3]);
	int cmd    = (int)(argv[2][0]); 
	//----------------------------------------------------------------
	WSADATA wsadata;

	if ( WSAStartup( MAKEWORD(2,2), &wsadata) != 0 )
	{
		printf("Can't Initialize Socket !\n");
		return ;
	}
	//--------------------------------------------
	SOCKET s = socket( AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN addr = {0};
	addr.sin_family = AF_INET;
	addr.sin_port   = htons( 4000 );
	addr.sin_addr.s_addr = inet_addr("61.81.99.138"); // ????

	if ( connect(s, (SOCKADDR*)&addr, sizeof(addr)) == -1 )
	{
		printf("������ �����Ҽ� �����ϴ�.\n");
		return ;
	}
	// ������ packet�� ������.
	CALCPACKET packet = { cmd, first, second };

	send( s, (char*)&packet, sizeof(packet),0);

	//--------------------------------------------------------
	// ���ƿ��� packet�� �����Ѵ�.
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
	//===================================================
	printf("��� : %d\n", packet.first);
	closesocket( s );
	//--------------------------------------------
	WSACleanup();
}











