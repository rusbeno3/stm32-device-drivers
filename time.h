/**************************************************************************
 * ������ ���������� ������������� ��� ������ � RTC, � ������ � Unix Time *
 * ��������� ���������� �� �������� � ���������(����, �����, ���) 		  *
 * � ����� (����, ������, �������), � �������							  *
 **************************************************************************/
 //#include "stm32f10x.h"

#define tm_def   1521000000  // ������ ���������� �� ���������
#define SEC_A_DAY 86400
typedef struct	   
	{
	int  year;
	char mon;
	char mday;
	char wday;
	char hour;
	char min;
	char sec;
	} unix_cal;// �������� ���������

	unix_cal unix_time; //������ ������ ����������� �� ��������
	unix_cal set_time; // ������ ��� ��������� �����

//u8 const *WEEK_STR[]= {"���.","���.","���.","���.","���.","���.","���."};

void timer_to_cal (unsigned long timer , unix_cal * unix_time);

void RTC_Configuration(void);
//void RTC_IRQHandler(void);
void NVIC_Configuration(void);
unsigned long cal_to_timer (unix_cal * unix_time);
void Init_Timer4 ();


