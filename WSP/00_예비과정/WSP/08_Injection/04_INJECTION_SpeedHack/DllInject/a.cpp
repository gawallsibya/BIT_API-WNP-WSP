#include <stdio.h>
#include <windows.h>

void DLLInject(DWORD pid, char* path )
{
	// process ID�� ������ Process �ڵ��� ��´�.
	HANDLE hProcess = OpenProcess( PROCESS_ALL_ACCESS, 0, pid );

	//---------------------------------------------
	// Kernel32.dll�� �ּҸ� ���Ѵ�.
	HMODULE hDll = GetModuleHandle( "Kernel32.dll");

	PTHREAD_START_ROUTINE f = (PTHREAD_START_ROUTINE)
							GetProcAddress( hDll, "LoadLibraryA" );
	
	// PTHREAD_START_ROUTINE �� �̸� ���ǵ� ������ �Լ������ �Լ������� type

	// NateOn�� �����ּ� ������ �Ҵ��Ѵ�.
	void* p = VirtualAllocEx( hProcess, 0, strlen(path)+1, 
									MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

	DWORD len;
	WriteProcessMemory( hProcess, p, path, strlen(path)+1, &len );

	//-----------------------------------------
	// ��� ���μ����� ���ο� �����带 �����Ѵ�.(Win2000 �̻� ���� ����)
	HANDLE hThread = CreateRemoteThread( hProcess, 0, 0,
										 f, p, // �Լ�, ����  
										 0,  0);
	CloseHandle( hProcess );
	CloseHandle( hThread );
}




void main()
{
	HWND hwnd = FindWindow( 0, "���� ã��");
	if ( hwnd == 0 )
	{
		printf("NateOn �� ���� �����ϼ���\n");
		return;
	}
	DWORD pid;
	DWORD tid = GetWindowThreadProcessId( hwnd, &pid );

	DLLInject( pid, "D:\\speedhack.dll");	// <<================
}






