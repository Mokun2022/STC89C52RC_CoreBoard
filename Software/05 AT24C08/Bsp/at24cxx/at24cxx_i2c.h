#ifndef  __AT24CXX_I2C_H__
#define  __AT24CXX_I2C_H__

#include <STC89C5xRC.H>
#include <intrins.h>

 
#define AT24CXX_SCL_PIN  P37
#define AT24CXX_SDA_PIN  P36


void AT24CXX_IIC_Init(void);
unsigned char AT24CXX_IIC_Wait_ACK(void);
void AT24CXX_IIC_ACK(unsigned char ACK);
unsigned char AT24CXX_IIC_ReadByte(void);
void AT24CXX_IIC_WriteByte(unsigned char Byte);
void AT24CXX_IIC_Stop(void);
void AT24CXX_IIC_Start(void);

#endif  


