#include "stc_it.h"
#include "led.h"
#include "uart.h"

int count = 0;

void timer0_handler(void) interrupt 1
{
	TH0 =(65535 - 1000 * 5)/256;
	TL0 =(65535 - 1000 * 5)%256;

	if(++count >= 200)	//200次5ms == 1s
	{
		count = 0;
		led_toggle(LED0);
		led_toggle(LED1);
		led_toggle(LED2);
		led_toggle(LED3);
	}
}

void timer1_handler(void) interrupt 3
{

}

//串口接收中断
void uart_isr() interrupt 4
{
	unsigned char temp;
	if(RI == 1)
	{
		temp = SBUF;
		if(temp != '\r' && temp!= '\n')
		{
			uart_dev.rev_buf[uart_dev.rev_len++] = temp;
			if(uart_dev.rev_len >= REV_BUFF_SIZE - 2)		//留一个位置给'\0'
			{
				uart_dev.rev_len = REV_BUFF_SIZE - 2;
			}
		}
		else
		{
			uart_dev.rev_finish = 1;
			uart_dev.rev_buf[uart_dev.rev_len + 1] = '\0';
		}
		RI=0;
	}
}
