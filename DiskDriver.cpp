#define _CRT_SECURE_NO_WARNINGS
#include "DiskDriver.h"

const char* DiskDriver::DISK_FILE_NAME = "1850772-fs.img";

DiskDriver::DiskDriver() {
    fp = fopen(DISK_FILE_NAME, "rb+");
}

DiskDriver::~DiskDriver() {
    if (fp) 
        fclose(fp);
    
}

/* ��龵���ļ��Ƿ���� */
bool DiskDriver::exists() {
    return fp != NULL;
}

/* �򿪾����ļ� */
void DiskDriver::construct() {
    fp = fopen(DISK_FILE_NAME, "wb+");
    if (fp == NULL) {
        printf("�򿪻��½��ļ�%sʧ�ܣ�", DISK_FILE_NAME);
        exit(-1);
    }
}

/* ʵ��д���̺��� */
void DiskDriver::write(const void* buffer, unsigned int size, int offset, int origin) {
    if (offset >= 0) {
        fseek(fp, offset, origin);
    }
    fwrite(buffer, size, 1, fp);
}

/* ʵ��д���̺��� */
void DiskDriver::read(void* buffer, unsigned int size, int offset, int origin) {
    if (offset >= 0) {
        fseek(fp, offset, origin);
    }
    
    fread(buffer, size, 1, fp);
}