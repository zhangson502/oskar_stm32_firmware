#ifndef __ADC_H
#define __ADC_H	
#include "sys.h"

#define Battery_Ch ADC_Channel_5
void Adc_Init(void);
u16 Get_Adc(u8 ch);
uint8_t Get_battery_volt(void);   

extern float V[10],VV;
extern u8 bat_Percentage;

#define BAT_MODEL_A 1
#define BAT_MODEL_B 0
#define MIN_VAL 11.5
#define MAX_VAL 12.6

#endif 















