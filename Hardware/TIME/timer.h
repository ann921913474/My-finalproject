#ifndef __NXPLPC11xx_TIME_H__
#define __NXPLPC11xx_TIME_H__
#include "LPC11xx.h"

extern void T16B0_init(void);

extern void T16B0_delay_ms(uint16_t ms);
extern void T16B0_delay_us(uint16_t us);

#define delay_ms T16B0_delay_ms
#define delay_us T16B0_delay_us

#endif





