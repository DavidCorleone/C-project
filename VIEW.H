#ifndef  _VIEW_H
#define  _VIEW_H
#include "structur.h"
#include "dealfile.h"
#include "user.h"

int viewcollegeIntroduce(char *symbol, const setpath *pathhead, setuser *person);
int showmessage(setcollege college/*, int *mx, int *my*/);
void showlivingmessage(setcollege college);
void showintroducemessage(setcollege college);
void CollegeIF();
void showmessageIF();
void showname(setcollege college, int *mx, int *my, int *flag);
void showstudyingmessage(setcollege college);

#endif
