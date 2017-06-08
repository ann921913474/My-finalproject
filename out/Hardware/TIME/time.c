/*****************************************************************************
 * @file:    time.c
 * @brief:   
 *           
 * @auther:  ���Ĳ� 13160200115     
 * @version: $Revision: V1.0$
 * @date:    $Date: 2015-6-08 $
 *****************************************************************************/
#include "time.h"


/*!
  @brief    ��ʼ��Time16��ʱ�� 
  @param[in]    ��ʱʱ��ms
  @return       void
 */
void T16B0_init(uint16_t ms)
{
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<7);					//ʹ��TIM16B0ʱ��
	LPC_TMR16B0->IR  = 0x01;											//MR0�жϸ�λ,�����жϣ�bit0:MR0, bit1:MR1, bit2:MR2, bit3:MR3, bit4:CP0��
	LPC_TMR16B0->PR  = SystemCoreClock/1000-1;		// 1����TC+1
	LPC_TMR16B0->MR0 = ms;												// ע�⣺MR0��16λ�Ĵ�����ֵ��Ҫ����65535
	LPC_TMR16B0->MCR = 0x03;											//MR0�жϲ���ʱTC��λ�������ж�
	LPC_TMR16B0->TCR = 0x01;											//������ʱ����TCR[0]=1;	  
	NVIC_EnableIRQ (TIMER_16_0_IRQn );
	NVIC_SetPriority (TIMER_16_0_IRQn ,2);
}



