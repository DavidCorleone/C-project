#include<stdio.h>
#include<graphics.h>
#include<stdlib.h>
#include<string.h>
#include<dos.h>
#include<bios.h>
#include<conio.h>
#include "nmouse.h"
#include "cartoon.h"
#include "collect.h"
#include "view.h" 
#include "hz.h"
#include "structur.h"


/**************************************************
Function: viewcollegeIntroduce
Description:学校介绍界面的后台函数
Input:  编码symbol代表englishname 
Attention:
Return:
***************************************************/
int viewcollegeIntroduce(char *symbol, const setpath *pathhead, setuser *person)
{ 
	int driver = VGA;
	int mode = VGAHI;
//	char *collegename = "C";
	char *chinesename = NULL;
	setcollege college;   //学校信息的结构体 
//	setcollect College;
	char *fileContent=NULL;
//	int flag = 0;  //判断输出英文名还是中文名 
	int judge = 0;    //判断应该调用那些函数的变量
	int buttons, mx, my;   //鼠标参数变量
//	int mark = 0;    //标记当前显示的是基础信息还是详细信息
//	int flag = 0;  //判断该学校是否已经收藏的变量,0表示未收藏，1表示已收藏
	
	mouseInit(&mx, &my, &buttons); 


	TransferToPath(symbol, pathhead, college.path); //可不用return 
	//getCollegename(symbol, college.chinesename, pathhead); //此处无需得到chinesename 

  //链表正常 
	strcat(college.path, "detailed.txt");  //修改 
	if (ReadFile(college.path, &fileContent) == 1)  //此函数功能正常 
	{
		
		WarningTips("后台数据不存在！", 260, 200, RED);
	/*	if(1)
					{
						closegraph();
						printf("Can't open %s", "helloworld");  //"FILES\\college\\mit"  test
						getchar();
						exit(1);  
					}
	*/
		//initgraph(&driver, &mode, "C:\\BORLANDC\\bgi");
		initgraph(&driver, &mode, "../BORLANDC\\bgi");
		cleardevice();
		return 1;
		
	}
	dealcollegeListFile(fileContent, &college);  //filecontent值正常 

	CollegeIF(college);
//	showname(college, &mx, &my, &flag);
	
	free(fileContent);
//	fileContent = NULL;
	//判断是否收藏 
	//strcat()
	if(ifCollect(&(person->college), college.chinesename) == 0)
	{
/*		if(1)
	{
		closegraph();
		printf("Can't open %d", ifCollect(&(person->college), college.chinesename));  //"FILES\\college\\mit"  test
		getchar();
		getchar();
		exit(1);  
	}*/
		setfillstyle(1, WHITE); 
		bar(484, 289, 516, 321);
		setfillstyle(1,DARKGRAY);
		setcolor(DARKGRAY);	
		pieslice(516, 310, 0, 360, 36); 
		puthz(488, 305, "未收藏", 16, 16, WHITE);
	} 
	else if(ifCollect(&(person->college), college.chinesename) == 1)
	{
		setfillstyle(1, WHITE);   
		bar(484, 289, 516, 321);
		setfillstyle(1,DARKGRAY);
		setcolor(DARKGRAY);
		pieslice(516, 310, 0, 360, 36); 
		puthz(488, 305, "已收藏", 16, 16, WHITE);
	}

	college.path[0] = '\0';  //初始化 
	symbol = NULL;
	while (1)
	{
		newxy(&mx, &my, &buttons);

		/*鼠标点击第一个椭圆区域，表示收藏功能*/
		//若未收藏，则收藏，若已收藏，则删除收藏 
		if (mx >= 478 && mx <= 550 && my >= 275 && my <= 350 && buttons)
		{
			if(ifCollect(&(person->college), college.chinesename) == 0)	
			{
				judge = 1;
			} 
			else
			{
				judge = 11;
			}
		} 
			
		/*鼠标点击第二个椭圆区域, 表示国家信息*/
		if (mx >= 10 && mx <= 80 && my >= 159 && my <= 230&& buttons)
		{
		
			judge = 2;
			
		}
			
		/*鼠标点击第三个椭圆区域，表示学费信息*/
		if (mx >= 311 && mx <= 377 && my >= 16 && my <= 80&& buttons)
		{
		
			judge = 3;
			
		}
			
		/*鼠标点击第四个椭圆区域，表示排名信息*/
		if (mx >= 102 && mx <= 169 && my >= 290 && my <= 358&& buttons)
		{
		
			judge = 4;
			
		}
		/*鼠标点击第五个椭圆区域，表示专业排名信息*/
		if (mx >= 182 && mx <= 257 && my >= 401 && my <= 470&& buttons)
		{
		
			judge = 5;
			
		}
		/*鼠标点击第六个椭圆区域，表示生活成本*/
		if (mx >= 368 && mx <= 441 && my >= 368 && my <= 439&& buttons)
		{
		
			judge = 6;
			
		}
		/*鼠标点击第七个椭圆区域，表示GPA*/
		if (mx >= 141 && mx <= 219 && my >= 53 && my <= 130&& buttons)
		{
		
			judge = 7;
			
		}
		/*鼠标点击第八个椭圆区域，表示详细信息（包括生活信息和学习信息）*/
		if (mx >= 506 && mx <= 585 && my >= 33 && my <= 110&& buttons)
		{
			judge = 8;	
		}
		
		/*如果鼠标点击返回区域*/
		if (mx >= 0 && mx <= 30 && my >= 0 && my <= 30 && buttons)
			judge = 9;

		/*鼠标点击个人中心区域*/
		if (mx >= 570 && mx <= 640 && my >= 0 && my <= 30 && buttons)
			judge = 10;
		 
	
		switch (judge)
		{
			
		/*收藏该景点*/
		case 1:
			setfillstyle(1, WHITE);
			collect(college.chinesename, college.englishname, person);  //如何清除收藏？ 
			bar(484, 289, 516, 321);
			setfillstyle(1,DARKGRAY);
			setcolor(DARKGRAY);
			pieslice(516, 310, 0, 360, 36); 
			puthz(488, 305, "已收藏", 16, 16, WHITE);
			judge = 0; 
			//backgroundChange(mx, my, 484, 289, 516, 321);
			break;
	
		/*显示国家信息*/
		case 2:
			setfillstyle(1, WHITE);
			bar(273, 220, 370, 250);
			puthz(304, 232, college.country, 16, 16, LIGHTGRAY);//先清空原来的框，然后输出college.country 
			judge = 0;
			break;

		/*显示学费信息*/
		case 3:
			setfillstyle(1, WHITE);
			bar(273, 220, 370, 250);
			puthz(300, 232, college.tuition, 16, 16, CYAN);	
			judge = 0;
			break;

			
		/*显示排名信息*/	
		case 4: 
			setfillstyle(1, WHITE);
			bar(273, 220, 370, 250);
			puthz(310, 232, college.globalrank, 16, 16, LIGHTRED);	
			judge = 0;
			break;

		/*表示学科信息*/
		case 5: 
			setfillstyle(1, WHITE);
			bar(273, 220, 370, 250);
			puthz(310, 232, college.disciplinerank, 16, 16, YELLOW);	
			judge = 0;
			break;

		/*表示生活成本*/
		case 6:
			setfillstyle(1, WHITE);
			bar(273, 220, 370, 250);
			puthz(300, 232, college.livingcost, 16, 16, LIGHTGREEN);	
			judge = 0;
			break;

		/*表示GPA*/
		case 7:
			setfillstyle(1, WHITE);
			bar(273, 220, 370, 250);
			puthz(300, 232, college.gpa, 16, 16, BROWN);	
			judge = 0;
			break;

		/*表示详细信息*/
		case 8:
			
			judge = showmessage(college);
			freecollege(&college);
			
			break;

		/*返回*/ 
		case 9:
			freecollege(&college);
			return 1;  //返回至viewcollegeintroduce界面 
	
		/*个人中心*/
		case 10:	
			freecollege(&college);
			return 5;
		
		/*取消收藏*/ 
		case 11:
			deleteCollect(college.chinesename, &(person->college), person);
			setfillstyle(1, WHITE); 
			bar(484, 289, 516, 321);
			setfillstyle(1,DARKGRAY);
			setcolor(DARKGRAY);	
			pieslice(516, 310, 0, 360, 36); 
			puthz(488, 305, "未收藏", 16, 16, WHITE);
			judge = 0;
			freecollege(&college);
			break;	
	
		}
	} 

}

/***********************************
Function: showname
Description:显示学校名称的函数，flag为奇数输出英文名，偶数时中文 
Attention:
Return:无
***********************************/
/*
void showname(setcollege college, int *mx, int *my, int *flag)
{
	int buttons;
	while (1)
	{
		//newxy(&mx, &my, &buttons);  

		//鼠标点击显示学校名称的圆 
		if (mx >= 270 && mx <= 190 && my >= 370 && my <= 290 && buttons)
		{
			if(*flag%2==0)
			{
				puthz(272, 232, college.chinesename, 16, 16, RED);
			}
			else
			{
				puthz(272, 232, college.englishname, 16, 16, RED);
				
			/*	if(1)
				{
					closegraph();
					printf("Can't open %s", college.englishname);  //"FILES\\college\\mit"  test
					getchar();
					exit(1);  
				}
			*/
/*			
		} 
			*flag++;	
		}
		else if(buttons)
		{
			return 0;
		}
		
 } 
} 
*/

/***********************************
Function: showmessage
Description:对显示进行选择的函数 
Attention:无
Return:无
***********************************/
int showmessage(setcollege college)
{ 
	int buttons=0;
	int mx, my;
	showmessageIF();
	mouseInit(&mx, &my, &buttons); 
	while (1)
	{
		newxy(&mx, &my, &buttons);

		/*显示introduce*/
		if (mx >= 31 && mx <= 160 && my >=31  && my <= 159 && buttons)
		{
			setfillstyle(1, WHITE); 
			bar(170, 30, 640, 480);
			puthz(180, 100, college.introduce, 16, 16, BROWN); 
		}
		/*留学建议*/ 
		if (mx >= 0 && mx <= 160 && my >= 160 && my <= 319 && buttons)
		{
			setfillstyle(1, WHITE); 
			bar(170, 30, 640, 480);
			puthz(180, 100, college.livingmessage, 16, 16, BROWN);
		}
		/*实用信息*/ 
		if (mx >= 0 && mx <= 160 && my >= 320 && my <= 480 && buttons)
		{
			setfillstyle(1, WHITE); 
			bar(170, 30, 640, 480);
 			puthz(180, 100, college.studyingmessage, 16, 16, BROWN); 
		}
		/*点击返回按钮*/
		if (mx >= 0 && mx <= 30 && my >= 0 && my <= 30 && buttons)
		{
			return 9;  //此处可以考虑不用堆栈 
		}
		/*点击个人中心*/
		if (mx >= 570 && mx <= 640 && my >= 0 && my <= 30 && buttons)
		{
			return 10;		
		} 
		 
	}	
}

/***********************************
Function: showmessage
Description:对输出信息选择的画图函数 
Attention:无
Return:无
***********************************/
void showmessageIF()
{
	cleardevice();
	setfillstyle(1, LIGHTGRAY);	//返回按钮
	bar(0, 0, 30, 30);  
	setcolor(WHITE);
	line(5, 15, 25, 15);
	line(5, 15, 10, 20);
	line(5, 15, 10, 10);
	setbkcolor(WHITE);	
	setlinestyle(0, 0, 3);
	setcolor(BLUE);
	line(160, 0, 160, 480);
	puthz(20, 70,"详细介绍", 32, 32, BLUE);
	line(0, 160, 160, 160);
	puthz(20, 230,"生活信息", 32, 32, BLUE);
	puthz(20, 290,"环境交通生活介绍", 16, 16, CYAN); 
	line(0, 320, 160, 320);	
	puthz(20, 390,"学习信息", 32, 32, BLUE);
	puthz(20, 450,"面试准备留学建议", 16, 16, CYAN); 
	setfillstyle(1, LIGHTGRAY);
	bar(570, 0, 640, 30);
	puthz(572, 6, "个人中心",16 ,16 ,WHITE);	
}

/***********************************
Function: 
Description:函数
Attention:无
Return:无
***********************************/
void CollegeIF(setcollege college)
{
	cleardevice();
	setbkcolor(WHITE);
	setcolor(BLUE);
	setlinestyle(0, 0, 3);
	setfillstyle(1,BLUE);
	circle(320, 240, 58);
	puthz(275, 225, college.chinesename, 16, 16, RED);  //测试 

	setfillstyle(1, LIGHTGRAY);
	bar(0, 0, 30, 30);  //返回按钮
	setcolor(WHITE);
	line(5, 15, 25, 15);
	line(5, 15, 10, 20);
	line(5, 15, 10, 10);
	
	bar(570, 0, 640, 30);
	puthz(572, 6, "个人中心",16 ,16 ,WHITE);
	
	setlinestyle(0, 0, 1);
	
	setfillstyle(1,CYAN);
	setcolor(CYAN);
	pieslice(345, 46, 0, 360, 33);
	line(334, 182, 342, 78);
	puthz(329, 41, "学费", 16, 16, WHITE);
	
	setfillstyle(1,BROWN);
    setcolor(BROWN);
	pieslice(180, 88, 0, 360, 38);
	line(276, 193, 206, 115);
	puthz(148, 83, "平均绩点", 16, 16, WHITE);
	
	setfillstyle(1,LIGHTGRAY);
	setcolor(LIGHTGRAY);
	pieslice(47, 192, 0, 360, 36);
	line(260, 225, 85, 198);
	puthz(31, 187, "国家", 16, 16, WHITE);
	
	setfillstyle(1,LIGHTRED);
	setcolor(LIGHTRED);
	pieslice(135, 323, 0, 360, 35);
	line(259, 266, 174, 304);
	puthz(119, 318, "排名", 16, 16, WHITE);
	
	setfillstyle(1,YELLOW);
	setcolor(YELLOW);
	pieslice(220, 437, 0, 360, 38);
	line(293, 297, 238, 401);
	puthz(188, 432, "专业排名", 16, 16, WHITE);
	
	setfillstyle(1,LIGHTGREEN);
	setcolor(LIGHTGREEN);
	pieslice(405, 402, 0, 360, 37);
	line(356, 288, 389, 364);
	puthz(373, 397, "生活成本", 16, 16, WHITE);
	
	setfillstyle(1,DARKGRAY);
	setcolor(DARKGRAY);
	pieslice(516, 310, 0, 360, 36);
	line(383, 251, 474, 297);  //收藏按钮 

	setfillstyle(1,LIGHTCYAN);
	setcolor(LIGHTCYAN);
	pieslice(547, 69, 0, 360, 40);
	line(364, 200, 506, 95);
	puthz(515, 64, "详细介绍", 16, 16, WHITE);
}
