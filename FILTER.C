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
Description:ɸѡ��������ĺ�̨����
Input:1�������ַ���symbol
	  3���ص�������ͷ�ڵ�
	  4���û������ĵ�ַperson
Attention:
Return:1������5��main_trip������ͷ����ѧУ���ܵĺ�̨����
*************************************************************/
int collegeGuide(char *symbol, const setfilter *filterhead, setuser *person, const setpath *pathhead)
{
    int judge = 1;    //�ж�Ӧ�õ�����Щ�����ı���
//	int temp;
	char FileContent[1000] = {'\0'};  //�����ܵĴ洢�ļ����� 
	int buttons, mx, my;   //����������
	char filterName[20];    //�����Ӧ��ɸѡ������������ 
	char englishName[20]; //�õ���Ӧ��Ӣ����д 
	char Path[100] = {'\0'};
	char *fileContent = NULL;  //����ÿһ�δ洢�ļ����� 
	static setcollegepathList *collegePathListHead = NULL;//�洢������Ϣ·��������
	//ͷ�ڵ㲻����Ч���� 
	static setcollegeList *collegeListHead = NULL;
	if ((collegeListHead = (setcollegeList *)malloc(sizeof(setcollegeList))) == NULL)
	{
		closegraph();
		printf("\nOverflow");
		//getchar();
		exit(1);
	}
	//��Ҫ�����ڴ棬����ΪNULL 
		
 

	if ((collegePathListHead = (setcollegepathList *)malloc(sizeof(setcollegepathList))) == NULL)
	{
		closegraph();
		printf("\nOverflow");
		getchar();
		exit(1);
	}
	
 
		 //symbol���� 
	filterName[0] = '\0';
	englishName[0] = '\0';
	
	SearchPath(symbol, pathhead, &collegePathListHead);  
	getFiltername(filterName, englishName, symbol, filterhead);   
	
	filterGuideIF(filterName, englishName);   	
	/*��Ҫ�ĳ�ʼ������*/
	mouseInit(&mx, &my, &buttons);
	while(1)
	{	
		newxy(&mx, &my, &buttons);
		/*��ʼĬ��judgeΪ1*/ 		
		switch (judge)
		{
		/*ѧУģ��*/
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
				WarningTips("��̨���ݲ�����", 260, 400, RED); 
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


		/*ѧУ��ϸ��Ϣ*/
		case 4:
			/*����4��main_trip������ͷ����ѧУ���ܵĺ�̨����*/
			return 3;
			

		/*������һ����*/
		case 6:
			return 1;
	
		/*�����û�������Ϣ����*/
		case 7:
			/*����5��main_trip������ͷ�����û��ĺ�̨����*/
			return 5;
			
		
		}
	}
}


/********************************
Function: filterGuideIF
Description:��ѧУ��������ĺ���
Input:��������
Attention:��
Return:��  
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
	bar(560, 0, 639, 40);  //���������Ľ��� 
	puthz(570, 10, "��������", 16, 16, WHITE);
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
Description: ���ݱ����������в���ɸѡ��������Ӧ����������Ӣ����д 
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
Description: ����abbreviation�������в���ɸѡ��������Ӧ��������
Attention:
Return:
*********************************************/
void getCollegename(const char *abbreviation, char *chinesename, const setpath *pathlisthead)
{
	setpath *current = pathlisthead;
//	current = current->next; 
	while (current != NULL)
	{
		current = current->next;  //����ͷ�ڵ㲻������ 
		if (strcmp(current->englishname, abbreviation) == 0)
	{
			break;
		}
	}
	strcpy(chinesename, current->chinesename);
}

/*****************************
Function: drawTransferPage
Description:�����½ǻ�ҳ�ĺ���
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
Description:��ʾѧУ�б��ĺ���
Input:ѧУ�б�ͷ�ڵ�collegepathlist����Ч���ݣ�����symbol���������mx,my
Attention:��
Return:����4�鿴ѧУ��Ϣ
***********************************************************/
int showCollegeList(setcollegeList *collegelisthead, char *symbol, int *mx, int *my)
{
	setcollegeList *first = NULL;
	setcollegeList *second = NULL;
	setcollegeList *current = NULL;
	setcollegeList *temp = NULL; //�����ݴ�õ���Current���� 
	int buttons = 0;    //���Ĳ�������
	int i ; 
	int j ;    
	int n=0 ;   //�����Ľڵ����
	int Currentpage = 1;    //ҳ��
	int formerPage = 0;


 	
	 //��¼�ڵ���� 
	current = collegelisthead->next;   //·����ͷ�ڵ� 
	
	while (current!= NULL)
	{
		n++;
		current = current->next;
	}

	current = collegelisthead;  //�ٴγ�ʼ�� 

	while (1)
	{
		newxy(mx, my, &buttons);

		/*�����������Ϣ����*/
		if (*mx >= 560 && *mx <= 640 && *my >= 0 && *my <= 30 && buttons)return 7;

		/*�������������*/
		if (*mx >= 0 && *mx <= 30 && *my >= 0 && *my <= 30 && buttons)return 6;

		   /*�����ҳ�������*/
		if (*mx >= 600 && *mx <= 630 && *my >= 440 && *my <= 470 && buttons)
		{
			Currentpage++;
			if (Currentpage > n / 2)Currentpage = n / 2;
		}
		/*�����ҳ�������*/
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

			/*��temp��λ��������ͷ�ĵ�i���ڵ�*/
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
				puthz(30, 239, "���", 16, 16, DARKGRAY);  //��Ҫ��ʾ���� 
			}

			if (second != NULL)
			{
				puthz(30, 302, second->chinesename, 32, 32, RED);
				puthz(30, 342, second->englishname, 16, 16, BLUE);
				puthz(70, 386, second->introduce, 16, 16, BLUE);
				puthz(30, 386, "���", 16, 16, DARKGRAY);
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
Description: ����college.txt�ļ��е���Ϣ����ѧУ��ַ����
Attention: 1�����ݹ�����ͷָ��һ��Ҫ��ȷ����ָ��
           2����college.txt�ļ�����գ�Ҫ���俪ͷ�ü��±�����#�Ų�����������������
           3�������������Ŀ�ͷ��ĩβ�ڵ㶼������Ч���ݣ�
Return:�޷���ֵ
***************************************************************/
void CreatePathList(setpath *head)
{
	setpath *current = NULL;  //ָ��ǰ����ָ�����
	FILE *fp = NULL;    //���ڴ�college.txt���ļ�ָ��
	char ch;    //���ڽ��ղ������ļ��ڲ��ַ����м����
	char *p = NULL;   //ָ����Ҫ�����ַ��ĵ�ַ��ָ�����


	/*��Ҫ�ĳ�ʼ������*/
	head->chinesename[0] = '\0';
	head->englishname[0] = '\0';
	head->path[0] = '\0';  //·����ʼ�� 
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
		ch = fgetc(fp);    //��.txt�ļ�����ȡһ���ַ�

		if (ch == '#')    //��ʾ���ֵĿ�ʼ����ŵĽ���
		{
			/*��ϵͳ����ռ�*/
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
		else if (ch == '*')      //��ʾ���ֵĽ�����ƴ����Сд��д�Ŀ�ʼ
		{
			*p = '\0';
			p = current->englishname;
		}
		else if (ch == '/')      //��ʾƴ���Թ���Ϊɸѡ�����ı��
		{
			*p = '\0';
			p = current->filter_country;
		}
		else if (ch =='^')  //�洢��ѧ������Ϊɸѡ�����ı��
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


