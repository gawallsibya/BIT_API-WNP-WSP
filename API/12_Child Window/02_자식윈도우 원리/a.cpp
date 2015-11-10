#pragma comment(linker, "/subsystem:windows")

#include <windows.h>
void Draw3dRect(HDC hdc, int x, int y, int xx, int yy, 
					BOOL down, int width )
{
	COLORREF clrMain  = RGB(192,192,192),
				clrLight = RGB(255,255,255), 
				clrDark  = RGB(128,128,128);

	HPEN hPen1, hPen2, hOldPen;
	HBRUSH hBrush, hOldBrush;     

	if(down)    
	{
		hPen2 = CreatePen(PS_SOLID,1,clrLight);
		hPen1 = CreatePen(PS_SOLID,1,clrDark);
	} 
	else 
	{
		hPen1 = CreatePen(PS_SOLID,1,clrLight);
		hPen2 = CreatePen(PS_SOLID,1,clrDark);
	}  
	hBrush =  CreateSolidBrush( clrMain );
	hOldPen = (HPEN)SelectObject(hdc, hPen1);
	hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);  

	Rectangle(hdc, x , y, xx+1, yy+1);  

	for(int i=0; i < width; i++)
	{
		SelectObject(hdc, hPen1);

		MoveToEx(hdc, xx - 1, y, 0 );
		LineTo(hdc, x, y);
		LineTo(hdc, x, yy - 1 );  

		SelectObject(hdc, hPen2);

		MoveToEx(hdc, x, yy,0);
		LineTo(hdc, xx, yy);
		LineTo(hdc, xx, y);  

		x++; y++; xx--; yy--;
	} 
	SelectObject(hdc, hOldPen);
	SelectObject(hdc, hOldBrush);

	DeleteObject(hPen1); 
	DeleteObject(hPen2); 
	DeleteObject(hBrush);
} 

// �ڽ�(��ư)�� �θ𿡰� WM_COMMAND�� ������ ����� �����ڵ�(�޼����� ������ ����)
#define BTN_LCLICK	1
#define BTN_RCLICK	2
#define BTN_LDBLCLK	3
#define BTN_RDBLCLK	4

// �θ� �ڽ�(��ư)�� ����� ���� �ڽĿ��� ������ �ִ� �޼����� �����Ѵ�.
// �θ� - �ڽ� ���� ���.
#define BM_CHANGESTYLE	WM_USER + 10
#define BM_CHANGETHICK  WM_USER + 11

//========================================================================
// �ڽĿ� �޼��� ó�� �Լ�.
LRESULT CALLBACK ChildProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static BOOL bDown = FALSE;
	static int  nThick = 2;

	switch( msg )
	{	

	// �θ� ������ �޼���
	case BM_CHANGETHICK:
		nThick = (int)wParam;  // wParam�� �β��� �����ֱ�� ���...
		InvalidateRect( hwnd, 0, FALSE);
		return 0;




	case WM_LBUTTONDOWN:
		bDown = TRUE;  InvalidateRect( hwnd, 0, FALSE );
		SetCapture( hwnd );
		return 0;

	case WM_LBUTTONUP:
		if ( GetCapture() == hwnd )
		{
			ReleaseCapture();
			bDown = FALSE; 
			InvalidateRect( hwnd, 0, FALSE );

			//========================================
			// �ڽ��� �������� �θ𿡰� �˷��ش�.
			HWND hParent = GetParent( hwnd );
			UINT id      = GetDlgCtrlID( hwnd );

			SendMessage( hParent,  WM_COMMAND, 
						MAKELONG(id, BTN_LCLICK),// ����16:id, ����16:�����ڵ�
						(LPARAM)hwnd);
		}
		return 0;




	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint( hwnd, &ps );
			// �ڽ��� hdc �� ��� �ڽ��� �׸��� ���� �θ𿡰� hdc �� �������ش�.
			// �θ� �ڽ��� ������ ������ ������ �ֱ� ���ؼ�..
			// �̷� �뵵�� �̸� ������� �޼����� WM_CTLCOLORxxx �̴�.

			// wParam ���� hdc �� lParam ���� �ڽ��� �ڵ��� �־� �ش�.
			HWND hParent = GetParent( hwnd );

			SendMessage( hParent, WM_CTLCOLORBTN, (WPARAM)hdc, (LPARAM)hwnd);

			//========================================================



			RECT rc;
			GetClientRect( hwnd, &rc);

			Draw3dRect( hdc, 0, 0, rc.right, rc.bottom, bDown, nThick );
			
			// �θ� ������ ĸ�� ���ڿ��� ������ ��� ����Ѵ�
			char s[256];
			GetWindowText( hwnd, s, 256 );

			SetBkMode( hdc, TRANSPARENT );
			
			if ( bDown == TRUE )
				OffsetRect( &rc, nThick, nThick ); // ������ �Ʒ��� �簢����
												// nThick ��ŭ �̵�

			DrawText( hdc, s, -1, &rc, 
							DT_SINGLELINE | DT_CENTER | DT_VCENTER );
			//-----------------------------------------------------





			EndPaint( hwnd, &ps );
		}
		return 0;
			// user.chol.com/~downboard/mine.txt ���� Draw3dRect() ������ ������
	}
	return DefWindowProc( hwnd, msg, wParam, lParam);
}
		















//============================================================================
// �θ�� �޼��� ó���Լ�.
LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HWND hChild;

	switch( msg )
	{	
	// �ڽ��� �ڽ��� �׸��� ���� ������ �޼��� - �θ𿡰� ���� ������ ��ȸ�� �ش�.
	case WM_CTLCOLORBTN:
		{
			HDC hdc = (HDC)wParam;
			HWND h  = (HWND)lParam;

			if ( hChild == h )  // �ڽ��� 2�� �̻��̶�� ���� ���ϴ� �ڽ����� Ȯ��
			{
				SetTextColor( hdc, RGB(255,0,0));
			}
		}
		return 0;






	case WM_LBUTTONDOWN:
		{
			static int n = 2;
			++n;

			// �ڽĿ��� �޼����� ������ �β��� �����ϰ� �Ѵ�
			// wParam : ������ �β�,   lParam : not used 
			SendMessage( hChild, BM_CHANGETHICK, n, 0);
		}
		return 0;



	// �ڽ�(��ư)�� ������ �޼���
	case WM_COMMAND:
		switch( LOWORD(wParam) ) // �ڽ� ID
		{
		case 1:
			if ( HIWORD(wParam) == BTN_LCLICK ) // �����ڵ� ����
			{
				MessageBox( hwnd, "Click!!", "", MB_OK);
			}
			break;
		}
		return 0;








	case WM_CREATE:

		hChild = CreateWindow( "CHILD", "�ڽ�", 
							WS_CHILD | WS_VISIBLE | WS_BORDER,
							10, 10, 100, 100,
							hwnd,	// �θ� ������ �ڵ�
							(HMENU)1, // �ڽ��� �޴��� ������ ����. ID�� ���
							0, 0);
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

	atom = RegisterClass( &wc); // �θ�� ������ Ŭ���� ���

	//========================================
	wc.lpfnWndProc = ChildProc;
	wc.lpszClassName = "CHILD";

	RegisterClass( &wc ); // �ڽĿ� ������ Ŭ���� ���
	//=========================================
	

	hwnd = CreateWindowEx( 0, "first", "Hello", WS_OVERLAPPEDWINDOW,
								CW_USEDEFAULT, 0, CW_USEDEFAULT,0, 0, 0, 
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

