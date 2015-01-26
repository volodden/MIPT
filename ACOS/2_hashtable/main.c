#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"

#define CHECK_NOT_NULL(ptr, return_value)                   \
    do                                                      \
    {                                                       \
        if (ptr == NULL)                                    \
        {                                                   \
            printf("ERROR. Code: %d\n", return_value);      \
            return return_value;                            \
        }                                                   \
    } while (0)

#define CHECK_FILE(arg, return_value)                       \
    do                                                      \
    {                                                       \
        if (arg < 2)                                        \
        {                                                   \
            printf("ERROR. Code: %d\n", return_value);      \
            return return_value;                            \
        }                                                   \
    } while (0)

#define CHECK(arg)                            \
    do                                                      \
    {                                                       \
        if (arg)                                            \
        {                                                   \
            printf("Error.\n");                               \
            return 1;                            \
        }                                                   \
    } while (0);

#define LENGTH              32
#define CAPACITY            16

#define ERROR_MASSIV_DOES_NOT_CREATED           1
#define ERROR_MASSIV_DOES_NOT_INCREASED         2
#define ERROR_CELL_DOES_NOT_CREATED             3
#define ERROR_CELL_DOES_NOT_INCREASED           4
#define ERROR_NAME_FILE                         5
#define ERROR_FILE_DOES_NOT_EXIST               6

int main(int argc, char* argv[])
{
//    CHECK_FILE(argc, ERROR_FILE_DOES_NOT_EXIST);
//    FILE* iFile = fopen(argv[1], "r"); //iFile is a InputFILE
    FILE* iFile = fopen("input.txt", "r"); //iFile is a InputFILE
    CHECK_NOT_NULL(iFile, ERROR_NAME_FILE);
    int cp = CAPACITY; // cp is a CaPacity
    char** mas = (char**) malloc(cp * sizeof(char*)); //mas is a MASsiv
    CHECK_NOT_NULL(mas, ERROR_MASSIV_DOES_NOT_CREATED);
    int sz = -1; //sz is a SiZe

    do
    {
        if ((++sz) == cp)
        {
            mas = (char**) realloc(mas, (cp *= 2) * sizeof(char*));
            CHECK_NOT_NULL(mas, ERROR_MASSIV_DOES_NOT_INCREASED);
        }
        char c; //c is a Char
        int idx = -1; //idx is a InDeX
        int ln = LENGTH; //ln is a LeNgth
        mas[sz] = (char*) malloc(ln * sizeof(char));
        CHECK_NOT_NULL(mas[sz], ERROR_CELL_DOES_NOT_CREATED);
        do
        {
            c = (char) getc(iFile);
            if ((c == EOF) || (c == '\n'))
            {
                mas[sz][++idx] = '\0';
                break;
            }
            if ((++idx) == ln)
            {
                mas[sz] = (char*) realloc(mas[sz], (ln *= 2) * sizeof(char));
                CHECK_NOT_NULL(mas[sz], ERROR_CELL_DOES_NOT_INCREASED);
            }
            mas[sz][idx] = c;
        }
        while ((c != EOF) && (c != '\n'));
        if (c == EOF)
        {
            break;
        }
    } while (!(feof(iFile)));
    fclose(iFile);

   int t = 0;
   int i = 0;

    struct HT* hsh = createHashTable(&t);
    CHECK(t);
    for (i = 0; i <= sz; ++i)
    {
        CHECK(addElementInHashTable(hsh, mas[i], mas[i]));
    }
//	printf("END OF ADD\n");
    char* ttt = 0;
    CHECK(findElementInHashTable(hsh, mas[0], &ttt));
    printf("%s\n", ttt);
    free(ttt);
//    printf("free: val\n");
//	printf("FOUND!\n");
    CHECK(deleteElementInHashTable(hsh, mas[0]));
//work :)	CHECK(deleteElementInHashTable(hsh, mas[4]));
    deleteHashTable(hsh);
    free(hsh);
//    printf("free: hashtable\n");
  for (i = 0; i <= sz; ++i)
    {
        free(mas[i]);
    }
    free(mas);

    return 0;
}
