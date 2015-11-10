#include <windows.h>


LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HCURSOR h1 = LoadCursorFromFile("c:\\WINDOWS\\Cursors\\sizens.ani");
	static HCURSOR h2 = LoadCursorFromFile("c:\\WINDOWS\\Cursors\\sizewe.ani");

	static int cx = 350, cy = 150;
	switch( msg )
	{
	case WM_CREATE:
		MoveWindow(hwnd, 0, 0, cx, cy, TRUE);
		return 0;

	case WM_KEYDOWN:
		// ����Ű...

		// wParam �� ���� 2byte => Ű���忡�� �߻��� �޽����� �����
		// ex) VK_RIGHT �� Ű���� 48 �̶�� wParam ���� 0048�� ���� ����ȴ�.
		if ( LOWORD (wParam) == VK_RIGHT)
		{
			cx  = cx+5;

			// ������ â ����
		}
		else if( LOWORD(wParam) == VK_LEFT)
		{
			cx = cx-5;
		}
		else if( LOWORD(wParam ) == VK_UP)
		{
			cy = cy-5;
		}
		else if (LOWORD(wParam) == VK_DOWN)
		{
			cy = cy+5;
		}
		MoveWindow(hwnd, 100, 100, cx, cy, TRUE);

		return 0;











	// ���콺 �̵��� ȣ��..
	case WM_SETCURSOR:
		switch( LOWORD(lParam)) // Hit test code
		{
		case HTTOP:
		case HTBOTTOM:
			SetCursor(h1);				break;

		case HTLEFT:
		case HTRIGHT:	
			SetCursor(h2);				break;

		default:
			// �������� ��ġ�� �������� �ݵ�� DefWindowProc���� �����ϵ���
			// ó�����ش�.
			return DefWindowProc(hwnd, msg, wParam, lParam);
		}
		
	case WM_LBUTTONDOWN:
		return 0;
	case WM_RBUTTONDOWN:
		// â�� ������ ��� �����ϱ�( Get/SetWindowText)
		char szTitle[80];
		GetWindowText(hwnd, szTitle, strlen(szTitle));
		MessageBox(hwnd, szTitle, "â ����", MB_OK);

		SetWindowText(hwnd, "â ������ �����Ѵ�.");
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
	wc.hCursor				= LoadCursor(0, IDC_CROSS);
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
	ShowWindow(hwnd, nShowCmd);
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