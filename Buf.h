#pragma once
#include "Sys.h"
using namespace std;

/*
 * ������ƿ�buf����
 * ��¼����Ӧ�����ʹ���������Ϣ��
 * ͬʱ����I/O����飬��¼�û���
 * ��ص�I/O�����ִ�н����
 */

class Buf {
public:


	enum BufFlag {				/* flags�б�־λ */
		//B_WRITE = 0x1,			/* д�������������е���Ϣд��Ӳ����ȥ */
		//B_READ = 0x2,		    /* �����������̶�ȡ��Ϣ�������� */
		B_DONE = 0x4,		    /* I/O�������� */
		//B_ERROR = 0x8,			/* I/O��������ֹ */
		//B_BUSY = 0x10,			/* ��Ӧ��������ʹ���� */
		//B_WANTED = 0x20,	    /* �н������ڵȴ�ʹ�ø�buf�������Դ����B_BUSY��־ʱ��Ҫ�������ֽ��� */
		//B_ASYNC = 0x40,			/* �첽I/O������Ҫ�ȴ������ */
		B_DELWRI = 0x80		    /* �ӳ�д������Ӧ����Ҫ��������ʱ���ٽ�������д����Ӧ���豸�� */
	};

public:
	unsigned int b_flags;	    /* ������ƿ��־λ */

	int		padding;		/* 4�ֽ���䣬ʹ��b_forw��b_back��Buf������Devtab��
							 * �е��ֶ�˳���ܹ�һ�£�����ǿ��ת������� */
							 /* ������ƿ���й���ָ�� */
	Buf* b_forw;
	Buf* b_back;
	//Buf* av_forw;
	//Buf* av_back;

	int		b_wcount;		    /* �贫�͵��ֽ��� */
	unsigned char* b_addr;		/* ָ��û�����ƿ�������Ļ��������׵�ַ */
	int		b_blkno;		    /* �����߼���� */
	int		b_error;			/* I/O����ʱ��Ϣ */
	int		b_resid;		    /* I/O����ʱ��δ���͵�ʣ���ֽ��� */

	int no;
public:
	Buf();
	~Buf();
};
