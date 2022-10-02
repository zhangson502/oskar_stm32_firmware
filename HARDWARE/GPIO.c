#include "GPIO.h"
  /**************************************************************************
By：AppleZhang Modified From OskarBot
@csdnID: z824074989y
**************************************************************************/


void Init_Power(void)
{
	/*********************************************
								电源管理管脚初始化：
								PC0---Main Power
								PC14--Main Output
								PC15--5V Output
								PC1---PBTN DETECT
	**********************************************/
	//初始化输出
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_14|GPIO_Pin_15;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(GPIOC, &GPIO_InitStructure);	
	GPIO_ResetBits(GPIOC, GPIO_Pin_15|GPIO_Pin_14);
	//初始化输入
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
}