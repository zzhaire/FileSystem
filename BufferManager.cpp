#include"Common.h"
using namespace std;

extern DiskDriver g_DiskDriver;

/*
 *	Buffer只用到了两个标志，B_DONE和B_DELWRI，分别表示已经完成IO和延迟写的标志。
 *	空闲Buffer无任何标志
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

/* 采用LRU Cache 算法，每次从头部取出，使用后放到尾部
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

/* 申请一块缓存，从缓存队列中取出，用于读写设备上的块blkno。*/
Buf* BufferManager::GetBlk(int blkno) {
	Buf* pb;
	if (map.find(blkno) != map.end()) {
		pb = map[blkno];
		DetachNode(pb);
		return pb;
	}
	pb = bFreeList->b_back;
	if (pb == bFreeList) {
		cout << "无Buffer可供使用" << endl;
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

/* 释放缓存控制块buf */
void BufferManager::Brelse(Buf* pb) {
	InsertTail(pb);
}

/* 读一个磁盘块，blkno为目标磁盘块逻辑块号。 */
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

/* 写一个磁盘块 */
void BufferManager::Bwrite(Buf* pb) {
	//pb->debugMark();
	//pb->debugContent();
	pb->b_flags &= ~(Buf::B_DELWRI);
	m_DeviceDriver->write(pb->b_addr, BUFFER_SIZE, pb->b_blkno * BUFFER_SIZE);
	pb->b_flags |= (Buf::B_DONE);
	this->Brelse(pb);
}

/* 延迟写磁盘块 */
void BufferManager::Bdwrite(Buf* bp) {
	bp->b_flags |= (Buf::B_DELWRI | Buf::B_DONE);
	this->Brelse(bp);
	return;
}

/* 清空缓冲区内容 */
void BufferManager::ClrBuf(Buf* bp) {
	memset(bp->b_addr, 0, BufferManager::BUFFER_SIZE);
	return;
}

/* 将队列中延迟写的缓存全部输出到磁盘 */
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
