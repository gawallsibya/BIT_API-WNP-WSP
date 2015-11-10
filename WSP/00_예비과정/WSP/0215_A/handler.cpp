//handler.cpp
#include "std.h"

struct DATA
{
	char message[30];
	char nickname[20];
	int  h, m, s;
};

HWND hSendButton;
HWND hListBox;
HWND hServer;
//���� ��ư Ŭ�� 
void OnConnect(HWND hDlg)
{
	// ���� ȹ�� 
	char nickname[20];
	GetDlgItemText(hDlg, IDC_EDIT1, nickname, 20);

	// ���� Ž�� 
	hServer = FindWindow(NULL, "SERVER");
	if ( hServer == 0 )
	{
		MessageBox(hDlg, "���ӽ���", "����", MB_OK);
		return;
	}
	
	//������ ������
	COPYDATASTRUCT cds;
	cds.cbData = strlen(nickname)+1;// ������ data ũ��
	cds.dwData = 1;					// 1 : �س���(����) 
	cds.lpData = nickname;			// ������ Pointer

	SendMessage( hServer, WM_COPYDATA, 0,  (LPARAM)&cds);

	//uió��
	EnableWindow(hSendButton, TRUE);
}

void OnSend(HWND hDlg)
{
	//1
	char msg[30];
	char msg1[20];
	GetDlgItemText(hDlg, IDC_EDIT2, msg, sizeof(msg));
	SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)msg);

	//2
	SYSTEMTIME mt;
	GetLocalTime(&mt);
	GetDlgItemText(hDlg, IDC_EDIT1, msg1, sizeof(msg1));
	DATA d;
	strcpy(d.message, msg);
	strcpy(d.nickname, msg1);
	d.h = mt.wHour;  d.m =  mt.wMinute; d.s =  mt.wSecond;

	//������ ������
	COPYDATASTRUCT cds;
	cds.cbData = sizeof(DATA);// ������ data ũ��
	cds.dwData = 2;					// 2 : ������ ����
	cds.lpData = &d;			// ������ Pointer

	SendMessage( hServer, WM_COPYDATA, 0,  (LPARAM)&cds);
	
}

int OnInitDialog(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	//1. �ڵ鰪 ȹ��
	hSendButton = GetDlgItem(hDlg, IDC_BUTTON2);
	hListBox	= GetDlgItem(hDlg, IDC_LIST1);

	//uió��
	EnableWindow(hSendButton, FALSE);
	return true;
}

int OnCommand(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	switch( LOWORD( wParam ) )
	{
	case IDC_BUTTON1: OnConnect(hDlg);			break;
	case IDC_BUTTON2: OnSend(hDlg);				break;
		
	case IDCANCEL: EndDialog(hDlg, IDCANCEL);	return 0;
	}
	return true;
}