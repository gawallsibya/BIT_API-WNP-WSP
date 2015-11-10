#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>
#include "resource.h"

#define BUFSIZE     50 // ���� ũ��
#define CHATTING    0  // �޽��� Ÿ��
#define DRAWING     1  // �޽��� Ÿ��
#define WM_DRAWIT   WM_USER+10 // ����� ���� ������ �޽���

// ä�� �޽���
struct CHATMSG
{
	char buf[BUFSIZE+1];
};

// �� �׸��� �޽���
struct DRAWMSG
{
	short int x0, y0;
	short int x1, y1;
};

static HWND hEditStatus;
static HWND hButtonSend;
static HWND hDrawWnd;
static IN_ADDR ipaddr;
static u_short port;
static HANDLE hServerThread, hClientThread;
static HANDLE hReadEvent, hWriteEvent;
static HINSTANCE hInst;
static BOOL bStart;
static CHATMSG g_chatmsg;
static SOCKET g_sock;

// ��ȭ���� �޽��� ó��
BOOL CALLBACK DlgProc(HWND hDlg, UINT uMsg, 
	WPARAM wParam, LPARAM lParam);

// ������ �޽��� ó��
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg,
	WPARAM wParam, LPARAM lParam);

// ������ �Լ�
DWORD WINAPI Server(LPVOID arg);
DWORD WINAPI Client(LPVOID arg);
DWORD WINAPI ReadThread(LPVOID arg);
DWORD WINAPI WriteThread(LPVOID arg);

// ��ƿ��Ƽ �Լ�
void err_quit(char *msg);
void DisplayText(char *fmt, ...);
BOOL GetIPAddr(char *name, IN_ADDR *addr);
int recvn(SOCKET s, char *buf, int len, int flags);

// ���� �Լ�
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE,
	LPSTR lpCmdLine, int nCmdShow)
{
	// ���� �ʱ�ȭ
	WSADATA wsa;
	if(WSAStartup(MAKEWORD(2,2), &wsa) != 0)
		return -1;

	// �̺�Ʈ ����
	hReadEvent = CreateEvent(NULL, FALSE, TRUE, NULL);
	if(hReadEvent == NULL) return -1;
	hWriteEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	if(hWriteEvent == NULL) return -1;

	bStart = FALSE;
	hInst = hInstance;
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);

	// �̺�Ʈ ����
	CloseHandle(hReadEvent);
	CloseHandle(hWriteEvent);

	// ���� ����
	WSACleanup();
	return 0;
}

// ��ȭ���� �޽��� ó��
BOOL CALLBACK DlgProc(HWND hDlg, UINT uMsg, 
	WPARAM wParam, LPARAM lParam)
{
	static HWND hButtonStartServer;
	static HWND hButtonStartClient;
	static HWND hEditMsg;
	static DWORD ThreadId;
	static char temp[128];

	switch(uMsg){
	case WM_INITDIALOG:
	{
		hButtonStartServer = GetDlgItem(hDlg, IDC_STARTSERVER);
		hButtonStartClient = GetDlgItem(hDlg, IDC_STARTCLIENT);
		hButtonSend = GetDlgItem(hDlg, IDC_SENDMSG);
		hEditMsg = GetDlgItem(hDlg, IDC_MSG);
		hEditStatus = GetDlgItem(hDlg, IDC_STATUS);
		SendMessage(hEditMsg, EM_SETLIMITTEXT, BUFSIZE, 0);
		EnableWindow(hButtonSend, FALSE);
		SetDlgItemText(hDlg, IDC_ADDR, "127.0.0.1");
		SetDlgItemText(hDlg, IDC_PORT, "9000");

		// ������ Ŭ���� ���
		WNDCLASS wndclass;
		wndclass.cbClsExtra = 0;
		wndclass.cbWndExtra = 0;
		wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
		wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wndclass.hInstance = hInst;
		wndclass.lpszClassName = "MyWindowClass";
		wndclass.lpszMenuName = NULL;
		wndclass.style = CS_HREDRAW | CS_VREDRAW;
		wndclass.lpfnWndProc = (WNDPROC)WndProc;
		if(!RegisterClass(&wndclass)) return -1;

		// ������ ����
		hDrawWnd = CreateWindow("MyWindowClass", 
			"�׸� �׸� ������", WS_CHILD, 
			15, 250, 545, 285,
			hDlg, (HMENU)NULL, hInst, NULL);
		if(hDrawWnd == NULL) return -1;
		ShowWindow(hDrawWnd, SW_SHOW);
		UpdateWindow(hDrawWnd);

		return TRUE;
	}
	case WM_COMMAND:
		switch(LOWORD(wParam)){
		case IDC_STARTSERVER:
			port = GetDlgItemInt(hDlg, IDC_PORT, NULL, FALSE);
			// ���� ������ ����
			hServerThread = CreateThread(NULL, 0, 
				Server, NULL, 0, &ThreadId);
			if(hServerThread == NULL){
				MessageBox(hDlg, "������ ������ �� �����ϴ�."
					"\r\n���α׷��� �����մϴ�.",
					"����", MB_ICONERROR);
				EndDialog(hDlg, 0);	
			}
			else{
				MessageBox(hDlg, "������ �����մϴ�.",
					"����", MB_ICONINFORMATION);
				CloseHandle(hServerThread);
				EnableWindow(hButtonStartServer, FALSE);
				EnableWindow(hButtonStartClient, FALSE);
				EnableWindow(hButtonSend, TRUE);
				SetFocus(hEditMsg);
			}
			return TRUE;
		case IDC_STARTCLIENT:
			GetDlgItemText(hDlg, IDC_ADDR, temp, 128);
			if(GetIPAddr(temp, &ipaddr) == FALSE){
				MessageBox(hDlg, "�߸��� �ּ��Դϴ�.",
					"����", MB_ICONERROR);
				return TRUE;
			}
			port = GetDlgItemInt(hDlg, IDC_PORT, NULL, FALSE);
			// Ŭ���̾�Ʈ ������ ����
			hClientThread = CreateThread(NULL, 0, 
				Client, NULL, 0, &ThreadId);
			if(hClientThread == NULL){
				MessageBox(hDlg, "Ŭ���̾�Ʈ�� ������ �� �����ϴ�."
					"\r\n���α׷��� �����մϴ�.",
					"����", MB_ICONERROR);
				EndDialog(hDlg, 0);	
			}
			else{
				MessageBox(hDlg, "Ŭ���̾�Ʈ�� �����մϴ�.",
					"����", MB_ICONINFORMATION);
				EnableWindow(hButtonStartServer, FALSE);
				EnableWindow(hButtonStartClient, FALSE);
				EnableWindow(hButtonSend, TRUE);
				SetFocus(hEditMsg);
			}
			return TRUE;
		case IDC_SENDMSG:
			// �б� �ϷḦ ��ٸ�
			WaitForSingleObject(hReadEvent, INFINITE);
			GetDlgItemText(hDlg, IDC_MSG, g_chatmsg.buf, BUFSIZE+1);
			// ���� �ϷḦ �˸�
			SetEvent(hWriteEvent);
			// �Էµ� �ؽ�Ʈ ��ü�� ���� ǥ��
			SendMessage(hEditMsg, EM_SETSEL, 0, -1);
			return TRUE;
		case IDC_SENDFILE:
			// ���ڰ� ������ �κ�
			return TRUE;
		case IDCANCEL: 
			// ���ø����̼� ����
			if(MessageBox(hDlg, "������ �����Ͻðڽ��ϱ�?", 
				"Ȯ��", MB_YESNO) == IDYES)
			{
				EndDialog(hDlg, 0);
			}
			return TRUE;
		}
		return FALSE;
	}
	return FALSE;
}

// ���� ����
DWORD WINAPI Server(LPVOID arg)
{
	int retval;

	// socket()
	SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if(listen_sock == INVALID_SOCKET) err_quit("socket()");	
	
	// bind()
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(port);
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	retval = bind(listen_sock, (SOCKADDR *)&serveraddr, sizeof(serveraddr));
	if(retval == SOCKET_ERROR) err_quit("bind()");
	
	// listen()
	retval = listen(listen_sock, SOMAXCONN);
	if(retval == SOCKET_ERROR) err_quit("listen()");

	SOCKET client_sock;
	SOCKADDR_IN clientaddr;
	int addrlen;
	HANDLE hThread[2];
	DWORD ThreadId[2];
	char temp[128];

	while(1)
	{
		// accept()
		addrlen = sizeof(clientaddr);
		client_sock = accept(listen_sock, (SOCKADDR *)&clientaddr, &addrlen);
		if(client_sock == INVALID_SOCKET)
			err_quit("accept()");
		
		wsprintf(temp, "Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d\n", 
			inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));
		MessageBox(NULL, temp, "�˸�", MB_ICONINFORMATION);

		// �б� ������ ����
		hThread[0] = CreateThread(NULL, 0, ReadThread, 
			(LPVOID)client_sock, 0, &ThreadId[0]);
		// ���� ������ ����
		hThread[1] = CreateThread(NULL, 0, WriteThread, 
			(LPVOID)client_sock, 0, &ThreadId[1]);

		if(hThread[0] == NULL || hThread[1] == NULL){
			MessageBox(NULL, "�����带 ������ �� �����ϴ�."
				"\r\n���α׷��� �����մϴ�.",
				"����", MB_ICONERROR);
			exit(-1);
		}

		bStart = TRUE;
		g_sock = client_sock;

		// ������ ���� ���
		retval = WaitForMultipleObjects(2, hThread, FALSE, INFINITE);
		retval -= WAIT_OBJECT_0;
		if(retval == 0)
			TerminateThread(hThread[1], -1);
		else
			TerminateThread(hThread[0], -1);
		CloseHandle(hThread[0]);
		CloseHandle(hThread[1]);

		bStart = FALSE;

		MessageBox(NULL, "Ŭ���̾�Ʈ�� ������ �������ϴ�",
			"�˸�", MB_ICONINFORMATION);
		EnableWindow(hButtonSend, FALSE);
	}

	// closesocket()
	closesocket(listen_sock);

	return 0;
}

// Ŭ���̾�Ʈ ����
DWORD WINAPI Client(LPVOID arg)
{
	int retval;

	// socket()
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock == INVALID_SOCKET) err_quit("socket()");	
	
	// connect()
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(port);
	serveraddr.sin_addr = ipaddr;
	retval = connect(sock, (SOCKADDR *)&serveraddr, sizeof(serveraddr));
	if(retval == SOCKET_ERROR) err_quit("connect()");

	HANDLE hThread[2];
	DWORD ThreadId[2];

	// �б� ������ ����
	hThread[0] = CreateThread(NULL, 0, ReadThread, 
		(LPVOID)sock, 0, &ThreadId[0]);
	// ���� ������ ����
	hThread[1] = CreateThread(NULL, 0, WriteThread, 
		(LPVOID)sock, 0, &ThreadId[1]);

	if(hThread[0] == NULL || hThread[1] == NULL){
		MessageBox(NULL, "�����带 ������ �� �����ϴ�."
			"\r\n���α׷��� �����մϴ�.",
			"����", MB_ICONERROR);
		exit(-1);
	}

	bStart = TRUE;
	g_sock = sock;

	// ������ ���� ���
	retval = WaitForMultipleObjects(2, hThread, FALSE, INFINITE);
	retval -= WAIT_OBJECT_0;
	if(retval == 0)
		TerminateThread(hThread[1], -1);
	else
		TerminateThread(hThread[0], -1);
	CloseHandle(hThread[0]);
	CloseHandle(hThread[1]);

	bStart = FALSE;

	MessageBox(NULL, "������ ������ �������ϴ�",
		"�˸�", MB_ICONINFORMATION);
	EnableWindow(hButtonSend, FALSE);

	return 0;
}

// ������ �ޱ�
DWORD WINAPI ReadThread(LPVOID arg)
{
	SOCKET sock = (SOCKET)arg;
	CHATMSG chatmsg;
	DRAWMSG drawmsg;
	int type;
	int retval;

	while(1){
		retval = recvn(sock, (char *)&type, sizeof(type), 0);
		if(retval == 0 || retval == SOCKET_ERROR){
			break;
		}

		if(type == CHATTING){
			retval = recvn(sock, chatmsg.buf, sizeof(g_chatmsg.buf), 0);
			if(retval == 0 || retval == SOCKET_ERROR)
				break;
			DisplayText("[���� �޽���] %s\r\n", chatmsg.buf);
		}

		else if(type == DRAWING){
			retval = recvn(sock, (char *)&drawmsg, sizeof(drawmsg), 0);
			if(retval == 0 || retval == SOCKET_ERROR)
				break;
			SendMessage(hDrawWnd, WM_DRAWIT,
				MAKEWPARAM(drawmsg.x0, drawmsg.y0), 
				MAKELPARAM(drawmsg.x1, drawmsg.y1));
		}
	}

	// closesocket()
	closesocket(sock);

	return 0;
}

// ������ ������
DWORD WINAPI WriteThread(LPVOID arg)
{
	SOCKET sock = (SOCKET)arg;
	int type;
	int retval;

	// ������ ������ ���
	while(1){
		// ���� �ϷḦ ��ٸ�
		WaitForSingleObject(hWriteEvent, INFINITE);

		// ���ڿ� ���̰� 0�̸� ������ ����
		if(strlen(g_chatmsg.buf) == 0){
			// ������ ��ư Ȱ��ȭ
			EnableWindow(hButtonSend, TRUE);
			// �б� �ϷḦ �˸�
			SetEvent(hReadEvent);
			continue;
		}

		// ������ ������
		type = CHATTING;
		retval = send(sock, (char *)&type, sizeof(type), 0);
		if(retval == SOCKET_ERROR){
			break;
		}
		retval = send(sock, (char *)&g_chatmsg.buf, sizeof(g_chatmsg.buf), 0);
		if(retval == SOCKET_ERROR){
			break;
		}
		DisplayText("[���� �޽���] %s\r\n", g_chatmsg.buf);

		// ������ ��ư Ȱ��ȭ
		EnableWindow(hButtonSend, TRUE);
		// �б� �ϷḦ �˸�
		SetEvent(hReadEvent);
	}

	// closesocket()
	closesocket(sock);

	return 0;
}

// ������ �޽��� ó��
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg,
	WPARAM wParam, LPARAM lParam)
{
	HDC hDC;
	PAINTSTRUCT ps;
	RECT rect;
	int cx, cy;
	static HDC hDCMem;
	static HBITMAP hBitmap;
	static int x0, y0;
	static int x1, y1;
	static BOOL bDrawing = FALSE;
	DRAWMSG drawmsg;
	int type = DRAWING;

	switch(uMsg){
	case WM_CREATE:
		hDC = GetDC(hWnd);
		// ȭ���� ������ ��Ʈ�� ����
		cx = GetDeviceCaps(hDC, HORZRES);
		cy = GetDeviceCaps(hDC, VERTRES);
		hBitmap = CreateCompatibleBitmap(hDC, cx, cy);
		// �޸� DC ����
		hDCMem = CreateCompatibleDC(hDC);
		// �޸� DC�� ��Ʈ�� ����
		SelectObject(hDCMem, hBitmap);
		// �޸� DC ȭ���� ������� ĥ��
		SelectObject(hDCMem, GetStockObject(WHITE_BRUSH));
		SelectObject(hDCMem, GetStockObject(WHITE_PEN));
		Rectangle(hDCMem, 0, 0, cx, cy);
		ReleaseDC(hWnd, hDC);
		return 0;
	case WM_LBUTTONDOWN:
		x0 = LOWORD(lParam);
		y0 = HIWORD(lParam);
		bDrawing = TRUE;
		return 0;
	case WM_MOUSEMOVE:
		if(bDrawing){
			hDC = GetDC(hWnd);
			x1 = LOWORD(lParam);
			y1 = HIWORD(lParam);

			// ȭ�鿡 �׸���
			SelectObject(hDC, GetStockObject(BLACK_PEN));
			MoveToEx(hDC, x0, y0, NULL);
			LineTo(hDC, x1, y1);
			// �޸� ��Ʈ�ʿ� �׸���
			SelectObject(hDCMem, GetStockObject(BLACK_PEN));
			MoveToEx(hDCMem, x0, y0, NULL);
			LineTo(hDCMem, x1, y1);

			if(bStart){
				// �� �׸��� ���� ������
				type = DRAWING;
				send(g_sock, (char *)&type, sizeof(type), 0);
				drawmsg.x0 = x0;
				drawmsg.y0 = y0;
				drawmsg.x1 = x1;
				drawmsg.y1 = y1;
				send(g_sock, (char *)&drawmsg, sizeof(drawmsg), 0);
			}
			
			x0 = x1;
			y0 = y1;
			ReleaseDC(hWnd, hDC);
		}
		return 0;
	case WM_LBUTTONUP:
		bDrawing = FALSE;
		return 0;
	case WM_DRAWIT:
		hDC = GetDC(hWnd);

		// ȭ�鿡 �׸���
		SelectObject(hDC, GetStockObject(BLACK_PEN));
		MoveToEx(hDC, LOWORD(wParam), HIWORD(wParam), NULL);
		LineTo(hDC, LOWORD(lParam), HIWORD(lParam));
		// �޸� ��Ʈ�ʿ� �׸���
		SelectObject(hDCMem, GetStockObject(BLACK_PEN));
		MoveToEx(hDCMem, LOWORD(wParam), HIWORD(wParam), NULL);
		LineTo(hDCMem, LOWORD(lParam), HIWORD(lParam));

		ReleaseDC(hWnd, hDC);
		return 0;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		// �޸� ��Ʈ�ʿ� ����� �׸��� ȭ�鿡 �����ϱ�
		GetClientRect(hWnd, &rect);
		BitBlt(hDC, 0, 0, rect.right - rect.left,
			rect.bottom - rect.top, hDCMem, 0, 0, SRCCOPY);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		DeleteObject(hBitmap);
		DeleteDC(hDCMem);
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
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

// ����Ʈ ��Ʈ�ѿ� ���ڿ� ���
void DisplayText(char *fmt, ...)
{
	va_list arg;
	va_start(arg, fmt);
	
	char cbuf[BUFSIZE+50];
	vsprintf(cbuf, fmt, arg);
	
	int nLength = GetWindowTextLength(hEditStatus);
	SendMessage(hEditStatus, EM_SETSEL, nLength, nLength);
	SendMessage(hEditStatus, EM_REPLACESEL, FALSE, (LPARAM)cbuf);
	
	va_end(arg);
}

// ������ �̸� -> IP �ּ�
BOOL GetIPAddr(char *name, IN_ADDR *addr)
{
	HOSTENT *ptr = gethostbyname(name);
	if(ptr == NULL)
		return FALSE;
	memcpy(addr, ptr->h_addr, ptr->h_length);
	return TRUE;
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