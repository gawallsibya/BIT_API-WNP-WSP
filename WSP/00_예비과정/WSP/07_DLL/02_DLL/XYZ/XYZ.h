// xyz.h

// �� ��� �Ѱ��� DLL�� ���鶧�� DLL�� ����Ҷ� ��� ����ϱ� ���� ���Ǻ�
// ������ ���

#ifdef DLL_SOURCE
	#define DLLFUNC	__declspec(dllexport)   
#else
	#define DLLFUNC __declspec(dllimport)
#endif

#include <windows.h>

EXTERN_C DLLFUNC int Add( int a, int b);

//--------------------------------------------------------