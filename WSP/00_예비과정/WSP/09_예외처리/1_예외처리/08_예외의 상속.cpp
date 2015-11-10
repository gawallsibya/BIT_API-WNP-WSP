/**************************************************************

	[ ������ ��� ]


	���� Ŭ������ ���

	� Ŭ������ public ����� ���� Ŭ������ ������ �ִٸ�, 
	�װ��� �⺻���� �Ͽ� �Ļ��Ǵ� Ŭ�������� �� ���� Ŭ�������� 
	����Ѵ�.

	������ ���ǵǾ� �ִ� ���� Ŭ������κ��� ���ο� ���� Ŭ������ 
	�Ļ���ų �� �ִ�.

	������ ������ ���� ��Ȳ���� Ŭ���� ���� ������ ǥ�������ν� 
	������ ����������.


	class MathErr {......};  
	class Overflow : public MathErr {......};
	class Underflow : public MathErr {......};
	class ZeroDivide : public MathErr {......};



   [ catch��� ������ ���ǻ��� ]

   catch ����� ����� ������� ���ܸ� �˻��Ѵ�.

   catch ����� ���� ��üȭ�� ���� Ŭ������ ���� ó���� ���� ������, 
   ���� �Ϲ�ȭ�� ���� Ŭ������ ���� ó���� ���߿� ������ �����ؾ� �Ѵ�. 
   ���� �Ϲ�ȭ�� ���� Ŭ������ ���� �´ٸ� ��üȭ�� ���� ó�� ������ ���� 
   ������� �ʴ´�.


   catch����� ����ó�� �����ϸ� ZeroDivide�� ���� catch����� 
   ���� ������� �ʴ´�.

	try { ...... }
	catch (Overflow) { ...... }
	catch (MathErr) { ...... }
	catch (ZeroDivide) { ...... }


**************************************************************/
//[����] �迭 ÷�� ������ ��߳� �� ���Ǵ� ESize ���� Ŭ������ 
//       �������� �����ϰ�, �װ�����
//      ���� �Ļ���Ų ChildESize�� ������ �� ������ �߻����״�. 


#include <iostream.h>

class ESize
{
protected:
	int index;
public:
	ESize(int i):index(i){}
	virtual void print() const;
};

void ESize::print() const
{
    cout << "Out of Range : " << index << endl;
}
//--------------------------------------------------------


class ChildESize : public ESize
{
    	int lbound;
    	int ubound;
public:
    	ChildESize(int i,int lidx, int uidx) : 
                        ESize(i), lbound(lidx), ubound(uidx) {};
	void print() const;
};

void ChildESize::print() const
{
    cout << "Out of Range [" << lbound << " to " << ubound << "]" ;
    cout << ", Current Index : " << index << endl;
}
//--------------------------------------------------------


class Array{
	int size;
	int* arr;
public:
	Array(){arr=NULL; size=0;};
	Array(int n);
	~Array(){ delete[] arr; }
	int getSize() { return size; }
	int summary();

	int& operator[](int i);
	const int& operator[](int i) const;
};

Array::Array(int n):size(n)
{
    arr = new int[size];
    for(int i=0; i<size; i++)  arr[i]=0;
}

int Array::summary()
{
    int sum=0;
    for (int i=0; i<size; i++)
        sum += arr[i];
    return sum;
}

int& Array::operator[](int i)
{
    if (i < 0 || i >= size)  throw ChildESize(i,0,size);
    return arr[i];
}

const int& Array::operator[](int i) const
{
    if (i < 0 || i >= size)  throw ChildESize(i,0,size);
    return arr[i];
}
//------------------------------------------------------


int main(void)
{
    Array mydata(3);

    try
	{
        for (int i=0; i<=3; i++) //���ܹ߻��� ���� �Ϻη� (i <= 3)���� ����
			mydata[i] = i*10;
	}
    catch(ESize &err)
    {
        cout << "## Exception ##\t" ;
        err.print();
    }
    try
	{
        for (int i=0; i<=3; i++) //���ܹ߻��� ���� �Ϻη� (i <= 3)���� ����
            cout << mydata[i] << endl;
    }
    catch(ChildESize &err)
    {
        cout << "## Exception ##\t" ;
        err.print();
    }
    return 0;
}
