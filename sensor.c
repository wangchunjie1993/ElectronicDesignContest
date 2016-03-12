#include<avr/io.h>
#include<util/delay.h>
#include"def.h"
#include"usart.h"

float_data roll,pitch,yaw;								  //陀螺仪测得的角度
extern int receive_count;
extern float ERROR;
/************************
* 传感器初始化
************************/
void sensor_init()
{
 usart0_puts("#o0");		//禁止流输出
 _delay_ms(5);
 usart0_puts("#oc");		//进入传感器校正模式
 _delay_ms(5);
 usart0_puts("#on");		//校正各个传感器
 _delay_ms(5);
 usart0_puts("#on");
 _delay_ms(5);
 usart0_puts("#on");
 _delay_ms(5);
 usart0_puts("#ob");
 _delay_ms(5);
}

/************************
* 读取当前陀螺仪与加速度传感器测得数据
************************/
void read_sensor()
{
 _delay_ms(10);
 receive_count=0;
 usart0_puts("#o1");			//使能流输出
 while(receive_count<12);
 usart0_puts("#o0");			//禁止流输出
 yaw.data_use-=ERROR;

}
