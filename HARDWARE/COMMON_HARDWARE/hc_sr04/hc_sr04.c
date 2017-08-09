/************************************************************
* ��֯���ƣ�
* �ļ�����: HARDWARE\COMMON_HARDWARE\HC_SR04\HC_SR04.C
* ����:
* �汾:
* ����:     2017/08/05
* ����:
* ��ʷ�޸ļ�¼:
* <����> <ʱ��> <�汾 > <����>
*
***********************************************************/
#define ext0Disable() EX0 = 0
#define ext0Able() EX0 = 1

//#define DEBUG
#include "hc_sr04.h"
#include <stdio.h>
#include "../SOFTWARE/TASK/COMMON_SOFTWARE/ALGORITHM/DIGITAL_FILTER/FILTER/FILTER.H"
typedef struct
{
	double distance;
	u8 state;
	u16 timerValue;

}HC_SR04;
static HC_SR04 hc_sr04[1];
static u8 extiBit = 0;
u8 str[20];
void HC_SR04_init(void)
{
	GPIO_InitTypeDef hc_sr04_GPIO;
	EXTI_InitTypeDef  hc_sr04_EXTI;
	hc_sr04_GPIO.Mode = GPIO_PullUp;
	hc_sr04_GPIO.Pin = GPIO_Pin_3;
	GPIO_Inilize(GPIO_P3, &hc_sr04_GPIO);
	hc_sr04_GPIO.Mode = GPIO_HighZ; //�ⲿ�ж�Ҫʹ�����ģʽ
	hc_sr04_GPIO.Pin = GPIO_Pin_2;
	GPIO_Inilize(GPIO_P3, &hc_sr04_GPIO);
	hc_sr04_EXTI.EXTI_Interrupt = ENABLE;
	hc_sr04_EXTI.EXTI_Mode = EXT_MODE_RiseFall;
	hc_sr04_EXTI.EXTI_Polity = PolityHigh;
	Ext_Inilize(EXT_INT0, &hc_sr04_EXTI);
	P32 = 0;//���ų�ʼ��
	P33 = 0;//���ų�ʼ��

}



//************************************
// Method:    open_HC_SR04
// FullName:  open_HC_SR04
// Access:    public 
// Returns:   void
// Qualifier: �򿪴�ģ��Ŀ���
// Parameter: u8 num
//************************************
void open_HC_SR04(u8 num)
{

	hc_sr04[num].state = ON;


}
void close_HC_SR04(u8 num)
{
	hc_sr04[num].state = OFF;
}
u8 getHC_SR04_State(u8 num)
{
	return hc_sr04[num].state;

}
void setTimerValue(u8 num, u16 value)
{
	hc_sr04[num].timerValue = value;
}
void setDistance(u8 num,float value)
{
	hc_sr04[num].distance = value;
}
//************************************
// Method:    getTimerValue
// FullName:  getTimerValue
// Access:    public 
// Returns:   u16
// Qualifier: �����ԭʼ�ĸߵ�ƽʱ�䣬��λms
// Parameter: u8 num
//************************************
u16 getTimerValue(u8 num)
{
	return hc_sr04[num].timerValue;

}
//************************************
// Method:    updateDistance
// FullName:  updateDistance
// Access:    public 
// Returns:   void
// Qualifier: ��������и��¾���
// Parameter: u8 num
//************************************
void updateDistance(u8 num)
{
	static double time;//��Ӧʱ������λms
	if (!hc_sr04[num].state)
	{
		return ;
	}
	ext0Able();

	Trig = HIGH;//���������ź�
	delay_us(5);//�˺�����̫׼��3usʵ�ʴ��
	Trig = LOW;
 }
//************************************
// Method:    getdistance
// FullName:  getdistance
// Access:    public 
// Returns:   float
// Qualifier: //��ȡ����������,��λcm,ԭʼ���ݣ�
// Parameter: u8 num
//************************************
double getdistance(u8 num)//��ȡ����������
{

 
	return hc_sr04[num].distance;//���û�и��������򷵻���һ�θ��µ�ֵ�����򷵻����ֵ
}
/********************* INT0�жϺ��� *************************/
static void Ext_INT0(void) interrupt INT0_VECTOR		//���ж�ʱ�Ѿ������־
{

	//u8 timerValueL, timerValueH;
#ifdef DEBUG
		//PrintString1("into\r\n");
#endif
	//delay_us(1);
	if (INT0 == RISING_EDGE)//������
	{
		Timer4_Run();//��ʼ��ʱ
		extiBit = LOW;
#ifdef DEBUG
		PrintString1("rising edge\r\n");
#endif

	}
	else if (INT0 == FALLING_EDGE)//�½���
	{

		Timer4_Stop();
		hc_sr04[0].timerValue = TH4;
		hc_sr04[0].timerValue = hc_sr04[0].timerValue * 256 + TL4;
#ifdef DEBUG
		USART1_printf("valueL is %d\r\n", (u16)TL4);
		USART1_printf("valueH is %d\r\n", (u16)TH4);
		sprintf(str, "value is %u\r\n", TH4 * 256 + TL4);
		PrintString1(str);
#endif  		
		TH4 = 0;
		TL4 = 0;
		extiBit = OK;//������׼����

	}
	else
	{
		extiBit = LOW;
		Timer4_Stop();

#ifdef DEBUG
		PrintString1("error\r\n");
#endif
	}
	//	ext0Disable();

}
