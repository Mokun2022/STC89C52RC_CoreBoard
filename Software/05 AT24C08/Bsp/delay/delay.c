#include "delay.h"

void Delay1ms(void)	//@12.000MHz
{
	unsigned char data i, j;

	i = 2;
	j = 239;
	do
	{
		while (--j);
	} while (--i);
}

void delay_ms(unsigned int ms)
{
	while(ms--)
		Delay1ms();
}