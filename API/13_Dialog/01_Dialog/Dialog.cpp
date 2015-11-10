#pragma comment(linker, "/subsystem:windows")

#include <windows.h>
#include "resource.h"

// DialogBoxParam() �� ����ϱ� ���ؼ��� ����ü�� �ʿ��ϴ�.
typedef struct _DLGDATA
{
	int x;
	int y;
} DLGDATA, *PDLGDATA;


// ����ڰ� ����� ���̾�α� �޼��� ó�� �Լ�
BOOL CALLBACK DlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static DLGDATA* pData;
	switch( msg )
	{
	case WM_INITDIALOG: // Dialog �� ��Ÿ���� ������ �޼���
		pData = (DLGDATA*)lParam; // DialogBoxParam()�� ������ ����

		// ����ü�� �������� control�� �ʱ�ȭ �Ѵ�
		SetDlgItemInt( hDlg, IDC_EDIT1, pData->x, 0);
		SetDlgItemInt( hDlg, IDC_EDIT2, pData->y, 0);
		return TRUE;

	case WM_COMMAND:    // ��ư(�ڽ�)�� ������ ó��
		switch( LOWORD( wParam ) )
		{
		case IDOK:
			{
				BOOL b;
				// Control �� -> ����ü��..!!
				pData->x = GetDlgItemInt( hDlg, IDC_EDIT1, &b, 0);
				pData->y = GetDlgItemInt( hDlg, IDC_EDIT2, &b, 0);

				EndDialog( hDlg, IDOK);
			}
			break;

		/*
		case IDOK:   
			{
				char s[256];

				// ID  -> HWND�� ��´�.
				HWND hEdit = GetDlgItem( hDlg, IDC_EDIT1 );
				GetWindowText( hEdit, s, 256 );

				// �� 2�ٴ�� �Ʒ� ���ٷε� ����
				// GetDlgItemText( hDlg, IDC_EDIT1, s, 256);
				
				MessageBox( 0, s, "", MB_OK);

				EndDialog( hDlg, IDOK );   
			}
			break;
			*/


		case IDCANCEL:EndDialog( hDlg, IDCANCEL); break;
		}
		return TRUE;
	}
	return FALSE; // �޼����� ó������ ���� ���.
}



LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static int xPos = 0, yPos = 0;
	switch( msg )
	{	
	case WM_LBUTTONDOWN: 
		{
			// DialogBox�� ��Ÿ�������� ����ü�� �����ؼ� static ���������� �ʱ�ȭ 
			DLGDATA data;
			data.x = xPos;
			data.y = yPos;

			// ��� ���̾�α� ��Ÿ����.
			UINT ret = DialogBoxParam( GetModuleHandle( 0 ), // hInstance
								MAKEINTRESOURCE(IDD_DIALOG1), // ���ҽ� ID
								hwnd,		// ������ �ڵ�.
								DlgProc,    // ���̾�α� ���ν���.
								(LPARAM)&data); 
							// WM_INITDIALOG�� lParam���� ����

			if ( ret == IDOK)
			{
				// Dialog�� �Է��� ���� ����ü�� �ִ�.
				// Static ������ �Ű� ��� ��ȿȭ
				xPos = data.x;
				yPos = data.y;
				InvalidateRect( hwnd, 0, TRUE);
			}
		}
		return 0;

	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint( hwnd, &ps );
			char s[256];
			wsprintf( s, "%d, %d", xPos, yPos );

			TextOut( hdc, 10, 10, s, strlen(s) );
			EndPaint( hwnd, &ps );
		}
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


// API ���� : 26��.  34��, 36��, 54��-- �⺻
//           39~45 : ���� �߿�  
//           49, 51: �� ����� ����(�ð��� �ٷ��� ���Ҽ��� ����)




















