#include <windows.h>

void main()
{
	// ��� ������ KO �����
	SECURITY_ATTRIBUTES sa;

	sa.nLength	= sizeof( sa );
	sa.bInheritHandle = TRUE;    // ��Ӱ����ϰ�
	sa.lpSecurityDescriptor = 0; // ���� ��������.

	HANDLE hEvent = CreateEvent(  &sa, // ����
								 0, 0, "e");

	// ��Ӱ����ϰ� �ٲٱ�..
	SetHandleInformation( hEvent, HANDLE_FLAG_INHERIT,
							      HANDLE_FLAG_INHERIT);


	CloseHandle( hEvent );
}