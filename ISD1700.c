#include<avr/io.h>
#include<util/delay.h>
#include"def.h"
#include"ISD1700.h"

#define SS_0 PORTC&=~(1<<0)
#define SS_1 PORTC|=(1<<0)
#define SCLK_0 PORTC&=~(1<<1)
#define SCLK_1 PORTC|=(1<<1)
#define MOSI_0 PORTC&=~(1<<2)
#define MOSI_1 PORTC|=(1<<2)
#define MISO_0 PORTC&=~(1<<3)
#define MISO_1 PORTC|=(1<<3)

#define SS 0
#define SCLK 1
#define MOSI 2
#define MISO 3

uchar SR0_L,SR0_H,SR1,ID,APCL=0,APCH=0;
uint caToneAdd[10]={0x0010,0x001c,0x001d,0x002d,0x002e,0x0035,0x0036,0x0039,0x0040,0x004d};

void simulate_SPI_init()
{
 DDRC|=(1<<SS)|(1<<SCLK)|(1<<MOSI);
 DDRC&=~(1<<MISO);
}

uchar SPI_master_transmit(uchar dat)
{
 uchar i;
 SCLK_1;
 SS_0;
 for(i=0;i<8;i++)
 {
  SCLK_0;
  _delay_ms(1);
  if(dat&0x01)
  {
   MOSI_1;
  }
  else
  {
   MOSI_0;
  }
  dat>>=1;
  if(MISO)
  {
   dat|=0x80;
  }
  SCLK_1;
  _delay_ms(1);
 }
 MOSI_0;
 return dat;

}

void ISD_PU()			//上电
{
 SS_0;
 SPI_master_transmit(ISD1700_PU);
 SPI_master_transmit(0x00);
 SS_1; 
 _delay_ms(50);

}

void ISP_PD()			//下电
{
 SS_0;
 SPI_master_transmit(ISD1700_PD);
 SPI_master_transmit(0x00);
 SS_1; 
 _delay_ms(50);

}

void ISP_STOP()			//停止当前操作
{
 SS_0;
 SPI_master_transmit(ISD1700_STOP);
 SPI_master_transmit(0x00);
 SS_1; 
 _delay_ms(50);

}

void RdStatus()		//读取状态
{
 SS_0;
 SPI_master_transmit(ISD1700_RD_STAUS);
 SPI_master_transmit(0x00);
 SPI_master_transmit(0x00);
 SS_1;
 _delay_ms(50);
 SR0_L=SPI_master_transmit(ISD1700_RD_STAUS);
 SR0_H=SPI_master_transmit(0x00);
 SR1=SPI_master_transmit(0x00);
 SS_1;
 _delay_ms(50);

}

void ClrInt()		//清除中断
{
 SS_0;
 SPI_master_transmit(ISD1700_CLR_INT);
 SPI_master_transmit(0x00);
 SS_1; 
 _delay_ms(50);

}

void ISD_WR_NVCFG()			//永久写入寄存器
{
 SS_0;
 SPI_master_transmit(ISD1700_WR_NVCFG);
 SPI_master_transmit(0x00);
 SS_1; 
 _delay_ms(50);

}
	
void ISD_WR_APC2()			//设置APC2
{
 SS_0;
 SPI_master_transmit(ISD1700_WR_APC2);
 SPI_master_transmit(0xa8);
 SPI_master_transmit(0x0c);
 SS_1; 
 _delay_ms(50);
 ISD_WR_NVCFG();

}

void Rd_APC()	//读取APC
{
 SS_0;
 SPI_master_transmit(ISD1700_RD_APC);
 SPI_master_transmit(0x00);
 SPI_master_transmit(0x00);
 SPI_master_transmit(0x00);
 SS_1; 
 _delay_ms(50);
 SR0_L=SPI_master_transmit(ISD1700_RD_APC);
 SR0_H=SPI_master_transmit(0x00);
 APCL=SPI_master_transmit(0x00);
 APCH=SPI_master_transmit(0x00);
 SS_1;
 _delay_ms(50);
 
}

void ISD_Init()			//初始化
{
 //SPI_master_init(); 
 simulate_SPI_init();
 ISD_Reset();
 ISD_Reset();
 ISD_Reset();
 /*do
 {
  ISD_PU();
  _delay_ms(10);
  RdStatus();
  _delay_ms(10);
 }while(((SR0_L&0x01)!=0)||((SR1&0x01)==0));*/
 ISD_PU();
 ISD_PU();
 ISD_PU();
 ClrInt();
 ISD_WR_APC2();
 Rd_APC();
}

void ISD_CHK_MEM()			//空间检查
{
 SS_0;
 SPI_master_transmit(ISD1700_CHK_MEM);
 SPI_master_transmit(0x00);
  SS_1;
 _delay_ms(50);

}

void ISD_Reset()			//复位
{
 SS_0;
 SPI_master_transmit(ISD1700_REST);
 SPI_master_transmit(0x00);
 SS_1;
 _delay_ms(50);
 
}

void RD_DevID()		//读取ID
{
 SS_0;
 SPI_master_transmit(ISD1700_DEVID);
 SPI_master_transmit(0x00);
 SPI_master_transmit(0x00);
 SS_1; 
 _delay_ms(50);
 SR0_L=SPI_master_transmit(ISD1700_DEVID);
 SR0_H=SPI_master_transmit(0x00);
 ID=SPI_master_transmit(0x00);
  SS_1;
 _delay_ms(50);

 return ID;
}


//取出当前语音的首末地址
void GetToneAdd(uchar cNum,uint * ipStartAdd,uint * ipEndAdd)
{
 *ipStartAdd=caToneAdd[cNum*2];
 *ipEndAdd=caToneAdd[cNum*2+1];
}

void SetPlay(uchar cNum)		//定点播放
{
 uint Add_ST,Add_ED;
 uchar Add_ST_H,Add_ST_L,Add_ED_H,Add_ED_L;
 /*do
 {
  RdStatus();
 }while(((SR0_L&0x01)!=0)||((SR1&0x01)==0));*/

 _delay_ms(50);
 ClrInt();
 GetToneAdd(cNum,&Add_ST,&Add_ED);

 Add_ST_L=(uchar)(Add_ST&0x00ff);
 Add_ST_H=(uchar)((Add_ST>>8)&0x00ff);
 Add_ED_L=(uchar)(Add_ED&0x00ff);
 Add_ED_H=(uchar)((Add_ED>>8)&0x00ff);
 
 SS_0;
 SPI_master_transmit(ISD1700_SET_PLAY);
 SPI_master_transmit(0x00);
 SPI_master_transmit(Add_ST_L);
 SPI_master_transmit(Add_ST_H);
 SPI_master_transmit(Add_ED_L);
 SPI_master_transmit(Add_ED_H);
 SPI_master_transmit(0x00);
 SS_1;
 _delay_ms(100);
 
 do
 {
  RdStatus();
 }while(((SR0_L&0x01)!=0)||((SR1&0x04)!=0));

}

void SetREC(uchar cNum)		//定点录音
{
 uint Add_ST,Add_ED;
 uchar Add_ST_H,Add_ST_L,Add_ED_H,Add_ED_L;
 /*do
 {
  RdStatus();
 }while(((SR0_L&0x01)!=0)||((SR1&0x01)==0));*/
 _delay_ms(50);
 ClrInt();
 GetToneAdd(cNum,&Add_ST,&Add_ED);

 Add_ST_L=(uchar)(Add_ST&0x00ff);
 Add_ST_H=(uchar)((Add_ST>>8)&0x00ff);
 Add_ED_L=(uchar)(Add_ED&0x00ff);
 Add_ED_H=(uchar)((Add_ED>>8)&0x00ff);

 SS_0;
 SPI_master_transmit(ISD1700_SET_REC);
 SPI_master_transmit(0x00);
 SPI_master_transmit(Add_ST_L);
 SPI_master_transmit(Add_ST_H);
 SPI_master_transmit(Add_ED_L);
 SPI_master_transmit(Add_ED_H);
 SPI_master_transmit(0x00);
 SS_1; 
 _delay_ms(50);

 do
 {
  RdStatus();
 }while(((SR0_L&0x01)!=0)||((SR1&0x08)==0));
}

void Erase_All()		//全部删除
{
 SS_0;
 SPI_master_transmit(ISD1700_G_ERASE);
 SPI_master_transmit(0x00);
 SS_1; 
 _delay_ms(50);

}
