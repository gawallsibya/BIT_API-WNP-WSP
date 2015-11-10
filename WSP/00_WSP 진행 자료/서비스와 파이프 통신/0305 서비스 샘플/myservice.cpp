//myservice.cpp
#include "std.h"

char	gbuf[65536]="�޸� ��� ����\r\n";
char temp[50];

void myservice_init()
{
	PROCESS_INFORMATION pi = { 0 };
	STARTUPINFO si = { 0 };
	si.cb = sizeof( si );

	BOOL b = CreateProcess( 0,				// app name
							"0636_�ǽ�.exe", // app name + commandline args
							0, 0,			// pko, tko ����
							FALSE,			// KOHT �� ��ӿ���
							NORMAL_PRIORITY_CLASS, // �켱���� | �÷���
							0, 0,			// ȯ�溯��, ���� ���丮
							&si,			// startup info ����
							&pi);	// ������ ���μ���, �������� �ڵ�� ID
									// �� ���� ����.
	if ( b )
	{
		CloseHandle( pi.hProcess); 
		CloseHandle( pi.hThread);
	}
	DWORD ThreadID;

	CloseHandle(CreateThread(NULL,0,MainThread,NULL,0,&ThreadID));
}
void myservice_run()
{
}
DWORD WINAPI PipeThread(LPVOID temp)
{
	HANDLE hPipe=(HANDLE)temp;
	TCHAR szInput[50];
	DWORD dwRead, dwWritten;
	BOOL bSuc;

	// ��û�� �ް� ������ �� �� ������ ������.
	for (;;) {
		bSuc=ReadFile(hPipe,szInput,50,&dwRead,NULL);
		if ((bSuc==FALSE) || (dwRead==0)) {
			break;
		}

		bSuc=WriteFile(hPipe,szInput,50,&dwWritten,NULL);
		if ((bSuc==FALSE) || (dwWritten==0)) {
			break;
		}
	}

	// ������ ����
	FlushFileBuffers(hPipe);
	DisconnectNamedPipe(hPipe);
	CloseHandle(hPipe);
	return 0;
}
DWORD WINAPI MainThread(LPVOID temp)
{
	HANDLE hPipe;
	DWORD ThreadID;
	BOOL bCon;

	//�̸��� ���� ������ 
	for (;;) {
		// ������ ����
		hPipe=CreateNamedPipe("\\\\.\\pipe\\MultiPipe",PIPE_ACCESS_DUPLEX,
			PIPE_TYPE_BYTE, 3,4096,0,1,NULL);

		// ���ϵ� ���. ���ӵǸ� ���ϵ� ��û ó�� ������ ����
		bCon=ConnectNamedPipe(hPipe,NULL);
		if ((bCon==FALSE) && (GetLastError() == ERROR_PIPE_CONNECTED))
			bCon=TRUE;
		if (bCon==TRUE) {
			CloseHandle(CreateThread(NULL,0,PipeThread,(LPVOID)hPipe,0,&ThreadID));
		} else {
			CloseHandle(hPipe);
		}
	}
	return 0;
}
