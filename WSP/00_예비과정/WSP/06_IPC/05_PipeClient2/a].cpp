#include <stdio.h>
#include <windows.h>

void main(int argc, char** argv)
{
//	if ( argc != 2 )
//	{
//		printf("�����α׷��� ���� �����ϸ� �ȵ˴ϴ�. �θ� ������ �ּ���\n");
//		return;
//	}
	// �θ� ������ pipe �ڵ��� ������.
	HANDLE hPipe = (HANDLE)atoi(argv[1]);
	
	printf("%d\n", hPipe);
	char buf[4096];
	while ( 1 )
	{
		memset( buf, 0, 4096 );
		DWORD len;
		BOOL b = ReadFile( hPipe, buf, 4096, &len, 0);

		if ( b == FALSE ) break;

		printf("%s\n", buf );
	}
	CloseHandle( hPipe );
}
// �� ���������� �̸��� child.exe �����ϼ���..

// child.exe�� PipeServer2.exe �� �ִ� ������ �ű⼼��..

// pipeserver2.exe �� �����ϼ���.. �θ𿡼� ���ڿ� �Է��� ������..











