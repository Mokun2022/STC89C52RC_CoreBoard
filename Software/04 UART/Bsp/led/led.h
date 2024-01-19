#ifndef __LED_H__
#define __LED_H__

#include <STC89C5xRC.H>

#define LED0_PIN		P34
#define LED1_PIN		P35
#define LED2_PIN		P40
#define LED3_PIN		P41

typedef enum
{
	LED0 = 0,
	LED1,
	LED2,
	LED3
}led_drive_e;

void led_toggle(led_drive_e led);
unsigned char led_get(led_drive_e led);
void led_set(led_drive_e led, unsigned char state);


#endif