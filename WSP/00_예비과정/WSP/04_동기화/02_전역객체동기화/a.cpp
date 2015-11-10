
/*
#include <iostream>
#include <windows.h>
#include <list>
using namespace std;

// stl �� list ���� �Ļ��� Ŭ������ �����.
// Thread - Safe Ŭ���� : �̱� �����峪 ��Ƽ ������ ȯ�濡�� �ƹ� ���� ���� 
//                        ����Ҽ� �ִ�.(�� �ڽ��� �����θ� ����ȭ �ϰ� �ִ�)
template<typename T> class Safe_List : public list<T>
{
	CRITICAL_SECTION m_cs;
public:
	Safe_List() { InitializeCriticalSection(&m_cs); }
	~Safe_List() { DeleteCriticalSection(&m_cs); }

	// �θ� �Լ� override
	void push_back( const T& x )
	{
		EnterCriticalSection( &m_cs );
		list<T>::push_back( x ); // �θ��� ���� ��� ���
		LeaveCriticalSection( &m_cs );
	}  
};

Safe_List<int> st; // ���� ��ü( ��� ����� static �� �����Ƿ� ��� �����忡 ����
			  // �����ȴ�. ���ٽ� ����ȭ�� �ʿ��Ѵ�.


// Serialization : ���ÿ� �������̴� �����尡 � ������ ���ķ� ���ʷ� 
//					��� �ϰ� �Ǵ� ���� ���´� ���

//				���� : MFC������ �ٸ� �뵵�� �� �� ����ϱ⵵�Ѵ�.



#define COUNT 500





DWORD WINAPI foo( void* p)
{
	for ( int i = 1; i < 10; ++i )
	{
		for ( int j = 1; j < COUNT; ++j )
			st.push_back( 10 );			// linked list ����

		printf("foo : %d\n", i );
	}
	return 0;
}
DWORD WINAPI goo( void* p)
{
	for ( int i = 1; i < 10; ++i )
	{
		for ( int j = 1; j < COUNT; ++j )
			st.push_back( 10 );			// linked list ����

		printf("\tgoo : %d\n", i );
	}
	return 0;
}
void main()
{
	HANDLE h[2];
	h[0] = CreateThread( 0, 0, foo, 0, 0, 0);
	h[1] = CreateThread( 0, 0, goo, 0, 0, 0);

	WaitForMultipleObjects( 2, h, TRUE, INFINITE );
	CloseHandle( h[0]);
	CloseHandle( h[1]);
}
								// foo�� �����ؼ� goo�� ���弼��

*/

#include <iostream>
#include <windows.h>
#include <list>
using namespace std;

list<int> st; // ���� ��ü( ��� ����� static �� �����Ƿ� ��� �����忡 ����
			  // �����ȴ�. ���ٽ� ����ȭ�� �ʿ��Ѵ�.
#define COUNT 500

// list �� ����ȭ�ϱ� ���� Critical Section
CRITICAL_SECTION cs;
CRITICAL_SECTION cs2; // printf�� ����ȭ �ϱ� ���� 

DWORD WINAPI foo( void* p)
{
	for ( int i = 1; i < 10; ++i )
	{
		for ( int j = 1; j < COUNT; ++j )
		{
			EnterCriticalSection( &cs );
			st.push_back( 10 );			// linked list ����
			LeaveCriticalSection( &cs );
		}
		EnterCriticalSection( &cs2);
		printf("foo : %d\n", i );
		LeaveCriticalSection( &cs2);
	}
	return 0;
}
DWORD WINAPI goo( void* p)
{
	for ( int i = 1; i < 10; ++i )
	{
		for ( int j = 1; j < COUNT; ++j )
		{
			EnterCriticalSection( &cs );
			st.push_back( 10 );			// linked list ����
			LeaveCriticalSection( &cs );
		}
		EnterCriticalSection(&cs2);
		printf("\tgoo : %d\n", i );
		LeaveCriticalSection(&cs2);
	}
	return 0;
}
void main()
{
	for ( int i = 0;  i < 10000; ++i )
	{
		InitializeCriticalSection( &cs );
		InitializeCriticalSection( &cs2 );

		HANDLE h[2];
		h[0] = CreateThread( 0, 0, foo, 0, 0, 0);
		h[1] = CreateThread( 0, 0, goo, 0, 0, 0);

		WaitForMultipleObjects( 2, h, TRUE, INFINITE );
		CloseHandle( h[0]);
		CloseHandle( h[1]);

		DeleteCriticalSection( &cs );
		DeleteCriticalSection( &cs2 );

		printf("============================================== %d\n", i );
	}
}
								














