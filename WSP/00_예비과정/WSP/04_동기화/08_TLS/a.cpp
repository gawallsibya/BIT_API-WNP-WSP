#include <windows.h>
#include <stdio.h>
// goo �� static ���� ������ ����ؼ� ���ϴ� ����� �����Ͽ���.
// �̱۽����� ȯ�濡���� �ƹ� ���� ����.   ��Ƽ ������ ���. ?
void goo( char*  name)
{
	// TLS ������ ������ �����Ѵ�.
	__declspec(thread) static int c = 0;

//	static int c = 0;
	++c;
	printf("%s : %d\n", name, c ); // �Լ��� ��� ȣ��Ǿ����� �˰� �ʹ�.
}
DWORD WINAPI foo( void* p )
{
	char* name = (char*)p;
	goo( name );
	goo( name );
	goo( name );
	return 0;
}
void main()
{
	HANDLE h1 = CreateThread( 0, 0, foo, "A", 0, 0);
	HANDLE h2 = CreateThread( 0, 0, foo, "\tB", 0, 0);

	HANDLE h[2] = { h1, h2};
	WaitForMultipleObjects( 2, h, TRUE, INFINITE );

	CloseHandle( h1 );
	CloseHandle( h2 );
}

// � �Լ��� ���������� ���� ������ ����Ѵ� -> 
//��Ƽ �����忡 �����Ѱ� ? OK

// � �Լ��� ���������� static ������ ����Ѵ�. -> 
// �̱۽������ ���� ����.
//  -> ��Ƽ ������� �����Ѱ� ?




