#include <stdio.h>
#include <windows.h>
#include <errno.h>
#include <conio.h>


void main()
{
	HWND hwnd = CreateWindow( 0, 0, 0, 0, 0, 0, 0 ,0, 0, 0, 0);

	if ( hwnd == 0 ) // ����
	{

		// thread �� 1���� �����ϴ� ���� �ڵ带 ��´�.
		DWORD e = GetLastError(); 

		printf("Fail : %d\n", e );

		// ���� ��ȣ -> ���ڿ� ��ȯ
		char* s; 

		// �����͸� �����ϰ� �ʿ��� ��ŭ API �Լ��� �Ҵ��ϰ� �ϴ� ���.
		// �� ������� ��� ��� �̹Ƿ� �˾Ƶ� �ʿ� ����
		FormatMessage( FORMAT_MESSAGE_FROM_SYSTEM | 
					   FORMAT_MESSAGE_ALLOCATE_BUFFER,
						0,  // ���ڿ��� ���� DLL�ڵ�(0 : �ý������� ���;�´�)
						e,	// ���� ��ȣ
						0,  // ���
						(char*)&s, 0, // ����, ����ũ��
						0); // va_list �� ������ ������ ���

		printf("%s\n", s);

		// FormateMessage() �� ���������� LocalAlloc()�̶�� �Լ��� ����ؼ�
		// �޸𸮸� �Ҵ��Ѵ�. ������ ����� å��
		LocalFree( s );
	}
}








