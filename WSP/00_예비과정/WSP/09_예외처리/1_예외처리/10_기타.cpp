//��������������������������������������
// [ ���� ó�� 1 ]
//��������������������������������������



// ����ó�� ��� : ���� ���� ũ�� ����, ���� �ӵ� ����
// ���� �������� ������ ó���ϱ� ���� ��쿡�� ����ó�� 
// ��Ŀ���� ��� 
//Funcmeister1

DWORD Funcmeister1()
{
	DOWRD dwTemp;
		// 1. ������ ó�� �۾�
	__try 
	{
		// 2. ������ ���� 
		dwTemp = 0;
	}
	__except(EXCEPTION_EXECUTE_HANDLER) {
		// 3. ���ܻ�Ȳ ó�� �Ѵ�. �� �κ��� ������� �ʴ´�.
	}
	// 4. ó���� �۾��� ����Ѵ�.
	return(dwTemp);
}
// try-finally���� ������
// 1. ���� �帧 : 1 -> 2 -> 4
//    ���� ��Ȳ�� �߻��� ��쿡�� __except�� ����ȴ�.
// 2. return, goto, continue, break���� �ߴ�ó���� ������ ���Ǵ°��� ���� ������
//    ���� �ڵ鷯������ ũ�� ����� ����.  


//Funcmeister2
#include <windows.h>
int main()
{
	DWORD dwTemp = 0;
		// 1. ������ ó�� �۾�
	__try {
		// 2. ������ ���� 
		MessageBox(NULL, "1", NULL, MB_OK);
		dwTemp = 5/dwTemp;	// ���� ��Ȳ�� �߻���Ų��. 
		MessageBox(NULL, "2", NULL, MB_OK);
		dwTemp += 10;		// ������� �ʴ´�. 

	}
	__except(EXCEPTION_EXECUTE_HANDLER) {  // 0, 1, -1 ??
		// 3. ���ܻ�Ȳ ó�� �Ѵ�. 
		MessageBox(NULL, "3", NULL, MB_OK);
		MessageBeep(0);
	}
	// 4. ó���� �۾��� ����Ѵ�.
	MessageBox(NULL, "4", NULL, MB_OK);
	return(dwTemp);
}

// 5�� 0���� �������� �õ��ϸ� ���� ��Ȳ �߻��� --> except���� �� ������ �̵�...
// ���� ���� : 
// ���� �� ��  1 --> EXCEPTION_EXECUTE_HANDLER (�Ϲ������� ���)
// ���� �� ��  0 --> EXCEPTION_CONTINUE_SEARCH
//                   ���� ��Ȳ �ν� ����   
// ���� �� �� -1 --> EXCEPTION_CONTINUE_EXECUTION --> ���ѷ��� 
// ���ܰ� �߻��� �������� ���� ��� ���� 

// ??? ////////////////////////////////////////////////////////////////////////////

#include <windows.h>
char g_szBuffer[100];

LONG OliFilter1(char **ppchBuffer)
{
	if(*ppchBuffer == NULL)
	{
		*ppchBuffer = g_szBuffer;
		return(EXCEPTION_CONTINUE_EXECUTION);	//-1
	}
	return (EXCEPTION_EXECUTE_HANDLER);	// 1
}

void main()
{
	int x = 0;
	char *pchBuffer = NULL;
	__try {
		*pchBuffer = 'j';	// ���� �߻� 
		x = 5 / x;
	}
	__except (OliFilter1(&pchBuffer)) {
	}
}


