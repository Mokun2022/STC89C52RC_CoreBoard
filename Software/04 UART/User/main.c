#include <STC89C5xRC.H>
#include "stc_it.h"
#include "timer.h"
#include "delay.h"
#include "uart.h"
#include "key.h"
#include "led.h"

void main(void)
{
	uart_init(2400);
	timer0_init(1000 * 5);

	uart_send_string("20210410B0128\r\n");
	
	while(1)
	{
		if(uart_dev.rev_finish == 1)	//接收串口数据
		{
			uart_send_string(uart_dev.rev_buf);
			uart_send_string("\r\n");
			uart_receive_clear();
		}
	}
}