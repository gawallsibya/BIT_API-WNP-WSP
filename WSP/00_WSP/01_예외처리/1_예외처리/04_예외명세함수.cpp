/**************************************************************

	[ C++�� ���� �� �Լ� (exception specification) ]


	���� ���� �����ν�, �ش� �Լ��� �߻���ų �� �ִ� ���ܵ��� 
	������ ������ �� �ִ�.

	�������̽� ����ڵ鿡�� � ���ܰ� �߻��Ǵ� �� �˷��ֱ� ���� 
	���̴�.


    ex)

	void f (int a) throw (x1, x2) {......}
	double g (double n, double m) throw ( ){......}


   - f() �Լ������� x1, x2 Ÿ���� ���ܳ� Ȥ�� �׷κ��� �Ļ��Ȱ�ü
      Ÿ���� ���ܰ� �߻��� �� �ִ�.
   - g() �Լ������� ���ܸ� �߻���Ű�� �ʴ´�. 

**************************************************************/


//[����] ���� ������ �������� divide()�Լ��� ���� ���� �غ��Ҵ�.

#include <iostream.h>
#include <stdlib.h>
double divide(double, double);

int main(void)
{
    try
	{
		double d1 = 10, d2 = 20;
		cout << d1 << " / " << d2 << " = " << divide(d1,d2) << endl;

		d2 = 0;
		cout << d1 << " / " << d2 << " = " << divide(d1,d2) << endl;
    }
    catch (char* msg)
	{
		cout << "## Error~!! : " << msg <<" ##" << endl;
    }
    return 0;
}


//���ڿ� ������ �߻��� �ǹ��ϴ� ��
double divide(double n, double m) throw (char*) 
{
    if (m == 0) 
		throw "0���� ���� �� �����ϴ�.";
//		throw 10;
    return n/m;
}

