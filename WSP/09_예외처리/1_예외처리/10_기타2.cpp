//��������������������������������������
// [ �Ϲ��� �ڵ� �� ]
//��������������������������������������

BOOL Funcarama1()
{
	HANDLE	hFile			= INVALID_HANDLE_VALUE;
	PVOID	pvBuf			= NULL;
	DOWRD	dwNumBytesRead;	
	BOOL	fOK;
	
	hFile = CreateFile(..., ..., ..., ..., ..., ..., ...);
	if(hFile == INVALID_HANDLE_VALUE)	{
		return FALSE;
	}
	pvBuf = VirtualAlloc(..., ..., ..., ...);
	if(pvBuf == NULL)	{
		CloseHandle(hFile);
		return FALSE;
	}
	fOK = ReadFile(..., ..., ..., ..., ...);
	if(!OK || (dwNumBytesRead == 0)	{
		VirtualFree(..., ...);
		CloseHandle(hFile);
		return FALSE;
	}
	// �۾�....
	// ������
	VirtualFree(.......);
	CloseHandle(hFile);
	return FALSE;
}
// ���� 1
BOOL Funcarama1()
{
	HANDLE	hFile			= INVALID_HANDLE_VALUE;
	PVOID	pvBuf			= NULL;
	DOWRD	dwNumBytesRead;	
	BOOL	fOK, fSuccess	= FALSE;
	
	hFile = CreateFile(..., ..., ..., ..., ..., ..., ...);
	if(hFile != INVALID_HANDLE_VALUE)	
	{
		pvBuf = VirtualAlloc(..., ..., ..., ...);
		if(pvBuf != NULL)	
		{
			fOK = ReadFile(..., ..., ..., ..., ...);
			if(fOK && (dwNumBytesRead != 0))	
			{
				// �۾�....
				// ������
				fSuccess = TRUE;
			}
		}
		VirtualFree(.......);
	}
	CloseHandle(hFile);
	return FALSE;
}
// �ڵ� ���ش� ������ ���ǹ��� ���� �߰������� �鿩���Ⱑ ������ ȭ���� ����������
// ġ���� �ֵ�.
// ���� ó���ڸ� �̿� ���� 
BOOL Funcarama1()
{
	HANDLE	hFile			= INVALID_HANDLE_VALUE;
	PVOID	pvBuf			= NULL;
	__try	
	{
		DOWRD	dwNumBytesRead;	
		BOOL	fOK;
		hFile = CreateFile(..., ..., ..., ..., ..., ..., ...);
		if(hFile == INVALID_HANDLE_VALUE)	{
			return FALSE;
		}
		pvBuf = VirtualAlloc(..., ..., ..., ...);
		if(pvBuf == NULL)	{
			return FALSE;
		}
		fOK = ReadFile(..., ..., ..., ..., ...);
		if(!fOK || (dwNumBytesRead != 1024))	{
			return FALSE;
		}
		// ������ ó���� �۾� 
	}
	__finally {
		// �Լ��� ���࿩�θ� ��Ÿ���� ��� ��Ҹ� ������
		if(pvBuf != NULL)
			VirtualFree(pvBuf,...);
		if(hFile != INVALID_HANDLE_VALUE)
			CloseHandle(hFile);
	}
	// �۾� ��� ���� 
	return FALSE;
}


// ��� ������ �ڵ带 finally��� �ȿ� ���ִٴ� ��
// return���� ���� ���� �帧 �����ڵ� ���� 
BOOL Funcarama1()
{
	HANDLE	hFile			= INVALID_HANDLE_VALUE;
	PVOID	pvBuf			= NULL;
	BOOL	fFunctinoOK		= NULL;
	__try	
	{
		DOWRD	dwNumBytesRead;	
		BOOL	fOK;
		hFile = CreateFile(..., ..., ..., ..., ..., ..., ...);
		if(hFile == INVALID_HANDLE_VALUE)	{
			__leave;
		}
		pvBuf = VirtualAlloc(..., ..., ..., ...);
		if(pvBuf == NULL)	{
			__leave;
		}
		fOK = ReadFile(..., ..., ..., ..., ...);
		if(!fOK || (dwNumBytesRead != 1024))	{
			__leave;
		}
		// ������ ó���� �۾� 
		// �Լ��� �ùٸ��� ����Ǿ����� �˸���. 
		fFunctionOK	 = TRUE;
	}
	__finally {
		// �Լ��� ���࿩�θ� ��Ÿ���� ��� ��Ҹ� ������
		if(pvBuf != NULL)
			VirtualFree(pvBuf,...);
		if(hFile != INVALID_HANDLE_VALUE)
			CloseHandle(hFile);
	}
	// �۾� ��� ���� 
	return fFunctionOK;
}
// __leave ==> try����� ������ ������ �����ϰ� �ȴ�. 

// AbnormalTerminateion()
// __finally ������ ��� ������ �Լ�
// try ���� ���������� __finally�� ���Դٸ� false�� ����
BOOL Funcarama1()
{
	DWORD	dwTemp;
	// 1. �۾� ó��
	__try	{
		WaitForSingleObject(g_hSem, INFINITE);
		DwTemp = Fincinator(g_dwProctedData);
	}
	__finally	{
		RelaseSemaphore(g_hSem, 1, NULL);
		if(!AbnormalTerminateion()){
			// ���������� ����
		}
		else
		{
			// ������������ ���� 
		}
	}
	return(dwTemp);
}
// 1.������ �������ϴ� �κ��� �� ���� ���ְ� �װ��� ����ǰ� �Ǿ��ֱ� ������
//   ���� ó���� ������ �� �� �ִ�.
// 2. ���α׷��� �������� ���� �� �ִ�.
// 3. �ڵ� ������ ����.
// 4. ������ ���ȴٸ� ���� �ð��� ����ȴ�.