//=================================================================
//   03�ܰ� ) �ɹ� �Լ� ������ ���̺��� �̿� 
//			 - �߰��Ǵ� �޽����� ���� �ڵ�ȭ�� ���� 
//			 - �⺻ ���� : �޽����� �ڵ鷯�� �ϳ��� �迭�� ����
//				�޽��� ���̶� �� 
//=================================================================


#include <windows.h>

//Forward declaration------------------------------------------------
LRESULT CALLBACK WndProc(HWND hwnd,UINT iMsg,WPARAM wParam,
                         LPARAM lParam);



//Class CObject------------------------------------------------------
class CObject 
{
protected:
    static char szAppName[];
    HWND        hwnd;
    MSG         msg;
    WNDCLASSEX  wndclass;
public:

    void InitInstance(HINSTANCE hInstance,PSTR szCmdLine,
                      int iCmdShow);

    void Run();

    WPARAM ExitInstance();

	// �޽��� ���� ���� �����Լ��� ������ 
};


void CObject::InitInstance(HINSTANCE hInstance,PSTR szCmdLine,
                        int iCmdShow) {
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

    RegisterClassEx(&wndclass);

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

    ShowWindow(hwnd,iCmdShow);
    UpdateWindow(hwnd);
}

void CObject::Run() 
{
    while (GetMessage(&msg,NULL,0,0)) 
	{
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

WPARAM CObject::ExitInstance() 
{
    return msg.wParam;
}

char CObject::szAppName[]="HelloWin";




//�߰��� �ҽ� �ڵ� ---------------------------------------

class CView;

//CView �ɹ� �Լ��� �Լ� ������ ������ (���� : void, ���� : void)
typedef void (CView::*CViewFunPointer)();

typedef struct tagMessageMap 
{
    UINT iMsg;
    CViewFunPointer fp;
} MessageMap;

static CViewFunPointer fpCViewGlobal;
//�߰��� �ҽ� �ڵ� ---------------------------------------



class CView : public CObject 
{
public:

	//   �޽��� �� �迭 ���� 
    static MessageMap messageMap[];
public:

	// �޽��� �߰� 
    void OnCreate();
    void OnDraw();
    void OnDestroy();
};


//{{BEGIN_MESSAGE_MAP
MessageMap CView::messageMap[]=
{
    {WM_CREATE,		CView::OnCreate},	// �޽��� id,  �޽��� �ڵ鷯 
    {WM_PAINT,		CView::OnDraw},
    {WM_DESTROY,	CView::OnDestroy},
    {0,NULL}
};
//}}END_MESSAGE_MAP



//CView Event handler------------------------------------------------
void CView::OnCreate() {}


void CView::OnDraw()
{
    HDC         hdc;
    PAINTSTRUCT ps;
    RECT        rect;

    hdc=BeginPaint(hwnd,&ps);
    GetClientRect(hwnd,&rect);
    DrawText(hdc,"Hello, Windows!",-1,&rect,
        DT_SINGLELINE|DT_CENTER|DT_VCENTER);
    EndPaint(hwnd,&ps);
}


void CView::OnDestroy() 
{
    PostQuitMessage(0);
}


//Global object------------------------------------------------------
CView app;



//Window procedure---------------------------------------------------
LRESULT CALLBACK WndProc(HWND hwnd,UINT iMsg,WPARAM wParam,
                         LPARAM lParam) {
    int i=0;

    while (CView::messageMap[i].iMsg!=0) 
	{
        if (iMsg==CView::messageMap[i].iMsg) 
		{
            fpCViewGlobal=CView::messageMap[i].fp;
            (app.*fpCViewGlobal)();
            return 0;
        }
        ++i;
    }
    return DefWindowProc(hwnd,iMsg,wParam,lParam);
}



int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,
                   PSTR szCmdLine,int iCmdShow) 
{
    app.InitInstance(hInstance,szCmdLine,iCmdShow);

    app.Run();

    return app.ExitInstance();
}



/*

MFC�� �޽��� �� ������ ����� �� ������ ����..

WinMain�� �ڵ�ȭ �Ǿ���.
������ ���ν����� �ڵ�ȭ �Ǿ���.

���α׷��Ӵ� ���� CView�� �޽��� �ʿ��� �����ϸ� �� 

*/