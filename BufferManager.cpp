#include"Common.h"
using namespace std;

extern DiskDriver g_DiskDriver;

/*
 *	Bufferֻ�õ���������־��B_DONE��B_DELWRI���ֱ��ʾ�Ѿ����IO���ӳ�д�ı�־��
 *	����Buffer���κα�־
*/
BufferManager::BufferManager()
{
	bFreeList = new Buf;
	InitList();
	m_DeviceDriver = &g_DiskDriver;
}

BufferManager::~BufferManager() {
	Bflush();
	delete bFreeList;
}

void BufferManager::FormatBuffer() {
	Buf emptyBuffer;
	for (int i = 0; i < NBUF; ++i) {
		memcpy(m_Buf + i, &emptyBuffer, sizeof(Buf));
	}
	InitList();
}

void BufferManager::InitList() {
	for (int i = 0; i < NBUF; ++i) {
		if (i) {
			m_Buf[i].b_forw = m_Buf + i - 1;
		}
		else {
			m_Buf[i].b_forw = bFreeList;
			bFreeList->b_back = m_Buf + i;
		}

		if (i + 1 < NBUF) {
			m_Buf[i].b_back = m_Buf + i + 1;
		}
		else {
			m_Buf[i].b_back = bFreeList;
			bFreeList->b_forw = m_Buf + i;
		}
		m_Buf[i].b_addr = buffer[i];
		m_Buf[i].no = i;
	}
}

/* ����LRU Cache �㷨��ÿ�δ�ͷ��ȡ����ʹ�ú�ŵ�β��
*/
void BufferManager::DetachNode(Buf* pb) {
	if (pb->b_back == NULL) {
		return;
	}
	pb->b_forw->b_back = pb->b_back;
	pb->b_back->b_forw = pb->b_forw;
	pb->b_back = NULL;
	pb->b_forw = NULL;
}

void BufferManager::InsertTail(Buf* pb) {
	if (pb->b_back != NULL) {
		return;
	}
	pb->b_forw = bFreeList->b_forw;
	pb->b_back = bFreeList;
	bFreeList->b_forw->b_back = pb;
	bFreeList->b_forw = pb;
}

/* ����һ�黺�棬�ӻ��������ȡ�������ڶ�д�豸�ϵĿ�blkno��*/
Buf* BufferManager::GetBlk(int blkno) {
	Buf* pb;
	if (map.find(blkno) != map.end()) {
		pb = map[blkno];
		DetachNode(pb);
		return pb;
	}
	pb = bFreeList->b_back;
	if (pb == bFreeList) {
		cout << "��Buffer�ɹ�ʹ��" << endl;
		return NULL;
	}
	DetachNode(pb);
	map.erase(pb->b_blkno);
	if (pb->b_flags & Buf::B_DELWRI) {
		m_DeviceDriver->write(pb->b_addr, BUFFER_SIZE, pb->b_blkno * BUFFER_SIZE);
	}
	pb->b_flags &= ~(Buf::B_DELWRI | Buf::B_DONE);
	pb->b_blkno = blkno;
	map[blkno] = pb;
	return pb;
}

/* �ͷŻ�����ƿ�buf */
void BufferManager::Brelse(Buf* pb) {
	InsertTail(pb);
}

/* ��һ�����̿飬blknoΪĿ����̿��߼���š� */
Buf* BufferManager::Bread(int blkno) {
	Buf* pb = GetBlk(blkno);
	//pb->debugMark();
	//pb->debugContent();
	if (pb->b_flags & (Buf::B_DONE | Buf::B_DELWRI)) {
		return pb;
	}
	m_DeviceDriver->read(pb->b_addr, BUFFER_SIZE, pb->b_blkno * BUFFER_SIZE);
	pb->b_flags |= Buf::B_DONE;
	return pb;
}

/* дһ�����̿� */
void BufferManager::Bwrite(Buf* pb) {
	//pb->debugMark();
	//pb->debugContent();
	pb->b_flags &= ~(Buf::B_DELWRI);
	m_DeviceDriver->write(pb->b_addr, BUFFER_SIZE, pb->b_blkno * BUFFER_SIZE);
	pb->b_flags |= (Buf::B_DONE);
	this->Brelse(pb);
}

/* �ӳ�д���̿� */
void BufferManager::Bdwrite(Buf* bp) {
	bp->b_flags |= (Buf::B_DELWRI | Buf::B_DONE);
	this->Brelse(bp);
	return;
}

/* ��ջ��������� */
void BufferManager::ClrBuf(Buf* bp) {
	memset(bp->b_addr, 0, BufferManager::BUFFER_SIZE);
	return;
}

/* ���������ӳ�д�Ļ���ȫ����������� */
void BufferManager::Bflush() {
	Buf* pb = NULL;
	for (int i = 0; i < NBUF; ++i) {
		pb = m_Buf + i;
		if ((pb->b_flags & Buf::B_DELWRI)) {
			pb->b_flags &= ~(Buf::B_DELWRI);
			m_DeviceDriver->write(pb->b_addr, BUFFER_SIZE, pb->b_blkno * BUFFER_SIZE);
			pb->b_flags |= (Buf::B_DONE);
		}
	}
}
