#include <windows.h>
#include <stdio.h>
#include <conio.h>
void main()
{
	const int size = 1024*1024*100;	// 100M

	char* base = (char*)VirtualAlloc( (void*)0x0, // ���ϴ� �����ּ�(64k ���)
								size * 15,		  // ũ��
								MEM_RESERVE,	  // ���ุ
								PAGE_READWRITE ); // ��ȣ�Ӽ�

	printf("����� �ּ� : %p\n", base );
//	*base = 'a'; // runtime error - ���� ���� ������ ����.
	//--------------------------------------------------
	char* p = base;
	for ( int i = 0; i < 15; ++i )
	{
		getch();
		void* temp = VirtualAlloc( p, size, MEM_COMMIT, PAGE_READWRITE);

		printf("Ȯ���� �ּ� : %p\n", temp );
		p = p + size;
	}
	VirtualFree( p, size *15, MEM_DECOMMIT ); // �ٽ� ���� ���·�.
	VirtualFree( p, size *15, MEM_FREE );	  // �ٽ� Free ���·�.
}
