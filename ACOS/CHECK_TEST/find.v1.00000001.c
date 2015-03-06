#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

struct two_mas
{
	char** names;
	char** direc;
	int mas_sz;
	int mas_cp;
};

#define CHECK_NOT_NULL(a, error_value)          \
    do                                          \
    {                                           \
        if (!(a))                               \
        {                                       \
            return error_value;                 \
        }                                       \
    } while(0)

#define ERROR_OPEN 1
#define NO_MEMORY 2
#define START_SIZE 64

struct two_mas namdir;
	
int mycompare(const void* first, const void* second)
{
	return strcasecmp(namdir.names[*((int*)first)], namdir.names[*((int*)second)]);
}

int find_file(char* input_name, struct two_mas* mas)
{
    int v;
    struct dirent* element_of_directory;

    DIR* actual_directory = opendir(input_name);
    if (actual_directory == NULL)
    {
//        printf("Can not open directory: %s.\n", input_name);
        return 0;
    }
    
    char* temporary_directory = (char*) malloc((strlen(input_name) + 1)  * sizeof(char));
    CHECK_NOT_NULL(temporary_directory, NO_MEMORY);
    strcpy(temporary_directory, input_name);
    if ((strcmp(input_name, "/") != 0) && (input_name[strlen(input_name) - 1] != '/'))
    {
        temporary_directory = (char*) realloc(temporary_directory, (strlen(temporary_directory) + 2) * sizeof(char));
        CHECK_NOT_NULL(temporary_directory, NO_MEMORY);
        strcat(temporary_directory, "/");
	}
    while ((element_of_directory = readdir(actual_directory)) != NULL)
    {
        if (element_of_directory->d_type == 4) //DT_DIR == 4
        {
            if ((strcmp(element_of_directory->d_name, "..")) && (strcmp(element_of_directory->d_name, ".")))
            {
		    	if (mas->mas_cp == mas->mas_sz)
				{
					mas->mas_cp = 2*(mas->mas_cp);
					mas->names = realloc(mas->names, (mas->mas_cp) * sizeof(char*));		
					mas->direc = realloc(mas->direc, (mas->mas_cp) * sizeof(char*));
					CHECK_NOT_NULL(mas->names, NO_MEMORY);
					CHECK_NOT_NULL(mas->direc, NO_MEMORY);
				}
		        mas->names[mas->mas_sz] = (char*) malloc((strlen(element_of_directory->d_name) + 1) * sizeof(char));
		        mas->direc[mas->mas_sz] = (char*) malloc((strlen(temporary_directory) + 1) * sizeof(char));
		        CHECK_NOT_NULL(mas->names[mas->mas_sz], NO_MEMORY);
				CHECK_NOT_NULL(mas->direc[mas->mas_sz], NO_MEMORY);
			
		        strcpy(mas->direc[mas->mas_sz], temporary_directory);
		        strcpy(mas->names[mas->mas_sz], element_of_directory->d_name);
				mas->mas_sz = mas->mas_sz + 1;
				
                char* temporary_name = (char*) malloc((strlen(temporary_directory) + strlen(element_of_directory->d_name) + 1) * sizeof(char));
                CHECK_NOT_NULL(temporary_name, NO_MEMORY);
                strcpy(temporary_name, temporary_directory);
                strcat(temporary_name, element_of_directory->d_name);
                v = find_file(temporary_name, mas);
                if (v != 0)
                {
                    free(temporary_name);
                    return v;
                }
                free(temporary_name);
            }
        }
        else
        {
        	if (mas->mas_cp == mas->mas_sz)
			{
				mas->mas_cp = 2*(mas->mas_cp);
				mas->names = realloc(mas->names, (mas->mas_cp) * sizeof(char*));		
				mas->direc = realloc(mas->direc, (mas->mas_cp) * sizeof(char*));
				CHECK_NOT_NULL(mas->names, NO_MEMORY);
				CHECK_NOT_NULL(mas->direc, NO_MEMORY);
			}
            mas->names[mas->mas_sz] = (char*) malloc((strlen(element_of_directory->d_name) + 1) * sizeof(char));
            mas->direc[mas->mas_sz] = (char*) malloc((strlen(temporary_directory) + 1) * sizeof(char));
            CHECK_NOT_NULL(mas->names[mas->mas_sz], NO_MEMORY);
			CHECK_NOT_NULL(mas->direc[mas->mas_sz], NO_MEMORY);
            strcpy(mas->direc[mas->mas_sz], temporary_directory);
            strcpy(mas->names[mas->mas_sz], element_of_directory->d_name);
            mas->mas_sz = mas->mas_sz + 1;
        }
    }
    free(temporary_directory);
    closedir(actual_directory);
    return 0;
}

int info(char* input_name, struct two_mas* mas)
{
    int v = 0;
    DIR* actual_directory;
	
	if ((actual_directory = opendir(input_name)) != NULL)
	{
	    closedir(actual_directory);
	    v = find_file(input_name, mas);
      	return v;
	}
	else
	{
		printf("Argument is not directory.\n");
		closedir(actual_directory);
		return 0; 
	}
}

int main (int argc, char* argv[])
{
    int i = 0;
    char* input_name;
	if (argc < 2)
	{
	    input_name = (char*) malloc(3*sizeof(char));
	    CHECK_NOT_NULL(input_name, NO_MEMORY);
	    input_name[0] = '.';
	    input_name[1] = '/';
	    input_name[2] = '\0';
	}
	else
    {
        if (strcmp(argv[1], ".") == 0)
        {
            input_name = (char*) malloc(3 * sizeof(char));
            CHECK_NOT_NULL(input_name, NO_MEMORY);
            input_name[0] = '.';
            input_name[1] = '/';
            input_name[2] = '\0';
	    }
        else
        {
            if (argv[1][strlen(argv[1]) - 1] == '.')
            {
                input_name = (char*) malloc((strlen(argv[1]) + 2) * sizeof(char));
                CHECK_NOT_NULL(input_name, NO_MEMORY);
                strcpy(input_name, argv[1]);
                i = strlen(input_name);
                input_name[i] = '/';
                input_name[i+1] = '\0';
            }
            else
            {
                input_name = (char*) malloc(strlen(argv[1] + 1) * sizeof(char));
                CHECK_NOT_NULL(input_name, NO_MEMORY);
                strcpy(input_name, argv[1]);
            }
        }
    }
	
	namdir.mas_sz = 0;
	namdir.mas_cp = START_SIZE;
	namdir.names = (char**) malloc(namdir.mas_cp * sizeof(char*));
	namdir.direc = (char**) malloc(namdir.mas_cp * sizeof(char*));

	i = info(input_name, &namdir);
    if (i != 0)
    {
        return i;
    }
	
	if (namdir.mas_sz == 0)
	{
		printf("Empty directory.\n");
		free(namdir.names);
		free(namdir.direc);
		free(input_name);
		return 0;
	}
	
	if (namdir.mas_sz == 1)
	{
		printf("No files.\n");
		free(namdir.names[0]);
		free(namdir.direc[0]);
		free(namdir.names);
		free(namdir.direc);
		free(input_name);
		return 0;
	}
	
//	for (i = 0; i < namdir.mas_sz; ++i)
//	{
//		printf("NAME: %s\n", namdir.names[i]);
//		printf("DIR: %s\n\n", namdir.direc[i]);
//	}
//	
//	printf("------------------------\n");

	int* ind = (int*) malloc(namdir.mas_sz * sizeof(int));
	CHECK_NOT_NULL(ind, NO_MEMORY);
	
	for (i = 0; i < namdir.mas_sz; ++i)
	{
		ind[i] = i;
	}
	
    qsort(ind, namdir.mas_sz, sizeof(int), mycompare);	
	
//	for (i = 0; i < namdir.mas_sz; ++i)
//	{
//		printf("NAME: %s\n", namdir.names[ind[i]]);
//		printf("DIR: %s\n\n", namdir.direc[ind[i]]);
//		free(namdir.names[ind[i]]);
//		free(namdir.direc[ind[i]]);
//	}
//	
//	printf("------------------------\n");

	i = 1;
    int nameexist = 0;
	while (i < namdir.mas_sz)
	{
//		printf("%d\n", i);
		if (strcasecmp(namdir.names[ind[i]], namdir.names[ind[i-1]]) == 0)
		{
			nameexist = 1;
			printf("%s found in:\n%s\n%s\n", namdir.names[ind[i]], namdir.direc[ind[i]], namdir.direc[ind[i-1]]);
			++i;
			while((i < namdir.mas_sz) && (strcasecmp(namdir.names[ind[i]], namdir.names[ind[i-1]]) == 0))
			{
//				printf("%d\n", i);
				printf("%s\n", namdir.direc[ind[i]]);
				++i;
			}
		}
		else
		{
			++i;
		}
	}
	
	if (nameexist == 0)
	{
		printf("No files.\n");
	} 
	
	for (i = 0; i < namdir.mas_sz; ++i)
	{
//		printf("NAME: %s\n", namdir.names[ind[i]]);
//		printf("DIR: %s\n\n", namdir.direc[ind[i]]);
		free(namdir.names[ind[i]]);
		free(namdir.direc[ind[i]]);
	}
	free(ind);
	free(namdir.names);
	free(namdir.direc);    
    free(input_name);
    return 0;
}
