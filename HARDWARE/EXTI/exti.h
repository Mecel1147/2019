#ifndef __EXTI_H
#define __EXIT_H	 
#include "sys.h"  	
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F407开发板
//外部中断 驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2014/5/4
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	 
\

#define SET0  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10)
#define SET1  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)
#define SET2  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)
#define PD0 PDout(0)
#define PD1 PDout(1)
#define PD2 PDout(2)
#define PD3 PDout(3)

#define SET3  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)
#define SET4  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)
#define SET5  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)
#define SET6  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)

void TURNRIGHT(void);
void TURNLEFT(void);

void EXTIX_Init(void);	//外部中断初始化		 					    
#endif

























