#include "NRF24L01.H"

u8 const TX_ADDRESS[TX_ADR_WIDTH] = {0x34,0x43,0x10,0x10,0x01};	//本地地址
u8 const RX_ADDRESS[RX_ADR_WIDTH] = {0x34,0x43,0x10,0x10,0x01};	//接收地址

void NRF24L01_TX_Init(void)
{
 	CE=0;    // chip enable
 	CSN=1;   // Spi  disable 
 	SCK=0;   // 
	SPI_Write_Buf(WRITE_REG + TX_ADDR, TX_ADDRESS, TX_ADR_WIDTH);    // 写本地地址	
	SPI_Write_Buf(WRITE_REG + RX_ADDR_P0, RX_ADDRESS, RX_ADR_WIDTH); // 写接收端地址
	SPI_RW_Reg(WRITE_REG + EN_AA, 0x01);      //  频道0自动	ACK应答允许	
	SPI_RW_Reg(WRITE_REG + EN_RXADDR, 0x01);  //  允许接收地址只有频道0，如果需要多频道可以参考Page21
	SPI_RW_Reg(WRITE_REG + SETUP_RETR,0x1a);//设置重发次  
	SPI_RW_Reg(WRITE_REG + RF_CH, 0x6e);	//   设置信道工作为2.4GHZ，收发必须一致数
	SPI_RW_Reg(WRITE_REG + RX_PW_P0, RX_PLOAD_WIDTH); //设置接收数据长度，本次设置为32字节
	SPI_RW_Reg(WRITE_REG + RF_SETUP, 0x27);   		//设置发射速率为1MB/S，发射功率为最大值+7dB，由于有X2401L功放，实际+21dbm输出
  SPI_RW_Reg(WRITE_REG + CONFIG, 0x5e); 
}

void NRF24L01_RX_Init(void)
{
  delay_us(100);
 	CE=0;    // chip enable
 	CSN=1;   // Spi  disable 
 	SCK=0;   // 
	SPI_Write_Buf(WRITE_REG + TX_ADDR, TX_ADDRESS, TX_ADR_WIDTH);    // 写本地地址	
	SPI_Write_Buf(WRITE_REG + RX_ADDR_P0, RX_ADDRESS, RX_ADR_WIDTH); // 写接收端地址
	SPI_RW_Reg(WRITE_REG + EN_AA, 0x01);      //  频道0自动	ACK应答允许	
	SPI_RW_Reg(WRITE_REG + EN_RXADDR, 0x01);  //  允许接收地址只有频道0，如果需要多频道可以参考Page21  
	SPI_RW_Reg(WRITE_REG + RF_CH, 0x6e);        //   设置信道工作为2.4GHZ，收发必须一致
	SPI_RW_Reg(WRITE_REG + RX_PW_P0, RX_PLOAD_WIDTH); //设置接收数据长度，本次设置为32字节
	SPI_RW_Reg(WRITE_REG + RF_SETUP, 0x27);   		//设置发射速率为1MB/S，发射功率为最大值+7dB，由于有X2401L功放，实际+21dbm输出 
	SetRX_Mode();
}
/****************************************************************************************************/
/*函数：void SetRX_Mode(void)
/*功能：数据接收配置 
/****************************************************************************************************/
void SetRX_Mode(void)
{
	CE=0;
	SPI_RW_Reg(WRITE_REG + CONFIG, 0x5f);   		// IRQ收发完成中断响应，16位CRC	，主接收
	CE = 1; 
	delay_us(1560);    //目的是为了让无线模块有足够的时间接收到数据
}

/******************************************************************************************************/
/*函数：unsigned char nRF24L01_RxPacket(unsigned char* rx_buf)
/*功能：数据读取后放如rx_buf接收缓冲区中
/******************************************************************************************************/
unsigned char nRF24L01_RxPacket(unsigned char* rx_buf)
{
	setSPIsta(SPI_Read(STATUS));	
	if(getSPIRX_DR())				
	{
	  CE = 0; 		
		SPI_Read_Buf(RD_RX_PLOAD,rx_buf,TX_PLOAD_WIDTH);	
	}
	SPI_RW_Reg(WRITE_REG+STATUS,getSPIsta());   //接收到数据后RX_DR,TX_DS,MAX_PT都置高为1，通过写1来清楚中断标志
	CE=1;
}

/***********************************************************************************************************
/*函数：void nRF24L01_TxPacket(unsigned char * tx_buf)
/*功能：发送 tx_buf中数据
/**********************************************************************************************************/
void nRF24L01_TxPacket(unsigned char * tx_buf)
{
	SPI_RW_Reg(WRITE_REG+STATUS,0xff);
	SPI_RW_Reg(0xE1,0xff);
	CE=0;		
	SPI_Write_Buf(WR_TX_PLOAD, tx_buf, TX_PLOAD_WIDTH); 			       	
	CE=1;		 
	delay_us(10);   //CE高电平大于10us才能进入发射模式
}