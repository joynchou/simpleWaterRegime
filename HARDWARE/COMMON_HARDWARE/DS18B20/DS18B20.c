#include "DS18B20.h"
	
//unsigned char tempL=0; 		//设全局变量
//unsigned char tempH=0; 
//unsigned int sdata;			//测量到的温度的整数部分
//unsigned char xiaoshu1;		//小数第一位
//unsigned char xiaoshu2;		//小数第二位
//unsigned char xiaoshu;		//两位小数
static int fg = 1;        			//温度正负标志

typedef struct
{
	u8 tempL;//温度低八位
	u8 tempH;//温度高八位
	float Tempera;//温度
	u8 StartState;//运行状态状态
	u8 InitState;//初始化状态
	u16 Integer;//整数部分
	u16 Decimal;//小数部分
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
	GPIO_InitTypeDef    DS18B20GPIO_InitStructure;     //结构定义
	DS18B20GPIO_InitStructure.Mode = GPIO_PullUp;  
	DS18B20GPIO_InitStructure.Pin = GPIO_Pin_0;    //指定要初始化的IO, GPIO_Pin_0 ~ GPIO_Pin_7, 或操作
	GPIO_Inilize(GPIO_P2, &DS18B20GPIO_InitStructure);  //初始化 
		DS18B20_DQ = 1; 					//DQ先置高 
		DS18B20Delay6us(); 				//稍延时
		DS18B20_DQ = 0; 					//发送复位脉冲 
		DS18B20Delay600us();//延时（>480us) 
		DS18B20_DQ = 1; 					//拉高数据线 
		DS18B20Delay30us(); 				//等待（15~60us) 
		s_Temperature.InitState = DS18B20_DQ; 					//用X的值来判断初始化有没有成功，18B20存在的话X=0，否则X=1 
		DS18B20Delay600us(); 
}

//读一个字节
u8 ReadDate(void)  			//主机数据线先从高拉至低电平1us以上，再使数据线升为高电平，从而产生读信号
{
	unsigned char i = 0; 		//每个读周期最短的持续时间为60us，各个读周期之间必须有1us以上的高电平恢复期
	unsigned char DS18B20_date = 0; 
	for (i = 8;i > 0;i--) 		//一个字节有8位 
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


//写一个字节
void WriteDate(unsigned char DS18B20_date) 
{ 
	unsigned char i = 0;	//数据线从高电平拉至低电平，产生写起始信号。15us之内将所需写的位送到数据线上，
	for(i = 8;i > 0;i--) 		//在15~60us之间对数据线进行采样，如果是高电平就写1，低写0发生。 
	{
		DS18B20_DQ = 1;
		NOP1();
		DS18B20_DQ = 0; 				//在开始另一个写周期前必须有1us以上的高电平恢复期。 
		DS18B20_DQ = DS18B20_date & 0x01;
		DS18B20Delay30us();
		DS18B20_DQ = 1; 
		DS18B20Delay3us();
		DS18B20_date >>= 1;
	} 
	DS18B20Delay6us();
	DS18B20Delay6us();
}

//读温度值（低位放tempL;高位放tempH;）
void ReadTemperature(void) 
{ 
	if(s_Temperature.StartState == 1)	
	{
		Init_DS18B20();
		WriteDate(0xcc); 				//跳过读序列号的操作
		WriteDate(0x44); 				//启动温度转换
		DS18B20Delay300us();						//转换需要一点时间，延时 
		Init_DS18B20(); 					//初始化
		WriteDate(0xcc); 				//跳过读序列号的操作 
		WriteDate(0xbe); 				//读温度寄存器（头两个值分别为温度的低位和高位） 
		s_Temperature.tempL = ReadDate(); 				//读出温度的低位LSB
		s_Temperature.tempH = ReadDate(); 				//读出温度的高位MSB	
		if(s_Temperature.tempH > 0x7f)      				//最高位为1时温度是负
		{
			s_Temperature.tempL = ~ s_Temperature.tempL;					//补码转换，取反加一
			s_Temperature.tempH = ~ s_Temperature.tempH + 1;       
			fg = -1;      						//读取温度为负时fg=0
		}
		else
		{
			fg = 1;
		}
		s_Temperature.Integer = s_Temperature.tempL / 16 + s_Temperature.tempH * 16;
//		s_Temperature.Tempera = fg * (//表示正负
//																	(float)((s_Temperature.tempL / 16) + s_Temperature.tempH * 16) //整数部分 
//																+ (float)(((s_Temperature.tempL & 0x0f) * 10 / 16) * 10)
//																+ (float)((s_Temperature.tempL & 0x0f) * 100 / 16 % 10));//小数部分
		s_Temperature.Tempera = (float)(s_Temperature.Integer);
//	xiaoshu1 = (tempL & 0x0f) * 10 / 16; 		//小数第一位
//	xiaoshu2 = (tempL & 0x0f) * 100 / 16 % 10;	//小数第二位
//	xiaoshu = xiaoshu1 * 10 + xiaoshu2; 		//小数两位
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

//显示函数
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
		
	if(fg == 0)  					//温度为负时显示的数据
	{
		
		SBUF = '-' ;		//显示负号
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