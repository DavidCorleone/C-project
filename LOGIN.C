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
Description: 用户登陆界面的后台函数
Attention:头指针一定要有确定的指向！
Return:返回1表示调用注册界面；
       返回2表示进入普通用户界面；
       返回5表示进入管理员界面； 
*************************************/
int userLogin(setuser *head, char *accounts, char *code)
{
	int judge = 0;    //判断应该调用哪些函数的变量
	int temp;    //用于吸收键盘缓冲区的变量
	char *rightcode=NULL;  //指向正确密码的指针
	int buttons, mx, my;   //鼠标参数变量
	int driver = VGA;
	int mode = VGAHI;


	/*必要的初始化过程*/
	mouseInit(&mx, &my, &buttons);
	*accounts = '\0';
	*code = '\0';
	//setMouseShape(1);

	while (1)
	{
		newxy(&mx, &my, &buttons);

		/*吸收键盘缓冲区域数据*/
		if (kbhit() != 0)
		{
			temp = bioskey(0);
		}

		if (mx >= 220 && mx <= 420 && my >= 160 && my <= 200 && buttons)judge = 1;   //if(鼠标点击【账号输入】区域)
		if (mx >= 220 && mx <= 420 && my >= 220 && my <= 260 && buttons)judge = 2;   //if(鼠标点击【密码输入】区域)
		if (mx >= 330 && mx <= 420 && my >= 280 && my <= 320 && buttons)judge = 3;   //if(鼠标点击【登陆】区域)
		if (mx >= 220 && mx <= 310 && my >= 280 && my <= 320 && buttons)return 1;    //if(鼠标点击【注册】区域)
		if (mx >= 220  && mx <= 420 && my >= 340 && my <= 380 && buttons)judge=5;		//if(鼠标点击【会员登录】区域） 
		/*鼠标点击退出系统区域*/
		if (mx >= 580 && mx <= 630 && my >= 20 && my <= 70 && buttons)
		{
			if (Choose("是否退出系统？", &mx, &my, WHITE) == 0)
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
				 //return 2;  //在main中调用2号界面（主菜单界面）及其后台函数
			 else
			 {
				puthz(450, 160, "用户名或密码输入错误！", 16, 16, BLACK);
				break;
			 }
		  }
		    break;
		case 4:
			LoginIF();
			getMousebk(mx, my);
			judge = 0;
			break;
		//会员登录 
		case 5:
			if (strcmp(accounts, "heming") == 0 && strcmp(code, "666666") == 0)
			{
				WarningTips("登陆成功！", 260, 200, BLUE);
				//initgraph(&driver, &mode, ".BORLANDC\\bgi");
				initgraph(&driver, &mode, "../BORLANDC\\bgi");
				cleardevice();
				return 5;
			}
			else
			{
				WarningTips("密码不匹配！", 260, 200, BLUE);
				//initgraph(&driver, &mode, "C:\\BORLANDC\\bgi");
				initgraph(&driver, &mode, "../BORLANDC\\bgi");
				cleardevice();
				return 0;
			} 
		}
	}
}



/************************************
Function:画登录界面函数
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
    bar(220, 160, 420, 200);  //账号密码框
	bar(220, 220, 420, 260);
	
	setlinestyle(0,0,3);	//画地球仪	
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
    bar(220, 280, 310, 320);  //注册登录框
	bar(330, 280, 420, 320);
	bar(220, 340, 420, 380);

	setfillstyle(1, BLUE);
	bar(0, 430, 640, 480);

	setlinestyle(0, 0, 3);     
	setcolor(WHITE);
	line(590, 30, 620, 60);
	line(590, 60, 620, 30);

	puthz(150, 160, "账号", 32, 32, WHITE);
	puthz(150, 220, "密码", 32, 32, WHITE);
	puthz(250, 290, "注册", 16, 16, BLUE);
	puthz(360, 290, "登录", 16, 16, BLUE);
	puthz(280, 350, "会员登录", 16, 16, BLUE);
	settextstyle(0, 0, 2);

    puthz(120, 445, "自动化1705     戴伟伟   熊海明", 16, 16, WHITE);

    settextstyle(0, 0, 6);
	puthz(120, 50, "出国留学咨询系统", 48, 48, WHITE);
}

/***********************************************
Function: LoginaccountsInput
Description: 1、用户登陆界面的账号输入函数
2、只能是大小写字母与数字
3、能输入1到10位
Attention:鼠标位置参数必须要以指针形式传递过来！
Return:返回2在userLogin中调用LogincodeInput函数
返回3在userLogin中使用登陆功能
返回4在userLogin中使用注册功能
************************************************/
int LoginaccountsInput(char *accounts, int *mx, int *my)
{
    int key;    //表示键值的变量
	int i = 0;   //用于计算已输入的字符数目的变量
	char *p = accounts;   //输入字符的中间指针变量
	char ch;     //用于临时储存键值所对应字符的变量
	int buttons;    //鼠标的参数变量
	char temp[2] = { '\0','\0' };  //用于outtextxy函数输出单个字符的数组

                                    //使p指向'\0'，i表示当前字符数
    while(*p!='\0')
    {
        p++;
        i++;
    }

    //画框
    AddFrame(*mx, *my, 220, 160, 420, 200, BROWN);

    while(1)
    {
        newxy(mx, my, &buttons);
        /*重置键值并得到新键值*/
        key = 0;
		if (kbhit() != 0)
		{
			key = bioskey(0);
		}
		/* if(按了一次enter键或鼠标点击密码输入区域或按了一次下方向键)返回2表示调用LogincodeInput函数*/
		if (*mx >= 210 && *mx <= 420 && *my >= 210 && *my <= 260 && buttons || key == 0x1c0d || key == 0x5000)
		{
			AddFrame(*mx, *my, 220, 160, 420, 200, BLACK);
			return 2;
		}

		/*if(点击登陆区域)返回3表示登陆 */
		if (*mx >= 330 && *mx <= 420 && *my >= 280 && *my <= 320 && buttons)
		{
			AddFrame(*mx, *my, 220, 160, 420, 200, BLACK);
			return 3;
		}

		/*if(点击注册区域)返回4表示注册*/
		if (*mx >= 210 && *mx <= 310 && *my >= 280 && *my <= 310 && buttons)
		{
			AddFrame(*mx, *my, 220, 160, 420, 200, BLACK);
			return 4;
		}

		/*如果按了回删键*/
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

		/*将按键对应的字符存入accounts数组中*/
		ch = searchKeyValue(key);
		if (ch != '\0'&&i<10)
		{
			/*将字符显示出来*/
			setfillstyle(1, WHITE);
			bar(230 + i * 11, 162, 241 + i * 11, 190);
			temp[0] = ch;
			settextstyle(2, 0, 6);
			setcolor(BLACK);
			outtextxy(230 + i * 11, 170, temp);
			backgroundChange(*mx, *my, 230 + i * 11, 162, 241 + i * 11, 190);

			/*将字符存入数组中*/
			*p = ch;
			p++;
			*p = '\0';
			i++;
		}

    }

}

/***********************************************
Function: LogincodeInput
Description: 1、用户登陆界面的密码输入函数
2、只能是大小写字母与数字
3、能输入1到10位
Attention:鼠标位置参数必须要以指针形式传递过来！
Return:返回1在userLogin中调用LoginaccountsInput函数
返回3在userLogin中使用登陆功能
返回4在userLogin中使用注册功能
************************************************/
int LogincodeInput(char *code, int *mx, int *my)
{

	int key;     //表示键值的变量
	int i = 0;   //用于计算已输入的字符数目的变量
	char *p = code;     //输入字符的中间指针变量
	char ch;     //用于临时储存键值所对应字符的变量
	int buttons;     //鼠标的参数变量


					 /*使p指向'\0',i表示当前字符数*/
	while (*p != '\0')
	{
		i++;
		p++;
	}

	/*画框*/
	AddFrame(*mx, *my, 220, 220, 420, 260, BROWN);

	while (1)
	{
		newxy(mx, my, &buttons);

		/*重置键值并得到新键值*/
		key = 0;
		if (kbhit() != 0)
		{
			key = bioskey(0);
		}

		/*if(鼠标点击账号输入区域或按了一次上方向键)返回1表示调用LoginaccountsInput函数*/
		if (*mx >= 210 && *mx <= 410 && *my >= 170 && *my <= 190 && buttons || key == 0x4800)
		{
			AddFrame(*mx, *my, 220, 220, 420, 260, BLACK);
			return 1;
		}

		/*if(按了一次enter键或点击登陆区域)返回3表示登陆*/
		if (*mx >= 210 && *mx <= 410 && *my >= 170 && *my <= 190 && buttons || key == 0x1c0d)
		{
			AddFrame(*mx, *my, 220, 220, 420, 260, BLACK);
			return 3;
		}

		/*if(点击注册区域)返回4表示注册*/
		if (*mx >= 210 && *mx <= 410 && *my >= 170 && *my <= 190 && buttons)
		{
			AddFrame(*mx, *my, 220, 220, 420, 260, BLACK);
			return 4;
		}


		/*如果按了回删键*/
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

		/*将按键对应的字符存入code数组中*/
		ch = searchKeyValue(key);
		if (ch != '\0'&&i<10)
		{
			/*将字符存入数组中*/
			*p = ch;
			p++;
			*p = '\0';
			i++;

			/*画一个圆*/
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
Description: 画用户须知界面的函数
Attention:
Return:
*************************************/
int noticeIF()
{
	int mx, my, buttons;
	cleardevice();
	setbkcolor(CYAN);
	puthz(256, 30, "用户须知", 32, 32, WHITE);
	setfillstyle(1, WHITE);
	bar(80, 80, 580, 400);
	puthz(90, 90, "由于存储的信息有限，只列出主要留学国家及其部分学校信息", 16, 16, BROWN);
	puthz(90, 120, "大学排名只列出较有参考价值的QS机构排名,专业排名仅列出大学的自动化排名", 16, 16, BROWN);
	puthz(90, 150, "GPA算法采用华中科技大学的GPA算法", 16, 16, BROWN);
	puthz(90, 180, "学费以学年为单位,生活成本以月为单位，均采用美元制", 16, 16, BROWN);
	puthz(90, 210,"本系统的信息来源于网络，因此可能与官方有所出入，仅供参考，本系统不承担任何责任", 16, 16, BROWN);
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
	puthz(253, 422, "同意", 16, 16, WHITE);
	puthz(353, 422, "拒绝", 16, 16, WHITE);	
	mouseInit(&mx, &my, &buttons);
	while(1)
	{
		newxy(&mx, &my, &buttons);
		if(mx >= 250 && mx <= 290 && my >= 420 && my <= 440 && buttons)//同意进入搜索 
		return 2; 
		if(mx >= 350 && mx <= 390 && my >= 420 && my <= 440 && buttons)//拒绝返回LOGIN 
		return 0;
	}
} 
