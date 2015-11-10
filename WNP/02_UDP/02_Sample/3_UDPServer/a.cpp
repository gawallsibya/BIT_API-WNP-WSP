// ��Ʈ��ũ �⺻ �ڵ� ������ ������..

#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <winsock2.h>	
#include <windows.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

void main()
{
	WSADATA wsadata;

	if ( WSAStartup( MAKEWORD(2,2), &wsadata) != 0 )
	{
		printf("Can't Initialize Socket !\n");
		return ;
	}
	//--------------------------------------------
	SOCKET s = socket( AF_INET, SOCK_DGRAM, 0);

	SOCKADDR_IN addr;
	addr.sin_family		= AF_INET;
	addr.sin_port		= htons(4000);
	addr.sin_addr.s_addr= INADDR_ANY;

	if ( bind ( s, (SOCKADDR*)&addr, sizeof(addr) ) == -1 )
	{
		printf("Can't bind\n");
		return ;
	}
	// ���� s�� ��Ƽ ĳ��Ʈ �׷쿡 �����Ѵ�.
	ip_mreq mreq;

//	mreq.imr_multiaddr.s_addr = inet_addr( "234.5.5.1"); // �������� ��
//	mreq.imr_interface.s_addr = INADDR_ANY;
//	setsockopt( s, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&mreq, sizeof( mreq));

	// �� �ٸ� �׷쿡 �����Ѵ�.-
	mreq.imr_multiaddr.s_addr = inet_addr( "234.5.5.2"); // 2��
	mreq.imr_interface.s_addr = INADDR_ANY;
	setsockopt( s, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&mreq, sizeof( mreq));
/*	
	mreq.imr_multiaddr.s_addr = inet_addr( "234.5.5.3"); // 3��
	mreq.imr_interface.s_addr = INADDR_ANY;
	setsockopt( s, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&mreq, sizeof( mreq));

	mreq.imr_multiaddr.s_addr = inet_addr( "234.5.5.4"); // 4��
	mreq.imr_interface.s_addr = INADDR_ANY;
	setsockopt( s, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&mreq, sizeof( mreq));

	mreq.imr_multiaddr.s_addr = inet_addr( "234.5.5.5"); // 5��
	mreq.imr_interface.s_addr = INADDR_ANY;
	setsockopt( s, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&mreq, sizeof( mreq));
*/




	while ( 1 )
	{
		SOCKADDR_IN c_addr;
		int sz = sizeof(c_addr);

		char buf[4096] = {0};

		recvfrom( s, buf, 4096, 0, (SOCKADDR*)&c_addr, &sz);

		printf("%s : %s\n", inet_ntoa( c_addr.sin_addr), buf );
	}


	//--------------------------------------------
	WSACleanup();
}






























