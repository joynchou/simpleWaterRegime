#ifndef _FILTER_H_
#define _FILTER_H_
#include "../../../../../../HARDWARE/devices.h"
extern float filter(float *ary, u16 num, float MaxValue, float MinValue);
extern double KalmanFilter(const double ResrcData,
double ProcessNiose_Q, double MeasureNoise_R, double InitialPrediction);

float limitingFilter(float value, float A);
float movingAverageFilter(float value);
float shudderingFilter(float value, u16 filter_n);
#endif
