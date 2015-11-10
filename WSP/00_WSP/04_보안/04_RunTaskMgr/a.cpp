	#include <windows.h>
	#include <iostream.h>

	// Process�� Ư���� �ο��Ѵ�.
	BOOL EnablePri( char* pri, BOOL bEnable )
	{
		// ���� ���μ����� ProcessToken�� ��´�.
		HANDLE hToken;

		OpenProcessToken( GetCurrentProcess(), // ���μ��� �ڵ�.
						  TOKEN_ADJUST_PRIVILEGES, 
						  &hToken);

		// Ư�� �̸��� Ư�� ��ȣ( 64��Ʈ, luid��� �θ�)���� �ٲ۴�.
		LUID luid;
		LookupPrivilegeValue( ".", // PC�̸�
							  pri, // Ư���̸�
							  &luid ); // Ư�� ��ȣ�� ���� ����.
		TOKEN_PRIVILEGES tp;
		tp.PrivilegeCount = 1; // Ư�� ����.
		tp.Privileges[0].Luid = luid; // ��ȣ
		tp.Privileges[0].Attributes = bEnable ? SE_PRIVILEGE_ENABLED : 0;

		return AdjustTokenPrivileges( hToken, 0, &tp, sizeof( tp), 0, 0);
	}


	void main()
	{
		EnablePri( SE_DEBUG_NAME,TRUE );

		STARTUPINFO si = { sizeof( si ) };

		PROCESS_INFORMATION pi;

		CreateProcess( 0, "TaskMgr.exe", 0,0,0,0,0,0,&si, &pi );
		CloseHandle( pi.hProcess);
		CloseHandle( pi.hThread);

	}
