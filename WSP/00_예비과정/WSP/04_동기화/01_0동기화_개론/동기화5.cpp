//  Event

#include <iostream>
#include <windows.h>
using namespace std;

void main()
{
	HANDLE	hEvent = CreateEvent(NULL,		//  ���ȼӼ�
								TRUE,		// ��������(TRUE), �ڵ�����(FALSE)
								FALSE,		// �ʱ� ����( NON SIGNAL )
								"e");		// ������ �̺�Ʈ �̸�

	/*
	AUTO RESET : WaitForSingleObjecct�� ����ϴ� ���� 
				 Signal => NonSignal�� ������� ��.
	
	MANUAL RESET : WaitForSingleObject�� ��ȭ�ϴ��� 
					Signal ���¸� ��� ������..
					=> ��ٸ��� ��������� �� �����ִ� ����..
	*/
	cout << "Event�� ��ٸ���." <<endl;
	WaitForSingleObject(hEvent, INFINITE);
	cout << "Event ȹ�� " << endl;

	cout << "Event�� ��ٸ���." << endl;
	WaitForSingleObject(hEvent, INFINITE);
	cout << "Event ȹ��" << endl;

	CloseHandle(hEvent);
}











