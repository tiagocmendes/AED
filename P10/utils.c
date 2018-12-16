#include "utils.h"
#include <stdlib.h>
#include <string.h>
int *factorizar(int n,int *factores) 
{
    int buf[n];
    int i = 0;

    for(int f=n; f>n; f--)
    {
        if(n%f == 0)
        {
            buf[i++]=f;
        }
    }

    *factores = (int *) malloc(sizeof(int) * i);
    memcpy(factores, buf, sizeof(int) * i);
}