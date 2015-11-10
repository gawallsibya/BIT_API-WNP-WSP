//------------------------------------------------------------
// [ BITMAP ����ϱ� ]
// 
//  �������� BITMAP  
//     - DDB(Device Dependant Bitmap)
//     - DIB(Device InDependant Bitmap)

//  LoadBitmap : ���ҽ��� �ִ� Bitmap ��������
//  LoadImage  : ���Ͽ� �ִ� Bitmap �������� 
//------------------------------------------------------------



#include <windows.h>

#include "resource.h"

LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch( msg )
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc( hwnd, msg, wParam, lParam);
}

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE , LPSTR lpCmdLine, int nShowCmd)
{
	WNDCLASS wc;
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
		
	// ���ҽ��� �ִ� ��Ʈ�� Load�ϱ�.
	//HBITMAP hBitmap = LoadBitmap( hInstance, MAKEINTRESOURCE(IDB_BITMAP1));

	// ȭ���� �ٷ� Load�ϱ� - JPG�� �ٸ� �׸��� �ٷ�� �ʹٸ� ���ͳݿ���
	//						 intel jpeg ���̺귯���� ���� ������.
	HBITMAP hBitmap = (HBITMAP)LoadImage( 0,  // ���ҽ����� �ε��Ҷ��� ���
										"C:\\windows\\��ä.bmp",
										IMAGE_BITMAP,
										0, 0, // Ŀ��, Icon load�ø� ���
										LR_LOADFROMFILE);
										
	// ��Ʈ������ �귯�� �����
	HBRUSH brush = CreatePatternBrush( hBitmap );

	// ��Ʈ���� ����� ����� �ı��ؾ� �Ѵ�.
	DeleteObject( hBitmap);

	wc.hbrBackground = brush; //(HBRUSH)GetStockObject( WHITE_BRUSH ); 
	//-----------------------------------------------------------


	wc.hCursor       = LoadCursor( 0, IDC_ARROW );	
	wc.hIcon         = LoadIcon( 0, IDI_WINLOGO);   
	wc.hInstance     = hInstance;
	wc.lpfnWndProc   = WndProc; 
	wc.lpszClassName = "First"; 
	wc.lpszMenuName  = 0;
	wc.style         = 0;

	ATOM atom = RegisterClass( &wc );

	HWND hwnd = CreateWindowEx( 0, "First", "Hello", WS_OVERLAPPEDWINDOW , CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,0, 0,  0,0);

	ShowWindow( hwnd, nShowCmd );

	MSG msg;
	while ( GetMessage( &msg, 0, 0, 0) )
	{
		DispatchMessage( &msg );
	}

	return 0;
}
