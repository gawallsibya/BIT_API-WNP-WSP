#pragma comment(linker, "/subsystem:windows")

#include <windows.h>

#include <commctrl.h> // ���� ��Ʈ�� ���.
#pragma comment( lib, "comctl32.lib") // comctl32.dll�� ����ϱ� ����.

// Tree �� �׸��� �߰��ϴ� �Լ�.
HTREEITEM AddItem( HWND hTree, HTREEITEM hParent, char* s )
{
	TVINSERTSTRUCT tv;
	tv.hParent      = hParent;  // << -- ���� �ϼ���.
	tv.hInsertAfter = TVI_SORT;
	tv.item.pszText = s;  // << ------ ����.
	tv.item.iImage  = 0;
	tv.item.iSelectedImage = 1;
	tv.item.mask    = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	HTREEITEM hItem = (HTREEITEM)SendMessage( hTree, TVM_INSERTITEM, 0,
												(LPARAM)&tv);	
	return hItem;  // << �߰��ϼ���.
}


void EnumFiles( HWND hTree, HTREEITEM hParent, char* path ) // << ����.
{
	SetCurrentDirectory( path );
	WIN32_FIND_DATA wfd;

	HANDLE hFind = FindFirstFile( "*.*", &wfd );
	do
	{
		if ( ( wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) &&
			!( wfd.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN ) )
		{
			//=========================================
			if ( strcmp( wfd.cFileName, ".")  != 0 &&
				 strcmp( wfd.cFileName, "..") != 0 )
			{
				
				HTREEITEM hItem = AddItem( hTree, hParent, wfd.cFileName);
					
				EnumFiles( hTree, hItem, wfd.cFileName ); // ��� ȣ��.



				SetCurrentDirectory("..");  // �ٽ� ���� ������.!
			}
			//=========================================
		}

	} while ( FindNextFile( hFind, &wfd ) );

	FindClose( hFind );
}








LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HWND hTree;
	
	switch( msg )
	{	
	case WM_CREATE:
			
		InitCommonControls(); // ���� ��Ʈ�� �ʱ�ȭ.

		// 1. Tree Control �����ϱ�.
		hTree = CreateWindow( WC_TREEVIEW, "",
			
			WS_CHILD | WS_VISIBLE | WS_BORDER | TVS_HASLINES | TVS_LINESATROOT |
			TVS_HASBUTTONS,

							10,10,300,500, hwnd, (HMENU)1, 0, 0);

		{
			// 2. Tree�� ImageList �����ϱ�
			HIMAGELIST hImg = ImageList_Create( 16,15,	// image ũ��.
								ILC_COLOR16 | ILC_MASK, // ���� | Mask ��뿩��
											2,  // �ʱ� ũ��
											0); // Grow Size
			// ��Ʈ�� Load
			HBITMAP hBitmap = (HBITMAP)LoadImage( 0, "folder.bmp",
												IMAGE_BITMAP, 0, 0, 
												LR_LOADFROMFILE );

			ImageList_AddMasked( hImg, hBitmap, RGB(0,128,128));
			DeleteObject( hBitmap ); 

			// Tree�� ImageList�� �����Ѵ�.
			SendMessage( hTree, TVM_SETIMAGELIST, TVSIL_NORMAL, (LPARAM)hImg);
		}


		// 2. Tree �׸� �߰�.!! - �ش��ϴ� ����ü�� ���� �޼����� �����Ѵ�.
		{
			EnumFiles( hTree, TVI_ROOT, "C:\\Program Files");

		}	
		return 0;











	case WM_DESTROY:
		PostQuitMessage(0); 
		return 0;
	}
	return DefWindowProc( hwnd, msg, wParam, lParam);
}

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
					LPSTR	  lpCmdLine, int nShowCmd )
{
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

	atom = RegisterClass( &wc);
	
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

	return 0;
}

