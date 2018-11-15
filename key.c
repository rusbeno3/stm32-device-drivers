#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include<stm32f10x_rcc.h>
#include "stm32f10x_conf.h"
#include "delay.h"

#include "d_7_led.h"
#include <stdio.h>

#include "main.h"
#include "key.h"
/*
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

void  key_ini(){
	key_init();
	blinc_init();
	 BIP_init();
	init_in_out();
	KEY_D;//������ ��������� � ���� D - �� �����
}

//��������� ����� ������
 void  key_init()
{	        				GPIO_InitTypeDef Pin_KEY;
		        				RCC_APB2PeriphClockCmd (RCC_PORT_KEY, ENABLE);
		        				Pin_KEY.GPIO_Speed = GPIO_Speed_50MHz;
		        				Pin_KEY.GPIO_Mode  = GPIO_Mode_IPU;
		        				Pin_KEY.GPIO_Pin   = PIN_KEY_1|PIN_KEY_2|PIN_KEY_3 |PIN_KEY_4;
		        		        GPIO_Init(PORT_KEY, &Pin_KEY);

}
///*/////////////////////////////////////////////////////////////////////
 void  init_in_out()
 {	        				GPIO_InitTypeDef in_out;
 		        				RCC_APB2PeriphClockCmd (RCC_PORT_IN_OUT, ENABLE);
 		        				in_out.GPIO_Speed = GPIO_Speed_50MHz;
 		        				in_out.GPIO_Mode  = GPIO_Mode_Out_PP;
 		        				in_out.GPIO_Pin   = PIN_OUT1|PIN_OUT2;
 		        		        GPIO_Init(PORT_IN_OUT, &in_out);

 }

//**********************************************************************//
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
void key_st(u8 T)//����� ���������
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
		        				ILL.GPIO_Mode  = GPIO_Mode_Out_PP;
		        				ILL.GPIO_Pin   = PIN_ILL ;//���� ���������
		        		        GPIO_Init(PORT_ILL, &ILL);

}
 void ILL_ON(){GPIO_SetBits(PORT_ILL, PIN_ILL);}// ���� ����
 void ILL_OFF(){GPIO_ResetBits(PORT_ILL, PIN_ILL);}//��������� ����


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


