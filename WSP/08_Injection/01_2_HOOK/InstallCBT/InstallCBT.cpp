#include <windows.h>
#include <iostream>
using namespace std;

typedef void(*F)(DWORD tid);

void main()
{
	HMODULE hDll = LoadLibrary( "HK2.dll" );

	F Install = (F)GetProcAddress(hDll, "Install");

	if(Install == 0)
		cout << "Error" << endl;
	else
		Install(0);

	int n;
	cin >> n;

	// �ڿ� ����.. ����...!! - ���μ����� ������ �ڵ����� ������ �ȴ�. 
	// ������ ������ �� �ϴ� ������ ���̵���...
}

