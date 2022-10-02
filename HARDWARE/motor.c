#include "motor.h"
#include "sys.h"
int encoder_L,encoder_R;
int pwm_L,pwm_R;
float tar_spd_L,tar_spd_R,spd_L,spd_R;
float pid_P,pid_I,pid_D;

void Control_Wheels(float l,float r)
{
	
}

void Motor_Init()
{
	Motor_GPIO_Init();
	Motor_PWM_Init();
	Motor_Encoder_Init();
}
/*
			Initialize GPIO for motor control
*/
void Motor_GPIO_Init()
{
	// TIM4����ͨ����GPIO��ʼ��
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}
void Motor_PWM_Init()
{
	
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	// ������ʱ��ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	// �Զ���װ�ؼĴ�����ֵ���ۼ�TIM_Period+1��Ƶ�ʺ����һ�����»����ж�
	TIM_TimeBaseStructure.TIM_Period = MOTOR_PWM_RESOLUTION;	
	// ����CNT��������ʱ�� = Fck_int/(psc+1)
	TIM_TimeBaseStructure.TIM_Prescaler = MOTOR_TIM_PSC_APB1;	
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

	/*--------------------����ȽϽṹ���ʼ����PWM��ʼ����-------------------*/	
	
	// ����ΪPWMģʽ1
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// ���ʹ��
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// ���ͨ����ƽ��������	
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	
	// ����Ƚ�ͨ�� 1
	TIM_OCInitStructure.TIM_Pulse = MOTOR_DEFAULT_DUTY;
	TIM_OC1Init(TIM4, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
	
	// ����Ƚ�ͨ�� 2
	TIM_OCInitStructure.TIM_Pulse = MOTOR_DEFAULT_DUTY;
	TIM_OC2Init(TIM4, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);
	
	// ����Ƚ�ͨ�� 3
	TIM_OCInitStructure.TIM_Pulse = MOTOR_DEFAULT_DUTY;
	TIM_OC3Init(TIM4, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
	
	// ����Ƚ�ͨ�� 4
	TIM_OCInitStructure.TIM_Pulse = MOTOR_DEFAULT_DUTY;
	TIM_OC4Init(TIM4, &TIM_OCInitStructure);
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);
	// ʹ�ܼ�����
	TIM_Cmd(TIM4, ENABLE);
}
void Motor_Encoder_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	/****EXTI��ʽʵ�ֻ����˱������Ķ�ȡ****/
	//����ʱ�ӿ���
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOA,ENABLE);
	//��ʼ��GPIO
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1|GPIO_Pin_3;	//���������ж�����
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING; //
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_2;	//�����жϲ�������
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD; //
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	/*********************�����ж�*********************
				���֣� PA0���жϲ��񣩣�PA1�������жϣ�
				���֣� PA2���жϲ��񣩣�PA3 (�����ж�)
	***************************************************/
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);	//����
	EXTI_InitStructure.EXTI_Line=EXTI_Line0;	//����
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;	
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource2);	//����
	EXTI_InitStructure.EXTI_Line=EXTI_Line2;	//����
	EXTI_Init(&EXTI_InitStructure);
	/*********************�����ж����ȼ�******************
												������ȼ�
	***************************************************/
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;		
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;			//��ռ���ȼ�2�� 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//�����ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;							//ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStructure); 
	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;		//ʹ�ܰ���key1���ڵ��ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStructure); 
}
void Set_PWM(int l,int r)
{
	//�������ֵ�PWM�Լ����򣨸�ֵ����ת��
	if(l>0)
	{
		TIM4->CCR1=0;TIM4->CCR2=l;
	}
	else if(l<0)
	{
		TIM4->CCR2=0;TIM4->CCR1=-l;
	}
	else
	{
		TIM4->CCR2=0;TIM4->CCR1=0;
	}
	//�������ֵ�PWM�Լ����򣨸�ֵ����ת��
	if(r>0)
	{
		TIM4->CCR4=0;TIM4->CCR3=r;
	}
	else if(r<0)
	{
		TIM4->CCR3=0;TIM4->CCR4=-r;
	}
	else
	{
		TIM4->CCR3=0;TIM4->CCR4=0;
	}
}
void Set_Dir(float l,float r)
{
	
}
short Read_Encoder_R(void)
{
	static int tmp_R;
	int ret;
	ret=encoder_R-tmp_R;
	tmp_R=encoder_R;
	return ret;
}
short Read_Encoder_L(void)
{
	static int tmp_L;
	int ret;
	ret=encoder_L-tmp_L;
	tmp_L=encoder_L;
	return ret;
}
float Read_Speed_L(float ctrl_freqs)
{
}
float Read_Speed_R(float ctrl_freqs)
{
}


/****************************************************************
											�жϺ�����ȡ������
*****************************************************************/
void EXTI0_IRQHandler(void)
{
	//��ȡ���ֱ���������
	if(EXTI_GetITStatus(EXTI_Line0)==1)
	{
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)) encoder_L--;
		else encoder_L++;
	}
	
	EXTI_ClearITPendingBit(EXTI_Line0); 
}
void EXTI2_IRQHandler(void)
{
	//��ȡ���ֱ���������
	/****�Ҳ�������෽��ͬ��Ҫȡ��****/
	if(EXTI_GetITStatus(EXTI_Line2)==1)
	{
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3)) encoder_R++;
		else encoder_R--;
	}
	
	EXTI_ClearITPendingBit(EXTI_Line2); 
}