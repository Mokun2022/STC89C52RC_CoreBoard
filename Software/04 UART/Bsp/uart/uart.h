#ifndef  _UART__H_
#define  _UART__H_

#include <STC89C5xRC.H>
#include <stdio.h>

#define  FOSC  	12000000
#define  REV_BUFF_SIZE  64

typedef struct
{
	unsigned int  rev_len;
	unsigned char rev_finish;
	unsigned char rev_buf[REV_BUFF_SIZE];
	
}UartDev_TypeDef;

extern UartDev_TypeDef uart_dev;

void uart_init(int baud_rate);
void uart_send_string(const char *str);
void uart_send_number(int len, const int num);
void uart_receive_clear(void);
void uart_receive_string(char *rev_data);

#endif
