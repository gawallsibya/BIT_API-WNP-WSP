// Memory �ε�

#include <windows.h>
#include <iostream.h>
/*
void main()
{

	// process ���� ��� �� Ȯ��
	HMODULE	h1 = GetModuleHandle(0);				// hInstance..
	HMODULE h2 = GetModuleHandle("kernel32.dll");

	cout << "exe    : "	<< (void*)h1 << endl;
	cout << "kernel : " << (void*)h2 << endl;
	//---------------------------------------------------------------------

	// �޸� ũ�� Ȯ��
	SYSTEM_INFO		si;
	// �ý��ۿ����� ������ �׻� ���� 
	// 4�� ������ �޸� ���� ������
	GetSystemInfo(&si);

	// CPU page ũ��	// 4096(4KB)
	cout << "page size  : " << si.dwPageSize	<< endl;

	// ��� ������ �ּ� �޸� �ּ� //65536( 64KB)
	cout << "Min addr   : " << (int)si.lpMinimumApplicationAddress << endl;

	// ��� ������ �ִ� �޸� �ּ� 
	cout << "Max addr   : " << si.lpMaximumApplicationAddress << endl;

	// �ּ� ���� �Ҵ� ����  // 65536 ( 64KB)
	cout << "Granularity: " << si.dwAllocationGranularity << endl;
	//---------------------------------------------------------------
}
*/

void print(const MEMORY_BASIC_INFORMATION & mbi)
{
	char *s = (char*)mbi.BaseAddress;
	char *e =  s + mbi.RegionSize - 1;
	char *state = "unknown";

	cout << (void*)s << " ~ " << (void*)e << " : ";

	switch( mbi.State)
	{
	case MEM_COMMIT:		state = "Commit";		break;
	case MEM_RESERVE:		state = "Reserve";		break;
	case MEM_FREE:			state = "Free";			break;
	}
	cout << state;

	char protect[10] = "--------";
	switch(mbi.Protect)
	{
	case PAGE_NOACCESS : strcpy( protect, "NOACCESS"); break;
	case PAGE_READONLY:  protect[0] = 'R';            break;
	case PAGE_EXECUTE:   protect[0] = 'E';				break;
	}
	cout << "\t" << protect << endl;
}
void main()
{
	char *addr = 0;
	MEMORY_BASIC_INFORMATION	mbi;

	while( addr < ( char*)0x80000000 ) // 0 ~ 2G����
	{
		VirtualQuery(addr, &mbi, sizeof(mbi));
		print(mbi);
		addr += mbi.RegionSize;
	}
}















