#include "led.h"

void led_set(led_drive_e led, unsigned char state)
{
	switch(led)
	{
		case LED0:
			if(state)	
				LED0_PIN = 1;	
			else
				LED0_PIN = 0;	
			break;
			
		case LED1:
			if(state)	
				LED1_PIN = 1;	
			else
				LED1_PIN = 0;	
			break;

		case LED2:
			if(state)	
				LED2_PIN = 1;	
			else
				LED2_PIN = 0;	
			break;
			
		case LED3:
			if(state)	
				LED3_PIN = 1;	
			else
				LED3_PIN = 0;	
			break;
			
		default:
			break;
	}
}

void led_toggle(led_drive_e led)
{
	switch(led)
	{
		case LED0:
			LED0_PIN = !LED0_PIN;
			break;
			
		case LED1:	
			LED1_PIN = !LED1_PIN;	
			break;

		case LED2:
			LED2_PIN = !LED2_PIN;	
			break;
			
		case LED3:
			LED3_PIN = !LED3_PIN;
			break;
			
		default:
			break;	
	}
}

unsigned char led_get(led_drive_e led)
{
	switch(led)
	{
		case LED0:
			return LED0_PIN;
			
		case LED1:
			return LED1_PIN;

		case LED2:
			return LED2_PIN;
			
		case LED3:
			return LED3_PIN;
			
		default:
			break;	
	}
	return 0;
}