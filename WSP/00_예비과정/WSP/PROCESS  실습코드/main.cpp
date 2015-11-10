#include "std.h"



BOOL CALLBACK DialogProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hpreinstance, LPSTR lpcmdline, int ncmdshow){
	DialogBox(hinstance, MAKEINTRESOURCE(IDD_DIALOG1), HWND_DESKTOP, DialogProc);
	return 0;
}


BOOL CALLBACK DialogProc(HWND hdlg, UINT message, WPARAM wparam, LPARAM lparam){

	// dlg instance
	static HINSTANCE hinst = GetModuleHandle(0);	
	static HWND		 hList;

	switch(message)
	{
	case WM_INITDIALOG:

		// ����Ʈ ��Ʈ�� �ʱ�ȭ 
		hList = InitListView(hinst, hdlg);

		// ����Ʈ ��Ʈ�ѿ� ������ �߰� 
		AttachReady(hList);
		
		return 0;
		
	case WM_COMMAND:
		switch(LOWORD(wparam))
		{
		case IDOK:
			// ������ ���� ��� 
			SelectTarget(hList);
			return 0;
			
		case IDCANCEL:
			EndDialog(hdlg, 0);
			return 0;
		case IDC_BUTTON1:
			MoveWindow(hdlg, 0, 0, 700, 600, TRUE);
			return 0;
		}
		return 0;
		
	}
	return 0;
}



