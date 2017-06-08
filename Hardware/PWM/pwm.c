/********************************************
函数名称:初始化Time32PWM定时器
功能描述:
版本    :	  1.0
备注事项:
********************************************/

#include "pwm.h"


/********************************************
函数名称:void TIM32B0_PWM(uint32_t cycle_us, uint8_t duty)
功能描述:PWM频率  占空比
版本    :1.0
备注事项:
********************************************/
void TIM32B0_PWM(uint32_t cycle_us, uint8_t duty)
{
	cycle_us = 1000000 /cycle_us ;
	if((duty>=100)&&(duty<=0))return;
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<9);		//使能TIM32B0时钟
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16);  		// 使能IOCON时钟
	LPC_IOCON->PIO0_1 &= ~0x07;
	LPC_IOCON->PIO0_1 |= 0x02;	      			//把P0_1脚设置为MAT2
	LPC_SYSCON->SYSAHBCLKCTRL &= ~(1<<16);  	// 禁能IOCON时钟

	LPC_TMR32B0->TCR = 0x02;		 	 		//复位定时器（bit1：写1复位）
	LPC_TMR32B0->PR  = 0x00;		  			//把预分频寄存器置0，使PC+1，TC+1
	LPC_TMR32B0->PWMC= (1<<2);		  			//设置MAT2为PWM输出引脚
	LPC_TMR32B0->MCR = 0x02<<9;       			//设置MR3匹配时复位TC,也就是把MR3当做周期寄存器
	LPC_TMR32B0->MR3 = 48*cycle_us;		  		//设置周期
	LPC_TMR32B0->MR2 = 48*cycle_us*(100-duty)/100;//设置占空比
	LPC_TMR32B0->TCR = 0x01;			  					//启动定时器
}

/********************************************
函数名称:void Set_pwm(uint32_t cycle_us, uint8_t duty)
功能描述: PWM频率   占空比
版本    :1.0
备注事项:
********************************************/
void Set_pwm(uint32_t cycle_us, uint8_t duty)
{
	cycle_us = 1000000 /cycle_us ;
	LPC_TMR32B0->TCR = 0x02;												//设置pwm占空比前需要复位定时器
	LPC_TMR32B0->MR3 = 48*cycle_us;		 
	LPC_TMR32B0->MR2 = 48*cycle_us*(100-duty)/100;
	LPC_TMR32B0->TCR = 0x01;			
}


void TIM16B1_PWM(uint32_t cycle_us, uint8_t duty)
{
	cycle_us = 1000000 /cycle_us ;
	if((duty>=100)&&(duty<=0))return;
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<8);		//使能TIM16B1时钟
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16);  		// 使能IOCON时钟
	
	LPC_IOCON->SWDIO_PIO1_3 &= ~0x07;
	LPC_IOCON->SWDIO_PIO1_3 |= 0x03;	      			//把P0_1脚设置为MAT2
	
	
	LPC_SYSCON->SYSAHBCLKCTRL &= ~(1<<16);  	// 禁能IOCON时钟

	LPC_TMR16B1->TCR = 0x02;		 	 		  //复位定时器（bit1：写1复位）
	LPC_TMR16B1->PR  = 0x00;		  			//把预分频寄存器置0，使PC+1，TC+1
	LPC_TMR16B1->PWMC= (1<<2);		  		//设置MAT2为PWM输出引脚
	LPC_TMR16B1->MCR = 0x02<<9;       	//设置MR3匹配时复位TC,也就是把MR3当做周期寄存器
	LPC_TMR16B1->MR3 = 48*cycle_us;		  //设置周期
	LPC_TMR16B1->MR2 = 48*cycle_us*(100-duty)/100;//设置占空比
	LPC_TMR16B1->TCR = 0x01;			  		//启动定时器
}



void Set_pwm_2(uint32_t cycle_us, uint8_t duty)
{
	cycle_us = 1000000 /cycle_us ;
	LPC_TMR16B1->TCR = 0x02;												//设置pwm占空比前需要复位定时器
	LPC_TMR16B1->MR3 = 48*cycle_us;		 
	LPC_TMR16B1->MR2 = 48*cycle_us*(100-duty)/100;
	LPC_TMR16B1->TCR = 0x01;			
}









