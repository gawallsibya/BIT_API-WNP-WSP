//handler.cpp
#include "std.h"

void OnNewWork(HWND hwnd)
{


}

int OnInitDialog(HWND hDlg)
{
	InitCommonControls();
	//����Ʈ �ڽ� �ʱ�ȭ
	ui_InitList(hDlg);

	return TRUE;
}

int OnCommand(HWND hwnd,WPARAM wParam)
{
	switch( wParam )
	{
	case ID_FILE_NEWWORK:	OnNewWork(hwnd);		  break;     //���۾�
	case IDC_REFRESH:		OnRefresh(hwnd);		  break;
	case IDC_PROEXIT: break;
	case IDC_WATCH:   break;
	case ID_FILE_EXIT:		EndDialog(hwnd,IDCANCEL); return 0;	 //����
	case IDCANCEL:			EndDialog(hwnd,IDCANCEL); return 0;
	}
	return TRUE;
}
int OnRefresh(HWND hwnd)
{
	HWND hList = GetDlgItem(hwnd,IDC_LIST);
	SendMessage(hList,LVM_DELETEALLITEMS,0,0);
	ui_ViewProcess(hList);
	return 0;
}

int OnNotify(HWND hDlg,LPARAM lParam)
{
	/*
	HWND hTree=GetDlgItem(hDlg,IDC_TREE1);
	
	LPNMHDR hdr;
	LPNMTREEVIEW ntv;
	hdr=(LPNMHDR)lParam;
	ntv=(LPNMTREEVIEW)lParam;
	if (hdr->hwndFrom == hTree) {
		switch (hdr->code)
		{
			// ���õ� �׸��� �����ش�.
			case TVN_SELCHANGED:
				ui_TreeSelect(hDlg, hTree,ntv); break;
		}
	}
	*/
	return 0;

}
