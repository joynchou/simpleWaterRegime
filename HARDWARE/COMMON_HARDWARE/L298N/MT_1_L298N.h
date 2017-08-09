/*����ֱ����ˢ����Ŀ��ƣ��˺�����Ҫ����С������*/
#ifndef __MT_1_L298N_H__
#define __MT_1_L298N_H__

#include "../BSP/BSP.H"

/*
MT-1 L298N��������ӷ�ʽ
OUT1 -> Left Motor Positive electrode
OUT2 -> Left Motor Negative electrode
OUT3 -> Right Motor Positive electrode
OUT4 -> Right Motor Negative electrode
*/

sbit IN1=P0^0;
sbit IN2=P0^1;
sbit IN3=P0^2;
sbit IN4=P0^3;

extern void setCarForward(void);//ǰ��
extern void setCarBack(void);//����
extern void setCarStop(void);//ֹͣ
extern void setCarRightForward(void);//ǰ����ת��
extern void setCarRightBack(void);//������ת��
extern void setCarRightTurn(void);//ԭ������ת
extern void setCarLeftForward(void);//ǰ����ת��
extern void setCarLeftBack(void);//������ת��
extern void setCarLeftTurn(void);//ԭ������ת