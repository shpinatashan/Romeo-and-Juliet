//created by Natalia
#define INPUTFILE 1

#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <dos.h>
#include <windows.h>
#include <stdlib.h>
#include <math.h>
#include <sys/stat.h>
using namespace std;

struct stat st = {};

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
void MyFree(char** arr);
void MyFree(char*** arr);

int main()
{
stat("RaJ.txt", &st);
int size = st.st_size +1;
char * buf = (char*) calloc(size, sizeof(char));

if (check(buf) == -1) return -1;

FILE* f2 = fopen("res.txt", "w");

if (f2 == NULL)
    {
        printf("Cannot open file");
    }
fclose(f2);

ReadPoem(size, buf);
long long int nlines = Count(buf, size);

printf("size %d \n", size);
printf("Nlines %ld\n", nlines);


char** text      = (char**)calloc(nlines,sizeof(char*));
char** textCOPY  = (char**)calloc(nlines,sizeof(char*));
char** textCorr  = (char**)calloc(nlines,sizeof(char*));
char** textRhyme = (char**)calloc(nlines,sizeof(char*));

if (check(text)      == -1) return -1;
if (check(textCOPY)  == -1) return -1;
if (check(textRhyme) == -1) return -1;
if (check(textCorr)  == -1) return -1;


Change(buf, size, text, textCOPY);
Sort(text, nlines);
Rhyme(textRhyme, textCOPY, nlines);
Sort (textRhyme, nlines);
Rhyme(textCorr, textRhyme, nlines);

OutputFile(text, nlines);
OutputFile(textCorr, nlines);
OutputFile(textCOPY, nlines);

printf("~meow~");

MyFree(&text);
MyFree(&textCOPY);
MyFree(&textRhyme);
MyFree(&buf);
MyFree(&textCorr);

return 0;
}

void MyFree(char*** arr)
{
    free(*arr);
    *arr = NULL;
}
void MyFree(char** arr)
{
    free(*arr);
    *arr = NULL;
}
int check(void* ptr)
{
    if (ptr == NULL)
     {
        printf ("error with ptr(array)");
        return -1;
     }
}

void ReadPoem(int size , char buf[])
{
    check(buf);
    FILE* onegin = fopen("RaJ.txt", "r");

    if (onegin == NULL)
    {
        printf("Cannot open file");
        return;
    }

    fread(buf, sizeof(char), size,onegin);
    buf [size] = '\n';
    fclose(onegin);
}
long long int Count(char buf[], int size)
{
    check(buf);
    long long int nlines = 1;

        for (int i = 0; i < size; i++)
    {
        if (buf[i] == '\n')
        {
            nlines++;
        }
    }

    return nlines;
}

void Change(char buf[], int size, char* text[], char* textCOPY[])
{
    check(buf);
    check(text);
    check(textCOPY);
    long long int nlines = 0;
    int n = 1;
    text[0] = &buf[0];
    textCOPY[0] = &buf[0];
    for (int i = 0; i < size; i++)
    {
        if (buf[i] == '\n')
        {
            text[n] = &buf[i+1];
            textCOPY[n] = &buf[i+1];
            buf[i] = '\0';
            n++;
        }
    }
}


void Rhyme(char* textRhyme[], char* textCOPY[], long long int nlines)
{
    check (textCOPY);
    check (textRhyme);

    for (int i = 0; i < nlines; i++)
    {
        check (textCOPY[i]);
        textRhyme[i] = Reverse(textCOPY[i]);
    }
}


char* Reverse(char* str1)
 {
    int length = strlen(str1);

    char * str2 = (char*) calloc(length, sizeof(char));

    int i = 0;
    for (int n = (strlen(str1) - 1); n >= 0; n-- )
        {
            str2[i] = str1[n];
            i++;
        }
   return str2;
 }

int AlphEncoding(char chr)
{

    char alph[53]={"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"};

    int i = 0;

    while(chr)
    {
        if ( chr == alph[i] ) return i;
        i++;
        if (i > 51)           return -2;
        if (chr == '\0')      return -1;
    }
    return -1;
}

int ComparatorStr(const void* ptr1,const void* ptr2)
{
    char* str1 = *((char**) ptr1);
    char* str2 = *((char**) ptr2);

    while ((AlphEncoding( *str1) != -1) && (AlphEncoding( *str2) != -1))
    {
        while(AlphEncoding( *str1) == -2) str1++;

        while(AlphEncoding( *str2) == -2) str2++;

        if (AlphEncoding(*str1) != AlphEncoding(*str2))
            return (AlphEncoding(*str1) - AlphEncoding(*str2));
        else
        {
            str1++;
            str2++;
        }
    }
    if ((AlphEncoding( *str1) != -1) && (AlphEncoding( *str2)   != -1)) return 0;
    if ((AlphEncoding( *str1) != -1) && (AlphEncoding( *str2)   == -1)) return -1;
    if ((AlphEncoding( *str1) == -1) && (AlphEncoding( *str2)   != -1)) return 1;

}

const void Sort(char* arr[],long long int nlines)
{
    check(arr);
    qsort(arr, nlines, sizeof(char*),  ComparatorStr);
}

void OutputFile(char* arr[], long long int nlines)
{
    check(arr);
    FILE* f2 = fopen("alph_rhyme_original.txt", "a+");

    for(int i = 0; i < nlines; i++)
    {
        check(arr[i]);
        fputs(arr[i], f2);
        fprintf (f2,"\n");
    }
    fprintf (f2,"\n\n\n\n");
    fclose(f2);
}
