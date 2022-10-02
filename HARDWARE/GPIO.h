#ifndef __LED_H
#define __LED_H
#include "sys.h"
  /**************************************************************************
By£ºAppleZhang Modified From OskarBot
@csdnID: z824074989y
**************************************************************************/
//LED ¶Ë¿Ú¶¨Òå
#define LED_1 PAout(2) 
#define LED_2 PAout(3) 
void LED_Init(void); 
void Led_Flash(u16 time);
void Init_Power(void);

#define POWER_KEY_STATUS	GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_1)
#define ADJ_OUTPUT_ON				GPIO_SetBits(GPIOC, GPIO_Pin_15)
#define ADJ_OUTPUT_OFF			GPIO_ResetBits(GPIOC, GPIO_Pin_15)

#define MAIN_OUTPUT_ON			GPIO_SetBits(GPIOC, GPIO_Pin_14)
#define MAIN_OUTPUT_OFF			GPIO_ResetBits(GPIOC, GPIO_Pin_14)

#define POWER_ON						GPIO_SetBits(GPIOC, GPIO_Pin_0)
#define POWER_OFF						GPIO_ResetBits(GPIOC, GPIO_Pin_0)

#endif
