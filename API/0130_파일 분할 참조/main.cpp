//main.cpp
#include "std.h"

HINSTANCE  hInst;

LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	static COLORREF	color	= RGB(255, 0, 0);
	static RECT     rc		= { 10, 10, 200, 200 };


	switch( msg )	
	{
	case WM_CREATE:		return OnCreate(lParam);

	case WM_CONTEXTMENU: return OnContextMenu(hwnd, lParam);

	return 0;
		
	// PopUp �޴��� �������� ����...
	case WM_INITMENUPOPUP:		{
//		HMENU hMenu = GetMenu(hwnd);
		HMENU hMenu = (HMENU)wParam;
/*
		CheckMenuItem(hMenu, IDM_MENU_RED, 
				color == RGB(255, 0, 0) ? MF_CHECKED : MF_UNCHECKED);
		CheckMenuItem(hMenu, IDM_GREEN, 
				color == RGB(0, 255, 0) ? MF_CHECKED : MF_UNCHECKED);
		CheckMenuItem(hMenu, IDM_BLUE, 
				color == RGB(0, 0, 255) ? MF_CHECKED : MF_UNCHECKED);
*/
//		EnableMenuItem(hMenu, IDM_MENU_RED, 
//				color == RGB(255, 0, 0) ? MF_GRAYED : MF_ENABLED);
//		EnableMenuItem(hMenu, IDM_GREEN, 
//				color == RGB(0, 255, 0) ? MF_GRAYED : MF_ENABLED);
//		EnableMenuItem(hMenu, IDM_BLUE, 
//			color == RGB(0, 0, 255) ? MF_GRAYED : MF_ENABLED);
		}
		return 0;
		/*
	case WM_COMMAND:
		{
		switch( LOWORD(wParam))		// ID ����
		{
		case IDM_MENU_FILE_EXIT:SendMessage(hwnd, WM_CLOSE, 0, 0);	break;
		case IDM_MENU_RED:	color = RGB(255, 0, 0);			break;
		case IDM_GREEN:		color = RGB(0, 255, 0);			break;
		case IDM_BLUE:		color = RGB(0, 0, 255);			break;
		}
		InvalidateRect(hwnd, &rc, FALSE);
		}
		return 0;
		*/
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);
			HBRUSH brush = CreateSolidBrush(color);
			HBRUSH old   = (HBRUSH)SelectObject(hdc, brush);
			Rectangle(hdc, 10, 10, 200, 200);
			DeleteObject( SelectObject(hdc, old));
			EndPaint(hwnd, &ps);
		}
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
	wc.hbrBackground		= (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hCursor				= LoadCursor(0, IDC_ARROW);
	wc.hIcon				= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wc.hInstance			= hInstance;
	wc.lpfnWndProc			= WndProc;			// DefWindowProc;
	wc.lpszClassName		= "First";
	wc.lpszMenuName			= MAKEINTRESOURCE(IDR_MENU1);
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