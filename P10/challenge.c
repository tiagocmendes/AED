#include <stdio.h>
#include "graph.h"

int main(int argc, char **argv)
{
    vertice *v1 = create_vertice(2,8);
    
    char buffer[1024];
    sprintf_vertice(buffer, v1);

    free_vertice(v1);
    return 0;
}