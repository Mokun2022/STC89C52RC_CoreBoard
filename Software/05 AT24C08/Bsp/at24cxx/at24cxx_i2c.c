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
		AT24CXX_SDA_PIN = Byte&(0x80>>i);		//Byte的最高位输入
		AT24CXX_SCL_PIN = 1;
		AT24CXX_Delay5us();
        AT24CXX_SCL_PIN = 0;
		AT24CXX_Delay5us();					//下降沿写入
	}
}

unsigned char AT24CXX_IIC_ReadByte(void)
{
	unsigned char i,Byte=0x00;
	AT24CXX_SDA_PIN = 1;					//在读取数据之前，要把SDA拉高，释放总线
	AT24CXX_Delay5us();
	for(i=0;i<8;i++)
	{
		AT24CXX_SCL_PIN = 1;
		AT24CXX_Delay5us();
		if(AT24CXX_SDA_PIN)				
			Byte|=(0x80>>i);			//先读取高位
		AT24CXX_Delay5us();
		AT24CXX_SCL_PIN= 0;
		AT24CXX_Delay5us();
	}
	
	return Byte;
}

//I2C主机发送应答  0:应答  1：非应答
void AT24CXX_IIC_ACK(unsigned char ACK)
{
	AT24CXX_SDA_PIN = ACK;
	AT24CXX_Delay5us();
    AT24CXX_SCL_PIN = 1;
	AT24CXX_Delay5us();
    AT24CXX_SCL_PIN = 0;
	AT24CXX_Delay5us();
}


//I2C从机接收应答		0:应答  1：非应答

unsigned char AT24CXX_IIC_Wait_ACK(void)
{
	unsigned char ACK;
	
	AT24CXX_SDA_PIN = 1;			// 释放总线
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




