
#include "servo.h"

servoPWM_t servoPWM = 
{
	1500,
	1500,
	1500,
	1500,
	1500,
	1500,
	1500,
	1500
};

void TIM3_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
  // 输出比较通道1和2 GPIO 初始化
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	// 输出比较通道3和4 GPIO 初始化
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0 | GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	
	// 开启定时器时钟,即内部时钟CK_INT=72M
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

/*--------------------时基结构体初始化-------------------------*/
	// 配置周期，这里配置为20ms
	
	// 自动重装载寄存器的值，累计TIM_Period+1个频率后产生一个更新或者中断
	TIM_TimeBaseStructure.TIM_Period = SERVO_PWM_RESOLUTION;	
	TIM_TimeBaseStructure.TIM_Prescaler = SERVO_TIM_PSC_APB1;
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	/*--------------------输出比较结构体初始化-------------------*/	
	
	
	// 配置为PWM模式1
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// 输出使能
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// 输出通道电平极性配置	
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	
	// 输出比较通道 1
	TIM_OCInitStructure.TIM_Pulse = SERVO_DEFAULT_DUTY;
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
	
	// 输出比较通道 2
	TIM_OCInitStructure.TIM_Pulse = SERVO_DEFAULT_DUTY;
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
	
	// 输出比较通道 3
	TIM_OCInitStructure.TIM_Pulse = SERVO_DEFAULT_DUTY;
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
	
	// 输出比较通道 4
	TIM_OCInitStructure.TIM_Pulse = SERVO_DEFAULT_DUTY;
	TIM_OC4Init(TIM3, &TIM_OCInitStructure);
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);
	
	// 使能计数器
	TIM_Cmd(TIM3, ENABLE);
}

void TIM8_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
  // 输出比较通道GPIO 初始化
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_TIM8, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
	
 	// 开启定时器时钟,即内部时钟CK_INT=72M
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);

/*--------------------时基结构体初始化-------------------------*/
	// 配置周期，这里配置为20ms
	
	// 自动重装载寄存器的值，累计TIM_Period+1个频率后产生一个更新或者中断
	TIM_TimeBaseStructure.TIM_Period = SERVO_PWM_RESOLUTION;	
	// 驱动CNT计数器的时钟 = Fck_int/(psc+1)
	TIM_TimeBaseStructure.TIM_Prescaler = SERVO_TIM_PSC_APB2;	
	// 时钟分频因子 ，配置死区时间时需要用到
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
	// 计数器计数模式，设置为向上计数
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
	// 重复计数器的值，没用到不用管
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	// 初始化定时器
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);

	/*--------------------输出比较结构体初始化-------------------*/	
	
	
	// 配置为PWM模式1
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// 输出使能
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// 输出通道电平极性配置	
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	
	// 输出比较通道 1
	TIM_OCInitStructure.TIM_Pulse = SERVO_DEFAULT_DUTY;
	TIM_OC1Init(TIM8, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);
	
	// 输出比较通道 2
	TIM_OCInitStructure.TIM_Pulse = SERVO_DEFAULT_DUTY;
	TIM_OC2Init(TIM8, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);
	
	// 输出比较通道 3
	TIM_OCInitStructure.TIM_Pulse = SERVO_DEFAULT_DUTY;
	TIM_OC3Init(TIM8, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable);
	
	// 输出比较通道 4
	TIM_OCInitStructure.TIM_Pulse = SERVO_DEFAULT_DUTY;
	TIM_OC4Init(TIM8, &TIM_OCInitStructure);
	TIM_OC4PreloadConfig(TIM8, TIM_OCPreload_Enable);
	
	// 使能计数器
	TIM_Cmd(TIM8, ENABLE);
	
	// 主输出使能，当使用的是通用定时器时，这句不需要
	TIM_CtrlPWMOutputs(TIM8, ENABLE);
}

// 舵机初始化
void Servo_Init(void)
{
	// 初始化PWM定时器
	TIM3_Init();
	TIM8_Init();
	
	Set_Servo_PWM(1, 1500);
	Set_Servo_PWM(2, 1500);
	Set_Servo_PWM(3, 1500);
	Set_Servo_PWM(4, 1500);
	Set_Servo_PWM(5, 1500);
	Set_Servo_PWM(7, 1500);
	Set_Servo_PWM(8, 1500);
}

/**
  * @brief 通过占空比[0,1]来设置舵机PWM值, 舵机PWM范围500us ~ 2500us, 
	* 这里对应占空比0 ~ 1, 即0表示500us, 1表示2500us, 其他值按比例计算, 舵机通道取值范围1 ~ 8
  * @param    channel: 1~8, servo pwm duty range: 500us ~ 2500us, duty: 0~1
  * @retval None
  */
uint16_t Duty_to_PWM(float duty)
{
	return 2000 * duty + 500;
}


/**
* @brief 直接设置舵机PWM值, 舵机PWM范围500us ~ 2500us, 中值:1500us, 舵机通道取值范围1 ~ 8
  * @param    channel: 1~8, servo pwm duty range: 500us ~ 2500us
  * @retval None
  */
void Set_Servo_PWM(uint8_t channel, uint16_t pwm)
{
	TIM_TypeDef *tim;
	if(channel > 8)
	{
		return;
	}
	
	// 如果PWM值不在区间[500,2500]内,则不处理
	if(pwm > 2500)
	{
		return;
	}
	else if(pwm < 500)
	{
		return;
	}
	
	if(channel > 4)
	{
		tim = TIM8;
		channel -= 4;
	}
	else
	{
		tim = TIM3;
	}
	
	switch(channel)
	{
		case 1: tim->CCR1 = pwm; break;
		case 2: tim->CCR2 = pwm; break;
		case 3: tim->CCR3 = pwm; break;
		case 4: tim->CCR4 = pwm; break;
		
		default:
			break;
	}
}

// 舵机释力
void Relax_Servo(uint8_t channel)
{
	TIM_TypeDef *tim;
	
	if(channel > 8)
	{
		return;
	}
	
	switch(channel)
	{
		case 1: servoPWM.servo1 = 0; break;
		case 2: servoPWM.servo2 = 0; break;
		case 3: servoPWM.servo3 = 0; break;
		case 4: servoPWM.servo4 = 0; break;
		case 5: servoPWM.servo5 = 0; break;
		case 6: servoPWM.servo6 = 0; break;
		case 7: servoPWM.servo7 = 0; break;
		case 8: servoPWM.servo8 = 0; break;
		
		default:
			break;
	}
	
	
	if(channel > 4)
	{
		tim = TIM8;
		channel -= 4;
	}
	else
	{
		tim = TIM3;
	}
	
	switch(channel)
	{
		case 1: tim->CCR1 = 0; break;
		case 2: tim->CCR2 = 0; break;
		case 3: tim->CCR3 = 0; break;
		case 4: tim->CCR4 = 0; break;
		
		default:
			break;
	}
}


// 舵机PWM占空比预处理,使PWM值处于[0,1]之间
void PWM(float *duty)
{
	if(*duty > 1)
	{
		*duty = 1;
	}
	else if(*duty < 0)
	{
		*duty = 0;
	}
}

/*********************************************END OF FILE**********************/
