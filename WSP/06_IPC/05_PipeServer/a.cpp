#include <windows.h>
#include <stdio.h>

// MultiThread ����� Named Pipe Server....!!!
// ������ n/w ���� ����Ϸ��� ���� socket ���α׷����� ����.!
DWORD WINAPI foo( void* )
{
	HANDLE hPipe = CreateNamedPipe( "\\\\.\\pipe\\source_server", // UNC
									PIPE_ACCESS_OUTBOUND, //��� ����
									PIPE_TYPE_BYTE,		  // stream ���
									5,		// �ִ� instance ����
									4096, 4096,// ����� ���� ũ��
									1000,	// WaitNamedPipe()�� ����� �ð�
									0);		// KO ����
	if ( hPipe == INVALID_HANDLE_VALUE )
	{
		printf("Pipe �� �����Ҽ� �����ϴ�.\n");
		return 0;
	}
	//=====================================================
	while ( 1 )
	{
		BOOL b = ConnectNamedPipe( hPipe, 0); // Client�� ������ ����Ѵ�.
									// Ŭ���̾�Ʈ�� �����Ҷ� ���� blocking

		if ( b == FALSE && GetLastError() == ERROR_PIPE_CONNECTED ) b = TRUE;

		if ( b ) // ���� �Ǿ��ٸ�
		{
			printf("Client ����\n");
			char* buf = 0;
			// Ŭ�����忡 �ִ� data�� ������.
			//=====================================
			if ( OpenClipboard( 0 ))
			{
				HANDLE hData = GetClipboardData( CF_TEXT);

				char* p = (char*)GlobalLock( hData );
				
				buf = (char*)malloc( strlen(p) +1);

				strcpy( buf, p );
				GlobalUnlock( hData );
				CloseClipboard();
			}
			//====================================
			// Pipe�� Write
			DWORD len;
			WriteFile( hPipe, buf, strlen(buf)+1, &len, 0);
			FlushFileBuffers( hPipe );
			DisconnectNamedPipe( hPipe ); // ������ ������ ���´�.

			free(buf );
		}
	}
}





void main()
{
	HANDLE h1 = CreateThread( 0, 0, foo, 0, 0, 0);
	HANDLE h2 = CreateThread( 0, 0, foo, 0, 0, 0);
	HANDLE h3 = CreateThread( 0, 0, foo, 0, 0, 0);
	HANDLE h4 = CreateThread( 0, 0, foo, 0, 0, 0);
	HANDLE h5 = CreateThread( 0, 0, foo, 0, 0, 0);

	HANDLE h[5] = { h1,h2, h3, h4, h5 };
	
	WaitForMultipleObjects( 5, h, TRUE, INFINITE );

	CloseHandle( h1 );
	CloseHandle( h2 );
	CloseHandle( h3 );
	CloseHandle( h4 );
	CloseHandle( h5 );
}




















