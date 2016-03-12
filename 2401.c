#include"2401.h"
#include"SPI.h"



unsigned char TxData[TRAN_DATA_NUM]={};	//要发送的数据
unsigned char RxData[TRAN_DATA_NUM]={};	//要接收的数据
unsigned char TxAdd[TxAddNum]={0XE7,0XE7,0XE7,0XE7,0XE7};

///*********************
//2401初始化
///*********************
void RF2401_Init(void)
{
    SPI_Init();
	DDR_SPI|=((1<<MOSI)|(1<<SCK)|(1<<CSN));	//设置MOSI、SCK、CSN输出，其余输入
	DDRF|=(1<<CE);
	DDR_SPI&=~(1<<MISO);//|(1<<IRQ));	
	DDRF &= ~(1<<IRQ);
	PORTF |=(1<<IRQ);
	PORT_SPI|=(1<<CSN);
}

void set_tx_mode()
{
    Sleep1_Mode();

	PORT_SPI&=~(1<<CSN);
	SpiRW(1|W_REGSITER);	//写 寄存器1
	SpiRW(0x0);				//禁止自动应答  
	PORT_SPI|=(1<<CSN);

	PORT_SPI&=~(1<<CSN);   
	SpiRW(0x31);			
	SpiRW(0X20);			//通道0有效数据宽度32
	PORT_SPI|=(1<<CSN);
	_delay_ms(1);
    Tx_Mode();
}

void send_data()
{
 //unsigned char i;
 //for(i=0;i<32;i++)			//发送接收到的数据
  //TxData[i]=i;//RxData[i];
 W_Send_Data(32);
 Tx_Mode();
}

void set_rx_mode()
{
 Sleep1_Mode();

 PORT_SPI&=~(1<<CSN);
 SpiRW(1|W_REGSITER);	//写 寄存器1
 SpiRW(0x0);				//禁止自动应答
 PORT_SPI|=(1<<CSN);

 PORTB&=~(1<<CSN);   
 SpiRW(0x31);			
 SpiRW(0X20);			//通道0有效数据宽度32
 PORTB|=(1<<CSN);
 _delay_ms(1);
 Rx_Mode();//接收模式
}

void receive_data()
{
 unsigned char irq_sta;
 while((PINF&(1<<IRQ)));

 do
 {  
  irq_sta=Read_IRQ();
 }while(!(irq_sta&(1<<RX_DR)));

 Clr_IRQ(1<<RX_DR);
 Read_Rx(32);
 _delay_ms(1);

}

///*********************
//发送模式
///*********************
void Tx_Mode(void)
{
	PORTF&=~(1<<CE);
	PORT_SPI&=~(1<<CSN);
	SpiRW(0|W_REGSITER);			//写寄存器 0
	SpiRW(0x12);		//使能所有中断，crc使能，8位crc，上电，发送模式
	PORT_SPI|=(1<<CSN);
	PORTF|=(1<<CE);
	_delay_ms(1);
}
///*********************
//接收模式
///*********************
void Rx_Mode(void)
{
	PORTF|=(1<<CE);
	PORT_SPI&=~(1<<CSN);
	SpiRW(0|W_REGSITER);			//写寄存器 0
	SpiRW(0x13);		//使能所有中断，crc使能，8位crc，上电，	接收模式
	PORT_SPI|=(1<<CSN);
	_delay_ms(2);
}
///*********************
//待机1模式
///*********************
void Sleep1_Mode(void)
{
	PORTF&=~(1<<CE);
}
///*********************
//写 要发送的有效数据
///*********************
void W_Send_Data(unsigned char send_data_num)
{
	PORT_SPI&=~(1<<CSN);
	SpiRW(FLUSH_TX);	//清除TX fifo寄存器
	PORT_SPI|=(1<<CSN);
	PORT_SPI&=~(1<<CSN);
	SpiRW(W_TX_PAYLOAD);//写命令
	unsigned char i;
	for(i=0;i<send_data_num;i++)
	{
		SpiRW(TxData[i]);
	}
	PORT_SPI|=(1<<CSN);
}
///*********************
//读 接收到的有效数据
///*********************
void Read_Rx(unsigned char rece_data_num)//输入要读取的数据数目
{
	PORT_SPI&=~(1<<CSN);
	SpiRW(R_RX_PAYLOAD);//读命令	RX FIFO
	unsigned char i;
	for(i=0;i<rece_data_num;i++)
	{
		RxData[i]=SpiRW(NOP);
	}
	PORT_SPI|=(1<<CSN);

	PORT_SPI&=~(1<<CSN);
	SpiRW(FLUSH_RX);	//清除RX 	fifo寄存器
	PORT_SPI|=(1<<CSN);
}
///*********************
//读 中断标志
///*********************
unsigned char Read_IRQ(void)
{
	PORT_SPI&=~(1<<CSN);
	unsigned char sta;
	sta=SpiRW(0X07);					//读状态寄存器	用NOP命令也可将状态读出
	PORT_SPI|=(1<<CSN);
	return sta;
}
///*********************
//清除标志位
///*********************
void Clr_IRQ(unsigned char note)	//示例：Cle_IRQ(((1<<tx_dr)|(1<<max_rt)))
{
	PORT_SPI&=~(1<<CSN);
	SpiRW(0X07|W_REGSITER);		//写状态寄存器
	SpiRW(note);
	PORT_SPI|=(1<<CSN);
}
