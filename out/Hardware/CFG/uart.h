#ifndef   UART_H
#define   UART_H

extern void UART_Init(void) ;  // 初始化串口
extern void UART_SendByte(uint8_t ucDat); // 串口发送字节数据
extern void UART_SendStr(char * pucStr); // 串口发送数组数据

#endif





