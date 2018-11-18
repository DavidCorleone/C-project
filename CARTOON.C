#include <stdio.h>
#include <graphics.h>
#include <stdlib.h>
#include "nmouse.h"
#include <conio.h>
#include <dos.h>
#include "hz.h"



/*****************************************************
Function: WarningTips
Description:信息提示框
Input:提醒内容content,提示框坐标x,y，提示字体颜色color
Attention:
*****************************************************/
void WarningTips(char *content, int x, int y, int color)

{
	unsigned int size;
	int i;
	void *ball;
	setcolor(LIGHTRED);
	
	setfillstyle(1, WHITE);

	bar(x - 90, y - 30, x + 110, y + 100);
	rectangle(x - 90, y - 30, x + 110, y + 100);
	puthz(x - 55, y + 55, content, 16, 16, color);

	setwritemode(XOR_PUT);
	setfillstyle(0, LIGHTRED);
	circle(x, y, 2);
	circle(x + 10, y - 5, 2);
	circle(x - 5, y + 10, 2);

	size = imagesize(x - 2, y - 2, x + 2, y + 2);
	ball = malloc(size);
	getimage(x - 2, y - 2, x + 2, y + 2, ball);
	for (i = 0;i<4;i++)
	{
		putimage(x + 8, y - 7, ball, XOR_PUT);//如果写成for循环会在每转一圈后出现卡顿
		putimage(x - 2, y + 18, ball, XOR_PUT);
		delay(100);
		putimage(x - 2, y - 2, ball, XOR_PUT);
		putimage(x + 8, y + 23, ball, XOR_PUT);
		delay(100);
		putimage(x - 7, y + 8, ball, XOR_PUT);
		putimage(x + 18, y + 18, ball, XOR_PUT);
		delay(100);
		putimage(x - 2, y + 18, ball, XOR_PUT);
		putimage(x + 23, y + 8, ball, XOR_PUT);
		delay(100);
		putimage(x + 8, y + 23, ball, XOR_PUT);
		putimage(x + 18, y - 2, ball, XOR_PUT);
		delay(100);
		putimage(x + 18, y + 18, ball, XOR_PUT);
		putimage(x + 8, y - 7, ball, XOR_PUT);
		delay(100);
		putimage(x + 23, y + 8, ball, XOR_PUT);
		putimage(x - 2, y - 2, ball, XOR_PUT);
		delay(100);
		putimage(x - 7, y + 8, ball, XOR_PUT);
		putimage(x + 18, y - 2, ball, XOR_PUT);
		delay(100);
	}
	free(ball);
}



/***********************************************************
Function: Choose
Description:选择框
Input:选择内容content,提示框坐标指针mx,my，提示字体颜色color
return:点击“是”返回1，点击“否”返回0
**********************************************************/
int Choose(char *content, int *mx, int *my, int color)
{
	int buttons;

	setcolor(BLUE);
	setfillstyle(1, BLUE);
	bar(200, 160, 420, 300);
	rectangle(200, 160, 420, 300);
	puthz(240, 200, content, 16, 16, color);

	setfillstyle(1, WHITE);
	bar(233, 248, 267, 272);
	bar(358, 248, 392, 272);
	rectangle(233, 248, 267, 272);
	rectangle(358, 248, 392, 272);
	setlinestyle(1, 0, 1);
	rectangle(235, 250, 265, 270);
	rectangle(360, 250, 390, 270);
	setlinestyle(3, 0, 1);
	rectangle(202, 162, 418, 298);
	setlinestyle(0, 0, 1);
	setcolor(WHITE);
	puthz(240, 252, "是", 16, 16, GREEN);
	puthz(365, 252, "否", 16, 16, LIGHTRED);


	while (1)
	{
		newxy(mx, my, &buttons);

		if (*mx >= 240 && *mx <= 256 && *my >= 252 && *my <= 268 && buttons)
			return 1;
		else if (*mx >= 365 && *mx <= 381 && *my >= 252 && *my <= 268 && buttons)
			return 0;
	}
}


