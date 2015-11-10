// ������ ��Ÿ�� ����
#include <windows.h>

// ����� ������ ��ä�� ������ �����ؼ� ���� �ð��� ������ style �����ϱ�
void ModifyStyle( HWND hwnd, UINT Remove, UINT Add, BOOL bReDraw = TRUE)
{
	// 1. ���� ��Ÿ��  ��� ����	: GetWindowLong
	UINT style = GetWindowLong(hwnd, GWL_STYLE);

	// 2. style ����				: bit ����..
	style = style & ~Remove;
	style = style | Add;
	SetWindowLong( hwnd, GWL_STYLE, style);

	// 3. style ���� �� �ٽ� �׷��� ��.. : SetWindowPos
	if( bReDraw)
	{
		SetWindowPos( hwnd, 0, 0, 0, 0, 0, // z order, x, y, w, h
			SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_DRAWFRAME);
	}

}

LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch( msg )
	{
//	case WM_LBUTTONDOWN:
//		ModifyStyle( hwnd, WS_CAPTION, 0);	return 0;
//	case WM_RBUTTONDOWN:
//		ModifyStyle( hwnd, 0, WS_CAPTION);	return 0;
	
	case WM_LBUTTONDOWN:
		// ����� Icon ����..
		{
			HICON hIcon = LoadIcon(0, IDI_QUESTION);
			SetClassLong(hwnd, GCL_HICON, (LONG)hIcon);
		}
		return 0;
	case WM_RBUTTONDOWN:
		// ���� ����..
		{
//			HBRUSH	h = (HBRUSH)GetStockObject(BLACK_BRUSH);
			HBRUSH h = CreateSolidBrush(RGB(255, 0, 0));
			SetClassLong(hwnd, GCL_HBRBACKGROUND, (LONG)h);
			InvalidateRect(hwnd, 0, TRUE);

			DeleteObject(h);

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
	wc.hbrBackground		= //(HBRUSH)GetStockObject(WHITE_BRUSH);
							  (HBRUSH)CreateSolidBrush(RGB(255, 255, 0));
	\
	wc.hCursor				= LoadCursor(0, IDC_ARROW);
	wc.hIcon				= LoadIcon(0, IDI_WINLOGO);
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