#include <windows.h>		
#include "resource.h"		
#include <CommCtrl.h>
#pragma comment(lib, "ComCtl32.lib")

// Dialog���� ���� ��� ���� ����ü
struct DATA
{
	int cx;			int cy;			int weight;
};


//------------------------------------
HWND g_hDlg; // Dialog �� �ڵ�
#define WM_APPLY	WM_USER + 100
//------------------------------------


////////////////////////////////////////////////////////////////////////
// Dialog Box Procedure..
// ���Լ��� ��¥ �޼��� �Լ��� �ƴϴ�. ��¥ �޼��� �Լ��� user32.dll��
// �ִ� DefDlgProc�̴�. DefDlgProc�� �ٽ� �Ʒ� �Լ��� ȣ���ϴ� ���̴�.
BOOL CALLBACK DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HWND hHorz;		
	static HWND hVert;		
	static HWND hSlider;
	static DATA* pData;
	switch(msg)
	{
	// Dialog�� ó�� ��Ÿ���� �߻�. �� ��Ʈ���� �ʱ�ȭ �Ѵ�.
	case WM_INITDIALOG:
		{
			pData = (DATA*)lParam;
			// pData�� ������ Dialog�� �ʱ�ȭ �Ѵ�.
			SetDlgItemInt( hDlg, IDC_EDIT_HORZ, pData->cx, FALSE);
			SetDlgItemInt( hDlg, IDC_EDIT_VERT, pData->cy, FALSE);
			// �� Control�� �ʱ�ȭ �Ѵ�.
			hHorz = GetDlgItem(hDlg, IDC_SPIN_HORZ);
			hVert = GetDlgItem(hDlg, IDC_SPIN_VERT);
			hSlider = GetDlgItem(hDlg, IDC_SLIDER_WEIGHT);
			// �� Control�� �޼��� ����.
			SendMessage( hHorz, UDM_SETRANGE32, 0, 300);
			SendMessage( hVert, UDM_SETRANGE32, 0, 300);

			SendMessage( hSlider, TBM_SETRANGE, TRUE, MAKELONG(0,8));
			SendMessage( hSlider, TBM_SETPOS, TRUE,pData->weight);
		}
		break;
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDOK: // ����(Apply)
			{
				// Control�� ���� �о pData�� �ִ´�.
				BOOL b;
				pData->cx = GetDlgItemInt(hDlg, IDC_EDIT_HORZ, &b, 0);
				pData->cy = GetDlgItemInt(hDlg, IDC_EDIT_VERT, &b, 0);
				pData->weight = SendMessage( hSlider, TBM_GETPOS,0,0);
				// �θ𿡰� �޼��� ����.
				SendMessage( GetParent( g_hDlg), WM_APPLY, 0, 0);
			}
			return TRUE;
		case IDCANCEL:
			DestroyWindow( g_hDlg );
			g_hDlg = 0; // �ٽ� ����� ���� �ֵ���,
			return TRUE;
		}
	}
	return FALSE; // �޼��� ó���� ���Ѱ��..
}
/////////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HINSTANCE s_hInst;
	static int s_nWeight;	
	static int s_cx, s_cy;	// block ��
	static DATA data;
	switch(msg)
	{
	//-----------------------------------------------
	// ��޸��� ���̾�αװ�...
	// SendMessage(�θ�������, WM_APPLY, 0, 0)

	case WM_APPLY: // Dialog�� ������ �޼���
		{
			s_cx = data.cx;
			s_cy = data.cy;
			s_nWeight = data.weight;

			InvalidateRect(hwnd, 0, TRUE);
		}
		return 0;
	//-------------------------------------------------
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDM_OPTION_SETTING:
			{
				// Dialog�� ��Ÿ���� ���� ����ü�� �ʱ�ȭ.
				data.cx = s_cx;	data.cy = s_cy;
				data.weight = s_nWeight;
				if ( g_hDlg == 0)
				{
					// ��޸��� �����.
					g_hDlg = CreateDialogParam( s_hInst,// hinstance
										MAKEINTRESOURCE(IDD_SETTING),
						hwnd,		// �θ�
						DlgProc, // �޼��� �Լ�.
						(LPARAM)&data); // WM_INITDIALOG�� lParam
										// �� ���޵ȴ�.

					// ���� ȣ���� ��� ���̾�α�...
					ShowWindow( g_hDlg, SW_SHOW );
				}
				else
					SetFocus( g_hDlg );//�̹� ������� ��� focus�̵�
			}
		}
		return 0;
/////////////////////////////////////////////////////////////////////////////////
	case WM_CREATE:
		InitCommonControls(); // ���� Control �ʱ�ȭ...
		s_hInst = ((LPCREATESTRUCT)lParam)->hInstance;

		s_nWeight = 0; // 0 ~ 8 �� 0: ����. 8 : �Ͼ��.
		s_cx = 8;
		s_cy = 8;
		return 0;

	// Draw s_cx * s_cy Grid.... color s_nWeight :0 -> black / s_nWeight : 8 -> white
	case WM_PAINT:
		{ 
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);
			RECT r;			GetClientRect(hwnd, &r);
			int nShade = s_nWeight * 32;
			if (nShade != 0) nShade--; // ??
			HPEN hPen = CreatePen(PS_SOLID, 1, RGB(nShade, nShade, nShade));
			HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
			int x;
			for (int i = 1; i < s_cx ; i++)
			{
				x = (r.right *i) / s_cx;			MoveToEx(hdc, x,0, NULL);
				LineTo(hdc, x, r.bottom );
			}
			int y;
			for (i = 1; i < s_cy ; i++)
			{
				y = (r.bottom * i) / s_cy;			MoveToEx(hdc, 0,y, NULL);
				LineTo(hdc, r.right , y);
			}
			DeleteObject( SelectObject(hdc, hOldPen));
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
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MAINFRAME);
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
	// ��޸��� Dialog �� �������� �޼��� Loop
	while( GetMessage(&msg, 0, 0, 0) )
	{
		// Dialog �� ��Ÿ�� �������� ȣ��ǰ� �Ѵ�.
		if ( ! IsWindow( g_hDlg ) || ! IsDialogMessage( g_hDlg, &msg))
		{
			TranslateMessage(&msg);		DispatchMessage(&msg);
		}
	}
	return msg.wParam;
}

