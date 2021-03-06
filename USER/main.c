#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "pwm.h"
#include "exti.h"
#include "motor.h"
#include "led.h" 


//ALIENTEK 探索者STM32F407开发板 实验9
//PWM输出实验-库函数版本
//技术支持：www.openedv.com
//淘宝店铺：http://eboard.taobao.com  
//广州市星翼电子科技有限公司  
//作者：正点原子 @ALIENTEK

int main(void)
{ 

	u16 led0pwmval=0;
	int fire=0;
	u8 dir=1;
	//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);  //初始化延时函数
	uart_init(115200);//初始化串口波特率为115200
 	TIM14_PWM_Init(1000-1,84-1);
	TIM3_Int_Init(6500-1,8400-1);	//小车转弯时间
  EXTIX_Init();
	PB6=1;	//IN1
	PB7=0;	//IN2
	PB8=0;	//正? ININ3      
	PB9=1;  //IN4
//	TIM_SetCompare1(TIM14,500);	//电机初速度    数值越小速度越大

//	TIM_SetCompare1(TIM13,500);	
	
	while(1)//主循环
		
	{
		fire=0;
		if(SET3==0)		fire++;
		if(SET4==0)		fire++;
		if(SET5==0)		fire++;
		if(SET6==0)		fire++;		
		if(fire==2&&SET2==0)	//两个火焰传感器都检测到，并且前方有障碍物
		{
			stop();   //停车
			FIRE1();
			delay_ms(2000);
			PD0=0;
			PD1=0;
			PD2=0;
			PD3=0;
			fire=0;			//火焰检测初始化
		}
			if(fire==3&&SET2==0)	//两个火焰传感器都检测到，并且前方有障碍物
		{
			stop();   //停车
			FIRE1();
			delay_ms(2000);
			PD0=0;
			PD1=0;
			PD2=0;
			PD3=0;
			fire=0;			//火焰检测初始化
		}
		if(fire==4&&SET2==0)	//两个火焰传感器都检测到，并且前方有障碍物
		{
			stop();   //停车
			FIRE1();
			delay_ms(2000);
			PD0=0;
			PD1=0;
			PD2=0;
			PD3=0;
			fire=0;			//火焰检测初始化
		}
		
			
		if(SET2==0)		//前方有障碍物
		{	
			TURNLEFT();
//			delay_ms(180);
		
		}
		if(SET0==0&&SET1==0&&SET2==1)//直行向左微调
		{
			turnleft();
//			delay_ms(150);
		}
		if(SET0==1&&SET1==0&&SET2==1)//直行向左微调
		{
			TURNLEFT();
//			delay_ms(150);
		}


		if(SET0==0&&SET1==1&&SET2==1)  //直行并且微向右偏
		{
		
			turnright();
	   	}
		if(SET0==1&&SET1==1&&SET2==1)		//右转
		{
			TURNRIGHT();
			
		}
		else
		{
			
		}
	}
}


