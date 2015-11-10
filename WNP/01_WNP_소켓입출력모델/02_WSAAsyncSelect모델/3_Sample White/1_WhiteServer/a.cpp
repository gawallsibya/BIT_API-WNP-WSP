// user.chol.com/~downboard/async.txt ������ ������.
#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <windows.h>
#pragma comment(lib, "ws2_32.lib")

struct LINE
{
	POINTS ptFrom;
	POINTS ptTo;
};

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static SOCKET listen_socket,  link_socket;
	static POINTS ptFrom;

	switch( msg )
	{	
	case WM_LBUTTONDOWN: ptFrom = MAKEPOINTS(lParam); return 0;
	case WM_MOUSEMOVE:
		if ( wParam & MK_LBUTTON )
		{
			POINTS pt = MAKEPOINTS(lParam);
			HDC hdc = GetDC( hwnd );

			MoveToEx( hdc, ptFrom.x, ptFrom.y, 0);
			LineTo  ( hdc, pt.x,     pt.y );
			ReleaseDC( hwnd, hdc );

			// client�� ������.
			LINE line;
			line.ptFrom = ptFrom;
			line.ptTo   = pt;

			send( link_socket, (char*)&line, sizeof(line), 0);
			ptFrom = pt;
		}
		return 0;

	case WM_USER+100:
		{
			WORD event = WSAGETSELECTEVENT( lParam );
			WORD error = WSAGETSELECTERROR( lParam );

			switch( event )
			{
			case FD_CLOSE:
				SetWindowText( hwnd, "������ ���� �����ϴ�.");
				closesocket( link_socket );
				return 0;

			case FD_READ:
				{
					// data ���� - �о� ����.
					LINE line;
					recv( link_socket, (char*)&line, sizeof(line), 0);

					HDC hdc = GetDC( hwnd );
					MoveToEx( hdc, line.ptFrom.x, line.ptFrom.y, 0);
					LineTo  ( hdc, line.ptTo.x,   line.ptTo.y);
					ReleaseDC( hwnd, hdc );
				}
				return 0;

			case FD_ACCEPT:
				{
					SOCKADDR_IN addr;
					int	size = sizeof( addr );

					link_socket = accept( listen_socket, (SOCKADDR*)&addr, &size);

					// ��� ������ �ݴ´�.(1:1 ���)
					closesocket( listen_socket); 

					SetWindowText( hwnd, "���� �Ǿ����ϴ�.");
					
					// ����� ������ �񵿱� �������� �����Ѵ�.
					WSAAsyncSelect( link_socket, hwnd, WM_USER+100, FD_READ | FD_CLOSE );
				}
				break;
			}
			break;
		}
		return 0;

	case WM_CREATE:
		{
			listen_socket = socket( AF_INET, SOCK_STREAM, 0 );

			// socket �� �񵿱� �������� �����Ѵ�.
			WSAAsyncSelect( listen_socket, hwnd, WM_USER+100, FD_ACCEPT);

			SOCKADDR_IN addr;
			addr.sin_family      = AF_INET;
			addr.sin_port        = htons( 6000 );
			addr.sin_addr.s_addr = INADDR_ANY;

			bind( listen_socket, (SOCKADDR*)&addr, sizeof(addr));

			listen( listen_socket, 5);
		}
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0); 
		return 0;
	}
	return DefWindowProc( hwnd, msg, wParam, lParam);
}

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR	lpCmdLine, int nShowCmd )
{
	WSADATA wsadata;
	if ( WSAStartup( MAKEWORD(2,2), &wsadata) != 0 )
	{
		MessageBox( 0, "Error", "", MB_OK);
		return 0;
	}

	ATOM atom;
	WNDCLASS wc;
	HWND hwnd;
	MSG msg;
	
	wc.cbClsExtra	= 0;
	wc.cbWndExtra	= 0;
	wc.hbrBackground= (HBRUSH)GetStockObject( WHITE_BRUSH ); 
	wc.hCursor		= LoadCursor( 0, IDC_ARROW );
	wc.hIcon		= LoadIcon( 0, IDI_APPLICATION);
	wc.hInstance	= hInstance;
	wc.lpfnWndProc  = WndProc; 
	wc.lpszClassName= "First";
	wc.lpszMenuName = 0;
	wc.style		= 0;

	atom = RegisterClass(&wc);
	
	if ( atom == 0 ) 
	{
		MessageBox( 0, "Fail To RegisterClass", "Error", MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx( 0, "first", "Hello", WS_OVERLAPPEDWINDOW,
								CW_USEDEFAULT, 0, CW_USEDEFAULT,0, 0, 0, 
								hInstance, 0); 
	ShowWindow( hwnd, nShowCmd); 
	UpdateWindow( hwnd );

	while ( GetMessage( &msg, 0, 0, 0) ) 
	{							
		TranslateMessage(&msg);
		DispatchMessage( &msg);
	}

	WSACleanup();
	return 0;
}


