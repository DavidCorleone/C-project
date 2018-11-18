#include "input.h"
#include "keyboard.h"
#include "nmouse.h"
#include<stdio.h>
#include<bios.h>
#include <graphics.h>
#include<conio.h>
/***********************************************************
Function: RegisteraccountsInput
Description: 1、用户注册界面的账号输入函数
             2、只能是大小写字母与数字
             3、能输入1到10位
Attention:鼠标位置参数必须要以指针形式传递过来！
Return:返回2在userRegister中调用LogincodeInput函数
       返回3在userRegister中调用RegistersecondcodeInput函数
       返回4在userRegister中使用登陆功能
       返回5在userRegister中使用注册功能
************************************************************/
int RegisteraccountsInput(char *accounts, int *mx, int *my) 
{
	int key;    //表示键值的变量
	int i = 0;   //用于计算已输入的字符数目的变量
	char *p = accounts;   //输入字符的中间指针变量
	char ch;     //用于临时储存键值所对应字符的变量
	int buttons;    //鼠标的参数变量
	char temp[2] = { '\0','\0' };  //用于outtextxy函数输出单个字符的数组

    /*使p指向'\0',i表示当前字符数*/
	while (*p != '\0')
	{
		i++;
		p++;
	}

	/*画框*/
	AddFrame(*mx, *my, 199, 119, 551, 166, RED);

	while (1)
	{
		newxy(mx, my, &buttons);

		/*重置键值并得到新键值*/
		key = 0;
		if (kbhit() != 0)
		{
			key = bioskey(0);
		}

		/*if(按了一次enter键或鼠标点击密码输入区域或按了一次下方向键)返回2表示调用RegistercodeInput函数*/
		if (*mx >= 200 && *mx <=550 && *my >= 200 && *my <= 245 && buttons || key == 0x1c0d || key == 0x5000)
		{
			AddFrame(*mx, *my, 199, 119, 551, 166, BLACK);
			return 2; 
		}

		/*if（鼠标点击再一次输入密码区域）返回3表示调用RegistersecondcodeInput函数*/
		if (*mx >= 200 && *mx <= 550 && *my >= 280 && *my <= 325 && buttons)
		{
			AddFrame(*mx, *my, 199, 119, 551, 166, BLACK);
			return 3;       
		}

		/*if(点击注册完成区域)返回4表示注册完成并发送登录请求 */
		if (*mx >= 230 && *mx <= 460 && *my >= 360 && *my <= 415 && buttons)
		{
			AddFrame(*mx, *my, 199, 119, 551, 166, BLACK);
			return 4;       
		}

		/*if(点击已有账号并登录区域)返回5表示返回登陆界面*/
		if (*mx >= 300 && *mx <= 455 && *my >= 437 && *my <= 455 && buttons)
		{
			AddFrame(*mx, *my, 199, 119, 551, 166, BLACK);
			return 5;       
		}

		/*按了回删键*/
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

		/*将按键对应的字符存入accounts数组中*/
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
Description: 1、用户注册界面的密码输入函数
             2、只能是大小写字母与数字
             3、能输入1到10位
Attention:鼠标位置参数必须要以指针形式传递过来！
Return:返回1在userRegister中调用RegisteraccountsInput函数
       返回3在userRegister中调用RegistersecondcodeInput函数
       返回4在userRegister中使用登陆功能
       返回5在userRegister中使用注册功能
************************************************************/
int RegistercodeInput(char *code, int *mx, int *my) //登陆界面新密码输入函数
{
	int key;     //表示键值的变量
	int i = 0;   //用于计算已输入的字符数目的变量
	char *p = code;     //输入字符的中间指针变量
	char ch;     //用于临时储存键值所对应字符的变量
	int buttons;     //鼠标的参数变量

	/*盖住密码输入提示的那行字*/
	if (*code == '\0')
	{
		setfillstyle(1, WHITE);
		bar(200, 200, 550, 245);

		backgroundChange(*mx, *my, 200, 200, 550, 245);
	}

	/*画框*/
	AddFrame(*mx, *my, 199, 199, 551, 246, RED);

	/*使p指向'\0',i表示当前字符数*/
	while (*p != '\0')
	{
		i++;
		p++;
	}

	while (1)
	{
		newxy(mx, my, &buttons);

		/*重置键值并得到新键值*/
		key = 0;
		if (kbhit() != 0)
		{
			key = bioskey(0);
		}

		/*if(鼠标点击账号输入区域或按了一次上方向键)返回1表示调用RegisteraccountsInput函数*/
		if (*mx >= 200 && *mx <=550 && *my >= 120 && *my <= 165 && buttons || key == 0x4800)
		{
			AddFrame(*mx, *my, 199, 199, 551, 246, BLACK);
			return 1; 
		}

		/*if(鼠标点击再次输入密码区域或按了一次enter键或下方向键) 返回3表示调用RegistersecondcodeInput函数*/
		if (*mx >= 200 && *mx <= 550 && *my >= 280 && *my <= 325 && buttons || key == 0x5000 || key == 0x1c0d)
		{
			AddFrame(*mx, *my, 199, 199, 551, 246, BLACK);
			return 3;
		}

		/*if(点击注册完成区域) 返回4表示注册完成并登陆*/
		if (*mx >= 230 && *mx <= 460 && *my >= 360 && *my <= 415 && buttons)
		{
			AddFrame(*mx, *my, 199, 199, 551, 246, BLACK);
			return 4;    
		}

		/*if(点击已有账号区域) 返回5表示返回登陆界面*/
		if (*mx >= 300 && *mx <= 455 && *my >= 437 && *my <= 455 && buttons)
		{
			AddFrame(*mx, *my, 199, 199, 551, 246, BLACK);
			return 5;       
		}

		/*按了回删键*/
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

		/*将键值存入code数组*/
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
Description: 1、用户注册界面的密码第二次输入函数
             2、只能是大小写字母与数字
             3、能输入1到10位
Attention:鼠标位置参数必须要以指针形式传递过来！
Return:返回1在userRegister中调用RegisteraccountsInput函数
       返回2在userRegister中调用RegistercodeInput函数
	   返回4在userRegister中使用登陆功能
	   返回5在userRegister中使用注册功能
************************************************************/
int RegistersecondcodeInput(char *secondcode, int *mx, int *my)
{
	int key;     //表示键值的变量
	int i = 0;   //用于计算已输入的字符数目的变量
	char *p = secondcode;     //输入字符的中间指针变量
	char ch;     //用于临时储存键值所对应字符的变量
	int buttons=0;     //鼠标的参数变量

	/*画框*/
	AddFrame(*mx, *my, 199, 279, 551, 326, RED);

	/*使p指向'\0',i表示当前字符数*/
	while (*p != '\0')
	{
		i++;
		p++;
	}

	while (1)
	{
		newxy(mx, my, &buttons);

		/*重置键值并得到新键值*/
		key = 0;
		if (kbhit() != 0)
		{
			key = bioskey(0);
		}

		/*if(鼠标点击账号输入区域)返回1表示调用RegisteraccountsInput函数*/
		if (*mx >= 200 && *mx <= 550 && *my >= 120 && *my <= 165 && buttons)
		{
			AddFrame(*mx, *my, 199, 279, 551, 326, BLACK);
			return 1;          
		}

		/*if(鼠标点击新密码输入区域或按了一下上方向键)返回2表示调用RegistercodeInput函数*/
		if (*mx >= 200 && *mx <= 550 && *my >= 200 && *my <= 245 && buttons || key == 0x4800)
		{
			AddFrame(*mx, *my, 199, 279, 551, 326, BLACK);
			return 2; 
		}

		/*if(按了一次enter键或点击登陆区域)返回4表示注册完成并登陆*/
		if (*mx >= 230 && *mx <= 460 && *my >= 360 && *my <= 415 && buttons || key == 0x1c0d)
		{
			AddFrame(*mx, *my, 199, 279, 551, 326, BLACK);
			return 4;      
		}

		/*if(点击已有账号区域)返回5表示返回登陆界面*/
		if (*mx >= 300 && *mx <= 455 && *my >= 437 && *my <= 455 && buttons)
		{
			AddFrame(*mx, *my, 199, 279, 551, 326, BLACK);
			return 5;    
		}

		/*按了回删键*/
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

		/*将键值存入secondcode数组*/
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
Description: 搜索框的输入函数
Attention:
Return:1、返回0表示退出输入且不进行任何其他操作
       2、返回2表示在上一级函数中进行首拼检索
************************************************************/
int  searchInput(char *abbreviation, int *mx,  int *my)
{
	int key;    //表示键值的变量
	int i = 0;   //用于计算已输入的字符数目的变量
	char *p = abbreviation;   //输入字符的中间指针变量
	char ch;     //用于临时储存键值所对应字符的变量
	int buttons;    //鼠标的参数变量
	char temp[2] = { '\0','\0' };  //用于outtextxy函数输出单个字符的数组

    /*使p指向'\0',i表示当前字符数*/
	while (*p != '\0')
	{
		i++;
		p++;
	}

	/*画框*/
	setlinestyle(0, 0, 3);
	AddFrame(*mx, *my, 125, 410, 425, 450 , BROWN);
	setlinestyle(0, 0, 1);

	while (1)
	{
		newxy(mx, my, &buttons);

		/*重置键值并得到新键值*/
		key = 0;
		if (kbhit() != 0)
		{
			key = bioskey(0);
		}

		/*if(点击搜索框以外的区域)返回0表示退出输入*/
		if (buttons&&(*mx <=125 || *mx >= 425|| *my <= 410|| *my >=450))
		{
			setlinestyle(0, 0, 3);
			AddFrame(*mx, *my, 125, 410, 425, 450 , WHITE);
			setlinestyle(0, 0, 1);
			AddFrame(*mx, *my, 125, 410, 425, 450, BROWN);
			return 0;
		}

		/*if(点击搜索按钮)返回2表示在search函数中进行首拼检索*/
		if (*mx >= 425 && *mx <= 475 && *my >= 410 && *my <= 450 && buttons)
		{
			setlinestyle(0, 0, 3);
			AddFrame(*mx, *my, 125, 410, 425, 450, WHITE);
			setlinestyle(0, 0, 1);
			AddFrame(*mx, *my, 125, 410, 425, 450, BROWN);
			return 2;
		}

		/*按了回删键*/
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

		/*将按键对应的字符存入abbreviation数组中*/
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
Description: 1、个人信息界面的账号输入函数
             2、只能是大小写字母与数字
             3、能输入1到10位
Attention:鼠标位置参数必须要以指针形式传递过来！
Return:
************************************************/
int oldcodeinput(char *code, int *mx, int *my)
{
	int key;    //表示键值的变量
	int i = 0;   //用于计算已输入的字符数目的变量
	char *p = code;   //输入字符的中间指针变量
	char ch;     //用于临时储存键值所对应字符的变量
	int buttons;    //鼠标的参数变量
	char temp[2] = { '\0','\0' };  //用于outtextxy函数输出单个字符的数组


	/*使p指向'\0',i表示当前字符数*/
	while (*p != '\0')
	{
		i++;
		p++;
	}

	/*画框*/
	AddFrame(*mx, *my, 250, 100, 400, 130, RED);

	while (1)
	{
		newxy(mx, my, &buttons);

		/*重置键值并得到新键值*/
		key = 0;
		if (kbhit() != 0)
		{
			key = bioskey(0);
		}

		/* if(按了一次enter键或鼠标点击密码输入区域或按了一次下方向键)返回1表示调用newcodeinput函数*/
		if (*mx >= 250 && *mx <= 400 && *my >= 140 && *my <= 170 && buttons || key == 0x1c0d || key == 0x5000)
		{
			AddFrame(*mx, *my, 250, 100, 400, 130, BLUE);
			return 1;
		}

		/* if(鼠标点击二次密码输入区域)返回2表示调用secondcodeinput函数*/
		if (*mx >= 250 && *mx <= 400 && *my >= 200 && *my <= 230 && buttons)
		{
			AddFrame(*mx, *my, 250, 100, 400, 130, BLUE);
			return 2;
		}

		/*鼠标点击修改密码*/
		if (*mx >= 295 && *mx <= 345 && *my >= 250 && *my <= 280 && buttons)
		{
			AddFrame(*mx, *my, 250, 100, 400, 130, BLUE);
			return 3;
		};

		/*如果按了回删键*/
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

		/*将按键对应的字符存入accounts数组中*/
		ch = searchKeyValue(key);
		if (ch != '\0'&&i<10)
		{
			/*将字符显示出来*/
			setfillstyle(1, WHITE);
			bar(260 + i * 11, 103, 271 + i * 11, 127);
			temp[0] = ch;
			settextstyle(2, 0, 6);
			setcolor(BLUE);
			outtextxy(260 + i * 11, 107, temp);
			backgroundChange(*mx, *my, 260 + i * 11, 101, 271 + i * 11, 129);

			/*将字符存入数组中*/
			*p = ch;
			p++;
			*p = '\0';
			i++;
		}

	}
}

/***********************************************
Function: newcodeinput
Description: 1、个人信息界面的账号输入函数
2、只能是大小写字母与数字
3、能输入1到10位
Attention:鼠标位置参数必须要以指针形式传递过来！
Return:
************************************************/
int newcodeinput(char *code, int *mx, int *my)
{
	int key;    //表示键值的变量
	int i = 0;   //用于计算已输入的字符数目的变量
	char *p = code;   //输入字符的中间指针变量
	char ch;     //用于临时储存键值所对应字符的变量
	int buttons;    //鼠标的参数变量


								   /*使p指向'\0',i表示当前字符数*/
	while (*p != '\0')
	{
		i++;
		p++;
	}

	/*画框*/
	AddFrame(*mx, *my, 250, 140, 400, 170, RED);

	while (1)
	{
		newxy(mx, my, &buttons);

		/*重置键值并得到新键值*/
		key = 0;
		if (kbhit() != 0)
		{
			key = bioskey(0);
		}

		/* if(鼠标点击密码输入区域或按了一次上方向键)返回0表示调用oldcodeinput函数*/
		if (*mx >= 250 && *mx <= 400 && *my >= 100 && *my <= 130 && buttons || key == 0x4800)
		{
			AddFrame(*mx, *my, 250, 140, 400, 170, BLUE);
			return 0;
		}

		/* if(按了一次enter键或鼠标点击密码输入区域或按了一次下方向键)返回2表示调用secondcodeinput函数*/
		if (*mx >= 250 && *mx <= 400 && *my >= 200 && *my <= 230 && buttons || key == 0x1c0d || key == 0x5000)
		{
			AddFrame(*mx, *my, 250, 140, 400, 170, BLUE);
			return 2;
		}

		/*鼠标点击修改密码*/
		if (*mx >= 295 && *mx <= 345 && *my >= 250 && *my <= 280 && buttons)
		{
			AddFrame(*mx, *my, 250, 140, 400, 170, BLUE);
			return 3;
		};

		/*如果按了回删键*/
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

		/*将按键对应的字符存入accounts数组中*/
		ch = searchKeyValue(key);
		if (ch != '\0'&&i<10)
		{
			/*画一个圆*/
			setfillstyle(1, WHITE);
			bar(260 + i * 11, 143, 271 + i * 11, 167);
			setcolor(BLUE);
			setfillstyle(1, BLUE);
			pieslice(265 + i * 11, 155, 0, 360, 4);

			backgroundChange(*mx, *my, 260 + i * 11, 143, 271 + i * 11, 167);


			/*将字符存入数组中*/
			*p = ch;
			p++;
			*p = '\0';
			i++;
		}

	}
}


/***********************************************
Function: secondcodeinput
Description: 1、个人信息界面的账号输入函数
             2、只能是大小写字母与数字
             3、能输入1到10位
Attention:鼠标位置参数必须要以指针形式传递过来！
Return:
************************************************/
int secondcodeinput(char *code, int *mx, int *my)
{
	int key;    //表示键值的变量
	int i = 0;   //用于计算已输入的字符数目的变量
	char *p = code;   //输入字符的中间指针变量
	char ch;     //用于临时储存键值所对应字符的变量
	int buttons;    //鼠标的参数变量
	char temp[2] = { '\0','\0' };  //用于outtextxy函数输出单个字符的数组


								   /*使p指向'\0',i表示当前字符数*/
	while (*p != '\0')
	{
		i++;
		p++;
	}

	/*画框*/
	AddFrame(*mx, *my, 250, 200, 400, 230, RED);

	while (1)
	{
		newxy(mx, my, &buttons);

		/*重置键值并得到新键值*/
		key = 0;
		if (kbhit() != 0)
		{
			key = bioskey(0);
		}

		/* if(鼠标点击密码输入区域)返回0表示调用oldcodeinput函数*/
		if (*mx >= 250 && *mx <= 400 && *my >= 100 && *my <= 130 && buttons)
		{
			AddFrame(*mx, *my, 250, 200, 400, 230, BLUE);
			return 0;
		}

		/* if(按了一次enter键或鼠标点击密码输入区域或按了一次下方向键)返回1表示调用newcodeinput函数*/
		if (*mx >= 250 && *mx <= 400 && *my >= 140 && *my <= 170 && buttons || key == 0x4800)
		{
			AddFrame(*mx, *my, 250, 200, 400, 230, BLUE);
			return 1;
		}

		/*鼠标点击修改密码*/
		if (*mx >= 295 && *mx <= 345 && *my >= 250 && *my <= 280 && buttons)
		{
			AddFrame(*mx, *my, 250, 200, 400, 230, BLUE);
			return 3;
		};

		/*如果按了回删键*/
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

		/*将按键对应的字符存入accounts数组中*/
		ch = searchKeyValue(key);
		if (ch != '\0'&&i<10)
		{

			/*画一个圆*/
			setfillstyle(1, WHITE);
			bar(260 + i * 11, 203, 271 + i * 11, 227);
			setcolor(BLUE);
			setfillstyle(1, BLUE);
			pieslice(265 + i * 11, 215, 0, 360, 4);

			backgroundChange(*mx, *my, 260 + i * 11, 203, 271 + i * 11, 227);

			/*将字符存入数组中*/
			*p = ch;
			p++;
			*p = '\0';
			i++;
		}

	}
}




