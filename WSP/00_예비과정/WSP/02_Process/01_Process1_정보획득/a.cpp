#include <stdio.h>
#include <windows.h>

void main()
{
	// ���� ���μ����� ID��� - > EPROCESS ���� �������� �Լ�.
	DWORD pid = GetCurrentProcessId( );
	printf("���μ��� ID : %d\n\n", pid );

	// ���� ���丮 ���.
	char dir[MAX_PATH]; 
	GetCurrentDirectory( MAX_PATH, dir );
	printf("���� ���丮 : %s\n\n",dir );

	// Command Line argument ���
	char* p = GetCommandLine();
	printf("Command Line Argument : %s\n\n", p);

	// ȯ�� ���� ������
	char temp[1024];
	GetEnvironmentVariable( "PATH", temp, 1024);

	printf("PATH��� ȯ�� ���� : %s\n", temp );
}











