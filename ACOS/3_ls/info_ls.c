#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>


#define NO_MEMORY 1

#define CHECK_NOT_NULL(a, error_value)          \
    do                                          \
    {                                           \
        if (!(a))                               \
        {                                       \
            return error_value;                 \
        }                                       \
    } while(0)

#define F_1 1
#define F_2 2
#define F_3 3
#define F_4 4
#define F_5 5
#define F_6 6
#define F_7 7
#define F_8 8
#define F_9 9
#define F_10 10
#define F_11 11
#define F_12 12

#define M_1 1
#define M_2 2
#define M_3 3
#define M_4 4
#define M_5 5
#define M_6 6
#define M_7 7
#define M_8 8
#define M_9 9
#define M_10 10
#define M_11 11
#define M_12 12
#define M_13 13

#define R_1 1
#define R_2 2

#define ERROR_OPEN 1

void print_file_stats(char* input_name)
{
    struct stat stats_about_file;
    if (stat(input_name, &stats_about_file) == 0)
    {
        S_ISDIR(stats_about_file.st_mode)    ? printf("d") : printf("-");
        (stats_about_file.st_mode & S_IRUSR) ? printf("r") : printf("-");
        (stats_about_file.st_mode & S_IWUSR) ? printf("w") : printf("-");
        (stats_about_file.st_mode & S_IXUSR) ? printf("x") : printf("-");
        (stats_about_file.st_mode & S_IRGRP) ? printf("r") : printf("-");
        (stats_about_file.st_mode & S_IWGRP) ? printf("w") : printf("-");
        (stats_about_file.st_mode & S_IXGRP) ? printf("x") : printf("-");
        (stats_about_file.st_mode & S_IROTH) ? printf("r") : printf("-");
        (stats_about_file.st_mode & S_IWOTH) ? printf("w") : printf("-");
        (stats_about_file.st_mode & S_IXOTH) ? printf("x") : printf("-");

        struct tm* time_info = gmtime(&stats_about_file.st_ctime);
        printf(" %2.ld %7.ld %04d-%02d-%02d %02d:%02d:%02d  %s\n",
               stats_about_file.st_nlink, stats_about_file.st_size,
               (time_info->tm_year + 1900), time_info->tm_mon, time_info->tm_mday,
               time_info->tm_hour, time_info->tm_min, time_info->tm_sec, input_name);
    }
    else
    {
        printf("Error: does't read stats.\n");
    }
}

int print_directory(char* input_name)
{
    int v;
    struct dirent* element_of_directory;

    printf("in print_directory\n");
    printf("%s\n", input_name);
    DIR* actual_directory = opendir(input_name);
    if (actual_directory == NULL)
    {
        printf("It is error.\n");
        closedir(actual_directory);
        return ERROR_OPEN;
    }
    printf("Malloc  %d : var temporary_directory\n", M_1);
    char* temporary_directory = (char*) malloc(strlen(input_name) * sizeof(char));
    CHECK_NOT_NULL(temporary_directory, NO_MEMORY);
    strcpy(temporary_directory, input_name);
    if ((strcmp(input_name, "/") != 0) && (input_name[strlen(input_name) - 1] != '/'))
    {
        printf("Realloc %d : var temporary_directory\n", R_1);
        temporary_directory = (char*) realloc(temporary_directory, (strlen(temporary_directory) + 1) * sizeof(char));
        CHECK_NOT_NULL(temporary_directory, NO_MEMORY);
        strcat(temporary_directory, "/");
    }
    while (element_of_directory = readdir(actual_directory))
    {
        printf("Open element: %s\n", element_of_directory->d_name);

        if (element_of_directory->d_type == 8) //DT_REG == 8
        {
            printf("It is regular file.\n");
            printf("Malloc  %d : var temporary_name\n", M_2);
            char* temporary_name = (char*) malloc((strlen(temporary_directory) + strlen(element_of_directory->d_name)) * sizeof(char));
            CHECK_NOT_NULL(temporary_name, NO_MEMORY);
            strcpy(temporary_name, temporary_directory);
            strcat(temporary_name, element_of_directory->d_name);
            print_file_stats(temporary_name);

            printf("Free    %d : var temporary_name\n", F_2);
            free(temporary_name);
        }
        if (element_of_directory->d_type == 4) //DT_DIR == 4
        {
            printf("It is directory.\n");
            if ((strcmp(element_of_directory->d_name, "..")) && (strcmp(element_of_directory->d_name, ".")))
            {
                printf("Malloc  %d : var temporary_name\n", M_11);
                char* temporary_name = (char*) malloc((strlen(temporary_directory) + strlen(element_of_directory->d_name)) * sizeof(char));
                CHECK_NOT_NULL(temporary_name, NO_MEMORY);
                strcpy(temporary_name, temporary_directory);
                strcat(temporary_name, element_of_directory->d_name);
                print_file_stats(temporary_name);
                v = print_directory(temporary_name);
                if (v != 0)
                {
                    printf("Free    %d : var temporary_name\n", F_11);
                    free(temporary_name);
                    return v;
                }
                printf("Free    %d : var temporary_name\n", F_12);
                free(temporary_name);
            }
        }
    }
    printf("Free    %d : var temporary_directory\n", F_3);
    free(temporary_directory);
    printf("All directory was read.\n");
    closedir(actual_directory);

    return 0;
}

int print(char* input_name)
{
    int v = 0;
    DIR* actual_directory;

	if ((actual_directory = opendir(input_name)) != NULL)
	{
	    closedir(actual_directory);
	    printf("Opendir: %s\n", input_name);
	    v = print_directory(input_name);
        return v;
	}
	else
	{
		closedir(actual_directory);

		char* actual_directoryS;
		char* input_name2;

////		if (strstr(input_name, "/") == 0)
////		{
////		    //printf("Malloc  %d : var input_name2\n", M_3);
////		    input_name2 = (char*) malloc(strlen(input_name) * sizeof(char));
////		    CHECK_NOT_NULL(input_name2, NO_MEMORY);
////            //printf("Malloc  %d : var actual_directoryS\n", M_4);
////		    actual_directoryS = (char*) malloc(strlen("./") * sizeof(char));
////			CHECK_NOT_NULL(actual_directoryS, NO_MEMORY);
////            strcpy(input_name2, input_name);
////			strcpy(actual_directoryS, "./");
////		}
////		else
////		{

		int j = -1;
		int i = 0;
		for (i = strlen(input_name) - 1; i >= 0; --i)
		{
			if (input_name[i] == '/')
			{
				j = i;
				break;
			}
		}
		if (j == -1)
        {
            printf("Malloc  %d : var actual_directoryS\n", M_12);
            actual_directoryS = (char*) malloc(3*sizeof(char));
            CHECK_NOT_NULL(actual_directoryS, NO_MEMORY);
            actual_directoryS[0] = '.';
            actual_directoryS[1] = '/';
            actual_directoryS[2] = '\0';
            printf("Malloc  %d : var input_name2\n", M_13);
            input_name2 = (char*) malloc(strlen(input_name)*sizeof(char));
            CHECK_NOT_NULL(input_name2, NO_MEMORY);
            strcpy(input_name2, input_name);
        }
        else
        {
            printf("Malloc  %d : var actual_directoryS\n", M_5);
            actual_directoryS = (char*) malloc((j+1)*sizeof(char));
            CHECK_NOT_NULL(actual_directoryS, NO_MEMORY);
            for (i = 0; i <= j; ++i)
            {
                actual_directoryS[i] = input_name[i];
            }
            actual_directoryS[j+1] = '\0';
            printf("Malloc  %d : var input_name2\n", M_6);
            input_name2 = (char*) malloc((strlen(input_name) - j - 1)*sizeof(char));
            CHECK_NOT_NULL(input_name2, NO_MEMORY);
            for (i = j + 1; i < strlen(input_name); ++i)
            {
                input_name2[i - j - 1] = input_name[i];
            }
            input_name2[strlen(input_name)] = '\0';
        }
		if (actual_directory = opendir(actual_directoryS))
     	{
     	    printf("Opendir: %s\n", actual_directoryS);
     		int k = 0;
     		struct dirent* element_of_directory;
     		while (element_of_directory = readdir(actual_directory))
     		{
     		    printf("Openelement: %s\n", element_of_directory->d_name);
     		    printf("Malloc  %d : var temporary_directory\n", M_7);
     		    char* temporary_directory = (char*) malloc(strlen(actual_directoryS) * sizeof(char));
     			CHECK_NOT_NULL(temporary_directory, NO_MEMORY);
     			strcpy(temporary_directory, actual_directoryS);
       			if ((element_of_directory->d_type == 8) && (!(strcmp(element_of_directory->d_name, input_name2)))) //DT_REG == 8
     			{
                    printf("File found.\n");
     				++k;
     				printf("Malloc  %d : var temporary_name\n", M_8);
       				char* temporary_name = (char*) malloc((strlen(temporary_directory) + strlen(element_of_directory->d_name) * sizeof(char)));
     				CHECK_NOT_NULL(temporary_name, NO_MEMORY);
     				strcpy(temporary_name, temporary_directory);
     				strcat(temporary_name, element_of_directory->d_name);

                    print_file_stats(temporary_name);

                    printf("Free    %d : var temporary_name\n", F_4);
                    free(temporary_name);
	    		}
                printf("Free    %d : var temporary_directory\n", F_5);
                free(temporary_directory);
                if (k != 0)
                {
                    break;
                }
	    	}
	    	if (k == 0)
            {
                printf("Error: doesn't found file.\n");
            }
	    	closedir(actual_directory);
	    }
	    printf("Free    %d : var input_name2\n", F_6);
	    free(input_name2);
	    printf("Free    %d : var actual_directoryS\n", F_7);
	    free(actual_directoryS);
	    return 0;
	}
}

int main (int argc, char* argv[])
{
    int i = 0;
    char* input_name;
	if (argc < 2)
	{
	    printf("Malloc  %d : var input_name\n", M_9);
	    input_name = (char*) malloc(3*sizeof(char));
	    CHECK_NOT_NULL(input_name, NO_MEMORY);
	    input_name[0] = '.';
	    input_name[1] = '/';
	    input_name[2] = '\0';
	}
	else
    {
        printf("Malloc  %d : var input_name\n", M_10);
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
                input_name = (char*) malloc((strlen(argv[1]) + 1) * sizeof(char));
                CHECK_NOT_NULL(input_name, NO_MEMORY);
                strcpy(input_name, argv[1]);
                i = strlen(input_name);
                input_name[i] = '/';
                input_name[i+1] = '\0';
            }
            else
            {
                input_name = (char*) malloc(strlen(argv[1]) * sizeof(char));
                CHECK_NOT_NULL(input_name, NO_MEMORY);
                strcpy(input_name, argv[1]);
            }
        }
    }

    printf("%s\n", input_name);
	i = print(input_name);
	if (i != 0)
    {
        return i;
    }

	printf("Free    %d : var input_name\n", F_8);
	free(input_name);
	return 0;
}
