// a.c
#include <windows.h>
#include <stdio.h>

char* buf = 0;
BOOL WINAPI DllMain( HANDLE hDll,	// DLL �ڵ�(Load �� �ּ�)
					 DWORD  r,		// DllMain�� ȣ��� ����(4���� �� 1��)
					 LPVOID how)	// DLL�� Load�� ���(������Ǵ� �Ͻ���)
{
	switch( r )
	{
	case DLL_PROCESS_ATTACH:  
		printf("DLL�� ���μ����� Load�˴ϴ�. �ּҴ� : %p\n", hDll);
		printf("Load����� %s\n", how == 0 ? "�����":"�Ͻ���");
		buf = (char*)malloc( 1000 );
		break;

	case DLL_PROCESS_DETACH: free(buf); printf("DLL�� ���μ������� ���� �˴ϴ�.\n");break;
	case DLL_THREAD_ATTACH: printf("���ο� �����尡 �����˴ϴ�.\n");	break;
	case DLL_THREAD_DETACH: printf("�����尡 �Ҹ�˴ϴ�.\n");break;
	}
	return TRUE; // FALSE�� �����ϸ� DLL�� Load���� �ʴ´�.
}

// ���� ��� DLL ���� �Լ����� buf�� ����ص� �ȴ�.!!!








