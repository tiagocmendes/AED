#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "utils.h"

int main(int argc, char **argv)
{
    vertice *v1 = create_vertice(2,8);
    
    char buffer[1024];
    sprint_vertice(buffer, v1);
    printf("Vertice coordinates = %s\n",buffer);

    int *factores;
    int n = factorizar(30, &factores);
    for(int i = 0; i < n; i++)
    {
        printf("%d\n", factores[i]);
    }
    free_vertice(v1);
    return 0;
}