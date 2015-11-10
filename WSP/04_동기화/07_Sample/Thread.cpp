#include <windows.h>
#include <tlhelp32.h>
#include "resource.h"

//-------------------------------------------
// �����忡 ���޵Ǵ� �����͸� ������ �ִ� ����ü
//-------------------------------------------
typedef struct _TDATA
{
	HWND	hDlg;			// �� �����尡 ���� Dialog�ڵ�
	char	exename[256];	// process �̸�
	DWORD	pid;			// process ID
}TDATA;


//------------------------------------------------------
// ComboBox �� ������ process ����� �����ϴ� �Լ� 
//-------------------------------------------------------
void Refresh( HWND hCombo )
{
	// 1. ComboBox �ʱ�ȭ(����ֱ�)
	SendMessage(hCombo, CB_RESETCONTENT, 0, 0);

	// 2. ComboBox ä��� 
	HANDLE	hSnap = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0);

	PROCESSENTRY32 ppe;
	BOOL	b     = Process32First(hSnap, &ppe);
	while( b )
	{
		// LPARAM : ������� process��.
		int index = SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)ppe.szExeFile);

		SendMessage(hCombo, CB_SETITEMDATA, index, (LPARAM)ppe.th32ProcessID);

		b = Process32Next(hSnap, &ppe);
	}
	CloseHandle(hSnap);

	// 3. ComboBox ������ ���� 
	SendMessage(hCombo, CB_SETCURSEL, 1, 0);
}
//---------------------------------------------
// Thread Function...
//---------------------------------------------
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
	
	//----- Event ���� ���� �߰� ---------------------------------
	HANDLE	hEvent		= CreateEvent(0, TRUE, 0, "Exit");	//-> Open.(������ ��ü�� �ڵ�)
	HANDLE	h[2]		= { hProcess, hEvent };

	DWORD ret = WaitForMultipleObjects( 2, h, FALSE, INFINITE);	// �κ� �ñ׳�

	if( ret		== WAIT_OBJECT_0)	// ���μ����� �ñ׳�
		MessageBox(0, "���μ��� ����", pData->exename, MB_OK);

	else if( ret == WAIT_OBJECT_0 + 1 )	// event �ñ׳�
		MessageBox(0, "event Signal,������ ����", "", MB_OK);

	CloseHandle( hEvent);
	
	//------------------------------------------------------------
/*
	DWORD ret = WaitForSingleObject(hProcess, INFINITE);
	// �ش� ���μ����� signal
	if( ret == WAIT_OBJECT_0 )	
		MessageBox(0, "���μ����� ����Ǿ���", pData->exename, MB_OK);
*/
	CloseHandle(hProcess);
	delete pData;
	
	return 0;
}


// DlgProc --------------------------------------------
BOOL CALLBACK DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HWND		hCombo;				// comboBox�� ������ �ڵ�

	static HANDLE	hThreadList[256];	// ������ thread�� �ڵ�
	static int		nCount = 0;			// ������ thread�� ���� 

	//-------------------------------------------------------------------
	static HANDLE	hExit;				// ����ȭ �̺�Ʈ ��ü(����)
	//-------------------------------------------------------------------

	switch( msg )
	{
	case WM_INITDIALOG:
		hExit				= CreateEvent(0, TRUE, 0, "Exit");	//���� �̺�Ʈ ��ü ����
		hCombo				= GetDlgItem(hDlg, IDC_COMBO1);
		Refresh(hCombo);
		return TRUE;
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		// watch��ư Ŭ���� ȣ��Ǵ� �޽��� �ڵ鷯.
		case IDC_BTN_WATCH:
			{
				//���� ���õ� �ε��� ����..
				int n		= SendMessage(hCombo, CB_GETCURSEL,0, 0);
				// wParam(index)�� ���޵� index�� ������ �ִ� data ����.
				DWORD pid	= SendMessage(hCombo, CB_GETITEMDATA, n, 0);

				// ������� ������ ����ü ���� ����
				TDATA *pData	= new TDATA;
				pData->hDlg		= hDlg;
				pData->pid		= pid;
				GetWindowText(hCombo, pData->exename, 256);
				//-----------------------------------------------------

				// ������ ���� �� ������ ����
				DWORD tid;
				hThreadList[nCount++] = CreateThread(0, 0, Watch, 
							(void*)pData, 0, &tid);

				// ������ ī��Ʈ ���
				SetDlgItemInt(hDlg, IDC_STATIC_COUNT, nCount, 0);
						

			}
			break;
		case IDC_BTN_REFRESH:
			{
				Refresh(hCombo);
			}
			break;
		case IDCANCEL:

			SetEvent(hExit);		// ������� ��� �����带 �����..

			// ��� ������ �����尡 ����ɶ����� �������..
			WaitForMultipleObjects( nCount, hThreadList, TRUE, INFINITE);

			for( int i=0; i< nCount; i++)
			{
				CloseHandle( hThreadList[i]);
			}
			EndDialog(hDlg, IDCANCEL);
			break;
		}
		return TRUE;
	}
	return FALSE;
}

int WINAPI WinMain( HINSTANCE hInst, HINSTANCE , LPSTR lpCmdLine,
						int nShowCmd)
{
	DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), 0, DlgProc);
	return 0;
}