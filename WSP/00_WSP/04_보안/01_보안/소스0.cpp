//��������������������������������������
//  [ TIP ] ��Ƽ�� ���� ��� 
//��������������������������������������


#include <windows.h>

#include <stdio.h>

 

// ��Ƽ�� table ���

typedef struct _PARTITION

{

        char active;  // ���� �����Ѱ�

        char begin[3];// CHS ��� ������ ���

        char type;    // ��Ƽ�� ����

        char end[3];  // CHS ��忡�� ���

 

        int start;    // LBA ��忡���� ��Ƽ���� ���۵Ǵ� sector ��ȣ

        int size;     // LBA ��忡�� ��Ƽ���� ũ��

} PARTITION;

 

void print(PARTITION *p)

{
        static int n = 1;

 

        printf("[PARTITION %d]\n", n++);

        printf("Start : %d\n", p->start);

        printf("Size : %d MB\n", p->size / 1024*512 / 1024);

        printf("Bootable : %x\n", p->active & 0x00ff); 

                                              // 0x80 : ���� ����

                                              // 0x00 : ���� �Ұ���

        printf("----------------\n");
}

 

 

//-----------------------------------------------------------------

void main()

{

        // �ϵ��ũ�� 1��° ���͸� ���������� �о�´�

        HANDLE hFile = CreateFile("\\\\.\\PhysicalDrive0", GENERIC_READ,

                                    FILE_SHARE_READ | FILE_SHARE_WRITE,

                                    0, OPEN_EXISTING,

                                    FILE_ATTRIBUTE_NORMAL, 0);

 

        if(hFile == INVALID_HANDLE_VALUE)

        {

                printf("����\n");

                return ;

        }

        //-------------------------------------------------------------

        char buf[512] = {0};

        DWORD len;

 

        BOOL b = ReadFile(hFile, buf, 512, &len, 0);

 

        PARTITION *p = (PARTITION*)(buf + 0x1BE);  // ��Ƽ�� table�� �ִ�

                                                   // ������ �̵�

 

        // Table�� ������ ������ش�.

        for(; p->size != 0; ++p)

        {

                print(p);

        }

}
