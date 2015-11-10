#pragma comment(linker, "/subsystem:windows")

#define _WIN32_WINNT 0x0500 // win2000 �� �Լ��� �޽����� ����ϱ� ����
#define WINVER	0x0500 // win98 �� �Լ��� �޽����� ����ϱ� ����

#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include "resource.h"

//��ü �׸���� �ߴµ�, �Ϻθ� �׷����°� ����.
//�׷��ٸ� �װ� ��� �˰� �Ϻθ� �׸��°�.
#define EMPTY 0
#define ONE	1
#define TWO 2
#define THREE 3
#define FOUR 4
#define FIVE 5
#define SIX 6
#define SEVEN 7
#define EIGHT 8
#define BOMB 99

#define CLOSE 0
#define OPEN 1
#define QUESTION 2
#define FLAG 3
#define NONFOUNDMINE 4
#define ERRORCHECKMINE 5

#define START 4
#define NORMAL 5
#define WIN 6
#define LOSE 7
#define MINE_WIDTH 16
#define MINE_HEIGHT 16
#define BOARD_SIZE 9
#define KILL 100
#define MINE_NUM 10

#define PICFLAG	16
#define PICQUESTION 16*2
#define PICREDMINE	16*3
#define PICXMINE	16*4
#define PICBLACKMINE	16*5

typedef struct _BLOCK
{
	int state;
	char isOpen;
} BLOCK;

BLOCK g_board[BOARD_SIZE][BOARD_SIZE];
int GAMESTATE = NORMAL;
int chooseMineNum;
int foundMineNum;
int blockMove;
int RButtonDown;
int LButtonDown;

void InitMine(HWND hwnd)
{
	// ���� ���� �ʱ�ȭ
	GAMESTATE = START;
	// ����ڰ� ������ ���� ���� �ʱ�ȭ
	chooseMineNum = 0;
	// ���� ã���� ���� ���� �ʱ�ȭ
	foundMineNum = 0;
	blockMove = 0;
	RButtonDown = 0;
	LButtonDown = 0;

	int i, j, x, y;
		
	// ���� �ʱ�ȭ.
	for(i=0; i < BOARD_SIZE; i++)
	{
		for(j=0; j < BOARD_SIZE; j++)
		{
			g_board[i][j].isOpen = CLOSE;
			g_board[i][j].state = EMPTY;
		}
	}

	// ��ź�� �����ϰ� ��ġ�ϰ� state �׸��� �ʱ�ȭ�Ѵ�.
	srand(time(NULL));
	
	for(int count = 0; count < MINE_NUM;)
	{
		i = rand() % 9;
		j = rand() % 9;
	
		if(g_board[i][j].state != BOMB)
		{
			g_board[i][j].state = BOMB;
			++count;

			// ���� �ֺ��� ���� ����
			for(x = max(0, i - 1); x <= min(BOARD_SIZE-1, i + 1); x++)
			{
				for(y = max(0, j - 1); y <= min(BOARD_SIZE-1, j + 1); y++)
				{
					if(g_board[x][y].state != BOMB)
					{
						++g_board[x][y].state;
					}
				}
			}
		}
	}
}

void LButtonClick(HWND hwnd, int x, int y)
{
	if((x < 0 || y < 0 || x >= BOARD_SIZE || y >= BOARD_SIZE) && (x+y) != KILL)	return;

	// �̹� �����ų� ���õ� ��ġ��� �׳� ����
	if(g_board[x][y].isOpen != CLOSE)	return;

	g_board[x][y].isOpen = OPEN;

	// ���ڸ� ���� �Ŷ��
	if(g_board[x][y].state == BOMB || (x+y == KILL))
	{
		GAMESTATE = LOSE;// ���ӿ� ������ ����

		//��� ���� �����ֱ�.
		InvalidateRect(hwnd, 0, FALSE);
		UpdateWindow(hwnd);
		

		if(MessageBox(hwnd, "���ڸ� ��ҽ��ϴ�.\n\n�ٽ� ������ �����ϰڽ��ϱ�?", "����ã��", MB_YESNO) == IDYES)
		{
			InitMine(hwnd);
			InvalidateRect(hwnd, 0, FALSE);
			UpdateWindow(hwnd);
		}

		return;
	}

	// EMPTY ���� Ŭ���� ��� �̾��� EMPTY �� ��� �����ֱ�.
	if(g_board[x][y].state == EMPTY)
	{
		for(int i = max(0, x-1); i <= min(BOARD_SIZE-1, x+1); i++)
		{
			for(int j = max(0, y-1); j <= min(BOARD_SIZE-1, y+1); j++)
			{
				LButtonClick(hwnd, i, j);
			}
		}
	}

	// ���� Ŭ�� ��ġ �ٽ� �׸���
	RECT rect;
	rect.left	= 12 + MINE_WIDTH * x;
	rect.top	= 55 + MINE_HEIGHT * y;
	rect.right	= rect.left + MINE_WIDTH;
	rect.bottom	= rect.top + MINE_HEIGHT;

	InvalidateRect(hwnd, &rect, FALSE);
	
}

void RButtonClick(HWND hwnd, int x, int y)
{
	int i, j;

	if(x < 0 || y < 0 || x >= BOARD_SIZE || y >= BOARD_SIZE)	return;

	if(g_board[x][y].isOpen == OPEN)	return;		// �̹� ���� ��ġ��� �׳� ����
	else if(g_board[x][y].isOpen == FLAG) 	// �̹� ���ڷ� ���õ� ��ġ���
	{
		// ����ǥ ��ȣ�� �ٲ۴�.
		g_board[x][y].isOpen = QUESTION; 
		// ���� ������ ���δ�
		--chooseMineNum;
		// ã�� ������ ���δ�
		if(g_board[x][y].state == BOMB)	--foundMineNum;
	}
	else if(g_board[x][y].isOpen == QUESTION)	// ����ǥ ǥ�� ����
		g_board[x][y].isOpen = CLOSE;
	else	// ���� ���¸�, �����÷��� ����
	{
		g_board[x][y].isOpen = FLAG;
		// ���� ������ ���� �߰�
		++chooseMineNum;
		// ���� �ִ� ���� ���������� ã�� ���ڰ��� �߰�
		if(g_board[x][y].state == BOMB)	++foundMineNum;
	}

	// ���� Ŭ�� ��ġ �ٽ� �׸���
	RECT rect;
	rect.left	= 12 + MINE_WIDTH * x;
	rect.top	= 55 + MINE_HEIGHT * y;
	rect.right	= rect.left + MINE_WIDTH;
	rect.bottom	= rect.top + MINE_HEIGHT;

	InvalidateRect(hwnd, &rect, FALSE);

	// ���� ã�� ���� ������ 10�����
	if(foundMineNum == MINE_NUM)
	{
		for(i=0; i<BOARD_SIZE; i++)
		{
			for(j=0; j<BOARD_SIZE; j++)
				if(g_board[i][j].isOpen == CLOSE) return;
		}
		// ���ӿ��� �̰����� �����Ѵ�
		GAMESTATE = WIN;
		InvalidateRect(hwnd, NULL, TRUE);

		if(MessageBox(hwnd, "����ã�� �¸�!\n\n�ٽ� ������ �����ϰڽ��ϱ�?",
			"����ã��", MB_YESNO) == IDYES)
		{
			InitMine(hwnd);
			InvalidateRect(hwnd, NULL, FALSE);
		}
	}
}

void CheckGameEnd(HWND hwnd)
{
	// ���ڸ� ���Ҵ��� Ȯ��. ��� ���� ���� ���ڰ� �ƴϸ� �׳� ����.
	for(int i = 0; i < BOARD_SIZE; i++)
	{
		for(int j = 0; j < BOARD_SIZE; j++)
		{
			if(g_board[i][j].isOpen == CLOSE && g_board[i][j].state != BOMB)	return;
		}
	}

	// ������ ���� ���ڵ��� ���ڷ� ������ ��ó�� �ٲ�
	for(i = 0; i < BOARD_SIZE; i++)
	{
		for(int j = 0; j < BOARD_SIZE; j++)
			if(g_board[i][j].isOpen == CLOSE)	g_board[i][j].isOpen = FLAG;
	}

	// ���ӿ��� �̰����� �����Ѵ�
	GAMESTATE = WIN;
	InvalidateRect(hwnd, 0, TRUE);

	if(MessageBox(hwnd, "����ã�� �¸�!\n\n�ٽ� ������ �����ϰڽ��ϱ�?",
		"����ã��", MB_YESNO) == IDYES)
	{
		InitMine(hwnd);
		InvalidateRect(hwnd, 0, TRUE);
	}
}

void Draw3dRect(HDC hdc, int x, int y, int xx, int yy, BOOL down, int width)
{
	COLORREF clrMain = RGB(192, 192, 192),
			 clrLight = RGB(255, 255, 255),
			 clrDark = RGB(128, 128, 128);
	
	HPEN hPen1, hPen2, hOldPen;
	HBRUSH hBrush, hOldBrush;

	if(down)
	{
		hPen2 = CreatePen(PS_SOLID, 1, clrLight);
		hPen1 = CreatePen(PS_SOLID, 1, clrDark);
	}
	else
	{
		hPen1 = CreatePen(PS_SOLID, 1, clrLight);
		hPen2 = CreatePen(PS_SOLID, 1, clrDark);
	}

	hBrush = CreateSolidBrush(clrMain);
	hOldPen = (HPEN)SelectObject(hdc, hPen1); // DC�� ���� ���� ����Ѵ�.
	hOldBrush = (HBRUSH)SelectObject(hdc, hBrush); // DC�� ���� �귯���� ����Ѵ�.

	Rectangle(hdc, x, y, xx+1, yy+1);
	
	for(int i=0; i < width; i++)
	{
		SelectObject(hdc, hPen1);

		MoveToEx(hdc, xx - 1, y, 0);
		LineTo(hdc, x, y);
		LineTo(hdc, x, yy-1);

		SelectObject(hdc, hPen2);
		
		MoveToEx(hdc, x, yy, 0);
		LineTo(hdc, xx, yy);
		LineTo(hdc, xx, y);

		x++; ;y++; xx--; yy--;
	}

	SelectObject(hdc, hOldPen);
	SelectObject(hdc, hOldBrush);

	DeleteObject(hPen1);
	DeleteObject(hPen2);
	DeleteObject(hBrush);
}


LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HINSTANCE hInstance;
	static HBITMAP mybit;
	static POINTS pt = {0, 0};
	HDC    hdc, MemDC;
	PAINTSTRUCT  ps;
	static RECT rect;
		
	switch( msg )
	{	
	
	case WM_CREATE:
		{
			hInstance = ((LPCREATESTRUCT) lParam)->hInstance;
			mybit = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP1));
			InitMine(hwnd);
		}
		return 0;

	case WM_PAINT:
		{			
			hdc = BeginPaint(hwnd, &ps);
			MemDC= CreateCompatibleDC(hdc);
			SelectObject(MemDC, mybit);

			int x =  (pt.x-12) / MINE_WIDTH;
			int y =  (pt.y-55) / MINE_HEIGHT;

			Draw3dRect(hdc, 0, 0, 168, 211, FALSE, 3);
			Draw3dRect(hdc, 9, 9, 156, 46, TRUE, 2);
			Draw3dRect(hdc, 15, 14, 57, 40, TRUE, 1);
			Draw3dRect(hdc, 109, 14, 150, 40, TRUE, 1);
			Draw3dRect(hdc, 9, 52, 159, 202, TRUE, 3);

			for(int i = 0; i < BOARD_SIZE; i++)
			{
				for(int j = 0; j < BOARD_SIZE; j++)
				{
					if(GAMESTATE == WIN || GAMESTATE == LOSE) // ������ �����ٸ�
					{
						// ������ �ִ� ��ġ���
						if(g_board[i][j].state == BOMB)
						{
							switch(g_board[i][j].isOpen)
							{
							case CLOSE:
								// ���� ����
								BitBlt(hdc, i*MINE_WIDTH + 12, j*MINE_HEIGHT +55, MINE_WIDTH, MINE_HEIGHT, MemDC, 0, PICBLACKMINE, SRCCOPY);
								break;
							case OPEN:
								// ���� ����
								BitBlt(hdc, i*MINE_WIDTH + 12, j*MINE_HEIGHT +55, MINE_WIDTH, MINE_HEIGHT, MemDC, 0, PICREDMINE, SRCCOPY);
								break;
							case FLAG:
								// ��� �׸�
								BitBlt(hdc, i*MINE_WIDTH + 12, j*MINE_HEIGHT +55, MINE_WIDTH, MINE_HEIGHT, MemDC, 0, PICFLAG, SRCCOPY);
								break;
							case QUESTION:
								// ����ǥ �׸�
								BitBlt(hdc, i*MINE_WIDTH + 12, j*MINE_HEIGHT +55, MINE_WIDTH, MINE_HEIGHT, MemDC, 0, PICQUESTION, SRCCOPY);
								break;
							case NONFOUNDMINE:
								// ������ ����
								BitBlt(hdc, i*MINE_WIDTH + 12, j*MINE_HEIGHT +55, MINE_WIDTH, MINE_HEIGHT, MemDC, 0, PICREDMINE, SRCCOPY);
								break;
							}
						}
						else
						{
							switch(g_board[i][j].isOpen)
							{
							case CLOSE:
								BitBlt(hdc, i*MINE_WIDTH + 12, j*MINE_HEIGHT +55, MINE_WIDTH, MINE_HEIGHT, MemDC, 0, 0, SRCCOPY);
								break;
							case OPEN :
								BitBlt(hdc, i*MINE_WIDTH + 12, j*MINE_HEIGHT +55, MINE_WIDTH, MINE_HEIGHT, MemDC, 0, (16*15)-g_board[i][j].state*16, SRCCOPY);
								break;
							case FLAG:
								// X ǥ��
								BitBlt(hdc, i*MINE_WIDTH + 12, j*MINE_HEIGHT +55, MINE_WIDTH, MINE_HEIGHT, MemDC, 0, PICXMINE, SRCCOPY);
								break;
							case QUESTION:
								// ����ǥ �׸�
								BitBlt(hdc, i*MINE_WIDTH + 12, j*MINE_HEIGHT +55, MINE_WIDTH, MINE_HEIGHT, MemDC, 0, PICQUESTION, SRCCOPY);
								break;
							case ERRORCHECKMINE:
								// ���ڷ� �߸� ������ ��
								BitBlt(hdc, i*MINE_WIDTH + 12, j*MINE_HEIGHT +55, MINE_WIDTH, MINE_HEIGHT, MemDC, 0, PICXMINE, SRCCOPY);
								break;
							}
							
						}	
					}
					else
					{
						switch(g_board[i][j].isOpen)
						{
							case CLOSE: 								
								// �⺻ ��
								if(LButtonDown && !blockMove)	BitBlt(hdc, i*MINE_WIDTH + 12, j*MINE_HEIGHT +55, MINE_WIDTH, MINE_HEIGHT, MemDC, 0, 16*15, SRCCOPY);
								else BitBlt(hdc, i*MINE_WIDTH + 12, j*MINE_HEIGHT +55, MINE_WIDTH, MINE_HEIGHT, MemDC, 0, 0, SRCCOPY);
								break;
							case OPEN:
								// ����
								BitBlt(hdc, i*MINE_WIDTH + 12, j*MINE_HEIGHT +55, MINE_WIDTH, MINE_HEIGHT, MemDC, 0, (16*15)-g_board[i][j].state*16, SRCCOPY);
								break;
							case FLAG:
								// ��� �׸�
								BitBlt(hdc, i*MINE_WIDTH + 12, j*MINE_HEIGHT +55, MINE_WIDTH, MINE_HEIGHT, MemDC, 0, PICFLAG, SRCCOPY);
								break;
							case QUESTION:
								// ����ǥ �׸�
								BitBlt(hdc, i*MINE_WIDTH + 12, j*MINE_HEIGHT +55, MINE_WIDTH, MINE_HEIGHT, MemDC, 0, PICQUESTION, SRCCOPY);
								break;
						}
					}

					
					
				}
			}

			DeleteDC(MemDC);
			EndPaint(hwnd, &ps);
					
		}
		return 0;
	case WM_MOUSEMOVE:
		{
			if(LButtonDown)
			{
				int x =  (pt.x-12) / MINE_WIDTH;
				int y =  (pt.y-55) / MINE_HEIGHT;
				int tempx = x;
				int tempy = y;
		
				pt = MAKEPOINTS(lParam);
				x =  (pt.x-12) / MINE_WIDTH;
				y =  (pt.y-55) / MINE_HEIGHT;
					
				if(g_board[x][y].isOpen == CLOSE)
				{	
					if(!(tempx==x && tempy==y))
					{
						rect.left	= 12 + MINE_WIDTH * x;
						rect.top	= 55 + MINE_HEIGHT * y;
						rect.right	= rect.left + MINE_WIDTH;
						rect.bottom	= rect.top + MINE_HEIGHT;
						InvalidateRect(hwnd, &rect, FALSE);
						UpdateWindow(hwnd);
						
						blockMove = 1;
						rect.left	= 12 + MINE_WIDTH * tempx;
						rect.top	= 55 + MINE_HEIGHT * tempy;
						rect.right	= rect.left + MINE_WIDTH;
						rect.bottom	= rect.top + MINE_HEIGHT;
						InvalidateRect(hwnd, &rect, FALSE);
						UpdateWindow(hwnd);
						
						blockMove = 0;
						}
				}
				else
				{
						blockMove = 1;
						rect.left	= 12 + MINE_WIDTH * tempx;
						rect.top	= 55 + MINE_HEIGHT * tempy;
						rect.right	= rect.left + MINE_WIDTH;
						rect.bottom	= rect.top + MINE_HEIGHT;
						InvalidateRect(hwnd, &rect, FALSE);
						UpdateWindow(hwnd);

						blockMove = 0;
				}
				return 0;
		
			}
			return 0;
		}  

	case WM_LBUTTONDOWN: 
		{
			if(GAMESTATE == WIN || GAMESTATE == LOSE)		return 0;	// ������ ���� ���¿����� ��ư�Է��� ���� ����.
				
			pt = MAKEPOINTS(lParam);
			// NORMAL, WIN, LOSE�� ������ ���� ����.
			int x =  (pt.x-12) / MINE_WIDTH;
			int y =  (pt.y-55) / MINE_HEIGHT;
			
			if(g_board[x][y].isOpen == CLOSE)
			{
				rect.left	= 12 + MINE_WIDTH * x;
				rect.top	= 55 + MINE_HEIGHT * y;
				rect.right	= rect.left + MINE_WIDTH;
				rect.bottom	= rect.top + MINE_HEIGHT;
				InvalidateRect(hwnd, &rect, FALSE);
			}
		
			LButtonDown = 1;
			// Ŭ�������Ƿ� ���� �׸� �ٽ� �׷���.
			
			// ���ʹ�ư�� ���� ���¿��� �����ʹ�ư�� ���� ��츦 ó��
			if(RButtonDown) 
			{
				int aroundflagNum = g_board[x][y].state;
				int realFlagCount=0;
				int checkFlagCount=0;
							
				// ���� ���� ���� Ŭ���ߴ��� �˻�.
				if(x < 0 || y < 0 || x >= BOARD_SIZE || y >= BOARD_SIZE)	return 0;

				// Ŭ���� ���� ���� �ִ� �������� �˻�.
				if(g_board[x][y].isOpen != OPEN)		return 0;

				// ���� �� �κб��� ������, for�� ���鼭 ���� �������� üũ.
				for(int i=max(0, x-1); i<=min(x+1, BOARD_SIZE-1); i++)
				{
					for(int j=max(0, y-1); j<=min(y+1, BOARD_SIZE-1); j++)
					{
						if(!(i==x && j==y))
						{// ���ڶ�� üũ�� ���� ���� ���ڰ� �ִ� ��ġ�� ��� ++realFlagCount
							if(g_board[i][j].isOpen == FLAG)
							{
								++checkFlagCount;
								if(g_board[i][j].state == BOMB)
									++realFlagCount;
								else
									g_board[i][j].isOpen = ERRORCHECKMINE;
							}
							else
							{
								if(g_board[i][j].state == BOMB)
									g_board[i][j].isOpen = NONFOUNDMINE;
							}

						}
					}
				}

				// ���� �ֺ����� ������ ����ڰ� üũ�� ���� ������ ������, �߸� üũ���� ���
				if(aroundflagNum == checkFlagCount && realFlagCount != checkFlagCount)
				{
					LButtonClick(hwnd, KILL, 0);
					return 0;
				}

				// ��� ������ ��������� ���ڶ�� üũ�� ���� ������ Ŭ�� ��ġ �ֺ��� ��� ����.
				if(aroundflagNum == checkFlagCount)
				{
					for(int i=max(0, x-1); i<=min(x+1, BOARD_SIZE-1); i++)
					{
						for(int j=max(0, y-1); j<=min(y+1, BOARD_SIZE-1); j++)
						{
							if(!(i==x && j==y))
							{
								if(g_board[i][j].state != BOMB)		LButtonClick(hwnd, i, j);
							}
						}
					}
				}
				// ����Ŭ���� ���� ó���� �Ϸ� �����Ƿ� RButtonDown �� �ʱ�ȭ.
				LButtonDown = 0;
				RButtonDown = 0;
				// ���� ���ڸ� �����ϰ� ��� ���� �����ִ��� üũ�ؼ� '��' ���̸� ���� ����.				
				CheckGameEnd(hwnd);
			}
		}
		return 0;

	case WM_LBUTTONUP:
		{
			if(GAMESTATE == WIN || GAMESTATE == LOSE)		return 0;	// ������ ���� ���¿����� ��ư�Է��� ���� ����.

			LButtonDown = 0;

			pt = MAKEPOINTS(lParam);
			int x = (pt.x - 12) / MINE_WIDTH;
			int y = (pt.y - 55) / MINE_HEIGHT;

			if(GAMESTATE == START)
			{
				int mineCount=0;
				int i, j;
				
				// ó���� Ŭ���� ��ġ�� ���ڰ� �ִٸ�,
				if(g_board[x][y].state == BOMB)
				{
					// ���ڸ� �ű���̹Ƿ�, �����ֺ��� ���ڸ� -1 �� �Ѵ�.
					for(i=max(0, x - 1); i<=min(BOARD_SIZE-1, x + 1); i++)
					{	
						for(j=max(0, y - 1); j<=min(BOARD_SIZE-1, y + 1); j++)
						{
							if(!(i==x && j==y))
							{
								if(g_board[i][j].state != BOMB)
									--g_board[i][j].state;
							
								else	
									++mineCount;
							}
						}
					}

					// �׸��� ���ڰ� �ִ� �ڸ����� ������ ���ڸ� �־���� �ϹǷ�, ���� mineCount-1 ���� �־��ش�. (�ֺ��� ���ڰ���)
					g_board[x][y].state = mineCount;
					
					// �׸��� ���ڸ� �ٸ� ���� �־��ش�.			
					srand(time(NULL));
					
					// ���� �Ҵ��� ��ġ�� �̹� ���ڰ� �����Ѵٸ�, �ٽ� �������� �Ҵ�޴´�.
					do{
						i = rand() % BOARD_SIZE;	
						j = rand() % BOARD_SIZE;
					}while(g_board[i][j].state == BOMB);
					
					// ���� �Ҵ��� ��ġ�� ���ڰ� �������� �ʴ´ٸ�, �� ��ġ�� ���ڸ� �ִ´�.
					g_board[i][j].state = BOMB;

					// ���� �Ҵ��� ��ġ �ֺ��� ���ڸ� ���� 1�� ������Ų��.
					for(int k = max(0, i - 1); k <= min(BOARD_SIZE-1, i + 1); k++)
					{	
						for(int l = max(0, j - 1); l <= min(BOARD_SIZE-1, j + 1); l++)
						{
							if(g_board[k][l].state != BOMB)
							{
								if(!(k==i && l==j))
									++g_board[k][l].state;
							}
						}
					}
				}
				GAMESTATE = NORMAL;
			}

			LButtonClick(hwnd, x, y);
			CheckGameEnd(hwnd);


		}
		return 0;
	
	case WM_RBUTTONDOWN:
		{
			if(GAMESTATE == WIN || GAMESTATE == LOSE)		return 0;

			pt = MAKEPOINTS(lParam);

			RButtonDown = 1;

			if(LButtonDown)
			{
				int x = (pt.x - 12) / MINE_WIDTH;
				int y = (pt.y - 55) / MINE_HEIGHT;
		
				int aroundflagNum = g_board[x][y].state;
				int realFlagCount=0;
				int checkFlagCount=0;
				
				// ���� ���� ���� Ŭ���ߴ��� �˻�.
				if(x < 0 || y < 0 || x >= BOARD_SIZE || y >= BOARD_SIZE)	return 0;

				// Ŭ���� ���� ���� �ִ� �������� �˻�.
				if(g_board[x][y].isOpen != OPEN)		return 0;

				// ���� �� �κб��� ������, for�� ���鼭 ���� �������� üũ.
				for(int i=max(0, x-1); i<=min(x+1, BOARD_SIZE-1); i++)
				{
					for(int j=max(0, y-1); j<=min(y+1, BOARD_SIZE-1); j++)
					{
						if(!(i==x && j==y))
						{// ���ڶ�� üũ�� ���� ���� ���ڰ� �ִ� ��ġ�� ��� ++realFlagCount
							if(g_board[i][j].isOpen == FLAG)
							{
								++checkFlagCount;
								if(g_board[i][j].state == BOMB)
									++realFlagCount;
								else
									g_board[i][j].isOpen = ERRORCHECKMINE;
							}
							else
							{
								if(g_board[i][j].state == BOMB)
									g_board[i][j].isOpen = NONFOUNDMINE;
							}

						}
					}
				}
		
				// ���� �ֺ����� ������ ����ڰ� üũ�� ���� ������ ������, �߸� üũ���� ���
				if(aroundflagNum == checkFlagCount && realFlagCount != checkFlagCount)
				{
					LButtonClick(hwnd, KILL, 0);
					return 0;
				}

				// ��� ������ ��������� ���ڶ�� üũ�� ���� ������ Ŭ�� ��ġ �ֺ��� ��� ����.
				if(aroundflagNum == checkFlagCount)
				{
					for(int i=max(0, x-1); i<=min(x+1, BOARD_SIZE-1); i++)
					{
						for(int j=max(0, y-1); j<=min(y+1, BOARD_SIZE-1); j++)
						{
							if(!(i==x && j==y))
							{
								if(g_board[i][j].state != BOMB)		LButtonClick(hwnd, i, j);
							}
						}
					}
				}
				// ����Ŭ���� ���� ó���� �Ϸ� �����Ƿ� RButtonDown �� �ʱ�ȭ.
				RButtonDown = 0;
				LButtonDown = 0;
				// ���� ���ڸ� �����ϰ� ��� ���� �����ִ��� üũ�ؼ� '��' ���̸� ���� ����.				
				CheckGameEnd(hwnd);
			}
		}
		return 0;
	
	case WM_RBUTTONUP:
		{
			pt = MAKEPOINTS(lParam);
			int x = (pt.x - 12) / MINE_WIDTH;
			int y = (pt.y - 55) / MINE_HEIGHT;

			if(GAMESTATE == WIN || GAMESTATE == LOSE)		return 0;

			RButtonDown = 0;

			if(chooseMineNum == 10 && g_board[x][y].isOpen != FLAG)
			{
				MessageBox(hwnd, "���̻� ������ �� �����ϴ�. ", "����ã��", MB_OK);
				return 0;
			}

			RButtonClick(hwnd, x, y);
		}
		return 0;

	case WM_DESTROY:
		DeleteObject(mybit);
		PostQuitMessage(0); 
		return 0;
	}
	return DefWindowProc( hwnd, msg, wParam, lParam);
}

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
					LPSTR	  lpCmdLine, int nShowCmd )
{
	ATOM atom;
	WNDCLASS wc;
	HWND hwnd;
	MSG msg;
	
	wc.cbClsExtra	= 0;
	wc.cbWndExtra	= 0;
	wc.hbrBackground= (HBRUSH)GetStockObject( WHITE_BRUSH ); 
	wc.hCursor		= LoadCursor( 0, IDC_ARROW );
	wc.hIcon		= LoadIcon( 0, IDI_APPLICATION);
	wc.hInstance	= hInstance;
	wc.lpfnWndProc  = WndProc; 
	wc.lpszClassName= "MYMINE";
	wc.lpszMenuName = 0;
	wc.style		= 0;

	atom = RegisterClass( &wc);
	
	if ( atom == 0 ) 
	{
		MessageBox( 0, "Fail To RegisterClass", "Error", MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx( 0, "MYMINE", "����ã��", WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~ WS_MAXIMIZEBOX,
								0, 0, 175, 240, 0, 0, hInstance, 0);
	ShowWindow( hwnd, nShowCmd); 
	UpdateWindow( hwnd );

	while ( GetMessage( &msg, 0, 0, 0) ) 
	{							
		TranslateMessage(&msg);
		DispatchMessage( &msg);
	}

	return 0;
}

