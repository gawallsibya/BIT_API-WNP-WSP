#include <stdio.h>
#include <windows.h>
#include <conio.h>
// �ʱ�ȭ�� ���� ���� .data section �� ���δ� - �⺻������ COPY ON WRITE
int x = 0; 

#pragma data_seg("AAA")	// exe(PE) �� ���ο� data section AAA�� �����
int y = 0;
#pragma data_seg()

// AAA ������ �Ӽ��� �����Ѵ�. (Read, Write, Share)
#pragma comment(linker, "/section:AAA,RWS") 

void main()
{
	++x; ++y;

	printf("x = %d\n", x);
	printf("y = %d\n", y);

	getch();
}
// ������ ���� 2���̻� ������ ������.!!



/*  
	�޸� ���� 1. Copy On Write ��� ���� - �߿��� OS���� �̹Ƿ� �� �˾� �Ѱ�...
	            2. ���� �޸� ����� ���. 

*/




