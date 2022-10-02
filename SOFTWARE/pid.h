#ifndef PID_H_
#define PID_H_
#include "sys.h"
#define P 200.0
#define I 0
#define D -100.0

u16 Deriv_Control_L(float target_vel,float cont_vel,int max_Effort);
u16 Deriv_Control_R(float target_vel,float cont_vel,int max_Effort);
#endif