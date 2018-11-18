#ifndef _COLLECT_H
#define _COLLECT_H


#include "structur.h"

int showmyCollect(char *symbol, setcollect *college, int *mx, int *my);
void collect(char *name, char *englishname, setuser *person);
void deleteCollect(char *name, setcollect *head, setuser *person);
int ifCollect(setcollect *head, char *name);
void freecollectList(setuser *person);
void RewriteCollectFile(setuser *person);
int manageCollectIF(char *name, int *mx, int *my, setcollect *college);
int manageCollect(setuser *person, int *mx, int *my);
void drawDeletebutton(int x, int y);
void showmyCollectIF();

#endif
