//main.cpp
#include"std.h"

BOOL CALLBACK MainDlgProc(HWND hDlg,UINT imessage,WPARAM wParam,LPARAM lParam)
{
	switch (imessage) 
	{
	case WM_INITDIALOG:		return OnInitDialog(hDlg,wParam,lParam);
	case WM_COMMAND:		return OnCommand(hDlg,wParam,lParam);
	case WM_NOTIFY:			return OnNotify(hDlg,wParam,lParam);
	}
	return FALSE;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE , PSTR lpCmdLine, int nShowCmd)
{
	
#ifndef MY_DEBUG
	AllocConsole(); // console â ����

	freopen( "CONOUT$",   // console ��
			 "wt",        // text write ����
			 stdout);	  // stdout �� ����..
#endif

	UINT ret = DialogBox(hInstance,MAKEINTRESOURCE(IDD_MAINDLG),NULL,MainDlgProc);
	return 0;
}