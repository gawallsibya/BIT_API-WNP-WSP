/******************************************************************

  Chapter 1. ���ӿ� ���� �Ұ� 

	1) ��Ƽ ������  
******************************************************************/

/*
�н� ��ǥ 
  ��Ƽ�������� �ʿ伺�� �����ϰ� �⺻ ������ ������.
  ��Ƽ�����带 �̿��Ͽ� TCP ������ �ۼ��Ѵ�.
  ������ ����ȭ ����� ������.


1. ��Ƽ������ ����
    ���� �ҽ��� ������ : 

	1) �ϳ��� Ŭ���̾�Ʈ�� ���� ���� ����
	2) ������ Ŭ���̾�Ʈ�� send(), recv() �Լ� ȣ�� ������ �¾ƾ� 
	   �Ѵ�.
	   => Ʋ���� ��������(deadlock) �� �߻� => ������ �Ͼ�� ���� 
	      ����� �� ���μ����� ��ٸ��� ��Ȳ 


    * 1)�� ������ �ذ�å�� ����� 
	 - ������ �ϳ��� Ŭ���̾�Ʈ�� ����ϴ� �ð��� ª�� �Ѵ�. 
	   ��, Ŭ���̾�Ʈ�� �Ź� �����͸� ������ ���� ������ �����ϰ� 
	    �����͸� �ְ� ���� �� 
	       ��ٷ� ������ ���´�.
		 ����) ������ �ý��� �ڿ��� ���� �Ҹ�
		       Ư���� ������� ���� ����
		 ����) ���� ���� �� ��뷮�� ������ ���۽� ���ø����̼�����
		       ������ 
		       ������ �����Ϸ��� Ŭ���̾�Ʈ�� ���� ���� ��� ���� ���� 
			   �߻� ����

     - ������ ������ Ŭ���̾�Ʈ�� �����带 �̿��Ͽ� ���������� ó�� 
	    ����)  ���� ���� ���� 
		����)  ������ Ŭ���̾�Ʈ ���� ����Ͽ� ������ �����ϹǷ� ������
		       �ý��� �ڿ� �Ҹ� ��������� ũ��. 

     - ���� ����� �� ���
	    ����) �ϳ� �Ǵ� �Ҽ��� �����带 �̿��Ͽ� �ټ��� Ŭ���̾�Ʈ ó��
		      ���� 
		      �ι�° ����� ���� ����� �ý��� �ڿ� �Ҹ� ���� 
		����) �ٸ� �� ����� ���� ������ ��ƴ�. 

   * 2) �� ������ �ذ�å�� �����
      - ������ �ۼ��� �κ��� �� �����Ͽ� ���� ���°� �߻����� �ʵ��� 
	    �Ѵ�.
	    ����) Ư���� ������� ���� ����
		����) ������ �ۼ��� ���Ͽ� ���� ���� ���� �߻� ����
		      ��� ��쿡 ���� �Ұ� 
	 
	  - ���Ͽ� Ÿ�Ӿƿ�(timeout) �ɼ� ����, send(), recv() �Լ� ȣ�� �� 
	    ���� �ð��� ������ ���� �ϵ��� ����
		����) ���� ������ ���� ����
		����) �ٸ� ����� ���� ������ ��������.

      - �ͺ��ŷ(nonblocking) ���� ���
	    ����) ���� ���¸� ���� �� �ִ�. 
		����) ������ �����ϴ�. �ý��� �ڿ�(CPU�ð�) �� ���ʿ��ϰ� 
		      ������ ���ɼ�

      - ���� ����� ���� ���
	    ����) ���ŷ�� �ͺ��ŷ ������ ������ ����, ���� ���� 
		      ���� �� �ִ�. 
		����) ù��° ����� ���� ������ ��ƴ�. 
		      �ι�° ����° ������ٴ� ����, �ϰ��� �ְ� ���� 
			  �����ϴ�. 

     => ���⼭�� ù��° ���� �ذ� ����� �ϳ���
	    ��Ƽ �����忡 ���� ���ظ� �Ѵ�.


1) �⺻ ���� 
   - ���μ���(process) : �޸𸮸� ����� ���� ���ҽ��� ��� �ִ�
                         �����̳ʷμ� ������ ����
   - ������(thread)    : ���� CPU �ð��� �Ҵ� �޾� ����Ǵ� ���� 
                         ���� �μ� ������ ���� 

     �ּ� �ϳ��� ������ �ʿ� , main, WinMain �Լ����� ���۵Ǵ� 
	 �����带 primary thread�� �Ѵ�.
	 ���ؽ�Ʈ ��ȯ(context switch) : �ü������ �̷������
	 ������ ���� ������ ����� �����۾�

     �۾� �����ڸ� Ȯ���غ��� �Ϲ������� �� �� �̻��� �����带 
	 ����ϴ� ���ø����̼��� ���� �����带 ����ϴ� �ͺ��� ����. 
	  
     �ܼ�, GUI ���ø����̼� ��� ��Ƽ������ ���� �����ϴ�. 
	 ��������� �̺�Ʈ �����  GUI ȯ�濡�� �� ���� ���ȴ�. 

2) �������� ������ ���� 
   - ������ ������ �ʿ��� ��� 
     -> �Լ��� ���� �ּ�( ������ �Լ��� ��- thread funtion )
	 -> ������ �Լ� ����� ����� ���� ������ ũ�� 
        �����尡 ����ɶ����� 1M�� ���ο� ���ÿ����� �����ȴ�. 
		2G / 1MB = 2048���� ������ ���� ����?

     CreateThread �Լ��� ���� ����

   - ������ ���� ���
     ������ �Լ� ����
	 ������ �Լ� ������ ExitThread() �Լ� ȣ��
	 TerminateThread() �Լ� ȣ��
	 �� �����尡 �����ϸ� ��� �����尡 ���� 


     #define CALLBACK	__stdcall
	 #define WINAPI		__stdcall
	 #define APIENTRY	WINAPI
	 #define PASCAL		__stdcall

     stdcall �� ǥ�� ������ API ���� ����ϴ� ȣ�� �Ծ��� 
	 �ݵ�� stdcall ȣ��Ծ��� ����� �Ѵ�. 

     �Ϲ����� ������ API �Լ��� ���ø����̼ǿ��� ȣ���ϴ� �� ���� 
	 ������ �Լ��� �ü���� ���� ȣ���Ѵ�.   
	 �ü���� __stdcall ȣ�� �Ծ࿡ ���� ������ �Լ��� ȣ���Ŵ���� 
	 ����ڰ� ������ ������ �Լ��� ������ ȣ�� �Ծ��� ����� �Ѵ�. 
	 �̷��� ����� �����ϴ� ���� WINAPI Ű����...
	 HANDLE WINAPI CreateThread(...)


     ���ø����̼�   API �Լ� ȣ��				������ �Լ� ȣ��

                        
		�ü��    API �Լ� �ڵ�				������ �Լ� ȣ�� 

  [ Thread Sample ]
*/

/*

//-------------------------------------
// 1. Sample : ��Ƽ ������ 
//-------------------------------------

#include <windows.h>
#include <stdio.h>

struct Point3D
{
	int x, y, z;
};

DWORD WINAPI MyThread(LPVOID arg)
{
	Point3D *pt = (Point3D *)arg;
	while(1){
		printf("Running another thread: %d, %d, %d\n", 
			pt->x, pt->y, pt->z);
		Sleep(1000);
	}

	return 0;
}

int main()
{
	// ù ��° ������ ����
	Point3D pt1 = {10, 20, 30};
	DWORD ThreadId1;
	HANDLE hThread1 = CreateThread(NULL, 0, MyThread, 
		(LPVOID)&pt1, 0, &ThreadId1);
	if(hThread1 == NULL) return -1;
	CloseHandle(hThread1);

	// �� ��° ������ ����
	Point3D pt2 = {40, 50, 60};
	DWORD ThreadId2;
	HANDLE hThread2 = CreateThread(NULL, 0, MyThread, 
		(LPVOID)&pt2, 0, &ThreadId2);
	if(hThread2 == NULL) return -1;
	CloseHandle(hThread2);

	while(1){
		printf("Running primary thread...\n");
		Sleep(1000);
	}

	return 0;
}
*/



//-------------------------------------
// 2. Sample : ������ �켱 ���� ���� : �ƻ� ���°� ������ �ʴ´�.
//-------------------------------------
/*
#include <windows.h>
#include <stdio.h>

DWORD WINAPI MyThread(LPVOID arg)
{
	while(1)
		printf("Running MyThread()\n");

	return 0;
}

int main()
{
	// ������ ����
	DWORD ThreadId;
	HANDLE hThread = CreateThread(NULL, 0, MyThread, NULL, 0, &ThreadId);
	if(hThread == NULL) return -1;

	// �켱���� ����
	SetThreadPriority(hThread, THREAD_PRIORITY_ABOVE_NORMAL);

	while(1)
		printf("Running main()....................\n");

	return 0;
}
*/



//-------------------------------------
// 3. Sample : ������ ��� 
//-------------------------------------
/*
#include <windows.h>
#include <stdio.h>

int sum = 0;

DWORD WINAPI MyThread(LPVOID arg)
{
	int num = (int)arg;
	for(int i=1; i<=num; i++)
		sum += i;

	return 0;
}

int main()
{
	// ������ ����
	DWORD ThreadId;
	int num = 100;
	HANDLE hThread = CreateThread(NULL, 0, MyThread, 
		(LPVOID)num, CREATE_SUSPENDED, &ThreadId);
	if(hThread == NULL) return -1;

	printf("������ ���� ��. ��� ��� = %d\n", sum);
	ResumeThread(hThread);
	WaitForSingleObject(hThread, INFINITE);
	printf("������ ���� ��. ��� ��� = %d\n", sum);
	CloseHandle(hThread);
	
	return 0;
}
*/





/*
2. ��Ƽ������ TCP ����

  ��Ƽ�����带 �̿��� TCP ���� ����

  ��Ƽ ������ TCP ������ �⺻ ���� 

  DWORD WINAPI ProcessClient(LPVOID arg)
  {
	 // ���޵� ����(3)
	 SOCKET client_sock = (SOCKET)arg;

	// Ŭ���̾�Ʈ ���� ���(4)
	addrlen	= sizeof(clientaddr);

    getpeername(client_sock, (SOCKADDR*)&clientaddr, &addrlen);

   // Ŭ���̾�Ʈ�� ������ ���(5)
   while(1)
   {
		....
   }
   closesocket(client_sock);
  }

  int main()
  {
	...
	whlie(1)
	{
		// Ŭ���̾�Ʈ ���� ����(1)
		client_sock = accept( listen_sock, ...);

		..

		// ������ ����(2)
		CreateThread(NULL, 0, ProcessClient, (LPVOID)client_sock, 0, &threadId);
	}
	...
  }

  (1) Ŭ���̾�Ʈ�� �����ϸ� accept() �Լ��� ������ �����Ѵ�.
  (2) Ŭ���̾�Ʈ �� �ϳ��� �����带 �����Ѵ�.  �̶� ������ �Լ��� ����� ������ �Ѱ��ش�.
  (3) ������ �Լ��� ���ڷ� ���޵� ������ SOCKET Ÿ������ �ɽ��� �Ͽ� �����Ѵ�.
  (4) getpeername() �Լ��� ȣ���Ͽ� Ŭ���̾�Ʈ�� IP, PORT �� ��´�.
      �� �ڵ�� �ʼ����� �κ��� �ƴϸ�, Ŭ���̾�Ʈ ������ ����� ���� �ʿ��ϴ�. 
  (5) Ŭ���̾�Ʈ�� ����� ������ �� ������ �����Ѵ�.


  * int getpeername(	SOCKET s, struct sockaddr* name, int *namelen	);

  * int getsockname(	SOCKET s, struct sockaddr* name, int *namelen	);

  => ���� 0, ���� : SOCKET_ERROR

  getpeername()
    ������ ����ü�� ����� ���� IP �ּҿ� ���� ��Ʈ ��ȣ ����
  getsockname()
    ������ ����ü�� ����� ���� �ּҿ� ���� ��Ʈ ��ȣ ���� 


  [ TCP Server ���� ���� ]



3. ������ ����ȭ 
   
	���� ���� ���ٽ� ���� �߻� ���� 

    �Ӱ迵��(Critical Section)
		: ���� ���ҽ��� ���� ���� �ϳ��� �����常 ���� ���

    ���ý�(Mutex)
		: ���� ���ҽ��� ���� ���� �ϳ��� �����常 ���� ���

    ��������(semaphore)
		: ������ ������ �ڿ��� ���� �����尡 ����Ϸ���  �� �� ���� ����

    ��� ���� Ÿ�̸�
		: Ư�� �ð��� �Ǹ� ��� ���� �����带 �����.


   * �Ϲ������� ����ȭ�� �ʿ��� ��Ȳ
   (1) �� �� �̻��� �����尡 ���� ���Ҹ��� ������ ��, ���� �� �����常 
       ������ ����ؾ� �ϴ� ��� 

   (2) Ư�� ��� �߻��� �ٸ� �����忡�� �˸��� ���, 
       ���� ���, �� �����尡 �۾��� �Ϸ��� �� ��� ���� �ٸ� �����带 
	   ����� ��� 


  [ Critical Section ]

*/

/*
#include <windows.h>
#include <stdio.h>

int A[100];
CRITICAL_SECTION cs;

DWORD WINAPI MyThread1(LPVOID arg)
{
//	EnterCriticalSection(&cs);
	for(int i=0; i<100; i++){
		A[i] = 3;
		Sleep(10);
	}
//	LeaveCriticalSection(&cs);

	return 0;
}

DWORD WINAPI MyThread2(LPVOID arg)
{
//	EnterCriticalSection(&cs);
	for(int i=99; i>=0; i--){
		A[i] = 4;
		Sleep(10);
	}
//	LeaveCriticalSection(&cs);

	return 0;
}

int main()
{
	// �Ӱ迵�� �ʱ�ȭ
	InitializeCriticalSection(&cs);

	// �� ���� ������ ����
	HANDLE hThread[2];
	DWORD ThreadId[2];
	hThread[0] = CreateThread(NULL, 0, MyThread1,
		NULL, 0, &ThreadId[0]);
	hThread[1] = CreateThread(NULL, 0, MyThread2,
		NULL, 0, &ThreadId[1]);

	// ������ ���� ���
	WaitForMultipleObjects(2, hThread, TRUE, INFINITE);

	// �Ӱ迵�� ����
	DeleteCriticalSection(&cs);

	// ��� ���
	for(int i=0; i<100; i++){
		printf("%d ", A[i]);
	}
	printf("\n");
	
	return 0;
}
*/


/*

  �̺�Ʈ 

  Ư�� ����� �߻��� �˸��� �� �ַ� ���

  1) �̺�Ʈ�� ���ȣ ���·� ����

  2) �� �����尡 �۾��� �����ϰ�, ������ ������� �̺�Ʈ�� ���� 
     Wait* () �Լ��� ȣ�������ν� �̺�Ʈ�� ��ȣ ���°� �Ǳ⸦ ��ٸ���.

  3) �����尡 �۾��� �Ϸ��ϸ�, �̺�Ʈ�� ��ȣ ���·� �ٲ۴�.

  4) ��ٸ��� �ִ� ��� �����尡 ����� �۾��� �����Ѵ�.
  
*/

/*
#include <windows.h>
#include <stdio.h>

#define BUFSIZE 16

HANDLE hReadEvent;
HANDLE hWriteEvent;
char buf[BUFSIZE];

DWORD WINAPI WriteThread(LPVOID arg)
{
	DWORD retval;

	for(int k=0; k<10; k++){
		// �б� �ϷḦ ��ٸ�
		retval = WaitForSingleObject(hReadEvent, INFINITE);		// ���� ���� �Ǳ⸦ ��ٸ�
		if(retval == WAIT_FAILED) break;						// ó���� ��ȣ �����̹Ƿ� ����� 

		// ���� ���ۿ� ������ ����
		for(int i=0; i<BUFSIZE; i++)
			buf[i] = 3;

		// ���� �ϷḦ �˸�
		SetEvent(hWriteEvent);
	}

	// �̺�Ʈ ����
	CloseHandle(hWriteEvent);

	return 0;
}

DWORD WINAPI ReadThread(LPVOID arg)
{
	DWORD retval;

	while(1){
		// ���� �ϷḦ ��ٸ�
		retval = WaitForSingleObject(hWriteEvent, INFINITE);	// ��ȣ���°� �Ǳ⸦ ��� 
		if(retval == WAIT_FAILED) break;

		// ���� �����͸� ���
		printf("Thread %d:\t", GetCurrentThreadId());
		for(int i=0; i<BUFSIZE; i++)
			printf("%d ", buf[i]);
		printf("\n");
		
		// ���۸� 0���� �ʱ�ȭ
		ZeroMemory(buf, sizeof(buf));

		// �б� �ϷḦ �˸�
		SetEvent(hReadEvent);
	}

	return 0;
}

int main()
{
	// �̺�Ʈ ����
	hReadEvent = CreateEvent(NULL, FALSE, TRUE, NULL);			// ��ȣ����
	if(hReadEvent == NULL) return -1;
	hWriteEvent = CreateEvent(NULL, FALSE, FALSE, NULL);		// ���ȣ���� 
	if(hWriteEvent == NULL) return -1;

	// �� ���� ������ ����
	HANDLE hThread[3];
	DWORD ThreadId[3];
	hThread[0] = CreateThread(NULL, 0, WriteThread,				// ����
		NULL, 0, &ThreadId[0]);
	hThread[1] = CreateThread(NULL, 0, ReadThread,				// �б�
		NULL, 0, &ThreadId[1]);
	hThread[2] = CreateThread(NULL, 0, ReadThread,				// �б� 
		NULL, 0, &ThreadId[2]);

	// ������ ���� ���
	WaitForMultipleObjects(3, hThread, TRUE, INFINITE);			// ���� ���(���)

	// �̺�Ʈ ����
	CloseHandle(hReadEvent);

	printf("��� �۾��� �Ϸ��߽��ϴ�.\n");

	return 0;
}


*/
/*
[ �� �� ]
1. �����쿡�� ���μ����� �޸𸮸� ����� ���� ���ҽ��� ��� �ִ� �����̳ʷν� ������ �����̰�
    ������� ���� CPU �ð��� �Ҵ�޾� ����Ǵ� ���� �����μ� ������ �����̴�.

2. main() �Ǵ� WinMain() �Լ����� ���۵Ǵ� �����带 �� ������� �θ���, ���μ����� ������ ��
  �����ȴ�.

3. CreateThread() �Լ��� �����带 ������ �� ������ �ڵ��� �����Ѵ�.

4. CreateThread() �Լ��� �����ϴ� �ٽ� ��Ҵ� ������ �Լ� �ּҿ� �Լ� ���ڴ�.

5. C/C++ ���̺귯�� �Լ��� ����ϴ� ���ø����̼ǿ����� CreateThread(), ExitThread() �Լ����ٴ�

   _beginthreadex(), _endthreadex() �Լ��� ����ϴ� ���� �ٶ����ϴ�.

6. ������� �� �����忡 CPU �ð��� ������ �й��ϱ� ���� ��å�� ����ϴµ�, �̸� ������ �����ٸ�
   �Ǵ� CPU �����ٸ� �̶� �θ���. 

7. SetThreadPriority() �Լ��� �켱���� ������ ������ ��, GetThreadPriority() �Լ��� �켱 ���� 
   ���� ���� ���� �� ����Ѵ�.

8. WaitForSingleObject(), WaitForMultipleObject() �Լ��� ����ϸ� Ư�� �����尡 ������ ������ ���
   �� �� �ִ�.

9. SuspendThread() �Լ��� ������ ������ �Ͻ� �����ϰ�, ResumeThread() �Լ��� �����带 ������Ѵ�.
   ���� Sleep() �Լ��� �����尡 ������ ���߰� ���� �ð� ���� ����ϵ��� �Ѵ�.

10. getpeername() getsockname() �Լ��� ���ϸ� ������ ���� �� �� ���ϰ� ������ �ּ� ������ �����ϴ� 
    ������ �Ѵ�.

11. ������ ����ȭ�� ��Ƽ������ȯ�濡�� �߻��ϴ� ������ �ذ��ϱ� ���� �Ϸ��� �۾��� ���Ѵ�.


12. ����ȭ ��ü�� ��ҿ��� ���ȣ ���·� �ִٰ� Ư�� ������ �����Ǹ� ��ȣ ���°� �ȴ�.
    �� ��ȣ => ��ȣ ���´� Wait*()�Լ��� ����Ͽ� ������ �� �ִ�.

13. �Ӱ� ������ �� �� �̻��� �����尡 ���� ���ҽ��� ������ ��, ���� �ϳ��� ������ ���ٸ� ����ؾ� 
    �ϴ� ��쿡 ���ȴ�. 
*/

