// hk2.c

#include <windows.h>

HMODULE g_hDll;  // ���� DLL�� �ڵ�(�ּ�)�� ����.
HHOOK   g_hook;  //�� �ڵ�..

BOOL WINAPI DllMain(HANDLE hDll, DWORD r, LPVOID H)
{
	if( r == DLL_PROCESS_ATTACH )
	{
		g_hDll = (HMODULE)hDll;
	}
	return TRUE;
}

// GetMessage()�� �������� ��� �޼����� �Ʒ� �Լ��� ������ ���� �ȴ�..
LRESULT CALLBACK foo(int nCode, WPARAM wParam, LPARAM lParam)
{
	HWND hwnd;
	char name[256];

	if( nCode == HCBT_CREATEWND ) // �޼����� �������� �ִ� ��... !~!!!!
	{							
		hwnd = (HWND)wParam;  // ����� ���� �ִ� ������ �ڵ�..
		// hwnd �� � ���������� ��� �˼� ������??
		GetClassName(hwnd, name, 256);

		if(strcmpi(name, "WMP Skin Host") == 0)
		{
			MessageBox(0, "��ȭ ���� ������...~!!!", "", MB_OK);

			return 1;  // WH_CBT���� ���� ������ ������ �ʰ� 1�� �����ϸ� 
					   // �����ǰ� �ִ� �����찡 �ı� �ȴ�..
					   // �����ϰ� �ȴ�..
		}
	}
	return CallNextHookEx(0, nCode, wParam, lParam);
}

__declspec(dllexport) void Install( DWORD tid)
{
	g_hook = SetWindowsHookEx(WH_CBT, foo, g_hDll, tid);
}

__declspec(dllexport) void Uninstall()
{
	UnhookWindowsHookEx(g_hook);
}

