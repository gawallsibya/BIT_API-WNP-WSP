//--------------------------------------------------------------
// Step1.  Align(���Ĵ���), Big endian & little endian
//----------------------------------------------------------------

#include <stdio.h>

// �����Ϸ����� ����(Align)�� ������ 1byte �����Ѵ�.
#pragma pack( 1 )

/*
struct DATA
{
	char c;
	int  n;
};

void main()
{
	printf("%d\n", sizeof( DATA ) ); // �������� ���� ������ ������.
}
*/



#include <winsock2.h>
#pragma comment( lib, "ws2_32.lib") // ��� socket ���� �Լ��� ws2_32.dll�� �ִ�.


void main()
{
//	int x = 0x12345678; // little endian ������� ���� 

	int x = htonl( 0x12345678);  // host����� data�� network ������� ��ȯ
								// �� Big Endian���� ���� 

	char* p = (char*)&x;

	printf( "%x\n", *p);  // 12 ? 78 ?
}







