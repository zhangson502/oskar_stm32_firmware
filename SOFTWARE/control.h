#ifndef __CONTROL_H
#define __CONTROL_H
#include "sys.h"
  /**************************************************************************
By£ºAppleZhang Modified From OskarBot
@csdnID: z824074989y
**************************************************************************/
#define MAINLOOP_INTERVAL_MS 20
#define BAT_CHECK_INTERVAL 10
#define SONAR_CHECK_INTERVAL 4
#define HEAD_CTRL_INTERVAL 4
#define POWER_KEY_CHECK_INTERVAL 10
#define USART_MAX_LOOP 1000/MAINLOOP_INTERVAL_MS

#define CPU_LED PCout(13)
#define CPU_BUSY_LED 0
#define CPU_FREE_LED 1

void Init_Control_Timer(void);
void MainLoop_Control(void);
void Init_CPU_Usage_Indicator_LED(void);

#endif