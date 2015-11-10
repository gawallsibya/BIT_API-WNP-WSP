/*
#include <windows.h>
#include <stdio.h>

int n = 0;
DWORD ExceptionFilter( DWORD code  )
{
	if ( code == EXCEPTION_INT_DIVIDE_BY_ZERO ) // c0000094
	{
		printf("0���� ������ ���� �߻�. ���ο� ���� �־� �ּ��� >> ");
		scanf( "%d", &n );

		return -1; // ������ ������ ���������Ƿ� ���ܳ� ���� �ٽ� ������ ����.
	}
	return 1; // ó���Ҽ� ���� ���� �̹Ƿ� �ڵ鷯�� �����Ѵ�.
}

void main()
{
	int s;
	__try
	{
		s = 10 / n;
		printf("��� : %d\n", s );
	} 
	__except( ExceptionFilter( GetExceptionCode() ) )	// 1 : �ڵ鷯 ����. -1: ���ܳ��� �ٽ� ����, 0:���� try������
	{
		printf("���� �߻� : %x\n", GetExceptionCode() );
		ExitProcess( 0); // ���ܰ� �߻��Ѱ�� ��κ� ���μ����� ���� �Ѵ�.
	}

	printf("���α׷� ��� ����\n");
}
*/




// SEH : Structual Exception Handling.
// Kernel32.dll �� StartOfProcess ( �Ǵ� � å������ BaseProcessStart()
StartOfProcess()
{
	__try
	{
		mainCRTStartup();
	}
	__except( UnhandledExceptionFilter( GetExceptionInformation() ) )
	{
		ExitProcess( 0 );
	}
}
DWORD UnhandledExceptionFilter( _EXCEPTION_POINTERS* p )
{
	UINT ret = MessageBox( hwnd, "�˼����� ���ܰ� �߻��߽��ϴ�.����� �Ͻ÷���"
							"��Ҹ� ���� �Ͻ÷��� Ȯ���� ���� �ּ���","", 
							MBOKCANCEL);
	if ( ret == IDCANCEL )
		// ����Ÿ� ���� �� ���μ����� �����Ѵ�.
	else if ( ret == IDOK) 
		return 1; // �ڵ鷯 ����
}



















