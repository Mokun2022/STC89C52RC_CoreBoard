#include "stc_it.h"
#include "led.h"

int count = 0;

void timer0_handler(void) interrupt 1
{
	TH0 =(65535 - 1000 * 5)/256;
	TL0 =(65535 - 1000 * 5)%256;

	if(++count >= 200)	//200´Î5ms == 1s
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