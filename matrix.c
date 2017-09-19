/*
Gregory Macri

This program is used to generate matrices of a specified size, assign each index in the matrix a random number 
between one and ten, multiply those matrices a specified number of times and produce how long it took to multiply them in seconds.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

double mytime();//prototype for time function

int main(int argc, char *argv[])
{
  int i,j,n,r,z,t,sum;//variables for loops, n and r to store input
  n = atoi(argv[1]);//converts command line inputs to ints and stores
  r = atoi(argv[2]);//
  
  int *mata[n];//matrices 
  int *matb[n];//
  int *matc[n];//

  double elapsedTime, averageTime;
  double t1secs, t2secs;//stores start and end times

  for(i = 0; i < n; ++i)//allocates memory for matrices
  {
    mata[i] = (int *)malloc(n * sizeof(int));
    matb[i] = (int *)malloc(n * sizeof(int));
    matc[i] = (int *)malloc(n * sizeof(int));
  }

  for(i = 0; i < n; ++i)//sets each value in matrices randomly between 1 and 10
  {
    for(j = 0; j < n; ++j)
    {
      mata[i][j] = (rand()%10 + 1);
      matb[i][j] = (rand()%10 + 1);
    }
  }

  for(t = 0; t < r; ++t)//performs matrix multiplication r times
  {
    sum = 0;//sets the sum used for matrix multiplication to zero
    t1secs = mytime();//get start time in seconds

    for(i = 0; i < n; ++i)//performs matrix multiplication and stores in matc
    {
      for(z = 0; z < n; ++z)
      {
	for(j = 0; j < n; ++j)
	   sum += mata[i][j] * matb[j][z];
        
	matc[i][z] = sum;
	sum = 0;
      }
    }

    t2secs = mytime();//get end time
    elapsedTime = t2secs - t1secs;//compute difference

    averageTime += elapsedTime;//accumulate all computed times
  }
  
  averageTime = averageTime / r;//get average time
  printf("%d, %d, %lf\n",n,r,averageTime);//print n,r,and average time  
  
  for(i = 0; i < n; ++i)//free up memory from matrices
  {
    free(mata[i]);
    free(matb[i]);
    free(matc[i]);
  }

  return 0;
}

//gets the current time, converts to seconds and returns value as double
double mytime()
{
  struct timeval t1;
  gettimeofday(&t1,NULL);
  
  return t1.tv_sec + t1.tv_usec/1000000.0;
}
