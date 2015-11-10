/****************************************************************************

  4) Sample3

    �񵿱� I/O(��ø�� �����) 

              : �ַ� ��Ʈ��ũ ���α׷��̳� �������(�ø���)�� ���

 

    ��뷮 ���� �������� �ַ� ���

    - ��뷮 ���� ���� �ֽ����忡���� accept�� �񵿱�� Send�� �ϰ� �ι�° 

       �����忡���� Send�۾����� Event�� �޾� Socket�� �ݴ� ��Ȱ�� �Ѵ�


     1. �񵿱� ��û�ϴ� ��

     2. �񵿱� �۾��� ���� ���

         -> Event ���

     3. ��û ������� ��� ������ �и�

****************************************************************************/


#include <stdio.h>
#include <windows.h>
#include <conio.h>

// IOCP ���� �񵿱� �۾��� ����� ������
DWORD WINAPI foo( void* p )
{
	HANDLE hPort = (HANDLE)p;

	// ���� IOCP �� �Ϸ� Q�� �Ϸ�� �񵿱� �۾��� ��� �ö� ���� ����Ѵ�.
	DWORD key;
	OVERLAPPED* ov;
	DWORD bytes;
	while ( 1 )
	{
		GetQueuedCompletionStatus( hPort, &bytes, &key, &ov, INFINITE );

		printf("�񵿱� �۾��� �Ϸ� �Ǿ����ϴ�.\n");
		printf("�Ϸ�Ű : %d\n", key);
		printf("Bytes  : %d\n", bytes );
	}
	return 0;
}


void main()
{
	HANDLE hFile = CreateFile( "COM1",// "COM1", // Serial Port Open
								GENERIC_WRITE,
								FILE_SHARE_READ | FILE_SHARE_WRITE,
								0,
								OPEN_EXISTING,
	FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,  // ȭ���� �񵿱�� Open
								0); // template file

	if ( hFile == INVALID_HANDLE_VALUE )
	{
		printf("COM1 �� Open �Ҽ� �����ϴ�.\n"); return;
	}

	// IOCP( ����� �Ϸ� ��Ʈ)�� �����Ѵ�.
	HANDLE hPort = CreateIoCompletionPort( INVALID_HANDLE_VALUE, // ȭ���ڵ�
											0, // ������ �����ϴ� IOCP �ڵ�
											0, // �Ϸ� Ű.
											2); // ���ÿ� ��� ���� �������

	// �ϼ��� IOCP �� ȭ���� �ڵ��� �߰��Ѵ�
	CreateIoCompletionPort( hFile, hPort, 1, // �Ϸ� Ű
										2);

	// ���ο� �����带 ���� �񵿱� IO�� �ϷḦ ó���Ѵ�.
	HANDLE hThread = CreateThread( 0, 0, foo, (void*)hPort, 0, 0);
	CloseHandle( hThread );

	//-----------------------------------------------------------------------
	const int size = 1024;
	char buf[size];
	DWORD len = 0;


	// ���� �񵿱� �۾��� �����Ѵ�.
	OVERLAPPED ov = { 0};
	BOOL b = WriteFile( hFile, buf, size, &len, &ov);

	// �ٸ� �۾� ����..... - �񵿱� �۾� �Ϸ�� ó���� �ٸ� �����尡 �ϰԵȴ�.
	getch();


	CloseHandle( hFile );
}





