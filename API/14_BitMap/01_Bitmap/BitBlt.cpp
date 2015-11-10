//----------------------------------------------------------------------
// ���ȭ���� ��Ÿ���� DC ���� �������� ClientDC�� �ȼ��� �����ϴ� ����
//  - BitBlt
//    BitBlt �Լ����� ���� �߿��� ���� 2���� DC�� �ݵ�� 
//    ȣȯ(Compatible, �����(plane)�� �ȼ��� ��Ʈ(bpp)�� ���� )�Ǿ�� �Ѵ�.
//----------------------------------------------------------------------

#include <windows.h>


LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch( msg )
	{

	case WM_PAINT:
	{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);
			SelectObject(hdc, GetStockObject(BLACK_BRUSH));
			Ellipse(hdc, 150, 150, 300, 300);
			SelectObject(hdc, GetStockObject(WHITE_BRUSH));
			EndPaint(hwnd, &ps);
	}

	return 0;

	case WM_LBUTTONDOWN:
		{
			// Ŭ���̾�Ʈ ������ ���� DC 
			HDC		hdc		= GetDC(hwnd);

//			HDC		hdc     = GetDC(0);	// ��üȭ��..

			// ����ȭ�� : �����..DC
			HDC		scrDC	= CreateDC("DISPLAY", 0, 0, 0);	// ����ȭ��..

// �ϳ��� DC�� �ִ� ��Ʈ���� �ٸ� DC�� �����ϴ� ��Ʈ�� �����Լ�..
// �� �� �� DC�� ȣȯ�Ǿ�� �ϳ� ���� ���� ������ ȣȯ���� ���� 
// ��� BitBlt�� ������� ���� ������ ����ó�� ���信 �°� ����..
	BitBlt(hdc, 0, 0, 500, 500,   // Dest dc,  x, y, w, h
			scrDC, 0, 0,		  // sorce dc, x, y
//			0x00DD0228);  //  S | ~ D (��������� �� | ~ ����Ǵ� ���� ��)
		    SRCPAINT);	  //  S | D										

	ReleaseDC(hwnd, hdc);
	DeleteDC(scrDC);
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
//	while( GetMessage( &msg, 0, 0, 0 ) )
//	{
//		TranslateMessage(&msg);
//		DispatchMessage(&msg);
//	}
	
	while(1)
	{
		if( PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			if( msg.message == WM_QUIT)
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			/*
			HDC scrDC		= CreateDC("DISPLAY", 0, 0, 0);
			SetTextColor(scrDC, RGB(rand()%255, rand()%255, rand()%255));
			SetBkMode(scrDC, TRANSPARENT);

			HFONT font = CreateFont(rand()%50, 0, rand()%100, 0, 0, 0, 0, 0,
					HANGEUL_CHARSET, 3, 2, 1,
					VARIABLE_PITCH | FF_ROMAN, "����ü");
			HFONT oldfont = (HFONT)SelectObject(scrDC, font);
			TextOut(scrDC, rand()%1024, rand()%768, "��������", 8);
			Sleep(500);

			SelectObject(scrDC, oldfont);
			DeleteObject(font);
			DeleteObject(scrDC);
			*/
		}
	
	}
	return 0;
}


































