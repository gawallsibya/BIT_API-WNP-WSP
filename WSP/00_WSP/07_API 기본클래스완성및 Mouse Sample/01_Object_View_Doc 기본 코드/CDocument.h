// CDocument.h
// ��� ���� : ������ ���� 

#ifndef _CDocument_
#define _CDocument_

#include <vector>
using namespace std;

class CDocument 
{
protected:
	vector<POINT*> data;

public:
	CDocument();
	~CDocument();
};

#endif