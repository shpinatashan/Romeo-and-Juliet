//created by Natalia

#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <sys/stat.h>

const int ArrSize   = 53;
const int NotLetter = -2;
const int EndofStr  = -1;

void ReadPoem(int size , char buf[]);
long long int Count(char buf[], int size);
void Change(char buf[], int size, char* text[], char* textCOPY[]);
void OutputFile(char* arr[],long long int nlines);
int AlphEncoding(char chr);
const void Sort(char* arr[],long long int nlines);
int ComparatorStr(const void* ptr1,const void* ptr2);
int check(void* ptr);
char* Reverse(char* str1);
void Rhyme(char* textRhyme[], char* textCOPY[], long long int nlines);
void MyFree(char**  arr);
void MyFree(char*** arr);

#include "RaJ.cpp"
