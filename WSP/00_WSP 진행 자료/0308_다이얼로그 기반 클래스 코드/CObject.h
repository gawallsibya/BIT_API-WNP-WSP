#include <windows.h>

#ifndef _CObject_
#define _CObject_

class CDocument;		// �������� 

class CObject 
{
protected:
    static char szAppName[];
    HWND        hwnd;
  
	CDocument *pDoc;

public:
    void InitInstance(HINSTANCE hInstance,PSTR szCmdLine,
                      int iCmdShow);
    void Run();
    WPARAM ExitInstance();

	LRESULT OnInitDialog(HWND hwnd,WPARAM wParam,LPARAM lParam);
};

#endif