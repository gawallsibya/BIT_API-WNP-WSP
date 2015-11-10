/*

�ý����� �ҹ� ��Ŷ(��Ǫ�ΰ��� ��ų��..)�� ���� ������Ʈ��

������� �ϴµ���.. ����. ȭ��� �����츦 ������ �ʰ�.

���� ������. ������ ����ڰ� �̸� �˰� ���α׷��� �׿�������.

�ǹ̰� ���ڳ���.. �׷��� ���� ���ᰡ �Ұ����ϰ� ������� �մϴ�.

----------------------------------------------------------------

���� �۾� �����ڿ��� ���ϼ� ���� �������..
�ش� ���μ����� �����Ҷ� CreateProcess�� 3��° �Ķ������ PKO�� ������ �����Ѵ�.
�̶� ��� �����(EveryOne)�� SID�� ������ Access ������ 0���� ���� �ϸ鼭 �����ϸ� �� 

�� ���⸦ �۾������ڿ��� ���ϼ� ���� �Ϸ���
1. EveryOne�� SID�� ��´�.
2. ACE�� �������� 1���� ���� SID�� ���� ���� ������ 0����.
3. ACL�� ������, Security Descriptor�� �����, SECURITY_ATTRIBUTES ����ü�� �ϼ��Ѵ�.
4. CreateProcess( 0, "calc.exe", &sa,/// 3���� ���� ����ü...

�� ���� �ϸ� �۾������ڿ��� ���ϼ� ����. 
���� TerminateProcess() �� ����ص� ���ϼ� ����.

//-------------------------------------------------
��, 
������ ��ó�� ������ ���⸦ ���� ���ϼ� ���� ���� �ƴϴ�..

Ư�� �����(Process)�� SE_DEBUG_NAME �̶�� Ư���� ������ TerminateProcess()�� �����ϸ� ���� ������ 
���� KO�� ������ ���Ǳ� ������ �� ���⸦ ���ϼ� �ִ�.

���� WinLogOn.exe�� ���ϼ� �ֽ��ϴ�.
���񽺵� ���� ���ϼ� �ֽ��ϴ�.

�۾������ڴ� SE_DEBUG_NAME Ư���� ����ϰ� ���� �ʱ� ������ ������ ���̴�. 
*/


// �۾� �����ڿ��� ���ϼ� ������ ���⸦ �����ϱ�

#define _WIN32_WINNT 0x0500
#define WINVER      0x0500
#include <windows.h>
#include <iostream.h>
#include <aclapi.h>

void main()
{
	DWORD cbSid=255,cbDomain=255;
	
	// Everyone�� SID�� ���Ѵ�.
	SID_IDENTIFIER_AUTHORITY SIDEvery=SECURITY_WORLD_SID_AUTHORITY;
	PSID pEverySID;
	AllocateAndInitializeSid(&SIDEvery,1,SECURITY_WORLD_RID,0,0,0,0,0,0,0,&pEverySID);
	
	// ACE �����.!!!!
	EXPLICIT_ACCESS EA[1];
	memset(EA,0,sizeof(EXPLICIT_ACCESS)*1);
	EA[0].grfAccessPermissions= 0;  // everyone �� ���� ������ NO Access �� ����.
	EA[0].grfAccessMode=SET_ACCESS;
	EA[0].grfInheritance=NO_INHERITANCE;
	EA[0].Trustee.TrusteeForm=TRUSTEE_IS_SID;
	EA[0].Trustee.TrusteeType=TRUSTEE_IS_WELL_KNOWN_GROUP;
	EA[0].Trustee.ptstrName=(LPTSTR)pEverySID;
	
	// ACL �����.
	PACL pAcl;
	SetEntriesInAcl(1,EA,NULL,&pAcl);
	
	// ���� ������ �����.
	SECURITY_DESCRIPTOR SD;
	// SD�� �ʱ�ȭ�Ѵ�.
	InitializeSecurityDescriptor(&SD, SECURITY_DESCRIPTOR_REVISION);
	
	// ACL�� SD�� ���Խ�Ų��.
	SetSecurityDescriptorDacl(&SD,TRUE,pAcl,FALSE);
	
	// ���� �Ӽ��� �����.
	SECURITY_ATTRIBUTES SA;
	
	SA.nLength=sizeof(SECURITY_ATTRIBUTES);
	SA.lpSecurityDescriptor=&SD;
	SA.bInheritHandle=FALSE;
	
	// ���μ��� ����.
	STARTUPINFO si = { 0 };
	si.cb = sizeof( si );
	
	PROCESS_INFORMATION pi;
	
	BOOL b= CreateProcess( 0, "calc.exe", 
		&SA, 0, // ���μ��� KO �� ���� ������ �����Ѵ�. (every one�� ���� NO_ACCESS )�̴�.
		0, NORMAL_PRIORITY_CLASS, 0, 0, &si, &pi );
	
	if ( b ) 
	{
		CloseHandle( pi.hProcess );
		CloseHandle( pi.hThread );
	}
	// �����߿� �Ҵ��� �޸𸮸� �����Ѵ�.
	FreeSid(pEverySID);
	LocalFree(pAcl);
}



