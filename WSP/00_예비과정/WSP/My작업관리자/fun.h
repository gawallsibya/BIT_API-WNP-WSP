// fun.h


int OnTrayIcon(HWND hwnd);

void TrayMessage(HWND hwnd, WPARAM wParam, LPARAM lParam);

//--- ��Ʈ�� �ʱ�ȭ 
void CreateChildControl(HWND hwnd);


//---- ���μ��� ��� ���
void ProcessList();
void ListBoxAddData(int i, PROCESSENTRY32 ppe);

//---- ���μ��� ���� 
void ProcessExit(HWND hwnd);


//---- ���μ��� ����
void WatchProcess(HWND hwnd);
DWORD WINAPI Watch( void *p);		// Thread Fun


//---- ���μ��� ���� 
void NewProcess(HWND hwnd);
