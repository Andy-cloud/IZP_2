/**
 * file: sps.c
 * author: xdarmo03
 * date: 2020-11-27
 * description: 
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MIN_CELL 10

typedef struct
{
    int rows;
    int cols;
    char ***data;

} matrix_t;

typedef struct
{
    int row1;
    int col1;
    int row2;
    int col2;

} select_t;

select_t sel;

matrix_t mat_init()
{
    matrix_t tab;
    tab.cols = 0;
    tab.rows = 0;
    tab.data = NULL;
    return tab;
}
select_t sel_init()
{
    select_t sel;
    sel.col1 = 0;
    sel.row1 = 0;
    sel.row2 = 0;
    sel.col2 = 0;
    return sel;
}

void mat_clear(matrix_t *tab, int r, int c)
{
    tab->cols = 0;
    tab->rows = 0;
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            free(tab->data[i][j]);
        }
        free(tab->data[i]);
        //printf("Dealokace %d\n", i);
    }

    free(tab->data);
    //printf("Dealokace tabulky\n");
}
void mat_alloc(matrix_t *tab)
{
    tab->data = malloc(tab->rows * sizeof(char *));
    if (tab->data == NULL)
    {
        printf("Malloc fail!");
        return;
    }
    for (int i = 0; i < tab->rows; i++)
    {
        tab->data[i] = malloc(tab->cols * sizeof(char *));
        if (tab->data[i] == NULL)
        {
            printf("Malloc fail!");
            mat_clear(tab, i, 0);
            return;
        }
        for (int j = 0; j < tab->cols; j++)
        {
            tab->data[i][j] = calloc(1,MIN_CELL);
            if (tab->data[i][j] == NULL)
            {
                printf("Calloc fail!");
                mat_clear(tab, i, j);
                return;
            }
            //printf("Alokace se provedla %d %d\n", i, j);
        }
    }
}
int mat_reall(matrix_t *tab, int size, int row, int col)
{

    char *p = realloc(tab->data[row][col], sizeof(char) * size);
    if (p == NULL)
    {
        printf("Realloc fail!");
        mat_clear(tab, tab->rows, tab->cols);
        return 0;
    }
    tab->data[row][col] = p;
    return 1;
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
void count_rows_cols(FILE *f, matrix_t *tab, const char del[])
{
    char c;
    int cols = 0;
    while ((c = fgetc(f)) != EOF)
    {
        if (c == '\n')
        {
            tab->rows++;
            tab->cols = cols + 1;
            cols = 0;
        }

        if (strchr(del, c) != NULL)
        {
            //počet nalezených znaků delim
            cols++;
        }
    }
}
void read_to_mat(FILE *f, matrix_t *tab, const char del[])
{
    count_rows_cols(f, tab, del);

    printf("Pocet sloupcu: %d\n", tab->cols);
    printf("Pocet radku: %d\n", tab->rows);

    mat_alloc(tab);

    //printf("Alokace se provedla\n");

    fseek(f, 0, SEEK_SET);

    int row = 0;
    int col = 0;
    int size = 0;
    int is_delim = 0;
    char c;

    while ((c = fgetc(f)) != EOF)
    {

        if (c == '\n')
        {
            tab->data[row][col][size] = '\0';
            row++;
            col = 0;
            size = 0;
            is_delim = 1;
            if (row == tab->rows)
            {
                break;
            }
            if (!mat_reall(tab, MIN_CELL, row, col))
            {
                return;
            }
        }
        for (unsigned i = 0; i < strlen(del); i++)
        {
            if (del[i] == c)
            {
                tab->data[row][col][size] = '\0';
                col++;
                size = 0;
                is_delim = 1;
                if (!mat_reall(tab, MIN_CELL, row, col))
                {
                    return;
                }
                break;
            }
            else
            {
                is_delim = 0;
            }
        }

        if (!is_delim)
        {
            if (c != '\n')
            {

                tab->data[row][col][size] = c;
                size++;
                if (size >= MIN_CELL)
                {
                    if (!mat_reall(tab, size + 1, row, col))
                    {
                        return;
                    }
                }
            }
        }
    }
}
void mat_add_row(matrix_t *tab, int where)
{
    char ***p_row;
    char **p_col;
    char *p_cell;
    tab->rows += 1;
    //where -= 1; // vloží řádek před určitý řádek
    //rozšíření pole s řádky
    p_row = realloc(tab->data, sizeof(char *) * tab->rows);
    if (p_row == NULL)
    {
        printf("Realloc fail!");
        mat_clear(tab, tab->rows-1, tab->cols);
        return;
    }
    else
        tab->data = p_row;
    //posunutí prvků pro vložení nového řádku na určité místo
    for (int i = tab->rows - 1; i > where; i--)
    {
        tab->data[i] = tab->data[i - 1];
    }
    //alokace pole sloupců pro nový řádek
    p_col = malloc(sizeof(char *) * tab->cols);
    if (p_col == NULL)
    {
        printf("Malloc fail!");
        mat_clear(tab, tab->rows-1, tab->cols);
        return;
    }
    else
        tab->data[where] = p_col;

    //alokoce nových stringů
    for (int j = 0; j < tab->cols; j++)
    {

        p_cell = calloc(1, MIN_CELL);
        if (p_cell == NULL)
        {
            printf("Calloc fail!");
            mat_clear(tab, tab->rows-1, tab->cols);
            return;
        }
        else
            tab->data[where][j] = p_cell;
    }
}

void mat_add_col(matrix_t *tab, int where)
{
    char **p_col;
    char *p_cell;

    tab->cols += 1;
    //where -= 1;

    for (int i = 0; i < tab->rows; i++)
    {
        p_col = realloc(tab->data[i], tab->cols * sizeof(char *));
        if (p_col == NULL)
        {
            printf("Realloc fail!");
            mat_clear(tab, tab->rows, tab->cols-1);
            return;
        }
        else
        {
            tab->data[i] = p_col;
        }
        for (int j = tab->cols - 1; j > where; j--)
        {
            tab->data[i][j] = tab->data[i][j - 1];
        }
        p_cell = calloc(1, MIN_CELL);
        if (p_cell == NULL)
        {
            printf("Realloc fail!");
            mat_clear(tab, tab->rows, tab->cols-1);
            return;
        }
        else
        {
            tab->data[i][where] = p_cell;
        }
    }
}
void sel_cells(char *command, int len)
{
    sel.col1 = 0;
    sel.row1 = 0;
    sel.row2 = 0;
    sel.col2 = 0;
    int count = 0;

    for (int i = 0; i < len; i++)
    {
        if ((command[i] != ',') && (command[i] != '[') && (command[i] != ']'))
        {
            if (command[i] != '_')
            {
                switch (count)
                {
                case 1:
                    sel.row1 = command[i] - '0';
                    break;
                case 2:
                    sel.col1 = command[i] - '0';
                    break;
                case 3:
                    sel.row2 = command[i] - '0';
                    break;
                case 4:
                    sel.col2 = command[i] - '0';
                    break;
                default:
                    break;
                }
            }
        } else if (command[i]==',')
        {
            count++;
        }
        
    }
}
void cho_fun(char *command, matrix_t *t)
{
    if ((command[0] == '[') && (command[strlen(command) - 1] == ']'))
    {
        sel_cells(command, strlen(command));
    }
    if (!strcmp(command, "irow"))
    {
        mat_add_row(t, sel.row1);
    }
    if (!strcmp(command, "arow"))
    {
        if (sel.row2 != 0)
        {
            mat_add_row(t, sel.row2);
        }
        else
        {
            mat_add_row(t, sel.row1);
        }
    }
    if (!strcmp(command, "icol"))
    {
        mat_add_col(t, sel.col1);
    }
    if (!strcmp(command, "acol"))
    {
        if (sel.col2 != 0)
        {
            mat_add_col(t, sel.col2);
        }
        else
        {
            mat_add_col(t, sel.col1);
        }
    }
}
void cmd_sequence(const char arg[], matrix_t *t)
{
    char cmd[1000];
    unsigned int i;
    for (i = 0; i < strlen(arg); i++)
    {
        cmd[i] = arg[i];
    }
    cmd[i++] = '\0';
    char *tok;

    tok = strtok(cmd,";");

    while (tok != NULL)
    {
        
        cho_fun(tok, t);
        tok = strtok(NULL,";");
    }
}
void close_file(FILE *f)
{
    printf("Soubor zavren!\n");
    fclose(f);
}
void mat_print(FILE *f, matrix_t *t, char del)
{
    int col = 0;
    for (int i = 0; i < t->rows; i++)
    {
        for (int j = 0; j < t->cols; j++)
        {
            fprintf(f, "%s", t->data[i][j]);
            col++;
            if (col < t->cols)
            {
                fprintf(f, "%c", del);
            }
        }
        col = 0;
        fprintf(f, "\n");
    }
}

int main(int argc, char const **argv)
{
    if (argc > 2)
    {
        FILE *f;
        matrix_t tab;
        char fin_del;
        tab = mat_init();
        sel = sel_init();
        if (open_file(&f, argv[argc - 1], "r"))
        {
            if ((strcmp(argv[1], "-d")) && (argc == 3))
            {
                const char *del = " ";
                fin_del = del[0];
                read_to_mat(f, &tab, del);
            }
            if ((!strcmp(argv[1], "-d")) && (argc == 5))
            {
                const char *del = argv[2];
                fin_del = del[0];
                read_to_mat(f, &tab, del);
            }
            close_file(f);
            cmd_sequence(argv[argc - 2], &tab);
            open_file(&f, argv[argc - 1], "w");
            mat_print(f, &tab, fin_del);
            mat_clear(&tab, tab.rows, tab.cols);
            close_file(f);
        }
        else
        {
            return 1;
        }
    }

    return 0;
}
