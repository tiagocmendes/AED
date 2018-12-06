#include <stdio.h>

int numWays(int n, int x, int y)
{

    if(x == 0 && y == 0) {
        return 1;
    } 
    else if( (x < 0 || y < 0 || x > n || y > n) )
    {
        return 0;
    }
    else
    {
        return numWays(n,x-1,y) + numWays(n,x,y-1) + numWays(n,x-2, y-1) + numWays(n,x-1,y -2);
    }
}

int main(int argc, char const *argv[])
{
    int i;
    for(i = 1; i <= 25; i++)
    {
        printf("(%d) Number of ways: %d\n",i,numWays(i+1,i,i));
    }
    return 0;
}
