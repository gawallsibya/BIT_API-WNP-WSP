//------------------------------------------------------------------
// ������ ���� ������ ����
//------------------------------------------------------------------
#pragma comment( linker, "/subsystem:windows")


#include <windows.h>
#include "AclApi.h"

//----------------------------------------------------------------------------
// GetSecurity
// ���� ������ ������ �����ִ� ���� 
// 
//----------------------------------------------------------------------------
char gMes[1024] = "���콺 ���� ��ư  Ŭ���� ���� ������ �������ϴ� ���� ����";
void GetSecurity()
{
	OPENFILENAME OFN;
	char lpstrFile[MAX_PATH] = "";
	HANDLE hFile;
	char Mes[255];
	PSECURITY_DESCRIPTOR pSD;
	PSID pOwner;
	PACL pDacl;
	int i;
	DWORD cbName, cbDomain;
	char *Name, *Domain;
	SID_NAME_USE	peUse;
	ULONG	nAce;
	PEXPLICIT_ACCESS pEntry;

	// 1. ��� ������ �̸��� ��´�.
	memset(&OFN, 0, sizeof(OPENFILENAME));

	OFN.lStructSize = sizeof(OPENFILENAME);
	OFN.hwndOwner	= NULL;
	OFN.lpstrFilter	= "Every File(*.*)\0*.*\0";
	OFN.lpstrFile	= lpstrFile;
	OFN.nMaxFile	= 256;
	OFN.lpstrInitialDir	= "c:\\";
	if(GetOpenFileName(&OFN)==0){
		return;
	}
	//------------------------------------------------------------



	// 2. ������ ����.
	hFile = CreateFile(lpstrFile, GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hFile == NULL)
		return;

	// ���ϸ� ���
	wsprintf(Mes, "���ϸ� = %s\n", lpstrFile);
	strcpy(gMes, Mes);


	
	//3. ���� �����ڸ� �д´�.---------------------------------------------------

	// ���� �ڵ�� ���� ���� �����ڸ� ���ϴ� �Լ� 
	// ������ ����, DACL ������ ���Ѵ�. 
	//1) ��� ������Ʈ�� �ڵ�
	//2) ���� ������Ʈ�� ������ ������ ������ ��  
	//   ������ ���� SE_FILE_OBJECT ������ ����
	//3) ���� �������� ������ ���ϰ��� �ϴ� ������ ���� 
	//   - ������ ����|DACL ���� 
	//4) ������ 4���� �μ��� ������ �����ޱ� ���� ������ ������
	// �������� ���� ������ �� ��ü�� �����ޱ� ���� ���� ������ ����ü ������ 
	//   - pOwner : ������Ʈ�� ������ �����ڿ� ���� ���� ȹ��(SID������)
	//   - pDacl  : DACL�� ���� ȹ�� 
	if(GetSecurityInfo(hFile, SE_FILE_OBJECT, OWNER_SECURITY_INFORMATION|
		DACL_SECURITY_INFORMATION, &pOwner, NULL, &pDacl, NULL, (LPVOID*)&pSD)!=
		ERROR_SUCCESS){
		MessageBox(NULL,"���� ������ ���� �� ����.", "", MB_OK);
		return;
	}
	CloseHandle(hFile);

	// ������ ���� �����ֱ�
	cbName = 0;
	cbDomain = 0;
	// pOwner�� ���� ������ ���� �����͸� ������ ���� Ȯ�� 



	// 4. ������ ���� ���� 
	//    ���� name�� domain�� ���� ���̸� �����Ѵ�. -----------------------
	//    LookupAccountSid()  : sid ==> ������� �̸� ��� 
	LookupAccountSid(NULL, pOwner, NULL, &cbName, NULL, &cbDomain, &peUse);
	Name = (char*)malloc(cbName);
	Domain = (char*)malloc(cbDomain);

	// ���� SID�� ���� ������� �̸��� ���Ѵ�. 
	// �������� ������ GetSecurtyInfo �Լ��� ���� pOwner�� ��� �ִ�.
	// pOwner�� ������ SID ���̱� ������ ���� ������ ����Ű���� �˼� ����.
	// ���� SID�κ��� ���� ������ ���ؾ� �Ѵ�.
	LookupAccountSid(NULL, pOwner, Name, &cbName, Domain, &cbDomain, &peUse);

	wsprintf(Mes, "������ = %s\n", Name);
	strcat(gMes, Mes);

	wsprintf(Mes, "������ ������ = %s\n", Domain);
	strcat(gMes, Mes);
	free(Name);
	free(Domain);

	// 5. DACL ���� �б� 
	//GetSecurityInfo()�κ��� DACl �����͸� �����.
	// pDacl�� ������ ���� �ִ�.
	// ACE�� ���� ��� 
	GetExplicitEntriesFromAcl(pDacl, &nAce, &pEntry);
	wsprintf(Mes, "ACE�� ���� = %d\n", nAce);
	strcat(gMes, Mes);

	for(i=0;i<(int)nAce; i++)
	{
		cbName = 0;
		cbDomain = 0;
		LookupAccountSid(NULL, pEntry[i].Trustee.ptstrName, NULL, &cbName,
			NULL, &cbDomain, &peUse);
		Name = (char*)malloc(cbName);
		Domain = (char*)malloc(cbDomain);
		LookupAccountSid(NULL, pEntry[i].Trustee.ptstrName, Name, &cbName,
			Domain, &cbDomain, &peUse);	

		wsprintf(Mes, "%s����ڿ��� %x �׼��� ������ %s�Ѵ�.\n",
			Name, pEntry[i].grfAccessPermissions,
			pEntry[i].grfAccessMode == GRANT_ACCESS ? "�㰡" : "�ź�");
		strcat(gMes, Mes);
		free(Name);
		free(Domain);
	}

	// �޸� ���� ��� ���
	LocalFree(pEntry);
	LocalFree(pSD);
	InvalidateRect(NULL, NULL, TRUE);

}
// �޼��� ó���Լ�.


LRESULT CALLBACK WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch( msg )
	{
	case WM_LBUTTONDOWN:
		GetSecurity();
		return 0;
	case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			// TODO: Add any drawing code here...
			RECT rt;
			GetClientRect(hWnd, &rt);
			DrawText(hdc, gMes, -1, &rt, 0);
			EndPaint(hWnd, &ps);
			break;

	case WM_DESTROY: 
		PostQuitMessage(0); 
		return 0;
	}
	return DefWindowProc( hWnd, msg, wParam, lParam);
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

	MSG msg;
	while ( GetMessage( &msg, 0, 0, 0) )
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}



