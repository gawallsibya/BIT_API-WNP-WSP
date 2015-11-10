// Critical Section
/*
=> Ŀ�� ��ü�� �ƴϴ�... ���� �Ʒ��� ���� Ư¡���� ��Ÿ����.
�� �� : ����ȭ ��ü�� ���� ������.
�� �� : ���� �ٸ� ���μ����� ����ȭ������ ����� �� ����.

=> ����ȭ ���� : �Ӱ迵��..
*/


#include <windows.h>
#include <iostream>
using namespace std;

void WorkFunc()	{	for( int i=0; i <10000000; i++);	}// �ð� ���� �Լ�	
// ���� �ڿ�
int g_x	= 0;
int g_x1 = 0;

//------------------------------------------------
CRITICAL_SECTION	g_cs;	// ����
CRITICAL_SECTION    g_cs1;
//------------------------------------------------

DWORD WINAPI Func( PVOID p)
{
	InterlockedIncrement(&g_x1);	// ++
	InterlockedDecrement(&g_x1);	// --
	//---------------------------------------------------------------
	EnterCriticalSection(&g_cs);

	for( int i=0; i< 20; i++)
	{
		g_x = 200;
		WorkFunc();
		g_x++;
		cout << "             Func : " << g_x << endl;
	}
	LeaveCriticalSection(&g_cs);
	//------------------------------------------------------------------

	return 0;
}
void main()
{
	InterlockedIncrement(&g_x1);


	InitializeCriticalSection(&g_cs);	// �Ӱ迵�� ���� �ʱ�ȭ.
	InitializeCriticalSection(&g_cs1);	// �Ӱ迵�� ���� �ʱ�ȭ.

	DWORD tid;
	HANDLE hThread = CreateThread(NULL, 0, Func, 0, NORMAL_PRIORITY_CLASS, &tid);
	//---------------------------------------------------------------
//	Sleep(1);
	EnterCriticalSection(&g_cs);
	for( int i=0; i< 20; i++)
	{
		g_x = 200;
		WorkFunc();
		g_x--;
		cout << "             Main : " << g_x << endl;
	}
	LeaveCriticalSection(&g_cs);
	//------------------------------------------------------------------
	
	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hThread);

	DeleteCriticalSection(&g_cs);	// �ı�
}



/*
#include <vector>
#include <windows.h>
#include <iostream>
using namespace std;

template<class T> 
class SafeVector : public vector<T> 
{
public:
	CRITICAL_SECTION	cs;
	SafeVector()	{ InitializeCriticalSection(&cs);	}
	~SafeVector()	{ DeleteCriticalSection(&cs);		}

	void push_back( const T n )
	{
		EnterCriticalSection(&cs);
		vector<T>::push_back(n);		// ������ ��� ���
		LeaveCriticalSection(&cs);
	}
	void resize(int x)
	{
		EnterCriticalSection(&cs);
		vector<T>::resize(0);		// ������ ��� ���
		LeaveCriticalSection(&cs);
	}
};


SafeVector<int> buf;
//vector<int> buf;	// �Ϲ����� vector Ŭ���� ���

DWORD WINAPI foo( LPVOID p)
{
	for( int i=0; i<10; i++)
	{
		for( int j=0; j<20000; j++)
		{
			buf.push_back(10);
		}
		buf.resize(0);
	}
	return 0;
}
void main()
{
	HANDLE hThread = CreateThread( 0, 0, foo, 0, 0, 0);
	for( int i=0; i<10; i++)
	{
		for( int j=0; j<20000; j++)
		{
			buf.push_back(10);
		}
		buf.resize(0);
		cout << "main: " << i << endl;
	}
}

*/














