
#include "stm32f10x_iwdg.h"
#include "wdt.h"
#include "stm32f10x.h"

void iwdt_init (u8 dl,u16 schet)
{
	IWDG_WriteAccessCmd(0x5555);//���� ������� � �������
	IWDG_SetPrescaler(dl);//��������� ���� ��������
	IWDG_SetReload(schet);//������������� �������� �������� �������
	IWDG_ReloadCounter(); //������������ ��������
	IWDG_Enable();//��� �������
}
