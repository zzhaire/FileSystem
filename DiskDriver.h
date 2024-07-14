#pragma once
#include"Sys.h"
using namespace std;
class DiskDriver {
public:
    /* 磁盘镜像文件名 */
    static const char* DISK_FILE_NAME;

private:
    /* 磁盘文件指针 */
    FILE* fp;

public:
    DiskDriver();
    ~DiskDriver();

    /* 检查镜像文件是否存在 */
    bool exists();

    /* 打开镜像文件 */
    void construct();

    /* 实际写磁盘函数 */
    void write(const void* buffer, unsigned int size,
        int offset = -1,int origin = 0);

    /* 实际写磁盘函数 */
    void read(void* buffer, unsigned int size,
        int offset = -1, int origin = 0);
};

class IOParameter {
public:
    unsigned char* base;	/* 当前读、写用户目标区域的首地址 */
    int offset;			    /* 当前读、写文件的字节偏移量 */
    int count;			    /* 当前还剩余的读、写字节数量 */
};


