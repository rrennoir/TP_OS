#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>

int is_dir(const char *path)
{
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISDIR(path_stat.st_mode);
}

char* concat(const char *s1, const char *s2)
{
    char *result;

    if ((result = malloc(strlen(s1) + strlen(s2) + 1)) == NULL)
    {
        printf("Malloc Failed.\n");
        exit(EXIT_FAILURE);
    }
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

char** realloc_array(char **array, int bufferSize, int word_size)
{
    char **tmp;
    bufferSize += 16;
    tmp = realloc(array, bufferSize * word_size);

    if (tmp)
    {
        array = tmp;
        free(tmp);
    }
    else
    {
        printf("Realloc Failed.\n");
        exit(EXIT_FAILURE);
    }
    return array;
}

char* readFile(char *path)
{
    int c;
    int n = 0;
    char *text;
    FILE *file;

    if((file = fopen(path, "r")) == NULL)
    {
        printf("Failed to open the file.\n");
        exit(EXIT_FAILURE);
    }
    
    fseek(file, 0, SEEK_END);
    long f_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    if ((text = malloc(f_size)) == NULL)
    {
        printf("Malloc file Failed.\n");
        exit(EXIT_FAILURE);
    }
    while((c = fgetc(file)) != EOF)
    {
        text[n++] = (char)c;     
    }
    text[n] = '\0';
    fclose(file);
    return text;
}

int find_ppid(char* text)
{
    int return_count = 0, find = 1, i = 0, j = 0;

    while (find && text[i] != EOF)
    {
        if (((return_count == 6) && (j == 6)) && text[i] == '0')
        { 
            return 1;
        }
        else if (return_count > 6)
        {
            return 0;
        }
        else
        {
            j++;
            if (text[i] == '\n')
            {
                return_count++;
                j = 0;
            }
        }
        i++;
    }
    return 0;
}

int is_a_number(char* number)
{
    int i = 0;
    while (number[i] != '\0')
    {
        if (!isdigit(number[i]))
        {
            return 0;
        }
        i++;
    }
    return 1;
}

int main(void)
{
    int /*i = 0,*/ bufferSize = 16, word_size = 64;
    char *path, *sub_path, *text, **son_array;

    DIR * proc_dir, * process_dir;
	struct dirent * proc_dir_struc;
    struct  dirent * process_dir_struc;
    
    if ((son_array = malloc(sizeof(char) * bufferSize * word_size)) == NULL){
        printf("Malloc array Failed\n");
        exit(EXIT_FAILURE);
    }

	if ((proc_dir = opendir("/proc")) == NULL)
    {
        printf("Opendir Failed.\n");
        exit(EXIT_FAILURE);
    }

	while ((proc_dir_struc = readdir(proc_dir)) != NULL)
    {  
        if (is_a_number(proc_dir_struc->d_name))
        {   
            printf("ok\n");
            path = concat(concat("/proc", "/"), proc_dir_struc->d_name);
            chdir(path);

            printf("%s\n", path);
            process_dir = opendir(path);

            if (process_dir == NULL)
            {
                printf("Opendir Failed.\n");
                exit(EXIT_FAILURE);
            }
            printf("ok\n");
            printf("I'm in %s\n", path);
             
            while((process_dir_struc = readdir(process_dir)) != NULL)
            {
                //printf("find %s\n", process_dir_struc->d_name);

                if ((strcmp(process_dir_struc->d_name, "status") == 0))
                {
                    sub_path = concat(concat(path, "/"), process_dir_struc->d_name);
                    printf("find the status file, will be readed soon and I'm in %s\n", sub_path);

                    text = readFile(sub_path);
                    printf("%s", text);
                    printf("file readed\n");
                    /*
                    if (find_ppid(text))
                    {
                        son_array[i] = sub_path;
                        printf("%s\n", son_array[i]);
                        i++;

                        if (i > bufferSize)
                        {
                            printf("realloc\n");
                            son_array = realloc_array(son_array, bufferSize, word_size);
                        }
                    }*/
                }
            }
            closedir(process_dir);
        }
    }
    /*
    for (int j = 0; j > bufferSize; j++)
    {
        printf("%s", son_array[j]);
    }

    free(son_array);*/
    //free(text);
    closedir(proc_dir);
    
}