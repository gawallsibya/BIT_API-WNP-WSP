// ȯ�溯��

#include <iostream.h>
#include <windows.h>

void main()
{
	// Process ���� �Լ� 
//	WinExec("calc.exe", SW_SHOW);
//	ShellExecute(0, "open", "calc.exe", 0, 0, SW_SHOW);

	// ���� ���μ����� ���� ���丮 ���
	char buf[256];
	GetCurrentDirectory(256, buf);
	cout << buf << endl;

	//---------------------------------------------

	// ȯ�� �������( ������ �޸� ����)�� �� �ֱ�
	
	SetEnvironmentVariable("mon", "������");
	char temp[256];
	GetEnvironmentVariable("mon", temp, 256);
	cout << temp << endl;
	//-------------------------------------------------------
	cout << __argc  << endl;
	cout << __argv  << endl;
}


