#include <stdio.h>
#include <stdlib.h>
#include "lab1_IO.h"
#include "timer.h"
#include <pthread.h>
#include <math.h>

struct thread_needed_info{
    pthread_t tid;
    int s;
    int i;
    int j;
    int done;
};

int **A; int **B; int **C; int n; int m; int q;

void get_i_and_j(int s, int* i, int* j){
    (*i) = floor(s / (n/q)) * q;
    (*j) = (s*q) % n;
}

int calculate_sum(int a, int b){
    int sum = 0;

    int iter;
    for (iter = 0; iter < n; iter++){
        sum += A[a][iter] * B[iter][b];
    }

    return sum;
}

void* thread(void* ptr){
    struct thread_needed_info *th = (struct thread_needed_info *) ptr;
    
    int i = th->i;
    int j = th->j;

    int a;
    int b;

    for (a = i; a<i+q; a++){
        for (b = j; b<j+q; b++){
            int summ = calculate_sum(a,b);
            C[a][b] = summ;
        }
    }

    th->done = 1;

    return ptr;
} 


int main(int argc, char const *argv[]){
    double start;
    GET_TIME(start);

    if (argc != 2){
        printf("Invalid Number of Arguments\n");
        exit(0);
    }

    int p = atoi(argv[1]);

    if (p <= 0){
        printf("Invalid argument\n");
        exit(0);
    }

    int root_p = sqrt(p);

    if (root_p * root_p != p){
        printf("Number of threads is not a square number\n");
        exit(0);
    }

    Lab1_loadinput(&A, &B, &n);

    if (((n*n) % p ) !=0){
        printf("n squared is not divisible by the number of threads\n");
        exit(0);
    }

    m = n / p;

    q = sqrt((n*n)/p);


    C = malloc(n * sizeof(int*));

    int g;
    for (g = 0; g < n; g++)
        C[g] = malloc(n * sizeof(int));

    struct thread_needed_info threads[p];

    int s;
    for (s=0; s<p; s++){
        int i; 
        int j;
        get_i_and_j(s, &i, &j);
        struct thread_needed_info th;
        th.i = i;
        th.j = j;
        th.tid = -1;
        th.done = 0;
        th.s = s;
        threads[s] = th;
    }


    for (s=0; s<p; s++){
        pthread_create(&threads[s].tid, NULL, thread, &threads[s]);
    }

    while(1){
        int all_done =1;

        for (s=0; s<p; s++){
            if (threads[s].done == 0){
                all_done = 0;
            }
        }

        if(all_done){
            break;
        }
    }


    double end;
    GET_TIME(end);
    
    Lab1_saveoutput(C, &n, end-start);

    return 0;
}
