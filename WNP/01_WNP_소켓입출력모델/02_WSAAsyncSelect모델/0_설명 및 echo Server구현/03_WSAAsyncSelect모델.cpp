
// WSAAsyncSelect �� 

 /* 
	WSAAsyncSelect() �Լ��� �ٽ����� ������ �Ѵٴ� �濡�� ���� �̸���

    �� ���� ����ϸ� ������ �޽��� ���·� ���ϰ� ���õ� ��Ʈ��ũ
	�̺�Ʈ�� ó���� �� �ִ�. 
	��� ���ϰ� ���� �޽����� �ϳ��� ������, �� �ϳ��� ������ ���ν���
	�� ���޵ǹǷ� ��Ƽ�����带 ������� �ʰ� ���� ������
	ó�� �� �� �ִ�. 




//-----------------------------------
// 01  ���ۿ��� 
//-----------------------------------

  ����� ����

  1) WSAAsyncSelect() �Լ��� �̿��Ͽ� ������ ���� ������ �޽����� ó��
     �� ��Ʈ��ũ �̺�Ʈ�� ����Ѵ�.
	 ex) ������ ���� �����͸� �����ų� ���� �� �ִ� ��Ȳ�� �Ǹ� Ư�� 
	     ������ �޽����� �˷��޶�� ������ ����Ѵ�.

  2) ����� ��Ʈ��ũ �̺�Ʈ�� �߻��ϸ� ������ �޽����� �߻��ϰ� ������ 
     ���ν����� ȣ��ȴ�.

  3) ������ ���ν��������� ���� �޽����� ������ ���� ������ ���� �Լ��� 
     ȣ���Ͽ� ó���Ѵ�.


  WSAAsyncSelect() �Լ� ���� 

  int  WSAAsyncSelect (  SOCKET s, HWND hwnd, 
						unsigned int wMsg, long lEvent);

  1) ó���ϰ��� �ϴ� ����
  2) �޽����� ���� �����츦 ��Ÿ���� �ڵ鰪
  3) �����찡 ���� �޽��� 
     ������ ���� �޽����� ���� ���ǵǾ� ���� �����Ƿ� ����� ������ 
	 �޽����� �̿��Ѵ�.

  4) ó���� ��Ʈ��ũ �̺�Ʈ ���Ḧ ��Ʈ ����ũ �������� ��Ÿ����.

     FD_ACCEPT		: Ŭ���̾�Ʈ�� �����ϸ� ������ �޽��� �߻���Ŵ
	 FD_READ		: ������ ���� �����ϸ� ������ �޽��� �߻���Ŵ
	 FD_WRITE		: ������ �۽��� �����ϸ� ������ �޽��� �߻���Ŵ
	 FD_CLOSE		: ��밡 ������ �����ϸ� ������ �޽��� �߻���Ŵ
	 FD_CONNECT		: ������ �Ϸ�Ǹ� ������ �޽����� �߻���Ŵ
	 


  ex) ���� S�� ���� FD_READ & FD_WRITE �̺�Ʈ�� ����ϴ� ��
  
  #define	WM_SOCKET (WM_USER + 1) 
  ..
  WSAAsyncSelect(s, hwnd, WM_SOCKET, FD_READ|FD_WRITE);


  * ���� ������

  - WSAAsyncSelect() �Լ��� ȣ���ϸ� �ش� ������ �ڵ����� �ͺ��ŷ ���
    �� ��ȯ��
	���ŷ ���� �޽��� ������ ������ų ���ɼ��� �ֱ� ������ �ͺ��ŷ
	��常 ���ǵ��� �����Ǿ� �ִ�.

  - accept() �Լ��� �����ϴ� ������ ���� ��� ���ϰ� ������ ������ ��
    �ϰ� �ȴ�.
	���� ��� ������ ���� �����͸� �ۼ������� �����Ƿ� FD_READ, FD_WRITE
	�̺�Ʈ�� ó������ �ʴ´�.
	�ݸ� �ڼ����� FD_READ |FD_WRITE �̺�Ʈ�� ó���ؾ� �ϹǷ�, 
	�ٽ� WSAAsyncSelect() �Լ��� ȣ���ؼ� �Ӽ��� �����ؾ� �Ѵ�.

  - ������ �޽����� �����Ͽ� ���� �Լ��� ȣ���ϸ� ��κ� ����������
    WSAEWOULDBLOCK ���� �ڵ尡 �߻��ϴ� ��쵵 �����Ƿ� �̸� üũ�Ѵ�.

  - ������ �޽����� �޾��� �� ������ ���� �Լ��� ȣ������ ������, ���� ��
    ���� ���� ������ �޽����� �߻����� �ʴ´�.
	ex) FD_READ �̺�Ʈ�� �����Ͽ� recv() �Լ��� ȣ������ ������, ������ 
	    ���Ͽ� ���Ͽ� FD_READ �̺�Ʈ�� �� �̻� �߻����� �ʴ´�.

    ���� ������ �޽����� �߻��ϸ� �ش�Ǵ� ���� �Լ��� ȣ���ؾ� �Ѵ�.

    * �̺�Ʈ �����Լ� 

     FD_ACCEPT		: accept()
	 FD_READ		: recv() , recvfrom()
	 FD_WRITE		: send(), sendto()
	 FD_CLOSE		: ����
	 FD_CONNECT		: ���� 


    * ��Ʈ��ũ �̺�Ʈ �߻��� ������ ���ν����� ���� ���޵Ǵ� ����

	LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM w , LPARAM l);

    1) �޽����� �߻��� ������ �ڵ�
	2) WSAAsyncSelect() �Լ� ȣ��� ����� ����� ���� �޽��� 
	3) ��Ʈ��ũ �̺�Ʈ�� �߻��� ����
	4) ���� 16��Ʈ : �߻��� ��Ʈ��ũ �̺�Ʈ
	   ���� 16��Ʈ : ���� �ڵ� 

		#define WSAGETSELECTERROR(lParam) HIWORD(lParam)
		#define WSAGETSELECTEVENT(lParam) LOWORD(lParam)

  [ ��  �� ]

  echo ���� ���� 
*/


#pragma comment(linker, "/subsystem:console")
#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>

#define BUFSIZE 512
#define WM_SOCKET (WM_USER+1)

// ���� ���� ������ ���� ����ü
struct SOCKETINFO
{
	SOCKET sock;
	char buf[BUFSIZE+1];
	int recvbytes;
	int sendbytes;
	BOOL recvdelayed;
	SOCKETINFO *next;
};

SOCKETINFO *SocketInfoList;

// ������ �޽��� ó�� �Լ�
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void ProcessSocketMessage(HWND, UINT, WPARAM, LPARAM);

// ���� ���� �Լ�
BOOL AddSocketInfo(SOCKET sock);
SOCKETINFO *GetSocketInfo(SOCKET sock);
void RemoveSocketInfo(SOCKET sock);

// ���� ��� �Լ�
void err_quit(char *msg);
void err_display(char *msg);
void err_display(int errcode);

int main(int argc, char* argv[])
{
	int retval;

	// ������ Ŭ���� ���
	WNDCLASS wndclass;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hInstance = NULL;
	wndclass.lpfnWndProc = (WNDPROC)WndProc;
	wndclass.lpszClassName = "MyWindowClass";
	wndclass.lpszMenuName = NULL;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	if(!RegisterClass(&wndclass)) return -1;

	// ������ ����
	HWND hWnd = CreateWindow("MyWindowClass", "TCP ����",
		WS_OVERLAPPEDWINDOW, 0, 0, 600, 300,
		NULL, (HMENU)NULL, NULL, NULL);
	if(hWnd == NULL) return -1;
	ShowWindow(hWnd, SW_SHOWNORMAL);
	UpdateWindow(hWnd);

	// ���� �ʱ�ȭ
	WSADATA wsa;
	if(WSAStartup(MAKEWORD(2,2), &wsa) != 0)
		return -1;

	// socket()
	SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if(listen_sock == INVALID_SOCKET) err_quit("socket()");

	// WSAAsyncSelect()
	retval = WSAAsyncSelect(listen_sock, hWnd, 
		WM_SOCKET, FD_ACCEPT|FD_CLOSE);
	if(retval == SOCKET_ERROR) err_quit("WSAAsyncSelect()");

	// bind()
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(9000);
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	retval = bind(listen_sock, (SOCKADDR *)&serveraddr, sizeof(serveraddr));
	if(retval == SOCKET_ERROR) err_quit("bind()");
	
	// listen()
	retval = listen(listen_sock, SOMAXCONN);
	if(retval == SOCKET_ERROR) err_quit("listen()");

	// �޽��� ����
	MSG msg;
	while(GetMessage(&msg, 0, 0, 0) > 0){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// ���� ����
	WSACleanup();
	return msg.wParam;
}

// ������ �޽��� ó��
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, 
	WPARAM wParam, LPARAM lParam)
{
	switch(uMsg){
	case WM_SOCKET: // ���� ���� ������ �޽���
		ProcessSocketMessage(hWnd, uMsg, wParam, lParam);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

// ���� ���� ������ �޽��� ó��
void ProcessSocketMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// ������ ��ſ� ����� ����
	SOCKETINFO *ptr;
	SOCKET client_sock;
	SOCKADDR_IN clientaddr;
	int addrlen;
	int retval;

	// ���� �߻� ���� Ȯ��
	if(WSAGETSELECTERROR(lParam)){
		err_display(WSAGETSELECTERROR(lParam));
		RemoveSocketInfo(wParam);
		return;
	}

	// �޽��� ó��
	switch(WSAGETSELECTEVENT(lParam))
	{
	case FD_ACCEPT:
		addrlen = sizeof(clientaddr);
		client_sock = accept(wParam, (SOCKADDR *)&clientaddr, &addrlen);
		if(client_sock == INVALID_SOCKET){
			if(WSAGetLastError() != WSAEWOULDBLOCK)
				err_display("accept()");
			return;
		}
		printf("[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d\n", 
			inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));
		AddSocketInfo(client_sock);
		retval = WSAAsyncSelect(client_sock, hWnd, 
			WM_SOCKET, FD_READ|FD_WRITE|FD_CLOSE);
		if(retval == SOCKET_ERROR){
			err_display("WSAAsyncSelect()");
			RemoveSocketInfo(client_sock);
		}
		break;
	case FD_READ:
		ptr = GetSocketInfo(wParam);
		if(ptr->recvbytes > 0){
			ptr->recvdelayed = TRUE;
			return;
		}
		// ������ �ޱ�
		retval = recv(ptr->sock, ptr->buf, BUFSIZE, 0);
		if(retval == SOCKET_ERROR){
			if(WSAGetLastError() != WSAEWOULDBLOCK){
				err_display("recv()");
				RemoveSocketInfo(wParam);
			}
			return;
		}
		ptr->recvbytes = retval;
		// ���� ������ ���
		ptr->buf[retval] = '\0';
		addrlen = sizeof(clientaddr);
		getpeername(wParam, (SOCKADDR *)&clientaddr, &addrlen);
		printf("[TCP/%s:%d] %s\n", inet_ntoa(clientaddr.sin_addr),
			ntohs(clientaddr.sin_port), ptr->buf);
	case FD_WRITE:
		ptr = GetSocketInfo(wParam);
		if(ptr->recvbytes <= ptr->sendbytes)
			return;
		// ������ ������
		retval = send(ptr->sock, ptr->buf + ptr->sendbytes, 
			ptr->recvbytes - ptr->sendbytes, 0);
		if(retval == SOCKET_ERROR){
			if(WSAGetLastError() != WSAEWOULDBLOCK){
				err_display("send()");
				RemoveSocketInfo(wParam);
			}
			return;
		}
		ptr->sendbytes += retval;
		// ���� �����͸� ��� ���´��� üũ
		if(ptr->recvbytes == ptr->sendbytes){
			ptr->recvbytes = ptr->sendbytes = 0;
			if(ptr->recvdelayed){
				ptr->recvdelayed = FALSE;
				PostMessage(hWnd, WM_SOCKET, wParam, FD_READ);
			}
		}
		break;
	case FD_CLOSE:
		RemoveSocketInfo(wParam);
		break;
	}
}

// ���� ���� �߰�
BOOL AddSocketInfo(SOCKET sock)
{
	SOCKETINFO *ptr = new SOCKETINFO;
	if(ptr == NULL){
		printf("[����] �޸𸮰� �����մϴ�!\n");
		return FALSE;
	}

	ptr->sock = sock;
	ptr->recvbytes = 0;
	ptr->sendbytes = 0;
	ptr->recvdelayed = FALSE;
	ptr->next = SocketInfoList;
	SocketInfoList = ptr;

	return TRUE;
}

// ���� ���� ���
SOCKETINFO *GetSocketInfo(SOCKET sock)
{
	SOCKETINFO *ptr = SocketInfoList;

	while(ptr){
		if(ptr->sock == sock)
			return ptr;
		ptr = ptr->next;
	}

	return NULL;
}

// ���� ���� ����
void RemoveSocketInfo(SOCKET sock)
{
	// Ŭ���̾�Ʈ ���� ���
	SOCKADDR_IN clientaddr;
	int addrlen = sizeof(clientaddr);
	getpeername(sock, (SOCKADDR *)&clientaddr, &addrlen);
	printf("[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d\n", 
		inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

	SOCKETINFO *curr = SocketInfoList;
	SOCKETINFO *prev = NULL;

	while(curr){
		if(curr->sock == sock){
			if(prev)
				prev->next = curr->next;
			else
				SocketInfoList = curr->next;
			closesocket(curr->sock);
			delete curr;
			return;
		}
		prev = curr;
		curr = curr->next;
	}
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
	printf("[%s] %s", msg, (LPCTSTR)lpMsgBuf);
	LocalFree(lpMsgBuf);
}

// ���� �Լ� ���� ���
void err_display(int errcode)
{
	LPVOID lpMsgBuf;
	FormatMessage( 
		FORMAT_MESSAGE_ALLOCATE_BUFFER|
		FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, errcode,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	printf("[����] %s", (LPCTSTR)lpMsgBuf);
	LocalFree(lpMsgBuf);
}

