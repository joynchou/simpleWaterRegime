#include "VOLTMETER.H"

typedef struct//电压表结构体
{
	u8 state;//电压表开关状态
	float voltage;//电压表示数
	u8 vol_unit;//电压表精度
}Voltmeter;

static Voltmeter vol[VOL_NUM];

void Voltmeter_config(void)
{
	u8 i;
	for(i = 0;i < VOL_NUM;i++)
	{
		vol[i].state = OFF;
		vol[i].voltage = 0.0f;
		vol[i].vol_unit = NULL;
	}
}

/********************************************************
 *函数：void setVolUnit(u8 VOL_N,u8 unit)
 *作用：设置电压表的量程
 *参数：	u8 VOL_N：电压通道
 *		  u8 unit：单位
 *返回值：无
 *说明：静止与ADC其他通道共用
 ********************************************************/
void setVolUnit(u8 VOL_N,u8 unit)
{
	vol[VOL_N].vol_unit = unit;
}

/********************************************************
 *函数：void openVoltmeter(u8 VOL_N)
 *作用：开启指定电压测量通道
 *参数：	u8 VOL_N：电压测量通道
 *返回值：无
 *说明：静止与ADC其他通道共用
 ********************************************************/
void openVoltmeter(u8 VOL_N)
{
	vol[VOL_N].state = ON;
	open_ADS1115(VOL_N);
}

/********************************************************
 *函数：void closeVoltmeter(u8 VOL_N)
 *作用：关闭指定电压测量通道
 *参数：	u8 VOL_N：电压测量通道
 *返回值：无
 *说明：静止与ADC其他通道共用
 ********************************************************/
void closeVoltmeter(u8 VOL_N)
{
	vol[VOL_N].state = OFF;
	close_ADS1115(VOL_N);
}

/********************************************************
 *函数：void openAllVoltmeter(void)
 *作用：开启电压表所有通道
 *参数：无
 *返回值：无
 *说明：静止与ADC其他通道共用
 ********************************************************/
void openAllVoltmeter(void)
{
	u8 i;
	for(i = 0;i < VOL_NUM;i++)
	{
		vol[i].state = ON;
	}
}

/********************************************************
 *函数：void closeAllVoltmeter(void)
 *作用：关闭电压表所有通道
 *参数：	无
 *返回值：无
 *说明：静止与ADC其他通道共用
 ********************************************************/
void closeAllVoltmeter(void)
{
	u8 i;
	for(i = 0;i < VOL_NUM;i++)
	{
		vol[i].state = OFF;
	}
}

/********************************************************
 *函数：float getVoltageValue(u8 VOL_N)
 *作用：返回指定通道的电压值
 *参数：	u8 VOL_N：电压测量通道
 *返回值：float
 *说明：静止与ADC其他通道共用
 ********************************************************/
float getVoltageValue(u8 VOL_N)
{
	return vol[VOL_N].voltage;
}

/********************************************************
 *函数：float getVoltageValue(u8 VOL_N)
 *作用：返回指定通道的电压值
 *参数：	u8 VOL_N：电压测量通道
 *返回值：float
 *说明：静止与ADC其他通道共用
 ********************************************************/
float CalculateVoltageValue(u8 VOL_N)
{
//	switch(vol[VOL_N].unit)
//	{
//		case 2_V:
//			return limitingFilter((float)getADS1115ConvsionData(VOL_1),(float)10.0f) / 65535.0f * REFERENCE_VOLTAGE * 3.0f * 2.5f;
//			break;
//		case 20_V:
//			return limitingFilter((float)getADS1115ConvsionData(VOL_1),(float)10.0f) / 65535.0f * REFERENCE_VOLTAGE * 3.0f * 2.3f;
//			break;
//		case 200_V:
//			return limitingFilter((float)getADS1115ConvsionData(VOL_1),(float)10.0f) / 65535.0f * REFERENCE_VOLTAGE * 3.0f * 2.1f;
//			break;
//	}
	float value;
	value = limitingFilter((float)getADS1115ConvsionData(VOL_1),(float)10.0f) / 65535.0f * REFERENCE_VOLTAGE * 3.0f * 2.5f;
	if(value - 2.0f > 0)value = value / 2.5f * 2.485f;
  if(value - 200.f > 0)value = value / 2.3f * 2.1f;
	return value;
}

/********************************************************
 *函数：void VoltageValueScan()
 *作用：通道数据扫描
 *参数：无
 *返回值：无
 *说明：静止与ADC其他通道共用
 ********************************************************/
void VoltageValueScan()
{
	if(vol[VOL_1].state == ON)
	{
		vol[VOL_1].voltage = CalculateVoltageValue(VOL_1);
	}
	else
	{
		vol[VOL_1].voltage = 0.0f; 
	}
	if(vol[VOL_2].state == ON)
	{
		vol[VOL_2].voltage = CalculateVoltageValue(VOL_2);
	}
	else
	{
		vol[VOL_2].voltage = 0.0f; 
	}
	if(vol[VOL_3].state == ON)
	{
		vol[VOL_3].voltage = CalculateVoltageValue(VOL_3);
	}
	else
	{
		vol[VOL_3].voltage = 0.0f; 
	}
	if(vol[VOL_4].state == ON)
	{
		vol[VOL_4].voltage = CalculateVoltageValue(VOL_4);
	}
	else
	{
		vol[VOL_4].voltage = 0.0f; 
	}
}