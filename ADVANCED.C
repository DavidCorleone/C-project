#include<stdio.h>
#include<dos.h>
#include<string.h>
#include<bios.h> 
#include<stdlib.h>
#include<conio.h>
#include<graphics.h>
#include"hz.h"
#include"nmouse.h" 
#include"input.h"
#include"structur.h"
#include"search.h"
#include"advanced.h" 
#include "view.h"
#include "cartoon.h"
/********************************************
Function: CollegeCompare
Description:�Ƚϴ�ѧ�ĺ��� 
Attention: 
Return:����iΪ��ѧλ�ã�����0Ϊδ�ҵ���Ӧ��ѧ 
********************************************/
int CollegeCompare(setpath *head,setpath *Goal)
{
	int n;
	setpath *Current;
	Current = head->next;
	/*if(1)
	{
		closegraph();
		//printf("Can't open %s%s%s%s", Goal->filter_country,Goal->filter_globalrank,Goal->filter_gpa,Goal->filter_tuition);  //"FILES\\college\\mit"  test
		printf("Can't open %s", head->next->englishname);//Current->next->filter_country,Current->next->filter_globalrank,Current->next->filter_gpa,Current->next->filter_tuition);
		getchar();
		exit(1);  
	}*/
	//������������ƥ��Ĵ�ѧ 
	for(n = 1; n < 10; n++)			
	{
		if((!strcmp(Current->filter_country,Goal->filter_country))&&(!strcmp(Current->filter_tuition,Goal->filter_tuition))&&(!strcmp(Current->filter_globalrank,Goal->filter_globalrank))/*&&(!strcmp(Current->filter_livingcost,Goal->filter_livingcost))*/&&(!strcmp(Current->filter_gpa,Goal->filter_gpa)))	
		{
	 		return n;
		}
		Current = Current->next;
	}
	return 0;
} 
/********************************************
Function: AdvancedSearch
Description:�߼���������ĺ�̨����
Attention:ͨ�����û�Ŀ���ѧ���ѧ�ļ��е���Ϣƥ��ɸѡ 
Return:
********************************************/
int AdvancedSearch(setpath *head, setuser *person)
{ 
	int judge = 0 ;
	int mx, my, buttons; 
	int i = 1;
	int j;
	int driver = VGA;
	int mode = VGAHI;
	setpath *Current= head->next;					//�����ѧ�������е�λ��
	setpath *Goal = NULL; 				//�û���Ŀ���ѧ 
	setcolor(GREEN);
	setlinestyle(0 , 0, 3);
	setfillstyle(1, WHITE);						
	mouseInit(&mx, &my, &buttons);						
	while(1)
	{
		newxy(&mx, &my, &buttons);
		/*�����������������*/
		if (mx >= 200 && mx <= 280 && my >= 40 && my <= 90 && buttons) 	//���� 
		{ 
			judge = 0;
			strcpy(Goal->filter_country,"A01");
			circle(240, 105, 8);
			bar(310, 95, 330, 115);
			bar(390, 95, 410, 115);
		}
		if (mx >= 280 && mx <= 360 && my >= 40 && my <= 90 && buttons)	//Ӣ�� 
		{	
			judge = 0;
			strcpy(Goal->filter_country,"A02");
			circle(320, 105, 8);
			bar(230, 95, 250, 115);
			bar(390, 95, 410, 115);
		}
		if (mx >= 360 && mx <= 440 && my >= 40 && my <= 90 && buttons)	//�¹�
		{	
			judge = 0;
			strcpy(Goal->filter_country,"A03");
			circle(400, 105, 8);
			bar(230, 95, 250, 115);
			bar(310, 95, 330, 115);
		}
		
		/*�����������������*/
		if (mx >= 200 && mx <= 280 && my >= 120 && my <= 170  && buttons) 
		{
			judge = 0;
			strcpy(Goal->filter_globalrank,"1");
			circle(240, 185, 8);
			bar(310, 175, 330, 195);
			bar(390, 175, 410, 195);
		}
		if (mx >= 280 && mx <= 360 && my >= 120 && my <= 170  && buttons) 
		{
			judge = 0;
			strcpy(Goal->filter_globalrank,"10");
			circle(320, 185, 8);
			bar(230, 175, 250, 195);
			bar(390, 175, 410, 195);
		}
		if (mx >= 360 && mx <= 440 && my >= 120 && my <= 170  && buttons) 
		{
			judge = 0;
			strcpy(Goal->filter_globalrank,"20");
			circle(400, 185, 8);
			bar(230, 175, 250, 195);
			bar(310, 175, 330, 195);
		}

		/*�����ѧ����������*/
		if (mx >= 200 && mx <= 280 && my >= 200 && my <= 250 && buttons)	//һ����Ԫ���� 
		{
			judge = 0;
			strcpy(Goal->filter_tuition,"E01");
			circle(240, 265, 8);
			bar(310, 255, 330, 275);
			bar(390, 255, 410, 275);
		}
		if (mx >= 280 && mx <= 360 && my >= 200 && my <= 250 && buttons)	//һ��������Ԫ 
		{
			judge = 0;
			strcpy(Goal->filter_tuition,"E02");
			circle(320, 265, 8);
			bar(230, 255, 250, 275);
			bar(390, 255, 410, 275);
		
		}
		if (mx >= 360 && mx <= 440 && my >= 200 && my <= 250 && buttons)	//������Ԫ���� 
		{
			judge = 0;
			strcpy(Goal->filter_tuition,"E03");
			circle(400, 265, 8);
			bar(230, 255, 250, 275);
			bar(310, 255, 330, 275);
		
		}
		
		/*�����ƽ��������������*/
		if (mx >= 200 && mx <= 280 && my >= 280 && my <= 330 && buttons)	//������ 
		{
			judge = 0;
			strcpy(Goal->filter_gpa,"D01");
			circle(240, 345, 8);
			bar(310, 335, 330, 355);
			bar(390, 335, 410, 355);
			
		}
		if (mx >= 280 && mx <= 360 && my >= 280 && my <= 330 && buttons)	//���������� 
		{
			judge = 0;
			strcpy(Goal->filter_gpa,"D02");
			circle(320, 345, 8);
			bar(230, 335, 250, 355);
			bar(390, 335, 410, 355);
		}
		if (mx >= 360 && mx <= 440 && my >= 280 && my <= 330 && buttons)	//�����嵽�� 
		{
			judge = 0;
			strcpy(Goal->filter_gpa,"D03");
			circle(400, 345, 8);
			bar(230, 335, 250, 355);
			bar(310, 335, 330, 355);
		
		}

		/*���������ɱ���������*/
	/*	if (mx >= 200 && mx <= 280 && my >= 120 && my <= 170  && buttons)	//һǧ��Ԫ
		{
			judge = 0;
			strcpy(Goal->filter_livingcost,"F01");
			circle(240, 425, 8);
			bar(310, 415, 330, 435);
			bar(390, 415, 410, 435);
			
		}
		
		if (mx >= 280 && mx <= 360 && my >= 200 && my <= 250 && buttons)	//һǧ��һǧ�� 
		{
			judge = 0;
			strcpy(Goal->filter_livingcost,"F02");
			circle(320, 425, 8);
			bar(230, 415, 250, 435);
			bar(390, 415, 410, 435);
			
		}
		if (mx >= 360 && mx <= 440 && my >= 120 && my <= 170  && buttons)	//һǧ������ 
		{
			judge = 0; 
			strcpy(Goal->filter_livingcost,"F03");
			circle(400, 425, 8);
			bar(230, 415, 250, 435);
			bar(310, 415, 330, 435);

		}  */
		/*�����ȷ�ϰ���*/
		if (mx >= 280 && mx <= 360 && my >= 440 && my <= 475 && buttons)
		{
			judge = 1;	
		
		}

		 
		/*��������ذ���*/
		if (mx >= 0 && mx <= 40 && my >= 0 && my <= 40 && buttons)
			judge = 2;
			
		switch(judge)
		{
			case 1:
				i = CollegeCompare(head, Goal);
			
				//δ�ҵ���Ӧ��ѧ 
				if(i == 0)				
				{
					judge = 2;
					WarningTips("δ�ҵ���ѧ", 300, 200, BLUE);
					initgraph(&driver, &mode, "../BORLANDC\\bgi");
					cleardevice();
					break;
				}
				else
				{
					j=1;
					while(j<i)
					{
						Current = Current->next;
						j++; 
					}
					//����Ӧ��ѧ 
					return viewcollegeIntroduce(Current->englishname, head, person); 
				}
			case 2:	 
				return 1; 
				
		}
	} 
	
	
} 

/********************************************
Function: AdvancedSearchIF
Description:���߼������Ľ��� 
Attention:
Return:
********************************************/
void AdvancedSearchIF()
{
	cleardevice();
	setbkcolor(WHITE);  
	setlinestyle(0, 0, 1);
	setfillstyle(1, BLUE);
	bar(280, 440, 360, 475);
	puthz(288, 442, "ȷ��", 32, 32, WHITE);
	setfillstyle(1, LIGHTGRAY);
	bar(0, 0, 40, 40);
	setcolor(WHITE); 
	line(10, 20, 35, 20);
	line(10, 20, 20, 10);
	line(10, 20, 20, 30);
	
	setfillstyle(1, BROWN);
	bar(200, 40, 440, 90);
	setcolor(WHITE);
	line(280, 40, 280, 90);
	line(360, 40, 360, 90);
	puthz(130, 55, "����", 16, 16, BROWN);
	puthz(220, 55, "����", 16, 16, WHITE);
	puthz(300, 55, "Ӣ��", 16, 16, WHITE);
	puthz(380, 55, "�¹�", 16, 16, WHITE);

	setfillstyle(1, CYAN);
	bar(200, 120, 440, 170);
	setcolor(WHITE);
	line(280, 120, 280, 170);
	line(360, 120, 360, 170);
	puthz(130, 135, "����", 16, 16, BROWN);
	puthz(220, 135, "��һ", 16, 16, WHITE);
	puthz(300, 135, "��ʮ", 16, 16, WHITE);
	puthz(380, 135, "�ڶ�ʮ", 16, 16, WHITE);

	setfillstyle(1, BLUE);
	bar(200, 200, 440, 250);
	setcolor(WHITE);
	line(280, 200, 280, 250);
	line(360, 200, 360, 250);
	puthz(130, 215, "ѧ��", 16, 16, BROWN);
	puthz(210, 215, "һ������", 16, 16, WHITE);
	puthz(290, 215, "һ����", 16, 16, WHITE);
	puthz(370, 215, "����", 16, 16, WHITE);

	setfillstyle(1, CYAN);
	bar(200, 280, 440, 330);
	setcolor(WHITE);
	line(280, 280, 280, 330);
	line(360, 280, 360, 330);
	puthz(130, 295, "ƽ������", 16 ,16, BROWN);
	puthz(220, 295, "������", 16, 16, WHITE);
	puthz(300, 295, "������", 16, 16, WHITE);
	puthz(380, 295, "�ĵ���", 16, 16, WHITE);

	/*setfillstyle(1, BROWN);
	bar(200, 360, 440, 410);
	setcolor(WHITE);
	line(280, 360, 280, 410);
	line(360, 360, 360, 410);
	puthz(130, 375, "����ɱ�", 16, 16, BROWN);
	puthz(220, 375, "һǧ", 16, 16, WHITE);
	puthz(300, 375, "һǧ��", 16, 16, WHITE);
	puthz(380, 375, "��ǧ", 16, 16, WHITE); */
} 