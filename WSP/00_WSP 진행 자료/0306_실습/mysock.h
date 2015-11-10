//mysock.h

typedef void (*RECVFUN)(char*, int);

//===================================================
//���̺귯�� �ʱ�ȭ ����
//===================================================
int mysock_init();
void mysock_exit();

void mysock_inirproc(RECVFUN OnRecv);

//====================================================
// ���� ���� 
//====================================================
void mysock_recvsock(int size, int port);
void recvthread(void* p);

void mysock_sendsock(int size, int port);


//====================================================
// ������ ����
void mysock_senddata(char* data, int length);


//====================================================
// ���� ���� �Լ� 
//====================================================
void err_quit(char *msg);
void err_display(char *msg);