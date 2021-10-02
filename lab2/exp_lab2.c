#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>


void check()
{
    printf("OpenMP: %d;\n", _OPENMP);
    printf("===============\n");
    int n,m,k;
    n = omp_get_thread_num();
    m = omp_get_max_threads();
    printf("Максимальное число потоков %d\n", m);
    printf("Текущий поток  %d\n", n);
    printf("===============\n");
}

double parl_time(int* array,int count,int threads ,int target,FILE* fout)
{
    int index = -1;
    int k = 100000;
    int bob = count/k;
    int start,end;
    double start_time , end_time;
    start_time = omp_get_wtime();
    #pragma omp parallel num_threads(threads) shared(array,k,bob)
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
    //printf("time: %lf\t,index: %d\n",end_time-start_time,index);
   // fprintf(fout,"index: %d\t target: %d\t time: %lf\t,threads: %d\n",index,target,end_time-start_time,threads);
    return end_time-start_time;
}
int* rand_massive(int count, int seed)
{
    srand(seed);
    int* array =0;
    array = (int*)malloc(count*sizeof(int));
    for(int i=0; i<count; i++) { array[i] = rand()%55555; }
    return array;
}

void print_massive_time(double** array, int k,FILE * fout)
{
    double* p_array = (double*)array;
    int threads = 2*omp_get_max_threads();
    double avg_SUM = 0;
    //fprintf(fout,"Число ->\n");
    //  for (int i = 0; i<threads; i++)
    // {
    //     fprintf(fout,"%d\t", i+1);
    // }
    fprintf(fout,"\n");
    for (int i = 0; i<threads; i++)
    {
        for(int j = 0; j < k; j++)
        {
        //printf("Число %d : время %lf\n", i+1,p_array[i*10+j]);
        avg_SUM = avg_SUM +p_array[i*10+j];
        }
        avg_SUM = avg_SUM/k;
        fprintf(fout,"%lf\t" ,avg_SUM);
    }
    //fprintf(fout,"\n<-Среднее время");
    fprintf(fout,"\n");
}
void printl()
{
    FILE * fin , *fout;
    int c, retval;
    fin = fopen("report.txt","r+");
    fout = fopen("r.txt","w");
    while ((c = getc(fin)) != EOF) {
        if (c == '.')
            retval = putc(',', fout);
        else
            retval = putc(c, fout);
        if (retval == EOF)
            break;
    }
    fclose(fout);
    fclose(fin);
}

void experiment(int seed,int count, double** time_massive_parl ,int k,int* array,int target,FILE* fout)
{
    double* time_array = (double*)time_massive_parl;
    int j = 2*omp_get_max_threads();
    for(int i= 0; i < j ; i++)
    {
       time_array[i*10+k]=parl_time(array,count,i+1,target,fout);
    }
}





int main(int argc, char** argv)
{
    FILE * fout;
    fout = fopen("report.txt","w");
    const int count = 2*1*1000*1000;
    int prev_seed = 0 ;
    int seed = 0;
    int j = 2*omp_get_max_threads();
    int times = 100;
    double time_massive_parl[j][times];
    check();
    int* array;
    int target;
    for (int i = 0; i < times ; i++)
    {
        int* array;
        seed = rand()%11111;
        target = 1*1000*1000-1;
        array=rand_massive(count,seed);
        while(seed == prev_seed)
        {
            seed = rand()%11111;
            free(array);
            array=rand_massive(count,seed);
        }
        prev_seed = seed;
        array[target]=target;
        //printf("target %d\n" , target);
        //printf("array %d\n",array[target]);
        printf("Seed %d\n" , i+1);
        //fprintf(fout,"%d :Seed: %d \n",i+1,seed);
        experiment(seed,count,(double**)time_massive_parl,i,array,target,fout);
        free(array);
    }
    print_massive_time((double**)time_massive_parl,times,fout);
    fclose(fout);
    printl();
    return(0);
}