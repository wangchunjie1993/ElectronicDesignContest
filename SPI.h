#ifndef _SPI_H_
#define _SPI_H_
///SPI宏定义
#include<avr/io.h>
#define DDR_SPI		DDRB
#define PORT_SPI	PORTB
#define CSN 		PB0	//信号的片选，低电平芯片工作
#define MOSI 		PB2//Master Output Slave Input
#define MISO 		PB3//Master Input Slave Output
#define SCK 		PB1//时钟信号
#define CE			PF2//芯片模式控制线
#define IRQ			PF3//中断信号

void SPI_Init(void);
uint8_t SpiRW(uint8_t val);
#endif
