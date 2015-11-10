#include <windows.h>
#include "resource.h"
#include <CommCtrl.h>

#pragma comment(lib, "ComCtl32.lib")

// DefDlgProc  => ��¥ �޽��� �Լ�(use32.dll)
// ���⼭ �Ʒ� �޽��� �ڵ鷯 ȣ���ϴ� ������..
BOOL CALLBACK DlgProc( HWND hDlg, UINT msg, WPARAM wParam,LPARAM lParam)
{
	switch( msg )
	{
	case WM_INITDIALOG:
		{
			// Diaog�� Icon �߰�
			HICON h = LoadIcon( 0, IDI_APPLICATION);
			SendMessage(hDlg, WM_SETICON, 0, (LPARAM)h);

			// Digloa�� �߾ӿ� ���
			RECT r;		
			GetWindowRect(hDlg, &r);
			int sx = GetSystemMetrics(SM_CXSCREEN);
			int sy = GetSystemMetrics(SM_CYSCREEN);

			int cx = r.right	- r.left;
			int cy = r.bottom	- r.top;

			MoveWindow(hDlg, (sx - cx) /2 , (sy - cy) / 2, cx, cy, TRUE);
		}
		break;
	case WM_COMMAND:
		switch( LOWORD( wParam ))
		{
		case IDOK:
			EndDialog(hDlg, IDOK);	return TRUE;
		case IDCANCEL:
			EndDialog(hDlg, IDCANCEL); return TRUE;
		}
	}
	return FALSE;
}


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, 
						PSTR lpCmdLine, int nShowCmd)
{
	UINT ret = DialogBox(hInst, 
		MAKEINTRESOURCE(IDD_SETTING), 0, DlgProc);
	return 0;
}