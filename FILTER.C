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
#include "filter.h"
#include "dealfile.h" 
#include "advanced.h"
#include "search.h"
/************************************************************
Function: collegeGuide
Description:筛选引导界面的后台函数
Input:1、编码字符串symbol
	  3、地点链表的头节点
	  4、用户变量的地址person
Attention:
Return:1、返回5在main_trip函数里头调用学校介绍的后台函数
*************************************************************/
int collegeGuide(char *symbol, const setfilter *filterhead, setuser *person, const setpath *pathhead)
{
    int judge = 1;    //判断应该调用那些函数的变量
//	int temp;
	char FileContent[1000] = {'\0'};  //用于总的存储文件内容 
	int buttons, mx, my;   //鼠标参数变量
	char filterName[20];    //编码对应的筛选条件中文名称 
	char englishName[20]; //得到对应的英文缩写 
	char Path[100] = {'\0'};
	char *fileContent = NULL;  //用于每一次存储文件内容 
	static setcollegepathList *collegePathListHead = NULL;//存储缩略信息路径的链表
	//头节点不存有效数据 
	static setcollegeList *collegeListHead = NULL;
	if ((collegeListHead = (setcollegeList *)malloc(sizeof(setcollegeList))) == NULL)
	{
		closegraph();
		printf("\nOverflow");
		//getchar();
		exit(1);
	}
	//需要分配内存，否则为NULL 
		
 

	if ((collegePathListHead = (setcollegepathList *)malloc(sizeof(setcollegepathList))) == NULL)
	{
		closegraph();
		printf("\nOverflow");
		getchar();
		exit(1);
	}
	
 
		 //symbol正常 
	filterName[0] = '\0';
	englishName[0] = '\0';
	
	SearchPath(symbol, pathhead, &collegePathListHead);  
	getFiltername(filterName, englishName, symbol, filterhead);   
	
	filterGuideIF(filterName, englishName);   	
	/*必要的初始化过程*/
	mouseInit(&mx, &my, &buttons);
	while(1)
	{	
		newxy(&mx, &my, &buttons);
		/*初始默认judge为1*/ 		
		switch (judge)
		{
		/*学校模块*/
		case 1:

			//setfillstyle(1, WHITE);
			//bar(0, 150, 640, 480);
		collegePathListHead = collegePathListHead->next;
		while(collegePathListHead->next != NULL)
		{
			strcpy(Path, collegePathListHead->path); 
			if (ReadFile(Path, &fileContent) == 1)
			{	
				int driver = VGA;
				int mode = VGAHI;
				WarningTips("后台数据不存在", 260, 400, RED); 
				initgraph(&driver, &mode, "D:\\BORLANDC\\bgi");
				cleardevice();
			}
			
	
			strcat(FileContent, fileContent);
			free(fileContent);
			fileContent = NULL;
			memset(Path,0,sizeof(Path));
			collegePathListHead = collegePathListHead->next;
		}	
			
			CreateCollegeList(FileContent, collegeListHead);

	/*		if(1)
		{
				closegraph();
				printf("Can't open %s","helloworld");
				for( ;collegeListHead->next!=NULL; )
				{
					printf("Can't open %s",collegeListHead->next->englishname);  //"FILES\\college\\mit"  test
				 	collegeListHead = collegeListHead->next;
				}
				getchar();
				
				exit(1);  
		}
	*/ 
			judge = showCollegeList(collegeListHead, symbol, &mx, &my);
			memset(FileContent,0,sizeof(FileContent));
			freecollegeList(&collegeListHead);
			freecollegepathList(&collegePathListHead);
			break;


		/*学校详细信息*/
		case 4:
			/*返回4在main_trip函数里头调用学校介绍的后台函数*/
			return 3;
			

		/*返回上一界面*/
		case 6:
			return 1;
	
		/*进入用户个人信息界面*/
		case 7:
			/*返回5在main_trip函数里头调用用户的后台函数*/
			return 5;
			
		
		}
	}
}


/********************************
Function: filterGuideIF
Description:画学校引导界面的函数
Input:国家名字
Attention:无
Return:无  
*********************************/
void filterGuideIF(char *filtername, char *englishname)
{
	cleardevice();
	setbkcolor(WHITE);
	setcolor(LIGHTGRAY);
	line(0, 145, 640, 145);
	line(0, 291, 640, 291);
	line(0, 440, 640, 440);
	puthz(50, 70, filtername, 48, 48, RED);
	puthz(450,98, englishname, 16, 16 ,GREEN);
	setfillstyle(1, BLUE);  
	bar(560, 0, 639, 40);  //画个人中心界面 
	puthz(570, 10, "个人中心", 16, 16, WHITE);
	setfillstyle(1, LIGHTGRAY);
	setcolor(WHITE);
	bar(0, 0, 30, 30);
	line(5, 15, 25, 15);
	line(5, 15, 10, 20);
	line(5, 15, 10, 10);
	bar(600, 440, 630, 470);
	bar(560, 440, 590, 470);
	line(608, 445, 622, 455);
	line(622, 455, 608, 465);
	line(608, 465, 608, 445);
	line(568, 455, 582, 445);
	line(582, 445, 582, 465);
	line(582, 465, 568, 455);
	setfillstyle(1, WHITE);
	floodfill(610, 455, WHITE);
	floodfill(580, 455, WHITE);

}


/*********************************************
Function: getFiltername
Description: 根据编码在链表中查找筛选条件的相应的中文名和英文缩写 
Attention:
Return:
*********************************************/
void getFiltername(char *chinesename, char *englishname, char *symbol, const setfilter *head)
{
	setfilter *current = head->next;


	while(current!=NULL)
	{
		if(strcmp(current->symbol,symbol)==0)
			break;
 		current = current->next; 

	}
	
	strcpy(chinesename, current->chinesename);
	strcpy(englishname, current->englishname);
	
	
}

/*********************************************
Function: getCollegename
Description: 根据abbreviation在链表中查找筛选条件的相应的中文名
Attention:
Return:
*********************************************/
void getCollegename(const char *abbreviation, char *chinesename, const setpath *pathlisthead)
{
	setpath *current = pathlisthead;
//	current = current->next; 
	while (current != NULL)
	{
		current = current->next;  //由于头节点不存数据 
		if (strcmp(current->englishname, abbreviation) == 0)
	{
			break;
		}
	}
	strcpy(chinesename, current->chinesename);
}

/*****************************
Function: drawTransferPage
Description:画右下角换页的函数
Input:  
Attention:
Return:
*****************************/
void drawTransferPage()
{
	setfillstyle(1, LIGHTGRAY);
	setcolor(WHITE);
	bar(0, 0, 30, 30);
	line(5, 15, 25, 15);
	line(5, 15, 10, 20);
	line(5, 15, 10, 10);
	bar(600, 440, 630, 470);
	bar(560, 440, 590, 470);
	line(608, 445, 622, 455);
	line(622, 455, 608, 465);
	line(608, 465, 608, 445);
	line(568, 455, 582, 445);
	line(582, 445, 582, 465);
	line(582, 465, 568, 455);
	setfillstyle(1, RED);
	floodfill(610, 455, RED);
	floodfill(580, 455, RED);
}

/**********************************************************
Function: showCollegeList
Description:显示学校列表的函数
Input:学校列表头节点collegepathlist无有效数据，编码symbol，鼠标坐标mx,my
Attention:无
Return:返回4查看学校信息
***********************************************************/
int showCollegeList(setcollegeList *collegelisthead, char *symbol, int *mx, int *my)
{
	setcollegeList *first = NULL;
	setcollegeList *second = NULL;
	setcollegeList *current = NULL;
	setcollegeList *temp = NULL; //用于暂存得到的Current数据 
	int buttons = 0;    //鼠标的参数变量
	int i ; 
	int j ;    
	int n=0 ;   //链表的节点个数
	int Currentpage = 1;    //页码
	int formerPage = 0;


 	
	 //记录节点个数 
	current = collegelisthead->next;   //路径的头节点 
	
	while (current!= NULL)
	{
		n++;
		current = current->next;
	}

	current = collegelisthead;  //再次初始化 

	while (1)
	{
		newxy(mx, my, &buttons);

		/*鼠标点击个人信息区域*/
		if (*mx >= 560 && *mx <= 640 && *my >= 0 && *my <= 30 && buttons)return 7;

		/*鼠标点击返回区域*/
		if (*mx >= 0 && *mx <= 30 && *my >= 0 && *my <= 30 && buttons)return 6;

		   /*鼠标点击页码加区域*/
		if (*mx >= 600 && *mx <= 630 && *my >= 440 && *my <= 470 && buttons)
		{
			Currentpage++;
			if (Currentpage > n / 2)Currentpage = n / 2;
		}
		/*鼠标点击页码减区域*/
		if (*mx >= 560 && *mx <= 590 && *my >= 440 && *my <= 470 && buttons)
		{
			Currentpage--;
			if (Currentpage < 1)
				Currentpage = 1;
		}

		if (Currentpage!= formerPage)
		{
			formerPage = Currentpage;
			first = NULL;
			second = NULL;
			setfillstyle(1, WHITE);
			bar(0, 150, 640, 438);
			i = Currentpage * 2 ;

			/*用temp定位到链表里头的第i个节点*/
			temp = collegelisthead;
			for (j = 1;j < i;j++)
			{
				temp = temp->next;
			}
			first = temp;
			if(first->next->next!=NULL)
			{
				second = first->next;
			}
			else
			{
				second = NULL;
			}

			if (first != NULL)
			{
				puthz(30, 155, first->chinesename, 32, 32, RED);
				puthz(30, 195, first->englishname, 16, 16, BLUE);
				puthz(70, 239, first->introduce, 16, 16, BLUE);
				puthz(30, 239, "简介", 16, 16, DARKGRAY);  //还要显示介绍 
			}

			if (second != NULL)
			{
				puthz(30, 302, second->chinesename, 32, 32, RED);
				puthz(30, 342, second->englishname, 16, 16, BLUE);
				puthz(70, 386, second->introduce, 16, 16, BLUE);
				puthz(30, 386, "简介", 16, 16, DARKGRAY);
			}
		}

		if (*mx >= 5 && *mx <= 635 && *my >= 150&& *my <= 293&& first != NULL)
		{
			AddFrame(*mx,*my, 5,150,635,293, RED);
			if (buttons)
			{
				strcpy(symbol, first->englishname);  
		
				return 4;
			}
		}
		else AddFrame(*mx, *my, 5, 150, 635, 293, WHITE);

		if (*mx >= 5 && *mx <= 635 && *my >= 297 && *my <= 435&& second != NULL)
		{
			AddFrame(*mx, *my, 5,297,635,435, RED);
			if (buttons)
			{
				strcpy(symbol, second->englishname);
				return 4;
			}
		}
		else AddFrame(*mx, *my, 5, 297, 635, 435, WHITE);
	}
}



/**************************************************************
Function: CreatePathList
Description: 根据college.txt文件中的信息创建学校地址链表
Attention: 1、传递过来的头指针一定要有确定的指向！
           2、若college.txt文件被清空，要在其开头用记事本加上#号才能正常创建链表！
           3、创建的链表的开头与末尾节点都不存有效数据！
Return:无返回值
***************************************************************/
void CreatePathList(setpath *head)
{
	setpath *current = NULL;  //指向当前结点的指针变量
	FILE *fp = NULL;    //用于打开college.txt的文件指针
	char ch;    //用于接收并传送文件内部字符的中间变量
	char *p = NULL;   //指向需要接收字符的地址的指针变量


	/*必要的初始化过程*/
	head->chinesename[0] = '\0';
	head->englishname[0] = '\0';
	head->path[0] = '\0';  //路径初始化 
	head->filter_country[0] = '\0';
	head->filter_disciplinerank[0] = '\0';
	head->filter_globalrank[0] = '\0';
	head->filter_gpa[0] = '\0';
	head->filter_livingcost[0] = '\0';
	head->filter_tuition[0]  = '\0';
	current = head;
	p = current->chinesename;

	/*if ((fp = fopen("FILES\\filter\\college.txt", "r+")) == NULL)
	{
		closegraph();
		printf("Can't open college.txt");
		getchar();
		exit(1);
	}*/
	if ((fp = fopen("E:\\test\\FILES\\filter\\college.txt", "r+")) == NULL)
	{
		closegraph();
		printf("Can't open college.txt");
		//getchar();
		exit(1);
	}


	while (!feof(fp))
	{
		ch = fgetc(fp);    //从.txt文件中提取一个字符

		if (ch == '#')    //表示汉字的开始，编号的结束
		{
			/*向系统申请空间*/
			if ((current->next = (setpath *)malloc(sizeof(setpath))) == NULL)
			{
				closegraph();
				printf("\nOverflow");
				//getchar();
				exit(1);
			}

			current = current->next;
			*p = '\0';
			p = current->chinesename;
		}
		else if (ch == '*')      //表示汉字的结束，拼音的小写缩写的开始
		{
			*p = '\0';
			p = current->englishname;
		}
		else if (ch == '/')      //表示拼储以国家为筛选条件的编号
		{
			*p = '\0';
			p = current->filter_country;
		}
		else if (ch =='^')  //存储以学费区间为筛选条件的编号
		{
			*p = '\0';
			p = current->filter_tuition;  
		 } 
		else if (ch == '@')
		{
			*p = '\0';
			p = current->filter_globalrank;  
		}
		else if (ch == '$')
		{
			*p = '\0';
			p = current->filter_disciplinerank;  
		}
		else if (ch == '&')
		{
			*p = '\0';
			p = current->filter_livingcost;  
		}
		else if (ch == '%')
		{
			*p = '\0';
			p = current->filter_gpa;  
		}
		
		else if (ch == '~')
		{
			*p = '\0';
			p = current->path;  
		}
		else if(ch!='\n')      
		{
			*p = ch;
			p++;
		}
	}

	current->chinesename[0] = '\0';
	current->englishname[0] = '\0';
	current->filter_country[0] = '\0';
	current->filter_tuition[0] = '\0';
	current->filter_globalrank[0] = '\0';
	current->filter_disciplinerank[0] = '\0';
	current->filter_livingcost[0] = '\0';	
	current->filter_gpa[0] = '\0';	
	current->path[0] = '\0';
	current->next = NULL;
 	
	fclose(fp);
//	fp = NULL;
}



