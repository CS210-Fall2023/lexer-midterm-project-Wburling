#include "functions.h"

int readAndSortOperators(char* s) {
    int stringLength = strlen(s); 
    int functionCount = 0; 
    for (int i =0; i < stringLength; i ++) {
        if(s[i] == '(' || s[i] == ')') {
            functionCount++; 
        }
    }
    
    return functionCount; 
}