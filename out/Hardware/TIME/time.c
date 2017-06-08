/*****************************************************************************
 * @file:    time.c
 * @brief:   
 *           
 * @auther:  陈文博 13160200115     
 * @version: $Revision: V1.0$
 * @date:    $Date: 2015-6-08 $
 *****************************************************************************/
#include "time.h"


/*!
  @brief    初始化Time16定时器 
  @param[in]    定时时间ms
  @return       void
 */
void T16B0_init(uint16_t ms)
{
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<7);					//使能TIM16B0时钟
	LPC_TMR16B0->IR  = 0x01;											//MR0中断复位,即清中断（bit0:MR0, bit1:MR1, bit2:MR2, bit3:MR3, bit4:CP0）
	LPC_TMR16B0->PR  = SystemCoreClock/1000-1;		// 1毫秒TC+1
	LPC_TMR16B0->MR0 = ms;												// 注意：MR0是16位寄存器，值不要超过65535
	LPC_TMR16B0->MCR = 0x03;											//MR0中断产生时TC复位并产生中断
	LPC_TMR16B0->TCR = 0x01;											//启动定时器：TCR[0]=1;	  
	NVIC_EnableIRQ (TIMER_16_0_IRQn );
	NVIC_SetPriority (TIMER_16_0_IRQn ,2);
}



