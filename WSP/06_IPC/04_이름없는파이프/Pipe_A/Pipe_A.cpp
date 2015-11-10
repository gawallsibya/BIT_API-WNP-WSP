	// �̸� ���� Pipe ����ϱ�
	#include <iostream.h>
	#include <windows.h>

	void main()
	{
		HANDLE hRead, hWrite;
		BOOL b = CreatePipe( &hRead, &hWrite, 0, 1024);

		// ��� ���μ����� �б� ���� �ڵ��� �������ش�.
		//----------------------------------------------------
		HWND hwnd = FindWindow( 0, "B");

		DWORD pid;
		DWORD tid = GetWindowThreadProcessId( hwnd, &pid);

		// �ּ� �䱸�� ��Ģ.
		HANDLE hProcess = OpenProcess( PROCESS_DUP_HANDLE, 0, pid );

		HANDLE hTarget;
		DuplicateHandle( GetCurrentProcess(), hRead, // source
						 hProcess, &hTarget,         // dest
						 0, 0,
						 DUPLICATE_SAME_ACCESS );
		//-------------------------------------------------------
		SendMessage( hwnd, WM_USER+99, 0, (LPARAM) hTarget );

		// ���� A�� �б����� �ڵ��� �ʿ� �����Ƿ� �ݴ´�.
		CloseHandle( hRead );

		char temp[256] = {0};

		while ( 1 )
		{
			cin.getline( temp, 256);

			// pipe�� Write
			DWORD len;

			WriteFile( hWrite, temp, 256, &len, 0);

			FlushFileBuffers( hWrite ); // ȭ�� ���� ����..
		}

		CloseHandle( hWrite );
	}











