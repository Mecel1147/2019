#include "motor.h"
#include "exti.h"
#include "pwm.h"
	 int a;
void TURNLEFT(void)//SET==1,SET1==1 Æ«ÀëÓÒ±ß    1-jin  2-yuan  
{
		//0×óÓÒÂÖ×Ó·´×ª
		PB6=1;	//IN1   
	  PB7=0;	//IN2
	  PB8=1;	//Õý× ININ3      
	  PB9=0;  //IN4
		TIM_SetCompare1(TIM14,450);	
		TIM_SetCompare1(TIM13,500);
	a=1;
	
}
  void TURNRIGHT()//¿¿Ç½Ì«Ô¶  SET==0£¬SET1==0
{

	if(a==1){
		a=0;
		PB6=1;	//IN1
	  PB7=0;	//IN2
	  PB8=1;	//Õý× ININ3      
	  PB9=0;  //IN4
		TIM_SetCompare1(TIM13,450);	//µç»ú×ªËÙ
		TIM_SetCompare1(TIM14,500);//14¿ØÖÆ×óÂÖ£¬13¿ØÖÆÓÒÂÖ
		delay_ms(15);}

		PB6=1;	//IN1
	  PB7=0;	//IN2
	  PB8=0;	//Õý× ININ3      
	  PB9=1;  //IN4
	
		TIM_SetCompare1(TIM13,670);	//µç»ú×ªËÙ
		TIM_SetCompare1(TIM14,370);//14¿ØÖÆ×óÂÖ£¬13¿ØÖÆÓÒÂÖ
	

}	

	
void turnleft(void)
{
//		
//			PB6=0;	//IN1  Õý×ª
//			PB7=0;	//IN2
//			PB8=0;	//IN3      
//			PB9=0;  //IN4
//			delay_ms(5);
			PB6=1;	//IN1  Õý×ª
			PB7=0;	//IN2
			PB8=0;	//IN3      
			PB9=1;  //IN4
			TIM_SetCompare1(TIM14,1000);	//µç»ú³õËÙ¶È    ÊýÖµÔ½Ð¡ËÙ¶ÈÔ½´ó
			TIM_SetCompare1(TIM13,470);
//			delay_ms(20);
			a=1;
}

void turnright(void)
{
			PB6=1;	//IN1
			PB7=0;	//IN2
			PB8=0;	//IN3      
			PB9=1;  //IN4
			TIM_SetCompare1(TIM14,480);	//µç»ú³õËÙ¶È    ÊýÖµÔ½Ð¡ËÙ¶ÈÔ½´ó
			TIM_SetCompare1(TIM13,720);			//++
			a=1;
}
void stop(void)
{
	PB6=0;	//IN1			
	PB7=0;	//IN2
	PB8=0;	//IN3    		
	PB9=0;  //IN4
	
}
void FIRE1(void)
{
	PD1=1;
	PD0=0;
	PD2=1;
	PD3=0;

}

