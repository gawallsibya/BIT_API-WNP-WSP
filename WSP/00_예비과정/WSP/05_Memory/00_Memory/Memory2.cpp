// Memory 


#include <windows.h>
#include <iostream>
using namespace std;

/*
void main()
{
	// �޸� �Ҵ� ���� �Լ�(������) ; malloc, new, heapAlloc, VirtualAlloc
	// GlobalAlloc, LocalAlloc : win16 �Լ� 

	BYTE *p  = (BYTE*)malloc(10);
	BYTE *p1 = new	BYTE[10];

	// ���ӵ� �޸� ������ ����... ( defult heap)
	cout << (void*)p  << endl;
	cout << (void*)p1 << endl;

	delete p;
	free(p1);
}
*/

/*
default Heap =>  ���� ���� 
Heap ??		 =>  
*/

/*
void main()
{
	// default Heap�� �ڵ��� ��� �Լ�.
	HANDLE	hHeap1	= GetProcessHeap();

	// ���ο� �� ����
	HANDLE	hHeap2	= HeapCreate( 0, // flag
								1024*1024, // �ʱ� ũ�� (1M - Ȯ��)
								1024*1024*10);	// �ִ� ũ��(����)

	char* p	= (char*)HeapAlloc(hHeap1, // �ڵ�
								0,     // flag
								100);  // ũ�� ( byte ���� )

	char *p1 = (char*)HeapAlloc(hHeap1, 0, 100);
	char *p2 = (char*)HeapAlloc(hHeap1, 0, 400);

	// �޸� �ʱ�ȭ ..... => Ȯ�� 0
	char *t  = (char*)HeapAlloc(hHeap2, HEAP_ZERO_MEMORY, 1024*1024);
//	char *t1 = (char*)HeapAlloc(hHeap2, HEAP_ZERO_MEMORY, 1024*1024);

	// �ּ� ���
	cout << (void*)p << endl;
	cout << (void*)p1 << endl;
	cout << (void*)p2 << endl;
	cout << (void*)t  << endl;

	// Ȯ���� �޸� ������ byte ����..
	DWORD lp = HeapSize(hHeap1, 0, p1);
	cout << "l " << lp << endl;
}
*/

class Node
{
public:
	static HANDLE	s_hHeap;
	static int		count;

	void *operator new(size_t s)		// new ������
	{
		if( s_hHeap == 0 )
		{
			s_hHeap = HeapCreate(0, 0, 0);
			if( s_hHeap == NULL)
				return NULL;
		}
		void *p = HeapAlloc( s_hHeap, 0, s);
		count++;
		return p;
	}
	void operator delete(void *p)		// delete ������
	{
		HeapFree( s_hHeap, 0, p);
		if( --count ==  0 )
			HeapDestroy(s_hHeap);
	}
};
HANDLE	Node::s_hHeap	= 0;
int		Node::count		= 0;

void main()
{
	Node *p1 = new Node;		Node *p2	= new Node;
	cout << p1 << endl;			cout << p2 << endl;
	delete p1;					delete p2;

}






















