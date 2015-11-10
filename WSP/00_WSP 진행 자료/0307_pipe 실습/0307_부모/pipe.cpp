//pipe.cpp
#include <windows.h>
#include <process.h>
#include "pipe.h"
#include <stdio.h>

HANDLE g_hWrite, g_hRead;
FUNC g_func;

void pipe_Create(FUNC func, int size)
{
	g_func = func;
	 
	HANDLE 	peer_hRead,  peer_hWrite;

	//1) �ΰ��� ������ ����
	CreatePipe( &g_hRead, &peer_hWrite, 0, size);
	CreatePipe( &peer_hRead, &g_hWrite, 0, size);

	printf("%d\n", peer_hRead);
	//2) �����ڵ鰪 2���� ��� �����ϰ� ����
	SetHandleInformation( peer_hRead, HANDLE_FLAG_INHERIT, HANDLE_FLAG_INHERIT);
	SetHandleInformation( peer_hWrite, HANDLE_FLAG_INHERIT, HANDLE_FLAG_INHERIT);

	//3) ����� ���� ���� : ���μ��� �� + �����ڵ鰪 + �����ڵ鰪 
	char cmd[256];
	wsprintf( cmd, "0636_�ǽ�.exe %d %d", peer_hRead,peer_hWrite); 
	
	//4) ���μ��� ���� 
	PROCESS_INFORMATION pi;
	STARTUPINFO si = { sizeof(si)};
	BOOL b = CreateProcess( 0, cmd, 0, 0, TRUE, CREATE_NEW_CONSOLE,		
		0,0,&si, &pi);
	
	if ( b )
	{
		CloseHandle( pi.hProcess);
		CloseHandle( pi.hThread);
		CloseHandle( peer_hWrite );
		CloseHandle( peer_hRead);
	}

	//5) ���� ������ ���� 
	_beginthread(recvthread, 0, (void*)size);
}

void recvthread(void* p)
{
	int size = (int)p;

	char *buf = (char*)malloc(size);
	while ( 1 )
	{
		memset( buf, 0, size );
		DWORD len;
		BOOL b = ReadFile( g_hRead, buf, size, &len, 0);
		if ( b == FALSE ) break;

		g_func(buf, len);
//		printf("%s\n", buf );
	}
	free(buf);
	CloseHandle( g_hRead );
}

void pipe_Write(char *buf, int length)
{
	DWORD len;
	WriteFile( g_hWrite, buf, length, &len, 0);
}