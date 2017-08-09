#include "PH.H"

typedef struct
{
	float k;
	float b;
}Equation;

static Equation PH[PH_NUM];

/*************************************************
* 函数名称:void    PH_config(u8 pin,u8 speed)
* 描述: 初始化PH传感器模块的adc
* 输入：u8 pin:需要使用的adc引脚
*       u8 speed: adc的转换速度
* 其他说明:
pin:
                 ADC_P10
                 ADC_P11
                 ADC_P12
                 ADC_P13
                 ADC_P14
                 ADC_P15
                 ADC_P16
                 ADC_P17
speed:
                 ADC_90T
                 ADC_180T
                 ADC_360T
                 ADC_540T
*************************************************/
void PH_config(u8 pin, u8 speed)
{
    ADC_InitTypeDef     ADC_InitStructure;
    ADC_InitStructure.ADC_Px = pin;
    ADC_InitStructure.ADC_Speed = speed;
    ADC_InitStructure.ADC_Power = ENABLE;
    ADC_InitStructure.ADC_AdjResult = ADC_RES_H8L2;
    ADC_InitStructure.ADC_Polity = PolityLow;
    ADC_InitStructure.ADC_Interrupt = DISABLE;
    ADC_Inilize(&ADC_InitStructure);
}

void setPHCoefficient(u8 PH_N,float k,float b)
{
	PH[PH_N].k = k;
	PH[PH_N].b = b;
}

float getPHvalue(u8 PH_N,bit whichPHvalue)
{
	u16 PHvalue;
	u8  PHvalueTime = 0;
	static float presentPH, lastPH;  //此函数还可以返回上一次的PH值，不需要读取时间 ，是静态的数据，因为需要保存
	if (whichPHvalue)  //返回当前结果
	{
		for(PHvalueTime = 0; PHvalueTime < 10; PHvalueTime++) //读取10次数据并保存在数组中
		{
			PHvalue = Get_ADC10bitResult(ADC_CH0);
		}
		presentPH = PHvalue / (float)PHvalueTime;
		lastPH = presentPH;
		return presentPH;
	}
	else  //返回上一次PH值结果
  {
		return  lastPH;
	}
}