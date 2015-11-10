// fun.cpp

#include "std.h"


int OnTrayIcon(HWND hwnd)
{
	NOTIFYICONDATA nid;
	nid.cbSize			= sizeof(nid);
	nid.hIcon			= LoadIcon(GetModuleHandle(0), MAKEINTRESOURCE(IDI_MAIN));
	nid.hWnd			= hwnd;
	
	strcpy(nid.szTip, "�۾������� Ver1.0");
	
	nid.uCallbackMessage= WM_TRAYMESSAGE;
	nid.uID				= 1;
	nid.uFlags			= NIF_ICON | NIF_TIP | NIF_MESSAGE;
	
	Shell_NotifyIcon(NIM_ADD, &nid);
	
	//-------------------------------------------------------
	// Animation ����� �����ϱ� ���� �ڵ� 
	int cx = GetSystemMetrics(SM_CXSCREEN);
	int cy = GetSystemMetrics(SM_CYSCREEN);
	
	RECT rcWin;
	GetWindowRect(hwnd, &rcWin);
	
	// taskbar�� ���� ũ���� ����...
	RECT rcTray = { cx-50, cy-50, cx, cy };
	
	DrawAnimatedRects(hwnd, IDANI_CAPTION, &rcWin, &rcTray);
	//---------------------------------------------------------
	ShowWindow(hwnd, SW_HIDE);
	return 0;
}


void TrayMessage(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	if( wParam == 1 ) 
	{
		if( lParam == WM_RBUTTONUP)
		{
			HMENU hMenu		= LoadMenu(GetModuleHandle(0), MAKEINTRESOURCE(IDR_TRAYMENU));	
			HMENU hSubMenu  = GetSubMenu(hMenu, 0);
			POINT pt;
			GetCursorPos(&pt);
			// ��ũ�� ��ǥ...
			TrackPopupMenu(hSubMenu, TPM_LEFTBUTTON, pt.x, pt.y, 
				0, hwnd, 0);
		}
		else if( lParam == WM_LBUTTONDBLCLK)
		{
			ShowWindow(hwnd, SW_SHOW);
			NOTIFYICONDATA  nid;
			nid.cbSize			= sizeof(nid);
			nid.hWnd			= hwnd;
			nid.uID				= 1;
			Shell_NotifyIcon(NIM_DELETE, &nid);
		}
	}
}


void CreateChildControl(HWND hwnd)
{
	CreateWindow("edit", "�� ���μ��� ���", WS_CHILD | WS_VISIBLE,
		10,10, 200, 20, hwnd, NULL, GetModuleHandle(0), NULL);

	//------------- LISTVIEW ��Ʈ�� �ʱ�ȭ(MAINLIST) -------------------------------
	LVCOLUMN COL;

	hMainList = CreateWindow(WC_LISTVIEW, NULL, WS_CHILD| WS_VISIBLE|WS_BORDER|
		LVS_REPORT,10, 30, 500, 420, hwnd, NULL, GetModuleHandle(0), NULL);

	// p890 �� ��ü ���� & ���� ǥ���ϱ� 
	ListView_SetExtendedListViewStyle(hMainList, 
		LVS_EX_CHECKBOXES|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP|LVS_EX_INFOTIP);

	COL.mask	= LVCF_FMT|LVCF_WIDTH|LVCF_TEXT|LVCF_SUBITEM;
	COL.fmt		= LVCFMT_LEFT;
	COL.cx		= 100;
	COL.pszText	= "�̹��� �̸�";
	COL.iSubItem= 0;
	SendMessage(hMainList, LVM_INSERTCOLUMN, 0, (LPARAM)&COL);

	COL.cx = 150;
	COL.pszText	= "PID";
	COL.iSubItem=1;
	SendMessage(hMainList, LVM_INSERTCOLUMN, 1, (LPARAM)&COL);

	COL.cx = 150;
	COL.pszText	= "������";
	COL.iSubItem=2;
	SendMessage(hMainList, LVM_INSERTCOLUMN, 2, (LPARAM)&COL);

	//--------------------------------------------------------------------

	//------------- BUTTON CONTROL �ʱ�ȭ -------------------------------
	hBtnRefresh = CreateWindow( "button", "��� ������Ʈ", 
		WS_CHILD | WS_VISIBLE | WS_BORDER,
		10,460,160,30, hwnd, (HMENU)IDC_BTNREFRESH, 0,0);

	hBtnTerminateProcess = CreateWindow( "button", "���μ��� ������", 
		WS_CHILD | WS_VISIBLE | WS_BORDER,
		180,460,160,30, hwnd, (HMENU)IDC_BTNTERMINATEPROCESS, 0,0);

	hBtnSpy = CreateWindow( "button", "���μ��� ����", 
		WS_CHILD | WS_VISIBLE | WS_BORDER,
		350,460,160,30, hwnd, (HMENU)IDC_BTNSPY, 0,0);

	hStaticLog = CreateWindow( "static", "", 
		WS_CHILD | WS_VISIBLE | WS_BORDER,
		10, 500, 500, 30, hwnd, (HMENU)IDC_LOG, 0,0);
}


void ProcessList()
{
	// 1. ListBox �ʱ�ȭ(����ֱ�)
	SendMessage(hMainList, LVM_DELETEALLITEMS, 0, 0);

	// 2. Process ����Ʈ ����  
	HANDLE	hSnap = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0);
	if( hSnap == 0 )
		return ;

	PROCESSENTRY32 ppe;
	BOOL	b     = Process32First(hSnap, &ppe);
	while( b )
	{
		int i=0;
		// ListBox Ctrl�� ������ �߰� 
		ListBoxAddData(i, ppe);

		b = Process32Next(hSnap, &ppe);
	}
	SetWindowText(hStaticLog, "���μ��� ����Ʈ�� �ʱ�ȭ �Ͽ����ϴ�.");

	CloseHandle(hSnap);
}

void ListBoxAddData(int i, PROCESSENTRY32 ppe)
{
	char temp[20];
	LVITEM LI;
	LI.mask = LVIF_TEXT;

	LI.iItem		= i;
	LI.iSubItem		= 0;
	LI.pszText		= ppe.szExeFile;
	SendMessage(hMainList, LVM_INSERTITEM, 0, (LPARAM)&LI);

	wsprintf(temp, "%d", ppe.th32ProcessID);
	LI.iSubItem		= 1;
	LI.pszText		= temp;
	SendMessage(hMainList, LVM_SETITEM, 0, (LPARAM)&LI);

	wsprintf(temp, "%d", ppe.cntThreads);
	LI.iSubItem		= 2;
	LI.pszText		= temp;
	SendMessage(hMainList, LVM_SETITEM, 0, (LPARAM)&LI);
}


void ProcessExit(HWND hwnd)
{
	char temp[10];
	DWORD pid;

	int idx  = ListView_GetNextItem(hMainList, -1, LVNI_ALL|LVNI_SELECTED);
	ListView_GetItemText(hMainList, idx, 1, temp, 10);
	pid = atoi(temp);
	HANDLE	hProcess = OpenProcess(PROCESS_ALL_ACCESS, 0, pid);
	if( hProcess)
	{
		TerminateProcess(hProcess, 1000);

		WaitForSingleObject(hProcess, INFINITE);

		ProcessList();

		SetWindowText(hStaticLog, "���μ����� �����߽��ϴ�.");
	}
}

#ifndef ListView_SetCheckState
#define ListView_SetCheckState(hwndLV, i, fCheck) \
ListView_SetItemState(hwndLV, i, \
INDEXTOSTATEIMAGEMASK((fCheck)+1), LVIS_STATEIMAGEMASK)
#endif

void WatchProcess(HWND hwnd)
{
	char processname[20];
	char temp[40];
	DWORD pid;

	int idx  = ListView_GetNextItem(hMainList, -1, LVNI_ALL|LVNI_SELECTED);
	ListView_GetItemText(hMainList, idx, 1, temp, 20);
	pid = atoi(temp);
	ListView_GetItemText(hMainList, idx, 0, processname, 20);

	// ������� ������ ����ü ���� ����
	TDATA *pData	= new TDATA;
	pData->hDlg		= hwnd;
	pData->pid		= pid;
	pData->idx      = idx;
	strcpy(pData->exename	, processname);

	// ������ ���� �� ������ ����
	DWORD tid;
	hThreadList[ThreadCount++] = CreateThread(0, 0, Watch, 
					(void*)pData, 0, &tid);

	wsprintf(temp, "[ %s ] ���μ����� �����մϴ�.", processname);
	SetWindowText(hStaticLog, temp);
}


DWORD WINAPI Watch( void *p)
{
	TDATA *pData	= (TDATA*)p;
	DWORD	pid		= pData->pid;	// process�� ID
	//------------------------------
	HANDLE	hProcess = OpenProcess(PROCESS_ALL_ACCESS, 0, pid);
	if( hProcess == 0 )
	{
		MessageBox(0, "���μ����� �ڵ��� ���� �� ����.", "", MB_OK);
		return 0;
	}
	ListView_SetCheckState(hMainList, pData->idx, TRUE);

	//----- Event ���� ���� �߰� ---------------------------------
	HANDLE	hEvent		= CreateEvent(0, TRUE, 0, "Exit");	//-> Open.(������ ��ü�� �ڵ�)
	HANDLE	h[2]		= { hProcess, hEvent };
	char    temp[50];
	DWORD ret = WaitForMultipleObjects( 2, h, FALSE, INFINITE);	// �κ� �ñ׳�

	if( ret		== WAIT_OBJECT_0)	// ���μ����� �ñ׳�
	{
		wsprintf(temp, "[ %s ] ���μ����� �����Ͽ����ϴ�.", pData->exename);
		SetWindowText(hStaticLog, temp);
		Sleep(1000);
	}

	CloseHandle( hEvent);
	CloseHandle(hProcess);
	delete pData;

	ProcessList();
	return 0;
}


void NewProcess(HWND hwnd)
{   

	UINT ret = DialogBoxParam( GetModuleHandle(0),
			MAKEINTRESOURCE(IDD_CREATEPROCESS),hwnd,
					NewProcessProc, // �޼��� �Լ�.
					(LPARAM)0); 
	if ( ret == IDOK ) 
	{
		ProcessList();	
		SetWindowText(hStaticLog, "���μ����� �����Ǿ����ϴ�");

	}
}
