#pragma comment(linker, "/subsystem:windows")

#include <windows.h>

LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HWND hEdit;

	switch( msg )
	{	
	case WM_CREATE:
		
		hEdit = CreateWindow( "edit", "", 
							WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE,
							10, 10, 500,500, hwnd, (HMENU)1, 0, 0);
		return 0;
	/*
	case WM_LBUTTONDOWN:
		{
			HANDLE hRead, hWrite;
			CreatePipe( & hRead, & hWrite, 0, 1024);
			SetHandleInformation( hWrite, HANDLE_FLAG_INHERIT, 
										  HANDLE_FLAG_INHERIT );

			PROCESS_INFORMATION pi = {0};
			STARTUPINFO si = { 0};
				
			si.cb = sizeof(si );
			si.hStdOutput = hWrite;//�������� ������ �ڵ��� �ڽ��� ǥ���������
			si.dwFlags = STARTF_USESTDHANDLES;

			BOOL b = CreateProcess( 0, "ping.exe www.imbc.com", 0,0, TRUE,
									CREATE_NO_WINDOW, 0, 0, &si, &pi );
			if ( b )
			{
				CloseHandle( hWrite ); // �������� �ڵ��� �ʿ� ����.

				DWORD len;
				while ( 1 )
				{
					char s[4096] = {0};
					BOOL bRet = ReadFile( hRead, s, 4096, &len, 0);

					if ( bRet == FALSE ) break; // �������� ���� ���.

					// SetWindowText()�� ����ϸ� ������ edit data �� ��������
					// ���Ӱ� �߰� �ȴ�. - ���پ� �����̷���!
					SendMessage( hEdit, EM_REPLACESEL, 0, (LPARAM)s);
				}
				CloseHandle( hRead );
				CloseHandle( pi.hProcess);
				CloseHandle( pi.hThread);
			}
		}
		return 0;
	*/





	case WM_LBUTTONDOWN: 
		{
			PROCESS_INFORMATION pi = { 0 } ;
			
			// ping ����� redirect �� ���� ����
			HANDLE hFile = CreateFile( "a.txt", GENERIC_READ | GENERIC_WRITE,
										FILE_SHARE_READ | FILE_SHARE_WRITE,
										0, 
										CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);

			// ��� KO �� �⺻������ ��� �Ұ��� �ϴ�.
			// Ư�� KO�� ��Ӱ����ϰ� �����Ѵ�.
			SetHandleInformation( hFile, HANDLE_FLAG_INHERIT, // ��Ӱ��ɿ��θ�
										 HANDLE_FLAG_INHERIT ); // ��Ӱ����ϰ�.
			//===============================================================
			STARTUPINFO si = {0};
			si.cb = sizeof( si );

			si.hStdOutput = hFile;  // ping �� stdout�� ������ ����.
			si.dwFlags    = STARTF_USESTDHANDLES;


			BOOL b = CreateProcess( 0, "ping.exe www.imbc.com", 0,0, TRUE,
							CREATE_NO_WINDOW, // flag. console�� ����������
									0, 0, &si, &pi);
			if ( b )
			{
				// ping�� ���� �ɶ����� ����Ѵ�.
				WaitForSingleObject( pi.hProcess, INFINITE );

				// a.txt ���� ��� data�� �о edit�� ����Ѵ�.
				char s[4096] = {0};

				SetFilePointer( hFile, 0, 0, FILE_BEGIN); // ȭ�� �����͸� ���� 
														  // ������
				DWORD len;
				ReadFile( hFile, s, 4096, &len, 0);

				SetWindowText( hEdit, s );

				CloseHandle( hFile );
				//===========================================
					
				


				CloseHandle( pi.hProcess );
				CloseHandle( pi.hThread );
			}
		}
		return 0;

	


//������Ʈ�� ã�¹�...
//HKEY_CURRENT_USER			\software \ ȸ���̸� \ ���α׷��̸�	\ ���� ���ð�.
//HKEY_LOCAL_MACHINE
//regedit.exe


//www.codeproject.com	// ������ ���� ���� �ҽ��ڵ� ����Ʈ
//www.catch22.net		//
//www.codeguru.com		// 3���� ���� �ܱ� ����Ʈ..
//www.devia.com			// -�ѱ�











	case WM_DESTROY:
		PostQuitMessage(0); 
		return 0;
	}
	return DefWindowProc( hwnd, msg, wParam, lParam);
}

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
					LPSTR	  lpCmdLine, int nShowCmd )
{
	ATOM atom;
	WNDCLASS wc;
	HWND hwnd;
	MSG msg;
	
	wc.cbClsExtra	= 0;
	wc.cbWndExtra	= 0;
	wc.hbrBackground= (HBRUSH)GetStockObject( WHITE_BRUSH ); 
	wc.hCursor		= LoadCursor( 0, IDC_ARROW );
	wc.hIcon		= LoadIcon( 0, IDI_APPLICATION);
	wc.hInstance	= hInstance;
	wc.lpfnWndProc  = WndProc; 
	wc.lpszClassName= "First";
	wc.lpszMenuName = 0;
	wc.style		= 0;

	atom = RegisterClass( &wc);
	
	if ( atom == 0 ) 
	{
		MessageBox( 0, "Fail To RegisterClass", "Error", MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx( 0, "first", "Hello", WS_OVERLAPPEDWINDOW,
								CW_USEDEFAULT, 0, CW_USEDEFAULT,0, 0, 0, 
								hInstance, 0); 
	ShowWindow( hwnd, nShowCmd); 
	UpdateWindow( hwnd );

	while ( GetMessage( &msg, 0, 0, 0) ) 
	{							
		TranslateMessage(&msg);
		DispatchMessage( &msg);
	}

	return 0;
}

