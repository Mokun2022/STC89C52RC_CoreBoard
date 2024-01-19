#include <STC89C5xRC.H>
#include "delay.h"
#include "led.h"
#include "key.h"

void main(void)
{
	unsigned char key_val;

	while(1)
	{
		key_val = key_scan();
		
		if(key_val == KEY_VAL_0)
			led_toggle(LED0);
		if(key_val == KEY_VAL_1)
			led_toggle(LED1);
		if(key_val == KEY_VAL_2)
			led_toggle(LED2);
		if(key_val == KEY_VAL_3)
			led_toggle(LED3);
	}
}