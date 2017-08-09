/* ****************************** ���ߣ�������� *****************************************
 * �ļ����� : stc15_spi.H
 * Ӳ��ƽ̨ ���w����̖ FSST15ʵ���
 * ������� ��Keil uVision5.13
 *
 * �汾���� : V1.0
 * �޸����� : 2015-08-29
 * ������̳ �����ӹ���ʦ���أ�http://www.ieebase.net��
 * �Ա����� ��http://fsmcu.taobao.com
 * ����˵�� ��������Ϊ�̲ġ���STC15��Ƭ��ǣ�ֵ���Щ�꡷���廪��ѧ�����磩��������
              Ϊ��Ƶ������ǳ����תSTC15��Ƭ�����������̣�¼��100��--�������޹���
              ��Ƶ���鼮����STC�����ں꾧�Ƽ����ٷ���ѧ�ƻ��͸�У����������ʵ����Ȩ���Ƽ�
 * Copyright (C), 2013-2015, ��ƽ��xymbmcu@163.com��/�廪��ѧ������/STC MCU International Limited
 * ����ѧϰʹ�ã�δ��������ɣ���������������ҵ��;������ؾ���
************************************************************************************** */
#ifndef __STC15_SPI_H__
#define __STC15_SPI_H__
#include    "../config.h"

sbit 	MISO	=P1^2;
sbit 	MOSI	=P1^3;
sbit	SCK	  =P1^1;
sbit	CE	  =P1^5;
sbit	CSN		=P1^4;
sbit	IRQ		=P1^0;

u8 SPI_RW(u8 uchars);
u8 SPI_Read(u8 reg);
u8 SPI_RW_Reg(u8 reg, u8 value);
u8 SPI_Read_Buf(u8 reg, u8 *pBuf, u8 uchars);
u8 SPI_Write_Buf(u8 reg, u8 *pBuf, u8 uchars);
void setSPIsta(u8 uchars);
u8 getSPIsta();
void setSPIRX_DR(u8 value);
bit getSPIRX_DR();
#endif
