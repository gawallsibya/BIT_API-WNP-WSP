/*
//��������������������������������������������������������������������������
	����(exception)
//��������������������������������������������������������������������������
*/

//int arr[10];
//arr[100] = 10;

/*
class String
{
	char *s;
public:
	String()		// ������ : ��ü�� ������ �� ȣ�� 
	{
		s = new char[10];
	}
	~String()		// �Ҹ��� : ��ü�� �Ҹ�� �� ȣ�� 
	{
		delete [] s;
	}
	char  operator [] ( int n )
	{
		return s[n];
	}
};

String str;				// ��ü ���� 
char ch = str[10] ;		// str.operator[](10);
*/


char String::operation[] (int i) const
{
	if((1 >=0) && (i < length))
		return buffer[i];
	// �Ű������� �Ѿ�� ÷�ڰ� ���ڿ��� ���� ������ �Ѿ��� 0��° �迭 ��Ҹ� ��ȯ
	// ������ ���ϴ� �κ� 
	else
		return buffer[0];
}

// 1. ���α׷� ����
char String::operation[] (int i) const
{
	if((1 >=0) && (i < length))
		return buffer[i];
	exit(-1);
}


// 2. ������ ��Ÿ���� �� ��ȯ
char String::operation[] (int i) const
{
	if((1 >=0) && (i < length))
		return buffer[i];
	else
		return -1;
}

// 3. ������ �߻������� �˸��� ���� ��ȯ�ϰ� ���α׷��� ���� ���¸� 
//    �״�� ���ܵд�.
  char String::operation[] (int i) const
{
	if((1 >=0) && (i < length))
		return buffer[i];
	else
	{
		errno = -1;
    	return buffer[i];
	}
}



// 4. ������ �߻��� �� ����ϵ��� �����Ǵ� �Լ��� ȣ���Ѵ�.
  void SetError(int errno)
  {
	switch(errno)
	{
		case = -1;
			cout << "Use a correct subscript!!\n;
			break;
			...
	}
  }

  char String::operation[] (int i) const
{
	if((1 >=0) && (i < length))
		return buffer[i];
	SetError(-1);
}


