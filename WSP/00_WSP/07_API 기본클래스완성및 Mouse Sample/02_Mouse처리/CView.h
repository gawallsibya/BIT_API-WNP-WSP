//=================================================================
//   05�ܰ� ) �ϼ� 
//      WinMain�� ������ ���ν����� �� ��������.
//		ó���ؾ� �� �޽������� �����Ͽ� Ŭ������ �����Ѵ�.
//		�����Ǵ� ���� : stdafx.h,  stdafx.cpp
//						CObject.h, CObject.cpp
//		�����ؾ� �� ���� : CView.h, CView.cpp
//=================================================================

// [ �޽��� �� ���� ]
// 1. MFC�� �޽��� ������ �޽��� ����(message pump)��� �θ���.
//    MFC�� �޽��� ������ GetMessage()�� ������� �ʰ� 
//    PeekMessage()�� ����ϸ�, ��� �ð�(idle time)�� ó���ϱ� ����
//    Ư���� ���� �Լ� OnIdle()�� ������.
// 2. �޽��� ���̶� ������ �޽����� �޾ƾ� �� Ŭ������ ������ ����
//    ����ü �迭�̴�.
//    �� ���� ����ü �迭�� ó���� �޽����� �޽����� �����ϴ� �ɹ�
//    �Լ��� ���� �����͸� �ٽ������� ������.
// 3. MFC�� �Ž��� ���� �ڵ� �ڵ�ȭ�� ���� DECLARE_MESSAGE_MAP����
//    ��ũ�θ� ������.

//=================================================================

#include <windows.h>
#include "stdafx.h"
#include "CObject.h"

#ifndef _CView_
#define _CView_

// message map structure -----------------------------------------
class CView;


typedef LRESULT (CView::*CViewFunPointer)(HWND,WPARAM,LPARAM);

typedef struct tagMessageMap 
{
    UINT iMsg;
    CViewFunPointer fp;
} MessageMap;

static CViewFunPointer fpCViewGlobal;//pointer to a member function


// class CView ---------------------------------------------------
class CView : public CObject 
{
	// �ɹ� ���� ---------------------------------
	BOOL bFull;	// ��ü �����ΰ�??
	//--------------------------------------------
public:
	CView();
	void ModifyStyle( HWND hwnd, UINT Remove, UINT Add, BOOL bRedraw = TRUE);
	BOOL WINAPI PreTranslateMessage(HWND hwnd, MSG *pMsg);

	CDocument * GetDocument();

public:
	LRESULT OnPaint(HWND hwnd, WPARAM wParam, LPARAM lParam);

    //{{AFX_MESSAGE
	LRESULT OnSetFocus(HWND, WPARAM, LPARAM);
    LRESULT OnCreate(HWND, WPARAM,LPARAM);
	LRESULT OnSize(HWND, WPARAM, LPARAM);
	LRESULT OnCommand(HWND, WPARAM, LPARAM);
	LRESULT OnKeyDown(HWND, WPARAM, LPARAM);
    LRESULT OnDestroy(HWND, WPARAM,LPARAM);
	LRESULT OnLButtonDown(HWND hwnd, WPARAM wParam, LPARAM lParam);
    //}}AFX_MESSAGE

    DECLARE_MESSAGE_MAP()
};

#endif


