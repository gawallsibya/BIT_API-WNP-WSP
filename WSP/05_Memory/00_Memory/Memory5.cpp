// ���� �޸� 

#include <iostream>
using namespace std;

/*
��� exe�� DLL ���� �̹����� ���� �κ��� �������� �����Ǿ� �ִ�.
�̸� Section�̶� ��..

.exe : ���α׷� �����Ͻ� ��� �ڵ��
.bass : �ʱ�ȭ���� ���� �����͵�
.data : �ʱ�ȭ�� ������(��������)
.rdata : �б� ���� data

  => �̷��� �������� �����Ϳ� �ڵ带 �и���Ű��, 
     ���Ǹ����� Ư¡���� ������ �ִ�.

  => �� �ܿ��� ����� ������ ����� �ִ�.=> ������ ��������...
*/

#pragma data_seg("AAA")
int a = 0;					// �ʱ�ȭ �� ������ ( AAA secion )
int b;						// �ʱ�ȭ ���� ���� ������ ( .bss section ) 
#pragma data_seg()

#pragma comment(linker, "/SECTION:AAA,RWS")		
// Section ������ Read, write, shared �Ӽ��� ��..


void main()
{
	a++;
	b++;
	cout << a << endl;
	cout << b << endl;

	int b;
	cin >> b;
}





















