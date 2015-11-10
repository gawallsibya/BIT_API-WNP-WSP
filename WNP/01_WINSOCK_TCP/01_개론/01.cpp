/******************************************************************

  Chapter 1. ���ӿ� ���� �Ұ�

	02.cpp	: ���� API �Ұ�
	03.cpp  : �ּ� ����
	04.cpp  : TCP/IP  ���� ����
	05.cpp  : TCP/IP  Ŭ���̾�Ʈ ����
	06.cpp  : ������ �ۼ���(������)
	07.cpp  : ������ �ۼ���(�񿬰���) UDP/IP
	08.cpp  : ��Ÿ �ٸ� API
******************************************************************/

//--------------------------------------------------
// ��Ʈ��ũ ���α׷��ְ� ������ ���� 
//--------------------------------------------------

/* IPC(Inter Process C)  || RPC
 ��Ʈ��ũ ���α׷��� : �ָ� ������ �ִ� ȣ��Ʈ���� ���� �����͸� �ְ� 
 ���� �� �ֵ��� ���α׷��� �����ϴ� ��(IPC)

  -> ���ϰ� �޸� �����͸� �ְ� ���� ����� �ָ� ������ �ֱ� ������ 
     ����Ʈ���� �������� ȣ��Ʈ�鰣�� ������ �ִ� ��ġ�� �ʿ��� ��.
	 �̷��� ����� ���ִ� ��ġ�� �����̶� �� 
  

     �ᱹ ������ ���� �ָ� ������ �ִ� �� ��ü�� �����Ű�� �� 

     �츮�� ���ϰ� ������ �����ϴ� ������ �ؾ� �Ѵ�.




// Server �ۼ�
1) ���� ���� �Լ� : ��ȭ�� �常
int socket( int domain, int type, int protocol);

2) ���Ͽ� IP �ּ� �Ҵ� :  ��ȭ��ȣ�� �Ҵ� 
int bind( int sockd, struct sockaddr *myaddr, int addrlen);

3) ������ ���̺� ���� : ��ȭ�⸦ ���̺� ���� 
int listen(int sockfd, int backlog);

4) ���� ��û : ���� �︮�� ��ȭ�� ���� 
int accept(int sockfd, struct sockaddr *addr, int *addrlen)

  ...
  ��ȭ ���� 

  windows 2000�̻�, ����2( windows socket 2.x) �� ������� ����
  
  ��������(protocol) : ���ΰ��� ��� , �ý��۰� �ý��۰� ����� �ϱ� ����
                       ������ ������ ��� 

   ex) TCP/IP �������� 
       UDP/IP �������� 

   ����)  ���ͳ� �������� ���� ( TCP/IP �������� ���� )
           ��Ʈ��ũ ����, ���ͳ� ����, ���� ����, ���ø����̼� ���� 
		   ��Ŷ 

          OSI( Open Systems Interconnection) 7���� �� ����, 
		  �� ������ ����� TCP/IP �������� �������� Ȯ�� 
    
*/



//------------------------------------------------------
// ������ ���� ( Ư¡, ����, ���� ���ø����̼� ������ 
//------------------------------------------------------

/*
���� : ��Ŭ�� ���н�(Berkeley Sofrware Distibution UNIX)���� ����� 
       ��Ʈ��ũ ���α׷��� �������̽� 

		=> �̸� ������ ȯ�濡�� ����� �� �ֵ��� �Ѱ��� 
		������ ����, �ٿ��� Winsock�̶� �Ѵ�.

       ������ 95�������� API�� �������� �����Ͽ� �����ϰ� �ִ�.
*/


// 1. Ư¡
/*
    => ���н� ���ϰ� ȣȯ �Ʒ��� �κ��� �߰��Ǿ� �ִ�. 

	������ ������ DLL�� ���� ��κ��� ����� �����ǹǷ� DLL �ʱ�ȭ��
	���� �۾��� ���� �Լ��� �ʿ��ϴ�. 

    ������ ���ø����̼��� �밳 �׷��� ����� �������̽�(GUI)�� ������� 
	�ϸ�,
	�޽��� ���� ������� �����ϹǷ� �̸� ���� Ȯ�� �Լ��� �����Ѵ�.

    ������� �ü�� �������� ��Ƽ�����带 �����ϹǷ� ��Ƽ ȯ�濡�� 
	����������
	�����ϱ� ���� ������ �̸� ���� �Լ��� �ʿ��ϴ�.

    ���� ����
	�ü��					���ӹ���
	������ 95					1.1(2.2)	
	������ 98/NT/2000/XP/2003	2.2
	������ CE					1.1(2.2)

    ���� 1.1���� : ���н� ���ϰ��� ȣȯ�� �� TCP/IP ���������� ����
	���� 2.x���� : �پ��� ���������� �����ϵ��� ���� ���� �� �Լ� �߰� 
	  TCP/IP, IPv6, IrDA, Bluetooth, IPX/SPX, ATM, DECNet, TP4, 
	  DLC, NetBEUI

   
	���� ��Ʈ�p ���α׷����� ����
	1) ���н� ���ϰ� �ҽ� �ڵ� ���ؿ��� ȣȯ���� �����Ƿ� ���� ���α׷� 
	   ������ ����.
	2) ���� �θ� ���̴� ��Ʈ��ũ ���α׷��� �������̽��̴�.
	3) TCP/IP �ܿ��� �پ��� ������ ���������� �����ϹǷ� �ּ����� �ڵ� 
	   �������� ���ø����̼ǿ��� ����� ���������� ������ �� �ִ�.
	4) ���� �������� ���α׷��� �������̽��� , �������� ��� 
	   �����ϹǷ�  ������ ��Ʈ��ũ ���ø����̼� ���� �����ϴ�.

    ����
	1) ���ø����̼� ������ ���������� ���α׷��Ӱ� ���� �����Ͽ��� 
	   �Ѵ�.
	   ������ ����, ���� ���� ���� ����� ���α׷���
	2) ���� �ٸ� ����Ʈ ���� ����� ����ϰų� ������ ó�� ������ 
	   ���� �ٸ� ���� �ý��۰��� ����� ���, 
	   ���ø����̼� ���ؿ��� ������ ��ȯó���� �ʿ��ϴ�.


 2. ���� 
    ws2_32.DLL �� ��κ��� ����� �����ȴ�. 

    ���� 1.X ���� : WINSOCK.DLL   WSOCK32.DLL�� ���� WS2_32.DLL�� 
	                ����� �ñ������� ����ϰ� �ȴ�.

    ���� 2.x ����		���� 1.x���� 
	���ø����̼�		���ø����̼�

                        WINSOCK.DLL(16bit)
						WSOCK32.DLL(32bit)

      ---------------------------------------
	  WS2_32.dll( 32bit)
	  ---------------------------------------
	   TCP/IP  IrDA   Bluetooth IPX/SPX  ... 


       [ ������ ���� ���� ]

    

  3. ���� ���ø����̼� ������ 

    

*/

#include <winsock2.h>	
#include <stdlib.h>		
#include <stdio.h>

#define BUFSIZE 512

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



int main(int argc, char* argv[])
{
	int retval;

	// ���� �ʱ�ȭ
	WSADATA wsa;
	if(WSAStartup(MAKEWORD(2,2), &wsa) != 0) 
		return -1;

	// 1. socket()
	SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if(listen_sock == INVALID_SOCKET) err_quit("socket()");	
	
	// 2. bind()
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(9000);
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	retval = bind(listen_sock, (SOCKADDR *)&serveraddr, sizeof(serveraddr));
	if(retval == SOCKET_ERROR) err_quit("bind()");
	
	// 3. listen()
	retval = listen(listen_sock, SOMAXCONN);
	if(retval == SOCKET_ERROR) err_quit("listen()");

	// ������ ��ſ� ����� ����
	SOCKET client_sock;
	SOCKADDR_IN clientaddr;
	int addrlen;
	char buf[BUFSIZE+1];

	while(1)
	{
		// 4. accept()
		addrlen = sizeof(clientaddr);
		client_sock = accept(listen_sock, (SOCKADDR *)&clientaddr, &addrlen);
		if(client_sock == INVALID_SOCKET){
			err_display("accept()");
			continue;
		}
		printf("\n[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d\n",
			inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

		// Ŭ���̾�Ʈ�� ������ ���
		while(1){
			// ������ �ޱ�
			retval = recv(client_sock, buf, BUFSIZE, 0);
			if(retval == SOCKET_ERROR){
				err_display("recv()");
				break;
			}
			else if(retval == 0){
				break;
			}
			else{
				// ���� ������ ���
				buf[retval] = '\0';
				printf("%s", buf);
			}
		}

		// closesocket()
		closesocket(client_sock);
		printf("\n[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d\n",
			inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));
	}

	// closesocket()
	closesocket(listen_sock);

	// ���� ����
	WSACleanup();
	return 0;
}


// ���� ����
// telnet 127.0.0.1 900 
// Ctrl + ]  quit ��� ���� => Ŭ���̾�Ʈ�� ������ ���� ������ ���� 
