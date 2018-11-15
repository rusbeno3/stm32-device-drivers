




//unsigned char simv[]={0x08,0x14,0x08,0x03,0x04,0x04,0x03,0x20};//������ �������
//unsigned char moln[]={0x01,0x02,0x04,0x08,0x02,0x04,0x08,0x10};// ������


#define CLEAR 0x01			//	������� ������
#define RETURN_HOME 0x02	//  ��������� � ������ ������

#define SHIFT_POSITION 0x04			//  ����� �������
#define F_SHIFT_KURSOR 0x00		//  ����� ������� ���������� 
#define F_SHIFT_ALL	   0x01		//�����  ������			  
#define F_SHIFT_R 0X02			//  �����  � �����
#define F_SHIFT_L 0x00			//  �����  � ����

#define DISPLEY_MODE	0X08			// ����� �����������
#define F_DISPLEY_ON	0X04			//  ��� �����������
#define F_DISPLEY_OFF 	0x00
#define F_KURSOR_ON	    0X02			//   ������	 ���
#define F_BLINC_ON	    0X01			//   ������� ����������	 ���
#define F_BLINC_OFF	    0X00			//   ������� ����������	 ����

#define DISPLEY_DATA    0X20			 // ����� �����������
#define F_8BIT          0X10
#define F_4BIT          0X00
#define F_2LINE		    0X08			//2 ������
#define F_1LINE         0X00	        //1 C�����
#define F_5X10 	        0X04
#define F_5X8		    0X00

#define CMD_SHIFT      		0X10			// ������� ������
#define F_CMD_SHIFT_ALL		0X08				//	����� ������
#define F_CMD_SHIFT_KURSOR	0X00			   // ����� �������
#define F_CMD_SHIFT_L		0X00				//� ����
#define F_CMD_SHIFT_R		0X04				//� �����

#define F_MESTO       0X80			//��������� � ��������  ������
#define F_RAMM        0X40 			// ��������� � ��������  ������

//��������  � main.h
//#define PORT_LCD       GPIOB
//#define RS 	 	GPIO_Pin_9
//#define RW  	    GPIO_Pin_8
//#define E 	 	GPIO_Pin_7

//#define D7		GPIO_Pin_6		//���� ������
//#define D6		GPIO_Pin_5		//���� ������
//#define D5		GPIO_Pin_4		//���� ������
//#define D4		GPIO_Pin_3  	//���� ������


#define PORT_LCD_ERR       GPIOC
#define PIN_ERR 	 	   GPIO_Pin_13

#define BDATA  1						// ������� ������
#define BCMD   0					// ������� �������

#define BREAD 	 1	
#define BWRITE 	 0	

#define  LCD_CLEAR     LCD_WRITE_4BIT(CLEAR,BCMD,BWRITE)
#define  LCD_HOME      LCD_WRITE_4BIT(RETURN_HOME,BCMD,BWRITE)

#define  LCD_BLINC_ON     LCD_WRITE_4BIT (DISPLEY_MODE|F_DISPLEY_ON|F_BLINC_ON,BCMD,BWRITE)
#define  LCD_BLINC_OFF    LCD_WRITE_4BIT (DISPLEY_MODE|F_DISPLEY_ON|F_BLINC_OFF,BCMD,BWRITE)

#define EE_ON			GPIO_SetBits(PORT_LCD,E)
#define EE_OFF			GPIO_ResetBits(PORT_LCD,E)
#define READ_BUSE 		GPIO_SetBits(PORT_LCD,RW); delay_us(10);GPIO_ResetBits(PORT_LCD,RS)

#define STROB_   EE_ON;delay_us(5);EE_OFF			   //������ ���������� �������


 void PORT_LCD_INI();
 void LCD_WRITE_4BIT(u8 DATA,_Bool RS_,_Bool RW_);
 void PORT_INI_F_LCD_IN ();
 void PORT_INI_F_LCD_OUT ();
 void LCD_F_BUSY ();
 void LCD_INI ();
 void LCD_GOTO (u8 X, u8 Y);
 void LCD_SETPC ( unsigned char c[]);
 void LCD_PUTC ( unsigned char c);
 void LCD_PUTS (unsigned char *str);
 void LCD_PUTST (unsigned char *str,u8 L);

