// ��� ���� �ϱ�.
#include <windows.h>
#include <tlhelp32.h>
#include <iostream>
using namespace std;

// Ư���� �ο��ϴ� �Լ�.
void EnablePri( char* name, BOOL bEnable ) // Ư���̸�, ���ɿ���
{
	HANDLE hToken;
	OpenProcessToken( GetCurrentProcess(), // ���μ��� �ڵ�
					  TOKEN_ADJUST_PRIVILEGES, 
					  &hToken );
	// Ư�� �̸����� ���� Ư�� ID( 64��Ʈ)�� ��´�.
	LUID luid;
	LookupPrivilegeValue( ".", // PC �̸�
						  name, // Ư���̸�
						  &luid); // luid�� ���� ����.
	TOKEN_PRIVILEGES tp;
	tp.PrivilegeCount = 1; // ����
	tp.Privileges[0].Luid = luid; // Ư�� ��ȣ
	tp.Privileges[0].Attributes = bEnable ? SE_PRIVILEGE_ENABLED : 0;

	AdjustTokenPrivileges( hToken, FALSE , &tp, sizeof(tp), 0, 0);
}

void main( int argc, char** argv)
{
	// �ý��� ���μ����� �����Ҽ��ִ� Ư�� �ο�
	EnablePri( SE_DEBUG_NAME, TRUE );

//	if ( argc != 2 )
//	{
//		cout << "usage : mds <pid>" << endl;
//		return ;
//	}
	//----------------------------------
	DWORD pid = 936;//atoi(argv[1]);
	HANDLE hSnap = CreateToolhelp32Snapshot( TH32CS_SNAPMODULE, pid );

	MODULEENTRY32 me;
	BOOL b = Module32First( hSnap, &me );
	while ( b )
	{
		cout << (void*)me.modBaseAddr << " : " << (char*)me.szModule << endl;

		b = Module32Next( hSnap, &me);
	}
	CloseHandle( hSnap );
}


































