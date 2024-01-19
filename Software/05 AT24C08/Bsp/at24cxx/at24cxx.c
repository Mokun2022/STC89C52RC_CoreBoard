#include "at24cxx.h"
#include "at24cxx_i2c.h"
#include "delay.h"
#include "uart.h"

/*
	AT24C08A��8K����EEPROM��
	�ڲ���֯Ϊ64ҳ��ÿҳ16�ֽڣ�
	10λ�������ֵ�ַ�����������Ѱַ��
*/



/**
  * @brief  IIC��ʼ��.
  * @param  void.
  * @retval void.
*/
void x24cxx_Init(void)
{
	AT24CXX_IIC_Init();
}


/**
  * @brief  дһ���ֽ�.
  * @param  u16Addr Ҫд���10λ��ַ.
  * @param  u8Data  Ҫд���8λ����.
  * @retval void.
*/
void x24Cxx_WriteByte(unsigned int u16Addr, unsigned char u8Data)
{
	AT24CXX_IIC_Start();//��ʼ�ź�
	AT24CXX_IIC_WriteByte(DEV_ADDR | WRITE_CMD | (((unsigned char)((u16Addr >> 8) & 0x03)) << 1));//����Ѱַ+д+ҳѡ��λ
	AT24CXX_IIC_Wait_ACK();//�ȴ�Ӧ��
	AT24CXX_IIC_WriteByte((unsigned char)(u16Addr & 0xFF));//ֻȡ��ַ�ĵ��ֽڣ����ֽ�����У��Ѿ�����ҳѡ��λ�������
	AT24CXX_IIC_Wait_ACK();//�ȴ�Ӧ��
	AT24CXX_IIC_WriteByte(u8Data);
	AT24CXX_IIC_Wait_ACK();//�ȴ�Ӧ��
	AT24CXX_IIC_Stop();//ֹͣ�ź�
}

/**
  * @brief  ҳд,���д��1ҳ����ֹ���������ַ��ҳ��ȥ����ҳ�Ĳ���.
  * @param  u16Addr Ҫд���10λ��ַ.
  * @param  u8Len   д�������ֽ��������ΪPAGE_SIZE.
  * @param  pData   Ҫд��������׵�ַ.
  * @retval void.
*/
void x24Cxx_WritePage(unsigned int u16Addr, unsigned char u8Len, unsigned char *pData)
{
	unsigned char i;
	
	AT24CXX_IIC_Start();//��ʼ�ź�
	AT24CXX_IIC_WriteByte(DEV_ADDR | WRITE_CMD | (((unsigned char)((u16Addr >> 8) & 0x03)) << 1));//����Ѱַ+д+ҳѡ��λ
	AT24CXX_IIC_Wait_ACK();//�ȴ�Ӧ��
	AT24CXX_IIC_WriteByte((unsigned char)(u16Addr & 0xFF));//ֻȡ��ַ�ĵ��ֽڣ����ֽ�����У��Ѿ�����ҳѡ��λ�������
	AT24CXX_IIC_Wait_ACK();//�ȴ�Ӧ��
	if (u8Len > PAGE_SIZE)//���ȴ���ҳ�ĳ���
	{
		u8Len = PAGE_SIZE;
	}
	if ((u16Addr + (unsigned int)u8Len) > CAPACITY_SIZE)//��������
	{
		u8Len = (unsigned char)(CAPACITY_SIZE - u16Addr);
	}
	if (((u16Addr % PAGE_SIZE) + (unsigned int)u8Len) > PAGE_SIZE)//�ж��Ƿ��ҳ
	{
		u8Len -= (unsigned char)((u16Addr + (unsigned int)u8Len) % PAGE_SIZE);//��ҳ���ص���ҳ�Ĳ���
	}
	
	for (i = 0; i < u8Len; i++)
	{
		AT24CXX_IIC_WriteByte(*(pData + i));
		AT24CXX_IIC_Wait_ACK();//�ȴ�Ӧ��
	}
	AT24CXX_IIC_Stop();//ֹͣ�ź�	
}


/**
  * @brief  ��һ���ֽ�.
  * @param  u16Addr  Ҫ��ȡ��10λ��ַ.
  * @retval u8Data   ������8λ����.
*/
unsigned char x24Cxx_ReadByte(unsigned int u16Addr)
{
	unsigned char u8Data = 0;
	
	AT24CXX_IIC_Start();//��ʼ�ź�	
	AT24CXX_IIC_WriteByte(DEV_ADDR | WRITE_CMD | (((unsigned char)((u16Addr >> 8) & 0x03)) << 1));//����Ѱַ+д+ҳѡ��λ
	AT24CXX_IIC_Wait_ACK();//�ȴ�Ӧ��
	AT24CXX_IIC_WriteByte((unsigned char)(u16Addr & 0xFF));//ֻȡ��ַ�ĵ��ֽڣ����ֽ�����У��Ѿ�����ҳѡ��λ�������
	AT24CXX_IIC_Wait_ACK();//�ȴ�Ӧ��
	AT24CXX_IIC_Start();//��ʼ�ź�
	AT24CXX_IIC_WriteByte(DEV_ADDR | READ_CMD);//����Ѱַ+��
	AT24CXX_IIC_Wait_ACK();//�ȴ�Ӧ��
	u8Data = AT24CXX_IIC_ReadByte();
	AT24CXX_IIC_ACK(1);
	AT24CXX_IIC_Stop();//ֹͣ�ź�
	return u8Data;
}



/**
  * @brief  ҳ��,����1ҳ����ֹ���������ַ��ҳ��ȥ����ҳ�Ĳ���
  * @param  u16Addr Ҫ��ȡ��10λ��ַ.
  * @param  u8Len   ��ȡ�����ֽ��������ΪPAGE_SIZE.
  * @param  pData   ��ȡ���ݴ���Ļ���.
  * @retval void.
*/
void x24Cxx_ReadPage(unsigned int u16Addr, unsigned char u8Len, unsigned char *pBuff)
{
	unsigned char i;	
	
	AT24CXX_IIC_Start();//��ʼ�ź�	
	AT24CXX_IIC_WriteByte(DEV_ADDR | WRITE_CMD | (((unsigned char)((u16Addr >> 8) & 0x03)) << 1));//����Ѱַ+д+ҳѡ��λ
	AT24CXX_IIC_Wait_ACK();//�ȴ�Ӧ��
	AT24CXX_IIC_WriteByte((unsigned char)(u16Addr & 0xFF));//ֻȡ��ַ�ĵ��ֽڣ����ֽ�����У��Ѿ�����ҳѡ��λ�������
	AT24CXX_IIC_Wait_ACK();//�ȴ�Ӧ��
	AT24CXX_IIC_Start();//��ʼ�ź�
	AT24CXX_IIC_WriteByte(DEV_ADDR | READ_CMD);//����Ѱַ+��
	AT24CXX_IIC_Wait_ACK();//�ȴ�Ӧ��
	if (u8Len > PAGE_SIZE)//���ȴ���ҳ�ĳ���
	{
		u8Len = PAGE_SIZE;
	}
	if ((u16Addr + (unsigned int)u8Len) > CAPACITY_SIZE)//��������
	{
		u8Len = (unsigned char)(CAPACITY_SIZE - u16Addr);
	}
	if (((u16Addr % PAGE_SIZE) + (unsigned int)u8Len) > PAGE_SIZE)//�ж��Ƿ��ҳ
	{
		u8Len -= (unsigned char)((u16Addr + (unsigned int)u8Len) % PAGE_SIZE);//��ҳ���ص���ҳ�Ĳ���
	}
	for (i = 0; i < (u8Len - 1); i++)
	{
		*(pBuff + i) = AT24CXX_IIC_ReadByte();
		AT24CXX_IIC_ACK(0);//����Ӧ��
	}
	*(pBuff + u8Len - 1) = AT24CXX_IIC_ReadByte();
	AT24CXX_IIC_ACK(1);//���һ����Ӧ��
	AT24CXX_IIC_Stop();//ֹͣ�ź�
}

