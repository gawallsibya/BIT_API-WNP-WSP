#include <windows.h>
#include <conio.h>
#include <stdio.h>
// DLL�� ����� ������ ����� ���̺귯�� ������ �ʿ� ����.
// DLL ��ü�� ������ ��� ���� �ϴ�. - �� �Լ��� signature�� �̸� �˰� �־�� �Ѵ�.

typedef int(*FUNC)(int, int);

void main()
{
	getch();
	HMODULE hDll = LoadLibrary("XYZ.dll");
	if ( hDll == 0 )
	{
		printf("xyz.dll �� ã������ �����ϴ�.\n");
		return;
	}
	printf("DLL�� Load�� �ּ� : %p\n", hDll );
	//----------------------------------------------
	FUNC f = (FUNC)GetProcAddress( hDll, "Add");c

	if ( f == 0 )
		printf("DLL �ȿ��� �ش� �Լ��� ã������ �����ϴ�.\n");
	else
	{
		printf("Add�Լ� �ּ� : %p\n", f);
		printf("10 + 20 = %d\n", f(10,20));
	}
	FreeLibrary( hDll ); // DLL ����
}

// �ݵ�� �˾ƾ� �ϴ� �Լ� 3�� 
// LoadLibrary()  / FreeLibrary()    / GetProcAddress()



















