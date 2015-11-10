//handler.cpp
#include "std.h"

int OnCreate(LPARAM lParam)
{
	LPCREATESTRUCT p  = LPCREATESTRUCT(lParam);
	hInst			  = p->hInstance;
	return 0;
}

int OnContextMenu(HWND hwnd, LPARAM lParam)
{
//	ui_TrackMenu(  );
	HMENU hMenu		= LoadMenu(hInst, MAKEINTRESOURCE(IDR_MENU1));	
	HMENU hSubMenu  = GetSubMenu(hMenu, 1);
//		POINTS pt		= MAKEPOINTS(lParam);	// Ŭ���̾�Ʈ..
	POINT  pt      = { LOWORD(lParam), HIWORD(lParam) };
//		ClientToScreen(hwnd, &pt);
		// ��ũ�� ��ǥ...
	TrackPopupMenu(hSubMenu, TPM_LEFTBUTTON, pt.x, pt.y, 0, hwnd, 0);
		return 0;
}