#ifndef __EXTI_H
#define __EXIT_H	 
#include "sys.h"  	
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//�ⲿ�ж� ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/4
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
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

void EXTIX_Init(void);	//�ⲿ�жϳ�ʼ��		 					    
#endif

























