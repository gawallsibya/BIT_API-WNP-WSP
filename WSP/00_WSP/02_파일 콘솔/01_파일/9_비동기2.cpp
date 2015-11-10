/****************************************************************************

  4) Sample2

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


#include <windows.h>
#include <stdio.h>
#include <conio.h>

 
/*
//----------------------- ���� ���� ----------------------------
void main()
{
        HANDLE hFile = CreateFile("COM3", // serial port open

                                  GENERIC_WRITE,

                                  FILE_SHARE_READ | FILE_SHARE_WRITE,

                                  0,

                                  OPEN_EXISTING,

                                  FILE_ATTRIBUTE_NORMAL, 0);

 
        if(hFile == INVALID_HANDLE_VALUE)
        {

                printf("Error, Can't Open com1\n");

                return;

        }

        // ���⼭ DCB��� ����ü�� ����ؼ� baud rate�� ���߰�...
        // Write, Read�ϸ� �ȴ�

        //----------------------------------------------------------
        const int size = 1024;   // 1k
        char buf[size] = {0};

        DWORD len;

        BOOL b = WriteFile(hFile, buf, size, &len, 0);

        if(b == TRUE)
        {
                printf("���������� ���� ����\n");
        }
        else
        {
                printf("����\n");
        }
        CloseHandle(hFile);
}
*/


//----------------------- �񵿱� ���� ------------------------//

 

// �񵿱� �۾��� ���Ḧ ����ϴ� ������
DWORD WINAPI foo( void* p )
{
        HANDLE hEvent = (HANDLE)p;

        // ������ event�� 1������� ������ �ᱹ��
        // Multiple�� ����ؼ� �������� ��� �ϰ� �Ѵ�.

        WaitForSingleObject( hEvent, INFINITE );

        printf("�۾��� ���� �Ǿ����ϴ�.\n");

        return 0;
}

//--------------------------------------------------------------

void main()
{
        HANDLE hFile = CreateFile( "COM1",// serial port open
                                   GENERIC_WRITE,
                                   FILE_SHARE_READ | FILE_SHARE_WRITE,
                                   0,
                                   OPEN_EXISTING,
                       FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED , 
                                   0);

        if ( hFile == INVALID_HANDLE_VALUE )
        {
                printf("Error, Can't Open COM1\n");
                return;
        } 

        // ���⼭ DCB ��� ����ü�� ����ؼ� baud rate �� 
        // ���߰�... Write,Read�ϸ� �ȴ�
        //--------------------------------------
        const int size = 1024; // 1K
        char buf[size] = { 0};
        DWORD len;

         // �񵿱�� ���⸦ ��û�ϴ� ���.- �񵿱�� �������� �ݵ�� 
        // �񵿱�� ��� �Ѵ�.
        OVERLAPPED ov = {0};
        ov.hEvent = CreateEvent( 0, 0, 0, "e1");

         // �񵿱� �۾� ���� �����带 �����ؼ� ����Ѵ�.

        HANDLE hThread = CreateThread( 0, 0, foo, (void*)ov.hEvent, 0,0);
        CloseHandle( hThread );

        BOOL b = WriteFile( hFile, buf, size, &len, &ov);

        if ( b == TRUE )
        {
                printf("���������� ���� ����\n");
        }
        else if ( b == FALSE && GetLastError() == ERROR_IO_PENDING )
        {
                printf("�񵿱������� �۾� ��...\n");

                getch(); // ������� �ʰ�.
                // �񵿱� �۾��� ���� �Ǹ� Overlapped ����ü�� ���޵� 
                // Event�� signal �ȴ�.
                // WaitForSingleObject( ov.hEvent, INFINITE);
                // printf("�񵿱� �۾��� ���� �Ǿ����ϴ�.\n");
        }
        else
        {
                printf("����\n");
        }
        CloseHandle( hFile );

}

