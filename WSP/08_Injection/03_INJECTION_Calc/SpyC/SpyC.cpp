// SpyC.cp

#include <windows.h>

#define MB(x) MessageBox(NULL, x, "SpyC", MB_OK);

WNDPROC	 oldProc = (WNDPROC)0x01006118;
LRESULT CALLBACK WndProc( HWND hwnd, UINT imsg, WPARAM wParam, LPARAM lParam)
{
	switch( imsg)
	{
	case WM_COMMAND:
		if( LOWORD(wParam) == 50000 )
		{ 
			MB("�߰��� �޴�"); 
			return 0; 
		}
		if( LOWORD (wParam) >= 0x7c &&
						LOWORD( wParam) <= 0x85)
		{
			MB("���� ����");
			wParam = wParam +1;
			lParam = (LPARAM)GetDlgItem(hwnd, LOWORD(wParam));
			return oldProc(hwnd, imsg, wParam, lParam);
		}
	}
	return oldProc(hwnd, imsg, wParam, lParam);
}

DWORD WINAPI foo( PVOID p)		// ������ �Լ�
{
	HWND hwnd	= FindWindow("SciCalc", "����");
	HMENU hmenu = GetMenu(hwnd);
	HMENU hSub  = GetSubMenu(hmenu, 0);
	MB("�޴� �߰�");

	AppendMenu(hSub, MF_SEPARATOR, 0, 0);
	AppendMenu(hSub, MF_STRING, 50000, "�߰��� �޴�");

	// �޽��� ó�� �Լ� ����
	SetWindowLong(hwnd, GWL_WNDPROC, (LONG)WndProc);
	return 0;
}
BOOL WINAPI DllMain( HANDLE, DWORD dwReason, PVOID)
{
	if( dwReason == DLL_PROCESS_ATTACH)
	{
		MB("DLL ����... �����带 �����Ѵ�.");

		HANDLE hThread	= CreateThread(NULL, 0, foo, 0, 0, 0);
		if( hThread != 0 )
		{
			MB("������ ���� ����");
			CloseHandle(hThread);
			
		}
	}
	return TRUE;
}