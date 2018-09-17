//
// Tomás Oliveira e Silva, AED, September 2014, September 2017
//
// program to print a table of the squares and square roots of some integers
//
// on GNU/Linux, run the command
//   man 3 printf
// to see how the manual page of the printf function
//

#include <math.h>
#include <stdio.h>

double d2r(double d){
  // fucntion to convert degrees into radians
  return d*(M_PI/180.0);
}

void do_it(int N)
{
  int i;
  FILE *fp;
  fp = fopen ("table.txt","w");
  
  printf(" n n*n      sqrt(n)\n");
  printf("-- --- -----------------\n");
  for(i = 1;i <= N;i++)
    printf("%2d %3d %17.15f\n",i,i * i,sqrt((double)i));
  
  printf("\nangle     sin     cos\n");
  printf("---------------------\n");
  for(i = 1;i <= 90;i++)
  {
    printf("%-5d %5.5f %5.5f\n",i,sin(d2r(i)),cos(d2r(i)));       // print in the terminal
    fprintf(fp, "%-5d %5.5f %5.5f\n",i,sin(d2r(i)),cos(d2r(i)));  // write to the file
  }
  fclose(fp);
}

int main(void)
{
  do_it(10);
  return 0;
}
