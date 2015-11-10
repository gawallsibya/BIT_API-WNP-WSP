

// Select �� 

 /* 
	select �Լ��� �ٽ����� ������ �Ѵٴ� �濡�� ���� �̸�
	���� ���(���ŷ, �ͺ��ŷ)�� ������� ���� ������ 
	�� ������� ó�������ϴ�.



//-----------------------------------
// 01  ���ۿ��� 
//-----------------------------------

  �ٽ� ��� : ���� �Լ��� ȣ���ؾ� �� ������ �˷������ν�
              �Լ� ȣ�� �� �׻� �����ϵ��� �ϴ� ���̴�. 

    - ���ŷ ���� :���� �Լ� ȣ��� ������ �������� �ʾ� ���ŷ
	               �Ǵ� ��Ȳ�� ���� �� �ִ�.

    - �ͺ��ŷ ���� : ���� �Լ� ȣ�� �� ������ �������� �ʾ� �ٽ� 
	               ȣ���ؾ� �ϴ� ��Ȳ�� ���� �� �ִ�. 


  ���� ���� 

  1) ������ ���� ��(socket set) �غ� 
     - ���� ���� ������ ���� �ϰ��� �ϴ� �۾��� ������ ��Ÿ����.
	   ex) �б� �� : recv() �Լ��� ȣ���ؾ� �� ������ �˰� ���� ��� 
	       ���� �� : send() �Լ��� ȣ���� ������ �˰� ���� ��� 

  2) ���� ���� �ʱ�ȭ(����.)

  3) ���� �¿� ������ �ִ´�.
     - �¿� ���� �� �ִ� ������ �ִ� ������ FD_SETSIZE(64)�� ���ǵ�


  4) select() �� ���� ����Ѵ�. : ���ŷ �Լ� 

  5) select() �Լ��� �����Ѵٴ� ���� ���� �¿� �ִ� ���� �� ��� 
     ������ ����� �غ� �Ǿ� �ִٴ� ���� �ǹ� 
	 ex) ���� ��û�� ������ �б� �¿� �ִ� ��� ������ �����.
	  
     �̶� ���ϼ¿��� �غ� �� ���ϸ� ���� �������� ��� ���ŵȴ�. 

  6) �ش� �۾��� ó���Ѵ�. 


  * �б� ��(read set)
    - �Լ� ȣ�� ���� 
	  Ŭ���̾�Ʈ�� ���������Ƿ� accept() �Լ� ȣ�� ����
	  �����͸� �޾����Ƿ� recv(), send() ���� �Լ� ȣ�� ����
	  ������ ����Ǿ����Ƿ� recv(), recvfrom() ���� �Լ��� ȣ�� ����
	  �̶� ���ϰ��� 0 or SOCKET_ERROR�� �ȴ�. 

  * ���� ��(write set)
    - �Լ� ȣ�� ���� 
	  �۽� ���۰� ����ϹǷ� send(), sendto()���� �Լ��� ȣ���Ͽ� 
	  ������ ������ �����ϴ�.

    - �Լ� ȣ�� ���
	  �ͺ��ŷ ������ ����� connect() �Լ� ȣ���� ����

  * ���� ��(exception set)
	  
	     


  select �Լ� ����
  int select ( int nfds, fd_set *readfds, fd_set *writefds, 
			   fd_set *excepfds, const struct timeval *timeout);

  1) ���н��� ȣȯ���� ���� : ������� ������� ����
  2) ���� �б�, ����, ���� ���� ��Ÿ��
     �ִ� 2������ NULL �� �� �� �ִ�. 

  3) Ÿ�� �ƿ��� ��Ÿ��.

     struct timeval {
		long tv_sec;		// seconds
		long tv_usec;		// microseconds
	};
   
     

  [ �� Ȯ��]

  ���� �� : echo �� ����
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
SOCKETINFO *SocketInfoArray[FD_SETSIZE];

// ���� ���� �Լ�
BOOL AddSocketInfo(SOCKET sock);
void RemoveSocketInfo(int nIndex);
// ���� ��� �Լ�
void err_quit(char *msg);
void err_display(char *msg);

int main(int argc, char* argv[])
{
	int retval;

	// 1) ���� �ʱ�ȭ ---------------------------------------------------
	WSADATA wsa;
	if(WSAStartup(MAKEWORD(2,2), &wsa) != 0)
		return -1;

	// socket()
	SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if(listen_sock == INVALID_SOCKET) err_quit("socket()");

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

	//------------------------------------------------------------------------

	// 2) �ͺ��ŷ �������� ��ȯ
	u_long on = TRUE;
	retval = ioctlsocket(listen_sock, FIONBIO, &on);
	if(retval == SOCKET_ERROR) err_display("ioctlsocket()");

	//-----------------------------------------------------------------------

	// ������ ��ſ� ����� ����
	FD_SET rset;
	FD_SET wset;
	SOCKET client_sock;
	SOCKADDR_IN clientaddr;
	int addrlen;

	while(1)
	{

		// 3) ���� �� �ʱ�ȭ 
		FD_ZERO(&rset);
		FD_ZERO(&wset);
		FD_SET(listen_sock, &rset);
		for(int i=0; i<nTotalSockets; i++)
		{
			if(SocketInfoArray[i]->recvbytes > SocketInfoArray[i]->sendbytes)
				FD_SET(SocketInfoArray[i]->sock, &wset);
			else
				FD_SET(SocketInfoArray[i]->sock, &rset);
		}
		//----------------------------------------------------------------------


		// 4) select()
		retval = select(0, &rset, &wset, NULL, NULL);
		if(retval == SOCKET_ERROR) err_quit("select()");

		// ���� �� �˻�(1): Ŭ���̾�Ʈ ���� ����
		if(FD_ISSET(listen_sock, &rset))
		{
			addrlen = sizeof(clientaddr);
			client_sock = accept(listen_sock, (SOCKADDR *)&clientaddr, &addrlen);
			if(client_sock == INVALID_SOCKET)
			{
				if(WSAGetLastError() != WSAEWOULDBLOCK)
					err_display("accept()");
			}
			else
			{
				printf("[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d\n", 
					inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));
				// ���� ���� �߰�
				if(AddSocketInfo(client_sock) == FALSE)
				{
					printf("[TCP ����] Ŭ���̾�Ʈ ������ �����մϴ�!\n");
					closesocket(client_sock);
				}
			}
		}
		//-----------------------------------------------------------------------


		// 5) ���� �� �˻�(2): ������ ���
		for(i=0; i<nTotalSockets; i++)
		{
			SOCKETINFO *ptr = SocketInfoArray[i];
			if(FD_ISSET(ptr->sock, &rset))
			{
				// ������ �ޱ�
				retval = recv(ptr->sock, ptr->buf, BUFSIZE, 0);
				if(retval == SOCKET_ERROR){
					if(WSAGetLastError() != WSAEWOULDBLOCK){
						err_display("recv()");
						RemoveSocketInfo(i);
					}
					continue;
				}
				else if(retval == 0){
					RemoveSocketInfo(i);
					continue;
				}
				ptr->recvbytes = retval;
				// ���� ������ ���
				addrlen = sizeof(clientaddr);
				getpeername(ptr->sock, (SOCKADDR *)&clientaddr, &addrlen);
				ptr->buf[retval] = '\0';
				printf("[TCP/%s:%d] %s\n", inet_ntoa(clientaddr.sin_addr),
					ntohs(clientaddr.sin_port), ptr->buf);
			}
			if(FD_ISSET(ptr->sock, &wset))
			{
				// ������ ������
				retval = send(ptr->sock, ptr->buf + ptr->sendbytes, 
					ptr->recvbytes - ptr->sendbytes, 0);
				if(retval == SOCKET_ERROR){
					if(WSAGetLastError() != WSAEWOULDBLOCK){
						err_display("send()");
						RemoveSocketInfo(i);
					}
					continue;
				}
				ptr->sendbytes += retval;
				if(ptr->recvbytes == ptr->sendbytes){
					ptr->recvbytes = ptr->sendbytes = 0;
				}
			}
		}
	}
	//--------------------------------------------------------------------

	// ���� ����
	WSACleanup();
	return 0;
}

// ���� ���� �߰�
BOOL AddSocketInfo(SOCKET sock)
{
	// FD_SETSIZE - ���� ��� ����
	if(nTotalSockets >= (FD_SETSIZE-1)){
		printf("[����] ���� ������ �߰��� �� �����ϴ�!\n");
		return FALSE;
	}

	SOCKETINFO *ptr = new SOCKETINFO;
	if(ptr == NULL){
		printf("[����] �޸𸮰� �����մϴ�!\n");
		return FALSE;
	}

	ptr->sock = sock;
	ptr->recvbytes = 0;
	ptr->sendbytes = 0;
	SocketInfoArray[nTotalSockets++] = ptr;

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
	printf("[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d\n", 
		inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

	closesocket(ptr->sock);
	delete ptr;

	for(int i=nIndex; i<nTotalSockets; i++){
		SocketInfoArray[i] = SocketInfoArray[i+1];
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