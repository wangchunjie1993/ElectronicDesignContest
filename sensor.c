#include<avr/io.h>
#include<util/delay.h>
#include"def.h"
#include"usart.h"

float_data roll,pitch,yaw;								  //�����ǲ�õĽǶ�
extern int receive_count;
extern float ERROR;
/************************
* ��������ʼ��
************************/
void sensor_init()
{
 usart0_puts("#o0");		//��ֹ�����
 _delay_ms(5);
 usart0_puts("#oc");		//���봫����У��ģʽ
 _delay_ms(5);
 usart0_puts("#on");		//У������������
 _delay_ms(5);
 usart0_puts("#on");
 _delay_ms(5);
 usart0_puts("#on");
 _delay_ms(5);
 usart0_puts("#ob");
 _delay_ms(5);
}

/************************
* ��ȡ��ǰ����������ٶȴ������������
************************/
void read_sensor()
{
 _delay_ms(10);
 receive_count=0;
 usart0_puts("#o1");			//ʹ�������
 while(receive_count<12);
 usart0_puts("#o0");			//��ֹ�����
 yaw.data_use-=ERROR;

}
