//��������������������������������������
// [ ���� ó�� 2 ]
//��������������������������������������


//��������������������������������������������������������������������������
// �ߴ� ó���� 
//��������������������������������������������������������������������������


// Funcenstein1 /////////////////////////////////////////////////////////////
DWORD Funcenstenin1()
{
	DWORD dwTemp;
		// 1. �۾��� ���� ���
	__try 
	{
		// 2. protected �����͸� ������ �� �ֵ��� ��û�ϰ� �װ��� ���
		WaitForSingleObject(g_hMutex, INFINITE);
		g_dwProtectedData = 5;
		dwTemp = g_dwProtectedData;
		// ���ο� ���� �����ش�.
		 return(dwTemp);
	}
	__finally 
	{
		// 3. �ٸ� ������ protected �����͸� ����Ѵ�.
		ReleaseMutex(g_hMutex);
	}
		// 4. ó���� �۾��� ����Ѵ�.
	dwTemp = 9;
	return(dwTemp);
}
// 1. �⺻ 1 --> 2 --> 3 --> 4 : ���ϰ� 9
// 2. return�� �߰��� 
//    ������� ������� �������� �ʴ´�.--> ���� �߻� 
//    �ߴ�ó���ڸ� ��������ν� return �� ������ �����ش�.
//     return ���� try ���� ������������ �� ��, finally����� ���� �����Ų��.
//     finally����� ����� �Ŀ� �Լ��� �����Ѵ�.    
//     ���� ���ϰ� : 5  

// Funcenstein2 /////////////////////////////////////////////////////////////
DWORD Funcenstenin1()
{
	DWORD dwTemp;
		// 1. �۾��� ���� ���

	__try {

		// 2. protected �����͸� ������ �� �ֵ��� ��û�ϰ� �װ��� ���
		WaitForSingleObject(g_hSem, INFINITE);
		g_dwProtectedData = 5;
		dwTemp = g_dwProtectedData;
		// finally������� �����Ѵ�.
		goto ReturnValue;
	}
	__finally {

		// 3. �ٸ� ������ protected �����͸� ����Ѵ�.
		ReleaseSemaphore(g_hSem, 1, NULL);
	}

		// 4. ó���� �۾��� ����Ѵ�.
	dwTemp = 9;
ReturnValue:
	return(dwTemp);
}
// goto���� ������ finally����� ������ �Ŀ� ReturnValue ���̺� �Ʒ��� �ڵ带 
// �����ϰ� �ȴ�.
// ���� return : 5
// ���� ������ �ƴϴ� ���������� ���� �帧 ����....--> ���� ���� �ʷ� 

// ��� ��  /////////////////////////////////////////////////////////////
DWORD Funcenstenin1()
{
	DWORD dwTemp;
		// 1. �۾��� ���� ���

	__try {

		// 2. protected �����͸� ������ �� �ֵ��� ��û�ϰ� �װ��� ���
		WaitForSingleObject(g_hSem, INFINITE);

		// ���� �������� �޸� ������ �õ��ϴ� �Լ��� �ϸ�..
		// ���� �ڽ��� ���� ���� ���μ��� �ߴܵ�....
		// �ٸ� ���μ����� ��������� ��� ��ٸ��� �ȴ�.
		dwTemp = Funcinator(g_dwProctedData);
	}
	__finally {

		// 3. �ٸ� ������ protected �����͸� ����Ѵ�.
		// ������ __finally������ �������� ���� ������ �����ϰ� ������ش�.
		ReleaseSemaphore(g_hSem, 1, NULL);
	}
		// 4. ó���� �۾��� ����Ѵ�.
	dwTemp = 9;
	return(dwTemp);
}

// ��� ��??  /////////////////////////////////////////////////////////////
DWORD Funcenstenin1()
{
	DWORD dwTemp = 0;
	while(dwTemp < 10) 
	{
		__try 
		{
			if (dwTemp == 2)
				continue;
			if (dwTemp == 3)
				break;
		}
		__finally 
		{
			dwTemp++;
		}
	}
	dwTemp += 10;
	return(dwTemp);
}

// ��� ��??  /////////////////////////////////////////////////////////////
DWORD Funcenstenin1()
{
	DWORD dwTemp;
		// 1. �۾��� ���� ���
	__try {

		// 2. protected �����͸� ������ �� �ֵ��� ��û�ϰ� �װ��� ���
		WaitForSingleObject(g_hSem, INFINITE);
		g_dwProctededData = 5;
		dwTemp = g_dwProctedData;
		// ���ο� ���� �����ش�.
		return(dwTemp);
	}
	__finally {
		// 3. �ٸ� ������ protected �����͸� ����Ѵ�.
		ReleaseSemaphore(g_hSem, 1, NULL);
		return(103);
	}
	dwTemp = 9;
	return(dwTemp);
}
/////////////////////////////////////////////////////////////////////////////////////////
// �ߴ� ó���� ���� try����̳� finally ��Ͼȿ� return, continue, break, goto
// ���� �����ϰ� �� ��ɵ��� �ߴ�ó���� �ٱ��κп� �ִ� ���� ����. 
// --> �����Ϸ��� ���� ���� �ڵ�� ���� �ڵ带 �����ϰ� �����ش�.