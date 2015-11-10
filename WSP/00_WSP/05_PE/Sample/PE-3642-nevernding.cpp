//---------------------------------------------------------------
// PE Section �м� ���α׷�
// ���� : �迵��(nevernding)
// ���� : kodoc11 at hanmail dot net
// ���ù��� : http://blog.naver.com/nevernding/
// ������ : 2006/05/22
// ����ȯ�� : Microsoft Visual Studio 2003 Profecional(Visual C++ .NET)
//---------------------------------------------------------------

//#include "stdafx.h"
#include <windows.h>
#include <iostream>
using namespace std;
#include <TCHAR.h>

void restore_filemapping_resources(HANDLE hFile, HANDLE hFileMap, LPVOID pMapView)
{
	UnmapViewOfFile(pMapView);
	CloseHandle(hFileMap);
	CloseHandle(hFile);
}

int _tmain(int argc, _TCHAR* argv[])
{
	HANDLE hFile, hFileMap;
	LPVOID pBaseAddr;
	
	// ������ ������ PE������ File-mapping�� �̿��Ͽ� �޸𸮿� �ø���.
	hFile = CreateFile("C:\\Windows\\system32\\notepad.exe", GENERIC_READ, FILE_SHARE_READ, 
					NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if(!hFile)		return 0;
	hFileMap = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, "PE");
	if(!hFileMap)
	{
		CloseHandle(hFile);
		return 0;
	}
	// Create Map-view pointer
	pBaseAddr = MapViewOfFile(hFileMap, FILE_MAP_READ, 0, 0, 0);
	if(!pBaseAddr)
	{
		CloseHandle(hFileMap);
		CloseHandle(hFile);
		return 0;
	}

	// �ùٸ� PE�������� Dos/NT ����� Signature�� �����Ѵ�.
	PIMAGE_DOS_HEADER pDosHdr = (PIMAGE_DOS_HEADER)pBaseAddr;
	if(pDosHdr->e_magic != IMAGE_DOS_SIGNATURE)
		restore_filemapping_resources(hFile, hFileMap, pBaseAddr);
	PIMAGE_NT_HEADERS pNtHdr = (PIMAGE_NT_HEADERS)((DWORD)pBaseAddr + (DWORD)pDosHdr->e_lfanew);
	if(pNtHdr->Signature != IMAGE_NT_SIGNATURE)
		restore_filemapping_resources(hFile, hFileMap, pBaseAddr);

	int iNumberOfSections;
	DWORD dwSectionAlignment, dwFileAlignment;
		
	// ���� ����(���ǰ���, Raw&Virtual���� alignment) ����� ���
	iNumberOfSections = pNtHdr->FileHeader.NumberOfSections;
	dwSectionAlignment = pNtHdr->OptionalHeader.SectionAlignment;
	dwFileAlignment = pNtHdr->OptionalHeader.FileAlignment;
	printf("- Section Information -\n");
	printf(" Number of sections: %d\n", iNumberOfSections);
	printf(" Section Alignment : 0x%08X\n", dwSectionAlignment);
	printf(" File Alignment    : 0x%08X\n", dwFileAlignment);

	// ��������� �̵�(��������� IMAGE_OPTIONAL_HEADER, �� IMAGE_NT_HEADER �ٷ� �ڿ� ��ġ�Ѵ�)
	PIMAGE_SECTION_HEADER pSecHdr = (PIMAGE_SECTION_HEADER)((DWORD)pNtHdr +
									sizeof(IMAGE_NT_HEADERS));

	// �����̸��� ��ġ/ũ�� �Ӽ� ������ ���.
	printf("%8s %10s %10s %10s %10s %10s\n", 
			"Name", "Raw Addr", "Raw Size", "Vir Addr", "Vir Size", "Characer");
	for(int i = 0; i < iNumberOfSections; i++)
	{
		printf("%8s 0x%08X 0x%08X 0x%08X 0x%08X 0x%08X",
					pSecHdr->Name,										// �����̸�
					pSecHdr->PointerToRawData, pSecHdr->SizeOfRawData,	// Raw������ �ּ�/ũ��
					pSecHdr->VirtualAddress, pSecHdr->Misc.VirtualSize,	// Virtual������ �ּ�/ũ��
					pSecHdr->Characteristics);							// ���� �Ӽ�
		
		// ���� �Ӽ� �÷����� ����(Characteristics flags)
		// IMAGE_SCN_CTN_CODE				0x00000020		�ڵ�� ä���� ����
		// IMAGE_SCN_CTN_INITIALIZED_DATA	0x00000040		�����Ͱ� �ʱ�ȭ�� ����
		// IMAGE_SCN_CTN_UNINITIALIZED_DATA	0x00000080		�����Ͱ� ���ʱ�ȭ�� ����
		// IMAGE_SCN_MEM_EXECUTE			0x20000000		�ڵ�μ� ����� �� �ִ� ����
		// IMAGE_SCN_MEM_READ				0x40000000		�б� ���ɿ��� ����
		// IMAGE_SCN_MEM_WRITE				0x80000000		���� ���ɿ��� ����
		
		// ���� �Ӽ� �˻�
		// if(0x00000040 & pSecHdr->Characteristics)	printf("/Initialized");
		// if(0x00000080 & pSecHdr->Characteristics)	printf("/Uninitialized");
		if(0x20000000 & pSecHdr->Characteristics)	printf("/Code");
		if(0x40000000 & pSecHdr->Characteristics)	printf("/Read");
		if(0x80000000 & pSecHdr->Characteristics)	printf("/Write");
		puts("");

		pSecHdr++;		// ���� ���� ������ �̵�
	}

	
	// �ڿ���ȯ
	restore_filemapping_resources(hFile, hFileMap, pBaseAddr);

	return 0;
}