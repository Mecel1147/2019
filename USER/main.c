#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "pwm.h"
#include "exti.h"
#include "motor.h"
#include "led.h" 


//ALIENTEK ̽����STM32F407������ ʵ��9
//PWM���ʵ��-�⺯���汾
//����֧�֣�www.openedv.com
//�Ա����̣�http://eboard.taobao.com  
//������������ӿƼ����޹�˾  
//���ߣ�����ԭ�� @ALIENTEK

int main(void)
{ 

	u16 led0pwmval=0;
	int fire=0;
	u8 dir=1;
	//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);  //��ʼ����ʱ����
	uart_init(115200);//��ʼ�����ڲ�����Ϊ115200
 	TIM14_PWM_Init(1000-1,84-1);
	TIM3_Int_Init(6500-1,8400-1);	//С��ת��ʱ��
  EXTIX_Init();
	PB6=1;	//IN1
	PB7=0;	//IN2
	PB8=0;	//��� ININ3      
	PB9=1;  //IN4
//	TIM_SetCompare1(TIM14,500);	//������ٶ�    ��ֵԽС�ٶ�Խ��

//	TIM_SetCompare1(TIM13,500);	
	
	while(1)//��ѭ��
		
	{
		fire=0;
		if(SET3==0)		fire++;
		if(SET4==0)		fire++;
		if(SET5==0)		fire++;
		if(SET6==0)		fire++;		
		if(fire==2&&SET2==0)	//�������洫��������⵽������ǰ�����ϰ���
		{
			stop();   //ͣ��
			FIRE1();
			delay_ms(2000);
			PD0=0;
			PD1=0;
			PD2=0;
			PD3=0;
			fire=0;			//�������ʼ��
		}
			if(fire==3&&SET2==0)	//�������洫��������⵽������ǰ�����ϰ���
		{
			stop();   //ͣ��
			FIRE1();
			delay_ms(2000);
			PD0=0;
			PD1=0;
			PD2=0;
			PD3=0;
			fire=0;			//�������ʼ��
		}
		if(fire==4&&SET2==0)	//�������洫��������⵽������ǰ�����ϰ���
		{
			stop();   //ͣ��
			FIRE1();
			delay_ms(2000);
			PD0=0;
			PD1=0;
			PD2=0;
			PD3=0;
			fire=0;			//�������ʼ��
		}
		
			
		if(SET2==0)		//ǰ�����ϰ���
		{	
			TURNLEFT();
//			delay_ms(180);
		
		}
		if(SET0==0&&SET1==0&&SET2==1)//ֱ������΢��
		{
			turnleft();
//			delay_ms(150);
		}
		if(SET0==1&&SET1==0&&SET2==1)//ֱ������΢��
		{
			TURNLEFT();
//			delay_ms(150);
		}


		if(SET0==0&&SET1==1&&SET2==1)  //ֱ�в���΢����ƫ
		{
		
			turnright();
	   	}
		if(SET0==1&&SET1==1&&SET2==1)		//��ת
		{
			TURNRIGHT();
			
		}
		else
		{
			
		}
	}
}


