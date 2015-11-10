//handler.cpp
#include "std.h"

char g_name[20];
int  g_group;			//0 : ��ü, 1 : 1��.....

SOCKET sendsock;
extern HWND g_heditview;
HANDLE hPipe;

void recvfun(char* data,int size,SOCKET sock)
{
	int *flag=(int*)data;
	switch(*flag)
	{
	case 0:	
	case 1:
		{
			//char message[90];
			PACKET* pack=(PACKET*)data;
			//wsprintf(message,"%s: %s (%s)\r\n",pack->s_name,pack->s_message,pack->s_time);
			DisplayText("%s: %s (%s)\r\n",pack->s_name,pack->s_message,pack->s_time);
		}break;
	case 2:
	case 3: break;
	}
}
void DisplayText(char *fmt, ...){
	va_list arg;
	va_start(arg, fmt);
	char cbuf[256];
	vsprintf(cbuf, fmt, arg);
	EnterCriticalSection(&cs);
	int nLength = GetWindowTextLength(g_heditview);
	SendMessage(g_heditview, EM_SETSEL, nLength, nLength);
	SendMessage(g_heditview, EM_REPLACESEL, FALSE, (LPARAM)cbuf);
	LeaveCriticalSection(&cs);
	
	va_end(arg);
}
DWORD OnInitDialog(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	// �޺��ڽ� ������ �ʱ�ȭ
	ui_init(hDlg);	

	// �α��� ��ư Ȱ��ȭ, ���� ��ư ��Ȱ��ȭ
	ui_EnableButton(hDlg, TRUE, FALSE);

	mysock_initlibraty();

	mysock_init(recvfun);

	DWORD ThreadID;
	CloseHandle(CreateThread(NULL,0,MainThread,NULL,0,&ThreadID));

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
	char name[20];
	ui_GetName(name);
	strcpy(g_name,name);
	g_group=ui_GetGroup();

	//2. ���� ���� 2���� ����(send, recv)
	sendsock = mysock_sendsock(PORT);
	mysock_recvsock(PORT);

	//3. �α��� ��ư ��Ȱ��ȭ, ���� ��ư Ȱ��ȭ
	ui_EnableButton(hDlg, FALSE, TRUE);
}


void OnLogOut(HWND hDlg)
{
	//1. ���������� ������ ���� �ʱ�ȭ
	strcpy(g_name,"");	g_group=0;
	ui_SetName(g_name);		ui_SetGroup(g_group);
	//2. ���� ����
	mysock_closesock(sendsock);
	//3. �α��� ��ư Ȱ��ȭ, ���� ��ư ��Ȱ��ȭ
	ui_EnableButton(hDlg, TRUE, FALSE);
}


char senddata[50];
// ���۹�ư �ڵ鷯
void OnSend(HWND hDlg)
{
	//1. �Է� ���� ȹ��(��, ���۹��ڿ�)
	int idx= ui_GetSendGroup();
	
	ui_GetSendData(senddata);

	//2. ��Ŷ ����
	PACKET pack;
	pack.flag=idx;
	strcpy(pack.s_name,g_name);
	SYSTEMTIME st;
	GetLocalTime(&st);
	wsprintf(pack.s_time,"%0d:%0d:%0d",st.wHour,st.wMinute,st.wSecond);
	strcpy(pack.s_message,senddata);
/*#ifndef MY_DEBUG
	printf("%s : %s\n",pack.s_name,pack.s_time);
#endif*/
	//3. ���� ����
	mysock_send(sendsock,(char*)&pack,sizeof(PACKET));
	//4. ���ڿ� �Է�â �ʱ�ȭ
	ui_SetSendData("");

	//=======================================================
	// ��û�� ���� �� ������ �޴´�.
	BOOL bSuc;
	DWORD dwRead, dwWritten;
	TCHAR szOutput[50];
	bSuc=WriteFile(hPipe,senddata,lstrlen(senddata)+1,&dwWritten,NULL);
	if ((bSuc==FALSE) || (dwWritten==0))
		return;
	
	ReadFile(hPipe,szOutput,50,&dwRead,NULL);

	MessageBox(0,szOutput,"",MB_OK);

	Sleep(500);

	// �������� �����ϰ� ����� ���� �����쿡 ����Ѵ�.
	
}

DWORD WINAPI MainThread(LPVOID temp)
{
	// ������ �������� ������ ������ ���� ����Ѵ�.
	for (;;) {
		if (WaitNamedPipe("\\\\.\\pipe\\MultiPipe",NMPWAIT_WAIT_FOREVER)==TRUE) {
			hPipe=CreateFile("\\\\.\\pipe\\MultiPipe",GENERIC_READ | GENERIC_WRITE,
				0,NULL,OPEN_EXISTING,0,NULL);
			if (hPipe!=INVALID_HANDLE_VALUE)
				break;
		}
	}
	
	return 0;
}

//���� ó�� �ڵ鷯 : �޴�(����)
void OnExit(HWND hDlg)
{
	//���� ���� ó�� 
	CloseHandle(hPipe);
	mysock_exitlibrary();
	mysock_closesock(sendsock);
	//���α׷� ����
	EndDialog(hDlg, IDCANCEL);
}
