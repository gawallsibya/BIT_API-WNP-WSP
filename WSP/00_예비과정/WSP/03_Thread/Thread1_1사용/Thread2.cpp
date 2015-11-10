// ���丮 ����.

#include <windows.h>

// ������ �Լ�
DWORD WINAPI	CFunc( LPVOID p)
{
	HWND	hwnd = (HWND)p;

	// hChange : ���丮�� ������ �� �ִ� Ŀ�� ������Ʈ 
	// ���丮�� ��ȭ�� �ִٸ� Signal ���·� ����ȴ�.
	HANDLE	hChange = FindFirstChangeNotification(
		"c:\\"	,	// ������ ���丮
		TRUE,		// ���� �˻� ���� 
		FILE_NOTIFY_CHANGE_DIR_NAME);	// ���丮 ���� �÷���
	
	while(1)
	{
		// Signal ���°� �Ǹ� ���ϵǴ� ��� �Լ� 
		WaitForSingleObject(hChange, INFINITE);
		// ������� ��ȭ ���ø� �ϰ�, ó���� �ֽ����忡�� ���ִ� ���� ����.
		// file �ý����� ��ȭ�� �ֽ����忡 �����Ѵ�.
		PostMessage(hwnd, WM_USER+100, 0, 0);
		MessageBox(hwnd, "WM_USER+100", 0, 0);
		MessageBox(NULL, "Change...", "", MB_OK);
		// ����ؼ� ���� ����..
		FindNextChangeNotification(hChange);
	}
	// �޽��� ť�� ������ �����ø��� ���� ���� ������ �� �ִ�.
	// �޽��� ������ while���� ���� �����ϸ� ��..
	MSG msg;
	while( GetMessage(&msg, 0, 0, 0))
	{
		if( msg.message == WM_USER + 200 )
		{
			MessageBox(NULL, "test", "", MB_OK);
			break;
		}
	}
	// ���ø� �����Ѵ�.
	FindCloseChangeNotification(hChange);
	return 0;
}

LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static DWORD	ThreadID;
	switch( msg )
	{
	case WM_LBUTTONDOWN:
		// ������ ����
		CreateThread(NULL, 0, CFunc, hwnd, 0, &ThreadID);
		return 0;
	case WM_RBUTTONDOWN:
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