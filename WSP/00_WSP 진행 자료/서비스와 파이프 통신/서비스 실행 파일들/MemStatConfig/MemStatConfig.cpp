/*************************************************************************************

  SERVICE ��ġ ���α׷� 

**************************************************************************************/
#include <windows.h>
#include <io.h>
#include "resource.h"

#define EXENAME "MemStatService.exe"
#define SRVNAME "MemStatService"
#define DISPNAME "Memory Status Log Service"

BOOL CALLBACK MainDlgProc(HWND hDlg,UINT iMessage,WPARAM wParam,LPARAM lParam);
HINSTANCE g_hInst;
HWND hDlgMain, hStatic;

void Install();
void UnInstall();

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance
         ,LPSTR lpszCmdParam,int nCmdShow)
{
    g_hInst=hInstance;
    
    DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG1), HWND_DESKTOP, MainDlgProc);

    return 0;
}

BOOL CALLBACK MainDlgProc(HWND hDlg,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	SC_HANDLE hScm, hSrv;

    switch(iMessage)
    {
    case WM_INITDIALOG:
		SetWindowPos(hDlg,HWND_TOP,100,100,0,0,SWP_NOSIZE);
        hDlgMain = hDlg;
		hStatic=GetDlgItem(hDlg,IDC_STATIC1);

		// ���񽺰� ��ġ�Ǿ� �ִ��� ������ ����.
		hScm=OpenSCManager(NULL,NULL,SC_MANAGER_CREATE_SERVICE);
		if (hScm!=NULL) {
			hSrv=OpenService(hScm,SRVNAME,SERVICE_ALL_ACCESS);
			if (hSrv!=NULL) {
				SetWindowText(hStatic,"���� ����:��ġ�Ǿ� �ֽ��ϴ�");
				CloseServiceHandle(hSrv);
			} else {
				SetWindowText(hStatic,"���� ����:��ġ���� �ʾҽ��ϴ�");
			}
			CloseServiceHandle(hScm);
		}
        return TRUE;
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
		case IDC_INSTALL:
			Install();
			return TRUE;
		case IDC_UNINSTALL:
			UnInstall();
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

// ���񽺸� ��ġ�Ѵ�.
void Install()
{
	SC_HANDLE hScm, hSrv;
	char SrvPath[MAX_PATH];
	SERVICE_DESCRIPTION lpDes;
	char Desc[1024];

	// SCM�� ����
	hScm=OpenSCManager(NULL,NULL,SC_MANAGER_CREATE_SERVICE);
	if (hScm==NULL) {
		MessageBox(hDlgMain,"SCM�� �� �� �����ϴ�.","�˸�",MB_OK);
		return;
	}

	// ����� ���� ������ �ִ��� ������ ���� ��θ� ���Ѵ�.
	GetCurrentDirectory(MAX_PATH,SrvPath);
	strcat(SrvPath, "\\");
	strcat(SrvPath, EXENAME);
	if (_access(SrvPath,0) != 0) {
		CloseServiceHandle(hScm);
		MessageBox(hDlgMain,"���� ���丮�� ���� ������ �����ϴ�.","�˸�",MB_OK);
		return;
	}

	// ���񽺸� ����Ѵ�. SERVICE_WIN32_OWN_PROCESS //GUI ���� SERVICE_INTERACTIVE_PROCESS
	hSrv=CreateService(hScm,SRVNAME,DISPNAME,SERVICE_PAUSE_CONTINUE | SERVICE_CHANGE_CONFIG,
		SERVICE_WIN32_OWN_PROCESS | SERVICE_INTERACTIVE_PROCESS,SERVICE_DEMAND_START,SERVICE_ERROR_IGNORE,SrvPath,
		NULL,NULL,NULL,NULL,NULL);
	if (hSrv==NULL) {
		MessageBox(hDlgMain,"��ġ���� ���߽��ϴ�.","�˸�",MB_OK);
	} else {
		// ������ ����Ѵ�.
		GetDlgItemText(hDlgMain,IDC_DESC,Desc,1024);
		lpDes.lpDescription=Desc;
		ChangeServiceConfig2(hSrv, SERVICE_CONFIG_DESCRIPTION, &lpDes);

		MessageBox(hDlgMain,"��ġ�߽��ϴ�.","�˸�",MB_OK);
		SetWindowText(hStatic,"���� ����:��ġ�Ǿ� �ֽ��ϴ�");
		CloseServiceHandle(hSrv);
	}

	CloseServiceHandle(hScm);
}

// ���񽺸� �����Ѵ�.
void UnInstall()
{
	SC_HANDLE hScm, hSrv;
	SERVICE_STATUS ss;

	// SCM�� ����
	hScm=OpenSCManager(NULL,NULL,SC_MANAGER_CREATE_SERVICE);
	if (hScm==NULL) {
		MessageBox(hDlgMain,"SCM�� �� �� �����ϴ�.","�˸�",MB_OK);
		return;
	}

	// ������ �ڵ��� ���Ѵ�.
	hSrv=OpenService(hScm,SRVNAME,SERVICE_ALL_ACCESS);
	if (hSrv==NULL) {
		CloseServiceHandle(hScm);
		MessageBox(hDlgMain,"���񽺰� ��ġ�Ǿ� ���� �ʽ��ϴ�.","�˸�",MB_OK);
		return;
	}

	// �������̸� ������Ų��.
	QueryServiceStatus(hSrv,&ss);
	if (ss.dwCurrentState != SERVICE_STOPPED) {
		ControlService(hSrv,SERVICE_CONTROL_STOP,&ss);
		Sleep(2000);
	}

	// ���� ����
	if (DeleteService(hSrv)) {
		MessageBox(hDlgMain,"���񽺸� �����߽��ϴ�.","�˸�",MB_OK);
		SetWindowText(hStatic,"���� ����:��ġ���� �ʾҽ��ϴ�");
	} else {
		MessageBox(hDlgMain,"���񽺸� �������� ���߽��ϴ�.","�˸�",MB_OK);
	}
	CloseServiceHandle(hSrv);
	CloseServiceHandle(hScm);
}
