// ���μ��� ���� �ڵ� ���
/*
 Process ���� �ڵ� �� ��� 
 1. GetExitCodeProcess �Լ� ��� 
 2. TerminateProcess�Լ� ==> Ÿ��... ���� ����...
    - �񵿱�.. => �Լ� ȣ��� ��ٷ� ���Ḧ ��Ű�� ���� �ƴ϶�
	              �Լ��� �����ϰ� �� ���� ����� �����Ѵ�...
    - OS������ �� ���μ����� ��ٷ� ������ �ʰ� ���Ḧ ���� �������� �۾��� �Ѵ�.

    - Process���� Signal ���� ����� �� 0, �׾��� �� 1(Signal����)�� ���� ���´�.
	0 -> 1 : ������ ���̱� 
	1 -> 0 : ���̴� �� �츮��(�翬�� �ȵ�)..

 3. WaitForSingleObject() �� ����Ͽ� Signal ���¸� �� �� �ִ�.
    - ��� �Լ� 
	- ����ϴ� ��ü�� Signal �� ��, 
	- ����ϰ��� �ϴ� �ð��� ������ ���� �� (INFINITE  : ������ ���)

*/
#include <windows.h>


LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//-------------------------------
	static PROCESS_INFORMATION pi;
	//--------------------------------
	switch( msg )
	{
	case WM_LBUTTONDOWN:
		{
			STARTUPINFO	si	= { 0 };
			si.cb			= sizeof(si);
			si.dwXSize		= 200;
			si.dwYSize		= 200;
			si.dwFlags		= STARTF_USESIZE;	

			BOOL b = CreateProcess(NULL,//"C:\\WINDOWS\\NotePad.exe",		// ���α׷� �̸�
								"calc.exe", // ���α׷� �̸� + �Ķ����
								0, 0,		// Process, Thread KO�� ���ȼӼ� ����
								FALSE,		// ��ӿ��� 
								NORMAL_PRIORITY_CLASS, // �켱���� (8)
								0, 0,		// ���μ����� ȯ����, ���� Dir 
								&si,		// ���� ������ ���� ����ü
								&pi);		// ���μ���, ������ �ڵ�, ID�� ���� ����ü
			if( b )
			{
				// ���μ����� Thread�� �ڵ��� �� �̻� �ʿ���� ��� �޵�� �ݴ´�.
				// �޸�...
//				CloseHandle(pi.hProcess);
//				CloseHandle(pi.hThread);
			}
		}
		return 0;
	case WM_RBUTTONDOWN:
		// Ctrl + RBUTTONDOWN
		if( wParam & MK_CONTROL)
		{
			// �񵿱��Լ���..
			TerminateProcess(pi.hProcess, 100);	// �ڵ鰪. ���� �ڵ尪

			// ����Լ�
			// 1) �ش�Ǵ� �ڵ��� �ñ׳εɶ� ����
			// 2) �ð��� ����Ǹ�.. 1�ʰ� ������
			WaitForSingleObject(pi.hProcess, INFINITE);
			SendMessage(hwnd, WM_RBUTTONDOWN, MK_SHIFT, lParam);
		}

		// SHIFT + RBUTTONDOWN
		if( wParam & MK_SHIFT)
		{
			// Process�� ���� �ڵ� ���
			DWORD code;
			GetExitCodeProcess(pi.hProcess	, &code);
			if( code == STILL_ACTIVE)	// 0x13
			{
				MessageBox(hwnd, "���� ��� �ִ�.", "�˸�", MB_OK);
			}
			else
			{
				char buf[256];
				wsprintf(buf, "���� : %d", code);
				MessageBox(hwnd, buf, "�˸�", MB_OK);
				CloseHandle(pi.hProcess);
				CloseHandle(pi.hThread);
			}
		}
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}


int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, 
				   LPSTR lpCmdLine, int nShowCmd)
{
	// 1. ������ Ŭ���� ����� 
	WNDCLASS wc;
	wc.cbWndExtra			= 0;
	wc.cbClsExtra			= 0;
	wc.hbrBackground		= (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hCursor				= LoadCursor(0, IDC_ARROW);
	wc.hIcon				= LoadIcon(0, IDI_APPLICATION);
	wc.hInstance			= hInstance;
	wc.lpfnWndProc			= WndProc;			// DefWindowProc;
	wc.lpszClassName		= "First";
	wc.lpszMenuName			= 0;
	wc.style				= 0;

	// 2. ���(������Ʈ����)
	RegisterClass(&wc);

	// 3. ������ â ����� 
	HWND hwnd = CreateWindowEx( 0,					// WS_EX_TOPMOST
				 "first",				// Ŭ���� ��
				 "Hello",				// ĸ�ǹ� ����
				 WS_OVERLAPPEDWINDOW, 
				 CW_USEDEFAULT , 0, CW_USEDEFAULT, 0,	// �ʱ� ��ġ 
				 0, 0,			// �θ� ������ �ڵ�, �޴� �ڵ�
				 hInstance,		// WinMain�� 1��° �Ķ���� (exe �ּ�)
				 0);			// ���� ����



	// 4. ������ �����ֱ�
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);
	

	// 5. Message 
	MSG msg;
	while( GetMessage( &msg, 0, 0, 0 ) )
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}