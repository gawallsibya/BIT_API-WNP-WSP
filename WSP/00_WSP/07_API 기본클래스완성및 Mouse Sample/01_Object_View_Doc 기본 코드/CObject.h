#include <windows.h>

#ifndef _CObject_
#define _CObject_

class CDocument;		// �������� 

class CObject 
{
protected:
    static char szAppName[];
    HWND        hwnd;
    MSG         msg;
    WNDCLASSEX  wndclass;

	CDocument *pDoc;

public:
    void InitInstance(HINSTANCE hInstance,PSTR szCmdLine,
                      int iCmdShow);
    void Run();
    WPARAM ExitInstance();
};

#endif