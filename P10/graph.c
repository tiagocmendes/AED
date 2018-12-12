#include "graph.h"
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