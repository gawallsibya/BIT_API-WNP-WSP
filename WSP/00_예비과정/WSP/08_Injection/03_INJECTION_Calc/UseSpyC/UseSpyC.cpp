// console

#include <windows.h>
#include <iostream>
using namespace std;


void main()
{
	HWND hwnd = FindWindow("SciCalc", "����");
	if( hwnd == 0 )
	{
		cout << "���Ⱑ ����. " << endl;
		return;
	}

	// ������ Process ID
	DWORD pid;
	GetWindowThreadProcessId(hwnd, &pid);

	// ID -> Handle
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

	// kernel32.dll�� ��ġ�� ��´�.
	HMODULE hdll = GetModuleHandle("kernel32.dll");

	// Kernel32 �ȿ� ���� LoadLibrary ��巹���� ����.
	// LoadLibrary => dll�� �ε��ϴ� �Լ�
	PTHREAD_START_ROUTINE func =		
			(PTHREAD_START_ROUTINE)GetProcAddress(hdll, "LoadLibraryA");

	//------------------------------------------------------------
	char file[] = "SpyC.dll";

	char *p = (char*)VirtualAllocEx(hProcess, 0, sizeof(file), 
		MEM_RESERVE | MEM_COMMIT , PAGE_READWRITE);

	if ( p == 0 )
	{
		cout << "�޸� �Ҵ� ���� " << endl;
		CloseHandle(hProcess);
		return;
	}

	// �Ҵ� ���� �޸𸮿� ���ڿ� ���, �ٸ� ���μ����� ���ڿ��� ��
	DWORD len;
	WriteProcessMemory( hProcess, p, file, sizeof(file), &len);

	//-------------------------------------------------------------
	// �ش� ���μ����� ������ ����
	HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, 
		func,	// �Լ�
		p,		// �Ķ����
		0, 0);

	CloseHandle(hThread);
	CloseHandle(hProcess);
}


















