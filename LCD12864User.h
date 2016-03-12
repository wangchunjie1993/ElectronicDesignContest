#ifndef _LCD12864USER_H_
#define _LCD12864USER_H_

#include "LCD12864Driver_IO.h"
extern unsigned char lcd_buffer[64][16];//lcd图形显示缓冲区
extern unsigned char temperature_coordinate[];			//temperature_coordinate图片数组
extern unsigned char intel[][8];				//avr图片数组
extern unsigned char gImage_test1[1024];
unsigned char gImage_yanshan[1024];
//----------------------------写字符串-----------------------------------------------------------//
void lcd_string_write(unsigned char address_8,unsigned char *string_8);
//----------------------------写多行字符串-------------------------------------------------------//
void lcd_multi_line_string_write(unsigned char address_8,unsigned char *string_8);
//----------------------------显示左移-----------------------------------------------------------//
void lcd_display_left_move(unsigned char number_8);
//----------------------------显示右移-----------------------------------------------------------//
void lcd_display_right_move(unsigned char number_8);
//----------------------------全屏反白-----------------------------------------------------------//
void lcd_display_inverse(void);
//----------------------------图片清屏-----------------------------------------------------------//
void lcd_picture_clear(void);
void _lcd_picture_clear(void);
//----------------------------画全屏图片---------------------------------------------------------//
void lcd_picture_draw(unsigned char *picture_8);
void _lcd_picture_draw(unsigned char picture_8[][8]);
void __lcd_picture_draw(unsigned char picture_8[][16]);
//----------------------------画小图片-----------------------------------------------------------//
void lcd_small_picture_draw(unsigned char x_8,unsigned char y_8,
							unsigned char lenght_8,unsigned char height_8,
							const unsigned char *picture_8);
//----------------------------画点---------------------------------------------------------------//
void lcd_point_draw(unsigned char x_8,unsigned char y_8,unsigned char color_8);
void _lcd_point_draw(unsigned char x_8,unsigned char y_8,unsigned char color_8,unsigned char lcd_buffer[64][16]);
//----------------------------画直线-------------------------------------------------------------//此函数待完成
void lcd_line_draw(unsigned char x0_8,unsigned char y0_8,
				   unsigned char x1_8,unsigned char y1_8,unsigned char color_8);
//----------------------------画圆---------------------------------------------------------------//此函数待完成
void lcd_circle_draw(unsigned char x_8,unsigned char y_8,unsigned char radius_8);

#endif
