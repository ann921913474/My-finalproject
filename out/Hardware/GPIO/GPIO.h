
#ifndef __GPIO_H
#define __GPIO_H
#include "LPC11XX.h"
#include "timer.h"
#define READ_GPIO(m,n)	LPC_GPIO##m->DATA & (1<<##n)
void Gpio_Init(int n,int m,int DIR);//标准io初始化
#endif







