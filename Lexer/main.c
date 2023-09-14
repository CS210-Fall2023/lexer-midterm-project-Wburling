#include <stdio.h>
#include "functions.h"

int main(int argc, char**argv) {
char* Buffer = malloc(sizeof(char) * 2048); 
char* fileName = argv[1]; 
FILE *targetFiles;
targetFiles = fopen(fileName, "r"); 
fread(Buffer, 1, 2048, targetFiles); 
// now we have to make a function to read through the file and find the operators... 
printf("%d", readAndSortOperators(Buffer)); 
}