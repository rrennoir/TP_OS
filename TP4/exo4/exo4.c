#include <stdio.h>
#include <stdlib.h> 

void main(int argc, char const *argv[])
{
    int cFile1;
    int cFile2;
    FILE *file1;
    FILE *file2;
    FILE *fileCopy;

    if(argc < 4)
    {
        printf("No enought arguments 3 needed :fileOrigine1, fileOrigine2, fileResult.\n");
        return;
    }

    file1 = fopen(argv[1], "r");
    file2 = fopen(argv[2], "r");
    fileCopy = fopen(argv[3], "w");

    if(file1 && file2 && fileCopy)
    {
        while((cFile1 = fgetc(file1)) != EOF)
        {
            fprintf(fileCopy, "%c", cFile1);
            if(cFile1 == '\n')
            {
                while((cFile2 = fgetc(file2)) != EOF && cFile2 != '\n')
                {
                    fprintf(fileCopy, "%c", cFile2);
                }
                fprintf(fileCopy, "\n");
            }
        }
        fclose(file1);
        fclose(file2);
        fclose(fileCopy);
    }
    else
    {
        printf("File do not exist or result.txt creation has failed.\n");
    }
}