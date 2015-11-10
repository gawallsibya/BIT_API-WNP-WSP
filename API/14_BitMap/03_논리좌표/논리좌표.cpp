// ����ǥ

#include <windows.h>

LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch( msg )
	{
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc		 = BeginPaint(hwnd, &ps);

			Rectangle(hdc, 100, 100, 200, 200);

			// �� 1= 0.1mm(����),  y�� ���� �� )
			SetMapMode(hdc, MM_LOMETRIC);	

			Rectangle(hdc, 0, 0, 100, -100);

			EndPaint(hwnd, &ps);
		}
		return 0;


// default ���� ���� ����ǥ�� ������ǥ�� ��ġ�Ǿ� ��ȯ�� �Ͼ�� �ʴ´�...

	case WM_LBUTTONDOWN:
		{
			HDC hdc = GetDC(hwnd);
			// ������ǥ                              (Ŭ���̾�Ʈ) ��ǥ..
//			POINTS pt = MAKEPOINTS(lParam);

			POINT  pt = { LOWORD(lParam), HIWORD(lParam) };

//			SetMapMode(hdc, MM_LOMETRIC);		//0.1mm ������, ���� ����

			// ����(Ŭ���̾�Ʈ) ==> �� ��ǥ��...
			DPtoLP(hdc, &pt, 1);

			// ����ǥ�� ���޵Ǿ�� ������ ��� ����..
			Rectangle(hdc, pt.x, pt.y, pt.x+50, pt.y+50);

			// �� ==> ����
			POINT buf[10];
			DPtoLP(hdc, buf, 10);

			// �ᱹ, 2���� Point,�� �� �� �ִ�..
			RECT r = { 10, 10, 20, 20 };
			DPtoLP(hdc, (POINT*)&r, 2);




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