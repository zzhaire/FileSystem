#pragma once

#include "INode.h"
using namespace std;

/*
 * 打开文件控制块File类。
 * 该结构记录了进程打开文件的读、写请求类型，文件读写位置等等。
 */
class File {
public:
    enum FileFlags {
        FREAD = 0x1,			/* 读请求类型 */
        FWRITE = 0x2,			/* 写请求类型 */
    };

public:
    File();
    ~File();

    unsigned int flag;		/* 对打开文件的读、写操作要求 */
    int		count;			/* 当前引用该文件控制块的进程数量 */
    INode*  inode;			/* 指向打开文件的内存INode指针 */
    int		offset;			/* 文件读写位置指针 */
};

/*
 * 进程打开文件描述符表(OpenFiles)的定义
 * 维护了当前进程的所有打开文件。
 */
class OpenFiles {
public:
    static const int MAX_FILES = 100;		/* 进程允许打开的最大文件数 */

private:
    File* processOpenFileTable[MAX_FILES];	/* File对象的指针数组，指向系统打开文件表中的File对象 */

public:
    OpenFiles();
    ~OpenFiles();

    /* 进程请求打开文件时，在打开文件描述符表中分配一个空闲表项 */
    int AllocFreeSlot();

    /* 根据用户系统调用提供的文件描述符参数fd，找到对应的打开文件控制块File结构 */
    File* GetF(int fd);

    /* 为已分配到的空闲描述符fd和已分配的打开文件表中空闲File对象建立勾连关系 */
    void SetF(int fd, File* pFile);
};

/*
 * 文件I/O的参数类
 * 对文件读、写时需用到的读、写偏移量、字节数以及目标区域首地址参数。
 */
