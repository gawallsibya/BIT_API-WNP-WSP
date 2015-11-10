#include <stdio.h>
#include <windows.h>

// �͸��� Pipe : �ܹ����� �̸����� pipe.(Named Pipe �� �����, �ܹ��� ��� ����)


DWORD WINAPI ReadThread(void* p)
{
	HANDLE hPipe=(HANDLE)p;
	char buf[4096];
	while ( 1 )
	{
		memset( buf, 0, 4096 );
		DWORD len;
		BOOL b = ReadFile( hPipe, buf, 4096, &len, 0);

		if ( b == FALSE ) break;

		printf("%s\n", buf );
	}
	return 0;
}

void main()
{
	//2���� ������ ����
	HANDLE hRead1, hWrite1;
	HANDLE hRead2, hWrite2;

	CreatePipe( &hRead1, &hWrite1, 0, 4096);
	CreatePipe( &hRead2, &hWrite2, 0, 4096);

	// hWrite �� ���� hRead���� ������ �ִ�.
	// hRead�� �ٸ� ���μ����� ������ �־�� �Ѵ�.
	// �̹� �ٸ� ���μ����� �������̶�� DuplicateHandle()��
	// ���Ӱ� �ڽ��� ����鼭 �����Ϸ��� KO ����� �̿��Ѵ�.

	// �б� ���� �ڵ��� ��� �����ϰ� �Ѵ�.
	//�����ڵ鰪�� ��� �����ϰ� ����
	SetHandleInformation( hRead1, HANDLE_FLAG_INHERIT, HANDLE_FLAG_INHERIT);
	SetHandleInformation( hWrite2, HANDLE_FLAG_INHERIT, HANDLE_FLAG_INHERIT);

	char cmd[256];
	wsprintf( cmd, "0636_�ǽ�.exe %d %d", hRead1,hWrite2); // ����� �������� ���

	PROCESS_INFORMATION pi;
	STARTUPINFO si = { sizeof(si)};

	BOOL b = CreateProcess( 0, cmd, 0, 0, TRUE, CREATE_NEW_CONSOLE,
		
		0,0,&si, &pi);
	
	if ( b )
	{
		CloseHandle( pi.hProcess);
		CloseHandle( pi.hThread);
		CloseHandle( hRead1 );
		CloseHandle( hWrite2 );
	}
	//--------------------------------------------
	CloseHandle(CreateThread(NULL,0,ReadThread,(void*)hRead2,0,NULL));
	char buf[4096];
	while ( 1 )
	{
		printf("������ �޼����� �Է��ϼ��� >> ");
		gets( buf );

		DWORD len;
		WriteFile( hWrite1, buf, strlen(buf)+1, &len, 0);
	}
}


















