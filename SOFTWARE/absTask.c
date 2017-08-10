#include <stdlib.h>
#include "TASK/task.h"
#define TEMPERATURE_UPDATE  15 
#define BUTTON_SCAN 14
#define TIME_UPDATE 13
#define BUTTON_SOUND 12
void taskStart() _task_ 0
{
	setup();
	//	blink(3);
	os_create_task(10);
	//os_create_task(BUTTON_SCAN);
	//os_create_task(BUTTON_SOUND);
	//	os_create_task(TEMPERATURE_UPDATE);
	//	os_create_task(TIME_UPDATE);
	os_delete_task(0);

}
void printDistance(void) _task_ 5
{
	for (;;)
	{
		DataScope_Get_Channel_Data(getADS1115ConvsionData(0)*(-0.00070804f) + 12.8156709f, 1);

		sendScopeData(1);
		os_wait(K_TMO, 30, 0);
	}
}
void printTmp()  _task_  9
{
	for (;;)
	{
		getDS18B20_Temperature(0);
		//		DataScope_Get_Channel_Data(getDS18B20_Temperature(0));
		//		sendScopeData(1);
		os_wait(K_TMO, 30, 0);
	}
}
void Distance(void)  _task_ 10
{
	for (;;)
	{
	updateDistance(US_100_1);
	DataScope_Get_Channel_Data( getdistance(US_100_1), 1);
 	sendScopeData(1);
	os_wait(K_TMO, 100, 0);
	}
}
//时间更新进程，频率5hz
void TimeUpdate(void) _task_ TIME_UPDATE
{
	for (;;)
	{

		os_wait(K_IVL, 200, 0);
	}
}
//温度计数值更新进程，频率10hz
void  TemperatureUpdata(void) _task_ TEMPERATURE_UPDATE
{
	for (;;)
	{


		os_wait(K_IVL, 100, 0);

	}
}
//键盘按键声发出进程，频率50hz
void ButtonSound(void) _task_ BUTTON_SOUND
{
	for (;;)
	{
		if (getButtonNum())
		{
			buzzWait();
		}
		os_wait(K_IVL, 20, 0);
	}

}
//按键扫描进程，50hz
void ButtonStateUpdate(void) _task_ BUTTON_SCAN
{
	for (;;)
	{
		buttonScan();


		os_wait(K_IVL, 20, 0);

	}

}

