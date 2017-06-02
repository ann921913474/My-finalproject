#include "oled_new.h"
#include "stdlib.h"	 
//#include "timer.h"



//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//Mini STM32开发板
//SSD1306 OLED 驱动IC驱动代码
//驱动方式:8080并口/4线串口
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2010/6/3
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 正点原子 2009-2019
//All rights reserved
////////////////////////////////////////////////////////////////////////////////// 	  
 


/********************************************
函数名称:OLED各显示函数
功能描述:
版本    :1.0
备注事项:
********************************************/


//OLED的显存
//存放格式如下.
//[0]0 1 2 3 ... 127	
//[1]0 1 2 3 ... 127	
//[2]0 1 2 3 ... 127	
//[3]0 1 2 3 ... 127	
//[4]0 1 2 3 ... 127	
//[5]0 1 2 3 ... 127	
//[6]0 1 2 3 ... 127	
//[7]0 1 2 3 ... 127 		   
u8 OLED_GRAM[132][8];	 
const u8 F6x8[][6] =
{
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // sp
    { 0x00, 0x00, 0x00, 0x2f, 0x00, 0x00 },   // !
    { 0x00, 0x00, 0x07, 0x00, 0x07, 0x00 },   // "
    { 0x00, 0x14, 0x7f, 0x14, 0x7f, 0x14 },   // #
    { 0x00, 0x24, 0x2a, 0x7f, 0x2a, 0x12 },   // $
    { 0x00, 0x62, 0x64, 0x08, 0x13, 0x23 },   // %
    { 0x00, 0x36, 0x49, 0x55, 0x22, 0x50 },   // &
    { 0x00, 0x00, 0x05, 0x03, 0x00, 0x00 },   // '
    { 0x00, 0x00, 0x1c, 0x22, 0x41, 0x00 },   // (
    { 0x00, 0x00, 0x41, 0x22, 0x1c, 0x00 },   // )
    { 0x00, 0x14, 0x08, 0x3E, 0x08, 0x14 },   // *
    { 0x00, 0x08, 0x08, 0x3E, 0x08, 0x08 },   // +
    { 0x00, 0x00, 0x00, 0xA0, 0x60, 0x00 },   // ,
    { 0x00, 0x08, 0x08, 0x08, 0x08, 0x08 },   // -
    { 0x00, 0x00, 0x60, 0x60, 0x00, 0x00 },   // .
    { 0x00, 0x20, 0x10, 0x08, 0x04, 0x02 },   // /
    { 0x00, 0x3E, 0x51, 0x49, 0x45, 0x3E },   // 0
    { 0x00, 0x00, 0x42, 0x7F, 0x40, 0x00 },   // 1
    { 0x00, 0x42, 0x61, 0x51, 0x49, 0x46 },   // 2
    { 0x00, 0x21, 0x41, 0x45, 0x4B, 0x31 },   // 3
    { 0x00, 0x18, 0x14, 0x12, 0x7F, 0x10 },   // 4
    { 0x00, 0x27, 0x45, 0x45, 0x45, 0x39 },   // 5
    { 0x00, 0x3C, 0x4A, 0x49, 0x49, 0x30 },   // 6
    { 0x00, 0x01, 0x71, 0x09, 0x05, 0x03 },   // 7
    { 0x00, 0x36, 0x49, 0x49, 0x49, 0x36 },   // 8
    { 0x00, 0x06, 0x49, 0x49, 0x29, 0x1E },   // 9
    { 0x00, 0x00, 0x36, 0x36, 0x00, 0x00 },   // :
    { 0x00, 0x00, 0x56, 0x36, 0x00, 0x00 },   // ;
    { 0x00, 0x08, 0x14, 0x22, 0x41, 0x00 },   // <
    { 0x00, 0x14, 0x14, 0x14, 0x14, 0x14 },   // =
    { 0x00, 0x00, 0x41, 0x22, 0x14, 0x08 },   // >
    { 0x00, 0x02, 0x01, 0x51, 0x09, 0x06 },   // ?
    { 0x00, 0x32, 0x49, 0x59, 0x51, 0x3E },   // @
    { 0x00, 0x7C, 0x12, 0x11, 0x12, 0x7C },   // A
    { 0x00, 0x7F, 0x49, 0x49, 0x49, 0x36 },   // B
    { 0x00, 0x3E, 0x41, 0x41, 0x41, 0x22 },   // C
    { 0x00, 0x7F, 0x41, 0x41, 0x22, 0x1C },   // D
    { 0x00, 0x7F, 0x49, 0x49, 0x49, 0x41 },   // E
    { 0x00, 0x7F, 0x09, 0x09, 0x09, 0x01 },   // F
    { 0x00, 0x3E, 0x41, 0x49, 0x49, 0x7A },   // G
    { 0x00, 0x7F, 0x08, 0x08, 0x08, 0x7F },   // H
    { 0x00, 0x00, 0x41, 0x7F, 0x41, 0x00 },   // I
    { 0x00, 0x20, 0x40, 0x41, 0x3F, 0x01 },   // J
    { 0x00, 0x7F, 0x08, 0x14, 0x22, 0x41 },   // K
    { 0x00, 0x7F, 0x40, 0x40, 0x40, 0x40 },   // L
    { 0x00, 0x7F, 0x02, 0x0C, 0x02, 0x7F },   // M
    { 0x00, 0x7F, 0x04, 0x08, 0x10, 0x7F },   // N
    { 0x00, 0x3E, 0x41, 0x41, 0x41, 0x3E },   // O
    { 0x00, 0x7F, 0x09, 0x09, 0x09, 0x06 },   // P
    { 0x00, 0x3E, 0x41, 0x51, 0x21, 0x5E },   // Q
    { 0x00, 0x7F, 0x09, 0x19, 0x29, 0x46 },   // R
    { 0x00, 0x46, 0x49, 0x49, 0x49, 0x31 },   // S
    { 0x00, 0x01, 0x01, 0x7F, 0x01, 0x01 },   // T
    { 0x00, 0x3F, 0x40, 0x40, 0x40, 0x3F },   // U
    { 0x00, 0x1F, 0x20, 0x40, 0x20, 0x1F },   // V
    { 0x00, 0x3F, 0x40, 0x38, 0x40, 0x3F },   // W
    { 0x00, 0x63, 0x14, 0x08, 0x14, 0x63 },   // X
    { 0x00, 0x07, 0x08, 0x70, 0x08, 0x07 },   // Y
    { 0x00, 0x61, 0x51, 0x49, 0x45, 0x43 },   // Z
    { 0x00, 0x00, 0x7F, 0x41, 0x41, 0x00 },   // [
    { 0x00, 0x55, 0x2A, 0x55, 0x2A, 0x55 },   // 55
    { 0x00, 0x00, 0x41, 0x41, 0x7F, 0x00 },   // ]
    { 0x00, 0x04, 0x02, 0x01, 0x02, 0x04 },   // ^
    { 0x00, 0x40, 0x40, 0x40, 0x40, 0x40 },   // _
    { 0x00, 0x00, 0x01, 0x02, 0x04, 0x00 },   // '
    { 0x00, 0x20, 0x54, 0x54, 0x54, 0x78 },   // a
    { 0x00, 0x7F, 0x48, 0x44, 0x44, 0x38 },   // b
    { 0x00, 0x38, 0x44, 0x44, 0x44, 0x20 },   // c
    { 0x00, 0x38, 0x44, 0x44, 0x48, 0x7F },   // d
    { 0x00, 0x38, 0x54, 0x54, 0x54, 0x18 },   // e
    { 0x00, 0x08, 0x7E, 0x09, 0x01, 0x02 },   // f
    { 0x00, 0x18, 0xA4, 0xA4, 0xA4, 0x7C },   // g
    { 0x00, 0x7F, 0x08, 0x04, 0x04, 0x78 },   // h
    { 0x00, 0x00, 0x44, 0x7D, 0x40, 0x00 },   // i
    { 0x00, 0x40, 0x80, 0x84, 0x7D, 0x00 },   // j
    { 0x00, 0x7F, 0x10, 0x28, 0x44, 0x00 },   // k
    { 0x00, 0x00, 0x41, 0x7F, 0x40, 0x00 },   // l
    { 0x00, 0x7C, 0x04, 0x18, 0x04, 0x78 },   // m
    { 0x00, 0x7C, 0x08, 0x04, 0x04, 0x78 },   // n
    { 0x00, 0x38, 0x44, 0x44, 0x44, 0x38 },   // o
    { 0x00, 0xFC, 0x24, 0x24, 0x24, 0x18 },   // p
    { 0x00, 0x18, 0x24, 0x24, 0x18, 0xFC },   // q
    { 0x00, 0x7C, 0x08, 0x04, 0x04, 0x08 },   // r
    { 0x00, 0x48, 0x54, 0x54, 0x54, 0x20 },   // s
    { 0x00, 0x04, 0x3F, 0x44, 0x40, 0x20 },   // t
    { 0x00, 0x3C, 0x40, 0x40, 0x20, 0x7C },   // u
    { 0x00, 0x1C, 0x20, 0x40, 0x20, 0x1C },   // v
    { 0x00, 0x3C, 0x40, 0x30, 0x40, 0x3C },   // w
    { 0x00, 0x44, 0x28, 0x10, 0x28, 0x44 },   // x
    { 0x00, 0x1C, 0xA0, 0xA0, 0xA0, 0x7C },   // y
    { 0x00, 0x44, 0x64, 0x54, 0x4C, 0x44 },   // z
    { 0x14, 0x14, 0x14, 0x14, 0x14, 0x14 }    // horiz lines
};





//void OLED_Port_Init(void)
//{
//	LPC_SYSCON->SYSAHBCLKCTRL|=(1<<6);//使能时钟
//	//OLED_CS_LOW();
//	LPC_GPIO2->DIR|=(1<<0);
//	LPC_GPIO2->DIR|=(1<<1);
//	LPC_GPIO2->DIR|=(1<<2);	
//	LPC_GPIO2->DIR|=(1<<3);	
//	
//	
//	OLED_CS_HIGH();
//	OLDE_SCL_HIGH();//LPC_GPIO2->DATA|=(1<<1);//OLED_SCL=1  //
//	OLED_DC_HIGH();//LPC_GPIO2->DATA|=(1<<3);//OLED_DC=1
//	OLED_SDA_HIGH();//LPC_GPIO2->DATA|=(1<<2);//OLED_SDA=1
//    

//	OLDE_SCL_HIGH();;//LPC_GPIO2->DATA|=(1<<1);//OLED_SCL=1	   //OLED_SCL=1;
//	OLED_CS_LOW();

//}
//更新显存到LCD		 
void OLED_Refresh_Gram(void)
{
	u8 i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //设置页地址（0~7）
		OLED_WR_Byte (0x00,OLED_CMD);      //设置显示位置—列低地址
		OLED_WR_Byte (0x10,OLED_CMD);      //设置显示位置—列高地址   
		for(n=0;n<128;n++)OLED_WR_Byte(OLED_GRAM[n][i],OLED_DATA); 
	}   
}


//向SSD1306写入一个字节。
//dat:要写入的数据/命令
//cmd:数据/命令标志 0,表示命令;1,表示数据;
void OLED_WR_Byte(u8 dat,u8 cmd)
{	
//	u8 i;			  
//	//OLED_RS=cmd; //写命令 
//	//OLED_CS=0;
//	OLED_CS_LOW();
//	
//	for(i=0;i<8;i++)
//	{			  
//		OLDE_SCL_HIGH();
//		if(dat&0x80)OLED_SDA_HIGH();
//		else OLED_SDA_LOW();;
//		OLDE_SCL_HIGH();
//		dat<<=1;   
//	}				 
//	OLED_CS_HIGH();		
	
	u8 i=8;
	
	if (cmd==0)//写数据
	{
		OLED_DC_LOW();
		OLED_SCL_LOW();
		while(i--)
	  {
		if(dat&0x80)
		{
			OLED_SDA_HIGH();//LPC_GPIO2->DATA|=(1<<2);	//OLED_SDA=1		//OLED_SDA=1;
		}
		else
		{
			OLED_SDA_LOW();//LPC_GPIO2->DATA&=~(1<<2);	//OLED_SDA=0    //OLED_SDA=0;
		}
		OLDE_SCL_HIGH();//LPC_GPIO2->DATA|=(1<<1);	//OLED_SCL=1	   //OLED_SCL=1;;

		OLED_SCL_LOW() ;//LPC_GPIO2->DATA&=~(1<<1);	//OLED_SCL=0   //OLED_SCL=0;;
		dat<<=1;;
	  }
	}
	else if(cmd)
	{
		OLED_DC_HIGH();// LPC_GPIO2->DATA|=(1<<3);//OLED_DC=1		//  OLED_DC=1;
		OLED_SCL_LOW();//  LPC_GPIO2->DATA&=~(1<<1);//OLED_SCL=0     // OLED_SCL=0;
	
		while(i--)
		  {
			if(dat&0x80)
			{
			OLED_SDA_HIGH();//LPC_GPIO2->DATA|=(1<<2);//OLED_SDA=1		//OLED_SDA=1;
			}
			else
			{
			 OLED_SDA_LOW();//LPC_GPIO2->DATA&=~(1<<2);//OLED_SDA=0    //OLED_SDA=0;
			}
			OLDE_SCL_HIGH();//LPC_GPIO2->DATA|=(1<<1);//OLED_SCL=1	   //OLED_SCL=1;
			//_asm("nop");;
				//asm("nop");
			OLED_SCL_LOW();// LPC_GPIO2->DATA&=~(1<<1);//OLED_SCL=0   //OLED_SCL=0;;
			dat<<=1;
		  }
	}
} 

	  	  
//开启OLED显示    
void OLED_Display_On(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC命令
	OLED_WR_Byte(0X14,OLED_CMD);  //DCDC ON
	OLED_WR_Byte(0XAF,OLED_CMD);  //DISPLAY ON
}
//关闭OLED显示     
void OLED_Display_Off(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC命令
	OLED_WR_Byte(0X10,OLED_CMD);  //DCDC OFF
	OLED_WR_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
}		   			 
//清屏函数,清完屏,整个屏幕是黑色的!和没点亮一样!!!	  
void OLED_Clear(void)  
{  
	u8 i,n;  
	for(i=0;i<8;i++)for(n=0;n<128;n++)OLED_GRAM[n][i]=0X00;  
	OLED_Refresh_Gram();//更新显示
}
//画点 
//x:0~127
//y:0~63
//t:1 填充 0,清空				   
void OLED_DrawPoint(u8 x,u8 y,u8 t)
{
	u8 pos,bx,temp=0;
	if(x>127||y>63)return;//超出范围了.
	pos=7-y/8;
	bx=y%8;
	temp=1<<(7-bx);
	if(t)OLED_GRAM[x][pos]|=temp;
	else OLED_GRAM[x][pos]&=~temp;	    
}



void OLED_WrCmd(u8 cmd)
{
	u8 i=8;
	
	
	OLED_DC_LOW();//LPC_GPIO2->DATA&=~(1<<3);	//OLED_DC=0    OLED_DC=0;;
    OLED_SCL_LOW();//LPC_GPIO2->DATA&=~(1<<1);	//OLED_SCL=0   OLED_SCL=0;;
	
	
	while(i--)
	  {
		if(cmd&0x80)
		{
			OLED_SDA_HIGH();//LPC_GPIO2->DATA|=(1<<2);	//OLED_SDA=1		//OLED_SDA=1;
		}
		else
		{
			OLED_SDA_LOW();//LPC_GPIO2->DATA&=~(1<<2);	//OLED_SDA=0    //OLED_SDA=0;
		}
		OLDE_SCL_HIGH();//LPC_GPIO2->DATA|=(1<<1);	//OLED_SCL=1	   //OLED_SCL=1;;

		OLED_SCL_LOW() ;//LPC_GPIO2->DATA&=~(1<<1);	//OLED_SCL=0   //OLED_SCL=0;;
		cmd<<=1;;
	  }

}



//x1,y1,x2,y2 填充区域的对角坐标
//确保x1<=x2;y1<=y2 0<=x1<=127 0<=y1<=63	 	 
//dot:0,清空;1,填充	  
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot)  
{  
	u8 x,y;  
	for(x=x1;x<=x2;x++)
	{
		for(y=y1;y<=y2;y++)OLED_DrawPoint(x,y,dot);
	}													    
	OLED_Refresh_Gram();//更新显示
}
void OLED_WrDat(u8 data)
{
  u8 i=8;
  //LCD_CS=0;;
  OLED_DC_HIGH();// LPC_GPIO2->DATA|=(1<<3);//OLED_DC=1		//  OLED_DC=1;
  OLED_SCL_LOW();//  LPC_GPIO2->DATA&=~(1<<1);//OLED_SCL=0     // OLED_SCL=0;
  //asm("nop");
  while(i--)
  {
    if(data&0x80)
	{
	OLED_SDA_HIGH();//LPC_GPIO2->DATA|=(1<<2);//OLED_SDA=1		//OLED_SDA=1;
	}
    else
	{
	 OLED_SDA_LOW();//LPC_GPIO2->DATA&=~(1<<2);//OLED_SDA=0    //OLED_SDA=0;
	}
    OLDE_SCL_HIGH();//LPC_GPIO2->DATA|=(1<<1);//OLED_SCL=1	   //OLED_SCL=1;
    //_asm("nop");;
		//asm("nop");
    OLED_SCL_LOW();// LPC_GPIO2->DATA&=~(1<<1);//OLED_SCL=0   //OLED_SCL=0;;
    data<<=1;
  }
	//LCD_CS=1;
}

void OLED_Fill_OLD(u8 bmp_data)
{
	u8 y,x;

	for(y=0;y<8;y++)
	{
		OLED_WrCmd(0xb0+y);
		OLED_WrCmd(0x01);
		OLED_WrCmd(0x10);
		for(x=0;x<128;x++)
		OLED_WrDat(bmp_data);
	}
}





void OLED_Init(void)
{ 	 				 	 	

	LPC_SYSCON->SYSAHBCLKCTRL|=(1<<6);//使能时钟
	LPC_GPIO2->DIR|=(1<<0);
	LPC_GPIO2->DIR|=(1<<1);
	LPC_GPIO2->DIR|=(1<<2);	
	LPC_GPIO2->DIR|=(1<<3);	
	
	
	OLED_CS_HIGH();
	OLDE_SCL_HIGH();//LPC_GPIO2->DATA|=(1<<1);//OLED_SCL=1  //
	OLED_DC_HIGH();//LPC_GPIO2->DATA|=(1<<3);//OLED_DC=1
	OLED_SDA_HIGH();//LPC_GPIO2->DATA|=(1<<2);//OLED_SDA=1
    

	OLDE_SCL_HIGH();;//LPC_GPIO2->DATA|=(1<<1);//OLED_SCL=1	   //OLED_SCL=1;
	OLED_CS_LOW();
		  
// 		  
	OLED_WR_Byte(0xAE,OLED_CMD); //关闭显示
	OLED_WR_Byte(0xD5,OLED_CMD); //设置时钟分频因子,震荡频率
	OLED_WR_Byte(0x80,OLED_CMD);   //[3:0],分频因子;[7:4],震荡频率
	OLED_WR_Byte(0xA8,OLED_CMD); //设置驱动路数
	OLED_WR_Byte(0X3F,OLED_CMD); //默认0X3F(1/64) 
	OLED_WR_Byte(0xD3,OLED_CMD); //设置显示偏移
	OLED_WR_Byte(0X00,OLED_CMD); //默认为0

	OLED_WR_Byte(0x40,OLED_CMD); //设置显示开始行 [5:0],行数.
													    
	OLED_WR_Byte(0x8D,OLED_CMD); //电荷泵设置
	OLED_WR_Byte(0x14,OLED_CMD); //bit2，开启/关闭
	OLED_WR_Byte(0x20,OLED_CMD); //设置内存地址模式
	OLED_WR_Byte(0x02,OLED_CMD); //[1:0],00，列地址模式;01，行地址模式;10,页地址模式;默认10;
	OLED_WR_Byte(0xA1,OLED_CMD); //段重定义设置,bit0:0,0->0;1,0->127;
	OLED_WR_Byte(0xC0,OLED_CMD); //设置COM扫描方向;bit3:0,普通模式;1,重定义模式 COM[N-1]->COM0;N:驱动路数
	OLED_WR_Byte(0xDA,OLED_CMD); //设置COM硬件引脚配置
	OLED_WR_Byte(0x12,OLED_CMD); //[5:4]配置
		 
	OLED_WR_Byte(0x81,OLED_CMD); //对比度设置
	OLED_WR_Byte(0xEF,OLED_CMD); //1~255;默认0X7F (亮度设置,越大越亮)
	OLED_WR_Byte(0xD9,OLED_CMD); //设置预充电周期
	OLED_WR_Byte(0xf1,OLED_CMD); //[3:0],PHASE 1;[7:4],PHASE 2;
	OLED_WR_Byte(0xDB,OLED_CMD); //设置VCOMH 电压倍率
	OLED_WR_Byte(0x30,OLED_CMD); //[6:4] 000,0.65*vcc;001,0.77*vcc;011,0.83*vcc;

	OLED_WR_Byte(0xA4,OLED_CMD); //全局显示开启;bit0:1,开启;0,关闭;(白屏/黑屏)
	OLED_WR_Byte(0xA6,OLED_CMD); //设置显示方式;bit0:1,反相显示;0,正常显示	    						   
	OLED_WR_Byte(0xAF,OLED_CMD); //开启显示	 
	OLED_Clear();
}  

void OLED_PutPixel(u8 x,u8 y,u8 data1)
{
	//data1当前点的数据
	data1 = data1<<(y%8);
	OLED_WrCmd(0xb0+(y>>3));
	OLED_WrCmd(((x&0xf0)>>4)|0x10);
	OLED_WrCmd((x&0x0f)|0x00);
	OLED_WrDat(data1);
}

void OLED_Set_Pos(u8 x, u8 y)
{
  OLED_WrCmd(0xb0+y);
  OLED_WrCmd(((x&0xf0)>>4)|0x10);
  OLED_WrCmd((x&0x0f)|0x01);
}
//==============================================================
//函数名：LCD_P6x8Str(u8 x,u8 y,u8 *p)
//功能描述：写入一组标准ASCII字符串
//参数：显示的位置（x,y），y为页范围0～7，要显示的字符串
//返回：无
//==============================================================
void OLED_P6x8Str(u8 x,u8 y,u8 ch[])
{
  u8 c=0,i=0,j=0;
  while (ch[j]!='\0')
  {
    c =ch[j]-32;
    if(x>128){x=0;y++;}
    OLED_Set_Pos(x,y);
  	for(i=0;i<6;i++)
  	  OLED_WrDat(F6x8[c][i]);
  	x+=6;
  	j++;
  }
}
//==============================================================
//函数名： void Draw_BMP(u8 x,u8 y)
//功能描述：显示BMP图片128×64
//参数：起始点坐标(x,y),x的范围0～127，y为页的范围0～7
//返回：无
//==============================================================
void Draw_BMP(u8 x0,u8 y0,u8 x1,u8 y1,u8 bmp[])
{
  u16 ii=0;
  u8 x,y;

  if(y1%8==0) y=y1/8;
  else y=y1/8+1;
	for(y=y0;y<=y1;y++)
	{
		OLED_Set_Pos(x0,y);
		for(x=x0;x<x1;x++)
	    {
	    	OLED_WrDat(bmp[ii++]);
	    }
	}
}









