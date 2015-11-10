// �ڵ� ���� ...
#include <windows.h>
/*
4G ���μ����� �ּ� �������� K O H T �� �����Ѵ�.

  ex) 1) CreateFile ���� -> ���ϰ��� file�� �ڵ�.
      2) ���ϵ� �ڵ��� Process �ּҰ����� KOT�� Index ���̴�..

      3) ���� � �������� �ڵ��� ������ �ִٰ� �ص� �� ��������
	     K O H T �� File�� ���� �ڵ��� Index�� ���ٸ� WriteFile ��
		 �� ����..

      4) �ٸ� �����쿡�� ������ �۾��� ���ְ� �ʹٸ�
	     DuplicateHandle�� ���� ������ ����ϸ� �ȴ�..

  ex) ��¥ ������ ��
      h1 = CreateFile(...)
	  h2 = h1;
	  CloesHandle( h1);
	  WriteFile( h2, "aaa");	// ��� �Ұ�

      CloesHandle �Լ��� �ǹ� 
	  => K O H T ���� �ش� Index(Handle)�� �����ϴ� ����.
	     ���� �ش� K O �� ���� ������ �����Ѵ�...
*/
LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//---------------------------------
	static PROCESS_INFORMATION	pi;
	static HANDLE	hProcess1;
	static HANDLE	hProcess2;
	//---------------------------------
	switch( msg )
	{
	case WM_LBUTTONDOWN:
		{
			STARTUPINFO	si	= { sizeof(si) };
			si.dwY			= 0;
			si.dwX			= 0;
			si.dwXSize		= 100;
			si.dwYSize		= 100;
			si.dwFlags		= STARTF_USEPOSITION;
			BOOL b = CreateProcess(NULL, "notePad.exe", 
				NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, &si, &pi);

			// ��¥ ���� 
			hProcess1 = pi.hProcess;

			// ��¥ ���� 
			DuplicateHandle(  GetCurrentProcess(),	// �� ���μ�������
							  pi.hProcess,			// �� �ڵ���
							  GetCurrentProcess(),	// �� ���μ����� �����϶�. 
							  &hProcess2,			// hProcess�� �ڵ鰪 ����
							  0, FALSE,				// ���� ����, ��� 
							  DUPLICATE_SAME_ACCESS);
			if( b )
			{
				CloseHandle(pi.hProcess);
				CloseHandle(pi.hThread);
			}
		}
		return 0;
	case WM_RBUTTONDOWN:
		TerminateProcess(hProcess2, 0);

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