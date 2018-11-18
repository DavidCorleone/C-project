#include "dealfile.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<graphics.h>

/********************************************
Function: SearchPath
Description: 在文件内搜寻，将编码转化成相应信息的路径存储到链表 
Attention:头节点与尾节点不存有效数据 
Return:
********************************************/
void SearchPath(char *symbol, const setpath *pathhead, setcollegepathList **collegepathlisthead)
{
	char *p=symbol;	
	int i = 0;
	setpath *current;
	setcollegepathList *Current = NULL;
	if ((Current = (setcollegepathList *)malloc(sizeof(setcollegepathList))) == NULL)
		{
			closegraph();
			printf("Overflow!");
			//getchar();
			exit(1);
		}
	current = pathhead;
	Current = *collegepathlisthead;

	if ((Current->next = (setcollegepathList *)malloc(sizeof(setcollegepathList))) == NULL)
		{
			closegraph();
			printf("Overflow!");
			//getchar();
			exit(1);
		}	 

 
	Current = Current->next;   //不可删除 

	if( *p == 65)  //采用ascii码比较 
	{
		i=1;		
	}
	
	if( *p == 68)
	{
		i=2;		
	}
	if( *p == 69)
	{
		i=3;		
	}
	if( *p == 70)
	{
		i=4;		
	}
	switch(i)
	{	
		case 1:
		
			current = current->next;  //由于头节点不存储有效数据 ，所以指向下一节点 
			
			while(current->next != NULL)
			{
				
				if(!(strcmp(symbol,current->filter_country)))
				{
					strcpy(Current->path,current->path);
					strcat(Current->path, "simple.txt");
					if ((Current->next = (setcollegepathList *)malloc(sizeof(setcollegepathList))) == NULL)
					{
						closegraph();
						printf("Overflow!");
						//getchar();
						exit(1);
					}	 
					Current = Current->next;
				}
	
				current = current->next;			
			}
			Current->path[0] = '\0';
			Current->next=NULL;
			break;
	
		case 2:

			current = current->next;
		
			while(current->next != NULL)
			{
				if(!(strcmp(symbol,current->filter_gpa)))
				{
					strcpy(Current->path,current->path);
					strcat(Current->path, "simple.txt");
					if ((Current->next = (setcollegepathList *)malloc(sizeof(setcollegepathList))) == NULL)
					{
						closegraph();
						printf("Overflow!");
						//getchar();
						exit(1);
					}	 
					Current = Current->next;		
			} 
			current = current->next; 
			}
			Current->path[0] = '\0';
			Current->next=NULL;
			break;
		case 3:

			current = current->next;
			while(current->next != NULL)
			{	if(!(strcmp(symbol,current->filter_tuition)))
				{
					strcpy(Current->path,current->path);
					strcat(Current->path, "simple.txt");
					if ((Current->next = (setcollegepathList *)malloc(sizeof(setcollegepathList))) == NULL)
					{
						closegraph();
						printf("Overflow!");
						//getchar();
						exit(1);
					}	 
					Current = Current->next;		
			}
					current = current->next;			
			}
			Current->path[0] = '\0';
			Current->next=NULL;
			break;
		case 4:
		current = current->next;  //由于头节点不存储有效数据 ，所以指向下一节点 
			
			while(current->next != NULL)
			{
				
				if(!(strcmp(symbol,current->filter_livingcost)))
				{
					strcpy(Current->path,current->path);
					strcat(Current->path, "simple.txt");
					if ((Current->next = (setcollegepathList *)malloc(sizeof(setcollegepathList))) == NULL)
					{
						closegraph();
						printf("Overflow!");
						//getchar();
						exit(1);
					}	 
					Current = Current->next;
				}
	
				current = current->next;			
			}
			Current->path[0] = '\0';
			Current->next=NULL;
			break;
	
	}
	p = NULL;
}
	 



/********************************************
Function: TransferToPath  测试通过 
Description: 将学校名称转化成相应信息的路径
Attention:在search函数里面还会使用，因此需要返回值 
Return:   
********************************************/
void freecollege(setcollege *college)
{
	setcollege current = (*college);
	current.chinesename[0] = '\0';
	current.country[0] = '\0';
	current.disciplinerank[0] = '\0';
	current.englishname[0] = '\0';
	current.globalrank[0] = '\0';
	current.gpa[0] = '\0';
	current.introduce[0] = '\0';
	current.livingcost[0] = '\0';
	current.livingmessage[0] = '\0';
	current.path[0] = '\0';
	current.studyingmessage[0] = '\0';
	current.tuition[0] = '\0';
}


/********************************************
Function: TransferToPath  测试通过 
Description: 将学校名称转化成相应信息的路径
Attention:在search函数里面还会使用，因此需要返回值 
Return:   
********************************************/
int TransferToPath(char *symbol, const setpath *pathhead, char *collegepath)
{
//	char *p =symbol;
	setpath *current;
	current = pathhead;
	current = current->next;  //由于头节点不存储有效数据 ，所以指向下一节点 
	while(strcmp(current->englishname, symbol) !=0 && current !=NULL)
	{
		current = current->next;			
	}
	if(current->next == NULL)
	{
		return 0;  //显示找不到相应的路径 
	 } 
	else
	{
		strcpy(collegepath, current->path);
		
/*	if(1)
	{
		closegraph();
		printf("Can't open %s", symbol);  //"FILES\\college\\mit"  test
		printf("Can't open %s", collegepath); 
		getchar();
		exit(1);  
	}
*/
		//collegepath = current->path;
		return 1;
	 } 
	
		
}


/*****************************************************
Function: ReadFile
Description: 将文件内容读入字符串中
Attention:
Return:返回1表示无法打开相应的文件，返回0表示打开成功
*****************************************************/
int ReadFile(const char *path, char **fileContent)
{
	FILE *fp = NULL;
	char ch = '\0';
	char *p = NULL;
	int length = INIT_STRING_LENGTH;
	int add = 0;

/*  if(1)
	{	

				closegraph();
				print("readfile-w"); 
				printf("Can't open %s\n", path);  //"FILES\\college\\mit"  test
				//getchar();
				exit(1);  
		}
*/	
	if ((*fileContent = (char *)malloc(INIT_STRING_LENGTH)) == NULL)
	{
		closegraph();
		printf("Overflow!");
		//getchar();
		exit(1);
	}

	p = *fileContent;
	if ((fp = fopen(path, "r+")) == NULL)
	{
		
		closegraph();
		printf("readasdafile-W\n");
		printf("Can't open %s\n", path);
		//getchar();
		exit(1);
	/*	free(*fileContent);
		*fileContent = NULL;
		return 1;
	*/ 
	}

	while (!feof(fp))
	{
		add = p - *fileContent;
		if ((add + 8)>length)
		{

			length += INCREMENT;
			if ((*fileContent = realloc(*fileContent, length)) == NULL)
			{
				closegraph();
				printf("\nOverflow");
				//getchar();
				exit(1);
			}
			else p = *fileContent + add;
		}

		ch = fgetc(fp);
		*p = ch;
		p++;
		*p = NULL;
	}
	*(p - 1) = NULL;
	fclose(fp);
	return 0;
}

/*************************************************************
Function: dealcollegeListFile
Description:处理学校缩略文件的函数
Attention:1、文件必须按要求格式化书写
          2、生成链表的头节点是空的，后面的节点都存有有效数据
          3、temp表示暂存文件内容 ，由于c语言没有引用的概念，因此需要** 
          4.此函数名称有问题 
Return:
**************************************************************/
void dealcollegeListFile(char *fileContent, setcollege *temp)
{
	
	int mark;  //字符接收传递的开关
	int i=0;    //记录次数的标志，用于switch判断 
	char *s = NULL;   //将文本字符串内容存入current里的指针
	while (*fileContent != '\0')
	{
		

		/*识别到#符号表示开始一段有效数据的复制*/
		if (*fileContent == '#')
		{
			mark = 1;
			i++;
			switch (i)
			{
				case 1:
					s = temp->chinesename;
					break;
				case 2:
					s = temp->englishname;
					break;
				case 3:
					 s = temp->introduce;
					break;
				case 4:
					s = temp->country;
					break;
					
				case 5:
					s = temp->tuition;
					break;
					
				case 6:
					s = temp->globalrank;
					break;
					
				case 7:
					s = temp->disciplinerank;
					break;
				case 8:
					s = temp->livingcost;
					break;
				case 9:
					s = temp->gpa;
					break;
				case 10:
					s = temp->livingmessage;
					break;
				case 11:
					s = temp->studyingmessage;
					break;
					 
				
				default:
					closegraph();  //文件内容超出 
					printf("Wrong in dealcollegeListFile!");
					//getchar();
					exit(1);
			}
			fileContent++;
			continue;
		}

		/*识别到*符号表示结束一段有效数据的复制并禁止复制*/
		if (*fileContent == '*')
		{
			mark = 0;
			*s = NULL;
			fileContent++;
			continue;
		}

		if (mark == 1)
		{
			*s = *fileContent;
			s++;
			*s = '\0';
		}

		fileContent++;
	}	
	
}




/*************************************************************
Function: dealcollegeFile
Description:处理学校缩略文件的函数
Attention:1、文件必须按要求格式化书写
          2、生成链表的头节点是空的，后面的节点都存有有效数据
          3、temp表示暂存文件内容 ，由于c语言没有引用的概念，因此需要** 
Return:
**************************************************************/
void dealcollegeFile(char *fileContent, setcollegeList **temp)
{
	
	int mark = 0;  //字符接收传递的开关
//	char *p = NULL;   //传递文本字符串的指针
	int i=0;    //记录次数的标志，用于switch判断 

	char *s = NULL;   //将文本字符串内容存入current里的指针

	setcollegeList *current=NULL;   //当前节点的指针

	if ((*temp = (setcollegeList *)malloc(sizeof(setcollegeList))) == NULL)
	{
		closegraph();
		printf("Overflow!");
		//getchar();
		exit(1);
	}
	(*temp)->next = NULL;

	/*初始化过程*/
//	p = fileContent;
	current = *temp;


	while (*fileContent != '\0')
	{
		

		/*识别到#符号表示开始一段有效数据的复制*/
		if (*fileContent == '#')
		{
			mark = 1;
			i++;
			switch (i)
			{
				case 1:
					s = current->chinesename;
					break;
				case 2:
					s = current->englishname;
					break;
				case 3:
					 s = current->introduce;
					break; 
				default:
					closegraph();
					printf("Wrong in dealcollegeFile!");
					//getchar();
					exit(1);
			}
			fileContent++;
			continue;
		}

		/*识别到*符号表示结束一段有效数据的复制并禁止复制*/
		if (*fileContent == '*')
		{
			mark = 0;
			*s = NULL;
			fileContent++;
			continue;
		}

		if (mark == 1)
		{
			*s = *fileContent;
			s++;
			*s = '\0';
		}

		fileContent++;
	}	
	/*	if(1)
	{
		closegraph();
		printf("Can't open %s", (*temp)->introduce);  //"FILES\\college\\mit"  test
		//getchar();
		exit(1);  
	}
	*/
}


/***********************************************
Function: freecollegeList
Description:释放链表的内存空间并将头指针置为NULL
Attention:文件必须按要求格式化书写
Return:
************************************************/
int freepathList(setpath **head)
{
	setpath *previous = *head;
	setpath *current = (*head)->next;

	if (*head == NULL)return 0;

	while (current != NULL)
	{
		free(previous);
		previous = current;
		current = current->next;
	}
	free(previous);
	*head = NULL;
	return 0;
}

/***********************************************
Function: freecollegepathList
Description:释放链表的内存空间并将头指针置为NULL
Attention:文件必须按要求格式化书写
Return:
************************************************/
int freecollegepathList(setcollegepathList **head)
{
	setcollegepathList *previous = *head;
	setcollegepathList *current = (*head)->next;

	if (*head == NULL)return 0;

	while (current != NULL)
	{
		free(previous);
		previous = current;
		current = current->next;
	}
	free(previous);
	*head = NULL;

	return 0;
}


/***********************************************
Function: freecollegeList
Description:释放collegeListHead链表的内存空间并将头指针置为NULL
Attention:文件必须按要求格式化书写
Return:
************************************************/
int freefilterList(setfilter **head)
{
	setfilter *previous = *head;
	setfilter *current = (*head)->next;

	if (*head == NULL)return 0;

	while (current != NULL)
	{
		free(previous);
		previous = current;
		current = current->next;
	}
	free(previous);
	*head = NULL;

	return 0;
	
}

/***********************************************
Function: freecollegeList
Description:释放collegeListHead链表的内存空间并将头指针置为NULL
Attention:文件必须按要求格式化书写
Return:
************************************************/
int freecollegeList(setcollegeList **head)
{
	setcollegeList *previous = *head;
	setcollegeList *current = (*head)->next;

	if (*head == NULL)return 0;

	while (current != NULL)
	{
		free(previous);
		previous = current;
		current = current->next;
	}
	free(previous);
	*head = NULL;
	return 0;
}


/**************************************************************
Function: CreateFilterList
Description: 根据filter.txt文件中的信息创建筛选条件链表
Attention: 1、传递过来的头指针一定要有确定的指向！
           2、若filter.txt文件被清空，要在其开头用记事本加上#号才能正常创建链表！
           3、创建的链表的开头与末尾节点都不存有效数据！
Return:无返回值
***************************************************************/
void CreateFilterList(setfilter *head)
{
	setfilter *current = NULL;  //指向当前结点的指针变量
	FILE *fp = NULL;    //用于打开college.txt的文件指针
	char ch;    //用于接收并传送文件内部字符的中间变量
	char *p = NULL;   //指向需要接收字符的地址的指针变量


	/*必要的初始化过程*/
	head->chinesename[0] = '\0';
	head->englishname[0] = '\0';
	head->symbol[0] = '\0';
	current = head;
	p = current->chinesename;

	/*if ((fp = fopen("C:\\.txt", "r+")) == NULL)
	{
		closegraph();
		printf("Can't open college.txt");
		//getchar();
		exit(1);
	}*/
	if ((fp = fopen("C:\\test\\FILES\\filter\\filter.txt", "r+")) == NULL)
	{
		closegraph();
		printf("Can't open filter.txt");
		//getchar();
		exit(1);
	}


	while (!feof(fp))
	{
		ch = fgetc(fp);    //从.txt文件中提取一个字符

		if (ch == '#')    //表示汉字的开始，编号的结束
		{
			/*向系统申请空间*/
			if ((current->next = (setfilter *)malloc(sizeof(setfilter))) == NULL)
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
			p = current->symbol;
		}
	
		else if(ch!='\n')      
		{
			*p = ch;
			p++;
		}
	}
}
/**************************************************************
Function: CreateCollegeList
Description: 1、创建的链表的开头与末尾节点都不存有效数据！
***************************************************************/
void CreateCollegeList(char *fileContent, setcollegeList *head)
{
//	int i = 0;  //用于记第几次遇到#符号
//	int mark = 0;    //字符接收传递的开关
	char *p = NULL;   //传递文本字符串的指针
//	char *s = NULL;   //将文本字符串内容存入current里的指针
	setcollegeList *current=NULL;   //当前节点的指针

	/*必要的初始化过程*/
	head->chinesename[0] = '\0';
	head->englishname[0] = '\0';
	head->introduce[0] = '\0';
	current = head;

	p = current->chinesename;
	
	while (*fileContent != '\0')
	{
	
		if (*fileContent == '#')    //表示汉字的开始，编号的结束
		{
			/*向系统申请空间*/
			if ((current->next = (setcollegeList *)malloc(sizeof(setcollegeList))) == NULL)
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
		else if (*fileContent == '*')      //表示汉字的结束，拼音的小写缩写的开始
		{
			*p = '\0';
			p = current->englishname;
		}
		else if(*fileContent == '/')
		{	
			*p = '\0';
			p = current->introduce;
			
		}
		else if(*fileContent !='\n')      
		{
			*p = *fileContent;
			p++;
		}
		
		fileContent++;
	}
	if ((current->next = (setcollegeList *)malloc(sizeof(setcollegeList))) == NULL)	
		{
			closegraph();	
			printf("\nOverflow");
			//getchar();
			exit(1);
		}
	current = current->next;
	current->chinesename[0] = '\0';
	current->englishname[0] = '\0';
	current->introduce[0] = '\0';
	current->next = NULL;
	
}



