// ���ؽ�

// Ŀ�� ������Ʈ
// - ���ȼӼ�,  �̸�(���ڿ�) 
// �̸��� ���� ���� �ٸ� ���μ������� ���ؽ��� ����ȭ�� �̷������.
#include <windows.h>
#include <stdio.h>
#include <conio.h>
void main()
{
	HANDLE hMutex = CreateMutex( 0,    // ���� �Ӽ�.
								FALSE, // �����ǿ���
								"m");  // ���ؽ� KO �̸�

	printf("���ؽ��� ����մϴ�.\n");

	WaitForSingleObject( hMutex, INFINITE );

	printf("���ؽ��� ȹ���߽��ϴ�.\n");

	getch(); // ��� ���

	ReleaseMutex( hMutex);
	CloseHandle( hMutex );
}


// �� ���α׷��� 2���̻� ������ ������(������ ���� ���¿���..)
/*
#include <windows.h>
#include <iostream>
using namespace std;

void main()
{
	// ���ؽ� ����
	HANDLE	hMutex = CreateMutex(NULL,  // ���ȼӼ�
				FALSE,					// ������ ���ؽ� ���� ����
				"mutex");				// �̸�
 
	// ������ ture�϶� -> Signal �� nonsignal�� �ٲ۴�.

	cout << "���ý��� ��ٸ��� �ִ�." << endl;

	DWORD d = WaitForSingleObject(hMutex, INFINITE);		// ���
	if( d == WAIT_TIMEOUT)
		MessageBox(NULL, "WAIT_TIMEOUT", "", MB_OK);
	else if( d ==WAIT_OBJECT_0)
		MessageBox(NULL, "WAIT_OBJECT_0", "", MB_OK);
	else if( d == WAIT_ABANDONED_0)
		MessageBox(NULL, "WAIT_ABANDONED_0", "", MB_OK);


	cout << "���ý� ȹ��" << endl;
	MessageBox(NULL, "���ý��� ���´�." , "", MB_OK);

//	ReleaseMutex(hMutex);	// ���ؽ� ���� ����.
	// nonsignal -> signal
}
*/
/*
	���ϰ��� WAIT_ABANDONED_0 ��� ���� ����� ���ý���� ���� ���ϵ� ��� 
	��������� �̷� ���α׷��� ����� ���� �ʴ�..
	��Ģ..
*/





















