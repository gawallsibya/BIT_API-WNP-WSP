#include <iostream>
#include <windows.h>
using namespace std;

// Event : �����尣 ����� ����� ����ȭ.
void main()
{
	HANDLE h = CreateEvent( 0,     // ����
							FALSE, // ������ ���� ( TRUE: manual, FALSE : auto)
							FALSE, // �ʱ� Signal ����
							"e");

	while ( 1 )
	{
		int n;	cin  >> n;

		// Event�� Signal �Ѵ�.
		SetEvent( h );
	}


	CloseHandle( h );
}


