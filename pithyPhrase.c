#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BSIZE 256



int main()
{

    const char filename[] = "C:\\Users\\13479\\Downloads\\new project\\pithyPhrase.txt";

    FILE *fp;

    char buffer[BSIZE];
    char *r, *entry;
    int items;

    char **list_base;
    int saying;

    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        fprintf(stderr,"Unable to open file %s\n",filename);
		exit(1);
    }
    // pointer pointer = (typecast) malloc( size of a char pointer ) * number of pointers to store
    //list base keeps track of the pointers in the code
    list_base = (char **)malloc(sizeof(char *) * 100);
    if (list_base == NULL)
    {
        fprintf(stderr,"Unable to allocate memory\n");
		exit(1);
    }
    items = 0;
    while (!feof(fp))
    {

        r = fgets(buffer, BSIZE, fp);
        if (r == NULL)
            break;
        // printf("%s", buffer);
        entry = (char *)malloc(sizeof(char) * strlen(buffer) + 1);
        if (entry == NULL)
        {
            fprintf(stderr,"Unable to allocate memory\n");
			exit(1);
        }
        strcpy(entry, buffer);
        *(list_base + items) = entry;
        items++;
        if (items % 100 == 0)
        {
            /* code */
            list_base = (char **)realloc(list_base, sizeof(char *) * (items + 100));
            if (list_base == NULL)
            {
                fprintf(stderr,"Unable to reallocate memory\n");
				exit(1);
            }
        }
    }

    fclose(fp);

    srand((unsigned)time(NULL));
    saying = rand() % (items - 1);
    printf("%s", *(list_base + saying));

    return (0);
}