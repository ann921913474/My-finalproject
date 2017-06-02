 #include "GPIO.h"
 
 

/********************************************
�������ƣ� void Gpio_Init(int i,int m��int DIR)
                         GPIOi->m      ����
��������������IO��ʼ��

********************************************/
 
 
void Gpio_Init(int i,int m,int DIR)//��׼io��ʼ��
 {
		//������ʼ��
		if (i>3||i<0||m>11||(i==3&&m>5))return ;//��ֹ����
		 
		 
		if (i==0&&m==10)//����GPIO0_10
			return ;
		if (i==0&&m==11)//��GPIO0_11���⴦��
		{
				LPC_SYSCON->SYSAHBCLKCTRL|=(1<<16);//��iocon����ʱ��
				LPC_IOCON->R_PIO0_11|=(1<<1);
				LPC_SYSCON->SYSAHBCLKCTRL&=~(1<<16);//�ر�����ʱ��
						//LPC_GPIO0->DIR |=(1<<11);//>DATA|=(1<<i);	//����Ϊ�ߵ�ƽ
						//LPC_GPIO0->DATA|=(1<<11);	//����Ϊ�ߵ�ƽ
		} 
		if (i==1&&(m==3||m==6||m==7))return ;//����GPIO1_3��6��7

		if (i==1&&(m==1||m==2||m==0))//��GPIO1_0��1��2���⴦��
		{
				LPC_SYSCON->SYSAHBCLKCTRL|=(1<<16);			//��iocon����ʱ��
			switch(m)
			{
				case 0:LPC_IOCON->R_PIO1_0|=(1<<1);break;
				case 1:LPC_IOCON->R_PIO1_1|=(1<<1);break;
				case 2:LPC_IOCON->R_PIO1_2|=(1<<1);break;
			}
				LPC_SYSCON->SYSAHBCLKCTRL&=~(1<<16);		//�ر�����ʱ��
		}

		LPC_SYSCON->SYSAHBCLKCTRL|=(1<<6);				//ʹ��GPIOʱ��
	if(DIR==1)//���ģʽ��ʼ��
		{
			switch(i)
			{
				case 0:		{	LPC_GPIO0->DIR |=(1<<m);						//����Ϊ���ģʽ
								LPC_GPIO0->DATA|=(1<<m);						//����Ϊ�ߵ�ƽ
								break;
				}
				case 1:		{	LPC_GPIO1->DIR |=(1<<m);						//����Ϊ���ģʽ
								LPC_GPIO1->DATA|=(1<<m);						//����Ϊ�ߵ�ƽ
								break;
				}
				case 2:		{	LPC_GPIO2->DIR |=(1<<m);						//���÷���
								LPC_GPIO2->DATA|=(1<<m);						//����Ϊ�ߵ�ƽ
								break;
				}
				case 3:		{	LPC_GPIO3->DIR |=(1<<m);						//���÷���
								LPC_GPIO3->DATA|=(1<<m);						//����Ϊ�ߵ�ƽ
								break;
				}
			}
		}
	
	if (DIR==0)//����ģʽ��ʼ��
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
	LPC_SYSCON->SYSAHBCLKCTRL|=(1<<16);//��iocon����ʱ��
	LPC_IOCON->PIO2_0&=~0X07;
	LPC_IOCON->PIO2_0|=0X00;//����ioΪgpioģʽ
	LPC_SYSCON->SYSAHBCLKCTRL&=~(1<<16);//�ر�����ʱ��
	*/
	//LPC_SYSCON->SYSAHBCLKCTRL|=(1<<16);//ʹ��gpioʱ��
	//LPC_GPIO2->DIR |=(1<<0);//����Ϊ���ģʽ
	//LPC_GPIO2->DATA|=(1<<0);	//����Ϊ�ߵ�ƽ
	//LPC_GPIO2->DIR |=0xff;//����Ϊ���ģʽ
	//LPC_GPIO2->DATA|=0x00;	//����Ϊ�ߵ�ƽ


 #endif 


