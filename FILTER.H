#ifndef _FILTER_H
#define _FILTER_H

#include "dealfile.h"
#include "user.h"
#include "STRUCTUR.H"
int collegeGuide(char *symbol, const setfilter *filterhead, setuser *person, const setpath *pathhead);
void CreateFilterList(setfilter *head);
void CreatePathList(setpath *head);
void drawTransferPage(void);
void filterGuideIF(char *filtername, char *englishname);
void getCollegename(const char *abbreviation, char *chinesename, const setpath *pathlisthead);
void getFiltername(char *chinesename, char *englishname, char *symbol, const setfilter *head);
int showCollegeList(setcollegeList *collegelisthead, char *symbol, int *mx, int *my);



#endif
