/*****************************************************************************
[ �ܼ��� �̿��� ���� ������ ]
  - ������ API�� ����Ͽ� ���콺 �Է� ó��  

  �ַܼκ��� ������ ����� �Է��� �ϴ� �Է� ���ۿ� ����ȴ�.
  �Է� ���۴� ����ڰ� Ű������ Ű�� �����ų� ���� Ȥ�� ���콺 �����͸� �ű�� ���� 
  �̺�Ʈ ������ ���� �����ϴ� INPUT_RECORD ����ü�� �����ϴ� ť��.
  �ܼ� �Է¿� API�� ����ؼ� �Է� ���ۿ��� �̺�Ʈ�� ���� ����� �Է��� ó���Ѵ�.

  �ܼ� �Է¿� API�� ����ذ� ���������� ������.
  ReadFile(�����API) : C/C++���̺귯�� �Լ��� ���� ����
                        �� ���콺 �Է��� ���õ�
  
  ReadConsoleInput(������ API) : �Է� ���۷κ��� �̺�Ʈ�� INPUT_RECORD ����ü 
                                ���·� ���� �� �ִ�.
   ���ڿ� �Է� ó���ÿ��� ����ġ��, ���콺 ������ �̿��� �� �ִ� ������ ������.
   �⺻���� ���콺 �Է��� ���� �ʴ� �����̹Ƿ� SetConsoleMode API�� ����� �Է� 
   ���� ������ �ʿ��ϴ�.


�����ڵ�)
   ���� ���� ������ 
   Ŀ�� Ű�� ���콺 Ŀ���� ��ġ�� �Űܼ� �װ��� ���ڸ� �Է��� �� �ֽ�
   ESC Ű�� ������ ���α׷��� ����Ǹ� �׶����� �Է��� ������ 'edit.txt' ���Ͽ� �����ϰ� ��
   2byte ���� �Է��� �����ϳ�, Ŀ�� �̵��ô� ȭ��ǥŰ�� �ι� ������ ��
********************************************************************************/

#pragma comment(linker, "/subsystem:console")

#include <windows.h>
#include <stdio.h>

int main()
{
	HANDLE				hIn, hOut, hOrig;
	INPUT_RECORD		ir;
	DWORD				mode;
	BOOL				bCont = TRUE;

	CONSOLE_SCREEN_BUFFER_INFO	csbi;
	CONSOLE_CURSOR_INFO			cci;
	COORD						csr;

	unsigned char		ch;
	DWORD				sz;
	FILE				*fp;

	// �Է� ���� �ڵ� ���
	hIn = CreateFile("CONIN$", GENERIC_READ|GENERIC_WRITE,
		FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, 0);

	if( hIn == INVALID_HANDLE_VALUE)
	{
		fprintf(stderr, "�Է� ���� �ڵ� ��� ����\n");
		return -1;
	}

	// ��ũ�� ���� �ڵ� ���
	hOrig = CreateFile("CONOUT$",  GENERIC_READ|GENERIC_WRITE,
		FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, 0); 

	if( hOrig == INVALID_HANDLE_VALUE)
	{
		fprintf(stderr, "��ũ�� ���� �ڵ� ��� ����\n");
		return -1;
	}

	// ���ο� ��ũ�� ���۸� ���� Ȱ��ȭ
	hOut = CreateConsoleScreenBuffer(GENERIC_READ|GENERIC_WRITE, 0, NULL,
		CONSOLE_TEXTMODE_BUFFER, NULL);
	if( hOut == INVALID_HANDLE_VALUE)
	{
		fprintf(stderr, "��ũ�� ���� ���� ����\n");
		CloseHandle(hOrig);
		CloseHandle(hIn);
		return -1;
	}
	// Ȱ�� ��ũ�� ���� ���� 
	SetConsoleActiveScreenBuffer(hOut);


	// ������ ���� ����
	SetConsoleTitle("���� ������(ESC�� ����)");


	// ���콺 �Է��� �ޱ� ���� �Է� ��� ����
	GetConsoleMode(hIn, &mode);
	SetConsoleMode(hIn, mode | ENABLE_MOUSE_INPUT);

	// Ŀ���� ũ�⸦ ���� ���� ������
	cci.dwSize		= 100;
	cci.bVisible	= TRUE;

	SetConsoleCursorInfo(hOut, &cci);


	// �Է� ó�� ����
	while( bCont )
	{
		// �Է� ó�� �̺�Ʈ �ϳ� �б�
		if( ReadConsoleInput(hIn, &ir, 1, &sz))
		{
			// ���� Ŀ���� ��ġ ���
			GetConsoleScreenBufferInfo(hOut, &csbi);
			csr.X	= csbi.dwCursorPosition.X;
			csr.Y	= csbi.dwCursorPosition.Y;

			// Ű���� �Է�
			if( ir.EventType == KEY_EVENT)
			{
				// ������ �̺�Ʈ�� ó��
				if( ir.Event.KeyEvent.bKeyDown )
				{
					switch(ir.Event.KeyEvent.wVirtualKeyCode)
					{
						// ESC �̸� ����
					case VK_ESCAPE:	bCont	= FALSE;	break;

						// ȭ��ǥŰ�� Ŀ�� �̵�
					case VK_RIGHT:
						if( csr.X < csbi.dwSize.X -1 )
						{
							csr.X++;
							SetConsoleCursorPosition(hOut, csr);
						}
						break;
					case VK_LEFT:
						if( csr.X < csbi.dwSize.X -1 )
						{
							csr.X--;
							SetConsoleCursorPosition(hOut, csr);
						}
						break;
					case VK_UP:
						if( csr.Y < csbi.dwSize.Y -1 )
						{
							csr.Y--;
							SetConsoleCursorPosition(hOut, csr);
						}
						break;
					case VK_DOWN:
						if( csr.Y < csbi.dwSize.Y -1 )
						{
							csr.Y--;
							SetConsoleCursorPosition(hOut, csr);
						}
						break;
					case VK_RETURN:
						if( csr.Y	< csbi.dwSize.Y-1)
						{
							csr.X	= 0;
							csr.Y++;
							SetConsoleCursorPosition(hOut, csr);
						}
						break;

					default:
						// ��ȿ�� ���ڶ�� Ŀ�� ��ġ�� ���
						ch = (unsigned char)ir.Event.KeyEvent.uChar.AsciiChar;

						if( ch >= 0x20 )
						{
							WriteFile(hOut, &ir.Event.KeyEvent.uChar.AsciiChar, 1, &sz, NULL);
						}


					}
				}
			}
			else if(ir.EventType	== MOUSE_EVENT)
			{
				// ��ư�� ���������� Ŀ�� �̵�
				if( ir.Event.MouseEvent.dwButtonState	& 0x01)
				{
					SetConsoleCursorPosition(hOut, ir.Event.MouseEvent.dwMousePosition);
				}
			}
		}
	}

	SetConsoleActiveScreenBuffer(hOrig);
	CloseHandle(hOrig);
	CloseHandle(hIn);

	// ��ũ�� ������ ������ ���Ͽ� ����
	//....

	CloseHandle(hOut);

	return 0;


}


