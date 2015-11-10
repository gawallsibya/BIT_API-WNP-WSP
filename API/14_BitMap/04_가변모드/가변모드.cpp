// �������..

#include <windows.h>

LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch( msg )
	{
	case WM_PAINT:
		{
			PAINTSTRUCT ps;

			HDC hdc = BeginPaint(hwnd, &ps);
			// ���� ��� ����
			SetMapMode(hdc, MM_ISOTROPIC);	// ���� ���� ����...MM_ANISOTROPIC
//			SetMapMode(hdc, MM_LOENGLISH);	// ��� ���� ���.. MM_ISOTROPIC


			// ���� Ŭ���̾�Ʈ�� ũ�� 
			RECT r;
			GetClientRect(hwnd, &r);
			int cx = r.right	- r.left;	// ��
			int cy = r.bottom	- r.top;	// ����

			// �� ��ǥ�� ũ�� ����( �������� ������ 100, 100���� ����)
			// �� ��ǥ : Window��� �θ� 
			//             �� ��ǥ�� ���Ǵ� ǥ��(���������� �׷��� ���)
			SetWindowExtEx(hdc, 100, 100, 0);

			// ������ǥ�� ũ��� Ŭ���̾�Ʈ�� ũ��� ����.
			// ���� ��ǥ : viewport��� �θ�
			//             ���� ���̴� ��ǥ ���� 
			SetViewportExtEx(hdc, cx, cy, 0);

			Rectangle(hdc, 10, 10, 90, 90 );
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
	wc.hIcon				= LoadIcon(0, IDI_APPLICATION);
	wc.hInstance			= hInstance;
	wc.lpfnWndProc			= WndProc;			// DefWindowProc;
	wc.lpszClassName		= "First";
	wc.lpszMenuName			= 0;
	wc.style				= CS_HREDRAW | CS_VREDRAW;

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