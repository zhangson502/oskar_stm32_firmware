#ifndef __USRAT3_H
#define __USRAT3_H 
#include "sys.h"	  	
  /**************************************************************************
By���ŵ���ɡ
��ӭ�����ҵĲ��ͣ�http://blog.sina.com/deyubooke
**************************************************************************/
extern u8 Usart3_Receive;
void uart3_init(u32 bound);
void USART3_IRQHandler(void);
#endif

