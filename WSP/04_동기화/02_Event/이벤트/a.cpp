#include <iostream>
#include <windows.h>
using namespace std;

// Event : �����尣 ����� ����� ����ȭ.
void main()
{
	HANDLE h = CreateEvent( 0,     // ����
							TRUE, // ������ ���� ( TRUE: manual, FALSE : auto)
							FALSE, // �ʱ� Signal ����
							"e");

	cout << "Event�� ��� �մϴ�." << endl;

	WaitForSingleObject( h, INFINITE );
	cout << "Event ȹ��" << endl;

	WaitForSingleObject( h, INFINITE );
	cout << "Event ȹ��" << endl;

	CloseHandle( h );
}

//--------------------------------------------------------------
//
HANDLE h = CreateEvent( 0, FALSE, FALSE, "e"); // auto

HANDLE h1 = CreateEvent( 0, TRUE, FALSE, "e"); // ���� �̸��� ���� �ϸ�	
											// 1, 2, 3 �� ���ڴ� ���� �ȴ�.

HANDLE h2 = CreateMutex( 0, 0, "e"); // ?? ����.. ��� KO�� ���� �̸� ���� ���.

















