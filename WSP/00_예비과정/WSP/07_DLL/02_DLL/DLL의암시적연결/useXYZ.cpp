#include <windows.h> // user32.dll�� ��� �Լ� ����.

#include <stdio.h>

// DLL ����ϱ�
//#include "xyz.h"					// ���� ��� include
//#pragma comment(lib, "xyz.lib")		// ���̺귯�� �߰�
void main()
{
	MessageBox(0,"A","",MB_OK);

//	int s = Add(10,20);			// DLL �Լ� ���
//	printf("��� : %d\n", s);

	void* p1 = GetModuleHandle( "xyz.dll");
	printf("xyz.dll �ּ� : %p\n", p1);
//	printf("Add �ּ� : %p\n",    Add);
}
// xyz.h �� xyz.lib �� ���� �� ������. ���� xyz.dll�� ���� ���� ������

// ������/link �Ͻø� ���� ����(exe)�� �����˴ϴ�.

// ������ ������ -> DLL�� ã���� ���ٴ� ������ ���ɴϴ�. Ȯ���� ������

// ���� xyz.dll�� �����ؿ�����. �ٽ� ������ ������..






