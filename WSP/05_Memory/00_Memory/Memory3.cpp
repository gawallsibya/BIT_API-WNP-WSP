// virtual Memory

#include <windows.h>
#include <iostream>
using namespace std;


void main()
{
	char *p = (char*)VirtualAlloc( NULL,			// ���ϴ� �ּ�(64K ���)
								1024*1024*50,		// ũ�� (50MB)
								MEM_RESERVE,		// ����
								PAGE_READWRITE);	// ��ȣ �Ӽ�

	cout << (void*)p << endl;

	char *p1 = (char*)VirtualAlloc(p,				// ���ϴ� �ּ�
									1024*1024*10,	// ũ��(10MB)
									MEM_COMMIT,		// Ȯ��
									PAGE_READWRITE);// ��ȣ�Ӽ�
	cout << (void*)p1 << endl;
	//-------------------------------------------------------

	char *temp = p;
	for( int i=0; i<10; i++)
	{
		int n; cin >> n;
		char *t = (char*)VirtualAlloc(temp, 1024*1024*10, MEM_COMMIT,
								PAGE_READWRITE);

		cout << "Ȯ���� �ּ� : " << (void*)t << endl;
		temp += 1024 * 1024 * 10;
	}
	// commit ==> decommit
	VirtualFree( p, 1024*1024* 10, MEM_DECOMMIT);

	// free
	VirtualFree( p, 0, MEM_FREE);


}















