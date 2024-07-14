#pragma once
#include"Buf.h"
#include"DiskDriver.h"
#include"Sys.h"
using namespace std;

class BufferManager {
public:
    static const int NBUF = 150;			/* 缓存控制块、缓冲区的数量 */
    static const int BUFFER_SIZE = 512;		/* 缓冲区大小。 以字节为单位 */

private:
    Buf* bFreeList;							/* 缓存队列控制块 */
    Buf m_Buf[NBUF];						/* 缓存控制块数组 */
    unsigned char buffer[NBUF][BUFFER_SIZE];	/* 缓冲区数组 */
    unordered_map < int, Buf* > map;        /* 相当于设备队列 */
    DiskDriver*  m_DeviceDriver;

public:
    BufferManager();
    ~BufferManager();

   
    Buf* GetBlk(int blkno);     /* 申请一块缓存，用于读写设备上的块blkno。*/
    void Brelse(Buf* bp);       /* 释放缓存控制块buf */
    Buf* Bread(int blkno);      /* 读一个磁盘块，blkno为目标磁盘块逻辑块号。 */
    void Bwrite(Buf* bp);       /* 写一个磁盘块 */
    void Bdwrite(Buf* bp);      /* 延迟写磁盘块 */
    void ClrBuf(Buf* bp);       /* 清空缓冲区内容 */

    /* 将队列中延迟写的缓存全部输出到磁盘 */
    void Bflush();

    /* 获取空闲控制块Buf对象引用 */
    //Buffer& GetFreeBuffer();				

    /* 格式化所有Buffer */
    void FormatBuffer();

private:
    void InitList();
    void DetachNode(Buf* pb);
    void InsertTail(Buf* pb);
};
