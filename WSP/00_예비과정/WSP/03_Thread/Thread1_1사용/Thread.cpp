// Thread
#include <windows.h>

HWND  MainWnd;

// Thread �Լ�
DWORD WINAPI ThreadFunc1( LPVOID temp)
{
	HDC	hdc;
	BYTE Blue;
	HBRUSH hBrush, hOldBrush;

	HWND h = (HWND)temp;

	hdc = GetDC(h);
	while(1)
	{
		Blue++;
		Sleep(1);
		hBrush		= CreateSolidBrush(RGB(0, 0, Blue));
		hOldBrush	= (HBRUSH)SelectObject(hdc, hBrush);
		Rectangle(hdc, 100, 100, 300, 400);
		
		SelectObject(hdc, hOldBrush);
		DeleteObject(hBrush);
	}
	ReleaseDC(h, hdc);
	return 0;
}

LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HANDLE hThread;
	static DWORD  ThreadID;
	switch( msg )
	{
	case WM_LBUTTONDOWN:
		{
			hThread = CreateThread(NULL, 0, ThreadFunc1, hwnd, 0, &ThreadID); // 2
			CloseHandle(hThread);		// use count : 1
		}
		return 0;
	case WM_RBUTTONDOWN:
		{
			HDC hdc = GetDC(hwnd);
			Ellipse(hdc, LOWORD(lParam), HIWORD(lParam), LOWORD(lParam)+20, 
						HIWORD(lParam)+20);
			ReleaseDC(hwnd, hdc);
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


	MainWnd = hwnd;

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