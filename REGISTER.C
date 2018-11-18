#include "register.h"
#include<stdlib.h>
#include<string.h>
#include<graphics.h>
#include "nmouse.h"
#include "input.h"
#include "hz.h"


/************************************
Function: userRegister
Description: 用户注册界面的后台函数
Attention:头指针一定要有确定的指向！
Return:返回0表示在main中调用登陆界面；
       返回2表示在main中调用主菜单界面；
*************************************/
int userRegister(setuser *head, char *accounts, char *code)
{
	int judge = 0; //判断应该调用那些函数的变量
	int mark1 = 0, mark2 = 0, mark3 = 0;  //分别为为用户名、密码、二次密码是否正确的判断变量
	int temp;  //用于吸收键盘缓冲区的变量
	char secondcode[11];  //第二次输入密码串
	int buttons, mx, my;  //鼠标参数变量


	/*必要的初始化过程*/
	secondcode[0] = '\0';
	*accounts = '\0';
	*code = '\0';

	mouseInit(&mx, &my,&buttons);

	while (1)
	{
		newxy(&mx, &my, &buttons);

		/*吸收键盘缓冲区域数据*/
		if (kbhit() != 0)
		{
			temp = bioskey(0);
		}

		if (mx >= 200 && mx <= 600 && my >= 120 && my <= 165 && buttons)judge = 1;         //if(鼠标点击新账号输入区域)
		if (mx >= 200 && mx <= 600 && my >= 200 && my <= 245 && buttons)judge = 2;         //if（鼠标点击新密码输入区域）
		if (mx >= 200 && mx <= 600 && my >= 280 && my <= 325 && buttons)judge = 3;         //if(鼠标点击再输入一次密码区域
		if (mx >= 230 && mx <= 460 && my >= 360 && my <= 415 && buttons)judge = 4;         //if(鼠标点击注册完成区域
		if (mx >= 300 && mx <= 455 && my >= 437 && my <= 455 && buttons)judge = 5;         //if(鼠标点击已有账户去登陆区域)

		/*根据judge的值判断需要调用的功能*/
		switch (judge)
		{

		/*case 1:调用账号输入函数*/
		case 1:
			judge = RegisteraccountsInput(accounts, &mx, &my);

			if (SearchAccounts(head, accounts) != NULL)
			{
				/*画红色的叉并提示该账号已被注册&&mark1=0*/
				setfillstyle(1, LIGHTBLUE);
				bar(560, 120, 600, 165);
				drawRedFork(560, 130);
				backgroundChange(mx,my,560, 120, 600, 165);
				setfillstyle(1, LIGHTBLUE);
				bar(210, 170, 550, 195);
				puthz(210,170, "该账号已被注册！", 16, 16, RED);
				backgroundChange(mx,my,210, 170, 550, 195);

				mark1 = 0;
			}
			else
			{
				/*画一个绿色的勾&&mark1=1*/
				setfillstyle(1, LIGHTBLUE);
				bar(210, 170, 550, 195);
				bar(560, 120, 600, 165);
				drawGreenHook(560, 130);
				backgroundChange(mx,my,560, 120, 600, 165);
				backgroundChange(mx,my,210, 170, 550, 195);

				mark1 = 1;
			}
			break;

		/*case 2:调用密码输入函数*/
		case 2:
			judge = RegistercodeInput(code, &mx, &my);
			if (strlen(code) < 6)
			{
				/*画红色的叉并提示密码不得少于6位&&mark2=0*/
				setfillstyle(1, LIGHTBLUE);
				bar(560, 200, 600, 245);
				drawRedFork(560, 210);
				backgroundChange(mx, my, 560, 200, 600, 245);
				setfillstyle(1, LIGHTBLUE);
				bar(210, 250, 550, 275);
				puthz(210, 250, "密码不得少于六位！", 16, 16, RED);
				backgroundChange(mx, my, 210, 250, 550, 275);

				mark2 = 0;
			}
			else
			{
				/*画一个绿色的勾&&mark2=1*/
				setfillstyle(1, LIGHTBLUE);
				bar(210, 250, 550, 275);
				bar(560, 200, 600, 245);
				drawGreenHook(560, 210);
				backgroundChange(mx, my, 560, 200, 600, 245);
				backgroundChange(mx, my, 210, 250, 550, 275);

				mark2 = 1;
			}
			break;

		/*case 3:调用二次密码输入函数*/
		case 3:
			judge = RegistersecondcodeInput(secondcode, &mx, &my);
			if (strcmp(code, secondcode) != 0)
			{
				/*画红色的叉并提示二次密码输入不同&&mark3=0*/
				setfillstyle(1, LIGHTBLUE);
				bar(560, 280, 600, 325);
				drawRedFork(560, 290);
				backgroundChange(mx, my, 560, 280, 600, 325);
				setfillstyle(1, LIGHTBLUE);
				bar(210, 330, 550, 355);
				puthz(210, 330, "两次密码输入不同！", 16, 16, RED);
				backgroundChange(mx, my, 210, 330, 550, 355);

				mark3 = 0;
			}
			else
			{
				/*画一个绿色的勾&&mark3=1*/
				setfillstyle(1, LIGHTBLUE);
				bar(210, 330, 550, 355);
				bar(560, 280, 600, 325);
				drawGreenHook(560, 290);
				backgroundChange(mx, my, 560, 280, 600, 325);
				backgroundChange(mx, my, 210, 330, 550, 355);

				mark3 = 1;
			}
			break;

		/*case 4:判断是否注册成功*/
		case 4:if (mark1 == 1 && mark2 == 1 && mark3 == 1)
		{
			AddNewUser(head, accounts, code);
			if(Choose("注册成功！\n是否自动登录？", 260,200,GREEN)==1)return 2;
			else return 0;
		}
			   break;

	    /*case 5:返回main函数调用登陆界面*/
		case 5: return 0;
		}
	}
}


/************************************
Function: RegisterIF
Description: 画注册界面的函数
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


	puthz( 60, 127,"用户名" , 32,  32, WHITE);
	puthz( 60,  207, "密码", 32,  32, WHITE);
	puthz( 60,  287, "确认密码", 32,  32, WHITE);
	puthz( 290, 370, "注册", 32, 32, WHITE);
	puthz(312, 436, "返回", 16, 16, WHITE);
	setcolor(WHITE);
	line(295, 455, 360, 455);
	puthz(240, 215, "6至10位字母与数字组合", 16, 16, BLUE);
	puthz(210, 20, "新用户注册", 48, 48,WHITE);
}


/************************************
Function: drawRedFork
Description: 在(x,y)处画一个红色的叉
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
Description: 在(x,y)处画一个绿色的勾
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
