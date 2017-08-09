#include "RTC.H"

typedef struct
{
	u16 second;//��
	u16 minute;//��
	u16 hour;	 //ʱ
	u16 week;  //����
	u16 day;   //����
	u16 month; //�·�
	u16 year;  //���
}TimerClock;

static TimerClock s_RTC_Time;
/**************************************************************
 *������u8 Read_RTC_Date(u8 address,u8 date)
 *���ã���ȡ������ַ������
 **************************************************************/
u8 Read_RTC_Date(u8 address,u8 date)
{
	u8 value;
	InputOneByte(address | IIC_WRITE);
	IIC_RdAck();
	InputOneByte(date);
	IIC_RdAck();
	InputOneByte(address | IIC_READ);
	IIC_RdAck();
	value = OutputOneByte();
	IIC_Nack();
	IIC_Stop();
	return value;
}

/**************************************************************
 *������u8 Write_RTC_Date(u8 date)
 *���ã�д����
 **************************************************************/
void Write_RTC_Date(u8 date)
{
	IIC_WrDevAddAndDatAdd(DS1307_ADDRESS | IIC_WRITE,DS1307_CONTROL);
	InputOneByte(date);
	IIC_RdAck();
	IIC_Stop();
}

/**************************************************************
 *������u8 *Read_RTC_Time(u8 address)
 *���ã���ȡʱ�������
 **************************************************************/
u8 get_RTC_Time(u8 address,u8 *Time)
{
	u8 i;
	IIC_Start();
	InputOneByte(address | IIC_READ);
	IIC_RdAck();
	for(i = 0;i < 7;i++)
	{	
		Time[i] = OutputOneByte();	
		IIC_Ack();
	}
	IIC_Nack();
	IIC_Stop();
//	return Time;
}
