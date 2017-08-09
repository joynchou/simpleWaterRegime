#include <stdio.h>
#include <stdlib.h>
#include "TASK/task.h"
void taskStart() _task_ 0
{
	setup();
	blink(4);
	//os_create_task(1);
	//os_create_task(2);
	os_create_task(3);
	//os_create_task(4);
 	//os_create_task(12);
	//os_create_task(13);
	//os_create_task(14);
	PrintString1("Setup is ok!\n");
	os_delete_task(0);
}

void task1(void) _task_ 1
{
	openAllPhotoEleMod();
	while(1)
	{
		PhotoElectricScan();
		os_wait(K_TMO,5,0);
	}
}

void task2(void) _task_ 2
{
	while(1)
	{
		if(getPhotoEleState(PHOTOELE_1) == 1)
			PrintString1("Code is no problem!\n");
	}
}

void task3(void) _task_ 3
{
	u8 date[30];
	ChoiceHalfDuplexMode(RX_MODE);
	while(1)
	{
		nRF24L01_RxPacket(date);
		PrintString1(date);
		os_wait(K_TMO,5,0);
	}
}

void task4(void) _task_ 4
{
	u8 date[128],i;
	u16 a[7] = {2,4,51,24,56,7,8};
	ChoiceHalfDuplexMode(TX_MODE);
	while(1)
	{
		sprintf(date,"%d %d %d %d %d %d %d\n",a[0],a[1],a[2],a[3],a[4],a[5],a[6]);
		nRF24L01_TxPacket(date);
		//PrintString1(date);
		os_wait(K_TMO,250,0);
		os_wait(K_TMO,250,0);
		os_wait(K_TMO,250,0);
		os_wait(K_TMO,250,0);
		for(i = 0;i < 7;i++)
		{
			a[i] += 3;
		}
	}
}

void task13(void) _task_ 13
{
	while(1)
	{
	  ReadTemperature();		
		os_wait(K_TMO,5,0);
	}
}

void task14(void) _task_ 14
{
	u16 tempValue;
	u8 value[30];
	while(1)
	{
		tempValue = getTemperatureInteger();
		sprintf(value,"%d\n",tempValue);
		PrintString1(value);
		os_wait(K_TMO,5,0);
	}
}