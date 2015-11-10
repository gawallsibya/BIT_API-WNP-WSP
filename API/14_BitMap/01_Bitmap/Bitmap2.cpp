// ������ �ð�
#include <windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//-----------------------------------------------
	static HBITMAP		hBitmap;
	static SYSTEMTIME	st;
	static RECT			rc = { 0, 0, 108, 27 };
	//----------------------------------------------

	switch( msg )
	{
	case WM_NCRBUTTONUP:
		{
			HINSTANCE	hInst = GetModuleHandle(0);
			HMENU		h1	  = LoadMenu(hInst, MAKEINTRESOURCE(IDR_MENU1));

			HMENU		h2    = GetSubMenu(h1, 0);
			POINT		pt;
			GetCursorPos(&pt);		// ��ũ�� ��ǥ ���..

			// �˾� �޴�..
			int cmd    = TrackPopupMenu(h2, TPM_LEFTBUTTON | TPM_RETURNCMD, 
							pt.x, pt.y, 0, hwnd, 0);
			// �޴� ó��.. 
			if( cmd == IDM_FILE_EXIT)
				SendMessage(hwnd, WM_CLOSE, 0, 0);
			DestroyMenu(h1);
		}
		return 0;
	case WM_TIMER:
		if( wParam == 1)
		{
			GetLocalTime(&st);
			InvalidateRect(hwnd, &rc, FALSE);
		}
		return 0;

	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC	hdc		= BeginPaint(hwnd, &ps);

			HDC memDC	= CreateCompatibleDC(hdc);
			HBITMAP old = (HBITMAP)SelectObject(memDC, hBitmap);
			SetViewportOrgEx(hdc, 2, 2, 0);
			// 
			// 
			//---------------------------------------------
			int t[8] = { st.wHour / 10, st.wHour % 10, 10, 
						st.wMinute / 10, st.wMinute % 10, 10, 
						st.wSecond / 10, st.wSecond	%10 };

			for( int i=0; i< 8; ++i)		// 0
				BitBlt(hdc, i*13, 0, 13, 23, // 0, 0, 13, 23
							memDC,  t[i]*13, 0,  SRCCOPY);
			//-----------------------------------------------
											// t[0]*13,0
			SelectObject(memDC, old);
			DeleteDC(memDC);

			EndPaint(hwnd, &ps);
		}
		return 0;
	case WM_DESTROY:
		//-------------------------
		KillTimer(hwnd, 1);
		DeleteObject(hBitmap);
		//-------------------------
		PostQuitMessage(0);
		return 0;

	case WM_CREATE:
		{
		// LoadBitmap : rc�� ����...
		// LoadImage  : ���丮/���� ������ ����..
		hBitmap = (HBITMAP)LoadImage(0, ".\\resource\\Digit.bmp", IMAGE_BITMAP, 0, 0, 
									LR_LOADFROMFILE);
//		 HINSTANCE hInst = ((LPCREATESTRUCT)lParam)->hInstance;
//		hBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP2));

		SetTimer(hwnd, 1, 1000, 0);
		SendMessage(hwnd, WM_TIMER, 1,0);

		// ������ ��Ÿ�� ����..
		// Popup �� �ְ� ��� �Ӽ� ����..
		SetWindowLong(hwnd, GWL_STYLE, (LONG)WS_POPUP);
		SetWindowPos(hwnd, 0, 0, 0, 108, 27, 
			SWP_NOMOVE | SWP_NOZORDER | SWP_DRAWFRAME);
		}
		return 0;
	case WM_NCHITTEST:
		return HTCAPTION;
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
	wc.hCursor				= LoadCursor(0, IDC_ARROW);
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
