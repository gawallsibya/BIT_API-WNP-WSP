#include <windows.h>
#include <stdio.h>

void main()
{
	PROCESS_INFORMATION pi = { 0 };
	STARTUPINFO si = { 0 };
	si.cb = sizeof( si );

	BOOL b = CreateProcess( 0,				// app name
							"freecell.exe", // app name + commandline args
							0, 0,			// pko, tko ����
							FALSE,			// KOHT �� ��ӿ���
							NORMAL_PRIORITY_CLASS, // �켱���� | �÷���
							0, 0,			// ȯ�溯��, ���� ���丮
							&si,			// startup info ����
							&pi);	// ������ ���μ���, �������� �ڵ�� ID
									// �� ���� ����.
	if ( b )
	{
		// �ڽ��� �ڵ��� �ݴ� ������ �ݵ�� �˾ƾ� �Ѵ�.
		// �ڽ��� �ڵ��� ���� ������ �ڽ��� ���� �Ǿ.. 
		// �ڽ��� �����ϴ�
		// PKO, TKO �� �ı� ���� �ʰ� �ִٰ� (�������� 1) 
		// �θ� �ڽ���
		// �ڵ��� �ݰų� �θ�����(�ڵ����� �ڵ� ����)�Ǿ߸� 
		// PKO, TKO �ı��ȴ�.
//		CloseHandle( pi.hProcess); //�ڵ��� �ʿ��� ���� ���� �ʾƾ� �Ѵ�.
//		CloseHandle( pi.hThread);
	}
	int cmd;
	while ( 1 )
	{
		scanf("%d", &cmd );

		if ( cmd == 2 )
		{
			// ���μ��� ������ ���� �ϱ�
			TerminateProcess( pi.hProcess, 100); // 100�� ���� �ڵ�

			// TerminateProcess�� �񵿱� �Լ� �̴�. ��.. �� ���� 
			// ������ �׾��ٰ� �����Ҽ��� ����.

			// ��� ���μ����� ������ PKO �� Signal �ȴ�.

			// Ư�� KO �� �ñ׳� �ɶ����� ���� �����帧(������)�� ��� ��Ų��.

			WaitForSingleObject( pi.hProcess, INFINITE );


			// ���� ������ �ڽ� ���μ����� �׾���.

			cmd = 1; // ?
		}




		//============================================================
		if ( cmd == 1 )
		{
			DWORD code;
			GetExitCodeProcess( pi.hProcess, &code ); // ���μ����� ���� �ڵ���
			
			if ( code == STILL_ACTIVE ) // 0x103 ���� ���ǵ� ���.
			{
				printf("���� �ڽ��� ��� �ֽ��ϴ�.\n");
			}
			else
			{
				printf("�ڽ� ���� : %d\n", code );
				CloseHandle( pi.hProcess );  // �ڽ��� ���� �Ǿ����Ƿ�
									// �ڵ��� �ݾƼ� PKO �� �ı� �ǵ��� �Ѵ�.
			}
		}
	}
}











