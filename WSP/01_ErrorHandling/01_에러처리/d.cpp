#include <stdio.h>
#include <windows.h>
#include <errno.h>
#include <conio.h>

// �Լ� ȣ���� ���������� ������ ������ �˱� ���ؼ� 
// GetLastError()�� ȣ���� ���� �ִ�.
//  - �׻�׷����� �ƴϴ�.
// ���ÿ� ������ 2���� ���μ����� �����Ǵ� ���� ���� ���.
void main()
{
	HANDLE hEvent = CreateEvent( 0, 0, 0,"e");
//	HANDLE hEvent = CreateEvent(0, 0, 0, "{0826602B-E8C6-4fd8-A497-6F514576AD48}");
	
	if ( hEvent != 0 ) // ����..!!
	{
		DWORD e = GetLastError(); // �� �����ߴ��� ������ �˰� �ʹ�.

		if ( e == ERROR_ALREADY_EXISTS )
		{
			printf("�̹� �����ϴ� event ��ü�� Open �߽��ϴ�.\n");
			printf("�̹� ���� ���α׷��� �������Դϴ�..\n");
			return;
		}
		else
		{
			printf("event ��ü�� ���Ӱ� �����߽��ϴ�.\n");
		}
	}
	getch(); // #include <conio.h> �߰��� �ּ���.
}




























