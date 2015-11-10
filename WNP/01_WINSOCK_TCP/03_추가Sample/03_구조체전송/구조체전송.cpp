#include <stdio.h>
#include <string.h>

typedef struct _tagMyChar{
	int		iDataSize;
	char	*pData;
}MyChar;

int main()
{
	MyChar	myChar;
	char	*ptr = new char[5];
	strcpy(ptr, "test");

	myChar.iDataSize	= strlen(ptr);
	myChar.pData		= ptr;

	printf("%d %s\n", myChar.iDataSize, myChar.pData);
	return 1;
}

// ������ �̿��� ������ ���۽� ������ ��
/*

1. ������ ��
	ret = send(socket, &myChar, sizeof(myChar), 0);
2. �޴� �� 
	ret	= recv(socket, &myChar, sizeof(myChar), 0);

	1) myChar.pData : ������ ������.. ���� pData�� �����ϴ� ���� ���� 
					  �޸𸮿� �ִ� ��Ʈ���� �ּҰ� �ȴ�. 
					  ���� �� �ּҸ� Ŭ���̾�Ʈ���� ����� ���� ���� 
					  ���Ұ���...
					  ������ �߸��� �޸� �ּҸ� �о ���� �߻�...

	2) ���۵����� ũ�� : myChar ����ü�� ũ�� �� int �� 4byte char ������ 
	                     �� 4byte �� 8byte ����
						�׷��� ���� 8byte�̻��� �����͸� �ִ´ٸ�???

3. ���� �ùٸ� ���� �����..
	1) �����͸� ���� �ʴ´�. --> �迭 ���

	typedef struct _tagMyChar{
		int		iDataSize;
		char	pData[28];
	}MyChar;
	

    2) �����͸� ����� ������. 
	   ������ ���ؼ� �׻� �� 4byte�� ������ ũ�⸦ ��Ÿ���ٰ� �ϰ�
	   ������ ���� �ڵ� �ۼ� 
	- ������ �� :
		myChar.iDataSize = strlen(myChar.pData);
		ret = send(socket, &myChar.iDataSize, sizeof(int),0);
		ret = send(socket, myChar.pData, myChar.iDataSize, 0);

   - �޴� �� :
		ret = recv(socket, &myChar.iDataSize, sizeof(int),0);
		myChar.pData = new char[myChar.iDataSize+1];
		ret	= recv(socket, myChar.pData, myChar.iDataSize, 0);
		myChar.pData[ret] = 0;

  */


/*
TCP ������ Ư��

  1. �������� ������ ����..
  2. ����� ���ļ� �ް� �Ǵ����� ������ ����..
     ������ ���۽� �� 2300byte ���� : 1000/500/800
	 ������ ���Ž� �� 2300byte ���� : 1100/300/800/100
*/