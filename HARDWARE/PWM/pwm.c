#include "pwm.h"
#include "led.h"
#include "usart.h"
 
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F407开发板
//定时器PWM 驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2014/5/4
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	 


//TIM14 PWM部分初始化 
//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
	u16 i=0;
void TIM3_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  ///使能TIM3时钟
	
  TIM_TimeBaseInitStructure.TIM_Period = arr; 	//自动重装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //定时器分频
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);//初始化TIM3
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //允许定时器3更新中断
	TIM_Cmd(TIM3,ENABLE); //使能定时器3
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn; //定时器3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}

//定时器3中断服务函数
void TIM3_IRQHandler(void)
{

	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET)
	{
		i++;
		if(i==98)	//溢出中断
		{
			PB6=1;	//IN1   
			PB7=0;	//IN2
			PB8=1;	//正? ININ3      
			PB9=0;  //IN4
			TIM_SetCompare1(TIM14,450);	
			TIM_SetCompare1(TIM13,500);
			delay_ms(750);
			i=0;
		}
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update); 

	}	//清除中断标志位
}

void TIM14_PWM_Init(u32 arr,u32 psc)
{		 					 
	//此部分需手动修改IO口设置
	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM13,ENABLE);	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14,ENABLE);  	//TIM14时钟使能    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	//使能gpio时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);	
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource6,GPIO_AF_TIM13);//GPIOA6复用为定时器13
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource7,GPIO_AF_TIM14); //GPIOA7复用为定时器14
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;         
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;      
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;    
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;      
	GPIO_Init(GPIOA,&GPIO_InitStructure);             
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;           //GPIOA7
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
	GPIO_Init(GPIOA,&GPIO_InitStructure);              //初始化PA7
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;        //初始化引脚PB6 PB7  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;       				//供IN1  IN2使用
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;     
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;       
	GPIO_Init(GPIOB,&GPIO_InitStructure);              
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;          //初始化引脚PB8 PB9
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;       					//供IN3   IN4 使用
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;     
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;       
	GPIO_Init(GPIOB,&GPIO_InitStructure);   

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12;         
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;      
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;    
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;      
	GPIO_Init(GPIOB,&GPIO_InitStructure);    

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;          //初始化引脚PD0,PD1，
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;       			
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//供IN1  IN2
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;     
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;       
	GPIO_Init(GPIOD,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3;          //初始化引脚PD2,PD3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//供IN3  IN4
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;     
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;       
	GPIO_Init(GPIOD,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_4|GPIO_Pin_3|GPIO_Pin_5;          //初始化引脚PD0,PD1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;       					//供IN1  IN2
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	     
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;       
	GPIO_Init(GPIOE,&GPIO_InitStructure);

	  
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //定时器分频
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseStructure.TIM_Period=arr;   //自动重装载值
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM14,&TIM_TimeBaseStructure);//初始化定时器14
	
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //定时器分频
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseStructure.TIM_Period=arr;   //自动重装载值
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM13,&TIM_TimeBaseStructure);//初始化定时器13
	
	//初始化TIM14 Channel1 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性高
	TIM_OC1Init(TIM14, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM1 4OC1
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性高
	TIM_OC1Init(TIM13, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM1 4OC1

	TIM_OC1PreloadConfig(TIM14, TIM_OCPreload_Enable);  //使能TIM14在CCR1上的预装载寄存器
 TIM_OC1PreloadConfig(TIM13, TIM_OCPreload_Enable);  //使能TIM13在CCR1上的预装载寄存器
 
  TIM_ARRPreloadConfig(TIM14,ENABLE);//ARPE使能 
	TIM_ARRPreloadConfig(TIM13,ENABLE);//ARPE使能 
	
	TIM_Cmd(TIM14, ENABLE);  //使能TIM14
  TIM_Cmd(TIM13, ENABLE);  //使能TIM13
										  
}  


