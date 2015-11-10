#pragma comment(linker, "/subsystem:windows")

#include <windows.h>

// control���� ID��...
#define IDC_BUTTON	1
#define IDC_EDIT	2
#define IDC_LISTBOX	3
//----------------------------------------

LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HWND hBtn,  hEdit, hListBox;

	static HBRUSH hBrush = CreateSolidBrush( RGB(255,255,0));

	switch( msg )
	{	
	// EditBox�� �ڽ��� �׷����� ���� �θ𿡰� �Ʒ� �޼����� �����Ѵ�.
	case WM_CTLCOLOREDIT:
		{
			HDC hdc = (HDC)wParam; // Edit �� ����� dc
			HWND h  = (HWND)lParam;

			if ( h == hEdit )
			{
				SetTextColor( hdc, RGB(0,0,255));
				SetBkColor  ( hdc, RGB(255,255,0));
			}
		}
		// ������ �������� ���� EditBox�� ��� ����Ʈ ������ ����ǰ� �ϱ� ����
		// �Ʒ��� �����Ѵ�.
		return DefWindowProc( hwnd, msg, wParam, lParam);




	// �ڽ� control ���� ������ �޼���
	case WM_COMMAND:
		switch( LOWORD(wParam) ) // ID ����.
		{
		case IDC_EDIT:		// EditBox �� �������
			if ( HIWORD(wParam) == EN_CHANGE ) //���� �ڵ� ����.
			{
				char s[256];
				GetWindowText( hEdit, s, 256); // Edit ���� ���� ��´�.

				SetWindowText( hwnd, s); // �θ� �������� ĸ���� �����Ѵ�.
			}
			break;

		case IDC_BUTTON:
			if ( HIWORD( wParam) == BN_CLICKED ) // ��ư�� ������ ������ ���� �ڵ� 
			{
				MessageBox( hwnd, "Click", "", MB_OK);
			}
			break;
		}
		return 0;







	case WM_CREATE:
		
		hBtn = CreateWindow( "button", "Push", 
							WS_CHILD | WS_VISIBLE | WS_BORDER | BS_AUTOCHECKBOX,
							
							10,10,90,90, hwnd, (HMENU)IDC_BUTTON, 0,0);


		hEdit = CreateWindow( "Edit", "", 
							WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE |
							WS_HSCROLL | WS_VSCROLL,

							110,10,90,90, hwnd, (HMENU)IDC_EDIT, 0,0);

		hListBox = CreateWindow( "listbox", "", 
							WS_CHILD | WS_VISIBLE | WS_BORDER,
							210,10,90,90, hwnd, (HMENU)IDC_LISTBOX, 0,0);
		
		// Edit�� �Է� �޴� ���� ������ �����Ѵ�.- �޼����� ������.
	//	SendMessage( hEdit, EM_LIMITTEXT, 5, 0);

		SendMessage( hEdit, EM_SETMARGINS, EC_LEFTMARGIN | EC_RIGHTMARGIN,
											MAKELONG( 10,10));
		// ListBox �� �׸��� �߰��Ѵ�.
		SendMessage( hListBox, LB_ADDSTRING, 0, (LPARAM)"AAAA");
		SendMessage( hListBox, LB_ADDSTRING, 0, (LPARAM)"�ѱ�");

			
		return 0;




	case WM_DESTROY:
		PostQuitMessage(0); 
		return 0;
	}
	return DefWindowProc( hwnd, msg, wParam, lParam);
}

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
					LPSTR	  lpCmdLine, int nShowCmd )
{
	ATOM atom;
	WNDCLASS wc;
	HWND hwnd;
	MSG msg;
	
	wc.cbClsExtra	= 0;
	wc.cbWndExtra	= 0;
	wc.hbrBackground= (HBRUSH)GetStockObject( WHITE_BRUSH ); 
	wc.hCursor		= LoadCursor( 0, IDC_ARROW );
	wc.hIcon		= LoadIcon( 0, IDI_APPLICATION);
	wc.hInstance	= hInstance;
	wc.lpfnWndProc  = WndProc; 
	wc.lpszClassName= "First";
	wc.lpszMenuName = 0;
	wc.style		= 0;

	atom = RegisterClass( &wc);
	
	if ( atom == 0 ) 
	{
		MessageBox( 0, "Fail To RegisterClass", "Error", MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx( 0, "first", "Hello", WS_OVERLAPPEDWINDOW,
								CW_USEDEFAULT, 0, CW_USEDEFAULT,
								0, 0, 0, 
								hInstance, 0); 
	ShowWindow( hwnd, nShowCmd); 
	UpdateWindow( hwnd );

	while ( GetMessage( &msg, 0, 0, 0) ) 
	{							
		TranslateMessage(&msg);
		DispatchMessage( &msg);
	}

	return 0;
}

