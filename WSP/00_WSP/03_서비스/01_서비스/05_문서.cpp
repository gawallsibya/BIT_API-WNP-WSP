/****************************************************************

  [ ���� ��ġ /���� ]

  ������ ���񽺸� SCM�� ����ؼ� �ܺ� ���α׷����� �����ϴ� ���

   1) ������ ��ġ�� ����

   2) ������ ����/������ �ٷ�� ���� ����

   3) ������ ���� ����

// ���񽺸� ��ġ(�ν���)�ϴ� ó�� 
void install(void)
{
	// 1) SCM �ڵ� ��� 
	// 1���� : ��ǻ�͸� (��Ʈ�p�� ����� ������ ��ǻ�͸� �ĺ��ϱ� ���� �̸�)
	//         NULL ���÷� ���� 
	//		   ��, ��Ʈ�p�� �ٸ� ��ǻ���� SCM�� �����ؼ� ���� ���۵�
	//		   �����ϴ�. 
	// 2���� : SCM�� ���� �����ͺ��̽��� �̸� : ���� NULL ��� 
	// 3���� : ���� ���� 
	SC_HANDLER scm = OpenSCManager(NULL, NULL, 
			SC_MANAGER_ALL_ACCESS);

	if( scm == NULL )
	{
		fprintf(stderr, "SCM�� �� �� �����ϴ�.");
		return;
	}

    //2) ���� ��ġ 
	SC_HANDLER scv = CreateService(
		scm,				// SCM�ڵ�
		BEEPSERVICE_NAME,	// ���� ��
		"BeepService",		// ���� ��¸�
		SERVICE_ALL_ACCESS,	// �ʿ��� ���� ����
		SERVICE_WIN32_OWN_PROCESS,		// ���� ����
		SERVICE_AUTO_START,				// ���� ���
		SERVICE_ERROR_NORMAL,			// ���� �߻��� ��ó ���

		"c:\\bin\\beepService.exe",		// ���� ��θ�

		NULL,		// �ε� ���� �׷� ����
		NULL,		// �ε� ���� �׷� ���� �±׸� �޴´�.
		NULL,		// �����ϴ� ���񽺸� ����Ʈ
		NULL,		// ���� ID(LocalSystem�� ������ ����)
		NULL,		// ��ȣ

		);

	if( scv != NULL )
	{
		CloseHandle(scv);
		printf("���񽺰� ��ġ�Ǿ����ϴ�.\n");
	}
	else
	{
		fprintf(stderr,"���񽺰� ��ġ���� �ʾҽ��ϴ�\n");
	}

	CloseServiceHandle(scm);
}


// ���񽺸� ����(���ν���)�ϴ� ó�� 
void uninstall(void)
{
	SC_HANDLER scm = OpenSCManager(NULL, NULL, 
			SC_MANAGER_ALL_ACCESS);

	if( scm == NULL )
	{
		fprintf(stderr, "SCM�� �� �� �����ϴ�.");
		return;
	}
	SC_HANDLER scv = OpenService(
		scm,				// SCM�ڵ�
		BEEPSERVICE_NAME,	// ���� ��
		DELETE
		);

	if( scv != NULL )
	{
		if( !DeleteService(scv)
		{
			printf("���񽺸� ������ �� �����ϴ�.\n");
		}
		else
		{
			CloseServiceHandle(scv);	
			printf(���񽺰� �����Ǿ����ϴ�.\n");
		}
	}
	else
	{
		fprintf(stderr, 
				"���񽺸� �� �� �����ϴ�\n");
	}

	CloseServiceHandle(scm);	
}


****************************************************************/
