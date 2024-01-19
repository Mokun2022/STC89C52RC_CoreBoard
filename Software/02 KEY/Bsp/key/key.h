#ifndef  __KEY_H__
#define  __KEY_H__

#include <STC89C5xRC.H>

#define KEY0_PIN	P32
#define KEY1_PIN	P33
#define KEY2_PIN	P42
#define KEY3_PIN	P43

typedef enum
{
	KEY_VAL_0 = 0,
	KEY_VAL_1,
	KEY_VAL_2,
	KEY_VAL_3,
	KEY_VAL_DEFAULT,
	
}key_val_e;

unsigned char key_scan(void);

#endif