//myservice.h

//�ʱ�ȭ
void myservice_init();

//����
void myservice_run();

//�߰� �ڵ鷯
DWORD WINAPI MainThread(LPVOID temp);
DWORD WINAPI PipeThread(LPVOID temp);