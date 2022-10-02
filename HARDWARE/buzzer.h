#ifndef __BUZZER_H
#define	__BUZZER_H


#include "stm32f10x.h"


#define BUZZER_ON         GPIO_SetBits(GPIOA, GPIO_Pin_8)
#define BUZZER_OFF        GPIO_ResetBits(GPIOA, GPIO_Pin_8)
#define TOGGLE_BUZZER     GPIOA->ODR ^= GPIO_Pin_8;


void Buzzer_Init(void);

void Play_Tone(u8 i,int delays);
void PlayMusic(void *param);

void Beep_OK(void);
void Beep_Usart_Error(void);
void Beep_Encoder_Error(void);
void Beep_Poweroff(void);

#endif /* __BUZZER_H */
