#ifndef __TIMER_H
#define __TIMER_H
#include <sys.h>	 
  /**************************************************************************
By���ŵ���ɡ
��ӭ�����ҵĲ��ͣ�http://blog.sina.com/deyubooke
**************************************************************************/
void TIM3_Cap_Init(u16 arr,u16 psc);
void Read_Distane(void);
void TIM3_IRQHandler(void);
#endif
