/***************************************************************

  Windows���� ȣȯ���� ���� 100�� ����� ���� ���� API�� ������ 

  �⺻�� �Ǵ� ���� ������ ����, �б�, ����, �ݱ� ó���� �ϴ�
  API�̴�.

  �̴� ǥ�� C���̺귯�� �Լ��� fopen, fread, fwrite, fclose�� 
  �ش�ȴ�.

***************************************************************/

//---------------------------------------------------
//  CreateFile API�� ���� ����
//---------------------------------------------------

/*

  ���     API			�ش� ���̺귯�� �Լ�
  --------------------------------------------------
  ����  CreateFile		fopen
  �б�	ReadFile		fread
  ����	WriteFile		fwrite
  �ݱ�	CloseHandle		fclose
  --------------------------------------------------


  CreateFile ���ڿ� ��ȯ��

  HANDLE CreateFile(			// ��ȯ��:���� �ڵ�
   LPCTSTR lpFileName,			// ���ϸ�
   DWORD dwDesiredAccess,		// ���� ���
   DWORD dwShareMode,			// ��Ÿ�� ���� ����
   LPSECURITY_ATTRIBUTES lpSA	// ����
   DWORD dwCreationDisposition,	// ���� ���
   DWORD dwFlagsAndAttributes,	// ���� �Ӽ� �÷���(���� ��� ����)
   HANDLE hTemplateFile			// ���ø� ���� �ڵ�(���� NULL���)
   );

   ���ٸ�� : �б�(GENERIC_READ)/����(GENERIC_WRITE)

   ���¹�� : CREATE_NEW		- �ű����� ����,���� ��������ÿ���
			  CREATE_ALWAYS		- ���� ���� ����� ���� ���� �����
								  �׻� ����
			  OPEN_EXISTING		- ���� ���� ����, ������ ����
			  OPEN_ALWAYS		- ���� ���� ����, ������ ����
			  TRUNCATE_EXISTING	- ���� ���� ����, ���� ���� ����

*/

