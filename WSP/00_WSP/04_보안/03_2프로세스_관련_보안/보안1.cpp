

#define _WIN32_WINNT 0x0500
#define WINVER      0x0500
#include <windows.h>
#include <iostream.h>
#include <aclapi.h>


void main()
{

	HANDLE hToken;
	OpenProcessToken( GetCurrentProcess(), 
		TOKEN_ADJUST_PRIVILEGES, &hToken );
	LUID luid;

	// Ư���� �̸�(SE_DEBUG_NAME)  ==> LUID�� ��ȯ 
	// - Ư�� : ���ڿ��� ���ǵǾ� �ְ� LUID��� ������ ����� 
	LookupPrivilegeValue( ".", SE_DEBUG_NAME, &luid );
	

	// Ư�� ������ �����ų�� ���Ǵ� ����ü 
	TOKEN_PRIVILEGES tp;
	tp.PrivilegeCount = 1;
	tp.Privileges[0].Luid = luid;
	tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	
	// ���μ����� �׼��� ��ū�� Ư�� �ο�.
//	AdjustTokenPrivileges( hToken, 0, &tp, sizeof(tp), 0, 0);

	HWND hwnd = FindWindow( "SciCalc", "����");
	DWORD pid;
	DWORD tid = GetWindowThreadProcessId( hwnd, &pid);




	HANDLE hProcess = OpenProcess( PROCESS_ALL_ACCESS, 0, pid );
	
	if (hProcess  )
	{
		BOOL b = TerminateProcess( hProcess, 0);
		
		if ( b ) 
			cout <<"Terminate" << endl;
		else
			cout <<"Faile"<< endl;
	}
	else
		cout <<"Fail To Get Handle" << endl;
}
