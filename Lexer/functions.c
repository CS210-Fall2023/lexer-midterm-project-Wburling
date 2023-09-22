#include "functions.h"

// Global Variables
int tokenCount = 0;
int keywordCount = 0;
char *Keywords[] = {"accessor", "and", "array", "begin", "bool", "case", "character"};

/*
char** separateIntoTokens(char* s) {
    char**arrayOfStrings = malloc(sizeof(char*) * 2048);
    for (int i = 0; i < 2048; i++) {
        arrayOfStrings[i] = malloc(sizeof(char) * 2048);
    }
    int stringLength = strlen(s) + 1;
    int start = 0;
    int end = start;

    for (int i =0; i < stringLength + 2; i ++) {
       if((s[i] == ' ' && s[i + 1] != ' ' )|| s[i] == '\n') {
        end = i;
        int totalTokenLength = (end - start);// + 1;
        for(int t = 0; t < totalTokenLength; t++) {
            arrayOfStrings[tokenCount][t] = s[start + t];

        }
        if((arrayOfStrings[tokenCount][0] != ' ' && arrayOfStrings[tokenCount][1] != ' ') && arrayOfStrings[tokenCount][0] != '\n')
        tokenCount++;
        start = end + 1;
       }

    }

    // at this point in the program all the stuff is sorted into tokens....
//     for (int i =0; i < tokenCount; i++) // this is a test loop to display all the tokens
//    printf("%s(%d) ", arrayOfStrings[i], i);
return arrayOfStrings;
}
*/

// Old function didnt use the strcpy function but it worked... I rewrote it to make it smaller

/*
This function separates the Buffer into tokens...
*/
char **separateIntoTokens(char *s)
{
    char **array = malloc(sizeof(char *) * 2048);
    int totalStringChar = strlen(s); // total file length
    int start = 0;
    int end = start;
    for (int m = 0; m < 2048; m++)
    {
        array[m] = malloc(sizeof(char *) * 2048);
    }

    for (int i = 0; i < totalStringChar; i++)
    {

        if (s[i] == ' ' || s[i] == '\n' || s[i] == '\0')
        {
            end = i;
            strncpy(array[tokenCount], s + start, end - start);
            array[tokenCount][i] = '\0'; 
            if(array[tokenCount][0] != '\0')
            tokenCount++;
        }
    
            for (int y = 0; y < 2048; y++)
            {
                if (s[end + y] != ' ')
                {
                    start = end + y;
                    break;
                }
            }
    }

    return array;
}

void sort(char **s)
{
    for (int i = 0; i < tokenCount; i++)
    {
        if (isKeyword(s[i]))
            keywordCount++;
    }
    printf("%d is how many keywords are in your file", keywordCount); // now write code to actually display this information in the display function....
}

/*
This Function displays the program....
*/
void display(char **s)
{
    for (int i = 0; i < tokenCount; i++) // this is a test loop to display all the tokens
        printf("%s(%d) ", s[i], i);
}

bool isKeyword(char *s)
{
    for (int i = 0; i < 7; i++)
    {
       if(strcmp(s,Keywords[i]) == 0) {
        return true; 
       }
    }
    return false;
}