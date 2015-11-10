#include <iostream>
#include <list>  //STL�� linked list
#include <windows.h>
using namespace std;


// list<int> st;  //���� list, �ᱹ st�� ��� ����� static�� �ִ�. ����ȭ �ʿ�

// Linked List Ŭ���� ��ü�� �����忡 �����ϰ� �����Ѵ�..

//Thread - Safe Ŭ����...

template<typename T> class SafeList
{
	list<T>s;
	CRITICAL_SECTION cs;
public :
	SafeList()  {  InitializeCriticalSection(&cs);	}
	~SafeList() {  DeleteCriticalSection(&cs);}

	void push_back(T a)
	{
		EnterCriticalSection(&cs);
		s.push_back(a);
		LeaveCriticalSection(&cs);
	}
};

// cout �� ��ü
// ostream cout

SafeList<int> st;  // �����忡 ������ Linked list ....

#define COUNT 10

DWORD WINAPI foo(void *p)
{
	for(int i=0; i<10; i++)
	{
		for(int j=0; j<COUNT; j++)
			st.push_back(1);

	//	cout << "foo : " << i << endl;
	}

	return 0;
}

DWORD WINAPI goo(void *p)
{
	for(int i=0; i<10; i++)
	{
		for(int j=0; j<COUNT; j++)
			st.push_back(1);

	//	cout << "goo : " << i << endl;
	}

	return 0;
}

void main()
{
	HANDLE h[2];
	h[0] = CreateThread(0, 0, foo, 0, 0, 0);
	h[1] = CreateThread(0, 0, goo, 0, 0, 0);

	WaitForMultipleObjects(2, h, TRUE, INFINITE);

	CloseHandle(h[0]);
	CloseHandle(h[1]);
}



/*
list<int> st;  //���� list, �ᱹ st�� ��� ����� static�� �ִ�. ����ȭ �ʿ�

#define COUNT 10000
CRITICAL_SECTION cs;

DWORD WINAPI foo(void *p)
{
	for(int i=0; i<10; i++)
	{
		for(int j=0; j<COUNT; j++){
			EnterCriticalSection(&cs);
			st.push_back(1);
			LeaveCriticalSection(&cs);
		}	
	}

	return 0;
}

DWORD WINAPI goo(void *p)
{
	for(int i=0; i<10; i++)
	{
		for(int j=0; j<COUNT; j++){
			EnterCriticalSection(&cs);
			st.push_back(1);
			LeaveCriticalSection(&cs);
		}	
	}

	return 0;
}

void main()
{
	InitializeCriticalSection(&cs);
	HANDLE h[2];
	h[0] = CreateThread(0, 0, foo, 0, 0, 0);
	h[1] = CreateThread(0, 0, goo, 0, 0, 0);

	WaitForMultipleObjects(2, h, TRUE, INFINITE);

	CloseHandle(h[0]);
	CloseHandle(h[1]);

	DeleteCriticalSection(&cs);
}

*/

// �״� ������ st.push_back()�� �ƴ϶�.. cout << " ... "  �����̴�...
// cout ��ü�� ����ȭ �ȵǼ� ������ ���� �Դϴ�...
// cout �κ��� �ּ����� ��������

// cout �� ostream Ŭ������ ���� ��ü �̴�, 2�� �̻��� �����忡�� cout
// �� ����Ϸ��� �ݵ�� ����ȭ�� �ʿ�...