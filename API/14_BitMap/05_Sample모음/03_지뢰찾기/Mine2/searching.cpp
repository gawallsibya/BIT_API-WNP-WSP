#include <windows.h>
#include <stdio.h>
#include "resource.h"
#include "declar.h"



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