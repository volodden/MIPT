#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

void print(char* inpt)
{
	struct dirent* odir;
	DIR* pdir;
	char temp [300] = {0};
	//char* temp = (char*) malloc (TEMP_1 * sizeof(char));

	pdir = opendir(inpt);
	if (pdir)
	{
		while ((odir = readdir(pdir)) != NULL)
		{
			strcpy(temp, inpt);
			if (strcmp(inpt, "/"))
            {
                strcat(temp, "/");
            }
			if (odir->d_type == 8)
			{
				char mbuf[512];
				strcpy(mbuf, temp);
				strcat(mbuf, odir->d_name);
				struct stat stf;
				if (!(stat(mbuf, &stf)))
				{
                    S_ISDIR(stf.st_mode)    ? printf("d") : printf("-");
	                (stf.st_mode & S_IRUSR) ? printf("r") : printf("-");
	                (stf.st_mode & S_IWUSR) ? printf("w") : printf("-");
	                (stf.st_mode & S_IXUSR) ? printf("x") : printf("-");
	                (stf.st_mode & S_IRGRP) ? printf("r") : printf("-");
	                (stf.st_mode & S_IWGRP) ? printf("w") : printf("-");
	                (stf.st_mode & S_IXGRP) ? printf("x") : printf("-");
	                (stf.st_mode & S_IROTH) ? printf("r") : printf("-");
	                (stf.st_mode & S_IWOTH) ? printf("w") : printf("-");
	                (stf.st_mode & S_IXOTH) ? printf("x") : printf("-");

	                struct tm* tmf = gmtime(&stf.st_ctime);
	                printf(" %2.ld %7.ld %04d-%02d-%02d %02d:%02d  %s\n",
                           stf.st_nlink, stf.st_size, (tmf->tm_year + 1900), tmf->tm_mon,
                           tmf->tm_mday, tmf->tm_hour, tmf->tm_min, odir->d_name);
				}
				else
				{
				    printf("Error: does't read stats.\n");
				}
			}
			if (odir->d_type == 4)
			{
				if ((strcmp(odir->d_name, "..")) && (strcmp(odir->d_name, ".")))
				{
					strcat(temp, odir->d_name);
					print(temp);
				}
			}
		}
		closedir(pdir);
	}
	else
	{
		closedir(pdir);
		char pdirBuf[302] = {0};
		char inpt2[300] = {0};
		if (!(strstr(inpt, "/")))
		{
			strcpy(inpt2, inpt);
			strcpy(pdirBuf, "./");
		}
		else
		{
			int j = 0;
			int i = 0;
			for (i = strlen(inpt); i >= 0; --i)
			{
				if (inpt[i] == '/')
				{
					j = i;
					break;
				}
			}
			for (i = 0; i <= j; ++i)
			{
				pdirBuf[i] = inpt[i];
			}
			for (i = j + 1; i < strlen(inpt); ++i)
			{
				inpt2[i - j - 1] = inpt[i];
			}
		}
		pdir = opendir(pdirBuf);
     	if (pdir)
     	{
     		int k = 0;
     		while ((odir = readdir(pdir)) != NULL)
     		{
     			strcpy(temp, pdirBuf);
       			if ((odir->d_type == 8) && (!(strcmp(odir->d_name, inpt2))))
     			{
     				++k;
       				char mbuf[511];
     				strcpy(mbuf, temp);
     				strcat(mbuf, odir->d_name);
     				struct stat stf;
     				if (!(stat(mbuf, &stf)))
     				{
     					S_ISDIR(stf.st_mode)    ? printf("d") : printf("-");
     	                (stf.st_mode & S_IRUSR) ? printf("r") : printf("-");
	                    (stf.st_mode & S_IWUSR) ? printf("w") : printf("-");
	                    (stf.st_mode & S_IXUSR) ? printf("x") : printf("-");
	                    (stf.st_mode & S_IRGRP) ? printf("r") : printf("-");
	                    (stf.st_mode & S_IWGRP) ? printf("w") : printf("-");
	                    (stf.st_mode & S_IXGRP) ? printf("x") : printf("-");
	                    (stf.st_mode & S_IROTH) ? printf("r") : printf("-");
	                    (stf.st_mode & S_IWOTH) ? printf("w") : printf("-");
	                    (stf.st_mode & S_IXOTH) ? printf("x") : printf("-");

	                    struct tm* tmf = gmtime(&stf.st_ctime);
	    				printf(" %s\n", odir->d_name);
                        printf(" %2.ld %7.d %04d-%02d-%02d %02d:%02d  %s\n",
                           stf.st_nlink, stf.st_size, (tmf->tm_year + 1900), tmf->tm_mon,
                           tmf->tm_mday, tmf->tm_hour, tmf->tm_min, odir->d_name);
                    }
                    else
                    {
                        printf("Error: does't read stats.\n");
                    }
	    		}
	    	}
	    	if (!(k))
            {
                printf("Error: doesn't found file.\n");
            }
	    	closedir(pdir);
	    }
	}
}

int main (int argc, char* argv[])
{
    char* sInput;
	if (argc < 2)
	{
	    sInput = ".";
	}
	else
    {
        sInput = argv[1];
    }
	print(sInput);
	return 0;
}
