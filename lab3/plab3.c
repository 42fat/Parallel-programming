
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define SWAP(A, B) { int t = A; A = B; B = t; }

// 2600
int main()
{
    FILE * fout;
    fout = fopen("report_fuLL_unsort.txt","w");

    int count = 100*1000;  

    int *array = array = (int*)malloc(count*sizeof(int));
    int *a = a = (int*)malloc(count*sizeof(int));

    for(int i=0; i<count; i++) { array[i] =  i; }
    //for(int i=0; i<count; i++) { array[i] = count - i; }
    //for(int i=0; i<count; i++) { array[i] = rand()%(count*100); }
    for(int i=0; i<count; i++) { a[i] = array[i]; }

    int threads = 16; 

    double start_time, end_time;
    for(int k = 1; k<=threads;k++)
    {
        start_time = omp_get_wtime();
        for(int s=count/2; s>0; s/=2){
            #pragma omp parallel num_threads(k) shared(array,count,s)
            {
                #pragma omp for 
                for(int i=0; i<count; i++){
                    for(int j=i+s; j<count; j+=s){
                        if(a[i] > a[j]){
                                SWAP(a[i],a[j]);
                        }
                    }
                }
            }
        }      
    }
    
    
    return 0;
}