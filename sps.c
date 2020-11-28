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
}

void mat_clear(matrix_t *tab)
{
    tab->cols=0;  
    tab->rows=0;
    free(tab->data);
}

int open_file(FILE *f, const char name[])
{
    f = fopen(name, "r");
    if (f==NULL)
    {
        printf("Not opened!");
        return 0;
    } else
    {
        return 1;
    }
    
}

void read_to_mat(FILE *f, matrix_t *tab)
{
    
    printf("ano");
}

void close_file(FILE *f)
{
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
            if ( opened = open_file(f,argv[argc-1]))
            {
                read_to_mat(f,&tab); 
                close_file(f);
            } else
            {
                close_file(f);
                return 1;
            }
            
        }
        if ((!strcmp(argv[1],"-d")) && (argc==5))
        {
            char *del=argv[2];
            if ( opened = open_file(f,argv[argc-1]))
            {
                read_to_mat(f,&tab); 
                close_file(f);
            } else
            {
                close_file(f);
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
