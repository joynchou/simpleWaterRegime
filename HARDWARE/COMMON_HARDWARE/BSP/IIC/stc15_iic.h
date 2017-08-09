/************************************************************
* �ļ�����: ���Ӵ���������\HARDWARE\COMMON_HARDWARE\BSP\IIC\STC15_IIC.H
* ����:     stc�ٷ�
* �汾:     v1.0
* ����:     2017/08/03
* ����:		���ģ���iic����
* ��ʷ�޸ļ�¼:
* <����> <ʱ��> <�汾 > <����>
* �ܳ��� 8/3    1.0     �޸���iic����
***********************************************************/

#ifndef __STC15_IIC_H__
#define __STC15_IIC_H__
#include    "../config.h"
sbit SCL = P3 ^ 4;
sbit SDA = P3 ^ 5;
/* ***************************************************** */
#define IIC_WRITE 0x00
#define IIC_READ  0x01
//typedef enum{FALSE,TRUE} BOOL;
#define BOOL bit
extern void Delay5US(void);
extern void IIC_Start(void);
extern void IIC_Stop(void);
extern void IIC_Ack(void);
extern BOOL IIC_RdAck(void);
extern void IIC_Nack(void);
extern u8 OutputOneByte(void);
extern void InputOneByte(u8 uByteVal);
extern BOOL IIC_WrDevAddAndDatAdd(u8 uDevAdd, u8 uDatAdd);
extern void IIC_WrDatToAdd(u8 uDevID, u8 uStaAddVal, u8 *p, u8 ucLenVal);
extern void IIC_RdDatFromAdd(u8 uDevID, u8 uStaAddVal, u8 *p, u8 uiLenVal);
#endif
