/****************************************************************************

  4) ���� I/O�� �񵿱� I/O�� ����� ����� �� ����.

     ex) �񵿱� I/O�� ����ؼ� �б⸦ �Ϸ��Ҷ����� 1�� ��������
		 �޽����� ����ϴ� �� 

         �������� �������� Ȯ���Ϸ��� ��뷮�� �����̳�, �÷��ǵ�ũ
		 ���� ���� ��ġ�� ���� �ʿ� 
****************************************************************************/

// �񵿱� I/O�� �̿��� ���� �б� 

#include <windows.h>
#include <stdio.h>

#define BUFSIZE		(10000000)

char buf[BUFSIZE];

int main()
{
	// ���� �缳�� Ÿ���� �̸����� �̺�Ʈ
	// ��ü ����
	HANDLE hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	if( hEvent == 0 )
	{
		printf("�̺�Ʈ ��ü ���� ����");
		return -1;
	}

	// FILE_FLAG_OVERLAPPED�� ������ ���� ���� 
	HANDLE hFile = CreateFile("TESTFILE.AVI", GENERIC_READ,
		0, NULL, OPEN_ALWAYS, 
		FILE_FLAG_OVERLAPPED, NULL);	// OVERLAPPED �÷��� ���� 
										// ��, �� ������ ���� I/O�� 
										// ������ �� ����. 
										// �ݵ�� �񵿱� I/O�� ����..
	if( hFile != INVALID_HANDLE_VALUE)
	{
		memset(buf, 0, sizeof(buf));
		DWORD xferCnt = 0;

		OVERLAPPED oi;				// ReadFile/WriteFile�� ����ɶ�����
									// ��ȿ�� �����ͷ� �����ؾ� �� 
		oi.hEvent		= hEvent;	// �̺�Ʈ �ڵ鷯
		oi.Offset		= 0;		// [�Է�] ���۽��� ��ġ�� ���� 32bit
		oi.OffsetHigh	= 0;		// [�Է�] ���۽��� ��ġ�� ���� 32bit
		oi.Internal		= 0;		// [���] ����:������, ȣȯ���� ���� 
		oi.InternalHigh	= 0;		// [���] ���۵� ����Ʈ ��:������, ȣȯ���� ����  

		if( ReadFile(hFile, buf, sizeof(buf), &xferCnt, &oi))
		{
			printf("�б� ó�� �Ϸ�");
		}
		else
		{
			DWORD rc = GetLastError();

			// �а� �ִ� ���� Ȯ�� 
			// �� ó���� ���������� ���۵Ǿ����� �Ϸ���� ���� ���� 
			if( rc == ERROR_IO_PENDING)
			{
				bool error = false;
				int cnt = 0;
												  //��ȯ : �����̸� TRUE
				while(!GetOverlappedResult(hFile, // ��� ���� �ڵ�
					&oi,						// OVERLAPPED����ü�� �ּ�
					&xferCnt,					// ������ ���۵� ����Ʈ �� 
					FALSE))						// TRUE�� ���� ���, FALSE�� ��� ���� 
				{
					rc = GetLastError();
					if( rc != ERROR_IO_INCOMPLETE)
					{
						printf("�񵿱� I/O ó�� �� ������"
							"�߻�(RC=%ld)\n", rc);
						error = true;
						break;
					}

					printf("�񵿱� I/O �ϷḦ �����"
						"(%d��°)\n", ++cnt);
					Sleep(1000);
				}

				if( !error)
				{
					printf("�񵿱� I/O�Ϸ�\n");
					printf("���� ����Ʈ��: %0ld\n", 
						xferCnt);
				}
			}
			else
			{
				printf("�񵿱� I/O ����"
					"����(RC=%ld)\n", rc);
			}
		}
		CloseHandle(hFile);
	}
	else
	{
		fprintf(stderr, "���� ���� ����\n");
	}
	CloseHandle(hEvent);
	return 0;
}