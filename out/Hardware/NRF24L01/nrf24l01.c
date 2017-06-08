#include "lpc11xx.h"
#include "nrf24l01.h"
#include "ssp.h"

const uint8_t TX_ADDRESS[TX_ADR_WIDTH]={0x68,0x86,0x66,0x88,0x28}; //发送地址
const uint8_t RX_ADDRESS[RX_ADR_WIDTH]={0x68,0x86,0x66,0x88,0x28}; //发送地址



/*******************************************/
/* 函数功能；NRF24L01初始化                */
/*******************************************/
void NRF24L01_Init()
{
#ifndef SSP0INIT		        // 如果没有初始化过SPI0
	SPI0_Init();		        // 初始化SPI0
#define SSP0INIT		        // 告诉编译器已经初始化过SPI0
#endif
	LPC_GPIO0->DIR |= (1<<7);       //P0.7脚为输出，用做CSN
	CSN_High;		//CSN=1;
	
	LPC_GPIO0->DIR &= ~(1<<2);      //NRF24L01_IRQ连接P0.2脚，设置P0.2脚为输入引脚
	LPC_GPIO0->DIR |= (1<<3);	    //NRF24L01_CE连接P0.3脚，设置P0.3脚为输出引脚
	CE_Low;	    //CE置低，使能24L01配置
	NRF24L01_Write_Reg(WRITE_REG+RX_PW_P0,RX_PLOAD_WIDTH);//选择通道0的有效数据宽度
	NRF24L01_Write_Reg(FLUSH_RX,0xff);//清除RX FIFO寄存器    
	NRF24L01_Write_Buf(WRITE_REG+TX_ADDR,(uint8_t*)TX_ADDRESS,TX_ADR_WIDTH);//写TX节点地址 
	NRF24L01_Write_Buf(WRITE_REG+RX_ADDR_P0,(uint8_t*)RX_ADDRESS,RX_ADR_WIDTH); //设置TX节点地址,主要为了使能ACK	  
	NRF24L01_Write_Reg(WRITE_REG+EN_AA,0x01);     //使能通道0的自动应答    
	NRF24L01_Write_Reg(WRITE_REG+EN_RXADDR,0x01); //使能通道0的接收地址  
	NRF24L01_Write_Reg(WRITE_REG+SETUP_RETR,0x1a);//设置自动重发间隔时间:500us + 86us;最大自动重发次数:10次
	NRF24L01_Write_Reg(WRITE_REG+RF_CH,40);       //设置RF通道为40
	NRF24L01_Write_Reg(WRITE_REG+RF_SETUP,0x0f);  //设置TX发射参数,0db增益,2Mbps,低噪声增益开启   
	NRF24L01_Write_Reg(WRITE_REG+CONFIG,0x0f);    //配置基本工作模式的参数;PWR_UP,EN_CRC,16BIT_CRC,接收模式,开启所有中断

	CE_High;	//CE置高，使能工作模式
}
/*********************************************/
/* 函数功能：给24L01的寄存器写值（一个字节） */
/* 入口参数：reg   要写的寄存器地址          */
/*           value 给寄存器写的值            */
/* 出口参数：status 状态值                   */
/*********************************************/
uint8_t NRF24L01_Write_Reg(uint8_t reg,uint8_t value)
{
	uint8_t status;

	CSN_Low;	 //CSN=0;   
  status = SPI0_communication(reg);//发送寄存器地址,并读取状态值
	SPI0_communication(value);
	CSN_High;   //CSN=1;

	return status;
}
/*************************************************/
/* 函数功能：读24L01的寄存器值 （一个字节）      */
/* 入口参数：reg  要读的寄存器地址               */
/* 出口参数：value 读出寄存器的值                */
/*************************************************/
uint8_t NRF24L01_Read_Reg(uint8_t reg)
{
 	uint8_t value;

	CSN_Low;	 //CSN=0;   
  SPI0_communication(reg);//发送寄存器值(位置),并读取状态值
	value = SPI0_communication(NOP);
	CSN_High; //CSN=1;

	return value;
}
/*********************************************/
/* 函数功能：读24L01的寄存器值（多个字节）   */
/* 入口参数：reg   寄存器地址                */
/*           *pBuf 读出寄存器值的存放数组    */
/*           len   数组字节长度              */
/* 出口参数：status 状态值                   */
/*********************************************/
uint8_t NRF24L01_Read_Buf(uint8_t reg,uint8_t *pBuf,uint8_t len)
{
	uint8_t status,u8_ctr;
	CSN_Low;//CSN=0       
  	status=SPI0_communication(reg);//发送寄存器地址,并读取状态值   	   
 	for(u8_ctr=0;u8_ctr<len;u8_ctr++)
	pBuf[u8_ctr]=SPI0_communication(0XFF);//读出数据
	CSN_High; //CSN=1
  	return status;        //返回读到的状态值
}
/**********************************************/
/* 函数功能：给24L01的寄存器写值（多个字节）  */
/* 入口参数：reg  要写的寄存器地址            */
/*           *pBuf 值的存放数组               */
/*           len   数组字节长度               */
/**********************************************/
uint8_t NRF24L01_Write_Buf(uint8_t reg, uint8_t *pBuf, uint8_t len)
{
	uint8_t status,u8_ctr;
	CSN_Low;	    
  	status = SPI0_communication(reg);//发送寄存器值(位置),并读取状态值
  	for(u8_ctr=0; u8_ctr<len; u8_ctr++)
	SPI0_communication(*pBuf++); //写入数据
	CSN_High;	 
  	return status;          //返回读到的状态值
}
/********************************************/
/* 函数功能：检测24L01是否存在              */
/* 返回值；  0  存在                        */
/*           1  不存在                      */
/********************************************/	
uint8_t NRF24L01_Check(void)
{
	uint8_t check_in_buf[5]={0x11,0x22,0x33,0x44,0x55};
	uint8_t check_out_buf[5]={0x00};

	NRF24L01_Write_Buf(WRITE_REG+TX_ADDR, check_in_buf, 5);

	NRF24L01_Read_Buf(READ_REG+TX_ADDR, check_out_buf, 5);

	if((check_out_buf[0] == 0x11)&&\
	   (check_out_buf[1] == 0x22)&&\
	   (check_out_buf[2] == 0x33)&&\
	   (check_out_buf[3] == 0x44)&&\
	   (check_out_buf[4] == 0x55))return 0;
	else return 1;
}
/*********************************************/
/* 函数功能：设置24L01为接收模式             */
/*********************************************/
void NRF24L01_RX_Mode(void)
{

	CE_Low;	//CE拉低，使能24L01配置 
  NRF24L01_Write_Reg(WRITE_REG+CONFIG, 0x0f);//配置基本工作模式的参数;PWR_UP,EN_CRC,16BIT_CRC,接收模式
	CE_High;	//CE置高，使能接收
}
/*********************************************/
/* 函数功能：设置24L01为发送模式             */
/*********************************************/
void NRF24L01_TX_Mode(void)
{
	CE_Low;	//CE拉低，使能24L01配置	    
  NRF24L01_Write_Reg(WRITE_REG+CONFIG,0x0e);    //配置基本工作模式的参数;PWR_UP,EN_CRC,16BIT_CRC,接收模式,开启所有中断
	CE_High;	//CE置高，使能发送
}
/*********************************************/
/* 函数功能：24L01接收数据                   */
/* 入口参数：rxbuf 接收数据数组              */
/* 返回值： 0   成功收到数据                 */
/*          1   没有收到数据                 */
/*********************************************/
uint8_t NRF24L01_RxPacket(uint8_t *rxbuf)
{
	uint8_t state;

	state=NRF24L01_Read_Reg(STATUS);  //读取状态寄存器的值    	 
	NRF24L01_Write_Reg(WRITE_REG+STATUS,state); //清除TX_DS或MAX_RT中断标志
	if(state&RX_OK)//接收到数据
	{
		NRF24L01_Read_Buf(RD_RX_PLOAD,rxbuf,RX_PLOAD_WIDTH);//读取数据
		NRF24L01_Write_Reg(FLUSH_RX,0xff);//清除RX FIFO寄存器 
		return 0; 
	}	   
	return 1;//没收到任何数据
}
/**********************************************/
/* 函数功能：设置24L01为发送模式              */
/* 入口参数：txbuf  发送数据数组              */
/* 返回值； 0x10    达到最大重发次数，发送失败*/
/*          0x20    成功发送完成              */
/*          0xff    发送失败                  */
/**********************************************/
uint8_t NRF24L01_TxPacket(uint8_t *txbuf)
{
	uint8_t state;
   
	CE_Low;	//CE拉低，使能24L01配置
  	NRF24L01_Write_Buf(WR_TX_PLOAD,txbuf,TX_PLOAD_WIDTH);//写数据到TX BUF  32个字节
 	CE_High;	//CE置高，使能发送	   
	while(IRQ_HIGH);//等待发送完成 
	state=NRF24L01_Read_Reg(STATUS);  //读取状态寄存器的值	   
	NRF24L01_Write_Reg(WRITE_REG+STATUS,state); //清除TX_DS或MAX_RT中断标志
	if(state&MAX_TX)//达到最大重发次数
	{
		NRF24L01_Write_Reg(FLUSH_TX,0xff);//清除TX FIFO寄存器 
		return MAX_TX; 
	}
	if(state&TX_OK)//发送完成
	{
		return TX_OK;
	}
	return 0xff;//发送失败
}					    














