// HookDll.cpp

#include <windows.h>

// dll => WINNT\\SYSTEM32 ���丮�� ���� 
HHOOK		hHook;
HMODULE		hDll;

BOOL  WINAPI DllMain( HANDLE h, DWORD , LPVOID p)
{
	hDll	= (HMODULE)h;
	return TRUE;
}

// Hook Procedure....

LRESULT CALLBACK foo( int nCode, WPARAM wParam, LPARAM lParam)
{
	// ��� �� �Լ��� �ݵ�� ���Ժΰ� �� ����� ���´�.
	if ( nCode < 0 )
		return CallNextHookEx( hHook, nCode, wParam, lParam);

	// ���� �����찡 ��������� �ִٸ�..
	if( nCode == HCBT_CREATEWND)
	{
		HWND hwnd = (HWND)wParam;		// ��������� �ִ� ������ �ڵ�
		char buf[256];

		GetClassName(hwnd, buf, 256);	// Ŭ���� �̸� ���

		if( strcmp(buf, "SciCalc") == 0 )	// ���� ���??
		{
			MessageBox(NULL, "���� ����", "", MB_OK);
			::WinExec("notePad.exe", SW_SHOW);

			DWORD pid;
			DWORD tid = GetWindowThreadProcessId(hwnd, &pid);
			HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
			TerminateProcess(hProcess, 0);
			CloseHandle(hProcess);
		}
	}
	return CallNextHookEx( hHook, nCode, wParam, lParam);
}

// install
extern "C" __declspec( dllexport)
void Install()
{
	// 4��° �μ��� 0�̸� �ý��� ��ü�� ���� ���� ���� 
	hHook	= SetWindowsHookEx(WH_CBT, foo, hDll, 0);
}

// uninstall
extern "C" __declspec( dllexport)
void UnInstall()
{
	UnhookWindowsHookEx(hHook);
}