#include <windows.h>
#include <TCHAR.h>
#include <windowsX.h>
#include "resource.h"
#include <time.h>   // <<== �߰��� �ּ���..

//--------------------------------------------------------------------------
// Function Declaration
LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

void OnPaint(HWND hwnd);
void OnDestroy( HWND hwnd );
BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);
void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
void OnLButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags);

void Swap(int* a, int* b);
BOOL MoveBlock( HWND hwnd, int x, int y );
void Shuffle( HWND hwnd );

//--------------------------------------------------------------------------
// Global Variable

//--------------------------------------------------------------------------
// WinMain
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE,PSTR lpCmdLine, int nShowCmd)
{
	TCHAR szAppName[] = _T("Puzzle Game");
	WNDCLASS wc;
	wc.cbClsExtra    	= 0;
	wc.cbWndExtra   	= 0;
	wc.hbrBackground 	= (HBRUSH)GetStockObject( LTGRAY_BRUSH);
	wc.hCursor       	= LoadCursor( 0, IDC_ARROW );
	wc.hIcon         	= LoadIcon  ( 0, IDI_WINLOGO);
	wc.hInstance     	= hInstance; 
	wc.lpfnWndProc 	= WndProc;
	wc.lpszClassName 	= szAppName; 
	wc.lpszMenuName 	= MAKEINTRESOURCE(IDR_PUZZLEMENU);
	wc.style         = 0; 

	ATOM atom = RegisterClass( &wc );

	HWND hwnd = CreateWindowEx( 0, szAppName, szAppName, 
						WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX,
						CW_USEDEFAULT, 0, CW_USEDEFAULT,  0, 0, 0, hInstance, 0);

	ShowWindow( hwnd, nShowCmd ); 
	UpdateWindow( hwnd );

	MSG msg;
	while ( GetMessage( &msg, 0, 0, 0) )
	{
		TranslateMessage( &msg );
		DispatchMessage( &msg );
	}
	return msg.wParam;
}



//-------------------------------------------------------------------------
// Window Procedure
LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch( msg )
	{
	HANDLE_MSG(hwnd, WM_CREATE,      OnCreate);
	HANDLE_MSG(hwnd, WM_PAINT,       OnPaint);
	HANDLE_MSG(hwnd, WM_LBUTTONDOWN, OnLButtonDown);
	HANDLE_MSG(hwnd, WM_COMMAND,     OnCommand); // �޴� ó��..!!
	HANDLE_MSG(hwnd, WM_DESTROY,     OnDestroy);
	}
	return DefWindowProc( hwnd, msg, wParam, lParam);
}



//--------------------------------------------------------------------------
// Message Handler
//--------------------------------------------------------------------------
// Global Variable
#define COUNT   5
#define EMPTY   (COUNT*COUNT-1)
#define OX		10
#define OY		10   

HBITMAP 	g_hBitmap;
SIZE    	g_szFull;
SIZE    	g_szBlock;
BOOL    	g_bRunning;
int	g_image[COUNT][COUNT];

//--------------------------------------------------------------------------
// Message Handler
BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct)
{
	HINSTANCE hInstace = lpCreateStruct->hInstance;

	// Bitmap Load
	g_hBitmap = (HBITMAP)LoadImage(0, "Puzzle.bmp",IMAGE_BITMAP, 0,0,LR_LOADFROMFILE);

	// ��Ʈ�� ����� ���ؼ� �������� �ʱ�ȭ.
	BITMAP bm;
	GetObject( g_hBitmap, sizeof(bm), &bm);

	g_szFull.cx = bm.bmWidth;
	g_szFull.cy = bm.bmHeight;

	g_szBlock.cx = g_szFull.cx / COUNT;
	g_szBlock.cy = g_szFull.cy / COUNT;
	//=---------------------------------------------------
	// Ŭ���̾�Ʈ ũ�Ⱑ 520*520 �� �Ǵ� ������ ũ�� ���ϱ�.
	RECT r = {0, 0, g_szFull.cx + OX * 2, g_szFull.cy + OY*2 };
	AdjustWindowRect( &r, GetWindowLong(hwnd, GWL_STYLE), TRUE);

	int width  = r.right-r.left;
	int height = r.bottom - r.top;

	// �����찡 �߾ӿ� ������..
	int x = (GetSystemMetrics( SM_CXSCREEN ) - width) / 2;
	int y = (GetSystemMetrics( SM_CYSCREEN ) - height) / 2;

	MoveWindow( hwnd, x,y, width, height, TRUE);

	g_bRunning = FALSE;

	int k = 0;
	for ( y = 0; y < COUNT; y++)
		for (int x = 0; x < COUNT; x++)
			g_image[y][x] = k++;


	return TRUE;
}

void OnDestroy( HWND hwnd )
{
	DeleteObject( g_hBitmap );
	PostQuitMessage( 0 );
}
void OnPaint(HWND hwnd)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint( hwnd, &ps );
	Rectangle( hdc, OX - 5, OY - 5,	OX + g_szFull.cx + 5,  OY + g_szFull.cy + 5 );

	SetViewportOrgEx( hdc, OX, OY, 0);

	HDC dcMem = CreateCompatibleDC( hdc );
	HBITMAP old = (HBITMAP)SelectObject( dcMem, g_hBitmap);

	for ( int y = 0; y < COUNT; y++)
	{
		for (int x = 0; x < COUNT; x++)
		{
			if ( g_image[y][x] == EMPTY ) // EMPTY
			{
				// ��� �簢�� �׸���.(�׵θ� ���� )
				PatBlt( hdc, x*g_szBlock.cx, y*g_szBlock.cy, g_szBlock.cx, g_szBlock.cy, WHITENESS);
			}
			else
			{
				POINTS pt = {g_image[y][x] % COUNT, g_image[y][x]/COUNT }; 

				BitBlt( hdc, 
					x * g_szBlock.cx, 
					y * g_szBlock.cy, 
					g_szBlock.cx - 1,  // <<== ���� ��� ũ�� ���� 1���� 
					g_szBlock.cy - 1,  // <<===
					dcMem, 
					pt.x * g_szBlock.cx , pt.y * g_szBlock.cy, SRCCOPY);
			}
		}
	}
	SelectObject( dcMem, old );
	DeleteDC( dcMem );
	EndPaint( hwnd, &ps );
}

/*
void OnPaint(HWND hwnd)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint( hwnd, &ps );

	// ��� �簢���� �׸���.
	Rectangle( hdc, OX - 5, OY - 5,	OX + g_szFull.cx + 5,  OY + g_szFull.cy + 5 );

	// ������ 10,10 ���� �̵��Ѵ�.
	SetViewportOrgEx( hdc, OX, OY, 0);

	// ���� �׸��� ����Ѵ�.
	HDC dcMem = CreateCompatibleDC( hdc );
	HBITMAP old = (HBITMAP)SelectObject( dcMem, g_hBitmap);

	int n = 7;
	POINTS pt = { n % COUNT, n / COUNT};

	BitBlt( hdc, 0, 0, g_szBlock.cx, g_szBlock.cy, 
			dcMem, 

			pt.x * g_szBlock.cx ,	// <<===== 
			pt.y * g_szBlock.cy,	// <<=====
			
			SRCCOPY);
	//-------------------------------------------------------------

	SelectObject( dcMem, old );
	DeleteDC( dcMem );
	EndPaint( hwnd, &ps );
}

*/



void Swap(int* a, int* b)
{
	int t = *a;
	*a = *b;
	*b = t;
} 

BOOL MoveBlock( HWND hwnd, int x, int y )
{
	// Rectangle Current Block - ���콺�� Ŭ���� x,y ����� ũ��.
	RECT r = { x * g_szBlock.cx,y * g_szBlock.cy,(x+1) * g_szBlock.cx, (y+1)* g_szBlock.cy };

	// 4������ �̵� ���� �� ���� ����.
	if ( y > 0 && g_image[y-1][x] == EMPTY )
	{
		Swap( &g_image[y][x], &g_image[y-1][x]);
		r.top -= g_szBlock.cy;
	}
	else if ( y < COUNT-1 && g_image[y+1][x] == EMPTY )
	{
		Swap( &g_image[y][x], &g_image[y+1][x]);
		r.bottom += g_szBlock.cy;
	}
	else if ( x > 0 && g_image[y][x-1] == EMPTY )
	{
		Swap( &g_image[y][x], &g_image[y][x-1]);
		r.left -= g_szBlock.cx;
	}
	else if ( x < COUNT-1 && g_image[y][x+1] == EMPTY )
	{
		Swap( &g_image[y][x], &g_image[y][x+1]);
		r.right += g_szBlock.cx;
	}
	else
		return FALSE;

	// ���� ��ȿȭ�� ������ ���� ��ŭ �̵��� �ش�.
	OffsetRect(&r, OX, OY); 

	// ��ȿȭ�ϸ� WM_PAINT �� �ش� 2����� �ٽ� �׷��ش� -> �̵��ϴ� ȿ��.
	InvalidateRect( hwnd, &r, FALSE);
	UpdateWindow( hwnd );

	return TRUE;
} 

void OnLButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags)
{
	// ������ �������� �ƴϰų� �������� ��� ���
	if ( (!g_bRunning) || ( x < OX ) || ( x > OX + g_szFull.cx) ||
		( y < OY ) || ( y > OY + g_szFull.cy ) )
	return ;

	// ��ǥ(pixel)  ��� x,y ���ϱ�
	int xBlock = (x - OX) / g_szBlock.cx;
	int yBlock = (y - OY) / g_szBlock.cy;

	// �̵� ���� �ϸ� �̵�. �Ұ����ϴ� FALSE �� ������ �Լ�.
	if ( ! MoveBlock( hwnd, xBlock, yBlock) )
		MessageBeep( 0 );
}


void Shuffle( HWND hwnd )
{
	enum { LEFT = 0, RIGHT = 1, UP = 2, DOWN = 3};
	srand(time(0) );
	// �ʱ� ����� 4,4 �̴�.
	int empty_x = COUNT-1;  // <<---
	int empty_y = COUNT-1;  // <<---
	int count = 0;
	while( 1 )
	{
		// ���� ���� 0~3�� ��´�.
		switch( ( rand() % 4) )
		{
		// ���� ���� ���� ����� ��,�Ʒ�, ��,�� �� 1���� ��´�.
		case LEFT: empty_x = max(0,       empty_x - 1 ); break;
		case RIGHT:empty_x = min(COUNT-1, empty_x + 1 ); break; // <<----
		case UP:   empty_y = max(0,       empty_y - 1 ); break;
		case DOWN: empty_y = min(COUNT-1, empty_y + 1 ); break; // <<----
		}
		// ���õ� ����� �̵� �غ���. �̵� �Ұ��� �Ҽ��� �ִ�. 250�� ����������!
		if ( MoveBlock( hwnd, empty_x, empty_y) ) 
		{
			++count;
			if ( count == COUNT * 50 ) break; // 250 �� ���´�.
			Sleep(50); // 1����� �����Ŀ� 0.05s ��� �Ѵ�.
		}
	}
}


void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	switch( id )
	{
	case ID_GAME_NEW: 
		if ( g_bRunning == TRUE )
		{
			UINT ret = MessageBox(hwnd, "���� ������ ���� �Ͻðڽ��ϱ� ?", "Ȯ��", MB_YESNO);
			if (ret != IDYES ) return;
		} 
		Shuffle( hwnd );
		g_bRunning = TRUE;
			return;


	case ID_GAME_HINT: return;

	case ID_GAME_EXIT:
		SendMessage( hwnd, WM_CLOSE, 0,0);
		return;
	}
}








