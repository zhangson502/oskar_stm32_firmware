#include "control.h"	

int tp_l,tp_r;		//	Target Power


void Init_Control_Timer()
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	TIM_TimeBaseStructInit(&TIM_TimeBaseInitStructure);
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	/********************************************************************
	Set the timer prescaler to 7200-1, which means the counting freq is:	
						7200/72000000=10000Hz / interval 0.1ms
	********************************************************************/
	TIM_TimeBaseInitStructure.TIM_Prescaler=7200-1;
	// 						Timer reload(interrupt) interval is:
	//    t=0.1ms*10*MAINLOOP_INTERVAL_MS=MAINLOOP_INTERVAL_MS(ms)
	TIM_TimeBaseInitStructure.TIM_Period=MAINLOOP_INTERVAL_MS*10;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
	//Configure timer interrupt handler
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM2,ENABLE);
	
	//NVIC configuration(Interrupt priority)

	NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x00;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
void Init_CPU_Usage_Indicator_LED(void)
{/*
	int i;
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	CPU_LED=CPU_FREE_LED;
	for(i=0;i<4;i++){
		CPU_LED=~CPU_LED;
		delay_ms(200);
	}*/
}
void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET)
	{
		MainLoop_Control();
	}
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
}
/*****************************************************************************************************************
						This is the main loop of MCU, processing encoders, IMUs, sonars, motors and other utilities 
******************************************************************************************************************/
void MainLoop_Control()
{
	static u32 interval_Clock;
}