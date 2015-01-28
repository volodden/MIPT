#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>


#define NO_MEMORY 1

#define CHECK_NOT_NULL(a, error_value)          \
    do                                          \
    {                                           \
        if (!(a))                               \
        {                                       \
            return error_value;                 \
        }                                       \
    } while(0)

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
	struct passwd* uid = getpwuid((size_t) stats_about_file.st_uid);
	char name[256];
	char group[256];
	name[0] = '-';
	name[1] = '\0';
	group[0] = '-';
	group[1] = '\0';
	if (uid != NULL)
	{
		strcpy(name, uid->pw_name);
	}

	struct group* gid = getgrgid((size_t) stats_about_file.st_gid);
	if (gid != NULL)
	{
		strcpy(group, gid->gr_name);
	}
        printf("%2.ld %7.ld %10s %10s %04d-%02d-%02d %02d:%02d:%02d  %s\n",
               stats_about_file.st_nlink, stats_about_file.st_size,
	       name, group, 
               (time_info->tm_year + 1900), time_info->tm_mon + 1, time_info->tm_mday,
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

    DIR* actual_directory = opendir(input_name);
   if (actual_directory == NULL)
    {
        printf("Can not open directory: %s.\n", input_name);
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
        if (element_of_directory->d_type == 8) //DT_REG == 8
        {
            char* temporary_name = (char*) malloc((strlen(temporary_directory) + strlen(element_of_directory->d_name) + 1) * sizeof(char));
            CHECK_NOT_NULL(temporary_name, NO_MEMORY);
            strcpy(temporary_name, temporary_directory);
            strcat(temporary_name, element_of_directory->d_name);
            print_file_stats(temporary_name);
            free(temporary_name);
        }
        if (element_of_directory->d_type == 4) //DT_DIR == 4
        {
            if ((strcmp(element_of_directory->d_name, "..")) && (strcmp(element_of_directory->d_name, ".")))
            {
                char* temporary_name = (char*) malloc((strlen(temporary_directory) + strlen(element_of_directory->d_name) + 1) * sizeof(char));
                CHECK_NOT_NULL(temporary_name, NO_MEMORY);
                strcpy(temporary_name, temporary_directory);
                strcat(temporary_name, element_of_directory->d_name);
                print_file_stats(temporary_name);
                v = print_directory(temporary_name);
                if (v != 0)
                {
                    free(temporary_name);
                    return v;
                }
                free(temporary_name);
            }
        }
    }
    free(temporary_directory);
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
	    v = print_directory(input_name);
        return v;
	}
	else
	{
		closedir(actual_directory);
		char* actual_directoryS;
		char* input_name2;
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
            actual_directoryS = (char*) malloc(3 * sizeof(char));
            CHECK_NOT_NULL(actual_directoryS, NO_MEMORY);
            actual_directoryS[0] = '.';
            actual_directoryS[1] = '/';
            actual_directoryS[2] = '\0';
            input_name2 = (char*) malloc((strlen(input_name) + 1) * sizeof(char));
            CHECK_NOT_NULL(input_name2, NO_MEMORY);
            strcpy(input_name2, input_name);
        }
        else
        {
            actual_directoryS = (char*) malloc( (j+2) *sizeof(char));
            CHECK_NOT_NULL(actual_directoryS, NO_MEMORY);
            for (i = 0; i <= j; ++i)
            {
                actual_directoryS[i] = input_name[i];
            }
            actual_directoryS[j+1] = '\0';
            input_name2 = (char*) malloc((strlen(input_name) - j) * sizeof(char));
            CHECK_NOT_NULL(input_name2, NO_MEMORY);
            for (i = j + 1; i < strlen(input_name); ++i)
            {
                input_name2[i - j - 1] = input_name[i];
            }
            input_name2[strlen(input_name)] = '\0';
        }
		if ((actual_directory = opendir(actual_directoryS)) != NULL)
     	{
     		int k = 0;
     		struct dirent* element_of_directory;
     		while ((element_of_directory = readdir(actual_directory)) != NULL)
     		{
     		    char* temporary_directory = (char*) malloc((strlen(actual_directoryS) + 1) * sizeof(char));
     			CHECK_NOT_NULL(temporary_directory, NO_MEMORY);
     			strcpy(temporary_directory, actual_directoryS);
       			if ((element_of_directory->d_type == 8) && (!(strcmp(element_of_directory->d_name, input_name2)))) //DT_REG == 8
     			{
     				++k;
       				char* temporary_name = (char*) malloc((strlen(temporary_directory) + strlen(element_of_directory->d_name + 1) * sizeof(char)));
     				CHECK_NOT_NULL(temporary_name, NO_MEMORY);
     				strcpy(temporary_name, temporary_directory);
     				strcat(temporary_name, element_of_directory->d_name);
                    print_file_stats(temporary_name);
                    free(temporary_name);
	    		}
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
	    free(input_name2);
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

	i = print(input_name);
	if (i != 0)
    {
        return i;
    }

	free(input_name);
	return 0;
}
