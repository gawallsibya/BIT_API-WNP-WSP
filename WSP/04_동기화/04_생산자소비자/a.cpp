#include <windows.h>
#include <iostream>
#include <queue> // STL�� Q
#include <time.h>
using namespace std;

queue<int> Q;		// 2���� �����尡 ���ÿ� ����ϴ� ���� �ڿ�

HANDLE hMutex;	// Q�� ������ ����ȭ �ϱ� ���� Mutex���(CRITICAL_SECTION �� 
				// �� ���� ������.mutex������ ����)

HANDLE hSemaphore;	// Q�� ������ Count �ϱ� ����.



// ������
DWORD WINAPI Produce( void* ) 
{
	static int value = 0;
	while ( 1 )
	{
		// Q�� ������ �Ѵ�.
		++value;
		
		// Q�� ���ٿ� ���� �������� ��´�.
		WaitForSingleObject( hMutex, INFINITE); 
		//---------------------------------------------
		Q.push( value );
		printf("Produce : %d\n", value );
		
		LONG old;
		ReleaseSemaphore( hSemaphore, 1, &old); // �������� ������ �����Ѵ�.
		//------------------------------------------------
		ReleaseMutex( hMutex );



		Sleep( (rand() % 20 )* 100); // 0.1s ~ 2s�� ���.
	}
	return 0;
}

// �Һ���
DWORD WINAPI Consume( void* p)
{
	while ( 1 )
	{
		WaitForSingleObject( hSemaphore, INFINITE ); // Q�� ��� �ִٸ� ���.
		WaitForSingleObject( hMutex, INFINITE );
		//----------------------------------------------
		int n = Q.front();  // Q�� ���� �տ�� ���(�������� �ʴ´�.)
		Q.pop();			// ����.
		printf("		Consume : %d\n", n );
		//----------------------------------------------
		ReleaseMutex( hMutex );







		Sleep( (rand()%20)*100); // 0.1s ~ 2s�� ���
	}
	return 0;
}



void main()
{
	hMutex = CreateMutex( 0, FALSE, "Q_ACCESS_GUARD");
	hSemaphore = CreateSemaphore( 0, 0, 1000, "Q_RESOURCE_COUNT"); //�ִ�
													// 1000���� , �ʱ� 0

	srand( time(0));
	HANDLE h[2];
	h[0] = CreateThread( 0, 0, Produce, 0, 0,0);
	h[1] = CreateThread( 0, 0, Consume, 0, 0,0);
  
	WaitForMultipleObjects( 2, h, TRUE, INFINITE );

	CloseHandle( h[0] );
	CloseHandle( h[1] );
	CloseHandle( hMutex );
	CloseHandle( hSemaphore );
}















