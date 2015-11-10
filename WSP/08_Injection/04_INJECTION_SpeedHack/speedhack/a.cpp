#include <windows.h>
#include "Dbghelp.h"
#pragma comment( lib, "Dbghelp.lib")


void Replace( HMODULE hModule, // .idata�� ���� ����� �ּ�
			  PCSTR	  dllname, // Hooking �� �Լ��� ���� DLL�̸�
			  PROC	  oldfunc, // ��ŷ�� API �Լ�.
			  PROC    newfunc) // �ٲ� �Լ� 
{
	// 1. module ���� .idata section ���ּҸ� ã�´�.
	ULONG sz = 0;
	PIMAGE_IMPORT_DESCRIPTOR pImage = (PIMAGE_IMPORT_DESCRIPTOR)
						ImageDirectoryEntryToData( hModule, TRUE,
									IMAGE_DIRECTORY_ENTRY_IMPORT, & sz);

	// 2. .idata section ���� ���ϴ� Dll�� ��ġ�� ã�´�. 
	for ( ; pImage->Name; ++pImage )
	{
		char* p = ((char*)hModule + pImage->Name);

		if ( strcmpi( p, dllname) == 0 ) break; // ã�� ���
	}
	//--------------------------------------------------------------
	// 3. Thunk Table ���� ���ϴ� �ּҸ� ��´�.
	PIMAGE_THUNK_DATA pThunk = 
				(PIMAGE_THUNK_DATA)( (char*)hModule + pImage->FirstThunk);

	for ( ; pThunk->u1.Function; ++pThunk )
	{
		if ( (PROC)(pThunk->u1.Function) == oldfunc ) // ã�� ���.
		{
			PROC* p = (PROC*)&(pThunk->u1.Function);

			// .idata section �κ��� ��ȣ �Ӽ��� �����Ѵ�.
			DWORD old;
			VirtualProtect( p,		// �� �ּ��� ����
							4,		// 4 Byte �� 
							PAGE_READWRITE,		// �а� ����� 
							&old);				// ���� ��ȣ�Ӽ� ����.



			*p = newfunc; // ���� ����.
		}
	}
}
















typedef UINT (WINAPI *F)(HWND, UINT, UINT, TIMERPROC);

UINT WINAPI MySetTimer( HWND hwnd, UINT id, UINT ms, TIMERPROC f )
{
	// ���� �Լ��� �ּҸ� ã�´�.
	HMODULE h = GetModuleHandle("User32.dll");
	F func = (F)GetProcAddress( h, "SetTimer");

	return func( hwnd, id, ms/20, f ); // 20�� ������ ���� �ϵ��� �Ѵ�.
}

BOOL WINAPI DllMain( HANDLE h, DWORD r, LPVOID how )
{
	if ( r == DLL_PROCESS_ATTACH )
	{
	

		Replace( GetModuleHandle(0), "user32.dll", (PROC)SetTimer,
													(PROC)MySetTimer);
	}
	return TRUE;
}

// DbgHelp.h �� Dbghelp.lib �� ��� ������ ������..

// �ϼ��� speedhack.dll �� D:\\ �Ʒ� ���� �ϼ���.

// �׸��� ���� ���� �ҽ��� DLLinject ���� ������.



































