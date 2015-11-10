#pragma comment(linker, "/subsystem:windows")

#include <windows.h>
#include <commctrl.h>

// Window ȯ�濡���� ������ �Լ��� ���. - �ܿ켼��.
DWORD WINAPI foo( void* p)
{
	HWND hPrg = (HWND)p;

	for ( int i = 0; i < 1000; ++i )
	{
		SendMessage( hPrg, PBM_SETPOS, i, 0); // ���α׷��� ����
		for ( int k = 0; k < 5000000; ++k ); // 0 6�� - some work.!!
	}
	return 0;
}



LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HWND hPrg;
	static HANDLE hThread;
	switch( msg )
	{	
	case WM_CREATE:
		hPrg = CreateWindow( PROGRESS_CLASS, "", 
							 WS_CHILD | WS_VISIBLE | WS_BORDER | PBS_SMOOTH,
							 10, 10, 500,30, hwnd, (HMENU)1, 0, 0);

		//����:0 ~1000 �ʱ���ġ:0���� �ʱ�ȭ.
		SendMessage( hPrg, PBM_SETRANGE32, 0, 1000);
		SendMessage( hPrg, PBM_SETPOS,     0, 0);
		return 0;
	case WM_LBUTTONDOWN: 
		{
			// ���ο� �����带 ���� �۾��� ��Ű�� �ֽ������ �ִ��� ����
			// �޼��� ������ ���� ���� ���� �޼����� ó���Ѵ�.
			DWORD tid;
			hThread = CreateThread( 0, 0, // TKO ����, Stack ũ��
								foo, (void*)hPrg, // ������� ������ �Լ�,����
								CREATE_SUSPENDED,// ���������� ������ ���� �ʴ´�.
								&tid);			// ������ ������ ID�� ���� ����
			//CloseHandle( hThread ); // TKO�� ���������� �ʱ⿡ 2�̴�.
							// ������ ����� �Բ� ��� �ı��ǵ��� 1 ���δ�.
		}
		return 0;

	case WM_RBUTTONDOWN:
		{
			static BOOL bRun = FALSE;

			bRun = !bRun; // Toggle
			if ( bRun )
				ResumeThread( hThread );	// ������ �簳
			else
				SuspendThread( hThread );  // ������ �Ͻ� ����
		}
		return 0;


	case WM_DESTROY:
		CloseHandle( hThread);
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

