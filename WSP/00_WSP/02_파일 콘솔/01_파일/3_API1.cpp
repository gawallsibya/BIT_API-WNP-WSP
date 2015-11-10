//---------------------------------------------------
//  ���� ���� ���� B
//---------------------------------------------------

#include <windows.h>
#include <stdio.h>


// ���� �޽��� ���
void PrintErrorMsg( DWORD err)
{
	LPTSTR	lpMsgBuf;
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, err, 
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	printf("%s ", lpMsgBuf);
	LocalFree(lpMsgBuf);
}

int main()
{
	
	HANDLE hf = CreateFile("c://test.dat", GENERIC_READ,
		FILE_SHARE_READ,  // ���� �߻� 
//		FILE_SHARE_WRITE, // ���� 
		NULL, OPEN_ALWAYS, 0, NULL);

	if( hf != INVALID_HANDLE_VALUE)
	{
		char	buf[256];
		DWORD	read;
		printf("���� ����\n\n");
		ReadFile(hf, buf, sizeof(buf), &read, NULL);
		buf[read] = '\0';
		printf("%s", buf);
		CloseHandle(hf);
	}
	else
	{
		PrintErrorMsg(GetLastError());
	}
	getchar();

	return 0;
}