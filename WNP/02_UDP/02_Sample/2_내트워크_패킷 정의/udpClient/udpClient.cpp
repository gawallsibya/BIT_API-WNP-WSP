//---------------------------------------------------------------------------------------------------
//��       �� : UDP �� TCP �����ϱ�
//Ŭ����   �� : udpClient 
//Ŭ���� ���� : Client �����ην�, three-way handshake ����� �����غ���. 
//�� �� �� �� : 2003�� 2�� 8��
//----------------------------------------------------------------------------------------------------

#include <winsock2.h>
#include <windows.h>
#include <stdio.h>


#define PACKET_SIZE 100

//---------------------------------------------------------------------------------------------------
// define ���� �κ� : ��Ŷ ���� ���� 
//---------------------------------------------------------------------------------------------------
#define DATA						1 // ������ ��Ŷ
#define ACK							2 // Ȯ�� ���� 
#define FAIL						3 // ����
#define SESSION_REQUEST				4 // connect ��û
#define SESSION_ACCEPTANCE			5 // accept
#define FILE_REQUEST				6 // ���� ���� ��û
#define FILE_ACCEPTANCE				7 // �������� ���� accept
#define FILE_TRANSFER_COMPLETE		8 // ���� ���� �Ϸ�
#define FIN							9 // ���� ����


//---------------------------------------------------------------------------------------------------
// ��Ŷ ����ü 
//---------------------------------------------------------------------------------------------------
struct packet{
	char	buf[PACKET_SIZE];			 // ����Ÿ ����, size�� 100���� define��	
	long	seq;						 // ��Ŷ ����
	int		ctrl_flag;					 // ��Ŷ�� ������ ��Ÿ���� �÷��� �� ����
}send_packet, recv_packet;


//---------------------------------------------------------------------------------------------------
// �Լ� ���� 
//---------------------------------------------------------------------------------------------------
void err_quit();						// ���� �߻��� ���� �Լ�
void set_send_packet();					// �۽� ��Ŷ �����Լ�
void send_state_print(int retval);		// �۽� ���� ��� �Լ�
void recv_state_print(int retval);		// ���� ���� ��� �Լ�


int main()
{
	WSADATA		wsa;					//���� �ʱ�ȭ�� �־��� �⺻ �ڷ� ���� ����
	int			retval;					//���� ó���� ����� ��
	SOCKET		s;						//send�� ���� 
	int			pack_count = 0;			//��Ŷ�� ���� Counting 

	
	//1. Winsock�� �ʱ�ȭ �Ѵ�. ������ 2.2
	retval  = WSAStartup(MAKEWORD(2,2), &wsa);
	if(retval != 0) err_quit();


	//2. ������ �����Ѵ�.(UDP���� �������� Setting) 
	s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if(s == INVALID_SOCKET) err_quit();
	
	//3. �������� �ϴ� ������ �ּҸ�  �����Ѵ�.
	SOCKADDR_IN serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(5150);
	serv_addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");


	struct sockaddr_in sender;
	int sender_size = sizeof(packet);  

	FILE* fp; // ���� ������ ���� ������
	static int seq;

	memset(&recv_packet, 0, sizeof(packet));
	
	// ���� ���� ���� ��û ���·� �����Ѵ�.
	recv_packet.ctrl_flag = SESSION_REQUEST; 

	printf("\t========================================================\n");
	printf("\t=             [Client PROGRAM]                         = \n"); 
	printf("\t========================================================\n");
	printf("\n-->[Client]Server�� ���� ��û ��Ŷ�� �������� ����Ű�� �������� : [ ]\b\b");
	if(getchar() == '\n')
	{
		printf("\n\n[Client] : ���� ��û ��Ŷ�� �����ϴ�.\n");
	}

	while(recv_packet.ctrl_flag != FIN) 
	{
		set_send_packet();
		
		//4.��Ŷ�� �����Ѵ�. 
		retval = sendto(s, (char*)&send_packet, sizeof(send_packet), 0, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

		send_state_print(retval); // ���� �۽� ���� ���

		//5. ��Ŷ�� �����Ѵ�. 
		memset(&recv_packet, 0, sizeof(packet));
		retval = recvfrom(s, (char*)&recv_packet, sizeof(packet),  0, (SOCKADDR*)&sender, &sender_size);
		if(retval == SOCKET_ERROR) err_quit();
		else if(!retval) 
		{
			printf("[ERROR] can't receive data\n");
		break;
		}
		else
		{
			switch(recv_packet.ctrl_flag) 
			{			

			case FILE_ACCEPTANCE:		//���� ��û�� ����� ������ 
				fp = fopen(recv_packet.buf, "wb");

				if(fp == NULL)
				{
					printf("%s ���� ���� ����\n", recv_packet.buf);
					exit(1);
				}

				printf("recv : %s", recv_packet.buf);				
				break;

			case DATA:					//�����Ͱ� �Ѿ�ö� 
				fseek(fp, (recv_packet.seq*100), SEEK_SET); // ���� CP ����				
				fwrite(recv_packet.buf, 1, 100, fp);
				printf("recv : data packet(seq.%d)", recv_packet.seq);
				break;

			case FILE_TRANSFER_COMPLETE:	//���� ������ ������ ���
				fclose(fp);
				printf("recv : %s\n", "FILE TRANSPER COMPLETE");				
				printf("[CLIENT] : ���� ������ �Ϸ�Ǿ����ϴ�. 'a.txt'������ Ȯ���ϼ���\n\n");
				printf("[CLIENT] : ������ �����մϴ�.\n\n");
				break;
			
			case ACK:		//���� �����͸� �޾��� ���
				fseek(fp, (seq*100), SEEK_SET); // ���� CP ����				
				fwrite(recv_packet.buf, 1, 100, fp);
				printf("recv : data packet(seq.%d)", seq);
				break;

			default:
				printf("recv : %s\n", recv_packet.buf);				
			}	
		}
		printf("\n");		
		Sleep(1000);
	}

	//6. ������ �ݴ´�.
	retval = closesocket(s);
	if(retval == SOCKET_ERROR) err_quit();

	//7. �������� �����Ѵ�.  
	retval = WSACleanup();
	if(retval != 0) err_quit();

	return 0;
}

//---------------------------------------------------------------------------------------
// �Լ�   �� : err_quit()
//      ���� : ���õ� ������ ������ �޽��� �ڽ��� ���ؼ� �˷��ش�.
//             ���� �޽��� �ڽ� Ȯ�ν� �����Ų��.
//      ���� : ���� ���� �� ������������ ���� Ȯ�� ���
//---------------------------------------------------------------------------------------
void err_quit()
{
	LPVOID lpMsgBuf;

	//���� ���� �޼��� ���ۿ� ���
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
					FORMAT_MESSAGE_FROM_SYSTEM |
					FORMAT_MESSAGE_IGNORE_INSERTS,
					NULL, WSAGetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
					(LPTSTR)&lpMsgBuf, 0, NULL);

	MessageBox(NULL, (LPCTSTR)lpMsgBuf, "����", MB_OK | MB_ICONINFORMATION);

	LocalFree(lpMsgBuf); // �޼��� ���� ����
	
	exit(1);
}


//---------------------------------------------------------------------------------------
// �Լ�   �� : send_state_print(int retval) 
//      ���� : ���� �۽� ���¸� console ȭ�鿡 ��½����ش�. 
//      ���� : retval - ������ üũ�ϱ����� sendTo�� ���ϰ��� �޾� �´�.
//				        ���� 0�̸� �۽��� �ȉ�ٴ� �޽����� ����ϰ�,
//						�� �̿��� ���̸� ��Ŷ�� ��� buf�� ������ ����Ѵ�.
//---------------------------------------------------------------------------------------
void send_state_print(int retval) // ���� �۽� ���� ���
{
	if(retval == SOCKET_ERROR) err_quit();
	else if(retval == 0) 
	{
		printf("[ERROR] can't send data\n");
		exit(1);
	}
	else printf("send : %s\n", send_packet.buf);	
}


//---------------------------------------------------------------------------------------
// �Լ�   �� : recv_state_print(int retval) 
//      ���� : ���� ���� ���¸� console ȭ�鿡 ��½����ش�. 
//      ���� : retval - ������ üũ�ϱ����� sendTo�� ���ϰ��� �޾� �´�.
//				        ���� 0�̸� �۽��� �ȉ�ٴ� �޽����� ����ϰ�,
//						�� �̿��� ���̸� ��Ŷ�� ��� buf�� ������ ����Ѵ�.
//---------------------------------------------------------------------------------------
void recv_state_print(int retval) // ���� ���� ���� ���
{
	if(retval == SOCKET_ERROR) err_quit();
	else if(!retval) 
	{
		printf("[ERROR] can't receive data\n");
		exit(1);
	}
	else printf("recv : %s\n", recv_packet.buf);
	printf("\n");		
}


//---------------------------------------------------------------------------------------
// �Լ�   �� : set_send_packet()
//      ���� : �������� �ϴ� ��Ŷ�� ������ �ʱ�ȭ, �����Ѵ�. 
//      ���� : ��Ŷ�� flag ���� ���� ���е� ��Ŷ ���� 
//---------------------------------------------------------------------------------------
void set_send_packet() // �۽� ��Ŷ ����
{	
	// �۽� ��Ŷ �ʱ�ȭ
	memset(&send_packet, 0, sizeof(send_packet));
	// ���ŵ� ��Ŷ�� �÷��׿� ���� �۽� ��Ŷ ����
	
	switch(recv_packet.ctrl_flag) 
	{			
		case SESSION_ACCEPTANCE: // ���� ����		
			printf("----> ������ ���������� �̷�������ϴ�.\n\n\n");
			printf("-->[Client] : ������ ��û�Ϸ��� ����Ű�� �������� : [ ]\b\b");
			if(getchar() == '\n')
			{
				//������ �����Ǿ��� ��� ���� ������ ��û�Ѵ�. 
				send_packet.ctrl_flag = FILE_REQUEST;
				sprintf(send_packet.buf, "FILE_REQUEST -> for a.txt");
			}
			break;

		case FILE_ACCEPTANCE: // ���� ���ۿ�û ����
			send_packet.ctrl_flag = DATA;
			sprintf(send_packet.buf, "DATA REQUEST");
			break;

		case DATA: // ����Ÿ ������ �� 
			send_packet.ctrl_flag  = ACK;
			sprintf(send_packet.buf, "ACK data packet(seq, %d)\n", recv_packet.seq);				
			break;

		case FILE_TRANSFER_COMPLETE: // ���� ���� �Ϸ� �϶�							
			send_packet.ctrl_flag = FILE_TRANSFER_COMPLETE;
			sprintf(send_packet.buf, "FILE TRANSFER COMPLETE");
			break;

		case ACK:		//���� ������ ���� ACK�� ���� 
			send_packet.ctrl_flag = ACK;
			sprintf(send_packet.buf, "ACK (seq, %d)", recv_packet.seq);
			break;
		
		case SESSION_REQUEST:  		// ���� ���� �����û
			sprintf(send_packet.buf, "SESSION REQUEST");
			send_packet.ctrl_flag = SESSION_REQUEST;
			break;
	}
}