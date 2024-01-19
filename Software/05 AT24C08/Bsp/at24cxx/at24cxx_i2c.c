#include "at24cxx_i2c.h"
#include "uart.h"


void AT24CXX_Delay5us(void)	//@12.000MHz
{
	unsigned char data i;

	_nop_();
	i = 2;
	while (--i);
}



void AT24CXX_IIC_Start(void)
{
	AT24CXX_SDA_PIN = 1;
	AT24CXX_SCL_PIN = 1;
	AT24CXX_Delay5us();
	
	AT24CXX_SDA_PIN = 0;
	AT24CXX_Delay5us();
	
	AT24CXX_SCL_PIN = 0;
	AT24CXX_Delay5us();
}

void AT24CXX_IIC_Stop(void)
{
	AT24CXX_SDA_PIN = 0;     
	AT24CXX_Delay5us();

	AT24CXX_SCL_PIN = 1;
	AT24CXX_Delay5us();
	
	AT24CXX_SDA_PIN = 1;
	AT24CXX_Delay5us();
}


void AT24CXX_IIC_WriteByte(unsigned char Byte)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		AT24CXX_SDA_PIN = Byte&(0x80>>i);		//Byte�����λ����
		AT24CXX_SCL_PIN = 1;
		AT24CXX_Delay5us();
        AT24CXX_SCL_PIN = 0;
		AT24CXX_Delay5us();					//�½���д��
	}
}

unsigned char AT24CXX_IIC_ReadByte(void)
{
	unsigned char i,Byte=0x00;
	AT24CXX_SDA_PIN = 1;					//�ڶ�ȡ����֮ǰ��Ҫ��SDA���ߣ��ͷ�����
	AT24CXX_Delay5us();
	for(i=0;i<8;i++)
	{
		AT24CXX_SCL_PIN = 1;
		AT24CXX_Delay5us();
		if(AT24CXX_SDA_PIN)				
			Byte|=(0x80>>i);			//�ȶ�ȡ��λ
		AT24CXX_Delay5us();
		AT24CXX_SCL_PIN= 0;
		AT24CXX_Delay5us();
	}
	
	return Byte;
}

//I2C��������Ӧ��  0:Ӧ��  1����Ӧ��
void AT24CXX_IIC_ACK(unsigned char ACK)
{
	AT24CXX_SDA_PIN = ACK;
	AT24CXX_Delay5us();
    AT24CXX_SCL_PIN = 1;
	AT24CXX_Delay5us();
    AT24CXX_SCL_PIN = 0;
	AT24CXX_Delay5us();
}


//I2C�ӻ�����Ӧ��		0:Ӧ��  1����Ӧ��

unsigned char AT24CXX_IIC_Wait_ACK(void)
{
	unsigned char ACK;
	
	AT24CXX_SDA_PIN = 1;			// �ͷ�����
	AT24CXX_Delay5us();
	
	AT24CXX_SCL_PIN = 1;
	AT24CXX_Delay5us();
	ACK = AT24CXX_SDA_PIN;
	AT24CXX_SCL_PIN = 0;
	AT24CXX_Delay5us();
	
	return ACK;
}




void AT24CXX_IIC_Init(void)
{
	AT24CXX_SCL_PIN = 1;
    AT24CXX_SDA_PIN = 1;
}




