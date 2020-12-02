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
    tab.cols = 0;
    tab.rows = 0;
    tab.data = NULL;
    return tab;
}

void mat_clear(matrix_t *tab, int r)
{
    tab->cols = 0;
    tab->rows = 0;
    for (int i = 0; i < r; i++)
    {
        free(tab->data[i]);
        printf("Dealokace %d\n", i);
    }

    free(tab->data);
    printf("Dealokace tabulky\n");
}
void mat_alloc(matrix_t *tab)
{
    tab->data = malloc(tab->cols * tab->rows * sizeof(char *));
    if (tab->data == NULL)
    {
        printf("Malloc fail!");
        return;
    }
    for (int i = 0; i < (tab->cols * tab->rows); i++)
    {
        tab->data[i] = malloc(sizeof(char));
        if (tab->data[i] == NULL)
        {
            printf("Malloc fail!");
            mat_clear(tab, i);
            return;
        }
    }
}

int open_file(FILE **f, const char name[], char *meth)
{
    *f = fopen(name, meth);
    if (f == NULL)
    {
        printf("Not opened!");
        return 0;
    }
    else
    {
        printf("Soubor otevren!\n");
        return 1;
    }
}

void read_to_mat(FILE *f, matrix_t *tab, const char del[])
{
    char c;
    int cols = 0;
    while (1)
    {
        c = fgetc(f);
        if (feof(f))
        {
            tab->cols += 1;
            break;
        }
        if (c == '\n')
        {
            tab->rows += 1;
            tab->cols = cols;
            cols = 0;
        }
        for (unsigned i = 0; i < strlen(del); i++)
        {
            if (del[i] == c)
            {
                cols += 1;
            }
        }
    }
    printf("Pocet sloupcu: %d\n", tab->cols);
    printf("Pocet radku: %d\n", tab->rows);

    mat_alloc(tab);

    printf("Alokace se provedla\n");

    fseek(f, 0, SEEK_SET);

    int tmp = 0;
    int size = 1;
    int is_delim = 0;

    while (1)
    {
        c = fgetc(f);
        if (c == '\n')
        {
            tab->data[tmp][size-1]='\0';
            tmp++;
            size = 1;
            is_delim = 1;
        }
        for (unsigned i = 0; i < strlen(del); i++)
        {
            if (del[i] == c)
            {
                tab->data[tmp][size-1]='\0';
                tmp++;
                size = 1;
                is_delim = 1;
                break;
            }
            else
            {
                is_delim = 0;
            }
        }
        if (feof(f))
        {
            break;
        }

        if (!is_delim)
        {
            if (c != '\n')
            {

                tab->data[tmp][size - 1] = c;
                size++;
                char *p = realloc(tab->data[tmp], size * sizeof(char));
                if (p == NULL)
                {
                    printf("Realloc fail!");
                    free(p);
                    free(tab->data);
                    return;
                }
                tab->data[tmp] = p;
            }
        }
    }
    for (int i = 0; i < tmp; i++)
    {

        printf("%s ", tab->data[i]);
    }
}

void close_file(FILE *f)
{
    printf("Soubor zavren!\n");
    fclose(f);
}

int main(int argc, char const **argv)
{
    int opened = 0;
    if (argc > 2)
    {
        FILE *f;
        matrix_t tab;
        tab = mat_init();
        if ((strcmp(argv[1], "-d")) && (argc == 3))
        {
            const char *del = " ";
            if (open_file(&f, argv[argc - 1], "r"))
            {
                read_to_mat(f, &tab, del);
                mat_clear(&tab, tab.rows);
                close_file(f);
            }
            else
            {
                return 1;
            }
        }
        if ((!strcmp(argv[1], "-d")) && (argc == 5))
        {
            const char *del = argv[2];
            if (open_file(&f, argv[argc - 1], "r"))
            {
                read_to_mat(f, &tab, del);
                mat_clear(&tab, tab.rows);
                close_file(f);
            }
            else
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
