#include "dealfile.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<graphics.h>

/********************************************
Function: SearchPath
Description: ���ļ�����Ѱ��������ת������Ӧ��Ϣ��·���洢������ 
Attention:ͷ�ڵ���β�ڵ㲻����Ч���� 
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

 
	Current = Current->next;   //����ɾ�� 

	if( *p == 65)  //����ascii��Ƚ� 
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
		
			current = current->next;  //����ͷ�ڵ㲻�洢��Ч���� ������ָ����һ�ڵ� 
			
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
		current = current->next;  //����ͷ�ڵ㲻�洢��Ч���� ������ָ����һ�ڵ� 
			
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
Function: TransferToPath  ����ͨ�� 
Description: ��ѧУ����ת������Ӧ��Ϣ��·��
Attention:��search�������滹��ʹ�ã������Ҫ����ֵ 
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
Function: TransferToPath  ����ͨ�� 
Description: ��ѧУ����ת������Ӧ��Ϣ��·��
Attention:��search�������滹��ʹ�ã������Ҫ����ֵ 
Return:   
********************************************/
int TransferToPath(char *symbol, const setpath *pathhead, char *collegepath)
{
//	char *p =symbol;
	setpath *current;
	current = pathhead;
	current = current->next;  //����ͷ�ڵ㲻�洢��Ч���� ������ָ����һ�ڵ� 
	while(strcmp(current->englishname, symbol) !=0 && current !=NULL)
	{
		current = current->next;			
	}
	if(current->next == NULL)
	{
		return 0;  //��ʾ�Ҳ�����Ӧ��·�� 
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
Description: ���ļ����ݶ����ַ�����
Attention:
Return:����1��ʾ�޷�����Ӧ���ļ�������0��ʾ�򿪳ɹ�
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
Description:����ѧУ�����ļ��ĺ���
Attention:1���ļ����밴Ҫ���ʽ����д
          2������������ͷ�ڵ��ǿյģ�����Ľڵ㶼������Ч����
          3��temp��ʾ�ݴ��ļ����� ������c����û�����õĸ�������Ҫ** 
          4.�˺������������� 
Return:
**************************************************************/
void dealcollegeListFile(char *fileContent, setcollege *temp)
{
	
	int mark;  //�ַ����մ��ݵĿ���
	int i=0;    //��¼�����ı�־������switch�ж� 
	char *s = NULL;   //���ı��ַ������ݴ���current���ָ��
	while (*fileContent != '\0')
	{
		

		/*ʶ��#���ű�ʾ��ʼһ����Ч���ݵĸ���*/
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
					closegraph();  //�ļ����ݳ��� 
					printf("Wrong in dealcollegeListFile!");
					//getchar();
					exit(1);
			}
			fileContent++;
			continue;
		}

		/*ʶ��*���ű�ʾ����һ����Ч���ݵĸ��Ʋ���ֹ����*/
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
Description:����ѧУ�����ļ��ĺ���
Attention:1���ļ����밴Ҫ���ʽ����д
          2������������ͷ�ڵ��ǿյģ�����Ľڵ㶼������Ч����
          3��temp��ʾ�ݴ��ļ����� ������c����û�����õĸ�������Ҫ** 
Return:
**************************************************************/
void dealcollegeFile(char *fileContent, setcollegeList **temp)
{
	
	int mark = 0;  //�ַ����մ��ݵĿ���
//	char *p = NULL;   //�����ı��ַ�����ָ��
	int i=0;    //��¼�����ı�־������switch�ж� 

	char *s = NULL;   //���ı��ַ������ݴ���current���ָ��

	setcollegeList *current=NULL;   //��ǰ�ڵ��ָ��

	if ((*temp = (setcollegeList *)malloc(sizeof(setcollegeList))) == NULL)
	{
		closegraph();
		printf("Overflow!");
		//getchar();
		exit(1);
	}
	(*temp)->next = NULL;

	/*��ʼ������*/
//	p = fileContent;
	current = *temp;


	while (*fileContent != '\0')
	{
		

		/*ʶ��#���ű�ʾ��ʼһ����Ч���ݵĸ���*/
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

		/*ʶ��*���ű�ʾ����һ����Ч���ݵĸ��Ʋ���ֹ����*/
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
Description:�ͷ��������ڴ�ռ䲢��ͷָ����ΪNULL
Attention:�ļ����밴Ҫ���ʽ����д
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
Description:�ͷ��������ڴ�ռ䲢��ͷָ����ΪNULL
Attention:�ļ����밴Ҫ���ʽ����д
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
Description:�ͷ�collegeListHead�������ڴ�ռ䲢��ͷָ����ΪNULL
Attention:�ļ����밴Ҫ���ʽ����д
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
Description:�ͷ�collegeListHead�������ڴ�ռ䲢��ͷָ����ΪNULL
Attention:�ļ����밴Ҫ���ʽ����д
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
Description: ����filter.txt�ļ��е���Ϣ����ɸѡ��������
Attention: 1�����ݹ�����ͷָ��һ��Ҫ��ȷ����ָ��
           2����filter.txt�ļ�����գ�Ҫ���俪ͷ�ü��±�����#�Ų�����������������
           3�������������Ŀ�ͷ��ĩβ�ڵ㶼������Ч���ݣ�
Return:�޷���ֵ
***************************************************************/
void CreateFilterList(setfilter *head)
{
	setfilter *current = NULL;  //ָ��ǰ����ָ�����
	FILE *fp = NULL;    //���ڴ�college.txt���ļ�ָ��
	char ch;    //���ڽ��ղ������ļ��ڲ��ַ����м����
	char *p = NULL;   //ָ����Ҫ�����ַ��ĵ�ַ��ָ�����


	/*��Ҫ�ĳ�ʼ������*/
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
		ch = fgetc(fp);    //��.txt�ļ�����ȡһ���ַ�

		if (ch == '#')    //��ʾ���ֵĿ�ʼ����ŵĽ���
		{
			/*��ϵͳ����ռ�*/
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
		else if (ch == '*')      //��ʾ���ֵĽ�����ƴ����Сд��д�Ŀ�ʼ
		{
			*p = '\0';
			p = current->englishname;
		}
		else if (ch == '/')      //��ʾƴ���Թ���Ϊɸѡ�����ı��
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
Description: 1�������������Ŀ�ͷ��ĩβ�ڵ㶼������Ч���ݣ�
***************************************************************/
void CreateCollegeList(char *fileContent, setcollegeList *head)
{
//	int i = 0;  //���ڼǵڼ�������#����
//	int mark = 0;    //�ַ����մ��ݵĿ���
	char *p = NULL;   //�����ı��ַ�����ָ��
//	char *s = NULL;   //���ı��ַ������ݴ���current���ָ��
	setcollegeList *current=NULL;   //��ǰ�ڵ��ָ��

	/*��Ҫ�ĳ�ʼ������*/
	head->chinesename[0] = '\0';
	head->englishname[0] = '\0';
	head->introduce[0] = '\0';
	current = head;

	p = current->chinesename;
	
	while (*fileContent != '\0')
	{
	
		if (*fileContent == '#')    //��ʾ���ֵĿ�ʼ����ŵĽ���
		{
			/*��ϵͳ����ռ�*/
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
		else if (*fileContent == '*')      //��ʾ���ֵĽ�����ƴ����Сд��д�Ŀ�ʼ
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


