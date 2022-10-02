#include "sys.h"
#include "usart.h"	  


u8 rx_pack_State,tx_pack_State;	//Data Receive State in USART[0: processing head 1:processing body]
u8 rx_pack_Addr,tx_pack_Addr;		//How many bits in a pack had been reveiced
u8 rx_Data[256],tx_Data[256];		//All data in tx/rx packs
u8 rx_pack_Len,tx_pack_Len;			//Pack length(HEAD included)
u8 rx_pack_Cmd,tx_pack_Cmd;			//Pack Commands
u8 usart_Delay;			
uint8_t temp[10];	//�����ֽ�
//USARTͨѶ�������ʱ���ػ����ƴ��������������ֵû���յ���Ϣ��usart������
/*****************************************
				��ʼ������1����
				֧�ִ���1 �Ի����˵Ŀ���
******************************************/
void Usart_Init()
{
  GPIO_InitTypeDef GPIO_InitStructure;	//Configure GPIO PA9--TX  PA10--RX
	USART_InitTypeDef USART_InitStructure;//Configure USART
	NVIC_InitTypeDef NVIC_InitStructure;	//Configure Interrupt Prorioty
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA,ENABLE);
	//PA9--TX:AF_PP PA10--RX:IN_FLOATING
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	//USART_Initialize
	USART_InitStructure.USART_BaudRate=9600;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_InitStructure.USART_Parity=USART_Parity_No;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	USART_Init(USART1,&USART_InitStructure);
	//Open USART
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	USART_Cmd(USART1,ENABLE);
	//Configure NVIC
	NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x00;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x00;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure); 
	rx_pack_Addr=tx_pack_State=0;
	rx_pack_State=tx_pack_State=PROCESSING_HEAD;
	usart_Delay=0;
}
/*****************************************
				��ʼ������3����
				֧�ִ���3 �Ի����˵Ŀ���
******************************************/
void UART_CH2_Init()
{
	
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	USART_ClockInitTypeDef USART_ClockInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	// �򿪴���GPIO�ʹ��������ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);

	// ��USART Tx��GPIO����Ϊ���츴��ģʽ
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

  // ��USART Rx��GPIO����Ϊ��������ģʽ
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	// ���ô��ڵĹ�������
	// ���ò�����
	USART_InitStructure.USART_BaudRate = 9600;
	// ���� �������ֳ�
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	// ����ֹͣλ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	// ����У��λ
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	// ����Ӳ��������
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	// ���ù���ģʽ���շ�һ��
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	// ��ɴ��ڵĳ�ʼ������
	USART_Init(UART4, &USART_InitStructure);
	
	USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;          // SCLKʱ������(ͬ��ģʽ����Ҫ)
	USART_ClockInitStructure.USART_CPOL = USART_CPOL_Low;                // ʱ�Ӽ���(ͬ��ģʽ����Ҫ)
	USART_ClockInitStructure.USART_CPHA = USART_CPHA_2Edge;              // ʱ����λ(ͬ��ģʽ����Ҫ)
	USART_ClockInitStructure.USART_LastBit = USART_LastBit_Disable;      // ���һλʱ������(ͬ��ģʽ����Ҫ)
	USART_ClockInit(UART4, &USART_ClockInitStructure);
	
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
	NVIC_Init(&NVIC_InitStructure); 

	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);

	// ʹ�ܴ���
	USART_Cmd(UART4, ENABLE);
	rx_pack_Addr=tx_pack_State=0;
	rx_pack_State=tx_pack_State=PROCESSING_HEAD;
  usart_Delay=0;
	MAIN_OUTPUT_ON;delay_ms(100);MAIN_OUTPUT_OFF;delay_ms(100);MAIN_OUTPUT_ON;delay_ms(100);MAIN_OUTPUT_OFF;delay_ms(100);MAIN_OUTPUT_ON;
}
// ����4�ж�, �ӿ����ź�CH4
void UART4_IRQHandler()
{
	
	static uint8_t i=0;				//�����ַƫ��
	//USART_ClearFlag(UART4,USART_FLAG_TC);	//Clear Tx flags.
	if(USART_GetITStatus(UART4, USART_IT_RXNE)!=RESET)
	{
		temp[i++]=USART_ReceiveData(UART4);
		if(i>=10)
		{
			if(temp[0]==0xff && temp[1]==0xff)
			{
				for(i=1;i<9;i++)
				{
					//��������
					Set_Servo_PWM(i,(int)(((temp[i+1])/255.0)*(2500.0-500.0)+500.0));
				}
				i=0;
				Usart_Feedback();
			}
			
		}
	}
}
// ����1�ж�, �ӿ����ź�CH1
void USART1_IRQHandler(void)	//USART1 Interrupt Function
{
	static uint8_t i=0;				//�����ַƫ��
	//USART_ClearFlag(UART4,USART_FLAG_TC);	//Clear Tx flags.
	if(USART_GetITStatus(USART1, USART_IT_RXNE)!=RESET)
	{
		temp[i++]=USART_ReceiveData(USART1);
		if(i>=10)
		{
			if(temp[0]==0xff && temp[1]==0xff)
			{
				for(i=1;i<9;i++)
				{
					//��������
					
					Set_Servo_PWM(i,(int)(((temp[i+1])/255.0)*(2500.0-500.0)+500.0));
				}
				i=0;
				//Usart_Feedback();
			}
			
		}
	}
}


/*****************************************
				Process usart commands
******************************************/
void Usart_Process()
{
		
}

void Init_Tx_Data(u8 len,u8 cmdID)
{
	tx_pack_Cmd=cmdID;tx_pack_Len=len;
	tx_Data[0]=tx_Data[1]=0xff;
	tx_Data[2]=len;tx_Data[3]=cmdID;
	usart_Delay=0;
}
void Usart_Feedback()
{

	USART_SendData(UART4,Get_battery_volt());
	while(USART_GetFlagStatus(UART4,USART_FLAG_TXE)==Bit_RESET);	

}

/*
	Error and exception processor
*/
void Process_IO_Error()
{
	UART_CH2_Init();
	Beep_Usart_Error();
}
void Check_CRC()
{
}
