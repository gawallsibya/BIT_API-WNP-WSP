#include <iostream>
using namespace std;


// c++���� �⺻������ exception Ŭ������ �ִ�.
// exception Ŭ������ ��¹޾� ����ϴ� ���� ����.
class MyException : public exception
{
public:
	// ���ÿ��� what() �Լ��� ���������ش�. 
	// �θ� virtual �̹Ƿ� virtual �� �������Ѵ�.
	virtual const char* what()const throw()
	{  
		return "MyException";
	}
};


void foo() throw(exception*)
{
	throw new MyException;
}


void main()
{
	try{
		foo();
	}
	catch(exception* p)
	{
		cout << p->what() << endl;
		delete p;
	}
}
