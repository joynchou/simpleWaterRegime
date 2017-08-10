#ifndef __VOLTMETER_H__
#define __VOLTMETER_H__

#include "../COMMON_HARDWARE/COMMON_HD.H"

#define VOL_NUM 4
#define REFERENCE_VOLTAGE 3.3
#define VOL_1 0
#define VOL_2 1
#define VOL_3 2
#define VOL_4 3
#define V_2 0
#define V_20 1
#define V_200 2
#define NULL 0

void Voltmeter_config(void);
void setVolUnit(u8 VOL_N,u8 unit);
void openVoltmeter(u8 VOL_N);
void closeVoltmeter(u8 VOL_N);
void openAllVoltmeter(void);
void closeAllVoltmeter(void);
float getVoltageValue(u8 VOL_N);
void VoltageValueScan();

#endif