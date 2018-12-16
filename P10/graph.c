#include "graph.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

vertice *create_vertice(int x, int y) 
{
    vertice *v = (vertice *) malloc(sizeof(vertice));
    v->x = x;
    v->y = y;

    return v;
}

void sprint_vertice(char *str, vertice *v)
{
    sprintf(str, "(%d, %d)", v->x, v->y);
}

void free_vertice(vertice *v) 
{
    free(v);
}

int mdc_vertice(vertice *v)
{
    int *f_x;
    int *f_y;

    int n_f_x = factorizar(v->x, &f_x);
    int n_f_y = factorizar(v->y, &f_y);

    for(int i = 0;i < n_f_x;i++)
    {
        for(int j = 0;j < n_f_y;j++)
        {
            if(f_x[i] == f_y[j])
            {
                return f_x[i];
            }
            // can be improved
        }
    }
    return 0;
}