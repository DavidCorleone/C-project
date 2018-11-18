#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<graphics.h>
#include "nmouse.h"
#include "hz.h"
#include "collect.h"
#include "structur.h"





/*******************************
Function: freecollectList
Description: �ͷ��û����ղ�����
Attention:
Return:
*******************************/
void freecollectList(setuser *person)
{
	setcollect *previous = NULL;
	setcollect *current = NULL;

	/*�ͷŴ�ѧ�����ռ�*/
	previous = person->college.next;
	if (previous == NULL)return 0;
	else current = previous->next;

	while (current != NULL)
	{
		free(previous);
		previous = current;
		current = current->next;
	}
	free(previous);
	person->college.next = NULL;
}




/**************************************************
Function: collect
Description:�ղؾ����Ƶ�
Attention:
Return:
***************************************************/
void collect(char *name, char *englishname, setuser *person)
{
	setcollect *current = NULL;
//	char *symbol="C"; 
	person->mark_collect = 1;
	
	/*���ղ�д������*/

	current = &(person->college);

	while (current->next != NULL)
		current = current->next;

	if ((current->next = (setcollect *)malloc(sizeof(setcollect))) == NULL)
	{
		closegraph();
		printf("\nOverflow");
		getchar();
		exit(1);
	}
//	strcat(symbol, name);
	current = current->next;
	strcpy(current->name, name);
	strcpy(current->englishname, englishname);
	current->next = NULL;
}



/****************************************************
Function: deleteCollect
Description:ɾ���ղ�
Attention: head Ϊ�ղ�������ͷָ��
Return:
****************************************************/
void deleteCollect(char *name, setcollect *head, setuser *person)
{
	setcollect *current = NULL;
	setcollect *previous = NULL;

	current = head->next;
	previous = head;

	person->mark_collect = 1;

	while (current != NULL)
	{
		if (strcmp(name, current->name) == 0)break;
		else
		{
			previous = current;
			current = current->next;
		}
	}

	previous->next = current->next;
	free(current);
}



/********************************************
Function: RewriteCollectFile
Description:����д���û����ղ���Ϣ���ļ���
Attention:
Return:
*********************************************/
void RewriteCollectFile(setuser *person)
{
	FILE *fp = NULL;
	//char path[100] = "C:\\myCCD\\FILES\\user\\collect\\";
	char path[100] = "FILES\\user\\collect\\";
	setcollect *current = NULL;
	
	strcat(path, person->accounts);
	strcat(path, ".txt");
	fp = fopen(path, "w+");

	fputc('#', fp);

	/*д���ղش�ѧ����Ϣ*/
	current = person->college.next;
	while (current != NULL)
	{
		fputs(current->name, fp);
		fputc('*', fp);
		fputs(current->englishname, fp);
		fputc('#', fp);
		current = current->next;
	}
	fclose(fp);
}

/**************************
Function: drawDeletebutton
Description:��ɾ����ť
Attention:
***************************/
void drawDeletebutton(int x, int y)
{
	setlinestyle(0, 0, 1);
	rectangle(x, y, x+48, y+28);
	puthz(x+8, y+7, "ɾ��", 16, 16, BROWN);
}

/*******************************
Function: manageCollect
Description:�༭�������ղصĺ���
Attention:
********************************/
int manageCollect(setuser *person, int *mx, int *my)
{
	char temp[20];
	int buttons;
	int judge=0;

	while (1)
	{

		switch (judge)
		{
			/*��ʾ�༭����*/
		case 0:
			judge = manageCollectIF(temp, mx, my, &(person->college));
			break;

			/*�˳��༭����*/
		case 1:
			return 2;
			break;

			/*ɾ���ղصĲ���*/
		case 2:
			deleteCollect(temp, &(person->college),person);
			judge = 0;
			break;
		}
	}

}
/**************************************************
Function: ifCollect
Description:�жϾ����Ƿ��Ѿ����ղ�
Input:
Attention:
Return:���ղط���1��δ�ղط���0
***************************************************/
int ifCollect(setcollect *head, char *name)
{
	setcollect *current = head;
//	char *symbol ="C";
//	strcat(symbol, name);
	while (current != NULL)
	{
		if (strcmp(current->name, name) == 0)return 1;
		current = current->next;
	}
	return 0;
}

/****************************************************
Function: showmyCollectIF
Description: ���ҵ��ղؽ��� 
Attention:
Return:
****************************************************/
void showmyCollectIF() 
{
	cleardevice();
	setbkcolor(WHITE);
	setlinestyle(0, 0, 1);
	setfillstyle(1, LIGHTBLUE);
	bar(20, 100, 150, 220);
	setfillstyle(1, LIGHTGRAY);

	bar(0, 0, 30, 30);
	setcolor(WHITE);
	line(5, 15, 25, 15);
	line(5, 15, 10, 20);
	line(5, 15, 10, 10);
	
	setcolor(LIGHTGRAY);
	line(20, 130, 150, 130);
	line(20, 160, 150, 160);
	line(20, 190, 150, 190);
	setcolor(WHITE);
	circle(30, 140, 5);
	line(23, 155, 37, 155);
	line(23, 155, 28, 143);
	line(37, 155, 32, 143);
	line(23, 183, 28, 177);
	line(28, 177, 32, 180);
	line(32, 180, 38, 170);
	line(38, 170, 38, 175);
	line(38, 170, 34, 173);

	setfillstyle(1, WHITE);
	floodfill(30, 140, WHITE);
	floodfill(30, 147, WHITE);
	arc(30, 207, 110, 430, 5);
	line(30, 206, 30, 198);
	circle(30, 120, 4);
	floodfill(30, 120, WHITE);
	line(30, 116, 30, 107);
	line(30, 109, 33, 111);
	line(30, 112, 33, 113);
	setcolor(LIGHTBLUE);
	circle(30, 122, 1);
	puthz(60, 107, "��������", 16, 16, WHITE);
	puthz(60, 137, "�ҵ��ղ�", 16, 16, WHITE);
	puthz(60, 167, "�������", 16, 16, WHITE);
	puthz(60, 197, "�˳���¼", 16, 16, WHITE);
	rectangle(200, 100, 600, 450);
	line(200, 150, 600, 150);	//�����ָ���
	line(200, 200, 600, 200);
	line(200, 250, 600, 250);
	line(200, 300, 600, 300);
	line(200, 350, 600, 350);
	line(200, 400, 600, 400);
	rectangle(200, 75, 300, 100);
	puthz(205, 80, "���ղصĴ�ѧ", 16, 16, BROWN);
	rectangle(560, 75, 600, 100);
	puthz(565, 80, "�༭", 16, 16, BROWN);
} 

/*****************************
Function: showmyCollect
Description:��ʾ�ղؽ���ĺ���
Attention:
******************************/
int showmyCollect(char *symbol, setcollect *college, int *mx, int *my)
{
  	setcollect *first = NULL;//6��ָ��ֱ�ָ��һҳ�е�6����Ϣ
	setcollect *second = NULL;
	setcollect *third = NULL;
	setcollect *forth = NULL;
	setcollect *fifth = NULL;
	setcollect *sixth = NULL;
	setcollect *current = NULL;//�������������ڵ���
	setcollect *p = NULL;
	int Currentpage = 1;    //ҳ��
	int formerPage = 0;
	int buttons = 0;    //���Ĳ�������

	int i;//��λ����ǰҳ�ĵ�һ����Ϣ
	int j;
	int n = 0;   //��ѧ�����Ľڵ����
	current = college;
	p = college;

	while (1)
	{
		newxy(mx, my, &buttons);

		/*������޸���������*/
		if (*mx >= 20 && *mx <= 150 && *my >= 100 && *my <= 130 && buttons)return 1;

		/*������ҵ��ղ�����*/
		if (*mx >= 20 && *mx <= 150 && *my >= 130 && *my <= 160 && buttons)return 2;

		/*����������������*/
		if (*mx >= 20 && *mx <= 150 && *my >= 160 && *my <= 190 && buttons)return 3;

		/*������˳�ϵͳ����*/
		if (*mx >= 20 && *mx <= 150 && *my >= 190 && *my <= 220 && buttons)return 4;

		/*��������ذ���*/
		if (*mx >= 0 && *mx <= 20 && *my >= 0 && *my <= 20 && buttons)return 5;
		
		/*���������༭����*/
		if (*mx >= 560 && *mx <= 592 && *my >= 76 && *my <= 99 && buttons)return 6;
		
		
		if (*mx >= 200 && *mx <= 300 && *my >= 75 && *my <= 100 && buttons)
		{
			current = college;
			p = current;
			Currentpage = 1;    //ҳ��
			formerPage = 0;
		}
		n = 0;
		while (current != NULL)
		{
			n++;
			current = current->next;
		}
		if (n>6)
		{
			puthz(340, 420, "��һҳ", 16, 16, BROWN);
			puthz(400, 420, "��һҳ", 16, 16, BROWN);
			setcolor(LIGHTRED);
			line(330, 428, 338, 420);
			line(338, 436, 330, 428);
			line(458, 428, 450, 420);
			line(458, 428, 450, 436);
		}
		/*�������һҳ����*/
		if (*mx >= 330 && *mx <= 390 && *my >= 420 && *my <= 436 && buttons)
		{
			Currentpage++;
			if (Currentpage > n / 6)Currentpage = n / 6;
		}

		/*�������һҳ����*/
		if (*mx >= 400 && *mx <= 460 && *my >= 420 && *my <= 436 && buttons)
		{
			Currentpage--;
			if (Currentpage < 1)Currentpage = 1;
		}
		if (Currentpage != formerPage)
		{
		
		formerPage = Currentpage;
		first = NULL;
		second = NULL;
		third = NULL;
		forth = NULL;
		fifth = NULL;
		sixth = NULL;
			
		setfillstyle(1, WHITE);
		bar(160, 65, 640, 480);
		setcolor(LIGHTGRAY);
		rectangle(200, 100, 600, 450);
		rectangle(200, 75, 300, 100);
		puthz(205, 80, "���ղصĴ�ѧ", 16, 16, BROWN);
		rectangle(560, 75, 600, 100);
		puthz(565, 80, "�༭", 16, 16, BROWN);
		backgroundChange(*mx, *my, 560, 75, 600, 100);
		line(200, 150, 600, 150);	//�����ָ���
		line(200, 200, 600, 200);
		line(200, 250, 600, 250);
		line(200, 300, 600, 300);
		line(200, 350, 600, 350);
		line(200, 400, 600, 400);
		i = Currentpage * 6 - 4; 
		current = p;
			for (j = 1;j < i;j++)
			{
				current = current->next;
			}
			first = current;
		if (first != NULL)second = first->next;
		if (second != NULL)third = second->next;
		if (third != NULL)forth = third->next;
		if (forth != NULL)fifth = forth->next;
		if (fifth != NULL)sixth = fifth->next;


		if (first != NULL)
		{
			puthz(230, 117, first->name, 16, 16, BROWN);
		}
		if (second != NULL)
		{
			puthz(230, 167, second->name, 16, 16, BROWN);
		}
		if (third != NULL)
		{
			puthz(230, 217, third->name, 16, 16, BROWN);
		}
		if (forth != NULL)
		{
			puthz(230, 267, forth->name, 16, 16, BROWN);
		}
		if (fifth != NULL)
		{
			puthz(230, 317, fifth->name, 16, 16, BROWN);
		}
		if (sixth != NULL)
		{
			puthz(230, 367, sixth->name, 16, 16, BROWN);
		}
	}
		
	if (*mx >= 200 && *mx <= 600 && *my > 100 && *my < 150 && first != NULL)
		{
			AddFrame(*mx, *my, 204, 104, 596, 146, RED);//�����ڵ�һ�����ݻ���ֺ�ɫ��
			if (buttons)
			{
				strcpy(symbol, first->englishname);
				return 7;
			}
		}
		else
			AddFrame(*mx, *my, 204, 104, 596, 146, WHITE);//����������ɫ����ʧ

		if (*mx >= 200 && *mx <= 600 && *my > 150 && *my < 200 && second != NULL)
		{
			AddFrame(*mx, *my, 204, 154, 596, 196, RED);
			if (buttons)
			{
				strcpy(symbol, second->englishname);
				return 7;
			}
		}
		else
			AddFrame(*mx, *my, 204, 154, 596, 196, WHITE);


		if (*mx >= 200 && *mx <= 600 && *my > 200 && *my < 250 && third != NULL)
		{
			AddFrame(*mx, *my, 204, 204, 596, 246, RED);
			if (buttons)
			{
				strcpy(symbol, third->englishname);
				return 7;
			}
		}
		else
			AddFrame(*mx, *my, 204, 204, 596, 246, WHITE);


		if (*mx >= 200 && *mx <= 600 && *my > 250 && *my < 300 && forth != NULL)
		{
			AddFrame(*mx, *my, 204, 254, 596, 296, RED);
			if (buttons)
			{
				strcpy(symbol, forth->englishname);
				return 7;
			}
		}
		else
			AddFrame(*mx, *my, 204, 254, 596, 296, WHITE);


		if (*mx >= 200 && *mx <= 600 && *my > 300 && *my < 350 && fifth != NULL)
		{
			AddFrame(*mx, *my, 204, 304, 596, 346, RED);
			if (buttons)
			{
				strcpy(symbol, fifth->englishname);
				return 7;
			}
		}
		else
			AddFrame(*mx, *my, 204, 304, 596, 346, WHITE);

		if (*mx >= 200 && *mx <= 600 && *my > 350 && *my < 400 && sixth != NULL)
		{
			AddFrame(*mx, *my, 204, 354, 596, 396, RED);
			if (buttons)
			{
				strcpy(symbol, sixth->englishname);
				return 7;
			}
		}
		else
			AddFrame(*mx, *my, 204, 354, 596, 396, WHITE);

	}
	
}


/**************************
Function: manageCollectIF
Description:���༭�ղؽ���
Attention:
***************************/

int manageCollectIF(char *name, int *mx, int *my, setcollect *college)
{
	setcollect *first = NULL;
	setcollect *second = NULL;
	setcollect *third = NULL;
	setcollect *forth = NULL;
	setcollect *fifth = NULL;
	setcollect *sixth = NULL;
	setcollect *current = NULL;
	setcollect *p = NULL;
	
	int buttons = 0;    //���Ĳ�������
	int Currentpage = 1;    //ҳ��
	int formerPage = 0;
	int i;
	int j;
	int n = 0;   //���������Ľڵ����
	//puthz(0, 50, college->name, 16, 16, BROWN);

//	mouseInit(&mx, &my, &buttons);

	current = college;
	p = college;
	while (1)
	{
		newxy(mx, my, &buttons);

		/*���������˳�����*/
		if (*mx >= 560 && *mx <= 592 && *my >= 80 && *my <= 112 && buttons)
		return 1;
		
		if (*mx >= 200 && *mx <= 300 && *my >= 75 && *my <= 100 && buttons)
		{
			current = college;
			p = current;
			Currentpage = 1;    //ҳ��
			formerPage = 0;
		}
		n=0;
		while (current != NULL)
		{
			n++;
			current = current->next;
		}
		if (n>6)
		{
			puthz(340, 420, "��һҳ", 16, 16, BROWN);
			puthz(400, 420, "��һҳ", 16, 16, BROWN);
			setcolor(LIGHTRED);
			line(330, 428, 338, 420);
			line(338, 436, 330, 428);
			line(458, 428, 450, 420);
			line(458, 428, 450, 436);
		}


		/*�������һҳ����*/
		if (*mx >= 330 && *mx <= 390 && *my >= 420 && *my <= 436 && buttons)
		{
			Currentpage--;
			if (Currentpage < 1)Currentpage = 1;
		}

		/*�������һҳ����*/
		if (*mx >= 400 && *mx <= 460 && *my >= 420 && *my <= 436 && buttons)
		{

			Currentpage++;
			if (Currentpage > n / 6 + 1)Currentpage = n / 6 + 1;
		}
		if (Currentpage != formerPage)
		{
			formerPage = Currentpage;
			first = NULL;
			second = NULL;
			third = NULL;
			forth = NULL;
			fifth = NULL;
			sixth = NULL;
			
		setfillstyle(1, WHITE);
	bar(160, 65, 640, 480);
	setcolor(LIGHTGRAY);
	rectangle(200, 100, 600, 450);
	line(200, 150, 600, 150);	//�����ָ���
	line(200, 200, 600, 200);
	line(200, 250, 600, 250);
	line(200, 300, 600, 300);
	line(200, 350, 600, 350);
	line(200, 400, 600, 400);
	rectangle(200, 75, 300, 100);
	puthz(205, 80, "���ղصĴ�ѧ", 16, 16, BROWN);
	rectangle(560, 75, 600, 100);
	puthz(565, 80, "�˳�", 16, 16, BROWN);
	backgroundChange(*mx, *my, 560, 75, 600, 100);
		
		i = Currentpage * 6 - 4;

			/*��current��λ��������ͷ�ĵ�i���ڵ�*/
			current = p;
			for (j = 1;j < i;j++)
			{
				current = current->next;
			}
		first = current;
		if (first != NULL)second = first->next;
		if (second != NULL)third = second->next;
		if (third != NULL)forth = third->next;
		if (forth != NULL)fifth = forth->next;
		if (fifth != NULL)sixth = fifth->next;

		setcolor(LIGHTRED);
		if (first != NULL)
		{
			puthz(230, 117, first->name, 16, 16, BROWN);
			drawDeletebutton(532, 110);
		}
		if (second != NULL)
		{
			puthz(230, 167, second->name, 16, 16, BROWN);
			drawDeletebutton(532, 160);
		}
		if (third != NULL)
		{
			puthz(230, 217, third->name, 16, 16, BROWN);
			drawDeletebutton(532, 210);
		}
		if (forth != NULL)
		{
			puthz(230, 267, forth->name, 16, 16, BROWN);
			drawDeletebutton(532, 260);
		}
		if (fifth != NULL)
		{
			puthz(230, 317, fifth->name, 16, 16, BROWN);
			drawDeletebutton(532, 310);
		}
		if (sixth != NULL)
		{
			puthz(230, 367, sixth->name, 16, 16, BROWN);
			drawDeletebutton(532, 360);
		}
		setlinestyle(0, 0, 1);
		}
		if (*mx >= 532 && *mx <= 580 && *my > 110 && *my < 140 && first != NULL && buttons)
		{
			strcpy(name, first->name);
			return 2;
		}

		if (*mx >= 532 && *mx <= 580 && *my > 160 && *my < 190 && second != NULL && buttons)
		{
			strcpy(name, second->name);
			return 2;

		}

		if (*mx >= 532 && *mx <= 580 && *my > 210 && *my < 240 && third != NULL && buttons)
		{

			strcpy(name, third->name);
			return 2;
		}


		if (*mx >= 532 && *mx <= 580 && *my > 260 && *my < 290 && forth != NULL && buttons)
		{

			strcpy(name, forth->name);
			return 2;

		}


		if (*mx >= 532 && *mx <= 580 && *my > 310 && *my < 340 && fifth != NULL && buttons)
		{
			strcpy(name, fifth->name);
			return 2;
		}

		if (*mx >= 532 && *mx <= 580 && *my > 360 && *my < 390 && sixth != NULL && buttons)
		{
			strcpy(name, sixth->name);
			return 2;
		}
	}
}