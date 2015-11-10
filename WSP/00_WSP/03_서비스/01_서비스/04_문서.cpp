/****************************************************************

  [ ���� �ڵ鷯�� SCM�����۽��ϴ� ���� �ڵ忡 �����Ѵ�.]

  ���񽺰� ������ �Ŀ� ��� �ʿ��ϸ� SCM�� ���� �ڵ鷯�� ȣ��
  �ؼ� ���񽺿� �� ����� �����Ѵ�.
  
  ����ڰ� ���� ���ø� �޴����� '����', '�Ͻ�����' ���� ������
  �� ��찡 �� ���̴�.

  - ���� �ڵ鷯�� �޴� �ֿ� ���� �ڵ� 
  ------------------------------------------------------
  �����ڵ�						����
  -----------------------------------------------------
  SERVICE_CONTROL_PAUSE			���� �Ͻ� ����
  SERVICE_CONTROL_CONTINUE		�Ͻ��������� ���� �����
  SERVICE_CONTROL_STOP			���� ����
  SERVICE_CONTROL_INTERROGATE	���� �ֽ� ���� ����
  SERVICE_CONTROL_PARAMCHANGE	������ ���� ���� ����
  SERVICE_CONTROL_SHUTDOWN		�ý��� �˴ٿ� ���� 
  -------------------------------------------------------

  - �ڵ鷯 ȣ���� ���� main �Լ����� StartServiceCtrlDispatcher
    API �� ȣ������ ���� ������(���� ������)�� ���ȴ�.

    �� ���� �ڵ鷯�� ServiceMain �Լ��� ���� ���۵� ���μ��� ���� 
	������ �������̴�. 

    �� ���ΰ� ��� �ʿ��ϴٸ� �����尣 ����� �ʿ��ϴ�. 

  - ���� �ڵ鷯�� ȣ��� �� 30�� �̳��� �����ؾ� �Ѵ�.(�߿�)
    ��ð� ��� ��ȯ���� ������ ���񽺸� ������ �� ���� �ȴ�.
	���� �� �̻��� �ð��� �ʿ��� ��쿡�� ���� �����带 ���� 
	ó���ϵ��� �ϰ�, �ڵ鷯�� ������� �ʰ� �ٷ� ���ͽ��Ѿ� �Ѵ�.

  - �ڵ鷯 ���ͽ� ó���ؾ� �� ����
    SetServiceStatus API�� ���� ���� ���� 

    ���� ó���� �ð��� ���� �ʾƼ� ���� �����带 ������� ����
	ó�������� ��Ÿ���� ~PENDING�� �켱 �ѱ�� ó���� �Ϸ�� ��������
	�ٽ�  SetServiceStatus�� ȣ���� ���¸� �����Ѵ�.
	�̴� ������ ���� ������ ���� ����. 
   
  // ���� �ڵ鷯 
  void WINAPI BeepServiceHandler(DWORD fdwControl)
  {
	char buf[256];

	SERVICE_STATUS status = {
		SERVICE_WIN32_OWN_PROCESS,			// ���� ���� 
		SERVICE_RUNNING,					// ���� ���� 
		SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_PAUSE_CONTINUE,	// ���� ������ �����ڵ� 
			0, 0, 0, 0)};

	switch( fdwControl )
	{
		case SERVICE_CONTROL_PAUSE:
			g_state = SERVICE_PAUSED;
			OutputDebugString("�Ͻ�����\n");
			SetEvent(g_event);
			WaitForSingleObject(g_event2, INFINITE);
			break;
		case SERVICE_CONTROL_CONTINUE:
			g_state = SERVICE_RUNNING;
			OutputDebugString("�����\n");
			SetEvent(g_event);
			WaitForSingleObject(g_event2, INFINITE);
			break;
		case SERVICE_CONTROL_STOP:
			g_state = SERVICE_STOPPED;
			OutputDebugString("����\n");
			SetEvent(g_event);
			WaitForSingleObject(g_event2, INFINITE);
			break;
		case SERVICE_CONTROL_INTERROGATE:	// ���� �ֽŻ��� ����
			break;
		default:
			sprintf(buf, "�������� �ʴ� �����ڵ� : 0x%081x\n", fdwControl);

			OutputDebugString(buf);

	}
	status.dwCurrentState = g_state;
	SetServiceStatus(g_ssh, &status);

	return;
}

****************************************************************/
