#include <stdio.h>
#include <windows.h>
#include <conio.h>

DWORD WINAPI foo( void* p)
{
	printf("foo\n");Sleep(5000);
	return 0;					// DllMain() ȣ��->������ ����
}
void main()
{
	getch();
	HMODULE hDll = LoadLibrary("W.dll"); // DllMain()ȣ��.
	if ( hDll == 0)
	{
		printf("DLL�� ������ ������\n");
		return;
	}
	getch();
	HANDLE h = CreateThread( 0, 0, foo, 0, 0,0); // DllMain()ȣ��
	WaitForSingleObject( h, INFINITE);

	getch();
	FreeLibrary( hDll );	// DllMain()ȣ�� -> ���μ������� ����.
}















