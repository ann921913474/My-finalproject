/********************************************
��������:������غ���
��������:
�汾    :1.0
��ע����:
********************************************/
#include "music.h"
#include "timer.h"

#define delay_ms T16B0_delay_ms


//������ ��(0~6) ��(7~13) ��(14~20) ��������(20~...)


//				   1	 2   3   4   5   6   7   8   9  10  11   12  13  14  15  16  17   18   19   20   21
uint16_t music[]={220,247,277,294,330,370,416,440,494,554,587,659,740,831,880,988,1108,1174,1318,1480,1662,\
//                 22  23   24   25   26   27   28   29   30   31   32   33   34   35   36   37   38   39
				  1543,1572,1736,1760,1838,1968,2049,2066,2092,2128,2165,2220,2228,2232,2242,2294,2304,2310,\
//	         	   40	41	 42    43   44  45   46   47   48   49   50   51   52   53   54
				 2347,2370,2404,2415,2427,2463,2525,2564,2577,2591,2604,2632,2732,2740,2809};
//��������   ��һ�ֽ�Ϊ���ģ��ڶ��ֽ�Ϊ����
uint8_t mysunshine[]={8,5, 8,8, 8,9, 16,10 ,16,10, 16,10, 8,9, 8,10, 16,8, 16,8, 8,8, 8,8, 8,9, 8,10, 16,11,
	16,13,16,12,8,11,16,10,16,10,8,10,8,8,8,9,8,10,16,11,16,13,16,13,8,12,8,11,16,10,16,8,24,8,8,9,24,10,8,11,
	24,9,8,10,32,8,8,8,8,5,8,8,8,9,16,10,16,10,16,10,8,9,8,10,32,8,16,8,8,9,8,10,16,11,16,13,16,13,8,12,8,11,32,10};


//�������԰�����������д��������music����ȷ����(0~6) ��(7~13) ��(14~20)�������������е���������������ȷ��
void Play_Music(void)
{		
	uint8_t i=0;
	for(i=0;i<38;i++)
	{
		Set_pwm (music[mysunshine [2*i+1]],40);				//�ڶ����ֽ�����
		delay_ms (1000*(mysunshine [2*i]));							//��һ���ֽڽ��ģ�ÿ��30ms
	}
	Set_pwm(0,0);
}