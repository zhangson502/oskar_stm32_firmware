#ifndef __MOTOR_H
#define __MOTOR_H
#include <sys.h>	 



#define PULSE_PER_METER 933



#define MOTOR_PWM_FREQUENCE  10000            // 1000Hz    
#define MOTOR_PWM_RESOLUTION 1000		         // 1ms = 1000us
#define MOTOR_DEFAULT_DUTY 	 0      				 // 0us
#define MOTOR_TIM_PSC_APB1 ((72000000/MOTOR_PWM_FREQUENCE)/MOTOR_PWM_RESOLUTION -1)

extern int encoder_L,encoder_R;
extern int pwm_L,pwm_R;
extern float tar_spd_L,tar_spd_R,spd_L,spd_R;
extern float pid_P,pid_I,pid_D;

void Motor_Init(void);
void Motor_PWM_Init(void);
void Motor_Encoder_Init(void);
void Motor_GPIO_Init(void);
void Control_Wheels(float l,float r);
void Set_PWM(int l,int r);
void Set_Dir(float l,float r);
short Read_Encoder_L(void);
short Read_Encoder_R(void);
float Read_Speed_L(float ctrl_freqs);
float Read_Speed_R(float ctrl_freqs);
#endif
