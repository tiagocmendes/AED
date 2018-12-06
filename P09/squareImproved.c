#include <stdio.h>

#define N 64
unsigned long long matriz[N][N];

unsigned long long numWays(unsigned long long x, unsigned long long y)
{

    if(x == 0 && y == 0) {
        return 1;
    } 
    else if( (x < 0 || y < 0 || x >= N || y >= N) )
    {
        return 0;
    }
    else
    {
        if(matriz[x][y] != 0)
        {
            return matriz[x][y];
        }
        matriz[x][y] = numWays(x-1,y) + numWays(x,y-1) + numWays(x-2, y-1) + numWays(x-1,y -2);
        return matriz[x][y];
    }
}

int main(int argc, char const *argv[])
{
    unsigned long long i;
    for(i = 1; i < N; i++)
    {
        printf("(%lld) Number of ways: %lld\n",i,numWays(i,i));
    }
    return 0;
}
