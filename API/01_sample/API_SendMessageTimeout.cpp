// TEST.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include <windows.h>


 

#define WM_ADD WM_APP+100   // �ٸ����α׷����� ����� ���� '������ �޼���'�̸��� ����

int _tmain(int argc, _TCHAR* argv[])
{ int a, b, r;                                                    // a,b�� ����� �Է� ���ڰ�,
                                                                      // r�� �ٸ� ���α׷����� ������ ����� �����ϴ� �Լ�
    LPDWORD sum;                                           // ������� ����ִ°��� �����͸� ������ �Լ�
    HWND hwnd = FindWindow(0, _T("HW_Receive")); // ������ �̸��� HW_Receive�� ���ִ� ���α׷��� �ڵ鰪 ����

 

    sum = (LPDWORD)malloc(sizeof(DWORD));

 

    if(hwnd != 0)        // HW_Receive�� �ڵ鰪�� ã������...
    {
        // ����ڰ� ���� �� �Է�
        printf("ù��° ���� �Է��� �ֽʽÿ�~ => ");
        scanf("%d", &a);
        printf("�ι�° ���� �Է��� �ֽʽÿ�~ => ");
        scanf("%d", &b);

 

        // ã�� �ڵ鰪�� �����쿡 ���ڰ���, WM_ADD�޼����� ������.
        // �״��� 5�ʵ��� ���ϰ��� �������, ���α׷� ��� ����
        r = SendMessageTimeout(hwnd, WM_ADD, a, b, SMTO_NORMAL, 5000, sum);

 

        if(r != 0)           // ��������κ��� ������ �־��� ���..
        {
            printf("\n���� - ����, ���� - ����\n");
            printf("�� ���� ����: %d\n", *sum);
        }
        else                // ��������κ��� ������ ������ ���...

            printf("\n���� - ����, ���� - ����\n");

    }
    else                    // HW_Receive�� �ڵ鰪�� ã�� ��������..
        MessageBox(0, _T("�޴����� ���α׷��� ��������� �ʽ��ϴ�."), _T("����!"), MB_OK | MB_ICONEXCLAMATION);

 

    free(sum); 
	return 0;
}




// TESTS.cpp : ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "TESTS.h"

#define MAX_LOADSTRING 100

// ���� ����:
HINSTANCE hInst;								// ���� �ν��Ͻ��Դϴ�.
TCHAR szTitle[MAX_LOADSTRING];					// ���� ǥ���� �ؽ�Ʈ�Դϴ�.
TCHAR szWindowClass[MAX_LOADSTRING];			// �⺻ â Ŭ���� �̸��Դϴ�.

// �� �ڵ� ��⿡ ��� �ִ� �Լ��� ������ �����Դϴ�.
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: ���⿡ �ڵ带 �Է��մϴ�.
	MSG msg;
	HACCEL hAccelTable;

	// ���� ���ڿ��� �ʱ�ȭ�մϴ�.
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_TESTS, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ���� ���α׷� �ʱ�ȭ�� �����մϴ�.
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TESTS));

	// �⺻ �޽��� �����Դϴ�.
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  �Լ�: MyRegisterClass()
//
//  ����: â Ŭ������ ����մϴ�.
//
//  ����:
//
//    Windows 95���� �߰��� 'RegisterClassEx' �Լ����� ����
//    �ش� �ڵ尡 Win32 �ý��۰� ȣȯ�ǵ���
//    �Ϸ��� ��쿡�� �� �Լ��� ����մϴ�. �� �Լ��� ȣ���ؾ�
//    �ش� ���� ���α׷��� �����
//    '�ùٸ� ������' ���� �������� ������ �� �ֽ��ϴ�.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TESTS));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_TESTS);
	wcex.lpszClassName	= _T("HW_Receive");
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   �Լ�: InitInstance(HINSTANCE, int)
//
//   ����: �ν��Ͻ� �ڵ��� �����ϰ� �� â�� ����ϴ�.
//
//   ����:
//
//        �� �Լ��� ���� �ν��Ͻ� �ڵ��� ���� ������ �����ϰ�
//        �� ���α׷� â�� ���� ���� ǥ���մϴ�.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

   hWnd = CreateWindow(_T("HW_Receive"), _T("HW_Receive"), WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ����: �� â�� �޽����� ó���մϴ�.
//
//  WM_COMMAND	- ���� ���α׷� �޴��� ó���մϴ�.
//  WM_PAINT	- �� â�� �׸��ϴ�.
//  WM_DESTROY	- ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.
//
//


#define WM_ADD WM_APP+100   // �ٸ����α׷����� ����� ���� '������ �޼���'�̸��� ����
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_ADD :                 // WM_ADD(����� ���� ������ �޼���)�� ȣ��ްԵǸ� �����
        MessageBox(0, _T("Ȯ�ι�ư�� ������ ���갪�� �����ݴϴ�."), _T("����~ ¦¦¦~"), MB_OK | MB_ICONHAND);
        return wParam + lParam;  // �޼��� ȣ��� �Բ� ���� 2�� ������ ����, �޼����� �������� ������.
   
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// �޴��� ���� ������ ���� �м��մϴ�.
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: ���⿡ �׸��� �ڵ带 �߰��մϴ�.
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// ���� ��ȭ ������ �޽��� ó�����Դϴ�.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
