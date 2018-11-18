#include "input.h"
#include "keyboard.h"
#include "nmouse.h"
#include<stdio.h>
#include<bios.h>
#include <graphics.h>
#include<conio.h>
/***********************************************************
Function: RegisteraccountsInput
Description: 1���û�ע�������˺����뺯��
             2��ֻ���Ǵ�Сд��ĸ������
             3��������1��10λ
Attention:���λ�ò�������Ҫ��ָ����ʽ���ݹ�����
Return:����2��userRegister�е���LogincodeInput����
       ����3��userRegister�е���RegistersecondcodeInput����
       ����4��userRegister��ʹ�õ�½����
       ����5��userRegister��ʹ��ע�Ṧ��
************************************************************/
int RegisteraccountsInput(char *accounts, int *mx, int *my) 
{
	int key;    //��ʾ��ֵ�ı���
	int i = 0;   //���ڼ�����������ַ���Ŀ�ı���
	char *p = accounts;   //�����ַ����м�ָ�����
	char ch;     //������ʱ�����ֵ����Ӧ�ַ��ı���
	int buttons;    //���Ĳ�������
	char temp[2] = { '\0','\0' };  //����outtextxy������������ַ�������

    /*ʹpָ��'\0',i��ʾ��ǰ�ַ���*/
	while (*p != '\0')
	{
		i++;
		p++;
	}

	/*����*/
	AddFrame(*mx, *my, 199, 119, 551, 166, RED);

	while (1)
	{
		newxy(mx, my, &buttons);

		/*���ü�ֵ���õ��¼�ֵ*/
		key = 0;
		if (kbhit() != 0)
		{
			key = bioskey(0);
		}

		/*if(����һ��enter������������������������һ���·����)����2��ʾ����RegistercodeInput����*/
		if (*mx >= 200 && *mx <=550 && *my >= 200 && *my <= 245 && buttons || key == 0x1c0d || key == 0x5000)
		{
			AddFrame(*mx, *my, 199, 119, 551, 166, BLACK);
			return 2; 
		}

		/*if���������һ�������������򣩷���3��ʾ����RegistersecondcodeInput����*/
		if (*mx >= 200 && *mx <= 550 && *my >= 280 && *my <= 325 && buttons)
		{
			AddFrame(*mx, *my, 199, 119, 551, 166, BLACK);
			return 3;       
		}

		/*if(���ע���������)����4��ʾע����ɲ����͵�¼���� */
		if (*mx >= 230 && *mx <= 460 && *my >= 360 && *my <= 415 && buttons)
		{
			AddFrame(*mx, *my, 199, 119, 551, 166, BLACK);
			return 4;       
		}

		/*if(��������˺Ų���¼����)����5��ʾ���ص�½����*/
		if (*mx >= 300 && *mx <= 455 && *my >= 437 && *my <= 455 && buttons)
		{
			AddFrame(*mx, *my, 199, 119, 551, 166, BLACK);
			return 5;       
		}

		/*���˻�ɾ��*/
		if (key == 0xe08)
		{
			if (p != accounts)
			{
				setfillstyle(1, WHITE);
				bar(180 + i * 30, 121, 210 + i * 30, 164);
				backgroundChange(*mx, *my, 180 + i * 30, 121, 210 + i * 30, 164);
				p--;
				i--;
			}
			*p = '\0';
		}

		/*��������Ӧ���ַ�����accounts������*/
		ch = searchKeyValue(key);
		if (ch != '\0'&&i<10)
		{
			setfillstyle(1, WHITE);
			bar(210 + i * 30, 121, 240 + i * 30, 164);
			temp[0] = ch;
			settextstyle(1, 0, 4);
			setcolor(BLACK);
			outtextxy(210 + i * 30, 120, temp);

			backgroundChange(*mx, *my, 210 + i * 30, 121, 240 + i * 30, 164);

			*p = ch;
			p++;
			*p = '\0';
			i++;
		}

	}
}

/***********************************************************
Function: RegistercodeInput
Description: 1���û�ע�������������뺯��
             2��ֻ���Ǵ�Сд��ĸ������
             3��������1��10λ
Attention:���λ�ò�������Ҫ��ָ����ʽ���ݹ�����
Return:����1��userRegister�е���RegisteraccountsInput����
       ����3��userRegister�е���RegistersecondcodeInput����
       ����4��userRegister��ʹ�õ�½����
       ����5��userRegister��ʹ��ע�Ṧ��
************************************************************/
int RegistercodeInput(char *code, int *mx, int *my) //��½�������������뺯��
{
	int key;     //��ʾ��ֵ�ı���
	int i = 0;   //���ڼ�����������ַ���Ŀ�ı���
	char *p = code;     //�����ַ����м�ָ�����
	char ch;     //������ʱ�����ֵ����Ӧ�ַ��ı���
	int buttons;     //���Ĳ�������

	/*��ס����������ʾ��������*/
	if (*code == '\0')
	{
		setfillstyle(1, WHITE);
		bar(200, 200, 550, 245);

		backgroundChange(*mx, *my, 200, 200, 550, 245);
	}

	/*����*/
	AddFrame(*mx, *my, 199, 199, 551, 246, RED);

	/*ʹpָ��'\0',i��ʾ��ǰ�ַ���*/
	while (*p != '\0')
	{
		i++;
		p++;
	}

	while (1)
	{
		newxy(mx, my, &buttons);

		/*���ü�ֵ���õ��¼�ֵ*/
		key = 0;
		if (kbhit() != 0)
		{
			key = bioskey(0);
		}

		/*if(������˺������������һ���Ϸ����)����1��ʾ����RegisteraccountsInput����*/
		if (*mx >= 200 && *mx <=550 && *my >= 120 && *my <= 165 && buttons || key == 0x4800)
		{
			AddFrame(*mx, *my, 199, 199, 551, 246, BLACK);
			return 1; 
		}

		/*if(������ٴ����������������һ��enter�����·����) ����3��ʾ����RegistersecondcodeInput����*/
		if (*mx >= 200 && *mx <= 550 && *my >= 280 && *my <= 325 && buttons || key == 0x5000 || key == 0x1c0d)
		{
			AddFrame(*mx, *my, 199, 199, 551, 246, BLACK);
			return 3;
		}

		/*if(���ע���������) ����4��ʾע����ɲ���½*/
		if (*mx >= 230 && *mx <= 460 && *my >= 360 && *my <= 415 && buttons)
		{
			AddFrame(*mx, *my, 199, 199, 551, 246, BLACK);
			return 4;    
		}

		/*if(��������˺�����) ����5��ʾ���ص�½����*/
		if (*mx >= 300 && *mx <= 455 && *my >= 437 && *my <= 455 && buttons)
		{
			AddFrame(*mx, *my, 199, 199, 551, 246, BLACK);
			return 5;       
		}

		/*���˻�ɾ��*/
		if (key == 0xe08)
		{
			if (p != code)
			{
				setfillstyle(1, WHITE);
				bar(172 + i * 30, 201, 202 + i * 30, 244);

				backgroundChange(*mx, *my, 172 + i * 30, 201, 202 + i * 30, 244);

				p--;
				i--;
			}
			*p = '\0';
		}

		/*����ֵ����code����*/
		ch = searchKeyValue(key);
		if (ch != '\0'&&i<10)
		{
			*p = ch;
			p++;
			*p = '\0';
			i++;

			setfillstyle(1, WHITE);
			bar(172 + i * 30, 201, 202 + i * 30, 244);
			setcolor(BLACK);
			setfillstyle(1, BLACK);
			pieslice(187 + i * 30, 223, 0, 360, 13);

			backgroundChange(*mx, *my, 172 + i * 30, 201, 202 + i * 30, 244);
		}
	}
}


/***********************************************************
Function: RegistersecondcodeInput
Description: 1���û�ע����������ڶ������뺯��
             2��ֻ���Ǵ�Сд��ĸ������
             3��������1��10λ
Attention:���λ�ò�������Ҫ��ָ����ʽ���ݹ�����
Return:����1��userRegister�е���RegisteraccountsInput����
       ����2��userRegister�е���RegistercodeInput����
	   ����4��userRegister��ʹ�õ�½����
	   ����5��userRegister��ʹ��ע�Ṧ��
************************************************************/
int RegistersecondcodeInput(char *secondcode, int *mx, int *my)
{
	int key;     //��ʾ��ֵ�ı���
	int i = 0;   //���ڼ�����������ַ���Ŀ�ı���
	char *p = secondcode;     //�����ַ����м�ָ�����
	char ch;     //������ʱ�����ֵ����Ӧ�ַ��ı���
	int buttons=0;     //���Ĳ�������

	/*����*/
	AddFrame(*mx, *my, 199, 279, 551, 326, RED);

	/*ʹpָ��'\0',i��ʾ��ǰ�ַ���*/
	while (*p != '\0')
	{
		i++;
		p++;
	}

	while (1)
	{
		newxy(mx, my, &buttons);

		/*���ü�ֵ���õ��¼�ֵ*/
		key = 0;
		if (kbhit() != 0)
		{
			key = bioskey(0);
		}

		/*if(������˺���������)����1��ʾ����RegisteraccountsInput����*/
		if (*mx >= 200 && *mx <= 550 && *my >= 120 && *my <= 165 && buttons)
		{
			AddFrame(*mx, *my, 199, 279, 551, 326, BLACK);
			return 1;          
		}

		/*if(����������������������һ���Ϸ����)����2��ʾ����RegistercodeInput����*/
		if (*mx >= 200 && *mx <= 550 && *my >= 200 && *my <= 245 && buttons || key == 0x4800)
		{
			AddFrame(*mx, *my, 199, 279, 551, 326, BLACK);
			return 2; 
		}

		/*if(����һ��enter��������½����)����4��ʾע����ɲ���½*/
		if (*mx >= 230 && *mx <= 460 && *my >= 360 && *my <= 415 && buttons || key == 0x1c0d)
		{
			AddFrame(*mx, *my, 199, 279, 551, 326, BLACK);
			return 4;      
		}

		/*if(��������˺�����)����5��ʾ���ص�½����*/
		if (*mx >= 300 && *mx <= 455 && *my >= 437 && *my <= 455 && buttons)
		{
			AddFrame(*mx, *my, 199, 279, 551, 326, BLACK);
			return 5;    
		}

		/*���˻�ɾ��*/
		if (key == 0xe08)
		{
			if (p != secondcode)
			{
				setfillstyle(1, WHITE);
				bar(173 + i * 30, 282, 201 + i * 30, 323);
				backgroundChange(*mx, *my, 173 + i * 30, 282, 201 + i * 30, 323);

				p--;
				i--;
			}
			*p = '\0';
		}

		/*����ֵ����secondcode����*/
		ch = searchKeyValue(key);
		if (ch != '\0'&&i<10)
		{
			*p = ch;
			p++;
			*p = '\0';
			i++;

			setfillstyle(1, WHITE);
			bar(173 + i * 30, 282, 201 + i * 30, 323);
			setcolor(BLACK);
			setfillstyle(1, BLACK);
			pieslice(187 + i * 30, 303, 0, 360, 13);

			backgroundChange(*mx, *my, 173 + i * 30, 282, 201 + i * 30, 323);
		}
	}
}


/***********************************************************
Function: searchInput
Description: ����������뺯��
Attention:
Return:1������0��ʾ�˳������Ҳ������κ���������
       2������2��ʾ����һ�������н�����ƴ����
************************************************************/
int  searchInput(char *abbreviation, int *mx,  int *my)
{
	int key;    //��ʾ��ֵ�ı���
	int i = 0;   //���ڼ�����������ַ���Ŀ�ı���
	char *p = abbreviation;   //�����ַ����м�ָ�����
	char ch;     //������ʱ�����ֵ����Ӧ�ַ��ı���
	int buttons;    //���Ĳ�������
	char temp[2] = { '\0','\0' };  //����outtextxy������������ַ�������

    /*ʹpָ��'\0',i��ʾ��ǰ�ַ���*/
	while (*p != '\0')
	{
		i++;
		p++;
	}

	/*����*/
	setlinestyle(0, 0, 3);
	AddFrame(*mx, *my, 125, 410, 425, 450 , BROWN);
	setlinestyle(0, 0, 1);

	while (1)
	{
		newxy(mx, my, &buttons);

		/*���ü�ֵ���õ��¼�ֵ*/
		key = 0;
		if (kbhit() != 0)
		{
			key = bioskey(0);
		}

		/*if(������������������)����0��ʾ�˳�����*/
		if (buttons&&(*mx <=125 || *mx >= 425|| *my <= 410|| *my >=450))
		{
			setlinestyle(0, 0, 3);
			AddFrame(*mx, *my, 125, 410, 425, 450 , WHITE);
			setlinestyle(0, 0, 1);
			AddFrame(*mx, *my, 125, 410, 425, 450, BROWN);
			return 0;
		}

		/*if(���������ť)����2��ʾ��search�����н�����ƴ����*/
		if (*mx >= 425 && *mx <= 475 && *my >= 410 && *my <= 450 && buttons)
		{
			setlinestyle(0, 0, 3);
			AddFrame(*mx, *my, 125, 410, 425, 450, WHITE);
			setlinestyle(0, 0, 1);
			AddFrame(*mx, *my, 125, 410, 425, 450, BROWN);
			return 2;
		}

		/*���˻�ɾ��*/
		if (key == 0xe08)
		{
			if (p != abbreviation)
			{
				setfillstyle(1, WHITE);
				bar( 125+ i * 18, 412, 143 + i * 18 , 448);
				backgroundChange(*mx, *my, 125+ i * 18, 412, 143 + i * 18 , 448);
				p--;
				i--;
			}
			*p = '\0';
		}

		/*��������Ӧ���ַ�����abbreviation������*/
		ch = searchKeyValue(key);
		if (ch != '\0'&&i<15)
		{
			setfillstyle(1, WHITE);
			bar(143+ i * 18, 412, 161 + i * 18 , 448);
			temp[0] = ch;
			settextstyle(1, 0, 2);
			setcolor(BLUE);
			outtextxy(143 + i * 18, 412, temp);

			backgroundChange(*mx, *my, 143+ i * 18, 412, 161 + i * 18 , 448);

			*p = ch;
			p++;
			*p = '\0';
			i++;
		}

	}
}


/***********************************************
Function: oldcodeinput
Description: 1��������Ϣ������˺����뺯��
             2��ֻ���Ǵ�Сд��ĸ������
             3��������1��10λ
Attention:���λ�ò�������Ҫ��ָ����ʽ���ݹ�����
Return:
************************************************/
int oldcodeinput(char *code, int *mx, int *my)
{
	int key;    //��ʾ��ֵ�ı���
	int i = 0;   //���ڼ�����������ַ���Ŀ�ı���
	char *p = code;   //�����ַ����м�ָ�����
	char ch;     //������ʱ�����ֵ����Ӧ�ַ��ı���
	int buttons;    //���Ĳ�������
	char temp[2] = { '\0','\0' };  //����outtextxy������������ַ�������


	/*ʹpָ��'\0',i��ʾ��ǰ�ַ���*/
	while (*p != '\0')
	{
		i++;
		p++;
	}

	/*����*/
	AddFrame(*mx, *my, 250, 100, 400, 130, RED);

	while (1)
	{
		newxy(mx, my, &buttons);

		/*���ü�ֵ���õ��¼�ֵ*/
		key = 0;
		if (kbhit() != 0)
		{
			key = bioskey(0);
		}

		/* if(����һ��enter������������������������һ���·����)����1��ʾ����newcodeinput����*/
		if (*mx >= 250 && *mx <= 400 && *my >= 140 && *my <= 170 && buttons || key == 0x1c0d || key == 0x5000)
		{
			AddFrame(*mx, *my, 250, 100, 400, 130, BLUE);
			return 1;
		}

		/* if(���������������������)����2��ʾ����secondcodeinput����*/
		if (*mx >= 250 && *mx <= 400 && *my >= 200 && *my <= 230 && buttons)
		{
			AddFrame(*mx, *my, 250, 100, 400, 130, BLUE);
			return 2;
		}

		/*������޸�����*/
		if (*mx >= 295 && *mx <= 345 && *my >= 250 && *my <= 280 && buttons)
		{
			AddFrame(*mx, *my, 250, 100, 400, 130, BLUE);
			return 3;
		};

		/*������˻�ɾ��*/
		if (key == 0xe08)
		{
			if (p != code)
			{
				setfillstyle(1, WHITE);
				bar(249 + i * 11, 103, 260 + i * 11, 127);
				backgroundChange(*mx, *my, 249 + i * 11, 103, 260 + i * 11, 127);
				p--;
				i--;
			}
			*p = '\0';
		}

		/*��������Ӧ���ַ�����accounts������*/
		ch = searchKeyValue(key);
		if (ch != '\0'&&i<10)
		{
			/*���ַ���ʾ����*/
			setfillstyle(1, WHITE);
			bar(260 + i * 11, 103, 271 + i * 11, 127);
			temp[0] = ch;
			settextstyle(2, 0, 6);
			setcolor(BLUE);
			outtextxy(260 + i * 11, 107, temp);
			backgroundChange(*mx, *my, 260 + i * 11, 101, 271 + i * 11, 129);

			/*���ַ�����������*/
			*p = ch;
			p++;
			*p = '\0';
			i++;
		}

	}
}

/***********************************************
Function: newcodeinput
Description: 1��������Ϣ������˺����뺯��
2��ֻ���Ǵ�Сд��ĸ������
3��������1��10λ
Attention:���λ�ò�������Ҫ��ָ����ʽ���ݹ�����
Return:
************************************************/
int newcodeinput(char *code, int *mx, int *my)
{
	int key;    //��ʾ��ֵ�ı���
	int i = 0;   //���ڼ�����������ַ���Ŀ�ı���
	char *p = code;   //�����ַ����м�ָ�����
	char ch;     //������ʱ�����ֵ����Ӧ�ַ��ı���
	int buttons;    //���Ĳ�������


								   /*ʹpָ��'\0',i��ʾ��ǰ�ַ���*/
	while (*p != '\0')
	{
		i++;
		p++;
	}

	/*����*/
	AddFrame(*mx, *my, 250, 140, 400, 170, RED);

	while (1)
	{
		newxy(mx, my, &buttons);

		/*���ü�ֵ���õ��¼�ֵ*/
		key = 0;
		if (kbhit() != 0)
		{
			key = bioskey(0);
		}

		/* if(��������������������һ���Ϸ����)����0��ʾ����oldcodeinput����*/
		if (*mx >= 250 && *mx <= 400 && *my >= 100 && *my <= 130 && buttons || key == 0x4800)
		{
			AddFrame(*mx, *my, 250, 140, 400, 170, BLUE);
			return 0;
		}

		/* if(����һ��enter������������������������һ���·����)����2��ʾ����secondcodeinput����*/
		if (*mx >= 250 && *mx <= 400 && *my >= 200 && *my <= 230 && buttons || key == 0x1c0d || key == 0x5000)
		{
			AddFrame(*mx, *my, 250, 140, 400, 170, BLUE);
			return 2;
		}

		/*������޸�����*/
		if (*mx >= 295 && *mx <= 345 && *my >= 250 && *my <= 280 && buttons)
		{
			AddFrame(*mx, *my, 250, 140, 400, 170, BLUE);
			return 3;
		};

		/*������˻�ɾ��*/
		if (key == 0xe08)
		{
			if (p != code)
			{
				setfillstyle(1, WHITE);
				bar(249 + i * 11, 143, 260 + i * 11, 167);
				backgroundChange(*mx, *my, 249 + i * 11, 143, 260 + i * 11, 167);
				p--;
				i--;
			}
			*p = '\0';
		}

		/*��������Ӧ���ַ�����accounts������*/
		ch = searchKeyValue(key);
		if (ch != '\0'&&i<10)
		{
			/*��һ��Բ*/
			setfillstyle(1, WHITE);
			bar(260 + i * 11, 143, 271 + i * 11, 167);
			setcolor(BLUE);
			setfillstyle(1, BLUE);
			pieslice(265 + i * 11, 155, 0, 360, 4);

			backgroundChange(*mx, *my, 260 + i * 11, 143, 271 + i * 11, 167);


			/*���ַ�����������*/
			*p = ch;
			p++;
			*p = '\0';
			i++;
		}

	}
}


/***********************************************
Function: secondcodeinput
Description: 1��������Ϣ������˺����뺯��
             2��ֻ���Ǵ�Сд��ĸ������
             3��������1��10λ
Attention:���λ�ò�������Ҫ��ָ����ʽ���ݹ�����
Return:
************************************************/
int secondcodeinput(char *code, int *mx, int *my)
{
	int key;    //��ʾ��ֵ�ı���
	int i = 0;   //���ڼ�����������ַ���Ŀ�ı���
	char *p = code;   //�����ַ����м�ָ�����
	char ch;     //������ʱ�����ֵ����Ӧ�ַ��ı���
	int buttons;    //���Ĳ�������
	char temp[2] = { '\0','\0' };  //����outtextxy������������ַ�������


								   /*ʹpָ��'\0',i��ʾ��ǰ�ַ���*/
	while (*p != '\0')
	{
		i++;
		p++;
	}

	/*����*/
	AddFrame(*mx, *my, 250, 200, 400, 230, RED);

	while (1)
	{
		newxy(mx, my, &buttons);

		/*���ü�ֵ���õ��¼�ֵ*/
		key = 0;
		if (kbhit() != 0)
		{
			key = bioskey(0);
		}

		/* if(�����������������)����0��ʾ����oldcodeinput����*/
		if (*mx >= 250 && *mx <= 400 && *my >= 100 && *my <= 130 && buttons)
		{
			AddFrame(*mx, *my, 250, 200, 400, 230, BLUE);
			return 0;
		}

		/* if(����һ��enter������������������������һ���·����)����1��ʾ����newcodeinput����*/
		if (*mx >= 250 && *mx <= 400 && *my >= 140 && *my <= 170 && buttons || key == 0x4800)
		{
			AddFrame(*mx, *my, 250, 200, 400, 230, BLUE);
			return 1;
		}

		/*������޸�����*/
		if (*mx >= 295 && *mx <= 345 && *my >= 250 && *my <= 280 && buttons)
		{
			AddFrame(*mx, *my, 250, 200, 400, 230, BLUE);
			return 3;
		};

		/*������˻�ɾ��*/
		if (key == 0xe08)
		{
			if (p != code)
			{
				setfillstyle(1, WHITE);
				bar(249 + i * 11, 203, 260 + i * 11, 227);
				backgroundChange(*mx, *my, 249 + i * 11, 203, 260 + i * 11, 227);
				p--;
				i--;
			}
			*p = '\0';
		}

		/*��������Ӧ���ַ�����accounts������*/
		ch = searchKeyValue(key);
		if (ch != '\0'&&i<10)
		{

			/*��һ��Բ*/
			setfillstyle(1, WHITE);
			bar(260 + i * 11, 203, 271 + i * 11, 227);
			setcolor(BLUE);
			setfillstyle(1, BLUE);
			pieslice(265 + i * 11, 215, 0, 360, 4);

			backgroundChange(*mx, *my, 260 + i * 11, 203, 271 + i * 11, 227);

			/*���ַ�����������*/
			*p = ch;
			p++;
			*p = '\0';
			i++;
		}

	}
}



