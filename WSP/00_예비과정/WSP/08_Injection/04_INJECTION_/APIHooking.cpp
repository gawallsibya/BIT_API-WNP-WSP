#include <stdio.h>
#include <windows.h>

// PEȭ���� ������ �˻��Ϸ��� DbgHelp.dll �� �ʿ��ϴ�.
#include "Dbghelp.h"
#pragma comment(lib, "Dbghelp.lib")

void Replace( HMODULE hModule, // .idata�� ���� ����� �ּ�
			  PCSTR	  dllname, // Hooking �� �Լ��� ���� DLL�̸�
			  PROC	  oldfunc, // ��ŷ�� API �Լ�.
			  PROC    newfunc) // �ٲ� �Լ� 
{
	// 1. module ���� .idata section ���ּҸ� ã�´�.
	ULONG sz = 0;
	PIMAGE_IMPORT_DESCRIPTOR pImage = (PIMAGE_IMPORT_DESCRIPTOR)

		ImageDirectoryEntryToData( hModule, TRUE, // <<----- FALSE �� TRUE�� 

									IMAGE_DIRECTORY_ENTRY_IMPORT, & sz);










	printf(".idata section �� �ּ� : %p\n", pImage );

	// 2. .idata section ���� ���ϴ� Dll�� ��ġ�� ã�´�. 
	for ( ; pImage->Name; ++pImage )
	{
		char* p = ((char*)hModule + pImage->Name);

		if ( strcmpi( p, dllname) == 0 ) break; // ã�� ���
	}
	if ( pImage->Name == 0 ) 
		printf("�ش� ����� %s �� import ���� �ʽ��ϴ�.\n", dllname);

	printf("%s ����� import section �ּ� : %p\n", dllname, pImage );





	//--------------------------------------------------------------
	// 3. Thunk Table ���� ���ϴ� �ּҸ� ��´�.
	PIMAGE_THUNK_DATA pThunk = 
				(PIMAGE_THUNK_DATA)( (char*)hModule + pImage->FirstThunk);

	for ( ; pThunk->u1.Function; ++pThunk )
	{
		if ( (PROC)(pThunk->u1.Function) == oldfunc ) // ã�� ���.
		{
			PROC* p = (PROC*)&(pThunk->u1.Function);

			*p = newfunc; // ���� ����.
		}
	}
}
// user.chol.com/~downboard/dbghelp.zip  �޾Ƽ� ���� Ǫ����..
// dbghelp.dll �� C:\\windows\\system32 �ȿ� �μ���..
// .h �� .lib ���� �۾� ������ ������ ������..


// MessageBox�� ��ü�� �Լ�.
typedef UINT (WINAPI *F)(HWND, PCSTR, PCSTR, UINT);

UINT WINAPI foo( HWND hwnd, PCSTR s, PCSTR title, UINT btn)
{
	printf("foo is called\n");
	printf("Message : %s\n", s);
	printf("TitleBar : %s\n", title );
	
	// �ٽ� ������ MessageBox�� �����Ϸ��� ?
	//MessageBoxA(); // ��� ȣ��..
	// ���� �Լ��� �ּҸ� ���Ѵ�.
	HMODULE hDll = GetModuleHandle("User32.dll");

	F f = (F)GetProcAddress( hDll, "MessageBoxA");

	return f( hwnd, s, title, btn);  // <<!!!
}


void main()
{
	Replace( GetModuleHandle( 0 ), // exe �ּ�
			 "User32.dll", (PROC)MessageBoxA, (PROC)foo );



	void* p = GetModuleHandle( "User32.dll");

	printf("User32.dll �� �ּ� : %p\n", p );
	printf("MessageBoxA�� �ּ� : %p\n", MessageBoxA );

	MessageBoxA( 0, "Hello", "AAA", MB_OK);
}












// MessageBox �� �ᱹ ��ũ���̰� ���� �Լ��� MessageBoxA �Ǵ� MessageBoxW��.