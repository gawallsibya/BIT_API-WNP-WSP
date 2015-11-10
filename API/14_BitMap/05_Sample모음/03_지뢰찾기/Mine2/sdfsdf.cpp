#include <stdio.h>							//	printf �� �ǰ� �ϴ¹�.. 
#include <windows.h>
#include <time.h>
#include "resource.h"
#include "declar.h"




//------------------------------------------------------------------------------//
//								Init �ʱ�ȭ �Լ�
//------------------------------------------------------------------------------//
//	�Űܺ��� : Iwidth  = ���λ���� �����Ѵ�
//			   iHeight = ���� ����� �����Ѵ�
//------------------------------------------------------------------------------//
//	��� :-------------------------------------------------------------------
//------------------------------------------------------------------------------//
// ����ã���� ���� ���� ����� �����ϰ� 
// �׿����� ���� �޸𸮸� ���� �Ҵ����ְ�
// ����ã�� ��濡 ���� ��� ��ǥġ�� �������ְ�
// �Ӽ��� CLOSE�� EMPTY�� �ʱ�ȭ�Ѵ�
//------------------------------------------------------------------------------//
void Init(int Iwidth , int Iheight , int Imind)
{
	
	int i,j;
	Xp = Iwidth;
	Yp = Iheight;
	INITMINE = Imind;
	g_board = (BLOCK*)malloc(sizeof(BLOCK)*Xp*Yp);


	// ����ü�� �����ʱ�ȭ
	Init_Position(Iwidth,Iheight);			

		
		for(j = 0 ; j <Iheight ; ++j)
			for(i = 0; i < Iwidth ; ++i){			// X�� = I = Iwidth
						
			//g_board[i][j].isOpen = CLOSE;
		
			//(*(g_board+((i*Xp)+j))).isOpen = CLOSE;
			G_BOARD(i,j).isOpen = CLOSE;
			G_BOARD(i,j).state = EMPTY;
			
		
		}

}


//------------------------------------------------------------------------------//
//								Binding ���ε� �Լ�
//------------------------------------------------------------------------------//
//	�Űܺ��� : Bmind   = ���� ������ ������ �������� ����
//			   Bwidth  = ���� ����	- �����Լ��� ����Ͽ� ���ڽ��� ��ġ�� �����Ѵ�
//			   Bheight = ���� ����	- �����Լ��� ����Ͽ� ���ڽ��� ��ġ�� �����Ѵ�
//			   first   = ó�� Ŭ���� x��ǥ(������� ��ǥ�̴�-�迭�� �ε����� �ش�)
//			   second  = ó�� Ŭ���� y��ǥ(x,y�� �ش��ϴ� ��ǥ�� ���ڸ� �����ʰ� �Ѵ�)
//
//------------------------------------------------------------------------------//
//	��� :		��ź ���ε� & ī����
//------------------------------------------------------------------------------//
//	1. ��ź�� ���ε�
// srand�� ����Ͽ� �迭�� ���� ���� ��ġ�� �����ϰ� ������ ��ź�� �ִ´�.
//			-ù��° Ŭ����ǥ�� ������ �ȵǰ�
//			-�ι�°	Bmind���� ��ŭ�� �ɴ´�
//						- �ߺ��� ���� �ʰ� �ٸ� ��ǥ�� ã�´�
//	2. ��ź COUNT
//	�迭�� i,j�� ���°� ��ź�� �ƴ϶�� �׹迭�� �������� 8���� �� �����Ѵ�
//	8������ �����Ҷ� i ,j�� ������ �ʰ����� �ʰ� �����Ѵ�
//	---�ٽ� ©���� ����ٸ� �� ���� �ְ� �Ұ�.-_-....
//	
//------------------------------------------------------------------------------//


void Binding(int Bmind , int Bwidth , int Bheight,	// Bmind�� ���� ���� ���� Bwidth �� x���� Bheight�� y����
			 int first,int second)					// first�� ó��Ŭ���� x��ǥ second�� ó�� y��ǥ
{
	
	
	int Bcount = 0;
	srand(time(NULL));

	//rand() % mind;
	int Bi;
	int Bj;

	int i,j;

	
	// ���ڽɱ�...
	while(Bcount < Bmind){// ���� ������ŭ ���ڸ� �ɾ�����. ������
		Bi = rand()% Bwidth;
		Bj = rand()% Bheight;

		// ���콺 ó��Ŭ���� ��ǥ�� �ƴϰ� ��ź�� �ƴ϶��
		//if ( (G_BOARD(Bi,Bj).state != BOMB) && (Bi !=first) && (Bj !=second)){
		//	 G_BOARD(Bi,Bj).state = BOMB ;					// ���ڸ� �ɾ��
		//	Bcount++;										// ���ڰ����� �������Ѷ�
		//}
		if( (  G_BOARD(Bi,Bj).state != BOMB) && (Bi !=first) && (Bj !=second)){
			G_BOARD(Bi,Bj).state = BOMB;
			Bcount++;
			
		}
	}

	printf("\n\n\n----------------------------------------------\n");
	printf("------------------�ʱ�ȭ��� -----------------\n");
	printf("------------------���� ����-----------------\n");
	printf("----------------------------------------------\n");
	
		
	for(j = 0 ; j < Bheight ; ++j){							// X�� = i = Bwidth
		for ( i = 0 ; i < Bwidth ; ++i){
			printf("%2d ",G_BOARD(i,j).state);
		}
		printf("\n");
	}



	//Bcount = 0;
	// ���� ī��Ʈ�ϴ� �κ�...................
	
	for(j = 0 ; j < Bheight ; ++j){							// X�� = i = Bwidth
		for ( i = 0 ; i < Bwidth ; ++i){
			Bcount = 0;			
			
			// i,j��ǥ�� ���°� ��ź�� �ƴ϶�� state���� �ϳ� ������Ų��...
			if(G_BOARD(i,j).state != BOMB)   {

				if(i-1 >=0)						if (G_BOARD(i-1,j).state == BOMB) 		Bcount++;
				if((i-1 >=0) &&(j-1 >=0))		if (G_BOARD(i-1,j-1).state==BOMB)		Bcount++;
				if(i+1 < Bwidth)				if(G_BOARD(i+1,j).state==BOMB)			Bcount++;
				if((i+1<Bwidth&&(j+1)<Bheight))	if (G_BOARD(i+1,j+1).state==BOMB)		Bcount++;
				if(j-1 >=0)						if(G_BOARD(i,j-1).state==BOMB)			Bcount++;
				if((i+1<Bwidth)&&(j-1>=0))		if (G_BOARD(i+1,j-1).state==BOMB)		Bcount++;
				if(j+1 <Bheight)				if(G_BOARD(i,j+1).state==BOMB)			Bcount++;
				if((i-1 >=0)&&(j+1<Bheight))	if (G_BOARD(i-1,j+1).state==BOMB)		Bcount++;
				
			
				switch(Bcount){
				//printf("Bcount is %d \n\n" , Bcount);
				case 0 : 				G_BOARD(i,j).state = EMPTY;				break;
				case 1 : 				G_BOARD(i,j).state = ONE;				break;
				case 2 : 				G_BOARD(i,j).state = TWO;				break;
				case 3 : 				G_BOARD(i,j).state = THREE;				break;
				case 4 : 				G_BOARD(i,j).state = FOUR;				break;
				case 5 : 				G_BOARD(i,j).state = FIVE;				break;
				case 6 : 				G_BOARD(i,j).state = SIX;				break;
				case 7 : 				G_BOARD(i,j).state = SEVEN;				break;
				case 8 : 				G_BOARD(i,j).state = EIGHT;				break;					
				}


			}	// ��ź�� if����

		}		// ù��° for��

			// �ι�° for��
	}

	
//--------------------------------Test Mode--------------------------------
	printf("\n\n\n----------------------------------------------\n");
	printf("--------------�ʱ�ȭ���---------------------\n");
	printf("-------------------STATE-------------------\n");
	printf("----------------------------------------------\n");
	for( j = 0 ; j < Bheight ; ++j){						// x��  i = Bwidth
		for (  i = 0 ; i < Bwidth ; ++i){
		
			printf("%2d ",G_BOARD(i,j).state);
		}
		printf("\n");

	}
//--------------------------------Test Mode--------------------------------
		
}		// ���α׷� ����











//------------------------------------------------------------------------------//
//									EmptySearching ���鳪���� �ַ���
//------------------------------------------------------------------------------//
//
//	Ư¡....-_- ��¥ �����ϰ� ���� Ž�� ��� �˰���
//				: �ϴ� �̾ȿ������� ��ǥ�� ������ ���� ���� ��ǥ�̴�
//				: �׷��� ��迡�� Ž���� ����þ����� � ��Ȳ�϶� �����ؾ��ϴµ� ��迡�� �߸���
//				: ���� ������ �ִ�. �׷��� else������ ������ ����Ȳ�� �´� ��츦 ���� �����Ͽ�
//				: ���� ����� �����
//
//	������ �ϴٽð�ġ�� �ȴٸ�...���� �� ����� 8������ �˻��ϱ� ���� ���⿡ ���� �迭�� ���� 
//	�׹迭 ������� 8������� ��� ������ �����Ҽ� �ְ� �Ͽ� �� �迭�� Ž���Ұ��� �ε����� ����ϰ� �Ѵ�
//		G_BOARD(����[count],����[count])		�̷������� count�� 8�� �ٵ����� ��� ������ �ٰ˻����ָ� 
//		�ɰ��̴�...�ƾƾ�-_- ��¥ �밡�� �ñ׷�...�ӵ��鿡���� ��Ǯ� ­���� �̰� ��������....-_-;;
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

void EmptySearching(int ArrX, int ArrY)		// ����� ã���� ���ڰ� ���ö����� OPEN��Ų��.
{

	
			//ArrX-1 , ArrY-1 ���⿡ ���� ó��
			// 1�� if	���°� EMPTY�̸鼭 ���������� OPEN���� �ؼ� ���� ���̰� �ϰ�
			//			�� �ڱ��ڽ� �Լ��� ȣ���ؼ� �׹����� ��ã�´�...
			// 2�� if   ���� ����ǥ�� ���°� FLAG�̰ų� QUESTION �̸� �ƹ�ó���� ���ϰ�
			// 3�� if	1,2,3,4,5,6,7,8 �ϰ�쿡�� �����ش�
			// �̷��� �ٺ� �밡�ٸ� �ϴ������� ��踦 �Ѿ ���� ������������ else�������� ó���������Ѵ�
			// ���� �־...-_-
			// �Ʒ� �����鵵 ���⿡ ���� ó���� Ʋ���� �Ȱ���

			if( (G_BOARD(ArrX-1,ArrY-1).state == EMPTY) && (G_BOARD(ArrX-1,ArrY-1).isOpen == CLOSE) )
			{
				G_BOARD(ArrX-1,ArrY-1).isOpen = OPEN;
				EmptySearching(ArrX-1,ArrY-1);
			}

			else if ((G_BOARD(ArrX-1,ArrY-1).state	== FLAG)	|| (G_BOARD(ArrX-1,ArrY-1).state == QUESTION) );
			else if ((G_BOARD(ArrX-1,ArrY-1).state	== ONE)		|| (G_BOARD(ArrX-1,ArrY-1).state == TWO)	 ||
					(G_BOARD(ArrX-1,ArrY-1).state	== THREE)	|| (G_BOARD(ArrX-1,ArrY-1).state == FOUR)	 ||
					(G_BOARD(ArrX-1,ArrY-1).state	== FIVE)	|| (G_BOARD(ArrX-1,ArrY-1).state == SIX)	 ||
					(G_BOARD(ArrX-1,ArrY-1).state   == SEVEN)	|| (G_BOARD(ArrX-1,ArrY-1).state == EIGHT))
			{
				G_BOARD(ArrX-1,ArrY-1).isOpen = OPEN;
			}



			//x, y-1

			if( (G_BOARD(ArrX,ArrY-1).state == EMPTY) && (G_BOARD(ArrX,ArrY-1).isOpen == CLOSE) )
			{
				G_BOARD(ArrX,ArrY-1).isOpen = OPEN;
				EmptySearching(ArrX,ArrY-1);
			}

			else if ((G_BOARD(ArrX,ArrY-1).state	== FLAG)	|| (G_BOARD(ArrX,ArrY-1).state == QUESTION) );
			else if ((G_BOARD(ArrX,ArrY-1).state	== ONE)		|| (G_BOARD(ArrX,ArrY-1).state == TWO)	 ||
					(G_BOARD(ArrX,ArrY-1).state	== THREE)	|| (G_BOARD(ArrX,ArrY-1).state == FOUR)	 ||
					(G_BOARD(ArrX,ArrY-1).state	== FIVE)	|| (G_BOARD(ArrX,ArrY-1).state == SIX)	 ||
					(G_BOARD(ArrX,ArrY-1).state   == SEVEN)	|| (G_BOARD(ArrX,ArrY-1).state == EIGHT))
			{
				G_BOARD(ArrX,ArrY-1).isOpen = OPEN;
			}


		//x+1 y-1
			if( (G_BOARD(ArrX+1,ArrY-1).state == EMPTY) && (G_BOARD(ArrX+1,ArrY-1).isOpen == CLOSE) )
			{
				G_BOARD(ArrX+1,ArrY-1).isOpen = OPEN;
				EmptySearching(ArrX+1,ArrY-1);
			}

			else if ((G_BOARD(ArrX+1,ArrY-1).state	== FLAG)	|| (G_BOARD(ArrX+1,ArrY-1).state == QUESTION) );
			else if ((G_BOARD(ArrX+1,ArrY-1).state	== ONE)		|| (G_BOARD(ArrX+1,ArrY-1).state == TWO)	 ||
					(G_BOARD(ArrX+1,ArrY-1).state	== THREE)	|| (G_BOARD(ArrX+1,ArrY-1).state == FOUR)	 ||
					(G_BOARD(ArrX+1,ArrY-1).state	== FIVE)	|| (G_BOARD(ArrX+1,ArrY-1).state == SIX)	 ||
					(G_BOARD(ArrX+1,ArrY-1).state   == SEVEN)	|| (G_BOARD(ArrX+1,ArrY-1).state == EIGHT))
			{
				G_BOARD(ArrX+1,ArrY-1).isOpen = OPEN;
			}

		//x+1 , y
			if( (G_BOARD(ArrX+1,ArrY).state == EMPTY) && (G_BOARD(ArrX+1,ArrY).isOpen == CLOSE) )
			{
				G_BOARD(ArrX+1,ArrY).isOpen = OPEN;
				EmptySearching(ArrX+1,ArrY);
			}

			else if ((G_BOARD(ArrX+1,ArrY).state	== FLAG)	|| (G_BOARD(ArrX+1,ArrY).state == QUESTION) );
			else if ((G_BOARD(ArrX+1,ArrY).state	== ONE)		|| (G_BOARD(ArrX+1,ArrY).state == TWO)	 ||
					(G_BOARD(ArrX+1,ArrY).state	== THREE)	|| (G_BOARD(ArrX+1,ArrY).state == FOUR)	 ||
					(G_BOARD(ArrX+1,ArrY).state	== FIVE)	|| (G_BOARD(ArrX+1,ArrY).state == SIX)	 ||
					(G_BOARD(ArrX+1,ArrY).state   == SEVEN)	|| (G_BOARD(ArrX+1,ArrY).state == EIGHT))
			{
				G_BOARD(ArrX+1,ArrY).isOpen = OPEN;	
			}

		//x+1 , y+1
			if( (G_BOARD(ArrX+1,ArrY+1).state == EMPTY) && (G_BOARD(ArrX+1,ArrY+1).isOpen == CLOSE) )
			{
				G_BOARD(ArrX+1,ArrY+1).isOpen = OPEN;
				EmptySearching(ArrX+1,ArrY+1);
			}

			else if ((G_BOARD(ArrX+1,ArrY+1).state	== FLAG)	|| (G_BOARD(ArrX+1,ArrY+1).state == QUESTION) );
			else if ((G_BOARD(ArrX+1,ArrY+1).state	== ONE)		|| (G_BOARD(ArrX+1,ArrY+1).state == TWO)	 ||
					(G_BOARD(ArrX+1,ArrY+1).state	== THREE)	|| (G_BOARD(ArrX+1,ArrY+1).state == FOUR)	 ||
					(G_BOARD(ArrX+1,ArrY+1).state	== FIVE)	|| (G_BOARD(ArrX+1,ArrY+1).state == SIX)	 ||
					(G_BOARD(ArrX+1,ArrY+1).state   == SEVEN)	|| (G_BOARD(ArrX+1,ArrY+1).state == EIGHT))
			{
				G_BOARD(ArrX+1,ArrY+1).isOpen = OPEN;
			}

		//x , y-1
			if( (G_BOARD(ArrX,ArrY-1).state == EMPTY) && (G_BOARD(ArrX,ArrY-1).isOpen == CLOSE) )
			{
				G_BOARD(ArrX,ArrY-1).isOpen = OPEN;
				EmptySearching(ArrX,ArrY-1);
			}

			else if ((G_BOARD(ArrX,ArrY-1).state	== FLAG)	|| (G_BOARD(ArrX,ArrY-1).state == QUESTION) );
			else if ((G_BOARD(ArrX,ArrY-1).state	== ONE)		|| (G_BOARD(ArrX,ArrY-1).state == TWO)	 ||
					(G_BOARD(ArrX,ArrY-1).state	== THREE)	|| (G_BOARD(ArrX,ArrY-1).state == FOUR)	 ||
					(G_BOARD(ArrX,ArrY-1).state	== FIVE)	|| (G_BOARD(ArrX,ArrY-1).state == SIX)	 ||
					(G_BOARD(ArrX,ArrY-1).state   == SEVEN)	|| (G_BOARD(ArrX,ArrY-1).state == EIGHT))
			{
				G_BOARD(ArrX,ArrY-1).isOpen = OPEN;		
			}

		// x-1 ,y+1
			if( (G_BOARD(ArrX-1,ArrY+1).state == EMPTY) && (G_BOARD(ArrX-1,ArrY+1).isOpen == CLOSE) )
			{
				G_BOARD(ArrX-1,ArrY+1).isOpen = OPEN;
				EmptySearching(ArrX-1,ArrY+1);
			}

			else if ((G_BOARD(ArrX-1,ArrY+1).state	== FLAG)	|| (G_BOARD(ArrX-1,ArrY+1).state == QUESTION) );
			else if ((G_BOARD(ArrX-1,ArrY+1).state	== ONE)		|| (G_BOARD(ArrX-1,ArrY+1).state == TWO)	 ||
					(G_BOARD(ArrX-1,ArrY+1).state	== THREE)	|| (G_BOARD(ArrX-1,ArrY+1).state == FOUR)	 ||
					(G_BOARD(ArrX-1,ArrY+1).state	== FIVE)	|| (G_BOARD(ArrX-1,ArrY+1).state == SIX)	 ||
					(G_BOARD(ArrX-1,ArrY+1).state   == SEVEN)	|| (G_BOARD(ArrX-1,ArrY+1).state == EIGHT))
			{
				G_BOARD(ArrX-1,ArrY+1).isOpen = OPEN	;	
			}


		// x-1 ,y
			if( (G_BOARD(ArrX-1,ArrY).state == EMPTY) && (G_BOARD(ArrX-1,ArrY).isOpen == CLOSE) )
			{
				G_BOARD(ArrX-1,ArrY).isOpen = OPEN;
				EmptySearching(ArrX-1,ArrY);
			}
			
			else if ((G_BOARD(ArrX-1,ArrY).state	== FLAG)	|| (G_BOARD(ArrX-1,ArrY).state == QUESTION) );
			else if ((G_BOARD(ArrX-1,ArrY).state	== ONE)		|| (G_BOARD(ArrX-1,ArrY).state == TWO)	 ||
					(G_BOARD(ArrX-1,ArrY).state	== THREE)	|| (G_BOARD(ArrX-1,ArrY).state == FOUR)	 ||
					(G_BOARD(ArrX-1,ArrY).state	== FIVE)	|| (G_BOARD(ArrX-1,ArrY).state == SIX)	 ||
					(G_BOARD(ArrX-1,ArrY).state   == SEVEN)	|| (G_BOARD(ArrX-1,ArrY).state == EIGHT))
			{
				G_BOARD(ArrX-1,ArrY).isOpen = OPEN;	
			}
	
}










//------------------------------------------------------------------------------//
//									WndProc
//------------------------------------------------------------------------------//
//
//	�߰���� :		printf���� , �ð� ī����, 
//
//------------------------------------------------------------------------------//
//	�������� :		
//					static int c	:	printf�� ���� ����ϱ����� ����
//					UINT style		:	style�� �ٲپ ��������ֱ� ���Ѻ���
//					static POINTS ClntPos	:	Ŭ���̾�Ʈ ������ ��ǥ
//					static POINTS ArrayPos	:	����� �迭 ��ǥ
//					static TCHAR str[256]	:	�׽�Ʈ�� ����
//
//
//					static int WMFlagCount	:	���� ��ܿ� ǥ���� �÷��� ����ī��Ʈ��
//
//					static int timeCount	:	1�� �����ϴ� �ð����� - Ÿ�̸ӿ��Բ� �۵�
//					�Ʒ� 3���� ������ timePos�� �ε����� ����Ͽ� ��Ʈ�ʻ��� Y�� ��ǥ���� ���´�
//					int timeF		:	ȭ���� �ð� ī������ 100������ ���� ī��Ʈ ����
//					int timeS		:	10����
//				 	int timeT		:	1����	
//
//					timePos�� �迭�� ���� ������ ��Ʈ��(IDB_BITMAP2)�� ��ǥ�� ����Ų�� 
//								      1   2   3   4   5   6   7  8  9  0
//					int timePos[10]={253,230,207,184,161,138,115,92,69,46}
//
//					picPos�� �迭�� ���� ������ ��Ʈ��(IDB_BITMAP1)�� ��ǥ�� ����Ų�� 
//					EMPTY,1,2,3,4,5,6,7,8, �Ϲ���ź,Ŭ����ź,X��ź,�Ϲݱ׸�,���,����ǥ
//					int picPos[16]={240,224,208,192,176,160,144,128,112,80,48,64,0,16,32};
//
//------------------------------------------------------------------------------//


// printf�ǰ��ϴ¹�..
char* s_msg[1000] = {"WM_NULL", "WM_CREATE"};		// �޼����� �ٳ־ ������� �Ѵ�



LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	
	// printf�ǰ��ϴ¹�..
	//static int c = 0;
	//printf("%04d : %d\n" , c++ ,msg);
//////////////////////////////////////////////////////////////////////////////////////////////
	UINT style;
	

	static POINTS ClntPos;							// Ŭ���̾�Ʈ ������ ��ǥ
	static POINTS ArrayPos;							// ����� �迭 ��ǥ
	
	static TCHAR str[256];							// �׽�Ʈ�� ����

	static int timeCount;							// 1�� �����ϴ� �ð�����
	int timeF;	int timeS; 	int timeT;	
		
	//---------------1,   2   3   4   5   6   7  8  9  0  -
	int timePos[11]={253,230,207,184,161,138,115,92,69,46,0};
	
	
	//EMPTY,1,2,3,4,5,6,7,8, �Ϲ���ź,Ŭ����ź,X��ź,CLOSE=12,FLAG=13,QUESTION=14
	int picPos[16]={240,224,208,192,176,160,144,128,112,80,48,64,0,16,32};

	/////////////////////////////////////////////////////////	
	static int WMFlagCount;							// ���� ��ܿ� ǥ���� �÷��� ����ī��Ʈ��
	int flagF;	int flagS; 	int flagT;				// 

	static int MINEMINE = INITMINE;					// 


	// ������ �׸���.
	// �Ӽ���.. Ŭ���� ������,	��۶� ������ , ��� ������, ������ ������ ,�Ϲ� ������
	//NORMAL_ON_SMILE	0		//	�Ϲ� ������        - ������ ��ư Ŭ���� -
	//GLASS_SMILE		1		//  ���۶� �� ������ - ���������� �����������
	//SUPRSISE_SMILE	2		//  ��� ������		   - ���콺 - LBUTTON_DOWN �� 
	//DISAPEAR_SMILE	3		//	������ ������	   - LBUTTON_UP��. ��ź�ϰ��.

	//NORMAL_SMILE		4		//	�Ϲ� ������		   - LBUTTON_UP��. ��ź�� �ƴҰ��
	int smilePos[5] = {0,24,48,72,96};				// x-24,y-24
	static int smileState = NORMAL_SMILE;					// ������ ������ �ʱⰪ�� �⺻ �����Ϸ� �д�

	// ����ü �ʱ�ȭ ���Ŀ� �����Ͽ����� ������ RECT ������ ����ش�
	RECT Invalid_SMILErect = {Client.smile.x,Client.smile.y+2,Client.smile.x+24,Client.smile.y+24};


	static int isOpenCount =0;						// isOpen �� ������ ����
	static int isDieFlag = FALSE;					// ������ �׾��� ���׾��� Ȯ��


	HDC hdc,MemDC;
	HBITMAP MyBitmap, OldBitmap;

	PAINTSTRUCT ps;
	
	
//////////////////////////////////////////////////////////////////////////////////////////////
	
	
	
	switch( msg )
	{
	case WM_CREATE:{
		Init(9,  9, 10);				// Xp Yp�� ���� 9,9 ���� ����ƽ
										// INITMIND�� ���� 10
		MINEMINE = INITMINE;
		
		RECT rc = { 0,0,Client.first.xx,Client.first.yy+35 };	// +35�� �Ʒ� ����
		WMFlagCount=INITMINE;			// ����� ī���� - �ʱ�ȭ�� �⺻ ��ź����
		style = GetWindowLong( hwnd, GWL_STYLE);
		style &= ~WS_THICKFRAME;
		SetWindowLong( hwnd, GWL_STYLE, style );
		AdjustWindowRect( &rc, style, FALSE );
		MoveWindow(hwnd, 0, 0, rc.right - rc.left, rc.bottom - rc.top, TRUE);
		
		
		}
		return 0;

	case WM_COMMAND :{

	case ID_GAME_BEGIN : {
				
				//if(g_board !)
		
				free(g_board);
				Init(9,9,10);

				timeCount=0;				  // Ÿ�̸� ���� �ʱ�ȭ	
				timeF=timeS=timeT=0;		  // Ÿ�̸Ӹ� ī������ ����
				
				RECT rc2 = { 0,0,Client.first.xx,Client.first.yy+35 };	// +35�� �Ʒ� ����
				WMFlagCount=INITMINE;			// ����� ī���� - �ʱ�ȭ�� �⺻ ��ź����
				style = GetWindowLong( hwnd, GWL_STYLE);
				style &= ~WS_THICKFRAME;
				SetWindowLong( hwnd, GWL_STYLE, style );
				AdjustWindowRect( &rc2, style, FALSE );
				MoveWindow(hwnd, 0, 0, rc2.right - rc2.left, rc2.bottom - rc2.top, TRUE);

				
				
				WMFlagCount=INITMINE;			// ����� ī���� - �ʱ�ȭ�� �⺻ ��ź����
				
				KillTimer(hwnd,1);				// Ÿ�̸Ӹ� ���δ�
				timeF=timeS=timeT=0;		  // Ÿ�̸Ӹ� ī������ ����

				mineSettingFLAG = FALSE;		// ���콺 ó��Ŭ���ؼ� ���ڼ����ϱ� ���ؼ� FALSE�� �ٽð�ģ��


				RECT rc = { 0,0,Client.first.xx,Client.first.yy+35 };	// +35�� �Ʒ� ����
				InvalidateRect(hwnd,&rc,TRUE);
			  }
	//case �߱� : {
	case ID_GAME_INTER : {
				free(g_board);
				Init(16,16,40);

				timeCount=0;				  // Ÿ�̸� ���� �ʱ�ȭ	
				timeF=timeS=timeT=0;		  // Ÿ�̸Ӹ� ī������ ����
				
				RECT rc2 = { 0,0,Client.first.xx,Client.first.yy+35 };	// +35�� �Ʒ� ����
				WMFlagCount=INITMINE;			// ����� ī���� - �ʱ�ȭ�� �⺻ ��ź����
				style = GetWindowLong( hwnd, GWL_STYLE);
				style &= ~WS_THICKFRAME;
				SetWindowLong( hwnd, GWL_STYLE, style );
				AdjustWindowRect( &rc2, style, FALSE );
				MoveWindow(hwnd, 0, 0, rc2.right - rc2.left, rc2.bottom - rc2.top, TRUE);

				
				
				WMFlagCount=INITMINE;			// ����� ī���� - �ʱ�ȭ�� �⺻ ��ź����
				
				KillTimer(hwnd,1);				// Ÿ�̸Ӹ� ���δ�
				timeF=timeS=timeT=0;		  // Ÿ�̸Ӹ� ī������ ����

				mineSettingFLAG = FALSE;		// ���콺 ó��Ŭ���ؼ� ���ڼ����ϱ� ���ؼ� FALSE�� �ٽð�ģ��


				RECT rc = { 0,0,Client.first.xx,Client.first.yy+35 };	// +35�� �Ʒ� ����
				InvalidateRect(hwnd,&rc,TRUE);
			  }

	case ID_GAME_HIGH : {
				free(g_board);
				Init(30,16,99);

				timeCount=0;				  // Ÿ�̸� ���� �ʱ�ȭ	
				timeF=timeS=timeT=0;		  // Ÿ�̸Ӹ� ī������ ����
				
				RECT rc2 = { 0,0,Client.first.xx,Client.first.yy+35 };	// +35�� �Ʒ� ����
				WMFlagCount=INITMINE;			// ����� ī���� - �ʱ�ȭ�� �⺻ ��ź����
				style = GetWindowLong( hwnd, GWL_STYLE);
				style &= ~WS_THICKFRAME;
				SetWindowLong( hwnd, GWL_STYLE, style );
				AdjustWindowRect( &rc2, style, FALSE );
				MoveWindow(hwnd, 0, 0, rc2.right - rc2.left, rc2.bottom - rc2.top, TRUE);

				
				
				WMFlagCount=INITMINE;			// ����� ī���� - �ʱ�ȭ�� �⺻ ��ź����
				
				KillTimer(hwnd,1);				// Ÿ�̸Ӹ� ���δ�
				timeF=timeS=timeT=0;		  // Ÿ�̸Ӹ� ī������ ����

				mineSettingFLAG = FALSE;		// ���콺 ó��Ŭ���ؼ� ���ڼ����ϱ� ���ؼ� FALSE�� �ٽð�ģ��


				RECT rc = { 0,0,Client.first.xx,Client.first.yy+35 };	// +35�� �Ʒ� ����
				InvalidateRect(hwnd,&rc,TRUE);
			  }





		}

		return 0;

	case WM_LBUTTONDOWN :
		{
			
			// �迭������ ��� ���� ��ǥ��.
			ClntPos = MAKEPOINTS(lParam);
			ArrayPos.x = (ClntPos.x-12) / 16 ;		
			ArrayPos.y = (ClntPos.y-55) / 16 ;

			


			
			
			// �̱���...
			ButtonPushMoveFLAG = TRUE;
			// Ŭ���Ѱ��� �����̾��ٸ� �����׸����� �����ش�
			if (G_BOARD(ArrayPos.x,ArrayPos.y).isOpen == CLOSE){
				printf("ArrayPos.x = %d \n ArrayPos.y = %d\n" ,ArrayPos.x,ArrayPos.y);

				hdc = BeginPaint( hwnd, &ps );	
				MemDC=CreateCompatibleDC(hdc);

				RECT temp = {GetClntX(ArrayPos.x),GetClntY(ArrayPos.y),GetClntX(ArrayPos.x)+16,GetClntY(ArrayPos.y)+16};
				

				// �޸� �Ҵ��ϰ� ���ҽ� �Ҹ��� �ε��� ��Ʈ�� ����
				MemDC = CreateCompatibleDC(hdc);						
				MyBitmap = LoadBitmap(g_hInst,MAKEINTRESOURCE(IDB_BITMAP1));
				OldBitmap = (HBITMAP)SelectObject(MemDC,MyBitmap);
				
				// �о���µ� �޸𸮻� y��ǥ�� �迭���� �����´�
				StretchBlt(hdc, 
					Client.miniPos.x+(ArrayPos.x*16) , Client.miniPos.y+(ArrayPos.y*16),	// ���� x,y��ǥ
					16,16,												// X�� 15 y�� 15��ŭ ī��
					MemDC , 0,picPos[OPEN],16,16,SRCCOPY);
				
				InvalidateRect(hwnd,&temp,FALSE);
				// �ڿ�����
				SelectObject(MemDC,OldBitmap);
				DeleteObject(MyBitmap);
				DeleteDC(MemDC);
				
			}
			
			
			
						
			
			// Ŭ���̾�Ʈ �������� ��ǥ�� �������� x1 ��ǥ�δ� ũ�ų� ����
			// Ŭ���̾�Ʈ �������� ��ǥ�� �������� x2 ��ǥ�δ� �۰ų� ����
			if( ( (ClntPos.x >= Client.smile.x+2) && (ClntPos.x <= Client.smile.xx-2) ) &&
				(ClntPos.y >= Client.smile.y+2) && (ClntPos.y <= Client.smile.yy-2) ) {
				// ���� ������
				smileState = NORMAL_ON_SMILE;
				InvalidateRect(hwnd,&Invalid_SMILErect,FALSE);

			}
			else{

			// �������� ����Ѵ�...��� ������........
			smileState = SUPRSISE_SMILE;
			InvalidateRect(hwnd,&Invalid_SMILErect,TRUE);
			}




				


			
						
		}
		return 0;




	case WM_TIMER :{

		// Ÿ�̸Ӹ� ������ �κ��� ��ȿȭ����
		RECT timeRect={109,14,150,40};
		
		// timer�� ����ɶ� ���� ��ī��Ʈ ����
		timeCount++;
			
		// �ð��� 999�ʱ����� �����ش� ���̻��϶��� Ÿ�̸Ӹ� ���δ�
		if (timeCount== 999)
			KillTimer(hwnd,1);			// timerī��Ʈ�� 999���� ���� Ÿ�̸Ӹ� �׿���

		printf("INITMINE = %d \n",INITMINE);
		InvalidateRect(hwnd,&timeRect,TRUE);
		}
		return 0;
			



			
//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------

	case WM_RBUTTONDOWN	:
		{
			int i,j;
			// Ŭ���̾�Ʈ ������ ��ǥ��
			ClntPos = MAKEPOINTS(lParam);

			// �迭������ ��� ���� ��ǥ��.
			ArrayPos.x = (ClntPos.x-12) / 16 ;
			ArrayPos.y = (ClntPos.y-55) / 16 ;


						
			// ����ã���� �� ���콺 ��ǥ�� �Ѱ����� �д�
			if( (  (ClntPos.x>=Client.miniPos.x)&&(ClntPos.x<=Client.miniPos.xx+15)  ) && 
				// Ŭ���̾�Ʈ X��ǥ�� �����簢���� ������ǥ���� ũ�ų� ����
				// Ŭ���̾�z X��ǥ�� ���� �������� X�� ��������ǥ�� ���۰����� �۰ų� ���ƾߵȴ�
				(  (ClntPos.y>=Client.miniPos.y)&&(ClntPos.y<=Client.miniPos.yy+15)  )  ){
				// Ŭ���̾�Ʈ Y��ǥ�� �����簢���� ������ǥ���� ũ�ų� ����
				// Ŭ���̾�Ʈ Y��ǥ�� ���� �簢���� Y�� ��������ǥ�� �������� �۰ų� ������ȴ�
				
			
				// ���� RBUTTONDOWN��ǥ
				

				// FLAG ��ǥ�� �Ӽ��� FLAG�� ���� �÷��� ī��Ʈ�� ���̱�
				if (G_BOARD(ArrayPos.x,ArrayPos.y).isOpen == CLOSE){
					G_BOARD(ArrayPos.x,ArrayPos.y).isOpen = FLAG;		// �Ӽ��� FLAG�� ���´�
					WMFlagCount--;										// �÷��� ī��Ʈ�� ���δ�

					// ���� �÷��׸� �������� ���� �ڸ���� ���� ī��Ʈ�� �ϳ� ���� ���Ѷ�
					if(G_BOARD(ArrayPos.x,ArrayPos.y).state == BOMB)
						INITMINE--;

					//------------------------------------------------------
					// ���ڸ� ��� ã����� ............
					//------------------------------------------------------
					//------------------------------------------------------
					//	���� ī��Ʈ ������ 0���̰� ��ü ��ǥ���� ������ ã�� ���ڰ���
					
					if (INITMINE == 0){
						// ���������Ƿ�
						isOpenCount=0;

						// �Ʒ��� ��Ա����� OPEN�� � ���ֳ� �����
						for (i = 0 ; i < Xp ; i++){
							for (j = 0 ; j < Yp ; j++){
								if(G_BOARD(i,j).isOpen == OPEN)  isOpenCount++;
							}
						}

						if (Xp*Yp-MINEMINE == isOpenCount) {

							//////////////////////////////////////////////////////////////////
							// ��۶� �� �������� ����Ѵ�
							//////////////////////////////////////////////////////////////////
							smileState = GLASS_SMILE;
							InvalidateRect(hwnd,&Invalid_SMILErect,FALSE);

							G_BOARD(ArrayPos.x,ArrayPos.y).isOpen = FLAG;
							

							// Ÿ�̸Ӹ� ���δ�
							KillTimer(hwnd,1);
							
							// ��� ����
							for(j = 0; j <Yp ;++j)					// x�� = i = Xp
								for(i = 0; i <Xp ; ++i)
									G_BOARD(i,j).isOpen = OPEN;				
						}//	if (Xp*Yp-MINEMINE ) close
					}	// if (INITMINE == 0){ close


				}else if ( G_BOARD(ArrayPos.x,ArrayPos.y).isOpen == FLAG){
					G_BOARD(ArrayPos.x,ArrayPos.y).isOpen =QUESTION;
					WMFlagCount++;

					// ���� �÷��׸� ���� �Ѱ��� ���� �ڸ���� ���� ī��Ʈ �ϳ��� ���� ���Ѷ�
					if(G_BOARD(ArrayPos.x,ArrayPos.y).state == BOMB)
						INITMINE++;

				}
				else if (G_BOARD(ArrayPos.x,ArrayPos.y).isOpen == QUESTION){
					//printf("X = %d Y= %d\n" ,ArrayPos.x,ArrayPos.y);
					//printf("QUESTION�Դϴ�---FLAG�� �ٲٰڽ��ϴ�\n");
					G_BOARD(ArrayPos.x,ArrayPos.y).isOpen = CLOSE;
				}


			}	// ��ǥ ���� if��

				
			RECT RBrect = {GetClntX(ArrayPos.x),GetClntY(ArrayPos.y),
				GetClntX(ArrayPos.x)+16,GetClntY(ArrayPos.y)+16};
			RECT FLAGRect = {Client.third.x,Client.third.y,Client.third.xx,Client.third.yy};
			printf("x1=%d,y1=%d,x2=%d,y2=%d\n",GetClntX(ArrayPos.x),GetClntY(ArrayPos.y),GetClntX(ArrayPos.x+16),GetClntY(ArrayPos.y+16));


			InvalidateRect(hwnd,&FLAGRect,FALSE);
			InvalidateRect(hwnd,&RBrect,FALSE);
		}

		return 0;
	case WM_LBUTTONUP : 
		{
			int i,j;
			
			// Ŭ���̾�Ʈ ������ ��ǥ��
			ClntPos = MAKEPOINTS(lParam);

			// �迭������ ��� ���� ��ǥ��.
			ArrayPos.x = (ClntPos.x-12) / 16 ;
			ArrayPos.y = (ClntPos.y-55) / 16 ;


			


			if (mineSettingFLAG == FALSE){			 // ó�� ���콺�� Ŭ���ϴ°��
				
				
				// timer
				SetTimer(hwnd ,1, 1000, 0);	  // 1�� Ÿ�̸� �߻� 1�ʿ� �ѹ���.
											  // Ÿ�̸ӽɱ�
				timeCount=0;				  // Ÿ�̸� ���� �ʱ�ȭ	
				timeF=timeS=timeT=0;		  // Ÿ�̸Ӹ� ī������ ����

						
				// ���ε�. ���ڸ� �ְ� ���ڸ� �ʱ�ȭ�ϴ� �Լ� ȣ��
				// ù��° ��ǥ�� �Ѱܼ� ���ڸ��� ���ڸ� �ʳִ´�
				Binding(INITMINE , Xp , Yp,ArrayPos.x,ArrayPos.y);	 
				//printf("--INITMINE = %d      ###########################\n ", INITMINE);

				WMFlagCount=INITMINE;			// ����� ī���� - �ʱ�ȭ�� �⺻ ��ź����

				// FLAG�� �ٲ㼭 ������ �ٽ� ����������
				mineSettingFLAG = TRUE;		  
			}
			




			// Ŭ���̾�Ʈ �������� ��ǥ�� �������� x1 ��ǥ�δ� ũ�ų� ����
			// Ŭ���̾�Ʈ �������� ��ǥ�� �������� x2 ��ǥ�δ� �۰ų� ����
			if( ( (ClntPos.x >= Client.smile.x+2) && (ClntPos.x <= Client.smile.xx-2) ) &&
				(ClntPos.y >= Client.smile.y+2) && (ClntPos.y <= Client.smile.yy-2) ) {
				
				//smileState = NORMAL_SMILE;
				//InvalidateRect(hwnd,&Invalid_SMILErect,FALSE);
				//Init(Xp,Yp,INITMINE);

				//g_board = (BLOCK*)malloc(sizeof(BLOCK)*Xp*Yp);
				// �ϴ� �޸𸮸� Ǯ���ְ� �ٽ����

				// �ʱ�
				//if(g_board !=NULL){
					free(g_board);
					printf("�޸� ����~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

				//}
				Init(9,9,10);

				timeCount=0;				  // Ÿ�̸� ���� �ʱ�ȭ	
				timeF=timeS=timeT=0;		  // Ÿ�̸Ӹ� ī������ ����
				
				RECT rc2 = { 0,0,Client.first.xx,Client.first.yy+35 };	// +35�� �Ʒ� ����
				WMFlagCount=INITMINE;			// ����� ī���� - �ʱ�ȭ�� �⺻ ��ź����
				style = GetWindowLong( hwnd, GWL_STYLE);
				style &= ~WS_THICKFRAME;
				SetWindowLong( hwnd, GWL_STYLE, style );
				AdjustWindowRect( &rc2, style, FALSE );
				MoveWindow(hwnd, 0, 0, rc2.right - rc2.left, rc2.bottom - rc2.top, TRUE);

				
				
				WMFlagCount=INITMINE;			// ����� ī���� - �ʱ�ȭ�� �⺻ ��ź����
				
				KillTimer(hwnd,1);				// Ÿ�̸Ӹ� ���δ�
				timeF=timeS=timeT=0;		  // Ÿ�̸Ӹ� ī������ ����

				mineSettingFLAG = FALSE;		// ���콺 ó��Ŭ���ؼ� ���ڼ����ϱ� ���ؼ� FALSE�� �ٽð�ģ��


				RECT rc = { 0,0,Client.first.xx,Client.first.yy+35 };	// +35�� �Ʒ� ����
				InvalidateRect(hwnd,&rc,TRUE);

			}

			//---------------------------------------------------------
			// ������ ���
			//---------------------------------------------------------
			// Ŭ���� ��ǥ�� ��ź�� ���ٸ� �Ϲ� �������� ����Ѵ�
			//---------------------------------------------------------
			if (G_BOARD(ArrayPos.x,ArrayPos.y).state != BOMB ){
				smileState = NORMAL_SMILE;
				InvalidateRect(hwnd,&Invalid_SMILErect,FALSE);
			}
			else if ( isDieFlag ==TRUE){
				smileState = DISAPEAR_SMILE;
				InvalidateRect(hwnd,&Invalid_SMILErect,FALSE);
			}


			// Ŭ���Ѱ��� ��ǥ�� �־ ���ӿ��� ������ ������ ����� ������ش�
							
			
			



			
			// ����ã���� �� ���콺 ��ǥ�� �Ѱ����� �д�

			if( (  (ClntPos.x>=Client.miniPos.x)&&(ClntPos.x<=Client.miniPos.xx+15)  ) && 
				// Ŭ���̾�Ʈ X��ǥ�� �����簢���� ������ǥ���� ũ�ų� ����
				// Ŭ���̾�z X��ǥ�� ���� �������� X�� ��������ǥ�� ���۰����� �۰ų� ���ƾߵȴ�
				(  (ClntPos.y>=Client.miniPos.y)&&(ClntPos.y<=Client.miniPos.yy+15)  )  &&
				// Ŭ���̾�Ʈ Y��ǥ�� �����簢���� ������ǥ���� ũ�ų� ����
				// Ŭ���̾�Ʈ Y��ǥ�� ���� �簢���� Y�� ��������ǥ�� �������� �۰ų� ������ȴ�
				(isDieFlag ==FALSE)){				
				// ���ڸ� ��� �����ʾҾ�� �Ѵ�
			
				// ���� CLICKUP��ǥ�� ���ڰ��ƴ� ���
				// ���ڰ� �ƴҰ�찡 �����⿡ ù��° if�� ����

	

				 if ( G_BOARD(ArrayPos.x,ArrayPos.y).isOpen == FLAG) {
					printf("�÷��׶��................\n");
					printf("�÷��׶��................\n");
					printf("�÷��׶��................\n");
					printf("�÷��׶��................\n");
					printf("�÷��׶��................\n");
					
				// �׸��� ��� ���´� Ŭ���ϸ�ȵȴ�


					
				//------------------------------------------------------	
				//------------------------------------------------------
				// Ŭ���Ѱ��� ��ź�̶��............
				//------------------------------------------------------
				//------------------------------------------------------

				}else if (G_BOARD(ArrayPos.x,ArrayPos.y).state == BOMB){
					
				
					

					//Ŭ���ϸ� ������ ���ڸ������ �Ӽ��� �ٲ��ش�
					G_BOARD(ArrayPos.x,ArrayPos.y).state = CLICKBOMB;
					// �ڱ��ڽ��� ����
					G_BOARD(ArrayPos.x,ArrayPos.y).isOpen =OPEN;

					// �ȿ��� ������ ���ڵ��� ��� �����ش�
					for(j = 0; j <Yp ;++j)					// x�� = i = Xp
						for(i = 0; i <Xp ; ++i)
							if (G_BOARD(i,j).state == BOMB)
								G_BOARD(i,j).isOpen = OPEN;	

					
					// �׸��� ���ڸ� Ŭ�������Ƿ� Ÿ�̸Ӹ� ���δ�
					KillTimer(hwnd,1);


					// Ŭ���� ��ǥ�� ��ź�� �ִٸ� �λ� ������
					smileState = DISAPEAR_SMILE;
					InvalidateRect(hwnd,&Invalid_SMILErect,FALSE);

					// ���ӿ��� ���ٴ� �÷���..�����Ƿ� ������ Ȱ��ȭ ��ų������ ���ӿ����� �����´�
					isDieFlag = TRUE;

							
					
				
				}	// if end
					

				//------------------------------------------------------	
				//------------------------------------------------------
				// Ŭ���Ѱ��� �Ӽ��� EMPTY��� ............
				//------------------------------------------------------
				//------------------------------------------------------

				else if (G_BOARD(ArrayPos.x,ArrayPos.y).state == EMPTY||
					G_BOARD(ArrayPos.x,ArrayPos.y).state == ONE||
					G_BOARD(ArrayPos.x,ArrayPos.y).state == TWO||
					G_BOARD(ArrayPos.x,ArrayPos.y).state == THREE||
					G_BOARD(ArrayPos.x,ArrayPos.y).state == FOUR||
					G_BOARD(ArrayPos.x,ArrayPos.y).state == FIVE||
					G_BOARD(ArrayPos.x,ArrayPos.y).state == SIX||
					G_BOARD(ArrayPos.x,ArrayPos.y).state == SEVEN){
					
					// ��Ī�ؼ� ������ ��ź�̾����� �ٿ����ش�
					G_BOARD(ArrayPos.x,ArrayPos.y).isOpen = OPEN;
					EmptySearching(ArrayPos.x,ArrayPos.y);
					
				}				
				

				//------------------------------------------------------	
				//------------------------------------------------------
				// ���ڸ� ��� ã����� ............
				//------------------------------------------------------
				//------------------------------------------------------
				//	���� ī��Ʈ ������ 0���̰� ��ü ��ǥ���� ������ ã�� ���ڰ���
				
				else if (INITMINE == 0){
					// ���������Ƿ�

					
					printf("INITMINE = %d\n", INITMINE);
					printf("isOpenCount= %d\n" , isOpenCount );
					printf("Xp*Yp-MINEMINE = %d\n" ,(Xp*Yp)-MINEMINE);

					printf("Xp = %d \n Yp = %d \n" , Xp, Yp);

					// �Ʒ��� ��Ա����� OPEN�� � ���ֳ� �����
					for (i = 0 ; i < Xp ; i++){
						for (j = 0 ; j < Yp ; j++){
							if(G_BOARD(i,j).isOpen == OPEN)  isOpenCount++;
						}
					}

					
					// �� �迭�� �������� ������ ������ŭ�� ����. 
					// 8*8�� ��� 64 -10 (���ڰ���) 
					// 54�� ��ŭ OPEN�̵Ǿ� �־�� �Ѵ�
					
					if (Xp*Yp-MINEMINE == isOpenCount) {

						//////////////////////////////////////////////////////////////////
						// ��۶� �� �������� ����Ѵ�
						//////////////////////////////////////////////////////////////////
						smileState = GLASS_SMILE;
						InvalidateRect(hwnd,&Invalid_SMILErect,FALSE);
						


						// Ÿ�̸Ӹ� ���δ�
						KillTimer(hwnd,1);
						
						// ��� ����
						for(j = 0; j <Yp ;++j)					// x�� = i = Xp
							for(i = 0; i <Xp ; ++i)
								G_BOARD(i,j).isOpen = OPEN;				
					}//	if (Xp*Yp-MINEMINE ) close
				}	// if (INITMINE == 0){ close
						
				else{
					// LBUTTON�� ���� �迭�� �Ӽ��� ON���� ��ħ.. 
					G_BOARD(ArrayPos.x,ArrayPos.y).isOpen = OPEN;					
				}	// else close
						

				
					printf("\n\n\n----------------------------------------------\n");
					printf("------------------���� ����-----------------\n");
					printf("----------------------------------------------\n");
					for ( j = 0 ; j < Yp ; ++j){
						for(i = 0 ; i < Xp ; ++i){
					printf("%2d ",G_BOARD(i,j).state);
					}
					printf("\n");
					}

					printf("\n\n\n----------------------------------------------\n");
					printf("------------------IS OPEN-----------------\n");
					printf("----------------------------------------------\n");
					for ( j = 0 ; j < Yp ; ++j){
						for(i = 0 ; i < Xp ; ++i){
					printf("%2d ",G_BOARD(i,j).isOpen);
					}
					printf("\n");
					}


				InvalidateRect(hwnd,0,FALSE);
				
			}
			
		}
		return 0;


//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------		
	case WM_PAINT:
		{		

		int i, j;

		hdc = BeginPaint( hwnd, &ps );	
		MemDC=CreateCompatibleDC(hdc);


//////////////////////////////////////////////////////////////////////////////////////////////
//									ȭ�� ��ü�� Ʋ
//////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////


		//===========================�޴� �� ��ư �׸���
		Draw3dRect( hdc, Client.first.x,   Client.first.y,  
			Client.first.xx, Client.first.yy , FALSE, 3 );		// �޴��Ʒ� Ŭ���̾�Ʈ ���ۺ���
		Draw3dRect( hdc, Client.second.x,   Client.second.y,  
			Client.second.xx, Client.second.yy,  TRUE,  2 );		
		Draw3dRect( hdc, Client.third.x,  Client.third.y, 
			Client.third.xx,  Client.third.yy,  TRUE,  1 );
		Draw3dRect( hdc, Client.four.x, Client.four.y,
			Client.four.xx, Client.four.yy,  TRUE,  1 );
		Draw3dRect( hdc, Client.five.x, Client.five.y, 
			Client.five.xx, Client.five.yy, TRUE,  3 );

		//Draw3dRect(hdc , Client.smile.x ,Client.smile.y ,Client.smile.xx ,Client.smile.yy,
		//	FALSE, 2);

		// ���콺 Ŭ���� ��� CLOSE OPEN ������ ������ ���� ������ �����ش�
		// ���� ������쿡�� 
		// ù���� dc , �ι�° �׸� x1, �ι�° y1. ����° x2 �׹�° y2



//////////////////////////////////////////////////////////////////////////////////////////////
//									ȭ�� ��ܿ� ��µǴ� �κ�
//////////////////////////////////////////////////////////////////////////////////////////////
//=================Ÿ�̸�=========================
///////////////////////////////////////////////////


		// ī��Ʈ�� ǥ�����ش�..
		// time ī��Ʈ
		timeF = timeCount/100;			// 100����
		timeS = (timeCount%100)/10;		// 10����
		timeT = timeCount %10;			// 1����

		
		MemDC = CreateCompatibleDC(hdc);
		MyBitmap = LoadBitmap(g_hInst,MAKEINTRESOURCE(IDB_BITMAP2));		// ������� ��Ʈ��
		OldBitmap = (HBITMAP)SelectObject(MemDC,MyBitmap);
		// timeF--100���� Ÿ�̸�
		StretchBlt(hdc, Client.four.x+1 , Client.four.y+2,	// ���� x,y��ǥ 4��° �����Ӻ��� +1,+2��ġ�̴�
						13,23,MemDC , 0,
						timePos[timeF],						// timePos(��Ʈ�ʿ��� �о�� Y����ǥ) Ÿ���� �ε�����)
						13,23,SRCCOPY);					    // x������ 13��ŭ Y������ 23��ŭ ī��
		// timeS--10���� Ÿ�̸�
		StretchBlt(hdc, Client.four.x+1+13 , Client.four.y+2,
						13,23,MemDC , 0,timePos[timeS],13,23,SRCCOPY);		
		// timeT--1���� Ÿ�̸�
		StretchBlt(hdc, Client.four.x+1+13+13 , Client.four.y+2,		
						13,23,MemDC , 0,timePos[timeT],13,23,SRCCOPY);		

		SelectObject(MemDC,OldBitmap);
		DeleteObject(MyBitmap);
		DeleteDC(MemDC);



//////////////////////////////////////////////////////////////////////////////////////////////
//									ȭ�� ��ܿ� ��µǴ� �κ�
//////////////////////////////////////////////////////////////////////////////////////////////
//=================flagī��Ʈ=========================
//////////////////////////////////////////////////////


		// flag ī��Ʈ
		// 100�����÷��״� �÷��� ī���Ͱ� 0���������� -ī���Ϳ뵵�� �ε��� 11��
		// 0���� Ŭ�� 100���� ���ڸ��ִ´�
		flagF = (WMFlagCount<0) ?	10 :  WMFlagCount/100;			// 100����
		flagS = (WMFlagCount%100)/10;		// 10����
		flagS = (flagS<0) ? -flagS : flagS;
		flagT = WMFlagCount %10;			// 1����
		flagT = (flagT<0) ? -flagT : flagT;

		printf("flagF=%d , flagS=%d ,flagT=%d \n", flagF,flagS,flagT);

		MemDC = CreateCompatibleDC(hdc);
		MyBitmap = LoadBitmap(g_hInst,MAKEINTRESOURCE(IDB_BITMAP2));		// ������� ��Ʈ��
		OldBitmap = (HBITMAP)SelectObject(MemDC,MyBitmap);
		// flagF--100���� Ÿ�̸� or ��ȣ
		StretchBlt(hdc, Client.third.x+1 , Client.third.y+2,	// ���� x,y��ǥ 4��° �����Ӻ��� +1,+2��ġ�̴�
						13,23,MemDC , 0,
						timePos[flagF],						// timePos(��Ʈ�ʿ��� �о�� Y����ǥ) Ÿ���� �ε�����)
						13,23,SRCCOPY);					    // x������ 13��ŭ Y������ 23��ŭ ī��
		// flagS--10���� Ÿ�̸�
		StretchBlt(hdc, Client.third.x+1+13 , Client.third.y+2,
						13,23,MemDC , 0,timePos[flagS],13,23,SRCCOPY);		
		// flagT--1���� Ÿ�̸�
		StretchBlt(hdc, Client.third.x+1+13+13 , Client.third.y+2,
						13,23,MemDC , 0,timePos[flagT],13,23,SRCCOPY);		

		SelectObject(MemDC,OldBitmap);
		DeleteObject(MyBitmap);
		DeleteDC(MemDC);


//////////////////////////////////////////////////////////////////////////////////////////////
//									ȭ�� ��ܿ� ��µǴ� �κ�
//////////////////////////////////////////////////////////////////////////////////////////////
//=================������=========================
///////////////////////////////////////////////////
		// �������� ���¿� ���� �������� ����Ѵ�.
		//			smileState

		MemDC = CreateCompatibleDC(hdc);
		MyBitmap = LoadBitmap(g_hInst,MAKEINTRESOURCE(IDB_BITMAP3));		// ������ ��� ��Ʈ��
		OldBitmap = (HBITMAP)SelectObject(MemDC,MyBitmap);
		StretchBlt(hdc, Client.smile.x , Client.smile.y+2,	// ���� x,y��ǥ 
						24,24,MemDC , 0,
						smilePos[smileState],				// smilePos�迭�� �ε����� smileState�� �����Ѵ�
						24,24,SRCCOPY);					    // x������ 26��ŭ Y������ 26��ŭ ī��
		SelectObject(MemDC,OldBitmap);
		DeleteObject(MyBitmap);
		DeleteDC(MemDC);




//////////////////////////////////////////////////////////////////////////////////////////////
//									ȭ�� �ϴܿ� ��µǴ� �κ�
//////////////////////////////////////////////////////////////////////////////////////////////
//=================����ã��=========================
/////////////////////////////////////////////////////



		// ������� ��ǥ i�� 0���� �����ؼ� i���� Xp.. �� ���� �����ŭ..(�迭�̴ϱ� Xp�� ���Ծȵȴ�)
		// ������� ��ǥ j�� 0���� �����ؼ� j���� Yp.. �� ���� �����ŭ
		// Ŭ���̾�Ʈ �������� �ּҷ� �ٲپ ����....
		
		for(j = 0 ; j < Yp ; j++){			// x�� = i  = Xp
			for(i = 0 ; i < Xp ; i++){
				//Draw3dRect( hdc, x, y, x + 15, y + 15, FALSE, 2 );

				if(G_BOARD(i,j).isOpen == CLOSE)							//isOpen == CLOSE�ϰ��
				{
					//Draw3dRect( hdc,12+(i*16),55+(j*16),12+((i+1)*16)-1,55+((j+1)*16)-1,FALSE,2);
					MemDC = CreateCompatibleDC(hdc);
					MyBitmap = LoadBitmap(g_hInst,MAKEINTRESOURCE(IDB_BITMAP1));
					OldBitmap = (HBITMAP)SelectObject(MemDC,MyBitmap);
					StretchBlt(hdc, 
						Client.miniPos.x+(i*16) , Client.miniPos.y+(j*16),	// ���� x,y��ǥ
						16,16,												// X�� 15 y�� 15��ŭ ī��
						MemDC , 0,0,16,16,SRCCOPY);
					SelectObject(MemDC,OldBitmap);
					DeleteObject(MyBitmap);
					DeleteDC(MemDC);
				//	printf("G_BOARD(%d,%d).isOpen ===CLOSE = %d\n",i,j,G_BOARD(i,j).isOpen);
					
				}					
				else if ( G_BOARD(i,j).isOpen == OPEN )						//isOpen == CLOSE
				{
				//	printf("G_BOARD(%d,%d).isOpen ===OPEN = %d\n",i,j,G_BOARD(i,j).isOpen);

					// �޸� �Ҵ��ϰ� ���ҽ� �Ҹ��� �ε��� ��Ʈ�� ����
					MemDC = CreateCompatibleDC(hdc);						
					MyBitmap = LoadBitmap(g_hInst,MAKEINTRESOURCE(IDB_BITMAP1));
					OldBitmap = (HBITMAP)SelectObject(MemDC,MyBitmap);
					
					// �о���µ� �޸𸮻� y��ǥ�� �迭���� �����´�
					StretchBlt(hdc, 
						Client.miniPos.x+(i*16) , Client.miniPos.y+(j*16),	// ���� x,y��ǥ
						16,16,												// X�� 15 y�� 15��ŭ ī��
						MemDC , 0,picPos[G_BOARD(i,j).state],16,16,SRCCOPY);
					
					// �ڿ�����
					SelectObject(MemDC,OldBitmap);
					DeleteObject(MyBitmap);
					DeleteDC(MemDC);
					
				}
				else if ( G_BOARD(i,j).isOpen == FLAG )						//isOpen == CLOSE
				{
				//	printf("G_BOARD(%d,%d).isOpen ===FLAG = %d\n",i,j,G_BOARD(i,j).isOpen);

					// �޸� �Ҵ��ϰ� ���ҽ� �Ҹ��� �ε��� ��Ʈ�� ����
					MemDC = CreateCompatibleDC(hdc);						
					MyBitmap = LoadBitmap(g_hInst,MAKEINTRESOURCE(IDB_BITMAP1));
					OldBitmap = (HBITMAP)SelectObject(MemDC,MyBitmap);
					
					// �о���µ� �޸𸮻� y��ǥ�� �迭���� �����´�
					StretchBlt(hdc, 
						Client.miniPos.x+(i*16) , Client.miniPos.y+(j*16),	// ���� x,y��ǥ
						16,16,												// X�� 15 y�� 15��ŭ ī��
						MemDC , 0,picPos[FLAG],16,16,SRCCOPY);
					
					// �ڿ�����
					SelectObject(MemDC,OldBitmap);
					DeleteObject(MyBitmap);
					DeleteDC(MemDC);
					
				}else if ( G_BOARD(i,j).isOpen == QUESTION )						//isOpen == CLOSE
				{
					//printf("G_BOARD(%d,%d).isOpen ===OPEN = %d\n",i,j,G_BOARD(i,j).isOpen);

					// �޸� �Ҵ��ϰ� ���ҽ� �Ҹ��� �ε��� ��Ʈ�� ����
					MemDC = CreateCompatibleDC(hdc);						
					MyBitmap = LoadBitmap(g_hInst,MAKEINTRESOURCE(IDB_BITMAP1));
					OldBitmap = (HBITMAP)SelectObject(MemDC,MyBitmap);
					
					// �о���µ� �޸𸮻� y��ǥ�� �迭���� �����´�
					StretchBlt(hdc, 
						Client.miniPos.x+(i*16) , Client.miniPos.y+(j*16),	// ���� x,y��ǥ
						16,16,												// X�� 15 y�� 15��ŭ ī��
						MemDC , 0,picPos[QUESTION],16,16,SRCCOPY);
					
					// �ڿ�����
					SelectObject(MemDC,OldBitmap);
					DeleteObject(MyBitmap);
					DeleteDC(MemDC);
					
				}// if�� ����	
			}		// �ι�° for
		}		//	ù��° for

  


		TextOut(hdc,ClntPos.x+5 , ClntPos.y+10 , str , lstrlen(str));
		EndPaint( hwnd, &ps );
		}
		return 0;

		


//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------


	case WM_DESTROY: 
		PostQuitMessage(0);					 
		return 0;
	}
	
	return DefWindowProc( hwnd, msg, wParam, lParam);
}






//=======================WinMain=================================
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
					LPSTR	  lpCmdLine, int nShowCmd )
	{

	// GUI�� Console�� �����Ҽ� �ִ�
	AllocConsole();

	// stdout�� console�� �����Ѵ�
	freopen("CONOUT$","wt",stdout);		// CONSOUT$ : console ���
										// wt : write text �ؽ�Ʈ ���� ���
										// ���� �����͸� �ٽ� �����Ҷ� ���� ���



	g_hInst = hInstance;
	WNDCLASS wc;
	wc.cbClsExtra	= 0;
	wc.cbWndExtra	= 0;
	wc.hbrBackground= (HBRUSH)GetStockObject( WHITE_BRUSH ); 
	wc.hCursor		= LoadCursor( 0, IDC_ARROW );
	wc.hIcon		= LoadIcon( hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wc.hInstance	= hInstance;
	wc.lpfnWndProc  = WndProc; 
	wc.lpszClassName= "First";
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	wc.style		= 0;
	ATOM atom = RegisterClass( &wc); 
	if ( atom == 0 ) 
	{
		MessageBox( 0, "Fail To RegisterClass", "Error", MB_OK);
		return 0;
	}

	HWND hwnd = CreateWindowEx( WS_EX_APPWINDOW , "first", "���� ã��", WS_OVERLAPPEDWINDOW,
								CW_USEDEFAULT, CW_USEDEFAULT,0 ,0, 0, 0, 
								hInstance, 0); 
	ShowWindow( hwnd, nShowCmd); 
	UpdateWindow( hwnd );

	MSG msg;
	while ( GetMessage( &msg, 0, 0, 0) ) 
	{									 
		DispatchMessage( &msg );
	}

	return 0;
}

