#include "lpc11xx.h"
#include "timer.h"

//��ʼ����ʱ��
/********************************************
��������:T16B0_init()
��������:��ʱ�����ȳ�ʼ��
�汾    :1.0
���ߣ� �ƺ���
********************************************/
void T16B0_init(void)
{
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<7);	//ʹ��TIM16B0ʱ��
	LPC_TMR16B0->IR  = 0x01;		//MR0�жϸ�λ,�����жϣ�bit0:MR0, bit1:MR1, bit2:MR2, bit3:MR3, bit4:CP0��
	LPC_TMR16B0->MCR = 0x04;		//MR0�жϲ���ʱֹͣTC��PC����ʹTCR[0]=0, ֹͣ��ʱ������
}



void T16B0_delay_ms(uint16_t ms)
{
	LPC_TMR16B0->TCR = 0x02;		//��λ��ʱ����bit1��д1��λ��
	LPC_TMR16B0->PR  = SystemCoreClock/1000-1;		// 1����TC+1
	LPC_TMR16B0->MR0 = ms;	// ע�⣺MR0��16λ�Ĵ�����ֵ��Ҫ����65535
	LPC_TMR16B0->TCR = 0x01;		//������ʱ����TCR[0]=1;	  
	while (LPC_TMR16B0->TCR & 0x01);//�ȴ���ʱ����ʱʱ�䵽

}

void T16B0_delay_us(uint16_t us)
{

	LPC_TMR16B0->TCR = 0x02;		//��λ��ʱ����bit1��д1��λ��
	LPC_TMR16B0->PR  = SystemCoreClock/1000000-1;		// 1΢��TC+1
	LPC_TMR16B0->MR0 = us;	// ע�⣺MR0��16λ�Ĵ�����ֵ��Ҫ����65535
	LPC_TMR16B0->TCR = 0x01;		//������ʱ����TCR[0]=1;	  
	while (LPC_TMR16B0->TCR & 0x01);//�ȴ���ʱ����ʱʱ�䵽

}





