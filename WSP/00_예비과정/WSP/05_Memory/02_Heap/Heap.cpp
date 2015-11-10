#include <stdio.h>
#include <windows.h>

void main()
{
	// ���μ����� �⺻ ���� �ڵ��� ���Ѵ�.
	HANDLE h1 = GetProcessHeap();
	HANDLE h2 = HeapCreate( 0, 1024*1024, 0); // flag, �ʱ� ũ��, �ִ� ũ��

	// ������ �޸� �Ҵ�
	void* p1 = HeapAlloc( h1, HEAP_ZERO_MEMORY, 100);
	void* p2 = HeapAlloc( h2, HEAP_ZERO_MEMORY, 100);

	printf("�Ҵ��� �޸� �ּ� : %p\n", p1 );
	printf("�Ҵ��� �޸� �ּ� : %p\n", p2 );

	HeapFree( h1, 0, p1 );
	HeapFree( h2, 0, p2 );

	// ������ �� �ı�(�⺻���� �ı����� �ʴ´�.)
	HeapDestroy( h2 );
}
// �ᱹ�� malloc() �� ����� �뵵�� ����ϸ� �ȴ�.!










