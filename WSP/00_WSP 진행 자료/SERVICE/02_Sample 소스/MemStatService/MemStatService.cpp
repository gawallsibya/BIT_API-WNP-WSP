/*************************************************************************************

  SERVICE ���α׷�

  - ũ�� 3�κ����� ����
     1) MAIN FUNCTION
	 2) SERVICE MAIN
	 3) HANDLER FUNCTION

**************************************************************************************/


#include <windows.h>

#define SERVICE_CONTROL_NEWFILE 128

void MyServiceMain(DWORD argc, LPTSTR *argv);
void MyServiceHandler(DWORD opCode);

SERVICE_STATUS_HANDLE g_hSrv;
DWORD g_NowState;
BOOL g_bPause;
HANDLE g_ExitEvent;
char gbuf[65536]="�޸� ��� ����\r\n";

/*************************************************************************************

  0) ����ó 

	 ��� ���� ���α׷��� ����� �ʱ�ȭ ���� 

      1) ���񽺿� SCM�� ����� �ϱ� ���� ��ġ ����
	     - �������� ���񽺵��� SCM���� ���� ���Ӿ��� ���� ��ȣ�� �ް� �ǰ� 
		   �ڽ��� ���¸� SCM���� �����ؾ� ��

         - ����ó�� SCM�� ,���� ���μ������� ����� ����ϴ� �������� 

     ��� �ó����� 
	 1) ���ο� ���� �����϶�
	 2) ����ó�� �� ���񽺸� ���� �����带 ����
	 3) ���� �����Լ��� �� �����忡�� ������
	 
	 1) ���񽺸� ��� �����ϰų� �簳�϶�
	 2) ������ �ڵ鷯���� �� ��ȣ�� ������
	     ���񽺰� scm���� ���� �Ǵ� ����ڷκ����� ���� ��ȣ�� ó���ϵ��� ��

      *) ����ó�� ���񽺰� �������� ���� ���� ������ ���� ���� ���۰� ����
	     ��ȣ ������ �����ϰ� ��

     ���� ���� ���� �����ϱ� ���� ����ó�� �� ���μ����� ��� ���񽺵��� 
	 ������ �ִ����� ���� ������ �ʿ�� ��
	 - main�Լ����� ����ó�� �����Ҷ� ���ڷ� ���޵� 
	   ex)main�Լ� Ȯ�� 
     
**************************************************************************************/


/*************************************************************************************

  1) MAIN FUNCTION

	 ����ó �����带 ���� 
	  - ���񽺸� �����ϰ� �ڵ鷯���� ���� �ڵ带 �����ϴ� ���� �ϴ� 
	    ������ ������ 
**************************************************************************************/
	/* ���� �ó����� 
	   1) SCM�� �ش� ���񽺸� ������ �ִ� ���μ����� ��θ� ������Ʈ������ ã�Ե�
	   2) �� ���μ����� �������� �ƴ϶�� ���μ����� ������
	      �̹� �������̸�, ����ó�� �����Ǿ� �����Ƿ� ����� �������� ������
		  
	   3) ���� ���μ����� main�Լ����� ����ó �����带 ����
	      ���޵� ������ �������� ����ó�� ���μ����� ���� ������ ������ ��������
		  SCM�� ����� ������

       4) �ش� ���񽺸� �����ϱ� ���� ����ó�� �� ���񽺸� ���� ������ �����带 
	      �����ϰ� ���� ���� �Լ��� ȣ���Ͽ� ���񽺸� ������ 
          - ���� �ϳ��� ������ �ϳ�
		  - ���� ���ο����� ���񽺸� ���� �ʱ�ȭ�� �ڵ鷯 ��� 

       5) ����ó�� ���� ���񽺰� ���۵Ǹ� ���񽺴� ������ �ڽ��� ���¸� 
	      ���÷� SCM���� �����ؾ� ��
		  SCM���� ���� ���� ��ȣ�� ������ ����ó�� �̸� ������ �ڵ鷯���� ����
		  �ϸ� �ڵ鷯�� �� ���� ��ȣ�� ó���� 

       6) ���񽺰� ����Ǹ� ����ó�� �������� ���� ī��带 1���� 
	      ���� 0�̶�� ����ó ���� �� main�Լ� ����
	*/

int main()
{

	SERVICE_TABLE_ENTRY ste[]={
		{"MemStat",	 (LPSERVICE_MAIN_FUNCTION)MyServiceMain},	// ���� �� , ���� ���� �Լ� 
		{NULL,NULL}
	};

	StartServiceCtrlDispatcher(ste);
	return 0;
}

// ������ ���� ���¸� �����ϴ� �Լ�
void MySetStatus(DWORD dwState, DWORD dwAccept=SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_PAUSE_CONTINUE)
{
	SERVICE_STATUS ss;
	ss.dwServiceType=SERVICE_WIN32_OWN_PROCESS;
	ss.dwCurrentState=dwState;
	ss.dwControlsAccepted=dwAccept;
	ss.dwWin32ExitCode=0;
	ss.dwServiceSpecificExitCode=0;
	ss.dwCheckPoint=0;
	ss.dwWaitHint=0;

	// ���� ���¸� ������ �д�.
	g_NowState=dwState;
	SetServiceStatus(g_hSrv,&ss);
}

/*************************************************************************************

  2) SERVICE MAIN

	 ���� ���� �۾��� �ϴ� ��ü 
	 - main�Լ����� ��ϵǾ� ���񽺸� �����ų �� ����ó�� ���� ȣ��Ǹ�
	   ���� ��� ���� ���� ���� ���� ������ 
	   - �ڵ鷯 ���
	   - ���� �⵿
	   - �ڽ��� ��ȭ�� SCM���� �Ƹ� 

     - ������ ������ �ִ�. 
**************************************************************************************/

void MyServiceMain(DWORD argc, LPTSTR *argv)
{
	HANDLE hFile;
	MEMORYSTATUS ms;
	DWORD dwWritten;
	char str[256];
	SYSTEMTIME st;

	// ���� �ڵ鷯�� ����Ѵ�.
	g_hSrv=RegisterServiceCtrlHandler("MemStat",(LPHANDLER_FUNCTION)MyServiceHandler);
	if (g_hSrv==0) {
		return;
	}

	// ���񽺰� ���������� �˸���.
	MySetStatus(SERVICE_START_PENDING);
	
	// ���� ������ �ʱ�ȭ�Ѵ�.
	g_bPause=FALSE;

	// �̺�Ʈ�� �����Ѵ�.
	g_ExitEvent=CreateEvent(NULL, TRUE, FALSE, "MemStatExit");

	// ���ο� �α� ������ �ۼ��Ѵ�.
	hFile=CreateFile("c:\\MemStat.txt",GENERIC_WRITE,0,NULL,
		CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	CloseHandle(hFile);
	
	// ���񽺰� ���۵Ǿ����� �˸���.
	MySetStatus(SERVICE_RUNNING);

	// 10�ʿ� �ѹ��� �޸� ��踦 �ۼ��Ѵ�.
	for (;;) 
	{
		if (g_bPause == FALSE) 
		{
			// ���� �ð��� �޸� ���� �����Ͽ� ���ڿ��� �����Ѵ�.
			GetLocalTime(&st);
			GlobalMemoryStatus(&ms);
			wsprintf(str, "%d�� %d�� %02d�� %02d�� %02d�� => "
				"��밡�� ���� �޸�=%dMbytes(%d%%), ��밡�� ����޸�=%dMbytes,"
				" ��밡�� ����¡ ����=%dMbytes\r\n",
				st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond,
				ms.dwAvailPhys/1048576,100-ms.dwMemoryLoad,ms.dwAvailVirtual/1048576,
				ms.dwAvailPageFile/1048576);

			// ���Ϸ� ��踦 ����Ѵ�. ���۰� ������ ��� ������ �ٽ� �����.
			if (strlen(gbuf) > 60000) 
			{
				hFile=CreateFile("c:\\MemStat.txt",GENERIC_WRITE,0,NULL,
					CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
				strcpy(gbuf,"�޸� ��� ����\r\n");
			} 
			else 
			{
				hFile=CreateFile("c:\\MemStat.txt",GENERIC_WRITE,0,NULL,
					OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
			}
			strcat(gbuf,str);
			WriteFile(hFile,gbuf,strlen(gbuf),&dwWritten,NULL);
			CloseHandle(hFile);
		}
		if (WaitForSingleObject(g_ExitEvent, 10000) == WAIT_OBJECT_0)
			break;
	}
	MySetStatus(SERVICE_STOPPED);
}


/*************************************************************************************

  3) HANDLER FUNCTION : �ڵ鷯 �Լ� 

	 ������ ���� ��ȣ�� ó���ϴ� �Լ� 
	 - ������ �޽��� ������ ���� ���� 
	 - ���� ���ο��� ����ó�� ��ϵ�
	 - ���� ���� ���α׷��̳� ���� ���ø��� ���� ����� �޾� ó���ϴ� �κ��� 
	   SCM�� �� ����� �޾� ����ó�� �����ϸ� ����ó�� ��ϵ� �ڵ鷯���� ���� ��ȣ��
	   ������ �� 

     - ������ ������ �ֽ� 
**************************************************************************************/

void MyServiceHandler(DWORD fdwControl)
{
	HANDLE hFile;

	// ���� ���¿� ���� ���� �ڵ��� ���� ó���� �ʿ� ����.
	if (fdwControl == g_NowState)
		return;

	switch (fdwControl) {
	// ���񽺸� �Ͻ� �����϶� 
	case SERVICE_CONTROL_PAUSE:
		MySetStatus(SERVICE_PAUSE_PENDING,0);
		g_bPause=TRUE;
		MySetStatus(SERVICE_PAUSED);
		break;
	// �Ͻ� ������ ���񽺸� �簳�϶�.
	case SERVICE_CONTROL_CONTINUE:
		MySetStatus(SERVICE_CONTINUE_PENDING,0);
		g_bPause=FALSE;
		MySetStatus(SERVICE_RUNNING);
		break;
	// ���񽺸� �����϶� 
	case SERVICE_CONTROL_STOP:
		MySetStatus(SERVICE_STOP_PENDING,0);
		SetEvent(g_ExitEvent);
		break;
	// ����� ���� ��ȣ 
	case SERVICE_CONTROL_NEWFILE:
		hFile=CreateFile("c:\\MemStat.txt",GENERIC_WRITE,0,NULL,
			CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
		strcpy(gbuf,"�޸� ��� ����\r\n");
		CloseHandle(hFile);
	// ������ ���� ���¸� �˷��޶� 
	case SERVICE_CONTROL_INTERROGATE:
	default:
		MySetStatus(g_NowState);
		break;
	}
}
