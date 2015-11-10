
// WSAAEventSelect �� 

 /* 
	WSAAEventSelect() �Լ��� �ٽ����� ������ �Ѵٴ� �濡�� ���� �̸���

	�̺�Ʈ ��ü�� ���� ��Ʈ��ũ �̺�Ʈ�� �����Ѵ�.
	�� ���Ͽ� ���� �̺�Ʈ ��ü�� �����ϰ�, �� �̺�Ʈ ��ü�� ���������ν�
	��Ƽ�����带 ������� �ʰ� ���� ���� ������ ó���� �� �ִ�. 





//-----------------------------------
// 01  ���ۿ��� 
//-----------------------------------

  �� ���ϸ��� �̺�Ʈ ��ü�� �ϳ��� �����Ͽ� ¦����θ�,
  ��Ʈ��ũ �̺�Ʈ�� �߻��� ������ �̺�Ʈ ��ü�� ��ȣ���°� �ȴ�.

  ���� �̺�Ʈ ��ü�� ��ȣ���¸� ���� ��Ʈ��ũ �̺�Ʈ �߻��� ����
  �� �� �ִ�.

  ������, �̰͸����δ� ��� ������ �̺�Ʈ�� �߻��Ǿ����� Ȥ��
  � ������ �߻��ߴ��� �� �� ����. 


  ����Լ� 

  �̺�Ʈ��ü ������ ����			: WSACreateEvent(), WSACloseEvent()
  ���ϰ� �̺�Ʈ ��ü ¦����			: WSAEventSelect()
  �̺�Ʈ ��ü�� ��ȣ ���� �����ϱ�	: WSAWaitForMultipleEvents()
  ��ü���� ��Ʈ��ũ �̺�Ʈ �˾Ƴ��� : WSAEnumNetworkEvents()


  * ����� ����
  1) ������ ������ ������ WSACreateEvnet()�Լ��� �̿��Ͽ� �̺�Ʈ 
     ��ü�� �����Ѵ�.

  2) WSAEventSelect() �Լ��� �̿��Ͽ� ���ϰ� �̺�Ʈ ��ü�� ¦������ ���ÿ�
     ó���� ��Ʈ��ũ �̺�Ʈ�� ����Ѵ�.
	 ex) ������ ���� �����͸� �����ų� ���� �� �ִ� ��Ȳ�� �Ǹ� �̺�Ʈ
	     ��ü�� ��ȣ ���·� �����϶�� ������ ����Ѵ�.

  3) WSAWaitForMultipleEvents() �Լ��� ȣ���Ͽ� �̺�Ʈ ��ü�� ��ȣ���°� 
     �Ǳ⸦ ��ٸ���.
	 ����� ��Ʈ��ũ �̺�Ʈ�� �߻��ϸ� �ش� ���ϰ� ������ �̺�Ʈ ��ü�� 
	 ��ȣ���°� �ȴ�.

  4) WSAEnumNetworkEvents() �Լ��� ȣ���Ͽ� �߻��� ��Ʈ��ũ �̺�Ʈ�� 
     �˾Ƴ���, ������ ���� �Լ��� ȣ���Ͽ� ó���Ѵ�.



  * �̺�Ʈ ��ü�� ������ ���� 
  WSACreateEvents() �Լ��� �̺�Ʈ ��ü�� �����ϴ� ������ �Ѵ�.
  �̶� �����Ǵ� �̺�Ʈ ��ü�� �׻� ���� ���� �̺�Ʈ�̴�.
  ���ȣ ���·� �����Ѵ�.
  ����� ���� �̺�Ʈ ��ü�� WSACloseEvents() �Լ��� ȣ���Ͽ� �����Ѵ�.

  WSAEVENT WSACreateEvents()
  // ���� :�̺�Ʈ ��ü �ڵ�, ���� : WSA_INVALID_EVENT

  BOOL WSACloseEvent(WSAEVENT hEvent)
  // ���� : TRUE	���� : FALSE



  * ���ϰ� �̺�Ʈ ��ü ¦���� 
  int WSAEventSelect( SOCKET s, WSAEVENT hEventObject, long lNetWorkEvents)

  1) ó���ϰ��� �ϴ� ����
  2) ���ϰ� ������ų �̺�Ʈ ��ü�� �ڵ�
  3) ó���� ��Ʈ��ũ �̺�Ʈ ���� ��Ʈ ����ũ ����ó�� 
     - WSAAsyncSelect�� ���� 


     FD_ACCEPT		: Ŭ���̾�Ʈ�� �����ϸ� ������ �޽��� �߻���Ŵ
	 FD_READ		: ������ ���� �����ϸ� ������ �޽��� �߻���Ŵ
	 FD_WRITE		: ������ �۽��� �����ϸ� ������ �޽��� �߻���Ŵ
	 FD_CLOSE		: ��밡 ������ �����ϸ� ������ �޽��� �߻���Ŵ
	 FD_CONNECT		: ������ �Ϸ�Ǹ� ������ �޽����� �߻���Ŵ


  ex) ���� s�� �̺�Ʈ ��ü�� ¦����, FD_READ | FD_WRITE �̺�Ʈ�� ���
      �ϴ� �� 

      WSAEVENT	hEvent	= WSACreateEvent();
	  WSAEVENTSelect( s, hEvent, FD_READ| FD_WRITE);

      �� �Լ� ���� ������

      - WSAEventSlect() �Լ� ȣ�� �� �ش� ������ �ڵ����� �ͺ��ŷ 
	    ���� ��ȯ�ȴ�.

      - accept() �Լ��� �����ϴ� ������ ���� ��� ���ϰ� ������ �Ӽ�
	    �� ���ϹǷ� �ڼ����� �ٽ� WSAEventSlect() �Լ��� ȣ���ؼ� 
		�Ӽ��� �����ؾ� �Ѵ�. 


   * �̺�Ʈ ��ü�� ��ȣ ���� ���� 

   WSAWaitForMultipleEvents() �Լ��� ���� �̺�Ʈ ��ü�� ���ÿ� ����
   �ϴ� ��� ����

   DWORD WSAWaitForMultipleEvents( DWORD cEvents, const WSAEVENT *lphEvents,
			BOOL fWaitAll, DWORD dwTimeout, BOOL fAlertable);

   - 1),2) �̺�Ʈ ��ü�� �ڵ��� ��� �迭�� �����ؾ� �Ѵ�. 
     1)�� �迭 ���� ���� (�ִ� ���� : WSA_MAXIMUM_WAIT_EVENTS(64)
	 2) �� �迭�� ���� �ּҸ� ��Ÿ����. 

   - 3) TRUE  : ��� ��ü�� ��ȣ ���°� �Ǹ� ����
        FALSE : �ϳ��� ��ü�� ��ȣ ���°� �Ǹ� ����

   - 4) ��� �ð����� �и��� ���� ��� 
        �� �ð����� ������ �������� �ʴ��� �Լ� ����
		WSA_INFINITE : ������ ��� 

   - 5)����� �Ϸ� ��ƾ�� ���õ� �κ�, ����� ������ FALSE


   * ��ü���� ��Ʈ��ũ �̺�Ʈ �˾Ƴ��� 

   int WSAEnumNetworkEvents( SOCKET s, WSAEVENT hEventObject, 
							 LPWSANETWORKEVENTS lpNetworkEvents);

   - 1) ��� ����
     2) ��� ���ϰ� ¦����� �̺�Ʈ ��ü �ڵ�
	    �ڵ����� �̺�Ʈ ��ü�� ���ȣ ���°� �ȴ�. 
		������� �������� NULL���� �ش�.

     3) �߻��� ��Ʈ��ũ �̺�Ʈ�� ���� ������ ����ȴ�. 

     typedef strut _WSANETWORKEVENTS{
		long lNetworkEvents;
		int  iErrocode[FD_MAX_EVNETS];
	 }WSANETWORKEVENTS, *LPWSANNETWORKEVENTS;

     

    1) ���յ� ���·� ����
	2) ���� ���� 
     FD_ACCEPT		: FD_ACCEPT_BIT
	 FD_READ		: FD_READ_BIT
	 FD_WRITE		: FD_WRITE_BIT
	 FD_CLOSE		: FD_CLOSE_BIT
	 FD_CONNECT		: FD_CONNECT_BIT 


    ex) 
	SOCKET				s;
	WSAEVENT			hEvent;
	WSANETWORKEVENTS	NetworkEvents;

    WSAEnumNetworkEvents(s, hEvent, &NetworkEvents);

    // FD_ACCEPT ó��
	if( NetworkEvents.lNetworkEvents & FD_ACCEPT)
	{
		if( NetworkEvents.iErrocode[FD_ACCEPT_BIT]; != 0 )
		{
			// ���� �ڵ� ���
		}
		else
		{
			// �Լ� ȣ�� 
		}
	}


  [ �� �� ]

*/

#pragma comment(linker, "/subsystem:console")
#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>

#define BUFSIZE 512

// ���� ���� ������ ���� ����ü
struct SOCKETINFO
{
	SOCKET sock;
	char buf[BUFSIZE+1];
	int recvbytes;
	int sendbytes;
};

int nTotalSockets = 0;
SOCKETINFO *SocketInfoArray[WSA_MAXIMUM_WAIT_EVENTS];
WSAEVENT EventArray[WSA_MAXIMUM_WAIT_EVENTS];

// ���� ���� �Լ�
BOOL AddSocketInfo(SOCKET sock);
void RemoveSocketInfo(int nIndex);

// ���� ��� �Լ�
void err_quit(char *msg);
void err_display(char *msg);
void err_display(int errcode);

int main(int argc, char* argv[])
{
	int retval;

	// ���� �ʱ�ȭ
	WSADATA wsa;
	if(WSAStartup(MAKEWORD(2,2), &wsa) != 0)
		return -1;

	// socket()
	SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if(listen_sock == INVALID_SOCKET)
		err_quit("socket()");

	// ���� ���� �߰�
	if(AddSocketInfo(listen_sock) == FALSE)
		return -1;

	// WSAEventSelect()
	retval = WSAEventSelect(listen_sock, EventArray[nTotalSockets-1], FD_ACCEPT | FD_CLOSE);
	if(retval == SOCKET_ERROR) 
		err_quit("WSAEventSelect()");

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
	if(retval == SOCKET_ERROR) 
		err_quit("listen()");

	// ������ ��ſ� ����� ����
	int index;
	WSANETWORKEVENTS NetworkEvents;
	SOCKET client_sock;
	SOCKADDR_IN clientaddr;
	int addrlen;

	while(1){
		// �̺�Ʈ ��ü ����
		index = WSAWaitForMultipleEvents(nTotalSockets, EventArray, FALSE, WSA_INFINITE, FALSE);
		if(index == WSA_WAIT_FAILED)
		{
			err_display("WSAWaitForMultipleEvents()");
			continue;
		}
		index -= WSA_WAIT_EVENT_0;

		// ��ü���� ��Ʈ��ũ �̺�Ʈ �˾Ƴ���
		retval = WSAEnumNetworkEvents(SocketInfoArray[index]->sock, EventArray[index], &NetworkEvents);
		if(retval == SOCKET_ERROR)
		{
			err_display("WSAEnumNetworkEvents()");
			continue;
		}

		// FD_ACCEPT �̺�Ʈ ó��
		if(NetworkEvents.lNetworkEvents & FD_ACCEPT)
		{
			if(NetworkEvents.iErrorCode[FD_ACCEPT_BIT] != 0)
			{
				err_display(NetworkEvents.iErrorCode[FD_ACCEPT_BIT]);
				continue;
			}

			addrlen = sizeof(clientaddr);
			client_sock = accept(SocketInfoArray[index]->sock, 
				(SOCKADDR *)&clientaddr, &addrlen);
			if(client_sock == INVALID_SOCKET)
			{
				err_display("accept()");
				continue;
			}
			printf("[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d\n", 
				inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

			if(nTotalSockets >= WSA_MAXIMUM_WAIT_EVENTS)
			{
				printf("[����] �� �̻� ������ �޾Ƶ��� �� �����ϴ�!\n");
				closesocket(client_sock);
				continue;
			}

			if(AddSocketInfo(client_sock) == FALSE)
				continue;

			retval = WSAEventSelect(client_sock, EventArray[nTotalSockets-1], FD_READ|FD_WRITE | FD_CLOSE);
			if(retval == SOCKET_ERROR) err_quit("WSAEventSelect()");
		}

		// FD_READ, FD_WRITE �̺�Ʈ ó��
		if(NetworkEvents.lNetworkEvents & FD_READ || NetworkEvents.lNetworkEvents & FD_WRITE)
		{
			if(NetworkEvents.lNetworkEvents & FD_READ && NetworkEvents.iErrorCode[FD_READ_BIT] != 0)
			{
				err_display(NetworkEvents.iErrorCode[FD_READ_BIT]);
				continue;
			}
			if(NetworkEvents.lNetworkEvents & FD_WRITE && NetworkEvents.iErrorCode[FD_WRITE_BIT] != 0)
			{
				err_display(NetworkEvents.iErrorCode[FD_WRITE_BIT]);
				continue;
			}
			
			SOCKETINFO *ptr = SocketInfoArray[index];

			if(ptr->recvbytes == 0)
			{
				// ������ �ޱ�
				retval = recv(ptr->sock, ptr->buf, BUFSIZE, 0);
				if(retval == SOCKET_ERROR)
				{
					if(WSAGetLastError() != WSAEWOULDBLOCK)
					{
						err_display("recv()");
						RemoveSocketInfo(index);
					}
					continue;
				}
				ptr->recvbytes = retval;
				// ���� ������ ���
				ptr->buf[retval] = '\0';
				addrlen = sizeof(clientaddr);
				getpeername(ptr->sock, (SOCKADDR *)&clientaddr, &addrlen);
				printf("[TCP/%s:%d] %s\n", inet_ntoa(clientaddr.sin_addr),
					ntohs(clientaddr.sin_port), ptr->buf);
			}

			if(ptr->recvbytes > ptr->sendbytes)
			{
				// ������ ������
				retval = send(ptr->sock, ptr->buf + ptr->sendbytes, ptr->recvbytes - ptr->sendbytes, 0);
				if(retval == SOCKET_ERROR)
				{
					if(WSAGetLastError() != WSAEWOULDBLOCK)
					{
						err_display("send()");
						RemoveSocketInfo(index);
					}
					continue;
				}
				ptr->sendbytes += retval;
				// ���� �����͸� ��� ���´��� üũ
				if(ptr->recvbytes == ptr->sendbytes)
					ptr->recvbytes = ptr->sendbytes = 0;
			}
		}

		// FD_CLOSE �̺�Ʈ ó��
		if(NetworkEvents.lNetworkEvents & FD_CLOSE)
		{
			if(NetworkEvents.iErrorCode[FD_CLOSE_BIT] != 0)
				err_display(NetworkEvents.iErrorCode[FD_CLOSE_BIT]);
			RemoveSocketInfo(index);
		}
	}

	// ���� ����
	WSACleanup();
	return 0;
}

// ���� ���� �߰�
BOOL AddSocketInfo(SOCKET sock)
{
	if(nTotalSockets >= WSA_MAXIMUM_WAIT_EVENTS)
	{
		printf("[����] ���� ������ �߰��� �� �����ϴ�!\n");
		return FALSE;
	}

	SOCKETINFO *ptr = new SOCKETINFO;
	if(ptr == NULL)
	{
		printf("[����] �޸𸮰� �����մϴ�!\n");
		return FALSE;
	}

	WSAEVENT hEvent = WSACreateEvent();
	if(hEvent == WSA_INVALID_EVENT)
	{
		err_display("WSACreateEvent()");
		return FALSE;
	}

	ptr->sock = sock;
	ptr->recvbytes = 0;
	ptr->sendbytes = 0;
	SocketInfoArray[nTotalSockets] = ptr;
	EventArray[nTotalSockets] = hEvent;
	nTotalSockets++;

	return TRUE;
}

// ���� ���� ����
void RemoveSocketInfo(int nIndex)
{
	SOCKETINFO *ptr = SocketInfoArray[nIndex];

	// Ŭ���̾�Ʈ ���� ���
	SOCKADDR_IN clientaddr;
	int addrlen = sizeof(clientaddr);
	getpeername(ptr->sock, (SOCKADDR *)&clientaddr, &addrlen);
	printf("[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

	closesocket(ptr->sock);
	delete ptr;
	WSACloseEvent(EventArray[nIndex]);

	for(int i=nIndex; i<nTotalSockets; i++)
	{
		SocketInfoArray[i] = SocketInfoArray[i+1];
		EventArray[i] = EventArray[i+1];
	}
	nTotalSockets--;
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