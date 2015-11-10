#include <iostream.h>
#include <windows.h>

/*
void CALLBACK foo( DWORD error,
				   DWORD byte,
				   OVERLAPPED* p)
{
	cout << "�񵿱� �۾��� �Ϸ� �Ǿ����ϴ�." << endl;
	cout << "�� �۾��� byte : " << byte << endl;
}
*/
	// OVERLAPPED ����ü Ȯ�� - C++�϶�
/*
	struct OVERLAPPED_PLUS : public OVERLAPPED
	{
		int jobID;
		int clientID;
	};
*/	
	struct OVERLAPPED_PLUS
	{
		OVERLAPPED ov;
		int jobID;
	};


DWORD WINAPI foo(void* p)
{
	HANDLE hPort = (HANDLE)p;

	DWORD byte;
	DWORD err;
	OVERLAPPED* pov;
	DWORD key;

	while ( GetQueuedCompletionStatus( hPort, &byte, &key, &pov, INFINITE) )
	{
		cout << "�񵿱� �۾��� �Ϸ� �Ǿ����ϴ�." << endl;
		cout << "Byte : " << byte << endl;
		cout << "�Ϸ�Ű : " << key << endl;
		OVERLAPPED_PLUS* p = (OVERLAPPED_PLUS*)pov;
		cout << "JobID : " << p->jobID << endl;
	}
	return 0;
}







void main()
{
	HANDLE hFile = CreateFile( "COM1", // Serial port
							   GENERIC_WRITE,
							   FILE_SHARE_READ | FILE_SHARE_WRITE,
							   0, // ����
							   OPEN_EXISTING, //
							   FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, 
							   0);

	// Baud rate setting...

	if ( hFile == INVALID_HANDLE_VALUE ) // -1
	{
		cout << "COM1 �� ������ �����ϴ�" << endl;
		return;
	}
	//-------------------------------------------------------------
	// IOCP�� �����Ѵ�.
	HANDLE hPort = CreateIoCompletionPort( INVALID_HANDLE_VALUE,// ��ġ �ڵ�.
										   0, // �̹� ������� port#
										   0,
										   2); // ���ÿ� �۾��Ҽ� �ִ� �������� ��.

	// �ϼ��� IOCP�� �񵿱� �۾����� ��ġ�� �����Ѵ�.
	CreateIoCompletionPort( hFile, hPort, 1, // �Ϸ� Ű..
							0);

	// �����带 �����ؼ� �񵿱� �۾��� ����Ѵ�.
	CreateThread( 0, 0, foo, (void*)hPort, 0, 0);
	CreateThread( 0, 0, foo, (void*)hPort, 0, 0);

	//-----------------------------------------------------------------
	//------------------------------------------------
	const int size = 2048; // 2k
	char buf[size];

	DWORD len;
	//---------------------------------
	// �񵿱� IO ��û�ϱ�.
	/*
	OVERLAPPED ov = { 0};
	ov.hEvent = CreateEvent( 0, 0, 0, "e");
	ov.Internal		= 0;
	ov.InternalHigh = 0; // os �� ��� ����ڴ� ������� �ʴ´�.
	ov.Offset		= 0; // ȭ���۾��� �����ϰ� ���� ȭ���� offset
	ov.OffsetHigh	= 0;
	*/
	OVERLAPPED_PLUS ov = { 0 };
	ov.jobID = 1;

	BOOL b = WriteFile( hFile, buf, size, &len, (OVERLAPPED*)&ov);



	int n;
	cin >> n;

//	BOOL b = WriteFileEx( hFile, buf, size, &ov, foo);

	// �ٸ��۾��� �ϰ�... ����������.
	// SleepEx()Ȥ�� WaitForSingleObjectEx()�� ����ؾ� �Ѵ�.
	
//	SleepEx( 3 0000, TRUE ); // ����ϴ� �񵿱��۾� �����.. foo��..


	//----------------------------------------------

	if ( b == TRUE )
	{
		cout << "���������� ���⸦ �Ϸ� �߽��ϴ�." << endl;
	}
	else if ( b == FALSE && GetLastError() == ERROR_IO_PENDING)
	{
		cout << "�񵿱�� �۾����Դϴ�." << endl;

	//	WaitForSingleObject( ov.hEvent , INFINITE);

		cout << "�񵿱� �۾� �Ϸ�" << endl;
	}
	else
		cout <<"COM1�� ������ �����ϴ�" << endl;




	CloseHandle( hFile );
}











