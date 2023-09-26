#include "functions.h"

// Global Variables
int tokenCount = 0;
int keywordCount = 0;
char *Keywords[] = {"accessor", "and", "array", "begin", "bool", "case", "character", "constant","else", "elsif", "end", "exit", "function",
"if", "in", "integer", "interface", "is", "loop", "module", "mutator", "natural", "null", "of", "or", "other", "out",
"positive", "procedure", "range", "return", "struct", "subtype", "then", "type", "when", "while"};
char *Operator[] = {".", "<", ">", "(", ")", "+", "-", "*","/","|", "&", ";", ",", ":", "[", "]", "=", ":=", "..","<<",">>","<>","<=",">=","**","!=","=>" }; 
char singleOperator[] = {'.', '<', '>', '(', ')', '+', '-', '*','/','|', '&', ';', ',', ':', '[', ']', '='}; 
bool isKeyword(char *s)
{
    for (int i = 0; i < 37; i++)
    {
       if(strcmp(s,Keywords[i]) == 0) {
        return true; 
       }
    }
    return false;
}
bool isOperator(char *s)
{
    for (int i = 0; i < 27; i++)
    {
       if(strcmp(s,Operator[i]) == 0) {
        return true; 
       }
    }
    return false;
}
bool isSingleOperator(char s)
{
    for (int i = 0; i < 17; i++)
    {
       if(s == singleOperator[i]) {
        return true; 
       }
    }
    return false;
}
/*
This function separates the Buffer into tokens...
*/
char **separateIntoTokens(char *s){
    char **array = malloc(sizeof(char *) * 2048);
    for (int k = 0; k < 2048; k++) {
        array[k] = malloc(sizeof(char *) * 2048);
    }
    int start = 0; 
    for(int i =0; i < strlen(s); i++) {
        if(s[i] == ' ' || s[i] == '\n' || isSingleOperator(s[i])) {
            for (int j = 0; j < i - start; j++) {
                array[tokenCount][j] = s[start + j]; 
            }
            if (array[tokenCount][0] != ' ' && array[tokenCount][0] != '\0') {
            tokenCount++;
            }
            start = i + 1; 
        }
        if(isSingleOperator(s[i])) {
                for (int j = 0; j < (i - start) - 1; j++) {
                array[tokenCount][j] = s[start + j]; 
            }
           
            if (array[tokenCount][0] != ' ' && array[tokenCount][0] != '\0') {
            tokenCount++;
            }
            array[tokenCount][0] = s[i]; 
            tokenCount++; 
           start = i + 1; 
    }
    }
    return array; 
}

void sort(char **s)
{
    for (int i = 0; i < tokenCount; i++)
    {
        if (isKeyword(s[i])) {
            strcat(s[i], " is a keyword");  
        }
        if (isOperator(s[i])) {
            strcat(s[i], " is an Operator");  
        }
    }
   
}

/*
This Function displays the program....
*/
void display(char **s)
{
    for (int i = 0; i < tokenCount; i++) // this is a test loop to display all the tokens
        printf("%s(%d)\n", s[i], i);
}

