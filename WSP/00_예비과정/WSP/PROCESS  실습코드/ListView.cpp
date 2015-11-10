// ListView.cpp
#include "std.h"

HWND InitListView(HINSTANCE hInst, HWND hdlg)
{
	HWND hList;
	LVCOLUMN col={0};

	// 1. ����Ʈ ��Ʈ�� ���� 
	hList=CreateWindow(
		WC_LISTVIEW,NULL,WS_VISIBLE|WS_CHILD|WS_BORDER| \
		LVS_REPORT|LVS_SHOWSELALWAYS,
		10,10,560,300,hdlg,(HMENU)1010, hInst, NULL);

	// 2. ��Ÿ�� ���� 
	ListView_SetExtendedListViewStyle(hList, 
		LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES); 

	// 3. �÷� ���� 
	col.mask=LVCF_FMT | LVCF_WIDTH | LVCF_SUBITEM | LVCF_TEXT;
	col.fmt=LVCFMT_LEFT;

	col.cx=40, col.iSubItem=0, col.pszText="PID";
	ListView_InsertColumn(hList,0,&col);

	col.cx=100, col.iSubItem=0, col.pszText="�� ��";
	ListView_InsertColumn(hList,1,&col);

	col.cx=420, col.iSubItem=0, col.pszText="��ü ���";
	ListView_InsertColumn(hList,2,&col); 

	return hList;
}


void __stdcall AttachReady(HWND hList)
{
	LVITEM li={0};

	if(!hList)
	{
		ListView_DeleteAllItems(hList); // ������ ǥ���� ����Ʈ�� ��(������)���� �� �����ش�.
		return;
	}

	HANDLE hsnap_process, hsnap_module;
	PROCESSENTRY32 ppe={0};
	MODULEENTRY32 mme={0};
	ppe.dwSize=sizeof(ppe);
	mme.dwSize=sizeof(mme);
	li.mask=LVIF_TEXT | LVIF_IMAGE | LVIF_STATE; // ����Ʈ�� ����� ��(������) �Ӽ� ����
	hsnap_process = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);
	Process32First(hsnap_process, &ppe); // ÷�� ������ ���μ����� �ߺ��˻�ǹǷ�
	Process32Next(hsnap_process, &ppe); // �� �� �粸�ش�. 

	char temp[8]="";
	do{
		hsnap_module=CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, ppe.th32ProcessID);
		Module32First(hsnap_module, &mme);

		// //li.iItem=i; // ����Ʈ�� ��(������) ���þ��ϸ� �˾Ƽ� �ֽ� ���μ����� ���� ���� ǥ��
		if(lstrcmp(ppe.szExeFile, mme.szExePath))
		{ 
			li.pszText=itoa(ppe.th32ProcessID, temp, 10); 
			ListView_InsertItem(hList, &li);
			ListView_SetItemText(hList, 0, 1, ppe.szExeFile);
			ListView_SetItemText(hList, 0, 2, mme.szExePath);
			//i++; // ���þ��ϸ� �˾Ƽ� �ֽ� ���μ����� ���� ���� ǥ��
		}
		CloseHandle(hsnap_module);
	}while(Process32Next(hsnap_process, &ppe)); // ���� ���μ��� �˻��Ѵ�.

	CloseHandle(hsnap_process);
	
	// ó�� ������ ������ ���·�
	PostMessage(hList,WM_LBUTTONDOWN,1,0x0017004c); 
	PostMessage(hList,WM_LBUTTONUP,0,0x0017004c);

}




void _stdcall SelectTarget(HWND hList)
{

	int target_pid=0;
	char process_name[30]="";
	char process_path[200]="";
	char pid_str[8]="";

	int num_selected=ListView_GetSelectedCount(hList);

	if(num_selected==0 || num_selected>1)
	{
		MessageBox(NULL,"�ùٸ��� �����ϼ���","����",MB_OK);
		return;
	}

	int index= ListView_GetNextItem (
		hList,-1,LVIS_SELECTED);

	ListView_GetItemText(hList, index, 0, pid_str, 8);
	target_pid=atoi(pid_str);
	ListView_GetItemText(hList, index, 2, process_path, 200);
	ListView_GetItemText(hList, index, 1, process_name, 30);
	MessageBox(NULL, process_path, process_name, MB_OK);

}



