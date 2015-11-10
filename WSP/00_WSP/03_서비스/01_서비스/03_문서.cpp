/****************************************************************

  [ �������� ó���� ServiceMain�Լ����� �Ѵ�.]

  ServiceMain�Լ��� ������ ���� �ִ�.

  �� �Լ��� ���ڴ� main�Լ��� ���������� ���� �� �� �Ѱ�����
  ���������� ������ ���������� ����� �������̴�.
 
  ���� ���ø� �Ӽ� ��ȭ������ '���� �Ű�����' �׸� ������
  ���ڿ��� �Ѿ��. 


#define BEEPSERVICE_NAME	"BoopService"
SERVICE_STATUS_HANDLE g_ssh = NULL;
HANDLE g_event = NULL;
HANDLE g_event2 = NULL;
DWORD g_state = SERVICE_STOPPED;

void WINAPI BeepServiceMain( DWORD dwArgc, LPTSTR *lpszArgv)
{

	//1. SCM�� ���� �ڵ鷯�� ����ϱ� ���� API---------------------------------
	//   - SCM�� ���񽺸� ������ �ʿ䰡 ������ �� �� ���� �ڵ鷯�� ȣ���ϴ�
	//     ������� ���񽺿� �����Ѵ�.
	//     �̰��� ��ϵǾ��  SCM�� ���� ���α׷��� ������ �� �ִ�.
	g_ssh = RegisterServiceCtrlHandler(
		BEEPSERVICE_NAME, BeepServiceHandler);
	if(g_ssh == NULL)
	{
		MessageBox(NULL, 
			"BeepService�� ������ �� �����ϴ�.",
			"BeepService����", MB_OK|MB_ICONERRRO|
			MB_SERVICE_NOTIFICATION);
			return;
	}

	//�̺�Ʈ ��ü ����, �ʱ� ���´� ����
	// g_state : ���񽺰� ���������� ��Ÿ��
	// g_event : ���� �ڵ鷯�� ���� ������ �ʿ����� ServiceMain�� �����ϱ� ����
	// g_event2: ���� ������ �Ϸ�� ���� ServiceMain�� �ڵ鷯�� �����ϱ� ����
	// ServiceMain�� �ڵ鷯�� �ٸ� ������� �����ϱ� ������ ����ȭ�� �ʿ��ϴ�.

	g_event = CreateEvent(NULL, FALSE, FALSE, NULL);
	g_event2= CreateEvent(NULL, FALSE, FALSE, NULL);
	g_state = SERVICE_RUNNING;

	// �ʱ�ȭ ���� ����
	SERVICE_STATUS status = {
		SERVICE_WIN32_OWN_PROCESS,			// ���� ���� 
		SERVICE_RUNNING,					// ���� ���� 
		SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_PAUSE_CONTINUE,	// ���� ������ �����ڵ� 
			0, 0, 0, 0)};


	// 2. ���񽺰� ���� ���°� �Ȱ��� SCM�� �����Ѵ�.-----------------
	SetServiceStatus(g_ssh, &status);

	OutputDebugString("BeepService ���񽺰� ���۵Ǿ����ϴ�.\n");



	// 3. ���� ������ �ӹ� ���� ----------------------------------- 
	//���� ��, 2�ʸ��� ������
	while(1)
	{
		Beep(440, 200); // 440Hz 0.2��

		// ���� ������ �ִ� 2�ʰ� ���
		if( WaitForSingleObject(g_event, 2000) == WAIT_TIMEOUT)
			continue;

		// �Ͻ� ���� ������ �������簳/���� ���
		while( g_state == SERVICE_PAUSED)
		{
			SetEvent(g_event2);	// ���� �Ϸ� ����
			WaitForSingleObject(g_event, INFINITE);
		}

		if( g_state == SERVICE_RUNNING)
			SetEvent(g_event2);	// ���� �Ϸ� ���� 
		else if( g_state == SERVICE_STOPPED)
			break;
	}

	OutputDebugString(
	"BeepService ���񽺰� �����Ǿ����ϴ�.");

	SetEvent(g_event2);		// ���� �Ϸ� ���� 
}

****************************************************************/
