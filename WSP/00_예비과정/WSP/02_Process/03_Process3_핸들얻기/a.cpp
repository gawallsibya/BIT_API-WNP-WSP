#pragma comment(linker, "/subsystem:windows")

#include <windows.h>

LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch( msg )
	{	
	case WM_LBUTTONDOWN: SetCapture( hwnd ); return 0;
	case WM_LBUTTONUP:
		if ( GetCapture() == hwnd )
		{
			ReleaseCapture();
			POINT pt;

			// ���� ���콺 ������ ���(��ũ�� ��ǥ)
			GetCursorPos(&pt);
			// ������ �ڵ� ���..
			HWND h = WindowFromPoint( pt );

			// �ش��ϴ� ������(h)�� ���� ���μ����� ID�� ���Ѵ�.
			DWORD pid;
			DWORD tid = GetWindowThreadProcessId( h, &pid );

			// ���μ��� ID�� ������ ���μ��� �ڵ��� ��´�.(Table�� �׸��������)
			HANDLE hProcess = OpenProcess( PROCESS_ALL_ACCESS, 0, pid );

			// ���μ��� �ڵ� ���
			TerminateProcess( hProcess, 0 );
			WaitForSingleObject( hProcess, INFINITE );

			CloseHandle( hProcess);
		}
		return 0;
				// � ���� �ϴ� �ڵ������� �� ���� ������ ������.







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

