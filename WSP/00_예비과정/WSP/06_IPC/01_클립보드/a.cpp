#include <windows.h>
#include <stdio.h>

void main()
{
	char buf[4096] = { 0 };

	if ( OpenClipboard( 0 ) )
	{
		// Ŭ�� ���忡 �ִ� �޸� �ڵ��� ��� �´�.
		HANDLE hData = GetClipboardData( CF_TEXT );

		char* p = (char*)GlobalLock( hData );
	
		strcpy( buf, p ); // �ڽ��� ���ۿ� �Ű� ��´�.
		
		GlobalUnlock( hData );
		
		CloseClipboard( );
	}

	printf("%s\n", buf );
}













/*
void main()
{
	char buf[256] = { 0 };

	while ( 1 )
	{
		printf("Ŭ�� ����� ������ �޼����� �Է��ϼ��� >> ");
		gets( buf );

		//==============================================
		// Ŭ�� ����� ������ �̵������� �޸𸮸� �Ҵ�
		HANDLE hData = GlobalAlloc( GMEM_MOVEABLE, 256 );

		// �ڵ� ����� �̵� ���� �޸𸮸� �����ͷ� �����Ѵ�.
		char* pData = (char*)GlobalLock( hData );
		strcpy( pData, buf );
		GlobalUnlock( hData);
		//=======================================
		// Ŭ�� ���带 Open�ϰ� �޸𸮸� �����Ѵ�.
		if ( OpenClipboard( 0 ) )   // ���ڴ� Ŭ�����带 Open �ϴ� ������ �ڵ�.
		{
			EmptyClipboard();  // ������ clipboard�� ����.
			SetClipboardData( CF_TEXT, hData ); 
			CloseClipboard();
		}
	}
}
*/












