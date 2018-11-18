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
Description:���˵������µ���������ĺ�̨����
Attention:
Return:
********************************************/
int search(const setpath *pathlisthead, char *symbol)
{

	int judge = 0;    //�ж�Ӧ�õ���Щ�����ı���
	int temp;    //�������ռ��̻������ı���
	int buttons, mx, my;   //����������
	char abbreviation[50]= {'\0'};    //ѧУ��д,�����������ڡ��˴�ֻ���������� 
 	buttons = 0; 
	 /*��Ҫ�ĳ�ʼ������*/
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

		/*���ռ��̻�����������*/
		if (kbhit() != 0)
		{
			temp = bioskey(0);
		}
		/*����������Զ���ֵjudge=3��������������ж�*/ 
		if(judge == 5)
		{
			return 6;    //showdisciplinerank
		} 
		if(judge == 6)
		{
			return 8;  //Show_globalrank
		}
		if (mx >= 125 && mx <= 425 && my >= 410 && my <= 450 && buttons)judge = 1;/*���������������*/
		if (mx >= 425 && mx <= 475 && my >= 410 && my <= 450 && buttons)judge = 2;/*�����������ť����*/
		if (mx >= 81 && mx <= 560 && my >= 60 && my <= 110)judge = 3;/*����Ƶ�ɸѡ������*/
	
		if (mx >=561 && mx <=640 && my >=0 && my <=40 && buttons)return 5; /*�����������������*/ 
		if (mx>= 0 && mx<= 80 && my >=0&& my<= 40 && buttons)return 7; //�����quit���� 
		if(mx>= 460 && mx<= 559 && my >=0&& my<= 40 && buttons)return 2;//������߼�ɸѡ 
		switch (judge)
		{
			/*����������򣬵�����ƴ���뺯��*/
		case 1:
			judge=searchInput(abbreviation,&mx,&my);
			break;

			/*�����������ť*/
		case 2:
			judge = showPossible(abbreviation, &mx, &my, pathlisthead, symbol);   //����possible��ַ������Ӧ�Ŀ�
			break;

			/*������Ӧ����Ϣ��*/
		case 3:
			judge = showFilter(symbol, &mx, &my);
			break;
		
		case 4: 
			return 4;
		case 20:
			return 3;//�����򷵻�judge = 5����viewcollege 
	
		case 15:
			return 1;//���������հ״��ػ�search 
			}	
		
	}
}

/*********************************************
Function: showPossible
Description: ��ʾ��������ĺ���
Attention:����������궼û�и� 
Return:���ص���viewcollegeintroduce�����������Ҫ����symbol 
*********************************************/
int  showPossible(char *abbreviation, int *mx, int *my, setpath *pathhead, char *symbol)
{
//	void *buffer = NULL;    //ָ��洢�������ڴ��ָ��
//	unsigned int size;    //�������ڴ�����ռ�Ĵ�С
	int buttons = 0;    //���Ĳ�������
	char *collegepath; //Ϊ�˷���TransferToPath����ʽ��ûʲô�� 
	char *chinesename;  //�洢ת����������������ڴ�ӡ 
//	const char *temp = abbreviation;  //�ݴ�abbreviation 
	if (TransferToPath(abbreviation, pathhead, collegepath)==0)
	{
		/*��ȡ����������*/
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
		/*��ʾ�Ҳ������ѧУ*/
	//	setfillstyle(1, LIGHTGRAY);           
	//	bar(240, 58, 480, 83);
		puthz(125, 380, "�Ҳ������ѧУ��", 16, 16, RED);
		return 15;
	}

	/*��ȡ����������*/
	/*size = imagesize(240, 58, 480, 83);
	if ((buffer = malloc(size)) == NULL)
	{
		closegraph();
		printf("Overflow!");
		getchar();
		exit(1);
	}
	getimage(240, 58, 480, 83, buffer);*/

	/*��ӡ���ܵ�ѧУ����*/
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
		/*�������Ƶ�ѡ������ʹѡ������߿���*/
		if(*mx >= 125 && *mx <= 250 && *my >= 375  && *my <= 405)
		{
			AddFrame(*mx, *my, 125, 375, 250, 405, RED);

			/*������°������ı�symbol���ݣ�����4��ʾ��search�����е��ù���4*/
			if (buttons)
			{	
			//	strcpy(symbol, abbreviation);
			//	free(buffer);  //�ͷ�bufferָ����ڴ�ռ�
				return 20;  //�������������viewcollegeintroduce���� 
			}
		}
		else AddFrame(*mx, *my, 125, 375, 250, 405, LIGHTGRAY);



		/*�������������޹��ܵ������£�����0���˳���ǰ����*/
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
Description:��������ĺ���
Attention:��
Return:��
*****************************/
void searchIF()
{
	/* 
	int graphdriver=VGA;
	int graphmode=2;
	initgraph(&graphdriver, &graphmode, "c://borlandc//bgi");
	*/
	cleardevice();
	setbkcolor(WHITE);  //�Ȼ��˳���������� 
	setcolor(BLACK);
	setlinestyle(0, 0, 2); 
	setfillstyle(1, BLUE);
	bar(0, 0, 80, 40);
	bar(560, 0, 639, 40);
	rectangle(0, 0, 80, 40);
	rectangle(560, 0, 639, 40);
	setfillstyle(1, BROWN); 
	bar(460, 0, 559, 40);
	puthz(470, 10,"�߼�ɸѡ", 16, 16, WHITE);
	
	setcolor(LIGHTGRAY);  //��ɸѡ����
	setlinestyle(0, 0, 1);
	setfillstyle(1, WHITE);
	bar(81, 60, 560, 110);
	rectangle(81, 60, 560, 110);
	line(160, 60, 160, 110);
	line(240, 60, 240, 110);
	line(320, 60, 320, 110);
	line(400, 60, 400, 110);
	line(480, 60, 480, 110);
	
	setcolor(RED);  //���������� 
	setlinestyle(0, 0, 2);
	setfillstyle(1, WHITE);
	bar(125, 410, 425, 450);
	rectangle(125, 410, 475, 450);
	setfillstyle(1, BROWN);
	bar(425, 410, 475, 450);
	
	puthz(435, 420, "����", 16, 16, BLACK);   //��������ƵĻ����ʾ�ַ� 
	puthz(570, 10, "��������", 16, 16, BLACK);
	puthz(20, 10, "quit", 16, 16, BLACK);
	puthz(104, 77, "����", 16, 16, RED);
	puthz(168, 77, "��������", 16, 16, RED);  //QS���� 
	puthz(248, 77, "�Զ�������", 16, 16, RED);  //�Զ���רҵ���� 
	puthz(336, 77, "GPA", 16, 16, RED);
	puthz(424, 77, "ѧ��", 16, 16, RED);
	puthz(488, 77, "����ɱ�", 16, 16, RED); 
}




/******************************
Function: showglobalrank 
Description: ��ʾ�����ĺ���
Attention:�ı�symbol��ֵ����ѧУ��Ӣ�����Ƹ���symbol 
Return:���ѡ���4,��ת��main��������collegeintroduce���� 
*******************************/
int showglobalrank(char *symbol,const setpath *pathhead)
{
	char Symbol[50][50];  //���ڴ洢�õ���symbolֵ 
	int i;
	int buttons = 0;
	int mx, my;
	setpath *current = pathhead;  //����������ĳһ��Ԫ�ؽ���������㷨
//	Symbol[0] = NULL;
	
	cleardevice();
	setbkcolor(WHITE);
	//���ذ�ť
	setfillstyle(1, LIGHTGRAY);
	bar(0, 0, 30, 30);  
	setcolor(WHITE);
	line(5, 15, 25, 15);
	line(5, 15, 10, 20);
	line(5, 15, 10, 10);
	setcolor(BLUE);
	setfillstyle(1, BLUE);
	//��top������ 
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
	//����̨ 
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
	
	for(i=0; current!=NULL; i++)  //������ѭ�����,Ҳ����ֱ��puthz 
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
	}  Symbol[i]û���� 
*/	
	if(mx >= 390 && mx <= 550 && my >= 60  && my <= 94&&buttons)  //�����������ѧУ���ƣ��͸ı�symbol��ֵ��������������  
	{
		strcpy(symbol, Symbol[0]);  //��һ��ѧУ 
		memset(Symbol,0,sizeof(Symbol));
		return 3;
	}  

	
	if(mx >= 390&& mx <= 550 && my >= 96  && my <= 130&&buttons)  //�����������ѧУ���ƣ��͸ı�symbol��ֵ��������������  
	{
			
		strcpy(symbol, Symbol[1]);
		memset(Symbol,0,sizeof(Symbol));
		return 3;
	} 

	if(mx >= 390 && mx <= 550 && my >= 132  && my <= 136&&buttons)  //�����������ѧУ���ƣ��͸ı�symbol��ֵ��������������  
	{
		
		strcpy(symbol, Symbol[2]);
			memset(Symbol,0,sizeof(Symbol));
		return 3;
	} 
	
	if(mx >= 390 && mx <= 550 && my >= 138  && my <= 172&&buttons)  //�����������ѧУ���ƣ��͸ı�symbol��ֵ��������������  
	{
		
		strcpy(symbol, Symbol[3]);
			memset(Symbol,0,sizeof(Symbol));
		return 3;
	} 
	
	if(mx >= 390 && mx <= 550 && my >= 174  && my <= 208&&buttons)  //�����������ѧУ���ƣ��͸ı�symbol��ֵ��������������  
	{
		
		strcpy(symbol, Symbol[4]);
			memset(Symbol,0,sizeof(Symbol));
		return 3;
	} 
	
	if(mx >= 390 && mx <= 550 && my >= 210  && my <= 244&&buttons)  //�����������ѧУ���ƣ��͸ı�symbol��ֵ��������������  
	{
		
		strcpy(symbol, Symbol[5]);
			memset(Symbol,0,sizeof(Symbol));
		return 3;
	} 
	 
	 if(mx >= 390 && mx <= 550 && my >= 246  && my <= 280&&buttons)  //�����������ѧУ���ƣ��͸ı�symbol��ֵ��������������  
	{
		
		strcpy(symbol, Symbol[6]);
			memset(Symbol,0,sizeof(Symbol));
		return 3;
	} 
	
	if(mx >= 390 && mx <= 550 && my >= 282  && my <= 316&&buttons)  //�����������ѧУ���ƣ��͸ı�symbol��ֵ��������������  
	{
		
		strcpy(symbol, Symbol[7]);
			memset(Symbol,0,sizeof(Symbol));
		return 3;
	} 
	
	if(mx >= 390 && mx <= 550 && my >= 318  && my <= 354&&buttons)  //�����������ѧУ���ƣ��͸ı�symbol��ֵ��������������  
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
Description: ��ʾ�����ĺ���
Attention:�ı�symbol��ֵ 
Return:���ѡ���
*******************************/
void sortglobalrank(setpath *head)   //����������ѧУ������������ 
{
	setpath *p, *prep, *temp, *tail;

	tail = NULL;

// �㷨�ĺ��Ĳ���
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
            // �ڵ����
            p = p->next;
            prep = prep->next;
        }
        tail = p;
    }// ��һ��while
}

/******************************
Function: showdisciplinerank
Description: ��ʾ�����ĺ���
Attention:�ı�symbol��ֵ����ѧУ��Ӣ�����Ƹ���symbol 
Return:���ѡ���4,��ת��main��������collegeintroduce���� 
*******************************/
int showdisciplinerank(char *symbol, const setpath *pathhead)
{
	
	int i;
	char Symbol[50][50];  //���ڴ洢�õ���symbolֵ 
	int buttons, mx, my;
	setpath *current = pathhead;  //����������ĳһ��Ԫ�ؽ���������㷨 
//	Symbol[0] = NULL;
	/*��Ҫ�ĳ�ʼ������*/
	mouseInit(&mx, &my, &buttons); 
//	puthz(200, 200, p, 16, 16, RED); //test
	cleardevice();
	setbkcolor(WHITE);
	//���ذ�ť
	setfillstyle(1, LIGHTGRAY);
	bar(0, 0, 30, 30);  
	setcolor(WHITE);
	line(5, 15, 25, 15);
	line(5, 15, 10, 20);
	line(5, 15, 10, 10);
	setcolor(BLUE);
	setfillstyle(1, BLUE);
	//��top������ 
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
	//����̨ 
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
	
	for(i=0; current!=NULL ; i++)  //������ѭ�����,Ҳ����ֱ��puthz 
	{


		outtextxy(346, 60+35*i, current->filter_disciplinerank);
		puthz(390, 60+35*i, current->chinesename, 32, 32, BROWN);
		strcpy(Symbol[i], current->englishname);   //����symbol��0��==NULL; 
		current = current->next;
	}
	
	if(mx >= 390 && mx <= 550 && my >= 60  && my <= 94&&buttons)  //�����������ѧУ���ƣ��͸ı�symbol��ֵ��������������  
	{
		strcpy(symbol, Symbol[0]);
			memset(Symbol,0,sizeof(Symbol));
		//symbol = Symbol[0];
		return 3;
	}  

	
	if(mx >= 390 && mx <= 550 && my >= 96  && my <= 130&&buttons)  //�����������ѧУ���ƣ��͸ı�symbol��ֵ��������������  
	{
			
		strcpy(symbol, Symbol[1]);
			memset(Symbol,0,sizeof(Symbol));
			//symbol = Symbol[1];
			return 3;
	} 

	if(mx >= 390 && mx <= 550 && my >= 132  && my <= 136&&buttons)  //�����������ѧУ���ƣ��͸ı�symbol��ֵ��������������  
	{
		strcpy(symbol, Symbol[2]);
			memset(Symbol,0,sizeof(Symbol));
			//symbol = Symbol[2];
			return 3;
	} 
	
	if(mx >= 390 && mx <= 550 && my >= 138  && my <= 172&&buttons)  //�����������ѧУ���ƣ��͸ı�symbol��ֵ��������������  
	{
		
	strcpy(symbol, Symbol[3]);
		memset(Symbol,0,sizeof(Symbol));
			//symbol = Symbol[3];
			return 3;
	} 
	
	if(mx >= 390 && mx <= 550 && my >= 174  && my <= 208&&buttons)  //�����������ѧУ���ƣ��͸ı�symbol��ֵ��������������  
	{
		strcpy(symbol, Symbol[4]);
			memset(Symbol,0,sizeof(Symbol));
			//symbol = Symbol[4];
			return 3;
	} 
	
	if(mx >= 390 && mx <= 550 && my >= 210  && my <= 244&&buttons)  //�����������ѧУ���ƣ��͸ı�symbol��ֵ��������������  
	{
		
		strcpy(symbol, Symbol[5]);
			memset(Symbol,0,sizeof(Symbol));
			//symbol = Symbol[5];
			return 3;
	} 
	 
	 if(mx >= 390 && mx <= 550 && my >= 246  && my <= 280&&buttons)  //�����������ѧУ���ƣ��͸ı�symbol��ֵ��������������  
	{
		
		strcpy(symbol, Symbol[6]);
			memset(Symbol,0,sizeof(Symbol));
			//symbol = Symbol[6];
			return 3;
	} 
	
	if(mx >= 390 && mx <= 550 && my >= 282  && my <= 316&&buttons)  //�����������ѧУ���ƣ��͸ı�symbol��ֵ��������������  
	{
		
	strcpy(symbol, Symbol[7]);
		memset(Symbol,0,sizeof(Symbol));

			//symbol = Symbol[7];
			return 3;
	} 
	
	if(mx >= 390 && mx <= 550 && my >= 318  && my <= 354&&buttons)  //�����������ѧУ���ƣ��͸ı�symbol��ֵ��������������  
	{
		
		strcpy(symbol, Symbol[8]);
			memset(Symbol,0,sizeof(Symbol));
		return 3;
	} 
	if (mx >= 0 && mx <= 30 && my >= 0 && my <= 30 && buttons)
	{
		memset(Symbol,0,sizeof(Symbol));  //����������� 
		return 1;  //����search����	
		
	}
}
	
	
}

/******************************
Function: sortdisciplinerank
Description: ��ʾ�����ĺ���
Attention: 
Return:���ѡ���
*******************************/
void sortdisciplinerank(setpath *head)
{
	setpath *f, *p, *x, *y;
	f = NULL;
	//�ж��Ƿ�ֻ��һ��Ԫ�ػ���û��Ԫ��
	if(head->next == NULL || head->next->next == NULL)
	{
		return 0;
	}
	while(f != head->next->next)
	{
		//�����N - 1��ѭ��,����
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
Description: ��ʾ�����ĺ���
Attention:�����ͬɸѡ�����еĲ�ͬѡ����ز�ͬ��symbol 
Return:���ѡ���4
*******************************/
int showFilter(char *symbol, int *mx, int *my)
{
	int buttons = 0;    //���Ĳ�������
	int judge = 0;
	setfillstyle(1, WHITE);
	setcolor(RED);
	while (1)
	{
		newxy(mx, my, &buttons);

		/*����ڵ�һ�����Ϸ�*/
		if (judge!=1&&*mx >= 81 && *mx <= 160 && *my >= 60 && *my <= 110)
		{
			
			bar(81, 110, 560, 370);
			rectangle(81, 110, 560, 370);
			puthz(100, 150, "����", 16, 16, RED);
			puthz(180, 150, "Ӣ��", 16, 16, RED);
			puthz(260, 150, "�¹�", 16, 16, RED);
			puthz(340, 150, "�ձ�", 16, 16, RED);
			//puthz(420, 150, "�¼���", 16, 16, RED);
			//puthz(500, 150, "�Ĵ�����", 16, 16, RED);
			judge = 1;
		}
		/*����ڵڶ������Ϸ�*/
		if (judge != 2 && *mx >= 160 && *mx <= 240 && *my >= 60 && *my <= 110 && buttons)
		{
			judge = 2;
			//return 5;   
		}

		/*����ڵ��������Ϸ�*/
		if (judge != 3 && *mx >= 240 && *mx <= 320 && *my >= 60 && *my <= 110 &&buttons)
		{
			judge = 3;
		}
		
		/*����ڵ��ĸ����Ϸ�*/
		if (judge != 4 && *mx >= 320 && *mx <= 400 && *my >= 60 && *my <= 110)
		{
			
			bar(81, 110, 560, 370);
			rectangle(81, 110, 560, 370);
			puthz(100, 150, "�����㼰����", 16, 16, RED);
			puthz(220, 150, "�����㵽������", 16, 16, RED);
			puthz(356, 150, "�����嵽�ĵ���", 16, 16, RED);
			judge = 4;
		}
	
		/*����ڵ�������Ϸ�*/
		if (judge != 5 && *mx >= 400 && *mx <= 480 && *my >= 60 && *my <= 110)
		{
			bar(81, 110, 560, 370);
			rectangle(81, 110, 560, 370);
			puthz(100, 150, "1����Ԫ����", 16, 16, RED);
			puthz(230, 150, "1��2����Ԫ", 16, 16, RED);
			puthz(366, 150, "2����Ԫ����", 16, 16, RED);
			judge = 5;
		}
	
		/*����ڵ��������Ϸ�*/ 
		if (judge != 6 && *mx >= 480 && *mx <= 560 && *my >= 60 && *my <= 110)
		{
			bar(81, 110, 560, 370);
			rectangle(81, 110, 560, 370);
			puthz(100, 150, "1000��Ԫ", 16, 16, RED);
			puthz(220, 150, "1000��1500��Ԫ", 16, 16, RED);
			puthz(420, 150, "1500��Ԫ����", 16, 16, RED);
			judge = 6;
		} 
		//����겻��ɸѡ��ʱ
		if (*mx < 81 || *mx > 560 || *my < 60 || *my > 370)
		{
			setfillstyle(1, WHITE);
			bar(81, 110, 560, 370);
			rectangle(81, 110, 560, 370);
			puthz(193,192,"�𾴵���ͨ�û���", 32, 32, RED); 
			puthz(118, 306, "��ӭ����������ѧ��ѯϵͳ��", 32, 32, RED);
			return 0;
		}
		
 		/*��ʾ��һ������ʱ*/ 
		 //��search����Ĺ�����college������ת����ͬɸѡ��ʽ��Ӧ�ĺ�����ͬ  
		if (judge == 1)
		{
			if (*mx >= 90 && *mx <= 140 && *my >= 140 && *my <= 160 && buttons)
			{
				strcpy(symbol, "A01"); //���� 
				return 4;

			}
			if (*mx >= 170 && *mx <= 220 && *my >= 140 && *my <= 160 && buttons)
			{
				strcpy(symbol, "A02"); //Ӣ�� 
				return 4;
			}
			if (*mx >= 250 && *mx <= 280 && *my >= 140 && *my <= 160 && buttons)
			{
				strcpy(symbol, "A03"); //�¹�
				return 4;
			}
				if (*mx >= 330 && *mx <= 360 && *my >= 140 && *my <= 160 && buttons)
			{
				strcpy(symbol, "A04"); //�ձ�
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
				strcpy(symbol, "D01");//�����㼰����
				return 4;

			}
			if (*mx >= 210 && *mx <= 320 && *my >= 140 && *my <= 160 && buttons)
			{
				strcpy(symbol, "D02");// �����㵽������
				return 4;
			}
			if (*mx >= 340 && *mx <= 450 && *my >= 140 && *my <= 160 && buttons)
			{
				strcpy(symbol, "D03");// �����嵽�ĵ���
				return 4;
			}
			
		}
		if (judge == 5)
		{
			if (*mx >= 90 && *mx <= 180 && *my >= 140 && *my <= 160 && buttons)
			{
				strcpy(symbol, "E01");//1����Ԫ����
				return 4;

			}
			if (*mx >= 210 && *mx <= 320 && *my >= 140 && *my <= 160 && buttons)
			{
				strcpy(symbol, "E02");// 1��2����Ԫ
				return 4;
			}
			if (*mx >= 340 && *mx <= 450 && *my >= 140 && *my <= 160 && buttons)
			{
				strcpy(symbol, "E03");// 2����Ԫ����
				return 4;
			}
		}
		if (judge == 6)
		{
			if (*mx >= 90 && *mx <= 180 && *my >= 140 && *my <= 160 && buttons)
			{
				strcpy(symbol, "F01");//1000��Ԫ
				return 4;

			}
			if (*mx >= 210 && *mx <= 390 && *my >= 140 && *my <= 160 && buttons)
			{
				strcpy(symbol, "F02");// 1000��1500��Ԫ
				return 4;
			}
			if (*mx >= 410 && *mx <= 550 && *my >= 140 && *my <= 160 && buttons)
			{
				strcpy(symbol, "F03");// 1500��Ԫ����
				return 4;
			}
		}
	}
}




