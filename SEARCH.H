#ifndef _SEARCH_H
#define _SEARCH_H

#include "structur.h"

void sortglobalrank(setpath **head);
int search(const setpath *pathlisthead, char *symbol);
void searchIF();
int showdisciplinerank(char *symbol,const setpath *pathhead);
int showFilter(char *symbol, int *mx, int *my);
int showglobalrank(char *symbol, setpath *pathhead);
int  showPossible(char *abbreviation, int *mx, int *my, setpath *pathhead, char *symbol);
void sortdisciplinerank(setpath *head)
#endif
