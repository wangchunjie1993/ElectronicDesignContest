#include<avr/io.h>
#include<avr/interrupt.h>
#include"def.h"

extern float_data roll,pitch,yaw;								  //ÍÓÂİÒÇ²âµÃµÄ½Ç¶È
int receive_count=0;			//ä¸²å£æ¥æ”¶æ•°æ®è®¡æ•°

uchar temp;
/***************
* usart0
***************/
void usart0_init(uint baud)
{
	UBRR0H=baud<<8;
	UBRR0L=baud;
	//UCSR0B|=(1<<7)|(1<<4)|(1<<3);
	UCSR0B|=(1<<3);
	UCSR0C|=(3<<0);
}

void usart0_transmit(uchar data)
{
	while(!(UCSR0A&(1<<5)));
	UDR0=data;
}

void usart0_puts(uchar *str)
{
	while(*str)
	{
		usart0_transmit(*str++);
	}
}



/***************
* usart1
***************/
void usart1_init(uint baud)
{
	UBRR1H=baud<<8;
	UBRR1L=baud;
//	UCSR1B|=(1<<7)|(1<<4)|(1<<3);
	UCSR1B|=(1<<3);
	UCSR1C|=(3<<0);
}

void usart1_transmit(uchar data)
{
	while(!(UCSR1A&(1<<5)));
	UDR1=data;
}

void usart1_puts(uchar *str)
{
	while(*str)
	{
		usart1_transmit(*str++);
	}
}

SIGNAL(USART0_RX_vect)
{

    if(receive_count<4)
	{
		roll.data_trans[receive_count]=UDR0;
	}
	else if(receive_count<8)
	{
		pitch.data_trans[receive_count-4]=UDR0;
	}
	else if(receive_count<12)
	{
		yaw.data_trans[receive_count-8]=UDR0;
	}
	else 
	{
		temp=UDR1;
		usart1_puts("#o0");			//½ûÖ¹Á÷Êä³ö
	}

	receive_count++;
}


