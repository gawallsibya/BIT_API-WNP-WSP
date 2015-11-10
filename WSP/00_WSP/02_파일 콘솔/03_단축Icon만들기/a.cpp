#include <iostream.h>
#include <windows.h>
#include <shlobj.h>

void Create( char* path, wchar_t* lnk)
{
	HRESULT ret;		
	// ShellLink ������Ʈ�� Load�Ѵ�. IShellLink �������̽��� ��û�Ѵ�.
	IShellLink* pLink;  
	ret = CoCreateInstance( CLSID_ShellLink, // ������Ʈ ID
								0,               // ����.(0 ������.
								CLSCTX_SERVER,  // Process�ȿ��� ����.
								IID_IShellLink,  // ���ϴ� Interface ID
								(void**)&pLink );
	if ( FAILED(ret))
	{
		cout << "Component�� Load�Ҽ� �����ϴ�." << endl;
		return ;
	}
	// component���
	pLink->SetPath( path );
	pLink->SetDescription("");
	pLink->SetArguments("");
	
	// IPersistFile �������̽��� ��´�.
	IPersistFile* pFile;
	pLink->QueryInterface( IID_IPersistFile, (void**)&pFile );
	
	pFile->Save( lnk, TRUE );
	
	// ���� interface�� �����Ѵ�.
	pFile->Release();
	pLink->Release();
}

void main()
{
	CoInitialize(0);
	
	Create("C:\\WINDOWS\\system32\\calc.exe", 
		
		L"C:\\Documents and Settings\\All Users\\���� ȭ��\\a.lnk");//Unicode�� �ѱ������ L ���þ ���δ�.
	
	CoUninitialize();
}
// MSDN���� IShellLink



