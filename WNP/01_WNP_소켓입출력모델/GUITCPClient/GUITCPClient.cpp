#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>
#include "resource.h"

#define BUFSIZE 512

// ��ȭ���� �޽��� ó�� �Լ�
BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);
// ����Ʈ ��Ʈ�� ��� �Լ�
void DisplayText(char *fmt, ...);
// ���� ��� �Լ�
DWORD WINAPI ClientMain(LPVOID arg);
// ���� ��� �Լ�
void err_quit(char *msg);
void err_display(char *msg);
// ����� ���� ������ ���� �Լ�
int recvn(SOCKET s, char *buf, int len, int flags);

SOCKET sock; // ����
char buf[BUFSIZE+1]; // ������ �ۼ��� ����
HWND hEdit1, hEdit2, hOKButton; // ����Ʈ ��Ʈ�Ѱ� OK ��ư
HANDLE hReadEvent, hWriteEvent; // �̺�Ʈ

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE,
	LPSTR lpCmdLine, int nCmdShow)
{
	// �̺�Ʈ ����
	hReadEvent = CreateEvent(NULL, FALSE, TRUE, NULL);
	if(hReadEvent == NULL) return -1;
	hWriteEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	if(hWriteEvent == NULL) return -1;

	// ���� ����� ����ϴ� ������ ����
	DWORD ThreadId;
	CreateThread(NULL, 0, ClientMain, NULL, 0, &ThreadId);
	
	// ��ȭ ���� ����
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
	
	// �̺�Ʈ ����
	CloseHandle(hReadEvent);
	CloseHandle(hWriteEvent);

	// closesocket()
	closesocket(sock);

	// ���� ����
	WSACleanup();	

	return 0;
}

// ��ȭ���� �޽��� ó��
BOOL CALLBACK DlgProc(HWND hDlg, UINT uMsg, 
	WPARAM wParam, LPARAM lParam)
{
	switch(uMsg){
	case WM_INITDIALOG:
		hEdit1 = GetDlgItem(hDlg, IDC_EDIT1);
		hEdit2 = GetDlgItem(hDlg, IDC_EDIT2);
		hOKButton = GetDlgItem(hDlg, IDOK);
		SendMessage(hEdit1, EM_SETLIMITTEXT, BUFSIZE, 0);
		return TRUE;
	case WM_COMMAND:
		switch(LOWORD(wParam)){
		case IDOK:
			// OK ��ư ��Ȱ��ȭ
			EnableWindow(hOKButton, FALSE);			
			// �б� �ϷḦ ��ٸ�
			WaitForSingleObject(hReadEvent, INFINITE);
			GetDlgItemText(hDlg, IDC_EDIT1, buf, BUFSIZE+1);			
			// ���� �ϷḦ �˸�
			SetEvent(hWriteEvent);

			SetFocus(hEdit1);
			SendMessage(hEdit1, EM_SETSEL, 0, -1);
			return TRUE;
		case IDCANCEL:
			EndDialog(hDlg, 0);
			return TRUE;
		}
		return FALSE;
	}
	return FALSE;
}

// TCP Ŭ���̾�Ʈ ���� �κ�
DWORD WINAPI ClientMain(LPVOID arg)
{
	int retval;

	// ���� �ʱ�ȭ
	WSADATA wsa;
	if(WSAStartup(MAKEWORD(2,2), &wsa) != 0)
		return -1;

	// socket()
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock == INVALID_SOCKET) err_quit("socket()");	
	
	// connect()
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(9000);
	serveraddr.sin_addr.s_addr = inet_addr("61.81.99.31");
	retval = connect(sock, (SOCKADDR *)&serveraddr, sizeof(serveraddr));
	if(retval == SOCKET_ERROR) err_quit("connect()");
		
	// ������ ������ ���
	while(1){
		// ���� �ϷḦ ��ٸ�
		WaitForSingleObject(hWriteEvent, INFINITE);

		// ���ڿ� ���̰� 0�̸� ������ ����
		if(strlen(buf) == 0){
			// OK ��ư Ȱ��ȭ
			EnableWindow(hOKButton, TRUE);
			// �б� �ϷḦ �˸�
			SetEvent(hReadEvent);
			continue;
		}

		// ������ ������
		retval = send(sock, buf, strlen(buf), 0);
		if(retval == SOCKET_ERROR){
			err_display("send()");
			break;
		}
		DisplayText("[TCP Ŭ���̾�Ʈ] %d����Ʈ�� ���½��ϴ�.\r\n", retval);

		// ������ �ޱ�
		retval = recvn(sock, buf, retval, 0);
		if(retval == SOCKET_ERROR){
			err_display("recv()");
			break;
		}
		else if(retval == 0){
			break;
		}
		
		// ���� ������ ���
		buf[retval] = '\0';
		DisplayText("[TCP Ŭ���̾�Ʈ] %d����Ʈ�� �޾ҽ��ϴ�.\r\n", retval);
		DisplayText("[���� ������] %s\r\n", buf);

		// OK ��ư Ȱ��ȭ
		EnableWindow(hOKButton, TRUE);
		// �б� �ϷḦ �˸�
		SetEvent(hReadEvent);
	}

	return 0;
}

// ����Ʈ ��Ʈ�ѿ� ���ڿ� ���
void DisplayText(char *fmt, ...)
{
	va_list arg;
	va_start(arg, fmt);
	
	char cbuf[BUFSIZE+256];
	vsprintf(cbuf, fmt, arg);
	
	int nLength = GetWindowTextLength(hEdit2);
	SendMessage(hEdit2, EM_SETSEL, nLength, nLength);
	SendMessage(hEdit2, EM_REPLACESEL, FALSE, (LPARAM)cbuf);
	
	va_end(arg);
}

// ���� �Լ� ���� ��� �� ����
void err_quit(char *msg)
{
	LPVOID lpMsgBuf;
	FormatMessage( 
		FORMAT_MESSAGE_ALLOCATE_BUFFER|
		FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	MessageBox(NULL, (LPCTSTR)lpMsgBuf, msg, MB_ICONERROR);
	LocalFree(lpMsgBuf);
	exit(-1);
}

// ���� �Լ� ���� ���
void err_display(char *msg)
{
	LPVOID lpMsgBuf;
	FormatMessage( 
		FORMAT_MESSAGE_ALLOCATE_BUFFER|
		FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	DisplayText("[%s] %s", msg, (LPCTSTR)lpMsgBuf);
	LocalFree(lpMsgBuf);
}

// ����� ���� ������ ���� �Լ�
int recvn(SOCKET s, char *buf, int len, int flags)
{
	int received;
	char *ptr = buf;
	int left = len;

	while(left > 0){
		received = recv(s, ptr, left, flags);
		if(received == SOCKET_ERROR) 
			return SOCKET_ERROR;
		else if(received == 0) 
			break;
		left -= received;
		ptr += received;
	}

	return (len - left);
}