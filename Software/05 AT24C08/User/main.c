#include <STC89C5xRC.H>
#include "string.h"
#include "at24cxx.h"
#include "stc_it.h"
#include "timer.h"
#include "delay.h"
#include "uart.h"
#include "key.h"
#include "led.h"

#define SAVE_ADDR  0x00

code unsigned char write_buf1[] = "ABCDEFGHI";				//储存数据区1
code unsigned char write_buf2[] = "123456789";				//储存数据区2

unsigned char len=sizeof(write_buf1)/sizeof(unsigned char);	//数据大小

unsigned char read_buf[16];									//读取缓冲区

void main(void)
{
	unsigned char key_val;
	
	uart_init(2400);		
	x24cxx_Init();		
	timer0_init(1000 * 5);	//5ms

	uart_send_string("SYSTEM_INIT_OK!\r\n");
	
	while(1)
	{
		//按键处理
		key_val = key_scan();
		switch(key_val)
		{
			case KEY_VAL_0:	//写数据1
				x24Cxx_WritePage(SAVE_ADDR, len, write_buf1);
				uart_send_string("WriteSize:\r\n");
				uart_send_number(2, len);
				uart_send_string("\r\nWriteData:\r\n");
				uart_send_string(write_buf1);
				break;
			
			case KEY_VAL_1:	//写数据2
				x24Cxx_WritePage(SAVE_ADDR, len, write_buf2);
				uart_send_string("WriteSize:\r\n");
				uart_send_number(2, len);
				uart_send_string("\r\nWriteData:\r\n");
				uart_send_string(write_buf2);
				break;
			
			case KEY_VAL_2:	//读数据
				x24Cxx_ReadPage(SAVE_ADDR, len, read_buf);
				uart_send_string("\r\nReadData:\r\n");
				uart_send_string(read_buf);
				break;
			
			case KEY_VAL_3:	//清除读缓冲区
				memset(read_buf, 0, len);
				uart_send_string("\r\nClearReadData!\r\n");
				break;
			  
			default:
				break;
		}
		
		//串口数据回环测试
		if(uart_dev.rev_finish == 1)	
		{
			uart_send_string(uart_dev.rev_buf);
			uart_receive_clear();
		}
	}
}
