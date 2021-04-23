#include "pwm.h"
#include "led.h"
#include "usart.h"
 
//////////////////////////////////////////////////////////////////////////////////	 
//±¾³ÌÐòÖ»¹©Ñ§Ï°Ê¹ÓÃ£¬Î´¾­×÷ÕßÐí¿É£¬²»µÃÓÃÓÚÆäËüÈÎºÎÓÃÍ¾
//ALIENTEK STM32F407¿ª·¢°å
//¶¨Ê±Æ÷PWM Çý¶¯´úÂë	   
//ÕýµãÔ­×Ó@ALIENTEK
//¼¼ÊõÂÛÌ³:www.openedv.com
//´´½¨ÈÕÆÚ:2014/5/4
//°æ±¾£ºV1.0
//°æÈ¨ËùÓÐ£¬µÁ°æ±Ø¾¿¡£
//Copyright(C) ¹ãÖÝÊÐÐÇÒíµç×Ó¿Æ¼¼ÓÐÏÞ¹«Ë¾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	 


//TIM14 PWM²¿·Ö³õÊ¼»¯ 
//PWMÊä³ö³õÊ¼»¯
//arr£º×Ô¶¯ÖØ×°Öµ
//psc£ºÊ±ÖÓÔ¤·ÖÆµÊý
	u16 i=0;
void TIM3_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  ///Ê¹ÄÜTIM3Ê±ÖÓ
	
  TIM_TimeBaseInitStructure.TIM_Period = arr; 	//×Ô¶¯ÖØ×°ÔØÖµ
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //¶¨Ê±Æ÷·ÖÆµ
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //ÏòÉÏ¼ÆÊýÄ£Ê½
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);//³õÊ¼»¯TIM3
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //ÔÊÐí¶¨Ê±Æ÷3¸üÐÂÖÐ¶Ï
	TIM_Cmd(TIM3,ENABLE); //Ê¹ÄÜ¶¨Ê±Æ÷3
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn; //¶¨Ê±Æ÷3ÖÐ¶Ï
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //ÇÀÕ¼ÓÅÏÈ¼¶1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //×ÓÓÅÏÈ¼¶3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}

//¶¨Ê±Æ÷3ÖÐ¶Ï·þÎñº¯Êý
void TIM3_IRQHandler(void)
{

	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET)
	{
		i++;
		if(i==98)	//Òç³öÖÐ¶Ï
		{
			PB6=1;	//IN1   
			PB7=0;	//IN2
			PB8=1;	//Õý× ININ3      
			PB9=0;  //IN4
			TIM_SetCompare1(TIM14,450);	
			TIM_SetCompare1(TIM13,500);
			delay_ms(750);
			i=0;
		}
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update); 

	}	//Çå³ýÖÐ¶Ï±êÖ¾Î»
}

void TIM14_PWM_Init(u32 arr,u32 psc)
{		 					 
	//´Ë²¿·ÖÐèÊÖ¶¯ÐÞ¸ÄIO¿ÚÉèÖÃ
	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM13,ENABLE);	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14,ENABLE);  	//TIM14Ê±ÖÓÊ¹ÄÜ    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	//Ê¹ÄÜgpioÊ±ÖÓ
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);	
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource6,GPIO_AF_TIM13);//GPIOA6¸´ÓÃÎª¶¨Ê±Æ÷13
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource7,GPIO_AF_TIM14); //GPIOA7¸´ÓÃÎª¶¨Ê±Æ÷14
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;         
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;      
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;    
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;      
	GPIO_Init(GPIOA,&GPIO_InitStructure);             
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;           //GPIOA7
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //¸´ÓÃ¹¦ÄÜ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//ËÙ¶È100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //ÍÆÍì¸´ÓÃÊä³ö
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //ÉÏÀ­
	GPIO_Init(GPIOA,&GPIO_InitStructure);              //³õÊ¼»¯PA7
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;        //³õÊ¼»¯Òý½ÅPB6 PB7  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;       				//¹©IN1  IN2Ê¹ÓÃ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;     
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;       
	GPIO_Init(GPIOB,&GPIO_InitStructure);              
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;          //³õÊ¼»¯Òý½ÅPB8 PB9
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;       					//¹©IN3   IN4 Ê¹ÓÃ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;     
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;       
	GPIO_Init(GPIOB,&GPIO_InitStructure);   

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12;         
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;      
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;    
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;      
	GPIO_Init(GPIOB,&GPIO_InitStructure);    

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;          //³õÊ¼»¯Òý½ÅPD0,PD1£¬
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;       			
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//¹©IN1  IN2
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;     
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;       
	GPIO_Init(GPIOD,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3;          //³õÊ¼»¯Òý½ÅPD2,PD3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//¹©IN3  IN4
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;     
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;       
	GPIO_Init(GPIOD,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_4|GPIO_Pin_3|GPIO_Pin_5;          //³õÊ¼»¯Òý½ÅPD0,PD1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;       					//¹©IN1  IN2
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	     
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;       
	GPIO_Init(GPIOE,&GPIO_InitStructure);

	  
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //¶¨Ê±Æ÷·ÖÆµ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //ÏòÉÏ¼ÆÊýÄ£Ê½
	TIM_TimeBaseStructure.TIM_Period=arr;   //×Ô¶¯ÖØ×°ÔØÖµ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM14,&TIM_TimeBaseStructure);//³õÊ¼»¯¶¨Ê±Æ÷14
	
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //¶¨Ê±Æ÷·ÖÆµ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //ÏòÉÏ¼ÆÊýÄ£Ê½
	TIM_TimeBaseStructure.TIM_Period=arr;   //×Ô¶¯ÖØ×°ÔØÖµ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM13,&TIM_TimeBaseStructure);//³õÊ¼»¯¶¨Ê±Æ÷13
	
	//³õÊ¼»¯TIM14 Channel1 PWMÄ£Ê½	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //Ñ¡Ôñ¶¨Ê±Æ÷Ä£Ê½:TIMÂö³å¿í¶Èµ÷ÖÆÄ£Ê½2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //±È½ÏÊä³öÊ¹ÄÜ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //Êä³ö¼«ÐÔ:TIMÊä³ö±È½Ï¼«ÐÔ¸ß
	TIM_OC1Init(TIM14, &TIM_OCInitStructure);  //¸ù¾ÝTÖ¸¶¨µÄ²ÎÊý³õÊ¼»¯ÍâÉèTIM1 4OC1
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //Ñ¡Ôñ¶¨Ê±Æ÷Ä£Ê½:TIMÂö³å¿í¶Èµ÷ÖÆÄ£Ê½2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //±È½ÏÊä³öÊ¹ÄÜ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //Êä³ö¼«ÐÔ:TIMÊä³ö±È½Ï¼«ÐÔ¸ß
	TIM_OC1Init(TIM13, &TIM_OCInitStructure);  //¸ù¾ÝTÖ¸¶¨µÄ²ÎÊý³õÊ¼»¯ÍâÉèTIM1 4OC1

	TIM_OC1PreloadConfig(TIM14, TIM_OCPreload_Enable);  //Ê¹ÄÜTIM14ÔÚCCR1ÉÏµÄÔ¤×°ÔØ¼Ä´æÆ÷
 TIM_OC1PreloadConfig(TIM13, TIM_OCPreload_Enable);  //Ê¹ÄÜTIM13ÔÚCCR1ÉÏµÄÔ¤×°ÔØ¼Ä´æÆ÷
 
  TIM_ARRPreloadConfig(TIM14,ENABLE);//ARPEÊ¹ÄÜ 
	TIM_ARRPreloadConfig(TIM13,ENABLE);//ARPEÊ¹ÄÜ 
	
	TIM_Cmd(TIM14, ENABLE);  //Ê¹ÄÜTIM14
  TIM_Cmd(TIM13, ENABLE);  //Ê¹ÄÜTIM13
										  
}  


