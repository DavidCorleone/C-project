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
Description: 释放用户的收藏链表
Attention:
Return:
*******************************/
void freecollectList(setuser *person)
{
	setcollect *previous = NULL;
	setcollect *current = NULL;

	/*释放大学链表空间*/
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
Description:收藏景点或酒店
Attention:
Return:
***************************************************/
void collect(char *name, char *englishname, setuser *person)
{
	setcollect *current = NULL;
//	char *symbol="C"; 
	person->mark_collect = 1;
	
	/*将收藏写入链表*/

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
Description:删除收藏
Attention: head 为收藏链表的头指针
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
Description:重新写入用户的收藏信息到文件里
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

	/*写入收藏大学的信息*/
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
Description:画删除按钮
Attention:
***************************/
void drawDeletebutton(int x, int y)
{
	setlinestyle(0, 0, 1);
	rectangle(x, y, x+48, y+28);
	puthz(x+8, y+7, "删除", 16, 16, BROWN);
}

/*******************************
Function: manageCollect
Description:编辑、管理收藏的函数
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
			/*显示编辑界面*/
		case 0:
			judge = manageCollectIF(temp, mx, my, &(person->college));
			break;

			/*退出编辑区域*/
		case 1:
			return 2;
			break;

			/*删除收藏的操作*/
		case 2:
			deleteCollect(temp, &(person->college),person);
			judge = 0;
			break;
		}
	}

}
/**************************************************
Function: ifCollect
Description:判断景点是否已经被收藏
Input:
Attention:
Return:已收藏返回1，未收藏返回0
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
Description: 画我的收藏界面 
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
	puthz(60, 107, "密码设置", 16, 16, WHITE);
	puthz(60, 137, "我的收藏", 16, 16, WHITE);
	puthz(60, 167, "意见反馈", 16, 16, WHITE);
	puthz(60, 197, "退出登录", 16, 16, WHITE);
	rectangle(200, 100, 600, 450);
	line(200, 150, 600, 150);	//六条分割线
	line(200, 200, 600, 200);
	line(200, 250, 600, 250);
	line(200, 300, 600, 300);
	line(200, 350, 600, 350);
	line(200, 400, 600, 400);
	rectangle(200, 75, 300, 100);
	puthz(205, 80, "已收藏的大学", 16, 16, BROWN);
	rectangle(560, 75, 600, 100);
	puthz(565, 80, "编辑", 16, 16, BROWN);
} 

/*****************************
Function: showmyCollect
Description:显示收藏界面的函数
Attention:
******************************/
int showmyCollect(char *symbol, setcollect *college, int *mx, int *my)
{
  	setcollect *first = NULL;//6个指针分别指向一页中的6条信息
	setcollect *second = NULL;
	setcollect *third = NULL;
	setcollect *forth = NULL;
	setcollect *fifth = NULL;
	setcollect *sixth = NULL;
	setcollect *current = NULL;//用来计算链表节点数
	setcollect *p = NULL;
	int Currentpage = 1;    //页码
	int formerPage = 0;
	int buttons = 0;    //鼠标的参数变量

	int i;//定位到当前页的第一条信息
	int j;
	int n = 0;   //大学链表的节点个数
	current = college;
	p = college;

	while (1)
	{
		newxy(mx, my, &buttons);

		/*鼠标点击修改密码区域*/
		if (*mx >= 20 && *mx <= 150 && *my >= 100 && *my <= 130 && buttons)return 1;

		/*鼠标点击我的收藏区域*/
		if (*mx >= 20 && *mx <= 150 && *my >= 130 && *my <= 160 && buttons)return 2;

		/*鼠标点击意见反馈区域*/
		if (*mx >= 20 && *mx <= 150 && *my >= 160 && *my <= 190 && buttons)return 3;

		/*鼠标点击退出系统区域*/
		if (*mx >= 20 && *mx <= 150 && *my >= 190 && *my <= 220 && buttons)return 4;

		/*鼠标点击返回按键*/
		if (*mx >= 0 && *mx <= 20 && *my >= 0 && *my <= 20 && buttons)return 5;
		
		/*如果鼠标点击编辑区域*/
		if (*mx >= 560 && *mx <= 592 && *my >= 76 && *my <= 99 && buttons)return 6;
		
		
		if (*mx >= 200 && *mx <= 300 && *my >= 75 && *my <= 100 && buttons)
		{
			current = college;
			p = current;
			Currentpage = 1;    //页码
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
			puthz(340, 420, "上一页", 16, 16, BROWN);
			puthz(400, 420, "下一页", 16, 16, BROWN);
			setcolor(LIGHTRED);
			line(330, 428, 338, 420);
			line(338, 436, 330, 428);
			line(458, 428, 450, 420);
			line(458, 428, 450, 436);
		}
		/*鼠标点击下一页区域*/
		if (*mx >= 330 && *mx <= 390 && *my >= 420 && *my <= 436 && buttons)
		{
			Currentpage++;
			if (Currentpage > n / 6)Currentpage = n / 6;
		}

		/*鼠标点击上一页区域*/
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
		puthz(205, 80, "已收藏的大学", 16, 16, BROWN);
		rectangle(560, 75, 600, 100);
		puthz(565, 80, "编辑", 16, 16, BROWN);
		backgroundChange(*mx, *my, 560, 75, 600, 100);
		line(200, 150, 600, 150);	//六条分割线
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
			AddFrame(*mx, *my, 204, 104, 596, 146, RED);//鼠标放在第一格内容会出现红色框
			if (buttons)
			{
				strcpy(symbol, first->englishname);
				return 7;
			}
		}
		else
			AddFrame(*mx, *my, 204, 104, 596, 146, WHITE);//鼠标移走则红色框消失

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
Description:画编辑收藏界面
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
	
	int buttons = 0;    //鼠标的参数变量
	int Currentpage = 1;    //页码
	int formerPage = 0;
	int i;
	int j;
	int n = 0;   //景点链表的节点个数
	//puthz(0, 50, college->name, 16, 16, BROWN);

//	mouseInit(&mx, &my, &buttons);

	current = college;
	p = college;
	while (1)
	{
		newxy(mx, my, &buttons);

		/*如果鼠标点击退出区域*/
		if (*mx >= 560 && *mx <= 592 && *my >= 80 && *my <= 112 && buttons)
		return 1;
		
		if (*mx >= 200 && *mx <= 300 && *my >= 75 && *my <= 100 && buttons)
		{
			current = college;
			p = current;
			Currentpage = 1;    //页码
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
			puthz(340, 420, "上一页", 16, 16, BROWN);
			puthz(400, 420, "下一页", 16, 16, BROWN);
			setcolor(LIGHTRED);
			line(330, 428, 338, 420);
			line(338, 436, 330, 428);
			line(458, 428, 450, 420);
			line(458, 428, 450, 436);
		}


		/*鼠标点击上一页区域*/
		if (*mx >= 330 && *mx <= 390 && *my >= 420 && *my <= 436 && buttons)
		{
			Currentpage--;
			if (Currentpage < 1)Currentpage = 1;
		}

		/*鼠标点击下一页区域*/
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
	line(200, 150, 600, 150);	//六条分割线
	line(200, 200, 600, 200);
	line(200, 250, 600, 250);
	line(200, 300, 600, 300);
	line(200, 350, 600, 350);
	line(200, 400, 600, 400);
	rectangle(200, 75, 300, 100);
	puthz(205, 80, "已收藏的大学", 16, 16, BROWN);
	rectangle(560, 75, 600, 100);
	puthz(565, 80, "退出", 16, 16, BROWN);
	backgroundChange(*mx, *my, 560, 75, 600, 100);
		
		i = Currentpage * 6 - 4;

			/*用current定位到链表里头的第i个节点*/
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
