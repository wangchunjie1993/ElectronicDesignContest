#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>
#include"def.h"
#include"motor.h"
#include"usart.h"
#include"2401.h"
#include"sensor.h"
#include"pid.h"
#include"SPI.h"


int motor_step1=0,motor_step2=0;		//�������������
int motor_speed1=0,motor_speed2=0;		//������������ٶ�
uchar direct_flag=0;		//�ڸ�ת���־��0->˳ʱ�룬1->��ʱ��
unsigned char irq_sta;
float angle_prev=0,angle_curr=0;		
uchar mod=0;
extern unsigned char RxData[TRAN_DATA_NUM];	//Ҫ���͵�����
extern float_data roll,pitch,yaw;
extern int motor_CTC_counter;
float ERROR=0;

int main()
{
 port_init();
 motor_init();
 RF2401_Init();
 usart0_init(16);
 //usart1_init(16);
 sensor_init();
 UCSR0B|=(1<<4)|(1<<7);				//ʹ�ܴ��ڽ����ж�
 SREG=0x80;
 Clr_IRQ(1<<RX_DR);
 /*do
 {
  read_sensor();
  ERROR=yaw.data_use;
 }while(KEY!=0);*/

 while(1)
 {
  set_rx_mode();
  receive_data();
  mod=RxData[0];
  _delay_ms(300);

  switch(mod)
  {
   case 0:
   {
    mod0();
    break;
   }
   case 1:
   {
    mod1();
    break;
   }
   case 2:
   {
    mod2();
    break;
   }
   case 3:
   {
    mod3();
    break;
   }
   case 4:
   {
    mod4();
    break;
   }
   case 5:
   {
    mod5();
    break;
   }
   case 6:
   {
    release();
	break;
   }
   default:
   break;
  }
 }

}

void abs(float *data)
{
 if((*data)<0)
 (*data)=-(*data);
}

void port_init()
{
 DDRA&=~(1<<0);			//������ʼ��
 PORTA|=(1<<0); 

}

void get_direction()
{
  read_sensor();
  angle_prev=yaw.data_use;
  _delay_ms(30);
  read_sensor();
  angle_curr=yaw.data_use;
  if(angle_curr>angle_prev)
  {
   direct_flag=0;		//˳ʱ��
  }
  else 
  {
   direct_flag=1;		//��ʱ��
  }
  if(angle_curr-angle_prev<(-280))
  {
   direct_flag=0;		//˳ʱ��
  }
  else if(angle_curr-angle_prev>280)
  {
   direct_flag=1;		//��ʱ��
  }
}

void spin()
{
  get_direction();
  if(direct_flag==0)
  {
   do
   {
    read_sensor();
   }while(((yaw.data_use>(-180))&&(yaw.data_use<(-40)))||((yaw.data_use>0)&&(yaw.data_use<125)));

   if((yaw.data_use<180)&&(yaw.data_use>125))
   {
	//speed_modify(LOW_SPEED);
    //left_count(570);
	uchar speed=LOW_SPEED;
    speed_modify(LOW_SPEED);
	left();
	for(uchar i=0;i<5;i++)
	{
	 speed-=6;
	 speed_modify(speed);
	 _delay_ms(13);
	}
	motor_stop();
   }
   else if((yaw.data_use>(-40))&&(yaw.data_use<0))
   {
    speed_modify(HIGH_SPEED);
    left_count(400);
   }
  }
  else
  {
   do
   {
    read_sensor();
   }while(((yaw.data_use<0)&&(yaw.data_use>(-125)))||((yaw.data_use>40)&&(yaw.data_use<180)));

   if((yaw.data_use>(-180))&&(yaw.data_use<(-125)))
   {
    //speed_modify(LOW_SPEED);
    //right_count(570);
    uchar speed=LOW_SPEED;
    speed_modify(LOW_SPEED);
	right();
	for(uchar i=0;i<5;i++)
	{
	 speed-=6;
	 speed_modify(speed);
	 _delay_ms(13);
	}
	motor_stop();
   }
   else if((yaw.data_use<40)&&(yaw.data_use>0))
   {
    speed_modify(HIGH_SPEED);
    right_count(400);
   }
  }
}

void go_up()
{
 get_direction();
  if(direct_flag==0)
  {
   do
   {
    read_sensor();
   }while(((yaw.data_use>(-180))&&(yaw.data_use<(-40)))||((yaw.data_use>0)&&(yaw.data_use<125)));

   if((yaw.data_use<180)&&(yaw.data_use>125))
   {
	//speed_modify(LOW_SPEED);
    //left_count(570);
	uchar speed=LOW_SPEED;
    speed_modify(LOW_SPEED);
	left();
	for(uchar i=0;i<5;i++)
	{
	 speed-=6;
	 speed_modify(speed);
	 _delay_ms(13);
	}
	motor_stop();
   }
   /*else if((yaw.data_use>(-40))&&(yaw.data_use<0))
   {
    speed_modify(HIGH_SPEED);
    left_count(400);
   }*/
  }
  else
  {
   do
   {
    read_sensor();
   }while(((yaw.data_use<0)&&(yaw.data_use>(-125)))||((yaw.data_use>40)&&(yaw.data_use<180)));

   if((yaw.data_use>(-180))&&(yaw.data_use<(-125)))
   {
    //speed_modify(LOW_SPEED);
    //right_count(570);
    uchar speed=LOW_SPEED;
    speed_modify(LOW_SPEED);
	right();
	for(uchar i=0;i<5;i++)
	{
	 speed-=6;
	 speed_modify(speed);
	 _delay_ms(13);
	}
	motor_stop();
   }
   /*else if((yaw.data_use<40)&&(yaw.data_use>0))
   {
    speed_modify(HIGH_SPEED);
    right_count(400);
   }*/
  }
}


void mod0()			//�ڽǳ���60��
{
 left_count(900);
 _delay_ms(100);
 while((PINF&(1<<IRQ)))
 {
  go_up();
 }

 do
 {  
  irq_sta=Read_IRQ();
 }while(!(irq_sta&(1<<RX_DR)));

 Clr_IRQ(1<<RX_DR);
 Read_Rx(32);
 _delay_ms(1);

}

void mod1()			//���Բ���˶�
{
 while((PINF&(1<<IRQ)))
 {
  spin();
 }

 do
 {  
  irq_sta=Read_IRQ();
 }while(!(irq_sta&(1<<RX_DR)));

 Clr_IRQ(1<<RX_DR);
 Read_Rx(32);
 _delay_ms(1);

}

void mod2()			//��165�ȵ���ֱ
{
 do
 {
  read_sensor();
 }
 while(KEY!=0);
 speed_modify(LOW_SPEED);
 if(yaw.data_use>0)
 {
  right_count(yaw.data_use*5);
 }
 else 
 {
  left_count((-yaw.data_use)*5);
 }
 //left_count(600);
 while((PINF&(1<<IRQ)))
 {
  //_delay_ms(30);
  
  read_sensor();
  while((yaw.data_use>25)||(yaw.data_use<(-25)))
  {
   go_up();
   read_sensor();
  }
   
  
   
   while(((yaw.data_use<(-2))&&(yaw.data_use>(-25)))||((yaw.data_use<(25))&&(yaw.data_use>(2))))
   {
    speed_modify(0x40);
    if(yaw.data_use>0)
    {
     right_count((int)((yaw.data_use)*2));
    }
    else
    {
     left_count((int)(-yaw.data_use)*2);
    }
	//_delay_ms(10);
	read_sensor();
   }
  
 }

 do
 {  
  irq_sta=Read_IRQ();
 }while(!(irq_sta&(1<<RX_DR)));

 Clr_IRQ(1<<RX_DR);
 Read_Rx(32);
 _delay_ms(1);

}


void mod3()			//���´�����ֱ
{
 speed_modify(HIGH_SPEED);
 left_count(900);
 while((PINF&(1<<IRQ)))
 {
  //_delay_ms(30);
  
  read_sensor();
  while((yaw.data_use>25)||(yaw.data_use<(-25)))
  {
   go_up();
   read_sensor();
  }
   
  
   
   while(((yaw.data_use<(-2))&&(yaw.data_use>(-25)))||((yaw.data_use<(25))&&(yaw.data_use>(2))))
   {
    speed_modify(0x40);
    if(yaw.data_use>0)
    {
     right_count((int)((yaw.data_use)*2));
    }
    else
    {
     left_count((int)(-yaw.data_use)*2);
    }
	//_delay_ms(10);
	read_sensor();
   }
  
 }

 do
 {  
  irq_sta=Read_IRQ();
 }while(!(irq_sta&(1<<RX_DR)));

 Clr_IRQ(1<<RX_DR);
 Read_Rx(32);
 _delay_ms(1);


}

void mod4()			//��ֱʱʩ������
{
 while((PINF&(1<<IRQ)))
 {
  
 }

 do
 {  
  irq_sta=Read_IRQ();
 }while(!(irq_sta&(1<<RX_DR)));

 Clr_IRQ(1<<RX_DR);
 Read_Rx(32);
 _delay_ms(1);

}

void mod5()			//��ֱʱ��ת360��
{
 while((PINF&(1<<IRQ)))
 {
  
 }

 do
 {  
  irq_sta=Read_IRQ();
 }while(!(irq_sta&(1<<RX_DR)));

 Clr_IRQ(1<<RX_DR);
 Read_Rx(32);
 _delay_ms(1);

}

void release()			//�ͷŵ���
{
 set_rx_mode();
 receive_data();
 while(RxData[1]!=0)
 {
  speed_modify(0xff);
  if(RxData[1]==1)
  {
   left();
   receive_data();
   motor_stop();
  }
  else if(RxData[1]==2)
  {
   right();
   receive_data();
   motor_stop();
  }
 }
}


