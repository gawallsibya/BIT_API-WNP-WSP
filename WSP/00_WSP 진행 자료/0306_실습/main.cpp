//main.cpp
#include "std.h"

BOOL CALLBACK DlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:	return OnInitDialog(hDlg, wParam, lParam);
	case WM_COMMAND:	return OnCommand(hDlg, wParam, lParam);
	}
	return FALSE;
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE , PSTR lpCmdLine, int nShowCmd)
{

#ifndef MY_DEBUG
	AllocConsole(); // console â ����

	freopen( "CONOUT$",   // console ��
			 "wt",        // text write ����
			 stdout);	  // stdout �� ����..
#endif

	UINT ret = DialogBox(hInst,MAKEINTRESOURCE(IDD_MAINDLG),	
					0, DlgProc);						
	return 0;
}
























