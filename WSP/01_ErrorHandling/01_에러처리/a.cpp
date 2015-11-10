// ErrorHandling
// �Լ� ȣ�� �� ���ϰ� Ȯ�� �۾�
// ������ ���� �� ���� Ȯ�� �۾� 

#include <windows.h>
#include <iostream>
using namespace std;

// ������� ���� �ڵ� ����
#define ERROR_MYERROR 100 

// ����� ���� �Լ� �ۼ���
BOOL foo()
{
	SetLastError(ERROR_MYERROR);
	return FALSE;
}

void main()
{

	// 1. �Լ� ȣ���� ���� Ȯ��
/*
	HWND hwnd = CreateWindow(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	if( hwnd ==  0 )
	{
		DWORD err = GetLastError();
		cout << "error : " << err << endl;

		char msg[256];
		FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, 0, 
			err, 0, msg, 256, 0);

		cout << msg << endl;
	}
*/
	// 1. GetLastError() -> FormatMessage
	// 2. ErrorLookup �� ���
	// 3. Debuging ��� => @err,hr ( watch â)

	// CreateWindow()	���н� 0�� ����.
	// CreateProcess()  ���н� -1�� ����
	// CreateFile()     ���н� INVALID_HANDLE_VALUE(-1)�� ����
	// ������ ��� HANDLE�� ����..


	// 2. ������ ���� ó�� ��ȣ ���� 
	if( foo() == FALSE)
	{
		DWORD e = GetLastError();
		cout << "����� ���� ���� :" << e << endl;
	}
	

}










