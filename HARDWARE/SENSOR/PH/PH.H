#ifndef __PH_H__
#define __PH_H__

#include "../../COMMON_HARDWARE/common_HD.h"

#define PH_NUM 2
#define PH_1 0
#define PH_2 1

void PH_config(u8 pin, u8 speed);
void setPHCoefficient(u8 PH_N,float k,float b);
float getPHvalue(u8 PH_N,bit whichPHvalue);

#endif