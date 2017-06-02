
#ifndef __NXPLPC11xx_TIME_H__
#define __NXPLPC11xx_TIME_H__
#include "lpc11xx.h"

void TIM32B1_PWM(uint32_t cycle_us, uint8_t duty);
void Set_pwm(uint32_t cycle_us, uint8_t duty);
void TIM16B1_PWM(uint32_t cycle_us, uint8_t duty);
void Set_pwm_2(uint32_t cycle_us, uint8_t duty);


//void TIM32B1_PWM(uint32_t cycle_us, uint8_t duty);
#endif





