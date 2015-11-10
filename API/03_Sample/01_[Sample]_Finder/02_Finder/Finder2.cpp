// STEP  3	
// WM_LBUTTONDOWN.... ���콺 ĸ��(������ ���� ���� ��츸 capture) 
//                    ���콺 ĸ�� ����...

#include <windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HICON		hFill, hEmpty;
	static HCURSOR		hCursor;
	static RECT			rc = { 50, 50 , 82, 82 };	// 32 * 32
	static HINSTANCE	hInst;

	switch( msg )
	{
	// �ʱ�ȭ
	case WM_CREATE:
		// Instance ���..
		hInst		= ( ( LPCREATESTRUCT)lParam)->hInstance;

		hFill		= LoadIcon  ( hInst, MAKEINTRESOURCE(IDI_ICONFILL));
		hEmpty		= LoadIcon  ( hInst, MAKEINTRESOURCE(IDI_ICON_EMPTY));
		hCursor		= LoadCursor( hInst, MAKEINTRESOURCE(IDC_CURSOR_TARGET));
		return 0;

	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc			= BeginPaint(hwnd, &ps);
			DrawIcon( hdc, rc.left, rc.top, hFill);	
			EndPaint(hwnd, &ps);
		}
		return 0;

	case WM_LBUTTONDOWN:
		{
			POINT  pt		=  { LOWORD(lParam), HIWORD(lParam) };

			// ������ ���� ���ΰ�??
			if( PtInRect( &rc, pt ) )
			{
				// 1. ���콺 ĸ�� 
				SetCapture(hwnd);

				// 2. ������ ����
				HDC  hdc = GetDC(hwnd);
				DrawIcon(hdc, rc.left, rc.top, hEmpty);

				ReleaseDC(hwnd, hdc);

				// 3. Ŀ�� ����
				SetCursor( hCursor);
			}
		}
		return 0;
	// ���콺 ĸ�İ� ���� �� �� ȣ��Ǵ� �ڵ鷯..
	// �� �޽������� ȭ���� ��ȿȭ �ϸ� Icon�� �ٽ� �׷�����...
	case WM_CAPTURECHANGED:
		InvalidateRect(hwnd, &rc, TRUE);
		return 0;

	case WM_LBUTTONUP:
		if( GetCapture() == hwnd )
			ReleaseCapture();
		return 0;

	case WM_RBUTTONDOWN:
		return 0;
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
	//------------------------------------------------------------------
	wc.hbrBackground		= (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	//-----------------------------------------------------------------
	wc.hCursor				= LoadCursor(0, IDC_ARROW);
	wc.hIcon				= LoadIcon(0, IDI_APPLICATION);
	wc.hInstance			= hInstance;
	wc.lpfnWndProc			= WndProc;			// DefWindowProc;
	wc.lpszClassName		= "Finder";
	wc.lpszMenuName			= 0;
	wc.style				= 0;

	// 2. ���(������Ʈ����)
	RegisterClass(&wc);

	// 3. ������ â ����� 
	HWND hwnd = CreateWindowEx( 0,					// WS_EX_TOPMOST
				 "Finder",				// Ŭ���� ��
				 "Finder",				// ĸ�ǹ� ����
				 //--------------------------------------------------------------
				 WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~ WS_MAXIMIZEBOX , 
				 100 , 100, 300, 300,	// �ʱ� ��ġ 
				 //----------------------------------------------------------------
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