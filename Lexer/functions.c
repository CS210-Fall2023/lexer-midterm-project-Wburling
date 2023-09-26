#include "functions.h"

// Global Variables
int tokenCount = 0;
int keywordCount = 0;
char *Keywords[] = {"accessor", "and", "array", "begin", "bool", "case", "character", "constant", "else", "elsif", "end", "exit", "function",
                    "if", "in", "integer", "interface", "is", "loop", "module", "mutator", "natural", "null", "of", "or", "other", "out",
                    "positive", "procedure", "range", "return", "struct", "subtype", "then", "type", "when", "while"};
char *Operator[] = {".", "<", ">", "(", ")", "+", "-", "*", "/", "|", "&", ";", ",", ":", "[", "]", "=", ":=", "..", "<<", ">>", "<>", "<=", ">=", "**", "!=", "=>"};
char singleOperator[] = {'.', '<', '>', '(', ')', '+', '-', '*', '/', '|', '&', ';', ',', ':', '[', ']', '='};
char *Comments[] = {"/*", "*/"};

bool isComment(char *s)
{
    for (int i = 0; i < 2; i++)
    {
        if (strcmp(s, Comments[i]) == 0)
        {
            return true;
        }
    }
    return false;
}
bool isKeyword(char *s)
{
    for (int i = 0; i < 37; i++)
    {
        if (strcmp(s, Keywords[i]) == 0)
        {
            return true;
        }
    }
    return false;
}
bool isOperator(char *s)
{
    for (int i = 0; i < 27; i++)
    {
        if (strcmp(s, Operator[i]) == 0)
        {
            return true;
        }
    }
    return false;
}
bool isSingleOperator(char s)
{
    for (int i = 0; i < 17; i++)
    {
        if (s == singleOperator[i])
        {
            return true;
        }
    }
    return false;
}
/*
This function separates the Buffer into tokens...
*/
char **separateIntoTokens(char *s)
{
    char **array = malloc(sizeof(char *) * 2048);
    for (int k = 0; k < 2048; k++)
    {
        array[k] = malloc(sizeof(char *) * 2048);
    }
    int start = 0;
    for (int i = 0; i < strlen(s); i++)
    {
        if (s[i] == ' ' || s[i] == '\n' || isSingleOperator(s[i]))
        {
            for (int j = 0; j < i - start; j++)
            {
                array[tokenCount][j] = s[start + j];
            }
            if (array[tokenCount][0] != ' ' && array[tokenCount][0] != '\0')
            {
                tokenCount++;
            }
            start = i + 1;
        }
        /*
        This function is called when a case such as = or * is found. 
        */
        if (isSingleOperator(s[i]) && isSingleOperator(s[i + 1]) == false)
        {
            for (int j = 0; j < (i - start) - 1; j++)
            {
                array[tokenCount][j] = s[start + j];
            }

            if (array[tokenCount][0] != ' ' && array[tokenCount][0] != '\0')
            {
                tokenCount++;
            }
            array[tokenCount][0] = s[i];
            tokenCount++;
            start = i + 1;
        }
        /*
        This function is called when a case has 2 operators together that make an operator.  
        */
        if (isSingleOperator(s[i]) && isSingleOperator(s[i + 1]))
        {
            bool isComment = false; 
            start = i; 
            // if its a comment
            for(int test = start; test < 2048; test++) {
                if(s[test] == '*' && s[test + 1] == '/') {
                i = test + 1; 
                isComment = true; 
                break; 
                }
            }
            // if its a normal double operator
            
             for (int j = 0; j < (i - start) - 1; j++)
            {
                array[tokenCount][j] = s[start + j];
            }

            if (array[tokenCount][0] != ' ' && array[tokenCount][0] != '\0')
            {
                tokenCount++;
            }
            
            start = i + 1;
        }

    }
    return array;
}

/*
    This function sorts out the words of the document scanned...
*/
void sort(char **s)
{
    for (int i = 0; i < tokenCount; i++)
    {
        if (isKeyword(s[i]))
        {
            strcat(s[i], " (Keyword)");
        }
        else if (isOperator(s[i]))
        {
            strcat(s[i], " (Operator)");
        }
        else if (s[i][0] == '/' && s[i][1] == '*') {
            strcat(s[i], " (Comment)");
        }
        else
        {
            strcat(s[i], " (Identifer)");
        }
    }
}

/*
This Function displays the program....
*/
void display(char **s)
{
    for (int i = 0; i < tokenCount; i++) // this is a test loop to display all the tokens
        printf("%s\n", s[i]);
}
