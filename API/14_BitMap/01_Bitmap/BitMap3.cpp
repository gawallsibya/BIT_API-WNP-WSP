
// Bitmap.. 
// < ���� ȭ�� >
//  ȭ��� ������ ������ ������ �ʴ� ȭ�� 
//  - ���� ȭ�鿡 �׸��� �׸��� ���� ȭ�鿡 ��� ����(BitBlt)��
//    �Ѵ�.
//  - ��� ���� ? ������ ȿ�� ���� ��....

#include <windows.h>
#include <vector>
using namespace std;

LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HINSTANCE	hInst;
	static vector<POINTS> buffer;

	//------------------------------------
	static HBITMAP		hBitmap;
	//------------------------------------
	switch( msg )
	{
	case WM_CREATE:

		hInst =  ( ( LPCREATESTRUCT)lParam)->hInstance;
		{
			HDC		hdc = GetDC(hwnd);
			// ȭ�� DC�� ȣȯ�Ǵ� ��Ʈ�� ����..
			// CreateBitmap : ���
			hBitmap     = CreateCompatibleBitmap(hdc, 1024, 768);

			// ��Ʈ�� �ʱ�ȭ..
			HDC memDC	= CreateCompatibleDC(hdc);
			HBITMAP old = (HBITMAP)SelectObject(memDC, hBitmap);

			RECT r = { 0, 0, 1024, 768 };
			FillRect(memDC, &r, (HBRUSH)GetStockObject(WHITE_BRUSH));

			SelectObject(memDC, old);
			DeleteObject(memDC);
			ReleaseDC(hwnd, hdc);
		}

		return 0;

	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);

			HDC memDC = CreateCompatibleDC(hdc);
			HBITMAP old = (HBITMAP)SelectObject(memDC, hBitmap);
			BitBlt(hdc, 0, 0, 1024, 768, memDC, 0, 0, SRCCOPY);
			SelectObject(memDC, old);
			DeleteDC(memDC);
			EndPaint(hwnd, &ps);
		}
		return 0;

	// client ������ ������ �� �޼���...
	// �� �޽����� DefwinProc�� ���޵Ǹ� ȭ���� ��������.
	case WM_ERASEBKGND:			return 0;

	case WM_LBUTTONDOWN:
		{
			POINTS pt = MAKEPOINTS(lParam);
			HDC hdc   = GetDC(hwnd);
			Rectangle(hdc, pt.x, pt.y, pt.x+50, pt.y+50);

			// ��Ʈ�ʿ� ������ �׸��� �׸� �� �ִ�..
			HDC memDC	 = CreateCompatibleDC(hdc);
			HBITMAP old  = (HBITMAP)SelectObject(memDC, hBitmap);

			Rectangle(memDC, pt.x, pt.y, pt.x+50, pt.y+50);

			SelectObject(memDC, old);

			DeleteDC(memDC);
			ReleaseDC(hwnd, hdc);
//			buffer.push_back(pt);
		}
		return 0;
/*
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);
			for( int i=0; i< buffer.size(); i++)
			{
				Rectangle(hdc, buffer[i].x, buffer[i].y, buffer[i].x+50,
							buffer[i].y+50);
			}
			EndPaint(hwnd, &ps);
		}
		return 0;
*/
	case WM_RBUTTONDOWN:
		return 0;
	case WM_DESTROY:
		//-----------------------------------
		DeleteObject(hBitmap);
		//-----------------------------------
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
