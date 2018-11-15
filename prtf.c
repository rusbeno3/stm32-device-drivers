#include "stm32f10x.h"
#include "prtf.h"



void _sprtf(char *buf, short d)
	{	short rz = d;
			do
				{*buf++; rz/=10;}
			while (rz != 0);
				   *buf = 0;
			do
				{*buf--;
					(*buf) = (d%10 + '0');
					d=d/10;}
				while (d != 0);
	}

void _sprtff(u8 S, char *buf, float d)//����������� ���� ����� �������
{	u8 tt;

	if (d<0){*buf++='-'; d *= -1;}
		if(S>0){for(tt=S;tt--;tt>0){d = d*10;}
				/**buf++;*/ S+=2;}

	u16 R;
	R = d;
	tt=0;
	do
		{	if(S>0 && tt==1){*buf++ = '.';tt++;}
				else{*buf++='0'; R/=10;tt++;}}
				while (R != 0 || tt <S);
					*buf = 0;
	R = d;
	S--;
		do
			{ buf--;

			if(S==1){*buf = '.';S--;}
			else {(*buf) = (R%10 + '0');
			R /=10; S--;}
			}
		while (R != 0 );

}

void _sprtffd(u8 S, unsigned char *buf, float d)// S ����������� ���� ����� �������
{
	unsigned char B[10];
	u32 R;
	u8 i = 0;

		if (d<0){*buf++='-'; d *= -1;}//��������� ������������� ��������

			R = d;
	if	(S!=0)
	{		while (S!=0)
			{B[i]= R%10 + '0'; R/=10; i++; S--; }//  �� ����� ��������
		B[i]= '.'; i++;
	}
		do { B[i]= R%10 + '0'; R/=10; i++; }//  �� ����� ��������
	while (R!=0);

		//i++;
		do {
		i--;*buf++ = B[i];  }
		while(i!=0);

		*buf++ = 0;
		*buf++ = 0;

	}

void _sprtff16(u8 S, u16 *buf, float d)// S ����������� ���� ����� �������
{
	unsigned char B[10];
	u32 R;
	u8 i = 0;

		if (d<0){*buf++='-'; d *= -1;}//��������� ������������� ��������

			R = d;
	if	(S!=0)
	{		while (S!=0)
			{B[i]= R%10 + '0'; R/=10; i++; S--; }//  �� ����� ��������
		B[i]= '.'; i++;
	}
		do { B[i]= R%10 + '0'; R/=10; i++; }//  �� ����� ��������
	while (R!=0);

		//i++;
		do {
		i--;*buf++ = B[i];  }
		while(i!=0);

		*buf++ = 0;
		*buf++ = 0;

	}


unsigned char  D_To_H(unsigned char H)//��������� � ����
{
	if(H > 9)
	{switch(H)
{
case 10: H='A'; return H;
case 11: H='B'; return H;
case 12: H='C'; return H;
case 13: H='D'; return H;
case 14: H='E'; return H;
case 15: H='F'; return H;
}
	}else H+='0';
	return H;
}


void _sprtf16(unsigned char *buf, unsigned char d)
	{
				*buf++ =D_To_H(d/16);
				*buf++ =D_To_H(d%16);
				*buf =	0;
	}
//*************����������� ������ �����***********************************************//

void chek_str(char *buf, unsigned char d)//d ������ ������ � ��������
{
	while(d--)
	{	*buf++;
		if(d == 1){if( *buf == '.'){*buf = ' ';}  }
		if(d == 0){*buf = 0;}
	}
}

void chek_str_dir(char *buf, unsigned char d, _Bool dir )//d ������ ������ � ��������, dir ��������� ������
{
	if(dir)//** ����������� �����������
		{u8 i=0; //********������ �����
			//u8 cl[10];//**��������� ������oo
			while(buf[i]!=0)// ���������� ������ ������
			{i++;}

		if(i!=d){u8 b=d;buf[b+1]=0;
			while(i!=0)// ������������ �����������
			{ buf[b--]= buf[i--];
			//buf[i+1] = ' ';
			}


		}
	}

	while(d--)//*������������ ������
	{	*buf++;
		if(d == 1){if( *buf == '.'){*buf = ' ';}  }
		if(d == 0){*buf = 0;}
	}


}




//************************************************************************//



//**************************************************************************//
