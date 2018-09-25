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

double degree_to_radians(int i) {
	return i*M_PI/180.0;
}

void do_it(int N)
{
  int i;
  FILE *fd = fopen("table.txt", "w");

  fprintf(fd, " n sin   cos\n");
  fprintf(fd, "-- ----- -----\n");
  for(i = 0;i <= N;i++)
    fprintf(fd, "%2d %5.2f %5.2f\n",i,sin(degree_to_radians(i)), cos(degree_to_radians(i)));
  fclose(fd);
}

int main(void)
{
  do_it(90);
  return 0;
}
