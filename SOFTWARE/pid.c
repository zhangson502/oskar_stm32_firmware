#include "pid.h"

u16 Deriv_Control_L(float target_vel,float cont_vel,int max_Effort)
{
	/*
					PID velocity control:
					target_vel:target velocity
					cont_vel: content velocity
					max_Effort: maximum safety PWM value
	*/
	static float vels[3],diffs[3];			//N-dimension vels supports N-1 order derivatives
	static float p_effort,i_effort,d_effort,total_Effort;
	static int Power;
	vels[0]=cont_vel;
	
	diffs[0]=target_vel-vels[0];		//0 order, Pure P value
	diffs[1]=vels[0]-vels[1];				//1 order, D value
	
	p_effort=diffs[0]*P;
	i_effort=(0)*I;
	d_effort=diffs[1]*D;
	
	Power+=(int)(p_effort+i_effort+d_effort);
	if(Power>MOTOR_PWM_RESOLUTION-100) Power=MOTOR_PWM_RESOLUTION-100;
	if(Power<=0) Power=0;
	return (u16)Power;
}

u16 Deriv_Control_R(float target_vel,float cont_vel,int max_Effort)
{
	/*
					PID velocity control:
					target_vel:target velocity
					cont_vel: content velocity
					max_Effort: maximum safety PWM value
	*/
	static float vels[3],diffs[3];			//N-dimension vels supports N-1 order derivatives
	static float p_effort,i_effort,d_effort,total_Effort;
	static int Power;
	vels[0]=cont_vel;
	
	diffs[0]=target_vel-vels[0];		//0 order, Pure P value
	diffs[1]=vels[0]-vels[1];				//1 order, D value
	diffs[2]=vels[1]-vels[2];
	
	p_effort=diffs[0]*P;
	i_effort=(0)*I;
	d_effort=diffs[1]*D;
	
	Power+=(int)(p_effort+i_effort+d_effort);
	if(Power>MOTOR_PWM_RESOLUTION-100) Power=MOTOR_PWM_RESOLUTION-100;
	if(Power<=0) Power=0;
	return (u16)Power;
}
