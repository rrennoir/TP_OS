#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

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

void readFileBis(char *path)
{
    int fd, bit_readed, done = 1, buffer = 64;
    char text_buffer[64];
    char *text = malloc(sizeof(char));

    if ((fd = open(path, O_APPEND)) == -1)
    {
        printf("Failed to open the file.\n");
        exit(EXIT_FAILURE);
    }
    
    while (done)
    {
        bit_readed = read(fd, text_buffer, buffer - 1);
        printf("bit readed: %d\n", bit_readed);

        if (bit_readed == buffer - 1)
        {
            text_buffer[buffer - 1] = '\0';
            text = concat(text, text_buffer);
            strcpy(text_buffer, "");
        }
        else
        {
            done = 0;
        }
    }

    printf("%s\n", text);
    free(text);
    close(fd);

    
}

char* readFile(char *path)
{
    /* Not perfect but work for the exo (doesn't read the last 2 lines of the file or the last line sometimes)
    Tested on /proc/1/status and /proc/2/status
    */
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
    printf("ok\n");
    return text;
}

int main(int argc, char const *argv[])
{
    char *text;

    readFileBis("/proc/4/status");
}
