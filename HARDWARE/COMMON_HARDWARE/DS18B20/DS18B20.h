#ifndef __DB18B20_H__
#define __DB18B20_H__

#include "../BSP/BSP.H"

sbit DS18B20_DQ=P2^0; 				//数据传输线接单片机的相应的引脚
void Init_DS18B20();//DS18B20初始化
void ReadTemperature(void);//读取DS18B20数据，温度扫描
float getTemperatureValue(void);//读取温度
void openTemperatureRead(void);//开启温度扫描开关
void closeTemperatureRead(void);//关闭温度扫描开关
u16 getTemperatureInteger(void);

#endif