/******************************************************************

  Chapter 1. ���ӿ� ���� �Ұ� 

	1) ��Ÿ �ٸ� API  
******************************************************************/



//---------------------------------------------------------------- 
//   1) ��Ÿ �ٸ� API 
//---------------------------------------------------------------- 
/*

  *) getpeername  
     ����� ������ ���Ͽ� ������ �ּ� ������ ��µ� ��� 

	 int getpeername(
		SOCKET				s,
		struct sockaddr FAR	*name,
		int				FAR *namelen
	 );
		

  *) getsockname  
     �ڽ��� ���� �ּ� ������ ��µ� ��� 

	 int getsockname(
		SOCKET				s,
		struct sockaddr FAR	*name,
		int				FAR *namelen
	 );
*/



/*
#include <winsock2.h>		
#include <stdlib.h>		
#include <stdio.h>
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

// ������ �̸� -> IP �ּ�
BOOL GetIPAddr(char *name, IN_ADDR *addr)	
{
	HOSTENT *ptr = gethostbyname(name);
	if(ptr == NULL){
		err_display("gethostbyname()");		return FALSE;
	}
	memcpy(addr, ptr->h_addr, ptr->h_length);
	return TRUE;
}

// IP �ּ� -> ������ �̸�
BOOL GetDomainName(IN_ADDR addr, char *name)
{	
	HOSTENT *ptr = gethostbyaddr((char *)&addr, 	sizeof(addr), AF_INET);
	if(ptr == NULL){
		err_display("gethostbyaddr()");		return FALSE;
	}
	strcpy(name, ptr->h_name);
	return TRUE;
}



int main(int argc, char* argv[])
{
	WSADATA wsa;
	if(WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return -1;

	// ������ �̸� -> IP �ּ�
	IN_ADDR addr;
	if(GetIPAddr("kr.yahoo.com", &addr)){
		// �����̸� ��� ���
		printf("IP �ּ� = %s\n", inet_ntoa(addr));
	
		// IP �ּ� -> ������ �̸�
		char name[256];
		if(GetDomainName(addr, name)){
			// �����̸� ��� ���
			printf("������ �̸� = %s\n", name);
		}
	}

	WSACleanup();
	return 0;
}
*/


