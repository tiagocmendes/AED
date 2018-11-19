//
// Tomás Oliveira e Silva, AED, November 2018
//
// This program implements a simple sieve of Eratosthenes.
// Use the valgrind program to check it.
//

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  const int limit = 1000000;
  char *sieve;

  sieve = (char *)calloc((size_t)limit,sizeof(char));
  if(sieve == NULL)
    return 1;
  sieve[0] = sieve[1] = 1; // 0 and 1 are not prime
  for(int p = 2;p * p < limit;p++)
    if(sieve[p] == 0)
      for(int i = p * p;i < limit;i += p)
        sieve[i] = 1; // i is not prime
  int c = 0;
  for(int i = 0;i < limit;i++)
    if(sieve[i] == 0)
      c++;
  printf("There are %d prime numbers up to %d\n",c,limit);
  free(sieve);
  return 0;
}
