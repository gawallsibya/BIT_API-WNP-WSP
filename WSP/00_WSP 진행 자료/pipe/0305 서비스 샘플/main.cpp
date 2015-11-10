#include "std.h"

SERVICE_STATUS_HANDLE g_hSrv;	
DWORD	g_NowState;
BOOL	g_bPause;
HANDLE	g_ExitEvent;

void MyServiceMain(DWORD argc, LPTSTR *argv)
{
	// ���� �ڵ鷯�� ����Ѵ�.
	g_hSrv=RegisterServiceCtrlHandlerEx(SERVICE_NAME, (LPHANDLER_FUNCTION_EX)MyServiceHandler, NULL);
	if (g_hSrv==0) {
		return;
	} 

	// ���񽺰� ���������� �˸���.
	MySetStatus(SERVICE_START_PENDING);
	
	// ���� ������ �ʱ�ȭ�Ѵ�.
	g_bPause=FALSE;

	// �̺�Ʈ�� �����Ѵ�.
	g_ExitEvent=CreateEvent(NULL, TRUE, FALSE, "MemStatExit");


	//(2.�ʱ�ȭ)==========================================================================
	myservice_init();
	//====================================================================================
	

	// ���񽺰� ���۵Ǿ����� �˸���.
	MySetStatus(SERVICE_RUNNING);

	// 10�ʿ� �ѹ��� �޸� ��踦 �ۼ��Ѵ�.
	for (;;) 
	{
		if (g_bPause == FALSE) 
		{
			//(3.����)======================================================================
			myservice_run();
			//============================================================================
		}
		
		if (WaitForSingleObject(g_ExitEvent, 10000) == WAIT_OBJECT_0)
			break;
	}
	MySetStatus(SERVICE_STOPPED);
}

int main()
{

	SERVICE_TABLE_ENTRY ste[]={
		{SERVICE_NAME,	 (LPSERVICE_MAIN_FUNCTION)MyServiceMain},	// ���� �� , ���� ���� �Լ� 
		{NULL,NULL}
	};

	StartServiceCtrlDispatcher(ste);
	return 0;
}



