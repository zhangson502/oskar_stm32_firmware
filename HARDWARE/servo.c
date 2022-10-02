
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
  // ����Ƚ�ͨ��1��2 GPIO ��ʼ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	// ����Ƚ�ͨ��3��4 GPIO ��ʼ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0 | GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	
	// ������ʱ��ʱ��,���ڲ�ʱ��CK_INT=72M
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

/*--------------------ʱ���ṹ���ʼ��-------------------------*/
	// �������ڣ���������Ϊ20ms
	
	// �Զ���װ�ؼĴ�����ֵ���ۼ�TIM_Period+1��Ƶ�ʺ����һ�����»����ж�
	TIM_TimeBaseStructure.TIM_Period = SERVO_PWM_RESOLUTION;	
	TIM_TimeBaseStructure.TIM_Prescaler = SERVO_TIM_PSC_APB1;
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	/*--------------------����ȽϽṹ���ʼ��-------------------*/	
	
	
	// ����ΪPWMģʽ1
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// ���ʹ��
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// ���ͨ����ƽ��������	
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	
	// ����Ƚ�ͨ�� 1
	TIM_OCInitStructure.TIM_Pulse = SERVO_DEFAULT_DUTY;
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
	
	// ����Ƚ�ͨ�� 2
	TIM_OCInitStructure.TIM_Pulse = SERVO_DEFAULT_DUTY;
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
	
	// ����Ƚ�ͨ�� 3
	TIM_OCInitStructure.TIM_Pulse = SERVO_DEFAULT_DUTY;
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
	
	// ����Ƚ�ͨ�� 4
	TIM_OCInitStructure.TIM_Pulse = SERVO_DEFAULT_DUTY;
	TIM_OC4Init(TIM3, &TIM_OCInitStructure);
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);
	
	// ʹ�ܼ�����
	TIM_Cmd(TIM3, ENABLE);
}

void TIM8_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
  // ����Ƚ�ͨ��GPIO ��ʼ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_TIM8, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
	
 	// ������ʱ��ʱ��,���ڲ�ʱ��CK_INT=72M
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);

/*--------------------ʱ���ṹ���ʼ��-------------------------*/
	// �������ڣ���������Ϊ20ms
	
	// �Զ���װ�ؼĴ�����ֵ���ۼ�TIM_Period+1��Ƶ�ʺ����һ�����»����ж�
	TIM_TimeBaseStructure.TIM_Period = SERVO_PWM_RESOLUTION;	
	// ����CNT��������ʱ�� = Fck_int/(psc+1)
	TIM_TimeBaseStructure.TIM_Prescaler = SERVO_TIM_PSC_APB2;	
	// ʱ�ӷ�Ƶ���� ����������ʱ��ʱ��Ҫ�õ�
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
	// ����������ģʽ������Ϊ���ϼ���
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
	// �ظ���������ֵ��û�õ����ù�
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	// ��ʼ����ʱ��
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);

	/*--------------------����ȽϽṹ���ʼ��-------------------*/	
	
	
	// ����ΪPWMģʽ1
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// ���ʹ��
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// ���ͨ����ƽ��������	
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	
	// ����Ƚ�ͨ�� 1
	TIM_OCInitStructure.TIM_Pulse = SERVO_DEFAULT_DUTY;
	TIM_OC1Init(TIM8, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);
	
	// ����Ƚ�ͨ�� 2
	TIM_OCInitStructure.TIM_Pulse = SERVO_DEFAULT_DUTY;
	TIM_OC2Init(TIM8, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);
	
	// ����Ƚ�ͨ�� 3
	TIM_OCInitStructure.TIM_Pulse = SERVO_DEFAULT_DUTY;
	TIM_OC3Init(TIM8, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable);
	
	// ����Ƚ�ͨ�� 4
	TIM_OCInitStructure.TIM_Pulse = SERVO_DEFAULT_DUTY;
	TIM_OC4Init(TIM8, &TIM_OCInitStructure);
	TIM_OC4PreloadConfig(TIM8, TIM_OCPreload_Enable);
	
	// ʹ�ܼ�����
	TIM_Cmd(TIM8, ENABLE);
	
	// �����ʹ�ܣ���ʹ�õ���ͨ�ö�ʱ��ʱ����䲻��Ҫ
	TIM_CtrlPWMOutputs(TIM8, ENABLE);
}

// �����ʼ��
void Servo_Init(void)
{
	// ��ʼ��PWM��ʱ��
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
  * @brief ͨ��ռ�ձ�[0,1]�����ö��PWMֵ, ���PWM��Χ500us ~ 2500us, 
	* �����Ӧռ�ձ�0 ~ 1, ��0��ʾ500us, 1��ʾ2500us, ����ֵ����������, ���ͨ��ȡֵ��Χ1 ~ 8
  * @param    channel: 1~8, servo pwm duty range: 500us ~ 2500us, duty: 0~1
  * @retval None
  */
uint16_t Duty_to_PWM(float duty)
{
	return 2000 * duty + 500;
}


/**
* @brief ֱ�����ö��PWMֵ, ���PWM��Χ500us ~ 2500us, ��ֵ:1500us, ���ͨ��ȡֵ��Χ1 ~ 8
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
	
	// ���PWMֵ��������[500,2500]��,�򲻴���
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

// �������
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


// ���PWMռ�ձ�Ԥ����,ʹPWMֵ����[0,1]֮��
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
