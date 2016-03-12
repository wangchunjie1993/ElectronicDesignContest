#include"def.h"

#ifndef __MOTOR_H__
#define __MOTOR_H__

void motor_init();
void left();
void left_count(int counter);
void right();
void right_count(int counter);
void motor_stop();
void motor_move(int counter);
void speed_modify();

#endif
