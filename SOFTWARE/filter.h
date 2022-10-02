#ifndef __FILTER_H
#define __FILTER_H
  /**************************************************************************
By：张德雨伞
欢迎访问我的博客：http://blog.sina.com/deyubooke
**************************************************************************/
extern float angle, angle_dot; 	
void Kalman_Filter(float Accel,float Gyro);		
void Yijielvbo(float angle_m, float gyro_m);
#endif
