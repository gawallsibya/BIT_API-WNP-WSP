// ABC.h
// ABC.lib�� �ִ� ��� �Լ��� ����θ� �����Ѵ�.
// ��� C++ �����Ϸ��� __cplusplus ��� ��ũ�θ� ���� �ϰ� �ִ�.(��� ǥ��)

/*
#ifdef __cplusplus
	#define EXTERN_C extern "C"
#else
	#define EXTERN_C 
#endif
*/

#include <windows.h>   // EXTERN_C �� ���������� ���� �Ǿ� �ִ�.

EXTERN_C int Add( int , int );

// �� ó�� ����� ����� C, C++ ��ο��� ����Ҽ� �ִ�.
// ��Ģ.
// 1. ���̺귯�� ��ü�� ���鶧�� .c �� ����ؼ� mangling�� ���´�.
// 2. ����� ���鶧�� ��ũ�θ� ��� C/C++ ��ο��� ����Ҽ� �ְ� �Ѵ�.







