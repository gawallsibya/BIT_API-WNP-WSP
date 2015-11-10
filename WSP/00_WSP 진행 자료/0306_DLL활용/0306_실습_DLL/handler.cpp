//handler.cpp
#include "std.h"

char g_name[20];
int  g_group;		// 0 : ��ü, 1 : 1��....

DWORD OnInitDialog(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	// �޺��ڽ� ������ �ʱ�ȭ
	ui_init(hDlg);	

	// �α��� ��ư Ȱ��ȭ, ���� ��ư ��Ȱ��ȭ
	ui_EnableButton(hDlg, TRUE, FALSE);

	// ���� �ʱ�ȭ <=========================
	if( mysock_init() == -1)
		MessageBox(hDlg, "���� �ʱ�ȭ ����", "����", MB_OK);

	mysock_inirproc(OnRecv);
	return TRUE;
}

DWORD OnCommand(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	switch( LOWORD( wParam ) )
	{
	case IDC_BTN_LOGIN: OnLogin(hDlg);	break;
	case IDC_BTN_SEND:	OnSend(hDlg);	break;
	case ID_LOGOUT:		OnLogOut(hDlg);	break;

	case ID_EXIT:
	case IDCANCEL: 		OnExit(hDlg);	break;
	}
	return TRUE;
}



//�α��� ��ư �ڵ鷯 
void OnLogin(HWND hDlg)
{
	//1. ��, �̸� ������ ���������� ����
	char name[20];		ui_GetName(name);
	strcpy(g_name, name);
	g_group		= ui_GetGroup();

#ifndef MY_DEBUG
	printf("%s : %d\n", g_name, g_group);
#endif
	
	//2. ����  2���� ����(send, recv)
	mysock_recvsock(sizeof(PACKET), RECV_PORT);
	mysock_sendsock(sizeof(PACKET), RECV_PORT);


	//3. �α��� ��ư ��Ȱ��ȭ, ���� ��ư Ȱ��ȭ
	ui_EnableButton(hDlg, FALSE, TRUE);
}


void OnLogOut(HWND hDlg)
{
	//1. ���������� ������ ���� �ʱ�ȭ
	strcpy(g_name, "");		g_group = 0;
	ui_SetName(g_name);		ui_SetGroup(g_group);
#ifndef MY_DEBUG
	printf("%s : %d\n", g_name, g_group);
#endif

	//2. ���� ����


	//3. �α��� ��ư Ȱ��ȭ, ���� ��ư ��Ȱ��ȭ
	ui_EnableButton(hDlg, TRUE, FALSE);
}



// ���۹�ư �ڵ鷯
void OnSend(HWND hDlg)
{
	//1. �Է� ���� ȹ��(��, ���۹��ڿ�)
	int idx = ui_GetSendGroup();
	char senddata[50];
	ui_GetSendData(senddata);
#ifndef MY_DEBUG
	printf("%s : %d\n", senddata, idx);
#endif

	//2. ��Ŷ ����
	PACKET pack = {0};
	pack.flag	= idx;
	SYSTEMTIME st;
	GetLocalTime(&st);
	char buf[20];
	wsprintf(buf, "%02d:%02d:%02d", st.wHour, st.wMinute, st.wSecond);
	strcpy(pack.s_time, buf);
	strcpy(pack.s_name, g_name);
	strcpy(pack.s_message, senddata);

	//3. ���� ����
	mysock_senddata((char*)&pack, sizeof(pack));
	

	//4. ���ڿ� �Է�â �ʱ�ȭ
	ui_SetSendData("");	
}


//���� ó�� �ڵ鷯 : �޴�(����)
void OnExit(HWND hDlg)
{
	//���� ���� ó�� 
	mysock_exit();		//<=====================

	//���α׷� ����
	EndDialog(hDlg, IDCANCEL);
}

//������ ����
void OnRecv(char* data, int length)
{
	PACKET *pack = (PACKET*)data;
	if(g_group != pack->flag)
		return;

	//���� ó���ؾ� �� ������
	char buf[256];
	wsprintf(buf, "[%s/%s]%s\r\n", pack->s_name, pack->s_time,pack->s_message);
#ifndef MY_DEBUG
	printf("���ŵ����� ==> %s", buf);
#endif

	ui_DisplayText(buf);	
}