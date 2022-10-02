#ifndef __HEAD_H
#define __HEAD_H
#include "sys.h"


void Head_Init(void);  //≥ı ºªØ
void Head_Rotate();

extern int head_Pos,head_tar_Pos;

#define HEAD_ROTATE_LEFT 0
#define HEAD_ROTATE_RIGHT 1

#endif
