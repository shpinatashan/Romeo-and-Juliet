#include "RaJ.h"

int main()
{
struct stat st = {};
stat("RaJ.txt", &st);
int size = st.st_size +1;
char * buf = (char*) calloc(size, sizeof(char));

if (check(buf) == -1) return -1;

FILE* f2 = fopen("alph_rhyme_original.txt", "w");

if (f2 == NULL)
    {
        printf("Cannot open file");
    }
fclose(f2);

ReadPoem(size, buf);
long long int nlines = Count(buf, size);

printf("size %d \n", size);
printf("Nlines %lld\n", nlines);
   
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

MyFree(&text);
MyFree(&textCOPY);
MyFree(&textRhyme);
MyFree(&buf);
MyFree(&textCorr);

return 0;
}
