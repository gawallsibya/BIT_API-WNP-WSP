/**************************************************************

	[ exception Ŭ���� ]
	
	exception ��� ���Ͽ� ����Ǿ� �ִ�.
	�ٸ� ���� Ŭ�������� �⺻ Ŭ������ ���ȴ�.
	what() �̶�� ����(virtual function) �Լ��� �־�����. 
	�� �Լ��� �̿��Ͽ� ��ȯ�� ���ڿ��� ������ �� �� �ִ�.

**************************************************************/

//[����1] �տ��� �� ESize Ŭ������ exception Ŭ������ �Ļ� Ŭ������
//       �����ϰ� ����Ͽ���.
/*
#include <iostream.h>
#include <exception>  //exception ������� ����


class ESize : public exception
{
	int index;
public:
	ESize(int i):index(i){}
	const char* what() {return "[Out of Range]" ;}
	//���� �Լ� what()�� ������ �Ͽ� ���ڿ��� �����Ͽ���.
};


class Array
{
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
    if (i < 0 || i >= size)  throw ESize(i); 
    return arr[i];
}

const int& Array::operator[](int i) const
{
    if (i < 0 || i >= size)  throw ESize(i);
        return arr[i];
}

int main(void)
{
    try
	{
        Array mydata(3);

        for (int i=0; i<3; i++)
            mydata[i] = i*10;

        for (i=0; i<4; i++)
            cout << mydata[i] << endl;
    }

    catch(ESize &err)
    {	
        cout << "## Exception ##\t" << err.what() << endl;
    }

    return 0;
}
*/




