#include "LPC11xx.h"                    // Device header
#include "adc.h"
#include "Key.h"
#include "uart.h"
#include <stdio.h>
#include <string.h>
char GcRcvBuf[20];//AD�ɼ���������
int Temp=0;
int ulADCData=0;
uint32_t ulADCBuf;


	/*********************************
	����������ADC��ʼ��ͨ��7
	���ߣ�Ƚ��
	�汾��1.0
	**********************************/
	void ADC_Init(void)
	{
	  LPC_SYSCON->SYSAHBCLKCTRL|=(1<<16);
		LPC_IOCON->PIO1_11&=~0xBF;//����PIO1_11Ϊģ������ģʽ
		LPC_IOCON->PIO1_11|=0x01;//PIO1_11ģ������ͨ��7
		LPC_SYSCON->PDRUNCFG&=~(0x01<<4);//ADCģ���ϵ�
		LPC_SYSCON->SYSAHBCLKCTRL|=(0x01<<13);//ʹ��ADCģ��ʱ��
		LPC_ADC->CR=(0x01<<7)|  //SEL=1��ѡ��ADC7
		            ((SystemCoreClock/1000000-1)<<8)|//ת��ʱ��1MHz
		            (0<<16)|//�������ת������
		            (0<<17)|//ʹ��11clocksת��
		            (0<<24)|//ADCת��ֹͣ
		            (0<<27);//ֱ������ADCת������λ��Ч
	}
	
	
	/*********************************
	������������ȡADC�Ĳ���ֵ
	���ߣ�Ƚ��
	�汾��1.0
	**********************************/
	void GetAdc(void)
	{
			uint32_t i;

		
				for(i=0;i<10;i++)
				{
					LPC_ADC->CR|=(1<<24);//����ת��
					while((LPC_ADC->DR[7]&0x80000000)==0);//��ȡDR7��Done
					LPC_ADC->CR|=(1<<24);//��һ��ת���������
					while((LPC_ADC->DR[7]&0x80000000)==0);//��ȡDR7��Done
					ulADCBuf=LPC_ADC->DR[7];//��ȡ����Ĵ���
					ulADCBuf=(ulADCBuf>>6)&0x3ff;//���ݴӵ�6λ��ʼ���棬ռ��10λ
					ulADCData+=ulADCBuf;//�����ۼ�
				}
					
				
     		ulADCData=ulADCData/10;//����10�ν����˲�����
        ulADCData=(ulADCData*10000)/(3300-ulADCData);  //������ת����ģ����
				
				Temp=GetTemp(ulADCData*3);
				
	}

/********************************************
��������:float GetTemp(uint32_t AdMuch)
��������:�¶ȴ�����
���ߣ�Ƚ��
�汾��1.0	
********************************************/

float GetTemp (int R)
{
	
	float  T=0;
	uint16_t k;//�¶�����Ŀ��
				
			
	if( (R<29371)&&(R>=18680) ) 	
	{
		k = 1069;
		return ((29370-R)/k)+0;
	}
	else if( (R<18681)&&(R>=12240) )
	{
		k = 644;
		return((18680-R)/k)+10;
	}
	else if( (R<12241)&&(R>=8221) )	
	{
		k = 402;
		return((11500-R)/k)+20;
	}
	else if( (R<8222)&&(R>=5648) )
	{
		k = 257;
		return ((9500-R)/k)+30;
	}
	else if( (R<5649)&&(R>=3958) )
	{
		k = 169;
		return ((5648-R)/k)+40;
	}
	else if( (R<3959)&&(R>=2823) )
	{
		k = 114;
		return ((3850-R)/k)+50;
	}
	else if( (R<2824)&&(R>=2047) )
	{
		k = 78;
		return ((2956-R)/k)+60;
	}
	else if( (R<2048)&&(R>=1506) )
	{
		k = 54;
		return((2048-R)/k)+70;
	}
	else if( (R<1507)&&(R>=1124) )
	{
		k = 38;
		return ((1507-R)/k)+80;
	}
	else if( (R<1125)&&(R>=850) )
	{
		k = 27;
		return ((1125-R)/k)+90;
	}
	else if( (R<851)&&(R>=651) )
	{
		k = 20;
		return((851-R)/k)+100;
	}
	else if( (R<652)&&(R>=504) )
	{
		k = 15;
		return ((652-R)/k)+110;
	}
	else if( (R<505)&&(R>=395) )
	{
		k = 11;
		return ((505-R)/k)+120;
	}
	else if( (R<47731)&&(R>=29370) )
	{
		k = 1836;
		return((47730-R)/k)-10;
	}
	else if( (R<80361)&&(R>=47730) )
	{
		k = 3263;
		return((80360-R)/k)-20;
	}
	else if( (R<140001)&&(R>=80360) )
	{
		k = 5964;
		return((140000-R)/k)-30;
	}
	else if( (R<249600)&&(R>=140000) )
	{
		k = 10960;
		return ((249600-R)/k)-40;
	}

}


	 
	 