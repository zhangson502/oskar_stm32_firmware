#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 

void Usart_Feedback(void);
void Usart_Process();


void Usart_Init(void);
void UART_CH2_Init();

void Process_IO_Error(void);
void Check_CRC(void);
void Init_Tx_Data(u8 len,u8 cmdID);
void USART3_IRQHandler(void);

extern u8 rx_pack_State,tx_pack_State;	//Data Receive State in USART[0: processing head 1:processing body]
extern u8 rx_pack_Addr,tx_pack_Addr;		//How many bits in a pack had been reveiced
extern u8 rx_pack_Len,tx_pack_Len;			//Pack length(HEAD included)
extern u8 rx_Data[256],tx_Data[256];		//All data in tx/rx packs
extern u8 rx_pack_Cmd,tx_pack_Cmd;			//Pack Commands
extern u8 usart_Delay;

//Data pack key positons
#define PACK_HEAD_POSITION 0
#define PACK_LEN_POSITION 2
#define PACK_CMD_POSITION 3
#define PACK_DATA_POSITION 4

//Data state defination
#define PROCESSING_HEAD 0
#define	PROCESSING_BODY 1

//Commands defination

#define SET_VELOCITY 0x01
#define SET_HEAD_ROTATE 0x02
#define SET_ARM 0x03
#define SET_UTILS 0x04
#define SET_LED 0x05
#define ASK_UTIL_STATE 0x11
#define ASK_SONAR_VALUE 0x12
#define ASK_IMU 0x13
#define ASK_BATT 0x14
#define ERROR 0xff


#endif



