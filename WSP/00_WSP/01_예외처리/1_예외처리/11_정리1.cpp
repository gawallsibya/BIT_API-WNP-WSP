//----------------
// Sample 1
//----------------


// SMART POINTER
/*
#include <iostream>
using namespace std;

class Test
{
	int x;
public:
	~Test() { cout << "Test::~Test" << endl; }
	void foo() { cout << "Test::Foo" << endl; }

};

// ����Ʈ ������ : �ٸ� ��ü�� ������ ����
template<typename T> class SPTR
{
	T *_t;
public:
	SPTR( T *t) : _t(t) {}
	~SPTR()				{ delete _t; }
	T* operator->()     { return _t; }
	T & operator*()     { return *_t;}
};

void main()
{
	SPTR<Test> p(new Test);

	p->foo();

//	delete p;
}
*/


/*
#include <memory>
// memory ��� ���� include �ϸ�
// auto_ptr �� ����Ҽ� ����. smart pointer ��� ����


class Test
{
public:
	Test()		{ cout << "Test" << endl;  }
	~Test()		{ cout << "~Test" << endl; }
	void goo()	{cout << "goo" << endl;    }
};

void foo()
{
//	auto_ptr<Test> p(new Test[100]); // error
	// auto_ptr�� �ݵ�� ��ü�� ��밡���ϴ�.
//	auto_ptr<Test> p = new Test; // explict constructor�̹Ƿ� error
	// �� ��ȯ�� �Ұ����ϴ�. �����ϰ� �Ʒ��� ���� ����

	auto_ptr<Test> p(new Test); // smart pointer..
	p->goo(); 
	throw "exception";
//  delete p; // error 
}


void main()
{
	try
	{
		foo();		
	}
	catch(char* msg)
	{	
		cout << msg << endl;		
	}
}
*/


//(ex) ���� ó�� : ����� ������ ó���ϴ� ǥ������ ���
/*
#include <iostream>		
using namespace std;

#define ERRROR   -1		
#define SUCCEEDED 0


int errorCode;
void SetErrrorCode(int a){		errorCode = a;		}

int GetErrorCode(){		return errorCode;		}

int foo()
{
	int *p = new int[1000];
	if(p==0)
	{
		SetErrrorCode(1);		
		return ERRROR;		
	}
	return SUCCEEDED;
}


void main()
{
	if(foo() == ERRROR)
	{
		int error = GetErrorCode();   
		cout << "error : " << error << endl;	
	}
}

*/


/*
// ex3)	ó�� ���� ���� ���� �߻�
#include <iostream>		
using namespace std;


void myHandler()
{
	cout << "ó�� ���� ���� ���� �߻�" << endl;	
	exit(-1);	
}


void foo() throw(int, char*)
{
	if (1) throw 1; 		
	if (2) throw "a";	
	throw new string("aa");
}

void main()
{
	// set_unexpected() �� ����ġ ���� ��� �߻� ó���ϴ� �Լ�
	// set_terminate() ó������ ���� ���ܸ� ó���ϴ� �Լ�	

//	set_terminate(myHandler); // ó�� ���� ���� ���� �߻���
	// set_terminate() �Լ��� ����Ͽ� myHandler()�θ� 
	try
	{		
		foo();		
	} 
	catch(char* a)
	{		
		cout << a << endl;		
	}
	// throw �� char�� catch ���� ���ϸ� �� ����  
	//abort()�� ȣ��ǰ� ���α׷��� ����ȴ�. 

//	catch(...)
//	{ // ... catch�� �ݵ�� �� �ؿ� �־�� �Ѵ�.
		
//	}
}
*/