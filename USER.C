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
Description: 根据usercode.txt文件中的信息创建用户链表
Attention: 1、传递过来的头指针一定要有确定的指向！ 
           2、若usercode.txt文件被清空，要在其开头用记事本加上#号才能正常创建链表！
		   3、创建的链表的开头与末尾节点都不存有效数据！
Return:无返回值
*********************************************************************************/
void CreateUserList(setuser *head)  
{
  setuser *current=NULL;  //指向当前结点的指针变量
  FILE *fp=NULL;    //用于打开usercode.txt的文件指针
  char ch;    //用于接收并传送文件内部字符的中间变量
  char *p=NULL;   //指向需要接收字符的地址的指针变量

  /*必要的初始化过程*/
  current = head;
  p = head->accounts;
  strcpy(head->code, "     ");   //防止不输入账号密码直接点登陆进入的情况发生

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
	ch=fgetc(fp);    //从usercode.txt文件中提取一个字符

	if(ch=='#')    //表示账户串的开始，密码串的结束
	 {
		/*向系统申请空间*/
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
	else if(ch=='*')      //表示账户串的结束，密码串的开始
	{
	  *p='\0';           
	  p=current->code;
	}
	else if(ch!=' '&&ch!='\n')       //将对应的账户串或密码串装入链表中
	{
	  *p=ch;
	  p++;
	}
  }

  strcpy(current->code, "   "); //防止直接点击登陆进入的情况发生
  current->next=NULL;
  fclose(fp);
}


/***********************************************
Function: freeUserlist
Description:释放链表的内存空间并将头指针置为NULL
Attention:文件必须按要求格式化书写
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
Description: 创建新的用户 
Attention:s1指代用户串，s2指代密码串
Return:
*************************************/
void AddNewUser(setuser *head,char *s1,char *s2)    
{
 setuser *current=head;
 FILE *fp;
 char *p;
 int length = strlen(s2);
 int i = 0;

 /*以下程序块是为新用户在链表中创建节点*/
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

 strcpy(current->accounts, "   "); //防止直接点击登陆进入的情况发生
 strcpy(current->code, "   "); //防止直接点击登陆进入的情况发生
 current->next=NULL;


 /*以下程序块是将将新用户的信息写入usercode.txt文件中*/
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


  /*将文件内部指针移到文件末端*/
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
Description: 在链表中搜索账号信息
Attention:
Return:若有则返回对应的密码串的地址，若没有则返回NULL
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
Description:用户收藏夹初始化函数
Attention:1、生成的用户收藏链表只有头节点数据域为空
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

	/*初始化操作标记为0*/
	person->mark_collect = 0;


	/*下面为初始化用户的收藏链表*/
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
			/*向系统申请空间*/
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
		else if (ch == '*')      //表示汉字的结束，拼音的小写缩写的开始
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
	FILE *fp = NULL;    //用于打开usercode.txt的文件指针
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
	int temp;    //用于吸收键盘缓冲区的变量

	while (1)
	{
		newxy(mx, my, &buttons);

		/*吸收键盘缓冲区域数据*/
		if (kbhit() != 0)
		{
			temp = bioskey(0);
		}

		if (mark == 1)
		{
			break;
		}

		/*鼠标点击旧密码输入框*/
		if (*mx >= 250 && *mx <= 400 && *my >= 100 && *my <= 130 && buttons)judge = 0;

		/*鼠标点击新密码输入框*/
		if (*mx >= 250 && *mx <= 400 && *my >= 140 && *my <= 170 && buttons)judge = 1;

		/*鼠标点击第二次输入密码*/
		if (*mx >= 250 && *mx <= 400 && *my >= 200 && *my <= 230 && buttons)judge = 2;

		/*鼠标点击修改密码*/
		if (*mx >= 295 && *mx <= 345 && *my >= 250 && *my <= 280 && buttons)judge = 3;

		/*鼠标点击我的收藏区域*/
		if (*mx >= 20 && *mx <= 150 && *my >= 130 && *my <= 160 && buttons)return 2;

		/*鼠标点击意见反馈区域*/
		if (*mx >= 20 && *mx <= 150 && *my >= 160 && *my <= 190 && buttons)return 3;

		/*鼠标点击退出系统区域*/
		if (*mx >= 20 && *mx <= 150 && *my >= 190 && *my <= 220 && buttons)return 4;

		/*鼠标点击返回按键*/
		if (*mx >= 0 && *mx <= 20 && *my >= 0 && *my <= 20 && buttons)return 5;

		switch (judge)
		{
			/*旧密码输入*/
		case 0:
			judge = oldcodeinput(oldcode,mx,my);
			break;
			/*新密码输入*/
		case 1:
			judge = newcodeinput(newcode,mx,my);
			break;

			/*第二次输入密码*/
		case 2:
		    judge = secondcodeinput(secondcode,mx,my);
			break;

			/*确认修改*/
		case 3:
			/*密码不匹配*/
			if (strcmp(oldcode, (*person).code) != 0)
			{
				setfillstyle(1, WHITE);
				bar(410, 105, 510, 130);
				puthz(410, 105, "原密码不匹配！", 16, 16, RED);
			}
			
			/*新密码少于6位*/
			else if (strlen(newcode) < 6)
			{
				setfillstyle(1, WHITE);
				bar(410, 105, 510, 130);
				bar(410, 145, 510, 170);
				puthz(410, 145, "新密码少于6位！", 16, 16, RED);
			}
			/*两次密码输入不同*/
			else if (strcmp(newcode, secondcode) != 0)
			{
				setfillstyle(1, WHITE);
				bar(410, 105, 510, 130);
				bar(410, 145, 510, 170);
				bar(410, 205, 510, 230);
				puthz(410, 205, "两次密码不匹配！", 16, 16, RED);
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

		WarningTips("密码修改成功！", 260, 200, GREEN);
		//initgraph(&driver, &mode, "C:\\BORLANDC\\bgi");
		initgraph(&driver, &mode, "../BORLANDC\\bgi");
		cleardevice();
		return 0;
	}
}


/****************************************************
Function: user
Description: 用户界面后台函数
Attention:
Return:
****************************************************/
int user(char *symbol, setuser *person)
{
	int judge = 0;    //判断应该调用那些函数的变量
	int buttons, mx, my;   //鼠标参数变量
	
	/*画返回按钮防止鼠标残影*/
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

		/*鼠标点击修改密码区域*/
		if (mx >= 190 && mx <= 450 && my >= 100 && my <= 185 && buttons)judge = 1;

		/*鼠标点击我的收藏区域*/
		if (mx >= 190 && mx <= 450 && my >= 185 && my <= 270  && buttons)judge= 2;

		/*鼠标点击意见反馈区域*/
		if (mx >= 190 && mx <= 450 && my >= 270 && my <= 355 && buttons)judge = 3;

		/*鼠标点击退出系统区域*/
		if (mx >= 190 && mx <= 450 && my >= 355 && my <= 440 && buttons)judge = 4;

		/*鼠标点击返回按键*/
		if (mx >= 0 && mx <= 30 && my >= 0 && my <= 30 && buttons)judge = 5;

		switch (judge)
		{
			/*欢迎界面*/
		case 0:
			welcomeIF(person->accounts);
			mouseInit(&mx, &my, &buttons);
			judge = -1;
			break;
			/*修改密码*/
		case 1:
			changeCodeIF();
			judge = ChangeCode(person, &mx, &my);
			break;

			/*我的收藏*/
		case 2:
			showmyCollectIF();
			judge = showmyCollect(symbol, &(person->college), &mx, &my);

			break;

			/*意见反馈*/
		case 3:
			feedbackIF(); 
			judge = feedback();
			break;

			/*注销登录*/
		case 4:
			if (Choose("是否退出登陆？", &mx, &my, WHITE) == 0)judge = 0;
			else return 7;

			break;
			/*返回上一个界面*/ 
		case 5:
			return 1;
		case 6:
			judge = manageCollect(person, &mx, &my); 
			break;
		case 7: //从收藏进入大学 
			return 3;
		}
	}
}



/******************************
Function: welcomeIF
Description:个人界面的欢迎界面
Attention:
******************************/
void welcomeIF(char *accounts)
{
	int n = 0;

	cleardevice();

	setbkcolor(WHITE);
	setfillstyle(1, LIGHTGRAY);
	bar(0, 0, 30, 30);  //返回按钮
	setcolor(WHITE);
	line(5, 15, 25, 15);
	line(5, 15, 10, 20);
	line(5, 15, 10, 10);

	setfillstyle(1, LIGHTBLUE);
	bar(190,100,450,440);
	//画提示符号 
	setlinestyle(0,0,3);
	setcolor(WHITE);
	line(190,185,450,185);
	line(190,270,450,270);
	line(190,355,450,355);
	puthz(250, 130, "密码设置", 32, 32, WHITE);
	puthz(250, 210, "我的收藏", 32, 32, WHITE);
	puthz(250, 295, "意见反馈" ,32, 32, WHITE);
	puthz(250, 380, "退出登录", 32, 32, WHITE);
	puthz(190, 20, "您好，", 32, 32, LIGHTBLUE);
	settextstyle(0,0,4);
	setcolor(LIGHTBLUE);
	outtextxy(280,20,accounts);
	n = strlen(accounts);
	puthz(280+n*32, 20, "！", 32, 32, LIGHTBLUE);
}


/**************************
Function: changeCodeIF
Description:画更改密码界面
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
	puthz(304, 257, "确定", 16, 16, WHITE);
	puthz(60, 107, "密码设置", 16, 16, WHITE);
	puthz(60, 137, "我的收藏", 16, 16, WHITE);
	puthz(60, 167, "意见反馈", 16, 16, WHITE);
	puthz(60, 197, "退出登录", 16, 16, WHITE);

	setcolor(BLUE);
	rectangle(250, 100, 400, 130);
	rectangle(250, 140, 400, 170);
	rectangle(250, 200, 400, 230);
	puthz(180, 107, "当前密码", 16, 16, DARKGRAY);
	puthz(196, 147, "新密码", 16, 16, DARKGRAY);
	puthz(180, 207, "确认密码", 16, 16, DARKGRAY);
	puthz(250, 177, "由字母、数字组成的6到12位字符，区分大小写", 16, 16, BROWN);
}
/****************************************************
Function: feedback
Description: 提供用户可选择的反馈 
Attention:
Return:
****************************************************/
int feedback()
{	
	int buttons, mx, my;   //鼠标参数变量
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
		
		/*鼠标点击满意区域*/
		if (mx >= 140 && mx <= 220 && my >= 275 && my <= 320 && buttons)
		{
			AddFrame(mx, my, 140, 275, 220, 320,BLACK);
			fputs("good\n\0",fpp);
			fclose(fpp);
			return 0;
		}
		
		/*鼠标点击一般区域*/
		if (mx >= 330 && mx <= 410 && my >= 275 && my <= 320 && buttons)
		{
			AddFrame(mx, my, 330, 275, 410, 320,BLACK);
			fputs("just so so\n\0",fpp);
			fclose(fpp);
			return 0;
		}
	
		/*鼠标点击返回按键*/
		if (mx >= 0 && mx <= 30 && my >= 0 && my <= 30 && buttons)
		return 0;
	
		/*鼠标点击确定按键*/
		if (mx >= 270 && mx <= 350 && my >= 410 && my <= 455 && buttons) 
		return 0;
			
	}
} 
/****************************************************
Function: feedbackIF
Description: 画反馈界面 
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
	puthz(60 , 95,"您好，欢迎给我们提建议！", 48, 48, BLUE);
	
	bar(100, 180, 510, 240);
	puthz(120 , 192,"对软件整体使用感受如何？", 32, 32, WHITE);
	setfillstyle(1, LIGHTGRAY);
	bar(140, 275, 220, 320);
	bar(330, 275, 410, 320);	
	puthz(147, 282,"满意", 32, 32, GREEN);
	
	puthz(337, 282,"一般", 32, 32, RED);
	//确认按键 
	setfillstyle(1, LIGHTBLUE);
	bar(270,410,350,455); 
	puthz(278, 416, "确定", 32, 32, WHITE);
} 



