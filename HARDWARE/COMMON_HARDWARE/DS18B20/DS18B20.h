#ifndef __DB18B20_H__
#define __DB18B20_H__

#include "../BSP/BSP.H"

sbit DS18B20_DQ=P2^0; 				//���ݴ����߽ӵ�Ƭ������Ӧ������
void Init_DS18B20();//DS18B20��ʼ��
void ReadTemperature(void);//��ȡDS18B20���ݣ��¶�ɨ��
float getTemperatureValue(void);//��ȡ�¶�
void openTemperatureRead(void);//�����¶�ɨ�迪��
void closeTemperatureRead(void);//�ر��¶�ɨ�迪��
u16 getTemperatureInteger(void);

#endif