// b.cpp
#include <stdio.h>

// static library ����ϱ�.
#include "ABC.h"				// 1. ��� include
#pragma comment(lib, "ABC.lib")	// 2. library �߰�

void main()
{
	int s = Add( 10, 20 );
	
	printf("��� : %d\n", s );
}

// ABC.h�� ABC.lib(Debug �Ʒ��ֽ��ϴ�.)�� ���� �۾� ������ ������ ������

// ������ �ϰ� ������ ������..

