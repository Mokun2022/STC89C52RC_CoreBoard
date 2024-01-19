#include "at24cxx.h"
#include "at24cxx_i2c.h"
#include "delay.h"
#include "uart.h"

/*
	AT24C08A，8K串行EEPROM：
	内部组织为64页，每页16字节，
	10位的数据字地址来进行随机字寻址。
*/



/**
  * @brief  IIC初始化.
  * @param  void.
  * @retval void.
*/
void x24cxx_Init(void)
{
	AT24CXX_IIC_Init();
}


/**
  * @brief  写一个字节.
  * @param  u16Addr 要写入的10位地址.
  * @param  u8Data  要写入的8位数据.
  * @retval void.
*/
void x24Cxx_WriteByte(unsigned int u16Addr, unsigned char u8Data)
{
	AT24CXX_IIC_Start();//起始信号
	AT24CXX_IIC_WriteByte(DEV_ADDR | WRITE_CMD | (((unsigned char)((u16Addr >> 8) & 0x03)) << 1));//器件寻址+写+页选择位
	AT24CXX_IIC_Wait_ACK();//等待应答
	AT24CXX_IIC_WriteByte((unsigned char)(u16Addr & 0xFF));//只取地址的低字节，高字节如果有，已经按照页选择位处理过了
	AT24CXX_IIC_Wait_ACK();//等待应答
	AT24CXX_IIC_WriteByte(u8Data);
	AT24CXX_IIC_Wait_ACK();//等待应答
	AT24CXX_IIC_Stop();//停止信号
}

/**
  * @brief  页写,最多写入1页，防止翻卷，如果地址跨页则去掉跨页的部分.
  * @param  u16Addr 要写入的10位地址.
  * @param  u8Len   写入数据字节数，最大为PAGE_SIZE.
  * @param  pData   要写入的数据首地址.
  * @retval void.
*/
void x24Cxx_WritePage(unsigned int u16Addr, unsigned char u8Len, unsigned char *pData)
{
	unsigned char i;
	
	AT24CXX_IIC_Start();//起始信号
	AT24CXX_IIC_WriteByte(DEV_ADDR | WRITE_CMD | (((unsigned char)((u16Addr >> 8) & 0x03)) << 1));//器件寻址+写+页选择位
	AT24CXX_IIC_Wait_ACK();//等待应答
	AT24CXX_IIC_WriteByte((unsigned char)(u16Addr & 0xFF));//只取地址的低字节，高字节如果有，已经按照页选择位处理过了
	AT24CXX_IIC_Wait_ACK();//等待应答
	if (u8Len > PAGE_SIZE)//长度大于页的长度
	{
		u8Len = PAGE_SIZE;
	}
	if ((u16Addr + (unsigned int)u8Len) > CAPACITY_SIZE)//超过容量
	{
		u8Len = (unsigned char)(CAPACITY_SIZE - u16Addr);
	}
	if (((u16Addr % PAGE_SIZE) + (unsigned int)u8Len) > PAGE_SIZE)//判断是否跨页
	{
		u8Len -= (unsigned char)((u16Addr + (unsigned int)u8Len) % PAGE_SIZE);//跨页，截掉跨页的部分
	}
	
	for (i = 0; i < u8Len; i++)
	{
		AT24CXX_IIC_WriteByte(*(pData + i));
		AT24CXX_IIC_Wait_ACK();//等待应答
	}
	AT24CXX_IIC_Stop();//停止信号	
}


/**
  * @brief  读一个字节.
  * @param  u16Addr  要读取的10位地址.
  * @retval u8Data   读出的8位数据.
*/
unsigned char x24Cxx_ReadByte(unsigned int u16Addr)
{
	unsigned char u8Data = 0;
	
	AT24CXX_IIC_Start();//起始信号	
	AT24CXX_IIC_WriteByte(DEV_ADDR | WRITE_CMD | (((unsigned char)((u16Addr >> 8) & 0x03)) << 1));//器件寻址+写+页选择位
	AT24CXX_IIC_Wait_ACK();//等待应答
	AT24CXX_IIC_WriteByte((unsigned char)(u16Addr & 0xFF));//只取地址的低字节，高字节如果有，已经按照页选择位处理过了
	AT24CXX_IIC_Wait_ACK();//等待应答
	AT24CXX_IIC_Start();//起始信号
	AT24CXX_IIC_WriteByte(DEV_ADDR | READ_CMD);//器件寻址+读
	AT24CXX_IIC_Wait_ACK();//等待应答
	u8Data = AT24CXX_IIC_ReadByte();
	AT24CXX_IIC_ACK(1);
	AT24CXX_IIC_Stop();//停止信号
	return u8Data;
}



/**
  * @brief  页读,最多读1页，防止翻卷，如果地址跨页则去掉跨页的部分
  * @param  u16Addr 要读取的10位地址.
  * @param  u8Len   读取数据字节数，最大为PAGE_SIZE.
  * @param  pData   读取数据存入的缓存.
  * @retval void.
*/
void x24Cxx_ReadPage(unsigned int u16Addr, unsigned char u8Len, unsigned char *pBuff)
{
	unsigned char i;	
	
	AT24CXX_IIC_Start();//起始信号	
	AT24CXX_IIC_WriteByte(DEV_ADDR | WRITE_CMD | (((unsigned char)((u16Addr >> 8) & 0x03)) << 1));//器件寻址+写+页选择位
	AT24CXX_IIC_Wait_ACK();//等待应答
	AT24CXX_IIC_WriteByte((unsigned char)(u16Addr & 0xFF));//只取地址的低字节，高字节如果有，已经按照页选择位处理过了
	AT24CXX_IIC_Wait_ACK();//等待应答
	AT24CXX_IIC_Start();//起始信号
	AT24CXX_IIC_WriteByte(DEV_ADDR | READ_CMD);//器件寻址+读
	AT24CXX_IIC_Wait_ACK();//等待应答
	if (u8Len > PAGE_SIZE)//长度大于页的长度
	{
		u8Len = PAGE_SIZE;
	}
	if ((u16Addr + (unsigned int)u8Len) > CAPACITY_SIZE)//超过容量
	{
		u8Len = (unsigned char)(CAPACITY_SIZE - u16Addr);
	}
	if (((u16Addr % PAGE_SIZE) + (unsigned int)u8Len) > PAGE_SIZE)//判断是否跨页
	{
		u8Len -= (unsigned char)((u16Addr + (unsigned int)u8Len) % PAGE_SIZE);//跨页，截掉跨页的部分
	}
	for (i = 0; i < (u8Len - 1); i++)
	{
		*(pBuff + i) = AT24CXX_IIC_ReadByte();
		AT24CXX_IIC_ACK(0);//主机应答
	}
	*(pBuff + u8Len - 1) = AT24CXX_IIC_ReadByte();
	AT24CXX_IIC_ACK(1);//最后一个不应答
	AT24CXX_IIC_Stop();//停止信号
}

