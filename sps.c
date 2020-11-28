/**
 * file: sps.c
 * author: xdarmo03
 * date: 2020-11-27
 * description: 
 */ 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct 
{
    int rows;
    int cols;
    char **data;

} matrix_t;

matrix_t mat_init()
{
    matrix_t tab;
    tab.cols=0;
    tab.rows=0;
    tab.data=NULL;
    return tab;
}

void mat_clear(matrix_t *tab, int r )
{
    tab->cols=0;  
    tab->rows=0;
    for (int i = 0; i < r; i++)
    {
        free(tab->data[i]);
    }
    
    free(tab->data);
}

int open_file(FILE **f, const char name[])
{
    *f = fopen(name, "r");
    if (f==NULL)
    {
        printf("Not opened!");
        return 0;
    } else
    {
        printf("Soubor otevren!\n");
        return 1;
    }
    
}

void read_to_mat(FILE *f, matrix_t *tab, const char del[])
{
    char row[255];
    char c;
    while (1)
    {
        c = fgetc(f);
        if (c=='\n')
        {
            tab->rows+=1;
        } 
        for (unsigned i = 0; i < strlen(del); i++)
        {
            if (del[i]==c)
            {
                tab->cols+=1;
            }
        }
        if (feof(f))
        {
            tab->rows+=1;
            break;
        }
               
    }
    printf("Pocet sloupcu: %d\n", tab->cols);
    printf("Pocet radku: %d\n",tab->rows);
    /*
    char **p = realloc(tab->data,tab->rows*sizeof(char*));
    if (p==NULL)
    {
        printf("Realloc fail!");
        return;
    }
    for (int i = 0; i < tab->rows; i++)
    {
        p[i] = realloc(tab->data[i],tab->cols*sizeof(char*));
        if (p[i]==NULL)
        {
            printf("Realloc fail!");
            mat_clear(tab,i);
            // ten clear nefunguje FIXME
        }
        
    }*/
}

void close_file(FILE *f)
{
    printf("Soubor zavren!\n");
    fclose(f);
}

int main(int argc, char const **argv)
{
    int opened = 0;
    if (argc>2)
    {
        FILE *f;
        matrix_t tab;
        tab = mat_init();
        if ((strcmp(argv[1],"-d")) && (argc==3))
        {
            const char *del=" ";
            if (open_file(&f,argv[argc-1]))
            {
                read_to_mat(f,&tab,del); 
                close_file(f);
            } else
            {
                return 1;
            }
            
        }
        if ((!strcmp(argv[1],"-d")) && (argc==5))
        {
            const char *del=argv[2];
            if (open_file(&f,argv[argc-1]))
            {
                read_to_mat(f,&tab,del); 
                close_file(f);
            } else
            {
                return 1;
            }
        }
        
        
    }
    if (opened)
    {
        /* code */
    }
    
    
    return 0;
}
