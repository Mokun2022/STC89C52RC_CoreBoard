#include <STC89C5xRC.H>
#include "delay.h"
#include "led.h"


//void main(void)
//{
//	while(1)
//	{
//		led_toggle(LED0);
//		led_toggle(LED1);
//		led_toggle(LED2);
//		led_toggle(LED3);
//		delay_ms(500);
//	}
//}

static void delay_ms(unsigned char t)
{
	while(t--);
}

#define Compare	100
#define Delay 20

void main(void)
{
	unsigned char i, time;
	
	while(1)
	{
		for(time = 0; time < Compare; time++)
		{
			for(i = 0; i< Delay; i++)
			{
				led_set(LED0, 1);
				led_set(LED1, 1);
				led_set(LED2, 1);
				led_set(LED3, 1);
				delay_ms(time);
				led_set(LED0, 0);
				led_set(LED1, 0);
				led_set(LED2, 0);
				led_set(LED3, 0);
				delay_ms(Compare - time);
			}
		}
		for(time = Compare; time > 0; time--)
		{
			for(i = 0; i< Delay; i++)
			{
				led_set(LED0, 1);
				led_set(LED1, 1);
				led_set(LED2, 1);
				led_set(LED3, 1);
				delay_ms(time);
				led_set(LED0, 0);
				led_set(LED1, 0);
				led_set(LED2, 0);
				led_set(LED3, 0);
				delay_ms(Compare - time);
			}
		}
	}
}