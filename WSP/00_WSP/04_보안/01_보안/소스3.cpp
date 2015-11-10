//---------------------------------------------------------
// ���� ������ - ���� 
//---------------------------------------------------------

#pragma comment( linker, "/subsystem:windows")

#include <windows.h>
#include <aclapi.h>

void SetSecurity()
{
	HANDLE hFile;
	char str[] = "������ �а� �� �� ������ User1�� �� �� �ִ�.";
	DWORD dwWritten;

	// ACE ���� ����ü �ʿ��� ����ŭ ���� : 
	// �������� ��� ������ �� ���ΰ�??
	EXPLICIT_ACCESS EA[2];
	char pSid[255];
	char pDomain[255];
	DWORD cbSid=255, cbDomain = 255;
	SID_NAME_USE peUse;
	PACL	pAcl;
	SECURITY_DESCRIPTOR	SD;
	SECURITY_ATTRIBUTES SA;

	// 1. ��� SID�� ���Ѵ�.
	SID_IDENTIFIER_AUTHORITY SIDEvery = SECURITY_WORLD_SID_AUTHORITY;
	PSID pEverySID;
	// ���� SID(Every, Administrator)�� ���ϴ� �Լ� : 
	// ��� ����ڸ� ��Ī�ϴ� SID�� pEverySID�� ���� 
	AllocateAndInitializeSid(&SIDEvery, 1, SECURITY_WORLD_RID, 0, 0, 0, 0, 0, 0, 0,
		&pEverySID);
	
	memset(EA, 0, sizeof(EXPLICIT_ACCESS)*2);
	// Every�� �б� ����(GENERIC_READ)�� �㰡(Set_ACCESS) ACE ���� 
	EA[0].grfAccessPermissions = GENERIC_READ;
	EA[0].grfAccessMode		   = SET_ACCESS;
	EA[0].grfInheritance	   = NO_INHERITANCE;
	EA[0].Trustee.TrusteeForm	= TRUSTEE_IS_SID;
	EA[0].Trustee.TrusteeType	= TRUSTEE_IS_WELL_KNOWN_GROUP;
	EA[0].Trustee.ptstrName     = (LPTSTR)pEverySID;

	// 1.1 User1�� SID�� ���Ѵ�.
	// ������� �̸����� ���� Ư�� SID�� ���ϴ� �Լ� 
	// pSid�� ����ȴ�.
	LookupAccountName(NULL, "User1", (PSID)pSid, &cbSid, pDomain, &cbDomain, &peUse);
	
	// ACE�� �����.
	// �������� : SID�� �����ϸ� ��
	// ��� ������ �� ���ΰ�   : ������ �����Ǵ� �ɹ��� ���� 
	// User1���� ��� ������ �㰡...
	EA[1].grfAccessPermissions	= GENERIC_ALL;
	EA[1].grfAccessMode			= SET_ACCESS;
	EA[1].grfInheritance		= NO_INHERITANCE;
	EA[1].Trustee.TrusteeForm	= TRUSTEE_IS_SID;
	EA[1].Trustee.TrusteeType	= TRUSTEE_IS_USER;
	EA[1].Trustee.ptstrName     = (LPTSTR)pSid;

	// ACE(����)�� ACL�� ���Խ�Ű�� �� ACL(List)�� �����.
	SetEntriesInAcl(2, EA, NULL, &pAcl);

	// SD�� �ʱ�ȭ �Ѵ�.
	InitializeSecurityDescriptor(&SD, SECURITY_DESCRIPTOR_REVISION);

	// ACL�� SD(���� �ؼ���)�� ���Խ�Ų��.
	SetSecurityDescriptorDacl(&SD, TRUE, pAcl, FALSE);

	// ���� �Ӽ��� �����.
	SA.nLength		= sizeof(SECURITY_ATTRIBUTES);
	SA.lpSecurityDescriptor	= &SD;
	SA.bInheritHandle		= FALSE;

	// ������ �����Ѵ�.
	hFile = CreateFile("c:\\User1Only.txt", GENERIC_ALL, 0, &SA,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(hFile, str, strlen(str), &dwWritten, NULL);
	CloseHandle(hFile);
	
	//�����߿� �Ҵ��� �޸� ����
	FreeSid(pEverySID);
	LocalFree(pAcl);
	// ������ ����� ����� ������ Ȯ��...

}
HINSTANCE g_hInst;
// �޼��� ó���Լ�.
LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

	switch( msg )
	{
	case WM_DESTROY: 
		PostQuitMessage(0); 
		return 0;
	}
	return DefWindowProc( hwnd, msg, wParam, lParam);
}

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE, PSTR lpCmdLine, int nShowCmd)
{
	WNDCLASS wc;

	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject( WHITE_BRUSH);

	wc.hCursor  = LoadCursor( 0, IDC_ARROW );
	wc.hIcon    = LoadIcon  ( 0, IDI_WINLOGO);
	wc.hInstance= hInstance; 

	wc.lpfnWndProc   = WndProc;
	wc.lpszClassName = "First"; 
	wc.lpszMenuName  = 0; 
	wc.style		 = 0; 

	ATOM atom = RegisterClass( &wc );

	HWND hwnd = CreateWindowEx( 0, "First", "Spy", 
					WS_OVERLAPPEDWINDOW, 0, 0, 500,500, 0, 0, hInstance, 0);

	ShowWindow( hwnd, SW_SHOW);
	g_hInst = hInstance;

	SetSecurity();
	MessageBox(NULL,"���� �����ڸ� �����߽��ϴ�", "�˸�",MB_OK);

	MSG msg;
	while ( GetMessage( &msg, 0, 0, 0) )
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	
	return msg.wParam;
}



