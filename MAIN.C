#include<stdio.h>
#include<stdlib.h>
#include <graphics.h>
#include <conio.h>
#include<dos.h>
#include "user.h"
#include "login.h"
#include "register.h"
#include "search.h"
#include "structur.h"


#define Login_screen  0
#define Register_screen 1
#define Main_Modular  2
#define Exit_system 4
#define Manager_screen 5

#define Search_screen 1
#define advanced_screen 2 
#define viewCollege_screen 3
#define Filter_screen 4
#define Person_screen   5
#define Show_disciplinerank 6
#define Return_Last_screen 7
#define Show_globalrank 8


int main()
{
//	int judge = Login_screen;  
	int judge =	Main_Modular;

	  //判断应该调用那些函数的变量
	setuser person;    //表示当前用户的变量
	setuser *head = NULL;    //用户链表的头节点
	int driver = VGA;
	int mode = VGAHI;

	/*必要的初始化过程*/
	person.accounts[0] = '\0';
	person.code[0] = '\0';
	
	initgraph(&driver, &mode, "../BORLANDC\\bgi");
	cleardevice();


	if ((head = (setuser *)malloc(sizeof(setuser))) == NULL)
	{
		printf("\nOverflow");
		return 0;
	}
	CreateUserList(head);


	while (1)
	{
	
		/*根据judge的值判断需要调用界面和其后台函数*/
		switch (judge)
		{
		case Login_screen:
			LoginIF();
			judge = userLogin(head, person.accounts, person.code);
			break;
		case Register_screen: 
			RegisterIF();
			judge = userRegister(head, person.accounts, person.code);
			break;

			/*开始普通用户的使用*/
		case Main_Modular:
			judge = main_trip(&person);
			break;

			/*退出程序*/
		case Exit_system:
			freeUserlist(&head);
			return 0;

			/*开始管理员的使用*/
		/*_screen:
			judge = manage();
			break;*/ 
		}
	}
}


/*************************************
Function: main_trip
Description:主菜单界面下的框架函数
Attention:
Return:
**************************************/
int main_trip(setuser *person)
{

	int judge = Search_screen;  
	setfilter *filterListHead = NULL;    //创建筛选条件的链表头指针
	setpath *pathListHead = NULL;  //创建学校信息的链表头指针 
	char symbol[20];    //筛选条件对应的编码 
	int driver = VGA;
	int mode = VGAHI; 
	UserInit(person); 

	if ((filterListHead = (setfilter *)malloc(sizeof(setfilter))) == NULL)
	{
		closegraph();
		printf("\nOverflow");
		//getchar();
		exit(1);
	}
	if ((pathListHead = (setpath *)malloc(sizeof(setpath))) == NULL)
	{
		closegraph();
		printf("\nOverflow");
		//getchar();
		exit(1);
	}
	CreateFilterList(filterListHead);    //此链表的建立有问题 
	CreatePathList(pathListHead); 
/*	if(1)
	{
		closegraph();
		for(;pathListHead->next!=NULL; )
		{
			printf("Can't open %s\n", pathListHead->next->path);
			printf("Can't open %s\n", pathListHead->next->englishname);
			pathListHead = pathListHead->next;
		}
		  //"FILES\\college\\mit"  test
		getchar();
		exit(1);  
	}


*/
	while (1)
	{
		/*根据judge的值判断需要调用界面和其后台函数*/
		switch (judge)
		{
			/*进入搜索界面*/
		case Search_screen:
			searchIF();
			judge = search(pathListHead, symbol);
			break;
			
			/*进入高级筛选界面*/
		case advanced_screen:
			AdvancedSearchIF();
				judge = AdvancedSearch(pathListHead, person);
				break;
			/*if(strcmp(person->accounts, "heming") == 0 && strcmp(person->code, "666666") == 0)
			{
				AdvancedSearchIF();
				judge = AdvancedSearch(pathListHead, person);
				break;
			}
			else
			{
				WarningTips("抱歉，不是会员！", 260, 200, BLUE);
				initgraph(&driver, &mode, "../BORLANDC\\bgi");
				cleardevice();
				judge = 1;
				break;
			
			}*/

			
			/*进入用户个人信息界面*/
		case Person_screen:
			judge = user(symbol, person);
			break;
			
		case Show_globalrank:
			judge = showglobalrank(symbol, pathListHead);
			break; 
			
		case Show_disciplinerank:
			//showdisciplinerankIF();   缺省 
			//judge = showrank(symbol,filterListHead);
			judge = showdisciplinerank(symbol, pathListHead); //test 
			break;
		
			/*点击筛选条件，进行筛选*/ 
		case Filter_screen:
			judge = collegeGuide(symbol, filterListHead, person, pathListHead);
			break;
		
			/*学校的详细介绍信息*/ 
		case viewCollege_screen:
			judge = viewcollegeIntroduce(symbol, pathListHead, person);
			break; 
			
			/*注销登录返回登陆界面*/
		case Return_Last_screen:
			if (person->mark_collect == 1)
			RewriteCollectFile(person);
			freepathList(&pathListHead);
			freefilterList(&filterListHead);
			freecollectList(person);
			symbol[0] = '\0';
			pathListHead = NULL;
			filterListHead = NULL;
		   	return Login_screen;
		   	break;
		
		 

		}
	}
}


