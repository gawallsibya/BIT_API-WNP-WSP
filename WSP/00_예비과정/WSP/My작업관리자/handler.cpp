// handler.cpp

#include "std.h"


//-------------------------------------------------------------------------
// �Լ��� : OnCreate
// ��  �� : �ڽ� ��Ʈ�� ���� �� �ʱ�ȭ 
//-------------------------------------------------------------------------
int OnCreate(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	InitCommonControls();

	CreateChildControl(hwnd);

	ProcessList();

	hExitEvent	= CreateEvent(0, TRUE, 0, "Exit");	//���� �̺�Ʈ ��ü ����

	return 0;
}

int OnCtrlColorEdit(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	static HBRUSH hBrush = CreateSolidBrush( RGB(255,255,0));

	HDC hdc = (HDC)wParam; // Edit �� ����� dc
	HWND h  = (HWND)lParam;

	SetBkColor( hdc, RGB(190,190,190));

	return (LRESULT)GetStockObject(LTGRAY_BRUSH); // WM_CTLCOLORxxx �޼����� ó���Ҷ�
}

//-------------------------------------------------------------------------
// �Լ��� : OnSysComand
// ��  �� : ���� ��ư Ŭ���� Ʈ���� ������ ó�� 
//-------------------------------------------------------------------------
int OnSysComand(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch( wParam & 0xFFF0 )	
	{
	case SC_MINIMIZE: return 	OnTrayIcon(hwnd);
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}


//-------------------------------------------------------------------------
// �Լ��� : OnTrayMessage
// ��  �� : Ʈ���� �����ܿ��� �߻��Ǵ� ����� ���� �޽��� ó��
//-------------------------------------------------------------------------
int OnTrayMessage(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	TrayMessage(hwnd, wParam, lParam);
	return 0;
}


//-------------------------------------------------------------------------
// �Լ��� : OnDestroy
// ��  �� : ���α׷� ���� �Լ� ȣ��
//-------------------------------------------------------------------------
int OnDestory()
{
	SetEvent(hExitEvent);		// ������� ��� �����带 �����..

	// ��� ������ �����尡 ����ɶ����� �������..
	WaitForMultipleObjects( ThreadCount, hThreadList, TRUE, INFINITE);

	for( int i=0; i< ThreadCount; i++)
	{
		CloseHandle( hThreadList[i]);
	}

	PostQuitMessage(0);
	return 0;
}

//-------------------------------------------------------------------------
// �Լ��� : OnCommand
// ��  �� : �޴� �� ��Ʈ���� NOTIFY ó�� 
//-------------------------------------------------------------------------
int OnCommand(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	switch( LOWORD(wParam))		// ID ����
	{
	case ID_EXIT:	SendMessage(hwnd, WM_CLOSE, 0, 0);	break;
	case ID_INFO:	MessageBox(hwnd, "���� ���� : WSP �ǽ�\r\n���� ��¥ : 2009.1.20\r\n��  ��  �� : CCM","���α׷� ����",  NULL);
	case ID_MENU_SHOW:	ShowWindow(hwnd, SW_SHOW);		break;

	case ID_MENU_NEWPROCESS: NewProcess(hwnd);			break;

	case IDC_BTNREFRESH:	ProcessList();				break;
	case IDC_BTNTERMINATEPROCESS: ProcessExit(hwnd);	break;
	case IDC_BTNSPY: WatchProcess(hwnd);				break;
	}
	return 0;
}