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
	COMx_InitStructure.UART_BRT_Use = BRT_Timer1;
	COMx_InitStructure.UART_BaudRate = BandRate;
	COMx_InitStructure.UART_RxEnable = ENABLE;
	COMx_InitStructure.BaudRateDouble = DISABLE;
	COMx_InitStructure.UART_Interrupt = ENABLE;
	COMx_InitStructure.UART_Polity = PolityHigh;
	COMx_InitStructure.UART_P_SW = UART1_SW_P30_P31;
	COMx_InitStructure.UART_RXD_TXD_Short = DISABLE;
	USART_Configuration(USART1, &COMx_InitStructure);
	PrintString1("STC15w4k58s4's UART1 is open \r\n");   //���ڲ���
}
void test(void)//��������
{
	u8 i = 0;
	Ds1302_Init();
	USART1_printf("this is a test\r\n");
	for (i = 0; i < 8; i++)
	{
		time_buf[i] = 1;
	}
	while (1)
	{
		{
			Ds1302_Read_Time();
			USART1_printf("%d-%d-%d-%d \r\n", (int)time_buf1[3], (int)time_buf1[4], (int)time_buf1[5], (int)time_buf1[6]);//������  %02d ʮ�������� 
			delay_ms(200);
		}
	}
}
void setup(void)
{

	UART1_init(115200ul);
	timerInit();
	NRF24L01_Init(HALF_DUPLEX);
//	Board_LED_Init();
//	LCD5510_Init();
//	LCD_printsl(0, 0, "Hello!");
//	os_wait(K_TMO, 250, 0);
//	LCD_clr_scr();
//	Button_config();
//	Speaker_Init();

// 
//	//InitJY901(JY901_1);
//	//EnableJY901(JY901_1);
//	//openJY901SbufMode(JY901_1);
//	ADC_config(ADC_P10, ADC_540T);
//	ADS1115_Config();
//	HC_SR04_init();
//	open_HC_SR04(HC_SR04_1);
//	open_ADS1115(CHANNEL_1);
//	open_ADS1115(CHANNEL_2);
//	open_ADS1115(CHANNEL_3);
//	open_ADS1115(CHANNEL_4);
//	// test();

}

