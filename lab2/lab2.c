#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>


int main(int argc, char** argv)
{
    double start_time, end_time;
    int index  = -1 ;
    int count = 100*1000*1000;
    int *array = array = (int*)malloc(count*sizeof(int));
    for(int i=0; i<count; i++) { array[i] = rand()%10000; }
    int target = 100*1000*999;
    array[target]=target;
    int threads = 8;
    int k = 100000;
    int bob = count/k;
    int start,end;
    printf("time: %lf\t,index: %d\n",end_time-start_time,index);
    index = -1;
    start_time = omp_get_wtime();
    #pragma omp parallel num_threads(threads) shared(array,k,bob) private(end,start)
    {
        #pragma omp for
        for(int i=0; i < k ;i++)
        {
            if(index!=-1)continue;
            start = i*bob;
            end = (i+1)*bob;
            for(int j=start;j<end;j++)
            {
                if(index!=-1)break;
                if(array[j]==target)
                {
                    index=j;
                }
            }
        }
    }
    end_time = omp_get_wtime();
    printf("time: %lf\t,index: %d\n",end_time-start_time,index);
}
