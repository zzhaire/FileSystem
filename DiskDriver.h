#pragma once
#include"Sys.h"
using namespace std;
class DiskDriver {
public:
    /* ���̾����ļ��� */
    static const char* DISK_FILE_NAME;

private:
    /* �����ļ�ָ�� */
    FILE* fp;

public:
    DiskDriver();
    ~DiskDriver();

    /* ��龵���ļ��Ƿ���� */
    bool exists();

    /* �򿪾����ļ� */
    void construct();

    /* ʵ��д���̺��� */
    void write(const void* buffer, unsigned int size,
        int offset = -1,int origin = 0);

    /* ʵ��д���̺��� */
    void read(void* buffer, unsigned int size,
        int offset = -1, int origin = 0);
};

class IOParameter {
public:
    unsigned char* base;	/* ��ǰ����д�û�Ŀ��������׵�ַ */
    int offset;			    /* ��ǰ����д�ļ����ֽ�ƫ���� */
    int count;			    /* ��ǰ��ʣ��Ķ���д�ֽ����� */
};


