/******************************************************************

  Chapter 1. ���ӿ� ���� �Ұ� 

	1) ������ ����� ���̺귯��
	2) ������ �ʱ�ȭ 
	3) ������ ���� 
	4) ���� ����� ó��
	5) example

******************************************************************/


//---------------------------------------------------------------- 
//   1) ������ ����� ���̺귯�� 
//---------------------------------------------------------------- 
/*
    winsock : �ϳ� �̻��� �������α׷����� ���� ��ġ ������ Ȥ�� 
	          ��Ʈ�p�� ���Ͽ� ����ϱ� ���� ���α׷��� �������̽�
			  (API)
			  ��, ���������� �ƴϴ�. 
			  TCP/IP ��  IPX �� ���� ��Ʈ�p �������ݿ� ���� ���α׷�
			  �� �������̽��� �����Ѵ�. 

    ����           

	  ���� 1 
	   winsock.h   /  wsock32.lib ��ũ 

      ���� 2
	   winsock2.h  /  ws2_32.lib ��ũ 
	   WSA�� ���۵Ǵ� �Լ���(���� �߰��ǰų� ������ �Լ���)
	   ex) WSASocket...

           WSAStaratup, WSACleanup, WSARecvEx, WSAGetLastError...
		   ���� Winsock1.1���� ���ǵ� �Լ��� 
         

      * Windows CE�� ������ ��� ������ �÷������� ��� ���� 
*/



//---------------------------------------------------------------- 
//   2) ������ �ʱ�ȭ  
//---------------------------------------------------------------- 
/*
	��� ���� �������α׷��� ������ ������ ���� DLL�� �ε��Ѵ�.
	���� ���� ���̺귯���� �ε����� �ʰ� ���� API�� ����ϸ� 
	SOCKET_ERROR ��� ������ ���ϵȴ�.
	�̶� WSAGetLastError() �� ȣ���ϸ� ���� �ڵ带 ���� �� �ִ�.

    
    int WSAStartup(
		WORD wVersionRequested,
		LPWSADATA lpWSAData
	);

    ������ : 0
	���н� : GetLastError�� ������� ���� 
			 WS2_32.dll�� �޸𸮿� �ε���� �ʴ´�.
			�� ��� WSAGetLastError() �Լ��� �����ϴ� ���� ����Ȯ 
			�ϹǷ� �Լ��� ���ϰ����� ���� �ڵ尡 ���ϵȴ�. 

    1����  : �ε��ϱ⸦ ���ϴ� ���� ���̺귯���� ���� 
	         ���� ����Ʈ(���� ���̳� ����)
			 ���� ����Ʈ(���� ������ ����)
			 MAKEWORD(x, y) ��ũ�θ� �ַ� ��� 

    2����  : �ε�� ���̺귯���� ���� ���� ���� 

   
	*) �÷����� ���� ���� 

    Windows 95		1.1(2.2)	 Windows 98		2.2
    Windows Me		2.2			 Windows NT		2.2
    Windows 2000	2.2			 Windows XP		2.2
    Windows CE		1.1

*/



//---------------------------------------------------------------- 
//   3) ������ ����
//---------------------------------------------------------------- 
/*
	���� �������̽��� ����� ��������
	�����ϰ� �ִ� ���ҽ��� ����

    int WSACleanup(void);

	���� ����� �������� �ü���� �˷� ���� ���ҽ��� ��ȯ�ϴ� 
	������ �Ѵ�.
    �Լ� ȣ���� ������ ��� 


*/



//---------------------------------------------------------------- 
//   4) ���� ����� ó��
//---------------------------------------------------------------- 
/*
	���� �������α׷��� ����� ���ؼ� �ʼ� �Ұ����� ���

    ��κ��� ���� �Լ����� ���� �߻��� SOCKET_ERROR����(-1)

    �ݵ�� WSAGetLastError()�Լ��� ȣ���Ͽ� ���� ���� Ȯ��

    int WSAGetLastError(void);

    ���� �ڵ尪�� ���� ������ ���� WINSOCK.h or WINSOCK2.h
	�� ���ǵǾ� �ֽ�

    ��Ʈ��ũ ���α׷������� ���� �������� ���� ������ �߻��� �� �ִ�. 
    ������ ���� ó���� �ʼ����̴�. 

   �����Լ��� ���� ó�� 3���� ����
   1) ���� ó���� �� �ʿ䰡 ���� ��� 
      ���ϰ��� ���ų� ȣ�� �� �׻� �����ϴ� �Ϻ� ���� �Լ� 
   2) ���ϰ������� ������ ó���ϴ� ���
      WSAStartup() �Լ�
   3) ���ϰ����� ���� �߻��� Ȯ���ϰ� ��ü���� ������ ���� �ڵ带 
      �̿��Ͽ� Ȯ���ϴ� ��� ��κ��� ���� �Լ� 


   => ���� �ڵ� ��� �Լ� 
      int WSAGetLastError(void);

      ��뿹)
	  if( �����Լ�(...) == ���� )
	  {
			int errcode = WSAGetLastError();
			printf(errorcode�� �ش��ϴ� �����޽���);
	  }

       - ���ϰ��� ���� �ڵ��� => 
	     �����ϰ� ���ڿ� ���·� ����ϴ� ���� �ٶ���
		 FormatMessage() �Լ��� ������ 

      DWORD FormatMessage {
		DWORD dwFlags,	LPCVOID lpSource, DWORD dwMessageId, 
		DWORD dwLanguageId, LPTSTR lpBuffer, DWORD nSize, 
		va_list *Arguments
	  };
	  => ���� : ���� �޽��� ����,  ���� : 0

      1) dwFlags 
		 FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM
		 => ���� �޽����� ������ ������ �Լ��� �˾Ƽ� �Ҵ��Ѵٴ� �ǹ�
		    �ü���κ��� ���� �޽����� �����´ٴ� �ǹ� 
			���� ���� ������ ��� 
			�Լ��� �� ��° ���ڿ��� NULL��, ������°, �ϰ���° ���ڿ��� 
			0, NULL���� ����ϸ� �ȴ�.
	  3) dwMessageId
	     ���� �ڵ带 ��Ÿ����, WSAGetLastError()�Լ��� ���ϰ��� ����Ѵ�.
      4) dwLanguageId
	     ���� �޽����� � ���� ǥ���� �������� ��Ÿ����,
		 MAKEELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT)�� ����ϸ�
		 �����ǿ��� ������ �⺻���� ���� �޽����� ���� �� �ִ�. 
	  5) lpBuffer
	     ���� �޽����� ���� �ּҰ� ���⿡ ����ȴ�.
		 �ý��ۿ��� �Ҵ��� �޸𸮸� ��ȯ�Ͽ��� �Ѵ�. LocalFree()
       => ���� ������ �����غ���
	   
	  #include <winsock2.h>
	  #include <stdlib.h>

	  void err_quit( char *msg)
	  {
		LPVOID lpMsgBuf;
		FormatMessage (
		   FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		   NULL, WSAGetLastError(), 
		   MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAUL),
		   (LPTSTR)&lpMsgBuf, 0, NULL);
		MessageBox(NULL, (LPCTSTR)lpMsgBuf, msg, MB_ICONERROR);
		LocalFree(lpMsgBuf);
		exit(-1);
	  }
	  => ��뿹
	  if( socket(...) == SOCK_ERROR)	err_quit("socket()");
	  if( bind(...)   == SOCK_ERROR)	err_quit("bind()");

      * ���� �Լ� ����
	    MessageBox ��� printf�� ���
		�����޽��� ��� �� ���ø����̼��� �������� ���� 
	  void err_display( char *msg)
	  {
		LPVOID lpMsgBuf;
		FormatMessage (
		   FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		   NULL, WSAGetLastError(), 
		   MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAUL),
		   (LPTSTR)&lpMsgBuf, 0, NULL);
		printf("[%s] %s", msg, (LPCTSTR)lpMsgBuf);
		LocalFree(lpMsgBuf);
	  }

*/



//---------------------------------------------------------------- 
//   5) example
//---------------------------------------------------------------- 

#include <stdio.h>
#include <winsock2.h>

void main()
{
	WSADATA		wsaData;
	int			Ret;

	// 1. ���� 2.2�� �ʱ�ȭ
	//    ���� �ε�ÿ� ������ ��� WSAGetLastError()��� �Ұ�
	//    ���ϰ��� Ȯ���ض�
	if( ( Ret = WSAStartup(MAKEWORD(2,2), &wsaData)) != 0 )
	{
		printf("WSAStartup failed with error %d\n", Ret);
		return;
	}

	// 2. ���� ���....


	// 3. ���� ��� ���� 
	if( WSACleanup() == SOCKET_ERROR )
	{
		printf("WSACleanup failed with error %d\n", 
					WSAGetLastError() );
	}
}
