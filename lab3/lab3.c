#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define SWAP(A, B) { int t = A; A = B; B = t; }
/* 23 */
int main()
{
    int count = 10 ;
    int j,n,nn;
    n =count;
    int *array = array = (int*)malloc(count*sizeof(int));
    
    for(int i=0; i<count; i++) { array[i] = rand()%10000; }

    double start_time, end_time;
    start_time = omp_get_wtime();

    for(int s=count/2; s!=1; s/=2){
        for(int i=0; i<count; i++){
            for(int j=i+s; j<count; j+=s){
                if(array[i] > array[j]){
                   SWAP(array[i],array[j]);
                }
            }
        }
    }
    end_time = omp_get_wtime();
     printf("\ntime : %lf\n",end_time-start_time);
    return 0;
}




