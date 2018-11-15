
#define SYSCLK 72000000
#define PRESCALER 72
#define Fmax (SYSCLK/PRESCALER) //������������ �������
#define NPER 0xFFFF//������ ������� �������
//#define  PORT_MOTO    GPIOB
//#define  X_PIN_STEP    GPIO_Pin_9
//#define  X_PIN_DIR    GPIO_Pin_7
//#define  X_PIN_EN    GPIO_Pin_6

	  _Bool  DR; //���������� ����������� � �������
	  _Bool  EN;
	  _Bool  S;
u16 STEP;
u16 PER; //�������� �� ���������
	float Line;//���� �� ���

 typedef struct
 	{
	 u8 STEP; //������������ ������� �������� ��������
	 //
	 int OB_P; //��������� ��/���
	 u16 AX_P;//��������� ���������� �������� �� ����
	 u16 V_PER_MIN;//�������� ���, ����������� ������ �������

	 _Bool  S_PAR;// STEP �������� ����������������� 1 ��� 0
	 _Bool  D_PAR;//DIR  �������� ����������������� 1 ��� 0
	 _Bool  E_PAR;//ENABLED  �������� ����������������� 1 ��� 0

 	} AXS;// �������� ���������

 	AXS X; //������ ������ ����������� �� ��������
 //	AXS Y;
 //	AXS Z;
 //	AXS A;


 	void INI_STEP_MOTO();
 	void INI_MOTO_GPIO();
 	void INI_MOTO_TIM();
 	 void StartMotor();
 	 void StoptMotor();



