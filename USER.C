#include "user.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<bios.h>
#include<graphics.h>
#include "hz.h"
#include "cartoon.h"
#include "input.h"
#include "structur.h"
#include "nmouse.h"
 

/********************************************************************************
Function: CreateUserList
Description: ����usercode.txt�ļ��е���Ϣ�����û�����
Attention: 1�����ݹ�����ͷָ��һ��Ҫ��ȷ����ָ�� 
           2����usercode.txt�ļ�����գ�Ҫ���俪ͷ�ü��±�����#�Ų�����������������
		   3�������������Ŀ�ͷ��ĩβ�ڵ㶼������Ч���ݣ�
Return:�޷���ֵ
*********************************************************************************/
void CreateUserList(setuser *head)  
{
  setuser *current=NULL;  //ָ��ǰ����ָ�����
  FILE *fp=NULL;    //���ڴ�usercode.txt���ļ�ָ��
  char ch;    //���ڽ��ղ������ļ��ڲ��ַ����м����
  char *p=NULL;   //ָ����Ҫ�����ַ��ĵ�ַ��ָ�����

  /*��Ҫ�ĳ�ʼ������*/
  current = head;
  p = head->accounts;
  strcpy(head->code, "     ");   //��ֹ�������˺�����ֱ�ӵ��½������������

  /*if((fp=fopen("C:\\myCCD\\FILES\\user\\usercode.txt","r+"))==NULL)
  {
	  closegraph();
	  printf("Can't open usercode.txt");
	  getchar();
      exit(1);
  }*/

  if ((fp = fopen("FILES\\user\\usercode.txt", "r+")) == NULL)
  {
	  closegraph();
	  printf("Can't open usercode.txt");
	  getchar();
	  exit(1);
  }

  while(!feof(fp))
  {
	ch=fgetc(fp);    //��usercode.txt�ļ�����ȡһ���ַ�

	if(ch=='#')    //��ʾ�˻����Ŀ�ʼ�����봮�Ľ���
	 {
		/*��ϵͳ����ռ�*/
	   if((current->next=(setuser *)malloc(sizeof(setuser)))==NULL)
		{
		   closegraph();
		   printf("\nOverflow");
		   getchar();
		   exit(1);
		}

	   current=current->next;

	   *p='\0';
	   p=current->accounts;
	 }
	else if(ch=='*')      //��ʾ�˻����Ľ��������봮�Ŀ�ʼ
	{
	  *p='\0';           
	  p=current->code;
	}
	else if(ch!=' '&&ch!='\n')       //����Ӧ���˻��������봮װ��������
	{
	  *p=ch;
	  p++;
	}
  }

  strcpy(current->code, "   "); //��ֱֹ�ӵ����½������������
  current->next=NULL;
  fclose(fp);
}


/***********************************************
Function: freeUserlist
Description:�ͷ��������ڴ�ռ䲢��ͷָ����ΪNULL
Attention:�ļ����밴Ҫ���ʽ����д
Return:
************************************************/
void freeUserlist(setuser **head)
{
	setuser *previous = *head;
	setuser *current = (*head)->next;

	if (*head == NULL)return 0;

	while (current != NULL)
	{
		free(previous);
		previous = current;
		current = current->next;
	}
	free(previous);
	*head = NULL;
}

/************************************
Function: AddNewUser
Description: �����µ��û� 
Attention:s1ָ���û�����s2ָ�����봮
Return:
*************************************/
void AddNewUser(setuser *head,char *s1,char *s2)    
{
 setuser *current=head;
 FILE *fp;
 char *p;
 int length = strlen(s2);
 int i = 0;

 /*���³������Ϊ���û��������д����ڵ�*/
 while(current->next!=NULL)  
 {
  current=current->next;
 }
 strcpy(current->accounts,s1);
 strcpy(current->code,s2);
 if((current->next=(setuser *)malloc(sizeof(setuser)))==NULL)
 {
	 closegraph();
	 printf("\nOverflow");
	 getchar();
     exit(1);
 }

 current=current->next;

 strcpy(current->accounts, "   "); //��ֱֹ�ӵ����½������������
 strcpy(current->code, "   "); //��ֱֹ�ӵ����½������������
 current->next=NULL;


 /*���³�����ǽ������û�����Ϣд��usercode.txt�ļ���*/
 if ((fp = fopen("FILES\\user\\usercode.txt", "r+")) == NULL)
 {
	 closegraph();
	 printf("Can't open usercode.txt");
	 getchar();
	 exit(1);
 }
 /* if((fp=fopen("C:\\myCCD\\FILES\\user\\usercode.txt","r+"))==NULL)   
  {
	  closegraph();
      printf("Can't open usercode.txt");   
      getchar();
      exit(1);
  }*/


  /*���ļ��ڲ�ָ���Ƶ��ļ�ĩ��*/
  fseek(fp,0L,2);

  p=s1;
  while(*p!='\0')
  {
	putc(*p,fp);
	p++;
  }
  putc('*',fp);

  p=s2;
  while(*p!='\0')
  {
	putc(*p,fp);
	p++;
  }
  for (i = 0;i < 10 - length;i++)
	  putc(' ', fp);
  putc('#',fp);

 fclose(fp);
}



/****************************************************
Function: SearchAccounts
Description: �������������˺���Ϣ
Attention:
Return:�����򷵻ض�Ӧ�����봮�ĵ�ַ����û���򷵻�NULL
****************************************************/
char *SearchAccounts(setuser *head,char *string)
{
 setuser *current=head;

 while(current&&strcmp(current->accounts,string)!=0)
 {
   current=current->next;
 }
 if(!current)return NULL;
 else return current->code;
}

/****************************************************
Function: UserInit
Description:�û��ղؼг�ʼ������
Attention:1�����ɵ��û��ղ�����ֻ��ͷ�ڵ�������Ϊ��
Return:
****************************************************/
 void UserInit(setuser *person)
{
	FILE *fp = NULL;
	char *p = NULL;
	char ch;
	//char Path[100] = "C:\\myCCD\\FILES\\user\\collect\\";
	char Path[100] = "C:\\test\\FILES\\user\\collect\\";
//	setcollect *currentcollege = NULL;
	setcollect *current = NULL;

	/*��ʼ���������Ϊ0*/
	person->mark_collect = 0;


	/*����Ϊ��ʼ���û����ղ�����*/
	/*person->college.name[0] = '\0';
	currentcollege = &(person->college);
	p = currentcollege->name;
	currentcollege->next = NULL;*/
	current=&(person->college);
	current->name[0] = '\0';
	current->englishname[0] = '\0'; 
	p = current->name;

	strcat(Path, person->accounts);
	strcat(Path, ".txt");

	fp = fopen(Path, "r+");
	
	while (fp != NULL && !feof(fp))
	{
	ch = fgetc(fp);

		if (ch == '#')
		{	
			/*	*p = '\0';
				ch = fgetc(fp);
				 if (ch == 'C')
				{
					if ((currentcollege->next = (setcollect *)malloc(sizeof(setcollect))) == NULL)
				{
					closegraph();
					printf("\nOverflow");
					getchar();
					exit(1);
				}
				currentcollege = currentcollege->next;
				currentcollege->next = NULL;
				current = currentcollege;
				*p = '\0';
				p = current->name;
				*p = 'C';
				p++;
			}*/
			/*��ϵͳ����ռ�*/
			if ((current->next = (setcollect *)malloc(sizeof(setcollect))) == NULL)
			{
				closegraph();
				printf("\nOverflow");
				getchar();
				exit(1);
			}

			current = current->next;
			*p = '\0';
			p = current->name;
		}
		else if (ch == '*')      //��ʾ���ֵĽ�����ƴ����Сд��д�Ŀ�ʼ
		{
			*p = '\0';
			p = current->englishname;
		}
		else if(ch!='\n') 
		{
			*p = ch;
			p++;
		}
	} 
	current->name[0] = '\0';
	current->englishname[0] = '\0';
	current->next = NULL;
	fclose(fp);
/*	if(1)
	{
		closegraph();
		printf("Can't open %s%s", person->college.next->name,person->college.next->next->name); 
		getchar();
		exit(1);  
	} */
	/*currentcollege->next = NULL;
	fclose(fp);
	fp = NULL;
	p = NULL;*/
	
}

int ChangeCode(setuser *person, int *mx, int *my)
{
	FILE *fp = NULL;    //���ڴ�usercode.txt���ļ�ָ��
	char ch = '\0';
	char CurrentAccounts[11];
	char *p = NULL;
	int length =0;
	int i;
	int buttons = 0;
	int judge = -1;
	int mark = 0;
	char oldcode[11] = {'\0'};
	char newcode[11] = { '\0' };
	char secondcode[11] = { '\0' };
	int temp;    //�������ռ��̻������ı���

	while (1)
	{
		newxy(mx, my, &buttons);

		/*���ռ��̻�����������*/
		if (kbhit() != 0)
		{
			temp = bioskey(0);
		}

		if (mark == 1)
		{
			break;
		}

		/*����������������*/
		if (*mx >= 250 && *mx <= 400 && *my >= 100 && *my <= 130 && buttons)judge = 0;

		/*����������������*/
		if (*mx >= 250 && *mx <= 400 && *my >= 140 && *my <= 170 && buttons)judge = 1;

		/*������ڶ�����������*/
		if (*mx >= 250 && *mx <= 400 && *my >= 200 && *my <= 230 && buttons)judge = 2;

		/*������޸�����*/
		if (*mx >= 295 && *mx <= 345 && *my >= 250 && *my <= 280 && buttons)judge = 3;

		/*������ҵ��ղ�����*/
		if (*mx >= 20 && *mx <= 150 && *my >= 130 && *my <= 160 && buttons)return 2;

		/*����������������*/
		if (*mx >= 20 && *mx <= 150 && *my >= 160 && *my <= 190 && buttons)return 3;

		/*������˳�ϵͳ����*/
		if (*mx >= 20 && *mx <= 150 && *my >= 190 && *my <= 220 && buttons)return 4;

		/*��������ذ���*/
		if (*mx >= 0 && *mx <= 20 && *my >= 0 && *my <= 20 && buttons)return 5;

		switch (judge)
		{
			/*����������*/
		case 0:
			judge = oldcodeinput(oldcode,mx,my);
			break;
			/*����������*/
		case 1:
			judge = newcodeinput(newcode,mx,my);
			break;

			/*�ڶ�����������*/
		case 2:
		    judge = secondcodeinput(secondcode,mx,my);
			break;

			/*ȷ���޸�*/
		case 3:
			/*���벻ƥ��*/
			if (strcmp(oldcode, (*person).code) != 0)
			{
				setfillstyle(1, WHITE);
				bar(410, 105, 510, 130);
				puthz(410, 105, "ԭ���벻ƥ�䣡", 16, 16, RED);
			}
			
			/*����������6λ*/
			else if (strlen(newcode) < 6)
			{
				setfillstyle(1, WHITE);
				bar(410, 105, 510, 130);
				bar(410, 145, 510, 170);
				puthz(410, 145, "����������6λ��", 16, 16, RED);
			}
			/*�����������벻ͬ*/
			else if (strcmp(newcode, secondcode) != 0)
			{
				setfillstyle(1, WHITE);
				bar(410, 105, 510, 130);
				bar(410, 145, 510, 170);
				bar(410, 205, 510, 230);
				puthz(410, 205, "�������벻ƥ�䣡", 16, 16, RED);
			}
			else
			{
				mark = 1;
			}
			judge = -1;
			break;
		}

	}

	length = strlen(newcode);
	/*if ((fp = fopen("C:\\myCCD\\FILES\\user\\usercode.txt", "r+")) == NULL)
	{
		closegraph();
		printf("Can't open usercode.txt");
		getchar();
		exit(1);
	}*/
	if ((fp = fopen("C:\\test\\FILES\\user\\usercode.txt", "r+")) == NULL)
	{
		closegraph();
		printf("Can't open usercode.txt");
		getchar();
		exit(1);
	}

	while (!feof(fp))
	{
		ch = fgetc(fp);
		if (ch == '#')
		{
			ch = fgetc(fp);
			for (p = CurrentAccounts;ch != '*';ch = fgetc(fp))
			{
				*p = ch;
				*(p + 1) = '\0';
				p++;
			}
			if (strcmp(CurrentAccounts, (*person).accounts) == 0)
			{
				p = newcode;
				fseek(fp, 0, SEEK_CUR);
				fputs(newcode, fp);
				for (i = 0;i < 10 - length;i++)
				putc(' ', fp);
				break;
			}
		}
	}

	strcpy((*person).code, newcode);
	fclose(fp);

	{
		int driver = VGA;
		int mode = VGAHI;

		WarningTips("�����޸ĳɹ���", 260, 200, GREEN);
		//initgraph(&driver, &mode, "C:\\BORLANDC\\bgi");
		initgraph(&driver, &mode, "../BORLANDC\\bgi");
		cleardevice();
		return 0;
	}
}


/****************************************************
Function: user
Description: �û������̨����
Attention:
Return:
****************************************************/
int user(char *symbol, setuser *person)
{
	int judge = 0;    //�ж�Ӧ�õ�����Щ�����ı���
	int buttons, mx, my;   //����������
	
	/*�����ذ�ť��ֹ����Ӱ*/
	cleardevice();
	setbkcolor(WHITE);
	setfillstyle(1, LIGHTGREEN);
	bar(20, 100, 150, 220);
	setfillstyle(1, LIGHTGRAY);
	bar(0, 0, 30, 30);
	setcolor(WHITE);
	line(5, 15, 25, 15);
	line(5, 15, 10, 20);
	line(5, 15, 10, 10);

	while (1)
	{
		newxy(&mx, &my, &buttons);

		/*������޸���������*/
		if (mx >= 190 && mx <= 450 && my >= 100 && my <= 185 && buttons)judge = 1;

		/*������ҵ��ղ�����*/
		if (mx >= 190 && mx <= 450 && my >= 185 && my <= 270  && buttons)judge= 2;

		/*����������������*/
		if (mx >= 190 && mx <= 450 && my >= 270 && my <= 355 && buttons)judge = 3;

		/*������˳�ϵͳ����*/
		if (mx >= 190 && mx <= 450 && my >= 355 && my <= 440 && buttons)judge = 4;

		/*��������ذ���*/
		if (mx >= 0 && mx <= 30 && my >= 0 && my <= 30 && buttons)judge = 5;

		switch (judge)
		{
			/*��ӭ����*/
		case 0:
			welcomeIF(person->accounts);
			mouseInit(&mx, &my, &buttons);
			judge = -1;
			break;
			/*�޸�����*/
		case 1:
			changeCodeIF();
			judge = ChangeCode(person, &mx, &my);
			break;

			/*�ҵ��ղ�*/
		case 2:
			showmyCollectIF();
			judge = showmyCollect(symbol, &(person->college), &mx, &my);

			break;

			/*�������*/
		case 3:
			feedbackIF(); 
			judge = feedback();
			break;

			/*ע����¼*/
		case 4:
			if (Choose("�Ƿ��˳���½��", &mx, &my, WHITE) == 0)judge = 0;
			else return 7;

			break;
			/*������һ������*/ 
		case 5:
			return 1;
		case 6:
			judge = manageCollect(person, &mx, &my); 
			break;
		case 7: //���ղؽ����ѧ 
			return 3;
		}
	}
}



/******************************
Function: welcomeIF
Description:���˽���Ļ�ӭ����
Attention:
******************************/
void welcomeIF(char *accounts)
{
	int n = 0;

	cleardevice();

	setbkcolor(WHITE);
	setfillstyle(1, LIGHTGRAY);
	bar(0, 0, 30, 30);  //���ذ�ť
	setcolor(WHITE);
	line(5, 15, 25, 15);
	line(5, 15, 10, 20);
	line(5, 15, 10, 10);

	setfillstyle(1, LIGHTBLUE);
	bar(190,100,450,440);
	//����ʾ���� 
	setlinestyle(0,0,3);
	setcolor(WHITE);
	line(190,185,450,185);
	line(190,270,450,270);
	line(190,355,450,355);
	puthz(250, 130, "��������", 32, 32, WHITE);
	puthz(250, 210, "�ҵ��ղ�", 32, 32, WHITE);
	puthz(250, 295, "�������" ,32, 32, WHITE);
	puthz(250, 380, "�˳���¼", 32, 32, WHITE);
	puthz(190, 20, "���ã�", 32, 32, LIGHTBLUE);
	settextstyle(0,0,4);
	setcolor(LIGHTBLUE);
	outtextxy(280,20,accounts);
	n = strlen(accounts);
	puthz(280+n*32, 20, "��", 32, 32, LIGHTBLUE);
}


/**************************
Function: changeCodeIF
Description:�������������
Attention:
***************************/
void changeCodeIF()
{
	cleardevice();

	setbkcolor(WHITE);
	setfillstyle(1, LIGHTBLUE);
	bar(20, 100, 150, 220);
	setfillstyle(1, LIGHTGRAY);

	bar(0, 0, 30, 30);
	setcolor(WHITE);
	line(5, 15, 25, 15);
	line(5, 15, 10, 20);
	line(5, 15, 10, 10);
	
	setcolor(LIGHTGRAY);
	line(20, 130, 150, 130);
	line(20, 160, 150, 160);
	line(20, 190, 150, 190);
	setcolor(WHITE);
	circle(30, 140, 5);
	line(23, 155, 37, 155);
	line(23, 155, 28, 143);
	line(37, 155, 32, 143);
	line(23, 183, 28, 177);
	line(28, 177, 32, 180);
	line(32, 180, 38, 170);
	line(38, 170, 38, 175);
	line(38, 170, 34, 173);

	setfillstyle(1, WHITE);
	floodfill(30, 140, WHITE);
	floodfill(30, 147, WHITE);
	arc(30, 207, 110, 430, 5);
	line(30, 206, 30, 198);
	circle(30, 120, 4);
	floodfill(30, 120, WHITE);
	line(30, 116, 30, 107);
	line(30, 109, 33, 111);
	line(30, 112, 33, 113);
	setcolor(LIGHTBLUE);
	circle(30, 122, 1);
	setfillstyle(1, BLUE);
	bar(295, 250, 345, 280);
	puthz(304, 257, "ȷ��", 16, 16, WHITE);
	puthz(60, 107, "��������", 16, 16, WHITE);
	puthz(60, 137, "�ҵ��ղ�", 16, 16, WHITE);
	puthz(60, 167, "�������", 16, 16, WHITE);
	puthz(60, 197, "�˳���¼", 16, 16, WHITE);

	setcolor(BLUE);
	rectangle(250, 100, 400, 130);
	rectangle(250, 140, 400, 170);
	rectangle(250, 200, 400, 230);
	puthz(180, 107, "��ǰ����", 16, 16, DARKGRAY);
	puthz(196, 147, "������", 16, 16, DARKGRAY);
	puthz(180, 207, "ȷ������", 16, 16, DARKGRAY);
	puthz(250, 177, "����ĸ��������ɵ�6��12λ�ַ������ִ�Сд", 16, 16, BROWN);
}
/****************************************************
Function: feedback
Description: �ṩ�û���ѡ��ķ��� 
Attention:
Return:
****************************************************/
int feedback()
{	
	int buttons, mx, my;   //����������
	FILE *fpp=NULL;
	mouseInit(&mx, &my, &buttons);
	if ((fpp = fopen("FILES\\feedback.txt", "r+")) == NULL)
 	{
	  	closegraph();
	  	printf("Can't open usercode.txt");
	  	getchar();
	  	exit(1);
  	}
  	fseek(fpp,0L,SEEK_END);
	while (1)
	{
		newxy(&mx, &my, &buttons);
		
		/*�������������*/
		if (mx >= 140 && mx <= 220 && my >= 275 && my <= 320 && buttons)
		{
			AddFrame(mx, my, 140, 275, 220, 320,BLACK);
			fputs("good\n\0",fpp);
			fclose(fpp);
			return 0;
		}
		
		/*�����һ������*/
		if (mx >= 330 && mx <= 410 && my >= 275 && my <= 320 && buttons)
		{
			AddFrame(mx, my, 330, 275, 410, 320,BLACK);
			fputs("just so so\n\0",fpp);
			fclose(fpp);
			return 0;
		}
	
		/*��������ذ���*/
		if (mx >= 0 && mx <= 30 && my >= 0 && my <= 30 && buttons)
		return 0;
	
		/*�����ȷ������*/
		if (mx >= 270 && mx <= 350 && my >= 410 && my <= 455 && buttons) 
		return 0;
			
	}
} 
/****************************************************
Function: feedbackIF
Description: ���������� 
Attention:
Return:
****************************************************/
void feedbackIF()
{
	cleardevice();
	setbkcolor(WHITE);
	
	setfillstyle(1, LIGHTGRAY);
	bar(0, 0, 30, 30);
	setcolor(WHITE);
	line(5, 15, 25, 15);
	line(5, 15, 10, 20);
	line(5, 15, 10, 10);
	
	setcolor(LIGHTBLUE);
	setfillstyle(1, LIGHTBLUE);
	puthz(60 , 95,"���ã���ӭ�������Ὠ�飡", 48, 48, BLUE);
	
	bar(100, 180, 510, 240);
	puthz(120 , 192,"����������ʹ�ø�����Σ�", 32, 32, WHITE);
	setfillstyle(1, LIGHTGRAY);
	bar(140, 275, 220, 320);
	bar(330, 275, 410, 320);	
	puthz(147, 282,"����", 32, 32, GREEN);
	
	puthz(337, 282,"һ��", 32, 32, RED);
	//ȷ�ϰ��� 
	setfillstyle(1, LIGHTBLUE);
	bar(270,410,350,455); 
	puthz(278, 416, "ȷ��", 32, 32, WHITE);
} 


