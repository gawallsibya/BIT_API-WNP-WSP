#include <stdio.h>
#include <windows.h>
#include <errno.h>
#include <conio.h>

// �������� C �� ���� ó�� ��� - 
// ���� ���μ����� 1���� ���� �ڵ�.
void main()
{
	FILE* f = fopen("a.txt", "rt");

	if ( f == 0 )
	{
		printf("���� \n");

		// 1. errno : C �� �̸� ������ ���� ����.
		printf("errno : %d\n", errno ); 

		// 2. errno-> ���ڿ���!
		char* s = strerror( errno ); 
		printf("%s\n", s );

		// 1.2���� fprintf(stderror, "Fail : %s\n", strerror(errno));
		perror("Fail"); 
	}
}
