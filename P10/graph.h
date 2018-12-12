#ifndef GRAPH_H_
#define GRAPH_H_

typedef struct vertice {
    int x;
    int y;
} vertice;

vertice *create_vertice(int x, int y);
void sprint_vertice(char *str, vertice *v);
void free_vertice(vertice *);

#endif