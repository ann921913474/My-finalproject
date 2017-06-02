#ifndef __ADC_H 
#define __ADC_H

#define  Vref   3300
typedef unsigned           char uint8_t;
typedef unsigned short     int uint16_t;
typedef unsigned           int uint32_t;


extern char GcRcvBuf[20];//AD采集到的数据
extern int Temp;




extern void ADC_Init(void);	   // 初始化ADC口
extern uint32_t ADC_Read(uint8_t Channel);   // 读取电压值
float GetTemp (int  R);
float TGet(void);
void GetAdc(void);
#endif



