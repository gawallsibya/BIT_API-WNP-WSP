// Cursor ����...

#include <windows.h>

// ���콺 Ŀ���� ������ ������ WM_SETCURSOR �޽����� �߻��Ѵ�..
// ����Ʈ ó�� ��ƾ...
// Ŀ���� ������ Ŭ������ ��ϵ� ������ �ٲپ� ������...

// SetCursor,  WM_SETCURSOR
// SetClassLong �� ���� ���� ���� ����..

LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HCURSOR	hNowCursor;

	static HCURSOR  hArrow, hIBeam, hWait, hNow;
	switch( msg )
	{

	case WM_CREATE:
		// LoadCursor
		hArrow = LoadCursor(NULL, IDC_ARROW);
		hIBeam = LoadCursor(NULL, IDC_IBEAM);
		hWait  = LoadCursor(NULL, IDC_WAIT);
		hNow   = hArrow;
		return 0;

	case WM_LBUTTONDOWN:
		// L Button ���������� Ŀ���� ��� ����
		if( hNow == hArrow)			hNow = hIBeam;
		else if( hNow == hIBeam)	hNow = hWait;
		else						hNow = hArrow;

//		SetCursor(hNow);
		// ���� : SetClassLong
		SetClassLong(hwnd, GCL_HCURSOR, (LONG)hNow);
		return 0;


/*
	case WM_SETCURSOR:
//		if( LOWORD(lParam) == HTCAPTION)
		if( LOWORD(lParam) == HTCLIENT)
		{
			SetCursor(hNowCursor);
			return TRUE;
		}
		break;
	case WM_LBUTTONDOWN:
		hNowCursor = LoadCursor(NULL, IDC_WAIT);
		return 0;

	case WM_RBUTTONDOWN:
		hNowCursor = LoadCursor(NULL, IDC_ARROW);
		return 0;
*/
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}


int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, 
				   LPSTR lpCmdLine, int nShowCmd)
{
	// 1. ������ Ŭ���� ����� 
	WNDCLASS wc;
	wc.cbWndExtra			= 0;
	wc.cbClsExtra			= 0;
	wc.hbrBackground		= (HBRUSH)GetStockObject(WHITE_BRUSH);

	// Ŀ�� ����
	// ���� windows �� ��ġ�� directory���
	char dir[256];
	GetWindowsDirectory(dir, 256);
	strcat(dir, "\\cursors\\dinosaur.ani");
	HCURSOR hc				= LoadCursorFromFile(dir);
//	HCURSOR hc				= LoadCursorFromFile("c:\\WINDOWS\\Cursors\\banana.ani");
	

	wc.hCursor				= hc;  //LoadCursor(0, IDC_CROSS);
	wc.hIcon				= LoadIcon(0, IDI_APPLICATION);
	wc.hInstance			= hInstance;
	wc.lpfnWndProc			= WndProc;			// DefWindowProc;
	wc.lpszClassName		= "First";
	wc.lpszMenuName			= 0;
	wc.style				= 0;

	// 2. ���(������Ʈ����)
	RegisterClass(&wc);

	// 3. ������ â ����� 
	HWND hwnd = CreateWindowEx( 0,					// WS_EX_TOPMOST
				 "first",				// Ŭ���� ��
				 "Hello",				// ĸ�ǹ� ����
				 WS_OVERLAPPEDWINDOW, 
				 CW_USEDEFAULT , 0, CW_USEDEFAULT, 0,	// �ʱ� ��ġ 
				 0, 0,			// �θ� ������ �ڵ�, �޴� �ڵ�
				 hInstance,		// WinMain�� 1��° �Ķ���� (exe �ּ�)
				 0);			// ���� ����



	// 4. ������ �����ֱ�
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);
	

	// 5. Message 
	MSG msg;
	while( GetMessage( &msg, 0, 0, 0 ) )
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}