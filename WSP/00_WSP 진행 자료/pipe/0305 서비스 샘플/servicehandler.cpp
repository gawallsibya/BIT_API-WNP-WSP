//servicehandler.cpp
#include "std.h"

void MyServiceHandler(DWORD fdwControl)
{
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
	// ������ ���� ���¸� �˷��޶� 
	case SERVICE_CONTROL_INTERROGATE:
	default:
		MySetStatus(g_NowState);
		break;
	}
}

void MySetStatus(DWORD dwState, DWORD dwAccept)
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
