/****************************************************
  [���� ���� ���α׷� ]
******************************************************/

#include <windows.h>
#include "resource.h"

#define SRVNAME "StartService"
#define SERVICE_CONTROL_NEWFILE 128

BOOL CALLBACK MainDlgProc(HWND hDlg,UINT iMessage,WPARAM wParam,LPARAM lParam);
HINSTANCE g_hInst;
HWND hDlgMain, hStatic;
SC_HANDLE hScm, hSrv;
SERVICE_STATUS ss;

void MemStart();
void MemControl(DWORD dwControl);
void QueryService();

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance
         ,LPSTR lpszCmdParam,int nCmdShow)
{
    g_hInst=hInstance;
    
    DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG1), HWND_DESKTOP, MainDlgProc);

    return 0;
}

BOOL CALLBACK MainDlgProc(HWND hDlg,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
    switch(iMessage)
    {
    case WM_INITDIALOG:
		SetWindowPos(hDlg,HWND_TOP,100,100,0,0,SWP_NOSIZE);
        hDlgMain = hDlg;
		hStatic=GetDlgItem(hDlg,IDC_STATIC1);

		// SCM�� ���� ������ ���� ���´�.
		hScm=OpenSCManager(NULL,NULL,GENERIC_READ);
		if (hScm==NULL) {
			MessageBox(hDlg,"SCM�� �� �� �����ϴ�","�˸�",MB_OK);
			EndDialog(hDlg,0);
		}

		// ���񽺰� ��ġ�Ǿ� ���� ������ ������ �� ����.
		hSrv=OpenService(hScm,SRVNAME,SERVICE_ALL_ACCESS);
		if (hSrv==NULL) {
			MessageBox(hDlg,"StartService ���񽺰� ��ġ�Ǿ� ���� �ʽ��ϴ�","�˸�",MB_OK);
			EndDialog(hDlg,0);
		} else {
			CloseServiceHandle(hSrv);
		}
		QueryService();
        return TRUE;
	case WM_DESTROY:
		CloseServiceHandle(hScm);
		return TRUE;
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
		case IDC_START:
			MemStart();
			return TRUE;
		case IDC_STOP:
			MemControl(SERVICE_CONTROL_STOP);
			return TRUE;
		case IDC_PAUSE:
			MemControl(SERVICE_CONTROL_PAUSE);
			return TRUE;
		case IDC_CONTINUE:
			MemControl(SERVICE_CONTROL_CONTINUE);
			return TRUE;
		case IDC_NEWFILE:
			MemControl(SERVICE_CONTROL_NEWFILE);
			return TRUE;
        case IDOK:
        case IDCANCEL:
            EndDialog(hDlgMain,0);
            return TRUE;
        }
        return FALSE;
    }
    return FALSE;
}

// ���� ���� ���¿� ���� ��ư�� ���¸� �����Ų��.
void QueryService()
{
	hSrv=OpenService(hScm,SRVNAME,SERVICE_INTERROGATE);

	do {
		ControlService(hSrv,SERVICE_CONTROL_INTERROGATE,&ss);
	} while ((ss.dwCurrentState != SERVICE_STOPPED) &&
		(ss.dwCurrentState != SERVICE_RUNNING) &&
		(ss.dwCurrentState != SERVICE_PAUSED));

	EnableWindow(GetDlgItem(hDlgMain,IDC_START),FALSE);
	EnableWindow(GetDlgItem(hDlgMain,IDC_STOP),FALSE);
	EnableWindow(GetDlgItem(hDlgMain,IDC_PAUSE),FALSE);
	EnableWindow(GetDlgItem(hDlgMain,IDC_CONTINUE),FALSE);
	EnableWindow(GetDlgItem(hDlgMain,IDC_NEWFILE),FALSE);
	switch(ss.dwCurrentState) {
	case SERVICE_STOPPED:
		EnableWindow(GetDlgItem(hDlgMain,IDC_START),TRUE);
		SetWindowText(hStatic,"���� ����:����");
		break;
	case SERVICE_RUNNING:
		EnableWindow(GetDlgItem(hDlgMain,IDC_STOP),TRUE);
		EnableWindow(GetDlgItem(hDlgMain,IDC_PAUSE),TRUE);
		EnableWindow(GetDlgItem(hDlgMain,IDC_NEWFILE),TRUE);
		SetWindowText(hStatic,"���� ����:������");
		break;
	case SERVICE_PAUSED:
		EnableWindow(GetDlgItem(hDlgMain,IDC_STOP),TRUE);
		EnableWindow(GetDlgItem(hDlgMain,IDC_CONTINUE),TRUE);
		SetWindowText(hStatic,"���� ����:�Ͻ�����");
		break;
	}

	CloseServiceHandle(hSrv);
}

// ���񽺸� ���۽�Ų��.
void MemStart()
{
	hSrv=OpenService(hScm,"StartService",SERVICE_START | SERVICE_QUERY_STATUS);

	// ���񽺸� ���۽�Ű�� ������ ������ ������ ����Ѵ�.
	SetCursor(LoadCursor(NULL,IDC_WAIT));
	if (StartService(hSrv,0,NULL)==TRUE) {
		QueryServiceStatus(hSrv, &ss);
		while (ss.dwCurrentState != SERVICE_RUNNING) {
			Sleep(ss.dwWaitHint);
			QueryServiceStatus(hSrv, &ss);
		}
	}
	SetCursor(LoadCursor(NULL,IDC_ARROW));

	CloseServiceHandle(hSrv);
	QueryService();
}

// ���񽺿� ���� �ڵ带 ������.
void MemControl(DWORD dwControl)
{
	hSrv=OpenService(hScm,"StartService",GENERIC_EXECUTE);

	ControlService(hSrv,dwControl,&ss);

	CloseServiceHandle(hSrv);
	QueryService();
}

