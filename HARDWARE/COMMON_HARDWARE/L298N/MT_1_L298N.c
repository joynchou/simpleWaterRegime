/**********************************
* �ļ����ƣ�L298Nģ�����
* ���ߣ���־ǿ
* �汾��1.0
* ���ڣ�2017/07/08
* ������
* 1.0����д�˶������Ҫ���ƺ�����������������ؿ��ơ�����Ƕȶ�ȡ���趨
* �����MT_1_L298N.H�е�ע��
************************************/

#include "MT_1_L298N.H"//ͷ�ļ�

void setCarForward(void)//ǰ��
{
	IN1=1;
	IN2=0;
	IN3=0;
	IN4=1;
} 

void setCarBack(void)//����
{
	IN1=0;
	IN2=1;
	IN3=1;
	IN4=0;
} 

void setCarStop(void)//ֹͣ
{
	IN1=0;
	IN2=0,
	IN3=0,
	IN4=0;
}

void setCarRightForward(void)//ǰ����ת��
{
	IN1=1;
	IN2=0;
	IN3=0;
	IN4=0;
}

void setCarRightBack(void)//������ת��
{
	IN1=0;
	IN2=1;
	IN3=0;
	IN4=0;
}	  

void setCarRightTurn(void)//ԭ������ת
{
	IN1=1;
	IN2=0;
	IN3=1;
	IN4=0;	
}

void setCarLeftForward(void)//ǰ����ת��
{
	IN1=0;
	IN2=0;
	IN3=0;
	IN4=1;
}

void setCarLeftBack(void)//������ת��
{
	IN1=0;
	IN2=0;
	IN3=1;
	IN4=0;
} 

void setCarLeftTurn(void)//ԭ������ת
{
	IN1=0;
	IN2=1;
	IN3=0;
	IN4=1;
}