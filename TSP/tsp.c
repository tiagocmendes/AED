//
// Students
// 88808 - João Miguel Nunes de Medeiros e Vasconcelos 
// 88886 - Tiago Carvalho Mendes
//
// AED, 2018/2019
//
// solution of the traveling salesman problem
//

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/resource.h>

#include "cities.h"
#include "elapsed_time.h"


//
// record best solutions
//

static int min_length,max_length;
static int min_tour[max_n_cities + 1],max_tour[max_n_cities + 1];
static long n_tours;

//
// first solution (brute force, distance computed at the end, compute best and worst tours)
//

void tsp_v1(int n,int m,int *a)
{

  
  FILE *file;
  int i,j,t;
  int tourLength = 0;
  file = fopen("test.csv", "a+");// a maneira como eu estruturei o codigo tive que fazer 'a+' em vez de 'w' para ir adicionando em cada linha a nova tour
 
  if(m < n - 1)
    for(i = m;i < n;i++)
    {
      t = a[m];
      a[m] = a[i];
      a[i] = t;
      tsp_v1(n,m + 1,a);
      t = a[m];
      a[m] = a[i];
      a[i] = t;
      
    }
  else
  { // visit permutation
    n_tours++;
    for(j = 0;j < n-1;j++)
    { // compute tourLength
      tourLength += cities[a[j]].distance[a[j+1]];
      
    }
    if(n==11){
      fprintf(file,"%5d \n",tourLength);//se quiseres correr mais que n=11 eliminar codigo de escrever no file
    }
    if(tourLength < min_length)
    { // update min_length and min_tour
      min_length = tourLength;
      for(j = 0;j < n;j++)
      {
        min_tour[j] = a[j];
      }
    }
    else if(tourLength > max_length)
    { // update max_length and max_tour
      max_length = tourLength;
      for(j = 0;j < n;j++)
      {
        max_tour[j] = a[j];
      }
    }
  }
  fclose(file);
}


//
// main program
//

int main(int argc,char **argv)
{
  int n_mec,special,n,i,a[max_n_cities];
  char file_name[32];
  double dt1;

  n_mec = 88886; // change later to n_mec = 88808 
  special = 0;
  init_cities_data(n_mec,special);
  printf("data for init_cities_data(%d,%d)\n",n_mec,special);
  fflush(stdout);
#if 0
  print_distances();
#endif
  for(n = 3;n <= 11/*n_cities*/;n++)  // n_cities == 13 to reduce time execution
  {
    //
    // try tsp_v1
    //
    dt1 = -1.0;
    if(n <= 16)
    {
      (void)elapsed_time();
      for(i = 0;i < n;i++)
        a[i] = i;
      min_length = 1000000000;
      max_length = 0;
      n_tours = 0l;
      tsp_v1(n,1,a); // no need to change the starting city, as we are making a tour
      dt1 = elapsed_time();
      printf("tsp_v1() finished in %8.3fs (%ld tours generated)\n",dt1,n_tours);
      printf("  min %5d [",min_length);
      for(i = 0;i < n;i++)
      {
        printf("%2d%s",min_tour[i],(i == n - 1) ? "] - " : ",");
      }
      for(i = 0;i < n;i++)
      {
        printf("%s%s", cities[min_tour[i]].name,(i == n - 1) ? "\n" : ",");
      } 
      printf("  max %5d [",max_length);
      for(i = 0;i < n;i++)
      {
        printf("%2d%s",max_tour[i],(i == n - 1) ? "] - " : ",");
      }
      for(i = 0;i < n;i++)
      {
        printf("%s%s", cities[max_tour[i]].name,(i == n - 1) ? "\n" : ",");
      } 
      fflush(stdout);
      if(argc == 2 && strcmp(argv[1],"-f") == 0)
      {
        min_tour[n] = -1;
        sprintf(file_name,"min_%02d.svg",n);
        make_map(file_name,min_tour);
        max_tour[n] = -1;
        sprintf(file_name,"max_%02d.svg",n);
        make_map(file_name,max_tour);
      }
    }
  }
  return 0;
}
