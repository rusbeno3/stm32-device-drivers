
//#include "stm32f10x_conf.h"
 #include "stm32f10x_gpio.h"
 #include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "delay.h"

//#include "prtf.h"
#include "lcd_ht1621_7_4.h"
#include "main.h"



	unsigned char const dec[]={0xD7, 0x50, 0xB5, 0xF1, 0x72, //0-4
	 				  	  0xE3, 0xE7, 0x51, 0xF7, 0xF3}; //5-9



//*********************************************************************************//

void LCDPORT_INI()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	   GPIO_InitTypeDef LCDPORT_;
	   LCDPORT_.GPIO_Pin = DATA|CS|WR;
	   LCDPORT_.GPIO_Speed = GPIO_Speed_50MHz;
	   LCDPORT_.GPIO_Mode = GPIO_Mode_Out_PP;
	   GPIO_Init(LCDPORT, &LCDPORT_);

	   // Disable JTAG for release LED PIN
	      RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	   	   AFIO->MAPR |= AFIO_MAPR_SWJ_CFG_JTAGDISABLE;
}
//**********************************************************************************//
void lcd_init(void)
{
	LCDPORT_INI();
	//set_lcd_com(0x28); //1/2bias��4comm
	set_lcd_com(0x29); //1/3bias��4comm ������ �� ��������
	//set_lcd_com(0xE3);//������ ���������
	set_lcd_com(0x03); //Open INTOSC
	set_lcd_com(0x01); //Enable Display
	lcd_clr();
	//������� �������� ��������
	all_lcd_data("----",4,1);

}

void lcd_clr()
{				//��� 4
	set_dat;
	u8 i;
    for (i=0;i<38;i++)
    {
    	 WR_LOW;
    	 DATA_LOW;
    	 WR_HIGH;
    }

    CS_HIGH;
}



//*/**********************************************************************************//
void set_lcd_com(unsigned char com)
{
     unsigned short int i =0;

     set_com;

    for (i =0;i<=7;i++)
     {
         WR_LOW;
         if ((com & 0x80) !=0) {DATA_HIGH;}
          else  DATA_LOW;
         	 	 WR_HIGH;
         com = com << 1;
     }

    WR_LOW;
    WR_HIGH;

    CS_HIGH;
}
//*******************************************************************************//
void set_lcd_data(unsigned short int address,unsigned short int data)
{
	unsigned short int i =0;

	set_dat;

    address = address << 2;
    for ( i =0;i<=5;i++)
     {
         WR_LOW;
         if ((address & 0x80) !=0) {DATA_HIGH;}
          else DATA_LOW;
         WR_HIGH;
         address = address << 1;
     }

     for (i =0;i<=3;i++)
     {
         WR_LOW;
         if ((data & 0x01) !=0) {DATA_HIGH;}
          else DATA_LOW;
         WR_HIGH;
         data = data >> 1;
     }

    CS_HIGH;
}

//*****************************************************************************//

void all_lcd_data(unsigned char temp[],u8 R, _Bool sek )    // ������ ���� ��� ������ ��������, ����������� ��������.
{
	u8 i =0;
	u8 j=0;
	u8 g=0;
	unsigned char temp_data;

   set_dat; // ���������� ��� ����� ������

    for (i =0;i<6;i++)//������� ����� 00
    {
         WR_LOW;
         DATA_LOW;
         WR_HIGH;
     }

    for (i=0;i<R;i++)  //������� �� ��������
    {	//��������� ������ ���� � �������
    	if(temp[i]=='.'){g = 1;i++;R++;}//����� ����� ������� �� �� ���� ���,}
    	if(temp[i]>=0x30 && 0x39>=temp[i]){temp_data= dec[temp[i]-0x30];}//����� �����

    	else{
    		switch (temp[i]) {
			case '-': temp_data = 0x20; break;
			case '_': temp_data = 0x80; break;
			case 'd': temp_data = 0xF4; break;
			case 'E': temp_data = 0xA7; break;
			case 't': temp_data = 0xA6; break;
			case 'f': temp_data = 0x28; break;
			case 'P': temp_data = 0x37; break;
			case 'o': temp_data = 0xE4; break;
			case 'u': temp_data = 0xC4; break;
			case 'A': temp_data = 0x77; break;
			case 'c': temp_data = 0x87; break;
			default:  temp_data = temp[i]; break;
    	  	  	  	  	  }
    	}
    	if(g==1){temp_data |= 0x08; g=0;}//���������� ������� ��������� �����.
    	if(i==0 && sek==1){temp_data|=0x08;}//������ ��������� �� ����������

        for (j=0;j<8;j++) 		//������� ����������
        {
             WR_LOW;
             if ((temp_data & 0x01) !=0) {DATA_HIGH;}
             else  DATA_LOW;
             WR_HIGH;
             temp_data = temp_data >> 1;
        }
    }

    CS_HIGH;
}
//*********************************************************************************//





