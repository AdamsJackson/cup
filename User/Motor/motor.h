#ifndef __motor_h__
#define __motor_h__

#include "main.h"


extern void motor_init(void);
extern void motor_set_speed(int16_t speed1,int16_t speed2,int16_t speed3,int16_t speed4);
extern void go_forward(int16_t speed);
#endif
