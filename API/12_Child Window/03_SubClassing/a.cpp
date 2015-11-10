#pragma comment(linker, "/subsystem:windows")

#include <windows.h>

WNDPROC old; // ������ EditBox�� �޼��� ó���Լ��� �ּҸ� ���� ����
LRESULT CALLBACK foo( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch( msg )
	{
	case WM_CHAR:
		if ( ( wParam >= '0' && wParam <= '9') || wParam == 8 )
			// ������ �޼���ó�� �Լ��� �����Ѵ�.
			wParam = 'a';
			return CallWindowProc( old, hwnd, msg, wParam, lParam);

		return 0; // ���� �̿��� ���� �����Ѵ�.
	}
	// ������ ��� �޼����� ������ �Լ��� �����Ѵ�.
	return CallWindowProc( old, hwnd, msg, wParam, lParam);
}
	



LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HWND hEdit;

	switch( msg )
	{	
	case WM_CREATE:
		hEdit = CreateWindow( "edit", "", WS_CHILD | WS_VISIBLE | WS_BORDER,
							10,10,200,200, hwnd, (HMENU)1, 0, 0);

		old = (WNDPROC)SetWindowLong( hEdit, GWL_WNDPROC, (LONG)foo );
		return 0;









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
		// ���⼭ �޼����� ó���ϸ� �θ�� �ƴ϶� ��� �ڽ�������� ���޵Ǵ�
		// �޼����� ���� ó���Ҽ� �ִ�.
//		if ( msg.message == WM_SYSKEYDOWN  && msg.wParam == 'X' )
//		{
//			MessageBox( hwnd, "����~~", "", MB_OK);
//			SendMessage( hwnd, WM_CLOSE, 0, 0);
//			continue;   
//		}

//	  PreTranslateMessage( &msg ); // MFC �� �ִ� �Լ�.*****
		TranslateMessage(&msg);
		DispatchMessage( &msg);
	}

	return 0;
}

// ���� 1. DispatchMessage() ���� �޼����� ó���ϴ� ���.
//      2. Subclassing.













