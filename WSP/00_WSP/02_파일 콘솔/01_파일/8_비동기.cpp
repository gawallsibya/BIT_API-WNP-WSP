/****************************************************************************

  3) GetOverlappedResult API�� ó�� ����� ���´�.

     ���� API�� ����ϸ� ó�� �Ϸ�� �˼������� �߿��� ó�� ����� 
	 �˼��� ����.

	 �̸� ���� GetOverlappedResult API�� �����Ѵ�.

	 BOOL GetOverlappedResult{	// ��ȯ�� : �����̸� TRUE
	  HANDLE hFile,				// ��� ���� �ڵ�
	  LPOVERLAPPED lpOver..		// OVERLAPPED ����ü�� �ּ�
	  LPDWORD lpNumber...		// ������ ���۵� ����Ʈ ��
	  BOOL bWait				// TRUE�� ���Ѵ�� FALSE�� ��� ����
	  );			


     BOOL GetOverlappedResult(HANDLE hFile, OVERLAPPED *lpOverlapped,
	  DWORD *lpNumberOfBytesTransfered, BOOL bWait)
	  {
		// �񵿱� I/O�� �Ϸ�Ǿ��°� Ȯ��
		BOOL rc = HasOverlappedIoCompleted(lpOverlapped);
		if(rc)
		{
			*lpNumberOfBytesTransfered = 
				lpOverlapped->InternalHigh;
		}
		else
		{
			if(bWait)
			{
				HANDLE hSync = lpOverlapped->hEvent;
				if( hSync == 0) hSync = hFile;
				if(WaitForSingleObject(hSync, INFINITE) == 
						WAIT_OBJECT_0)
				{
					rc = TRUE;
					*lpNumberOfBytesTransfered = 
						lpOverlapped->InternalHigh;
				}
			}
		}
		return rc;
	  }

    *) ���� �񵿱� I/O ó���� ����Ǿ��ٴ� �͸� Ȯ���Ϸ��� 
	   HasOverlappedIoCompleted API�� ����� ���� �ִ�.

****************************************************************************/













