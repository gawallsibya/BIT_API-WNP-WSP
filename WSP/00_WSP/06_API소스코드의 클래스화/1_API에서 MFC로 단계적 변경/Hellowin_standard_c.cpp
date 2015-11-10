//=================================================================
//   00�ܰ� ) ������ C
//=================================================================

#include <windows.h>


LRESULT CALLBACK WndProc(HWND hwnd,UINT iMsg,WPARAM wParam, LPARAM lParam);



//----------------------------------------------------------------------
//1) WinMain()
//----------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,
                   PSTR szCmdLine,int iCmdShow)
{
    static char szAppName[]="HelloWin";
    HWND        hwnd;
    MSG         msg;
    WNDCLASSEX  wndclass;

    wndclass.cbSize         =sizeof(wndclass);
    wndclass.style          =CS_HREDRAW|CS_VREDRAW;
    wndclass.lpfnWndProc    =WndProc;
    wndclass.cbClsExtra     =0;
    wndclass.cbWndExtra     =0;
    wndclass.hInstance      =hInstance;
    wndclass.hIcon          =LoadIcon(NULL,IDI_APPLICATION);
    wndclass.hCursor        =LoadCursor(NULL,IDC_ARROW);
    wndclass.hbrBackground  =(HBRUSH)GetStockObject(WHITE_BRUSH);
    wndclass.lpszMenuName   =NULL;
    wndclass.lpszClassName  =szAppName;
    wndclass.hIconSm        =LoadIcon(NULL,IDI_APPLICATION);

//----------------------------------------------------------------------
//2) ������ Ŭ���� ���
//----------------------------------------------------------------------
    RegisterClassEx(&wndclass);


//----------------------------------------------------------------------
//3) ������ ����
//----------------------------------------------------------------------
    hwnd=CreateWindow(szAppName,    //window class name
        "The Hello Program",        //window caption
        WS_OVERLAPPEDWINDOW,        //window style
        CW_USEDEFAULT,              //initial x position
        CW_USEDEFAULT,              //initial y position
        CW_USEDEFAULT,              //initial x size
        CW_USEDEFAULT,              //initial y size
        NULL,                       //parent window handle
        NULL,                       //window menu handle
        hInstance,                  //program instance handle
        NULL);                      //creation parameters

//----------------------------------------------------------------------
//4) ������ ȭ�鿡 ��Ÿ���� 
//----------------------------------------------------------------------
    ShowWindow(hwnd,iCmdShow);
    //UpdateWindow(hwnd);


//----------------------------------------------------------------------
//5) �޽��� ������ �ۼ� 
//----------------------------------------------------------------------
    /* //
    while (GetMessage(&msg,NULL,0,0))
    {
        //TranslateMessage(&msg);
        static int  i = 0;
        char        buffer[80];
        wsprintf( buffer, "%i\n", ++i );
        OutputDebugString( buffer );
        DispatchMessage(&msg);
    }//while
    /**/
    while ( 1 )
    {
        if ( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
        {
            if ( msg.message == WM_QUIT ) break;
            DispatchMessage(&msg);
        }//if
        static int  i = 0;
        char        buffer[8];
        wsprintf( buffer, "%i\n", ++i );
        OutputDebugString( buffer );		// �޽����� ���� ��� Debug â�� ���ڿ� ��� 
    }//while
    return msg.wParam;
}//WinMain()



//----------------------------------------------------------------------
//6) ������ ���ν����� ����
//----------------------------------------------------------------------
// ť�� ����Ǵ� �޽����� ������� �ʴ� �޽��� 
// GetDC / BeginPaint()
// GetMessage / PeekMessage
// Handle : �ü���� �����ϴ� ���� ��ϵ��� �����ϰ� �����ϴ� ID �� (��������)
LRESULT CALLBACK WndProc(HWND hwnd,UINT iMsg,WPARAM wParam,
                         LPARAM lParam)
{
    HDC         hdc;
    PAINTSTRUCT ps;
    RECT        rect;

    switch (iMsg)
    {
    case WM_CREATE:
        return 0;
    case WM_PAINT:
        hdc=BeginPaint(hwnd,&ps);
        //hdc = GetDC(hwnd);
        GetClientRect(hwnd,&rect);
        DrawText(hdc,"Hello, Windows!",-1,&rect,
            DT_SINGLELINE|DT_CENTER|DT_VCENTER);
        EndPaint(hwnd,&ps);
        //ReleaseDC(hwnd, hdc);
        return 0;
    case WM_LBUTTONDOWN:
        hdc = GetDC(hwnd);
        MoveToEx(hdc,0,0,NULL);
        LineTo(hdc,100,100);
        ReleaseDC(hwnd, hdc);
        return 0;
//    case WM_CLOSE:
//        hdc = GetDC(hwnd);
//        MoveToEx(hdc,0,0,NULL);
//        LineTo(hdc,100,100);
//        ReleaseDC(hwnd, hdc);
//        Sleep(2000);
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }//switch
    return DefWindowProc(hwnd,iMsg,wParam,lParam);
}//WndProc()