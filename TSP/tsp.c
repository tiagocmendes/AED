//
// Students
// 88808 - João Miguel Nunes de Medeiros e Vasconcelos 
// 88886 - Tiago Carvalho Mendes
//
// AED, 2018/2019
//
// solution of the traveling salesman problem
//

#include <assert.h>
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

int computeTourLength(int n, int *a, int special)
{
  int i, tourLength = 0;

  for(i = 0;i < n-1;i++)
  {
    tourLength += cities[a[i]].distance[a[i+1]];
  }
  if(special == 0)
  { 
    return tourLength += cities[a[0]].distance[a[n-1]];
  }
  else
  {
    return tourLength += cities[a[n-1]].distance[a[0]];
  }
}

void updateLengths(int n, int tourLength, int *a)
{
  int i;

  if(tourLength < min_length)
  { // update min_length and min_tour
    min_length = tourLength;
    for(i = 0;i < n;i++)
     {
      min_tour[i] = a[i];
    }
  }
  else if(tourLength > max_length)
  { // update max_length and max_tour
    max_length = tourLength;
    for(i = 0;i < n;i++)
    {
      max_tour[i] = a[i];
    }
  }
}

void tsp_v1(int n,int m,int *a,int special)
{
  
  int i,t,tourLength;
 
  if(m < n - 1)
    for(i = m;i < n;i++)
    {
      t = a[m];
      a[m] = a[i];
      a[i] = t;
      tsp_v1(n,m + 1,a,special);
      t = a[m];
      a[m] = a[i];
      a[i] = t;
    }
  else
  { // visit permutation
    n_tours++;
    tourLength = computeTourLength(n,a,special);
    updateLengths(n,tourLength,a);  // update min_length, min_tour, max_length and max_tour
  }
}

void rand_perm(int n,int a[],int special)
{
  int i,j,k,tourLength;

  for(i = 0;i < n;i++)
  {
    a[i] = i;
  }
  for(i = n - 1;i > 0;i--)
  {
    j = (int)floor((double)(i + 1) * (double)rand() / (1.0 + (double)RAND_MAX)); // range 0..i
    assert(j >= 0 && j <= i);
    k = a[i];
    a[i] = a[j];
    a[j] = k;
  }
  n_tours++;
  tourLength = computeTourLength(n,a,special);
  updateLengths(n,tourLength,a);  // update min_length, min_tour, max_length and max_tour
}

//
// main program
//

int main(int argc,char **argv)
{
  int n_mec,special,n,i,random,a[max_n_cities];
  char file_name[64];
  double dt1;
  FILE *file;

  n_mec = 88886; // change later to n_mec = 88808 
  special = 1;   // if you want asymmetric distances, change this to special = 1;
  random = 0;    // if you want random permutations, change this to random = 1;
  init_cities_data(n_mec,special);
  printf("data for init_cities_data(%d,%d)\n",n_mec,special);
  fflush(stdout);

  // open data file and initialize it
  sprintf(file_name,"./Data/Special_%d/%d/%s.csv",special,n_mec,(random == 0) ? "tsp_data" : "tsp_random_data");
  file = fopen(file_name,"w");
  fprintf(file, "%s;%s;%s;%s;%s;%s\n","Number of cities (n)","Execution time (s)","minLength","minPath","maxLength","maxPath");
  
#if 0
  print_distances();
#endif
    for(n = 3;n <= 14/*n_cities*/;n++)
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

        // choose permutations type
        if(random == 0)
        {
          tsp_v1(n,1,a,special); // no need to change the starting city, as we are making a tour
        }
        else 
        { // random permutations
          for(i = 0;i < 1000000;i++)
          {
            rand_perm(n,a,special);
          }
        }
  
        dt1 = elapsed_time();
        printf("%d) tsp_v1() finished in %8.3fs (%ld tours generated)\n",n,dt1,n_tours);

        // print min_tour by index
        printf("  min %5d [",min_length);
        for(i = 0;i < n;i++)
        {
          printf("%2d%s",min_tour[i],(i == n - 1) ? "] - " : ",");
        }

        // print min_tour by city name
        for(i = 0;i < n;i++)
        {
          printf("%s%s", cities[min_tour[i]].name,(i == n - 1) ? "\n" : ",");
        }

        // print max_tour by index
        printf("  max %5d [",max_length);
        for(i = 0;i < n;i++)
        {
          printf("%2d%s",max_tour[i],(i == n - 1) ? "] - " : ",");
        }

        // print max_tour by city name
        for(i = 0;i < n;i++)
        {
          printf("%s%s", cities[max_tour[i]].name,(i == n - 1) ? "\n\n" : ",");
        }

        // save the computed data into a file
        fprintf(file,"%d;%8.3f;%d;[",n,dt1,min_length);
        for(i = 0; i < n;i++)
        {
          fprintf(file,"%d%s",min_tour[i],(i == n - 1) ? "];" : ",");
        }
        fprintf(file,"%d;[",max_length);
        for(i = 0; i < n;i++)
        {
          fprintf(file,"%d%s",max_tour[i],(i == n - 1) ? "]\n" : ",");
        }
        

        fflush(stdout);
        if(argc == 2 && strcmp(argv[1],"-f") == 0)
        {
          min_tour[n] = -1;
          sprintf(file_name,"./Maps/Special_%d/%d/%s/min_%02d.svg",special,n_mec,(random == 0) ? "Normal" : "Random",n);
          make_map(file_name,min_tour);
          max_tour[n] = -1;
          sprintf(file_name,"./Maps/Special_%d/%d/%s/max_%02d.svg",special,n_mec,(random == 0) ? "Normal" : "Random",n);
          make_map(file_name,max_tour);
        }      
      }
    }  
  fclose(file);
  return 0;
}
