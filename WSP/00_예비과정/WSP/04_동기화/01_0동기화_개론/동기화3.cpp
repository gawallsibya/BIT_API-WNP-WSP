// Semaphre
#include <windows.h>
#include <stdio.h>

void main()
{
	HANDLE hSemaphore = CreateSemaphore( 0, // ����
										3,  // count �ʱⰪ
										3,	// �ִ� count
										"s"); // �̸�
	printf("������� ����մϴ�.\n");

	WaitForSingleObject( hSemaphore, INFINITE ); //++count

	printf("���� ��� ȹ��\n");
	MessageBox(0, "Release??","", MB_OK);

	LONG old;
	ReleaseSemaphore( hSemaphore, 1, &old ); // count -= 2nd parameter

	CloseHandle( hSemaphore );
}

// �޼��� Box �� OK�� ������ ����.. 4�� �̻� ������ ������..













/*
count ���� ������ �ִ�.(���� ������ ����)

���α׷��� �ν��Ͻ� ������ �����ϴ� �� ���� 
�ٿ�ε� �� �� �ִ� �ٿ�ε� ���ڸ� �����ϴ� �� ���
*/
/*
#include <windows.h>
#include <iostream>
using namespace std;



void main()
{
	HANDLE	h = CreateSemaphore( NULL, 3, 3, // �ʱ� count, �ִ� count
					"sem");		// ������ �̸�

	cout << "������� ��ٸ���." << endl;
	WaitForSingleObject(h, INFINITE);

	cout << "DownLoading.............." << endl;
	for( int i=0; i<100; i++)
	{
		cout << ".";
		for( int j=0; j< 10000000; j++);
	}
	MessageBox(NULL, "End DownLoad", "", MB_OK);
	long old;
	ReleaseSemaphore(h, 1, &old);		// count 1����
	CloseHandle(h);
}
*/