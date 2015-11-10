// Bitmap  
/*
������� �����ϴ� ��Ʈ�� ����
1. DDB  : Device Dependent Bitmap
   - ������ �������� : �̹��� ũ��� ����, �̹��� ������, (���� 3.0 �������� ���)

2. DIB  : Device Independent Bitmap
   - ��ġ�� ������( Ȯ���� BMP) �� ���⿡ �ش� 
   -> Win32ȯ�濡�� �Ϲ������� ���
   - ���� ���̺�, �ػ� ����... ���� �߰� ������ �ֽ�

  => ȣȯ ���鿡�� DDB ���, DC�� ���õ� �� �ִ� ��Ʈ���� DDB
     DIB�� ���� DC�� ���õ� �� ����..
*/

//------------------------------------------------------
// Bitmap Object�� �Ϲ� DC�� ���õ� �� ����.
// MemoryDC���� Bitmap Object�� ������ �� �ִ�.

//  DDB ==(SelectObject)==> MemoryDC ==(BitBlt)==>Client DC ==> ȭ�� ���

//-------------------------------------------------------

#include <windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HINSTANCE	hInst;
	static HBITMAP		hBitmap;
	static BITMAP		bm;			// DDB ���..

	switch( msg )
	{
	case WM_CREATE:
		hInst = ( ( LPCREATESTRUCT)lParam)->hInstance;

		//1. Bitmap �ε�
		// ���ҽ��� �ۼ��Ǵ� ��Ʈ���� DIB�̹�����
		// LoadBitmap �Լ��� ���� ȣȯ�Ǵ� DDB�� ��ȯ��
		// ���� �޸� DC�� �����Ͽ� ��ٷ� ��� ����..
		hBitmap	= LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1));

		//2. DDB Bitmap ��� ���
		GetObject(hBitmap, sizeof(bm), &bm);
		return 0;

	case WM_LBUTTONDOWN:
		{
			HDC hdc		= GetDC(hwnd);

			// ȭ�� DC�� ȣȯ(���ϻ���)�Ǵ� �޸� DC�� ����..
			HDC memDC	= CreateCompatibleDC(hdc);		

			// �޸� DC�� ��Ʈ�� ����
			SelectObject(memDC, hBitmap);

			// ��Ʈ���������
			TextOut(memDC, 5, 5, "hello", 5);

			// �޸� DC --> ȭ�� DC//
			POINTS pt = MAKEPOINTS(lParam);
			BitBlt(hdc, pt.x, pt.y, bm.bmWidth, bm.bmHeight, 
				memDC, 0, 0, SRCCOPY);

			// �޸� ����
			DeleteDC(memDC);
			ReleaseDC(hwnd, hdc);
		}

		return 0;
	case WM_RBUTTONDOWN:
		//--------------------------------
		DeleteObject(hBitmap);
		//-----------------------------------
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
	
	HBITMAP hBitmap = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP1));

	// BItmap���� �귯�� ����  // CreateSolidBrush, CreateHatchBrush..
	HBRUSH brush   = CreatePatternBrush(hBitmap);

//	wc.hbrBackground		= (HBRUSH)brush;
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