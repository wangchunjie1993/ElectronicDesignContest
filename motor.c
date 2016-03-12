#include<avr/io.h>
#include<avr/interrupt.h>
#include"def.h"

//PB4输出CTC,PB5控制电机方向

int motor_CTC_counter;

void motor_init()
{
 TCCR0=0x00;
 TCNT0=0x00;
 OCR0=0x37;
 TCCR0|=(7<<2);
 DDRB|=(1<<5);
}

void speed_modify(uchar speed)
{
 OCR0=speed;
}

void left()
{
 PORTB|=(1<<5);
 DDRB|=(1<<4);
}

void left_count(int counter)
{
 motor_CTC_counter=counter;
 PORTB|=(1<<5);
 TIMSK|=(1<<1);
 DDRB|=(1<<4);
 while(motor_CTC_counter>=0);
 motor_stop();
 TIMSK&=~(1<<1);
}

void right()
{
 PORTB&=~(1<<5);
 DDRB|=(1<<4);
}

void right_count(int counter)
{
 motor_CTC_counter=counter;
 PORTB&=~(1<<5);
 TIMSK|=(1<<1);
 DDRB|=(1<<4);
 while(motor_CTC_counter>=0);
 motor_stop();
 TIMSK&=~(1<<1);
}

void motor_stop()
{
	DDRB&=~(1<<4);
}

void motor_move(int motor_speed)
{
 if(motor_speed>=210)
 motor_speed=210;
 else if(motor_speed<(-210))
 motor_speed=-210;

 if(motor_speed>0)
 {
  speed_modify(255-motor_speed);
  left();
 }
 else if(motor_speed<0)
 {
  speed_modify(255+motor_speed);
  right();
 }
}

SIGNAL(TIMER0_COMP_vect)
{
 motor_CTC_counter--;
}



