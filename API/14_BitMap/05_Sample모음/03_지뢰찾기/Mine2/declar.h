

#define INTERVAL 16			//
typedef struct _POS{
		int x;	int y;	int xx;	int yy;
}POS;

typedef struct _FRAME_POS{
	POS first;				// ó�� �������� ���� ���� ��ǥ, ������ ������ǥ
	POS second;				// �ι�° ��������            "
	POS third;				// ����° ��������            "
	POS four;				// �׹�° ��������            "
	POS five;				// �ټ���° ��������          "
	POS smile;				// ���� ��ư�� ��ġ - ��ư ��ü ������ 26,26 
	POS miniPos;			// ���� ��ư�� ���� x,y ���� �� x,y����
}FRAME_POS;

FRAME_POS Client;


void Init_Position(int width,int height){
	//===== �ʱ� �߱� ��� ���� ���鶧 ����� ��ǥ����
	
	Client.first.x = 0;		Client.first.y = 0;
	//------------------������--------------------------
	// ���߿� ����� ��峪 ��庰 ������ �̺κ� ���μ��� ������ 
	// ������ ���������ָ� �������� �ڵ����� �����ȴ�.

	Client.first.xx = (INTERVAL * width) + 24;	
	Client.first.yy = (INTERVAL * height) + 67;		// 55�� ���� ���� 28 �Ʒ�
	//--------------------------------------------------

	//--------------------------------------------------
	Client.second.x =9;		Client.second.y =9;
	Client.second.xx = Client.first.xx-9;	
	Client.second.yy =46;
	//--------------------------------------------------

	//--------------------------------------------------
	Client.third.x =15;		Client.third.y =14;
	Client.third.xx =57;		Client.third.yy =40;
	//--------------------------------------------------
	
	//--------------------------------------------------
	Client.four.x = Client.second.xx -50;
	Client.four.y = 14;
	Client.four.xx = Client.second.xx -9;
	Client.four.yy = 40;
	//--------------------------------------------------

	//--------------------------------------------------
	Client.five.x = 9;		Client.five.y = 52;
	Client.five.xx = Client.first.xx -9;
	Client.five.yy = Client.first.yy -9;
	//--------------------------------------------------

	//--------------------------------------------------
	Client.miniPos.x = 12;	Client.miniPos.y = 55;
	Client.miniPos.xx = Client.first.xx -28;
	Client.miniPos.yy = Client.first.yy -28;
	//--------------------------------------------------
	
	//------------------������ ��ǥ----------------------
	Client.smile.x = (Client.second.x + Client.second.xx)/2 -13;
	Client.smile.y = 14;
	Client.smile.xx = Client.smile.x + 26;
	Client.smile.yy = 40;
	//--------------------------------------------------
}


// ����ã�� ó���� ���ڸ� �ż��Ҷ� �� �÷��װ� FALSE�� ���¿��� MOUSEUP �Ұ��
// FLAG�� TRUE�� �ٲٰ� ���ڸ� ���콺 Ŭ�� ��ǥ�� �ƴ� ������ ������ �����ϰ�
// �ż��Ѵ�.
static BOOL mineSettingFLAG = FALSE;

// ��ư�� Ǫ�� ���¿��� ���콺 ���� ���� ������ �׸� �ٲ�� ���̴�..
// LBUTTONUP�Ҷ� FALSE�� �ǰ�
// LBUTTONDOWN�Ҷ� TRUE�� �ǰ�
// MOUSEMOVE�Ҷ� TRUE�̸� ������ ��ǥ�� ���� �׸��� ������
// �Ӽ��� CLOSE �Ǿ��ִ°͸� ���ش�. �̹̿����ִ°� �ǵ��� �ʴ´�
static BOOL ButtonPushMoveFLAG = FALSE;	

// WinMain ���� hInstance�� ��Ʈ�� ����Ʈ...
HINSTANCE g_hInst;	


// �ʱ� ����..�ʺ����� ��� 9,9
static int Xp;
static int Yp;

static int INITMINE;						//	��ü ���ڰ����� �����Ұ� �ʱⰪ 10��

#define GetClntX(K) ( (12+((K)*16)) )
#define GetClntY(P) ( (55+((P)*16)) )

#define ArrayX(x) =  ((int)((x-12) / 16))		//	ClntPos.x
#define ArrayY(y) =  ((int)((y-55) / 16))		//  ClntPos.y

//#define G_BOARD(i,j)	(*(*(g_board+i)+j))
#define G_BOARD(i,j) (*(g_board+(((i)*Xp)+(j))))






void Draw3dRect(HDC hdc, int x, int y, int xx, int yy, BOOL down, int width )
{
	COLORREF clrMain  = RGB(192,192,192),
				clrLight = RGB(255,255,255), 
				clrDark  = RGB(128,128,128);

	HPEN hPen1, hPen2, hOldPen;
	HBRUSH hBrush, hOldBrush;     

	if(down)    
	{
		hPen2 = CreatePen(PS_SOLID,1,clrLight);
		hPen1 = CreatePen(PS_SOLID,1,clrDark);
	} 
	else 
	{
		hPen1 = CreatePen(PS_SOLID,1,clrLight);
		hPen2 = CreatePen(PS_SOLID,1,clrDark);
	}  
	hBrush =  CreateSolidBrush( clrMain );
	hOldPen = (HPEN)SelectObject(hdc, hPen1);
	hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);  

	Rectangle(hdc, x , y, xx+1, yy+1);  

	for(int i=0; i < width; i++)
	{
		SelectObject(hdc, hPen1);

		MoveToEx(hdc, xx - 1, y, 0 );
		LineTo(hdc, x, y);
		LineTo(hdc, x, yy - 1 );  

		SelectObject(hdc, hPen2);

		MoveToEx(hdc, x, yy,0);
		LineTo(hdc, xx, yy);
		LineTo(hdc, xx, y);  

		x++; y++; xx--; yy--;
	} 
	SelectObject(hdc, hOldPen);
	SelectObject(hdc, hOldBrush);

	DeleteObject(hPen1); 
	DeleteObject(hPen2); 
	DeleteObject(hBrush);
} 





//enum STATE { EMPTY = 0, ONE , TWO , THREE , FOUR , FIVE ,SIX ,SEVEN , EIGHT, BOMB=99};
#define EMPTY	0
#define ONE		1
#define TWO		2
#define THREE	3
#define FOUR	4
#define FIVE	5
#define SIX		6
#define SEVEN	7
#define EIGHT	8
#define BOMB	9

#define CLICKBOMB 10
#define CROSSBOMB 11
#define GENERAL   12


	//---------------1,   2   3   4   5   6   7  8  9  0
//	int timePos[10]={253,230,207,184,161,138,115,92,69,46};
	
	
	//EMPTY,1,2,3,4,5,6,7,8, �Ϲ���ź,Ŭ����ź,X��ź,CLOSE=12,FLAG=13,QUESTION=14
//	int picPos[16]={240,224,208,192,176,160,144,128,112,80,48,64,0,16,32};


#define CLOSE 0				// �����׸�
#define OPEN 1				// �����׸�
#define FLAG 13				// ��߲Ŵ±׸�
#define QUESTION 14			// ����ǥ �׸�




///// ������ ����					
// �Ӽ���.. Ŭ���� ������,	 �Ϲ� ������, ��۶� ������ , ��� ������, ������ ������
//			NORMAL_ON_SMILE NORMAL_SMILE, GLASS_SMILE		SUPRISE_SMILE	DISAPEAR_SMILE
//	int smilePos[5] = {0,24,48,72,96};				// x-24,y-24
#define NORMAL_ON_SMILE	0		//	�Ϲ� ������        - ������ ��ư Ŭ���� -
#define GLASS_SMILE		1		//  ���۶� �� ������ - ���������� �����������
#define DISAPEAR_SMILE	2		//	������ ������	   - LBUTTON_UP��. ��ź�ϰ��.
#define SUPRSISE_SMILE	3		//  ��� ������		   - ���콺 - LBUTTON_DOWN �� 

#define NORMAL_SMILE	4		//	�Ϲ� ������		   - LBUTTON_UP��. ��ź�� �ƴҰ��







typedef struct _BLOCK{
	int state;
	char isOpen;			// OPEN FLAG QUESTION
	
}BLOCK;

//BLOCK g_board[Xp][Yp];
// ���� �Ҵ�..
BLOCK * g_board;

