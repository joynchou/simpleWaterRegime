/************************************************************
* ��֯���ƣ�
* �ļ�����: K:\��Ƭ�����\���Ӵ���������\HARDWARE\COMMON_HARDWARE\DS1302\DS1302.C
* ����:
* �汾:
* ����:     2017/08/04
* ����:
* ��ʷ�޸ļ�¼:
* <����> <ʱ��> <�汾 > <����>
*
***********************************************************/
#include "DS1302.H"


unsigned char time_buf1[8];//��������ʱ������,ʱ�����û�����
unsigned char time_buf[8]; //��������ʱ�����ܣ�ʱ��д�뻺����


/*************************************************
* ��������: Ds1302_Write_Byte
* ����: ��DS1302д��һ�ֽ�����
* ����: unsigned char addr, unsigned char d
* ����ֵ: ��
* ����˵��: ���ֹͣDS1302����
*************************************************/

void Ds1302_Write_Byte(unsigned char addr, unsigned char d)
{

	unsigned char i;
	RST_SET;

	//д��Ŀ���ַ��addr
	addr = addr & 0xFE;     //���λ����
	for (i = 0; i < 8; i++)
	{
		if (addr & 0x01)
		{
			IO_SET;
		}
		else
		{
			IO_CLR;
		}
		SCK_SET;
		SCK_CLR;
		addr = addr >> 1;
	}

	//д�����ݣ�d
	for (i = 0; i < 8; i++)
	{
		if (d & 0x01)
		{
			IO_SET;
		}
		else
		{
			IO_CLR;
		}
		SCK_SET;
		SCK_CLR;
		d = d >> 1;
	}
	RST_CLR;					//ֹͣDS1302����
}


/*************************************************
* ��������: Ds1302_Read_Byte
* ����: ��DS1302����һ�ֽ�����
* ����: unsigned char addr
* ����ֵ: temp
* ����˵��: ����ԭʼ����
*************************************************/

unsigned char Ds1302_Read_Byte(unsigned char addr)
{

	unsigned char i;
	unsigned char temp;
	RST_SET;

	//д��Ŀ���ַ��addr
	addr = addr | 0x01;//���λ�ø�
	for (i = 0; i < 8; i++)
	{

		if (addr & 0x01)
		{
			IO_SET;
		}
		else
		{
			IO_CLR;
		}
		SCK_SET;
		SCK_CLR;
		addr = addr >> 1;
	}

	//������ݣ�temp
	for (i = 0; i < 8; i++)
	{
		temp = temp >> 1;
		if (IO_R)
		{
			PrintString1(" high\r\n");
			temp |= 0x80;
		}
		else
		{
		  PrintString1(" low\r\n");

			temp &= 0x7F;
		}
		SCK_SET;
		SCK_CLR;
	}

	RST_CLR;	//ֹͣDS1302����
	return temp;
}

/*************************************************
* ��������: Ds1302_Write_Time
* ����: ��DS1302д��ʱ������
* ����: ��
* ����ֵ: �꣬�£��գ�ʱ���֣��룬��
* ����˵��:��������ʱ������,ʱ�����û�����
*************************************************/

void Ds1302_Write_Time(void)
{

	unsigned char i, tmp;
	for (i = 0; i < 8; i++)
	{                  //BCD����
		tmp = time_buf1[i] / 10;
		time_buf[i] = time_buf1[i] % 10;
		time_buf[i] = time_buf[i] + tmp * 16;
	}
	Ds1302_Write_Byte(ds1302_control_add, 0x00);			//�ر�д���� 
	Ds1302_Write_Byte(ds1302_sec_add, 0x80);				//��ͣ 
	Ds1302_Write_Byte(ds1302_charger_add,0xa9);			//������ 

	Ds1302_Write_Byte(shuju_1_add, time_buf[0]);//д�����ǰ��λ��RAM
	Ds1302_Write_Byte(ds1302_year_add, time_buf[1]);		//�� 
	Ds1302_Write_Byte(ds1302_month_add, time_buf[2]);	//�� 
	Ds1302_Write_Byte(ds1302_date_add, time_buf[3]);		//��  
	Ds1302_Write_Byte(ds1302_hr_add, time_buf[4]);		  //ʱ 
	Ds1302_Write_Byte(ds1302_min_add, time_buf[5]);		//��
	Ds1302_Write_Byte(ds1302_sec_add, time_buf[6]);		//��
	Ds1302_Write_Byte(ds1302_day_add, time_buf[7]);		//�� 
	Ds1302_Write_Byte(ds1302_control_add, 0x80);			//��д���� 
}

/*************************************************
* ��������: Ds1302_Read_Time
* ����: ��DS1302����ʱ������
* ����: ��
* ����ֵ:time_buf
* ����˵��: ��������ʱ�����ܣ�ʱ��д�뻺����
*************************************************/

void Ds1302_Read_Time(void)
{
	unsigned char i, tmp;


	time_buf[0] = Ds1302_Read_Byte(shuju_1_add);//����RAM�����ǰ��λ
	time_buf[1] = Ds1302_Read_Byte(ds1302_year_add);		//�� 
	time_buf[2] = Ds1302_Read_Byte(ds1302_month_add);		//�� 
	time_buf[3] = Ds1302_Read_Byte(ds1302_date_add);		//�� 
	time_buf[4] = Ds1302_Read_Byte(ds1302_hr_add);		//ʱ 
	time_buf[5] = Ds1302_Read_Byte(ds1302_min_add);		//�� 
	time_buf[6] = (Ds1302_Read_Byte(ds1302_sec_add)) & 0x7F;//�� 
	time_buf[7] = Ds1302_Read_Byte(ds1302_day_add);		//�� 


	for (i = 0; i < 8; i++)
	{           //BCD����
		tmp = time_buf[i] / 16;
		time_buf1[i] = time_buf[i] % 16;
		time_buf1[i] = time_buf1[i] + tmp * 10;
	}
}

/*************************************************
* ��������: Ds1302_Init
* ����: DS1302��ʼ��
* ����: ��
* ����ֵ:��
* ����˵��: ds1302ģ���ʼ��
*************************************************/

void Ds1302_Init(void)
{
	GPIO_InitTypeDef    GPIO_InitStructure;     //���ùܽ�
	GPIO_InitStructure.Mode = GPIO_PullUp;
	GPIO_InitStructure.Pin = GPIO_Pin_3 | GPIO_Pin_1 | GPIO_Pin_2 ;   //ds1302
	GPIO_Inilize(GPIO_P1, &GPIO_InitStructure);
	RST_CLR;			//RST���õ�
	delay_us(50);
	SCK_CLR;			//SCK���õ�
	delay_us(50);
	Ds1302_Write_Byte(ds1302_sec_add, 0x00);
}
