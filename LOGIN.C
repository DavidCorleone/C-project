#include "login.h"
#include<stdlib.h>
#include<string.h>
#include<bios.h>
#include<graphics.h>
#include "nmouse.h"
#include "cartoon.h"
#include "hz.h"


/************************************
Function: userLogin
Description: �û���½����ĺ�̨����
Attention:ͷָ��һ��Ҫ��ȷ����ָ��
Return:����1��ʾ����ע����棻
       ����2��ʾ������ͨ�û����棻
       ����5��ʾ�������Ա���棻 
*************************************/
int userLogin(setuser *head, char *accounts, char *code)
{
	int judge = 0;    //�ж�Ӧ�õ�����Щ�����ı���
	int temp;    //�������ռ��̻������ı���
	char *rightcode=NULL;  //ָ����ȷ�����ָ��
	int buttons, mx, my;   //����������
	int driver = VGA;
	int mode = VGAHI;


	/*��Ҫ�ĳ�ʼ������*/
	mouseInit(&mx, &my, &buttons);
	*accounts = '\0';
	*code = '\0';
	//setMouseShape(1);

	while (1)
	{
		newxy(&mx, &my, &buttons);

		/*���ռ��̻�����������*/
		if (kbhit() != 0)
		{
			temp = bioskey(0);
		}

		if (mx >= 220 && mx <= 420 && my >= 160 && my <= 200 && buttons)judge = 1;   //if(��������˺����롿����)
		if (mx >= 220 && mx <= 420 && my >= 220 && my <= 260 && buttons)judge = 2;   //if(��������������롿����)
		if (mx >= 330 && mx <= 420 && my >= 280 && my <= 320 && buttons)judge = 3;   //if(���������½������)
		if (mx >= 220 && mx <= 310 && my >= 280 && my <= 320 && buttons)return 1;    //if(�������ע�᡿����)
		if (mx >= 220  && mx <= 420 && my >= 340 && my <= 380 && buttons)judge=5;		//if(���������Ա��¼������ 
		/*������˳�ϵͳ����*/
		if (mx >= 580 && mx <= 630 && my >= 20 && my <= 70 && buttons)
		{
			if (Choose("�Ƿ��˳�ϵͳ��", &mx, &my, WHITE) == 0)
			{
				judge = 4;
			}
			else return 4;
		}

        switch (judge)
		{
		case 1:
			judge = LoginaccountsInput(accounts, &mx, &my);break;
		case 2:
			judge = LogincodeInput(code, &mx, &my);break;
		case 3:
		  {
			 rightcode = SearchAccounts(head, accounts);
			 if (rightcode != NULL &&strcmp(rightcode, code) == 0)
			 	return noticeIF();
				 //return 2;  //��main�е���2�Ž��棨���˵����棩�����̨����
			 else
			 {
				puthz(450, 160, "�û����������������", 16, 16, BLACK);
				break;
			 }
		  }
		    break;
		case 4:
			LoginIF();
			getMousebk(mx, my);
			judge = 0;
			break;
		//��Ա��¼ 
		case 5:
			if (strcmp(accounts, "heming") == 0 && strcmp(code, "666666") == 0)
			{
				WarningTips("��½�ɹ���", 260, 200, BLUE);
				//initgraph(&driver, &mode, ".BORLANDC\\bgi");
				initgraph(&driver, &mode, "../BORLANDC\\bgi");
				cleardevice();
				return 5;
			}
			else
			{
				WarningTips("���벻ƥ�䣡", 260, 200, BLUE);
				//initgraph(&driver, &mode, "C:\\BORLANDC\\bgi");
				initgraph(&driver, &mode, "../BORLANDC\\bgi");
				cleardevice();
				return 0;
			} 
		}
	}
}



/************************************
Function:����¼���溯��
Description:
Attention:
Return:
*************************************/
void LoginIF(void)
{
    cleardevice();
    setbkcolor(LIGHTBLUE);
    setcolor(WHITE);
    setfillstyle(1, WHITE);
    bar(220, 160, 420, 200);  //�˺������
	bar(220, 220, 420, 260);
	
	setlinestyle(0,0,3);	//��������	
	circle(540,204,50);
	line(495,159,504,168);
	line(576,240,585,249);
	setlinestyle(0,0,1);
	line(537,263,537,272);
	line(543,263,543,272);
	arc(540,204,135,315,56);
	arc(540,204,135,315,59);
	ellipse(540,274,0,360,18,6);
	
	
		
	setlinestyle(0,0,3);
    bar(220, 280, 310, 320);  //ע���¼��
	bar(330, 280, 420, 320);
	bar(220, 340, 420, 380);

	setfillstyle(1, BLUE);
	bar(0, 430, 640, 480);

	setlinestyle(0, 0, 3);     
	setcolor(WHITE);
	line(590, 30, 620, 60);
	line(590, 60, 620, 30);

	puthz(150, 160, "�˺�", 32, 32, WHITE);
	puthz(150, 220, "����", 32, 32, WHITE);
	puthz(250, 290, "ע��", 16, 16, BLUE);
	puthz(360, 290, "��¼", 16, 16, BLUE);
	puthz(280, 350, "��Ա��¼", 16, 16, BLUE);
	settextstyle(0, 0, 2);

    puthz(120, 445, "�Զ���1705     ��ΰΰ   �ܺ���", 16, 16, WHITE);

    settextstyle(0, 0, 6);
	puthz(120, 50, "������ѧ��ѯϵͳ", 48, 48, WHITE);
}

/***********************************************
Function: LoginaccountsInput
Description: 1���û���½������˺����뺯��
2��ֻ���Ǵ�Сд��ĸ������
3��������1��10λ
Attention:���λ�ò�������Ҫ��ָ����ʽ���ݹ�����
Return:����2��userLogin�е���LogincodeInput����
����3��userLogin��ʹ�õ�½����
����4��userLogin��ʹ��ע�Ṧ��
************************************************/
int LoginaccountsInput(char *accounts, int *mx, int *my)
{
    int key;    //��ʾ��ֵ�ı���
	int i = 0;   //���ڼ�����������ַ���Ŀ�ı���
	char *p = accounts;   //�����ַ����м�ָ�����
	char ch;     //������ʱ�����ֵ����Ӧ�ַ��ı���
	int buttons;    //���Ĳ�������
	char temp[2] = { '\0','\0' };  //����outtextxy������������ַ�������

                                    //ʹpָ��'\0'��i��ʾ��ǰ�ַ���
    while(*p!='\0')
    {
        p++;
        i++;
    }

    //����
    AddFrame(*mx, *my, 220, 160, 420, 200, BROWN);

    while(1)
    {
        newxy(mx, my, &buttons);
        /*���ü�ֵ���õ��¼�ֵ*/
        key = 0;
		if (kbhit() != 0)
		{
			key = bioskey(0);
		}
		/* if(����һ��enter������������������������һ���·����)����2��ʾ����LogincodeInput����*/
		if (*mx >= 210 && *mx <= 420 && *my >= 210 && *my <= 260 && buttons || key == 0x1c0d || key == 0x5000)
		{
			AddFrame(*mx, *my, 220, 160, 420, 200, BLACK);
			return 2;
		}

		/*if(�����½����)����3��ʾ��½ */
		if (*mx >= 330 && *mx <= 420 && *my >= 280 && *my <= 320 && buttons)
		{
			AddFrame(*mx, *my, 220, 160, 420, 200, BLACK);
			return 3;
		}

		/*if(���ע������)����4��ʾע��*/
		if (*mx >= 210 && *mx <= 310 && *my >= 280 && *my <= 310 && buttons)
		{
			AddFrame(*mx, *my, 220, 160, 420, 200, BLACK);
			return 4;
		}

		/*������˻�ɾ��*/
		if (key == 0xe08)
		{
			if (p != accounts)
			{
				setfillstyle(1, WHITE);
				bar(218 + i * 11, 162, 231 + i * 11, 190);
				backgroundChange(*mx, *my, 220 + i * 11, 162, 231 + i * 11, 190);
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
			bar(230 + i * 11, 162, 241 + i * 11, 190);
			temp[0] = ch;
			settextstyle(2, 0, 6);
			setcolor(BLACK);
			outtextxy(230 + i * 11, 170, temp);
			backgroundChange(*mx, *my, 230 + i * 11, 162, 241 + i * 11, 190);

			/*���ַ�����������*/
			*p = ch;
			p++;
			*p = '\0';
			i++;
		}

    }

}

/***********************************************
Function: LogincodeInput
Description: 1���û���½������������뺯��
2��ֻ���Ǵ�Сд��ĸ������
3��������1��10λ
Attention:���λ�ò�������Ҫ��ָ����ʽ���ݹ�����
Return:����1��userLogin�е���LoginaccountsInput����
����3��userLogin��ʹ�õ�½����
����4��userLogin��ʹ��ע�Ṧ��
************************************************/
int LogincodeInput(char *code, int *mx, int *my)
{

	int key;     //��ʾ��ֵ�ı���
	int i = 0;   //���ڼ�����������ַ���Ŀ�ı���
	char *p = code;     //�����ַ����м�ָ�����
	char ch;     //������ʱ�����ֵ����Ӧ�ַ��ı���
	int buttons;     //���Ĳ�������


					 /*ʹpָ��'\0',i��ʾ��ǰ�ַ���*/
	while (*p != '\0')
	{
		i++;
		p++;
	}

	/*����*/
	AddFrame(*mx, *my, 220, 220, 420, 260, BROWN);

	while (1)
	{
		newxy(mx, my, &buttons);

		/*���ü�ֵ���õ��¼�ֵ*/
		key = 0;
		if (kbhit() != 0)
		{
			key = bioskey(0);
		}

		/*if(������˺������������һ���Ϸ����)����1��ʾ����LoginaccountsInput����*/
		if (*mx >= 210 && *mx <= 410 && *my >= 170 && *my <= 190 && buttons || key == 0x4800)
		{
			AddFrame(*mx, *my, 220, 220, 420, 260, BLACK);
			return 1;
		}

		/*if(����һ��enter��������½����)����3��ʾ��½*/
		if (*mx >= 210 && *mx <= 410 && *my >= 170 && *my <= 190 && buttons || key == 0x1c0d)
		{
			AddFrame(*mx, *my, 220, 220, 420, 260, BLACK);
			return 3;
		}

		/*if(���ע������)����4��ʾע��*/
		if (*mx >= 210 && *mx <= 410 && *my >= 170 && *my <= 190 && buttons)
		{
			AddFrame(*mx, *my, 220, 220, 420, 260, BLACK);
			return 4;
		}


		/*������˻�ɾ��*/
		if (key == 0xe08)
		{
			if (p != code)
			{
				setfillstyle(1, WHITE);
				bar(220 + i * 11, 222, 231 + i * 11, 258);

				backgroundChange(*mx, *my, 220 + i * 11, 222, 231 + i * 11, 258);

				p--;
				i--;
			}
			*p = '\0';
		}

		/*��������Ӧ���ַ�����code������*/
		ch = searchKeyValue(key);
		if (ch != '\0'&&i<10)
		{
			/*���ַ�����������*/
			*p = ch;
			p++;
			*p = '\0';
			i++;

			/*��һ��Բ*/
			setfillstyle(1, WHITE);
			bar(220 + i * 11, 222, 229 + i * 11, 258);
			setcolor(BLACK);
			setfillstyle(1, BLACK);
			pieslice(224 + i * 11, 240, 0, 360, 4);

			backgroundChange(*mx, *my, 220 + i * 11, 222, 229 + i * 11, 258);
		}
	}
}
/************************************
Function: noticeIF
Description: ���û���֪����ĺ���
Attention:
Return:
*************************************/
int noticeIF()
{
	int mx, my, buttons;
	cleardevice();
	setbkcolor(CYAN);
	puthz(256, 30, "�û���֪", 32, 32, WHITE);
	setfillstyle(1, WHITE);
	bar(80, 80, 580, 400);
	puthz(90, 90, "���ڴ洢����Ϣ���ޣ�ֻ�г���Ҫ��ѧ���Ҽ��䲿��ѧУ��Ϣ", 16, 16, BROWN);
	puthz(90, 120, "��ѧ����ֻ�г����вο���ֵ��QS��������,רҵ�������г���ѧ���Զ�������", 16, 16, BROWN);
	puthz(90, 150, "GPA�㷨���û��пƼ���ѧ��GPA�㷨", 16, 16, BROWN);
	puthz(90, 180, "ѧ����ѧ��Ϊ��λ,����ɱ�����Ϊ��λ����������Ԫ��", 16, 16, BROWN);
	puthz(90, 210,"��ϵͳ����Ϣ��Դ�����磬��˿�����ٷ��������룬�����ο�����ϵͳ���е��κ�����", 16, 16, BROWN);
	setcolor(WHITE);
	setlinestyle(0, 0, 3);
	line(70, 70, 140, 70);
	line(70, 70, 70, 115);
	line(590, 70, 520, 70);
	line(590, 70, 590, 115);
	line(70, 390, 70, 345);
	line(70, 390, 140, 390);
	line(590, 410, 590, 365);
	line(590, 410, 520, 410);
	setfillstyle(1, CYAN);
	bar(250, 420, 290, 440);
	bar(350, 420, 390, 440);
	puthz(253, 422, "ͬ��", 16, 16, WHITE);
	puthz(353, 422, "�ܾ�", 16, 16, WHITE);	
	mouseInit(&mx, &my, &buttons);
	while(1)
	{
		newxy(&mx, &my, &buttons);
		if(mx >= 250 && mx <= 290 && my >= 420 && my <= 440 && buttons)//ͬ��������� 
		return 2; 
		if(mx >= 350 && mx <= 390 && my >= 420 && my <= 440 && buttons)//�ܾ�����LOGIN 
		return 0;
	}
} 