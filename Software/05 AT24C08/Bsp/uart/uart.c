#include  "uart.h"
#include  "string.h"

UartDev_TypeDef uart_dev;

//串口初始化
void uart_init(int baud_rate)				//	Baud_Rate  波特率预设置
{
	//配置串口寄存器
	SCON  =  0X50;						    //串口方式1  10位UART  失能校验 使能接收 清除标志位
	PCON &= ~(0x1<<7);					   //波特率不翻倍

	//定时器1,方式2
	TMOD &= ~(0XF<<4);  						  //清零
	TMOD |= (0x2<<4); 					 	  //方式2
	
	TH1=TL1=(256-(FOSC / 32 / 12 / baud_rate));	//定时器预设 =>波特率
	ET1 = 0;									//禁止定时器1中断
	TR1 = 1;							        //启动定时器1
	EA=1;										//启动总中断
	ES=1;										//启动串口中断
}


//串口发送一个字节的数据
static void uart_send_byte(const char byte)
{
	SBUF = byte;
	while(TI == 0);			//等待上次发送完成
	TI= 0;				//软件清零
}


//串口接收一个字节的数据
static char uart_receive_byte(void)
{
	char rev_data;	
	while(RI == 0);		//等待接收完成	
	RI = 0;				//软件清零
	rev_data = SBUF;			
	return rev_data;
}


//串口发送字符串
void uart_send_string(const char *str)
{
	while(*str != '\0')
	{
		uart_send_byte(*str++);
	}
}



//返回值=X的Y次方
static int uart_pow(int x,int y)
{
	unsigned char i;
	int result = 1;
	for(i = 0;i < y; i++)
	{
		result *= x;
	}
	return result;
}


//串口发送数字
void uart_send_number(int len, const int num)
{
	int i = 0;
	for(i = len; i > 0; i--)
	{
		uart_send_byte(num / uart_pow(10,i-1)%10+'0');
	}
}



//串口接收字符串(阻塞模式,无中断)
void uart_receive_string(char *rev_data)
{
	int i=0;
	char temp;
	
	while(1)
	{
		temp = uart_receive_byte();
		if(temp !='\n' && temp!='\r')
		{
			*rev_data++ = temp;
		}
		else
		{
			rev_data[i]= '\0';
			i=0;	
			return;
		}
	}
}

void uart_receive_clear(void)
{
	uart_dev.rev_len = 0;
	uart_dev.rev_finish = 0;
	memset(uart_dev.rev_buf, 0x00, REV_BUFF_SIZE);
}




