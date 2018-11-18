#ifndef _DEALFILE_H
#define _DEALFILE_H

#define  INIT_STRING_LENGTH  1000  //�ַ��������Ͻ�
#define  INCREMENT 100    //�ַ�����������

#include "structur.h"
void freecollege(setcollege *college);
int ReadFile( const char *path, char **fileContent);
void dealcollegeFile(char *fileContent, setcollegeList **temp);
void SearchPath(char *symbol, const setpath *pathhead, setcollegepathList **collegepathlisthead);
void dealcollegeListFile(char *fileContent, setcollege *temp);
int freecollegepathList(setcollegepathList **head);
int freefilterList(setfilter **head);
int freepathList(setpath **head);
int freecollegeList(setcollegeList **head);
int TransferToPath(char *symbol, const setpath *pathhead, char *collegepath);
void CreateCollegeList(char *fileContent, setcollegeList *head);
void CreateFilterList(setfilter *head);
#endif