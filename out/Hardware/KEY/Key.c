
#include "Key.h"




/********************************************
函数名称:void Key_init(void)
功能描述:按键初始化
版本    :1.0
作者： 唐海月
********************************************/
void Key_init(void)
{
	LPC_GPIO3 ->DIR &=~(1<<0);//初始化GPIO3.0~4
	LPC_GPIO3 ->DIR &=~(1<<1);//初始化GPIO3.0~4
	LPC_GPIO3 ->DIR &=~(1<<2);//初始化GPIO3.0~4
	LPC_GPIO3 ->DIR &=~(1<<3);//初始化GPIO3.0~4
	LPC_GPIO3 ->DIR &=~(1<<4);//初始化GPIO3.0~4
	LPC_SYSCON->SYSAHBCLKCTRL|=(1<<6);//使能时钟
}










