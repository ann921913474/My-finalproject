
#include "Key.h"




/********************************************
��������:void Key_init(void)
��������:������ʼ��
�汾    :1.0
���ߣ� �ƺ���
********************************************/
void Key_init(void)
{
	LPC_GPIO3 ->DIR &=~(1<<0);//��ʼ��GPIO3.0~4
	LPC_GPIO3 ->DIR &=~(1<<1);//��ʼ��GPIO3.0~4
	LPC_GPIO3 ->DIR &=~(1<<2);//��ʼ��GPIO3.0~4
	LPC_GPIO3 ->DIR &=~(1<<3);//��ʼ��GPIO3.0~4
	LPC_GPIO3 ->DIR &=~(1<<4);//��ʼ��GPIO3.0~4
	LPC_SYSCON->SYSAHBCLKCTRL|=(1<<6);//ʹ��ʱ��
}










