


// �����Ϸ����� ���� ���ߴٸ� ���� 
#ifndef _MT
#define _MT	// MSDN�̳� �ٸ� �ҽ������� �ݵ�� �����϶�� �Ǿ� �ִ� �ɺ�...
			// �ᱹ _MT�ɺ��� �����Ϸ� �ɼǿ��� /MT �� �����ϴ� �Ͱ� ������ ȿ�� ..
#endif

#include <iostream>
#include <process.h>  // _beginthreadex() �� ����ϱ� ����..
#include <windows.h>
using namespace std;

unsigned int __stdcall foo(void *p)  // �ᱹ DWORD WINAPI foo() �̴� ~!!
{
	cout << "foo" << endl;
	Sleep(1000);
	cout << "foo finish" << endl;
	return 0;
}

void main()
{	
	unsigned long h = _beginthreadex(0, 0, foo, 0, 0, 0);

	// h�� �ᱹ �ڵ��̴�.
	WaitForSingleObject((HANDLE)h, INFINITE);

	CloseHandle((HANDLE)h);
}
//---------------------------------------------------------------------------------------
/*
	VC++����  C ��Ƽ������ ���̺귯�� ������ ����Ϸ��� 
	1. Project -> Setting ���� C/C++ tab�� Code Generation �׸񿡼� 
	   multi - thread �������� ����..


	2 . �����Ϸ� option �� /MT�� �߰� �ϴ���
	    #define _MT �� �ҽ��� �߰� ..

		VC++�� ����ϸ� �ڵ����� /MT �߰� �ȴ�.
		������ Dos â���� Cl.exe �� ���� ������ �Ҷ��� ���� ������ option�� �ִ��� 
		�ҽ���  #define _MT �� �߰��Ѵ�. 

	3. Process.h ��� �ʿ� ..

*/
//--------------------------------------------------------------------------------------