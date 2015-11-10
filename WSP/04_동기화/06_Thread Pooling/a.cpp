#include <iostream>
#include <queue>  
#include <windows.h>
#include <conio.h>
using namespace std;

// ������ Ǯ��..!


//-------------------------------------------------
// �۾��� ���(�ᱹ �۾��̶� -> �Լ� �� �ǹ�.)
typedef void(*WORK)();

queue<WORK> WORK_Q;
HANDLE hSemaphore; // �۾� Q�� ������  count;

DWORD WINAPI Thread( void* p )
{
	while ( 1 )
	{
		// �۾� Q�� �۾��� ������ ���� ����Ѵ�.
		WaitForSingleObject( hSemaphore, INFINITE );
		WORK f = WORK_Q.front();
		WORK_Q.pop();
		f(); // �۾� ����.
	}
	return 0;
}
void InitPool( int n )
{
	hSemaphore = CreateSemaphore( 0, 0, 1000, "WORK_COUNT");
	for ( int i = 0; i < n; ++i)
	{
		CloseHandle( CreateThread( 0, 0, Thread, 0, 0, 0));
	}
}
void AddWork( WORK f)
{
	// �۾� Q�� �۾�(�Լ��ּ�)�� �ִ´�.
	WORK_Q.push( f );
	// ������� �����ؼ� �ڰ� �ִ� �����带 �����.
	LONG old;
	ReleaseSemaphore( hSemaphore, 1, &old);
}
//=============================================================
// ���� �۾� �Լ�.
CRITICAL_SECTION cs;
void foo()
{
	for ( int i = 0; i < 10; ++i )
	{
		EnterCriticalSection(&cs);
		printf("%d : %d\n", GetCurrentThreadId(), i );
		fflush(stdout);
		LeaveCriticalSection(&cs);

		Sleep( 1000 );
	}
	return;
}
void main()
{
	InitializeCriticalSection(&cs);
	InitPool( 1 );
	// 5���� �۾��� Q�� �ִ´�.
	AddWork( foo ); AddWork( foo ); AddWork( foo ); AddWork( foo );AddWork( foo );

	getch(); // ������ �ʵ���.
	DeleteCriticalSection( &cs);
}




































