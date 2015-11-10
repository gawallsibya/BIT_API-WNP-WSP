/*
���� ����

*���� ������ NTFS������ ����

 

1. ACE(Access Control Entry) �����

2. ACL(Access Control List)��  ACE�߰�

3. ACL�� SECURITY_DESCRIPTOR�� �߰�

4. SD�� SECURITY_ATTRIBUTES�� �߰�

--------------------------------------------------------------------------
*/


#include <windows.h>

#include <aclapi.h>       // ���Ȱ��� ���

 

void main()

{

        // 1. sid ���

        char sid[256] = {0};

        char domain[256] = {0};

 

        DWORD sz1 = 256;

        DWORD sz2 = 256;

 

        SID_NAME_USE use;

 

        LookupAccountName(".", "everyone", sid, &sz1, domain, &sz2, &use);

 

        // 2. ACE �����

        EXPLICIT_ACCESS ea = {0};

        ea.grfAccessPermissions = GENERIC_READ;        // ���ٱ���

        ea.grfInheritance = NO_INHERITANCE;

        ea.grfAccessMode = SET_ACCESS;

        ea.Trustee.TrusteeForm = TRUSTEE_IS_SID;

        ea.Trustee.TrusteeType = TRUSTEE_IS_WELL_KNOWN_GROUP;

        ea.Trustee.ptstrName = (LPSTR)sid;

 

        // 3. ACL �����

        PACL pAcl;

        SetEntriesInAcl(1, &ea, 0, &pAcl);

 

        // 4. SECURITY_DESCRIPTOR�� ACL �ֱ�

        SECURITY_DESCRIPTOR sd;

 

        InitializeSecurityDescriptor(&sd, SECURITY_DESCRIPTOR_REVISION);

        SetSecurityDescriptorDacl(&sd, TRUE, pAcl, FALSE);

 

        // 5. SA �����

        SECURITY_ATTRIBUTES sa;

        sa.bInheritHandle                = FALSE;  // ��� ���ɿ���

        sa.lpSecurityDescriptor = &sd;        // ���� ������.

        sa.nLength = sizeof(sa);

 

        //-----------------------------------------------------------------

        // KO ������ sa�� �����ϸ� ���� �Ӽ��� �����ȴ�

/*      HANDLE hFile = CreateFile("c:\\a.txt",

                           GENERIC_READ | GENERIC_WRITE,

                           0,

                           &sa,        // ���ȼӼ�

                           CREATE_ALWAYS,

                           FILE_ATTRIBUTE_NORMAL, 0);

                                                          */

        PROCESS_INFORMATION pi;

        STARTUPINFO si = {0};

        si.cb = sizeof(si);

 

        char name[256] = "calc.exe";

 

        // ��� ����ڰ� ������ ������ ���μ����� �����Ѵ�.

        BOOL b = CreateProcess(0, name, &sa, &sa, // ����

                                                   0, 0, 0, 0, &si, &pi);

 

        if(b)

        {

                CloseHandle(pi.hProcess);

                CloseHandle(pi.hThread);

        }

 

//        CloseHandle(hFile);

        LocalFree(sid);

}

 

// �����϶�

// Ž���⸦ ��� c:\\a.txt�� ������ ��ư�� ������ �Ӽ� -> ���� ��

// ���� �����ƶ�

