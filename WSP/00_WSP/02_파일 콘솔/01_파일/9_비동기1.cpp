/****************************************************************************

  4) Sample1

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

//---------------------------------------------------
//  �񵿱� I/O ó���� �̿��� ���� ����
//---------------------------------------------------

#include <stdio.h>
#include <windows.h>
#include <conio.h>

void main()
{
	HANDLE hFile = CreateFile( "COM1", // Serial Port Open
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

	// �񵿱�� ����Ѵ�.
	OVERLAPPED ov = { 0 };
	ov.hEvent       = CreateEvent( 0, 0, 0, "e"); // �۾��� 1���� event�� �ش�.
	ov.Offset       = 0;
	ov.OffsetHigh   = 0; // �۾��� ������ ȭ�� offset �� �����Ѵ�.
	ov.Internal     = 0;
	ov.InternalHigh = 0; // OS�� ���������� ����ϴ� �׸�-����ڴ� �������� 
						// �ʴ´�.

	const int size = 1000000;
	char buf[size];
	DWORD len = 0;


	BOOL b = WriteFile( hFile, buf, size, &len, &ov);

	if ( b == TRUE )
		printf("���������� ȭ�� ��� �Ϸ�\n");
	else if ( b == FALSE && GetLastError() == ERROR_IO_PENDING )
	{
		printf("�񵿱�� �۾���..\n");
		
		//...
		// �ٸ� �۾��� ��ģ�� �����۾��� ������ ���� ��ٸ�����
		WaitForSingleObject( ov.hEvent, INFINITE );

		//WaitForSingleObject( hFile, INFINITE );
		printf("�񵿱� �۾� �Ϸ�\n");
	}
	else
		printf("����\n");


	CloseHandle( hFile );
}







