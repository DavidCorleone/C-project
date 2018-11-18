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

	  //�ж�Ӧ�õ�����Щ�����ı���
	setuser person;    //��ʾ��ǰ�û��ı���
	setuser *head = NULL;    //�û�������ͷ�ڵ�
	int driver = VGA;
	int mode = VGAHI;

	/*��Ҫ�ĳ�ʼ������*/
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
	
		/*����judge��ֵ�ж���Ҫ���ý�������̨����*/
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

			/*��ʼ��ͨ�û���ʹ��*/
		case Main_Modular:
			judge = main_trip(&person);
			break;

			/*�˳�����*/
		case Exit_system:
			freeUserlist(&head);
			return 0;

			/*��ʼ����Ա��ʹ��*/
		/*_screen:
			judge = manage();
			break;*/ 
		}
	}
}


/*************************************
Function: main_trip
Description:���˵������µĿ�ܺ���
Attention:
Return:
**************************************/
int main_trip(setuser *person)
{

	int judge = Search_screen;  
	setfilter *filterListHead = NULL;    //����ɸѡ����������ͷָ��
	setpath *pathListHead = NULL;  //����ѧУ��Ϣ������ͷָ�� 
	char symbol[20];    //ɸѡ������Ӧ�ı��� 
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
	CreateFilterList(filterListHead);    //�������Ľ��������� 
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
		/*����judge��ֵ�ж���Ҫ���ý�������̨����*/
		switch (judge)
		{
			/*������������*/
		case Search_screen:
			searchIF();
			judge = search(pathListHead, symbol);
			break;
			
			/*����߼�ɸѡ����*/
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
				WarningTips("��Ǹ�����ǻ�Ա��", 260, 200, BLUE);
				initgraph(&driver, &mode, "../BORLANDC\\bgi");
				cleardevice();
				judge = 1;
				break;
			
			}*/

			
			/*�����û�������Ϣ����*/
		case Person_screen:
			judge = user(symbol, person);
			break;
			
		case Show_globalrank:
			judge = showglobalrank(symbol, pathListHead);
			break; 
			
		case Show_disciplinerank:
			//showdisciplinerankIF();   ȱʡ 
			//judge = showrank(symbol,filterListHead);
			judge = showdisciplinerank(symbol, pathListHead); //test 
			break;
		
			/*���ɸѡ����������ɸѡ*/ 
		case Filter_screen:
			judge = collegeGuide(symbol, filterListHead, person, pathListHead);
			break;
		
			/*ѧУ����ϸ������Ϣ*/ 
		case viewCollege_screen:
			judge = viewcollegeIntroduce(symbol, pathListHead, person);
			break; 
			
			/*ע����¼���ص�½����*/
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

