#include "../TASK/TASK.h"
#include <rtx51tny.h>                 /* RTX-51 tiny functions & defines      */
#include <stdio.h>
#include <stdlib.h>
#include "../TASK/setup.h"
#include "../../HARDWARE/DEVICES/BUTTON/BUTTON.H"
#include "../../HARDWARE/DEVICES/LED/LED.H"
#include "../../HARDWARE/DEVICES/TM1638/TM1638.H"
#include "../../HARDWARE/BSP/USART1.H"
#include "../HARDWARE/DEVICES/SENSOR/ANGLE/ANGLE.h"
#include "../COMMON_SOFTWARE/DATA_SCOPE/DataScope_DP.h"
#include "../COMMON_SOFTWARE/STORAGE/STORAGE.h"

void taskStart() _task_ 0
{ 
	setup();
	TM1638LedDisplay(1,2,3,4,5,6,7,8);
	blink(4);
	//os_create_task(1);
	//os_create_task(2);
	//os_create_task(3);
	os_create_task(4);
	os_delete_task(0);

}
void task1(void) _task_ 1
{
	unsigned char button;
	while(1)
	{
		button = ButtonNum();
		switch (button) 
		{ 
			case 1: 
			PrintString1("a"); 
			break; 
			case 2 : 
			PrintString1("b");
			break; 
			case 3 : 
			PrintString1("c");
			break; 
			case 4 : 
			PrintString1("d");
			break; 
			case 5 : 
			PrintString1("e");
			break; 
			case 6 : 
			PrintString1("f");
			break;  
			case 7 : 
			PrintString1("g");
			break; 
			case 8 : 
			PrintString1("h");
			break;  
			case 9: 
			PrintString1("i"); 
			break; 
			case 10 : 
			PrintString1("j");
			break; 
			case 11 : 
			PrintString1("k");
			break; 
			case 12 : 
			PrintString1("l");
			break; 
			case 13 : 
			PrintString1("m");
			break; 
			case 14 : 
			PrintString1("n");
			break;  
			case 15: 
			PrintString1("o");
			break; 
			case 16 : 
			PrintString1("p");
			break;  
			default : 
			break;
		}
	}
}
void task2(void) _task_ 2
{
	while(1)
	{
		TM1638LedDisplay(1,2,3,4,5,6,7,8);
	}
}
void task3(void) _task_ 3
{
	while(1)
	ButtonNum();
}
void task4(void) _task_ 4
{
	unsigned char LEDvalue[8] = {0},key;
	unsigned int count = 0,i;
	while(1)
	{
		key = getButtonNum();
		if(key)
		{
			for(i = count;i > 0;i--)LEDvalue[i] = LEDvalue[i-1];
			LEDvalue[0] = key;
			count++;
			if(count >= 8)count = 0;
		}
		TM1638LedDisplay(LEDvalue[7],LEDvalue[6],LEDvalue[5],LEDvalue[4],LEDvalue[3],LEDvalue[2],LEDvalue[1],LEDvalue[0]);
	}
}
void task5(void) _task_ 5
{
	unsigned long count = 0;
	for (;;)
	{

		buttonScan();
		os_wait(K_IVL, 2, 0);
	}
}

void task7(void) _task_ 7
{
	for (;;)
	{
		if (getButtonState(BUTTON1_GPIO_PIN))
		{
			open_Board_LED();
		}
	
		os_wait(K_IVL, 10, 0);
	}
}
void task8(void) _task_ 8
{
	for (;;)
	{
		if (getAngle(1) > 50)
		{
			open_Board_LED();
		}
		else
		{
			close_Board_LED();
		}
		os_wait(K_IVL, 1, 0);
	}
}
void task9(void) _task_ 9
{
	for (;;)
	{
		sendScopeData(getAngle(1), 1);
		os_wait(K_IVL, 40, 0);

	}

}

