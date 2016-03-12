#include "LCD12864Driver_IO.h"
/**************************************************************************
//程序：void lcd_ms_delay(unsigned int ms_16)
//功能：ms延时
//参数：延时时间
***************************************************************************/
void lcd_ms_delay(unsigned int ms_16)
{
	unsigned int i,j;
	for(i=0;i<ms_16;i++)
	{
	   for(j=0;j<795;j++);
    }
}
/**************************************************************************
//程序：void lcd_10us_delay(unsigned int ten_us_16)
//功能：10us延时
//参数：延时时间
***************************************************************************/
void lcd_10us_delay(unsigned int ten_us_16)
{
    unsigned int p,q;
    for(p=ten_us_16;p>0;p--)
        for(q=9;q>0;q--);
}
/**************************************************************************
//程序：void lcd_reset(void)
//功能：LCD复位
//参数：无
***************************************************************************/
void lcd_reset(void)
{
	/*lcd_PORT_RST_L;			//复位引脚置低
	lcd_ms_delay(5);		//延时1ms
	lcd_PORT_RST_H;			//复位引脚置高*/
}
/**************************************************************************
//程序：void lcd_byte_write(unsigned char byte_8)
//功能：写字节
//参数：一个字节数据（8位）
***************************************************************************/
void lcd_byte_write(unsigned char byte_8)
{	
	unsigned char i;
	lcd_PORT_SCLK_L;
	for(i=8;i>0;i--)
	{
		if(byte_8 & 0x80) lcd_PORT_SID_H;	//置1
		else lcd_PORT_SID_L;				//置0
		//NOP();			//调试时用
		lcd_PORT_SCLK_H;
		lcd_PORT_SCLK_L;
		byte_8=byte_8<<1;
		//------------------//
		//lcd_10us_delay(1);	//模拟SPI串行通信，延时
		//------------------//（调节SPI速度：延时越长，SPI传送速度越慢）
	}
}
/**************************************************************************
//程序：void lcd_command_write(unsigned char command_8)
//功能：写命令
//参数：地址或命令（8位）
***************************************************************************/
void lcd_command_write(unsigned char command_8)
{
	lcd_byte_write(0xf8);	//起始字节：11111、WR=0（写）、RS=0（指令）、0
	lcd_byte_write(command_8 & 0xf0);		//写高四位
	lcd_byte_write(command_8<<4&0xf0);	//写低四位
}
/**************************************************************************
//程序：void lcd_data_write(unsigned char data_8)
//功能：写数据
//参数：数据（8位）
***************************************************************************/
void lcd_data_write(unsigned char data_8)
{
	lcd_byte_write(0xfa);	//起始字节：11111、WR=0（写）、RS=1（数据）、0
	lcd_byte_write(data_8 & 0xf0);		//写高四位
	lcd_byte_write(data_8<<4&0xf0);	//写低四位	
}
/**************************************************************************
//程序：void lcd_screen_clear(void)
//功能：LCD清屏
//参数：无
***************************************************************************/
void lcd_screen_clear(void)
{
	lcd_command_write(0x30);	//基本指令集
	lcd_command_write(0x01);	//清除显示DDRAM
	lcd_ms_delay(2);
}
/**************************************************************************
//程序：void lcd_display_on_off(unsigned char on_off_8)
//功能：显示开关
//参数：开关变量：为1则显示开，否则显示关。
***************************************************************************/
void lcd_display_on_off(unsigned char on_off_8)
{
	lcd_command_write(0x30);	//基本指令集
	if(on_off_8==1) lcd_command_write(0x0C);	//显示状态开关：整体显示开，光标显示关，光标显示反白关
	else lcd_command_write(0x08);				//显示状态开关：整体显示关，光标显示关，光标显示反白关
}
/**************************************************************************
//程序：void lcd_display_initialize(void)
//功能：LCD初始化
//参数：无
***************************************************************************/
void lcd_display_initialize(void)
{
	//unsigned char init_cycles=2;
	//lcd_DDR_RST_Out;		//复位引脚设置为输出
	lcd_DDR_SID_Out;		//数据引脚设置为输出
	lcd_DDR_SCLK_Out;		//时钟引脚设置为输出
	lcd_DDR_CS_Out;			//片选引脚设置为输出
	lcd_DDR_PSB_OUT;
	lcd_DDR_PSB_L;
	lcd_ms_delay(40);
	lcd_reset();			//LCD复位
	lcd_PORT_CS_H;			//片选使能
	lcd_command_write(0x30);	//基本指令集
	lcd_10us_delay(15);
	lcd_command_write(0x30);	//基本指令集
	lcd_10us_delay(5);
	lcd_command_write(0x0C);	//显示状态开关：整体显示开，光标显示关，光标显示反白关
	lcd_10us_delay(15);
	lcd_command_write(0x01);	//清除显示DDRAM
	lcd_ms_delay(15);
	lcd_command_write(0x06);	//起始点设定，光标右移
	lcd_command_write(0x02);	//地址归零
	lcd_screen_clear();		//LCD清屏
	lcd_display_on_off(1);	//开显示
	//以下是初始化完成LED信号指示，闪烁两次
	/*while(init_cycles!=0)	//LED灯（D3）闪烁三次
	{
		runled_1;			//D3---LED灯亮
		lcd_ms_delay(300);
		runled_0;			//D3---LED灯灭
		lcd_ms_delay(300);
		init_cycles--;
	}
	runled_0;				//D3---LED灯灭*/
}
