// �簢�� �׸���
#include <windows.h>



LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static bx, by, ex, ey, progx, progy;
	static isdraw = false;
	switch( msg )
	{
	case WM_LBUTTONDOWN:
		isdraw = true;
		bx = LOWORD(lParam);
		by = HIWORD(lParam);
		progx = bx;
		progy = by;
		return 0;
		
		case WM_MOUSEMOVE:
		{
			HDC hdc;
			hdc= GetDC(hwnd);
			if(isdraw)
			{
				//-------------------------------------------
				int nx, ny;
				nx = LOWORD(lParam); 
				ny = HIWORD(lParam);
				SetROP2(hdc,R2_NOTXORPEN);
				SelectObject(hdc,GetStockObject(NULL_BRUSH));            
				Rectangle(hdc, bx, by, progx, progy);
				Rectangle(hdc, bx, by, nx, ny);
				progx = nx;
				progy = ny;
				//--------------------------------------------
			}
			ReleaseDC(hwnd, hdc);
		}
		return 0;
		case WM_LBUTTONUP:
			isdraw = false;

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