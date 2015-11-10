// Thread Stack

#include <windows.h>
#include <iostream>
using namespace std;

/*
������ ������ IMB stack�� �������
PAGE_READWRITE ���� : 4K ����� �� �ִ� ����
PAGE_GUARD			: ��� �Ұ���, �̵� ����
PAGE_RESERVER		: ���� ����

=> ��뷮�� �þ������ 4K ������ 
   PAGE_READWRITE�� PAGE_GUARD ������ �̵���

���� ������ ���� �Ǹ� Exception ���� �߻�(overflow)
*/
int Sum( int n )
{
	// Sum�� ����� ȣ��
	return n == 0 ? 0 : ( n + Sum(n - 1) );
}

DWORD Handler( DWORD e )
{
	if ( e == EXCEPTION_STACK_OVERFLOW)
		cout << "stack overflow" << endl;
	return EXCEPTION_EXECUTE_HANDLER;
}
DWORD WINAPI ThreadFunc( LPVOID p)
{
	// �հ踦 ���ؾ� �� ������ ������ ����
	int n= (int)p;

	int s = -1;
	__try{
		// s���� n������ �հ踦 ����
		// �հ踦 ����� �� ���� ��� -1�� ����
		s = Sum(n);
	}
	__except( Handler(GetExceptionCode()) )
	{
		// ���� �����÷ο찡 �߻����� �� �� �κ� ����
		cout << " ���� �߻� " << endl;
	}
	return s;
}

void main()
{
	int n;
	while(1)
	{
		cin >> n;
		HANDLE hThread = CreateThread(NULL, 0, // 1MB Stack Memory
				ThreadFunc, (void*)n, 0, 0);

		cout << "��� ���"  << endl;
		WaitForSingleObject( hThread, INFINITE);

		DWORD code;
		GetExitCodeThread(hThread, &code);
		if( code == -1 )
		{
			cout << "���� �ʹ� ũ��. " << endl;
		}
		else
		{
			cout << "��� : " << code << endl;
		}
		CloseHandle(hThread);
	}
}
























