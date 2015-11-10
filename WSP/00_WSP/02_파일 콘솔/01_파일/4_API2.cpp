//---------------------------------------------------
//  SetFilePointer ���

//  ��κ��� �ü�������� ���� ���ϸ��� �б�/���⸦ ����
//  ���� ��ġ ������ �����Ѵ�.
//  Windows������ �̸� ���� �����Ͷ�� �Ѵ�.
//  �� ������ �б�/���⸦ �� ��� �������� ���� ���ηκ����� 
//  �������̴�.
//  ���� �� ���� ������ ���� �����ʹ� ������ ���ο� ��ġ�Ѵ�.

//  �׸��� ReadFile�̳� WriteFile�� ȣ���ϸ� ������ �а� ��
//  ��ŭ ���� �����Ͱ� ������ �������� �̵��Ѵ�.
//  ReadFile�� ��� ȣ���ؼ� ���������� ���� �� �ִ� ������ 
//  �� �����̴�.

//  ���� �����ʹ� �����Ͱ� �ִ� ������� SetFilePointer API
//  �� ����ؼ� �����Ӱ� �̵��� �� �ְ�, �̸� Ž��(SEEK)�� �Ѵ�.

//  ������ Ư�� ��ġ���� �а� ������ �� ��ġ�� ���� �����͸� 
//  �ű�� ���� ReadFile / WriteFile �� ȣ���ϸ� �ȴ�.

//  DWORD SetFilePointer(		��ȯ�� : �̵��� ������������ ���� 
//										 32bit��ġ
//   HANDLE hFile,				 ���� �ڵ�
//   LONG lDistanceToMove,		 �̵��� ��� �Ÿ��� ���� 32bit
//   PLOING lpDistanceToMoveHigh, �̵��� ��� �Ÿ��� ���� 32bit�� 
//								  ���� ������ �ּ�, �̵����� ���� 
//								  32bit�� ��ȯ��
//   DWORD dwMoveMethod			  �̵� ���� ��ġ 
//---------------------------------------------------

#include <windows.h>
#include <stdio.h>
  
int main()
{
	// �б� ���� ���� ����
	HANDLE hf = CreateFile("test.dat",
		GENERIC_WRITE | GENERIC_READ,
		0, NULL, CREATE_ALWAYS, 0, NULL);
	if(hf != INVALID_HANDLE_VALUE)
	{
		char *data = "�׽�Ʈ ��\r\n";
		char buf[256];
		DWORD written, read;

		// ������ ���
		WriteFile(hf, data, strlen(data), &written, NULL);

		// ���� ������ �̵�
		SetFilePointer(hf, 0, NULL, FILE_BEGIN);

		// ������ �κи� �б�
		ReadFile(hf, buf, sizeof(buf), &read, NULL);

		buf[read] = '?';

		// ���� ������ ���
		printf("%s", buf);

		CloseHandle(hf);
		//������ �߿� 
		// CloseHandle() : ���ϰ� TRUE �� �ݵ�� Ȯ������ .
	}
	return 0;
}
