#ifndef _STRUCTUR_H
#define _STRUCTUR_H


/*�ղ�ѧУ�Ľṹ��*/
typedef struct collect
{
	char name[50];
	char englishname[50];
	struct collect *next;
}setcollect;

/*�û��ͽṹ*/
typedef struct User
{
	char accounts[11];  //�û����˺�
	char code[11];  //�û������� 
	setcollect college;  //�û�������·��ͷ�ڵ�


	int mark_collect;  //����û��Ƿ���ղ����������ı���

	struct User *next;  //ָ����һ���û���ָ��
}setuser;


/*ɸѡ�����Ľṹ��*/
typedef struct  Filter
{
	char chinesename[50];  //ɸѡ��������������
	char englishname[50];  //ɸѡ������Ӣ����д 
	char symbol[20];   //ɸѡ�����ı���
	struct Filter *next;  //ָ����һ��ɸѡ������ָ��
}setfilter;

/*�洢ѧУ·���Ľṹ��*/
typedef struct collegepathlist
{
	char path[100];  //�洢·����Ϣ
	struct collegepathlist *next;
}setcollegepathList;

/*ѧУ���԰���Ϣ�Ľṹ��*/
typedef struct collegeList
{
	char chinesename[100];  //ѧУ����������
	char englishname[100];  //ѧУ��Ӣ��������д 
	char introduce[1000];  //��� 
	struct collegeList *next;   //ָ����һ��ѧУ��ָ��
}setcollegeList;

/*�洢·���Ľṹ*/ 
typedef struct pathStack
{
	char path[100];  //�洢ѧУ��Ӧ��·�� 
	//char symbol[10];   //ѧУ�ı���
	char chinesename[50]; //�洢ѧУ�������� 
	char englishname[50]; // �洢ѧУӢ������ 
	char filter_country[50];//�洢�Թ���Ϊɸѡ�����ı�� 
	char filter_tuition[50]; //�洢��ѧ������Ϊɸѡ�����ı��
	char filter_globalrank[50];  //�洢����������Ϊɸѡ�����ı�� 
	char filter_disciplinerank[50];//�洢��ѧ������Ϊɸѡ�����ı��
	char filter_livingcost[100]; //�洢������ɱ�Ϊɸѡ�����ı��
	char filter_gpa[50];  //�洢��GPA����Ϊɸѡ�����ı�� 
	struct pathStack *next;  //ָ����һ��·����ָ�� 
}setpath; 



/*ѧУ��ϸ��Ϣ�ṹ��*/
typedef struct Collegeinformation
{
	char path[100];  //�洢ѧУ��Ӧ��·�� 
	char chinesename[50];  //ѧУ��������
	char englishname[50];  //ѧУӢ������
	char introduce[1000];  //�˴�Ϊ������� 
	char country[10];//�洢�Թ���Ϊɸѡ�����ı�� 
	char tuition[10]; //�洢��ѧ������Ϊɸѡ�����ı��
	char globalrank[10];  //�洢����������Ϊɸѡ�����ı�� 
	char disciplinerank[10];//�洢��ѧ������Ϊɸѡ�����ı��
	char livingcost[10]; //�洢������ɱ�Ϊɸѡ�����ı��
	char gpa[10];  //�洢��GPA����Ϊɸѡ�����ı��
	char livingmessage[1000];  //ѧУ����ϸ��Ϣ->������Ϣ 
	char studyingmessage[1000];  //ѧУ����ϸ��Ϣ-> ѧϰ��Ϣ����ѧ����+����׼���� 
}setcollege;


#endif