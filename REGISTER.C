#include "register.h"
#include<stdlib.h>
#include<string.h>
#include<graphics.h>
#include "nmouse.h"
#include "input.h"
#include "hz.h"


/************************************
Function: userRegister
Description: �û�ע�����ĺ�̨����
Attention:ͷָ��һ��Ҫ��ȷ����ָ��
Return:����0��ʾ��main�е��õ�½���棻
       ����2��ʾ��main�е������˵����棻
*************************************/
int userRegister(setuser *head, char *accounts, char *code)
{
	int judge = 0; //�ж�Ӧ�õ�����Щ�����ı���
	int mark1 = 0, mark2 = 0, mark3 = 0;  //�ֱ�ΪΪ�û��������롢���������Ƿ���ȷ���жϱ���
	int temp;  //�������ռ��̻������ı���
	char secondcode[11];  //�ڶ����������봮
	int buttons, mx, my;  //����������


	/*��Ҫ�ĳ�ʼ������*/
	secondcode[0] = '\0';
	*accounts = '\0';
	*code = '\0';

	mouseInit(&mx, &my,&buttons);

	while (1)
	{
		newxy(&mx, &my, &buttons);

		/*���ռ��̻�����������*/
		if (kbhit() != 0)
		{
			temp = bioskey(0);
		}

		if (mx >= 200 && mx <= 600 && my >= 120 && my <= 165 && buttons)judge = 1;         //if(��������˺���������)
		if (mx >= 200 && mx <= 600 && my >= 200 && my <= 245 && buttons)judge = 2;         //if���������������������
		if (mx >= 200 && mx <= 600 && my >= 280 && my <= 325 && buttons)judge = 3;         //if(�����������һ����������
		if (mx >= 230 && mx <= 460 && my >= 360 && my <= 415 && buttons)judge = 4;         //if(�����ע���������
		if (mx >= 300 && mx <= 455 && my >= 437 && my <= 455 && buttons)judge = 5;         //if(����������˻�ȥ��½����)

		/*����judge��ֵ�ж���Ҫ���õĹ���*/
		switch (judge)
		{

		/*case 1:�����˺����뺯��*/
		case 1:
			judge = RegisteraccountsInput(accounts, &mx, &my);

			if (SearchAccounts(head, accounts) != NULL)
			{
				/*����ɫ�Ĳ沢��ʾ���˺��ѱ�ע��&&mark1=0*/
				setfillstyle(1, LIGHTBLUE);
				bar(560, 120, 600, 165);
				drawRedFork(560, 130);
				backgroundChange(mx,my,560, 120, 600, 165);
				setfillstyle(1, LIGHTBLUE);
				bar(210, 170, 550, 195);
				puthz(210,170, "���˺��ѱ�ע�ᣡ", 16, 16, RED);
				backgroundChange(mx,my,210, 170, 550, 195);

				mark1 = 0;
			}
			else
			{
				/*��һ����ɫ�Ĺ�&&mark1=1*/
				setfillstyle(1, LIGHTBLUE);
				bar(210, 170, 550, 195);
				bar(560, 120, 600, 165);
				drawGreenHook(560, 130);
				backgroundChange(mx,my,560, 120, 600, 165);
				backgroundChange(mx,my,210, 170, 550, 195);

				mark1 = 1;
			}
			break;

		/*case 2:�����������뺯��*/
		case 2:
			judge = RegistercodeInput(code, &mx, &my);
			if (strlen(code) < 6)
			{
				/*����ɫ�Ĳ沢��ʾ���벻������6λ&&mark2=0*/
				setfillstyle(1, LIGHTBLUE);
				bar(560, 200, 600, 245);
				drawRedFork(560, 210);
				backgroundChange(mx, my, 560, 200, 600, 245);
				setfillstyle(1, LIGHTBLUE);
				bar(210, 250, 550, 275);
				puthz(210, 250, "���벻��������λ��", 16, 16, RED);
				backgroundChange(mx, my, 210, 250, 550, 275);

				mark2 = 0;
			}
			else
			{
				/*��һ����ɫ�Ĺ�&&mark2=1*/
				setfillstyle(1, LIGHTBLUE);
				bar(210, 250, 550, 275);
				bar(560, 200, 600, 245);
				drawGreenHook(560, 210);
				backgroundChange(mx, my, 560, 200, 600, 245);
				backgroundChange(mx, my, 210, 250, 550, 275);

				mark2 = 1;
			}
			break;

		/*case 3:���ö����������뺯��*/
		case 3:
			judge = RegistersecondcodeInput(secondcode, &mx, &my);
			if (strcmp(code, secondcode) != 0)
			{
				/*����ɫ�Ĳ沢��ʾ�����������벻ͬ&&mark3=0*/
				setfillstyle(1, LIGHTBLUE);
				bar(560, 280, 600, 325);
				drawRedFork(560, 290);
				backgroundChange(mx, my, 560, 280, 600, 325);
				setfillstyle(1, LIGHTBLUE);
				bar(210, 330, 550, 355);
				puthz(210, 330, "�����������벻ͬ��", 16, 16, RED);
				backgroundChange(mx, my, 210, 330, 550, 355);

				mark3 = 0;
			}
			else
			{
				/*��һ����ɫ�Ĺ�&&mark3=1*/
				setfillstyle(1, LIGHTBLUE);
				bar(210, 330, 550, 355);
				bar(560, 280, 600, 325);
				drawGreenHook(560, 290);
				backgroundChange(mx, my, 560, 280, 600, 325);
				backgroundChange(mx, my, 210, 330, 550, 355);

				mark3 = 1;
			}
			break;

		/*case 4:�ж��Ƿ�ע��ɹ�*/
		case 4:if (mark1 == 1 && mark2 == 1 && mark3 == 1)
		{
			AddNewUser(head, accounts, code);
			if(Choose("ע��ɹ���\n�Ƿ��Զ���¼��", 260,200,GREEN)==1)return 2;
			else return 0;
		}
			   break;

	    /*case 5:����main�������õ�½����*/
		case 5: return 0;
		}
	}
}


/************************************
Function: RegisterIF
Description: ��ע�����ĺ���
Attention:
Return:
*************************************/
void RegisterIF()
{
	cleardevice();
	setbkcolor(LIGHTBLUE);
	setcolor(WHITE);
	setfillstyle(1, WHITE);
	bar(199, 119, 551, 166);
	bar(199, 199, 551, 246);
	bar(199, 279, 551, 326);
    setfillstyle(1, BLUE);
    bar(250, 360 , 400, 415);


	puthz( 60, 127,"�û���" , 32,  32, WHITE);
	puthz( 60,  207, "����", 32,  32, WHITE);
	puthz( 60,  287, "ȷ������", 32,  32, WHITE);
	puthz( 290, 370, "ע��", 32, 32, WHITE);
	puthz(312, 436, "����", 16, 16, WHITE);
	setcolor(WHITE);
	line(295, 455, 360, 455);
	puthz(240, 215, "6��10λ��ĸ���������", 16, 16, BLUE);
	puthz(210, 20, "���û�ע��", 48, 48,WHITE);
}


/************************************
Function: drawRedFork
Description: ��(x,y)����һ����ɫ�Ĳ�
Attention:
Return:
*************************************/
void drawRedFork(int x, int y)
{
	int dot[26];
	dot[0] = x + 2;
	dot[1] = y;
	dot[2] = x + 12;
	dot[3] = y + 10;
	dot[4] = x + 22;
	dot[5] = y;
	dot[6] = x + 24;
	dot[7] = y + 2;
	dot[8] = x + 14;
	dot[9] = y + 12;
	dot[10] = x + 24;
	dot[11] = y + 22;
	dot[12] = x + 22;
	dot[13] = y + 24;
	dot[14] = x + 12;
	dot[15] = y + 14;
	dot[16] = x + 2;
	dot[17] = y + 24;
	dot[18] = x;
	dot[19] = y + 22;
	dot[20] = x + 10;
	dot[21] = y + 12;
	dot[22] = x;
	dot[23] = y + 2;
	dot[24] = x + 2;
	dot[25] = y;

	setcolor(RED);
	setfillstyle(1, LIGHTRED);
	drawpoly(13, dot);
	floodfill(x + 2, y + 2, RED);
}


/************************************
Function: drawGreenHook
Description: ��(x,y)����һ����ɫ�Ĺ�
Attention:
Return:
*************************************/
void drawGreenHook(int x, int y)
{
	int dot[14];
	dot[0] = x;
	dot[1] = y + 15;
	dot[2] = x + 9;
	dot[3] = y + 24;
	dot[4] = x + 24;
	dot[5] = y + 9;
	dot[6] = x + 22;
	dot[7] = y + 7;
	dot[8] = x + 9;
	dot[9] = y + 20;
	dot[10] = x + 2;
	dot[11] = y + 13;
	dot[12] = x;
	dot[13] = y + 15;
	setcolor(GREEN);
	setfillstyle(1, GREEN);
	drawpoly(7, dot);
	floodfill(x + 1, y + 15, GREEN);
}