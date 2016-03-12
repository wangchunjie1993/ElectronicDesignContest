#include<avr/io.h>
#include"SPI.h"
#include"def.h"
//SPI初始化
void SPI_Init(void)
{
	DDR_SPI|=((1<<MOSI)|(1<<SCK)|(1<<CSN));	//设置MOSI、SCK、CSN输出，其余输入
	DDRF|=(1<<CE);
	DDR_SPI&=~(1<<MISO);					//一直为主机模式
	DDRF &= ~(1<<IRQ);
    PORTF |= (1<<IRQ);
	SPCR|=((1<<SPE)|(1<<MSTR));						//使能SPI、主机，set clock rate fck/4
													//
}


// SPI基本读写函数
uint8_t SpiRW(uint8_t val)  	
{
	uint8_t temp; 
    SPDR=val; 
	while (!(SPSR&(1<<SPIF)))
		; 
    temp=SPSR;//对SPIF清零
	temp=SPDR; 
    return temp; 
} 
