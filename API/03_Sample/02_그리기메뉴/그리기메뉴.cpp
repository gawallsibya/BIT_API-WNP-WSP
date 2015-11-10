// �׸��� �޴�...
#include <windows.h>
#include "resource.h"

// �޴� �׸��� �׸��� �޴��� �����ϰ� Icon�� ItemData�� ����
void AddMenuIcon(HMENU hMenu, UINT id, HICON hIcon)
{
	ModifyMenu(hMenu, id, MF_BYCOMMAND | MF_OWNERDRAW, id, 0);

	MENUITEMINFO	mmi = { 0 };
	mmi.cbSize			= sizeof(mmi);
	mmi.dwItemData		= (DWORD)hIcon;
	mmi.fMask			= MIIM_DATA;		// mask ����ü�� ���� ������ �׸� ����

	// 2����  �Ķ���Ͱ� ID�� ���(TRUE: ��ġ)
	SetMenuItemInfo(hMenu, id, FALSE, &mmi);
}

// �޴��� IDM_MENU_AAA, IDM_MENU_BBB, IDM_MENU_CCC..
LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

	switch( msg )
	{
	case WM_CREATE:
		{
			// �׸��� �޴� 1�ܰ� : �޴��� �Ӽ� ����..
			HMENU  hMenu		= GetMenu(hwnd);
			HMENU hSubMenu		= GetSubMenu(hMenu, 0);

			AddMenuIcon( hSubMenu, IDM_MENU_AAA, LoadIcon(0, IDI_WINLOGO));
			AddMenuIcon( hSubMenu, IDM_MENU_BBB, LoadIcon(0, IDI_APPLICATION));
			AddMenuIcon( hSubMenu, IDM_MENU_CCC, LoadIcon(0, IDI_QUESTION));
		}
		return 0;
		
	case WM_MEASUREITEM:
		{
			// �׸��� �޴� 2�ܰ� : ũ�� ����
			PMEASUREITEMSTRUCT p = (PMEASUREITEMSTRUCT)lParam;
			p->itemWidth		 = GetSystemMetrics(SM_CYICON) *4;
			p->itemHeight		 = GetSystemMetrics(SM_CYICON);
		}
		return 0;
		
	case WM_DRAWITEM:
		{
			// �׸��� �޴� 3�ܰ� : �޴� �׸� �׸��� �׸�..
			PDRAWITEMSTRUCT p	= (PDRAWITEMSTRUCT)lParam;

			HDC hdc		= p->hDC;
			RECT rc		= p->rcItem;
			int  id		= p->itemID;
			int state   = p->itemState;

			HMENU hMenu = (HMENU)(p->hwndItem);  
			//-----------------------------------------------------
			COLORREF  color;
			if( state & ODS_SELECTED)
				color = GetSysColor(COLOR_HIGHLIGHT); // ���� û��
			else
				color = RGB(255, 255, 255);

			HBRUSH brush = CreateSolidBrush(color);
			FillRect(hdc, &rc, brush);
//			FrameRect(hdc, &rc, brush);

			DeleteObject(brush);
			SetBkMode(hdc, TRANSPARENT);  // ������ ����� �����ϰ�.
			//--------------------------------------------------------
			// �ش� �޴�Item�� itemData�� �ٷ� ���� �� �ִ�.
			HICON hIcon = (HICON)(p->itemData);	

			DrawIcon(hdc, rc.left, rc.top, hIcon);
			char str[256];
			GetMenuString(hMenu, id, str,256,  MF_BYCOMMAND);
			TextOut(hdc, rc.left + 35, rc.top + 5, str, strlen(str));
		}
		return 0;
	
	case WM_LBUTTONDOWN:
		return 0;
	case WM_RBUTTONDOWN:
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
	wc.lpszMenuName			= MAKEINTRESOURCE(IDR_MENU1);
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