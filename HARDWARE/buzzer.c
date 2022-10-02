#include "sys.h"
const uint16_t tone[] = {247,262,294,330,349,392,440,294,523,587,659,698,784,1000};

// �쳾���,������
const uint8_t music[] = {5,5,6,8,7,6,5,6,13,13,
									5,5,6,8,7,6,5,3,13,13,
									2,2,3,5,3,5,6,3,2,1,
									6,6,5,6,5,3,6,5,13,13,

									5,5,6,8,7,6,5,6,13,13,
									5,5,6,8,7,6,5,3,13,13,
									2,2,3,5,3,5,6,3,2,1,
									6,6,5,6,5,3,6,1,	

									13,8,9,10,10,9,8,10,9,8,6,
									13,6,8,9,9,8,6,9,8,6,5,
									13,2,3,5,5,3,5,5,6,8,7,6,
									6,10,9,9,8,6,5,6,8};

// �쳾���,���ı�
const uint8_t time[] = {2,4,2,2,2,2,2,8,4, 4,
									2,4,2,2,2,2,2,8,4, 4, 
									2,4,2,4,2,2,4,2,2,8,
									2,4,2,2,2,2,2,8,4 ,4, 

									2,4,2,2,2,2,2,8,4, 4, 
									2,4,2,2,2,2,2,8,4, 4, 
									2,4,2,4,2,2,4,2,2,8,
									2,4,2,2,2,2,2,8,

									4, 2,2,2, 4, 2,2,2, 2,2,8,
									4, 2,2,2,4,2,2,2,2,2,8,
									4, 2,2,2,4,2,2,5,2,6,2,4,
									2,2 ,2,4,2,4,2,2,12};	

int music_len = sizeof(music)/sizeof(music[0]);
int music_index = 0;
									
void Buzzer_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	// ����Ƚ�ͨ��1 GPIO ��ʼ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1 | RCC_APB2Periph_GPIOA, ENABLE); 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
	// ������ʱ��ʱ��,���ڲ�ʱ��CK_INT = 72M
	//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

	/*--------------------ʱ���ṹ���ʼ��-------------------------*/
	// �������ڣ���������Ϊ1K
	
	// �Զ���װ�ؼĴ�����ֵ���ۼ�TIM_Period+1��Ƶ�ʺ����һ�����»����ж�
	TIM_TimeBaseStructure.TIM_Period = 999;	
	// ����CNT��������ʱ�� = Fck_int/(psc+1)
	TIM_TimeBaseStructure.TIM_Prescaler = 71;	
	// ʱ�ӷ�Ƶ���� ����������ʱ��ʱ��Ҫ�õ�
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;		
	// ����������ģʽ������Ϊ���ϼ���
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;		
	// �ظ���������ֵ��û�õ����ù�
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;	
	// ��ʼ����ʱ��
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

	/*--------------------����ȽϽṹ���ʼ��-------------------*/	
	
	// ����ΪPWMģʽ1
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// ���ʹ��
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable; 
	// ���ͨ����ƽ��������	
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	// ���ͨ�����е�ƽ��������
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
	
	// ����Ƚ�ͨ�� 1
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);
	
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
	
	
	TIM_ClearFlag(TIM1, TIM_FLAG_Update);//���TIM�ĸ��±�־λ
	TIM_ITConfig(TIM1, TIM_IT_Update, DISABLE);
	
	
	// �����ʹ�ܣ���ʹ�õ���ͨ�ö�ʱ��ʱ����䲻��Ҫ
	TIM_CtrlPWMOutputs(TIM1, DISABLE);
	
	// ʹ�ܼ�����
	TIM_Cmd(TIM1, DISABLE);
	
	
//	TIM6_Init();
}


// ����Ƶ�ʱ�





void Play_Tone(u8 i,int delays)
{
	if(i==0)
	{
		delay_ms(delays);
		return;
	}
	//��ʼ����
	TIM1->ARR = 1000000 / tone[i];
	TIM1->CCR1 = tone[i];
	TIM_SetCounter(TIM1, 0);
	TIM_Cmd(TIM1, ENABLE);
	TIM_CtrlPWMOutputs(TIM1, ENABLE);
	delay_ms(delays);
	TIM_SetCounter(TIM1, 0);
	TIM_Cmd(TIM1, DISABLE);
	TIM_CtrlPWMOutputs(TIM1, DISABLE);
}	
void Beep_OK()
{
	Play_Tone(3,100);
	Play_Tone(5,100);
	Play_Tone(7,100);
}
void Beep_Poweroff()
{
	Play_Tone(5,100);
	Play_Tone(3,100);
	Play_Tone(1,100);
}
void Beep_Usart_Error()
{
		Play_Tone(10,50);
}

void Beep_Encoder_Error()
{
}

void PlayMusic(void *param)
{
	music_index = 0;
	
	TIM_SetCounter(TIM1, 0);
	TIM_Cmd(TIM1, ENABLE);
	TIM_CtrlPWMOutputs(TIM1, ENABLE);
	
	while(1)
	{
//		printf(">>PlayMusic Task...\r\n");
		
		if(music_index < music_len)
		{
			TIM1->ARR = 1000000 / tone[music[music_index]];
			TIM1->CCR1 = tone[music[music_index]];
			
			TIM_SetCounter(TIM1, 0);
			TIM_Cmd(TIM1, ENABLE);
			TIM_CtrlPWMOutputs(TIM1, ENABLE);
			
			delay_ms(100 * time[music_index]);
			
			TIM_SetCounter(TIM1, 0);
			TIM_Cmd(TIM1, DISABLE);
			TIM_CtrlPWMOutputs(TIM1, DISABLE);
			
			music_index++;
		}
		else
		{
			TIM_SetCounter(TIM1, 0);
			TIM_Cmd(TIM1, DISABLE);
			TIM_CtrlPWMOutputs(TIM1, DISABLE);
			
			delay_ms(1000);
			
			music_index = 0;
		}
	}
	
}

