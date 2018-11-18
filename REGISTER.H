#ifndef  _REGISTER_H
#define  _REGISTER_H

#include<stdio.h>
#include "user.h"

#include"STRUCTUR.H"
int userRegister(setuser *head, char *accounts, char *code);
void RegisterIF();
void drawRedFork(int x, int y);
void drawGreenHook(int x, int y);

#endif
