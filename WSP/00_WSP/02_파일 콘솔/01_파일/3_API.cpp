//---------------------------------------------------
//  ���� ���� ���� A
//  - Win32 API�� ����Ͽ� �������۽� ��� ���� �� �ϳ�
//    
//  - ��Ÿ�� ���� : �ڽ��� �������� ���Ͽ� ���� �ٸ� ���α׷�
//    �� ������ �㰡���� ������ �����ϴ� �� 

//  - CreateFile�� ����° ���ڸ� Ȱ���� 
//    0 : �ݱ� ������ �� ������ �ٸ� ���α׷����� ��� �Ұ� 
//    FILE_SHARE_READ : �ٸ� ���α׷����� �б� ���
//    FILE_SHARE_WRITE : �ٸ� ���α׷����� ���� ���
//    OR �����ڷ� ���� ���� 

//  Sample Ȯ��)
//   - ��Ÿ�� ���� ���� 
//  - �б� ��� : ���� ��� �б� ��� ó�� �ʿ� 
//---------------------------------------------------

#include <windows.h>
#include <stdio.h>

int main()
{
	
	HANDLE hf = CreateFile("c://test.dat", GENERIC_WRITE,
//		0, 
		FILE_SHARE_READ, 
		NULL, OPEN_ALWAYS, 0, NULL);

	if( hf != INVALID_HANDLE_VALUE)
	{
		// C���̺귯���� �޸� API���� ����� ������ ����.
		// ���� ���� ó���� \r\n���� �Ѵ�.
		char *data = "�׽�Ʈ ��\r\n";
		DWORD written;
		WriteFile(hf, data, strlen(data), &written, NULL);
		printf("Enter Ű�� ����\n");
		getchar();
		CloseHandle(hf);
	}

	return 0;
}