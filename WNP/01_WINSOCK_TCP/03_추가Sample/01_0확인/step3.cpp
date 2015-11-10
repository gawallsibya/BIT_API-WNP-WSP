//--------------------------------------------------------------
// IPv4 : inet_addr & inet_ntoa
//
//----------------------------------------------------------------


#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <windows.h>	
#include <winsock2.h>	
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
	// ���ڿ� ������ IP�� Long ���� ���� �ϱ�. - IPv4, 
	long ip = inet_addr("100.100.100.200");
	printf("%x\n", ip );

	// IP �ּҸ� ���ϰ� �ٷ�� ���� ������� ����ü - in_addr(ũ��� �ᱹ 4byte)
	in_addr addr;  
	addr.s_addr = ip; // long ������ ����.
	
	printf("%d\n", addr.s_impno); // ������ 4��° byte�� ��´�.
	//------------------------------------------------------------
	// in_addr �� ��� �ּҸ� �ٽ� ���ڿ��� �ٲٴ� �Լ�.
	char* p = inet_ntoa( addr );

	printf("%s\n", p );


	//--------------------------------------------
	WSACleanup();
}









