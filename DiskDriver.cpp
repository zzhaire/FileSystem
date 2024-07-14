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

/* 检查镜像文件是否存在 */
bool DiskDriver::exists() {
    return fp != NULL;
}

/* 打开镜像文件 */
void DiskDriver::construct() {
    fp = fopen(DISK_FILE_NAME, "wb+");
    if (fp == NULL) {
        printf("打开或新建文件%s失败！", DISK_FILE_NAME);
        exit(-1);
    }
}

/* 实际写磁盘函数 */
void DiskDriver::write(const void* buffer, unsigned int size, int offset, int origin) {
    if (offset >= 0) {
        fseek(fp, offset, origin);
    }
    fwrite(buffer, size, 1, fp);
}

/* 实际写磁盘函数 */
void DiskDriver::read(void* buffer, unsigned int size, int offset, int origin) {
    if (offset >= 0) {
        fseek(fp, offset, origin);
    }
    
    fread(buffer, size, 1, fp);
}