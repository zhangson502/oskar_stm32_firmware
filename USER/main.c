#include "stm32f10x.h"
#include "sys.h"
  /**************************************************************************
By£ºAppleZhang Modified From OskarBot
@csdnID: z824074989y
**************************************************************************/
int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	Init_Power();
	POWER_ON;
	Buzzer_Init();
	Servo_Init();
	Adc_Init();
	Beep_OK();
	Usart_Init();
	UART_CH2_Init();
	Init_Control_Timer();
	//delay_ms(5000);
	while(1)
	{
		delay_ms(100);
	} 
}

