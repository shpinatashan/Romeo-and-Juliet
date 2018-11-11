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
/*
    FILE* juliet = fopen("RaJ.txt", "r");
    char alph[NAlph] = {};
    fread(alph, sizeof(char), NAlph, juliet);
    fclose(juliet);
*/

    char alph[NAlph] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"};
    
    int i = 0;

    while(chr)
    {
        if ( chr == alph[i] ) return i;
        i++;
        if (i > NAlph-2)           return -2;
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

