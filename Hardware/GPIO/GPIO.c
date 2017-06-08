 #include "GPIO.h"
 
 

/********************************************
函数名称： void Gpio_Init(int i,int m，int DIR)
                         GPIOi->m      方向
功能描述：单个IO初始化

********************************************/
 
 
void Gpio_Init(int i,int m,int DIR)//标准io初始化
 {
		//公共初始化
		if (i>3||i<0||m>11||(i==3&&m>5))return ;//防止出错
		 
		 
		if (i==0&&m==10)//屏蔽GPIO0_10
			return ;
		if (i==0&&m==11)//对GPIO0_11特殊处理
		{
				LPC_SYSCON->SYSAHBCLKCTRL|=(1<<16);//打开iocon配置时钟
				LPC_IOCON->R_PIO0_11|=(1<<1);
				LPC_SYSCON->SYSAHBCLKCTRL&=~(1<<16);//关闭配置时钟
						//LPC_GPIO0->DIR |=(1<<11);//>DATA|=(1<<i);	//配置为高电平
						//LPC_GPIO0->DATA|=(1<<11);	//配置为高电平
		} 
		if (i==1&&(m==3||m==6||m==7))return ;//屏蔽GPIO1_3、6、7

		if (i==1&&(m==1||m==2||m==0))//对GPIO1_0、1、2特殊处理
		{
				LPC_SYSCON->SYSAHBCLKCTRL|=(1<<16);			//打开iocon配置时钟
			switch(m)
			{
				case 0:LPC_IOCON->R_PIO1_0|=(1<<1);break;
				case 1:LPC_IOCON->R_PIO1_1|=(1<<1);break;
				case 2:LPC_IOCON->R_PIO1_2|=(1<<1);break;
			}
				LPC_SYSCON->SYSAHBCLKCTRL&=~(1<<16);		//关闭配置时钟
		}

		LPC_SYSCON->SYSAHBCLKCTRL|=(1<<6);				//使能GPIO时钟
	if(DIR==1)//输出模式初始化
		{
			switch(i)
			{
				case 0:		{	LPC_GPIO0->DIR |=(1<<m);						//配置为输出模式
								LPC_GPIO0->DATA|=(1<<m);						//配置为高电平
								break;
				}
				case 1:		{	LPC_GPIO1->DIR |=(1<<m);						//配置为输出模式
								LPC_GPIO1->DATA|=(1<<m);						//配置为高电平
								break;
				}
				case 2:		{	LPC_GPIO2->DIR |=(1<<m);						//配置方向
								LPC_GPIO2->DATA|=(1<<m);						//配置为高电平
								break;
				}
				case 3:		{	LPC_GPIO3->DIR |=(1<<m);						//配置方向
								LPC_GPIO3->DATA|=(1<<m);						//配置为高电平
								break;
				}
			}
		}
	
	if (DIR==0)//输入模式初始化
	{
		switch(i)
		{
			case 0:		{LPC_GPIO0->DIR &=~(1<<m);break;}
			case 1:		{LPC_GPIO1->DIR &=~(1<<m);break;}
			case 2:		{LPC_GPIO2->DIR &=~(1<<m);break;}
			case 3:		{LPC_GPIO3->DIR &=~(1<<m);break;}
		}
	}
	return ;
}
 #if 0
 
	/*	
	LPC_SYSCON->SYSAHBCLKCTRL|=(1<<16);//打开iocon配置时钟
	LPC_IOCON->PIO2_0&=~0X07;
	LPC_IOCON->PIO2_0|=0X00;//配置io为gpio模式
	LPC_SYSCON->SYSAHBCLKCTRL&=~(1<<16);//关闭配置时钟
	*/
	//LPC_SYSCON->SYSAHBCLKCTRL|=(1<<16);//使能gpio时钟
	//LPC_GPIO2->DIR |=(1<<0);//配置为输出模式
	//LPC_GPIO2->DATA|=(1<<0);	//配置为高电平
	//LPC_GPIO2->DIR |=0xff;//配置为输出模式
	//LPC_GPIO2->DATA|=0x00;	//配置为高电平


 #endif 


