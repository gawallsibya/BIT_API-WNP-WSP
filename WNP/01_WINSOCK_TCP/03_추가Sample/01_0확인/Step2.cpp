//--------------------------------------------------------------
// #define WIN32_LEAN_AND_MEAN
// h���� �浹 ó�� 
//----------------------------------------------------------------

#define WIN32_LEAN_AND_MEAN // windows.h ���� ���� ������� ���� ���� �����Ͽ���
							// ���� �Ѵ�. winsock2.h ���� �浹�� ���� �ش�.
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

	//--------------------------------------------
	WSACleanup();
}

// ��������� �ڵ尡 ��� Network ���α׷��� �⺻ �ڵ� �Դϴ�. �� ������ �μ���.
// ������ �� �ڵ带 �����ؼ� ����ϰڽ��ϴ�.








