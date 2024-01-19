#include  "uart.h"
#include  "string.h"

UartDev_TypeDef uart_dev;

//���ڳ�ʼ��
void uart_init(int baud_rate)				//	Baud_Rate  ������Ԥ����
{
	//���ô��ڼĴ���
	SCON  =  0X50;						    //���ڷ�ʽ1  10λUART  ʧ��У�� ʹ�ܽ��� �����־λ
	PCON &= ~(0x1<<7);					   //�����ʲ�����

	//��ʱ��1,��ʽ2
	TMOD &= ~(0XF<<4);  						  //����
	TMOD |= (0x2<<4); 					 	  //��ʽ2
	
	TH1=TL1=(256-(FOSC / 32 / 12 / baud_rate));	//��ʱ��Ԥ�� =>������
	ET1 = 0;									//��ֹ��ʱ��1�ж�
	TR1 = 1;							        //������ʱ��1
	EA=1;										//�������ж�
	ES=1;										//���������ж�
}


//���ڷ���һ���ֽڵ�����
static void uart_send_byte(const char byte)
{
	SBUF = byte;
	while(TI == 0);			//�ȴ��ϴη������
	TI= 0;				//�������
}


//���ڽ���һ���ֽڵ�����
static char uart_receive_byte(void)
{
	char rev_data;	
	while(RI == 0);		//�ȴ��������	
	RI = 0;				//�������
	rev_data = SBUF;			
	return rev_data;
}


//���ڷ����ַ���
void uart_send_string(const char *str)
{
	while(*str != '\0')
	{
		uart_send_byte(*str++);
	}
}



//����ֵ=X��Y�η�
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


//���ڷ�������
void uart_send_number(int len, const int num)
{
	int i = 0;
	for(i = len; i > 0; i--)
	{
		uart_send_byte(num / uart_pow(10,i-1)%10+'0');
	}
}



//���ڽ����ַ���(����ģʽ,���ж�)
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




