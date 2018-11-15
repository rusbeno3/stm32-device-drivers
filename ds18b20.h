

#include "stm32f10x.h"
#include "delay.h"
#include  "stm32f10x_usart.h"

#define config_ds18b20 0xff
/***************************************/
//� ���� �� ������
/***************************************/
#define PORT_DS18B20  GPIOB
#define DS18B20       GPIO_Pin_11

void PORT_DS18B20_IN();
void PORT_DS18B20_OUT();
void RESET_DS18B20();
_Bool CHEK_DS18B20 (void);
void WRITE_BYTE_DS18B20 (u8 date);
_Bool READ_BIT_DS18B20 (void);
u8 READ_BYTE_DS18B20 (void);
void START_DS18B20(void);
short GET_TEMP_DS18B20(void);

/**************************************/
//����� Usart
/*************************************/
/*
 * #define USART_DS18B20   USART3
#define Rx_USART_DS18B20 GPIO_Pin_11
#define Tx_USART_DS18B20 GPIO_Pin_10
#define PORT_USART_DS18B20 GPIOB

*/

#define SEARCH_ROM   0xF0 // ���������������� ���� ROM ���� ������� ��������� �� ����.
#define READ_ROM     0x33 // ���� �������. ��� ��������� ������� ���� ������ 64-��������� ��� ROM ��������
#define MATCH_ROM    0x55  //�������������� 64-��������� ����� ROM, ��������� ������� ���� ���������� � ������������� �������� �� ������������� ��� ������������ ����
#define SKIP_ROM     0xCC // ��� �������������� ��������� �� ���� ����������� �� ����, �� ��������� ���������� � ���� ROM
#define ALARM_SEARCH 0xEC // ������� ������ ������� � ������������� ������ �������
#define CONVERT_T    0x44 // �������������� ���� �������������� �����������
#define WRITE_SCRATCHPAD 0x4E //���������� 3 ����� ������ ����������� ������ DS18B20
#define READ_SCRATCHPAD 0xBE //������ ���������� ����������� �����
#define COPY_SCRATCHPAD 0x48 //�������� ���������� ����������� ��������� TH, TL � ������������ (����� 2, 3 � 4 � EEPROM.
#define REC_SCRATCHPAD    0xB8 //�������� �������� ������  � ������������ �� EEPROM  � �������� 2, 3, � 4 ����������� ������, ��������������
#define READ_POWER_SUPPLY 0xB4 //������������ �� �� ���� DS18B20 � ���������� ��������.
unsigned char code[8];//���� ����� ��� ���
unsigned char data[9];//������ ������
_Bool   cont_circut; //��� ����������� ���� ����������� �������

#define  COF_P  0.0625 //��� ���������� �������  0.5�C, 0.25�C, 0.125�C, � 0.0625�C
#define  COF_AP  0.125	//��� ����������  ��� ������� �������
#define	TL_  data[0]//������
#define	TH_  data[1]//������
#define	ATH_  data[2]//����������� ������ �������� �������
#define	ATL_  data[3]//����������� ����������� ������� �������
#define CFG_  data[4]//���� ������������
#define RCRC  data[8]//����������� �����
#define	AFTH_  data[2]&0x80//���� �������� �������
#define	AFTL_  data[3]&0x80//���� ������� �������






void Init_USART_GPIO_DS18B20();
_Bool Reset_USART_DS18B20();
void Write_USART_DS18B20(u8 cmd);
u8 Read_byt_USART_DS18B20();
void Start_USART_DS18B20();
void Get_Rom_USART_DS18B20 (u8 *rom);
void Set_Rom_USART_DS18B20 (u8 *rom);
void GET_RAM_USART_DS18B20(u8 rom[],u8 *dat);
unsigned char iButtonCRC( unsigned char *code);
void Set_CFG_USART_DS18B20 (u8 *rom,u8 H_,u8 L_,u8 CFG);
_Bool CHEK_TEMP_DS18B20 (u8 TH, u8 TL);
float CONV_TEMP_DS18B20 (float C, u8 TH, u8 TL);//�����ר� � �������
void TEMP_CONF_DS18B20 (u16 T,float C,u8 *R);
void COF_DS18B20 (float COF);//���������� ���������� �� ������������
void Get_CFG_USART_DS18B20 (u8 *rom, u8 *dat);
_Bool Control_circut ();
unsigned char crc(char *code);
_Bool crc_check(unsigned char *code);

