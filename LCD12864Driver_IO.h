#ifndef _LCD12864DRIVER_IO_H_
#define _LCD12864DRIVER_IO_H_

#include <avr/io.h>
/*-----------------------LCD控制硬件说明-----------------
//MCU:ATmega128A
//单片机时钟：外部8MHz晶振
//LCD型号：12864ZW
//LCD控制器：ST7920
//LCD供电电压：5V
//控制接口：串行接口
----------------------------END-------------------------*/
/*-----------------------LCD固定接线----------------------
//MCU---LCD12864ZW_ST7920串行控制   	
//硬件接线方法：
//———————————————————————————————
//1. GND(VSS)	--------	GND
//2. VCC(VDD)	--------	VCC
//3. V0			--------	VCC
//4. RS(CS)		--------	PC2
//5. R/W(SID)	--------	PC0
//6. E(SCLK)	--------	PC1
//15.PSB		--------	GND
//17.RST		--------	PC3
//19.LED+(A)	--------	VCC
//20.LED-(K)	--------	GND
———————————————————————————————
----------------------------END-------------------------*/
//D3---LED灯
//#define runled_1 	PORTA|=(1<<0)
//#define runled_0 	PORTA&=~(1<<0)
//******************液晶屏相关定义*********************
//如果需要修改端口定义，只需在此处更改
//*************CS（RS） 端口 定义**************串行片选信号，高电平有效
#define lcd_DDR_CS_Out 		(DDRG|=(1<<2))
#define lcd_PORT_CS_H 		(PORTG|=(1<<2))
#define lcd_PORT_CS_L 		(PORTG&=~(1<<2))
//*************RST 端口 定义*******************复位脚，低电平有效
//#define lcd_DDR_RST_Out 	(DDRC|=(1<<3))
//#define lcd_PORT_RST_H 		(PORTC|=(1<<3))
//#define lcd_PORT_RST_L 		(PORTC&=~(1<<3))
//*************SCLK（E） 端口 定义*************串行时钟信号
#define lcd_DDR_SCLK_Out 	(DDRG|=(1<<4))
#define lcd_PORT_SCLK_H 	(PORTG|=(1<<4))
#define lcd_PORT_SCLK_L 	(PORTG&=~(1<<4))
//*************SID（R/W） 端口 定义************串行数据输入端
#define lcd_DDR_SID_Out 	(DDRG|=(1<<3))
#define lcd_PORT_SID_H 		(PORTG|=(1<<3))
#define lcd_PORT_SID_L 		(PORTG&=~(1<<3))

//并行、串行选择端
#define lcd_DDR_PSB_OUT 	(DDRG|=(1<<1))
#define lcd_DDR_PSB_H		(PORTG|=(1<<1))
#define lcd_DDR_PSB_L		(PORTG&=~(1<<1))
//-----------------------ms延时---------------------------//
void lcd_ms_delay(unsigned int ms_16);
//-----------------------10us延时-------------------------//
void lcd_10us_delay(unsigned int ten_us_16);
//-----------------------LCD复位--------------------------//
void lcd_reset(void);
//-----------------------写字节---------------------------//
void lcd_byte_write(unsigned char byte_8);
//-----------------------写命令---------------------------//
void lcd_command_write(unsigned char command_8);
//-----------------------写数据---------------------------//
void lcd_data_write(unsigned char data_8);
//-----------------------LCD清屏--------------------------//
void lcd_screen_clear(void);
//-----------------------显示开关-------------------------//
void lcd_display_on_off(unsigned char on_off_8);
//-----------------------LCD初始化------------------------//
void lcd_display_initialize(void);

#endif
