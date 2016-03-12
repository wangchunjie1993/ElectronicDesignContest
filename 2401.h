#ifndef _2401_H_
#define _2401_H_
#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>
///***************************
///***************************
//2401，基本函数 
///***************************
//基本命令定义
#define R_REGSITER	  0X00	//读寄存器	直接与地址按位或
#define W_REGSITER	  0X20	//写寄存器	直接与地址按位或,只能在掉电模式或待机模式下操作
#define R_RX_PAYLOAD  0X61	//读数据 1-32 字节  从0字节开始，用于接收模式下
#define W_TX_PAYLOAD  0XA0	//写数据 1-32 字节  从0字节开始，用于发射模式下
#define FLUSH_TX	  0xe1	//清除TX FIFO 寄存器，用于接收模式下
#define FLUSH_RX      0XE2	//清除RX FIFO 寄存器，用于发射模式下， 传输应答信号时，不应使用此命令
#define RESUSE_TX_PL  0XE3	//应用于发射端，重新使用上一包有效数据，当CE为高时，数据包不断重新发射
#define NOP			  0XFF	//空指令 用于取回数据

//状态寄存器中标志位
#define RX_DR	6	//接收中断
#define	TX_DS	5	//发送完毕中断
#define MAX_RT	4	//最大重发中断

#define RECE_DATA_NUM	32	//接收数据最大量
#define TRAN_DATA_NUM	32	//接收数据最大量
#define TxAddNum		5	//发送地址宽度
#define RxAddNum		5	//发送地址宽度

/*******24L01初始化*********/
void RF2401_Init(void);
/*******发送模式**********/
void Tx_Mode(void);
/*******接收模式**********/
void Rx_Mode(void);
/*******待机模式一********/
void Sleep1_Mode(void);
/*******写 要发送的有效数据**********/
void W_Send_Data(unsigned char send_data_num);//输入要读取的数据数目
/*******读 接收到的有效数据**********/
void Read_Rx(unsigned char rece_data_num);//输入要读取的数据数目
/*******读 中断标志********/
unsigned char Read_IRQ(void);
/*******清除标志位**********/
void Clr_IRQ(unsigned char note);

#endif
