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
bool isString(char s) {
    if(s == '\"') {
        return true;
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
    int plusForString = 0; 
    for (int i = 0; i < strlen(s); i++)
    {
       if (s[i] == ' ' || s[i] == '\n' || isSingleOperator(s[i]) || isString((s[i])))
        {
            if(isString(s[i]))
            plusForString = -1; 
            for (int j = 0; j < i - start + plusForString; j++)
            {
                array[tokenCount][j] = s[start + j];
            }
            if (array[tokenCount][0] != ' ' && array[tokenCount][0] != '\0')
            {
                tokenCount++;
            }
            start = i + 1;
            plusForString = 0; 
        }

         if (s[i] == '\"')
        {
            int h = i + 1;
            while(s[h] != '\"')
            h++; 
            for (int j = 0; j < h - i + 1; j++)
            {
                array[tokenCount][j] = s[i + j];
            }
            tokenCount++;
            i = h + 1;
            start = i;
        }
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
        else if (isSingleOperator(s[i]) && isSingleOperator(s[i + 1]))
        {
            start = i;
            if (s[i] == '/' && s[i + 1] == '*')
            {
                // if its a comment
                for (int test = start; test < 2048; test++)
                {
                    if (s[test] == '*' && s[test + 1] == '/')
                    {
                        for (int j = 0; j < (test - start) + 2; j++)
                        {
                            array[tokenCount][j] = s[start + j];
                        }
                        if (array[tokenCount][0] != ' ' && array[tokenCount][0] != '\0')
                        {
                            tokenCount++;
                        }
                        i = test + 3;
                        start = i;
                        break;
                    }
                }
                // if its a normal double operator
            }
            else
            {
                for (int j = 0; j < 2; j++)
                {
                    array[tokenCount][j] = s[start + j];
                }

                if (array[tokenCount][0] != ' ' && array[tokenCount][0] != '\0')
                {
                    tokenCount++;
                }
                i += 1;
                start = i + 2;
            }
        }

       
        /*
        This function is called when a case such as = or * is found.
        */
       
        /*
        This function is called when a case has 2 operators together that make an operator.
        */
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
            strcat(s[i], " (keyword)");
        }
        else if (isOperator(s[i]))
        {
            strcat(s[i], " (operator)");
        }
        else if (s[i][0] == '/' && s[i][1] == '*')
        {
            strcat(s[i], " (comment)");
        }
        else if (s[i][0] == '\"')
        {
            strcat(s[i], " (string)");
        }
        else
        {
            strcat(s[i], " (identifier)");
        }
    }
}

/*
This Function displays the program....
*/
void display(char **s, FILE *file)
{
    for (int i = 0; i < tokenCount; i++)
    { // this is a test loop to display all the tokens
        //fprintf(stdout, "%s\n", s[i]);
        fprintf(file, "%s\n", s[i]);
    }
}