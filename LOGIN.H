#ifndef  _LOGIN_H
#define _LOGIN_H

#include<stdio.h>
#include "user.h"
#include"STRUCTUR.H"
int LoginaccountsInput(char *accounts, int *mx, int *my);
int LogincodeInput(char *code, int *mx, int *my);
int userLogin(setuser *head, char *accounts, char *code);
void LoginIF();
int noticeIF();

#endif
