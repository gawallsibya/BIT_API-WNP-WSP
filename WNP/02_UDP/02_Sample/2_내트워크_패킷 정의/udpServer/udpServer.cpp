//---------------------------------------------------------------------------------------------------
//��       �� : UDP �� TCP �����ϱ�
//Ŭ����   �� : udpServer 
//Ŭ���� ���� : Server �����ην�, three-way handshake ����� �����غ���. 
//�� �� �� �� : 2003�� 2�� 8��
//----------------------------------------------------------------------------------------------------

#include <winsock2.h>
#include <windows.h>
#include <stdio.h>

#define BUFFER_SIZE 100 

//---------------------------------------------------------------------------------------------------
// define ���� �κ� : ��Ŷ ���� ���� 
//---------------------------------------------------------------------------------------------------
#define DATA						1 // ������ ��Ŷ
#define ACK							2 // Ȯ�� ���� 
#define FAIL						3 // ����
#define SESSION_REQUEST				4 // connect ��û
#define SESSION_ACCEPTANCE			5 // accept
#define FILE_REQUEST				6 // ���� ���� ��û
#define FILE_REQUEST_ACCEPTE		7 // �������� ���� accept
#define FILE_TRANSFER_COMPLETE		8 // ���� ���� �Ϸ�
#define FIN							9 // ���� ����


//---------------------------------------------------------------------------------------------------
// ��Ŷ ����ü 
//---------------------------------------------------------------------------------------------------
struct packet{
	char		buf[BUFFER_SIZE];   // ����Ÿ ����, size�� 100���� define��	
	long		seq;				// ��Ŷ ����
	int			ctrl_flag;			// ��Ŷ�� ������ ��Ÿ���� �÷��� �� ����
}send_packet, recv_packet;


//---------------------------------------------------------------------------------------------------
// �Լ� ���� 
//---------------------------------------------------------------------------------------------------
void err_quit();					// ���� �߻��� ���� �Լ�
void set_send_packet();				// �۽� ��Ŷ �����Լ�
void send_state_print(int retval);  // �۽� ���� ��� �Լ�


int main()
{
	
	WSADATA				wsa;					//���� �ʱ�ȭ�� �־��� �⺻ �ڷ� ���� ����
	int					retval;					//���� ó���� ����� ��
	SOCKET				s;						//accept�� ���� 
	SOCKADDR_IN			serv_addr;				//�ּҸ� �������ִ� ����ü 

	struct sockaddr_in  client_addr;			//���� ��û�� Client�� ���� ���� 
	int addr_size	  = sizeof(client_addr);


	//1. Winsock�� �ʱ�ȭ �Ѵ�. ������ 2.2
	retval  = WSAStartup(MAKEWORD(2,2), &wsa);
	if(retval != 0) err_quit();


	//2. ������ �����Ѵ�.(UDP���� �������� Setting) 
	s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if(s == INVALID_SOCKET) err_quit();


	//3. ������ �ּ� ����ü�� ������ �ִ´�.(�ּ� ����)  
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(5150);
	serv_addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

	//4. bid : ���ϰ� ip, port�� ��������ش�.
	retval = bind(s, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
	if(retval == SOCKET_ERROR) err_quit();


	printf("\t========================================================\n");
	printf("\t=             [SERVER PROGRAM]                         = \n"); 
	printf("\t========================================================\n");
	printf("\n-->[server]�� �����Ϸ��� ����Ű�� �������� : [ ]\b\b");
	if(getchar() == '\n')
	{
		printf("\n\n[server] : ���� ��û�� ��ٸ��ϴ�.\n");
	}

	while(1) 
	{
		//--------------------------------------------------------------------
		// 5. recv : Ŭ���̾�Ʈ�κ��� send �Ǵ� ��Ŷ�� �޴´�. 
		//--------------------------------------------------------------------
		
		// 5.1 �ʱ�ȭ
		memset(&recv_packet, 0, sizeof(packet));
		addr_size = sizeof(client_addr);
		
		//5.2 recvfrom
		retval = recvfrom(s, (char*)&recv_packet, sizeof(packet), 
							0, (struct sockaddr*)&client_addr, &addr_size);
		if(retval == SOCKET_ERROR) err_quit();
		else if(retval == 0) break;
		
		//5.3 ���������� ������ Ŭ���̾�Ʈ�� ��Ŷ�� ���� ������ ����Ѵ�.
		else
		{
			switch(recv_packet.ctrl_flag)
			{

			case SESSION_REQUEST:	//���� ��û
				printf("recv : SESION INIIATION REQUEST");
				break;

			case FILE_REQUEST:		//���� ��û
				printf("recv : FILE REQUEST --> a.txt\n");
				break;
			
			case ACK:				//���� ���� Ȯ�� 
				printf("recv : %s\n", recv_packet.buf) ;
				break;
			}
		}
	

		//--------------------------------------------------------------------
		// 6. send : Ŭ���̾�Ʈ�� ��Ŷ�� �����Ѵ�. 
		//--------------------------------------------------------------------

		//6.1 �۽� ��Ŷ�� �����Ѵ�.
		set_send_packet(); // �۽� ��Ŷ ����
		
		//6.2 ����� Ŭ���̾�Ʈ�� ��Ŷ�� �����Ѵ�.
		retval = sendto(s, (char*)&send_packet, sizeof(send_packet), 
							0, (struct sockaddr*)&client_addr, addr_size);
		
		//6.3 �۽� ���¸� ����Ѵ�.
		if(send_packet.ctrl_flag == DATA)
		{
			//�۽ŵ� �������� ������ ������� �ʴ´�. 
		}
		else
		{
			send_state_print(retval); 
		}
		printf("\n");
	}

	//7. ������ �����Ѵ�. 
	retval = closesocket(s);
	if(retval == SOCKET_ERROR) err_quit();

	//8. ������ �����Ѵ�.
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

	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
					FORMAT_MESSAGE_FROM_SYSTEM |
					FORMAT_MESSAGE_IGNORE_INSERTS,
					NULL, WSAGetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
					(LPTSTR)&lpMsgBuf, 0, NULL);

	MessageBox(NULL, (LPCTSTR)lpMsgBuf, "����", MB_OK | MB_ICONINFORMATION);

	LocalFree(lpMsgBuf);
	exit(1);
}


//---------------------------------------------------------------------------------------
// �Լ�   �� : send_state_print(int retval) 
//      ���� : ���� �۽� ���¸� console ȭ�鿡 ��½����ش�. 
//      ���� : retval - ������ üũ�ϱ����� sendTo�� ���ϰ��� �޾� �´�.
//				        ���� 0�̸� �۽��� �ȉ�ٴ� �޽����� ����ϰ�,
//						�� �̿��� ���̸� ��Ŷ�� ��� buf�� ������ ����Ѵ�.
//---------------------------------------------------------------------------------------

void send_state_print(int retval) 
{
	if(retval == SOCKET_ERROR) err_quit();
	else if(retval == 0) 
	{
		printf("[ERROR] can't send data\n");
		exit(1);
	}
	else 
		printf("\nsend : %s\n", send_packet.buf);	
}


//---------------------------------------------------------------------------------------
// �Լ�   �� : set_send_packet()
//      ���� : �������� �ϴ� ��Ŷ�� ������ �ʱ�ȭ, �����Ѵ�. 
//      ���� : ��Ŷ�� flag ���� ���� ���е� ��Ŷ ���� 
//---------------------------------------------------------------------------------------

void set_send_packet() 
{
	static long seq = 1;
	// �۽� ��Ŷ �ʱ�ȭ
	memset(&send_packet, 0, sizeof(send_packet));


	// ���ŵ� ��Ŷ�� �÷��װ��� ���� ���� �ٸ� ó�� 
	switch(recv_packet.ctrl_flag) 
	{			

		case SESSION_REQUEST: 	// ���� ��û						
			send_packet.ctrl_flag = SESSION_ACCEPTANCE;
			sprintf(send_packet.buf, "SESSION_ACCEPTANCE\n");
			break;

		case FILE_REQUEST: // ���� ��û ó���� �޾��� ��� 
			send_packet.ctrl_flag = FILE_REQUEST_ACCEPTE;
			printf("send : FILE_REQUEST_ACCEPT\n");
			sprintf(send_packet.buf, "a.txt");
			break;

		case ACK: 
		case DATA:   // ����Ÿ ���� 
			FILE* fp;
			int readdata;
			if((fp = fopen("a.txt", "rb")) == NULL ) 
			{
				printf("-->error : Not found file;\n");
				exit(1);
			}
			fseek(fp, ((seq-1)*100), SEEK_SET);
			readdata = fread(send_packet.buf, 1, 100, fp);
			fclose(fp);
			if(readdata == 0) 
			{
				send_packet.ctrl_flag = FILE_TRANSFER_COMPLETE;
				sprintf(send_packet.buf, "FILE TRANSFER COMPLETE");		
			}
			else
			{
							send_packet.ctrl_flag  = DATA;
			send_packet.seq = seq;
			printf("send : data packet(seq, %d)", send_packet.seq);						
			seq++;

			}
	break;
	
		case FILE_TRANSFER_COMPLETE: // ���� ���� �Ϸ�							
			send_packet.ctrl_flag = FIN;
			printf("\n[SERVER] : ���� ������ �Ϸ�Ǿ����ϴ�.\n\n");
			printf("[SERVER] : ������ �����մϴ�.\n\n");				
			sprintf(send_packet.buf, "FIN");
			break;	
	}
}