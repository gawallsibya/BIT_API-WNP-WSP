//----------------------------------------------------------------
//  ���ŷ�� �ͺ��Ŷ ���� ����� ����� ����
//  Select ���� ����� �� ���� 
//  WSAAsyncSelect ���� ����� �� ���� Ȱ��
//  WSAEventSelect ���� ����� �� ���� Ȱ�� 
//----------------------------------------------------------------


//-----------------------------------
// 01  ���� 
//-----------------------------------

/*

	���ݱ��� ��� ���� �Լ������ε� �����ϰ� �ǿ����� ������ �ۼ�
	�� �� ������ �� �� ���� Ŭ���̾�Ʈ ������ ȿ�������� ó���Ϸ���
	���ο� ����� ���� �ʿ��ϴ�.


1. ���� ��� 
   
   ������ �Լ� ȣ�� �� ���� ��Ŀ� ���� ���ŷ�� �ͺ��ŷ �������� ����
   �Ѵ�.
   �̸� ���� ���(socket mode)�� �Ѵ�.

   ���ŷ ����
   - ���� �Լ� ȣ�� �� ������ �������� ������ �Լ��� �������� �ʰ� �ش� 
     ������� ��� ����(wait state)�� �ȴ�.

     ����  ��Ƽ�����带 ����Ͽ� �ٸ� �۾��� ���� �ʴ� �� ���ø����̼���
	 ���� ������ �� ����.

   - accept()			: Ŭ���̾�Ʈ�� �������� �� 
     send(), sendto()	: �۽� ���ۿ� �����͸� ��� �������� ��
	 recv(), recvfrom()	: ���� ���ۿ� ������ �����Ͱ� �ֵ� �� 


   �ͺ��ŷ ����
   - ���� �Լ� ȣ�� �� ������ �������� �ʴ��� �Լ��� �����ϹǷ� �ش� ����
     ��� ��� ������ �� �ִ�.
	 socket() �Լ��� �⺻������ ���ŷ ������ �����ϹǷ� ������ ���� 
	 ioctlsocket() �Լ��� ȣ���ϸ� �ͺ��ŷ �������� �ٲ� �� �ִ�. 

     // ���ŷ ���� ����
	 SOCKET listen_sock			= socket(AF_INET, SOCK_STREAM, 0);
	 if( listen_sock == INVALID_SOCKET) err_quit("socket()");

     // �ͺ��ŷ �������� ��ȯ
	 u_long on	= 1;
	 retval		= ioctlsocket(listen_sock, FIONBIO, &on);
	 if( retval  == SOCKET_ERROR) err_quit("loctlsocket()");


     => �ͺ��ŷ ���� �Լ��� ȣ������ �� ������ �������� �ʾ� �۾��� �Ϸ�
	    �� �� ������ ���� �Լ��� ������ �����Ѵ�.
		�̶��� WSAGetLastError() �Լ��� ȣ���Ͽ� �ݵ�� �����ڵ带 Ȯ���Ѵ�.
		�ͺ��ŷ ������ ����� ��� �밳 ���� �ڵ�� WSAWOULDBLOCK�� �Ǹ�
		�̴� ������ �������� ������ ��Ÿ���Ƿ� ���߿� �ٽ� �����Լ���
		ȣ���ϸ� �ȴ�.


     [ ó���� �ۼ��� TCP ������ �����غ���. ]

*/

/*
#pragma comment(linker, "/subsystem:console")
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

	// socket()
	SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if(listen_sock == INVALID_SOCKET) err_quit("socket()");	
	
     // �ͺ��ŷ �������� ��ȯ -----------------------------------

	 //------------------------------------------------------------

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

	// ������ ��ſ� ����� ����
	SOCKET client_sock;
	SOCKADDR_IN clientaddr;
	int addrlen;
	char buf[BUFSIZE+1];

	while(1){
		// accept()
		addrlen = sizeof(clientaddr);
		client_sock = accept(listen_sock, (SOCKADDR *)&clientaddr, &addrlen);
		if(client_sock == INVALID_SOCKET){
			//----------------------------------------
			//----------------------------------------
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
				//----------------------------------------
				//----------------------------------------

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
*/


/*

  �ͺ��ŷ ������ Ư¡

  �� �� : ���� �Լ� ȣ��� ��ϵ��� �����Ƿ� �ٸ� �۾��� ������ �� �ִ�.
          ��Ƽ�����带 ������� �ʰ� ���� ���� ���� ������� ó���� �� �ִ�.

  �� �� : ���� �Լ��� ȣ���� ������ WSAWOULDBLOCK�� ���� �ڵ带 Ȯ���ϰ�, �ٽ� 
          �ش� �Լ��� ȣ���ؾ� �ϹǷ� ���α׷� ������ ����������.

          ���ŷ  ������ ����� ��캸�� CPU ������ ����. 

  => ������ ��� ���� ����� ���� ����ϸ� �ͺ��ŷ ������ ������ �״�� ����
     �ϸ鼭 ������ �ذ� �� �� �ִ�. 

     ���ο� ���� ����� ���� Ȯ���غ��� ���� ������ ���� �ۼ� ���� �����غ���.





//-----------------------------------
// 02  ���� �ۼ� �� 
//-----------------------------------

  ���ݱ��� ��� TCP UDP ������ �ݺ� ������ ���� ������ �з� ����

  1) �ݺ� ����(iterative server)

     ������ ���� Ŭ���̾�Ʈ�� �ϳ��� ���ʴ�� ó���Ѵ�.
	 TCP����, UDP ������ �ݺ� ������ �ش� 

     ���� : �ϳ��� ������� Ŭ���̾�Ʈ�� ó���ϹǷ� �ý��� �ڿ�
	        �Ҹ� ����.

     ���� : ������ Ŭ���̾�Ʈ�� ��� �ð��� ������� �ٸ� Ŭ����
	        ��Ʈ�� ��� �ð��� �������.

     => �ݺ������� �Ϲ������� UDP ������ �ۼ��� �� �����ϴ�.
	    �׷��� UDP ������ ���� ���۰� ���� �ð��� ���� �ɸ��� �۾���
		ó���Ѵٸ� ���� ������ �ۼ��ϴ� ���� �ٶ����ϴ�.

  2) ���� ����(concurrent server)
    
	 ������ ���� Ŭ���̾�Ʈ�� ���������� ó���Ѵ�.
	 ��Ƽ�����带 �̿��� TCP ���� 

     ���� : ������ Ŭ���̾�Ʈ�� ��� �ð��� ��������� �ٸ� Ŭ����
	        ��Ʈ�� ��ſ� ������ ���� �ʴ´�.

     ���� : ��Ƽ���μ��� �Ǵ� ��Ƽ�����带 �̿��Ͽ� �����ϹǷ� �ý���
	        �ڿ� �Ҹ� ũ��.

     => ���� ������ �Ϲ������� TCP ������ �ۼ��� �� �����ϴ�.
	    �׷��� TCP ������ ������ Ŭ���̾�Ʈ�� �ſ� ª�� �ð� ���ȸ�
		 ����ϰ� , ������ Ŭ���̾�Ʈ ���� ���� �ʴٰ� �����Ѵٸ�
		 �ݺ� ������ �ۼ��ص� �ȴ�.





//-----------------------------------
// 03  �̻����� ���� ����� �� 
//-----------------------------------

  �ݺ� ������ ���� ������ ������ ��� �����鼭 ������ ������ �ذ��� ����

  - ��� Ŭ���̾�Ʈ ������ �����Ѵ�

  - ������ �� Ŭ���̾�Ʈ�� ���� ��û�� �ִ��� ������ �����ϸ�
    ������� �����͸� �����Ѵ�.

  - ���� ���� ����� �����ϵ� �ý��� �ڿ� ��뷮�� �ּ�ȭ�Ѵ�.
    CPU �����̳� �޸� ��뷮 ���� �ּ�ȭ�Ѵ�.

  => �̻����� ������ �ۼ��ϱ� ���� ���� ����� �𵨿� �䱸�Ǵ� ���� ?

  1) ���� �Լ� ȣ��� ���ŷ�� �ּ�ȭ �Ѵ�.
     - �ͺ��ŷ ��븸���δ� ������� �ʴ�.
	 - CPU ����� �ּҷ� �ϸ鼭 �ͺ��ŷ ������ ����� ��� ���� 
	   �Լ� ȣ���� ���������� �̷��������...
	   ( WSAWOULDBLOCK���� �����ڵ� �߻��� �̿��� ����)

  2) ����� �۾��� �ٸ� �۾��� ����
     - ������ �ð� ���� ���ø����̼��� ���� ���� ���� ó���� �� 
	   �ֵ��� ����

  3) ������ ���� �ּ�ȭ
     - �ʿ��� �޸𸮸� ���
	 - ������ ���� �������� �������� ����ӵ��� ������ ������ ���������ʷ���
	   �̻����� ����� ���� CPU �� �ϳ��� �����带 �����Ͽ� ���� Ŭ����
	   ��Ʈ�� ������ ó�� �ϵ��� ��

  4) ���� ���� Ŀ�θ�� ��ȯ Ƚ���� ������ ���� �ּ�ȭ
     - ��尣 ��ȯ�� ����� CPU ����Ŭ�� �Ҹ���
	   ��� ��ȯ���� ���� 
	   ���ʿ��� ���縦 �ּ�ȭ 





//-----------------------------------
// 04  ���� ����� ���� ���� 
//-----------------------------------

   ������ CE	   : �ִ� �� ���� ���� ����� �� ����
   ������ 95�̻�   : Completion Port ���� ������ ��� ���� ����� ����
   ������ NT �迭  : ��� ���� ����� �� ����
   

   select
   WSAAsyncSelect
   WSAEventSelect
   Overlapped
   Completion Port


*/


