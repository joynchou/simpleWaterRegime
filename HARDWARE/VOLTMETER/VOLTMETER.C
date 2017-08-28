#include "VOLTMETER.H"

typedef struct//��ѹ���ṹ��
{
	u8 state;//��ѹ������״̬
	float voltage;//��ѹ��ʾ��
	u8 vol_unit;//��ѹ������
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
 *������void setVolUnit(u8 VOL_N,u8 unit)
 *���ã����õ�ѹ��������
 *������	u8 VOL_N����ѹͨ��
 *		  u8 unit����λ
 *����ֵ����
 *˵������ֹ��ADC����ͨ������
 ********************************************************/
void setVolUnit(u8 VOL_N,u8 unit)
{
	vol[VOL_N].vol_unit = unit;
}

/********************************************************
 *������void openVoltmeter(u8 VOL_N)
 *���ã�����ָ����ѹ����ͨ��
 *������	u8 VOL_N����ѹ����ͨ��
 *����ֵ����
 *˵������ֹ��ADC����ͨ������
 ********************************************************/
void openVoltmeter(u8 VOL_N)
{
	vol[VOL_N].state = ON;
	open_ADS1115(VOL_N);
}

/********************************************************
 *������void closeVoltmeter(u8 VOL_N)
 *���ã��ر�ָ����ѹ����ͨ��
 *������	u8 VOL_N����ѹ����ͨ��
 *����ֵ����
 *˵������ֹ��ADC����ͨ������
 ********************************************************/
void closeVoltmeter(u8 VOL_N)
{
	vol[VOL_N].state = OFF;
	close_ADS1115(VOL_N);
}

/********************************************************
 *������void openAllVoltmeter(void)
 *���ã�������ѹ������ͨ��
 *��������
 *����ֵ����
 *˵������ֹ��ADC����ͨ������
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
 *������void closeAllVoltmeter(void)
 *���ã��رյ�ѹ������ͨ��
 *������	��
 *����ֵ����
 *˵������ֹ��ADC����ͨ������
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
 *������float getVoltageValue(u8 VOL_N)
 *���ã�����ָ��ͨ���ĵ�ѹֵ
 *������	u8 VOL_N����ѹ����ͨ��
 *����ֵ��float
 *˵������ֹ��ADC����ͨ������
 ********************************************************/
float getVoltageValue(u8 VOL_N)
{
	return vol[VOL_N].voltage;
}

/********************************************************
 *������float getVoltageValue(u8 VOL_N)
 *���ã�����ָ��ͨ���ĵ�ѹֵ
 *������	u8 VOL_N����ѹ����ͨ��
 *����ֵ��float
 *˵������ֹ��ADC����ͨ������
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
 *������void VoltageValueScan()
 *���ã�ͨ������ɨ��
 *��������
 *����ֵ����
 *˵������ֹ��ADC����ͨ������
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