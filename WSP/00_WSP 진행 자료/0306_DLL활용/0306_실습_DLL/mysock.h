//mysock.h


#ifdef DLL_SOURCE
	#define DLLFUNC	__declspec(dllexport)   
#else
	#define DLLFUNC __declspec(dllimport)
#endif

typedef void (*RECVFUN)(char*, int);

//===================================================
//���̺귯�� �ʱ�ȭ ����
//===================================================
EXTERN_C DLLFUNC int mysock_init();
EXTERN_C DLLFUNC void mysock_exit();

EXTERN_C DLLFUNC void mysock_inirproc(RECVFUN OnRecv);

//====================================================
// ���� ���� 
//====================================================
EXTERN_C DLLFUNC void mysock_recvsock(int size, int port);
void recvthread(void* p);

EXTERN_C DLLFUNC void mysock_sendsock(int size, int port);


//====================================================
// ������ ����
EXTERN_C DLLFUNC void mysock_senddata(char* data, int length);


//====================================================
// ���� ���� �Լ� 
//====================================================
void err_quit(char *msg);
void err_display(char *msg);