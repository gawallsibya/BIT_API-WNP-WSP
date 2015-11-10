/**************************************************************

	[ ���� Ǯ��(Stack Unwinding) ]


	�߻��� ���ܿ� ���Ͽ� ó���� catch ����� ���� ���, �ڵ����� 
	���� �Լ��� ���� ��ü�� �����Ѵ�.

	���� main()�Լ����� ���޵Ǿ��� ������ ó���� catch() ����� ������ 
	���α׷��� ����ȴ�.
 

**************************************************************/

//[����] ���� Ǯ���� ���� ���α׷�

#include <iostream.h>

void f3(double n); 
void f2(double n); 
void f1(double n);

int main(void)
{
    try
	{
        double num = -100;
        f1(num);
    }
    catch (char* msg)  
	{
		cout << "[main()] ##Error!! : " << msg << endl;
	}
    return 0;
}


void f1(double n)
{
    try		{    		f2(n);    	}
    catch (int no) {cout << "[f1()] ##Error!! : " << no << endl;};
}

void f2(double n)
{
    try{    f3(n);    }
    catch (int no) {cout << "[f2()] ##Error!! : " << no << endl;};
}

void f3(double n)
{
    try{    if (n < 0) throw "The number is too small.";    }
    catch (int no) {cout << "[f3()] ##Error!! : " << no << endl;};
}
