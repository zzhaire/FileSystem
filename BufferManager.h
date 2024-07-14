#pragma once
#include"Buf.h"
#include"DiskDriver.h"
#include"Sys.h"
using namespace std;

class BufferManager {
public:
    static const int NBUF = 150;			/* ������ƿ顢������������ */
    static const int BUFFER_SIZE = 512;		/* ��������С�� ���ֽ�Ϊ��λ */

private:
    Buf* bFreeList;							/* ������п��ƿ� */
    Buf m_Buf[NBUF];						/* ������ƿ����� */
    unsigned char buffer[NBUF][BUFFER_SIZE];	/* ���������� */
    unordered_map < int, Buf* > map;        /* �൱���豸���� */
    DiskDriver*  m_DeviceDriver;

public:
    BufferManager();
    ~BufferManager();

   
    Buf* GetBlk(int blkno);     /* ����һ�黺�棬���ڶ�д�豸�ϵĿ�blkno��*/
    void Brelse(Buf* bp);       /* �ͷŻ�����ƿ�buf */
    Buf* Bread(int blkno);      /* ��һ�����̿飬blknoΪĿ����̿��߼���š� */
    void Bwrite(Buf* bp);       /* дһ�����̿� */
    void Bdwrite(Buf* bp);      /* �ӳ�д���̿� */
    void ClrBuf(Buf* bp);       /* ��ջ��������� */

    /* ���������ӳ�д�Ļ���ȫ����������� */
    void Bflush();

    /* ��ȡ���п��ƿ�Buf�������� */
    //Buffer& GetFreeBuffer();				

    /* ��ʽ������Buffer */
    void FormatBuffer();

private:
    void InitList();
    void DetachNode(Buf* pb);
    void InsertTail(Buf* pb);
};
