// Process ���� 

// 1. ToolHelpAPI �̿� : 2000, 98, 95 ��� ����
#include <windows.h>
#include <TLHelp32.h>
#include <iostream>
using namespace std;

/*
  ������Ʈ�� �ȿ� ������ �ʴ� HKEY_PERFORMANCE_DATA ��� ���� 
  ��� �ý��� ������ ����ִ�.

  ���� ������ ���� ���ϰ� ������ �����ϴ� �Լ��� ���� �����Ѵ�.

   TLHelp32.h�� �ִ� �Լ����� �̿��Ͽ� ������ ����...
   MSDN   .. toolhelpmodule Ȯ��..
*/

// Tool Help API �� ����ϱ� �������.
// Tool Help API : ���μ���, ������, ���, �� ���� ���� �Ҷ� ����ϴ� �Լ��� ����
/*
void main()
{
	HANDLE	hSnap = CreateToolhelp32Snapshot(
						TH32CS_SNAPPROCESS, 0);	// process ID

	if( hSnap == 0 )
		return ;

	PROCESSENTRY32	ppe;
	BOOL	b = Process32First(hSnap, &ppe);
	while ( b )
	{
		printf("%04d %04d %s\n", ppe.th32ProcessID,
								 ppe.th32ParentProcessID,
								 ppe.szExeFile);

		b = Process32Next( hSnap, &ppe );
	}
	CloseHandle(hSnap);
}
*/

// 2. PSAPI : EnumProcess()
/*
#include <windows.h>
#include <stdio.h>
#include "psapi.h"		// psapi.lib �߰�..

void PrintProcessNameAndID( DWORD processID)
{
	char szProcessName[ MAX_PATH ] = "unknown";

	// ���μ����� �ڵ� ���
	HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION | 
								   PROCESS_VM_READ, 
								   FALSE, processID);

	// process �̸� ��������
	if( NULL != hProcess)
	{
		HMODULE hMod;
		DWORD	cbNeeded;
		if( EnumProcessModules( hProcess, &hMod, sizeof( hMod), &cbNeeded))
		{
			GetModuleBaseName( hProcess, hMod, szProcessName, sizeof( szProcessName));
		}
		else
			return;
	}
	else return;

	//print
	printf("%s ( PROCESS ID : %u )\n", szProcessName, processID);
	CloseHandle(hProcess);

}
void main()
{
	// process list ��������(id��)
	DWORD aProcess[1024], cbNeeded, cProcesses;
	unsigned int i;

	if( !EnumProcesses(aProcess, sizeof( aProcess), &cbNeeded) )
		// �迭 ��, ���ϵǴ� ����Ʈ �� 
		// �迭�� id������ ����.
		return;

	// �󸶳� ���� ���μ������� ���ϵǾ��� ���
	cProcesses = cbNeeded / sizeof( DWORD);

	// process �̸� ���
	for( i = 0; i < cbNeeded; i++)
		PrintProcessNameAndID( aProcess[i] );
}
*/

// 3. ��� ����
#include <windows.h>
#include <TLHelp32.h>
#include <iostream>
using namespace std;

void main()
{
	// ���� ProcessID���
	HWND hCalc = FindWindow(0, "����");

	DWORD pid;
	GetWindowThreadProcessId(hCalc, &pid);

	HANDLE hSnap = CreateToolhelp32Snapshot( TH32CS_SNAPMODULE, pid);

	MODULEENTRY32	mme;
	BOOL b = Module32First( hSnap, &mme);

	while( b )
	{
		cout << (void*)mme.modBaseAddr << " : "
			<< mme.szModule << " PATH : " << mme.szExePath << endl;

		b = Module32Next( hSnap, &mme);
	}
	CloseHandle(hSnap);
}





























