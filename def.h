#ifndef __DEF_H__
#define __DEF_H__

#define uchar unsigned char
#define uint unsigned int 

#define HIGH_SPEED	0x20
#define LOW_SPEED	0x40

#define ANGLE_ERROR (-2.0)
#define ANGLE_HIGH	177
//#define ERROR	(0.5)
#define KEY (PINA&(1<<0))

typedef union
{
	uchar data_trans[4];		//���������ֽڴ���
	float data_use;				//ֱ��ʹ�õ�����
}float_data;

#endif
