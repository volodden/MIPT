#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

#define CAPACITY            32
#define LENGTH              64

#define ERROR_MASSIV_DOES_NOT_CREATED           1
#define ERROR_MASSIV_DOES_NOT_INCREASED         2
#define ERROR_CELL_DOES_NOT_CREATED             3
#define ERROR_CELL_DOES_NOT_INCREASED           4
#define ERROR_NAME_FILE                         5
#define ERROR_FILE_DOES_NOT_EXIST               6


int mycompare(const void* first, const void* second)
{
    return strcmp(*((char**)first), *((char**)second));
}

int main(int argc, char* argv[])
{
    CHECK_FILE(argc, ERROR_FILE_DOES_NOT_EXIST);
    FILE* iFile = fopen(argv[1], "r"); //iFile is a InputFILE
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
            if ((c == EOF) || (c == '\n') || (c == ' '))
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
        while ((c != EOF) && (c != '\n') && (c != ' '));
        if (c == EOF)
        {
            break;
        }
    } while (!(feof(iFile)));
    fclose(iFile);

    if (!(strlen(mas[sz])))
    {
        free(mas[sz]);
        --sz;
    }

    if (sz == -1)
    {
        free(mas);
        printf("0\n");
        return 0;
    }

    if (sz == 0)
    {
        free(mas[0]);
        free(mas);
        printf("1\n");
        return 0;
    }

    qsort(mas, sz+1, sizeof(char*), mycompare);

    int ks = 0;
    if (strlen(mas[0]))
    {
        ++ks;
    }

    int i = 1;
    for (i = 1; i <= sz; i++)
    {
        if ((strcmp(mas[i], mas[i-1])) && (strlen(mas[i])))
        {
            ++ks;
        }
    }

    printf("%d\n", ks);

    for (i = 0; i < sz; i++)
    {
        free(mas[i]);
    }
    free(mas);

    return 0;
}
