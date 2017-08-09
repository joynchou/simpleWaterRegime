/************************************************************
* ��֯���ƣ� (C), 1988-1999, Tech. Co., Ltd.
* �ļ�����: test.cpp
* ����:
* �汾 :
* ����:
* ����: // ģ������
* ��Ҫ�������书�� : // ��Ҫ�������书��
  1. -------
* ��ʷ�޸ļ�¼: // ��ʷ�޸ļ�¼
* <����> <ʱ��> <�汾 > <����>
* David 96/10/12 1.0 build this moudle
***********************************************************/
//------------------------------------------------
//ͷ�ļ�
#include "stc15_spi.h"
#include "../DELAY/DELAY.H"

static u8 	bdata sta;   //״̬��־
sbit	RX_DR	=sta^6;
sbit	TX_DS	=sta^5;
sbit	MAX_RT	=sta^4;

/****************************************************************************************************
/*������uint SPI_RW(uint uchar)
/*���ܣ�NRF24L01��SPIдʱ��
/****************************************************************************************************/
u8 SPI_RW(u8 uchars)
{
	u8 bit_ctr;
  for(bit_ctr=0;bit_ctr<8;bit_ctr++) // output 8-bit
 	{
		MOSI = (uchars & 0x80);         // output 'uchar', MSB to MOSI
		uchars = (uchars << 1);           // shift next bit into MSB..
		SCK = 1;                      // Set SCK high..
		uchars |= MISO;       		  // capture current MISO bit
		SCK = 0;            		  // ..then set SCK low again 
	}
  return(uchars);           		  // return read uchar
}
/****************************************************************************************************
/*������uchar SPI_Read(uchar reg)
/*���ܣ�NRF24L01��SPIʱ��
/****************************************************************************************************/
u8 SPI_Read(u8 reg)
{
	u8 reg_val;
	
	CSN = 0;                // CSN low, initialize SPI communication...
	SPI_RW(reg);            // Select register to read from..
	reg_val = SPI_RW(0);    // ..then read registervalue
	CSN = 1;                // CSN high, terminate SPI communication
	
	return(reg_val);        // return register value
}
/****************************************************************************************************/
/*���ܣ�NRF24L01��д�Ĵ�������
/****************************************************************************************************/
u8 SPI_RW_Reg(u8 reg, u8 value)
{
	u8 status;
	
	CSN = 0;                   // CSN low, init SPI transaction
	status = SPI_RW(reg);      // select register
	SPI_RW(value);             // ..and write value to it..
	CSN = 1;                   // CSN high again
	
	return(status);            // return nRF24L01 status uchar
}
/****************************************************************************************************/
/*������uint SPI_Read_Buf(uchar reg, uchar *pBuf, uchar uchars)
/*����: ���ڶ����ݣ�reg��Ϊ�Ĵ�����ַ��pBuf��Ϊ���������ݵ�ַ��uchars���������ݵĸ���
/****************************************************************************************************/
u8 SPI_Read_Buf(u8 reg, u8 *pBuf, u8 uchars)
{
	u8 status,uchar_ctr;
	
	CSN = 0;                    		// Set CSN low, init SPI tranaction
	status = SPI_RW(reg);       		// Select register to write to and read status uchar
	
	for(uchar_ctr=0;uchar_ctr<uchars;uchar_ctr++)
		pBuf[uchar_ctr] = SPI_RW(0);    // 
	
	CSN = 1;                           
	
	return(status);                    // return nRF24L01 status uchar
}
/*********************************************************************************************************
/*������uint SPI_Write_Buf(uchar reg, uchar *pBuf, uchar uchars)
/*����: ����д���ݣ�Ϊ�Ĵ�����ַ��pBuf��Ϊ��д�����ݵ�ַ��uchars��д�����ݵĸ���
/*********************************************************************************************************/
u8 SPI_Write_Buf(u8 reg, u8 *pBuf, u8 uchars)
{
	u8 status,uchar_ctr;
	
	CSN = 0;            //SPIʹ��       
	status = SPI_RW(reg);
	delay_us(10);	
	for(uchar_ctr=0; uchar_ctr<uchars; uchar_ctr++) //
		SPI_RW(*pBuf++);
	CSN = 1;           //�ر�SPI
	return(status);    // 
}

void setSPIsta(u8 uchars)
{
	sta = uchars;
}

u8 getSPIsta()
{
	return sta;
}

void setSPIRX_DR(u8 value)
{
	RX_DR = value;
}

bit getSPIRX_DR()
{
	return RX_DR;
}