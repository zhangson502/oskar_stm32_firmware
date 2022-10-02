#include "adc.h"



float V[10],VV;
u8 bat_Percentage;

void  Adc_Init(void)
{    
	ADC_InitTypeDef ADC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC |RCC_APB2Periph_ADC1	, ENABLE );	 //Enable ADC1
	//GPIO configure
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;	
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
	//ADC Configure
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //72/6=12MHz, ADC Clock could not exceed 14MHz  
	ADC_DeInit(ADC1);  
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//Disable Multi channels
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//Disable continous mode
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//Do not triggered by EXTI or timer
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//Right Aligned(Lower bits rightforward)
	ADC_InitStructure.ADC_NbrOfChannel = 1;	//Channel sequences
	ADC_Init(ADC1, &ADC_InitStructure);	  
	ADC_Cmd(ADC1, ENABLE);
	//ADC reset and calibration
	ADC_ResetCalibration(ADC1);	 	 
	while(ADC_GetResetCalibrationStatus(ADC1));	
	ADC_StartCalibration(ADC1);	
	while(ADC_GetCalibrationStatus(ADC1));
}		


u16 Get_Adc(u8 ch)   
{
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5 );	//239.5 Cycles  			     
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//Start ADC convertion		 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//Wait until finish
	return ADC_GetConversionValue(ADC1);	//Get The last convertion
}


/**************************************************************************

		Get Battery Voltage
		MCU: 3.3V  Volt Sepetation: 100K(Total)  20K(Down)/20%  80K(Up) 80%
		
**************************************************************************/
uint8_t Get_battery_volt(void)   
{  
	static float Volt;
	static uint8_t PER;
	Volt=Get_Adc(Battery_Ch)*3.3*105.1/(5.1*4096);	
	PER=100*(Volt-MIN_VAL)/(MAX_VAL-MIN_VAL);
	return PER;
}



