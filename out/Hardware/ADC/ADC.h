#ifndef __ADC_H 
#define __ADC_H

#define  Vref   3300
typedef unsigned           char uint8_t;
typedef unsigned short     int uint16_t;
typedef unsigned           int uint32_t;


extern char GcRcvBuf[20];//AD�ɼ���������
extern int Temp;




extern void ADC_Init(void);	   // ��ʼ��ADC��
extern uint32_t ADC_Read(uint8_t Channel);   // ��ȡ��ѹֵ
float GetTemp (int  R);
float TGet(void);
void GetAdc(void);
#endif



