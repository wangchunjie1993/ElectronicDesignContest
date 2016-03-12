#include "LCD12864User.h"

unsigned char lcd_buffer[64][16];//lcd图形显示缓冲区


//unsigned char gImage_test1[1024] = { /* 0X10,0X01,0X00,0X80,0X00,0X40, */
/*0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X80,0X20,0X08,0X02,0X00,0X80,0X20,0X08,0X02,0X00,0X80,0X20,0X08,0X02,0X00,0X80,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
};*/


unsigned char gImage_yanshan[1024] = { /* 0X10,0X01,0X00,0X80,0X00,0X30, */
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X80,0X00,
0X00,0X01,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XE8,0X00,
0X00,0X03,0XE0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XFC,0X00,
0X00,0X01,0XE0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XF8,0X00,
0X00,0X01,0XE0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XCF,0X00,
0X00,0XC1,0XE0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XDF,0X80,
0X00,0XC3,0XF8,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X0C,0XDD,0XC0,
0X00,0X7F,0XF8,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X0F,0XE1,0X80,
0X01,0XFF,0XF8,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X6C,0XFD,0X80,
0X07,0XFF,0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X3C,0X00,0X00,0X7D,0XBF,0X00,
0X07,0XFF,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X78,0X00,0X00,0X75,0XB7,0X00,
0X03,0XF6,0X0C,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XF6,0X00,0X00,0X77,0XAF,0X00,
0X01,0XFF,0X1C,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XFF,0X80,0X00,0X37,0XEF,0X00,
0X0E,0XFF,0X8C,0X00,0X00,0X00,0X00,0X00,0X00,0X3F,0XFF,0XC0,0X00,0X37,0XE7,0X60,
0X1F,0X7F,0X0E,0X00,0X00,0X03,0X00,0X00,0X00,0X7F,0XFF,0X80,0X00,0X37,0XFF,0XF8,
0X0F,0X3E,0XDF,0X00,0X00,0X07,0X80,0X00,0X00,0X7F,0XC0,0X00,0X02,0X17,0XFF,0XFC,
0X07,0X9F,0XFB,0X80,0X00,0X07,0X80,0X00,0X00,0X03,0XC0,0X00,0X07,0X3F,0XC0,0XF8,
0X07,0X9F,0XFF,0X80,0X00,0X07,0XC0,0XC0,0X00,0X07,0X80,0X00,0X07,0XBC,0X01,0XF0,
0X0F,0XFF,0XDF,0X00,0X00,0X07,0XE0,0XE0,0X00,0X07,0X00,0X00,0X07,0X80,0X03,0XC0,
0X3F,0X7D,0XBC,0X00,0X00,0XC7,0XE0,0XF0,0X00,0X0F,0X00,0X00,0X07,0X80,0X7E,0X00,
0XFF,0X77,0X78,0X00,0X00,0XC7,0XE0,0XF0,0X00,0X0E,0X00,0X00,0X0F,0X01,0XFE,0X00,
0X37,0XE7,0XF0,0X00,0X01,0XC7,0XE0,0XF0,0X00,0X1E,0X00,0X00,0X06,0X03,0XFE,0X00,
0X07,0XEE,0XE0,0X00,0X03,0XE7,0XF0,0XF0,0X00,0X3F,0XF8,0X00,0X06,0X07,0X38,0X00,
0X07,0XEE,0X7F,0X80,0X03,0XFF,0XFE,0XF0,0X00,0X3D,0XFF,0XE0,0X00,0X00,0X30,0X00,
0X0F,0X6E,0X7F,0XC0,0X07,0XFF,0XFE,0XF0,0X01,0XF8,0X07,0XF0,0X00,0X00,0X70,0X00,
0X1E,0X06,0XFF,0X80,0X03,0XF0,0X00,0X60,0X03,0XF0,0X03,0XF0,0X00,0X00,0X78,0X00,
0X1E,0X00,0X78,0X00,0X03,0XC0,0X00,0X00,0X03,0XE0,0X07,0XF8,0X00,0X00,0X3F,0XE0,
0X1C,0X00,0XC0,0X00,0X00,0XC0,0X00,0X00,0X03,0XC0,0X1F,0XF8,0X00,0X00,0XFF,0XE0,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,0X00,0X00,0X00,0X00,0X03,0XFF,0XF0,
0X00,0X04,0X0F,0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X02,0X1C,0X10,
0X07,0X1F,0X8F,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X02,0X3C,0X00,
0X1F,0X0F,0X01,0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,0XF8,0X00,
0X07,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,0XF0,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X80,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X24,0X18,0X6C,0X70,0XB0,0XC1,0XA0,0X09,0X1B,0X18,0X90,0XE3,0XC3,0XC6,0X3C,0X48,
0X3C,0X38,0X6C,0XD8,0XB0,0XE1,0XA0,0X09,0X1B,0X18,0X90,0X81,0X62,0XC6,0X18,0X78,
0X18,0X28,0X7C,0X60,0XB0,0XA1,0XA0,0X09,0X1F,0X18,0XF0,0X81,0X63,0X06,0X18,0X70,
0X18,0X2C,0X7C,0X30,0XF0,0XA1,0XE0,0X09,0X1F,0X18,0XF0,0XE3,0XC1,0XC6,0X18,0X30,
0X18,0X3C,0X7C,0X18,0XB1,0XE1,0X60,0X09,0X1F,0X18,0X70,0X81,0X60,0XC6,0X18,0X30,
0X18,0X2C,0X6C,0XD8,0XB1,0XB1,0X60,0X09,0X1B,0X18,0X60,0X81,0X62,0XC6,0X18,0X30,
0X18,0X64,0X6C,0X70,0XB1,0X31,0X60,0X0F,0X1B,0X18,0X60,0XE1,0X63,0X86,0X18,0X30,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};







/**************************************************************************
//程序：void lcd_string_write(unsigned char address_8,unsigned char *string_8)
//功能：写字符串
//参数：起始地址，字符串指针
***************************************************************************/
void lcd_string_write(unsigned char address_8,unsigned char *string_8)
{
	lcd_command_write(0x30);	//基本指令集
	lcd_command_write(address_8);
	while(*string_8!='\0')
	{
		lcd_data_write(*string_8);	//一个汉字要写两次
		string_8++;
		//lcd_data_write(*string_8);
		//string_8++;
	}
}

/**************************************************************************
//程序：void lcd_multi_line_string_write(unsigned char address_8,unsigned char *string_8)
//功能：写多行字符串
//参数：起始地址，字符串指针
//备注：函数功能未测试
***************************************************************************/
void lcd_multi_line_string_write(unsigned char address_8,unsigned char *string_8)
{
	lcd_command_write(0x30);	//基本指令集
	while(*string_8!='\0')
	{	
		switch(address_8)
		{
			case 0x88 : address_8=0x90;break;
			case 0x98 : address_8=0x88;break;
			case 0x90 : address_8=0x98;break;
			case 0x80 : address_8=0x80;break;
			default   : break;
		}
		lcd_command_write(address_8++);
		lcd_data_write(*string_8++);	
	}
}
/**************************************************************************
//程序：void lcd_display_left_move(unsigned char number_8)
//功能：显示左移
//参数：移动次数
***************************************************************************/
void lcd_display_left_move(unsigned char number_8)
{
	unsigned char move;
	lcd_command_write(0x30);		//基本指令集
	for(move=number_8;move>0;move--)
	{
		lcd_command_write(0x18);	//显示向左移动，游标跟着移动
	}
}
/**************************************************************************
//程序：void lcd_display_right_move(unsigned char number_8)
//功能：显示右移
//参数：移动次数
***************************************************************************/
void lcd_display_right_move(unsigned char number_8)
{
	unsigned char move;
	lcd_command_write(0x30);		//基本指令集
	for(move=number_8;move>0;move--)
	{
		lcd_command_write(0x1C);	//显示向右移动，游标跟着移动
	}
}
/**************************************************************************
//程序：void lcd_display_inverse(void)
//功能：全屏反白。仅可用于文字反白。
//参数：无
***************************************************************************/
void lcd_display_inverse(void)
{
	unsigned char count=2,X=0x80,i,j;		//循环变量
	lcd_command_write(0x34);	//扩充指令集，绘图显示关
	lcd_command_write(0x36);	//扩充指令集，绘图显示开 
	for(count=2;count>0;count--)
	{
		for(i=0;i<32;i++)
		{   
			lcd_command_write(0x80|i);
			lcd_command_write(X); 		//X地址坐标,自动加1.
			for(j=0;j<16;j++)  			//16*8=128
				lcd_data_write(0xFF); 	//反白
		}
		X=0x88;	//下半屏   
	}  
	lcd_command_write(0x30);	//基本指令集
}
/**************************************************************************
//程序：void lcd_picture_clear(void)
//功能：图片清屏
//参数：无
***************************************************************************/
void lcd_picture_clear(void)
{
	unsigned char count=2,X=0x80,i,j;		//循环变量
	unsigned char m,n;		//循环变量
	for(m=0;m<64;m++)		//清空LCD图片缓冲数组
	{
		for(n=0;n<16;n++)
		{
			lcd_buffer[m][n]=0x00;
		}
	}
	lcd_command_write(0x34);	//扩充指令集，绘图显示关
	lcd_command_write(0x36);	//扩充指令集，绘图显示开 
	for(count=2;count>0;count--)//清空LCD的图形缓冲区（GDRAM）
	{
		for(i=0;i<32;i++)
		{   
			lcd_command_write(0x80|i);
			lcd_command_write(X); 		//X地址坐标,自动加1.
			for(j=0;j<16;j++)  			//16*8=128
				lcd_data_write(0x00); 	//填充无色
		}
		X=0x88;	//下半屏   
	}


	lcd_command_write(0x30);	//基本指令集
}

void _lcd_picture_clear(void)
{
	unsigned char count=2,X=0x80,i,j;		//循环变量
	lcd_command_write(0x34);	//扩充指令集，绘图显示关
	lcd_command_write(0x36);	//扩充指令集，绘图显示开 
	for(count=2;count>0;count--)
	{
		for(i=0;i<32;i++)
		{   
			lcd_command_write(0x80|i);
			lcd_command_write(X); 		//X地址坐标,自动加1.
			for(j=0;j<16;j++)  			//16*8=128
				lcd_data_write(0x00); 	//填充无色
		}
		X=0x88;	//下半屏   
	}  
	lcd_command_write(0x30);	//基本指令集
}

/**************************************************************************
//程序：void lcd_picture_draw(unsigned char *picture_8)
//功能：画全屏图片（点数为128*64）。
//参数：全屏图片数组指针
***************************************************************************/
void lcd_picture_draw(unsigned char *picture_8)
{
	unsigned char count=2,X=0x80,i,j;	//循环变量
	unsigned char m,n;		//循环变量
	unsigned char *temp=picture_8;	//获得图片数组首地址
	for(m=0;m<64;m++)				//将图片或入LCD图片缓冲数组
	{
		for(n=0;n<16;n++)
		{
			lcd_buffer[m][n]|=(*temp++);
		}
	}
	picture_8=&lcd_buffer[0][0];	//获得LCD图片缓冲数组首地址
	lcd_command_write(0x34);	//扩充指令集，绘图显示关
	lcd_command_write(0x36);	//扩充指令集，绘图显示开
	for(count=2;count>0;count--)	//将LCD图片缓冲数组图片写入LCDGDRAM
	{
		for(i=0;i<32;i++)
		{   
			lcd_command_write(0x80|i);
			lcd_command_write(X); 		//X地址坐标,自动加1.
			for(j=0;j<16;j++)  			//16*8=128
				lcd_data_write(*picture_8++); 
		}
		X=0x88;	//下半屏   
	}  
	lcd_command_write(0x30);	//基本指令集
}

void __lcd_picture_draw(unsigned char picture_8[][16])
{
	unsigned char count=2,X=0x80,i,j,hang;	//循环变量
	unsigned char m,n;		//循环变量
	unsigned char *temp=picture_8;	//获得图片数组首地址
	for(m=0;m<64;m++)				//将图片或入LCD图片缓冲数组
	{
		for(n=0;n<16;n++)
		{
			lcd_buffer[m][n]|=(*temp++);
		}
	}
	picture_8=&lcd_buffer[0][0];	//获得LCD图片缓冲数组首地址
	lcd_command_write(0x34);	//扩充指令集，绘图显示关
	lcd_command_write(0x36);	//扩充指令集，绘图显示开
	for(count=2;count>0;count--)	//将LCD图片缓冲数组图片写入LCDGDRAM
	{
		for(i=0;i<32;i++)
		{   
			lcd_command_write(0x80|i);
			lcd_command_write(X); 		//X地址坐标,自动加1.
			for(j=0;j<16;j++)  			//16*8=128
				lcd_data_write(picture_8[hang][j]); 
			hang++;
		}
		X=0x88;	//下半屏   
	}  
	lcd_command_write(0x30);	//基本指令集
}


void _lcd_picture_draw(unsigned char picture_8[][8])
{
	unsigned char count=2,X=0x80,i,j,k,hang=0;		//循环变量
	lcd_command_write(0x34);	//扩充指令集，绘图显示关
	lcd_command_write(0x36);	//扩充指令集，绘图显示开
	for(count=2;count>0;count--)
	{
		for(i=0;i<32;i++)
		{   
			lcd_command_write(0x80|i);
			lcd_command_write(X); 		//X地址坐标,自动加1.
			for(j=0;j<2;j++)  			//16*8=128
			{
				for(k=0;k<8;k++)
				{
					lcd_data_write(picture_8[hang][k]);					
				}
				hang++;
			}
				
		}
		X=0x88;	//下半屏   
	}  
	lcd_command_write(0x30);	//基本指令集
}

/**************************************************************************
//程序：void lcd_small_picture_draw(unsigned char x_8,unsigned char y_8,
//							unsigned char lenght_8,unsigned char height_8,
//							const unsigned char *picture_8)
//功能：以指定坐标开始，画图片。使用前需清除GDRAM。
//参数：坐标（x，y），高，长，图片数组指针。
//		注意：坐标范围（0，0）~（128，64）；长度范围0~128；高度范围0~64。
//			  lenght_8应为16的倍数，x坐标应为16的倍数。
***************************************************************************/
void lcd_small_picture_draw(unsigned char x_8,unsigned char y_8,
							unsigned char lenght_8,unsigned char height_8,
							const unsigned char *picture_8)
{
	unsigned char x_start_8=x_8/16,y_start_8=y_8;	//定义开始坐标并赋初值
	unsigned char x_end_8=0,y_end_8=0;				//定义结束坐标
	unsigned char X=x_start_8,Y=y_start_8;			//循环变量
	x_end_8=x_start_8+lenght_8/16;		//计算X结束坐标
	y_end_8=y_start_8+height_8;			//计算Y结束坐标
	if(x_end_8>128) x_end_8=x_start_8;
	if(y_end_8>64) y_end_8=y_start_8;
	lcd_command_write(0x34);	//扩充指令集，绘图显示关
	lcd_command_write(0x36);	//扩充指令集，绘图显示开
	for(Y=y_start_8;Y<y_end_8;Y++)
	{
		if(Y>=32)
		{
			Y-=32;y_start_8-=32;y_end_8-=32;	//循环变量Y、Y起始值与Y结束值同时减掉32
			x_start_8+=8; x_end_8+=8;			//循环变量X、X起始值与X结束值同时加上8
		}
		lcd_command_write(0x80|Y);			//Y坐标
		lcd_command_write(0x80|x_start_8);	//X坐标
		for(X=x_start_8;X<x_end_8;X++)
		{
			lcd_data_write(*picture_8++);	//D15~D8写入RAM
			lcd_data_write(*picture_8++);	//D7~D0写入RAM  
		}
	}
	lcd_command_write(0x30);	//基本指令集
}
/**************************************************************************
//程序：void lcd_point_draw(unsigned char x_8,unsigned char y_8,unsigned char color_8)
//功能：画点
//参数：水平坐标X（范围0~127），垂直坐标Y（范围0~63），
//		颜色color（color=1:显示;color=0:清除;color=2:取反）。
***************************************************************************/
void lcd_point_draw(unsigned char x_8,unsigned char y_8,unsigned char color_8)
{
	unsigned char x_word_8=(x_8/16);	//计算x在16个字中的哪一个
	unsigned char x_bit_8=(x_8&0x0F);	//计算x在一个字中的第几位
	unsigned char y_screen_8=(y_8/32);	//计算y在哪半屏（1为上半屏，0为下半屏）
	unsigned char y_line_8=(y_8&0x1F);	//计算y在0~31行中的哪一行
	unsigned char *GDRAM_high_byte;	//当前显示数据高8位
	unsigned char *GDRAM_low_byte;	//当前显示数据低8位
	if((x_8/8)%2==0)
	{
		GDRAM_high_byte=&lcd_buffer[y_8][x_8/8];
		GDRAM_low_byte=&lcd_buffer[y_8][x_8/8+1];
	}
	else
	{
		GDRAM_high_byte=&lcd_buffer[y_8][x_8/8-1];
		GDRAM_low_byte=&lcd_buffer[y_8][x_8/8];
	}										
	if(x_bit_8<8)	//判断x在高8位,还是在低8位
	{
		if(color_8==1)
		{
			
			*GDRAM_high_byte=(*GDRAM_high_byte|(0x01<<(7-x_bit_8)));	 	//置位GDRAM区中高8位数据中相应的点
		}
		else if(color_8==0)
			*GDRAM_high_byte=(*GDRAM_high_byte&(~(0x01<<(7-x_bit_8))));		//清除GDRAM区中高8位数据中相应的点
			 else if(color_8==2)
					*GDRAM_high_byte=(*GDRAM_high_byte^(0x01<<(7-x_bit_8)));//异或操作，取反一位数据			
	}
	else
	{
		if(color_8==1)
		{
			*GDRAM_low_byte=(*GDRAM_low_byte|(0x01<<(15-x_bit_8)));			//置位GDRAM区中低8位数据中相应的点
		}
		else if(color_8==0)
				*GDRAM_low_byte=(*GDRAM_low_byte&(~(0x01<<(15-x_bit_8)))); 	//清除GDRAM区中低8位数据中相应的点
			 else if(color_8==2)
					*GDRAM_low_byte=(*GDRAM_low_byte^(0x01<<(15-x_bit_8))); //异或操作，取反一位数据
	}
	lcd_command_write(0x34);	//扩充指令集，绘图显示关

	lcd_command_write(0x80+y_line_8);				//设定行地址（y坐标）：垂直坐标
	lcd_command_write(0x80+x_word_8+8*y_screen_8);	//设定列地址（x坐标）：水平坐标
													//通过y_screen_8选定上下屏，即水平地址	
	lcd_data_write(*GDRAM_high_byte);	//写入GDRAM区中高8位数据
	lcd_data_write(*GDRAM_low_byte);	//写入GDRAM区中低8位数据
	lcd_command_write(0x36);	//扩充指令集，绘图显示开	
	lcd_command_write(0x30);	//基本指令集	
}

void lcd_point_draw_buffer(unsigned char x_8,unsigned char y_8,unsigned char color_8)
{
	unsigned char x_word_8=(x_8/16);	//计算x在16个字中的哪一个
	unsigned char x_bit_8=(x_8&0x0F);	//计算x在一个字中的第几位
	unsigned char y_screen_8=(y_8/32);	//计算y在哪半屏（1为上半屏，0为下半屏）
	unsigned char y_line_8=(y_8&0x1F);	//计算y在0~31行中的哪一行
	unsigned char *GDRAM_high_byte;	//当前显示数据高8位
	unsigned char *GDRAM_low_byte;	//当前显示数据低8位
	if((x_8/8)%2==0)
	{
		GDRAM_high_byte=&lcd_buffer[y_8][x_8/8];
		GDRAM_low_byte=&lcd_buffer[y_8][x_8/8+1];
	}
	else
	{
		GDRAM_high_byte=&lcd_buffer[y_8][x_8/8-1];
		GDRAM_low_byte=&lcd_buffer[y_8][x_8/8];
	}										
	if(x_bit_8<8)	//判断x在高8位,还是在低8位
	{
		if(color_8==1)
		{
			
			*GDRAM_high_byte=(*GDRAM_high_byte|(0x01<<(7-x_bit_8)));	 	//置位GDRAM区中高8位数据中相应的点
		}
		else if(color_8==0)
			*GDRAM_high_byte=(*GDRAM_high_byte&(~(0x01<<(7-x_bit_8))));		//清除GDRAM区中高8位数据中相应的点
			 else if(color_8==2)
					*GDRAM_high_byte=(*GDRAM_high_byte^(0x01<<(7-x_bit_8)));//异或操作，取反一位数据			
	}
	else
	{
		if(color_8==1)
		{
			*GDRAM_low_byte=(*GDRAM_low_byte|(0x01<<(15-x_bit_8)));			//置位GDRAM区中低8位数据中相应的点
		}
		else if(color_8==0)
				*GDRAM_low_byte=(*GDRAM_low_byte&(~(0x01<<(15-x_bit_8)))); 	//清除GDRAM区中低8位数据中相应的点
			 else if(color_8==2)
					*GDRAM_low_byte=(*GDRAM_low_byte^(0x01<<(15-x_bit_8))); //异或操作，取反一位数据
	}
	/*lcd_command_write(0x34);	//扩充指令集，绘图显示关

	lcd_command_write(0x80+y_line_8);				//设定行地址（y坐标）：垂直坐标
	lcd_command_write(0x80+x_word_8+8*y_screen_8);	//设定列地址（x坐标）：水平坐标
													//通过y_screen_8选定上下屏，即水平地址	
	lcd_data_write(*GDRAM_high_byte);	//写入GDRAM区中高8位数据
	lcd_data_write(*GDRAM_low_byte);	//写入GDRAM区中低8位数据
	lcd_command_write(0x36);	//扩充指令集，绘图显示开	
	lcd_command_write(0x30);	//基本指令集*/	
}


/**************************************************************************
//程序：
//功能：画直线
//参数：
***************************************************************************/
void lcd_line_draw(unsigned char x0_8,unsigned char y0_8,
				   unsigned char x1_8,unsigned char y1_8,unsigned char color_8)
{
	;
}
/**************************************************************************
//程序：
//功能：画圆
//参数：
***************************************************************************/
void lcd_circle_draw(unsigned char x_8,unsigned char y_8,unsigned char radius_8)
{
	;
}

/**************************************************************************
//程序：
//功能：
//参数：
***************************************************************************/

/**************************************************************************
//程序：
//功能：
//参数：
***************************************************************************/
