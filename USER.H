#ifndef  _USER_H
#define  _USER_H

#include "structur.h"




void CreateUserList(setuser *head);
void freeUserlist(setuser **head);
void AddNewUser(setuser *head, char *s1, char *s2);
char *SearchAccounts(setuser *head, char *string);
int ChangeCode(setuser *person, int *mx, int *my);
void changeCodeIF();
int user(char *symbol, setuser *person);
void welcomeIF(char *accounts);
int feedback();
void UserInit(setuser *person);
void feedbackIF();



#endif