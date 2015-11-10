// data.h

// ����� ���� �޽��� 
#define WM_TRAYMESSAGE WM_USER + 100

#define IDC_BTNREFRESH			1
#define IDC_BTNTERMINATEPROCESS	2
#define IDC_BTNSPY				3
#define IDC_LOG					4

struct MEMBER
{
	char name[20];
	char uni[20];
	char maj[20];
	char num[20];
	char phone[20];

	MEMBER() {}
	MEMBER(char *n, char*u, char*ma, char*nu, char*ph)
	{
		strcpy(name, n);		strcpy(uni, u);
		strcpy(maj, ma);		strcpy(num, nu);
		strcpy(phone, ph);
	}
};
	   
extern HWND hMainList;
extern HWND hBtnRefresh, hBtnTerminateProcess, hBtnSpy;
extern HWND hStaticLog;


typedef struct _TDATA
{
	HWND	hDlg;			// �� �����尡 ���� Dialog�ڵ�
	char	exename[256];	// process �̸�
	DWORD	pid;			// process ID
	int		idx;			// ������ ����Ʈ���� idx
}TDATA;


extern HANDLE	hThreadList[20];	// ������ thread�� �ڵ�
extern int		ThreadCount;
extern HANDLE	hExitEvent;


