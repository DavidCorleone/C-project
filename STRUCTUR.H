#ifndef _STRUCTUR_H
#define _STRUCTUR_H


/*收藏学校的结构体*/
typedef struct collect
{
	char name[50];
	char englishname[50];
	struct collect *next;
}setcollect;

/*用户型结构*/
typedef struct User
{
	char accounts[11];  //用户的账号
	char code[11];  //用户的密码 
	setcollect college;  //用户的所有路线头节点


	int mark_collect;  //标记用户是否对收藏链表操作的变量

	struct User *next;  //指向下一个用户的指针
}setuser;


/*筛选条件的结构体*/
typedef struct  Filter
{
	char chinesename[50];  //筛选条件的中文名字
	char englishname[50];  //筛选条件的英文缩写 
	char symbol[20];   //筛选条件的编码
	struct Filter *next;  //指向下一个筛选条件的指针
}setfilter;

/*存储学校路径的结构体*/
typedef struct collegepathlist
{
	char path[100];  //存储路径信息
	struct collegepathlist *next;
}setcollegepathList;

/*学校缩略版信息的结构体*/
typedef struct collegeList
{
	char chinesename[100];  //学校的中文名字
	char englishname[100];  //学校的英文名称缩写 
	char introduce[1000];  //简介 
	struct collegeList *next;   //指向下一个学校的指针
}setcollegeList;

/*存储路径的结构*/ 
typedef struct pathStack
{
	char path[100];  //存储学校对应的路径 
	//char symbol[10];   //学校的编码
	char chinesename[50]; //存储学校中文名称 
	char englishname[50]; // 存储学校英文名称 
	char filter_country[50];//存储以国家为筛选条件的编号 
	char filter_tuition[50]; //存储以学费区间为筛选条件的编号
	char filter_globalrank[50];  //存储以排名种类为筛选条件的编号 
	char filter_disciplinerank[50];//存储以学科种类为筛选条件的编号
	char filter_livingcost[100]; //存储以生活成本为筛选条件的编号
	char filter_gpa[50];  //存储以GPA区间为筛选条件的编号 
	struct pathStack *next;  //指向下一个路径的指针 
}setpath; 



/*学校详细信息结构体*/
typedef struct Collegeinformation
{
	char path[100];  //存储学校对应的路径 
	char chinesename[50];  //学校中文名称
	char englishname[50];  //学校英文名称
	char introduce[1000];  //此处为详情介绍 
	char country[10];//存储以国家为筛选条件的编号 
	char tuition[10]; //存储以学费区间为筛选条件的编号
	char globalrank[10];  //存储以排名种类为筛选条件的编号 
	char disciplinerank[10];//存储以学科种类为筛选条件的编号
	char livingcost[10]; //存储以生活成本为筛选条件的编号
	char gpa[10];  //存储以GPA区间为筛选条件的编号
	char livingmessage[1000];  //学校的详细信息->生活信息 
	char studyingmessage[1000];  //学校的详细信息-> 学习信息（留学建议+面试准备） 
}setcollege;


#endif
