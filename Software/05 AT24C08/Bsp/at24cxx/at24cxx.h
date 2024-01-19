#ifndef  __AT24CXX_H__
#define  __AT24CXX_H__

#include <STC89C5xRC.H>

#define READ_CMD				1
#define WRITE_CMD				0
#define DEV_ADDR				0xA0					//设备硬件地址
#define PAGE_NUM				64						//页数
#define PAGE_SIZE				16						//页面大小(字节)
#define CAPACITY_SIZE			(PAGE_NUM * PAGE_SIZE)	//总容量(字节)
#define ADDR_BYTE_NUM			1						//地址字节个数


void x24cxx_Init(void);
void x24Cxx_WritePage(unsigned int u16Addr, unsigned char u8Len, unsigned char *pData);
void x24Cxx_ReadPage(unsigned int u16Addr, unsigned char u8Len, unsigned char *pBuff);

#endif