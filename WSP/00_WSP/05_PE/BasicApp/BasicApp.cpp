/*******************************************************************************
 * ��  �� : HelloWin.C
 * ��  �� : C ��ü
 * ��  �� : WinMain - Win32 Entry Point.
 *          WndProc - Windows Procedure.
 * ��  �� : ���� �������� �������� GUI ���ø����̼��� ����...
 * ----------------------------------------------------------------------------
 * ��  �� : Yi HoDong
 * ��  ¥ : 2001.11.06
 * ��  �� : 1.0
 * ȸ  �� : YHD Works Co. (http://www.yhdworks.com)
 ******************************************************************************/
#include <windows.h>


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


/*******************************************************************************
 * ��  �� : WIN32 ��Ʈ�� ����Ʈ �c��
 * ��  �� : ����
 * ��  �� : WinMain
 * ��  �� : HINSTANCE hInstance [IN] : �� ���μ����� �ν��Ͻ� �ڵ�(���۹���)
 *          HINSTANCE hPrevInst [IN] : ������ 0, ����(16��Ʈ���� ȣȯ�� ����)
 *          PSTR      szCmdLine [IN] : Ŀ�ǵ� ���� �з�����
 *          int       iCmdShow  [IN] : �����찡 �������� ����
 * ��  ȯ : int : 
 * ��  �� : WIN32 ��Ʈ�� ����Ʈ �c��
 *          �ܼ� ���α׷�(main)���� �ٸ��� GUI������ WinMain�� ��Ʈ�� ����Ʈ
 *          �Լ��� �ν��Ѵ�.
 * ----------------------------------------------------------------------------
 * ��  �� : Yi HoDong
 * ��  ¥ : 2001.08.06
 * ��  �� : 1.0
 * ȸ  �� : YHD Works Co. (http://www.yhdworks.com)
 ******************************************************************************/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst,
                   PSTR szCmdLine, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT("HelloWin");
	HWND         hWnd;
	MSG          msg;
	WNDCLASS     wndclass;

	//TCHAR szOut[32];
	//wsprintf(szOut, "0x%08X", hInstance);
	//MessageBox(NULL, szOut, TEXT("HINSTANCE ��"), MB_OK);

	////////////////////////////////////////////////////////////////////////////
	//�������� Ŭ���� ���
	////////////////////////////////////////////////////////////////////////////
	wndclass.style         = CS_HREDRAW|CS_VREDRAW;
	wndclass.lpfnWndProc   = WndProc;
	wndclass.cbClsExtra    = 0;
	wndclass.cbWndExtra    = 0;
	wndclass.hInstance     = hInstance;
	wndclass.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName  = NULL;
	wndclass.lpszClassName = szAppName;

	if(!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("This program requires Windows NT!"),
				  szAppName, MB_ICONERROR) ;
		return 0 ;
	}
	////////////////////////////////////////////////////////////////////////////


	////////////////////////////////////////////////////////////////////////////
	//�������� ����
	////////////////////////////////////////////////////////////////////////////
	hWnd = CreateWindow(szAppName,					// window class name
						TEXT("The Hello Program"),	// window caption
						WS_OVERLAPPEDWINDOW,		// window style
						CW_USEDEFAULT,              // initial x position
						CW_USEDEFAULT,              // initial y position
						CW_USEDEFAULT,              // initial x size
						CW_USEDEFAULT,              // initial y size
						NULL,                       // parent window handle
						NULL,                       // window menu handle
						hInstance,                  // program instance handle
						NULL) ;                     // creation parameters

	ShowWindow(hWnd, iCmdShow);
	UpdateWindow(hWnd);
	////////////////////////////////////////////////////////////////////////////


	////////////////////////////////////////////////////////////////////////////
	//�޽��� ����
	////////////////////////////////////////////////////////////////////////////
	while(GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	////////////////////////////////////////////////////////////////////////////

	return msg.wParam;
}
////////////////////////////////////////////////////////////////////////////////


/*******************************************************************************
 * ��  �� : �������� ���ν��� �Լ�(�ݹ� �Լ�)
 * ��  �� : ����
 * ��  �� : WndProc
 * ��  �� : HWND   hWnd   [IN] : �޽����� ���� ������ �ڵ�
 *          UINT   uMsg   [IN] : �޽���
 *          WPARAM wParam [IN] : ����1
 *          LPARAM lParam [IN] : ����2
 * ��  ȯ : LRESULT : 
 * ��  �� : �������� ���ν���
 *          WINDOWCLASS�� lpfnWndProc �ʵ忡 �� �Լ��� ������ ����ؾ� �Ѵ�.
 *          �������� ������ �� �Լ� ������ ��Ʈ���Ѵ�.
 * ----------------------------------------------------------------------------
 * ��  �� : Yi HoDong
 * ��  ¥ : 2001.08.06
 * ��  �� : 1.0
 * ȸ  �� : YHD Works Co. (http://www.yhdworks.com)
 ******************************************************************************/
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC         hDC;
	PAINTSTRUCT ps;
	RECT        rc;
	static char szOutBuf[] = 
		TEXT("The Most Simple Windows GUI Program by YHD.");

	switch(uMsg)
	{
		case WM_PAINT:
			hDC = BeginPaint(hWnd, &ps);
			GetClientRect(hWnd, &rc);
			DrawText(hDC, 
					 szOutBuf, 
					 lstrlen(szOutBuf), 
					 &rc, 
					 DT_SINGLELINE|DT_CENTER|DT_VCENTER);
			EndPaint (hWnd, &ps) ;
		return 0;

		case WM_DESTROY:
			PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
////////////////////////////////////////////////////////////////////////////////