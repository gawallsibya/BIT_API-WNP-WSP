#include <stdio.h>
#include <windows.h>

void EnumFiles( char* path )
{
	SetCurrentDirectory( path );
	WIN32_FIND_DATA wfd;

	HANDLE hFind = FindFirstFile( "*.*", &wfd );
	do
	{
		if ( ( wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) &&
			!( wfd.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN ) )
			printf( "%s\n", wfd.cFileName );

	} while ( FindNextFile( hFind, &wfd ) );

	FindClose( hFind );
}


/*
// ��� ȣ�� ����.
void EnumFiles( char* path )
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
			if ( strcmp( wfd.cFileName, ".") != 0 &&
				 strcmp( wfd.cFileName, "..")!= 0 )
			{
				printf( "%s\n", wfd.cFileName );
					
				EnumFiles( wfd.cFileName ); // ��� ȣ��.
				SetCurrentDirectory("..");  // �ٽ� ���� ������.!
			}
			//=========================================
		}

	} while ( FindNextFile( hFind, &wfd ) );

	FindClose( hFind );
}
*/











void main()
{
	EnumFiles( "C:\\");
}










