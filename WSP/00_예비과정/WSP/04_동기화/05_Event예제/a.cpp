#include <windows.h>
#include <stdio.h>

DWORD WINAPI foo(void* p)
{
	DWORD pid = (DWORD)p;
	HANDLE hProcess = OpenProcess( PROCESS_ALL_ACCESS, 0, pid );
	if ( hProcess == 0 )
	{
		printf("Can't Get Process Handle...\n");
		return 0;
	}
	//------------------------------------------------
	HANDLE hEvent = OpenEvent(EVENT_ALL_ACCESS, 0, "EXIT_EVENT");
	HANDLE h[2] = { hProcess, hEvent };

	// ���ϰ��� �����ϴ� �ڵ带 �� ���� �μ���..!
	DWORD ret = WaitForMultipleObjects( 2, h, FALSE, // 2�� 1���� signal �Ǹ�
											  INFINITE );

	if ( ret == WAIT_OBJECT_0 ) // h[0] �� ���μ����� signal
	{
		printf("\n --  %d �� ���μ��� �� ���� �Ǿ����ϴ�. --\n", pid);
	}
	else if ( ret == WAIT_OBJECT_0 + 1)
	{
		printf("Event�� Signal �Ǿ ���� �մϴ�.\n");
	}
	CloseHandle( hEvent );
	CloseHandle( hProcess );
	return 0;
}













//--------------------------------------------------
void main()
{
	HANDLE hEvent = CreateEvent( 0, TRUE, 0, "EXIT_EVENT");
	HANDLE hThread[1000];
	int count = 0;
	while ( 1 )
	{
		printf("������ ���μ��� ID�� �־� �ּ��� >> ");
		DWORD pid;
		scanf( "%d", &pid );
		if ( pid == -1 ) break; // ����...
		hThread[count++] = CreateThread( 0, 0, foo, (void*)pid, 0, 0);
	}
	// ��� ���� ��� �����带 �����.
	SetEvent( hEvent );

	// ��� �����尡 ������ ���� �Ҷ����� ����Ѵ�.
	WaitForMultipleObjects( count, hThread, TRUE, INFINITE );

	for ( int i = 0; i < count; ++i ) CloseHandle( hThread[i]);
}











// ���⸦ �������Ŀ� PID�� Ȯ���ϼ���.( �۾������ڳ� ������ ���� ps��)
// ���� ���α׷��� �����ϰ� ������ PID�� ��������..


















