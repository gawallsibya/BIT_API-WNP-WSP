// a.c
#define DLL_SOURCE
#include "xyz.h"	// �� �ȿ� �ִ� DLLFUNC�� __declspec(dllexport)�� �ȴ�.

int Add( int a, int b )
{
	return a + b;
}
