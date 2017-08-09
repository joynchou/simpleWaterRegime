#include "DS18B20.h"
	
//unsigned char tempL=0; 		//��ȫ�ֱ���
//unsigned char tempH=0; 
//unsigned int sdata;			//���������¶ȵ���������
//unsigned char xiaoshu1;		//С����һλ
//unsigned char xiaoshu2;		//С���ڶ�λ
//unsigned char xiaoshu;		//��λС��
static int fg = 1;        			//�¶�������־

typedef struct
{
	u8 tempL;//�¶ȵͰ�λ
	u8 tempH;//�¶ȸ߰�λ
	float Tempera;//�¶�
	u8 StartState;//����״̬״̬
	u8 InitState;//��ʼ��״̬
	u16 Integer;//��������
	u16 Decimal;//С������
}DS18B20;

static DS18B20 s_Temperature;

void DS18B20Delay3ms()		//@24.000MHz,3us delay
{
	unsigned char i;

	_nop_();
	_nop_();
	i = 15;
	while (--i);
}


void DS18B20Delay6us()		//@24.000MHz,6us delay
{
	unsigned char i;

	_nop_();
	_nop_();
	i = 33;
	while (--i);
}

void DS18B20Delay24us()		//@24.000MHz,24us delay
{
	unsigned char i, j;

	i = 1;
	j = 140;
	do
	{
		while (--j);
	}while (--i);
}

void DS18B20Delay30us()		//@24.000MHz,30us delya
{
	unsigned char i, j;

	i = 1;
	j = 176;
	do
	{
		while (--j);
	} while (--i);
}

void DS18B20Delay300us()		//@24.000MHz,300us delay
{
	unsigned char i, j;

	i = 7;
	j = 254;
	do
	{
		while (--j);
	} while (--i);
}

void DS18B20Delay600us()		//@24.000MHz,600us delay
{
	unsigned char i, j;

	i = 14;
	j = 255;
	do
	{
		while (--j);
	} while (--i);
}

void DS18B20Delay1000ms()		//@24.000MHz,1s delay
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 92;
	j = 50;
	k = 238;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void Init_DS18B20() 
{
	GPIO_InitTypeDef    DS18B20GPIO_InitStructure;     //�ṹ����
	DS18B20GPIO_InitStructure.Mode = GPIO_PullUp;  
	DS18B20GPIO_InitStructure.Pin = GPIO_Pin_0;    //ָ��Ҫ��ʼ����IO, GPIO_Pin_0 ~ GPIO_Pin_7, �����
	GPIO_Inilize(GPIO_P2, &DS18B20GPIO_InitStructure);  //��ʼ�� 
		DS18B20_DQ = 1; 					//DQ���ø� 
		DS18B20Delay6us(); 				//����ʱ
		DS18B20_DQ = 0; 					//���͸�λ���� 
		DS18B20Delay600us();//��ʱ��>480us) 
		DS18B20_DQ = 1; 					//���������� 
		DS18B20Delay30us(); 				//�ȴ���15~60us) 
		s_Temperature.InitState = DS18B20_DQ; 					//��X��ֵ���жϳ�ʼ����û�гɹ���18B20���ڵĻ�X=0������X=1 
		DS18B20Delay600us(); 
}

//��һ���ֽ�
u8 ReadDate(void)  			//�����������ȴӸ������͵�ƽ1us���ϣ���ʹ��������Ϊ�ߵ�ƽ���Ӷ��������ź�
{
	unsigned char i = 0; 		//ÿ����������̵ĳ���ʱ��Ϊ60us������������֮�������1us���ϵĸߵ�ƽ�ָ���
	unsigned char DS18B20_date = 0; 
	for (i = 8;i > 0;i--) 		//һ���ֽ���8λ 
	{
		DS18B20_DQ = 1; 
		NOP1(); 
		DS18B20_DQ = 0;
		DS18B20_date >>= 1;
		NOP1();		
		DS18B20_DQ = 1;
		DS18B20Delay6us();
		if(DS18B20_DQ == 1) 
			DS18B20_date |= 0x80; 
		else
			DS18B20_date |= 0x00;
		DS18B20Delay24us();
	} 
	return(DS18B20_date);
}


//дһ���ֽ�
void WriteDate(unsigned char DS18B20_date) 
{ 
	unsigned char i = 0;	//�����ߴӸߵ�ƽ�����͵�ƽ������д��ʼ�źš�15us֮�ڽ�����д��λ�͵��������ϣ�
	for(i = 8;i > 0;i--) 		//��15~60us֮��������߽��в���������Ǹߵ�ƽ��д1����д0������ 
	{
		DS18B20_DQ = 1;
		NOP1();
		DS18B20_DQ = 0; 				//�ڿ�ʼ��һ��д����ǰ������1us���ϵĸߵ�ƽ�ָ��ڡ� 
		DS18B20_DQ = DS18B20_date & 0x01;
		DS18B20Delay30us();
		DS18B20_DQ = 1; 
		DS18B20Delay3us();
		DS18B20_date >>= 1;
	} 
	DS18B20Delay6us();
	DS18B20Delay6us();
}

//���¶�ֵ����λ��tempL;��λ��tempH;��
void ReadTemperature(void) 
{ 
	if(s_Temperature.StartState == 1)	
	{
		Init_DS18B20();
		WriteDate(0xcc); 				//���������кŵĲ���
		WriteDate(0x44); 				//�����¶�ת��
		DS18B20Delay300us();						//ת����Ҫһ��ʱ�䣬��ʱ 
		Init_DS18B20(); 					//��ʼ��
		WriteDate(0xcc); 				//���������кŵĲ��� 
		WriteDate(0xbe); 				//���¶ȼĴ�����ͷ����ֵ�ֱ�Ϊ�¶ȵĵ�λ�͸�λ�� 
		s_Temperature.tempL = ReadDate(); 				//�����¶ȵĵ�λLSB
		s_Temperature.tempH = ReadDate(); 				//�����¶ȵĸ�λMSB	
		if(s_Temperature.tempH > 0x7f)      				//���λΪ1ʱ�¶��Ǹ�
		{
			s_Temperature.tempL = ~ s_Temperature.tempL;					//����ת����ȡ����һ
			s_Temperature.tempH = ~ s_Temperature.tempH + 1;       
			fg = -1;      						//��ȡ�¶�Ϊ��ʱfg=0
		}
		else
		{
			fg = 1;
		}
		s_Temperature.Integer = s_Temperature.tempL / 16 + s_Temperature.tempH * 16;
//		s_Temperature.Tempera = fg * (//��ʾ����
//																	(float)((s_Temperature.tempL / 16) + s_Temperature.tempH * 16) //�������� 
//																+ (float)(((s_Temperature.tempL & 0x0f) * 10 / 16) * 10)
//																+ (float)((s_Temperature.tempL & 0x0f) * 100 / 16 % 10));//С������
		s_Temperature.Tempera = (float)(s_Temperature.Integer);
//	xiaoshu1 = (tempL & 0x0f) * 10 / 16; 		//С����һλ
//	xiaoshu2 = (tempL & 0x0f) * 100 / 16 % 10;	//С���ڶ�λ
//	xiaoshu = xiaoshu1 * 10 + xiaoshu2; 		//С����λ
	}
}

float getTemperatureValue(void)
{
	return s_Temperature.Tempera;
}

void openTemperatureRead(void)
{
	s_Temperature.StartState = 1;
}

void closeTemperatureRead(void)
{
	s_Temperature.StartState = 0;
}

u16 getTemperatureInteger(void)
{
	return s_Temperature.Integer;
}

/*
void WriteData(unsigned int val)
{
	switch(val)
	{
		case 0:
			SBUF = '0';
			break;
		case 1:
			SBUF = '1';
			break;
		case 2:
			SBUF = '2';
			break;
		case 3:
			SBUF = '3';
			break;
		case 4:
			SBUF = '4';
			break;
		case 5:
			SBUF = '5';
			break;
		case 6:
			SBUF = '6';
			break;
		case 7:
			SBUF = '7';
			break;
		case 8:
			SBUF = '8';
			break;
		case 9:
			SBUF = '9';
			break;
	}
	TI = 0;
}

//��ʾ����
void Led(unsigned int date)
{ 
	if(fg == 1)
	{

		WriteData(date / 10);
		delay_us(5);

		

		WriteData(date % 10);
		delay_us(5);
	
		delay_us(5);

		delay_us(5);
	
	}
		
	if(fg == 0)  					//�¶�Ϊ��ʱ��ʾ������
	{
		
		SBUF = '-' ;		//��ʾ����
		TI = 0;
		delay_us(5);
		
		WriteData(date / 10);
		delay_us(5);
	
		WriteData(date % 10);
		delay_us(5);
		
		delay_us(5);
	}
	//SBUF = 's';
	//TI = 0;
}
*/