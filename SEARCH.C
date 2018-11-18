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
#include "structur.h"
#include "search.h"
#include "dealfile.h"
void sortglobalrank(setpath *head);
int showFilter(char *symbol, int *mx, int *my);
void sortdisciplinerank(setpath *head);
int  showPossible(char *abbreviation, int *mx, int *my, setpath *pathhead, char *symbol); 
/********************************************
Function: search
Description:主菜单界面下的搜索界面的后台函数
Attention:
Return:
********************************************/
int search(const setpath *pathlisthead, char *symbol)
{

	int judge = 0;    //判断应该调哪些函数的变量
	int temp;    //用于吸收键盘缓冲区的变量
	int buttons, mx, my;   //鼠标参数变量
	char abbreviation[50]= {'\0'};    //学校简写,在搜索功能内。此处只可以用数组 
 	buttons = 0; 
	 /*必要的初始化过程*/
	mouseInit(&mx, &my, &buttons);
	while (1)
	{
	/*		if(1)
	{
		closegraph();
		for(;pathlisthead->next!=NULL; )
		{
			printf("Can't open %s\n", pathlisthead->next->path);
			pathlisthead = pathlisthead->next;
		}
		  //"FILES\\college\\mit"  test
		getchar();
		exit(1);  
	}*/
		newxy(&mx, &my, &buttons);

		/*吸收键盘缓冲区域数据*/
		if (kbhit() != 0)
		{
			temp = bioskey(0);
		}
		/*由于下面会自动赋值judge=3，因此在这里先判断*/ 
		if(judge == 5)
		{
			return 6;    //showdisciplinerank
		} 
		if(judge == 6)
		{
			return 8;  //Show_globalrank
		}
		if (mx >= 125 && mx <= 425 && my >= 410 && my <= 450 && buttons)judge = 1;/*鼠标点击搜索框区域*/
		if (mx >= 425 && mx <= 475 && my >= 410 && my <= 450 && buttons)judge = 2;/*鼠标点击搜索按钮区域*/
		if (mx >= 81 && mx <= 560 && my >= 60 && my <= 110)judge = 3;/*鼠标移到筛选框区域*/
	
		if (mx >=561 && mx <=640 && my >=0 && my <=40 && buttons)return 5; /*鼠标点击个人中心区域*/ 
		if (mx>= 0 && mx<= 80 && my >=0&& my<= 40 && buttons)return 7; //鼠标点击quit区域 
		if(mx>= 460 && mx<= 559 && my >=0&& my<= 40 && buttons)return 2;//鼠标点击高级筛选 
		switch (judge)
		{
			/*点击了搜索框，调用首拼输入函数*/
		case 1:
			judge=searchInput(abbreviation,&mx,&my);
			break;

			/*点击了搜索按钮*/
		case 2:
			judge = showPossible(abbreviation, &mx, &my, pathlisthead, symbol);   //根据possible地址弹出对应的框
			break;

			/*弹出相应的信息框*/
		case 3:
			judge = showFilter(symbol, &mx, &my);
			break;
		
		case 4: 
			return 4;
		case 20:
			return 3;//搜索框返回judge = 5进入viewcollege 
	
		case 15:
			return 1;//搜索框点击空白处重画search 
			}	
		
	}
}

/*********************************************
Function: showPossible
Description: 显示搜索结果的函数
Attention:这里面的坐标都没有改 
Return:返回调用viewcollegeintroduce函数，因此需要传入symbol 
*********************************************/
int  showPossible(char *abbreviation, int *mx, int *my, setpath *pathhead, char *symbol)
{
//	void *buffer = NULL;    //指向存储背景的内存的指针
//	unsigned int size;    //背景在内存中所占的大小
	int buttons = 0;    //鼠标的参数变量
	char *collegepath; //为了符合TransferToPath的形式，没什么用 
	char *chinesename;  //存储转换后的中文名，用于打印 
//	const char *temp = abbreviation;  //暂存abbreviation 
	if (TransferToPath(abbreviation, pathhead, collegepath)==0)
	{
		/*截取背景并保存*/
	/*	size = imagesize(240, 58, 480, 83);
		if ((buffer = malloc(size)) == NULL)
		{
			closegraph();
			printf("Overflow!");
			getchar();
			exit(1);
		}
		getimage(240, 58, 480, 83, buffer);*/
//125, 410, 425, 450
		/*提示找不到相关学校*/
	//	setfillstyle(1, LIGHTGRAY);           
	//	bar(240, 58, 480, 83);
		puthz(125, 380, "找不到相关学校！", 16, 16, RED);
		return 15;
	}

	/*截取背景并保存*/
	/*size = imagesize(240, 58, 480, 83);
	if ((buffer = malloc(size)) == NULL)
	{
		closegraph();
		printf("Overflow!");
		getchar();
		exit(1);
	}
	getimage(240, 58, 480, 83, buffer);*/

	/*打印可能的学校名称*/
//	setfillstyle(1, LIGHTGRAY);
//	bar(240, 58, 480, 83);

	strcpy(symbol, abbreviation);

	getCollegename(abbreviation, chinesename, pathhead);
/*		if(1)
	{
		closegraph();
		printf("Can't open %s", abbreviation);  //"FILES\\college\\mit"  test
		getchar();
		exit(1);  
	}
*/
	puthz(128, 380,chinesename, 16, 16, BLUE);
	abbreviation = NULL;
	while (1)
	{
		newxy(mx, my, &buttons);
		delay(10);
		/*如果鼠标移到选项区域，使选项区域边框变红*/
		if(*mx >= 125 && *mx <= 250 && *my >= 375  && *my <= 405)
		{
			AddFrame(*mx, *my, 125, 375, 250, 405, RED);

			/*如果按下按键，改变symbol内容，返回4表示在search函数中调用功能4*/
			if (buttons)
			{	
			//	strcpy(symbol, abbreviation);
			//	free(buffer);  //释放buffer指向的内存空间
				return 20;  //在主函数里调用viewcollegeintroduce函数 
			}
		}
		else AddFrame(*mx, *my, 125, 375, 250, 405, LIGHTGRAY);



		/*如果鼠标在其他无功能的区域按下，返回0，退出当前功能*/
		if (buttons && (*mx < 125 || *mx > 550 || *my < 375 || *my > 450))
		{
		/*	putimage(240, 58, buffer, COPY_PUT);
			free(buffer);*/
			setfillstyle(1, WHITE);
			bar(125, 375, 250, 405);
		//	return 15;
		}
}
}


/****************************
Function: searchIF
Description:画主界面的函数
Attention:无
Return:无
*****************************/
void searchIF()
{
	/* 
	int graphdriver=VGA;
	int graphmode=2;
	initgraph(&graphdriver, &graphmode, "c://borlandc//bgi");
	*/
	cleardevice();
	setbkcolor(WHITE);  //先画退出与个人中心 
	setcolor(BLACK);
	setlinestyle(0, 0, 2); 
	setfillstyle(1, BLUE);
	bar(0, 0, 80, 40);
	bar(560, 0, 639, 40);
	rectangle(0, 0, 80, 40);
	rectangle(560, 0, 639, 40);
	setfillstyle(1, BROWN); 
	bar(460, 0, 559, 40);
	puthz(470, 10,"高级筛选", 16, 16, WHITE);
	
	setcolor(LIGHTGRAY);  //画筛选界面
	setlinestyle(0, 0, 1);
	setfillstyle(1, WHITE);
	bar(81, 60, 560, 110);
	rectangle(81, 60, 560, 110);
	line(160, 60, 160, 110);
	line(240, 60, 240, 110);
	line(320, 60, 320, 110);
	line(400, 60, 400, 110);
	line(480, 60, 480, 110);
	
	setcolor(RED);  //画搜索界面 
	setlinestyle(0, 0, 2);
	setfillstyle(1, WHITE);
	bar(125, 410, 425, 450);
	rectangle(125, 410, 475, 450);
	setfillstyle(1, BROWN);
	bar(425, 410, 475, 450);
	
	puthz(435, 420, "搜索", 16, 16, BLACK);   //接下来在频幕上显示字符 
	puthz(570, 10, "个人中心", 16, 16, BLACK);
	puthz(20, 10, "quit", 16, 16, BLACK);
	puthz(104, 77, "国家", 16, 16, RED);
	puthz(168, 77, "世界排名", 16, 16, RED);  //QS排名 
	puthz(248, 77, "自动化排名", 16, 16, RED);  //自动化专业排名 
	puthz(336, 77, "GPA", 16, 16, RED);
	puthz(424, 77, "学费", 16, 16, RED);
	puthz(488, 77, "生活成本", 16, 16, RED); 
}




/******************************
Function: showglobalrank 
Description: 显示区域框的函数
Attention:改变symbol的值，将学校的英文名称赋给symbol 
Return:点击选项返回4,跳转至main函数调用collegeintroduce函数 
*******************************/
int showglobalrank(char *symbol,const setpath *pathhead)
{
	char Symbol[50][50];  //用于存储得到的symbol值 
	int i;
	int buttons = 0;
	int mx, my;
	setpath *current = pathhead;  //根据链表由某一项元素进行排序的算法
//	Symbol[0] = NULL;
	
	cleardevice();
	setbkcolor(WHITE);
	//返回按钮
	setfillstyle(1, LIGHTGRAY);
	bar(0, 0, 30, 30);  
	setcolor(WHITE);
	line(5, 15, 25, 15);
	line(5, 15, 10, 20);
	line(5, 15, 10, 10);
	setcolor(BLUE);
	setfillstyle(1, BLUE);
	//画top的字样 
	bar(28, 98, 90, 117);
	bar(49, 117, 69, 173);
	pieslice(140, 135, 0, 360, 37);
	setcolor(WHITE);
	setfillstyle(1, WHITE);
	pieslice(140, 135, 0, 360, 20);
	setcolor(BLUE);
	setfillstyle(1, BLUE);
	bar(196, 94, 211, 173);
	setcolor(BLUE);
	setfillstyle(1, BLUE);
	pieslice(211, 123, 270, 360, 29);
	setcolor(WHITE);
	setfillstyle(1, WHITE);
	pieslice(211, 123, 270, 360, 14);
	setcolor(BLUE);
	setfillstyle(1, BLUE);
	pieslice(211, 123, 0, 90, 29);
	setcolor(WHITE);
	setfillstyle(1, WHITE);
	pieslice(211, 123, 0, 90, 14);
	//画讲台 
	setfillstyle(1, CYAN);
	bar(48, 309, 212, 344);
	bar(48, 295, 96, 309);
	bar(96, 234, 162, 309);
	bar(162, 281, 212, 309);
	settextstyle(0, 0, 3);
	setcolor(CYAN);
	mouseInit(&mx, &my, &buttons);  
	sortglobalrank(current); 
	current = current->next;
	while(1)
	{
		newxy(&mx, &my, &buttons);	
	
	for(i=0; current!=NULL; i++)  //用坐标循环输出,也可以直接puthz 
	{
		outtextxy(346, 60+35*i, current->filter_globalrank);
		puthz(390, 60+35*i, current->chinesename, 32, 32, BROWN);
		strcpy(Symbol[i], current->englishname); 
		current = current->next;
	}
//	current = pathhead;
	
/*	if(1)
	{
		closegraph();
		for(i=0;i<8;i++ )
		{
			printf("global");
			printf("Can't open %s\n", Symbol[i]);
			//current = current->next;
		}
		  //"FILES\\college\\mit"  test
		getchar();
		exit(1);  
	}  Symbol[i]没问题 
*/	
	if(mx >= 390 && mx <= 550 && my >= 60  && my <= 94&&buttons)  //如果鼠标点击这个学校名称，就改变symbol的值并返回至主函数  
	{
		strcpy(symbol, Symbol[0]);  //第一个学校 
		memset(Symbol,0,sizeof(Symbol));
		return 3;
	}  

	
	if(mx >= 390&& mx <= 550 && my >= 96  && my <= 130&&buttons)  //如果鼠标点击这个学校名称，就改变symbol的值并返回至主函数  
	{
			
		strcpy(symbol, Symbol[1]);
		memset(Symbol,0,sizeof(Symbol));
		return 3;
	} 

	if(mx >= 390 && mx <= 550 && my >= 132  && my <= 136&&buttons)  //如果鼠标点击这个学校名称，就改变symbol的值并返回至主函数  
	{
		
		strcpy(symbol, Symbol[2]);
			memset(Symbol,0,sizeof(Symbol));
		return 3;
	} 
	
	if(mx >= 390 && mx <= 550 && my >= 138  && my <= 172&&buttons)  //如果鼠标点击这个学校名称，就改变symbol的值并返回至主函数  
	{
		
		strcpy(symbol, Symbol[3]);
			memset(Symbol,0,sizeof(Symbol));
		return 3;
	} 
	
	if(mx >= 390 && mx <= 550 && my >= 174  && my <= 208&&buttons)  //如果鼠标点击这个学校名称，就改变symbol的值并返回至主函数  
	{
		
		strcpy(symbol, Symbol[4]);
			memset(Symbol,0,sizeof(Symbol));
		return 3;
	} 
	
	if(mx >= 390 && mx <= 550 && my >= 210  && my <= 244&&buttons)  //如果鼠标点击这个学校名称，就改变symbol的值并返回至主函数  
	{
		
		strcpy(symbol, Symbol[5]);
			memset(Symbol,0,sizeof(Symbol));
		return 3;
	} 
	 
	 if(mx >= 390 && mx <= 550 && my >= 246  && my <= 280&&buttons)  //如果鼠标点击这个学校名称，就改变symbol的值并返回至主函数  
	{
		
		strcpy(symbol, Symbol[6]);
			memset(Symbol,0,sizeof(Symbol));
		return 3;
	} 
	
	if(mx >= 390 && mx <= 550 && my >= 282  && my <= 316&&buttons)  //如果鼠标点击这个学校名称，就改变symbol的值并返回至主函数  
	{
		
		strcpy(symbol, Symbol[7]);
			memset(Symbol,0,sizeof(Symbol));
		return 3;
	} 
	
	if(mx >= 390 && mx <= 550 && my >= 318  && my <= 354&&buttons)  //如果鼠标点击这个学校名称，就改变symbol的值并返回至主函数  
	{
		
		strcpy(symbol, Symbol[8]);
		memset(Symbol,0,sizeof(Symbol));
		return 3;
	} 
	if (mx >= 0 && mx <= 30 && my >= 0 && my <= 30 && buttons)
	{
		memset(Symbol,0,sizeof(Symbol));
		return 1; 
	
	}	
		
	}
	
	
	
}


/******************************
Function: sortglobalrank   
Description: 显示区域框的函数
Attention:改变symbol的值 
Return:点击选项返回
*******************************/
void sortglobalrank(setpath *head)   //对链表按照学校排名进行排序 
{
	setpath *p, *prep, *temp, *tail;

	tail = NULL;

// 算法的核心部分
	while( head->next != tail ){
    prep = head;
    p = head->next;
    while( p->next != tail )
	{
	    if( (p->filter_globalrank[0]) > (p->next->filter_globalrank[0] ))
		{
            temp = p->next;
            prep->next = p->next;
            p->next = p->next->next;
            prep->next->next = p;
            p = temp;
            }
            // 节点后移
            p = p->next;
            prep = prep->next;
        }
        tail = p;
    }// 第一个while
}

/******************************
Function: showdisciplinerank
Description: 显示区域框的函数
Attention:改变symbol的值，将学校的英文名称赋给symbol 
Return:点击选项返回4,跳转至main函数调用collegeintroduce函数 
*******************************/
int showdisciplinerank(char *symbol, const setpath *pathhead)
{
	
	int i;
	char Symbol[50][50];  //用于存储得到的symbol值 
	int buttons, mx, my;
	setpath *current = pathhead;  //根据链表由某一项元素进行排序的算法 
//	Symbol[0] = NULL;
	/*必要的初始化过程*/
	mouseInit(&mx, &my, &buttons); 
//	puthz(200, 200, p, 16, 16, RED); //test
	cleardevice();
	setbkcolor(WHITE);
	//返回按钮
	setfillstyle(1, LIGHTGRAY);
	bar(0, 0, 30, 30);  
	setcolor(WHITE);
	line(5, 15, 25, 15);
	line(5, 15, 10, 20);
	line(5, 15, 10, 10);
	setcolor(BLUE);
	setfillstyle(1, BLUE);
	//画top的字样 
	bar(28, 98, 90, 117);
	bar(49, 117, 69, 173);
	pieslice(140, 135, 0, 360, 37);
	setcolor(WHITE);
	setfillstyle(1, WHITE);
	pieslice(140, 135, 0, 360, 20);
	setcolor(BLUE);
	setfillstyle(1, BLUE);
	bar(196, 94, 211, 173);
	setcolor(BLUE);
	setfillstyle(1, BLUE);
	pieslice(211, 123, 270, 360, 29);
	setcolor(WHITE);
	setfillstyle(1, WHITE);
	pieslice(211, 123, 270, 360, 14);
	setcolor(BLUE);
	setfillstyle(1, BLUE);
	pieslice(211, 123, 0, 90, 29);
	setcolor(WHITE);
	setfillstyle(1, WHITE);
	pieslice(211, 123, 0, 90, 14);
	//画讲台 
	setfillstyle(1, CYAN);
	bar(48, 309, 212, 344);
	bar(48, 295, 96, 309);
	bar(96, 234, 162, 309);
	bar(162, 281, 212, 309);
	settextstyle(0, 0, 3);
	setcolor(CYAN);
//	sortdisciplinerank(current); 
	current=current->next;
	while(1)
	{
		newxy(&mx, &my, &buttons);	
	
	for(i=0; current!=NULL ; i++)  //用坐标循环输出,也可以直接puthz 
	{


		outtextxy(346, 60+35*i, current->filter_disciplinerank);
		puthz(390, 60+35*i, current->chinesename, 32, 32, BROWN);
		strcpy(Symbol[i], current->englishname);   //由于symbol【0】==NULL; 
		current = current->next;
	}
	
	if(mx >= 390 && mx <= 550 && my >= 60  && my <= 94&&buttons)  //如果鼠标点击这个学校名称，就改变symbol的值并返回至主函数  
	{
		strcpy(symbol, Symbol[0]);
			memset(Symbol,0,sizeof(Symbol));
		//symbol = Symbol[0];
		return 3;
	}  

	
	if(mx >= 390 && mx <= 550 && my >= 96  && my <= 130&&buttons)  //如果鼠标点击这个学校名称，就改变symbol的值并返回至主函数  
	{
			
		strcpy(symbol, Symbol[1]);
			memset(Symbol,0,sizeof(Symbol));
			//symbol = Symbol[1];
			return 3;
	} 

	if(mx >= 390 && mx <= 550 && my >= 132  && my <= 136&&buttons)  //如果鼠标点击这个学校名称，就改变symbol的值并返回至主函数  
	{
		strcpy(symbol, Symbol[2]);
			memset(Symbol,0,sizeof(Symbol));
			//symbol = Symbol[2];
			return 3;
	} 
	
	if(mx >= 390 && mx <= 550 && my >= 138  && my <= 172&&buttons)  //如果鼠标点击这个学校名称，就改变symbol的值并返回至主函数  
	{
		
	strcpy(symbol, Symbol[3]);
		memset(Symbol,0,sizeof(Symbol));
			//symbol = Symbol[3];
			return 3;
	} 
	
	if(mx >= 390 && mx <= 550 && my >= 174  && my <= 208&&buttons)  //如果鼠标点击这个学校名称，就改变symbol的值并返回至主函数  
	{
		strcpy(symbol, Symbol[4]);
			memset(Symbol,0,sizeof(Symbol));
			//symbol = Symbol[4];
			return 3;
	} 
	
	if(mx >= 390 && mx <= 550 && my >= 210  && my <= 244&&buttons)  //如果鼠标点击这个学校名称，就改变symbol的值并返回至主函数  
	{
		
		strcpy(symbol, Symbol[5]);
			memset(Symbol,0,sizeof(Symbol));
			//symbol = Symbol[5];
			return 3;
	} 
	 
	 if(mx >= 390 && mx <= 550 && my >= 246  && my <= 280&&buttons)  //如果鼠标点击这个学校名称，就改变symbol的值并返回至主函数  
	{
		
		strcpy(symbol, Symbol[6]);
			memset(Symbol,0,sizeof(Symbol));
			//symbol = Symbol[6];
			return 3;
	} 
	
	if(mx >= 390 && mx <= 550 && my >= 282  && my <= 316&&buttons)  //如果鼠标点击这个学校名称，就改变symbol的值并返回至主函数  
	{
		
	strcpy(symbol, Symbol[7]);
		memset(Symbol,0,sizeof(Symbol));

			//symbol = Symbol[7];
			return 3;
	} 
	
	if(mx >= 390 && mx <= 550 && my >= 318  && my <= 354&&buttons)  //如果鼠标点击这个学校名称，就改变symbol的值并返回至主函数  
	{
		
		strcpy(symbol, Symbol[8]);
			memset(Symbol,0,sizeof(Symbol));
		return 3;
	} 
	if (mx >= 0 && mx <= 30 && my >= 0 && my <= 30 && buttons)
	{
		memset(Symbol,0,sizeof(Symbol));  //清空数组内容 
		return 1;  //返回search界面	
		
	}
}
	
	
}

/******************************
Function: sortdisciplinerank
Description: 显示区域框的函数
Attention: 
Return:点击选项返回
*******************************/
void sortdisciplinerank(setpath *head)
{
	setpath *f, *p, *x, *y;
	f = NULL;
	//判断是否只有一个元素或者没有元素
	if(head->next == NULL || head->next->next == NULL)
	{
		return 0;
	}
	while(f != head->next->next)
	{
		//外层是N - 1次循环,升序
		for(p = head; p->next->next != f; p = p->next)
		{
			if(p->next->filter_disciplinerank > p->next->next->filter_disciplinerank)
			{
				x = p->next;
				y = p->next->next;
				p->next = y;
				x->next = y -> next;
				y->next = x;
			}
		}
		f = p->next;
	}
}


/******************************
Function: showFilter
Description: 显示区域框的函数
Attention:点击不同筛选条件中的不同选项，返回不同的symbol 
Return:点击选项返回4
*******************************/
int showFilter(char *symbol, int *mx, int *my)
{
	int buttons = 0;    //鼠标的参数变量
	int judge = 0;
	setfillstyle(1, WHITE);
	setcolor(RED);
	while (1)
	{
		newxy(mx, my, &buttons);

		/*鼠标在第一个框上方*/
		if (judge!=1&&*mx >= 81 && *mx <= 160 && *my >= 60 && *my <= 110)
		{
			
			bar(81, 110, 560, 370);
			rectangle(81, 110, 560, 370);
			puthz(100, 150, "美国", 16, 16, RED);
			puthz(180, 150, "英国", 16, 16, RED);
			puthz(260, 150, "德国", 16, 16, RED);
			puthz(340, 150, "日本", 16, 16, RED);
			//puthz(420, 150, "新加坡", 16, 16, RED);
			//puthz(500, 150, "澳大利亚", 16, 16, RED);
			judge = 1;
		}
		/*鼠标在第二个框上方*/
		if (judge != 2 && *mx >= 160 && *mx <= 240 && *my >= 60 && *my <= 110 && buttons)
		{
			judge = 2;
			//return 5;   
		}

		/*鼠标在第三个框上方*/
		if (judge != 3 && *mx >= 240 && *mx <= 320 && *my >= 60 && *my <= 110 &&buttons)
		{
			judge = 3;
		}
		
		/*鼠标在第四个框上方*/
		if (judge != 4 && *mx >= 320 && *mx <= 400 && *my >= 60 && *my <= 110)
		{
			
			bar(81, 110, 560, 370);
			rectangle(81, 110, 560, 370);
			puthz(100, 150, "三点零及以下", 16, 16, RED);
			puthz(220, 150, "三点零到三点五", 16, 16, RED);
			puthz(356, 150, "三点五到四点零", 16, 16, RED);
			judge = 4;
		}
	
		/*鼠标在第五个框上方*/
		if (judge != 5 && *mx >= 400 && *mx <= 480 && *my >= 60 && *my <= 110)
		{
			bar(81, 110, 560, 370);
			rectangle(81, 110, 560, 370);
			puthz(100, 150, "1万美元以下", 16, 16, RED);
			puthz(230, 150, "1万到2万美元", 16, 16, RED);
			puthz(366, 150, "2万美元以上", 16, 16, RED);
			judge = 5;
		}
	
		/*鼠标在第六个框上方*/ 
		if (judge != 6 && *mx >= 480 && *mx <= 560 && *my >= 60 && *my <= 110)
		{
			bar(81, 110, 560, 370);
			rectangle(81, 110, 560, 370);
			puthz(100, 150, "1000美元", 16, 16, RED);
			puthz(220, 150, "1000到1500美元", 16, 16, RED);
			puthz(420, 150, "1500美元以上", 16, 16, RED);
			judge = 6;
		} 
		//当鼠标不在筛选框时
		if (*mx < 81 || *mx > 560 || *my < 60 || *my > 370)
		{
			setfillstyle(1, WHITE);
			bar(81, 110, 560, 370);
			rectangle(81, 110, 560, 370);
			puthz(193,192,"尊敬的普通用户，", 32, 32, RED); 
			puthz(118, 306, "欢迎来到出国留学咨询系统！", 32, 32, RED);
			return 0;
		}
		
 		/*显示第一个方框时*/ 
		 //由search界面的国家向college界面跳转，不同筛选方式对应的函数不同  
		if (judge == 1)
		{
			if (*mx >= 90 && *mx <= 140 && *my >= 140 && *my <= 160 && buttons)
			{
				strcpy(symbol, "A01"); //美国 
				return 4;

			}
			if (*mx >= 170 && *mx <= 220 && *my >= 140 && *my <= 160 && buttons)
			{
				strcpy(symbol, "A02"); //英国 
				return 4;
			}
			if (*mx >= 250 && *mx <= 280 && *my >= 140 && *my <= 160 && buttons)
			{
				strcpy(symbol, "A03"); //德国
				return 4;
			}
				if (*mx >= 330 && *mx <= 360 && *my >= 140 && *my <= 160 && buttons)
			{
				strcpy(symbol, "A04"); //日本
				return 4;
			}
		}
		
		if (judge ==2)
		{
			return 6;  //Show_globalrank
			 
		}
			
		if (judge ==3)
		{
			return 5;  
			
		}
	
		if (judge == 4)
		{
			if (*mx >= 90 && *mx <= 180 && *my >= 140 && *my <= 160 && buttons)
			{
				strcpy(symbol, "D01");//三点零及以下
				return 4;

			}
			if (*mx >= 210 && *mx <= 320 && *my >= 140 && *my <= 160 && buttons)
			{
				strcpy(symbol, "D02");// 三点零到三点五
				return 4;
			}
			if (*mx >= 340 && *mx <= 450 && *my >= 140 && *my <= 160 && buttons)
			{
				strcpy(symbol, "D03");// 三点五到四点零
				return 4;
			}
			
		}
		if (judge == 5)
		{
			if (*mx >= 90 && *mx <= 180 && *my >= 140 && *my <= 160 && buttons)
			{
				strcpy(symbol, "E01");//1万美元以下
				return 4;

			}
			if (*mx >= 210 && *mx <= 320 && *my >= 140 && *my <= 160 && buttons)
			{
				strcpy(symbol, "E02");// 1万到2万美元
				return 4;
			}
			if (*mx >= 340 && *mx <= 450 && *my >= 140 && *my <= 160 && buttons)
			{
				strcpy(symbol, "E03");// 2万美元以上
				return 4;
			}
		}
		if (judge == 6)
		{
			if (*mx >= 90 && *mx <= 180 && *my >= 140 && *my <= 160 && buttons)
			{
				strcpy(symbol, "F01");//1000美元
				return 4;

			}
			if (*mx >= 210 && *mx <= 390 && *my >= 140 && *my <= 160 && buttons)
			{
				strcpy(symbol, "F02");// 1000到1500美元
				return 4;
			}
			if (*mx >= 410 && *mx <= 550 && *my >= 140 && *my <= 160 && buttons)
			{
				strcpy(symbol, "F03");// 1500美元以上
				return 4;
			}
		}
	}
}





