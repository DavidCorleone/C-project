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


/**************************************************
Function: viewcollegeIntroduce
Description:ѧУ���ܽ���ĺ�̨����
Input:  ����symbol����englishname 
Attention:
Return:
***************************************************/
int viewcollegeIntroduce(char *symbol, const setpath *pathhead, setuser *person)
{ 
	int driver = VGA;
	int mode = VGAHI;
//	char *collegename = "C";
	char *chinesename = NULL;
	setcollege college;   //ѧУ��Ϣ�Ľṹ�� 
//	setcollect College;
	char *fileContent=NULL;
//	int flag = 0;  //�ж����Ӣ�������������� 
	int judge = 0;    //�ж�Ӧ�õ�����Щ�����ı���
	int buttons, mx, my;   //����������
//	int mark = 0;    //��ǵ�ǰ��ʾ���ǻ�����Ϣ������ϸ��Ϣ
//	int flag = 0;  //�жϸ�ѧУ�Ƿ��Ѿ��ղصı���,0��ʾδ�ղأ�1��ʾ���ղ�
	
	mouseInit(&mx, &my, &buttons); 


	TransferToPath(symbol, pathhead, college.path); //�ɲ���return 
	//getCollegename(symbol, college.chinesename, pathhead); //�˴�����õ�chinesename 

  //�������� 
	strcat(college.path, "detailed.txt");  //�޸� 
	if (ReadFile(college.path, &fileContent) == 1)  //�˺����������� 
	{
		
		WarningTips("��̨���ݲ����ڣ�", 260, 200, RED);
	/*	if(1)
					{
						closegraph();
						printf("Can't open %s", "helloworld");  //"FILES\\college\\mit"  test
						getchar();
						exit(1);  
					}
	*/
		//initgraph(&driver, &mode, "C:\\BORLANDC\\bgi");
		initgraph(&driver, &mode, "../BORLANDC\\bgi");
		cleardevice();
		return 1;
		
	}
	dealcollegeListFile(fileContent, &college);  //filecontentֵ���� 

	CollegeIF(college);
//	showname(college, &mx, &my, &flag);
	
	free(fileContent);
//	fileContent = NULL;
	//�ж��Ƿ��ղ� 
	//strcat()
	if(ifCollect(&(person->college), college.chinesename) == 0)
	{
/*		if(1)
	{
		closegraph();
		printf("Can't open %d", ifCollect(&(person->college), college.chinesename));  //"FILES\\college\\mit"  test
		getchar();
		getchar();
		exit(1);  
	}*/
		setfillstyle(1, WHITE); 
		bar(484, 289, 516, 321);
		setfillstyle(1,DARKGRAY);
		setcolor(DARKGRAY);	
		pieslice(516, 310, 0, 360, 36); 
		puthz(488, 305, "δ�ղ�", 16, 16, WHITE);
	} 
	else if(ifCollect(&(person->college), college.chinesename) == 1)
	{
		setfillstyle(1, WHITE);   
		bar(484, 289, 516, 321);
		setfillstyle(1,DARKGRAY);
		setcolor(DARKGRAY);
		pieslice(516, 310, 0, 360, 36); 
		puthz(488, 305, "���ղ�", 16, 16, WHITE);
	}

	college.path[0] = '\0';  //��ʼ�� 
	symbol = NULL;
	while (1)
	{
		newxy(&mx, &my, &buttons);

		/*�������һ����Բ���򣬱�ʾ�ղع���*/
		//��δ�ղأ����ղأ������ղأ���ɾ���ղ� 
		if (mx >= 478 && mx <= 550 && my >= 275 && my <= 350 && buttons)
		{
			if(ifCollect(&(person->college), college.chinesename) == 0)	
			{
				judge = 1;
			} 
			else
			{
				judge = 11;
			}
		} 
			
		/*������ڶ�����Բ����, ��ʾ������Ϣ*/
		if (mx >= 10 && mx <= 80 && my >= 159 && my <= 230&& buttons)
		{
		
			judge = 2;
			
		}
			
		/*�������������Բ���򣬱�ʾѧ����Ϣ*/
		if (mx >= 311 && mx <= 377 && my >= 16 && my <= 80&& buttons)
		{
		
			judge = 3;
			
		}
			
		/*��������ĸ���Բ���򣬱�ʾ������Ϣ*/
		if (mx >= 102 && mx <= 169 && my >= 290 && my <= 358&& buttons)
		{
		
			judge = 4;
			
		}
		/*������������Բ���򣬱�ʾרҵ������Ϣ*/
		if (mx >= 182 && mx <= 257 && my >= 401 && my <= 470&& buttons)
		{
		
			judge = 5;
			
		}
		/*�������������Բ���򣬱�ʾ����ɱ�*/
		if (mx >= 368 && mx <= 441 && my >= 368 && my <= 439&& buttons)
		{
		
			judge = 6;
			
		}
		/*��������߸���Բ���򣬱�ʾGPA*/
		if (mx >= 141 && mx <= 219 && my >= 53 && my <= 130&& buttons)
		{
		
			judge = 7;
			
		}
		/*������ڰ˸���Բ���򣬱�ʾ��ϸ��Ϣ������������Ϣ��ѧϰ��Ϣ��*/
		if (mx >= 506 && mx <= 585 && my >= 33 && my <= 110&& buttons)
		{
			judge = 8;	
		}
		
		/*����������������*/
		if (mx >= 0 && mx <= 30 && my >= 0 && my <= 30 && buttons)
			judge = 9;

		/*�����������������*/
		if (mx >= 570 && mx <= 640 && my >= 0 && my <= 30 && buttons)
			judge = 10;
		 
	
		switch (judge)
		{
			
		/*�ղظþ���*/
		case 1:
			setfillstyle(1, WHITE);
			collect(college.chinesename, college.englishname, person);  //�������ղأ� 
			bar(484, 289, 516, 321);
			setfillstyle(1,DARKGRAY);
			setcolor(DARKGRAY);
			pieslice(516, 310, 0, 360, 36); 
			puthz(488, 305, "���ղ�", 16, 16, WHITE);
			judge = 0; 
			//backgroundChange(mx, my, 484, 289, 516, 321);
			break;
	
		/*��ʾ������Ϣ*/
		case 2:
			setfillstyle(1, WHITE);
			bar(273, 220, 370, 250);
			puthz(304, 232, college.country, 16, 16, LIGHTGRAY);//�����ԭ���Ŀ�Ȼ�����college.country 
			judge = 0;
			break;

		/*��ʾѧ����Ϣ*/
		case 3:
			setfillstyle(1, WHITE);
			bar(273, 220, 370, 250);
			puthz(300, 232, college.tuition, 16, 16, CYAN);	
			judge = 0;
			break;

			
		/*��ʾ������Ϣ*/	
		case 4: 
			setfillstyle(1, WHITE);
			bar(273, 220, 370, 250);
			puthz(310, 232, college.globalrank, 16, 16, LIGHTRED);	
			judge = 0;
			break;

		/*��ʾѧ����Ϣ*/
		case 5: 
			setfillstyle(1, WHITE);
			bar(273, 220, 370, 250);
			puthz(310, 232, college.disciplinerank, 16, 16, YELLOW);	
			judge = 0;
			break;

		/*��ʾ����ɱ�*/
		case 6:
			setfillstyle(1, WHITE);
			bar(273, 220, 370, 250);
			puthz(300, 232, college.livingcost, 16, 16, LIGHTGREEN);	
			judge = 0;
			break;

		/*��ʾGPA*/
		case 7:
			setfillstyle(1, WHITE);
			bar(273, 220, 370, 250);
			puthz(300, 232, college.gpa, 16, 16, BROWN);	
			judge = 0;
			break;

		/*��ʾ��ϸ��Ϣ*/
		case 8:
			
			judge = showmessage(college);
			freecollege(&college);
			
			break;

		/*����*/ 
		case 9:
			freecollege(&college);
			return 1;  //������viewcollegeintroduce���� 
	
		/*��������*/
		case 10:	
			freecollege(&college);
			return 5;
		
		/*ȡ���ղ�*/ 
		case 11:
			deleteCollect(college.chinesename, &(person->college), person);
			setfillstyle(1, WHITE); 
			bar(484, 289, 516, 321);
			setfillstyle(1,DARKGRAY);
			setcolor(DARKGRAY);	
			pieslice(516, 310, 0, 360, 36); 
			puthz(488, 305, "δ�ղ�", 16, 16, WHITE);
			judge = 0;
			freecollege(&college);
			break;	
	
		}
	} 

}

/***********************************
Function: showname
Description:��ʾѧУ���Ƶĺ�����flagΪ�������Ӣ������ż��ʱ���� 
Attention:
Return:��
***********************************/
/*
void showname(setcollege college, int *mx, int *my, int *flag)
{
	int buttons;
	while (1)
	{
		//newxy(&mx, &my, &buttons);  

		//�������ʾѧУ���Ƶ�Բ 
		if (mx >= 270 && mx <= 190 && my >= 370 && my <= 290 && buttons)
		{
			if(*flag%2==0)
			{
				puthz(272, 232, college.chinesename, 16, 16, RED);
			}
			else
			{
				puthz(272, 232, college.englishname, 16, 16, RED);
				
			/*	if(1)
				{
					closegraph();
					printf("Can't open %s", college.englishname);  //"FILES\\college\\mit"  test
					getchar();
					exit(1);  
				}
			*/
/*			
		} 
			*flag++;	
		}
		else if(buttons)
		{
			return 0;
		}
		
 } 
} 
*/

/***********************************
Function: showmessage
Description:����ʾ����ѡ��ĺ��� 
Attention:��
Return:��
***********************************/
int showmessage(setcollege college)
{ 
	int buttons=0;
	int mx, my;
	showmessageIF();
	mouseInit(&mx, &my, &buttons); 
	while (1)
	{
		newxy(&mx, &my, &buttons);

		/*��ʾintroduce*/
		if (mx >= 31 && mx <= 160 && my >=31  && my <= 159 && buttons)
		{
			setfillstyle(1, WHITE); 
			bar(170, 30, 640, 480);
			puthz(180, 100, college.introduce, 16, 16, BROWN); 
		}
		/*��ѧ����*/ 
		if (mx >= 0 && mx <= 160 && my >= 160 && my <= 319 && buttons)
		{
			setfillstyle(1, WHITE); 
			bar(170, 30, 640, 480);
			puthz(180, 100, college.livingmessage, 16, 16, BROWN);
		}
		/*ʵ����Ϣ*/ 
		if (mx >= 0 && mx <= 160 && my >= 320 && my <= 480 && buttons)
		{
			setfillstyle(1, WHITE); 
			bar(170, 30, 640, 480);
 			puthz(180, 100, college.studyingmessage, 16, 16, BROWN); 
		}
		/*������ذ�ť*/
		if (mx >= 0 && mx <= 30 && my >= 0 && my <= 30 && buttons)
		{
			return 9;  //�˴����Կ��ǲ��ö�ջ 
		}
		/*�����������*/
		if (mx >= 570 && mx <= 640 && my >= 0 && my <= 30 && buttons)
		{
			return 10;		
		} 
		 
	}	
}

/***********************************
Function: showmessage
Description:�������Ϣѡ��Ļ�ͼ���� 
Attention:��
Return:��
***********************************/
void showmessageIF()
{
	cleardevice();
	setfillstyle(1, LIGHTGRAY);	//���ذ�ť
	bar(0, 0, 30, 30);  
	setcolor(WHITE);
	line(5, 15, 25, 15);
	line(5, 15, 10, 20);
	line(5, 15, 10, 10);
	setbkcolor(WHITE);	
	setlinestyle(0, 0, 3);
	setcolor(BLUE);
	line(160, 0, 160, 480);
	puthz(20, 70,"��ϸ����", 32, 32, BLUE);
	line(0, 160, 160, 160);
	puthz(20, 230,"������Ϣ", 32, 32, BLUE);
	puthz(20, 290,"������ͨ�������", 16, 16, CYAN); 
	line(0, 320, 160, 320);	
	puthz(20, 390,"ѧϰ��Ϣ", 32, 32, BLUE);
	puthz(20, 450,"����׼����ѧ����", 16, 16, CYAN); 
	setfillstyle(1, LIGHTGRAY);
	bar(570, 0, 640, 30);
	puthz(572, 6, "��������",16 ,16 ,WHITE);	
}

/***********************************
Function: 
Description:����
Attention:��
Return:��
***********************************/
void CollegeIF(setcollege college)
{
	cleardevice();
	setbkcolor(WHITE);
	setcolor(BLUE);
	setlinestyle(0, 0, 3);
	setfillstyle(1,BLUE);
	circle(320, 240, 58);
	puthz(275, 225, college.chinesename, 16, 16, RED);  //���� 

	setfillstyle(1, LIGHTGRAY);
	bar(0, 0, 30, 30);  //���ذ�ť
	setcolor(WHITE);
	line(5, 15, 25, 15);
	line(5, 15, 10, 20);
	line(5, 15, 10, 10);
	
	bar(570, 0, 640, 30);
	puthz(572, 6, "��������",16 ,16 ,WHITE);
	
	setlinestyle(0, 0, 1);
	
	setfillstyle(1,CYAN);
	setcolor(CYAN);
	pieslice(345, 46, 0, 360, 33);
	line(334, 182, 342, 78);
	puthz(329, 41, "ѧ��", 16, 16, WHITE);
	
	setfillstyle(1,BROWN);
    setcolor(BROWN);
	pieslice(180, 88, 0, 360, 38);
	line(276, 193, 206, 115);
	puthz(148, 83, "ƽ������", 16, 16, WHITE);
	
	setfillstyle(1,LIGHTGRAY);
	setcolor(LIGHTGRAY);
	pieslice(47, 192, 0, 360, 36);
	line(260, 225, 85, 198);
	puthz(31, 187, "����", 16, 16, WHITE);
	
	setfillstyle(1,LIGHTRED);
	setcolor(LIGHTRED);
	pieslice(135, 323, 0, 360, 35);
	line(259, 266, 174, 304);
	puthz(119, 318, "����", 16, 16, WHITE);
	
	setfillstyle(1,YELLOW);
	setcolor(YELLOW);
	pieslice(220, 437, 0, 360, 38);
	line(293, 297, 238, 401);
	puthz(188, 432, "רҵ����", 16, 16, WHITE);
	
	setfillstyle(1,LIGHTGREEN);
	setcolor(LIGHTGREEN);
	pieslice(405, 402, 0, 360, 37);
	line(356, 288, 389, 364);
	puthz(373, 397, "����ɱ�", 16, 16, WHITE);
	
	setfillstyle(1,DARKGRAY);
	setcolor(DARKGRAY);
	pieslice(516, 310, 0, 360, 36);
	line(383, 251, 474, 297);  //�ղذ�ť 

	setfillstyle(1,LIGHTCYAN);
	setcolor(LIGHTCYAN);
	pieslice(547, 69, 0, 360, 40);
	line(364, 200, 506, 95);
	puthz(515, 64, "��ϸ����", 16, 16, WHITE);
}