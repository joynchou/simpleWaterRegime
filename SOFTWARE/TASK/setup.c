/************************************************************
* ��֯���ƣ�
* �ļ�����: K:\��Ƭ�����\���Ӵ���������\SOFTWARE\TASK\SETUP.C
* ����:     �ܳ��� 
* �汾:    
* ����:     2017/07/18
* ����:		��ʼ�������Ͳ�������ʹ��
* ��ʷ�޸ļ�¼:
* <����> <ʱ��> <�汾 > <����>
* 
***********************************************************/

#include "setup.h"
#include "../HARDWARE/DEVICES/SENSOR/ANGLE/ANGLE.h"
#include "../../HARDWARE/DEVICES/BUTTON/BUTTON.h"
#include "../../HARDWARE/DEVICES/TM1638/TM1638.h"
#include "../../HARDWARE/DEVICES/MOTOR/DC_MOTOR/MOTOR.h"
#include "../../HARDWARE/DEVICES/LED/LED.h"
#include "../../HARDWARE/BSP/USART1.h"
#include "../../HARDWARE/BSP/timer.h"
#include "../../HARDWARE/BSP/GPIO.h"
#include "../../HARDWARE/BSP/delay.h"
#include "../../HARDWARE/BSP/STC15_PWM.h"
#include "../../HARDWARE/DEVICES/MOTOR/STEP_MOTOR/STEP_MOTOR.h"
#include "../../HARDWARE/DEVICES/MOTOR/SERVO/SERVO.h"
#include "../../HARDWARE/DEVICES/DISPLAY/1602/LCD1602.H"
#include "../../HARDWARE/COMMON_HARDWARE/fixedPulser.h"



/*************  ����1��ʼ������ *****************/
/*************************************************
* ��������: void    UART1_init(unsigned long BandRate)
* ����: ����1��ʼ������
* ����: unsigned long BandRate �����ڵĲ����ʣ�������ֵ�����ĸ"L"����ֹ������
* ���: ���ô˺����ᷢ��һ�β������ �� STC15w4k58s4 UART1 is open ��
* ����ֵ: ��
* ����˵��: ��
*************************************************/
void    UART1_init(unsigned long BandRate)
{
	COMx_InitDefine     COMx_InitStructure;
	COMx_InitStructure.UART_Mode = UART_8bit_BRTx;
	COMx_InitStructure.UART_BRT_Use = BRT_Timer2;
	COMx_InitStructure.UART_BaudRate = BandRate;
	COMx_InitStructure.UART_RxEnable = ENABLE;
	COMx_InitStructure.BaudRateDouble = DISABLE;
	COMx_InitStructure.UART_Interrupt = ENABLE;
	COMx_InitStructure.UART_Polity = PolityHigh;
	COMx_InitStructure.UART_P_SW = UART1_SW_P30_P31;
	COMx_InitStructure.UART_RXD_TXD_Short = DISABLE;
	USART_Configuration(USART1, &COMx_InitStructure);
	// PrintString1("STC15w4k58s4's UART1 is open \r\n");   //���ڲ���
}
/*void test(void)//��������
{
		//stepMotor_Init (STEP_MOTOR_1,1.8f,4,6000);
	//setStepMotorWithRound(STEP_MOTOR_1,30,100);   
//	Init_Str_Motor(SERVO_1,0.5f,2.5f,180,300);
//	//Init_Str_Motor(SERVO_2,0.5f,2.5f,180,300);
//		//open_STR(SERVO_1);
//   //	set_STR_angle(SERVO_1,1);
//	    

//   for(;i<180;i++)
//	{
//	set_STR_angle(SERVO_1,i);
//  open_StepMotor(STEP_MOTOR_1);
//		delay_ms(200);
//		delay_ms(200);
//		delay_ms(200);
//	}
	//open_STR(SERVO_2);
  	int i = 0;
	GPIO_InitTypeDef    GPIO_InitStructure;     //�ṹ����
	PWM_InitTypeDef  PWM_InitStructure;


	GPIO_InitStructure.Mode = GPIO_PullUp;       //ָ��IO������������ʽ,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP

	GPIO_InitStructure.Pin = GPIO_Pin_7;    //ָ��Ҫ��ʼ����IO, GPIO_Pin_0 ~ GPIO_Pin_7, �����
	GPIO_Inilize(GPIO_P3, &GPIO_InitStructure);  //��ʼ��
	P37 = 1;
	PWM_UNLOCK;
	PWM_InitStructure.PWM_GOTO_ADC = DISABLE;
	PWM_InitStructure.PWM_V_INIT = PWM_LOW;
	PWM_InitStructure.PWM_0ISR_EN = DISABLE;
	PWM_InitStructure.PWM_OUT_EN = ENABLE;
	PWM_InitStructure.PWM_UNUSUAL_EN = DISABLE;
	PWM_InitStructure.PWM_UNUSUAL_OUT = DISABLE;
	PWM_InitStructure.PWM_UNUSUAL_ISR_EN = DISABLE;
	PWM_InitStructure.PWM_UNUSUAL_CMP0_EN = DISABLE;
	PWM_InitStructure.PWM_UNUSUAL_P24_EN = DISABLE;
	PWM_InitStructure.PWM_CLOCK = PWM_Clock_NT;
	PWM_InitStructure.PWM_CLOCK_DIV = 15;
	PWM_InitStructure.PWM_SELECTx_IO = PWM_SELECT_N;
	PWM_InitStructure.PWM_ISRx_EN = DISABLE;
	PWM_InitStructure.PWM_T1x_EN = DISABLE;
	PWM_InitStructure.PWM_T2x_EN = DISABLE;
	PWM_InitStructure.PWM_EN = DISABLE;
	PWM_Inilize(PWM_2, &PWM_InitStructure);
	PWM_LOCK;
	setPWM_DIV(PWM_2, 16);//16��Ƶ
	set_PWM_period(PWM_2, 50);
	set_PWM_duty(PWM_2, 0.1f);
	open_PWM_N(PWM_2);

	for (i = 100; i < 1000; i++)
	{
		set_PWM_duty(PWM_2, i / 1000.0f);
		delay_ms(200);
		delay_ms(200);
		delay_ms(200);

	}

}*/
void setup(void)
{
	UART1_init(115200L);
	// timerInit();
	Init_TM1638();
	Board_LED_Init();

	//Button_config();
	//ADC_config(ADC_P10, ADC_540T);
	//LCD1602_Init();
	//EA = 1;
	//test();
}

