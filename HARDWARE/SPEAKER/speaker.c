#include "speaker.h"
void setSpeakerPeriod(u16 value)
{

}
void setLength(u16 value)
{

}
void open_Speaker(u8 value)
{

}
void close_Speaker(u8 value)
{

}
//************************************
// Method:    buzz
// FullName:  buzz
// Access:    public 
// Returns:   void
// Qualifier: 
// Parameter: u16 time:�����ĳ���ʱ����ms
//						u16 type:������Ƶ��
//************************************
void buzz(u16 type,u16 time)
{
	u16 pulse=(u16)(time*type/1000.0f);  //����ʱ����Ƶ�����������
	u8 loopTime=time/255;
	   closePulser(PULSER_2);
		setPulse(PULSER_2, type, pulse);
		openPulser(PULSER_2);
		//PrintString1("buzz\r\n");
	if(time<255)//С��255
		{
		 os_wait(K_TMO, time, 0);

		}
		else
		{
			while(loopTime--)
			{
		 os_wait(K_TMO, 255, 0);
				
			}
		os_wait(K_TMO, time%255, 0);

		}

}
void buzzSucceed(void)
{
	buzz(530, 150);
	buzz(660, 150);
	buzz(788, 150);
}
void buzzWait(void)
{
	buzz(530, 150);

}
void buzzFailed(void)
{
	buzz(788, 150);
	buzz(660, 150);
	buzz(530, 150);

}
void Speaker_Init(void)
{
   PulserInit();
	buzz(444, 100); //6
	buzz(394, 100); //5
	buzz(350, 100); //4
	buzz(394, 100); //5
 	buzz(530, 400); //��1

}

