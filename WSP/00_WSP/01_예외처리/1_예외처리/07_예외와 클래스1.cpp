/**************************************************************

	[ ���ܿ� Ŭ���� ]


	�������� ���� Ŭ���� ����

	Ư�� ��ü�� ���õǾ�� �߻��ϴ� ���ܰ� �ƴϸ� �������� 
	�����Ͽ��� ����.
 

    ex)

	class ERange {......};    //out of Range Exception
	class ESize {......};   //bad Size Exception

	class Vector
	{
			int size;
	public:
			//......
	};
	void f()
	{
		try { use_vector(); }
		catch (ERange) {......}
		catch (ESize) {......}
	}

**************************************************************/


#include <iostream.h>


class ESize
{
	int index;
public:
	ESize(int i):index(i){}
	void print() const
	{
		cout << "Out of Range : " << index << endl;
	}

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
    if (i < 0 || i >= size)  throw ESize(i); //ESize ���� �߻� 
    return arr[i];
}

const int& Array::operator[](int i) const
{
    if (i < 0 || i >= size)  throw ESize(i); //ESize ���� �߻� 
    return arr[i];
}


int main(void)
{
    try
	{
		Array mydata(3); //�迭 ����� 3���� ������

		for (int i=0; i<3; i++)  mydata[i] = i*10;

		for (i=0; i<=3; i++) //i=3�̸� ������ �ʰ��ϰ� �ȴ�.
			cout << mydata[i] << endl;
    }

    catch(ESize &err) //ESize ���� ó�� 
    {
		cout << "## Exception ##\t" ;
		err.print();
    }

	cout << "��� ����" << endl;

    return 0;
}
