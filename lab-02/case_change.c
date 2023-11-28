#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()
{
    FILE *fpin, *fpout;
    char c;
    
    fpin = fopen("Input1.txt", "r");
    fpout = fopen("Output1.txt", "w");
    
    if(fpin == NULL || fpout == NULL)
        printf("Cannot open the file!");
    else
    {
        while((c = fgetc(fpin)) != EOF)
        {
            if(isupper(c))
            {
                c = tolower(c);
            }
            else if(islower(c))
            {
                c = toupper(c);
            }
            printf("%c",c);
            fputc(c, fpout);
        }
    }
    
    fclose(fpin);
    fclose(fpout);
    printf("\n");
    
    return 0;
}