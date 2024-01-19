#include "key.h"
#include "delay.h"

unsigned char key_scan(void)
{
	static char kp = 0;	
	
	if((KEY0_PIN != 1) || (KEY1_PIN != 1) || (KEY2_PIN != 1) || (KEY3_PIN != 1))
	{
		delay_ms(10);
		if(((KEY0_PIN != 1) || (KEY1_PIN != 1) || (KEY2_PIN != 1) || (KEY3_PIN != 1)) && (kp == 0))
		{
			kp = 1;
			if(KEY0_PIN == 0)
				return KEY_VAL_0;
			
			if(KEY1_PIN == 0)
				return KEY_VAL_1;	
			
			if(KEY2_PIN == 0)
				return KEY_VAL_2;
			
			if(KEY3_PIN == 0)
				return KEY_VAL_3;	
		}
	}
	else
		kp = 0;
	
	return KEY_VAL_DEFAULT;
}
