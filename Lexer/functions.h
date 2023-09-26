#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef int bool;
#define true 1
#define false 0


char** separateIntoTokens(char* s); 
void sort(char** s);
void display(char** s); 
bool isKeyword(char* s);
bool isOperator(char *s);
bool isDoubleOperator(char *s);
bool isSingleOperator(char s);

#endif 