#include "std.h"

char	gbuf[65536]="�޸� ��� ����\r\n";

void myservice_init()
{
	PROCESS_INFORMATION pi = { 0 };
	STARTUPINFO si = { 0 };
	si.cb = sizeof( si );

	BOOL b = CreateProcess( 0,				// app name
							"freecell.exe", // app name + commandline args
							0, 0,			// pko, tko ����
							FALSE,			// KOHT �� ��ӿ���
							NORMAL_PRIORITY_CLASS, // �켱���� | �÷���
							0, 0,			// ȯ�溯��, ���� ���丮
							&si,			// startup info ����
							&pi);	// ������ ���μ���, �������� �ڵ�� ID
									// �� ���� ����.
	if ( b )
	{
		// �ڽ��� �ڵ��� �ݴ� ������ �ݵ�� �˾ƾ� �Ѵ�.
		// �ڽ��� �ڵ��� ���� ������ �ڽ��� ���� �Ǿ.. 
		// �ڽ��� �����ϴ�
		// PKO, TKO �� �ı� ���� �ʰ� �ִٰ� (�������� 1) 
		// �θ� �ڽ���
		// �ڵ��� �ݰų� �θ�����(�ڵ����� �ڵ� ����)�Ǿ߸� 
		// PKO, TKO �ı��ȴ�.
//		CloseHandle( pi.hProcess); //�ڵ��� �ʿ��� ���� ���� �ʾƾ� �Ѵ�.
//		CloseHandle( pi.hThread);
	}

	// ���ο� �α� ������ �ۼ��Ѵ�.
	HANDLE hFile=CreateFile("c:\\MemStat.txt", GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	CloseHandle(hFile);
}

void myservice_run()
{
	MEMORYSTATUS ms;
	DWORD dwWritten;
	char str[256];
	SYSTEMTIME st;
	HANDLE hFile;

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
	strcat(gbuf, str);
	WriteFile(hFile, gbuf, strlen(gbuf), &dwWritten, NULL);
	CloseHandle(hFile);
}

void myservice_OnNewFile()
{
	HANDLE hFile=CreateFile("c:\\MemStat.txt",GENERIC_WRITE,0,NULL,
			CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	strcpy(gbuf,"�޸� ��� ����\r\n");
	CloseHandle(hFile);
}