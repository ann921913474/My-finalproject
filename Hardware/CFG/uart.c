#include "lpc11xx.h"
#include "uart.h"
#include<stdio.h>
#include<string.h>
#define UART_BPS 9600//串口通信波特率


	/**********************************
 串口初始化，设置为8位数据位，1位停止位，无奇偶校验，波特率为115200
	***********************************/
	void UART_Init(void) 
	{
	 uint16_t usFdiv;
	 LPC_SYSCON->SYSAHBCLKCTRL|=(1<<16); //打开IOCON配置时钟
	 LPC_IOCON->PIO1_6&=~0x07;
	 LPC_IOCON->PIO1_6|=(1<<0);//配置p1.6为RXD
	 LPC_IOCON->PIO1_7&=~0x07;
	 LPC_IOCON->PIO1_7|=(1<<0);//配置P1.7为TXD
	 LPC_SYSCON->SYSAHBCLKCTRL|=(1<<12);//打开UART功能部件时钟
	 LPC_SYSCON->UARTCLKDIV=0x01;//UART时钟分频
	 LPC_UART->LCR=0x83;//允许设置波特率
	 usFdiv=(SystemCoreClock/LPC_SYSCON->UARTCLKDIV/16)/UART_BPS;//设置波特率
	 LPC_UART->DLM = usFdiv/256;
	 LPC_UART->DLL = usFdiv % 256;
	 LPC_UART->LCR = 0x03;//锁定波特率
	 LPC_UART->FCR = 0x07;
	}
	/************************************
	向串口发送字节数据，并等待数据发送完成，使用查询方式
	ucDat:要发送的数据
	*************************************/
	void UART_SendByte(uint8_t ucDat)
	{
	 LPC_UART->THR=ucDat;//写入数据
	 while((LPC_UART->LSR&0x40)==0);//等待数据发送完毕		
	
	}
	/*************************************
	向串口发送字符串
	puiStr:要发送的字符串指针
	**************************************/
	void UART_SendStr(char * pucStr)
	{
	 
		while(1){
		      if(*pucStr=='\0')break;//遇到结束符，退出
			    UART_SendByte(*pucStr++);
		
		}
	}
	
	


