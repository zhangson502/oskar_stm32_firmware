#include "head_motor.h"

int head_Pos,head_tar_Pos;
int phase;
void Head_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;	  
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;     
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;     
  GPIO_Init(GPIOB, &GPIO_InitStructure);					     
	head_Pos=0;head_tar_Pos=0;phase=0;
}
void Head_Rotate()
{
	int i;
	if(head_tar_Pos==head_Pos)
	{
		GPIO_ResetBits(GPIOB,GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_12|GPIO_Pin_15);
		return;
	}
	if(head_tar_Pos>head_Pos)
	{
		if(phase==0) phase=1;
		else if(phase==1) phase=2;
		else if(phase==2) phase=3;
		else if(phase==3) phase=0;
		head_Pos++;
	}
	if(head_tar_Pos<head_Pos)
	{
		if(phase==0) phase=1;
		else if(phase==1) phase=2;
		else if(phase==2) phase=3;
		else if(phase==3) phase=0;
		head_Pos--;
	}
	if(phase==0){
			GPIO_SetBits(GPIOB,GPIO_Pin_15);
			GPIO_ResetBits(GPIOB,GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_12);}
	if(phase==1){
			GPIO_SetBits(GPIOB,GPIO_Pin_14);
			GPIO_ResetBits(GPIOB,GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_15);}
	if(phase==2){
			GPIO_SetBits(GPIOB,GPIO_Pin_13);
			GPIO_ResetBits(GPIOB,GPIO_Pin_12|GPIO_Pin_14|GPIO_Pin_15);}
	if(phase==3){
			GPIO_SetBits(GPIOB,GPIO_Pin_12);
			GPIO_ResetBits(GPIOB,GPIO_Pin_15|GPIO_Pin_13|GPIO_Pin_14);}

}
