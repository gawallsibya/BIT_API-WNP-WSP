	#include <iostream.h>
	#include <windows.h>

	void main()
	{
		HANDLE hPipe = CreateFile( "\\\\.\\pipe\\TimeServer", // UNC
									GENERIC_READ,
									FILE_SHARE_WRITE,
									0,
									OPEN_EXISTING,
									FILE_ATTRIBUTE_NORMAL, 
									0);

		if ( hPipe == INVALID_HANDLE_VALUE )
		{
			cout << "Pipe ������ �����Ҽ� �����ϴ�" << endl;
			return;
		}

		DWORD len;
		SYSTEMTIME st;

		ReadFile( hPipe, &st, sizeof(st), &len, 0);



		// UTC �ð��� ->���� �ð�����
		::SystemTimeToTzSpecificLocalTime( 0, &st, &st );

		SetLocalTime( &st );

		//cout << st.wHour << "��" << st.wMinute << "��" << endl;

		char date[256];
		char time[256];
		GetDateFormat( LOCALE_USER_DEFAULT, 0, &st,  0, date, 256);
		GetTimeFormat( LOCALE_USER_DEFAULT, 0, &st,  0, time, 256);

		cout << date << endl;
		cout << time << endl;

		CloseHandle( hPipe );
	}
	// TimeServer�� �����ϼ���... �׸��� TimeClient����.



