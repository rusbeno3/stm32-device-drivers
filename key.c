//****************************************************************************************//
#include "key.h"
#include "main.h"
#include "delay.h"
#include "time.h"

#include "stm32f10x.h"
#include <stm32f10x_iwdg.h>
#include <stm32f10x_rtc.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_rcc.h>
#include "stm32f10x_conf.h"
#include "stm32f10x_exti.h"
#include <core_cm3.h>
#include "misc.h"
#include <stm32f10x_pwr.h>
#include <stm32f10x_tim.h>
#include <stm32f10x_bkp.h>

/*�� ��������� � main.h
#define     PORT_KEY GPIOB
#define		PIN_KEY_1 GPIO_Pin_10
#define		PIN_KEY_2 GPIO_Pin_11
#define		PIN_KEY_3 GPIO_Pin_12
#define		RCC_PORT_KEY  RCC_APB2Periph_GPIOB


#define  PORT_IN_OUT 		GPIOB  //���� ���������� ���������
#define  PIN_OUT1 		GPIO_Pin_0 //����� ���������� ���������1
#define  PIN_OUT2 		GPIO_Pin_1 //����� ���������� ���������2
#define	 RCC_PORT_IN_OUT  RCC_APB2Periph_GPIOB
*/
//u8 keys;  //�������� ������� ������

void  key_ini()
{
	key_init();
	blinc_init();
	BIP_init();
	init_in_out();
	KEY_D;//������ ��������� � ���� D - �� �����
	NVIC_EXTI_Configuration();

}
//**************************************************************************************************//
//��������� ����� ������
 void  key_init()
{	        				GPIO_InitTypeDef Pin_KEY;
		        				RCC_APB2PeriphClockCmd (RCC_PORT_KEY, ENABLE);
		        				Pin_KEY.GPIO_Speed = GPIO_Speed_50MHz;
		        				Pin_KEY.GPIO_Mode  = GPIO_Mode_IPU;
		        				Pin_KEY.GPIO_Pin   = PIN_KEY_1|PIN_KEY_2|PIN_KEY_3 |PIN_KEY_4;
		        		        GPIO_Init(PORT_KEY, &Pin_KEY);

}
///**********************************************************************************************//
 void  init_in_out()
 {	        				GPIO_InitTypeDef in_out;
 		        				RCC_APB2PeriphClockCmd (RCC_PORT_IN_OUT, ENABLE);
 		        				in_out.GPIO_Speed = GPIO_Speed_50MHz;
 		        				in_out.GPIO_Mode  = GPIO_Mode_Out_PP;
 		        				in_out.GPIO_Pin   = PIN_OUT1|PIN_OUT2;
 		        		        GPIO_Init(PORT_IN_OUT, &in_out);

 }
 //*************���������� �� ������***********************************************************//
 void NVIC_EXTI_Configuration(void)
 {

	 EXTI_InitTypeDef EXTI_key;
	 NVIC_InitTypeDef NVIC_key;


 	    NVIC_key.NVIC_IRQChannel = 40/*|23*/;
 	    NVIC_key.NVIC_IRQChannelPreemptionPriority = 0;
 	    NVIC_key.NVIC_IRQChannelSubPriority = 0;
 	    NVIC_key.NVIC_IRQChannelCmd = 					ENABLE;
 	    NVIC_Init(&NVIC_key);

 	    NVIC_SystemLPConfig(NVIC_LP_SLEEPONEXIT, DISABLE); //����� �� ������ �� ����������

 	    GPIO_EXTILineConfig(PORT_KEY,/*PIN_KEY_1|*/PIN_KEY_2/*|PIN_KEY_3*/);

 	    EXTI_key.EXTI_Line = 		/*EXTI_Line9|*/EXTI_Line10/*|EXTI_Line11|EXTI_Line12*/;
 	    EXTI_key.EXTI_LineCmd = 	ENABLE;
 	    EXTI_key.EXTI_Mode = 		EXTI_Mode_Interrupt;
 	    EXTI_key.EXTI_Trigger = 	EXTI_Trigger_Falling;
 	    EXTI_Init(&EXTI_key);

 	   NVIC_EnableIRQ (EXTI15_10_IRQn);
 	  // NVIC_EnableIRQ (EXTI9_5_IRQn);

 }


//********************************************************************************************//
 //����� ������********���������� ����� ������****/////////

// u8	key_sk(){u8 K; K = keys;keys = 0; return K;}


u8 key ()
{
	if (KEY_1 && !KEY_2 && KEY_3){BIP(150,300); return 4;}
	if (KEY_1 && !KEY_2 && !KEY_3){BIP(150,300);return 1;}
	if (!KEY_1 && KEY_2 && !KEY_3){BIP(150,300);return 2;}
	if (!KEY_1 && !KEY_2 && KEY_3){BIP(150,300);return 3;}
}
//************************************************************************//
void key_sk()
{
	keys = 0;
	if (!KEY_4){BIP(150,300);keys=4;}
	if (!KEY_1){BIP(150,300);keys=1;}
	if (!KEY_2){BIP(150,300);keys=2;}
	if (!KEY_3){BIP(150,300);keys=3;}
}

//********������ � ���������*******************//
void key_st(u8 T)//����� ��������� ������
{
	keys = 0;
	u8 k=0;//��� ���� �������� ������
	while(!KEY_1){BIP(150,300);k++; if(k>T){keys=10;return;}else keys=1;}
	while(!KEY_2){BIP(150,300);k++; if(k>T){keys=20;return;}else keys=2;}
	while(!KEY_3){BIP(150,300);k++; if(k>T){keys=30;return;}else keys=3;}
	while(!KEY_4){BIP(150,300);k++; if(k>T){keys=40;return;}else keys=4;}


}


//***********��������� ����� ��� LED***************////� ����� ���������� ���������
 void blinc_init()
 {				GPIO_InitTypeDef Pin_BLIK;
				RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
				Pin_BLIK.GPIO_Speed = GPIO_Speed_50MHz;
				Pin_BLIK.GPIO_Mode  = GPIO_Mode_Out_PP;
				Pin_BLIK.GPIO_Pin   = GPIO_Pin_13;
		        GPIO_Init(GPIOC, &Pin_BLIK);
		        GPIO_SetBits(GPIOC, GPIO_Pin_13);
 }
//*********������� �����������************************************//
 void blinc (u16 t)  // t ������������� �������� �������
 {
	 if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13))
	 { GPIO_ResetBits(GPIOC, GPIO_Pin_13);//��� ������
	 delay_ms(t);
	 GPIO_SetBits(GPIOC, GPIO_Pin_13);// ���� ������
	 }
	 else
	 {
		 GPIO_SetBits(GPIOC, GPIO_Pin_13);
		 delay_ms(t);
		 GPIO_ResetBits(GPIOC, GPIO_Pin_13);
	 }

 }
//**************���������*******************************************//

 void  ILL_init()
{	        				GPIO_InitTypeDef ILL;
		        				RCC_APB2PeriphClockCmd (RCC_PORT_ILL, ENABLE);
		        				ILL.GPIO_Speed = GPIO_Speed_50MHz;
		        				ILL.GPIO_Mode  = GPIO_Mode_AF_PP;//����������� � �������
		        				ILL.GPIO_Pin   = PIN_ILL ;// ���������
		        		        GPIO_Init(PORT_ILL, &ILL);

		        		        RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
		        		       	 RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

		        		       		    TIM_TimeBaseInitTypeDef tm;
		        		       		    tm.TIM_Prescaler = sysclock*20;
		        		       		    tm.TIM_Period = 20;
		        		       		    tm.TIM_ClockDivision = 0;
		        		       		    tm.TIM_CounterMode = TIM_CounterMode_Up;
		        		       		    TIM_TimeBaseInit (TIM3, &tm);

		        		       		    TIM_OCInitTypeDef tmPWM;
		        		       		    tmPWM.TIM_Pulse = level_ill;
		        		       		    tmPWM.TIM_OCMode = TIM_OCMode_PWM1;
		        		       		    tmPWM.TIM_OutputState = TIM_OutputState_Enable;
		        		       		    tmPWM.TIM_OCPolarity = TIM_OCPolarity_High; //TIM_OCPolarity_Low;//

		        		       		    TIM_OC4Init(TIM3, &tmPWM);
		        		       		  //  TIM_OC4Init(TIM3, &tmPWM);
		        		       		    		//TIM_PWMIConfig(TIM3,TIM_Channel_3);

		        		       		    TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);
		        		       		    TIM_ARRPreloadConfig(TIM3, ENABLE);

		        		       		    	TIM_Cmd(TIM3, ENABLE); //�������� �� �������������!!!

}

 void level (u8 level_ill )
 	 {
	 TIM3->CCR4 = level_ill;
 	 }



 void ILL_ON(){

	 	 	 	 	 	 	 	 	GPIO_InitTypeDef ILL;
	 		        				RCC_APB2PeriphClockCmd (RCC_PORT_ILL, ENABLE);
	 		        				ILL.GPIO_Speed = GPIO_Speed_2MHz;
	 		        				ILL.GPIO_Mode  = GPIO_Mode_AF_PP;//����������� � �������
	 		        				ILL.GPIO_Pin   = PIN_ILL ;// ���������
	 	        		        GPIO_Init(PORT_ILL, &ILL);

	 TIM_Cmd(TIM3,ENABLE);}    //GPIO_SetBits(PORT_ILL, PIN_ILL);}// ���� ����





 void ILL_OFF(){TIM_Cmd(TIM3, DISABLE);

 	 	 	 	 	 	 	 	 GPIO_InitTypeDef ILL;
 		        				RCC_APB2PeriphClockCmd (RCC_PORT_ILL, ENABLE);
 		        				ILL.GPIO_Speed = GPIO_Speed_2MHz;
 		        				ILL.GPIO_Mode  = GPIO_Mode_Out_PP;//����������� � �������
 		        				ILL.GPIO_Pin   = PIN_ILL ;// ���������
 		        		        GPIO_Init(PORT_ILL, &ILL);
  		        		        GPIO_ResetBits(PORT_ILL, PIN_ILL);

 		        		        }//��������� ����


//**************������ ���********************************************//
 void BIP_init()
 {
	 GPIO_InitTypeDef BIP;
	 	RCC_APB2PeriphClockCmd (RCC_PORT_BIP, ENABLE);
	 	BIP.GPIO_Speed = GPIO_Speed_50MHz;
	 	BIP.GPIO_Mode  = GPIO_Mode_Out_PP;
	 	BIP.GPIO_Pin   = PIN_BIP ;//���� ���������
	 	GPIO_Init(PORT_BIP, &BIP);
 }
//**********************************************************************//
 void BIP(int p,int t)//p ������(�������)  t ������������ ��������
 {						// ������������ ��������
	while(t!=0)
	{ GPIO_SetBits(PORT_BIP, PIN_BIP); //���� ������
  	  delay_us(p);
	 GPIO_ResetBits(PORT_BIP, PIN_BIP);////���� �����
	 delay_us(p);
	 t--;
	}
	GPIO_ResetBits(PORT_BIP, PIN_BIP);
 }
//*********************************************************************//
 void BipP(int p,int t)//p ������(�������)  t ������������ ��������
 {						// ������������ ��������
	while(t!=0)
	{ GPIO_SetBits(PORT_BIP, PIN_BIP); //���� ������()
  	  delay_us(p);
	 GPIO_ResetBits(PORT_BIP, PIN_BIP);////���� �����
	 delay_us(p);
	 t--;if(p>1){p--;}
	}
	GPIO_ResetBits(PORT_BIP, PIN_BIP);
 }


//*********************************************************************//
 void BipStop(){ BIP(150,300); delay_ms(50);
 	 	 	 	 BIP(150-20,300); delay_ms(50);
 	 	 	 	 BIP(150-40,300);}

 //********************************************************************//
 void BipExit(){

	 u8 i=150;
	 while(i>50){BIP(i--,20);}

 }
 //*********************************************************************//

