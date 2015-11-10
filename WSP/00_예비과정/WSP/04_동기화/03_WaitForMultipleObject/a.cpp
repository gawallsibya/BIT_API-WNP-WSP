#include <windows.h>
#include <stdio.h>

// ���������� ��Ƽ ������ ȯ�濡���� �����ϴ� - ������� ����ص� �ȴ�.
// ����(static����)������ ��Ƽ ������ ȯ�濡���� �������� �ʴ�.
// �ݵ�� ����ȭ �ؾ� �Ѵ�.
// CriticalSection, Mutex, Semaphore, Event ���� ����� ����ؾ� �Ѵ�.


void Delay() { for(int i = 0; i< 5000000; ++i); }  // �ð� ����

BOOL bWait = TRUE;

CRITICAL_SECTION cs; // �Ӱ迵�� cs �ȿ��� 1���� �����常 ��� �ü� �ִ�.

DWORD WINAPI foo( void* p )
{
	char* name = (char*)p;
	static int x = 0;
	
	for ( int i = 0; i < 20; ++i )
	{
		EnterCriticalSection( &cs ); // cs�� ��� ����.
		//---------------------------------------------
		x = 100; Delay();
		x = x+1; Delay();
		printf("%s : %d\n", name, x); Delay();
		//---------------------------------------------
		LeaveCriticalSection( &cs ); // cs���� ���´�.

	}

	printf("Finish...%s\n", name);

	return 0;
}









//===========================================
void main()
{
	InitializeCriticalSection( &cs ); // main ���ϾƷ���
									 // DeleteCriticalSection(&cs); �߰�.


	HANDLE h1 = CreateThread( 0, 0, foo, "A", 0, 0);
	HANDLE h2 = CreateThread( 0, 0, foo, "\tB", 0, 0);

	HANDLE h[2] = { h1, h2 };
	// 64 �� ������ KO �� ����Ҽ� �ִ�.
	WaitForMultipleObjects( 2, h, TRUE, // 2�� ��� signal �ɶ� ���� ���
								INFINITE );

	// Thread KO �� ������ Signal �ȴ�.
//	WaitForSingleObject( h1, INFINITE );
//	while( bWait );  // ���� ����ϸ� �ȵǴ� �־��� ��� - �ϴ��� ����
					 // CPU�� ����ϰ� �ȴ�.
	CloseHandle( h1 );
	CloseHandle( h2 );

	//ExitThread( 0 ); // ���� �����常 ����.
	//return ;       // ���μ����� ����

	DeleteCriticalSection(&cs); 
}


























