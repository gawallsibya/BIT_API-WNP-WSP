#include <windows.h>
#include <stdio.h>

void main()
{
	// ǥ�� C�Լ� ��� 
//	system("freecell.exe");

	//API�Լ�..
	WinExec("freecell.exe", SW_SHOW); // non blocking,

	printf("Bye~~\n");
}
