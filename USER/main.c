#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "pwm.h"
#include "exti.h"
#include "motor.h"
#include "led.h" 


//ALIENTEK Ì½Ë÷ÕßSTM32F407¿ª·¢°å ÊµÑé9
//PWMÊä³öÊµÑé-¿âº¯Êý°æ±¾
//¼¼ÊõÖ§³Ö£ºwww.openedv.com
//ÌÔ±¦µêÆÌ£ºhttp://eboard.taobao.com  
//¹ãÖÝÊÐÐÇÒíµç×Ó¿Æ¼¼ÓÐÏÞ¹«Ë¾  
//×÷Õß£ºÕýµãÔ­×Ó @ALIENTEK

int main(void)
{ 

	u16 led0pwmval=0;
	int fire=0;
	u8 dir=1;
	//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//ÉèÖÃÏµÍ³ÖÐ¶ÏÓÅÏÈ¼¶·Ö×é2
	delay_init(168);  //³õÊ¼»¯ÑÓÊ±º¯Êý
	uart_init(115200);//³õÊ¼»¯´®¿Ú²¨ÌØÂÊÎª115200
 	TIM14_PWM_Init(1000-1,84-1);
	TIM3_Int_Init(6500-1,8400-1);	//Ð¡³µ×ªÍäÊ±¼ä
  EXTIX_Init();
	PB6=1;	//IN1
	PB7=0;	//IN2
	PB8=0;	//Õý× ININ3      
	PB9=1;  //IN4
//	TIM_SetCompare1(TIM14,500);	//µç»ú³õËÙ¶È    ÊýÖµÔ½Ð¡ËÙ¶ÈÔ½´ó

//	TIM_SetCompare1(TIM13,500);	
	
	while(1)//Ö÷Ñ­»·
		
	{
		fire=0;
		if(SET3==0)		fire++;
		if(SET4==0)		fire++;
		if(SET5==0)		fire++;
		if(SET6==0)		fire++;		
		if(fire==2&&SET2==0)	//Á½¸ö»ðÑæ´«¸ÐÆ÷¶¼¼ì²âµ½£¬²¢ÇÒÇ°·½ÓÐÕÏ°­Îï
		{
			stop();   //Í£³µ
			FIRE1();
			delay_ms(2000);
			PD0=0;
			PD1=0;
			PD2=0;
			PD3=0;
			fire=0;			//»ðÑæ¼ì²â³õÊ¼»¯
		}
			if(fire==3&&SET2==0)	//Á½¸ö»ðÑæ´«¸ÐÆ÷¶¼¼ì²âµ½£¬²¢ÇÒÇ°·½ÓÐÕÏ°­Îï
		{
			stop();   //Í£³µ
			FIRE1();
			delay_ms(2000);
			PD0=0;
			PD1=0;
			PD2=0;
			PD3=0;
			fire=0;			//»ðÑæ¼ì²â³õÊ¼»¯
		}
		if(fire==4&&SET2==0)	//Á½¸ö»ðÑæ´«¸ÐÆ÷¶¼¼ì²âµ½£¬²¢ÇÒÇ°·½ÓÐÕÏ°­Îï
		{
			stop();   //Í£³µ
			FIRE1();
			delay_ms(2000);
			PD0=0;
			PD1=0;
			PD2=0;
			PD3=0;
			fire=0;			//»ðÑæ¼ì²â³õÊ¼»¯
		}
		
			
		if(SET2==0)		//Ç°·½ÓÐÕÏ°­Îï
		{	
			TURNLEFT();
//			delay_ms(180);
		
		}
		if(SET0==0&&SET1==0&&SET2==1)//Ö±ÐÐÏò×óÎ¢µ÷
		{
			turnleft();
//			delay_ms(150);
		}
		if(SET0==1&&SET1==0&&SET2==1)//Ö±ÐÐÏò×óÎ¢µ÷
		{
			TURNLEFT();
//			delay_ms(150);
		}


		if(SET0==0&&SET1==1&&SET2==1)  //Ö±ÐÐ²¢ÇÒÎ¢ÏòÓÒÆ«
		{
		
			turnright();
	   	}
		if(SET0==1&&SET1==1&&SET2==1)		//ÓÒ×ª
		{
			TURNRIGHT();
			
		}
		else
		{
			
		}
	}
}


