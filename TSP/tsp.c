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

int computeTourLength(int n, int *a)
{
  int i, tourLength = 0;

  for(i = 0;i < n-1;i++)
  {
    tourLength += cities[a[i]].distance[a[i+1]];
  }
  return tourLength += cities[a[0]].distance[a[n-1]];
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

void tsp_v1(int n,int m,int *a)
{
  
  int i,t,tourLength;
 
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
    tourLength = computeTourLength(n,a);
    updateLengths(n,tourLength,a);  // update min_length, min_tour, max_length and max_tour
  }
}

void rand_perm(int n,int a[])
{
  int i,j,k;

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
}

//
// main program
//

int main(int argc,char **argv)
{
  int n_mec,special,n,i ,a[max_n_cities],a_simu[max_n_cities],repetitions=1000000,tourlengthsimu;//number of repetitions for the simulation
  char file_name[32];
  double dt1;
  

  n_mec = 88886; // change later to n_mec = 88808 
  special = 0;
  init_cities_data(n_mec,special);
  printf("data for init_cities_data(%d,%d)\n",n_mec,special);
  fflush(stdout);

  // open a file and initialize it
  FILE *file;
  file = fopen("tsp_data.csv", "w");
  fprintf(file, "%s;%s;%s;%s;%s;%s\n","Number of cities (n)","Execution time (s)","minLength","minPath","maxLength","maxPath");

#if 0
  print_distances();
#endif
  for(n = 3;n <= 7/*n_cities*/;n++)  // n_cities == 13 to reduce time execution
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


      min_length = 1000000000; //renitialize the variables so we can compute min_length and max_length for the simulation
      max_length = 0;
      for(int k=0;k<=repetitions;k++){
        rand_perm(n,a_simu);// permutation with n-1 numbers
        tourlengthsimu = computeTourLength(n,a_simu);
        updateLengths(n,tourlengthsimu,a_simu);  // update min_length, min_tour, max_length and max_tour
       
      }
      //simulation print
      // print min_tour by index
      printf("Simulação com %8d repetições \n",repetitions);
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
        sprintf(file_name,"./Maps/min_%02d.svg",n);
        make_map(file_name,min_tour);
        max_tour[n] = -1;
        sprintf(file_name,"./Maps/max_%02d.svg",n);
        make_map(file_name,max_tour);
      }

      // random permutations
      
    }
  }
  fclose(file);
  return 0;
}
