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
Description:比较大学的函数 
Attention: 
Return:返回i为大学位置，返回0为未找到相应大学 
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
	//遍历链表查找匹配的大学 
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
Description:高级搜索界面的后台函数
Attention:通过将用户目标大学与大学文件中的信息匹配筛选 
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
	setpath *Current= head->next;					//计算大学在链表中的位置
	setpath *Goal = NULL; 				//用户的目标大学 
	setcolor(GREEN);
	setlinestyle(0 , 0, 3);
	setfillstyle(1, WHITE);						
	mouseInit(&mx, &my, &buttons);						
	while(1)
	{
		newxy(&mx, &my, &buttons);
		/*鼠标点击国家条件区域*/
		if (mx >= 200 && mx <= 280 && my >= 40 && my <= 90 && buttons) 	//美国 
		{ 
			judge = 0;
			strcpy(Goal->filter_country,"A01");
			circle(240, 105, 8);
			bar(310, 95, 330, 115);
			bar(390, 95, 410, 115);
		}
		if (mx >= 280 && mx <= 360 && my >= 40 && my <= 90 && buttons)	//英国 
		{	
			judge = 0;
			strcpy(Goal->filter_country,"A02");
			circle(320, 105, 8);
			bar(230, 95, 250, 115);
			bar(390, 95, 410, 115);
		}
		if (mx >= 360 && mx <= 440 && my >= 40 && my <= 90 && buttons)	//德国
		{	
			judge = 0;
			strcpy(Goal->filter_country,"A03");
			circle(400, 105, 8);
			bar(230, 95, 250, 115);
			bar(310, 95, 330, 115);
		}
		
		/*鼠标点击排名条件区域*/
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

		/*鼠标点击学费条件区域*/
		if (mx >= 200 && mx <= 280 && my >= 200 && my <= 250 && buttons)	//一万美元以下 
		{
			judge = 0;
			strcpy(Goal->filter_tuition,"E01");
			circle(240, 265, 8);
			bar(310, 255, 330, 275);
			bar(390, 255, 410, 275);
		}
		if (mx >= 280 && mx <= 360 && my >= 200 && my <= 250 && buttons)	//一万到两万美元 
		{
			judge = 0;
			strcpy(Goal->filter_tuition,"E02");
			circle(320, 265, 8);
			bar(230, 255, 250, 275);
			bar(390, 255, 410, 275);
		
		}
		if (mx >= 360 && mx <= 440 && my >= 200 && my <= 250 && buttons)	//两万美元以上 
		{
			judge = 0;
			strcpy(Goal->filter_tuition,"E03");
			circle(400, 265, 8);
			bar(230, 255, 250, 275);
			bar(310, 255, 330, 275);
		
		}
		
		/*鼠标点击平均绩点条件区域*/
		if (mx >= 200 && mx <= 280 && my >= 280 && my <= 330 && buttons)	//三以下 
		{
			judge = 0;
			strcpy(Goal->filter_gpa,"D01");
			circle(240, 345, 8);
			bar(310, 335, 330, 355);
			bar(390, 335, 410, 355);
			
		}
		if (mx >= 280 && mx <= 360 && my >= 280 && my <= 330 && buttons)	//三到三点五 
		{
			judge = 0;
			strcpy(Goal->filter_gpa,"D02");
			circle(320, 345, 8);
			bar(230, 335, 250, 355);
			bar(390, 335, 410, 355);
		}
		if (mx >= 360 && mx <= 440 && my >= 280 && my <= 330 && buttons)	//三点五到四 
		{
			judge = 0;
			strcpy(Goal->filter_gpa,"D03");
			circle(400, 345, 8);
			bar(230, 335, 250, 355);
			bar(310, 335, 330, 355);
		
		}

		/*鼠标点击生活成本条件区域*/
	/*	if (mx >= 200 && mx <= 280 && my >= 120 && my <= 170  && buttons)	//一千美元
		{
			judge = 0;
			strcpy(Goal->filter_livingcost,"F01");
			circle(240, 425, 8);
			bar(310, 415, 330, 435);
			bar(390, 415, 410, 435);
			
		}
		
		if (mx >= 280 && mx <= 360 && my >= 200 && my <= 250 && buttons)	//一千到一千五 
		{
			judge = 0;
			strcpy(Goal->filter_livingcost,"F02");
			circle(320, 425, 8);
			bar(230, 415, 250, 435);
			bar(390, 415, 410, 435);
			
		}
		if (mx >= 360 && mx <= 440 && my >= 120 && my <= 170  && buttons)	//一千五以上 
		{
			judge = 0; 
			strcpy(Goal->filter_livingcost,"F03");
			circle(400, 425, 8);
			bar(230, 415, 250, 435);
			bar(310, 415, 330, 435);

		}  */
		/*鼠标点击确认按键*/
		if (mx >= 280 && mx <= 360 && my >= 440 && my <= 475 && buttons)
		{
			judge = 1;	
		
		}

		 
		/*鼠标点击返回按键*/
		if (mx >= 0 && mx <= 40 && my >= 0 && my <= 40 && buttons)
			judge = 2;
			
		switch(judge)
		{
			case 1:
				i = CollegeCompare(head, Goal);
			
				//未找到相应大学 
				if(i == 0)				
				{
					judge = 2;
					WarningTips("未找到大学", 300, 200, BLUE);
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
					//有相应大学 
					return viewcollegeIntroduce(Current->englishname, head, person); 
				}
			case 2:	 
				return 1; 
				
		}
	} 
	
	
} 

/********************************************
Function: AdvancedSearchIF
Description:画高级搜索的界面 
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
	puthz(288, 442, "确认", 32, 32, WHITE);
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
	puthz(130, 55, "国家", 16, 16, BROWN);
	puthz(220, 55, "美国", 16, 16, WHITE);
	puthz(300, 55, "英国", 16, 16, WHITE);
	puthz(380, 55, "德国", 16, 16, WHITE);

	setfillstyle(1, CYAN);
	bar(200, 120, 440, 170);
	setcolor(WHITE);
	line(280, 120, 280, 170);
	line(360, 120, 360, 170);
	puthz(130, 135, "排名", 16, 16, BROWN);
	puthz(220, 135, "第一", 16, 16, WHITE);
	puthz(300, 135, "第十", 16, 16, WHITE);
	puthz(380, 135, "第二十", 16, 16, WHITE);

	setfillstyle(1, BLUE);
	bar(200, 200, 440, 250);
	setcolor(WHITE);
	line(280, 200, 280, 250);
	line(360, 200, 360, 250);
	puthz(130, 215, "学费", 16, 16, BROWN);
	puthz(210, 215, "一万以下", 16, 16, WHITE);
	puthz(290, 215, "一万五", 16, 16, WHITE);
	puthz(370, 215, "两万", 16, 16, WHITE);

	setfillstyle(1, CYAN);
	bar(200, 280, 440, 330);
	setcolor(WHITE);
	line(280, 280, 280, 330);
	line(360, 280, 360, 330);
	puthz(130, 295, "平均绩点", 16 ,16, BROWN);
	puthz(220, 295, "三点零", 16, 16, WHITE);
	puthz(300, 295, "三点五", 16, 16, WHITE);
	puthz(380, 295, "四点零", 16, 16, WHITE);

	/*setfillstyle(1, BROWN);
	bar(200, 360, 440, 410);
	setcolor(WHITE);
	line(280, 360, 280, 410);
	line(360, 360, 360, 410);
	puthz(130, 375, "生活成本", 16, 16, BROWN);
	puthz(220, 375, "一千", 16, 16, WHITE);
	puthz(300, 375, "一千五", 16, 16, WHITE);
	puthz(380, 375, "两千", 16, 16, WHITE); */
} 
